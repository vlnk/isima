MODULE methodes

CONTAINS

!------------------------------------------------------------------------------
! subroutine des différentes methodes de résolution du système linéaire Ax=b
!------------------------------------------------------------------------------

SUBROUTINE resolution(ichoix,A,b,omega,nb_iter,x1,eps)
IMPLICIT NONE

integer,intent(in)                      :: ichoix           !choix de l'utilisateur
real(8),dimension(:,:),intent(inout)    :: A                !matrice A
real(8),dimension(:),intent(inout)      :: x1               !inconnue
real(8),dimension(:),intent(in)         :: b                !second membre
real(8),intent(inout)                   :: omega            !coefficient de relaxation
real(8),dimension(:),allocatable        :: x2               !vecteur de la suite

integer,intent(out)                     :: nb_iter          !nombre d'itération
integer                                 :: i,j,k,im,ip      !variable de boucle
integer                                 :: n                !rang de A
real(8),intent(in)                      :: eps              !valeur de test
real(8)                                 :: arret            !critère d'arrêt
real(8)                                 :: v1, v2           !calcul des normes

!initialisation
nb_iter = 0
v1 = 0.d0
v2 = 0.d0
n = size(b)
allocate(x2(n))

arret = eps+1.d0

!methode de Jacobi
IF (ichoix == 1) THEN
    DO WHILE (arret > eps) !on utilise la norme 2

        !initialisation des variables de boucles (calcul de norme et itérations)
        v1 = 0.d0
        v2 = 0.d0
        nb_iter = nb_iter + 1

        !calcul des xk suivant la methode de Jacobi
        DO i=1,n
            ip = i+1
            im = i-1
            x2(i) = (b(i) - dot_product(A(i,1:im),x1(1:im)) - dot_product(A(i,ip:n),x1(ip:n)))/A(i,i)

            !calcul de la norme 2
            v1 = v1 + (x2(i)-x1(i))**2
            v2 = v2 + x2(i)**2
        END DO

        !calcul du critère d'arrêt (actualisé pour chaque itération)
        arret = sqrt(v1/v2)
        x1 = x2
    END DO

!methode de relaxation + Gauss-Seidel (omega = 1)
ELSE IF ((ichoix == 3) .or. (ichoix == 2)) THEN
    DO WHILE (arret > eps)

        !initialisation des variables de boucles (calcul de norme et itérations)
        v1 = 0.d0
        v2 = 0.d0
        nb_iter = nb_iter + 1

        !calcul des xk suivant la methode de Gauss-Seidel
        DO i=1,n
            ip = i+1
            im = i-1
            x2(i) = (1.d0-omega)*x1(i) + (b(i) - dot_product(A(i,1:im),x2(1:im)) - dot_product(A(i,ip:n),x1(ip:n)))*omega/A(i,i)

            !calcul de la norme 2
            v1 = v1 + (x2(i)-x1(i))**2
            v2 = v2 + x2(i)**2
        END DO

        !calcul du critère d'arrêt (actualisé pour chaque itération)
        arret = sqrt(v1/v2)
        x1 = x2
    END DO
END IF

END SUBROUTINE resolution

!------------------------------------------------------------------------------
!------------------------------------------------------------------------------

END MODULE methodes
