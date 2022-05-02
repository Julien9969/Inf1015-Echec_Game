#pragma once
#include <QObject>
#include <list>
//#include <vector>
#include <utility>
#include <string>
#include <QColor>
#include "modelCase.h"
#include "StructSpecial.h"

//namespace Ui { 
//	class Case

//namespace Ui {;
////	struct ListeCases;
////};
//	class Case;
//	struct ListeCases;
//};

namespace model {

	//class ModelCase;
	struct ListeCases;

	struct EmplacementValide {
		int ligne;
		int colone;
		QColor couleur;
	};

	class ModelPieceEchec : public QObject
	{
		Q_OBJECT
	public:
		ModelPieceEchec(std::string equipe);
		//virtual ~ModelPieceEchec() = default;
		virtual ~ModelPieceEchec();

		const MatricePosition& lireMatricePos() const { return mPosition_; }

		const PixelPosition& lireScenePos() const { return pPosition_; }


		const QString& lireCheminImage() const { return cheminImage; }
		void mangeLaPiece(ModelPieceEchec* piece);

		const std::string& lireEquipe() const { return equipe_; }
		std::list<EmplacementValide>& lireEmplacementValide() { return listeEmplacementsValides; }

		void positionner(MatricePosition matricePos, PixelPosition scenePos);
		
	protected:
		std::string equipe_;
		QString cheminImage;

		//std::pair<int, int> ScenePos_;

		MatricePosition mPosition_;
		PixelPosition pPosition_;

		std::list<EmplacementValide> listeEmplacementsValides;

	public slots:
		virtual std::list<EmplacementValide>& listerDeplacementsValides(ListeCases& listeCase) = 0;
		virtual bool deplacementEstValide(const MatricePosition& destination) = 0;
	
	signals:   
		void mettrePositionVue(PixelPosition scenePos);
		void suppressionPiece();
		void enleverLaPieceDuPlateau(ModelPieceEchec* piece);
	};
}