/* Nama File : game.c */
/* File body dari header game.h */

#include "game.h"

/* Fungsi dan Prosedur Utama */
/** Pergerakan Pemain **/
void RollDice(Board B,Chance C,ListOfPlayer Pl, Address1 *Position)
/* Gulirkan Dadumu */
{
	int dice1,dice2,total;
	int i;
	Address1 P;
	
	if (Injail(Cur(Pl))==0)
	{
		P = *Position;
		
		dice1 = RandomRange(1,6);
		dice2 = RandomRange(1,6);
		
		total = dice1+dice2;
		
		for (i=1;i<=total;i++)
		{
			*Position=Next(*Position);
			//Beberapa Command Otomatis Saat Melewati Petak Tertentu
			if (IsKataSama(Info(*Position).Nama,StringToKata("Start")))
			{
				Uang(Cur(Pl))=Uang(Cur(Pl))+1000; //Nambah yey
				printf("Anda telah melewati Start.\n");
				printf("Anda mendapat uang sebesar 1M\n");
				ResetLampu(Pl,B);
			}
			if (IsKataSama(Info(*Position).Nama,StringToKata("World Cup")))
			{
				ResetWorldCup(Pl,B);
			}
		}
		
		DeletePlayerPosition(Pl,P);
		PlacePlayer(Pl,*Position);
		
		//Output Command
		printf("> %d + %d = %d\n",dice1,dice2,total);
		printf("  Player %c sampai di ",Id(Cur(Pl))); PrintKata(Info(*Position).Nama); printf("\n");
		printf("\n");
		
		//Check for autocommand
		AutoCommand(*Position,B,Pl,C);
	}
	else
	{
		printf("Maaf Anda sedang dipenjara!\n");
	}
}

/** Berhubungan dengan Petak dan Pemain **/
void ShowOffered(Board B)
//Menampilkan yang sedang dijual saat ini
{
	Address1 P;
	P=Start(B);
	int count;
	count=0;
	for(;;)
	{
		if (Info(P).Offered=='T')
		{
			printf("> ");
			PrintKata(Info(P).Nama);
			printf(", ");
			printf("harga ");PrintUang(HargaSellOffered(P));printf("\n");
			count++;
		}	
		if (Next(P)==Start(B))
		{
			break;
		}
		else
		{
			P=Next(P);
		}
	}
	if (count==0)
	{
		printf("Maaf tidak ada yang dimasukan dalam list offered.\n");
	}
}

void UpgradeHouse(Board B, ListOfPlayer Pl, Kata NamaPetak)
/*  I.S. : B, NamaPetak, dan Pl terdefinisi.
    F.S. : Level bangunan yang sedang ditempati terupgrade.
           Update Board jika bangunan berhasil diupgrade. */
{
    //Kamus
    Address2 P2;
    Address1 P;
    int BiayaUpgrade;
    
    //Algoritma
    BiayaUpgrade=0;

    P2 = Cur(Pl);
    /* mencari alamat petak yang dimaksud */
    P = SearchPetak(B,NamaPetak);
    /* petak selalu ditemukan */
    if (Info(P).JenisPetak == 'K')
    /* upgrade hanya bisa dilakukan jika Info(P) == K */
    {
        if (Info(P).Pemilik == Info(P2).id)
        {
			if (Info(P).Level < 4)
			/* Level bangunan biasa 1-3 */
			{
				BiayaUpgrade = HargaUpgrade(P);
				if(Uang(P2)<BiayaUpgrade){
					printf("Uangmu tidak cukup untuk upgrade kota ini.\n");
				} else {
					Info(P2).uang = Info(P2).uang - BiayaUpgrade;
					Info(P).Level = Info(P).Level + 1;
					Info(P).Harga = Info(P).Harga + BiayaUpgrade;
					printf("Selamat kini bangunanmu di ");
					PrintKata(NamaPetak);
					printf(" memiliki level %d!\n", Info(P).Level);
					printf("Sisa uangmu: "); PrintUang(Uang(P2));printf("\n");
				}
			}
			else if (Info(P).Level == 4)
			/* Jika level 4 -> 5. Bangunan menjadi Landmark */
			{
				BiayaUpgrade = HargaUpgrade(P) + (HargaUpgrade(P) * 10 / 100);
				if(Uang(P2)<BiayaUpgrade){
					printf("Uangmu tidak cukup untuk upgrade kota ini.\n");
				} else {
					Info(P2).uang = Info(P2).uang - BiayaUpgrade;
					Info(P).Level = Info(P).Level + 1;
					printf("Selamat kini bangunanmu di ");
					PrintKata(NamaPetak);
					printf(" menjadi sebuah Landmark.\n");
					printf("Sisa uangmu: "); PrintUang(Uang(P2));printf("\n");
				}
			}
		}
		else
		{
			printf("> Maaf bukan milik Anda.\n");
		}
    }
    else
    {
        printf("Anda tidak bisa melakukan upgrade house disini!\n");
    } 
}

