#pragma once
#include "ModelPieceEchec.h"
#include <QGraphicsPixmapItem>
#include <utility>


namespace model {

	class Tour : public ModelPieceEchec
	{
	public:
		Tour(std::string equipe);
		//~Tour() = default;

	//public slots:
		std::list<EmplacementValide>& listerDeplacementsValides(ListeCases& listeCase) override;
		bool deplacementEstValide(const MatricePosition& destination) override;
		

	private:


	//signals:

	};
}
