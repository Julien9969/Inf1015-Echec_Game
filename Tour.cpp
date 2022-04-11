#include "Tour.h"


using model::Tour;
using Ui::ListeCases;

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

	//setFlags(QGraphicsItem::ItemIsSelectable | QGraphicsItem::ItemIsMovable);
	setAcceptHoverEvents(true);

	setScale(1.4);

}

std::list<std::pair<int, int>>& Tour::deplacementsValide(ListeCases& ListeCase)
{
	//Vers le bas
	for (int ligne = ligne_ + 1; ligne < 8; ligne++)
	{
		ListeCase(ligne, colone_)->mettreCouleur(Qt::green);
	}

	return emplacementsValides;
}


Tour::~Tour()
{
}

