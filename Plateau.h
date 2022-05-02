#pragma once
#include "jeu.h"
#include "ModelCase.h"
#include "ModelPieceEchec.h"
#include "Tour.h" 
#include "Roi.h"
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <cppitertools/range.hpp>
#include <vector>
#include <list>
#include <memory>
#include "PieceEchec.h"
#include <QObject>

//pas sur utile
//#include "case.h"


//namespace Ui {
//	class InterfaceJeu;
//	//class Case;
//	//struct ListeCases;
//};

//namespace model { 
//	//struct CaseValide;
//	//class PieceEchec;
//};



class Plateau : public QObject
{
	Q_OBJECT
public:
	Plateau(/*Ui::InterfaceJeu* jeu*/);
	~Plateau() = default;

	void creeCases();
	void creePiecesNoir();
	void creePieceBlanc();
	void mettreLesPieces();

	void couleurSurCaseValide(std::list<model::EmplacementValide> listeEmplacements);
	void couleurPlateauInitial();

	std::vector<std::unique_ptr<model::ModelPieceEchec>> ListePieceNoir;
	std::vector<std::unique_ptr<model::ModelPieceEchec>> ListePieceBlanc;


	model::ListeCases listeCases;

	//void mouseMoveEvent(QGraphicsSceneMouseEvent* event);


private:
	
	model::ModelPieceEchec* pieceActuelle_;

signals:
	//mettre

public slots:
	void recevoirPieceClique(Ui::VuePieceEchec* piece);
	void recevoirCaseClique(model::ModelCase* caseClique);
	void enleverPieceElimine(model::ModelPieceEchec* piece);

};
