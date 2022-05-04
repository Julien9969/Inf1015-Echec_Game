#include "VueCase.h"
#include <QDebug>


Ui::VueCase::VueCase(qreal x, qreal y, qreal width, qreal height, model::ModelCase* caseAssocie, QGraphicsItem* parent) : QGraphicsRectItem(x, y, width, height, parent)
{
	caseAssocie_ = caseAssocie;

	setOpacity(1);
	brush.setStyle(Qt::SolidPattern);
	setBrush(brush);
	
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
	event->accept();

	brush.setColor(Qt::darkGray);
	setBrush(brush);

	if (couleurActuelle != Qt::darkGreen) {
		setCursor(Qt::ForbiddenCursor);
	}
	else {
		setCursor(Qt::ArrowCursor);
	}

	QString ok;
	caseAssocie_->getPiece() != nullptr ? ok = QString::fromStdString(caseAssocie_->getPiece()->lireEquipe()) : ok = " Null";

	qDebug() <<" case pos : "<< ok << " " << ligne_ << " " << colone_;
}


void Ui::VueCase::hoverLeaveEvent(QGraphicsSceneHoverEvent* event) 
{
	event->accept();
	mettreCouleur(couleurActuelle);
}


void Ui::VueCase::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
	if (event->buttons() == Qt::LeftButton)
	{
		
		qDebug() << "cliqueCase";
		emit caseClique(caseAssocie_);
	}
}

