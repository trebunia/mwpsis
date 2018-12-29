#MwPSIS - Data Center Disk Optimization Model

#Stale

# N[disk] - liczba dyskow typu A,B,C,D
# V[disk] - pojemnosc dysku danego typu
# S[disk] - szybkosc zapisu dysku danego typu
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

param C{raid in RAID, disk in DISK}, integer, >= 0;

param R{raid in RAID}, integer, >= 0;

param G{raid in RAID}, integer, >= 0;

param S_klienta, integer, >= 0;

param D_min, integer, >= 0;

param D_max, integer, >= 0;

#Zmienne

#X[raid, disk] - LIczba dyskow danego typu w danej konfiguracji RAID

var X{raid in RAID, disk in DISK}, integer, >= 0;

#Funcja celu

maximize z: sum{raid in RAID, disk in DISK} X[raid, disk]*C[raid, disk]*V[disk];

#Ograniczenia

s.t. c1: X[1,1] + X[5,1] + X[6,1] <= N[1]; #Liczba dyskow typu A w roznych konfiguracjach RAID nie przekracza calkowitej liczby dyskow A
s.t. c2: X[1,2] + X[5,2] + X[6,2] <= N[2]; #Liczba dyskow typu B w roznych konfiguracjach RAID nie przekracza calkowitej liczby dyskow B
s.t. c3: X[1,3] + X[5,3] + X[6,3] <= N[3]; #Liczba dyskow typu C w roznych konfiguracjach RAID nie przekracza calkowitej liczby dyskow C
s.t. c4: X[1,4] + X[5,4] + X[6,4] <= N[4]; #Liczba dyskow typu D w roznych konfiguracjach RAID nie przekracza calkowitej liczby dyskow D
s.t. c5: sum{raid in RAID, disk in DISK} V[raid, disk] / R[raid] >= D_min; #Pojemnosc dyskowa / stosunek uzytecznosci jest wiekszy niz demand klienta
s.t. c6: sum{raid in RAID, disk in DISK} X[raid, disk] * S[disk] * G[raid] >= sum{disk in DISK} N[disk] * S_klienta;
s.t. c6: sum{raid in RAID, disk in DISK} V[raid, disk] / R[raid] <= D_max;

#Input Data
