/* Nama File : board.c */
/* File Body dari header board.h */

#include "board.h"

char filename[30];

/** Fungsi dan Prosedur Mengatur Board **/

/* Fungsi dan Prosedur Primitif */
void AlokasiPetak(Address1 *P,Infotype1 X)
/* Mengalokasikan tipe petak */
{
	//Kamus Lokal
	int i;
	//Algoritma
	*P = (Petak *) malloc((1)*sizeof(Petak));
	if (*P!=Nil)
	{
		//Memasukan Nama
		Info(*P).Nama=X.Nama;
		//Memasukan Harga
		Info(*P).Harga=X.Harga;
		//Memasukan Pemilik
		Info(*P).Pemilik=X.Pemilik;
		//Memasukan Jenis Pemilik
		Info(*P).JenisPetak=X.JenisPetak;
		//Memasukan Data Level
		Info(*P).Level=X.Level;
		//Memasukan Status Mati Lampu
		Info(*P).MatiLampu=X.MatiLampu;
		//Memasukan Status Offered
		Info(*P).Offered=X.Offered;
		//Memasukan Status World Cup
		Info(*P).WorldCup=X.WorldCup;
		//Memasukan status ditempati oleh
		for (i=0;i<4;i++)
		{
			Info(*P).WhoInHere[i]=X.WhoInHere[i];
		}
		Next(*P)=Nil;
	}
}

void DealokasiBoard(Address1 *P)
/* Menghapus elemen petak dan mengembalikan memori ke sistem */
{
	//Kamus Lokal
	
	//Algoritma
	free(*P);
}

void CreateEmptyBoard(Board *B)
/* Membuat board kosong */
{
	//Kamus Lokal
	
	//Algoritma
	Start(*B)=Nil;
}

boolean IsEmptyBoard(Board B)
/* Pengecekan apakah board kosong */
{
	//Kamus Lokal
	
	//Algoritma
	if (Start(B)==Nil)
	{
		return true;
	}
	else 
	{
		return false;
	}
}

Address1 LastBoard(Board B)
/* Mencari alamat terakhir Board */
{
	//Kamus Lokal
	Address1 P;
	//Algoritma
	if (IsEmptyBoard(B))
	{
		return Nil;
	}
	else
	{
		P=Start(B);
		while (Next(P)!=Start(B))
		{
			P=Next(P);
		}
	}
	return P;	
}

void LoadBoard(Board *B,char fileinput[])
/* Membaca data Board melalui file lalu disimpan dalam memori. */
{
	//Kamus Lokal
	Address1 P,Prec;
	Infotype1 X;
	int i;
	//Algoritma
	strcpy(filename,fileinput);
	STARTKATA();
	CreateEmptyBoard(B);
	while (!EndKata)
	{
		X.Nama=CopyKata(CKata);
		ADVKATA();
		ADVKATA();
		//Memasukan Harga
		X.Harga=ConvertToBilangan(CKata);
		ADVKATA();
		ADVKATA();
		//Memasukan Pemilik
		X.Pemilik=CKata.TabKata[0];
		ADVKATA();
		ADVKATA();
		//Memasukan Jenis Pemilik
		X.JenisPetak=CKata.TabKata[0];
		ADVKATA();
		ADVKATA();
		//Memasukan Data Level
		X.Level=ConvertToBilangan(CKata);
		ADVKATA();
		ADVKATA();
		//Memasukan Status Mati Lampu
		X.MatiLampu=CKata.TabKata[0];
		ADVKATA();
		ADVKATA();
		//Memasukan Status Offered
		X.Offered=CKata.TabKata[0];
		ADVKATA();
		ADVKATA();
		//Memasukan Status World Cup
		X.WorldCup=CKata.TabKata[0];
		//Memasukan status ditempati oleh
		for (i=0;i<4;i++)
		{
			ADVKATA();
			ADVKATA();
			X.WhoInHere[i]=CKata.TabKata[0];
		}
		//Alokasi Address1
		AlokasiPetak(&P,X);
		if (P!=Nil)
		{
			if (Start(*B)==Nil)
			{
				//Insert First
				Start(*B)=P;
				Next(P)=Start(*B);
				Prec=P;
			}
			else
			{
				//Insert After
				Next(Prec)=P;
				Next(P)=Start(*B);
				Prec=P;
			}
		}
		ADVKATA();
	}
}