//Membeli itu menyenangkan
void Buy(Board B,ListOfPlayer Pl,Kata NamaPetak)
/*I.S Player Terdefinisi dan Player pada suatu posisi di Map*/ 
/*F.S Jika uang player cukup maka player membeli petak pada map 
 * 	  jika uangnya tidak cukup maka player tidak bisa membeli petak tersebut*/
{
	//Kamus
	Address1 P;
	Address2 Player1;
	Address2 Player2;
	
	//Algoritma
	P = SearchPetak(B,NamaPetak);
	Player1 = Cur(Pl);
	
	if(JenisPetak(P)!='N'){	//Masuk ke fungsi Buy
		if(Pemilik(P)=='N'){
			if(Uang(Player1)<Harga(P)){
				printf("Uangmu tidak cukup untuk membeli kota ini.\n");
			}else{
				Pemilik(P) = Info(Player1).id;
				Uang(Player1) = Uang(Player1) - Harga(P);
				printf("> Selamat, kota ");
				PrintKata(NamaPetak);
				printf(" kini menjadi milikmu!\n");
				Level(P)++;
				printf("> Level bangunan %d\n", Level(P));
				printf("> Sisa uangmu: ");PrintUang(Uang(Player1));printf("\n");
				printf("> Player %c", Info(Player1).id);
				printf(" mendapatkan hasil penjualan sebesar "); PrintUang(Harga(P)); printf("\n");
			}
		}
		else if (Pemilik(P)==Info(Player1).id)
		{
			printf("Lokasi ini sudah milik Anda.\n");
		}
		else //Rebut miliki pemain lain
		{
			if((Level(P)!=5) && (JenisPetak(P)=='K'))
			{
				Player2=SearchPlayer(Pl,Pemilik(P));
				if (Uang(Player1)>=HargaRebut(P))
				{
					Uang(Player1) = Uang(Player1) - HargaRebut(P);
					Uang(Player2) = Uang(Player2) + HargaRebut(P);
					printf("> Kota ");PrintKata(NamaPetak);printf(" telah direbut player %c dari player %c.\n",Id(Player1),Id(Player2));
					Pemilik(P)=Id(Player1);
					printf("Dengan harga : ");PrintUang(HargaRebut(P));printf("\n");
				}
				else
				{
					printf("Uang Anda tidak mencukupi.\n");
				}
			}
			else
			{
				printf("Petak ini tidak dapat direbut.\n");
			}
		}
	}
	else
	{
		printf("> Petak yang Anda tempati tidak dapat dibeli.\n");
	}
}

