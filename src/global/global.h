/* Nama File : global.h */
/* File header untuk definisi global */

#ifndef global_h
#define global_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../mesinkata/mesinkata.h"
#include "../mesinkata/mesinkarakter.h"
#include "boolean.h"

//Konstanta
#define Nil NULL

//Selektor Global Address
#define Info(P) (P)->info
#define Next(P) (P)->next

#endif
