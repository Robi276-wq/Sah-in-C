# Sah-in-C
Șah în C (Console Chess)

Un motor de șah complet funcțional, scris de la zero în limbajul C. Jocul rulează direct în terminal (consolă) și dispune de o interfață vizuală colorată, validare strictă a regulilor și detectare automată pentru stările de final de joc.

Acest proiect a fost construit pentru a aprofunda conceptele de programare în C: lucrul cu matrice, pointeri, modularizarea codului și simularea mutărilor (algoritmi de generare a stărilor).

Funcționalități Implementate

* Interfață Grafică în Terminal: Tabla este desenată folosind culori de fundal (ANSI Escape Codes) și piese reale de șah (caractere Unicode UTF-8).
* Validare Geometrică Strictă: Fiecare piesă respectă regulile clasice de mișcare din șah.
* Protecția Regelui (Save & Undo): Sistemul simulează mutările în fundal înainte de a le aproba. Jucătorii nu pot face mutări care le-ar lăsa propriul rege în șah.
* Detectare Automată (Forță Brută) Șah: Avertizează jucătorul când regele este atacat.
* Șah Mat: Identifică momentul în care jucătorul curent nu mai are nicio mutare legală salvatoare.
* Remiză (Pat / Stalemate): Oprește jocul dacă regele nu este în șah, dar jucătorul nu are mutări legale.
* Sistem de Punctaj: Calculează scorul pe baza valorii pieselor capturate (Pion = 1, Cal/Nebun = 3, Tură = 5, Regină = 9).
* Promovarea Pionului: Pionii care ajung la capătul tablei sunt promovați automat în Regină.

 Arhitectura Proiectului

Codul este modularizat pentru a fi curat și ușor de citit:
* main.c - Bucla principală a jocului și gestionarea turelor.
* reguli.c - "Creierul" jocului (validări, simulări, matematică).
* grafic.c - Funcțiile responsabile de desenarea tablei și culori.
* sah.h - Fișierul header care leagă toate componentele.
* Makefile - Scriptul pentru automatizarea compilării.

 Cum se Instalează și Rulează

Pentru a juca, ai nevoie de un compilator C (ex: GCC) și utilitarul `make` instalat pe sistemul tău.

1. Clonează repository-ul:
   ```bash
   git clone [https://github.com/numele-tau/Sah-in-C.git](https://github.com/numele-tau/Sah-in-C.git)
   cd Sah-in-C
