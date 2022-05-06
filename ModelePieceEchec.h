/*
* Classe abstraite implémentant la logique de base d'une piece d'échec.
*
* Fichier : ModelePieceEchec.h, ModelePieceEchec.cpp
* Auteurs : Sebastian Espin, Julien Roux
* Date : 05/05/2022
* Crée : 01/04/2022
*/

#pragma once
#pragma warning(disable:5054)
#include <QObject>
#include <QColor>
#pragma warning(default:5054)

#include <string>
#include <list>
#include "ModeleCase.h"
#include "StructSpecial.h"

#define HAUT 0
#define BAS 7
#define GAUCHE 0
#define DROITE 7


namespace Modele {

	struct ListeCases;
	class ModeleCase;

	struct EmplacementValide {
		int ligne;
		int colonne;
		QColor couleur;
	};

	class ModelePieceEchec : public QObject
	{
		Q_OBJECT
	public:
		ModelePieceEchec(std::string equipe);
		virtual ~ModelePieceEchec();

		const MatricePosition& lireMatricePos() const { return mPosition_; }

		const PixelPosition& lireScenePos() const { return pPosition_; }


		const QString& lireCheminImage() const { return cheminImage; }
		void mangeLaPiece(ModelePieceEchec* piece);

		const std::string& lireEquipe() const { return equipe_; }
		std::list<EmplacementValide>& lireEmplacementValide() { return listeEmplacementsValides; }
		bool listEmplacementEstVide() { return listeEmplacementsValides.empty(); }

		void positionner(const MatricePosition& matricePos, const PixelPosition& scenePos);

		bool neDepassePas(int position, int bord) { return position >= bord; }
		bool depasse(int position, int bord) { return position <= bord; }

	protected:
		std::string equipe_;
		QString cheminImage;

		MatricePosition mPosition_;
		PixelPosition pPosition_;

		std::list<EmplacementValide> listeEmplacementsValides;

	public slots:
		virtual void listerDeplacementsSemiValides(ListeCases& listeCase) = 0;
		virtual bool deplacementEstValide(const MatricePosition& destination) = 0;
	
	signals:   
		void mettrePositionVue(PixelPosition scenePos);
		void suppressionPiece();
		void enleverLaPieceDuPlateau(ModelePieceEchec* piece);
	};
}