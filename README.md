# mwpsis
Projekt z Matematyki w Projektowaniu Sieci i Systemów\
Calosc testowana byla na debianie i powinno dzialac.
Trzeba zainstalowac nastepujace pakiety:
```bash
sudo apt-get install apache2 git build-essentials make g++
```
Plik 000-default.conf trzeba przeniesc do /etc/apache2/sites-available.conf
Katalog html trzeba przeniesc do /var/www

Aby skompilowac kcgi:
```bash
git clone https://github.com/kristapsdz/kcgi
cd kcgi
./configure
make
sudo make install
```

Aby skompilowac hdd.c nalezy wykonac:
```bash
g++ hdd.c -o hdd -lkcgihtml -lkcgi -L/usr/local/lib -lClp -L/usr/local/lib -lcoinglpk -ldl -lm -L/usr/local/lib -lCoinUtils -lm -L/usr/local/lib -lcoinglpk -ldl -lm
```

Kompilowanie solvera zgodnia z instrukcja na labach czyli:
```bash
sudo apt-get install build-essential autoconf subversion
svn co https://projects.coin-or.org/svn/Cbc/releases/2.9.9 cbc
cd cbc/ThirdParty/Glpk
./get.Glpk
./configure
cd ../..
./configure CFLAGS='-m64 -O3' --enable-gnu-packages --enable-cbc-parallel --enable-debug -C --prefix=/usr/local
make -j 4
sudo make install
```
