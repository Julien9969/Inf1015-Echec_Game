#include "Plateau.h"
#include <QDebug>
#include <QLabel>
//#include <QGraphicsDropShadowEffect>
#include <QEvent>

//extern Jeu* jeu;

using iter::range;
using Ui::Case;
using model::Tour;
using model::PieceEchec;

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
	Tour* tourN = new Tour("Noir");
	ListePieceNoir.push_back(tourN);

	Tour* tourN1 = new Tour("Noir");
	ListePieceNoir.push_back(tourN1);

	Tour* tourN2 = new Tour("Noir");
	ListePieceNoir.push_back(tourN2);

	Tour* tourN3 = new Tour("Noir");
	ListePieceNoir.push_back(tourN3);

	Tour* tourN4 = new Tour("Noir");
	ListePieceNoir.push_back(tourN4);

	Tour* tourN5 = new Tour("Noir");
	ListePieceNoir.push_back(tourN5);

	Tour* tourN6 = new Tour("Noir");
	ListePieceNoir.push_back(tourN6);

	Tour* tourN7 = new Tour("Noir");
	ListePieceNoir.push_back(tourN7);
	
}

void Plateau::creePieceBlanc()
{
	Tour* tourB = new Tour("Blanc");
	ListePieceBlanc.push_back(tourB);

	Tour* tourB1 = new Tour("Blanc");
	ListePieceBlanc.push_back(tourB1);

	Tour* tourB2 = new Tour("Blanc");
	ListePieceBlanc.push_back(tourB2);

	Tour* tourB3 = new Tour("Blanc");
	ListePieceBlanc.push_back(tourB3);

	Tour* tourB4 = new Tour("Blanc");
	ListePieceBlanc.push_back(tourB4);

	Tour* tourB5 = new Tour("Blanc");
	ListePieceBlanc.push_back(tourB5);

	Tour* tourB6 = new Tour("Blanc");
	ListePieceBlanc.push_back(tourB6);

	Tour* tourB7 = new Tour("Blanc");
	ListePieceBlanc.push_back(tourB7);

}

void Plateau::mettreLesPieces()
{
	Ui::Case* tempCase = nullptr;
	model::PieceEchec* tempPiece = nullptr;

	
	for (int i = 0; i < 1; i++) {
		for (int j = 0; j < 8; j++) {

			tempCase = listeCases(i, j);
			tempPiece = ListePieceNoir[i * 8 + j];

			tempCase->mettrePiece(tempPiece);
			tempPiece->positionnerPiece(tempCase->lireMatricePosition(), tempCase->lirePixPosition());
			QObject::connect(tempPiece, &model::PieceEchec::pieceClique, this, &Plateau::recevoirPieceClique);
			
			
			ajouterDansScene(tempPiece);//i+j
			
		}
	}

	for (int i = 0; i < 1; i++) {
		for (int j = 0; j < 8; j++) {

			tempCase = listeCases(i, j + 56);
			tempPiece = ListePieceBlanc[i * 8 + j];

			tempCase->mettrePiece(tempPiece);
			tempPiece->positionnerPiece(tempCase->lireMatricePosition(), tempCase->lirePixPosition());
			QObject::connect(tempPiece, &model::PieceEchec::pieceClique, this, &Plateau::recevoirPieceClique);


			ajouterDansScene(tempPiece);//i+j

		}
	}

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
		//listeCases(pieceActuelle_->lireX(), + pieceActuelle_->lireY())->mettreCouleur(Qt::yellow);

		qDebug() << "indice tableau case : " << pieceActuelle_->lireX() + 8 * pieceActuelle_->lireY();

		caseClique->mettrePiece(pieceActuelle_);
		pieceActuelle_->positionnerPiece(caseClique->lireMatricePosition(), caseClique->lirePixPosition());
		pieceActuelle_->estDeClique();
		couleurPlateauInitial();
		pieceActuelle_ = nullptr;

	}
}


void Plateau::recevoirPieceClique(model::PieceEchec* piece)
{
	couleurPlateauInitial();
	
	if ((pieceActuelle_ != nullptr) && (piece->lireEquipe() != pieceActuelle_->lireEquipe())) {
		if (pieceActuelle_->deplacementEstValide(piece->matricePos())) {

			listeCases(pieceActuelle_->lireX(), pieceActuelle_->lireY())->enleverPiece();
			listeCases(piece->lireX(), piece->lireY())->mettrePiece(pieceActuelle_);
			pieceActuelle_->mangeLaPiece(piece);
			pieceActuelle_ = nullptr;
		}
	}
	else {
		pieceActuelle_ = piece;
		couleurSurCaseValide(pieceActuelle_->listerDeplacementsValides(listeCases));

	}

	qDebug() << "on Save";
}

void Plateau::couleurSurCaseValide(std::list<model::CaseValide> listeEmplacements)
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



void Plateau::mouseMoveEvent(QGraphicsSceneMouseEvent* event) {
	// if there is a cardToPlace, then make it follow the mouse
	if (pieceActuelle_ != nullptr) {
		pieceActuelle_->setPos(event->scenePos().x() - 45, event->scenePos().y() - 45);
		qDebug() << "piece move" << event->pos();

	}

	qDebug() << "move";
}

Plateau::~Plateau()
{
	/*for (auto&& elem : listeCase) {
		delete elem;
	}*/

	/*for (auto&& elem : ListePieceNoir) {
		delete elem;
	}
	
	for (auto&& elem : ListePieceBlanc) {
		delete elem;
	}*/

}

