#include "ModelCase.h"

model::ModelCase::ModelCase(int ligne, int colone)
{
	position.ligne = ligne;
	position.colone = colone;

}


void model::ModelCase::mettrePiece(ModelPieceEchec* piece){
	piece_ = piece;
}

void model::ModelCase::enleverPiece() {
	 piece_ = nullptr;
}

model::ModelCase::~ModelCase()
{
}


