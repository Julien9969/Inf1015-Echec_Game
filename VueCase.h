/*
* Représentation graphique d'une case, cette case peut être cliqué et changer de couleur
*
* Fichier : VueCase.h, VueCase.cpp
* Auteurs : Sebastian Espin, Julien Roux
* Date : 05/05/2022
* Crée : 25/04/2022
*/

#pragma once
#pragma warning(disable:5054)
#include <QObject>
#include <QGraphicsRectItem>
#include <QGraphicsSceneMouseEvent>
#include <QBrush>
#include <QCursor>
#pragma warning(default:5054)

#include "ModeleCase.h"

namespace Ui {

	class VueCase : public QObject, public QGraphicsRectItem
	{
		Q_OBJECT

	public:
		VueCase(qreal x, qreal y, qreal width, qreal height, Modele::ModeleCase* caseAssocie, QGraphicsItem* parent = NULL);
		~VueCase() = default;

		void mettreCouleurbase(QColor couleur);

		void mettreCoordonnees(int i, int j);
	
		virtual void hoverEnterEvent(QGraphicsSceneHoverEvent* event);
		virtual void hoverLeaveEvent(QGraphicsSceneHoverEvent* event);

		void mousePressEvent(QGraphicsSceneMouseEvent* event);

	private:
		int ligne_, colonne_;

		Modele::ModeleCase* caseAssocie_;

		QBrush brush;
		QColor couleurDeBase_;
		QColor couleurActuelle;

	public slots:
		void mettreCouleur(QColor couleur);
		void mettreCouleurBase();

	signals:
		void caseClique(Modele::ModeleCase* caseClique);
	};
}