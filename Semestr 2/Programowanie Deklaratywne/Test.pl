m(L,X):-member(X,L),a(X,L).
a(X,L):-L=[]; L=[H|T], H=<X,a(X,T).

f(a,m).
f(a,n).

p(A,B):-not(A=B),f(Z,A),f(Z,B).

op(100,xfy,^).
op(100,fy,~).
