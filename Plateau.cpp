//Corps de la classe plateau
#include "Plateau.h"
#include <QDebug>

using iter::range;
using Modele::Reine;
using Modele::Tour;
using Modele::Roi;
using Modele::Fou;
using Modele::Pion;
using Modele::ModelePieceEchec;
using Modele::Plateau;
using Modele::Cavalier;

Plateau::Plateau()
{
	creeCases();
	creePiecesNoir();
	creePieceBlanc();
}

void Plateau::creeCases() 
{
	for (int ligne : range(8)) {

		for (int colonne : range(8)) {

			std::unique_ptr<Modele::ModeleCase> uneCase = std::make_unique<Modele::ModeleCase>(ligne, colonne);

			listeCases.push_back(move(uneCase));
		}
	}
}
	

void Plateau::creePiecesNoir()
{
	std::unique_ptr<ModelePieceEchec> tourN = std::make_unique<Tour>("Noir");
	ListePieceNoir.push_back(move(tourN));

	std::unique_ptr<ModelePieceEchec> tourN1 = std::make_unique<Tour>("Noir");
	ListePieceNoir.push_back(move(tourN1));

	std::unique_ptr<ModelePieceEchec> roiN = std::make_unique<Roi>("Noir");
	ListePieceNoir.push_back(move(roiN));

	std::unique_ptr<ModelePieceEchec> fouN = std::make_unique<Fou>("Noir");
	ListePieceNoir.push_back(move(fouN));

	std::unique_ptr<ModelePieceEchec> fouN1 = std::make_unique<Fou>("Noir");
	ListePieceNoir.push_back(move(fouN1));

	std::unique_ptr<ModelePieceEchec> reineN = std::make_unique<Reine>("Noir");
	ListePieceNoir.push_back(move(reineN));

	std::unique_ptr<ModelePieceEchec> cavalierN1 = std::make_unique<Cavalier>("Noir");
	ListePieceNoir.push_back(move(cavalierN1));

	std::unique_ptr<ModelePieceEchec> cavalierN2 = std::make_unique<Cavalier>("Noir");
	ListePieceNoir.push_back(move(cavalierN2));

	for (int i = 0; i < 8; i++)
	{
		std::unique_ptr<ModelePieceEchec> PionN = std::make_unique<Pion>("Noir");
		ListePieceNoir.push_back(move(PionN));
	}

}

void Plateau::creePieceBlanc()
{

	std::unique_ptr<ModelePieceEchec> tourB = std::make_unique<Tour>("Blanc");
	ListePieceBlanc.push_back(move(tourB));

	std::unique_ptr<ModelePieceEchec> tourB1 = std::make_unique<Tour>("Blanc");
	ListePieceBlanc.push_back(move(tourB1));

	std::unique_ptr<ModelePieceEchec> roiB = std::make_unique<Roi>("Blanc");
	ListePieceBlanc.push_back(move(roiB));

	std::unique_ptr<ModelePieceEchec> fouB = std::make_unique<Fou>("Blanc");
	ListePieceBlanc.push_back(move(fouB));

	std::unique_ptr<ModelePieceEchec> fouB1 = std::make_unique<Fou>("Blanc");
	ListePieceBlanc.push_back(move(fouB1));

	std::unique_ptr<ModelePieceEchec> reineB = std::make_unique<Reine>("Blanc");
	ListePieceBlanc.push_back(move(reineB));

	std::unique_ptr<ModelePieceEchec> cavalierB1 = std::make_unique<Cavalier>("Blanc");
	ListePieceBlanc.push_back(move(cavalierB1));

	std::unique_ptr<ModelePieceEchec> cavalierB2 = std::make_unique<Cavalier>("Blanc");
	ListePieceBlanc.push_back(move(cavalierB2));

	try {
		std::unique_ptr<ModelePieceEchec> roiB2 = std::make_unique<Roi>("Blanc");
	}
	catch (std::logic_error& e) {
		qDebug() << "Erreur : " << e.what();
	}

	for (int i = 0; i < 8; i++)
	{
		std::unique_ptr<ModelePieceEchec> PionB = std::make_unique<Pion>("Blanc");
		ListePieceBlanc.push_back(move(PionB));
	}
}

