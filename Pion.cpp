//Corps de la classe Pion
#include "Pion.h"
#include <QDebug>

using Modele::Pion;
using Modele::EmplacementValide;
using iter::range;

Pion::Pion(std::string equipe) : ModelePieceEchec(equipe)
{
	if (equipe_ == "Noir") {
		cheminImage = "images/PionN.png";
		sens = 1;
	}
	else {
		cheminImage = "images/PionB.png";
		sens = -1;
	}
}

void Modele::Pion::positionner(const MatricePosition& matricePos, const PixelPosition& scenePos)
{
	mPosition_ = matricePos;
	pPosition_ = scenePos;

	deplacement = 1;

	emit mettrePositionVue(scenePos);

	promotion();
}



void Modele::Pion::listerDeplacementsSemiValides(ListeCases& listeCase)
{
	listeEmplacementsValides.clear();

	int position = lireMatricePos().ligne;

	for ([[maybe_unused]] int i : range(deplacement)) {
		position += sens;
		if (!(tropHautOuBas(position)) && listeCase(position, lireMatricePos().colonne)->getPiece() == nullptr) {
			listeEmplacementsValides.push_back({ position, lireMatricePos().colonne, Qt::darkGreen });
			
		}
		else {
			break;
		}
	}
	if (!(tropHautOuBas(position)) && !(depasseGauche(lireMatricePos().colonne - 1))) {
		if (listeCase(caseHautGauche(sens))->getPiece() != nullptr && listeCase(caseHautGauche(sens))->getPiece()->lireEquipe() != equipe_) {
			listeEmplacementsValides.push_back({ caseHautGauche(sens), Qt::darkRed });
		}
	}

	if (!(tropHautOuBas(position)) && !(depasseDroite(lireMatricePos().colonne + 1))) {
		if (listeCase(caseHautDroite(sens))->getPiece() != nullptr && listeCase(caseHautDroite(sens))->getPiece()->lireEquipe() != equipe_) {
			listeEmplacementsValides.push_back({ caseHautDroite(sens), Qt::darkRed });
		}
	}
}

void Modele::Pion::promotion()
{
	if (lireMatricePos().ligne == 0 || lireMatricePos().ligne == 7) {
		emit promouvoir(this);
	}
}


