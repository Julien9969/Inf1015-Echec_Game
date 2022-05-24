#pragma once
#include "ModelePieceEchec.h"
#include "cppitertools/range.hpp"
/*
* Classe implémentant la logique de la pièce Pion.
*
* Fichier : Pion.h, PIon.cpp
* Auteurs : Sebastian Espin, Julien Roux
* Date : 18/05/2022
* Crée : 18/05/2022
*/

#define caseHautGauche(sens) lireMatricePos().ligne + sens, lireMatricePos().colonne - 1
#define caseHautDroite(sens) lireMatricePos().ligne + sens, lireMatricePos().colonne + 1
#define tropHautOuBas(ligne) ligne > 7 || ligne < 0
#define depasseGauche(position) position < 0
#define depasseDroite(position) position > 7

namespace Modele {

	class Pion : public ModelePieceEchec
	{
	public:
		Pion(std::string equipe);
		//~Pion();

		void listerDeplacementsSemiValides(ListeCases& listeCase) override;
		void positionner(const MatricePosition& matricePos, const PixelPosition& scenePos) override;
	private:
		int deplacement = 2;
		int sens;

	};

}

