/* Nama File : player.c */
/* Body dari file header board.h */

#include "../global/global.h"
#include "player.h"

/** Fungsi dan Prosedur Mengatur Player **/

/* Fungsi dan Prosedur Primitif */
void AlokasiPlayer(Address2 *P,Infotype2 X)
/* Mengalokasikan tipe data Player */
{
	//Kamus Lokal
	int i;
	//Algoritma
	*P= (Player *) malloc (sizeof(Player));
	if (*P!=Nil)
	{
		//Menyimpan informasi id
		Info(*P).id=X.id;
		//Menyimpan informasi uang
		Info(*P).uang=X.uang;
		//Menyimpan informasi chance
		for (i=0;i<4;i++)
		{
			Info(*P).chance[i]=X.chance[i];
		}
		//Menyimpan informasi status dipenjara
		Info(*P).injail=X.injail;
		//Menyimpan status menggulirkan dadu
		Info(*P).RolledDice=X.RolledDice;
		//Menyimpan status pembelian
		Info(*P).Bought=X.Bought;
		//Menyimpan status mengupgrade
		Info(*P).Upgraded=X.Upgraded;
		Next(*P)=Nil;
	}
}

void DealokasiPlayer(Address2 *P)
/* Mengembalikan memori ke sistem */
{
	//Kamus Lokal
	
	//Algoritma
	free(*P);
}


void CreatePlayer(ListOfPlayer *Pl)
/* Membuat tanpa player */
{
	//Kamus Lokal
	
	//Algoritma
	Cur(*Pl)=Nil;
}

boolean IsEmptyPlayer(ListOfPlayer Pl)
/* Pengecekan apakah tanpa pemain */
{
	//Kamus Lokal
	
	//Algoritma
	if (Cur(Pl)==Nil)
	{
		return true;
	}
	else
	{
		return false;
	}
}

Address2 LastPlayer(ListOfPlayer Pl)
/* Mencari alamat Player Terakhir */
{
	//Kamus Lokal
	Address2 P;
	//Algoritma
	if (IsEmptyPlayer(Pl))
	{
		return Nil;
	}
	else
	{
		P=Cur(Pl);
		while (Next(P)!=Cur(Pl))
		{
			P=Next(P);
		}
	}
	return P;
}

void LoadPlayerStatus(ListOfPlayer *Pl,char fileinput[])
/* I.S : Pl sembarang dan nama file terdefinisi. */
/* F.S : Pl terdefinisi sesuai dengan nama file. Jika gagal Pl tidak berubah. */
/* Proses : Membaca file sesuai dengan input nama file. */
{
	//Kamus Lokal
	Address2 Pt,Prec;
	Infotype2 X;
	int i;
	//Algoritma
	//Menyalin nama file
	strcpy(filename,fileinput);
	//Mulai membaca
	STARTKATA();
	CreatePlayer(Pl);
	while(!EndKata)
	{
		X.id=CKata.TabKata[0];
		ADVKATA();
		ADVKATA();
		X.uang=ConvertToBilangan(CKata);
		for (i=0;i<4;i++)
		{
			ADVKATA();
			ADVKATA();
			X.chance[i]=ConvertToBilangan(CKata);
		}
		ADVKATA();
		ADVKATA();
		X.injail=ConvertToBilangan(CKata);
		ADVKATA();
		ADVKATA();
		X.RolledDice=CKata.TabKata[0];
		ADVKATA();
		ADVKATA();
		X.Bought=CKata.TabKata[0];
		ADVKATA();
		ADVKATA();
		X.Upgraded=CKata.TabKata[0];
		AlokasiPlayer(&Pt,X);
		if (Pt!=Nil)
		{
			if (Cur(*Pl)==Nil)
			{
				Cur(*Pl)=Pt;
				Next(Pt)=Cur(*Pl);
				Prec=Pt;
			}
			else
			{
				Next(Prec)=Pt;
				Next(Pt)=Cur(*Pl);
				Prec=Pt;
			}
		}
		ADVKATA();
	}
}

