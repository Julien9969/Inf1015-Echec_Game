#pragma once
#include <QObject>
#include <vector>
#include <memory>
#include "StructSpecial.h"

#include "ModelPieceEchec.h"



namespace model {

	class ModelPieceEchec;

	class ModelCase : public QObject
	{
		Q_OBJECT
	public:
		ModelCase(int ligne, int colone);
		~ModelCase();

		const MatricePosition& lirePosition() { return mPosition; }
		const PixelPosition& lirePixelPos() { return pPosition; }
		PixelPosition* accedeCasePixelPos() { return &pPosition; }

		void mettrePiece(ModelPieceEchec* piece);
		void enleverPiece();

		const ModelPieceEchec* getPiece() const { return piece_; }


	private:
		ModelPieceEchec* piece_ = nullptr;
		MatricePosition mPosition;
		PixelPosition pPosition;

	public slots:


	signals:
		void mettreCouleur(QColor couleur);
		void mettreCouleurBase();

	};


	struct ListeCases {
		std::vector<std::unique_ptr<ModelCase>> listeCases;

		ModelCase* operator[](int x) {
			return listeCases[x].get();
		}

		ModelCase* operator()(int x, int y) {
			return listeCases[x * 8 + y].get();
		}

		void push_back(std::unique_ptr<ModelCase> box) {
			listeCases.push_back(move(box));
		}

		auto begin() { return listeCases.begin(); }

		auto end() { return listeCases.end(); }
	};
}