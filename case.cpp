#include "case.h"


extern QPointer<Jeu> jeu;

Case::Case(qreal x, qreal y, qreal width, qreal height, QGraphicsItem* parent) : QGraphicsRectItem(x, y, width, height, parent)
{
	//brush.setStyle(Qt::SolidPattern);
	setOpacity(0.8);
	setBrush(brush);

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
	setBrush(brush);
}