void SavePlayerStatus(ListOfPlayer Pl,char fileinput[])
/* Menyimpan Status Player Sebelumnya */
{
	//Kamus Lokal
	char filename1[40];
	Address2 P;
	int i;
	//Algoritma
	strcpy(filename1,"../data/");
	strcat(filename1,fileinput);
	FILE *fp = fopen(filename1,"w+");
	if (!IsEmptyPlayer(Pl))
	{
		P=Cur(Pl);
		for (;;)
		{
			fprintf(fp,"%c",Info(P).id);
			fprintf(fp," | ");
			fprintf(fp,"%d",Info(P).uang);
			for (i=0;i<4;i++)
			{
				fprintf(fp," | ");
				fprintf(fp,"%d",Info(P).chance[i]);
			}
			fprintf(fp," | ");
			fprintf(fp,"%d",Info(P).injail);
			fprintf(fp," | ");
			fprintf(fp,"%c",Info(P).RolledDice);
			fprintf(fp," | ");
			fprintf(fp,"%c",Info(P).Bought);
			fprintf(fp," | ");
			fprintf(fp,"%c",Info(P).Upgraded);
			fprintf(fp,"\n");
			if (Next(P)==Cur(Pl))
			{
				break;
			}
			else
			{
				P=Next(P);
			}
		}
	}
	fprintf(fp," .");
	fclose(fp);
}

void DeletePlayer(ListOfPlayer *Pl)
/* Menghapus hanya satu player saat kalah */
{
	//Kamus Lokal
	Address2 Pdel,PLast,P2;
	//Algoritma
	if (!IsEmptyPlayer(*Pl))
	{
		//Delete First
		Pdel=Cur(*Pl);
		P2=Next(Cur(*Pl));
		PLast=LastPlayer(*Pl);
		Next(PLast)=P2;
		Next(Cur(*Pl))=Nil;
		Cur(*Pl)=P2;
		DealokasiPlayer(&Pdel);
	}
}

void DeleteAllPlayer(ListOfPlayer *Pl)
/* Menghapus semua data dalam Player */
{
	//Kamus Lokal
	Address2 P,P2,PLast,Pdel;
	//Algoritma
	if(Cur(*Pl)!=Nil)
	{
		P=Cur(*Pl);
		while (Next(P)!=Cur(*Pl))
		{
			//Delete First
			Pdel=P;
			P2=Next(Cur(*Pl));
			PLast=LastPlayer(*Pl);
			Next(PLast)=P2;
			Next(Cur(*Pl))=Nil;
			Cur(*Pl)=P2;
			P=Cur(*Pl);
			DealokasiPlayer(&Pdel);
		}
		//Delete first saat satu elemen
		Pdel=Cur(*Pl);
		DealokasiPlayer(&Pdel);
		Cur(*Pl)=Nil;
	}
}

/* Fungsi Tambahan */
Address2 SearchPlayer(ListOfPlayer Pl,char playerid)
//Mencari alamat player pada giliran player
{
	//Kamus Lokal
	Address2 Pt;
	boolean found;
	//Algoritma
	if (IsEmptyPlayer(Pl))
	{
		return Nil;
	}
	else
	{
		Pt=Cur(Pl);
		found=false;
		while ((Next(Pt)!=Cur(Pl)) && (!found))
		{
			if (Info(Pt).id==playerid)
			{
				found=true;
			}
			else
			{
				Pt=Next(Pt);
			}
		}
		if (Info(Pt).id==playerid)
		{
			return Pt;
		}
		else
		{
			return Nil;
		}
	}
}

void PrintPlayerStatus(ListOfPlayer Pl)
/* Print semua status pemain. */
{
	//Kamus Lokal
	Address2 P;
	int i;
	//Algoritma
	P=Cur(Pl);
	if (P!=Nil)
	{
		for(;;)
		{
			printf("%c\n",Info(P).id);
			printf("Uang : %d\n",Info(P).uang);
			for (i=0;i<4;i++)
			{
				printf("Kartu Chance %d : %d\n",i+1,Info(P).chance[i]);
			}
			printf("Dipenjara ? %c\n",Info(P).injail);
			printf("Sudah putar dadu ? %c\n",Info(P).RolledDice);
			printf("Sudah beli ? %c\n",Info(P).Bought);
			printf("Sudah upgrade ? %c\n",Info(P).Upgraded);
			if (Next(P)==Cur(Pl))
			{
				break;
			}
			else
			{
				P=Next(P);
			}
		}
	}
}