void BuyOffered(Board B, ListOfPlayer Pl, Kata NamaPetak)
/*  I.S. : M, Pl, dan Nama terdefinisi.
    F.S. : Membeli petak dari list Offered. Petak yang sudah dibeli, dikeluarkan daripetak list offered */
{
    Address1 P;
    Address2 P2;
    Address2 Owner;
    int BiayaAlih;

    P2 = Cur(Pl);
    P=SearchPetak(B,NamaPetak);

	if (P!=Nil)
	{
		if (Info(P).Offered == 'T') {
			if (Info(P).Pemilik!=Id(Cur(Pl)))
			{	
				BiayaAlih = HargaSellOffered(P);
				if (Info(P2).uang >= BiayaAlih) {
					Info(P2).uang = Info(P2).uang - BiayaAlih;
					Owner=SearchPlayer(Pl,Info(P).Pemilik);
					Info(Owner).uang = Info(Owner).uang + BiayaAlih;
					Info(P).Pemilik = Info(P2).id;
					Info(P).Offered = 'F';
					PrintKata(NamaPetak);
					printf(" sekarang menjadi milikmu.\n");
					printf("Sisa uangmu ");PrintUang(Uang(P2));printf("\n");
				}
				else
				{
					printf("Uangmu tidak cukup untuk melakukan pembelian.\n");
				}
			}
			else
			{
				printf("Maaf ini sudah milik Anda.\n");
			}
		}
		else
		{
			printf("Maaf nama yang Anda masukan bukan dalam List Offered\n");
		}
	}
	else
	{
		printf("Nama yang Anda masukan tidak ada di petak.\n");
	}
}

//Menjual itu dibutuhkan
void SellKotaOffered(Board B,ListOfPlayer Pl,Kata NamaPetak)
{
	//KAMUS LOKAL
	Address1 P;
	//ALGORITMA;
	P = SearchPetak(B,NamaPetak);
	if(P != Nil) {
		if (Info(P).Pemilik==Info(Cur(Pl)).id)
		{
			Info(P).Offered = 'T';
			printf("> ");
			PrintKata(NamaPetak);
			printf(" dimasukkan ke list penjualan. Jika ");
			PrintKata(NamaPetak);
			printf(" terjual, kamu akan mendapat uang hasil penjualan.\n");
		}
		else
		{
			printf("> Maaf petak tersebut bukan milik anda.\n");
		}
	}
	else
	{
		printf("> Petak yang anda inginkan tidak ditemukan.\n");
	}
}

void SellKotaBank(Board B,ListOfPlayer Pl,Kata NamaPetak){
	//KAMUS LOKAL
	Address1 P;
	int HargaJual;
	//ALGORITMA
	P = SearchPetak(B,NamaPetak);
	if(P!=Nil) {
		if (Info(Cur(Pl)).id==Info(P).Pemilik)
		{
			HargaJual = HargaSellBank(P); //Silahkan tentukan harga jual sebaiknya bagaimana
			Info(Cur(Pl)).uang = Info(Cur(Pl)).uang + HargaJual; //Harga tidak sama dengan harga jual
			Info(P).Pemilik = 'N';
			Info(P).Offered = 'F';
			Info(P).WorldCup= 'F';
			Info(P).Level = 0;
			printf("> ");
			PrintKata(NamaPetak);
			printf(" dijual ke bank dengan harga ");PrintUang(HargaJual);printf("\n");
			printf("> Uangmu sekarang ");PrintUang(Uang(Cur(Pl)));printf("\n");
		}
		else
		{
			printf("> Maaf petak tersebut bukan milik Anda.\n");
		}
	}
	else
	{
		printf("Maaf petak yang anda inginkan tidak ditemukan.");
	}
}

/** Prosedur dan Fungsi Khusus Di Petak Tertentu **/
void Host(ListOfPlayer Pl,Address1 P)
{
	if (P!=Nil)
	{
		if ((JenisPetak(P)!='N') && (Pemilik(P)==Id(Cur(Pl))))
		{
			WorldCup(P)=Id(Cur(Pl));
			printf("> ");PrintKata(Info(P).Nama);
			printf(" menjadi host World Cup. Uang sewa di ");
			PrintKata(Info(P).Nama);
			printf(" menjadi ");PrintUang(HargaSewa(P));printf(".\n");
		}
		else
		{
			printf("> Tidak dapat dijadikan host.\n");
		}
	}
	else
	{
		printf("Maaf petak yang anda inginkan tidak ada.\n");
	}
}

