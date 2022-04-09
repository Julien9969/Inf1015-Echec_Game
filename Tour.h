#pragma once
#include "PieceEchec.h"
#include <QGraphicsPixmapItem>
#include <utility>

namespace model {

	class Tour : public PieceEchec
	{
	public:
		Tour(QString equipe, QGraphicsItem* parent = NULL);
		~Tour();

		void ajouterImage() override;
		void deplacementValide() override;

	private:

	};
}
