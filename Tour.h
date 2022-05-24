/*
* Classe impl�mentant la logique de la pi�ce Tour.
*
* Fichier : Tour.h, Tour.cpp
* Auteurs : Sebastian Espin, Julien Roux
* Date : 05/05/2022
* Cr�e : 30/04/2022
*/

#pragma once
#include "ModelePieceEchec.h"

namespace Modele {

	class Tour : public ModelePieceEchec
	{
	public:
		Tour(std::string equipe);
		//~Tour() = default;

		void listerDeplacementsSemiValides(ListeCases& listeCase) override;
		//bool deplacementEstValide(const MatricePosition& destination) override;
		

	private:



	};
}
