#pragma once
#include "jeu.h"
#include "case.h"
#include "Tour.h" 
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <cppitertools/range.hpp>
#include <vector>
#include <list>
//#include "PieceEchec.h"
#include <QObject>

namespace Ui {
	class Jeu;
	//class Case;
	//struct ListeCases;
};

namespace model { 
	//struct CaseValide;
	//class PieceEchec;
};



class Plateau : public QObject
{
	Q_OBJECT
public:
	Plateau(Ui::Jeu* jeu);
	~Plateau();

	void creeCases();

	void creePiecesNoir();
	void creePieceBlanc();
	void mettreLesPieces();

	void ajouterDansScene(QGraphicsItem* item);

	void couleurSurCaseValide(std::list<model::CaseValide> listeEmplacements);
	void couleurPlateauInitial();

	std::vector<model::PieceEchec*> ListePieceNoir;
	std::vector<model::PieceEchec*> ListePieceBlanc;


	Ui::ListeCases listeCases;

	void mouseMoveEvent(QGraphicsSceneMouseEvent* event);


private:
	Ui::Jeu* ptrJeu_;
	model::PieceEchec* pieceActuelle_;

public slots:
	void recevoirPieceClique(model::PieceEchec* piece);
	void recevoirCaseClique(Ui::Case* caseClique);

};
