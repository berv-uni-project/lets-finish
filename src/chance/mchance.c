#include "chance.h"

int main() {
	//Kamus
	Chance C;
	//Algoritma
	//Inisialisasi
	CreateEmptyChance(&C);
	//Load Chance melalui file
	LoadChance(&C,"default-chance.txt");
	//Mencetak Isi Chance
	PrintChance(C);
	return 0;
}
