/* Nama File : game.h */
/* File Header berkenaan pengaturan game */

#ifndef game_h
#define game_h

#include "../chance/chance.h"
#include "../board/board.h"
#include "../player/player.h"
#include "../global/global.h"
#include "../command/command.h"

//Dipakai untuk leaderboard


/* Fungsi dan Prosedur Utama */
/** Pergerakan Pemain **/
void RollDice(Board B,Chance C,ListOfPlayer Pl, Address1 *Position);
/* Gulirkan Dadumu */

/** Berhubungan dengan Petak dan Pemain **/
void ShowOffered(Board B);
//Menampilkan yang sedang dijual saat ini

void UpgradeHouse(Board B, ListOfPlayer Pl, Kata NamaPetak);
/*  I.S. : B, NamaPetak, dan Pl terdefinisi.
    F.S. : Level bangunan yang sedang ditempati terupgrade.
           Update Board jika bangunan berhasil diupgrade. */

//Membeli itu menyenangkan
void Buy(Board B,ListOfPlayer Pl,Kata NamaPetak);
//Asumsi masukan player sudah ada jadi tidak perlu memakai current soalnya *player sudah menunjuk ke info player.
/*I.S Player Terdefinisi dan Player pada suatu posisi di Map*/ 
/*F.S Jika uang player cukup maka player membeli petak pada map 
 * 	  jika uangnya tidak cukup maka player tidak bisa membeli petak tersebut*/

void BuyOffered(Board B, ListOfPlayer Pl, Kata NamaKata);
/*  I.S. : M, Pl, dan Nama terdefinisi.
    F.S. : Membeli petak dari list Offered. Petak yang sudah dibeli, dikeluarkan daripetak list offered */

//Menjual itu dibutuhkan
void SellKotaOffered(Board B,ListOfPlayer Pl,Kata NamaPetak);

void SellKotaBank(Board B,ListOfPlayer Pl,Kata NamaPetak);

/** Prosedur dan Fungsi Khusus Di Petak Tertentu **/
void Travel(Board B,ListOfPlayer Pl,Address1 Location);

void GetBonus(ListOfPlayer Pl);
/*I.S player masuk ke petak bonus*/
/*F.S Mendapatkan bonus berupa uang*/

void RandomChance(Board B,Chance C,ListOfPlayer Pl);
//Acak kartu

/** Gunakan Kartu Chance-mu **/
void FreeMe(ListOfPlayer Pl);
//Bebaskan dirimu

void FreeTax(ListOfPlayer Pl, Address1 PlayerPosition);
//Lepaskan dari pajak yang membelit

void Off(ListOfPlayer Pl,Address1 Pt,Address2 P);
//Mematikan lampu...

void Protect(Address2 P,Address1 Pt);
//Lindungi kota mu


/** Command Tambahan **/
void PayToFree(ListOfPlayer Pl);
//Membayar untuk keluar penjara

/** Menampilkan berbagai status **/
void Leaderboard(ListOfPlayer Pl, Board M);
/*I.S List Of Player Terdefinisi 
 *F.S Menampilkan leaderboard player dari yang paling kaya ke yang miskin*/

/** Giliran Pemain Sudah Selesai **/
int RandomRange(int min,int max);
/* Mendapatkan nilai random diantara 1 - max */

void EndTurn(ListOfPlayer *Pl);
//Mengakhiri giliran pemain

/* Fungsi dan Prosedur Tambahan */
/** Membantu Fungsi dan Prosedur Utama **/
Address1 PlayerPlace(Board B,char id);
//Mencari letak player di Board

/** Pengatur Antar Muka **/
void ShowPlayerStatus(Address2 Pl,Address1 Location);
/* Menampilkan Status Pemain */

void ShowWelcomeMessage();
/* Menampilkan Pesan Pembuka */

void ERRORMESSAGE();
//Menampilkan pesan kesalahan

void ShowHelp();
/* Menampilkan Antarmuka Bantuan */

/** Mengatur Posisi Pemain dalam Petak **/
void DeletePlayerPosition(ListOfPlayer Pl,Address1 P);

void PlacePlayer(ListOfPlayer Pl,Address1 P);
//Menaruh pemain

/** Mengatur State Game **/
void InisialisasiGame(ListOfPlayer *Pl,Board *B,Chance *C);
/* New Game Detected */

void CleanGame(ListOfPlayer *Pl,Board *B);
/* Clean the Allocation */

boolean IsThreePlayerBankrup(ListOfPlayer Pl);
/* Permainan Selesai jika hanya satu pemain */

void MasukPenjara(Board B, ListOfPlayer Pl);
/*
  I.S Player Berada Diluar Penjara, Player Mendapatkan Kartu masuk penjara
  F.S Player Masuk Ke penjara
*/

int totalAsset(Board B, Address2 P);
/*Mengembalikan total aset 1 player*/

void AutoCommand(Address1 Position,Board B,ListOfPlayer Pl,Chance C);
//Generate AutoCommand

void ResetWorldCup(ListOfPlayer Pl,Board B);
//Menghapus semua history world cup

void ResetLampu(ListOfPlayer Pl,Board B);
//Reset semua yang sudah dimatikan atau menyalakan semua yang mati

boolean IsBankrup(Address2 P1,Board B);
//Apakah kamu sudah tidak sanggup bermain?

boolean IsNoAsset(Address2 P1,Board B);
//Apakah asetmu masih ada?

boolean IsRunOutOfMoney(Address2 P1);
//Apakah uangmu habis?

/* Bayar Pajak */
void Tax(Board B,Address2 PL);
//Membayar pajak itu baik

void PrintUang(int Uang);
//Mencetak format konversi angka

#endif
