#include "Bouton.h"
#include <QDebug>

Bouton::Bouton(QString name, int xPos, int yPos, QGraphicsItem* parent) : QGraphicsRectItem(parent) {

    setRect(xPos - 250 / 2, yPos + 80, 250, 80);

    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(QColor(54, 69, 137));
    setBrush(brush);

    text = new QGraphicsTextItem(name, this);
    QFont f;
    f.setPixelSize(35);
    //f.setBold(true);
    text->setFont(f);
    text->setDefaultTextColor(Qt::white);
    
    qDebug() << text->boundingRect().width();
    text->setPos(xPos - text->boundingRect().width() /2 , yPos + 80 + text->boundingRect().height()/4 /*+ 80*/);

    setAcceptHoverEvents(true);
}

void Bouton::mousePressEvent(QGraphicsSceneMouseEvent* event) {
    emit clicked();
}

void Bouton::hoverEnterEvent(QGraphicsSceneHoverEvent* event) {

    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(Qt::lightGray);
    setBrush(brush);
}

void Bouton::hoverLeaveEvent(QGraphicsSceneHoverEvent* event) {

    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(QColor(54, 69, 137));
    setBrush(brush);
}