void SaveBoard(Board B,char fileinput[])
/* Menyimpan data Board ke dalam file. */
{
	//Kamus
	char filename1[40];
	Address1 P;
	int i;
	//Membuka file
	strcpy(filename1,"../data/");
	strcat(filename1,fileinput);
	//Membuat file baru
	FILE *fp = fopen(filename1,"w+");
	//Algoritma
	if (!IsEmptyBoard(B))
	{
		P=Start(B);
		for (;;)
		{
			for (i=0;i<Info(P).Nama.Length;i++)
			{
				if (Info(P).Nama.TabKata[i]==' ')
				{
					fprintf(fp,"_");
				}
				else
				{
					fprintf(fp,"%c",Info(P).Nama.TabKata[i]);
				}
			}
			fprintf(fp," | ");
			fprintf(fp,"%d",Info(P).Harga);
			fprintf(fp," | ");
			fprintf(fp,"%c",Info(P).Pemilik);
			fprintf(fp," | ");
			fprintf(fp,"%c",Info(P).JenisPetak);
			fprintf(fp," | ");
			fprintf(fp,"%d",Info(P).Level);
			fprintf(fp," | ");
			fprintf(fp,"%c",Info(P).MatiLampu);
			fprintf(fp," | ");
			fprintf(fp,"%c",Info(P).Offered);
			fprintf(fp," | ");
			fprintf(fp,"%c",Info(P).WorldCup);
			for (i=0;i<4;i++)
			{
				fprintf(fp," | ");				
				fprintf(fp,"%c",Info(P).WhoInHere[i]);
			}
			fprintf(fp,"\n");
			if (Next(P)==Start(B))
			{
				break;
			}
			else
			{
				P=Next(P);
			}
		}
				}
	//Memberikan MARK
	fprintf(fp," .");
	//Menutup file
	fclose(fp);	
}

void DeleteAllBoard(Board *B)
/* Menghapus semua petak dalam Board. */
{
	//Kamus Lokal
	Address1 P,Pdel,PLast,P2;
	//Algoritma
	
	if(Start(*B)!=Nil)
	{
		P=Start(*B);
		while (Next(P)!=Start(*B))
		{
			//Delete First
			Pdel=P;
			P2=Next(Start(*B));
			PLast=LastBoard(*B);
			Next(PLast)=P2;
			Next(Start(*B))=Nil;
			Start(*B)=P2;
			P=Start(*B);
			DealokasiBoard(&Pdel);
		}
		//Elemen terakhir - sisa 1 elemen
		Pdel=Start(*B);
		DealokasiBoard(&Pdel);
		Start(*B)=Nil;
	}	
}

/** ============================================= **/
/* Fungsi dan Prosedur Tambahan */
Address1 SearchPetak(Board B,Kata NamaPetak)
{
	Address1 P;
	boolean found;
	if (IsEmptyBoard(B))
	{
		return Nil;
	}
	else
	{
		P=Start(B);
		found=false;
		while ((Next(P)!=Start(B))&&(!found))
		{
			if(IsKataSama(Info(P).Nama,NamaPetak))
			{
				found=true;
			}
			else
			{
				P=Next(P);
			}
		}
		if (IsKataSama(Info(P).Nama,NamaPetak))
		{
			return P;
		}
		else
		{
			return Nil;
		}
	}
}

