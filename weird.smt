(set-info :status unknown)
(set-logic ALL)

; Variables
;(declare-fun x0  () Real)

; Axiomatized power function
(declare-fun pow (Real Real) Real)

(assert
 (and
  ; Pow definition (axioms)
  (forall ((c27 Real)) (= (pow c27 0.0) 1.0))
  (forall ((c27 Real)) (= (pow c27 1.0) c27))
  (forall ((c27 Real) (c28 Real) (c29 Real))
    (= (pow c27 (+ c28 c29)) (* (pow c27 c28) (pow c27 c29))))
  (forall ((c27 Real) (c28 Real) (c29 Real))
    (= (pow c27 (- c28 c29)) (/ (pow c27 c28) (pow c27 c29))))
  
  
  ;(distinct (pow 2.0 (- 0.0 4.0)) (/ (pow 2.0 0.0) (pow 2.0 4.0)))
  ;(distinct (pow 2.0 0.0) 1.0)
  
  (distinct (pow 2.0 (- 0.0 4.0)) (/ 1.0 (pow 2.0 4.0)))
  ;(distinct (* x0 (pow 2.0 (- 0.0 4.0))) (/ x0 (pow 2.0 4.0)))
  ;(distinct
  ;    (* x0 (pow 2.0 (- 0.0 4.0)))
  ;    (/ x0 (pow 2.0 4.0)))
 )
)

(check-sat)
