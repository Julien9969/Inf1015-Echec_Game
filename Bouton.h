#pragma once
#include <QGraphicsRectItem>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsTextItem>
#include <QBrush>
#include <QFont>

class Bouton :public QObject, public QGraphicsRectItem {
    Q_OBJECT
public:
    
    Bouton(QString name, int xPox, int yPos, QGraphicsItem* parent = NULL);

    void mousePressEvent(QGraphicsSceneMouseEvent* event);
    void hoverEnterEvent(QGraphicsSceneHoverEvent* event);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent* event);
signals:
    void clicked();
private:
    QGraphicsTextItem* text;
};
