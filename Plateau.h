#pragma once
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QGraphicsTextItem>
#include "case.h"
#include <QPointer>
#include <cppitertools/range.hpp>
#include <vector>
#include "jeu.h"
//#include "PieceEchec.h"
#include "Tour.h" 

class Jeu;
class Case;
class PieceEchec;

class Plateau 
{
public:
	Plateau(Jeu* jeu);
	~Plateau();

	void creeCases();

	void creePiecesNoir();
	void mettreLesPieces();

	void ajouterDansScene(QGraphicsItem* item);

	std::vector<PieceEchec*> ListePieceNoir;
	std::vector<QGraphicsPixmapItem*> ListePieceBlanc;


	std::vector<Case*> ListeCase;

private:
	Jeu* ptrJeu_;
};
