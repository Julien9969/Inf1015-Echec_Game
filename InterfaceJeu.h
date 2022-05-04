#pragma once
#include <QMainWindow>
#include <QCoreApplication>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsTextItem>
#include <QGraphicsRectItem>
#include <QPushButton>
#include "Bouton.h"
#include <cppitertools/range.hpp>


#include "VueCase.h"
#include "VuePieceEchec.h"
#include "Plateau.h"

namespace model {
	class Plateau;
}

namespace Ui {

	class InterfaceJeu : public QMainWindow
	{
		Q_OBJECT

	public:
		InterfaceJeu(QWidget* parent = NULL);

		//~InterfaceJeu() = default;
		~InterfaceJeu() {
			/*delete scene; delete window_;*/
		};


		void initialisationFenetre();

		void nouvellePartie();

		void creationElementBord();
		void creationDesBord(int taille, int x, int y, QColor couleur, double opacite);

		void creationVueCases();
		void creationVuePiece();

	private:

		QGraphicsScene* scene;
		QGraphicsView* window_;
		
		std::unique_ptr<model::Plateau> plateau_;

		QGraphicsTextItem* quiDoitJouer;

	public slots:
		void mettreDansScene(QGraphicsItem* object);
		void mettreTour(std::string equipeQuiJoue);
		void MenuPrincipal(std::string gagnant = "");


	};

}