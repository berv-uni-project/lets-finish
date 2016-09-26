/* Nama File : board.h */
/* Header Struktur Data Board */

#ifndef board_h
#define board_h

#include "../global/global.h"

/** Tipe Data Board **/
typedef struct TPetak *Address1;
//Address1 sebagai list of petak
//List yang digunakan list sirkuler

typedef struct {
	int Harga; 
	//Berisi harga pembelian petak, -999 tidak dapat dibeli
	int Level;
	//Berisi level rumah dalam petak [0..4]
	char WhoInHere[4];
	//Akan berisi huruf pemain yang ada dalam petak [A..D], kosong N semua.
	char MatiLampu;
	//H - Hidup, M - Mati
	char Offered; 
	// T -  Offered / F - Not Offered
	char WorldCup; 
	// A..D - Player ... actived world cup , - - not actived
	char JenisPetak;
	//N tidak dapat dibeli
	//K Kota
	//P Tempat Parawisata
	char Pemilik;
	//Berisi pemilik petak [A..D], N menandakan tanpa pemilik
	Kata Nama;
	//Berisi nama petak
} Infotype1;
//Informasi yang disimpan oleh petak

typedef struct TPetak {
	Address1 next;
	Infotype1 info;
} Petak;

typedef struct {
	Address1 Start;
} Board;
//Petak Menunjukan Awal

//Selektor
#define Start(B) (B).Start

//Selektor Khusus
#define Pemilik(P) Info(P).Pemilik
#define JenisPetak(P) Info(P).JenisPetak
#define WorldCup(P) Info(P).WorldCup
#define Offered(P) Info(P).Offered
#define Level(P) Info(P).Level
#define Harga(P) Info(P).Harga
#define MatiLampu(P) Info(P).MatiLampu

/** Fungsi dan Prosedur Struktur Data Board **/

/* Fungsi dan Prosedur Primitif */
void AlokasiPetak(Address1 *P,Infotype1 X);
/* Mengalokasikan tipe petak */

void DealokasiPetak(Address1 *P);
/* Menghapus elemen petak dan mengembalikan memori ke sistem */

void CreateEmptyBoard(Board *B);
/* Membuat board kosong */

boolean IsEmptyBoard(Board B);
/* Pengecekan apakah board kosong */

Address1 LastBoard(Board B);
/* Mencari alamat terakhir Board */

void LoadBoard(Board *B,char fileinput[]);
/* Membaca data Board melalui file disimpan dalam memori. */

void SaveBoard(Board B,char fileinput[]);
/* Menyimpan data Board ke dalam file. */

void DeleteAllBoard(Board *B);
/* Menghapus semua petak dalam Board. */

/* Fungsi dan Prosedur Tambahan */
Address1 SearchPetak(Board B,Kata NamaPetak);

void InfoPetak(Board B,Kata NamaPetak);
/*  I.S. : B dan Nama terdefinisi.
    F.S. : Informasi mengenai harga jual petak atau properti */

void PrintBoard(Board B);
/* Print Board untuk Pengetesan */

int NbElmtPetak(Board B);
//Jumlah petak

Address1 SearchPrec(Board B,Address1 P);
//Mencari alamat sebelum P

void ShowBoard(Board B);
//Menampilkan keadaan board saat ini

/* Prosedur Bantuan Show Board */
void PrintSpasi(int n);
/* Mencetak spasi sejumlah n*/

void PrintPenutup(int n);
/* Mencetak simbol _ */

int JumlahBilangan(int N);
/* Mendapatkan jumlah bilangan, contoh : 10 = 2, 1 = 1, 300 = 3*/

boolean IsEmptyPenempat(Address1 P);
//Mengecek apakah ada yang menempati suatu board

int TotalPenempat(Address1 P);
//Menentukan jumlah penempat

void PrintPenempat(Address1 P);
//Mencetak Penempat Yang Ada

int HargaUpgrade(Address1 P);
//Menghasilkan harga upgrade

int HargaSewa(Address1 P);
//Menghasilkan harga sewa

int HargaSellBank(Address1 P);
//Menghasilkan harga jual ke Bank

int HargaSellOffered(Address1 P);
//Menghasilkan harga jual ke pembeli

int HargaRebut(Address1 P);
//Menghasilkan harga rebut

#endif
