#pragma once
//#include "jeu.h"
#include <QObject>
#include <QGraphicsRectItem>
#include <QGraphicsSceneMouseEvent>
#include <QBrush>
#include <QCursor>

//#include <QEvent>


namespace model { class ModelPieceEchec; };

namespace Ui {

	class Case : public QObject, public QGraphicsRectItem
	{
		Q_OBJECT

	public:
		Case(qreal x, qreal y, qreal width, qreal height, QGraphicsItem* parent = NULL);
		~Case() = default;

		void mettreCouleurbase(QColor couleur);

		void mettreCouleur(QColor couleur);
		void mettreCouleur();

		void mettreCoordonnees(int i, int j);

		void mettrePiece(model::ModelPieceEchec* piece);
		void enleverPiece() { piece_ = nullptr; }

		const model::ModelPieceEchec* getPiece() const { return piece_; }

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

		model::ModelPieceEchec* piece_ = nullptr;
		QBrush brush;
		QColor couleurDeBase_;
		QColor couleurActuelle;

	signals:
		void caseClique(Case* caseClique);
		

	};

	struct ListeCases {
		std::vector<Case*> listeCases;

		Case* operator[](int x) {
			return listeCases[x];
		}

		Case* operator()(int x, int y) {
			return listeCases[x * 8 + y];
		}

		void push_back(Case* box) {
			listeCases.push_back(box);
		}

		auto begin() { return listeCases.begin(); }
		
		auto end() { return listeCases.end(); }
	};

}