#pragma once
#include <QObject>


#include "ModelPieceEchec.h"



namespace model {
	
	struct Position { int ligne = 0, colone = 0; };


	class ModelCase : public QObject
	{
		Q_OBJECT
	public:
		ModelCase(int ligne, int colone);
		~ModelCase();

		const Position& lirePosition() { return position; }

		void mettrePiece(ModelPieceEchec* piece);
		void enleverPiece();


	private:
		ModelPieceEchec* piece_ = nullptr;
		Position position;


	public slots:


	signals:





	};


	struct ListeCases {
		std::vector<ModelCase*> listeCases;

		ModelCase* operator[](int x) {
			return listeCases[x];
		}

		ModelCase* operator()(int x, int y) {
			return listeCases[x * 8 + y];
		}

		void push_back(ModelCase* box) {
			listeCases.push_back(box);
		}

		auto begin() { return listeCases.begin(); }

		auto end() { return listeCases.end(); }
	};
}