#include "ModelPieceEchec.h"
#include "QDebug"

using model::ModelPieceEchec;


ModelPieceEchec::ModelPieceEchec(std::string equipe)
{
	equipe_ = equipe;
}

void model::ModelPieceEchec::PieceElimine()
{
	emit suppressionPiece();

	qDebug() << "on est de retour";
}

//On repositionne la piece qui mange puis on enleve l'ancienne piece
void ModelPieceEchec::mangeLaPiece(ModelPieceEchec* piece) {
	positionner(piece->matricePos(), piece->ScenePos_);
	qDebug() << "une piece : " << "equpie marche pas" << " a été mangé.";

	piece->PieceElimine();
}


void model::ModelPieceEchec::positionner(std::pair<int, int> matricePos, std::pair<int, int> scenePos)
{
	ligne_ = matricePos.first;
	colone_ = matricePos.second;
	emit mettrePositionVue(scenePos);
}
