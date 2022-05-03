#include "VueCase.h"
#include <QDebug>


Ui::VueCase::VueCase(qreal x, qreal y, qreal width, qreal height, model::ModelCase* caseAssocie, QGraphicsItem* parent) : QGraphicsRectItem(x, y, width, height, parent)
{
	caseAssocie_ = caseAssocie;

	setOpacity(1);
	brush.setStyle(Qt::SolidPattern);
	setBrush(brush);
	
	//setFlags(QGraphicsItem::ItemIsSelectable); //QGraphicsItem::ItemIsMovable | 
	setAcceptHoverEvents(true);
	setAcceptDrops(true);
}

void Ui::VueCase::mettreCoordonnees(int i, int j)
{
	ligne_ = i;
	colone_ = j;
}

void Ui::VueCase::mettreCouleurbase(QColor couleur) {
	couleurDeBase_ = couleur; 
	mettreCouleur(couleur);
}

void Ui::VueCase::mettreCouleur(QColor couleur)
{
	couleurActuelle = couleur;
	brush.setColor(couleur);
	setBrush(brush);
}

void Ui::VueCase::mettreCouleurBase()
{
	couleurActuelle = couleurDeBase_;
	brush.setColor(couleurDeBase_);
	setBrush(brush);
}


void Ui::VueCase::hoverEnterEvent(QGraphicsSceneHoverEvent* event)
{
	brush.setColor(Qt::darkGray);
	setBrush(brush);

	if (couleurActuelle != Qt::darkGreen) {
		setCursor(Qt::ForbiddenCursor);
	}
	else {
		setCursor(Qt::ArrowCursor);
	}

	qDebug() <<" case pos : "<< caseAssocie_->getPiece() << " " << ligne_ << " " << colone_;
	
}


void Ui::VueCase::hoverLeaveEvent(QGraphicsSceneHoverEvent* event) {
	mettreCouleur(couleurActuelle);
	
	//qDebug() << "leaving";
}


void Ui::VueCase::mouseReleaseEvent(QGraphicsSceneMouseEvent* event)
{
	
	qDebug() << "deClique" << " " << ligne_ << " " << colone_;

}


void Ui::VueCase::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
	if (event->buttons() == Qt::LeftButton)
	{
		
		qDebug() << "cliqueCase";
		emit caseClique(caseAssocie_);
	}
	
}

