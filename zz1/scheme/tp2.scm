;;exercice 1


(define quel-que-soit? (lambda (L P)
    (if (null? L) #t
        (and (P (car L)) (quel-que-soit? (cdr L) P))
    )
))


(define tous-egaux (lambda (L)
    (quel-que-soit? (cdr L)(lambda (x) 
        (equal? (car L) x)
    ))
))


(tous-egaux '(1 1 1 1))


(define existe? (lambda (L P)
    (if (null? L) #f
        (or (P (car L)) (existe? (cdr L) P))
    )
))


(define tous-egaux (lambda (L)
    (not (existe? (cdr L) (lambda (x)
        (not (equal? (car L) x))
    )))
))


(define tous-diff (lambda (L)
    (quel-que-soit? (cdr L) (lambda (x)
        (unique? x L)
    ))
))


(define unique? (lambda (x L)
    (if  (null? (cdr L))
        #t
        (if (equal? x (car L))
            (absent? x (cdr L))
            (unique? x (cdr L))
         )
    )
))


(define absent? (lambda (x L)
    (if (null? L)
        #t
        (and (not (equal? x (car L))) (absent? x (cdr L)))
    )
))


(tous-diff '(1 2 2))


;;------------------------------------------------------------------------------------------------
;;exercice 2


(define RS (lambda (n f n0 un0)
    (if (= n n0)
        un0
        (f (RS (- n 1) f n0 un0) n)
    )
))


(define fact (lambda (n)
    (RS n * 0 1)
))


(define som_int (lambda (n)
    (RS n + 1 1)
))


(define som_carre (lambda (n)
    (RS n (lambda (un-1 n) (+ un-1 (* n n))) 1 1 n)
))


(define fibo (lambda (n)
    (car (RS n (lambda (un-1 n) 
        (list (+ (car un-1) (cadr un-1)) (car un-1))) 0 '(1 0)
    )))
)


(fibo 7)


(define RD (lambda (f n n0 un0 un0+1)
    (if (= n n0)
        un0
        (car (RS n (lambda(un-1 n)
            (list (f (car un-1) (cadr un-1) n) (car un-1))) (+ n0 1) (list un0+1 un0)
        ))
    )
))


(define fibo2 (lambda (n)
    (RD (lambda(a b c) (+ a b))
        n
        0
        1
        1
    )
))


(fibo2 7)


;;------------------------------------------------------------------------------------------------
;;exercice 6


(define trace (lambda(M)
    (if (null? M)
        0
        (let ((suiv (trace (cdr M))))
            (+ (cadar M) suiv)
        )
    )
))


(trace '((11 21 31) (12 22 32) (13 23 33)))


(define transp (