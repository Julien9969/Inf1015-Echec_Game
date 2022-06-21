#include "InterfaceJeu.h"

#if __has_include("gtest/gtest.h")
#include "gtest/gtest.h"
#endif
#ifdef TEST
using Ui::InterfaceJeu;
using Ui::VuePieceEchec;
using Ui::VueCase;

TEST(InterfaceJeu, CreationDuJeu) {
	InterfaceJeu jeu;
	jeu.MenuPrincipal();
	jeu.menuInfo();
	EXPECT_EQ(jeu.plateau(), nullptr);
	jeu.nouvellePartie();
	EXPECT_NE(jeu.plateau(), nullptr);
	EXPECT_EQ(jeu.plateau()->listeCases.size(), 64);
	EXPECT_NE(jeu.scene(), nullptr);
}

TEST(InterfaceJeu, Deplacement) {
	InterfaceJeu jeu;
	jeu.nouvellePartie();
	
	VuePieceEchec piece(jeu.plateau()->listeCases(7, 0)->getPiece());
	auto event = new QGraphicsSceneMouseEvent(QEvent::MouseButtonPress);
	piece.mousePressEvent(event);
	auto hover = new QGraphicsSceneHoverEvent();
	piece.hoverEnterEvent(hover);

	VueCase caseU(0, 0, 0, 0, jeu.plateau()->listeCases(3, 0));
	caseU.mousePressEvent(event);
	caseU.hoverEnterEvent(hover);
	caseU.hoverLeaveEvent(hover);

	delete event;
	delete hover;

	jeu.plateau()->recevoirPieceClique(jeu.plateau()->listeCases(6, 0)->getPiece());
	jeu.plateau()->recevoirCaseClique(jeu.plateau()->listeCases(4, 0));

	EXPECT_EQ(jeu.plateau()->listeCases(6, 0)->getPiece(), nullptr);
	EXPECT_NE(jeu.plateau()->listeCases(4, 0)->getPiece(), nullptr);

	jeu.plateau()->listeCases(4, 0)->getPiece()->mangeLaPiece(jeu.plateau()->listeCases(1, 0)->getPiece());

	EXPECT_EQ(jeu.plateau()->ListePieceNoir.size(), 15);

}

TEST(InterfaceJeu, FinDuJeu) {
	InterfaceJeu jeu;
	jeu.nouvellePartie();
	jeu.plateau()->ListePieceNoir.erase(jeu.plateau()->ListePieceNoir.begin(), jeu.plateau()->ListePieceNoir.end());
	jeu.plateau()->recevoirPieceClique(jeu.plateau()->listeCases(6, 0)->getPiece());
	jeu.plateau()->recevoirCaseClique(jeu.plateau()->listeCases(5, 0));
	EXPECT_EQ(jeu.plateau(), nullptr);
}

#endif
