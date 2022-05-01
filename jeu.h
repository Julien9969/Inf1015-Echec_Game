#pragma once
#include <QMainWindow>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsTextItem>
#include <QGraphicsRectItem>
#include <cppitertools/range.hpp>
#include <vector>
#include <memory>

//#include "case.h"
#include "Plateau.h"

class Plateau;
namespace Ui {

	class InterfaceJeu : public QMainWindow
	{
		Q_OBJECT

	public:
		InterfaceJeu(QWidget* parent = NULL);

		~InterfaceJeu() { delete plateau; };

		void creationElementBord();
		void creationDesBord(int taille, int x, int y, QColor couleur, double opacite);
		void initialisationFenetre();


		QString ab = "bonojour";

	private:

		QGraphicsScene* scene;
		QGraphicsView* window_;
		
		Plateau* plateau;

		QGraphicsTextItem* quiDoitJouer;

	public slots:
		void mettreDansScene(QGraphicsItem* object);



	};

}