void Plateau::mettreLesPieces()
{
	Modele::ModeleCase* tempCase = nullptr;
	ModelePieceEchec* tempPiece = nullptr;
	int positionPieceN[16] = { 0, 7, 4, 2, 5, 3, 1, 6, 8, 9, 10, 11, 12, 13, 14, 15 };
	int positionPieceB[16] = { 0, 7, 4, 2, 5, 3, 1, 6, -1, -2, -3, -4, -5, -6, -7, -8 };

	int i = 0;

	for (auto&& j = ListePieceNoir.begin(); j != ListePieceNoir.end(); j++) {
			
		tempCase = listeCases[positionPieceN[i++]];
		tempPiece = j->get();

		tempCase->mettrePiece(tempPiece);
		
		tempPiece->ModelePieceEchec::positionner(tempCase->lirePosition(), tempCase->lirePixelPos());
	}

	i = 0;
	
	for (auto&& j = ListePieceBlanc.begin(); j != ListePieceBlanc.end(); j++) {

		tempCase = listeCases[56 + positionPieceB[i++]];
		tempPiece = j->get();

		tempCase->mettrePiece(tempPiece);

		tempPiece->ModelePieceEchec::positionner(tempCase->lirePosition(), tempCase->lirePixelPos());
	}
}



void Plateau::recevoirCaseClique(Modele::ModeleCase* caseClique)
{
	if ((pieceActuelle_ != nullptr) && (caseClique->getPiece() == nullptr) && (pieceActuelle_->deplacementEstValide(caseClique->lirePosition())))
	{
		listeCases(pieceActuelle_->lireMatricePos().ligne, pieceActuelle_->lireMatricePos().colonne)->enleverPiece();

		caseClique->mettrePiece(pieceActuelle_);
		pieceActuelle_->positionner(caseClique->lirePosition(), caseClique->lirePixelPos());

		tourDeJeuChangement(pieceActuelle_->lireEquipe());
		couleurPlateauInitial();

		echecEtMat(pieceActuelle_->lireEquipe());
		pieceActuelle_ = nullptr;

	}
}



void Plateau::recevoirPieceClique(Modele::ModelePieceEchec* pieceClique)
{
	couleurPlateauInitial();

	if ((pieceActuelle_ != nullptr) && (pieceClique->lireEquipe() != pieceActuelle_->lireEquipe())) {
		if (pieceActuelle_->deplacementEstValide(pieceClique->lireMatricePos())) {

			listeCases(pieceActuelle_->lireMatricePos().ligne, pieceActuelle_->lireMatricePos().colonne)->enleverPiece();
			listeCases(pieceClique->lireMatricePos().ligne, pieceClique->lireMatricePos().colonne)->mettrePiece(pieceActuelle_);

			pieceActuelle_->mangeLaPiece(pieceClique);
			tourDeJeuChangement(pieceActuelle_->lireEquipe());
			echecEtMat(pieceActuelle_->lireEquipe());

			pieceActuelle_ = nullptr;
		}
	}
	else if (tourDeJeu == pieceClique->lireEquipe()) {
		pieceActuelle_ = pieceClique;
		listerDeplacementsValide(pieceActuelle_);
		couleurSurCaseValide(pieceActuelle_->lireEmplacementValide());
	}
}

