#pragma once
#include <cppitertools/range.hpp>
#include <vector>
#include <memory>
#include <algorithm>
#include <functional>
//#include "StructSpecial.h"
#include <QObject>
#include "ModelCase.h"
#include "ModelPieceEchec.h"
#include "VuePieceEchec.h"
#include "Tour.h" 
#include "Roi.h"
#include "Fou.h"


namespace model {

	class Plateau : public QObject
	{
		Q_OBJECT
	public:
		Plateau();
		~Plateau() = default;

		void creeCases();
		void creePiecesNoir();
		void creePieceBlanc();
		void mettreLesPieces();

		void couleurSurCaseValide(std::list<EmplacementValide> listeEmplacements);
		void couleurPlateauInitial();

		void tourDeJeuChangement(std::string quiJoue);
		void verificationEchec();

		std::vector<std::unique_ptr<ModelPieceEchec>> ListePieceNoir;
		std::vector<std::unique_ptr<ModelPieceEchec>> ListePieceBlanc;


		model::ListeCases listeCases;

		//void mouseMoveEvent(QGraphicsSceneMouseEvent* event);


	private:

		ModelPieceEchec* pieceActuelle_;
		TourDeJeu tourDeJeu;

	signals:
		void changementTour(std::string equipe);

	public slots:
		void recevoirPieceClique(ModelPieceEchec* pieceClique);
		void recevoirCaseClique(ModelCase* caseClique);
		void enleverPieceElimine(ModelPieceEchec* piece);

	};

}