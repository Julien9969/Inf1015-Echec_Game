#pragma once
#include "ModelPieceEchec.h"
#include <QGraphicsPixmapItem>
#include <stdexcept>

namespace model {
	class Roi : public ModelPieceEchec
	{
	public:
		Roi(std::string equipe);
		~Roi() { compteurDeRoi--; }


		std::list<EmplacementValide>& listerDeplacementsValides(ListeCases& listeCase) override;
		bool deplacementEstValide(const MatricePosition& destination) override;


	private:
		static inline int compteurDeRoi = 0;

	signals:

	};
}

