          PROGRAM SQUELETTE_TP

;----- Constantes --------------------------------------------------------------

;Déclarer les constantes ici

ADR_GPIO    EQU 0xFFFFF400 ; adresse de base du PIO
GPIO_OUTPUT EQU 0xF  ; ‘1’ la direction du PIO est initialisée en sortie
LED1        EQU 0x8  ; DS4 la LED est connectée au PIO n° 4
LED2        EQU 0x4  ; DS3
LED3        EQU 0x2  ; DS2
LED4  EQU 0x1  ; DS1


;----- Segment de donn‚es -----------------------------------------------------
          RSEG DATA_ID:DATA(2)
          DATA

;Déclarer les variables ici
t DC32 1000000


          
;----- Segment de code --------------------------------------------------------------------
          RSEG CODE:CODE(2)
          CODE32

          PUBLIC main
main  nop

      LDR R0,=ADR_GPIO  ; R0 adresse de base GPIO
      LDR R1,=GPIO_OUTPUT  ; R1 direction de sortie des LEDs
      STR R1,[R0,#0]  ; valider le GPIO (voir annexe jointe)
      STR R1,[R0,#16]  ; Valider le GPIO en Sortie
      
      LDR R1,=LED1  ; R1 = LED1
      LDR R2,=LED2  ; R2 = LED2
      LDR R3,=LED3  ; R3 = LED3
      LDR R4,=LED4  ; R4 = LED4
      
      
      STR R1,[R0,#48]  ; 30h Eteindre LED1
      STR R2,[R0,#48]  ; 30h Eteindre LED2      
      STR R3,[R0,#48]  ; 30h Eteindre LED3      
      STR R4,[R0,#48]  ; 30h Eteindre LED4      
      

BOU: 

      STR R1,[R0,#52]  ; 34h Allumer LED1
      BL DELAY
      STR R1,[R0,#48]  ; 30h Eteindre LED1
      STR R2,[R0,#52]  ; 34h Allumer LED2
      BL DELAY
      STR R2,[R0,#48]  ; 30h Eteindre LED2
      STR R3,[R0,#52]  ; 34h Allumer LED3
      BL DELAY
      STR R3,[R0,#48]  ; 30h Eteindre LED3
      STR R4,[R0,#52]  ; 34h Allumer LED4
      BL DELAY
      STR R4,[R0,#48]  ; 30h Eteindre LED4 
      
      B BOU



;Fin du programme principal

          B   .
          
; -- Sous-prog --

DELAY:
  PUSH {R0}
  LDR R0,t
  
BOUD:
  CMP R0,#0
  BEQ FIND
  PUSH {R0}
  POP {R0}
  SUBS R0,R0,#1
  B BOUD
  
FIND:
  POP{R0}     
  BX LR
          END ;main
          
          
