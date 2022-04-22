#include "PieceEchec.h"
#include "QDebug"

using Ui::VuePieceEchec;

VuePieceEchec::VuePieceEchec(model::ModelPieceEchec* piece, QGraphicsItem* parent) : QGraphicsPixmapItem(parent)
{
	pieceAssocie_ = piece;
    //setAcceptDrops(true);
	QObject::connect(piece, &model::ModelPieceEchec::mettrePositionVue, this, &Ui::VuePieceEchec::positionnerPiece);
	QObject::connect(piece, &model::ModelPieceEchec::suppressionPiece, this, &Ui::VuePieceEchec::laPieceEstElimine);


	setPixmap(QPixmap(pieceAssocie_->lireCheminImage()));
	//setFlags(QGraphicsItem::ItemIsSelectable | QGraphicsItem::ItemIsMovable);
	setAcceptHoverEvents(true);

	setScale(1.4);
}



void VuePieceEchec::positionnerPiece(std::pair<int, int> scenePos)
{
	//qDebug() << scenePos.first;
	
	pieceAssocie_->scenePos() = scenePos;

	setPos(scenePos.first, scenePos.second);
}


//RAII
VuePieceEchec::~VuePieceEchec() {
	emit enleverLaPiece(pieceAssocie_);
	pieceAssocie_ = nullptr;
}

void Ui::VuePieceEchec::laPieceEstElimine()
{
	//pieceAssocie_->~ModelPieceEchec();
	/*this->~VuePieceEchec();*/
	delete this;
}


void VuePieceEchec::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
	if (event->buttons() == Qt::LeftButton)
	{
		qDebug() << "clique" << pieceAssocie_->lireX() << pieceAssocie_->lireY();
		emit pieceClique(this);
	}
}

void VuePieceEchec::hoverEnterEvent(QGraphicsSceneHoverEvent* event)
{
	//qDebug() << pieceDuJeuEstClique;
	//this->~VuePieceEchec();
}


//void PieceEchec::mouseMoveEvent(QGraphicsSceneMouseEvent* event) {
//	// if there is a cardToPlace, then make it follow the mouse
//	if (estClique) {
//		setPos(event->scenePos().x() - 45, event->scenePos().y() - 45);
//		qDebug() << "piece move" << event->pos();
//
//	}
//
//	qDebug() << "move";
//	QGraphicsPixmapItem::mouseMoveEvent(event);
//}







