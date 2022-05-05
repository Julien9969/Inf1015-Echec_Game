#pragma once
#include <QMainWindow>
#include <QCoreApplication>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsTextItem>
#include <QGraphicsRectItem>
#include <cppitertools/range.hpp>

#include "Bouton.h"
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

		~InterfaceJeu() = default;

		void initialisationFenetre();

		void nouvellePartie();

		void creationElementBord();
		void creationDesBord(int taille, int x, int y, QColor couleur, double opacite);

		void creationVueCases();
		void creationVuePiece();

		model::Plateau* plateau() const { return plateau_.get(); }
		QGraphicsScene* scene() const { return scene_; }

	private:

		QGraphicsScene* scene_;
		QGraphicsView* window_;
		
		std::unique_ptr<model::Plateau> plateau_;

		QGraphicsTextItem* quiDoitJouer;

	public slots:
		void mettreDansScene(QGraphicsItem* object);
		void mettreTour(std::string equipeQuiJoue);
		void MenuPrincipal(std::string textePrincipal = "Echec de Fou");
	};
}