void Travel(Board B,ListOfPlayer Pl,Address1 Location)
{
	if (Location==Nil)
	{
		printf("> Maaf lokasi yang Anda inginkan tidak ditemukan!\n");
		printf("> Posisi Anda tetap di World Travel!\n");
	}
	else
	{
		PlacePlayer(Pl,Location);
		DeletePlayerPosition(Pl,SearchPetak(B,StringToKata("World Travel")));
		printf("> Player %c sampai ",Id(Cur(Pl)));
		PrintKata(Info(Location).Nama);
		printf("\n");
	}
}

void GetBonus(ListOfPlayer Pl)
/*I.S player masuk ke petak bonus*/
/*F.S Mendapatkan bonus berupa uang*/
{
	//Kamus
	Address2 P1;
	int Bonus;
	
	//Algoritma
	P1 = Cur(Pl);
	Bonus = RandomRange(100,1000);
	Uang(P1) = Uang(P1) + Bonus;
	printf("> Selamat, kamu mendapatkan ");PrintUang(Bonus);printf("\n");
	printf("> Uang kamu sekarang ");PrintUang(Uang(Cur(Pl)));printf("\n");
}

void RandomChance(Board B,Chance C,ListOfPlayer Pl)
/*I.S Player masuk ke petak chance*/
/*F.S Player mendapat salah satu dari kartu chance*/
{
	//Kamus
	int i;
	Address2 CP;
	CP=Cur(Pl);
	//Algoritma
	i = RandomRange(0,4);
	if (C.Tab[i]==1)
	{
		Info(CP).chance[0]++;
		printf("Selamat Anda mendapat kartu Chance Free Me.\n");
	}
	else if (C.Tab[i]==2)
	{
		Info(CP).chance[1]++;
		printf("Selamat Anda mendapat kartu Chance Free Tax.\n");
	} else if (C.Tab[i]==3)
	{
		Injail(CP) = 1;
		MasukPenjara(B,Pl);
		printf("Anda dipenjara.\n");
	} else if (C.Tab[i]==4)
	{
		Info(CP).chance[2]++;
		printf("Selamat Anda mendapat kartu Chance Off.\n");
	} else // 5
	{
		Info(CP).chance[3]++;
		printf("Selamat Anda mendapat kartu Chance Protect.\n");
	}
}

/** Gunakan Kartu Chance-mu **/
void FreeMe(ListOfPlayer Pl)
//Kartu Chance No 1
//Bebaskan dirimu
{
	Address2 P;
	P=Cur(Pl);
	if (Injail(P)=='T')
	{
		if (Info(P).chance[0]!=0)
		{
			Info(P).chance[0] = Info(P).chance[0] - 1;
			Injail(P) = 'F'; //Lepas dari penjara
			printf("Selamat Anda lepas dari Dessert Island.\n");
			printf("Sisa kartu chance Free Me Anda : %d buah.\n",Info(P).chance[0]);
		}
		else
		{
			printf("Maaf Anda tidak punya kartu Chance free me.\n");
		}
	}
	else 
	{
		printf("Anda sedang tidak dipenjara!\n");
	}
}

void FreeTax(ListOfPlayer Pl,Address1 PlayerPosition)
//Kartu Chance 2
//Lepaskan dari pajak yang membelit
{
	Address2 Pt;
	Address1 Pm;
	Pt=Cur(Pl);
	Pm=PlayerPosition;
	if (IsKataSama(Info(Pm).Nama,StringToKata("Tax")))
	{
		if (Info(Pt).chance[1]!=0)
		{
			Info(Pt).chance[1] = Info(Pt).chance[1] - 1;
			printf("Selamat Anda bebas dari pajak.\n");
			printf("Sisa kartu bebas pajak Anda : %d buah.\n",Info(Pt).chance[1]);
		}
		else
		{
			printf("Maaf Anda tidak punya kartu Chance freetax.\n");
		}
	}
	else
	{
		printf("Maaf Anda sedang tidak di petak Tax.\n");
	}
}

