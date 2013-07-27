!------------------------------------------------------------------------------
! module d'affichage des matrices et des vecteurs
!------------------------------------------------------------------------------

MODULE affichage

CONTAINS

!------------------------------------------------------------------------------
!subroutine du l'affichage de la matrice a
!------------------------------------------------------------------------------

SUBROUTINE afficheMat(a,n)
IMPLICIT NONE

!déclaration des variables
character(len=10), parameter                :: fmt='(F5.2)'    !constante format
real(8),dimension(:,:),intent(inout)        :: a        !matrice
integer, intent(inout)                      :: n        !rang de a
integer                                     :: i,j      !indice de boucle

!affichage de la matrice a
print *,"La matrice A :"
DO i=1,n
    print fmt,(a(i,j),j=1,n)
END DO

END SUBROUTINE afficheMat

!------------------------------------------------------------------------------
!subroutine de l'affichage du vecteur x
!------------------------------------------------------------------------------

SUBROUTINE afficheVect(x,n)
IMPLICIT NONE

!déclaration des variables
real(8),dimension(:),intent(inout)          :: x    !vecteur
integer,intent(inout)                       :: n    !rang de x
integer                                     :: i    !indice de boucle

!affichage du vecteur x
print *,"Le vecteur x :"
do i=1,n
    print *,x(i)
end do

END SUBROUTINE afficheVect

!------------------------------------------------------------------------------
!------------------------------------------------------------------------------

END MODULE affichage
