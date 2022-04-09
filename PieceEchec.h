#pragma once
#include <QGraphicsPixmapItem>
#include <QGraphicsSceneMouseEvent>
#include <utility>
#include <QObject>

namespace model {

	class PieceEchec : public QObject, public QGraphicsPixmapItem
	{
		Q_OBJECT
	public:
		PieceEchec(QString equipe, QGraphicsItem* parent = NULL);
		~PieceEchec() = default;

		void mousePressEvent(QGraphicsSceneMouseEvent* event);
		virtual void hoverEnterEvent(QGraphicsSceneHoverEvent* event);


		int lireX() const { return x_; }
		int lireY() const { return y_; }

		virtual void ajouterImage() = 0;

		virtual void deplacementValide() = 0;
		void positionnerPiece(std::pair<int, int> matricePos, std::pair<int, int> pos);

	protected:
		QString equipe_;
		int x_;
		int y_;

	signals:
		void pieceClique(PieceEchec* pieceClique);

	};
}