void Plateau::listerDeplacementsValide(ModelePieceEchec* pieceActuelle)
{
	pieceActuelle->listerDeplacementsSemiValides(listeCases);

	std::vector<std::unique_ptr<ModelePieceEchec>>* listePieceAdverse;
	std::vector<std::unique_ptr<ModelePieceEchec>>* listePieceMonEquipe;

	pieceActuelle->lireEquipe() == "Blanc" ? listePieceMonEquipe = &ListePieceBlanc : listePieceMonEquipe = &ListePieceNoir;
	pieceActuelle->lireEquipe() == "Blanc" ? listePieceAdverse = &ListePieceNoir : listePieceAdverse = &ListePieceBlanc;

	std::vector<std::unique_ptr<ModelePieceEchec>>::iterator  monRoi = std::find_if(listePieceMonEquipe->begin(), listePieceMonEquipe->end(),
		[](std::unique_ptr<ModelePieceEchec>& piece) { return dynamic_cast<Roi*>(piece.get()) != 0; });

	for (auto&& piece = listePieceAdverse->begin(); piece != listePieceAdverse->end(); piece++) {

		//On doit protéger le roi si il est en echec avant move
		if (dynamic_cast<Roi*>(pieceActuelle) == 0 && roiEnEchec(piece->get(), monRoi->get()->lireMatricePos()))
		{
			listeCases(monRoi->get()->lireMatricePos().ligne, monRoi->get()->lireMatricePos().colonne)->enleverPiece();

			auto it = std::remove_if(pieceActuelle->lireEmplacementValide().begin(), pieceActuelle->lireEmplacementValide().end(),
				[&](Modele::EmplacementValide& emplacement) {
					if (listeCases(emplacement.ligne, emplacement.colonne)->getPiece() == nullptr) 
					{
						listeCases(emplacement.ligne, emplacement.colonne)->mettrePiece(pieceActuelle);
						bool metEnEchec = roiEnEchec(piece->get(), monRoi->get()->lireMatricePos());
						listeCases(emplacement.ligne, emplacement.colonne)->enleverPiece();
						return metEnEchec;
					}
					else if (listeCases(emplacement.ligne, emplacement.colonne)->getPiece() == piece->get()) {
						return false;
					}
					return true;
				});

			if (it != pieceActuelle->lireEmplacementValide().end()) {
				listeCases(piece->get()->lireMatricePos().ligne, piece->get()->lireMatricePos().colonne)->mettreCouleur(QColor(236, 206, 91));
				pieceActuelle->lireEmplacementValide().erase(it, pieceActuelle->lireEmplacementValide().end());
			}

			listeCases(monRoi->get()->lireMatricePos().ligne, monRoi->get()->lireMatricePos().colonne)->mettrePiece(pieceActuelle);

		}
		//On se met pas nous même en echec
		else {

			if (pieceActuelle != nullptr) {
				listeCases(pieceActuelle->lireMatricePos().ligne, pieceActuelle->lireMatricePos().colonne)->enleverPiece();
			}

			auto it = std::remove_if(pieceActuelle->lireEmplacementValide().begin(), pieceActuelle->lireEmplacementValide().end(),
				[&](EmplacementValide& deplacemet){
					Modele::ModelePieceEchec* tempsPiece = listeCases(deplacemet.ligne, deplacemet.colonne)->getPiece();
					listeCases(deplacemet.ligne, deplacemet.colonne)->mettrePiece(pieceActuelle);

					//si on bouge le roi on envoi sa nouvelle position temporaire
					MatricePosition nouvellePositionTemp;
					dynamic_cast<Roi*>(pieceActuelle) == 0 ? nouvellePositionTemp = monRoi->get()->lireMatricePos() : nouvellePositionTemp = { deplacemet.ligne, deplacemet.colonne };

					if (deplacementMetEnEchec(monRoi->get(), nouvellePositionTemp)) {
						listeCases(deplacemet.ligne, deplacemet.colonne)->mettrePiece(tempsPiece);
						return true;
					}
					else {
						listeCases(deplacemet.ligne, deplacemet.colonne)->mettrePiece(tempsPiece);
						return false;
					}
				});

			if (it != pieceActuelle->lireEmplacementValide().end()) {
				pieceActuelle->lireEmplacementValide().erase(it, pieceActuelle->lireEmplacementValide().end());
			}

			listeCases(pieceActuelle->lireMatricePos().ligne, pieceActuelle->lireMatricePos().colonne)->mettrePiece(pieceActuelle);
		}
	}
}

