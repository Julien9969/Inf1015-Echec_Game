#pragma once
#include "ModelPieceEchec.h"

namespace model {

	class Fou : public ModelPieceEchec
	{
	public:
		Fou(std::string equipe);
		//~Fou() = default;

		void listerDeplacementsValides(ListeCases& listeCase) override;
		bool deplacementEstValide(const MatricePosition& destination) override;


	private:



	};
}
