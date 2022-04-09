#pragma once
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsTextItem>
#include <QGraphicsRectItem>
#include <QMainWindow>
#include <cppitertools/range.hpp>
#include <vector>
//#include "case.h"


namespace Ui {

	class Jeu : public QMainWindow
	{
		Q_OBJECT

	public:
		Jeu(QWidget* parent = NULL);

		~Jeu() = default;

		void debutPartie();
		void creationDesBord(int taille, int x, int y, QColor couleur, double opacite);

		void mettreDansScene(QGraphicsItem* object);

		QGraphicsScene* scene;

		QGraphicsView* window_;

		QString ab = "bonojour";

	private:

		QGraphicsTextItem* quiDoitJouer;



	};

}