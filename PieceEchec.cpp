#include "PieceEchec.h"
#include "QDebug"

using model::PieceEchec;

PieceEchec::PieceEchec(QString equipe, QGraphicsItem* parent) : QGraphicsPixmapItem(parent)
{
	equipe_ = equipe;
	
    //setAcceptDrops(true);
    



}

void PieceEchec::positionnerPiece(std::pair<int, int> matricePos, std::pair<int, int> pixPos)
{
	qDebug() << pixPos.first;
	x_ = matricePos.first;
	y_ = matricePos.second;
	setPos(pixPos.first, pixPos.second);
}

void PieceEchec::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
	if (event->buttons() == Qt::LeftButton)
	{
		qDebug() << "clique";
		emit pieceClique(this);
	}

}

void PieceEchec::hoverEnterEvent(QGraphicsSceneHoverEvent* event)
{
	qDebug() << x_ << " " << y_;
}
