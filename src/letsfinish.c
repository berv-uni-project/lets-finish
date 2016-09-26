/* Nama file : letsfinish.c */
/* Program Utama Game Let's Finish */

#include "game/game.h"
#include "command/command.h"
#include "board/board.h"
#include "global/global.h"
#include <time.h>

int main ()
{
	//Kamus
	//State permainan
	boolean Finish; 
	//Penyimpanan command
	char command[30];
	//Lokasi Pemain Saat Ini
	Address1 Pd;
	//Data Global Permainan
	Chance C;
	Board B;
	ListOfPlayer Pl;
		
	//Algoritma
	
	//Pesan Awal
	ShowWelcomeMessage();
	//Inisialisasi State
	Finish=false;
	//Inisialisasi Board dan ListOfPlayer
	Start(B)=Nil;
	Cur(Pl)=Nil;
	//Mengaktifkan suatu random
	srand(time(0));
	//Memasuki permainan
	do
	{
		printf("> ");
		//Pembacaan Command
		ReadCommand(command);
		//Eksekusi Command
		if (ValidCommand1(command))
		{
			if (IsStringSama("exit",command))
			{
				Finish=true;
			}
			else
			{
				ProccessPhase1(command,&B,&Pl,&C);
				if (IsEmptyBoard(B))
				{
					printf("Maaf, silahkan coba lagi. Data belum dimasukan.\n");
				}
				//Masuk permainan
				else //Sudah Masuk Phase 2
				{
					printf("Selamat Bermain...\n");
					do
					{
						//Inisialisasi Lokasi Pemain.
						Pd=PlayerPlace(B,Info(Cur(Pl)).id);
						//Menampilkan Status Pemain.
						ShowPlayerStatus(Cur(Pl),Pd);
						printf("> ");
						//Pembacaan Command
						ReadCommand(command);
						CommandProccessor(command,&Finish,&B,&Pl,C,&Pd);
					}
					while ((!Finish) && (!IsThreePlayerBankrup(Pl)));
					if (IsThreePlayerBankrup(Pl))
					{
						printf("Congrulation! Player %c, YOU WINNER!\n",Id(Cur(Pl)));
					}
				}		
			}
		}
		else
		{
			printf("Maaf masukan Anda salah.\n");
			printf("Jika ingin memulai masukan start atau load <nama file>\n");
			printf("Jika ingin keluar masukan exit\n");
		}
	}
	while (!Finish);
	
	//Selesai permainan
	if (!IsEmptyBoard(B))
	{
		CleanGame(&Pl,&B);
	}
	/*
	if(IsEmptyPlayer(Pl) && IsEmptyBoard(B))
	{
		printf("The game has clean.\n");
	}
	else
	{
		printf("You have garbage game.\n");
	}*/
	return 0;
}
