/* Nama File : command.c */
/* File Header mengatur Command pengguna*/

#include "command.h"

/** Mengatur Command dari Pengguna **/
void ReadCommand(char command[])
/* Membaca Command Dari Pengguna */
//String yang digunakan sedikit berbeda
{
	//Kamus
	int i;
	char ch;
	//Algoritma
	i=0; 
	do
	{
		scanf("%c",&ch);
		if (ch!='\n')
		{ 
			command[i]=ch;
			i++;
		}
	}
	while(ch!='\n');
	//Akan berhenti membaca saat pengguna memasukan new line
	command[i]='\0';
	//Menyisipkan '\0' sebagai akhir dari sebuah string
}

/** Hanya digunakan sebelum permainan **/
boolean ValidCommand1(char command[])
/* Mengecek Validasi Command Sebelum Mulai Permainan */
{
	if (IsSubString("load",command) || IsStringSama("start",command) || IsStringSama("exit",command))
		return true;
	else
		return false;

}

void ProccessPhase1(char command[],Board *B,ListOfPlayer *Pl,Chance *C)
/* Memproses Phase 1 */
{
	char query[25];
	char query1[25];
	char query2[25];
	if (IsStringSama("start",command))
	{
		//Inisialisasi Board, Player dan Chance
		InisialisasiGame(Pl,B,C);
		printf("You now play New Game!\n");
	}
	else //load
	{
		TakeCommandEntry(command,"load",query);
		strcpy(query1,"../data/");
		strcpy(query2,"../data/");
		strcat(query1,query);
		strcat(query2,query);
		strcat(query1,"-map.txt");
		strcat(query2,"-player.txt");
		FILE *fp = fopen(query1,"r");
		if (fp!=NULL)
		{
			fclose(fp);
			if (!IsEmptyBoard(*B))
			{
				DeleteAllBoard(B);
				DeleteAllPlayer(Pl);
			}
			LoadBoard(B,query1);
			printf("> Permainan di-load dari file %s ",query1);
			LoadPlayerStatus(Pl,query2);
			printf("dan %s\n",query2);
		}
		else
		{
			fprintf(stderr,"File tidak ditemukan!\n");
		}
	}
}

