//Corps de la classe ModelePieceEchec
#include "ModelePieceEchec.h"
#include "QDebug"

using Modele::ModelePieceEchec;


ModelePieceEchec::ModelePieceEchec(std::string equipe)
{
	equipe_ = equipe;
}

Modele::ModelePieceEchec::~ModelePieceEchec()
{
	emit suppressionPiece();
}


//On repositionne la piece qui mange puis on enleve la piece du plateau
void ModelePieceEchec::mangeLaPiece(ModelePieceEchec* piece) 
{
	positionner(piece->lireMatricePos(), piece->lireScenePos());
	emit enleverLaPieceDuPlateau(piece);
}


void Modele::ModelePieceEchec::positionner(const MatricePosition& matricePos, const PixelPosition& scenePos)
{
	mPosition_ = matricePos;
	pPosition_ = scenePos;
	emit mettrePositionVue(scenePos);
}
