#pragma once
#include <QObject>
#include <QMediaPlayer>

#include <list>
#include <string>
#include <QColor>
#include "modelCase.h"
#include "StructSpecial.h"



namespace model {

	struct ListeCases;
	class modelCase;

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

		std::list<model::EmplacementValide>& lirePiecesAlies() { return pieceAutourAlie; }

		const QString& lireCheminImage() const { return cheminImage; }
		void mangeLaPiece(ModelPieceEchec* piece);

		const std::string& lireEquipe() const { return equipe_; }
		std::list<EmplacementValide>& lireEmplacementSemiValide() { return listeEmplacementsValides; }

		void positionner(const MatricePosition& matricePos, const PixelPosition& scenePos);
		
	protected:
		std::string equipe_;
		QString cheminImage;

		QMediaPlayer music;
		MatricePosition mPosition_;
		PixelPosition pPosition_;

		std::list<EmplacementValide> listeEmplacementsValides;
		std::list<model::EmplacementValide> pieceAutourAlie;

	public slots:
		virtual void listerDeplacementsSemiValides(ListeCases& listeCase) = 0;
		virtual bool deplacementEstValide(const MatricePosition& destination) = 0;
	
	signals:   
		void mettrePositionVue(PixelPosition scenePos);
		void suppressionPiece();
		void enleverLaPieceDuPlateau(ModelPieceEchec* piece);
	};
}