void InfoPetak(Board B,Kata NamaPetak)
/*  I.S. : B dan Nama terdefinisi.
    F.S. : Informasi mengenai harga jual petak atau properti */
{
	//Kamus
	Address1 P;
    int Sewa, BiayaAlih, BiayaUpgrade;
    
    //Algoritma
    //Inisialisasi
    Sewa=0;
    BiayaAlih=0;
    BiayaUpgrade=0;

    P = SearchPetak(B,NamaPetak);
    if (P!=Nil)
    /* Petak ditemukan, maka informasi petak akan ditampilkan ke layar */
    {
        if (Harga(P) != -999)
        /* Petak dapat dibeli */
        {
            if (Pemilik(P) != 'N')
            /* Petak merupakan suatu kota */
            {
                if ((JenisPetak(P) == 'K') && (Level(P) < 5))
                /* kota sudah memiliki pemilik tetapi bisa diambil alih karena belum berstatus Landmark */
                {
                    Sewa = HargaSewa(P);         //biaya sewa = 20% harga petak saat itu
                    BiayaUpgrade = HargaUpgrade(P);  //biaya upgrade = 80% harga petak saat itu
                    BiayaAlih = HargaSellOffered(P);     //biaya alih = 120% harga petak saat itu
                    PrintKata(NamaPetak);
                    printf(", pemilik properti %c, bangungan level %d\n", Info(P).Pemilik, Info(P).Level);
                    printf("Biaya sewa: %dK\n", Sewa);
                    printf("Biaya ambil alih: %dK\n", BiayaAlih);
                    printf("Biaya upgrade bangunan: %dK\n", BiayaUpgrade);
                }
                else if ((JenisPetak(P) == 'K') && (Level(P)==5))
				/* Kota tidak dapat dibeli karena sudah berstatus Landmark */
				{
					PrintKata(NamaPetak);
					printf("\n");
					printf("Pemilik properti: %c\n", Pemilik(P));
					printf("Level Bangunan: Landmark\n");
					printf("Harga sewa : %dK\n",HargaSewa(P));
					printf("Anda tidak bisa membeli bangunan ini.\n");
				}
				else if (JenisPetak(P) == 'P')
                /* Petak adalah tempat pariwisata */
                {
                    PrintKata(NamaPetak);
                    printf("\n");
                    printf("Pemilik properti: %c\n", Pemilik(P));
                    BiayaAlih = HargaSellOffered(P);     //biaya alih = 120% harga petak saat itu
                    printf("Biaya ambil alih: %dK\n", BiayaAlih);
                }
            }
            else
            /* Info(P).Pemilik == N. Petak belum memiliki pemilik */
            {
                PrintKata(NamaPetak);
                printf("\n");
                printf("Harga petak: %dK\n", Harga(P));
            }
        }
        else
        /* Info(P).Harga == -999. Petak tidak dapat dibeli */
        {
            /* Bukan petak untuk dijual */
            PrintKata(NamaPetak);
            printf("\n");
        }
    }
    else
    /* P == Nil. Address tidak ditemukan */
    {
        printf("Nama petak/properti tidak ditemukan.\n");
    }

}

void PrintBoard(Board B)
/* Print Board untuk Pengetesan */
{
	//Kamus
	Address1 P;
	int i,j;
	//Algoritma
	P=Start(B);
	if (!IsEmptyBoard(B))
	{
		i=1;
		for (;;)
		{
			printf("%d. ",i);PrintKata(Info(P).Nama);
			printf("\n");
			printf("Harga : %dK\n",Harga(P));
			printf("Pemilik : Player %c\n",Pemilik(P));
			printf("Level : %d\n",Level(P));
			for (j=0;j<4;j++)
			{			
				printf("%c ",Info(P).WhoInHere[j]);
			}
			printf("\n");
			printf("\n");
			if (Next(P)==Start(B))
			{
				break;
			}
			else
			{
				P=Next(P);
				i++;
			}
		}
	}
}

int NbElmtPetak(Board B)
//Jumlah Petak
{
	Address1 P;
	int count;
	count=0;
	if (IsEmptyBoard(B))
	{
		return 0;
	}
	else
	{
		P=Start(B);
		for(;;)
		{
			count++;
			if (Next(P)==Start(B))
			{
				break;
			}
			else
			{
				P=Next(P);
			}
		}
		return count;
	}
	
}

Address1 SearchPrec(Board B,Address1 P)
//Mencari alamat sebelum P
{
	Address1 Pt;
	boolean found;
	
	if(IsEmptyBoard(B))
	{
		return Nil;
	}
	else
	{
		Pt=Start(B);
		found=false;
		do
		{
			if (Next(Pt)==P)
			{
				found=true;
			} else
			{
				Pt=Next(Pt);
			}
		}
		while((Next(Pt)!=Start(B))&&(!found));
		if (found)
		{
			return Pt;
		}
		else
		{
			return Nil;
		}
	}
}

