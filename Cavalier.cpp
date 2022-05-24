#include "Cavalier.h"

Modele::Cavalier::Cavalier(std::string equipe) : ModelePieceEchec(equipe)
{
	if (equipe_ == "Noir") {
		cheminImage = "images/CavalierN.png";
	}
	else {
		cheminImage = "images/CavalierB.png";
	}
}

void Modele::Cavalier::listerDeplacementsSemiValides(ListeCases& listeCase)
{
	listeEmplacementsValides.clear();

	std::vector<std::pair<int, int>> deplacementCavalier = { {-2,-1}, {-1,-2}, {-2,1}, {-1, 2}, {1,2}, {2,1}, {2, -1}, {1,-2} };

	for (auto&& coordonnee : deplacementCavalier) {
		int ligne = lireMatricePos().ligne + coordonnee.first;
		int colonne = lireMatricePos().colonne + coordonnee.second;

		if (ligne < 0 || ligne > 7 || colonne < 0 || colonne > 7) {
			continue;
		}

		if (listeCase(ligne, colonne)->getPiece() != nullptr) {
			if (listeCase(ligne, colonne)->getPiece()->lireEquipe() != equipe_) {
				listeEmplacementsValides.push_back({ ligne, colonne, Qt::darkRed });
			}
		}
		else
		{
			listeEmplacementsValides.push_back({ ligne, colonne, Qt::darkGreen });
		}
	}
}