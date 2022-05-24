/*
* Corps de la classe InterfaceJeu
*
* Fichier : InterfaceJeu.h, InterfaceJeu.cpp
* Auteurs : Sebastian Espin, Julien Roux
* Date : 05/05/2022
* Crée : 20/04/2022
*/

#include "InterfaceJeu.h"
#include <QDebug>

using iter::range;
using Modele::Plateau;

Ui::InterfaceJeu::InterfaceJeu(QWidget* parent) : QMainWindow(parent)
{
	window_ = new QGraphicsView(this);
	scene_ = new QGraphicsScene(window_);
	music_ = new QMediaPlayer(this);

	initialisationFenetre();
	MenuPrincipal();
}

void Ui::InterfaceJeu::initialisationFenetre()
{
	setFixedSize(1080, 780);
	setWindowIcon(QIcon("images/Icone2.ico"));
	setWindowTitle("Jeu d'Echec de Fou");

	window_->setFixedSize(1080, 780);
	window_->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	window_->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

	scene_->setSceneRect(0, 0, 1080, 778);
	window_->setScene(scene_);
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

			Modele::ModeleCase* caseAssocie = plateau_->listeCases(i, j);

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
			QObject::connect(plateau_->listeCases(i, j), &Modele::ModeleCase::mettreCouleurBase, box, &Ui::VueCase::mettreCouleurBase);
			QObject::connect(plateau_->listeCases(i, j), &Modele::ModeleCase::mettreCouleur, box, &Ui::VueCase::mettreCouleur);
			QObject::connect(box, &Ui::VueCase::caseClique, &*plateau_, &Plateau::recevoirCaseClique);

			mettreDansScene(box);
		}
	}
}

void Ui::InterfaceJeu::creationVuePiece()
{
	for (auto&& j = plateau_->ListePieceNoir.begin(); j != plateau_->ListePieceNoir.end(); j++) {

		VuePieceEchec* piece = new VuePieceEchec(j->get());

		QObject::connect(piece, &Ui::VuePieceEchec::pieceClique, &*plateau_, &Plateau::recevoirPieceClique);
		QObject::connect(j->get(), &Modele::ModelePieceEchec::enleverLaPieceDuPlateau, &*plateau_, &Plateau::enleverPieceElimine);
		QObject::connect(piece, &Ui::VuePieceEchec::jouerSon, this, &Ui::InterfaceJeu::jouerSon);

		mettreDansScene(piece);
	}

	for (auto&& j = plateau_->ListePieceBlanc.begin(); j != plateau_->ListePieceBlanc.end(); j++) {

		VuePieceEchec* piece = new VuePieceEchec(j->get());

		QObject::connect(piece, &Ui::VuePieceEchec::pieceClique, &*plateau_, &Plateau::recevoirPieceClique);
		QObject::connect(j->get(), &Modele::ModelePieceEchec::enleverLaPieceDuPlateau, &*plateau_, &Plateau::enleverPieceElimine);
		QObject::connect(piece, &Ui::VuePieceEchec::jouerSon, this, &Ui::InterfaceJeu::jouerSon);

		mettreDansScene(piece);
	}

	plateau_->mettreLesPieces();
}


void Ui::InterfaceJeu::creationDesBord(int taille, int x, int y, QColor couleur, double opacite)
{
	QBrush brush;
	brush.setStyle(Qt::SolidPattern);
	brush.setColor(couleur);

	QGraphicsRectItem* panel = new QGraphicsRectItem(x, y, taille, height());
	panel->setBrush(brush);
	panel->setOpacity(opacite);
	scene_->addItem(panel);
}

