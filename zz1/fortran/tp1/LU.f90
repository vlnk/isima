module factorisation
implicit none

contains

subroutine LU(a,b,x,ndx,ichoix,ierr,nbperm)
implicit none

!déclarations des varaibles
integer,intent(in)                                  :: ichoix   !choix de l'utilisateur
integer,intent(inout)                               :: ierr     !affichage de l'erreur
real(8),dimension(:,:),intent(inout)                :: a        !matrice à factoriser
real(8),dimension(:),intent(in)                     :: b        !second membre
real(8),dimension(:),intent(inout)                  :: x        !vecteur résultat
integer,dimension(size(a,dim=1)),intent(inout)      :: ndx      !vecteur des permutations
integer,dimension(1)                                :: ipivot   !indice du pivot
integer,intent(inout)                               :: nbperm   !nombre de permutation(s)

!variables temporaires
real(8),dimension(size(a,dim=1))                    :: temp     !vecteur de stockage
integer                                             :: itemp    !stockage d'indice

!variables locales
integer                                             :: i, j     !variables de boucles
integer                                             :: n        !rang de la matrice

!initialisation de la variable subroutine
nbperm = 1
n = size(a, dim=1)
ierr = 0

!initialisation du vecteur des permutations
ndx=(/(j,j=1,n)/)

!decomposition a <- LU (ichoix=1 ou 2)
if ((ichoix == 1) .or. (ichoix == 2)) then

    do j=1,n
        do i=1,j
            !calcul des u(i,j)
            a(i,j) = a(i,j) - dot_product(a(i,1:i-1),a(1:i-1,j))
        end do

        a(j,j) = a(j,j) - dot_product(a(j,1:j-1),a(1:j-1,j))

        do i=j+1,n
            !calcul des l[tilde](i,j)
            a(i,j) = a(i,j) - dot_product(a(i,1:j-1),a(1:j-1,j))
        end do

        !recherche de l'indice du max pour le pivot
        ipivot = maxloc(abs(a(j:n,j))) + (j-1)

        !methode du pivot partiel
        !si l'indice de ligne du pivot est différente de j on permute les lignes ipivot et j
        if (ipivot(1) /= j) then

            temp(1:n) = a(j,1:n)
            a(j,1:n) = a(ipivot(1),1:n)
            a(ipivot(1),1:n) = temp(1:n)
            itemp = ndx(j)
            ndx(j) = ipivot(1)
            ndx(ipivot(1)) = itemp
            nbperm = -nbperm

        endif

        !si on trouve un pivot nul on retourne ierr=1
        if(abs(a(j,j)) < 1.d-12) then
            ierr = j
            return

        !sinon on calcul l(i,j)
        else
            do i=j+1,n
                !calcul des l(i,j)
                a(i,j) = a(i,j)/a(j,j)
            end do
        endif
    end do
endif

!résolution de ax = b par substitution
if ((ichoix == 1) .or. (ichoix == 3)) then

    !substitution directe Ly = b (ichoix = 1 ou 3)
    x = b(ndx)
    do i=2,n
        x(i) = x(i) - dot_product(x(1:i-1),a(i,1:i-1))
    end do

    !substitution directe Ux = y
    x(n) = x(n)/a(n,n)
    do i=n-1,1,-1
        x(i) = (x(i) - dot_product(a(i,i+1:n),x(i+1:n)))/a(i,i)
    end do
endif

end subroutine LU
end module factorisation
