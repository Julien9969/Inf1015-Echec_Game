#include "PieceEchec.h"
#include "QDebug"

using model::PieceEchec;

PieceEchec::PieceEchec(QString equipe, QGraphicsItem* parent) : QGraphicsPixmapItem(parent)
{
	equipe_ = equipe;
	pieceDuJeuEstClique = false;
    //setAcceptDrops(true);


}

void PieceEchec::positionnerPiece(std::pair<int, int> matricePos, std::pair<int, int> scenePos)
{
	qDebug() << scenePos.first;
	ligne_ = matricePos.first;
	colone_ = matricePos.second;
	ScenePos_ = scenePos;

	setPos(scenePos.first, scenePos.second);
}



void PieceEchec::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
	if (event->buttons() == Qt::LeftButton)
	{
		pieceDuJeuEstClique = true;
		qDebug() << "clique";
		emit pieceClique(this);
	}

}

void PieceEchec::mangeLaPiece(PieceEchec* piece) {
	positionnerPiece(piece->matricePos(), piece->ScenePos_);
	qDebug() << "une piece : " << piece->equipe_ << " a été mangé.";

	delete piece;
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
	qDebug() << pieceDuJeuEstClique;
	//this->~PieceEchec();
}




