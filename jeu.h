#pragma once
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QGraphicsTextItem>
#include "case.h"
#include <QPointer>
#include <cppitertools/range.hpp>
#include <vector>



class Jeu : public QGraphicsView
{
	Q_OBJECT

public:
	Jeu(QWidget* parent = nullptr);

	/*~Jeu() {
		for (auto&& i : ListeCase)
			delete i;
	}*/

	void debutPartie();
	void creationDesBord(int taille, int x, int y, QColor couleur, double opacite);

	void creationPlateau();

	void image();

	QPointer<QGraphicsScene> scene;
	std::vector<QGraphicsRectItem*> ListeCase;

private:

	QPointer<QGraphicsTextItem> quiDoitJouer;



};

