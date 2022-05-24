/*
* Classe permettant la création d'un boutton cliquable
*
* Fichier : Bouton.h, Bouton.cpp
* Auteurs : Sebastian Espin, Julien Roux
* Date : 05/05/2022
* Crée : 04/05/2022
*/

#pragma once
#pragma warning(disable:5054)
#include <QGraphicsRectItem>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsTextItem>
#include <QBrush>
#include <QFont>
#pragma warning(default:5054)


class Bouton :public QObject, public QGraphicsRectItem {
    Q_OBJECT
public:
    
    Bouton(QString name, int xPox, int yPos, int xSize = 250, int ySize = 80, QGraphicsItem* parent = NULL);

    void mousePressEvent(QGraphicsSceneMouseEvent* event);
    void hoverEnterEvent(QGraphicsSceneHoverEvent* event);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent* event);

private:
    QGraphicsTextItem* text;

signals:
    void clicked();
};
