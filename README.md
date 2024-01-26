# AUTONOMNO VOZILO - PROJEKTNI ZADATAK
Ovaj repozitorijum sadži dokumentaciju potrebnu za izradu projektnog zadataka iz predmeta Računarska elektronika/Mikrokontrolerski sistemi na Elektrotehničkom fakultetu u Banjoj Luci. Na projekatu rade tri studenta na četvrtoj godini. Cilj projekta jeste implementacija sistema za autonomnu vožnju koji može bezbijedno i efikasno upravljati vozilom. Sistem se nadograđuje na [Joy-car](https://joy-it.net/en/products/mb-joy-car).

# Specifikacija projektnog zadataka 
### Upravljačka PCB ploča
Potrebno je realizovati PCB pločicu koja ispunjava sljedeće zahtjeve: 
* PCB pločica može biti maksimalno dvoslojna.
* Koristi se SMD tip komponenti
* Minimalna širina veze prilikom rutiranja iznosi 0.254 mm, a minimalno rastojanje između komponenata 0.1 mm.
* Korišćenje mikrokontrolera (MCU) tipa PIC24FJ64GAxx za upravljanje i kontrolu sistema.
* Podrška za komunikaciju putem UART, SPI i I2C interfejsa za povezivanje različitih komponenti.
* Integracija Wi-Fi modula za bežičnu komunikaciju i daljinsko upravljanje.
* Upotreba već postojećeg baterijskog napajanja.
* Budzet za kupovinu komponenata od 20 do 30 dolara.

### Lidar
* Implementacija 2D mapiranja prostora oko vozila korišćenjem Lidar tehnologije.
* Korišćenje Lidar senzora za precizno očitavanje i analizu okoline vozila.

## Aplikacija
* Razvoj aplikacije za prikazivanje okoline oko vozila.
* Mogućnost pokretanja i zaustavljanja vozila putem aplikacije, 2D prikaz reljefa.
