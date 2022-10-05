decnabin(0,[0]):-!.
decnabin(1,[1]):-!.
decnabin(X,L):-mod(X,2)==0,X1 is div(X,2),append(L1,[0],L),decnabin(X1,L1),!.
decnabin(X,L):-mod(X,2)==1,X1 is div(X,2),append(L1,[1],L),decnabin(X1,L1),!.

rozdziel([],_,[],[]).
rozdziel([H|T],X,T1,[H|T2]):-H>=X,rozdziel(T,X,T1,T2).
rozdziel([H|T],X,[H|T1],T2):-H<X, rozdziel(T,X,T1,T2).

szybkisort([],[]).
szybkisort([H|T],S):-rozdziel(T,H,W,M),szybkisort(M,MS),szybkisort(W,WS),append(MS,[H|WS],S).


ilewyst([],_,0).
ilewyst([H|T],H,N):- ilewyst(T,H,N1),N is N1 + 1.
ilewyst([H|T],Y,N):- ilewyst(T,Y,N),H\=Y.

binnadec(L,X):-binnadec(L,X,_),!.
binnadec([1],1,0):-!.
binnadec([0],0,0):-!.
binnadec([H|T],D,P):-binnadec(T,Dt,Pt),P is Pt+1, D is Dt + H* 2**P.

rotacjaL
