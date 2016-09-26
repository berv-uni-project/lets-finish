/* File Name : mmesinkata.c */

char filename[30];

#include "mesinkata.h"
int main()
{
	int count;
	strcpy(filename,"default-player.txt");
	count=0;
	STARTKATA();
	while (!EndKata)
	{
		if (CKata.TabKata[0]!='|')
		{
			count++;
		}
		ADVKATA();
	}
	printf("Jumlah kata yang dibaca tanpa pipeline '|' :  %d buah.\n",count);
	return 0;
}
