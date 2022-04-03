#include "case.h"
#include <QDebug>

extern QPointer<Jeu> jeu;

Case::Case(qreal x, qreal y, qreal width, qreal height, QGraphicsItem* parent) : QGraphicsRectItem(x, y, width, height, parent)
{
	//brush.setStyle(Qt::SolidPattern);
	setOpacity(0.8);
	setBrush(brush);
	setFlags(QGraphicsItem::ItemIsSelectable); //QGraphicsItem::ItemIsMovable | 
	setAcceptHoverEvents(true);

	//jeu->scene->addItem(this);
}

Case::~Case()
{
	delete this;
}


void Case::mettreCouleur(Qt::GlobalColor couleur)
{
	brush.setStyle(Qt::SolidPattern);
	brush.setColor(couleur);
	color_ = brush.color();
	setBrush(brush);
}

void Case::hoverEnterEvent(QGraphicsSceneHoverEvent* event)
{
	brush.setColor(Qt::darkGray);
	qDebug() << "entering";
	setBrush(brush);
	update();
	
}

void Case::hoverLeaveEvent(QGraphicsSceneHoverEvent* event) {
	brush.setColor(color_);
	qDebug() << "leaving";
	setBrush(brush);
	update();

}