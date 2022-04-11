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
	ligne_ = matricePos.first;
	colone_ = matricePos.second;
	setPos(pixPos.first, pixPos.second);
}

void PieceEchec::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
	if (event->buttons() == Qt::LeftButton)
	{
		estClique = true;
		qDebug() << "clique";
		emit pieceClique(this);
	}

}

//void PieceEchec::mouseMoveEvent(QGraphicsSceneMouseEvent* event) {
//	// if there is a cardToPlace, then make it follow the mouse
//	if (estClique) {
//		setPos(event->scenePos().x() - 45, event->scenePos().y() - 45);
//		qDebug() << "piece move" << event->pos();
//
//	}
//
//	qDebug() << "move";
//	QGraphicsPixmapItem::mouseMoveEvent(event);
//}


void PieceEchec::hoverEnterEvent(QGraphicsSceneHoverEvent* event)
{
	qDebug() << ligne_ << " " << colone_;
	//this->~PieceEchec();
}
