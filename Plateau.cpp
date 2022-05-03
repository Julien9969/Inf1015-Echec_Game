#include "Plateau.h"
#include <QDebug>
#include <QLabel>
#include <QEvent>


using iter::range;
using model::Tour;
using model::Roi;
using model::Fou;
using model::ModelPieceEchec;
using model::Plateau;

Plateau::Plateau()
{
	creeCases();
	creePiecesNoir();
	creePieceBlanc();
	mettreLesPieces();
}

void Plateau::creeCases() 
{
	for (int ligne : range(8)) {

		for (int colone : range(8)) {

			std::unique_ptr<model::ModelCase> uneCase = std::make_unique<model::ModelCase>(ligne, colone);

			listeCases.push_back(move(uneCase));
		}
	}
}

void Plateau::creePiecesNoir()
{
	std::unique_ptr<ModelPieceEchec> tourN = std::make_unique<Tour>("Noir");
	ListePieceNoir.push_back(move(tourN));

	std::unique_ptr<ModelPieceEchec> tourN1 = std::make_unique<Tour>("Noir");
	ListePieceNoir.push_back(move(tourN1));

	std::unique_ptr<ModelPieceEchec> roiN = std::make_unique<Roi>("Noir");
	ListePieceNoir.push_back(move(roiN));

	std::unique_ptr<ModelPieceEchec> fouN = std::make_unique<Fou>("Noir");
	ListePieceNoir.push_back(move(fouN));

	std::unique_ptr<ModelPieceEchec> fouN1 = std::make_unique<Fou>("Noir");
	ListePieceNoir.push_back(move(fouN1));
}

void Plateau::creePieceBlanc()
{
	std::unique_ptr<ModelPieceEchec> tourB = std::make_unique<Tour>("Blanc");
	ListePieceBlanc.push_back(move(tourB));

	std::unique_ptr<ModelPieceEchec> tourB1 = std::make_unique<Tour>("Blanc");
	ListePieceBlanc.push_back(move(tourB1));

	std::unique_ptr<ModelPieceEchec> roiB = std::make_unique<Roi>("Blanc");
	ListePieceBlanc.push_back(move(roiB));

	std::unique_ptr<ModelPieceEchec> fouB = std::make_unique<Fou>("Blanc");
	ListePieceBlanc.push_back(move(fouB));

	std::unique_ptr<ModelPieceEchec> fouB1 = std::make_unique<Fou>("Blanc");
	ListePieceBlanc.push_back(move(fouB1));

	try {
		std::unique_ptr<ModelPieceEchec> roiB2 = std::make_unique<Roi>("Blanc");
	}
	catch (std::logic_error& e) {
		qDebug() << "Erreur : " << e.what();
	}
}

void Plateau::mettreLesPieces()
{
	model::ModelCase* tempCase = nullptr;
	ModelPieceEchec* tempPiece = nullptr;
	int i = 0;
	
	for (auto&& j = ListePieceNoir.begin(); j != ListePieceNoir.end(); j++) {
			
		tempCase = listeCases[i++];
		tempPiece = j->get();

		tempCase->mettrePiece(tempPiece);
		
		tempPiece->positionner(tempCase->lirePosition(), tempCase->lirePixelPos());
	}

	i = 0;
	
	for (auto&& j = ListePieceBlanc.begin(); j != ListePieceBlanc.end(); j++) {

		tempCase = listeCases[56 + i++];
		tempPiece = j->get();

		tempCase->mettrePiece(tempPiece);

		tempPiece->positionner(tempCase->lirePosition(), tempCase->lirePixelPos());
	}
}



void Plateau::recevoirCaseClique(model::ModelCase* caseClique)
{
	if ((pieceActuelle_ != nullptr) && (caseClique->getPiece() == nullptr) && (pieceActuelle_->deplacementEstValide(caseClique->lirePosition())))
	{
		listeCases(pieceActuelle_->lireMatricePos().ligne, pieceActuelle_->lireMatricePos().colone)->enleverPiece();

		qDebug() << "indice tableau case : " << pieceActuelle_->lireMatricePos().ligne + 8 * pieceActuelle_->lireMatricePos().colone;

		caseClique->mettrePiece(pieceActuelle_);
		pieceActuelle_->positionner(caseClique->lirePosition(), caseClique->lirePixelPos());

		tourDeJeuChangement(pieceActuelle_->lireEquipe());

		couleurPlateauInitial();
		pieceActuelle_ = nullptr;

	}
}



