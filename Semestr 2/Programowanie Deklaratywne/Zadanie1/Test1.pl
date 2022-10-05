ostatni(X,[X]).
ostatni(X,[_|L]):-ostatni(X,L).

przedostatni(X,[X,_]).
przedostatni(X,[_|L]):-przedostatni(X,L).

nakoniec(X,[],[X]).
nakoniec(X,[H|T],[H|T1]):-nakoniec(X,T,T1).

bezostatniego([_],[]).
bezostatniego([H|L1],[H|L2]):-bezostatniego(L1,L2).

podwajaj([],[]).
podwajaj([H|T1],[H,H|T2]):-podwajaj(T1,T2).

codrugi([],[]).
codrugi([_],[]).
codrugi([_,H|T1],[H|T2]):-codrugi(T1,T2).

splataj([],[],[]).
splataj([H1|T1],[H2|T2],[H1,H2|T3]):-splataj(T1,T2,T3).

lewoprawo(X,[X|T],[],T).
lewoprawo(X,[H|T],[H|T1],T2):-lewoprawo(X,T,T1,T2).

wymiana(_,_,[],[]).
wymiana(X,Y,[X|T],[Y|T1]):-!,wymiana(X,Y,T,T1).
wymiana(X,Y,[H|T],[H|T1]):-wymiana(X,Y,T,T1).
