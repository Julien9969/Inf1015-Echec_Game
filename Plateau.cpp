#include "Plateau.h"
#include <QDebug>
#include <QLabel>
//#include <QGraphicsDropShadowEffect>
#include <QEvent>

//extern Jeu* jeu;

using iter::range;
using Ui::Case;
using model::Tour;
using model::Roi;
using Ui::VuePieceEchec;
using model::ModelPieceEchec;

//using ui::Case, ui::Jeu;

Plateau::Plateau(Ui::Jeu* jeu)
{
	qDebug() << "plateau : " << jeu->ab;
	ptrJeu_ = jeu;
	creeCases();
	creePiecesNoir();
	creePieceBlanc();
	mettreLesPieces();
}

void Plateau::creeCases() {
	
	for (int i : range(8)) {

		for (int j : range(8)) {

			Ui::Case* box = new Ui::Case((ptrJeu_->width() - ptrJeu_->height()) / 2 + 90 * j, 90 * i, 90, 90);

			box->mettreCoordonnees(i, j);

			if (((i + j) % 2) == 0) {

				box->mettreCouleurbase(Qt::darkBlue);
			}
			else {
				box->mettreCouleurbase(Qt::white);
			}

			QObject::connect(box, &Ui::Case::caseClique, this, &Plateau::recevoirCaseClique);

			ajouterDansScene(box);
			listeCases.push_back(box);


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
	catch (std::domain_error& e) {
		qDebug() << "Erreur : " << e.what();
	}
}

void Plateau::mettreLesPieces()
{
	Ui::Case* tempCase = nullptr;
	ModelPieceEchec* tempPiece = nullptr;
	int i = 0;
	
	for (auto&& j = ListePieceNoir.begin(); j != ListePieceNoir.end(); j++) {
			
		tempCase = listeCases[i++];
		tempPiece = j->get();// ListePieceNoir[i * 8 + j].get();

		VuePieceEchec* piece = new VuePieceEchec(tempPiece);

		tempCase->mettrePiece(tempPiece);
		
		tempPiece->positionner(tempCase->lireMatricePosition(), tempCase->lirePixPosition());
			
		QObject::connect(piece, &Ui::VuePieceEchec::pieceClique, this, &Plateau::recevoirPieceClique);
		QObject::connect(piece, &Ui::VuePieceEchec::enleverLaPiece, this, &Plateau::enleverPieceElimine);


		ajouterDansScene(piece);
			
	}
	

	i = 0;
	
	for (auto&& j = ListePieceBlanc.begin(); j != ListePieceBlanc.end(); j++) {

		tempCase = listeCases[56 + i++];
		tempPiece = j->get();//ListePieceBlanc[i * 8 + j].get();

		VuePieceEchec* piece = new VuePieceEchec(tempPiece);

		tempCase->mettrePiece(tempPiece);

		tempPiece->positionner(tempCase->lireMatricePosition(), tempCase->lirePixPosition());
		QObject::connect(piece, &Ui::VuePieceEchec::pieceClique, this, &Plateau::recevoirPieceClique);
		QObject::connect(piece, &Ui::VuePieceEchec::enleverLaPiece, this, &Plateau::enleverPieceElimine);
		
		ajouterDansScene(piece);	
	}
	
	//ListePieceBlanc.erase();
}

void Plateau::ajouterDansScene(QGraphicsItem* item)
{
	ptrJeu_->mettreDansScene(item);
}

void Plateau::recevoirCaseClique(Case* caseClique)
{
	if ((pieceActuelle_ != nullptr) && (caseClique->getPiece() == nullptr) && (pieceActuelle_->deplacementEstValide(caseClique->lireMatricePosition())))
	{
		listeCases(pieceActuelle_->lireX(), pieceActuelle_->lireY())->enleverPiece();

		qDebug() << "indice tableau case : " << pieceActuelle_->lireX() + 8 * pieceActuelle_->lireY();

		caseClique->mettrePiece(pieceActuelle_);
		pieceActuelle_->positionner(caseClique->lireMatricePosition(), caseClique->lirePixPosition());
		
		couleurPlateauInitial();
		pieceActuelle_ = nullptr;

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


void Plateau::recevoirPieceClique(Ui::VuePieceEchec* piece)
{
	couleurPlateauInitial();
	model::ModelPieceEchec* pieceClique = piece->lirePiece();

	if ((pieceActuelle_ != nullptr) && (pieceClique->lireEquipe() != pieceActuelle_->lireEquipe())) {
		if (pieceActuelle_->deplacementEstValide(pieceClique->matricePos())) {

			listeCases(pieceActuelle_->lireX(), pieceActuelle_->lireY())->enleverPiece();
			listeCases(pieceClique->lireX(), pieceClique->lireY())->mettrePiece(pieceActuelle_);

			pieceActuelle_->mangeLaPiece(pieceClique);
			pieceActuelle_ = nullptr;
			//enleverPieceElimine(pieceClique);
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
		listeCases(caseValide.ligne, caseValide.colone)->mettreCouleur(caseValide.couleur);
	}

}

void Plateau::couleurPlateauInitial() {
	
	qDebug() << "seze : " << listeCases.listeCases.size();
	for (auto&& box : listeCases) {
		box->mettreCouleur();
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

