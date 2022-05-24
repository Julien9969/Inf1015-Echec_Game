/*
* Classe implémentant la logique de la pièce Cavalier.
*
* Fichier : Cavalier.h, Cavalier.cpp
* Auteurs : Sebastian Espin, Julien Roux
* Date : 05/05/2022
* Crée : 30/04/2022
*/

#pragma once
#include "ModelePieceEchec.h"

namespace Modele {

	class Cavalier : public ModelePieceEchec
	{
	public:
		Cavalier(std::string equipe);

		void listerDeplacementsSemiValides(ListeCases& listeCase) override;
		//bool deplacementEstValide(const MatricePosition& destination) override;


	private:



	};
}
