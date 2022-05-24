/*
* Classe implémentant la logique de la pièce Roi.
*
* Fichier : Roi.h, Roi.cpp
* Auteurs : Sebastian Espin, Julien Roux
* Date : 05/05/2022
* Crée : 25/04/2022
*/

#pragma once
#include "ModelePieceEchec.h"
#include <stdexcept>

namespace Modele {
	class Roi : public ModelePieceEchec
	{
	public:
		Roi(std::string equipe);
		~Roi() { compteurDeRoi--; }

		void listerDeplacementsSemiValides(ListeCases& listeCase) override;
		//bool deplacementEstValide(const MatricePosition& destination) override;		

	private:
		static inline int compteurDeRoi = 0;

	};
}