void Off(ListOfPlayer Pl,Address1 Pt,Address2 P)
//Mematikan lampu...
{
	Address2 P2;
	if (Info(P).chance[2]==0)
	{
		printf("Maaf anda belum mempunyai kartu ini.\n");
	}
	else
	{
		if ((JenisPetak(Pt)!='N') && (Pemilik(Pt)!='N') && (Pemilik(Pt)!= Id(P)))
		{
			printf("Kota ");PrintKata(Info(Pt).Nama);printf(" milik Player %c mati listrik.\n",Pemilik(Pt));
			printf("Biaya sewa di kota ");PrintKata(Info(Pt).Nama);printf(" = 0\n");
			MatiLampu(Pt) = 'M';
			P2 = SearchPlayer(Pl,Pemilik(Pt));
			if (Info(P2).chance[3]!=0)
			{
				printf("Player %c memiliki kartu perlindungan! Berhati-hatilah!\n",Id(P2));
			}
		}
		else
		{
			printf("Petak tersebut tidak dapat dimatikan lampunya.\n");
		}
	}
}

void Protect(Address2 P,Address1 Pt)
//Lindungi kota mu
{
	if (Info(P).chance[3]==0)
	{
		printf("Maaf anda belum mempunyai kartu ini.\n");
	}
	else
	{
		if ((MatiLampu(Pt)=='M'))
		{
			printf("Selamat Anda menghidupkan kembali lampu kota Anda.\n");
			MatiLampu(Pt)='H';
			Info(P).chance[3]= Info(P).chance[3] - 1;
			printf("Sisa kartu chance Protect Anda : %d buah.\n",Info(P).chance[4]);
		}
		else
		{
			printf("Maaf tempat yang Anda pilih sedang tidak mati lampu.\n");
		}
	}
}

/** Command Tambahan **/
void PayToFree(ListOfPlayer Pl)
//Membayar untuk keluar penjara
{
	Uang(Cur(Pl))= Uang(Cur(Pl)) - Uang(Cur(Pl)) * 10 / 100;
	printf("Uang anda terpotong 10 persen untuk keluar penjara.\n");
	Injail(Cur(Pl)) = 'F';
}

/** Menampilkan berbagai status **/
void Leaderboard(ListOfPlayer Pl, Board B)
/*I.S List Of Player Terdefinisi 
 *F.S Menampilkan leaderboard player dari yang paling kaya ke yang miskin*/
{
    //Kamus
    typedef struct {
		int Total;
		char id;
	} Aset;
    
    Aset Kekayaan[4];
    Address2 P;
    int max, i, j, k;
    char id;
     
    //Algoritma
    i = 1;
    P = Cur(Pl);
    for(;;){ //Memasukkan Total Kekayaan Seorang Player
        Kekayaan[i].Total = Uang(P) + totalAsset(B,P);
        Kekayaan[i].id = Id(P);
        if((Next(P) == Cur(Pl))||(i>=4)){
            break;
        }else{
            i++;
            P = Next(P);
        }
    }
    for(i=1; i<=4;i++){ //Sort All
        max = Kekayaan[i].Total;
        k = i;
        for(j=i; j<=4; j++){
            if(max<Kekayaan[j].Total){
                max = Kekayaan[j].Total;
                k = j;
            }
        }
        Kekayaan[k].Total=Kekayaan[i].Total;
        Kekayaan[i].Total=max;
        id = Kekayaan[k].id;
        Kekayaan[k].id = Kekayaan[i].id;
        Kekayaan[i].id = id;
    }
    for(i=1;i<=4;i++){
        printf("Player %c ", Kekayaan[i].id);
        PrintUang(Kekayaan[i].Total);printf("\n");
    }
}