void Plateau::recevoirPieceClique(model::ModelPieceEchec* pieceClique)
{
	couleurPlateauInitial();

	qDebug() << "tour : " << QString::fromStdString(tourDeJeu.tour) << " joue " << QString::fromStdString(pieceClique->lireEquipe());

	if ((pieceActuelle_ != nullptr) && (pieceClique->lireEquipe() != pieceActuelle_->lireEquipe())) {
		if (pieceActuelle_->deplacementEstValide(pieceClique->lireMatricePos())) {

			listeCases(pieceActuelle_->lireMatricePos().ligne, pieceActuelle_->lireMatricePos().colone)->enleverPiece();
			listeCases(pieceClique->lireMatricePos().ligne, pieceClique->lireMatricePos().colone)->mettrePiece(pieceActuelle_);

			pieceActuelle_->mangeLaPiece(pieceClique);
			tourDeJeuChangement(pieceActuelle_->lireEquipe());
			pieceActuelle_ = nullptr;
		}
	}
	else if (tourDeJeu == pieceClique->lireEquipe()) {
		pieceActuelle_ = pieceClique;
		pieceClique->listerDeplacementsSemiValides(listeCases);
		listerDeplacementsValide();
		couleurSurCaseValide(pieceClique->lireEmplacementSemiValide());
		qDebug() << "on Save";
	}
}

void Plateau::listerDeplacementsValide()
{
	std::vector<std::unique_ptr<ModelPieceEchec>>* listePieceAdverse;
	std::vector<std::unique_ptr<ModelPieceEchec>>* listePieceMonEquipe;

	//Le Roi ne peut pas se mettre en echec
	if (dynamic_cast<Roi*>(pieceActuelle_) != 0) {
		pieceActuelle_->lireEquipe() == "Blanc" ? listePieceAdverse = &ListePieceNoir : listePieceAdverse = &ListePieceBlanc;
		qDebug() << "verif c un roi";

		listeCases(pieceActuelle_->lireMatricePos().ligne, pieceActuelle_->lireMatricePos().colone)->enleverPiece();

		for (auto&& piece = listePieceAdverse->begin(); piece != listePieceAdverse->end(); piece++) {
			piece->get()->listerDeplacementsSemiValides(listeCases);

			for (auto&& deplacemetAdv = piece->get()->lireEmplacementSemiValide().begin(); deplacemetAdv != piece->get()->lireEmplacementSemiValide().end(); deplacemetAdv++) 
			{
				qDebug() << "adv : " << deplacemetAdv->ligne << " " << deplacemetAdv->colone;
				std::list<model::EmplacementValide>::iterator mauvaisDeplacement = std::find_if(pieceActuelle_->lireEmplacementSemiValide().begin(), 
					pieceActuelle_->lireEmplacementSemiValide().end(),
					[&](model::EmplacementValide& deplacement)
					{
						/*bool mangeEnemiMeMetEnEchec = false;
						bool deplacementEstInvalide = (deplacemetAdv->ligne == deplacement.ligne) && (deplacemetAdv->colone == deplacement.colone);*/
						qDebug() << "adv : " << deplacemetAdv->ligne << " " << deplacemetAdv->colone << " MOI" << deplacement.ligne << " " << deplacement.colone;
						if ((deplacemetAdv->ligne == deplacement.ligne) && (deplacemetAdv->colone == deplacement.colone)) {
							return true;
						}
						else {
							for (auto&& emplacement = piece->get()->lirePiecesAlies().begin(); emplacement != piece->get()->lirePiecesAlies().end(); emplacement++)
							{
								if ((emplacement->ligne == deplacement.ligne) && (emplacement->colone == deplacement.colone)) {
									return true;
									break;
								}
							}
							
						}
					});

				if (mauvaisDeplacement != pieceActuelle_->lireEmplacementSemiValide().end()) {
					listeCases(piece->get()->lireMatricePos().ligne, piece->get()->lireMatricePos().colone)->mettreCouleur(QColor(236, 206, 91));
					pieceActuelle_->lireEmplacementSemiValide().erase(mauvaisDeplacement);
					qDebug() << "mauvais deplacement";
				}
				
			}
		}

		listeCases(pieceActuelle_->lireMatricePos().ligne, pieceActuelle_->lireMatricePos().colone)->mettrePiece(pieceActuelle_);
	}

	else if (pieceActuelle_ != nullptr)
	{
		pieceActuelle_->lireEquipe() == "Blanc" ? listePieceMonEquipe = &ListePieceBlanc : listePieceMonEquipe = &ListePieceNoir;
		pieceActuelle_->lireEquipe() == "Blanc" ? listePieceAdverse = &ListePieceNoir : listePieceAdverse = &ListePieceBlanc;


		std::vector<std::unique_ptr<ModelPieceEchec>>::iterator  monRoi = std::find_if(listePieceMonEquipe->begin(), listePieceMonEquipe->end(),
			[](std::unique_ptr<ModelPieceEchec>& piece) { return dynamic_cast<Roi*>(piece.get()) != 0; });
		
		for (auto&& piece = listePieceAdverse->begin(); piece != listePieceAdverse->end(); piece++) {
			
			//On protege le roi si il est en echec avant move
			if (roiEnEchec(piece->get(), monRoi->get()))
			{
				//qDebug() << "deplacement ateint " << deplacementAtteindRoi->ligne << " " << deplacementAtteindRoi->colone;
				bool metEnEchec;
				listeCases(piece->get()->lireMatricePos().ligne, piece->get()->lireMatricePos().colone)->mettreCouleur(QColor(236, 206, 91));
				listeCases(pieceActuelle_->lireMatricePos().ligne, pieceActuelle_->lireMatricePos().colone)->enleverPiece();

				auto it = std::remove_if(pieceActuelle_->lireEmplacementSemiValide().begin(), pieceActuelle_->lireEmplacementSemiValide().end(),
					[&](model::EmplacementValide& emplacement) {
						if (listeCases(emplacement.ligne, emplacement.colone)->getPiece() == nullptr) {
							listeCases(emplacement.ligne, emplacement.colone)->mettrePiece(pieceActuelle_);
							metEnEchec = roiEnEchec(piece->get(), monRoi->get());
							listeCases(emplacement.ligne, emplacement.colone)->enleverPiece();
							return metEnEchec;
						}
						else if (listeCases(emplacement.ligne, emplacement.colone)->getPiece() == piece->get()) {
							return false;
						}
						return true;
					}
					);

				pieceActuelle_->lireEmplacementSemiValide().erase(it, pieceActuelle_->lireEmplacementSemiValide().end());

				listeCases(pieceActuelle_->lireMatricePos().ligne, pieceActuelle_->lireMatricePos().colone)->mettrePiece(pieceActuelle_);
			}
			//On se met pas en echec apres un deplacement
			else {

			}
		}

		qDebug() << "lesrt go" << QString::fromStdString(monRoi->get()->lireEquipe());
	}
}

