#include "jeu.h"
#include <QDebug>
#include <QLabel>

using namespace iter;

Jeu::Jeu(QWidget* parent) : QGraphicsView(parent)
{
	setFixedSize(1080, 720);
	setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

	scene = new QGraphicsScene();
	scene->setSceneRect(0, 0, 1080, 720);
	setScene(scene);



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

	image();
	
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
	for (int i : range(8)) {

		for (int j : range(8)) {
			Case* box = new Case((width() - height()) / 2 + 90 * i, 90 * j, 90, 90);

			if (((i + j) % 2) == 0) {
				box->mettreCouleur(Qt::black);
			}
			scene->addItem(box);
			ListeCase.push_back(box);

		}
	}
}

void Jeu::image() {

	auto box = dynamic_cast<Case*>(ListeCase[0]);
	box->mettreCouleur(Qt::blue);
	/*box->*/

}