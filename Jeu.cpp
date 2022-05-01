#include "jeu.h"
#include <QDebug>

//#include <QLabel>
//#include <QGraphicsDropShadowEffect>


using iter::range;

Ui::InterfaceJeu::InterfaceJeu(QWidget* parent) : QMainWindow(parent)
{
	window_ = new QGraphicsView(this);
	scene = new QGraphicsScene(window_);

	initialisationFenetre();

	creationElementBord();

	plateau = new Plateau(this);


}

void Ui::InterfaceJeu::initialisationFenetre()
{
	setFixedSize(1080, 780);
	setWindowIcon(QIcon("images/Icone2.ico"));

	window_->setFixedSize(1080, 780);
	window_->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	window_->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

	window_->setScene(scene);

	//scene->setSceneRect(0, 0, 1080, 720);
	//setMouseTracking(true);
}

void Ui::InterfaceJeu::creationElementBord()
{
	//scene->clear()
	int taillePaneau = (width() - 720) / 2;

	creationDesBord(taillePaneau, 0, 0, Qt::blue, 0.3);

	creationDesBord(taillePaneau, width() - taillePaneau, 0, Qt::red, 0.3);

	QGraphicsTextItem* joueur1 = new QGraphicsTextItem("Jsp quoi on verra 1 :\n yufuyfuyf");
	joueur1->setPos(50, 5);
	joueur1->setScale(1);
	joueur1->setDefaultTextColor(Qt::blue);
	scene->addItem(joueur1);

	QGraphicsTextItem* joueur2 = new QGraphicsTextItem("Jsp quoi on verra 2 :");
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
	
}

void Ui::InterfaceJeu::creationDesBord(int taille, int x, int y, QColor couleur, double opacite)
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


void Ui::InterfaceJeu::mettreDansScene(QGraphicsItem* object)
{
	scene->addItem(object);
}

