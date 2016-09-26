/* Nama File : chance.c */
/* File Body dari header chance.h*/

#include "chance.h"

char filename[30];

/** Prosedur dan Fungsi Chance **/
/* Prosedur dan Fungsi Primitif */
void CreateEmptyChance(Chance *C)
/* Mendefinisikan Chance Kosong */
{
	int i;
	for (i=IdxMin;i<=IdxMax;i++)
	{
		(*C).Tab[i]=ValUndef;
	}
	(*C).Jumlah=IdxUndef;
}

void LoadChance(Chance *C,char fileinput[])
/* Meload Chance pada file */
{
	int i;
	strcpy(filename,fileinput);
	STARTKATA();
	i=1;
	while (!EndKata)
	{
		(*C).Tab[i]=ConvertToBilangan(CKata);
		i++;
		ADVKATA();
		ADVKATA();
	}
	(*C).Jumlah=i-1;
}

/** ================================================= **/
/* Prosedur dan Fungsi Tambahan */
void PrintChance(Chance C)
/* Mencetak daftar Chance*/
{
	//Kamus
	int i;
	//Algoritma
	for (i=1;i<=C.Jumlah;i++)
	{
		printf("What Chance ? %d\n",C.Tab[i]);
	}
}

