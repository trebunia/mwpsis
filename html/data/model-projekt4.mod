#MwPSIS - Data Center Disk Optimization Model

#Stale

# N[disk] - liczba dyskow typu A,B,C,D
# V[disk] - pojemnosc dysku danego typu
# S[disk] - szybkosc zapisu dysku danego typu
# SR[disk] - szybkosc odczytu z dysku danego typu
# S_klienta - szybkosc jaka zyczy sobie klient
# G[raid] - gain jaki jest osiagniety dzieki zastosowaniu danego raidu
# C[raid, disk] - cena danego typu dysku i danej macierzy RAID (za 1 gb)
# R[raid] - stosunek pojemnosci uzytecznej
# D - Wymagania klienta dot. pojemnosci uzytecznej

#Indeksy

set RAID, default {1,5,6};
set DISK, default {1,2,3,4};

param N{disk in DISK}, integer, >= 0;

param V{disk in DISK}, integer, >= 0;

param S{disk in DISK}, integer, >= 0;

param SR{disk in DISK}, integer, >= 0;

param C{raid in RAID, disk in DISK}, >= 0;

param R{raid in RAID}, >= 0;

param G{raid in RAID}, >= 0;

param GR{raid in RAID}, >= 0;

param S_klienta, integer, >= 0;

param SR_klienta, integer, >= 0;

param D_min, integer, >= 0;

param D_max, integer, >= 0;

#Zmienne

#X[raid, disk] - Liczba macierzy z 8 dyskow danego typu w danej konfiguracji RAID

var X{raid in RAID, disk in DISK}, integer, >= 0;

#Funcja celu

minimize z: sum{raid in RAID, disk in DISK} 8*X[raid, disk]*C[raid, disk]*V[disk];

#Ograniczenia

s.t. c1: X[1,1] + X[5,1] + X[6,1] <= N[1]/8; #Liczba dyskow typu A w roznych konfiguracjach RAID nie przekracza calkowitej liczby dyskow A
s.t. c2: X[1,2] + X[5,2] + X[6,2] <= N[2]/8; #Liczba dyskow typu B w roznych konfiguracjach RAID nie przekracza calkowitej liczby dyskow B
s.t. c3: X[1,3] + X[5,3] + X[6,3] <= N[3]/8; #Liczba dyskow typu C w roznych konfiguracjach RAID nie przekracza calkowitej liczby dyskow C
s.t. c4: X[1,4] + X[5,4] + X[6,4] <= N[4]/8; #Liczba dyskow typu D w roznych konfiguracjach RAID nie przekracza calkowitej liczby dyskow D
s.t. c5: sum{raid in RAID, disk in DISK} 8 * X[raid, disk] * V[disk] * R[raid] >= D_min;
s.t. c6: sum{raid in RAID, disk in DISK} 8 * X[raid, disk] * V[disk] * R[raid] <= D_max;
s.t. c7: sum{raid in RAID, disk in DISK} X[raid, disk] * S[disk] * G[raid] >= S_klienta * sum{raid in RAID, disk in DISK} X[raid, disk];
s.t. c8: sum{raid in RAID, disk in DISK} X[raid, disk] * SR[disk] * GR[raid] >= SR_klienta * sum{raid in RAID, disk in DISK} X[raid, disk];

#Input Data

data;

param N := 1 10000 2 10000 3 10000 4 10000;
param V := 1 8000 2 6000 3 1000 4 500;
param S := 1 90 2 90 3 375 4 375;
param SR := 1 100 2 100 3 425 4 425;
param C :	1	2	3	4 :=
	1	0.5	0.5	1.5	1.5
	5	0.1	0.1	0.8	0.8
	6	0.3	0.3	1.1	1.1;
param R := 1 0.125 5 0.875 6 0.75;
param G := 1 1 5 2 6 1.33;
param GR := 1 8 5 7 6 6;
param S_klienta := 0;
param SR_klienta := 3400;
param D_min := 168000;
param D_max := 168000;

end;
