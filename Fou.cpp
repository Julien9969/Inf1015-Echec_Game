#include "Fou.h"
#include <QDebug>


using model::Fou;
using model::EmplacementValide;

Fou::Fou(std::string equipe) : ModelPieceEchec(equipe)
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
    for (int ligne = lireMatricePos().ligne - 1, colone = lireMatricePos().colone - 1; ligne >= 0 && colone >= 0; ligne--, colone--)
    {
        if (listeCase(ligne, colone)->getPiece() != nullptr) {
            if (listeCase(ligne, colone)->getPiece()->lireEquipe() != equipe_) {
                listeEmplacementsValides.push_back({ ligne, colone, Qt::darkRed });
                qDebug() << "pas equipe apfhepfaefi";
            }
            break;
        }
        else {
            listeEmplacementsValides.push_back({ ligne, colone, Qt::darkGreen });
        }
    }

    //Haut gauche
    for (int ligne = lireMatricePos().ligne - 1, colone = lireMatricePos().colone + 1; ligne >= 0 && colone <= 7; ligne--, colone++)
    {
        if (listeCase(ligne, colone)->getPiece() != nullptr) {
            if (listeCase(ligne, colone)->getPiece()->lireEquipe() != equipe_) {
                listeEmplacementsValides.push_back({ ligne, colone, Qt::darkRed });
                qDebug() << "pas equipe apfhepfaefi";
            }
            break;
        }
        else {
            listeEmplacementsValides.push_back({ ligne, colone, Qt::darkGreen });
        }
    }

    //bas droite
    for (int ligne = lireMatricePos().ligne + 1, colone = lireMatricePos().colone + 1; ligne <= 7 && colone <= 7; ligne++, colone++)
    {
        if (listeCase(ligne, colone)->getPiece() != nullptr) {
            if (listeCase(ligne, colone)->getPiece()->lireEquipe() != equipe_) {
                listeEmplacementsValides.push_back({ ligne, colone, Qt::darkRed });
                qDebug() << "pas equipe apfhepfaefi";
            }
            break;
        }
        else {
            listeEmplacementsValides.push_back({ ligne, colone, Qt::darkGreen });
        }
    }

    //bas gauche
    for (int ligne = lireMatricePos().ligne + 1, colone = lireMatricePos().colone - 1; ligne <= 7 && colone >= 0; ligne++, colone--)
    {
        if (listeCase(ligne, colone)->getPiece() != nullptr) {
            if (listeCase(ligne, colone)->getPiece()->lireEquipe() != equipe_) {
                listeEmplacementsValides.push_back({ ligne, colone, Qt::darkRed });
                qDebug() << "pas equipe apfhepfaefi";
            }
            break;
        }
        else {
            listeEmplacementsValides.push_back({ ligne, colone, Qt::darkGreen });
        }
    }
}

bool model::Fou::deplacementEstValide(const MatricePosition& destination)
{
	for (auto&& emplacement : listeEmplacementsValides) {
		if (emplacement.ligne == destination.ligne && emplacement.colone == destination.colone) {
			return true;
		}

	}
	return false;
}

