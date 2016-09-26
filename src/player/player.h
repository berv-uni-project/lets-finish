/* Nama file : player.h */
/* Header Struktur Data List Player */

#ifndef player_h
#define player_h

#include "../global/global.h"
/** Tipe Data Player **/
typedef struct TPlayer *Address2;
//Address2 sebagai List Of Player
//List yang digunakan list sirkuler

typedef struct {
	int chance[4]; //Chance yang akan disimpan
	int uang; //Satuan dalam K
	char id; //ID Player [A..D], N no player
	int injail; // 1[Awal penjara] - 4[Harus membayar] - Dipenjara / 0 - Bebas
	char RolledDice; // N - No, R - Rolled
	char Bought; // N - No, B - Bought
	char Upgraded; // N - No, U - Upgraded
} Infotype2;

typedef struct TPlayer {
	Infotype2 info;
	Address2 next;
} Player;

typedef struct {
	Address2 Current;
} ListOfPlayer;

//Selektor
#define Cur(Pl) (Pl).Current

//Selektor Khusus
#define Uang(Pl) Info(Pl).uang
#define Id(Pl) Info(Pl).id
#define Injail(Pl) Info(Pl).injail
#define RolledDice(Pl) Info(Pl).RolledDice
#define Bought(Pl) Info(Pl).Bought
#define Upgraded(Pl) Info(Pl).Upgraded

/** Fungsi dan Prosedur Mengatur Player **/

/* Fungsi dan Prosedur Primitif */
void AlokasiPlayer(Address2 *P,Infotype2 X);
/* Mengalokasikan tipe data Player */

void DealokasiPlayer(Address2 *P);
/* Mengembalikan memori ke sistem */

void CreatePlayer(ListOfPlayer *Pl);
/* Membuat tanpa player */

boolean IsEmptyPlayer(ListOfPlayer Pl);
/* Pengecekan apakah tanpa pemain */

Address2 LastPlayer(ListOfPlayer Pl);
/* Mencari alamat Player Terakhir */

void LoadPlayerStatus(ListOfPlayer *Pl,char fileinput[]);
/* I.S : Pl sembarang dan nama file terdefinisi. */
/* F.S : Pl terdefinisi sesuai dengan nama file. Jika gagal Pl tidak berubah. */
/* Proses : Membaca file sesuai dengan input nama file. */

void SavePlayerStatus(ListOfPlayer Pl,char fileinput[]);
/* Menyimpan Status Player Sebelumnya */

void DeletePlayer(ListOfPlayer *Pl);
/* Menghapus hanya satu player */

void DeleteAllPlayer(ListOfPlayer *Pl);
/* Menghapus semua data dalam Player */

/* Fungsi Tambahan */
Address2 SearchPlayer(ListOfPlayer Pl,char playerid);
//Mencari alamat player pada giliran player

void PrintPlayerStatus(ListOfPlayer Pl);
/* Print semua status pemain. */

#endif
