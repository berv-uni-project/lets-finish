/* Nama file : mcommand.c */
/* Driver command processor */

#include "command.h"

int main()
{
	//Kamus
	char test[30];
	char test1[30];
	//Algoritma
	//Membaca sebuah command
	ReadCommand(test);
	//Tulis kembali perintah tersebut
	printf("Your command : %s\n",test);
	//Mengambil query dari perintah tertentu
	printf("Insert command : now <day>\n");
	ReadCommand(test);
	TakeCommandEntry(test,"now",test1);
	//Tuliskan query tersebut
	printf("Your entry : %s\n",test1);
	return 0;
}
