#pragma once
#include "jeu.h"
#include <QGraphicsRectItem>
#include <QPointer>

class PieceEchec;
class Case : public QGraphicsRectItem
{
	Q_GADGET
public:
	Case(qreal x, qreal y, qreal width, qreal height, QGraphicsItem* parent = nullptr);
	//~Case() ;

	void mettreCouleur(Qt::GlobalColor couleur);

	void mettreEmplacement(int i, int j);

	void mettrePiece(PieceEchec* piece);

	virtual void hoverEnterEvent(QGraphicsSceneHoverEvent* event = 0);
	virtual void hoverLeaveEvent(QGraphicsSceneHoverEvent* event = 0);

	const std::pair<int, int> lirePosition() const;



private:
	int ligne_ = 0;
	int colone_ = 0;

	PieceEchec* piece_;
	QBrush brush;
	QColor color_;

	int xPos_;
	int yPos_;

};

