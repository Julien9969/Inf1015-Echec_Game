#include "PieceEchec.h"
#include "QDebug"



PieceEchec::PieceEchec(QString equipe, QGraphicsItem* parent) : QGraphicsPixmapItem(parent)
{
	equipe_ = equipe;
}

void PieceEchec::positionnerPiece(int xPos, int yPos, std::pair<int, int> pos)
{
	qDebug() << pos.first;
	x_ = xPos;
	y_ = yPos;
	setPos(pos.first, pos.second);
}