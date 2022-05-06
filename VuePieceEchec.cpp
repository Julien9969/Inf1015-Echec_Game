//Corps de la classe VuePieceEchec
#include "VuePieceEchec.h"
#include "QDebug"

using Ui::VuePieceEchec;

VuePieceEchec::VuePieceEchec(Modele::ModelePieceEchec* piece, QGraphicsItem* parent) : QGraphicsPixmapItem(parent)
{
	pieceAssocie_ = piece;
    
	QObject::connect(piece, &Modele::ModelePieceEchec::mettrePositionVue, this, &Ui::VuePieceEchec::positionnerPiece);
	QObject::connect(piece, &Modele::ModelePieceEchec::suppressionPiece, this, [this]() { delete this; });
	
	setPixmap(QPixmap(pieceAssocie_->lireCheminImage()));
	setAcceptHoverEvents(true);
	
	setCursor(Qt::PointingHandCursor);
}



void VuePieceEchec::positionnerPiece(PixelPosition scenePosition)
{
	emit jouerSon("Sons/Move.mp3");
	setPos(scenePosition.x, scenePosition.y);
}


void VuePieceEchec::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
	if (event->buttons() == Qt::LeftButton)
	{
		qDebug() << "clique" << pieceAssocie_->lireMatricePos().ligne << pieceAssocie_->lireMatricePos().colonne;
		emit pieceClique(pieceAssocie_);
	}
}

void VuePieceEchec::hoverEnterEvent(QGraphicsSceneHoverEvent* event)
{
	event->accept();
	if (pieceAssocie_->lireEquipe() == "Noir")
	{
		qDebug() << "noir" << lirePiece()->lireMatricePos().ligne << lirePiece()->lireMatricePos().colonne;
	}
	else 
	{
		qDebug() << "blanc" << lirePiece()->lireMatricePos().ligne << lirePiece()->lireMatricePos().colonne;
	}
}

Ui::VuePieceEchec::~VuePieceEchec()
{
	emit jouerSon("Sons/Slash.mp3");
}






