/*
* Classe implémentant la logique de la pièce Fou.
*
* Fichier : Fou.h, Fou.cpp
* Auteurs : Sebastian Espin, Julien Roux
* Date : 05/05/2022
* Crée : 28/04/2022
*/

#pragma once
#include "ModelePieceEchec.h"

namespace Modele {

	class Fou : public ModelePieceEchec
	{
	public:
		Fou(std::string equipe);

		void listerDeplacementsSemiValides(ListeCases& listeCase) override;
		bool deplacementEstValide(const MatricePosition& destination) override;

	};
}
