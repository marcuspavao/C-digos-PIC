/*
 * File:   mainLCD.c
 * Author: Marcus Vin�cius Fernandes Pav�o de Souza
 */

// Funciona na Placa Exto NEO201 e na PicGenios
// alterar flexlcd.h para o LCD funcionar em cada uma das placas

#define _XTAL_FREQ 8000000
#include "configbits.h"
#include <xc.h>
#include "flexlcd.h"
#define BT1 PORTBbits.RB0
#define BT2 PORTBbits.RB1
#define BT3 PORTBbits.RB2
#define BT_CLEAR PORTBbits.RB3
#define BACK PORTBbits.RB4
#define SHIFT PORTBbits.RB5

void main(void) 
{
    ADCON0 = 0b00000000; // Desabilita o conversor A/D
    ADCON1 = 0b00001111; //configura todos os pinos AD como I/O
    //ADCON2 = 0b00000000;
    //INTCON = 0b00000000;
    //INTCON2 = 0b00000000;
    INTCON2bits.RBPU = 1; // Pull-up resistors
    // Input or Output
    TRISB = 0b11111111; 
    TRISC = 0b00000000;
    TRISD = 0b00000000; 
    TRISE = 0b00000000;
    // Clear ports
    PORTB = 0; 
    LATB = 0;
    PORTC = 0; 
    LATC = 0;
    PORTD = 0; 
    LATD = 0;
    PORTE = 0; 
    LATE = 0;
    int col, l;
    col = 0;
    l = 1;
    Lcd_Init();
    Lcd_Cmd(LCD_CURSOR_OFF);
    //Lcd_Out(1, 0, "PROFICAM  CAM210");
    //Lcd_Out(2, 0, "Sist. Embarcados");
    while(1) 
    {
        
        if(BT_CLEAR == 0){
            Lcd_Cmd(LCD_CLEAR);   
            col = 0;
        }
        if(BT1 == 0){
            Lcd_Out(l, col, "1");
            col++;
            __delaywdt_ms(200);
        }
        if(BT2 == 0){
            Lcd_Out(l, col, "2");
            col++;
            __delaywdt_ms(200);
        }
        if(BT3 == 0){
            Lcd_Out(l, col, "3");
            col++;
            __delaywdt_ms(200);
        }
        
        if(col == 16){
            l = 2;
            col = 0;
        }
        
        if(col == 16 && l == 2){
            col = 0; l = 1;
        }
        
        if(BACK == 0){
            col = col - 1;
            if(col == -1 && l == 2){
                l = 1;
                col = 15;            
            }
            Lcd_Out(l, col, " ");
            __delaywdt_ms(200);
        }
        
//        if(SHIFT == 0)
//        {   
//            Lcd_Cmd(LCD_SHIFT_LEFT);
//            __delaywdt_ms(400);
//        }
        
        CLRWDT();       
    }
    return;
}
