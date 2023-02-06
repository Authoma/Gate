#include <Arduino.h>

/* AUTOMAZIONE CANCELLO BATTENTE
Editor Caotiko 28/03/2021
Automazione per il controllo di un cancello a battente mediante da autocostruita basata su arduino stand alone con chip Atmega 328P
Progetto editato con PlatformIo
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

// Inizio programma

#define PA 4 //Pin pb4 arduino pulsante apertura
#define PS 10 //Pin pd2 arduino pulsante stop
#define FA 11 //Pin pd3 arduino fotocellula interna
#define FC 12 //Pin pd4 arduino fotocellula esterna
#define FB 13 //Pin pd5 arduino barriera
#define R1 14 //Pin pd6 arduino motore 1
#define R2 21 //Pin pd7 arduino motore 2
#define R3 22 //Pin pc0 arduino relè inversione
#define AD0 A5 //Pin pa5 arduino pot pausa
#define AD1 A6 //Pin pa6 arduino pot apre-chiude
#define D13 0 //Pin pb0 arduino led diagnosi
#define LD1 24 //Pin pa0 arduino led apri
#define LD2 25 //Pin pa1 arduino led stop
#define LD3 26 //Pin pa2 arduino led ftc interna
#define LD4 27 //Pin pa3 arduino led ftc esterna
#define LD5 28 //Pin pa4 arduino led barriera

//Legenda stati: 0:attesa chiuso 1:in apertura 2:in chiusura 3:aperto in temporizzazione 4:chiusura in temporizzazione

int statoPA = 1;
int statoPS = 1;
int statoFA = 1;
int statoFC = 1;
int statoFB = 0;
int conteggioAp = 0;
int conteggioCh = 0;
int tempoPausa = 0;
int stato = 0;
int tempoApertura = 0;
int tempoAperto = 0;
boolean timeOutAp = false;
boolean timeOutCh = false;

void setup() {
  // put your setup code here, to run once:
  pinMode(PA, INPUT); //impostazione pin come ingressi uscite
  pinMode(PS, INPUT);
  pinMode(FA, INPUT);
  pinMode(FC, INPUT);
  pinMode(FB, INPUT);
  pinMode(R1, OUTPUT);
  pinMode(R2, OUTPUT);
  pinMode(R3, OUTPUT);
  pinMode(D13, OUTPUT);
  pinMode(LD1, OUTPUT);
  pinMode(LD2, OUTPUT);
  pinMode(LD3, OUTPUT);
  pinMode(LD4, OUTPUT);
  pinMode(LD5, OUTPUT);
  
}

void loop() {
    // put your main code here, to run repeatedly:
  tempoApertura = analogRead(AD0);
  tempoPausa = analogRead(AD1);

  if (digitalRead(PA)==0 || stato==1) //Pressione PA o programma in stato 1 routine apertura
  {
    stato=1;
    if (digitalRead(FA)==0 && timeOutAp==false)
    {
      digitalWrite(R1, 1);
      delay(1000);
      digitalWrite(R2, 1);
    }
    
  }
  else
  {
        stato = 3;              //tempo apertura trascorso avvio temporizzazione
        digitalWrite(R1, 0);
        digitalWrite(R2, 0);
        digitalWrite(R3, 0);
  }

  if (stato == 2) //Routine chiusura
  {
    if (digitalRead(FA)==0 && digitalRead(FC)==0 && timeOutCh==false)
    {
      digitalWrite(R3, 1);
      delay(2000);
      digitalWrite(R2, 1);
      delay(2000);
      digitalWrite(R1, 1);
    }
    
  }
  else
  {
      digitalWrite(R2, 0);
      digitalWrite(R1, 0);
      delay(500);
      digitalWrite(R3, 0);
      delay(2000);
      stato=1;
  }

  
 if (stato = 1) //In apertura temporizzazione
 {
   delay(1000);
   conteggioAp=conteggioAp+1;
   if (conteggioAp==tempoApertura)
   {
     timeOutAp = true;
     conteggioAp = 0;
   }
  }

 if (stato = 2) //In chiusura temporizzazione
 {
   delay(1000);
   conteggioCh=conteggioCh+1;
   if (conteggioCh==tempoApertura)
   {
     timeOutCh = true;
     conteggioCh = 0;
   }
 }
 if (stato = 3) //Aperto temporizzazione
 {
   delay(1000);
   tempoAperto=tempoAperto+1;
   if (tempoAperto==tempoPausa)
   {
     stato=2;
     tempoAperto=0;
   }
  }

}