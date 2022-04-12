#pragma once
#include <QGraphicsPixmapItem>
#include <QGraphicsSceneMouseEvent>
#include <utility>
#include <QObject>
#include <list>
#include "case.h"

namespace Ui { 
	class Case;
	struct ListeCases;
};


namespace model {

	struct CaseValide {
		int ligne;
		int colone;
		QColor couleur;
	};

	class PieceEchec : public QObject, public QGraphicsPixmapItem
	{
		Q_OBJECT
	public:
		PieceEchec(QString equipe, QGraphicsItem* parent = NULL);
		virtual ~PieceEchec() = default;

		void mousePressEvent(QGraphicsSceneMouseEvent* event);
		virtual void hoverEnterEvent(QGraphicsSceneHoverEvent* event);
		//void mouseMoveEvent(QGraphicsSceneMouseEvent* event);

		int lireX() const { return ligne_; }
		int lireY() const { return colone_; }
		std::pair<int, int> matricePos() const { return { ligne_, colone_ }; }

		QString lireEquipe() const { return equipe_; }
		std::list<CaseValide>& lireEmplacementValide() { return emplacementsValides; }

		void estDeClique() { pieceDuJeuEstClique = false; }

		virtual void ajouterImage() = 0;
		
		void mangeLaPiece(PieceEchec* piece);

		virtual std::list<CaseValide>& listerDeplacementsValides(Ui::ListeCases& ListeCase) = 0;
		virtual bool deplacementEstValide(const std::pair<int, int>& destination) = 0;

		void positionnerPiece(std::pair<int, int> matricePos, std::pair<int, int> pos);
		

	protected:
		QString equipe_;
		int ligne_ = 0;
		int colone_ = 0;
		std::pair<int, int> ScenePos_;


		bool pieceDuJeuEstClique;

		std::list<CaseValide> emplacementsValides;

	signals:
		void pieceClique(PieceEchec* pieceClique);

	};
}
