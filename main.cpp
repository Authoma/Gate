#include <Arduino.h>

/* AUTOMAZIONE CANCELLO BATTENTE
Editor Schirò Roberto 28/03/2021
Automazione per il controllo di un cancello a battente mediante da autocostruita basata su arduino stand alone con chip Atmega 328P
Ingressi presenti:
PA pulsante apertura
PS pulsante di stop
FA fotocellule apertura
FC fotocellule chiusura 
FB barriera
AD0 trimmer lavoro
AD1 trimmer pausa aperto
Uscite presenti:
R1 motore destro
R2 motore sinistro
R3 relè inversione motori
*/

#define PA 2 //Pin 4 arduino
#define PS 3 //Pin 5 arduino
#define FA 4 //Pin 6 arduino
#define FC 5 //Pin 11 arduino
#define FB 6 //Pin 12 arduino
#define R1 7 //Pin 13 arduino
#define R2 8 //Pin 14 arduino
#define R3 9 //Pin 15 arduino
#define AD0 0 //Pin AD0 arduino
#define AD1 1 //Pin AD1 arduino
#define D13 13 //Pin 19 arduino

void setup() {
  // put your setup code here, to run once:
}

void loop() {
  // put your main code here, to run repeatedly:
}