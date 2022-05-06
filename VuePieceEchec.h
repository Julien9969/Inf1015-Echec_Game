/*
* Représentation graphique d'une pièce d'échec
* Permet de cliqué une piece et de la déplacer
*
* Fichier : VuePieceEchec.h, VuePieceEchec.cpp
* Auteurs : Sebastian Espin, Julien Roux
* Date : 05/05/2022
* Crée : 20/04/2022
*/

#pragma once
#pragma warning(disable:5054)
#include <QGraphicsPixmapItem>
#include <QGraphicsSceneMouseEvent>
#include <QObject>
#include <QCursor>
#pragma warning(default:5054)

#include "ModelePieceEchec.h"

namespace Ui {

	class VuePieceEchec : public QObject, public QGraphicsPixmapItem
	{
		Q_OBJECT
	public:
		VuePieceEchec(Modele::ModelePieceEchec* piece, QGraphicsItem* parent = NULL);
		~VuePieceEchec();
		
		Modele::ModelePieceEchec* lirePiece() { return pieceAssocie_; }

	private:
		Modele::ModelePieceEchec* pieceAssocie_;

	public slots:
		void mousePressEvent(QGraphicsSceneMouseEvent* event);
		void hoverEnterEvent(QGraphicsSceneHoverEvent* event);
		void positionnerPiece(PixelPosition scenePosition);

	signals:
		void pieceClique(Modele::ModelePieceEchec* pieceClique);
		void jouerSon(QString cheminVersSon);
	};
}


