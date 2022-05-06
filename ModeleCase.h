/*
* Classe implémentant la logique d'une Case.
* Structure pour encapsuler une liste de Cases
* 
* Fichier : ModeleCase.h, ModeleCase.cpp
* Auteurs : Sebastian Espin, Julien Roux
* Date : 05/05/2022
* Crée : 28/04/2022
*/

#pragma once
#include <QObject>
#include <vector>
#include <memory>
#include "StructSpecial.h"

#include "ModelePieceEchec.h"



namespace Modele {

	class ModelePieceEchec;

	class ModeleCase : public QObject
	{
		Q_OBJECT
	public:
		ModeleCase(int ligne, int colonne);
		~ModeleCase();

		const MatricePosition& lirePosition() { return mPosition; }
		const PixelPosition& lirePixelPos() { return pPosition; }
		PixelPosition* accedeCasePixelPos() { return &pPosition; }

		void mettrePiece(ModelePieceEchec* piece);
		void enleverPiece();

		ModelePieceEchec* getPiece() { return piece_; }

	private:
		ModelePieceEchec* piece_ = nullptr;
		MatricePosition mPosition;
		PixelPosition pPosition;

	signals:
		void mettreCouleur(QColor couleur);
		void mettreCouleurBase();

	};


	struct ListeCases {
		std::vector<std::unique_ptr<ModeleCase>> listeCases;

		ModeleCase* operator[](int x) {
			return listeCases[x].get();
		}

		ModeleCase* operator()(int x, int y) {
			return listeCases[size_t(x * 8 + y)].get();
		}

		void push_back(std::unique_ptr<ModeleCase> box) {
			listeCases.push_back(move(box));
		}

		const size_t size() const { return listeCases.size(); }

		auto begin() { return listeCases.begin(); }

		auto end() { return listeCases.end(); }
	};
}