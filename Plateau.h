#pragma once
#include "jeu.h"
#include "case.h"
#include "Tour.h" 
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <cppitertools/range.hpp>
#include <vector>
//#include "PieceEchec.h"
#include <QObject>

namespace Ui {
	class Jeu;
	class Case;
};

namespace { class PieceEchec; };

class Plateau : public QObject
{
	Q_OBJECT
public:
	Plateau(Ui::Jeu* jeu);
	~Plateau();

	void creeCases();

	void creePiecesNoir();
	void mettreLesPieces();

	void ajouterDansScene(QGraphicsItem* item);

	std::vector<model::PieceEchec*> ListePieceNoir;
	std::vector<model::PieceEchec*> ListePieceBlanc;


	std::vector<Ui::Case*> ListeCase;



private:
	Ui::Jeu* ptrJeu_;
	model::PieceEchec* pieceActuelle_;

public slots:
	void enregistrerPieceClique(model::PieceEchec* piece);
	void recevoirCaseClique(Ui::Case* caseClique);

};
