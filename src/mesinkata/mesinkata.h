#ifndef MESINKATA_H
#define MESINKATA_H
#define mark '.'
#define blank ' '
#define NMax 30
#include "mesinkarakter.h"

//definisi tipe kata
typedef struct {
	char TabKata[NMax];
	int	 Length;
} Kata;

//definisi state mesin kata
extern boolean EndKata;
extern Kata	CKata;

/* Primitif-primitif mesin kata */
void Ignore_Blank();
/*	Mengabaikan satu atau beberapa BLANK
	I.S. : CC sembarang
	F.S. : CC != BLANK atau CC == MARK
*/

void STARTKATA();
/*	I.S. : CC sembarang
	F.S  : Salah satu dari dua kondisi dibawah.
		1. EndKata = true dan CC == Mark
		2. EndKata = false, CKata adalah kata yang sudah diakuisisi, dan CC adalah satu karakter setelah karakter terakhir kata

		Keterangan: CC mengacu pada yang disebut pada mesinkarakter
*/

void ADVKATA();
/*	I.S. : EndKata = false; CC adalah karakter sesudah karakter terakhir
	dari kata yg sudah diakuisisi
	F.S. : Jika CC == MARK, maka EndKata == true
	atau EndKata = false, CKata adalah kata terakhir yang sudah diakuisisi;
	CC karakter pertama sesudah karakter terakhir kata
*/

void SalinKata();
/*	Mengakuisisi kata, menyimpan dalam CKata
	I.S. : CC adalah karakter pertama dari kata
	F.S. : CKata berisi kata yang sudah diakuisisi, jika karakternya melebihi
	NMax, sisa "kata" dibuang; CC == BLANK atau CC == MARK; CC adalah
	karakter sesudah karakter terakhir yang diakuisisi
*/

/* Operasi Lain */
boolean IsKataSama(Kata K1, Kata K2);
/*	Mengembalikan true jika K1 = K2; dua kata dikatakan sama jika panjangnya sama dan
	urutan karakter yang menyusun kata juga sama. Sensitif terhadap uppercase dan lowercase
*/

int ConvertToBilangan(Kata CKata);
/*	Mengembalikan nilai bilangan dari CKata */

Kata CopyKata(Kata CKata);
/* Copy CKata ke suatu variabel */

void PrintKata(Kata CKata);
//Mencetak Kata

#endif
