; TP2 ASSEMBLEUR
; DEROSSIS Léo
; LAURENT Valentin
        
        NAME    main
        
        PUBLIC  __iar_program_start
        
        SECTION .intvec : CODE (2)
        CODE32
        
__iar_program_start
        B       main

        
        SECTION .text : CODE (2)
        CODE32

main    NOP

; --- Code ---
        LDR     r0, =L              ; r0 : adr liste I
        LDR	    r2, N		        ; r2 : compteur N
        SUBS	r2, r2, #1	        ; N:=N-1
		
BOUCLEI:	
        ;pour cpt de N-1 a 1 pas -1
        CMP	    r2, #0   	        ; si N:=0
        BEQ	    FIN                 ; finpour
        MOV     r3, r2              ; r3 : variable S:=N
        MOV	    r1, r0		        ; r1 : variable J:=I
		
BOUCLEJ: 	
        ;pour cpt de S a 1 pas -1      
        CMP     r3, #0              ; si S:=0
        BEQ     FINB                ; finpour
        SUBS    r3, r3, #1          ; S-- 
        ADDS    r1, r1, #4          ; J++
        LDR     r4, [r0]            ; r4 : contenu L[I]
        LDR     r5, [r1]            ; r5 : contenu L[J]
        CMP	    r4, r5              ; L(i)>L(j)?
        BLT    	BOUCLEJ
        STR	    r5, [r0]	        ; permute
        STR	r4, [r1]
        B       BOUCLEJ
		
FINB:
        ADD     r0, r0, #4	        ; I:=I+1
        SUBS    r2, r2, #1          ; N--
        B       BOUCLEI

FIN:
        ;That is all folks!
        B .
        
; ---Donnees---
        DATA
N       DC32 	8		            ;N
L       DC32 	6,2,5,3,1,10,7,4    ;tableau L

        END
