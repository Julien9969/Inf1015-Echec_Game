#include "VuePieceEchec.h"
#include "QDebug"

using Ui::VuePieceEchec;

VuePieceEchec::VuePieceEchec(model::ModelPieceEchec* piece, QGraphicsItem* parent) : QGraphicsPixmapItem(parent)
{
	pieceAssocie_ = piece;
    //setAcceptDrops(true);
	QObject::connect(piece, &model::ModelPieceEchec::mettrePositionVue, this, &Ui::VuePieceEchec::positionnerPiece);
	QObject::connect(piece, &model::ModelPieceEchec::suppressionPiece, this, [this]() { delete this; });

	
	setScale(1);//1.4
	//qDebug() << transformationMode();
	setPixmap(QPixmap(pieceAssocie_->lireCheminImage()));
	//setFlags(QGraphicsItem::ItemIsSelectable | QGraphicsItem::ItemIsMovable);
	setAcceptHoverEvents(true);
	
	setCursor(Qt::PointingHandCursor);
}



void VuePieceEchec::positionnerPiece(PixelPosition scenePosition)
{
	setPos(scenePosition.x, scenePosition.y);
}


void VuePieceEchec::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
	if (event->buttons() == Qt::LeftButton)
	{
		qDebug() << "clique" << pieceAssocie_->lireMatricePos().ligne << pieceAssocie_->lireMatricePos().colone;
		emit pieceClique(pieceAssocie_);
	}
}

void VuePieceEchec::hoverEnterEvent(QGraphicsSceneHoverEvent* event)
{
	if (pieceAssocie_->lireEquipe() == "Noir") {
		qDebug() << "noir";
		qDebug() << lirePiece()->lireMatricePos().ligne;
		qDebug() << lirePiece()->lireMatricePos().colone;

	}
	else {
		qDebug() << "blanc";
		qDebug() << lirePiece()->lireMatricePos().ligne;
		qDebug() << lirePiece()->lireMatricePos().colone;

	}
	//this->~VuePieceEchec();
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







