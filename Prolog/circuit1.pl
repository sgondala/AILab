high(1).
low(0).

connected(X1,X2) :- high(X1),high(X2).
connected(X1,X2) :- low(X1),low(X2).

nand(X,Y,Z) :- high(X),high(Y),low(Z).
nand(X,Y,Z) :- low(X),high(Y),high(Z).
nand(X,Y,Z) :- high(X),low(Y),high(Z).
nand(X,Y,Z) :- low(X),low(Y),high(Z).

not1(X,Y) :- nand(X,X,Y).
and1(X,Y,Z) :- nand(X,Y,Z1) , not1(Z,Z1).
or1(X,Y,Z) :- not1(X,X1),not1(Y,Y1),nand(X1,Y1,Z).
nor(X,Y,Z) :-  or1(X,Y,Z1),not1(Z1,Z).
