//Corps de la classe VueCase
#include "VueCase.h"
#include <QDebug>


Ui::VueCase::VueCase(qreal x, qreal y, qreal width, qreal height, Modele::ModeleCase* caseAssocie, QGraphicsItem* parent) : QGraphicsRectItem(x, y, width, height, parent)
{
	caseAssocie_ = caseAssocie;

	brush.setStyle(Qt::SolidPattern);
	setBrush(brush);
	
	setAcceptHoverEvents(true);
}

void Ui::VueCase::mettreCoordonnees(int i, int j)
{
	ligne_ = i;
	colonne_ = j;
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

	brush.setColor(QColor(148, 148, 148));
	setBrush(brush);

	if (couleurActuelle != QColor(148, 148, 148)) {
		setCursor(Qt::ForbiddenCursor);
	}
	else {
		setCursor(Qt::ArrowCursor);
	}

	QString piece;
	caseAssocie_->getPiece() != nullptr ? piece = QString::fromStdString(caseAssocie_->getPiece()->lireEquipe()) : piece = " Null";

	qDebug() <<" case pos : "<< piece << " " << ligne_ << " " << colonne_;
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
		emit caseClique(caseAssocie_);
	}
}

