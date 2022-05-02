#pragma once
#include <QMainWindow>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsTextItem>
#include <QGraphicsRectItem>
#include <cppitertools/range.hpp>
//#include <vector>
//#include <memory>

#include "case.h"
#include "PieceEchec.h"

#include "Plateau.h"

class Plateau;

namespace Ui {

	class InterfaceJeu : public QMainWindow
	{
		Q_OBJECT

	public:
		InterfaceJeu(QWidget* parent = NULL);

		//~InterfaceJeu() = default;
		~InterfaceJeu() { delete plateau_; };


		void initialisationFenetre();

		void creationElementBord();
		void creationDesBord(int taille, int x, int y, QColor couleur, double opacite);

		void creationVueCases();
		void creationVuePiece();

		QString ab = "bonojour";

	private:

		QGraphicsScene* scene;
		QGraphicsView* window_;
		
		Plateau* plateau_;

		QGraphicsTextItem* quiDoitJouer;

	public slots:
		void mettreDansScene(QGraphicsItem* object);



	};

}