/** Giliran Pemain Sudah Selesai **/
void EndTurn(ListOfPlayer *Pl)
//Mengakhiri giliran pemain
{
	//Kamus
	Address2 P;
	//Algoritma
	P=Cur(*Pl);
	//Reset Status Player
	RolledDice(P)='N';
	Bought(P)='N';
	Upgraded(P)='N';
	//Menambahkan kesempatan dalam penjara jika sedang dipenjara
	if (Injail(Cur(*Pl))>0)
	{
		Injail(Cur(*Pl))++;
	} else if (Injail(Cur(*Pl))==5)
	{
		PayToFree(*Pl);
		printf("Anda sudah membayar denda secara otomatis karena sudah tiga kesempatan di dalam penjara.\n");
		printf("Denda sebesar 10 persen dari uang Anda.\n");
	}
	//Mengganti Cur(*Pl) menjadi Next dari Cur(*Pl)
	//Next
	Cur(*Pl)=Next(P);
}

/* Fungsi dan Prosedur Tambahan */
/** Membantu Fungsi dan Prosedur Utama **/
int RandomRange(int min,int max)
/* Mendapatkan nilai random diantara min - max */
{
	//Kamus
	int random_number;
	//Algoritma
	random_number = rand();
	return((random_number % max) + min);
}

Address1 PlayerPlace(Board B,char id)
//Mencari letak player di Board
{
	Address1 P;
	int i;
	boolean found;
	
	P=Start(B);
	if (P!=Nil)
	{
		found = false;
		while ((Next(P)!=Start(B))&&(!found))
		{
			i=0;
			while ((i<5) && (!found))
			{
				if (Info(P).WhoInHere[i]==id)
				{
					found=true;
				}
				else
				{
					i++;
				}
			}
			if (!found)
			{
				P=Next(P);
			}
		}
	}
	return P;
}

/** Pengatur Antar Muka **/
void ShowPlayerStatus(Address2 Pl,Address1 Location)
/* Menampilkan Status Pemain */
{
	printf("\n");
	printf("Player %c turn.\n",Id(Pl));
	printf("Your Money : ");PrintUang(Uang(Pl));printf("\n");
	printf("Your position : ");PrintKata(Info(Location).Nama);printf("\n");
	printf("Status Anda : ");
	if (Injail(Pl)==0)
	{
		printf("Tidak Dipenjara.\n");
	}
	else
	{
		printf("Dipenjara.\n");
	}
	printf("---------------------------------------------------------\n");
}

void ShowWelcomeMessage()
/* Menampilkan Pesan Pembuka */
{
	printf("Selamat Datang di Let's Finish This!\n");
	printf("Untuk membaca data save anda gunakan command load <namafile>\n");
	printf("Untuk memulai gunakan command start\n");
	printf("========================================================\n");
	printf("\n");
}

void ERRORMESSAGE()
//Menampilkan pesan kesalahan
{
	printf("> Maaf perintah salah!\n");
}

void ShowHelp()
/* Menampilkan Antarmuka Bantuan */
{
	printf("Command yang tersedia : \n");
	printf("roll dice\n");
	printf("info <nama petak>\n");
	printf("buy\n");
	printf("sell <nama petak>\n");
	printf("sell bank <nama petak>\n");
	printf("show offered\n");
	printf("buy offered <nama petak>\n");
	printf("upgrade\n");
	printf("board\n");
	printf("leaderboard\n");
	printf("host <nama kota>\n");
	printf("travel <nama kota>\n");
	printf("end turn\n");
	printf("save <nama file>\n");
	printf("load <nama file>\n");
	printf("pay to free\n");
	printf("\n");
	printf("Perintah Tambahan menggunakan Chance :\n");
	printf("free me\n");
	printf("free tax\n");
	printf("off <namakota/tempatrekreasi\n");
	printf("protect <namakota/tempatrekreasi\n");
}

/** Mengatur Posisi Pemain dalam Petak **/
void DeletePlayerPosition(ListOfPlayer Pl,Address1 P)
{
	boolean done;
	int i;
	i=0;
	done=false;
	if (P!=Nil)
	{
		while ((i<4) && (!done))
		{
			if (Info(P).WhoInHere[i]==Id(Cur(Pl)))
			{
				Info(P).WhoInHere[i]='N';
				done=true;
			}
			else
			{
				i++;
			}
		}
	}
}