void ShowBoard(Board B)
//Menampilkan keadaan board saat ini
{
	//Kamus
	int i,j; //untuk traversal
	int total,baris,kolom; //konstan
	int totalisi; //konstan
	int space,spkiri,spkanan;	
	Address1 P,PL,P3;
	
	//Algoritma
	if (IsEmptyBoard(B))
	{
		printf("Board Kosong.\n");
	}
	else
	{
		//Inisialisasi Kotak Global
		totalisi=17;
		total=NbElmtPetak(B);
		//Inisialisasi Baris dan Kolom
		baris = total / 4 + 1;
		kolom = baris - 2;
		/* Cetak satu baris nama */
		PrintPenutup(totalisi*baris+(baris+1));
		printf("\n");
		P=Start(B);
		for (i=1;i<=baris;i++)
		{
			space = totalisi - Info(P).Nama.Length;
			spkiri = space/2;
			spkanan = space - spkiri;
			printf("|");
			PrintSpasi(spkiri);
			PrintKata(Info(P).Nama);
			PrintSpasi(spkanan);
			P=Next(P);
		}
		printf("|\n");
		/* Cetak Baris Harga */
		P=Start(B);
		for (i=1;i<=baris;i++)
		{
			if (Harga(P)==-999)
			{
				printf("|");
				PrintSpasi(totalisi);
			}
			else
			{
				space = totalisi - (JumlahBilangan(Harga(P))+1);
				spkiri = space/2;
				spkanan = space - spkiri;
				printf("|");
				PrintSpasi(spkiri);
				printf("%dK",Harga(P));
				PrintSpasi(spkanan);
			}
			P=Next(P);
		}
		printf("|\n");
		/* Cetak Baris Pemilik dan Level */
		P=Start(B);
		for (i=1;i<=baris;i++)
		{
			if (Pemilik(P)=='N')
			{
				printf("|");
				PrintSpasi(totalisi);
			}
			else
			{
				space = totalisi - 2;
				spkiri = space/2;
				spkanan = space - spkiri;
				printf("|");
				PrintSpasi(spkiri);
				printf("%c%d",Pemilik(P),Level(P));
				PrintSpasi(spkanan);
			}
			P=Next(P);
		}
		printf("|\n");
		/* Print Penempat */
		P=Start(B);
		for (i=1;i<=baris;i++)
		{
			if (IsEmptyPenempat(P))
			{
				printf("|");
				PrintSpasi(totalisi);
			}
			else
			{
				space = totalisi - (2*(TotalPenempat(P)));
				spkiri = space/2;
				spkanan = space - spkiri;
				printf("|");
				PrintSpasi(spkiri);
				PrintPenempat(P);
				PrintSpasi(spkanan);
			}
			P=Next(P);
		}
		printf("|\n");
		//Tutup Baris 1
		PrintPenutup(totalisi*baris+(baris+1));
		printf("\n");
		
		/* Cetak baris per baris beda kolom */
		P3=P;
		PL=LastBoard(B);
		for(j=i;j<kolom+i;j++)
		{
			//Awal
			PrintPenutup(totalisi+2);
			//Pengantar
			PrintSpasi((baris-2)*totalisi+(baris-4)+1); //Ruang Space
			PrintPenutup(totalisi+2);
			printf("\n");
			//Cetak Nama Kiri
			space = totalisi - Info(PL).Nama.Length;
			spkiri = space/2;
			spkanan = space - spkiri;
			printf("|");
			PrintSpasi(spkiri);
			PrintKata(Info(PL).Nama);
			PrintSpasi(spkanan);
			printf("|");
			//Pengantar
			PrintSpasi((baris-2)*totalisi+(baris-4)+1); //Ruang Space
			//Cetak Nama Kanan
			space = totalisi - Info(P).Nama.Length;
			spkiri = space/2;
			spkanan = space - spkiri;
			printf("|");
			PrintSpasi(spkiri);
			PrintKata(Info(P).Nama);
			PrintSpasi(spkanan);
			printf("|\n");
			//Cetak Harga Kiri
			if (Harga(PL)==-999)
			{
				printf("|");
				PrintSpasi(totalisi);
				printf("|");
			}
			else
			{
				space = totalisi - (JumlahBilangan(Harga(PL))+1);
				spkiri = space/2;
				spkanan = space - spkiri;
				printf("|");
				PrintSpasi(spkiri);
				printf("%dK",Harga(PL));
				PrintSpasi(spkanan);
				printf("|");
			}
			//Pengantar
			PrintSpasi((baris-2)*totalisi+(baris-4)+1); //Ruang Space
			//Cetak Harga Kanan
			if (Harga(P)==-999)
			{
				printf("|");
				PrintSpasi(totalisi);
				printf("|\n");
			}
			else
			{
				space = totalisi - (JumlahBilangan(Harga(P))+1);
				spkiri = space/2;
				spkanan = space - spkiri;
				printf("|");
				PrintSpasi(spkiri);
				printf("%dK",Harga(P));
				PrintSpasi(spkanan);
				printf("|\n");
			}
			//Cetak Pemilik Kiri
			if (Pemilik(PL)=='N')
			{
				printf("|");
				PrintSpasi(totalisi);
				printf("|");
			}
			else
			{
				space = totalisi - 2;
				spkiri = space/2;
				spkanan = space - spkiri;
				printf("|");
				PrintSpasi(spkiri);
				printf("%c%d",Pemilik(PL),Level(PL));
				PrintSpasi(spkanan);
				printf("|");
			}
			//Pengantar
			PrintSpasi((baris-2)*totalisi+(baris-4)+1); //Ruang Space
			//Cetak Pemilik Kanan
			if (Pemilik(P)=='N')
			{
				printf("|");
				PrintSpasi(totalisi);
				printf("|\n");
			}
			else
			{
				space = totalisi - 2;
				spkiri = space/2;
				spkanan = space - spkiri;
				printf("|");
				PrintSpasi(spkiri);
				printf("%c%d",Pemilik(P),Level(P));
				PrintSpasi(spkanan);
				printf("|\n");
			}
			//Cetak Penempat Kiri
			if (IsEmptyPenempat(PL))
			{
				printf("|");
				PrintSpasi(totalisi);
				printf("|");
			}
			else
			{
				space = totalisi - (2*(TotalPenempat(PL)));
				spkiri = space/2;
				spkanan = space - spkiri;
				printf("|");
				PrintSpasi(spkiri);
				PrintPenempat(PL);
				PrintSpasi(spkanan);
				printf("|");
			}
			//Pengantar
			PrintSpasi((baris-2)*totalisi+(baris-4)+1); //Ruang Space
			//Cetak Penempat Kanan
			if (IsEmptyPenempat(P))
			{
				printf("|");
				PrintSpasi(totalisi);
				printf("|\n");
			}
			else
			{
				space = totalisi - (2*(TotalPenempat(P)));
				spkiri = space/2;
				spkanan = space - spkiri;
				printf("|");
				PrintSpasi(spkiri);
				PrintPenempat(P);
				PrintSpasi(spkanan);
				printf("|\n");
			}
			
			//Next
			PL = SearchPrec(B,PL);
			//Next
			P=Next(P);
		}
		//Tutup
		PrintPenutup(totalisi*baris+(baris+1));
		printf("\n");
		
		/* Cetak Baris Terakhir */
		P3=PL;
		for (i=j+baris-1;i>=j;i--)
		{
			space = totalisi - Info(PL).Nama.Length;
			spkiri = space/2;
			spkanan = space - spkiri;
			printf("|");
			PrintSpasi(spkiri);
			PrintKata(Info(PL).Nama);
			PrintSpasi(spkanan);
			PL=SearchPrec(B,PL);
		}
		printf("|\n");
		//Cetak Harga
		PL=P3;
		for (i=1;i<=baris;i++)
		{
			if (Harga(PL)==-999)
			{
				printf("|");
				PrintSpasi(totalisi);
			}
			else
			{
				space = totalisi - (JumlahBilangan(Harga(PL))+1);
				spkiri = space/2;
				spkanan = space - spkiri;
				printf("|");
				PrintSpasi(spkiri);
				printf("%dK",Harga(PL));
				PrintSpasi(spkanan);
			}
			PL=SearchPrec(B,PL);
		}
		printf("|\n");
		//Cetak Pemilik dan Level
		/* Cetak Baris Pemilik dan Level */
		PL=P3;
		for (i=1;i<=baris;i++)
		{
			if (Pemilik(PL)=='N')
			{
				printf("|");
				PrintSpasi(totalisi);
			}
			else
			{
				space = totalisi - 2;
				spkiri = space/2;
				spkanan = space - spkiri;
				printf("|");
				PrintSpasi(spkiri);
				printf("%c%d",Pemilik(PL),Level(PL));
				PrintSpasi(spkanan);
			}
			PL=SearchPrec(B,PL);
		}
		printf("|\n");
		//Cetak Penempat
		PL=P3;
		for (i=1;i<=baris;i++)
		{
			if (IsEmptyPenempat(PL))
			{
				printf("|");
				PrintSpasi(totalisi);
			}
			else
			{
				space = totalisi - (2*(TotalPenempat(PL)));
				spkiri = space/2;
				spkanan = space - spkiri;
				printf("|");
				PrintSpasi(spkiri);
				PrintPenempat(PL);
				PrintSpasi(spkanan);
			}
			PL=SearchPrec(B,PL);
		}
		printf("|\n");
		//Tutup
		PrintPenutup(totalisi*baris+(baris+1));
		printf("\n");
	}
}

