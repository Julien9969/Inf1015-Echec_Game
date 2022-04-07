#include "Plateau.h"
#include <QDebug>
#include <QLabel>
//#include <QGraphicsDropShadowEffect>
#include <QEvent>

//extern Jeu* jeu;

using iter::range;

Plateau::Plateau(Jeu* jeu)
{
	qDebug() << "plateau : " << jeu->ab;
	ptrJeu_ = jeu;
	
}

void Plateau::creeCases() {
	
	for (int i : range(8)) {

		for (int j : range(8)) {

			Case* box = new Case((ptrJeu_->width() - ptrJeu_->height()) / 2 + 90 * i, 90 * j, 90, 90);

			box->mettreEmplacement(i, j);

			if (((i + j) % 2) == 0) {
				box->mettreCouleur(Qt::darkBlue);
			}
			else {
				box->mettreCouleur(Qt::white);
			}

			ajouterDansScene(box);
			ListeCase.push_back(box);

		}
	}

}

void Plateau::creePiecesNoir()
{
	Tour* tourN = new Tour("Noir");
	ListePieceNoir.push_back(tourN);
	//ajouterDansScene(tourN);
	//ajouterDansScene(ListePieceNoir[0]);
}

void Plateau::mettreLesPieces()
{
	
	/*for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 2; j++) {
			
		}
	}*/
	ListeCase[0]->mettrePiece(ListePieceNoir[0]);
	ListePieceNoir[0]->positionnerPiece(0, 0, ListeCase[0]->lirePosition());
	ListeCase[0]->mettreCouleur(Qt::yellow);
	
	ajouterDansScene(ListePieceNoir[0]);//i+j

}

void Plateau::ajouterDansScene(QGraphicsItem* item)
{
	ptrJeu_->mettreDansScene(item);
}

Plateau::~Plateau()
{
	for (auto&& elem : ListeCase) {
		delete elem;
	}

	for (auto&& elem : ListePieceNoir) {
		delete elem;
	}
	
	for (auto&& elem : ListePieceBlanc) {
		delete elem;
	}

}