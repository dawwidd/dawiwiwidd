reversed([],[]).
reversed([H|T],L):-reversed(T,RevL),append(RevL,[H],L).

symetryczna([]).
symetryczna(L):-reversed(L,L).


parami([],[]).
parami([A,B|T],[[A,B]|T1]):-parami(T,T1).


polowki([],[],[]).
polowki([H|L],[H|L1],[H2|L2]):-append(L1,[H2|L2],L), append(L1,L2,LC), polowki(LC,L1,L2).



sumuj([],0).
sumuj([H|T],S):-sumuj(T,S1), S is S1+H.


ile_dodatnich([],0).
ile_dodatnich([H|T],N):-ile_dodatnich(T,N1), (H>0 -> N is N1+1 ; H=<0 -> N is N1).


plus_minus([],0).
plus_minus([H|T],N):-plus_minus(T,N1), (H='+' -> N is N1+1 ; H='-' -> N is N1-1).


wstawiaj(T,H,1,[H|T]).
wstawiaj([H|T],X,I,[H|T1]):-I>0, I1 is I-1, wstawiaj(T,X,I1,T1).


usuwaj(L,0,L).
usuwaj([_|T],I,L):-I>0, I1 is I-1, usuwaj(T,I1,L).


rozdziel([],_,[],[]).
rozdziel([H|T],X,[H|T1],T2):-H<X, rozdziel(T,X,T1,T2).
rozdziel([H|T],X,T1,[H|T2]):-H>=X, rozdziel(T,X,T1,T2).


powiel([],[],[]).
powiel([H|T],[1|T1],[H|T2]):-powiel(T,T1,T2).
powiel([H|T],[X|T1],[H|T2]):-X>1,X1 is X-1, powiel([H|T],[X1|T1],T2).
