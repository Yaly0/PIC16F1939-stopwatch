/*
 * File:   Projectmain.c
 * Author: Yahya
 *
 * Created on January 24, 2019, 7:48 PM
 */

#include <xc.h>

#pragma config FOSC=HS,WDTE=OFF,PWRTE=OFF,MCLRE=ON,CP=OFF,CPD=OFF,BOREN=OFF,CLKOUTEN=OFF
#pragma config IESO=OFF,FCMEN=OFF,WRT=OFF,VCAPEN=OFF,PLLEN=OFF,STVREN=OFF,LVP=OFF

#define _XTAL_FREQ 8000000
#define setbit(var,bit) ((var)|= (1<<(bit)))
#define clrbit(var,bit) ((var &=~(1<<bit)))
#define tranz1 RA5
#define tranz2 RE0
#define tranz3 RE1
#define tranz4 RE2

#define start PORTAbits.RA0
#define stop PORTAbits.RA1
#define prikaz PORTAbits.RA4

#define ledice LATB
#define displej PORTD
#define t 3000

char cifre[] = {0xc0, 0xf9, 0xa4, 0xb0, 0x99, 0x92, 0x82, 0xf8, 0x80, 0x90};

char brojac = 0, brojac1 = 0, brojac2 = 0, brojac3 = 0, brojac4 = 0,
     uzlazna1 = 0, uzlazna2 = 0, uzlazna3 = 0, sekunda = 0, kretanje = 0, prikazivanje = 0;

void inicijalizacija() {
    //Za 4 tranzistore PNP tipa(A5,E0,E1,E2) i 3 ulaza na PORTA(0,1,4)
    ANSELA = 0x00;
    TRISA = 0x13; // 0b00010011
    LATA = 0x00;
    ANSELE = 0x00;
    TRISE = 0x00;
    LATE = 0x00;
    //Za diode sa zajednickom anodom (pale se na nulu)
    ANSELB = 0x00;
    TRISB = 0x00;
    TRISD = 0x00;
    displej = 0X00;
    ledice = 0;
    
    TMR0 = 0;
    TMR0CS = 0;
    PSA = 0;
    OPTION_REGbits.PS = 0x06; // 0b110 -> preskaler = 128, 128 * 256 *  (4/8MHz) = 16384ms
    GIE = 1;
    TMR0IE = 1;
}

void ispisi1() {
    tranz4 = 1;
    tranz1 = 0;
    if(sekunda == 1) {
        sekunda = 0;
        brojac1++;
        if(brojac1 > 9) {
            brojac2++;
            if(brojac2 > 5) {
                brojac3++;
                if(brojac3 > 9) {
                    brojac4 = brojac4 == 9 ? 0 : brojac4 + 1;
                    brojac3 = 0;
                }
                brojac2 = 0;
            }
            brojac1 = 0;
        }
        if(prikazivanje != 0) {
            if(prikazivanje == 1 && (brojac3 > 3 || brojac4 > 0))
                        prikazivanje++;
            if(prikazivanje == 1) ledice = brojac1 + 10 * brojac2 + 64 * brojac3;
            else if(prikazivanje == 2)
                ledice = brojac3 + 10 * brojac4;
            else ledice = brojac1 + 10 * brojac2;
        } else ledice = 0;
    }
    displej = cifre[brojac1];
}

void ispisi2() {
    tranz1 = 1;
    tranz2 = 0;
    displej = cifre[brojac2];
}

void ispisi3() {
    tranz2 = 1;
    tranz3 = 0;
    displej = cifre[brojac3] ^ (1<<7); // da bi se i tacka ispisala u sredini
}

void ispisi4() {
    tranz3 = 1;
    tranz4 = 0;
    displej = cifre[brojac4];
}

void jelStart() {
    if(start) {
            if(uzlazna1 == 0) {
                    uzlazna1 = 1;
                    kretanje = 1;
            }
    } else
            uzlazna1 = 0;
}

void jelStop() {
     if(stop) {
            if(uzlazna2 == 0) {
                    uzlazna2 = 1;
                    if(kretanje == 1) kretanje = 0;
                    else {
                        brojac1 = 0;
                        brojac2 = 0;
                        brojac3 = 0;
                        brojac4 = 0;
                    }
            }
    } else
            uzlazna2 = 0;
}

void jelPrikaz() {
    if(prikaz) {
            if(uzlazna3 == 0) {
                    uzlazna3 = 1;
                    prikazivanje = prikazivanje == 3 ? 0 : prikazivanje + 1;
            }
    } else
        uzlazna3 = 0;
}

void __interrupt() sek() { // void __interrupt(high_priority) sek(void)
    if(TMR0IE && TMR0IF) {
        TMR0IF = 0;
        if(kretanje == 1) brojac++;
        if(brojac == 61) { // 16384 * 61 = 999.424
            sekunda = 1;
            brojac = 0;
        }
    }

}

void main() {
    inicijalizacija();
    while(1) {
        ispisi1();
        __delay_us(t);
        ispisi2();
        __delay_us(t);
        ispisi3();
        __delay_us(t);
        ispisi4();
        __delay_us(t);
        jelStart();
        jelStop();
        jelPrikaz();
    }
}
