#pragma once
#include <QGraphicsPixmapItem>
#include <utility>


class PieceEchec : public QGraphicsPixmapItem
{
public:
	PieceEchec(QString equipe, QGraphicsItem* parent = NULL);
	//~PieceEchec() = default ;

	virtual void ajouterImage() = 0;

	virtual void deplacementValide() = 0;
	void positionnerPiece(int x, int y, std::pair<int, int> pos);

protected:
	QString equipe_;
	int x_;
	int y_;
};

