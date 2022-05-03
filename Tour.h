#pragma once
#include "ModelPieceEchec.h"

namespace model {

	class Tour : public ModelPieceEchec
	{
	public:
		Tour(std::string equipe);
		//~Tour() = default;

		void listerDeplacementsSemiValides(ListeCases& listeCase) override;
		bool deplacementEstValide(const MatricePosition& destination) override;
		

	private:



	};
}
