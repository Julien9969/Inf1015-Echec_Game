#pragma once
#include "jeu.h"
#include "case.h"
#include "PieceEchec.h"
#include "Tour.h" 
#include "Roi.h"
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <cppitertools/range.hpp>
#include <vector>
#include <list>
#include <memory>
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
	~Plateau() = default;

	void creeCases();
	void creePiecesNoir();
	void creePieceBlanc();
	void mettreLesPieces();

	void ajouterDansScene(QGraphicsItem* item);

	void couleurSurCaseValide(std::list<model::EmplacementValide> listeEmplacements);
	void couleurPlateauInitial();

	std::vector<std::unique_ptr<model::ModelPieceEchec>> ListePieceNoir;
	std::vector<std::unique_ptr<model::ModelPieceEchec>> ListePieceBlanc;

	//std::vector <Ui::VuePieceEchec*> tempsPiecelist;

	Ui::ListeCases listeCases;

	//void mouseMoveEvent(QGraphicsSceneMouseEvent* event);


private:
	Ui::Jeu* ptrJeu_;
	model::ModelPieceEchec* pieceActuelle_;

public slots:
	void recevoirPieceClique(Ui::VuePieceEchec* piece);
	void recevoirCaseClique(Ui::Case* caseClique);
	void enleverPieceElimine(model::ModelPieceEchec* piece);

};
