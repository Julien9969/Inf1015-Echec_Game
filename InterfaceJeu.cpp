#include "InterfaceJeu.h"
#include <QDebug>

using iter::range;
using model::Plateau;

Ui::InterfaceJeu::InterfaceJeu(QWidget* parent) : QMainWindow(parent)
{
	window_ = new QGraphicsView(this);
	scene_ = new QGraphicsScene(window_);

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

	scene_->setSceneRect(0, 0, 1080, 778);

	window_->setScene(scene_);
}

void Ui::InterfaceJeu::creationElementBord()
{
	int taillePaneau = (width() - 720) / 2;

	creationDesBord(taillePaneau, 0, 0, QColor(114, 137, 218), 1);

	creationDesBord(taillePaneau, width() - taillePaneau, 0, QColor(255, 78, 80), 1);

	QFont f;
	f.setPixelSize(30);

	QGraphicsTextItem* joueur1 = new QGraphicsTextItem("Blanc : ");
	joueur1->setPos(50, 5);
	joueur1->setFont(f);
	scene_->addItem(joueur1);

	QGraphicsTextItem* joueur2 = new QGraphicsTextItem("Noir : ");
	joueur2->setFont(f);
	joueur2->setPos(width() - taillePaneau + 50, 5);
	scene_->addItem(joueur2);

	quiDoitJouer = new QGraphicsTextItem();
	quiDoitJouer->setScale(3);
	quiDoitJouer->setDefaultTextColor(Qt::black);
	quiDoitJouer->setPlainText("Tour : Blanc");
	quiDoitJouer->setPos(width() * 0.5 - 93, -2);
	scene_->addItem(quiDoitJouer);

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
				box->mettreCouleurbase(QColor(238, 238, 238));
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
	for (auto&& j = plateau_->ListePieceNoir.begin(); j != plateau_->ListePieceNoir.end(); j++) {

		//tempCase = plateau_->listeCases[i++];

		VuePieceEchec* piece = new VuePieceEchec(j->get());

		//j->get()->positionner(tempCase->lirePosition(), tempCase->lirePixelPos());

		QObject::connect(piece, &Ui::VuePieceEchec::pieceClique, &*plateau_, &Plateau::recevoirPieceClique);
		QObject::connect(j->get(), &model::ModelPieceEchec::enleverLaPieceDuPlateau, &*plateau_, &Plateau::enleverPieceElimine);


		mettreDansScene(piece);

	}

	//i = 0;

	for (auto&& j = plateau_->ListePieceBlanc.begin(); j != plateau_->ListePieceBlanc.end(); j++) {

		//tempCase = plateau_->listeCases[56 + i++];

		VuePieceEchec* piece = new VuePieceEchec(j->get());

		//j->get()->positionner(tempCase->lirePosition(), tempCase->lirePixelPos());

		QObject::connect(piece, &Ui::VuePieceEchec::pieceClique, &*plateau_, &Plateau::recevoirPieceClique);
		QObject::connect(j->get(), &model::ModelPieceEchec::enleverLaPieceDuPlateau, &*plateau_, &Plateau::enleverPieceElimine);


		mettreDansScene(piece);
	}

	plateau_->mettreLesPieces();
}


void Ui::InterfaceJeu::creationDesBord(int taille, int x, int y, QColor couleur, double opacite)
{
	QGraphicsRectItem* panel = new QGraphicsRectItem(x, y, taille, height());
	QBrush brush;
	brush.setStyle(Qt::SolidPattern);
	brush.setColor(couleur);
	panel->setBrush(brush);
	panel->setOpacity(opacite);
	scene_->addItem(panel);
}

void Ui::InterfaceJeu::nouvellePartie()
{
	scene_->clear();

	creationElementBord();

	plateau_ = std::make_unique<Plateau>();

	QObject::connect(&*plateau_, &Plateau::changementTour, this, &InterfaceJeu::mettreTour);
	QObject::connect(&*plateau_, &Plateau::MenuPrincipal, this, &InterfaceJeu::MenuPrincipal);

	creationVueCases();
	creationVuePiece();
}

void Ui::InterfaceJeu::MenuPrincipal(std::string textePrincipal)
{
	scene_->clear();
	plateau_ = nullptr;

	window_->setBackgroundBrush(QBrush(QColor(236, 206, 91)));
	
	QString ok = QString::fromStdString(textePrincipal);

	auto test = new QGraphicsTextItem(ok);
	QFont f;
	f.setPixelSize(100);
	f.setBold(true);
	test->setFont(f);
	test->setDefaultTextColor(Qt::black);
	test->setPos(width() * 0.5 - test->boundingRect().width() / 2, 40);
	scene_->addItem(test);

	Bouton* bouton = new Bouton("Nouvelle Partie", width() / 2, height() / 2);
	QObject::connect(bouton, &Bouton::clicked , this, &InterfaceJeu::nouvellePartie);
	mettreDansScene(bouton);

	Bouton* boutonQuitter = new Bouton("Quitter", width() / 2, height() / 2 + 100);
	QObject::connect(boutonQuitter, &Bouton::clicked, this, [&]() { QCoreApplication::exit(0); });

	mettreDansScene(boutonQuitter);
}

void Ui::InterfaceJeu::mettreDansScene(QGraphicsItem* object)
{
	scene_->addItem(object);
}

