;;puissance quatrième

(define quad (lambda (x)
    (* x x x x)
))

;;------------------------------------------------------------------------------------------
;;liste contenant la circonférence et la surface du cercle de rayon r

(define cercle (lambda (r) (let ((pi 3.14159)) (list (* 2 pi r) (* pi r r)))))

;;------------------------------------------------------------------------------------------
;;factorielle

(define factorielle (lambda (n)
    (if (> n 0)
        (* n (factorielle (- n 1)))
        1)
))

;;------------------------------------------------------------------------------------------
;;somme des n preminers entiers

(define som_int (lambda (n)
        (if (= n 0)
            0
            (+ n (som_int (- n 1)))
        )
))

;;------------------------------------------------------------------------------------------
;;longueur de la liste L

(define long (lambda (L)
    (if (null? L)
        0
        (+ 1 (long (cdr L)))
    )
))

;;------------------------------------------------------------------------------------------
;;longueur (récursivité terminale)

(define long2 (lambda (L)
    (lg L 0)
))
(define lg (lambda (L n)
    (if (null? L)
        n
        (lg (cdr L) (+ n 1))
    )
))

(long2 '(2 3 4))

;;------------------------------------------------------------------------------------------
;;liste renversée

(define miroir (lambda (L)
    (if (null? L)
        ()
        (append (miroir (cdr L)) (list (car L)))
    )
))

(define miroir2 (lambda (L)
    (m L ())))
(define m (lambda (L LM)
    (if (null? L)
        LM
        (m (cdr L) (cons (car L) LM))
    )
))

(miroir '(1 2 3))
(miroir2 '(1 2 3))

;;------------------------------------------------------------------------------------------
;;liste des carrés

(define carre (lambda (L)
    (if (null? L)
        ()
        (cons (* (car L) (car L)) (carre (cdr L)))
    )
))

(carre '(1 2 3))

;;------------------------------------------------------------------------------------------
;;nombre de nombres positifs

(define nbpos (lambda (L)
    (if (null? L)
        0
        (if (> (car L) 0)
            (+ (nbpos (cdr L)) 1)
            (nbpos (cdr L))
        )
    )
))

(nbpos '(1 -1 8 9))

;;------------------------------------------------------------------------------------------
;;appartient?

(define membre (lambda (x L)
    (if (null? L)
        #f
        (if (= (car L) x)
            #t
            (membre x (cdr L))
        )
    )
))

(membre 4 '(1 2 3))

;;------------------------------------------------------------------------------------------
;;liste sans double

(define epure (lambda (L)
    (if (null? L)
        L
        (if (membre (car L) (cdr L))
             (epure (cdr L))
             (cons (car L) (epure (cdr L)))
        )
    )
))

(epure '(1 1 2 3))

;;------------------------------------------------------------------------------------------
;;nieme element de la lite

(define nieme (lambda (n L)
    (if (null? L)
        -1
        (if (= n 1)
            (car L)
            (nieme (- n 1) (cdr L))
        )
    )
))

(nieme 4 '(1 1 1 4 1))

;;------------------------------------------------------------------------------------------
;;insère l'element en nieme place

(define insere (lambda (n x L)
    (if (null? L)
        ()
        (if (= n 1)
            (cons x L)
            (cons (car L) (insere (- n 1) x (cdr L)))
        )
    )
))


(insere 3 3 '(1 2 4 5))

;;------------------------------------------------------------------------------------------
;;union

(define union (lambda (L1 L2)
    (if (null? L2)
        L1
        (append L1 L2)
    )
))

(union '(1 2 3 4) '(4 5 6))

;;------------------------------------------------------------------------------------------
;;intersection

(define inter (lambda (L1 L2)
    (if (null? L1)
        ()
        (if (membre (car L1) L2)
            (cons (car L1) (inter (cdr L1) L2))
            (inter (cdr L1) L2)
        )
    )
))

(inter '(1 2 3 4) '(3 4 5 6))

;;------------------------------------------------------------------------------------------
;;retourne la liste sans sous-liste

(define niv0 (lambda (L)
    (if (null? L)
        ()
        (if (list? (car L))
	    (append (niv0 (car L)) (niv0 (cdr L)))
	    (cons (car L) (niv0 (cdr L)))
	)
    )
))

(niv0 '(1 (2 (3))))

;;------------------------------------------------------------------------------------------
;;retourne le nombre d'occurence

(define nb_occ (lambda (x L)
    (if (null? L)
        0
        (if (equal? x (car L))
            (+ 1 (nb_occ x (cdr L)))
            (nb_occ x (cdr L))
        )
    )
))

(nb_occ 3 '(1 2 3 4 3 5 3 6 7))

(define nb_occ2 (lambda (x L)
    (occ x L 0)
))
(define occ (lambda (x L k)
    (if (null? L)
        k
        (if (equal? x (car L))
            (occ x (cdr L) (+ 1 k))
            (occ x (cdr L) k)
        )
    )
))

(nb_occ2 3 '(1 2 3 4 3 5 3 6 7))

;;------------------------------------------------------------------------------------------
;;retourne la liste des couples de L1 et L2 (en même position)

(define zip (lambda (L1 L2)
    (if (and (null? L1) (null? L2))
        ()
    (if (not (equal? (long L1) (long L2)))
        ()
        (cons (list (car L1) (car L2)) (zip (cdr L1) (cdr L2)))
    ))
))

(zip '(1 3) '(a b))

;;------------------------------------------------------------------------------------------
;;retourne le produit cartésien entre L1 et L2

(define cart (lambda (x L)
    (if (null? L)
        ()
        (cons (list x (car L)) (cart x (cdr L)))
    )
))

(define prod (lambda (L1 L2)
    (if (null? L1)
        ()
        (append (cart (car L1) L2) (prod (cdr L1) L2))
    )
))

(prod '(1 2 3) '(a b c d))

;;------------------------------------------------------------------------------------------
;;retourne la somme des élements de la liste

(define som_list (lambda (L)
    (if (null? L)
        0
        (+ (car L) (som_list (cdr L)))
    )
))

(som_list '(1 2 3))

;;-----------------------------------------------------------------------------------------
;;retourne la liste triangulaire

(define triang (lambda(n)
    (if (or (= n 0) (= n 1))
        ()
	(t 2 n)
    )
))

(define t (lambda(k n)
    (if (= k n)
        (list n)
	(append (cons k (t (+ k 1) n)) (list k))
    )
))

(triang 7)

;;------------------------------------------------------------------------------------------
;;suite de fibonacci

(define fibo (lambda (n)
    (if (or (= n 1) (= n 0))
        1
	(f n 2 1)
    )
))

(define f (lambda (n uk uk-1)
    (if (= n 2)
        uk
	(f (- n 1) (+ uk uk-1) uk)
    )
))

(fibo 7)

(define fibo_vect (lambda (n)
    (if (or (= n 1) (= n 0))
        1
	(car (f n))
    )
))

(define f_vect (lambda (n)
    (if (= n 2)
	'(2 1)
	(let ((L (f (- n 1))))
	    (list (+ (car L) (cadr L)) (car L))
	)
    )
))

(fibo 7)

;;-------------------------------------------------------------------------------------------
;;calcul de la moyenne

(define moy (lambda (L)
    (if (null? L)
	()
	(let ((LL (m L 0 0)))
	    (/ (car LL) (cadr LL))
	)
    )
))

(define m (lambda (L s n)
    (if (null? L)
	    (list s n)
	    (let ((LL (m (cdr L) (+ s (car L)) (+ n 1))))
	        (list (car LL) (cadr LL))
	    )
    )
))

(moy '(1 2 3 4))

;;-------------------------------------------------------------------------------------------
;;retourne la liste des élements inférieurs à n, celle des élements supérieurs et celle des
;;élements égaux

(define ies (lambda (L n)
    (if (null? L)
        (list ()()())
        (let ((LL (ies (cdr L) n)) (e (car L)))
            (if (< n (car L)) 
                (list (cons e (car LL)) (cadr LL) (caddr LL))
                (if (> n (car L))
                    (list (car LL) (cadr LL) (cons e (caddr LL)))
                    (list (car LL) (cons e (cadr LL)) (caddr LL))
                )
            )
        )
    )
))


(ies '(3 5 4 4 7 9 4 6 2) 4)

;;-------------------------------------------------------------------------------------------
;;tri par insertion

(define tri_ins (lambda (L)
    (if (null? L)
        ()
        (aux (tri_ins (cdr L)) (car L))
    )
 ))

(define aux (lambda (L1 e)
    (if (null? L1)
        (list e)
        (if (< e (car L1))
            (cons e L1)
            (cons (car L1) (aux (cdr L1) e))
        )
    )
))

(tri_ins '(3 5 4 4 7 9 4 6 2))

;;------------------------------------------------------------------------------------------
;;tri par selection

(define tri_sel (lambda (L)
    (if (null? L)
        ()
        (let ((LL (aux1 L)))
	    (cons (car LL) (tri_sel (cadr LL)))
        )
    )
))

(define aux1 (lambda (L)
    (if (null? (cdr L))
        (list (car L) ())
        (let ((LL (aux1 (cdr L))))
	    (if (< (car L) (car LL))
		(list (car L) (cons (car LL) (cadr LL)))
		(list (car LL) (cons (car L) (cadr LL)))
	     )
	 )
    )
))

(aux1 '(5 4 4 7 8 4 6 3 10))

(tri_sel '(5 4 7 8 4 3 6 10 4))

;;-------------------------------------------------------------------------------------------
;;tri par bulles

(define tri_bul (lambda (L)
    (if (null? L)
	    ()
	    (aux_bul L ())
    )
))

(define aux_bul (lambda (L NL)
    (if (null? (cdr L))
	    (append NL (list (car L)))
	    (let ((LL (cdr L)))
	        (if (< (car LL) (car L))
	            (aux_bul (append NL (cons (car LL) (cons (car L) (cdr LL)))) ())
                (aux_bul (cdr L) (append  NL (list (car L))))
            )
        )
    )
))

(tri_bul '(5 4 7 8 4 3 6 10 4))

;;-------------------------------------------------------------------------------------------
;;tri fusion

(define taille (lambda (L)
    (if (null? L)
        0
        (+ 1 (taille (cdr L)))
    )
))

(define tri_fus (lambda (L)
    (if (null? L)
        ()
        (if (null? (cdr L))
            (list (car L))
            (let* ((LL (coupe L () () 0)))
                (let ((L1 (tri_fus (car LL))) (L2 (tri_fus (cadr LL))))
                    (fusion L1 L2)
                )
            )
        )
    )
))

(define coupe (lambda (L L1 L2 k)
    (if (null? L)
        (list L1 L2)
        (if (= (modulo k 2) 0)
            (coupe (cdr L) (cons (car L) L1) L2 (+ k 1))
            (coupe (cdr L) L1 (cons (car L) L2) (+ k 1))
        )
    )
))


(taille '(5 4 7 8 4 3 6 10 4))

(coupe '(5 4 7 8 4 3 6 10 4) () () 0)

(define fusion (lambda (L1 L2)
    (if (and (null? L1) (null? L2))
        ()
        (if (null? L1)
            L2
            (if (null? L2)
                L1
                (if (< (car L1) (car L2))
                    (let ((LL (fusion (cdr L1) L2)))
                        (cons (car L1) LL)
                    )
                    (let ((LL (fusion L1 (cdr L2))))
                        (cons (car L2) LL)
                    )
                )
            )
        )
    )
))

(fusion '(4 8 7 4 5) '(4 10 6 3))

(tri_fus '(5 4 7 8 4 3 6 10 4 2))

;;-------------------------------------------------------------------------------------------
;;tri rapide

(define tri_rap (lambda (L)
    (if (null? L)
        ()
        (let* ((LL (pivot (cdr L) (car L) () ())) (L1 (car LL)) (L2 (cadr LL)))
            (append (tri_rap L1) (cons (car L) (tri_rap L2)))
        )
    )
))

(define pivot (lambda (L n L1 L2)
    (if (null? L)
        (list L1 L2)
        (if (< (car L) n)
            (pivot (cdr L) n (cons (car L) L1) L2)
            (pivot (cdr L) n L1 (cons (car L) L2))
        )
    )
))

(pivot '(4 7 8 4 3 6 10 4 2) 5 () ())

(tri_rap '(5 4 7 8 4 3 6 10 4 2 1 11 34 7 6 68 3 5))
