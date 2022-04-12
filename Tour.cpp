#include "Tour.h"


using model::Tour;
using model::CaseValide;
using Ui::ListeCases;

Tour::Tour(QString equipe, QGraphicsItem* parent) : PieceEchec(equipe, parent)
{
	ajouterImage();
	
}


void Tour::ajouterImage()
{
	if (equipe_ == "Noir") {
		setPixmap(QPixmap("images/TourN.png"));
	}
	else {
		setPixmap(QPixmap("images/TourB.png"));
	}

	//setFlags(QGraphicsItem::ItemIsSelectable | QGraphicsItem::ItemIsMovable);
	setAcceptHoverEvents(true);

	setScale(1.4);

}

std::list<CaseValide>& Tour::listerDeplacementsValides(ListeCases& listeCase)
{
	emplacementsValides.clear();

	//Vers le bas
	for (int ligne = ligne_ + 1; ligne < 8; ligne++)
	{
		if (listeCase(ligne, colone_)->getPiece() != nullptr) {
			if (listeCase(ligne, colone_)->getPiece()->lireEquipe() != equipe_) {
				emplacementsValides.push_back({ ligne, colone_, Qt::darkRed });
			}
			break;
		}
		else {
			emplacementsValides.push_back({ ligne, colone_, Qt::darkGreen });
		}
	}

	//vers le haut
	for (int ligne = ligne_ - 1; ligne >= 0; ligne--)
	{
		if (listeCase(ligne, colone_)->getPiece() != nullptr) {
			if (listeCase(ligne, colone_)->getPiece()->lireEquipe() != equipe_) {
				emplacementsValides.push_back({ ligne, colone_, Qt::darkRed });
			}
			break;
		}
		else {
			emplacementsValides.push_back({ ligne, colone_, Qt::darkGreen });
		}
	}

	//vers la droite
	for (int colone = colone_ + 1; colone < 8; colone++)
	{
		if (listeCase(ligne_, colone)->getPiece() != nullptr) {
			if (listeCase(ligne_, colone)->getPiece()->lireEquipe() != equipe_) {
				emplacementsValides.push_back({ ligne_, colone, Qt::darkRed });
			}
			break;
		}
		else {
			emplacementsValides.push_back({ ligne_, colone, Qt::darkGreen });
		}
	}


	//vers la gauche
	for (int colone = colone_ - 1; colone >= 0; colone--)
	{
		if (listeCase(ligne_, colone)->getPiece() != nullptr) {
			if (listeCase(ligne_, colone)->getPiece()->lireEquipe() != equipe_) {
				emplacementsValides.push_back({ ligne_, colone, Qt::darkRed });
			}
			break;
		}
		else {
			emplacementsValides.push_back({ ligne_, colone, Qt::darkGreen });
		}
	}

	return emplacementsValides;
}

bool model::Tour::deplacementEstValide(const std::pair<int, int>& destination)
{
	for (auto&& emplacement : emplacementsValides) {
		if (emplacement.ligne == destination.first && emplacement.colone == destination.second) {
			return true;
		}

	}
	return false;
}

