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
	mettreLesPieces();
}

void Plateau::creeCases() {
	
	for (int i : range(8)) {

		for (int j : range(8)) {

			Ui::Case* box = new Ui::Case((ptrJeu_->width() - ptrJeu_->height()) / 2 + 90 * j, 90 * i, 90, 90);

			box->mettreCoordonnees(i, j);

			if (((i + j) % 2) == 0) {
				box->mettreCouleur(Qt::darkBlue);
			}
			else {
				box->mettreCouleur(Qt::white);
			}

			QObject::connect(box, &Ui::Case::caseClique, this, &Plateau::recevoirCaseClique);

			ajouterDansScene(box);
			ListeCase.push_back(box);


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

void Plateau::mettreLesPieces()
{
	Ui::Case* tempCase = nullptr;
	model::PieceEchec* tempPiece = nullptr;

	
	for (int i = 0; i < 1; i++) {
		for (int j = 0; j < 8; j++) {

			tempCase = ListeCase[i * 8 + j];
			tempPiece = ListePieceNoir[i * 8 + j];

			tempCase->mettrePiece(tempPiece);
			tempPiece->positionnerPiece({ i, j }, tempCase->lirePixPosition());
			QObject::connect(tempPiece, &model::PieceEchec::pieceClique, this, &Plateau::enregistrerPieceClique);
			
			
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
	if (pieceActuelle_ != nullptr && caseClique->getPiece() == nullptr) 
	{
		ListeCase[pieceActuelle_->lireX() * 8 + pieceActuelle_->lireY()]->enleverPiece();
		ListeCase[pieceActuelle_->lireX() * 8 + pieceActuelle_->lireY()]->mettreCouleur(Qt::yellow);
		qDebug() << "indice tableau case : " << pieceActuelle_->lireX() + 8 * pieceActuelle_->lireY();
		caseClique->mettrePiece(pieceActuelle_);
		pieceActuelle_->positionnerPiece(caseClique->lireMatricePosition(), caseClique->lirePixPosition());
		pieceActuelle_ = nullptr;
	}
}


void Plateau::enregistrerPieceClique(model::PieceEchec* piece) 
{

	pieceActuelle_ = piece;
	qDebug() << "on Save";
}


Plateau::~Plateau()
{
	for (auto&& elem : ListeCase) {
		delete elem;
	}

	/*for (auto&& elem : ListePieceNoir) {
		delete elem;
	}
	
	for (auto&& elem : ListePieceBlanc) {
		delete elem;
	}*/

}

