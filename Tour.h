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
		~Tour();

		void ajouterImage() override;
		std::list<std::pair<int, int>>& deplacementsValide(Ui::ListeCases& ListeCase) override;

		

	private:

	};
}