bool Plateau::deplacementMetEnEchec() {

}

bool Plateau::roiEnEchec(ModelPieceEchec* piece, ModelPieceEchec* roi) {
	piece->listerDeplacementsSemiValides(listeCases);

	std::list<model::EmplacementValide>::iterator deplacementAtteindRoi = std::find_if(piece->lireEmplacementSemiValide().begin(), piece->lireEmplacementSemiValide().end(),
		[&roi](model::EmplacementValide& emplacement)
		{return (emplacement.ligne == roi->lireMatricePos().ligne) && ((emplacement.colone == roi->lireMatricePos().colone)); });

	return deplacementAtteindRoi != piece->lireEmplacementSemiValide().end();
}

void Plateau::couleurSurCaseValide(std::list<model::EmplacementValide> listeEmplacements)
{
	for (auto&& caseValide : listeEmplacements) {
		emit listeCases(caseValide.ligne, caseValide.colone)->mettreCouleur(caseValide.couleur);
	}

}

void Plateau::couleurPlateauInitial() 
{
	qDebug() << "seze : " << listeCases.listeCases.size();
	for (auto&& box : listeCases) {
		emit box->mettreCouleurBase();
	}
}

void model::Plateau::tourDeJeuChangement(std::string quiJoue)
{
	tourDeJeu == "Noir" ? tourDeJeu = "Blanc" : tourDeJeu = "Noir";
	qDebug() << QString::fromStdString(tourDeJeu.tour);
	emit changementTour(tourDeJeu.tour);

}

void Plateau::enleverPieceElimine(model::ModelPieceEchec* piece)
{
	std::vector<std::unique_ptr<ModelPieceEchec>>::iterator pieceAsupprimer;

	if (piece->lireEquipe() == "Noir")
	{
		for (auto&& it = ListePieceNoir.begin(); it != ListePieceNoir.end(); it++) {
			if (it->get() == piece) {
				qDebug() << "enleve du vector";
				pieceAsupprimer = it;
			}
		}

		ListePieceNoir.erase(pieceAsupprimer);
	}
	else
	{
		for (auto&& it = ListePieceBlanc.begin(); it != ListePieceBlanc.end(); it++) {
			if (it->get() == piece) {
				qDebug() << "enleve du vector";
				pieceAsupprimer = it;
			}
		}
		ListePieceBlanc.erase(pieceAsupprimer);
	}


}




//void Plateau::mouseMoveEvent(QGraphicsSceneMouseEvent* event) {
//	// if there is a cardToPlace, then make it follow the mouse
//	if (pieceActuelle_ != nullptr) {
//		pieceActuelle_->setPos(event->scenePos().x() - 45, event->scenePos().y() - 45);
//		qDebug() << "piece move" << event->pos();
//
//	}
//
//	qDebug() << "move";
//}

