#MPSIS - Data Center Disk Optimization Model

#Stale

# N1, N2, N3, N4 - liczba dyskow typu A,B,C,D
# V1, V1, V3, V4 - pojemnosc dysku danego typu
# S1, S2, S3, S4 - szybkosc zapisu dysku danego typu
# C11, C12 ... C64 - cena danego typu dysku i danej macierzy RAID (za 1 gb)
# R1, R5, R6 - stosunek pojemnosci uzytecznej

param N1, integer, >= 0;
param N2, integer, >= 0;
param N3, integer, >= 0;
param N4, integer, >= 0;
param V1, integer, >= 0;
param V2, integer, >= 0;
param V3, integer, >= 0;
param V4, integer, >= 0;
param S1, integer, >= 0;
param S2, integer, >= 0;
param S3, integer, >= 0;
param S4, integer, >= 0;
param C11, integer, >=0;
param C12, integer, >=0;
param C13, integer, >=0;
param C14, integer, >=0;
param C51, integer, >=0;
param C52, integer, >=0;
param C53, integer, >=0;
param C54, integer, >=0;
param C61, integer, >=0;
param C62, integer, >=0;
param C63, integer, >=0;
param C64, integer, >=0;
param R1, integer, >=0;
param R5, integer, >=0;
param R6, integer, >=0;

#Zmienne

#X11,X12,...,X64 - LIczba dyskow danego typu w danej konfiguracji RAID

var X11, integer, >=0;
var X12, integer, >=0;
var X13, integer, >=0;
var X14, integer, >=0;
var X51, integer, >=0;
var X52, integer, >=0;
var X53, integer, >=0;
var X54, integer, >=0;
var X61, integer, >=0;
var X62, integer, >=0;
var X63, integer, >=0;
var X64, integer, >=0;

#Indeksy

set I, default {1,5,6};
set J, default {1,2,3,4};

#Funcja celu

maximize z: sum{i in I, j in J} R[i]*X[i,j]*C[i,j]*V[j];

#Ograniczenia

s.t. c1: X11 + X51 + X61 <= N1; #Liczba dyskow typu A w roznych konfiguracjach RAID nie przekracza calkowitej liczby dyskow A
s.t. c2: X12 + X52 + X62 <= N2; #Liczba dyskow typu B w roznych konfiguracjach RAID nie przekracza calkowitej liczby dyskow A
s.t. c3: X13 + X53 + X63 <= N3; #Liczba dyskow typu A w roznych konfiguracjach RAID nie przekracza calkowitej liczby dyskow A
s.t. c4: X14 + X54 + X64 <= N4; #Liczba dyskow typu A w roznych konfiguracjach RAID nie przekracza calkowitej liczby dyskow A
