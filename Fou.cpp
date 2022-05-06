//Corps de la classe Fou
#include "Fou.h"
#include <QDebug>

using Modele::Fou;
using Modele::EmplacementValide;

Fou::Fou(std::string equipe) : ModelePieceEchec(equipe)
{
	if (equipe_ == "Noir") {
		cheminImage = "images/FouN.png";
	}
	else {
		cheminImage = "images/FouB.png";
	}
}

void Fou::listerDeplacementsSemiValides(ListeCases& listeCase)
{
	listeEmplacementsValides.clear();

    //Haut gauche
    for (int ligne = lireMatricePos().ligne - 1, colonne = lireMatricePos().colonne - 1; neDepassePas(ligne, HAUT) && neDepassePas(colonne, GAUCHE); ligne--, colonne--)
    {
        if (listeCase(ligne, colonne)->getPiece() != nullptr) {
            if (listeCase(ligne, colonne)->getPiece()->lireEquipe() != equipe_) {
                listeEmplacementsValides.push_back({ ligne, colonne, Qt::darkRed });
            }
            break;
        }
        else {
            listeEmplacementsValides.push_back({ ligne, colonne, Qt::darkGreen });
        }
    }

    //Haut droite
    for (int ligne = lireMatricePos().ligne - 1, colonne = lireMatricePos().colonne + 1; neDepassePas(ligne, HAUT) && depasse(colonne, BAS); ligne--, colonne++)
    {
        if (listeCase(ligne, colonne)->getPiece() != nullptr) {
            if (listeCase(ligne, colonne)->getPiece()->lireEquipe() != equipe_) {
                listeEmplacementsValides.push_back({ ligne, colonne, Qt::darkRed });
            }
            break;
        }
        else {
            listeEmplacementsValides.push_back({ ligne, colonne, Qt::darkGreen });
        }
    }

    //bas droite
    for (int ligne = lireMatricePos().ligne + 1, colonne = lireMatricePos().colonne + 1; depasse(ligne, BAS) && depasse(colonne, BAS); ligne++, colonne++)
    {
        if (listeCase(ligne, colonne)->getPiece() != nullptr) {
            if (listeCase(ligne, colonne)->getPiece()->lireEquipe() != equipe_) {
                listeEmplacementsValides.push_back({ ligne, colonne, Qt::darkRed });
            }
            break;
        }
        else {
            listeEmplacementsValides.push_back({ ligne, colonne, Qt::darkGreen });
        }
    }

    //bas gauche
    for (int ligne = lireMatricePos().ligne + 1, colonne = lireMatricePos().colonne - 1; depasse(ligne, BAS) && neDepassePas(colonne, GAUCHE); ligne++, colonne--)
    {
        if (listeCase(ligne, colonne)->getPiece() != nullptr) {
            if (listeCase(ligne, colonne)->getPiece()->lireEquipe() != equipe_) {
                listeEmplacementsValides.push_back({ ligne, colonne, Qt::darkRed });
            }
            break;
        }
        else {
            listeEmplacementsValides.push_back({ ligne, colonne, Qt::darkGreen });
        }
    }
}

bool Modele::Fou::deplacementEstValide(const MatricePosition& destination)
{
	for (auto&& emplacement : listeEmplacementsValides) {
		if (emplacement.ligne == destination.ligne && emplacement.colonne == destination.colonne) {
			return true;
		}
	}
	return false;
}

