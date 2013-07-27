!------------------------------------------------------------------------------
! TP3 : LES Méthodes itératives QR
! Auteur : Valentin Laurent (ZZ1,G1)
! Date : 11/12/12
! Compilation : gfortran algo.f90 affichage.f90 val_p.f90 -o val_p
! Fichiers de tests : matrice41.txt, matrice42.txt et matrice9.txt
!------------------------------------------------------------------------------

PROGRAM val_p

USE algo
USE affichage

IMPLICIT NONE

real(8),dimension(:,:),allocatable      :: A        !la matrice A
real(8),dimension(:), allocatable       :: spA      !le spectre de A
integer                                 :: n        !le rang de A
integer                                 :: i        !variable de boucle
integer                                 :: iter     !nombre d'itération
integer                                 :: iter_max !nombre d'itération max
real(8)                                 :: eps      !ce cher epsilon
character (len=20)                      :: nomfich  !nom du fichier

!affichage menu
print *,"------------------- tp3 : la methode QR -------------------"
print *,"Calcule le spectre d'une matrice donnée selon la methode QR"
print *,"-----------------------------------------------------------"


! Lecture du nom du fichier de donnees
print *,' Entrez le nom du fichier de donnees : '
read *,nomfich

!initialisation
open(1,file=nomfich,status="old",action="read")
read(1,*) n
allocate(A(n,n),spA(n))

DO i=1,n
    read(1,*) A(i,1:n)
END DO
close(1)

print *,"Veuillez saisir la valeur d'epsilon : "
read *,eps

print *,"Veuillez saisir le nombre d'iterations maximal : "
read *,iter_max

call afficheMat(A,n)
call QR(A,eps,iter_max,iter)

print *,"Nombre d'iterations : ",iter

!call afficheMat(A)
DO i=1,n
    spA(i) = A(i,i)
END DO

print *,"Le spectre de A : "
call afficheVect(spA,n)

print *,"-------------------------------------------------------"

END PROGRAM val_p
!fin du TP3
