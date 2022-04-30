#include "ModelPieceEchec.h"
#include "QDebug"

using model::ModelPieceEchec;


ModelPieceEchec::ModelPieceEchec(std::string equipe)
{
	equipe_ = equipe;
}

model::ModelPieceEchec::~ModelPieceEchec()
{
	emit suppressionPiece();
}


//On repositionne la piece qui mange puis on enleve la piece du plateau
void ModelPieceEchec::mangeLaPiece(ModelPieceEchec* piece) {
	positionner(piece->matricePos(), piece->ScenePos_);
	qDebug() << "une piece : " << "equpie marche pas" << " a été mangé.";

	emit enleverLaPieceDuPlateau(piece);
}


void model::ModelPieceEchec::positionner(std::pair<int, int> matricePos, std::pair<int, int> scenePos)
{
	ligne_ = matricePos.first;
	colone_ = matricePos.second;
	emit mettrePositionVue(scenePos);
}
