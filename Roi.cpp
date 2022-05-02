#include "Roi.h"

using model::Roi;
using model::EmplacementValide;

//int Roi::compteurDeRoi = 0;

Roi::Roi(std::string equipe) : ModelPieceEchec(equipe)
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

std::list<EmplacementValide>& Roi::listerDeplacementsValides(ListeCases& listeCase)
{
	listeEmplacementsValides.clear();

	std::vector<std::pair<int, int>> deplacementRoi = { {-1,-1}, {1,1}, {-1,1}, {1,-1}, {1,0}, {-1,0}, {0,1}, {0,-1} };

	for (auto&& coordonnee : deplacementRoi) {
		int ligne = lireMatricePos().ligne + coordonnee.first;
		int colone = lireMatricePos().colone + coordonnee.second;
		
		if (ligne < 0 || ligne > 7 || colone < 0 || colone > 7) {
			continue;
		}

		if (listeCase(ligne, colone)->getPiece() != nullptr) {
			if (listeCase(ligne, colone)->getPiece()->lireEquipe() != equipe_) {
				listeEmplacementsValides.push_back({ ligne, colone, Qt::darkRed });
			}
		}
		else
		{
			listeEmplacementsValides.push_back({ ligne, colone, Qt::darkGreen });
		}
	}



	return listeEmplacementsValides;
}

bool model::Roi::deplacementEstValide(const MatricePosition& destination)
{
	for (auto&& emplacement : listeEmplacementsValides) {
		if (emplacement.ligne == destination.ligne && emplacement.colone == destination.colone) {
			return true;
		}

	}
	return false;
}