rozdziel([],_,[],[]).
rozdziel([H|T],P,[H|T1],T2):-P>=H,!,rozdziel(T,P,T1,T2).
rozdziel([H|T],P,T1,[H|T2]):-P<H,!,rozdziel(T,P,T1,T2).

quicksort([],[]).
quicksort([H|T],S):-rozdziel(T,H,M,W),quicksort(M,MS),quicksort(W,WS),append(MS,[H|WS],S).

mediana([X],X):-mediana([X],X,1).
mediana([H|T],X,C):-mediana(T,X,C1), C1 is C+1, length(T)=:=C1.

rotacjaL([H|T],L):-append(T,[H],L).
rotacjaR(L,R):-rotacjaL(R,L).

paruj([],[]).
paruj([X,Y|T],[[X,Y]|T1]):-paruj(T,T1).

pitagoras([X1,Y1],[X2,Y2],Z):-Z is (X1-X2)**2+(Y1-Y2)**2.

najwiekszy([X],X).
najwiekszy([H|T],Max):-najwiekszy(T,NMax),H>NMax, Max is H.
najwiekszy([H|T],Max):-najwiekszy(T,NMax),H=<NMax, Max is NMax.