void PlacePlayer(ListOfPlayer Pl,Address1 P)
//Menaruh pemain
{
	boolean done;
	int i;
	i=0;
	done=false;
	if (P!=Nil)
	{
		while ((i<4) && (!done))
		{
			if (Info(P).WhoInHere[i]=='N')
			{
				Info(P).WhoInHere[i]=Info(Cur(Pl)).id;
				done=true;
			}
			else
			{
				i++;
			}
		}
	}
}

/** Mengatur State Game **/
void InisialisasiGame(ListOfPlayer *Pl,Board *B,Chance *C)
/* New Game Detected */
{
	CreateEmptyBoard(B);
	CreatePlayer(Pl);
	CreateEmptyChance(C);
	LoadBoard(B,"default-map.txt");
	LoadPlayerStatus(Pl,"default-player.txt");
	LoadChance(C,"default-chance.txt");
}

void CleanGame(ListOfPlayer *Pl,Board *B)
/* Clean the Allocation */
{
	DeleteAllBoard(B);
	DeleteAllPlayer(Pl);
}

boolean IsThreePlayerBankrup(ListOfPlayer Pl)
/* Permainan Selesai jika hanya satu pemain */
{
	if (Next(Cur(Pl))==Cur(Pl))
	{
		return true;
	}
	else
	{
		return false;
	}
}

void MasukPenjara(Board B, ListOfPlayer Pl)
/*
  I.S Player Berada Diluar Penjara, Player Mendapatkan Kartu masuk penjara
  F.S Player Masuk Ke penjara
*/
{
    //Kamus
    Address1 LocPlayer, LocPenjara;
    Address2 P;
     
    //Algoritma
    P = Cur(Pl);
    LocPlayer = PlayerPlace(B, Id(P));
    LocPenjara = SearchPetak(B,StringToKata("Deserted Island"));
    DeletePlayerPosition(Pl, LocPlayer);
    PlacePlayer(Pl, LocPenjara);
}
 
int totalAsset(Board B, Address2 P)
/*Mengembalikan total aset 1 player*/
{
    //Kamus
    Address1 Loc;
    int Sum = 0;
     
    //Algoritma
    Loc = Start(B);
    for(;;){
        if(Pemilik(Loc)==Id(P)){
			Sum += Harga(Loc)*Level(Loc);
        }
        if(Next(Loc)==Start(B)){
            break;
        }else{
            Loc = Next(Loc);
        }
    }
    return Sum;
}

void AutoCommand(Address1 Position,Board B,ListOfPlayer Pl,Chance C)
//Generate AutoCommand
{
	//Kamus Lokal
	char command[20];
	char query[20];
	Address1 P;
	boolean finish;
	//Algoritma
	if (IsKataSama(Info(Position).Nama,StringToKata("Tax")))
	{
		Tax(B,Cur(Pl));
	}
	else if (IsKataSama(Info(Position).Nama,StringToKata("Bonus")))
	{
		GetBonus(Pl);
	}
	else if (IsKataSama(Info(Position).Nama,StringToKata("Chance")))
	{
		RandomChance(B,C,Pl);
	}
	else if (IsKataSama(Info(Position).Nama,StringToKata("World Travel")))
	{
		finish=false;
		do
		{
			printf("> ");
			ReadCommand(command);
			if (IsSubString("travel",command))
			{
				TakeCommandEntry(command,"travel",query);
				P=SearchPetak(B,StringToKata(query));
				Travel(B,Pl,P);
				if (P!=Nil)
				{
					finish=true;
				}
			}
			else
			{
				ERRORMESSAGE();
			}
		} while (!finish);		
	}
	else if (IsKataSama(Info(Position).Nama,StringToKata("World Cup")))
	{
		//Initialize
		ResetWorldCup(Pl,B);
		finish=false;
		if (IsNoAsset(Cur(Pl),B))
		{
			printf("Maaf anda tidak memiliki aset sehingga tidak dapat menggunakan World Cup.\n");
		}
		else
		{
			do
			{
				printf("> ");
				ReadCommand(command);
				if (IsSubString("host",command))
				{
					TakeCommandEntry(command,"host",query);
					P=SearchPetak(B,StringToKata(query));
					if (P!=Nil)
					{
						Host(Pl,P);
						if (Info(P).WorldCup!='-')
						{
							finish=true;
						}
					}
					else
					{
						printf("Petak tidak ada.\n");
					}
				}
				else
				{
					ERRORMESSAGE();
				}
			} while (!finish);	
		}
	} else if((Pemilik(Position)!='N') && (Pemilik(Position) != Info(Cur(Pl)).id))
	{
		Address2 P2;
		int Tagihan = HargaSewa(Position);
		P2 = SearchPlayer(Pl,Pemilik(Position));
		Uang(Cur(Pl)) = Uang(Cur(Pl)) - Tagihan;
		Uang(P2) = Uang(P2) + Tagihan;
		printf("Player %c membayar uang sewa ke Player %c.\n",Id(Cur(Pl)),Id(P2));
		printf("Sebesar ");PrintUang(Tagihan);printf("\n");
	} else if (IsKataSama(Info(Position).Nama,StringToKata("Start")))
	{
		Uang(Cur(Pl))=Uang(Cur(Pl))+1000; //Nambah yey
		printf("Anda telah sampai Start.\n");
		printf("Anda mendapat uang sebesar 1M\n");
		ResetLampu(Pl,B);
	}
}