/* Prosedur Bantuan Show Board */
void PrintSpasi(int n)
/* Mencetak spasi sejumlah n*/
{
	int i;
	for (i=1;i<=n;i++)
	{
		printf(" ");
	}
}

void PrintPenutup(int n)
/* Mencetak simbol _ */
{
	int i;
	for (i=1;i<=n;i++)
	{
		printf("-");
	}
}

int JumlahBilangan(int N)
/* Mendapatkan jumlah bilangan, contoh : 10 = 2, 1 = 1, 300 = 3*/
{
	if (N<10)
	{
		return 1;
	}
	else
	{
		return 1+JumlahBilangan(N/10);
	}
}

boolean IsEmptyPenempat(Address1 P)
//Mengecek apakah ada yang menempati suatu board
{
	//Kamus
	boolean found;
	int i;
	i=0;
	//Algoritma
	found=false;
	while ((i<=3)&&(!found))
	{
		if (Info(P).WhoInHere[i]!='N')
		{
			found=true;
		}
		else
		{
			i++;
		}
	}
	if (found)
	{
		return false;
	}
	else
	{
		return true;
	}
}

int TotalPenempat(Address1 P)
//Menentukan jumlah penempat
{
	//Kamus
	int count;
	int i;
	//Algoritma
	i=0;
	count=0;
	for (i=0;i<=3;i++)
	{
		if (Info(P).WhoInHere[i]!='N')
		{
			count++;
		}
	}
	return count;
}

