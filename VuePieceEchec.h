#pragma once
#include <QGraphicsPixmapItem>
#include <QGraphicsSceneMouseEvent>
#include <QObject>
#include <QCursor>
#include "ModelPieceEchec.h"



namespace Ui {

	class VuePieceEchec : public QObject, public QGraphicsPixmapItem
	{
		Q_OBJECT
	public:
		VuePieceEchec(model::ModelPieceEchec* piece, QGraphicsItem* parent = NULL);
		~VuePieceEchec() = default;
		
		model::ModelPieceEchec* lirePiece() { return pieceAssocie_; }

	private:

		model::ModelPieceEchec* pieceAssocie_;

	public slots:
		void mousePressEvent(QGraphicsSceneMouseEvent* event);
		void hoverEnterEvent(QGraphicsSceneHoverEvent* event);
		void positionnerPiece(PixelPosition scenePosition);

	signals:
		void pieceClique(model::ModelPieceEchec* pieceClique);

	};
}


