xor1(X,Y,Z) :- not1(X,X1),not1(Y,Y1),connected(X1,X2),connected(Y1,Y2),and1(X,Y2,Z1),and1(X2,Y,Z2),
		connected(Z1,Z3),connected(Z2,Z4),or1(Z3,Z4,Z).

fadd1(A,B,C,O1,O2) :- xor1(A,B,A1), xor1(A1,C,O1), and1(A,B,A2), and1(A1,C,A3), or1(A3,A2,O2).

verify(xor,[A,B|_],O) :- xor1(A,B,O),!.

verify(fadd,[A,B,C|_],[O1,O2|_]) :- fadd1(A,B,C,O1,O2),!.
