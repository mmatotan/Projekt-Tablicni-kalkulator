# Projekt_Tablicni_kalkulator
Projekt iz predmeta "Programiranje II"

Opis Zadatka

Malo koji računarac voli unositi podatke u tablice, ali izraditi svoj osobni tablični kalkulator poseban je izazov.

U ovom zadatku potrebno je izraditi samu jezgru tabličnog kalkulatora odnosno program koji će od niza jednadžbi, za svaku ćeliju po jedna, izračunati i ispisati prikazane vrijednosti u svim ćelijama.

-------------
Ulazni podaci
-------------

U prvom retku nalazi se cijeli broj t (1≤t≤100) koji označava broj listova (spreadsheet) dokumenta tabličnog kalkulatora. Za svaki list zadani su redom sljedeći podaci, u prvom retku je zadan broj n (1≤n≤200) odnosno broj jednadžbi u listu. U svakom od sljedećih n redaka zadana je po jedna jednadžba s najviše 200 znakova.

Svaka jednadžba započinje s oznakom ćelije čija vrijednost se njome izračunava zatim nastavlja znakom = nakon čega slijedi aritmetički izraz odnosno naizmjenični niz operanada (to mogu biti ili oznake ćelija ili pozitivni cijeli brojevi) i računskih operatora. Aritmetički izraz počinje i završava operandom i sadrži samo četiri osnovne računske operacije -, +, / i * te ne sadrži zagrade.

Susjedni elementi jednadžbe međusobno su odvojeni jednim znakom razmaka.

Oznaka pojedine ćelije sastoji se od niza velikih slova engleske abecede kao oznaka stupca te niz znamenki kao oznaka retka npr. A1 za prvi redak i prvi stupac ili AB123 za 123. redak i 28. stupac. Najveća duljina oznake ćelije je 5 znakova.

U jednadžbama nema ciklusa u kojem vrijednost ćelije ovisi o samoj sebi niti izravno niti preko jednadžbi za druge ćelije. Sve ćelije koje se nalaze u pojedinom aritmetičkom izrazu imaju svoju jednadžbu.

Prilikom evaluacije aritmetičkih izraza potrebno je poštivati prioritet računskih operacija: najprije množenje i dijeljenje s lijeva na desno, a zatim oduzimanje i zbrajanje također s lijeva na desno.

Sve jednadžbe su takve da svi rezultati i međurezultati stanu u 32-bitnu cjelobrojnu vrijednost odnosno tip int.

Operator / je operator cijelobrojnog dijeljenja, odnosno rezultat se uvijek zaokružuje na nižu cijelobrojnu vrijednost. Djeljenik je uvijek veći ili jednak nula, a djelitelj je uvijek veći od nule.

Prije opisanih ulaznih podataka za svaki pojedini list nalazi se jedan prazni redak.

--------------
Izlazni podaci
--------------

Za svaki od t listova dokumenta potrebno je ispisati n linija oblika ĆELIJA = VRIJEDNOST pri čemu su ćelije ispisane u leksikografskom odnosno abecednom poretku njihovih oznaka. Sve vrijednosti su veće ili jednake nula.