#include "case.h"
#include <QDebug>


Ui::Case::Case(qreal x, qreal y, qreal width, qreal height, QGraphicsItem* parent) : QGraphicsRectItem(x, y, width, height, parent)
{
	xPixPos_ = x;
	yPixPos_ = y;

	setOpacity(0.8);
	brush.setStyle(Qt::SolidPattern);
	setBrush(brush);
	
	//setFlags(QGraphicsItem::ItemIsSelectable); //QGraphicsItem::ItemIsMovable | 
	setAcceptHoverEvents(true);
	setAcceptDrops(true);

}

void Ui::Case::mettreCoordonnees(int i, int j)
{
	ligne_ = i;
	colone_ = j;
}

void Ui::Case::mettreCouleurbase(QColor couleur) {
	couleurDeBase_ = couleur; 
	mettreCouleur(couleur);
}

void Ui::Case::mettreCouleur(QColor couleur)
{
	couleurActuelle = couleur;
	brush.setColor(couleur);
	setBrush(brush);
}

void Ui::Case::mettreCouleur()
{
	couleurActuelle = couleurDeBase_;
	brush.setColor(couleurDeBase_);
	setBrush(brush);
}

void Ui::Case::mettrePiece(model::ModelPieceEchec* piece)
{
	piece_ = piece;
}

void Ui::Case::hoverEnterEvent(QGraphicsSceneHoverEvent* event)
{
	brush.setColor(Qt::darkGray);
	setBrush(brush);

	qDebug() <<"case pos : " << piece_ << " " << ligne_ << " " << colone_;
	update();
	
}


void Ui::Case::hoverLeaveEvent(QGraphicsSceneHoverEvent* event) {
	mettreCouleur(couleurActuelle);
	//qDebug() << "leaving";
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
	
	qDebug() << "deClique";
	
}


void Ui::Case::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
	if (event->buttons() == Qt::LeftButton)
	{
		
		qDebug() << "cliqueCase";
		emit caseClique(this);
	}

}

