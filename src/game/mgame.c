/* File name : mgame.c */
/* Driver Game */

#include "game.h"
int main()
{
	//Kamus
	Board B;
	Chance C;
	ListOfPlayer Pl;
	//Algoritma
	InisialisasiGame(&Pl,&B,&C);
	Leaderboard(Pl,B);
	//Mencoba prosedur otomatis
	RandomChance(B,C,Pl);
	GetBonus(Pl);
	Tax(B,Cur(Pl));
	//Bersih-bersih
	CleanGame(&Pl,&B);
	return 0;
}
