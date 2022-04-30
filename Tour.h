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

		
		std::list<EmplacementValide>& listerDeplacementsValides(Ui::ListeCases& listeCase) override;
		bool deplacementEstValide(const std::pair<int, int>& destination) override;
		

	private:


	signals:

	};
}
