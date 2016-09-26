/* Nama file : mboard.c */
/* Driver board */

#include "board.h"
#include "../game/game.h"

int main()
{
	//Kamus
	Board B;
	//Inisialisasi
	CreateEmptyBoard(&B);
	//Load Board
	LoadBoard(&B,"default-map.txt");
	//Print Isi Semua Board
	PrintBoard(B);
	//Simpan ke dalam teks file
	SaveBoard(B,"saved-map.txt");
	printf("Data sudah tersimpan dalam directory data.\n");
	//Menampilkan papan permainan
	ShowBoard(B);
	//Menghapus Semua Isi Board
	DeleteAllBoard(&B);
	return 0;
}
