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
	positionner(piece->lireMatricePos(), piece->lireScenePos());
	qDebug() << "une piece : " << "equpie marche pas" << " a été mangé.";

	
	music.setMedia(QUrl("Sons/Slash.mp3"));
	music.setVolume(20);
	music.play();

	emit enleverLaPieceDuPlateau(piece);
}


void model::ModelPieceEchec::positionner(const MatricePosition& matricePos, const PixelPosition& scenePos)
{
	mPosition_ = matricePos;
	pPosition_ = scenePos;
	emit mettrePositionVue(scenePos);
}
