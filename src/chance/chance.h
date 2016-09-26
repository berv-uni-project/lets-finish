/* Nama File : chance.h */
/* File header Struktur Data Chance */

#ifndef chance_h
#define chance_h

#include "../global/global.h"

//Data Chance disimpan dalam tabel kontigu

/** Tipe Data Chance **/
#define IdxMax 50
#define IdxMin 1
#define IdxUndef -999
#define ValUndef -9999

typedef int IdxType;
typedef int ElType;

typedef struct {
	ElType Tab[IdxMax+1];
	int Jumlah;
} Chance;

/** Prosedur dan Fungsi Chance **/
/* Prosedur dan Fungsi Primitif */
void CreateEmptyChance(Chance *C);
/* Mendefinisikan Chance Kosong */

void LoadChance(Chance *C,char fileinput[]);
/* Meload Chance pada file */

/* Prosedur dan Fungsi Tambahan */
void PrintChance(Chance C);
/* Mencetak daftar Chance*/


#endif
