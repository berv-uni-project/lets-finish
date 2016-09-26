/* Nama File : mplayer.c */
/* File driver player */

#include "player.h"

int main()
{
	//Kamus
	ListOfPlayer Pl;
	//Algoritma
	CreatePlayer(&Pl);
	//Membaca status pemain
	LoadPlayerStatus(&Pl,"default-player.txt");
	//Mencetak seluruh status pemain
	PrintPlayerStatus(Pl);
	//Menghapus player yang sedang aktif atau yang pertama
	DeletePlayer(&Pl);
	//Mencetak seluruh status pemain
	PrintPlayerStatus(Pl);
	//Menghapus seluruh status pemain
	DeleteAllPlayer(&Pl);

	return 0;
}
