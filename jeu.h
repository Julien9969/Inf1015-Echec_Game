#pragma once
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsTextItem>
#include <QGraphicsRectItem>
#include <QMainWindow>
#include <QPointer>
#include <cppitertools/range.hpp>
#include <vector>
#include <memory>
//#include "case.h"
#include "Plateau.h"

class Plateau;

class Jeu : public QMainWindow
{
	Q_OBJECT

public:
	Jeu(QWidget* parent = NULL);

	~Jeu() = default;

	void debutPartie();
	void creationDesBord(int taille, int x, int y, QColor couleur, double opacite);

	void creationPlateau();

	void mettreDansScene(QGraphicsItem* object);

	QGraphicsScene* scene;

	QGraphicsView* window_;

	QString ab = "bonojour";

	std::unique_ptr<Plateau> plateau_;

private:

	QPointer<QGraphicsTextItem> quiDoitJouer;



};

