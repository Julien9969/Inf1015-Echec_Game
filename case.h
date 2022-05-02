#pragma once
//#include "jeu.h"
#include <QObject>
#include <QGraphicsRectItem>
#include <QGraphicsSceneMouseEvent>
#include <QBrush>
#include <QCursor>

#include "ModelCase.h"

//#include <QEvent>


namespace Ui {

	class Case : public QObject, public QGraphicsRectItem
	{
		Q_OBJECT

	public:
		Case(qreal x, qreal y, qreal width, qreal height, model::ModelCase* caseAssocie, QGraphicsItem* parent = NULL);
		~Case() = default;

		void mettreCouleurbase(QColor couleur);


		void mettreCoordonnees(int i, int j);

	
		virtual void hoverEnterEvent(QGraphicsSceneHoverEvent* event);
		virtual void hoverLeaveEvent(QGraphicsSceneHoverEvent* event);


		void mousePressEvent(QGraphicsSceneMouseEvent* event);

		void mouseReleaseEvent(QGraphicsSceneMouseEvent* event);


		//const std::pair<int, int> lireMatricePosition() const;

	private:
		int ligne_, colone_;

		model::ModelCase* caseAssocie_;

		QBrush brush;
		QColor couleurDeBase_;
		QColor couleurActuelle;

	public slots:
		void mettreCouleur(QColor couleur);
		void mettreCouleurBase();

	signals:
		void caseClique(model::ModelCase* caseClique);
		

	};

}