bool Plateau::deplacementMetEnEchec(/*ModelePieceEchec* pieceAdverse,*/ ModelePieceEchec* roi, const MatricePosition& positionRoiModifie) {

	std::vector<std::unique_ptr<ModelePieceEchec>>* listePieceAdverse;
	roi->lireEquipe() == "Blanc" ? listePieceAdverse = &ListePieceNoir : listePieceAdverse = &ListePieceBlanc;

	for (auto&& piece = listePieceAdverse->begin(); piece != listePieceAdverse->end(); piece++) {
		if (roiEnEchec(piece->get(), positionRoiModifie)) {
			listeCases(piece->get()->lireMatricePos().ligne, piece->get()->lireMatricePos().colonne)->mettreCouleur(QColor(236, 206, 91));
			return true;
			break;
		}
	}
	return false;
}

bool Plateau::roiEnEchec(ModelePieceEchec* piece, const MatricePosition& positionRoi) {

	piece->listerDeplacementsSemiValides(listeCases);

	std::list<Modele::EmplacementValide>::iterator deplacementAtteindRoi = std::find_if(piece->lireEmplacementValide().begin(), piece->lireEmplacementValide().end(),
		[&positionRoi](Modele::EmplacementValide& emplacement)
		{return (emplacement.ligne == positionRoi.ligne) && (emplacement.colonne == positionRoi.colonne); });

	return deplacementAtteindRoi != piece->lireEmplacementValide().end();
}

void Modele::Plateau::echecEtMat(std::string equipeQuiVientDeJouer)
{
	std::vector<std::unique_ptr<ModelePieceEchec>>* listePieceAdverse;
	equipeQuiVientDeJouer == "Blanc" ? listePieceAdverse = &ListePieceNoir : listePieceAdverse = &ListePieceBlanc;

	bool AuMoins1emplacementValide = false;

	for (auto&& piece = listePieceAdverse->begin(); piece != listePieceAdverse->end(); piece++) 
	{
		listerDeplacementsValide(piece->get());

		if (!(piece->get()->listEmplacementEstVide())) {
			AuMoins1emplacementValide = true;
			qDebug() << "le jeu continue";
			break;
		}
	}

	if ((AuMoins1emplacementValide == false))
	{
		emit MenuPrincipal(pieceActuelle_->lireEquipe() + " a gagné");
	}
	else if ((ListePieceBlanc.size() < 2 && ListePieceNoir.size() < 2))
	{
		emit MenuPrincipal("Egalité");
	}
}

void Plateau::couleurSurCaseValide(std::list<Modele::EmplacementValide> listeEmplacements)
{
	for (auto&& caseValide : listeEmplacements) {
		emit listeCases(caseValide.ligne, caseValide.colonne)->mettreCouleur(caseValide.couleur);
	}
}

void Plateau::couleurPlateauInitial() 
{
	for (auto&& box : listeCases) {
		emit box->mettreCouleurBase();
	}
}

void Modele::Plateau::tourDeJeuChangement(std::string quiJoue)
{
	tourDeJeu == "Noir" ? tourDeJeu = "Blanc" : tourDeJeu = "Noir";
	emit changementTour(tourDeJeu.tour);
}

void Plateau::enleverPieceElimine(Modele::ModelePieceEchec* piece)
{
	std::vector<std::unique_ptr<ModelePieceEchec>>::iterator pieceAsupprimer;

	if (piece->lireEquipe() == "Noir")
	{
		for (auto&& it = ListePieceNoir.begin(); it != ListePieceNoir.end(); it++) {
			if (it->get() == piece) {
				pieceAsupprimer = it;
			}
		}

		ListePieceNoir.erase(pieceAsupprimer);
	}
	else
	{
		for (auto&& it = ListePieceBlanc.begin(); it != ListePieceBlanc.end(); it++) {
			if (it->get() == piece) {
				pieceAsupprimer = it;
			}
		}
		ListePieceBlanc.erase(pieceAsupprimer);
	}
}
