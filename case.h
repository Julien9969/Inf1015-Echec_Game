#pragma once
#include "jeu.h"
#include <QGraphicsRectItem>
#include <QPointer>


class Case : public QGraphicsRectItem
{
public:
	Case(qreal x, qreal y, qreal width, qreal height, QGraphicsItem* parent = nullptr);
	~Case();

	void mettreCouleur(Qt::GlobalColor couleur);


private:
	QBrush brush;
};

