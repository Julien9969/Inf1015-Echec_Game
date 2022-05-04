#include "VuePieceEchec.h"
#include "QDebug"

using Ui::VuePieceEchec;

VuePieceEchec::VuePieceEchec(model::ModelPieceEchec* piece, QGraphicsItem* parent) : QGraphicsPixmapItem(parent)
{
	pieceAssocie_ = piece;
    
	QObject::connect(piece, &model::ModelPieceEchec::mettrePositionVue, this, &Ui::VuePieceEchec::positionnerPiece);
	QObject::connect(piece, &model::ModelPieceEchec::suppressionPiece, this, [this]() { delete this; });
	
	setPixmap(QPixmap(pieceAssocie_->lireCheminImage()));
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
	event->accept();
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
}







