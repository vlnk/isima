MODULE algo
CONTAINS

SUBROUTINE QR(A,eps,iter_max,iter)
IMPLICIT NONE

real(8),dimension(:,:),intent(inout)    :: A        !matrice A
real(8),dimension(:),allocatable        :: v        !vecteur de calcul de Householder
real(8),dimension(:,:),allocatable      :: Q        !matrice de factorisation QR
real(8),dimension(:,:),allocatable      :: H        !matrice de Householder
real(8)                                 :: s        !calcul de la norme de A
real(8)                                 :: a_max    !composante maximale (non diag) de A
real(8),intent(in)                      :: eps      !epsilon

integer, intent(in)                     :: iter_max !iteration maximale
integer, intent(inout)                  :: iter     !compteur d'iterations
integer                                 :: n        !rang de A
integer                                 :: test     !valeur de test (pour l'iteration)
integer                                 :: i,j,k    !variables de boucle
integer                                 :: kp,km    !valeur de k+1 et k-1

!initialisation
n = size(A,dim = 1)
iter = 1
test = 0

!allocations
allocate(Q(n,n),H(n,n),v(n))

DO WHILE ((test == 0) .and. (iter < iter_max))

    iter = iter +1
    !initialisation de Q
    Q = 0
    DO i=1,n
        Q(i,i) = 1.d0
    END DO

    DO k=1,n-1

        !calcul de s
        s = 0.d0
        DO j=k,n
            s = s + A(j,k)**2
        END DO
        s = sqrt(s)

        !calcul de v
        kp = k+1
        km = k-1
        v(1:km) = 0
        v(k) = A(k,k)+A(k,k)/abs(A(k,k))*s
        v(kp:n) = A(kp:n,k)

        !calcul de r (-> s) et w (-> v)
        s = sqrt(2*s*(s+abs(A(k,k))))
        v = v/s

        !calcul de H
        DO i=1,n
            DO j=1,n
                IF (i == j) THEN
                    H(i,j) = 1-2*v(i)*v(j)
                ELSE
                    H(i,j) = -2*v(i)*v(j)
                END IF
            END DO
        END DO

        !calcul de Q et A
        Q = matmul(Q,H)
        A = matmul(H,A)

    END DO

    !mise à jour de A
    A = matmul(A,Q)

    !test sur les elements non diagonaux
    a_max = 0.d0
    DO i=1,n
        DO j=1,n
            IF (a_max < A(i,j)) THEN
                a_max = A(i,j)
            END IF
        END DO
    END DO

    IF (a_max < eps) THEN
        test = 1
    END IF

END DO

END SUBROUTINE QR

END MODULE algo
