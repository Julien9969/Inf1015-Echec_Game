#pragma once
#include "ModelPieceEchec.h"
#include <stdexcept>

namespace model {
	class Roi : public ModelPieceEchec
	{
	public:
		Roi(std::string equipe);
		~Roi() { compteurDeRoi--; }


		void listerDeplacementsSemiValides(ListeCases& listeCase) override;
		bool deplacementEstValide(const MatricePosition& destination) override;

		

	private:
		static inline int compteurDeRoi = 0;

	};
}

