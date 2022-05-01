#pragma once
#include <QGraphicsPixmapItem>
#include <QGraphicsSceneMouseEvent>
#include <utility>
#include <QObject>
#include <QCursor>
#include "ModelPieceEchec.h"
//#include "case.h"
//
//namespace Ui { 
//	class Case;
//	struct ListeCases;
//};


namespace Ui {

	class VuePieceEchec : public QObject, public QGraphicsPixmapItem
	{
		Q_OBJECT
	public:
		VuePieceEchec(model::ModelPieceEchec* piece, QGraphicsItem* parent = NULL);
		~VuePieceEchec() = default;


		void mousePressEvent(QGraphicsSceneMouseEvent* event);
		virtual void hoverEnterEvent(QGraphicsSceneHoverEvent* event);
		//void mouseMoveEvent(QGraphicsSceneMouseEvent* event);

		
		model::ModelPieceEchec* lirePiece() { return pieceAssocie_; }

	
	private:

		model::ModelPieceEchec* pieceAssocie_;


	public slots:
		//void recevoirImagePiece();
		void positionnerPiece(std::pair<int, int> pos);

	signals:
		void pieceClique(VuePieceEchec* pieceClique);

	};
}


