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
		LDR		r0, =L			; r0 : adr liste I
		LDR		r1, N			; r1 : compteur N
        LDR     r2, =chaine     ; r2 : adr chaine
        LDR 	r3, val 		; r3 : valeur a convertir
		LDR 	r4, germe 		; r4 : germe
		MOV 	r6, #1
		
        ; tri de la liste
		PUSH	{r0,r1}			; on empile les paramètres    
        BL		TriSel			; appel du sous-programme de tri
        
        ; conversion en hexa
        PUSH    {r2,r3}      	; on empile les paramètres
		BL 		ConvHexa 		; appel du sous-programme de conversion
		
		; alea
		MOV		r5, r0			;copie l'adr de la liste
		
BOUCLEAlea:                 	;generation de N nombres aleatoires
		PUSH	{r4,r5}
        BL      Alea            ;on place dans r0 un nombre aleatoire
        STR     r6, [r5]        ;on place ce nombre dans la liste
        ADD     r5, r5, #4      ;passage a l'element suivant
        SUB     r1, r1, #1
        CMP     r1, #0
        BNE     BOUCLEAlea
		
        LDR     r1, N
	
		PUSH	{r0,r1}
        BL      TriSel
        B .

; --- Sous Programme (Tri par selection) ---
TriSel:
		PUSH	{r0-r5,LR}      ; sauver les registres
		
	;variables locales : r2 (compteur I), 
	;		     r3 (compteur J)
	;		     r4 (permutation)
	;		     r5 (permutation)
		
        LDR     r0, [SP,#28]   	; r0 : adr liste I
		LDR		r2, [SP,#32]	; r2 : compteur N
        SUBS	r2, r2, #1	    ; N:=N-1
		
BOUCLEI:	
        ;pour cpt de N-1 a 1 pas -1
        CMP		r2, #0   	    ; si N:=0
        BEQ		FIN             ; finpour
        MOV     r3, r2          ; r3 : variable S:=N
        MOV		r1, r0		    ; r1 : variable J:=I
		
BOUCLEJ: 	
        ;pour cpt de S a 1 pas -1      
        CMP     r3, #0       	; si S:=0
        BEQ     FINB         	; finpour
        SUBS    r3, r3, #1   	; S-- 
        ADDS    r1, r1, #4   	; J++
        LDR     r4, [r0]     	; r4 : contenu L[I]
        LDR     r5, [r1]     	; r5 : contenu L[J]
        CMP	    r4, r5       	; L(i)>L(j)?
        BLT    	BOUCLEJ
        STR	    r5, [r0]	 	; permute
        STR	    r4, [r1]
        B       BOUCLEJ
		
FINB:
        ADD     r0, r0, #4	  	; I:=I+1
        SUBS    r2, r2, #1    	; N--
        B       BOUCLEI

FIN:
        POP	    {r0-r5,LR}      ; restaurer les registres
		
        ADD	    SP,SP,#8		; liberer la zone des parametres
		BX	    LR
	;That is all folks!

; --- Sous Programme (Conversion Hexadecimale) ---
ConvHexa:
        PUSH	{r0-r4,LR}      ; sauver les registres
        LDR     r1, [SP,#24]   	; r4 : valeur a convertirr1 : adr chaine
        LDR     r0, [SP,#28]    ; r0 : valeur a convertir
        MOV    	r2, #8      	; r2 : compteur := 8
        
BOUCLEConv:
		ROR 	r0, r0, #28		;decalage a droite de 4 bits
        MOV     r3, r0			;sauvegarde de r0
        AND     r0, r0, #1111b	;masque qui garde le bit de poids faible
        CMP     r0, #10			;comparaison avec 10 (en ascii)
        ADDLO   r0, r0, #'0'
        ADDHS   r0, r0, #'A'-10
        STRB    r0, [r1]		;ecrit dans la chaine
		MOV 	r0, r3
        ADDS    r1, r1, #1      ; avance le pointeur de chaine
        SUBS    r2, r2, #1      ; compteur --
        CMP     r2, #0
        BNE     BOUCLEConv      ; compteur N fois
        
FIN2:
        POP     {r0-r4,LR}
        ADD     SP,SP,#8
        BX      LR
    ;That is all folks again!
    
	; --- Fonction alea ---
        Alea:
	    PUSH	{r0-r5,LR}
	    LDR		r0,[SP,#28]
	
        MUL     r6, r0, r6   	;on genere un nombre aleatoirement
        ADD     r6, r6, #1
	
	    POP		{r0-r5,LR}
        BX 		LR
	
;-- Données --
		DATA
N		DC32	6
L		DC32	2, 8, 45, 4, 9, 34
val 	DC32 	987654321
chaine  DS8     8
germe	DC32	987654321

        END
