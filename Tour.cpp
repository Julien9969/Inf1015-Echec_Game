#include "Tour.h"
#include <QDebug>


using model::Tour;
using model::EmplacementValide;

Tour::Tour(std::string equipe) : ModelPieceEchec(equipe)
{
	if (equipe_ == "Noir") {
		cheminImage = "images/TourN.png";
	}
	else {
		cheminImage = "images/TourB.png";
	}

}

void Tour::listerDeplacementsSemiValides(ListeCases& listeCase)
{
	listeEmplacementsValides.clear();

	//Vers le bas
	for (int ligne = lireMatricePos().ligne + 1; ligne < 8; ligne++)
	{
		if (listeCase(ligne, lireMatricePos().colone)->getPiece() != nullptr) {
			if (listeCase(ligne, lireMatricePos().colone)->getPiece()->lireEquipe() != equipe_) {
				listeEmplacementsValides.push_back({ ligne, lireMatricePos().colone, Qt::darkRed });
				qDebug() << "pas equipe apfhepfaefi";
			}
			break;
		}
		else {
			listeEmplacementsValides.push_back({ ligne, lireMatricePos().colone, Qt::darkGreen });
		}
	}

	//vers le haut
	for (int ligne = lireMatricePos().ligne - 1; ligne >= 0; ligne--)
	{
		if (listeCase(ligne, lireMatricePos().colone)->getPiece() != nullptr) {
			if (listeCase(ligne, lireMatricePos().colone)->getPiece()->lireEquipe() != equipe_) {
				listeEmplacementsValides.push_back({ ligne, lireMatricePos().colone, Qt::darkRed });
				qDebug() << "pas equipe apfhepfaefi";

			}
			break;
		}
		else {
			listeEmplacementsValides.push_back({ ligne, lireMatricePos().colone, Qt::darkGreen });
		}
	}

	//vers la droite
	for (int colone = lireMatricePos().colone + 1; colone < 8; colone++)
	{
		if (listeCase(lireMatricePos().ligne, colone)->getPiece() != nullptr) {
			if (listeCase(lireMatricePos().ligne, colone)->getPiece()->lireEquipe() != equipe_) {
				listeEmplacementsValides.push_back({ lireMatricePos().ligne, colone, Qt::darkRed });
		

			}
			break;
		}
		else {
			listeEmplacementsValides.push_back({ lireMatricePos().ligne, colone, Qt::darkGreen });
		}
	}


	//vers la gauche
	for (int colone = lireMatricePos().colone - 1; colone >= 0; colone--)
	{
		if (listeCase(lireMatricePos().ligne, colone)->getPiece() != nullptr) {
			if (listeCase(lireMatricePos().ligne, colone)->getPiece()->lireEquipe() != equipe_) {
				listeEmplacementsValides.push_back({ lireMatricePos().ligne, colone, Qt::darkRed });
				qDebug() << "pas equipe apfhepfaefi";

			}
			break;
		}
		else {
			listeEmplacementsValides.push_back({ lireMatricePos().ligne, colone, Qt::darkGreen });
		}
	}
}

bool model::Tour::deplacementEstValide(const MatricePosition& destination)
{
	for (auto&& emplacement : listeEmplacementsValides) {
		if (emplacement.ligne == destination.ligne && emplacement.colone == destination.colone) {
			return true;
		}

	}
	return false;
}

