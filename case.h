#pragma once
//#include "jeu.h"
#include <QObject>
#include <QGraphicsRectItem>
#include <QGraphicsSceneMouseEvent>
#include <QBrush>

//#include <QEvent>


namespace model { class PieceEchec; };

namespace Ui {

	class Case : public QObject, public QGraphicsRectItem
	{
		Q_OBJECT

	public:
		Case(qreal x, qreal y, qreal width, qreal height, QGraphicsItem* parent = NULL);
		~Case() = default;

		void mettreCouleur(Qt::GlobalColor couleur);

		void mettreCoordonnees(int i, int j);

		void mettrePiece(model::PieceEchec* piece);
		void enleverPiece() { piece_ = nullptr; }

		const model::PieceEchec* getPiece() const { return piece_; }

		virtual void hoverEnterEvent(QGraphicsSceneHoverEvent* event);
		virtual void hoverLeaveEvent(QGraphicsSceneHoverEvent* event);


		void mousePressEvent(QGraphicsSceneMouseEvent* event);

		void mouseReleaseEvent(QGraphicsSceneMouseEvent* event);


		const std::pair<int, int> lirePixPosition() const;
		const std::pair<int, int> lireMatricePosition() const;



	private:
		int ligne_ = 0;
		int colone_ = 0;

		int xPixPos_;
		int yPixPos_;

		model::PieceEchec* piece_ = nullptr;
		QBrush brush;
		QColor color_;

	signals:
		void caseClique(Case* caseClique);
		

	};

	struct ListeCases {
		std::vector<Case*> listeCase;

		Case* operator()(int x, int y) {
			return listeCase[x * 8 + y];
		}

		void push_back(Case* box) {
			listeCase.push_back(box);
		}
	};

}