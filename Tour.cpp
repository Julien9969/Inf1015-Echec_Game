//Corps de la classe Tour
#include "Tour.h"
#include <QDebug>

using Modele::Tour;
using Modele::EmplacementValide;

Tour::Tour(std::string equipe) : ModelePieceEchec(equipe)
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
	for (int ligne = lireMatricePos().ligne + 1; depasse(ligne, BAS); ligne++)
	{
		if (listeCase(ligne, lireMatricePos().colonne)->getPiece() != nullptr) {
			if (listeCase(ligne, lireMatricePos().colonne)->getPiece()->lireEquipe() != equipe_) {
				listeEmplacementsValides.push_back({ ligne, lireMatricePos().colonne, Qt::darkRed });
			}
			break;
		}
		else {
			listeEmplacementsValides.push_back({ ligne, lireMatricePos().colonne, Qt::darkGreen });
		}
	}

	//vers le haut
	for (int ligne = lireMatricePos().ligne - 1; neDepassePas(ligne, HAUT); ligne--)
	{
		if (listeCase(ligne, lireMatricePos().colonne)->getPiece() != nullptr) {
			if (listeCase(ligne, lireMatricePos().colonne)->getPiece()->lireEquipe() != equipe_) {
				listeEmplacementsValides.push_back({ ligne, lireMatricePos().colonne, Qt::darkRed });

			}
			break;
		}
		else {
			listeEmplacementsValides.push_back({ ligne, lireMatricePos().colonne, Qt::darkGreen });
		}
	}

	//vers la droite
	for (int colonne = lireMatricePos().colonne + 1; depasse(colonne, DROITE); colonne++)
	{
		if (listeCase(lireMatricePos().ligne, colonne)->getPiece() != nullptr) {
			if (listeCase(lireMatricePos().ligne, colonne)->getPiece()->lireEquipe() != equipe_) {
				listeEmplacementsValides.push_back({ lireMatricePos().ligne, colonne, Qt::darkRed });
		

			}
			break;
		}
		else {
			listeEmplacementsValides.push_back({ lireMatricePos().ligne, colonne, Qt::darkGreen });
		}
	}

	//vers la gauche
	for (int colonne = lireMatricePos().colonne - 1; neDepassePas(colonne, GAUCHE); colonne--)
	{
		if (listeCase(lireMatricePos().ligne, colonne)->getPiece() != nullptr) {
			if (listeCase(lireMatricePos().ligne, colonne)->getPiece()->lireEquipe() != equipe_) {
				listeEmplacementsValides.push_back({ lireMatricePos().ligne, colonne, Qt::darkRed });

			}
			break;
		}
		else {
			listeEmplacementsValides.push_back({ lireMatricePos().ligne, colonne, Qt::darkGreen });
		}
	}
}

