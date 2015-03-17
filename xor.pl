connected(a,in(1,a1)).
connected(b,in(1,n1)).
connected(out(n1),in(2,a1)).

connected(a,in(1,n2)).
connected(b,in(2,a2)).
connected(out(n2),in(1,a2)).

connected(out(a1), in(1,o1)).
connected(out(a2), in(2,o1)).

type(a1,and).
type(a2,and).
type(n1,not).
type(n2,not).
type(o1,or).
