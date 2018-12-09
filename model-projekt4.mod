#MPSIS - Data Center Disk Optimization Model

#Stale

# N[disk] - liczba dyskow typu A,B,C,D
# V[disk] - pojemnosc dysku danego typu
# S[disk] - szybkosc zapisu dysku danego typu
# C[raid, disk] - cena danego typu dysku i danej macierzy RAID (za 1 gb)
# R1[raid] - stosunek pojemnosci uzytecznej

#Indeksy

set RAID, default {1,5,6};
set DISK, default {1,2,3,4};

param N{disk in DISK}, >= 0;

param V{disk in DISK}, >= 0;

param S{disk in DISK}, >= 0;

param C{raid in RAID, disk in DISK}, >= 0;

param R{raid in RAID}, >= 0;

#Zmienne

#X[raid, disk] - LIczba dyskow danego typu w danej konfiguracji RAID

var X{raid in RAID, disk in DISK}, integer, >= 0;


#Funcja celu

maximize z: sum{raid in RAID, disk in DISK} R[raid]*X[raid, disk]*C[raid, disk]*V[disk];

#Ograniczenia

s.t. c1: X[1,1] + X[5,1] + X[6,1] <= N[1]; #Liczba dyskow typu A w roznych konfiguracjach RAID nie przekracza calkowitej liczby dyskow A
s.t. c2: X[1,2] + X[5,2] + X[6,2] <= N[2]; #Liczba dyskow typu B w roznych konfiguracjach RAID nie przekracza calkowitej liczby dyskow A
s.t. c3: X[1,3] + X[5,3] + X[6,3] <= N[3]; #Liczba dyskow typu A w roznych konfiguracjach RAID nie przekracza calkowitej liczby dyskow A
s.t. c4: X[1,4] + X[5,4] + X[6,4] <= N[4]; #Liczba dyskow typu A w roznych konfiguracjach RAID nie przekracza calkowitej liczby dyskow A

#Input Data

data;

param N := 1 1
           2 1
	   3 1
	   4 1;

param V := 1 1
	   2 1
 	   3 1
	   4 1;

param S := 1 1
	   2 1
	   3 1
	   4 1;

param C :    1 2 3 4 :=
           1 1 1 1 1
           5 1 1 1 1
	   6 1 1 1 1;
	   

param R := 1 1
           5 1
	   6 1;	   

end;
