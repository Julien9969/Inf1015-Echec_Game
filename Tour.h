#pragma once
#include "PieceEchec.h"
#include <QGraphicsPixmapItem>
#include <utility>

namespace Ui {
	class Case;
	struct ListeCases;
};

namespace model {

	class Tour : public PieceEchec
	{
	public:
		Tour(QString equipe, QGraphicsItem* parent = NULL);
		~Tour() = default;

		void ajouterImage() override;
		std::list<CaseValide>& listerDeplacementsValides(Ui::ListeCases& listeCase) override;
		bool deplacementEstValide(const std::pair<int, int>& destination) override;
		

	private:

	};
}
