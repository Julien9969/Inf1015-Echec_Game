#pragma once
#include <QGraphicsPixmapItem>
#include <QGraphicsSceneMouseEvent>
#include <utility>
#include <QObject>
#include <list>
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
		//~VuePieceEchec() = default;
		~VuePieceEchec();



		void mousePressEvent(QGraphicsSceneMouseEvent* event);
		virtual void hoverEnterEvent(QGraphicsSceneHoverEvent* event);
		//void mouseMoveEvent(QGraphicsSceneMouseEvent* event);

		/*int lireX() const { return ligne_; }
		int lireY() const { return colone_; }*/
		model::ModelPieceEchec* lirePiece() { return pieceAssocie_; }
		
		//void mangeLaPiece(VuePieceEchec* piece);

		/*virtual std::list<CaseValide>& listerDeplacementsValides(Ui::ListeCases& ListeCase) = 0;
		virtual bool deplacementEstValide(const std::pair<int, int>& destination) = 0;*/

	
	private:

		model::ModelPieceEchec* pieceAssocie_;


	public slots:
		//void recevoirImagePiece();
		void positionnerPiece(std::pair<int, int> pos);
		void laPieceEstElimine();

	signals:
		void pieceClique(VuePieceEchec* pieceClique);
		void enleverLaPiece(model::ModelPieceEchec* pieceAssocie_);

	};
}


