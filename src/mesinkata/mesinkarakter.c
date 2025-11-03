#include "../global/global.h"
#include "mesinkarakter.h"

//definisi states
char CC;
boolean EOP;

static FILE *pita;
static int retval;


void START()
/* 	I.S. sembarang
	F.S. CC adalah karakter pertama pita (file)
		 Bila Kondisi EOP terpenuhi, nyalakan EOP
*/
{		
		//Kamus Lokal
		char filename1[40];
		//Algoritma
		strcpy(filename1,"../data/");
		strcat(filename1,filename);
		pita=fopen(filename1,"r");
		ADV();
}

void ADV()
/*	I.S. CC!=mark
	F.S. CC adalah karakter berikutnya yang dapat diakuisisi
		 contoh untuk pita "IF", bila CC menunjuk 'I', maka CC berikutnya adalah 'F' 
		 Bila Kondisi EOP terpenuhi, nyalakan EOP
*/
{
	retval = fscanf(pita,"%c",&CC);
	EOP = (CC==mark);
	if (EOP)	{
		fclose(pita);
	}
}

