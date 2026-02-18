(set-info :status unknown)
(set-logic ALL)

; Variables
(declare-fun x0  () Real)
(declare-fun x4  () Real)
(declare-fun x5  () Real)
(declare-fun x9  () Real)
(declare-fun x10 () Real)
(declare-fun x11 () Real)
(declare-fun x12 () Real)
(declare-fun x13 () Real)
(declare-fun x14 () Real)
(declare-fun x15 () Real)
(declare-fun x16 () Real)
(declare-fun x17 () Real)
(declare-fun x18 () Real)
(declare-fun x19 () Real)
(declare-fun x20 () Real)
(declare-fun x21 () Real)
(declare-fun x22 () Real)
(declare-fun x23 () Real)
(declare-fun x24 () Real)
(declare-fun x25 () Real)
(declare-fun x26 () Real)
(declare-fun x27 () Real)
(declare-fun x44 () Real)

; Axiomatized power function
(declare-fun pow (Real Real) Real)

(assert
 (and
  ; Pow definition (axioms)
  (forall ((c27 Real)) (= 1.0 (pow c27 0.0)))
  ;(forall ((c27 Real) (c28 Real)) (= (pow c27 c28) (^ c27 c28)))
  (forall ((c27 Real)) (= (pow c27 1.0) c27))
  (forall ((c27 Real) (c28 Real) (c29 Real))
    (= (pow c27 (+ c28 c29)) (* (pow c27 c28) (pow c27 c29))))
  (forall ((c27 Real) (c28 Real) (c29 Real))
    (= (pow c27 (- c28 c29)) (/ (pow c27 c28) (pow c27 c29))))
  
  ; Mantissa implicit bit
  ;(= x4 (+ (/ x0 128.0) 1.0))
  ;(= x9 (+ (/ x5 128.0) 1.0))
  
  ; Mantissa product
  (= x10 (* x0 x5))
  
  ; Max exponent
  (= x19 (+ x11 x15))
  (= x20 (+ x12 x16))
  (= x22 (+ x13 x17))
  (= x23 (+ x14 x18))
  (= x21 (ite (>= x19 x20) x19 x20))
  (= x24 (ite (>= x22 x23) x22 x23))
  (= x25 (ite (>= x21 x24) x21 x24))
  
  ; Shift amount
  (= x26 (- x25 x19))
  
  ; Shifted mantissa
  (= x27 (/ x10 (pow 2.0 x26)))
  
  ; Shifted mantissa, outer spec
  (let ((_let_1 (+ x11 x15)))
    (let ((_let_2 (+ x14 x18)))
      (let ((_let_3 (+ x13 x17)))
        (let ((_let_4 (+ x12 x16)))
          (let ((_let_5 (ite (>= _let_1 _let_4) _let_1 _let_4)))
            (let ((_let_6 (ite (>= _let_5 _let_3) _let_5 _let_3)))
              (= x44
                 (/ (* x0 x5) (pow 2.0 (- (ite (>= _let_6 _let_2) _let_6 _let_2) _let_1))))))))))
  
  (distinct x44 x27)
 )
)

(check-sat)
