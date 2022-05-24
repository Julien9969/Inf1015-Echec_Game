//Corps de la classe Bouton.h

#include "Bouton.h"
#include <QDebug>

Bouton::Bouton(QString name, int xPos, int yPos, int xSize, int ySize, QGraphicsItem* parent) : QGraphicsRectItem(parent) {

    setRect(xPos - xSize / 2, yPos, xSize, ySize);

    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(QColor(54, 69, 137));
    setBrush(brush);

    QFont f;
    f.setPixelSize(35);

    text = new QGraphicsTextItem(name, this);
    text->setFont(f);
    text->setDefaultTextColor(Qt::white);
    
    text->setPos(xPos - text->boundingRect().width() /2 , yPos + (ySize - text->boundingRect().height()) / 2);

    setAcceptHoverEvents(true);
}

void Bouton::mousePressEvent(QGraphicsSceneMouseEvent* event) 
{
    if (event->buttons() == Qt::LeftButton) {
        emit clicked();
    }
}

void Bouton::hoverEnterEvent(QGraphicsSceneHoverEvent* event) 
{
    event->accept();

    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(QColor(148, 148, 148));
    setBrush(brush);
}

void Bouton::hoverLeaveEvent(QGraphicsSceneHoverEvent* event) 
{
    event->accept();

    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(QColor(54, 69, 137));
    setBrush(brush);
}