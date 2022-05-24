/*
* Classe implémentant la logique du jeu d'echec
* s'occupe de mettre en place le jeu et fait les vérifications d'échec
*
* Fichier : Plateau.h, Plateau.cpp
* Auteurs : Sebastian Espin, Julien Roux
* Date : 05/05/2022
* Crée : 28/04/2022
*/

#pragma once
#include <cppitertools/range.hpp>
#include <vector>
#include <memory>
#include <algorithm>
#include <functional>
#include "ModeleCase.h"
#include "ModelePieceEchec.h"
#include "Tour.h" 
#include "Roi.h"
#include "Fou.h"
#include "Pion.h"
#include "Reine.h"
#include "Cavalier.h"


namespace Modele {

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
		void listerDeplacementsValide(ModelePieceEchec* pieceActuelle);
		bool deplacementMetEnEchec(ModelePieceEchec* roi ,const MatricePosition& positionRoiModifie);
		bool roiEnEchec(ModelePieceEchec* piece, const MatricePosition& positionRoiModifie);

		void echecEtMat(std::string equipeQuiVientDeJouer);

		std::vector<std::unique_ptr<ModelePieceEchec>> ListePieceNoir;
		std::vector<std::unique_ptr<ModelePieceEchec>> ListePieceBlanc;


		Modele::ListeCases listeCases;

	private:

		ModelePieceEchec* pieceActuelle_;
		TourDeJeu tourDeJeu;

	signals:
		void changementTour(std::string equipe);
		void MenuPrincipal(std::string gagnant);

	public slots:
		void recevoirPieceClique(ModelePieceEchec* pieceClique);
		void recevoirCaseClique(ModeleCase* caseClique);
		void enleverPieceElimine(ModelePieceEchec* piece);

	};

}