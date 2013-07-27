!-----------------------
! TP1 : fortran
! Factorisation LU
!----------------------

program TP1

use factorisation
implicit none

!déclaration des variables
real(8),dimension(:,:),allocatable          :: a        !matrice de factorisation
real(8),dimension(:),allocatable            :: b        !second membre
real(8),dimension(:),allocatable            :: x        !vecteur résultat
integer                                     :: n        !rang de la matrice a
integer,dimension(:),allocatable            :: ndx      !matrice des indices
integer                                     :: ichoix=1 !choix de l'utilisateur
integer                                     :: ierr     !indice d'erreur
integer                                     :: i,j      !indice de boucle
integer                                     :: nbperm   !nombre de permutations
real(8)                                     :: det      !déterminant de a
integer                                     :: menu     !variable de menu

!initialisation des variables
menu = 0

do while (ichoix /= 0)
    !affichage du menu
    print *,"--------- tp1 : Factorisation LU et ses applications ---------"
    print *,"ichoix = 0 -> quitte le programme                             "
    print *,"ichoix = 1 -> décomposition LU et résolution du système ax = b"
    print *,"ichoix = 2 -> décomposition LU seulement                      "
    print *,"ichoix = 3 -> résolution du système ax = b seulement          "
    print *,"Les choix 1 et 2 calculent aussi det(a) et inverse(a)         "
    print *,"--------------------------------------------------------------"

    !saisie de ichoix
    print *,"Veuillez saisir la valeur de ichoix : "
    read *, ichoix

    !allocation de a,b,x et ndx par lecture du fichier systeme.dat
    open(1,file='systeme.txt',action='read',status='old')
    read(1,*) n

    if (menu == 0) then
        allocate(a(n,n))
        allocate(b(n))
        allocate(x(n))
        allocate(ndx(n))
    endif

    do i=1,n
        read(1,*) (a(i,j),j=1,n), b(i)
    end do
    close(1)

    !application du module LU selon ichoix
    call LU(a,b,x,ndx,ichoix,ierr,nbperm)

    !choix de l'utilisateur dans l'affichage
    select case (ichoix)
        case(1)
            !affichage de a,x,det(a) et invere(a)
            call afficheMat(a,n)
            call afficheVect(x,n)
            call determinant(a,n,nbperm,det)
            call inverse(a,n,det,ndx,x,nbperm,ierr)
        case(2)
            !affichage de a,det(a) et inverse(a)
            call afficheMat(a,n)
            call determinant(a,n,nbperm,det)
            call inverse(a,n,det,ndx,x,nbperm,ierr)
        case(3)
            !affichage de a et x
            call afficheMat(a,n)
            call afficheVect(x,n)

        case(0)
            !affichage de fin
            print *,"Fin du programme"

        case default
            print *,"Opération inconnue"
    end select

    !nombre d'utilisation
    menu = menu + 1

end do

!fin du programme principal (execution)

contains

!------------------------------------------------------------------------------
!subroutine du l'affichage de la matrice a
!------------------------------------------------------------------------------

subroutine afficheMat(a,n)
implicit none

!déclaration des variables
real(8),dimension(:,:),intent(inout)        :: a    !matrice
integer, intent(inout)                      :: n    !rang de a
integer                                     :: i,j  !indice de boucle

!affichage de la matrice a
print *,"La matrice a :"
do i=1,n
   print *,(a(i,j), j=1,n)
end do

end subroutine afficheMat

!------------------------------------------------------------------------------
!subroutine de l'affichage du vecteur x
!------------------------------------------------------------------------------

subroutine afficheVect(x,n)
implicit none

!déclaration des variables
real(8),dimension(:),intent(inout)          :: x    !vecteur
integer,intent(inout)                       :: n    !rang de x
integer                                     :: i    !indice de boucle

!affichage du vecteur x
print *,"Le vecteur x :"
do i=1,n
    print *,x(i)
end do

end subroutine afficheVect

!------------------------------------------------------------------------------
!subroutine du calcul du determinant de a
!------------------------------------------------------------------------------

subroutine determinant(a,n,nbperm,det)
implicit none

!déclaration des variables
real(8),dimension(:,:),intent(inout)        :: a        !matrice décomposée LU
integer,intent(inout)                       :: n        !rang de a
integer,intent(in)                          :: nbperm   !nombre de permutations de a
integer                                     :: i        !indice de boucle
real(8),intent(inout)                       :: det      !déterminant

!Calcul du déterminant
det = nbperm

do i=1,n
    det = det * a(i,i)
end do

!affichage du déterminant
print *,"det(a) = " ,det

end subroutine determinant

!------------------------------------------------------------------------------
!subroutine du calcul de l'inverse de a
!------------------------------------------------------------------------------

subroutine inverse(a,n,det,ndx,x,nbperm,ierr)
implicit none

!déclaration des variables
real(8),dimension(:,:),intent(inout)                :: a        !matrice décomposée LU
integer,intent(inout)                               :: n        !rang de a
real(8),intent(in)                                  :: det      !déterminant de a
real(8),dimension(:,:),allocatable                  :: inva     !inverse de a
real(8),dimension(:),allocatable                    :: Id       !colonne de la matrice identité
integer                                             :: i,j,k    !indice de boucle
integer,dimension(size(a,dim=1)),intent(inout)      :: ndx      !vecteur des permutations
integer,intent(inout)                               :: nbperm   !nombre de permutation(s)
integer,intent(inout)                               :: ierr     !affichage de l'erreur
real(8),dimension(:),intent(inout)                  :: x        !vecteur résultat
real(8)                                           	:: eps=1d-12

allocate(inva(n,n),Id(n))

!vérification du déterminant
if (abs(det)>eps) then

    !Calcul de l'inverse de a
    do i=1,n
        Id=0.d0
        Id(i)=1.d0
        !calcul de xi
        call LU(a,Id,x,ndx,3,ierr,nbperm)

        !calcul de l'inverse
        inva(1:n,i) = x(1:n)
    end do

    !affichage de la matrice inv(a)
    print *,"La matrice inverse(a) :"
    do j=1,n
        print *,(inva(i,j), k=1,n)
    end do

else
    !si la matrice a n'est pas inversible
    print *,"La matrice a n'est pas inversible !"

end if
end subroutine

!------------------------------------------------------------------------------
!------------------------------------------------------------------------------

end program TP1
!fin du tp1
