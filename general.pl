signal(out(G),1) :- type(G,and), connected(X1,in(1,G)), connected(X2,in(2,G)), signal(X1,1), signal(X2,1).
signal(out(G),0) :- type(G,and), connected(X1,in(1,G)), signal(X1,0).
signal(out(G),0) :- type(G,and), connected(X2,in(2,G)), signal(X2,0).
 
signal(out(G),1) :- type(G,or), connected(X1,in(1,G)), signal(X1,1).
signal(out(G),1) :- type(G,or), connected(X2,in(2,G)), signal(X2,1).
signal(out(G),0) :- type(G,or), connected(X1,in(1,G)), connected(X2,in(2,G)), signal(X1,0), signal(X2,0).

signal(out(G),1) :- type(G,not), connected(X,in(1,G)), signal(X,0).
signal(out(G),0) :- type(G,not), connected(X,in(1,G)), signal(X,1).

signal(X,A) :- connected(Y,X), signal(Y,A).

signal(a,1).
signal(b,0).
