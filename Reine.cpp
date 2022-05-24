#include "Reine.h"

Modele::Reine::Reine(std::string equipe) : ModelePieceEchec(equipe)
{
	if (equipe_ == "Noir") {
		cheminImage = "images/ReineN.png";
	}
	else {
		cheminImage = "images/ReineB.png";
	}
}



void Modele::Reine::listerDeplacementsSemiValides(ListeCases& listeCase)
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