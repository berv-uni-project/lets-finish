/* Nama File : command.h */
/* File Header mengatur Command pengguna*/
#ifndef command_h
#define command_h

#include "../game/game.h"

/** Mengatur Command dari Pengguna **/
void ReadCommand(char command[]);
/* Membaca Command Dari Pengguna */

boolean ValidCommand1(char command[]);
/* Mengecek Validasi Command Sebelum Mulai Permainan */

void ProccessPhase1(char command[],Board *B,ListOfPlayer *Pl,Chance *C);
/* Memproses Phase 1 */

void CommandProccessor(char command[],boolean *Finish,Board *B,ListOfPlayer *Pl,Chance C,Address1 *Pd);
/* Mengatur Command */

void TakeCommandEntry(char command1[],char command[],char entry[]);
/* Mengambil Entry yang dimasukan oleh command yang valid */

/*  Berhubungan string dan kata */
Kata StringToKata(char str[]);
/* Fungsi merubah representasi string menjadi kata */

boolean IsSubString(char s1[],char s2[]);
//Mengecek apakah s1 substring dari s2

boolean IsStringSama(char s1[],char s2[]);
//Mengecek apakah s1 sama dengan s2

#endif
