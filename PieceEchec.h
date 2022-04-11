#pragma once
#include <QGraphicsPixmapItem>
#include <QGraphicsSceneMouseEvent>
#include <utility>
#include <QObject>
#include <list>
#include "case.h"

namespace Ui { 
	class Case;
	struct ListeCases;
};


namespace model {

	class PieceEchec : public QObject, public QGraphicsPixmapItem
	{
		Q_OBJECT
	public:
		PieceEchec(QString equipe, QGraphicsItem* parent = NULL);
		~PieceEchec() = default;

		void mousePressEvent(QGraphicsSceneMouseEvent* event);
		virtual void hoverEnterEvent(QGraphicsSceneHoverEvent* event);
		//void mouseMoveEvent(QGraphicsSceneMouseEvent* event);

		int lireX() const { return ligne_; }
		int lireY() const { return colone_; }

		void estDeClique() { estClique = false; }

		virtual void ajouterImage() = 0;
		

		virtual std::list<std::pair<int, int>>& deplacementsValide(Ui::ListeCases& ListeCase) = 0;
		void positionnerPiece(std::pair<int, int> matricePos, std::pair<int, int> pos);

	protected:
		QString equipe_;
		int ligne_ = 0;
		int colone_ = 0;

		bool estClique = false;

		std::list<std::pair<int, int>> emplacementsValides;

	signals:
		void pieceClique(PieceEchec* pieceClique);

	};
}
