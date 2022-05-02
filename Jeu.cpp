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

	plateau_ = new Plateau();

	creationVueCases();
	creationVuePiece();
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

void Ui::InterfaceJeu::creationVueCases()
{
	
	for (int i : range(8)) {

		for (int j : range(8)) {

			model::ModelCase* caseAssocie = plateau_->listeCases(i, j);

			caseAssocie->accedeCasePixelPos()->x = (width() - 720) / 2 + 90 * j;
			caseAssocie->accedeCasePixelPos()->y = 60 + 90 * i;

			Ui::Case* box = new Ui::Case(caseAssocie->accedeCasePixelPos()->x, caseAssocie->accedeCasePixelPos()->y, 90, 90, caseAssocie); //ptrJeu_->height() -> 720

			box->mettreCoordonnees(i, j);

			if (((i + j) % 2) == 0) {

				box->mettreCouleurbase(Qt::darkBlue);
			}
			else {
				box->mettreCouleurbase(Qt::white);
			}
			QObject::connect(plateau_->listeCases(i, j), &model::ModelCase::mettreCouleurBase, box, &Ui::Case::mettreCouleurBase);
			QObject::connect(plateau_->listeCases(i, j), &model::ModelCase::mettreCouleur, box, &Ui::Case::mettreCouleur);
			QObject::connect(box, &Ui::Case::caseClique, plateau_, &Plateau::recevoirCaseClique);

			mettreDansScene(box);

		}
	}
	
}

void Ui::InterfaceJeu::creationVuePiece()
{
	model::ModelCase* tempCase;
	int i = 0;

	for (auto&& j = plateau_->ListePieceNoir.begin(); j != plateau_->ListePieceNoir.end(); j++) {

		tempCase = plateau_->listeCases[i++];

		VuePieceEchec* piece = new VuePieceEchec(j->get());

		j->get()->positionner(tempCase->lirePosition(), tempCase->lirePixelPos());

		QObject::connect(piece, &Ui::VuePieceEchec::pieceClique, plateau_, &Plateau::recevoirPieceClique);
		QObject::connect(j->get(), &model::ModelPieceEchec::enleverLaPieceDuPlateau, plateau_, &Plateau::enleverPieceElimine);


		mettreDansScene(piece);

	}

	i = 0;

	for (auto&& j = plateau_->ListePieceBlanc.begin(); j != plateau_->ListePieceBlanc.end(); j++) {

		tempCase = plateau_->listeCases[56 + i++];

		VuePieceEchec* piece = new VuePieceEchec(j->get());

		j->get()->positionner(tempCase->lirePosition(), tempCase->lirePixelPos());

		QObject::connect(piece, &Ui::VuePieceEchec::pieceClique, plateau_, &Plateau::recevoirPieceClique);
		QObject::connect(j->get(), &model::ModelPieceEchec::enleverLaPieceDuPlateau, plateau_, &Plateau::enleverPieceElimine);


		mettreDansScene(piece);
	}
	
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

