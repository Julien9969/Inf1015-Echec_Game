//Corps de la classe Roi
#include "Roi.h"

using Modele::Roi;
using Modele::EmplacementValide;


Roi::Roi(std::string equipe) : ModelePieceEchec(equipe)
{
	if (equipe_ == "Noir") {
		cheminImage = "images/RoiN.png";
	}
	else {
		cheminImage = "images/RoiB.png";
	}

	compteurDeRoi++;

	if (compteurDeRoi > 2) {
		compteurDeRoi--;
		throw std::logic_error("Trop de roi");
	}
}

void Roi::listerDeplacementsSemiValides(ListeCases& listeCase)
{
	listeEmplacementsValides.clear();

	std::vector<std::pair<int, int>> deplacementRoi = { {-1,-1}, {1,1}, {-1,1}, {1,-1}, {1,0}, {-1,0}, {0,1}, {0,-1} };

	for (auto&& coordonnee : deplacementRoi) {
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

bool Modele::Roi::deplacementEstValide(const MatricePosition& destination)
{
	for (auto&& emplacement : listeEmplacementsValides) {
		if (emplacement.ligne == destination.ligne && emplacement.colonne == destination.colonne) {
			return true;
		}

	}
	return false;
}