void PrintPenempat(Address1 P)
//Mencetak Penempat Yang Ada
{
	//Kamus
	//Kamus
	int i;
	//Algoritma
	i=0;
	for (i=0;i<=3;i++)
	{
		if (Info(P).WhoInHere[i]!='N')
		{
			printf("%c ",Info(P).WhoInHere[i]);
		}
	}
}

int HargaUpgrade(Address1 P)
//Menghasilkan harga upgrade
{
	int sum = Harga(P) * (Level(P)+1); 
	return sum;
}

int HargaSewa(Address1 P)
//Menghasilkan harga sewa
{
	int sum = (Harga(P) * Level(P))/10;
	if (WorldCup(P))
	{
		return sum*2;
	}
	else if (MatiLampu(P))
	{
		return 0;
	}
	else
	{
		return sum;
	}
}

int HargaSellBank(Address1 P)
//Menghasilkan harga jual ke Bank
{
	int sum=HargaSellOffered(P)*9/10;
	return sum;
}

int HargaSellOffered(Address1 P)
//Menghasilkan harga jual ke pembeli
{
	int sum = Harga(P) + (Harga(P) * Level(P));
	return sum;
}

int HargaRebut(Address1 P)
//Menghasilkan harga rebut
{
	int sum =  HargaSellOffered(P) * 2;
	return sum;
}
