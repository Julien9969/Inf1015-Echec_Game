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

	virtual void hoverEnterEvent(QGraphicsSceneHoverEvent* event);
	virtual void hoverLeaveEvent(QGraphicsSceneHoverEvent* event);



private:
	QBrush brush;
	QColor color_;

};

