/*
* Interface graphique du jeu d'échec, s'occupe de crée les différents menus et les représentations des cases et des pieces
* 
*
* Fichier : InterfaceJeu.h, InterfaceJeu.cpp
* Auteurs : Sebastian Espin, Julien Roux
* Date : 05/05/2022
* Crée : 20/04/2022
*/


#pragma once
#pragma warning(disable:5054)
#include <QMainWindow>
#include <QCoreApplication>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsTextItem>
#include <QGraphicsRectItem>
#include <QMediaPlayer>
#pragma warning(default:5054)

#include <cppitertools/range.hpp>
#include "Bouton.h"
#include "VueCase.h"
#include "VuePieceEchec.h"
#include "Plateau.h"

namespace Modele {
	class Plateau;
}

namespace Ui {

	class InterfaceJeu : public QMainWindow
	{
		Q_OBJECT

	public:
		InterfaceJeu(QWidget* parent = NULL);

		~InterfaceJeu() = default;

		void initialisationFenetre();

		void nouvellePartie();

		void creationElementBord();
		void creationDesBord(int taille, int x, int y, QColor couleur, double opacite);

		void creationVueCases();
		void creationVuePiece();

		Modele::Plateau* plateau() const { return plateau_.get(); }
		QGraphicsScene* scene() const { return scene_; }


	private:
		void menuInfoText(QString texte, int xPos, int yPos, int taille, bool bold);
		void menuInfoCase(int xPos, int yPos, int xSize, int ySize, QColor couleur);


		QGraphicsScene* scene_;
		QGraphicsView* window_;
		
		std::unique_ptr<Modele::Plateau> plateau_;

		QGraphicsTextItem* quiDoitJouer;
		QMediaPlayer* music_;

	public slots:
		void mettreDansScene(QGraphicsItem* object);
		void mettreTour(std::string equipeQuiJoue);
		void MenuPrincipal(std::string textePrincipal = "Echec de Fou");
		void menuInfo();
		void retour();
		void jouerSon(QString cheminVersSon);

	};
}