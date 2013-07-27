        NAME    main

        PUBLIC  __iar_program_start

        SECTION .intvec : CODE (2)
        CODE32

__iar_program_start
        B       main


        SECTION .text : CODE (2)
        CODE32

main    NOP
        LDR 	R1,=chaine			;ptr Lecture
        LDR 	R2,=chaine			;ptr Ecriture

RJA:
        LDRB 	R0,[R1],#1			;Lecture caractere
        CMP 	R0,#' '				;Comparaison avec l'espace
        BEQ 	BOU 				;Si c'est un espace, on n'ecrit pas
        STRB 	R0,[R2],#1			;Sinon on ecrit

BOU:
        CMP 	R0,#0				;Comparaison avec le bit NULL
        BNE 	RJA					;Si non egale, on continue
        ; That is all folks !
        B .

; --- Donnees ---
        DATA
chaine  DC8 	" H e l l o  W o r l d"

        END
