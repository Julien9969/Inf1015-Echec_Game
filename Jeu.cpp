#include "jeu.h"
#include <QDebug>

#include <QLabel>
#include <QGraphicsDropShadowEffect>
#include <QEvent>


using iter::range;

Jeu::Jeu(QWidget* parent) : QMainWindow(parent)
{
	setFixedSize(1080, 720);
	window_ = new QGraphicsView(this);
	window_->setFixedSize(1080, 720);
	window_->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	window_->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

	scene = new QGraphicsScene(window_);
	scene->setSceneRect(0, 0, 1080, 720);
	window_->setScene(scene);
	
	

	debutPartie();

}

void Jeu::debutPartie()
{
	//scene->clear()
	int taillePaneau = (width() - height()) / 2;

	creationDesBord(taillePaneau, 0, 0, Qt::blue, 0.3);

	creationDesBord(taillePaneau, width() - taillePaneau, 0, Qt::red, 0.3);

	QPointer<QGraphicsTextItem> joueur1 = new QGraphicsTextItem("Jsp quoi on verra 1 :");
	joueur1->setPos(50, 5);
	scene->addItem(joueur1);

	QPointer<QGraphicsTextItem> joueur2 = new QGraphicsTextItem("Jsp quoi on verra 2 :");
	joueur2->setPos(width() - taillePaneau + 50, 5);
	scene->addItem(joueur2);

	// place whosTurnText
	quiDoitJouer = new QGraphicsTextItem();

	// getter setter a faire ?

	QString tour = "c'est a joueur x de jouer : ";

	quiDoitJouer->setPlainText(tour);
	quiDoitJouer->setPos(width() * 0.5 - 20, 5);
	scene->addItem(quiDoitJouer);

	setWindowTitle(tour);
	
	creationPlateau();

}

void Jeu::creationDesBord(int taille, int x, int y, QColor couleur, double opacite)
{
	 //qDebug() << scene->height();

	QGraphicsRectItem* panel = new QGraphicsRectItem(x, y, taille, height());
	QBrush brush;
	//brush.setStyle(Qt::SolidPattern);
	brush.setStyle(Qt::SolidPattern);
	brush.setColor(couleur);
	panel->setBrush(brush);
	panel->setOpacity(opacite);
	scene->addItem(panel);

}

void Jeu::creationPlateau()
{
	plateau_ = std::make_unique<Plateau>(this);
	plateau_->creeCases();
	plateau_->creePiecesNoir();
	plateau_->mettreLesPieces();
	
}

void Jeu::mettreDansScene(QGraphicsItem* object)
{
	scene->addItem(object);
}

