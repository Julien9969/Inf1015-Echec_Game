#pragma once
#include <string>

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

struct MatricePosition { int ligne = 0, colone = 0; };

struct PixelPosition
{
	int x = 0;
	int y = 0;
};
