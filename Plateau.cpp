#include "Plateau.h"
#include <QDebug>
#include <QLabel>
//#include <QGraphicsDropShadowEffect>
#include <QEvent>

//extern Jeu* jeu;

using iter::range;
//using Ui::Case;
using model::Tour;
using model::Roi;
//using Ui::VuePieceEchec;
using model::ModelPieceEchec;

//using ui::Case, ui::Jeu;

Plateau::Plateau(/*Ui::InterfaceJeu* jeu*/)
{
	//qDebug() << "plateau : " << jeu->ab;
	/*ptrJeu_ = jeu;*/
	creeCases();
	creePiecesNoir();
	creePieceBlanc();
	mettreLesPieces();
}

void Plateau::creeCases() {
	
	for (int ligne : range(8)) {

		for (int colone : range(8)) {

			std::unique_ptr<model::ModelCase> uneCase = std::make_unique<model::ModelCase>(ligne, colone);

			listeCases.push_back(move(uneCase));
		}
	}
	//ListeCase[3 * 8 + 3]->mettreCouleur(Qt::green);

}

void Plateau::creePiecesNoir()
{
	std::unique_ptr<ModelPieceEchec> tourN = std::make_unique<Tour>("Noir");
	ListePieceNoir.push_back(move(tourN));

	std::unique_ptr<ModelPieceEchec> tourN1 = std::make_unique<Tour>("Noir");
	ListePieceNoir.push_back(move(tourN1));

	std::unique_ptr<ModelPieceEchec> roiN = std::make_unique<Roi>("Noir");
	ListePieceNoir.push_back(move(roiN));
	
}

void Plateau::creePieceBlanc()
{
	std::unique_ptr<ModelPieceEchec> tourB = std::make_unique<Tour>("Blanc");
	ListePieceBlanc.push_back(move(tourB));

	std::unique_ptr<ModelPieceEchec> tourB1 = std::make_unique<Tour>("Blanc");
	ListePieceBlanc.push_back(move(tourB1));

	std::unique_ptr<ModelPieceEchec> roiB = std::make_unique<Roi>("Blanc");
	ListePieceBlanc.push_back(move(roiB));

	try {
		std::unique_ptr<ModelPieceEchec> roiB2 = std::make_unique<Roi>("Blanc");
	}
	catch (std::logic_error& e) {
		qDebug() << "Erreur : " << e.what();
	}
	
}

void Plateau::mettreLesPieces()
{
	model::ModelCase* tempCase = nullptr;
	ModelPieceEchec* tempPiece = nullptr;
	int i = 0;
	
	for (auto&& j = ListePieceNoir.begin(); j != ListePieceNoir.end(); j++) {
			
		tempCase = listeCases[i++];
		tempPiece = j->get();

		tempCase->mettrePiece(tempPiece);
		
		tempPiece->positionner(tempCase->lirePosition(), tempCase->lirePixelPos());
			
	}
	

	i = 0;
	
	for (auto&& j = ListePieceBlanc.begin(); j != ListePieceBlanc.end(); j++) {

		tempCase = listeCases[56 + i++];
		tempPiece = j->get();// ListePieceNoir[i * 8 + j].get();

		tempCase->mettrePiece(tempPiece);

		tempPiece->positionner(tempCase->lirePosition(), tempCase->lirePixelPos());

	}
	
}



void Plateau::recevoirCaseClique(model::ModelCase* caseClique)
{
	if ((pieceActuelle_ != nullptr) && (caseClique->getPiece() == nullptr) && (pieceActuelle_->deplacementEstValide(caseClique->lirePosition())))
	{
		listeCases(pieceActuelle_->lireMatricePos().ligne, pieceActuelle_->lireMatricePos().colone)->enleverPiece();

		qDebug() << "indice tableau case : " << pieceActuelle_->lireMatricePos().ligne + 8 * pieceActuelle_->lireMatricePos().colone;

		caseClique->mettrePiece(pieceActuelle_);
		pieceActuelle_->positionner(caseClique->lirePosition(), caseClique->lirePixelPos());
		
		couleurPlateauInitial();
		pieceActuelle_ = nullptr;

	}
}



void Plateau::recevoirPieceClique(Ui::VuePieceEchec* piece)
{
	couleurPlateauInitial();
	model::ModelPieceEchec* pieceClique = piece->lirePiece();

	if ((pieceActuelle_ != nullptr) && (pieceClique->lireEquipe() != pieceActuelle_->lireEquipe())) {
		if (pieceActuelle_->deplacementEstValide(pieceClique->lireMatricePos())) {

			listeCases(pieceActuelle_->lireMatricePos().ligne, pieceActuelle_->lireMatricePos().colone)->enleverPiece();
			listeCases(pieceClique->lireMatricePos().ligne, pieceClique->lireMatricePos().colone)->mettrePiece(pieceActuelle_);

			pieceActuelle_->mangeLaPiece(pieceClique);
			pieceActuelle_ = nullptr;
		}
	}
	else {
		pieceActuelle_ = pieceClique;
		couleurSurCaseValide(pieceClique->listerDeplacementsValides(listeCases));

	}
	qDebug() << "on Save";
}

void Plateau::couleurSurCaseValide(std::list<model::EmplacementValide> listeEmplacements)
{
	for (auto&& caseValide : listeEmplacements) {
		emit listeCases(caseValide.ligne, caseValide.colone)->mettreCouleur(caseValide.couleur);
	}

}

void Plateau::couleurPlateauInitial() {
	
	qDebug() << "seze : " << listeCases.listeCases.size();
	for (auto&& box : listeCases) {
		emit box->mettreCouleurBase();
	}
	
}

void Plateau::enleverPieceElimine(model::ModelPieceEchec* piece)
{
	if (piece->lireEquipe() == "Noir")
	{
		for (auto&& it = ListePieceNoir.begin(); it != ListePieceNoir.end(); it++) {
			if (it->get() == piece) {
				qDebug() << "enleve du vector";
				*it = nullptr;
			}
		}
	}
	else
	{
		for (auto&& it = ListePieceBlanc.begin(); it != ListePieceBlanc.end(); it++) {
			if (it->get() == piece) {
				qDebug() << "enleve du vector";
				*it = nullptr;
			}
		}
	}
}




//void Plateau::mouseMoveEvent(QGraphicsSceneMouseEvent* event) {
//	// if there is a cardToPlace, then make it follow the mouse
//	if (pieceActuelle_ != nullptr) {
//		pieceActuelle_->setPos(event->scenePos().x() - 45, event->scenePos().y() - 45);
//		qDebug() << "piece move" << event->pos();
//
//	}
//
//	qDebug() << "move";
//}

