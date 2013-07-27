!------------------------------------------------------------------------------
! TP2 : Méthodes itératives de résolution des systèmes linéaires
! Auteur : Valentin Laurent (ZZ1,G1)
! Date : 11/12/12
! Compilation : gfortran methode.f90 affichage.f90 syslin.f90 -o syslin
! Fichiers de tests : matrice4.txt et matrice9.txt
!------------------------------------------------------------------------------

PROGRAM syslin

USE methodes
USE affichage

IMPLICIT NONE

integer                                 :: ichoix   !choix de l'utilisateur
real(8),dimension(:,:),allocatable      :: A        !matrice A du système
real(8),dimension(:),allocatable        :: b        !second membre du système
real(8),dimension(:),allocatable        :: x        !inconnue du système
real(8)                                 :: omega    !coefficient de relaxation
integer                                 :: nb_iter  !nombre d'itération
integer                                 :: n        !rang de A
integer                                 :: i,j,k    !variable de boucle
integer                                 :: menu     !valeur de menu
character (len=20)                      :: nomfich  !nom du fichier
integer                                 :: ierr     !variable d'erreur
real(8)                                 :: x0       !valeur de x0
real(8)                                 :: eps      !valeur de test


!initialisation du menu
menu = 1

! Lecture du nom du fichier de donnees
print *,' Entrez le nom du fichier de donnees : '
read *,nomfich

!initialisation de x
print *,' Entrez la valeur de x0 (0.d0) :'
read *,x0

!initialisation de eps
print *,' Entrez la valeur de epsilon (1.d-12) :'
read *,eps

DO WHILE (menu /= 0)

    ! Ouverture du fichier en lecture
    open(1,file=nomfich,status='old',action='read',iostat=ierr)
    IF (ierr /= 0) THEN
        print *,'Fichier de donnees inexistant'
        stop
    END IF

    !lecture du rang
    read(1,*) n

    IF (menu == 1) THEN
        !allocation de A,b,x pour la première utilisation
        allocate(A(n,n))
        allocate(b(n))
        allocate(x(n))
    END IF

    !Lecture de la matrice A et de b dans "matrice.txt"
    DO i=1,n
        read(1,*) (A(i,j),j=1,n)
    END DO
    read(1,*) (b(k),k=1,n)

    !fermeture du fichier
    close(1)

    !initialisation de x
    x(1:n) = x0

    !affichage du menu
    print *,"----------------- tp2 Resolution de systemes lineaires -----------------"
    print *,"ichoix = 0 -> quitte le programme"
    print *,"ichoix = 1 -> Methode de Jacobi"
    print *,"ichoix = 2 -> Methode de Gauss-Seidel"
    print *,"ichoix = 3 -> Methode de relaxation"
    print *,"Le choix 3 effectue un tableau pour omega variant de 0.1 à 1.9"
    print*,"-------------------------------------------------------------------------"

    !saisie utilisateur
    print *,"Veuillez saisir votre choix ?"
    read *,ichoix

    !choix des différentes methodes
    SELECT CASE(ichoix)
        CASE (0)
            !sortie du programme
            menu = -1

        CASE (1)
            !methode de Jacobi
            call resolution(1,A,b,omega,nb_iter,x,eps)

            !affichage
            !call afficheMat(A,n)
            call afficheVect(x,n)
            print *,"Nombre d'iterations : ",nb_iter

        CASE(2)
            !methode de Gauss-Seidel
            omega = 1.d0
            call resolution(2,A,b,omega,nb_iter,x,eps)

            !affichage
            !call afficheMat(A,n)
            call afficheVect(x,n)
            print *,"Nombre d'iterations : ",nb_iter

        CASE(3)
            !methode de relaxation
            omega = 1.d-1
            call afficheMat(A,n)

            DO k=1,19

                !initialisation de x
                x(1:n) = x0

                call resolution(3,A,b,omega,nb_iter,x,eps)

                !affichage
                print '(/)'
                print *,"Valeur d'omega : ",omega
                call afficheVect(x,n)
                print *,"Nombre d'iterations : ",nb_iter
                omega = omega + 1.d-1
            END DO

        CASE DEFAULT
            print *,"Evenement inconnu"

    END SELECT

    !affichage
    menu = menu + 1
    print '(/)'

END DO

print *,"Fin du programme"
print '(/)'
!fin du programme principal (execution)

END PROGRAM syslin
!fin du TP2