/** Digunakan saat mulai permainan **/
void CommandProccessor(char command[],boolean *Finish,Board *B,ListOfPlayer *Pl,Chance C,Address1 *Pd)
/* Mengatur Command */
{
	char query[20];
	char query1[20];
	char query2[20];
	Address1 PTemp;
	if (IsStringSama("exit",command))
	{
		printf("> Terima kasih sudah bermain!\n");
		*Finish=true;
	}
	else if(IsStringSama("help",command))
	{
		ShowHelp();
	}
	else if (IsSubString("load",command))
	{
		TakeCommandEntry(command,"load",query);
		strcpy(query1,"../data/");
		strcpy(query2,"../data/");
		strcat(query1,query);
		strcat(query2,query);
		strcat(query1,"-map.txt");
		strcat(query2,"-player.txt");
		FILE *fp = fopen(query1,"r");
		if (fp!=NULL)
		{
			fclose(fp);
			if (!IsEmptyBoard(*B))
			{
				DeleteAllBoard(B);
				DeleteAllPlayer(Pl);
			}
			LoadBoard(B,query1);
			printf("> Permainan di-load dari file %s ",query1);
			LoadPlayerStatus(Pl,query2);
			printf("dan %s\n",query2);
		}
		else
		{
			fprintf(stderr,"File tidak ditemukan!\n");
		}
	}
	else if (IsSubString("save",command))
	{
		if (IsStringSama("save",command))
		{
			printf("Masukan nama file.\n");
		}
		else
		{
			TakeCommandEntry(command,"save",query);
			strcpy(query1,query);
			strcpy(query2,query);
			strcat(query1,"-map.txt");
			strcat(query2,"-player.txt");
			SaveBoard(*B,query1);
			printf("> Permainan telah disimpan ke file %s ",query1);
			SavePlayerStatus(*Pl,query2);
			printf("dan %s\n",query2);
		}
	}
	else if (IsSubString("buy",command))
	{
		if (IsSubString("buy offered",command))
		{
			TakeCommandEntry(command,"buy offered",query);
			BuyOffered(*B,*Pl,StringToKata(query));
		}
		else
		{
			if (IsStringSama("buy",command) && (Bought(Cur(*Pl))!='B') && (RolledDice(Cur(*Pl))=='R'))
			{
				//buy normal
				Buy(*B,*Pl,Info(*Pd).Nama);
				Bought(Cur(*Pl)) = 'B';
			}
			else
			{
				ERRORMESSAGE();
			}
		}
	}
	else if (IsStringSama("roll dice",command) && (RolledDice(Cur(*Pl))!='R'))
	{
		RollDice(*B,C,*Pl,Pd);
		RolledDice(Cur(*Pl))='R';
	}
	else if (IsSubString("info",command))
	{
		TakeCommandEntry(command,"info",query);
		InfoPetak(*B,StringToKata(query));
	}
	else if (IsSubString("sell",command))
	{
		if (IsSubString("sell bank",command))
		{
			TakeCommandEntry(command,"sell bank",query);
			SellKotaBank(*B,*Pl,StringToKata(query));
		}
		else //sell offered
		{
			TakeCommandEntry(command,"sell",query);
			SellKotaOffered(*B,*Pl,StringToKata(query));
		}
	} 
	else if (IsStringSama("show offered",command))
	{
		ShowOffered(*B);
	}
	else if ((IsStringSama("upgrade",command)) && (Upgraded(Cur(*Pl))!='U') && (RolledDice(Cur(*Pl))=='R') && (Bought(Cur(*Pl))!='B'))
	{
		UpgradeHouse(*B,*Pl,Info(*Pd).Nama);
		Upgraded(Cur(*Pl))='U';
	}
	else if (IsStringSama("board",command))
	{
		ShowBoard(*B);
	}
	else if (IsStringSama("leaderboard",command))
	{
		Leaderboard(*Pl,*B);
	}
	else if (IsStringSama("end turn",command))
	{
		if (IsBankrup(Cur(*Pl),*B))
		{
			DeletePlayer(Pl);
			printf("Sorry, YOU LOSE!\n");
		} else if (IsRunOutOfMoney(Cur(*Pl))&&!(IsNoAsset(Cur(*Pl),*B)))
		{
			printf("You must sell your asset to BANK to get the money!\n");
			printf("Recommend sell to BANK.\n");
			do
			{
				printf("> ");
				ReadCommand(command);
				if (IsSubString("sell bank",command))
				{
					TakeCommandEntry(command,"sell bank",query);
					SellKotaBank(*B,*Pl,StringToKata(query));
				}
				else if (IsStringSama("board",command))
				{
					ShowBoard(*B);
				}
				else {
					printf("Sell it!\n");
				}
			} while(IsRunOutOfMoney(Cur(*Pl)));
			EndTurn(Pl);
		} else if (((Injail(Cur(*Pl)))==0)&&((RolledDice(Cur(*Pl)))=='R'))
		{
			EndTurn(Pl);
		} else if(Injail(Cur(*Pl))>0)
		{
			EndTurn(Pl);
		} else
		{
			ERRORMESSAGE();
		}
	}
	else if (IsStringSama("free me",command))
	{
		FreeMe(*Pl);
	}
	else if (IsStringSama("free tax",command))
	{
		FreeTax(*Pl,*Pd);
	}
	else if (IsSubString("off",command))
	{
		TakeCommandEntry(command,"off",query);
		PTemp = SearchPetak(*B,StringToKata(query));
		if (PTemp!=Nil)
		{
			Off(*Pl,PTemp,Cur(*Pl));
		}
		else
		{
			printf("Tempat yang Anda masukan tidak ada di board.\n");
		}
	}
	else if (IsSubString("protect",command))
	{
		TakeCommandEntry(command,"protect",query);
		PTemp = SearchPetak(*B,StringToKata(query));
		if (PTemp!=Nil)
		{
			Protect(Cur(*Pl),PTemp);
		}
		else
		{
			printf("Tempat yang Anda masukan tidak ada di board.\n");
		}
	}
	else if (IsStringSama("pay to free",command) && (Injail(Cur(*Pl))>0))
	{
		PayToFree(*Pl);
	}
	else
	{ 
		ERRORMESSAGE();
	}
}

/** Pengambilan entry dari suatu command **/
void TakeCommandEntry(char command1[],char command[],char entry[])
/* Mengambil Entry yang dimasukan oleh command yang valid */
{
	int i,j;
	i=0;
	j=0;
	while (command1[j]==command[j])
	{
		j++;
	}
	j=j+1;
	while (command1[j]!='\0')
	{
		entry[i]=command1[j];
		i++;
		j++;
	}
	entry[i]='\0';

}

/** Fungsi dan Prosedur Tambahan **/
/*  Berhubungan string dan kata */
Kata StringToKata(char str[])
/* Fungsi merubah representasi string menjadi kata */
{
	Kata Temp;
	int i;
	i=0;
	while (str[i]!='\0')
	{
		Temp.TabKata[i]=str[i];
		i++;
	}
	Temp.Length=i;
	return Temp;
}

boolean IsSubString(char s1[],char s2[])
//Mengecek apakah s1 substring dari s2
{
	int i;
	boolean found;
	found=false;
	i=0;
	while ((s1[i]!='\0') && (s2[i]!='\0') && (!found))
	{
		if (s1[i]!=s2[i])
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
		if ((s2[i]=='\0') && (s1[i]!='\0'))
		{
			return false;
		}
		else
		{
			return true;
		}
	}
}

boolean IsStringSama(char s1[],char s2[])
//Mengecek apakah s1 sama dengan s2
{
	int i;
	boolean found;
	found=false;
	i=0;
	while ((s1[i]!='\0') && (s2[i]!='\0') && (!found))
	{
		if (s1[i]!=s2[i])
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
		if ((s2[i]=='\0') && (s1[i]!='\0'))
		{
			return false;
		}
		else
		{
			if ((s1[i]=='\0') && (s2[i]=='\0'))
			{
				return true;
			}
			else
			{
				return false;
			}
		}
	}
}
