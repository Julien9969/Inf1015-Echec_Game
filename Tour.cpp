#include "Tour.h"




Tour::Tour(QString equipe, QGraphicsItem* parent) : PieceEchec(equipe, parent)
{
	ajouterImage();
	
}


void Tour::ajouterImage()
{
	if (equipe_ == "Noir") {
		setPixmap(QPixmap("images/TourN.png"));
	}
	else {
		setPixmap(QPixmap("images/TourB.png"));
	}

	setFlags(QGraphicsItem::ItemIsSelectable | QGraphicsItem::ItemIsMovable);
	setAcceptHoverEvents(true);

	setScale(1.4);

}

void Tour::deplacementValide()
{
	

}


Tour::~Tour()
{
}

