/*
* Définitions de structures pour simplifier l'utilisation de certains élément.
*
* Fichier : StructSpécial.h, StructSpécial.cpp
* Auteurs : Sebastian Espin, Julien Roux
* Date : 05/05/2022
* Crée : 01/04/2022
*/

#pragma once
#include <string>
#include <utility>

struct TourDeJeu{ 
	TourDeJeu operator=(std::string str) {
		tour = str;
		return *this;
	}

	bool operator==(std::string str) {
		if (str == tour) {
			return true;
		}
		return false;
	}

	std::string tour = "Blanc";
};

struct MatricePosition { 
	int ligne = 0, colonne = 0;
};

struct PixelPosition
{
	int x = 0;
	int y = 0;
};