void ResetWorldCup(ListOfPlayer Pl,Board B)
//Menghapus semua history world cup
{
	//Kamus
	Address2 P1;
	Address1 Pt;
	//Algoritma
	P1=Cur(Pl);
	if (!IsEmptyBoard(B))
	{
		Pt=Start(B);
		for(;;)
		{
			//Resetting
			if (WorldCup(Pt)==Id(P1))
			{
				WorldCup(Pt)='-';
			}
			//Traversal
			if(Next(Pt)==Start(B))
			{
				break;
			}
			else
			{
				Pt=Next(Pt);
			}
		}
	}
}

void ResetLampu(ListOfPlayer Pl,Board B)
//Reset semua yang sudah dimatikan atau menyalakan semua yang mati
{
	//Kamus
	Address2 P1;
	Address1 Pt;
	//Algoritma
	P1=Cur(Pl);
	if (!IsEmptyBoard(B))
	{
		Pt=Start(B);
		for(;;)
		{
			//Resetting
			if (Pemilik(Pt)==Id(P1)&&(MatiLampu(Pt)=='M'))
			{
				MatiLampu(Pt)='H';
			}
			//Traversal
			if(Next(Pt)==Start(B))
			{
				break;
			}
			else
			{
				Pt=Next(Pt);
			}
		}
	}
}

boolean IsBankrup(Address2 P1,Board B)
//Apakah kamu sudah tidak sanggup bermain?
{
	//Kamus
	
	//Algoritma
	if (Uang(P1)+totalAsset(B,P1)<0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

boolean IsNoAsset(Address2 P1,Board B)
//Apakah asetmu masih ada?
{
	//Algoritma
	if (totalAsset(B,P1)==0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

boolean IsRunOutOfMoney(Address2 P1)
//Apakah uangmu habis?
{
	if (Uang(P1)<0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

/* Bayar Pajak */
void Tax(Board B,Address2 PL)
//Membayar pajak itu baik
{
	int sum;
	sum = totalAsset(B,PL) * 10 / 100;
	Uang(PL) = Uang(PL) - sum;
	printf("Anda membayar pajak sebesar 10 persen dari total asset Anda!\n");
	printf("Total Pembayaran Anda : ");PrintUang(sum);printf("\n");
}

void PrintUang(int Uang)
//Mencetak format konversi angka
{
	int sisa;
	if (Uang<1000)
	{
		printf("%dK",Uang);
	}
	else
	{
		sisa = Uang % 1000;
		printf("%dM %dK",Uang/1000,sisa);
	}
}
