ostatni(X,[X]).
ostatni(X,[_|T]):-ostatni(X,T).

przedostatni(X,[X,_]).
przedostatni(X,[_|T]):-przedostatni(X,T).

nakoniec(X,[],[X]).
nakoniec(X,[H|L1],[H|L2]):-nakoniec(X,L1,L2).

bezostatniego([_],[]).
bezostatniego([H|L1],[H,L2]):-bezostatniego(L1,L2).

podwajaj([],[]).
podwajaj([H|T1],[H,H|T2]):-podwajaj(T1,T2).

codrugi([],[]).
codrugi([_],[]).
codrugi([_,H|T1],[H|T2]):-codrugi(T1,T2).

splataj([],[],[]).
splataj([H1|T1],[H2|T2],[H1,H2|T3]):-splataj(T1,T2,T3).

lewoprawo(X,[X|T],[],T).
lewoprawo(X,[H|T1],[H|T2],T3):-lewoprawo(X,T1,T2,T3).

polacz([],[]).
polacz([H|T],L):-polacz(T,T1),append(H,T1,L).

wymiana(_,_,[],[]).
wymiana(X,Y,[X|T1],[Y|T2]):-!,wymiana(X,Y,T1,T2).
wymiana(X,Y,[H|T1],[H|T2]):-wymiana(X,Y,T1,T2).

