#include "mesinkata.h"

//definisi state mesin kata
boolean EndKata;
Kata	CKata;

/* Primitif-primitif mesin kata */
void Ignore_Blank()
/*	Mengabaikan satu atau beberapa BLANK
	I.S. : CC sembarang
	F.S. : CC != BLANK atau CC == MARK
*/
{
	while (((CC==blank)||(CC=='\n'))&&(CC!=mark))
	{
		ADV();
	}
}

void STARTKATA()
/*	I.S. : CC sembarang
	F.S  : Salah satu dari dua kondisi dibawah.
		1. EndKata = true dan CC == Mark
		2. EndKata = false, CKata adalah kata yang sudah diakuisisi, dan CC adalah satu karakter setelah karakter terakhir kata

		Keterangan: CC mengacu pada yang disebut pada mesinkarakter
*/
{
	START();
	Ignore_Blank();
	if (CC==mark) {
		EndKata = true;
	}
	else
	{
		EndKata = false;
		SalinKata();
	}
}

void ADVKATA()
/*	I.S. : EndKata = false; CC adalah karakter sesudah karakter terakhir
	dari kata yg sudah diakuisisi
	F.S. : Jika CC == MARK, maka EndKata == true
	atau EndKata = false, CKata adalah kata terakhir yang sudah diakuisisi;
	CC karakter pertama sesudah karakter terakhir kata
*/
{
	Ignore_Blank();
	if (CC==mark) {
		EndKata=true;
	}
	else {
		SalinKata();
	}
}

void SalinKata()
/*	Mengakuisisi kata, menyimpan dalam CKata
	I.S. : CC adalah karakter pertama dari kata
	F.S. : CKata berisi kata yang sudah diakuisisi, jika karakternya melebihi
	NMax, sisa "kata" dibuang; CC == BLANK atau CC == MARK; CC adalah
	karakter sesudah karakter terakhir yang diakuisisi
*/
{
	//Kamus Lokal
	int i=0;
	//Algoritma
	for (;;)
	{
		CKata.TabKata[i]=CC;
		ADV();
		if ((CC==mark)||(CC==blank)||(CC=='\n'))
			break;
		else
			i++;
	}
	CKata.Length=i+1;
}

/* Operasi Lain */
boolean IsKataSama(Kata K1, Kata K2)
/*	Mengembalikan true jika K1 = K2; dua kata dikatakan sama jika panjangnya sama dan
	urutan karakter yang menyusun kata juga sama. Sensitif terhadap uppercase dan lowercase
*/
{
	if (K1.Length!=K2.Length)
		return false;
	else
	{
		boolean found;
		found = true;
		int i=0;
		while ((i<K1.Length)&&(found))
		{
			if (K1.TabKata[i]!=K2.TabKata[i])
				found = false;
			else
				i++;
		}
		if (found)
			return true;
		else
			return false;
	}
}

int ConvertToBilangan(Kata CKata) {
/*	Mengembalikan nilai bilangan dari CKata
*/
	int i;
	int total = 0;
	if (CKata.TabKata[0]=='-')
	{
		for (i=1; i<CKata.Length; i++)
		{
			if (i>1)
				total *= 10;
			total = total + (CKata.TabKata[i]-'0');
		}
		total = total * (-1);
	}
	else
	{
		for (i=0; i<CKata.Length; i++)
		{
			if (i>0)
				total *= 10;
			total = total + (CKata.TabKata[i]-'0');
		}
	}
	return total;

}

Kata CopyKata(Kata CKata)
/* Copy CKata ke suatu variabel */
{
	Kata Temp;
	int i;
	for (i=0;i<CKata.Length;i++)
	{
		if(CKata.TabKata[i]=='_')
		{
			Temp.TabKata[i]=' ';
		}
		else
		{
			Temp.TabKata[i]=CKata.TabKata[i];
		}
	}
	Temp.Length=CKata.Length;
	return Temp;
}

void PrintKata(Kata CKata)
//Mencetak Kata
{
	int i;
	for (i=0;i<CKata.Length;i++)
	{
		printf("%c",CKata.TabKata[i]);
	}
}
