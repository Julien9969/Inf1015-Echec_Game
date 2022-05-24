/*
* Classe implémentant la logique de la pièce Reine.
*
* Fichier : Reine.h, Reine.cpp
* Auteurs : Sebastian Espin, Julien Roux
* Date : 05/05/2022
* Crée : 30/04/2022
*/

#pragma once
#include "ModelePieceEchec.h"

namespace Modele {

	class Reine : public ModelePieceEchec
	{
	public:
		Reine(std::string equipe);

		void listerDeplacementsSemiValides(ListeCases& listeCase) override;
		//bool deplacementEstValide(const MatricePosition& destination) override;


	private:



	};
}
