#pragma once
#include <QObject>
#include <list>
#include <vector>
#include <utility>
#include <string>
#include <QColor>
#include "case.h"

//namespace Ui { 
//	class Case;
//	struct ListeCases;
//};

namespace Ui {
	class Case;
	struct ListeCases;
};

namespace model {

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
		virtual ~ModelPieceEchec() = default;

		int lireX() const { return ligne_; }
		int lireY() const { return colone_; }
		std::pair<int, int> matricePos() const { return { ligne_, colone_ }; }

		std::pair<int, int>& scenePos() { return ScenePos_; }


		const QString& lireCheminImage() const { return cheminImage; }
		void mangeLaPiece(ModelPieceEchec* piece);

		const std::string& lireEquipe() const { return equipe_; }
		std::list<EmplacementValide>& lireEmplacementValide() { return listeEmplacementsValides; }

		void positionner(std::pair<int, int> matricePos, std::pair<int, int> scenePos);
		
		void PieceElimine();

	protected:
		std::string equipe_;
		QString cheminImage;

		std::pair<int, int> ScenePos_;

		int ligne_ = 0;
		int colone_ = 0;

		std::list<EmplacementValide> listeEmplacementsValides;

	public slots:
		virtual std::list<EmplacementValide>& listerDeplacementsValides(Ui::ListeCases& listeCase) = 0;
		virtual bool deplacementEstValide(const std::pair<int, int>& destination) = 0;
	
	signals:   
		void mettrePositionVue(std::pair<int, int> matricePos, std::pair<int, int> scenePos);
		void suppressionPiece();
	};
}