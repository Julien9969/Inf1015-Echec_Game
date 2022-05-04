#include "InterfaceJeu.h"
#include <QDebug>

//#include <QGraphicsDropShadowEffect>


using iter::range;
using model::Plateau;

Ui::InterfaceJeu::InterfaceJeu(QWidget* parent) : QMainWindow(parent)
{
	window_ = new QGraphicsView(this);
	//setCentralWidget(window_);
	scene = new QGraphicsScene(window_);
	initialisationFenetre();

	MenuPrincipal();
	
}

void Ui::InterfaceJeu::initialisationFenetre()
{
	setFixedSize(1080, 780);
	setWindowIcon(QIcon("images/Icone2.ico"));

	window_->setFixedSize(1080, 780);
	window_->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	window_->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

	scene->setSceneRect(0, 0, 1080, 780);

	window_->setScene(scene);

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

	quiDoitJouer = new QGraphicsTextItem();
	quiDoitJouer->setScale(3);
	quiDoitJouer->setDefaultTextColor(Qt::black);
	quiDoitJouer->setPlainText("Tour : Blanc");
	quiDoitJouer->setPos(width() * 0.5 - 93, -2);
	scene->addItem(quiDoitJouer);

	setWindowTitle("Jeu d'Echec de Fou");
}
void Ui::InterfaceJeu::mettreTour(std::string equipeQuiJoue)
{
	QString tour = QString::fromStdString("Tour : " + equipeQuiJoue);
	quiDoitJouer->setPlainText(tour);
}

void Ui::InterfaceJeu::creationVueCases()
{
	for (int i : range(8)) {

		for (int j : range(8)) {

			model::ModelCase* caseAssocie = plateau_->listeCases(i, j);

			caseAssocie->accedeCasePixelPos()->x = (width() - 720) / 2 + 90 * j;
			caseAssocie->accedeCasePixelPos()->y = 60 + 90 * i;

			Ui::VueCase* box = new Ui::VueCase(caseAssocie->accedeCasePixelPos()->x, caseAssocie->accedeCasePixelPos()->y, 90, 90, caseAssocie); //ptrJeu_->height() -> 720

			box->mettreCoordonnees(i, j);

			if (((i + j) % 2) == 0) {

				box->mettreCouleurbase(QColor(54, 69, 137));
			}
			else {
				box->mettreCouleurbase(Qt::white);
			}
			QObject::connect(plateau_->listeCases(i, j), &model::ModelCase::mettreCouleurBase, box, &Ui::VueCase::mettreCouleurBase);
			QObject::connect(plateau_->listeCases(i, j), &model::ModelCase::mettreCouleur, box, &Ui::VueCase::mettreCouleur);
			QObject::connect(box, &Ui::VueCase::caseClique, &*plateau_, &Plateau::recevoirCaseClique);

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

		QObject::connect(piece, &Ui::VuePieceEchec::pieceClique, &*plateau_, &Plateau::recevoirPieceClique);
		QObject::connect(j->get(), &model::ModelPieceEchec::enleverLaPieceDuPlateau, &*plateau_, &Plateau::enleverPieceElimine);


		mettreDansScene(piece);

	}

	i = 0;

	for (auto&& j = plateau_->ListePieceBlanc.begin(); j != plateau_->ListePieceBlanc.end(); j++) {

		tempCase = plateau_->listeCases[56 + i++];

		VuePieceEchec* piece = new VuePieceEchec(j->get());

		j->get()->positionner(tempCase->lirePosition(), tempCase->lirePixelPos());

		QObject::connect(piece, &Ui::VuePieceEchec::pieceClique, &*plateau_, &Plateau::recevoirPieceClique);
		QObject::connect(j->get(), &model::ModelPieceEchec::enleverLaPieceDuPlateau, &*plateau_, &Plateau::enleverPieceElimine);


		mettreDansScene(piece);
	}
}


void Ui::InterfaceJeu::creationDesBord(int taille, int x, int y, QColor couleur, double opacite)
{
	 //qDebug() << scene->height();

	QGraphicsRectItem* panel = new QGraphicsRectItem(x, y, taille, height());
	QBrush brush;
	brush.setStyle(Qt::SolidPattern);
	brush.setColor(couleur);
	panel->setBrush(brush);
	panel->setOpacity(opacite);
	scene->addItem(panel);

}

void Ui::InterfaceJeu::nouvellePartie()
{
	scene->clear();

	creationElementBord();

	plateau_ = std::make_unique<Plateau>();

	QObject::connect(&*plateau_, &Plateau::changementTour, this, &InterfaceJeu::mettreTour);
	QObject::connect(&*plateau_, &Plateau::MenuPrincipal, this, &InterfaceJeu::MenuPrincipal);

	creationVueCases();
	creationVuePiece();
}

void Ui::InterfaceJeu::MenuPrincipal(std::string gagnant)
{
	scene->clear();
	plateau_ = nullptr;

	window_->setBackgroundBrush(QBrush(QColor(236, 206, 91)));
	
	QString ok = QString::fromStdString(gagnant);

	auto test = new QGraphicsTextItem(ok);
	QFont f;
	f.setPixelSize(23);
	//f.setBold(true);
	test->setFont(f);

	test->boundingRect().setWidth(100);
	test->setDefaultTextColor(Qt::darkMagenta);
	
	qDebug() << test->boundingRect().width();
	
	test->setPos(width() * 0.25, height() * 0.25);
	
	scene->addItem(test);

	Bouton* bouton = new Bouton("Nouvelle Partie", width() / 2, height() / 2);
	QObject::connect(bouton, &Bouton::clicked , this, &InterfaceJeu::nouvellePartie);
	mettreDansScene(bouton);

	Bouton* boutonQuitter = new Bouton("Quitter", width() / 2, height() / 2 + 100);
	QObject::connect(boutonQuitter, &Bouton::clicked, this, [&]() { QCoreApplication::exit(0); });

	mettreDansScene(boutonQuitter);

}

void Ui::InterfaceJeu::mettreDansScene(QGraphicsItem* object)
{
	scene->addItem(object);
}

