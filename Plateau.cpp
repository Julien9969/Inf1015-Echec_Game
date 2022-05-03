#include "Plateau.h"
#include <QDebug>
#include <QLabel>
#include <QEvent>


using iter::range;
using model::Tour;
using model::Roi;
using model::Fou;
using model::ModelPieceEchec;
using model::Plateau;

Plateau::Plateau()
{
	creeCases();
	creePiecesNoir();
	creePieceBlanc();
	mettreLesPieces();
}

void Plateau::creeCases() 
{
	for (int ligne : range(8)) {

		for (int colone : range(8)) {

			std::unique_ptr<model::ModelCase> uneCase = std::make_unique<model::ModelCase>(ligne, colone);

			listeCases.push_back(move(uneCase));
		}
	}
}

void Plateau::creePiecesNoir()
{
	std::unique_ptr<ModelPieceEchec> tourN = std::make_unique<Tour>("Noir");
	ListePieceNoir.push_back(move(tourN));

	std::unique_ptr<ModelPieceEchec> tourN1 = std::make_unique<Tour>("Noir");
	ListePieceNoir.push_back(move(tourN1));

	std::unique_ptr<ModelPieceEchec> roiN = std::make_unique<Roi>("Noir");
	ListePieceNoir.push_back(move(roiN));

	std::unique_ptr<ModelPieceEchec> fouN = std::make_unique<Fou>("Noir");
	ListePieceNoir.push_back(move(fouN));

	std::unique_ptr<ModelPieceEchec> fouN1 = std::make_unique<Fou>("Noir");
	ListePieceNoir.push_back(move(fouN1));
}

void Plateau::creePieceBlanc()
{
	std::unique_ptr<ModelPieceEchec> tourB = std::make_unique<Tour>("Blanc");
	ListePieceBlanc.push_back(move(tourB));

	std::unique_ptr<ModelPieceEchec> tourB1 = std::make_unique<Tour>("Blanc");
	ListePieceBlanc.push_back(move(tourB1));

	std::unique_ptr<ModelPieceEchec> roiB = std::make_unique<Roi>("Blanc");
	ListePieceBlanc.push_back(move(roiB));

	std::unique_ptr<ModelPieceEchec> fouB = std::make_unique<Fou>("Blanc");
	ListePieceBlanc.push_back(move(fouB));

	std::unique_ptr<ModelPieceEchec> fouB1 = std::make_unique<Fou>("Blanc");
	ListePieceBlanc.push_back(move(fouB1));

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
		tempPiece = j->get();

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

		tourDeJeuChangement(pieceActuelle_->lireEquipe());

		couleurPlateauInitial();
		pieceActuelle_ = nullptr;

	}
}



void Plateau::recevoirPieceClique(model::ModelPieceEchec* pieceClique)
{
	couleurPlateauInitial();

	qDebug() << "tour : " << QString::fromStdString(tourDeJeu.tour) << " joue " << QString::fromStdString(pieceClique->lireEquipe());

	if ((pieceActuelle_ != nullptr) && (pieceClique->lireEquipe() != pieceActuelle_->lireEquipe())) {
		if (pieceActuelle_->deplacementEstValide(pieceClique->lireMatricePos())) {

			listeCases(pieceActuelle_->lireMatricePos().ligne, pieceActuelle_->lireMatricePos().colone)->enleverPiece();
			listeCases(pieceClique->lireMatricePos().ligne, pieceClique->lireMatricePos().colone)->mettrePiece(pieceActuelle_);

			pieceActuelle_->mangeLaPiece(pieceClique);
			tourDeJeuChangement(pieceActuelle_->lireEquipe());
			pieceActuelle_ = nullptr;
		}
	}
	else if (tourDeJeu == pieceClique->lireEquipe()) {
		pieceActuelle_ = pieceClique;
		pieceClique->listerDeplacementsValides(listeCases);
		couleurSurCaseValide(pieceClique->lireEmplacementValide());
		qDebug() << "on Save";
	}
}

void Plateau::verificationEchec()
{


}

void Plateau::couleurSurCaseValide(std::list<model::EmplacementValide> listeEmplacements)
{
	for (auto&& caseValide : listeEmplacements) {
		emit listeCases(caseValide.ligne, caseValide.colone)->mettreCouleur(caseValide.couleur);
	}

}

void Plateau::couleurPlateauInitial() 
{
	qDebug() << "seze : " << listeCases.listeCases.size();
	for (auto&& box : listeCases) {
		emit box->mettreCouleurBase();
	}
}

void model::Plateau::tourDeJeuChangement(std::string quiJoue)
{
	tourDeJeu == "Noir" ? tourDeJeu = "Blanc" : tourDeJeu = "Noir";
	qDebug() << QString::fromStdString(tourDeJeu.tour);
	emit changementTour(tourDeJeu.tour);

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

