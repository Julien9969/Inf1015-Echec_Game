//Corps de la classe ModeleCase
#include "ModeleCase.h"

Modele::ModeleCase::ModeleCase(int ligne, int colonne)
{
	mPosition.ligne = ligne;
	mPosition.colonne = colonne;

}


void Modele::ModeleCase::mettrePiece(ModelePieceEchec* piece){
	piece_ = piece;
}

void Modele::ModeleCase::enleverPiece() {
	 piece_ = nullptr;
}

Modele::ModeleCase::~ModeleCase()
{
}


