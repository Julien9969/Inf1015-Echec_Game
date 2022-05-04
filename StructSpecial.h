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
	int ligne = 0, colone = 0;

	/*MatricePosition operator=(std::pair<int, int> nouvellePos) {
		ligne = nouvellePos.first;
		colone = nouvellePos.second;

		return *this;
	}*/
};

struct PixelPosition
{
	int x = 0;
	int y = 0;
};
