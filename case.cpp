#include "case.h"
#include <QDebug>


Ui::Case::Case(qreal x, qreal y, qreal width, qreal height, QGraphicsItem* parent) : QGraphicsRectItem(x, y, width, height, parent)
{
	//brush.setStyle(Qt::SolidPattern);
	xPixPos_ = x;
	yPixPos_ = y;
	setOpacity(0.8);
	setBrush(brush);
	setFlags(QGraphicsItem::ItemIsSelectable); //QGraphicsItem::ItemIsMovable | 
	setAcceptHoverEvents(true);
	setAcceptDrops(true);

	//jeu->scene->addItem(this);
}

void Ui::Case::mettreCoordonnees(int i, int j)
{
	ligne_ = i;
	colone_ = j;
}

void Ui::Case::mettreCouleur(Qt::GlobalColor couleur)
{
	brush.setStyle(Qt::SolidPattern);
	brush.setColor(couleur);
	color_ = brush.color();
	setBrush(brush);
}

void Ui::Case::mettrePiece(model::PieceEchec* piece)
{
	piece_ = piece;
}

void Ui::Case::hoverEnterEvent(QGraphicsSceneHoverEvent* event)
{
	brush.setColor(Qt::darkGray);
	qDebug() <<"case pos : " << piece_ << " " << ligne_ << " " << colone_;
	setBrush(brush);
	update();
	
}


void Ui::Case::hoverLeaveEvent(QGraphicsSceneHoverEvent* event) {
	brush.setColor(color_);
	//qDebug() << "leaving";
	setBrush(brush);
	update();

}

const std::pair<int, int> Ui::Case::lirePixPosition() const
{
	return std::pair<int, int>(xPixPos_, yPixPos_);
}

const std::pair<int, int> Ui::Case::lireMatricePosition() const
{
	return std::pair<int, int>(ligne_, colone_);
}


void Ui::Case::mouseReleaseEvent(QGraphicsSceneMouseEvent* event)
{
	
	//qDebug() << "deClique";
	
}


void Ui::Case::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
	if (event->buttons() == Qt::LeftButton)
	{
		
		qDebug() << "cliqueCase";
		emit caseClique(this);
	}

}

