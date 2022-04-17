#include "Tour.h"


using model::Tour;
using model::EmplacementValide;
using Ui::ListeCases;

Tour::Tour(std::string equipe) : ModelPieceEchec(equipe)
{
	if (equipe_ == "Noir") {
		cheminImage = "images/TourN.png";
	}
	else {
		cheminImage = "images/TourB.png";
	}

}

std::list<EmplacementValide>& Tour::listerDeplacementsValides(ListeCases& listeCase)
{
	listeEmplacementsValides.clear();

	//Vers le bas
	for (int ligne = ligne_ + 1; ligne < 8; ligne++)
	{
		if (listeCase(ligne, colone_)->getPiece() != nullptr) {
			if (listeCase(ligne, colone_)->getPiece()->lireEquipe() != equipe_) {
				listeEmplacementsValides.push_back({ ligne, colone_, Qt::darkRed });
			}
			break;
		}
		else {
			listeEmplacementsValides.push_back({ ligne, colone_, Qt::darkGreen });
		}
	}

	//vers le haut
	for (int ligne = ligne_ - 1; ligne >= 0; ligne--)
	{
		if (listeCase(ligne, colone_)->getPiece() != nullptr) {
			if (listeCase(ligne, colone_)->getPiece()->lireEquipe() != equipe_) {
				listeEmplacementsValides.push_back({ ligne, colone_, Qt::darkRed });
			}
			break;
		}
		else {
			listeEmplacementsValides.push_back({ ligne, colone_, Qt::darkGreen });
		}
	}

	//vers la droite
	for (int colone = colone_ + 1; colone < 8; colone++)
	{
		if (listeCase(ligne_, colone)->getPiece() != nullptr) {
			if (listeCase(ligne_, colone)->getPiece()->lireEquipe() != equipe_) {
				listeEmplacementsValides.push_back({ ligne_, colone, Qt::darkRed });
			}
			break;
		}
		else {
			listeEmplacementsValides.push_back({ ligne_, colone, Qt::darkGreen });
		}
	}


	//vers la gauche
	for (int colone = colone_ - 1; colone >= 0; colone--)
	{
		if (listeCase(ligne_, colone)->getPiece() != nullptr) {
			if (listeCase(ligne_, colone)->getPiece()->lireEquipe() != equipe_) {
				listeEmplacementsValides.push_back({ ligne_, colone, Qt::darkRed });
			}
			break;
		}
		else {
			listeEmplacementsValides.push_back({ ligne_, colone, Qt::darkGreen });
		}
	}

	return listeEmplacementsValides;
}

bool model::Tour::deplacementEstValide(const std::pair<int, int>& destination)
{
	for (auto&& emplacement : listeEmplacementsValides) {
		if (emplacement.ligne == destination.first && emplacement.colone == destination.second) {
			return true;
		}

	}
	return false;
}

