      SUBROUTINE HAMMERSORT(N,A,V,JDA)
C
C SORT THE REAL ARRAY A BY DECREASING VALUES (DERIVED FROM SUBROUTINE
C SORTZV OF THE C.E.R.N. LIBRARY).
C
C JDA           = LENGTH OF ARRAY A;
C N             = NUMBER OF ELEMENTS OF A TO BE SORTED;
C V(I) (INPUT)  = POINTER TO THE I-TH ELEMENT TO BE SORTED;
C V(I) (OUTPUT) = POINTER TO THE I-TH ELEMENT OF THE SORTED ARRAY.
C
C ON RETURN, ARRAY A IS UNCHANGED.
C
      INTEGER V(N),IU(20),IL(20)
      REAL    A(JDA)
      II = 1
      JJ = N
      IF ( N .LE. 1 ) RETURN
      M = 1
      I = II
      J = JJ
   10 IF ( I .GE. J ) GO TO 80
   20 K = I
      IJ = (J + I)/2
      IV = V(IJ)
      T = A(IV)
      KI = V(I)
      IF ( A(KI) .GE. T ) GO TO 30
      V(IJ) = KI
      V(I) = IV
      IV = V(IJ)
      T = A(IV)
   30 L = J
      KI = V(J)
      IF ( A(KI) .LE. T ) GO TO 50
      V(IJ) = KI
      V(J) = IV
      IV = V(IJ)
      T = A(IV)
      KI = V(I)
      IF ( A(KI) .GE. T ) GO TO 50
      V(IJ) = KI
      V(I) = IV
      IV = V(IJ)
      T = A(IV)
      GO TO 50
   40 V(L) = V(K)
      V(K) = IVT
   50 L = L - 1
      KI = V(L)
      IF ( A(KI) .LT. T ) GO TO 50
      IVT = KI
   60 K = K + 1
      KI = V(K)
      IF ( A(KI) .GT. T ) GO TO 60
      IF ( K .LE. L ) GO TO 40
      IF ( L - I .LE. J - K ) GO TO 70
      IL(M) = I
      IU(M) = L
      I = K
      M = M + 1
      GO TO 90
   70 IL(M) = K
      IU(M) = J
      J = L
      M = M + 1
      GO TO 90
   80 M = M - 1
      IF ( M .EQ. 0 ) RETURN
      I = IL(M)
      J = IU(M)
   90 IF ( J - I .GE. II ) GO TO 20
      IF ( I .EQ. II ) GO TO 10
      I = I - 1
  100 I = I + 1
      IF ( I .EQ. J ) GO TO 80
      IV = V(I+1)
      T = A(IV)
      KI = V(I)
      IF ( A(KI) .GE. T ) GO TO 100
      K = I
  110 V(K+1) = V(K)
      K = K - 1
      KI = V(K)
      IF ( T .GT. A(KI) ) GO TO 110
      V(K+1) = IV
      GO TO 100
      END