void Ui::InterfaceJeu::nouvellePartie()
{
	scene_->clear();

	window_->setBackgroundBrush(QBrush(QColor(243, 246, 244)));

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

	window_->setBackgroundBrush(QBrush(QColor(164, 150, 207)));
	
	QString ok = QString::fromStdString(textePrincipal);

	auto image = new QGraphicsPixmapItem(QPixmap("images/imageMenu"));
	image->setPos(width() * 0.5 - image->boundingRect().width() / 2, height() * 0.25);
	mettreDansScene(image);

	QFont f;
	f.setPixelSize(100);
	f.setBold(true);

	auto test = new QGraphicsTextItem(ok);
	test->setFont(f);
	test->setDefaultTextColor(Qt::black);
	test->setPos(width() * 0.5 - test->boundingRect().width() / 2, 40);
	mettreDansScene(test);

	Bouton* BoutonInfo = new Bouton("?", width() - 40, 10, 60, 60);
	QObject::connect(BoutonInfo, &Bouton::clicked, this, &InterfaceJeu::menuInfo);
	mettreDansScene(BoutonInfo);


	Bouton* bouton = new Bouton("Nouvelle Partie", width() / 2, height() / 2 + 100);
	QObject::connect(bouton, &Bouton::clicked , this, &InterfaceJeu::nouvellePartie);
	mettreDansScene(bouton);

	Bouton* boutonQuitter = new Bouton("Quitter", width() / 2, height() / 2 + 200);
	QObject::connect(boutonQuitter, &Bouton::clicked, this, [&]() { QCoreApplication::exit(0); });

	mettreDansScene(boutonQuitter);
}


void Ui::InterfaceJeu::creationElementBord()
{
	int taillePaneau = (width() - 720) / 2;

	creationDesBord(taillePaneau, 0, 0, QColor(114, 137, 218), 1);
	creationDesBord(taillePaneau, width() - taillePaneau, 0, QColor(199, 102, 102), 1);

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
}

void Ui::InterfaceJeu::menuInfo() 
{
	scene_->clear();

	Bouton* closeInfo = new Bouton("X", width() - 40, 10, 60, 60);
	QObject::connect(closeInfo, &Bouton::clicked, this, &InterfaceJeu::retour);
	mettreDansScene(closeInfo);

	menuInfoText("Information sur le jeu", width() * 0.5 - 270, 30, 55, true);

	menuInfoText("Le jeu se termine quand un joueur n'a plus de coups possible\n \
		ou quand il ne reste qu'une pièce par joueur/", width() * 0.05, 150, 35, false);


	menuInfoCase(width() * 0.15, height() * 0.40, 90, 90, Qt::darkGreen);
	menuInfoText("Positions de déplacement valides", 300, height() * 0.42, 35, false);

	menuInfoCase(width() * 0.15, height() * 0.60, 90, 90, Qt::darkRed);
	menuInfoText("Pièce adverse pouvant être mangée", 300, height() * 0.62, 35, false);

	menuInfoCase(width() * 0.15, height() * 0.80, 90, 90, QColor(236, 206, 91));
	menuInfoText("Pièce adverse restreignant nos déplacements", 300, height() * 0.82, 35, false);
}

void Ui::InterfaceJeu::menuInfoText(QString texte, int xPos, int yPos ,int taille, bool bold ) 
{
	QFont f;
	f.setPixelSize(taille);
	f.setBold(bold);

	auto test = new QGraphicsTextItem(texte);
	test->setFont(f);
	test->setDefaultTextColor(Qt::black);
	test->setPos(xPos, yPos);
	mettreDansScene(test);

}

void Ui::InterfaceJeu::menuInfoCase(int xPos, int yPos, int xSize, int ySize, QColor couleur) 
{
	QBrush brush;
	brush.setStyle(Qt::SolidPattern);

	brush.setColor(couleur);
	QGraphicsRectItem* caseVerte = new QGraphicsRectItem(xPos, yPos, xSize, ySize);
	caseVerte->setBrush(brush);
	mettreDansScene(caseVerte);
}

void Ui::InterfaceJeu::retour()
{
	MenuPrincipal();
}

void Ui::InterfaceJeu::mettreDansScene(QGraphicsItem* object)
{
	scene_->addItem(object);
}

void Ui::InterfaceJeu::jouerSon(QString cheminVersSon) 
{
	music_->setMedia(QUrl(cheminVersSon));
	music_->setVolume(20);
	music_->play();
}
