najwiekszy([X],X).
najwiekszy([H|T],Max):-najwiekszy(T,MaxCr),H > MaxCr, Max is H.
najwiekszy([H|T],Max):-najwiekszy(T,MaxCr),H=< MaxCr, Max is MaxCr.


liniowa([X,Y]).
liniowa([X,Y,Z|T]):-liniowa([Y,Z|T]),X-Y =:= Y-Z.


rozbij([],[],[]).
rozbij([H|T],[1|T1],[[H]|T2]):-rozbij(T,T1,T2).
rozbij([H|T],[X|T1],[[H|T2]|T3]):-X>1, X1 is X-1, rozbij(T,[X1|T1],[T2|T3]).


przynaleznosc([],[X,Y],[],[]).
przynaleznosc([H|T],[D,G],[H|T1],T2):-H>=D,H=<G,przynaleznosc(T,[D,G],T1,T2).
przynaleznosc([H|T],[D,G],T1,[H|T2]):-H<D, przynaleznosc(T,[D,G],T1,T2).
przynaleznosc([H|T],[D,G],T1,[H|T2]):-H>G, przynaleznosc(T,[D,G],T1,T2).




rozdziel([],_,[],[]).
rozdziel([H|T],X,T1,[H|T2]):-H<X,rozdziel(T,X,T1,T2).
rozdziel([H|T],X,[H|T1],T2):-H>=X, rozdziel(T,X,T1,T2).

szybkisort([],[]).
szybkisort([H|T],S):-rozdziel(T,H,W,M),szybkisort(M,MS),szybkisort(W,WS),append(MS,[H|WS],S).


doposort([H|T],X,[X,H|T]):-H>=X,!.
doposort([],X,[X]):-!.
doposort([H|T],X,[H|T1]):-doposort(T,X,T1).

wstawsort([],[]).
wstawsort([H|T],S):-wstawsort(T,S1),doposort(S1,H,S).


unikalne([],[]).
unikalne([H|T],[H|T1]):- \+member(H,T),!,unikalne(T,T1).
unikalne([_|T],U):-unikalne(T,U).


najblizszy(X,[Y],Y):-!.
najblizszy(X,[H|T],Y):-najblizszy(X,T,Y1),Diff1 is abs(X-H), Diff2 is abs(Y1-H), Diff1 =< Diff2, Y is H.
najblizszy(X,[H|T],Y):-najblizszy(X,T,Y1),Diff1 is abs(X-H), Diff2 is abs(Y1-H), Diff1 > Diff2, Y is Y1.


ciagliczb(X,X,[X]):-!.
ciagliczb(X,Y,[X|T]):-X<Y,X1 is X+1,!, ciagliczb(X1,Y,T).

odsiewaj(X,[],[]).
odsiewaj(X,[H|T],[H|T1]):- mod(X,H)=\=0, odsiewaj(X,T,T1).
odsiewaj(X,[H|T],T1):- mod(X,H)=:=0,odsiewaj(X,T,T1).

sito([],[]).
sito([H|T],L):-odsiewaj(H,T,LT),sito(LT,D),append([H],D,L).

eratostenes(N,L):-ciagliczb(2,N,Ciag),sito(Ciag,L).

%zbior 7

podzielniki(N,N,[]).
podzielniki(N,D,[D|T]):-D<N,mod(N,D)=:=0,D1 is D+1, podzielniki(N,D1,T),!.
podzielniki(N,D,T):-D<N,mod(N,D)=\=0,D1 is D+1, podzielniki(N,D1,T),!.


doskonala(N):-podzielniki(N,1,L),sumuj(L,N).



przekroj(_,_,[]).
przekroj([H|T],[H|T1],[H|T2]):-przekroj(T,T1,T2).
przekroj([H|T],[H1|T1],[H2|T2]):-przekroj(T,[H1|T1],[H2|T2]),H<H2.
przekroj([H|T],[H1|T1],[H2|T2]):-przekroj([H|T],T1,[H2|T2]),H1<H2.


glowyogony([],[],[]).
glowyogony([[H|HT]|T],[H|T1],[HT|T2]):-glowyogony(T,T1,T2).

slad([X],X).
slad([H|T],X):-glowyogony([H|T],[GG|_],[_|TO]),slad(TO,X1),X is X1+GG.


rozszerzaj([[X,Y]],[X,Y]).
rozszerzaj([[X,Y]|T],[X1,Y1]):-rozszerzaj(T,[X1,Y1]), X1=<X, Y1>=Y.
rozszerzaj([[X,Y]|T],[X,Y1]) :-rozszerzaj(T,[X1,Y1]), X1>=X, Y1>=Y.
rozszerzaj([[X,Y]|T],[X1,Y]) :-rozszerzaj(T,[X1,Y1]), X1=<X, Y1=<Y.
rozszerzaj([[X,Y]|T],[X,Y])  :-rozszerzaj(T,[X1,Y1]), X1>=X, Y1=<Y.


liczpodziel(N,N,0):-!.
liczpodziel(N,D,C):-mod(N,D)=:=0, D1 is D+1, liczpodziel(N,D1,C1),!,C is C1+1.
liczpodziel(N,D,C):-mod(N,D)=\=0, D1 is D+1, liczpodziel(N,D1,C),!.

antyp([],X).
antyp([H|T],X):-liczpodziel(H,1,C),!,C<X,antyp(T,X),!.

antypierwsza(1):-!.
antypierwsza(X):-X>0,X1 is X-1, ciagliczb(1,X1,L),liczpodziel(X,1,X2),!,antyp(L,X2).


wpolu([],[LD,PG],[]):-!.
wpolu([[X,Y]|T],[[X1,Y1],[X2,Y2]],[[X,Y]|T1]):-X>=X1,Y>=Y1,X=<X2,Y=<Y2,wpolu(T,[[X1,Y1],[X2,Y2]],T1),!.
wpolu([[X,Y]|T],[[X1,Y1],[X2,Y2]],T1):-(X<X1;Y<Y1;X>X2;Y>Y2),wpolu(T,[[X1,Y1],[X2,Y2]],T1),!.


minX([[X,_]],X):-!.
minX([[X,_]|T],Min):-minX(T,NMin), X<NMin, Min is X,!.
minX([[X,_]|T],Min):-minX(T,NMin), X>=NMin, Min is NMin, !.

maxX([[X,_]],X):-!.
maxX([[X,_]|T],Max):-maxX(T,NMax), X>NMax, Max is X,!.
maxX([[X,_]|T],Max):-maxX(T,NMax), X=<NMax, Max is NMax, !.

minY([[_,Y]],Y):-!.
minY([[_,Y]|T],Min):-minY(T,NMin), Y<NMin, Min is Y,!.
minY([[_,Y]|T],Min):-minY(T,NMin), Y>=NMin, Min is NMin, !.

maxY([[_,Y]],Y):-!.
maxY([[_,Y]|T],Max):-maxY(T,NMax), Y>NMax, Max is Y,!.
maxY([[_,Y]|T],Max):-maxY(T,NMax), Y=<NMax, Max is NMax, !.

minpole(L,[[Xmin,Ymin],[Xmax,Ymax]]):-minX(L,Xmin),minY(L,Ymin),maxX(L,Xmax),maxY(L,Ymax).


ciagFib(N,F1,F2,[]):-F1>N.
ciagFib(N,F1,F2,[F1|T]):-F1=<N,F3 is F1 + F2, ciagFib(N,F2,F3,T),!.




decnabin(0,[0]):-!.
decnabin(1,[1]):-!.
decnabin(X,L):-Test is mod(X,2), Test==(0), X1 is div(X,2), append(L1,[0],L), decnabin(X1,L1),!.
decnabin(X,L):-Test is mod(X,2), Test==(1), X1 is div(X,2), append(L1,[1],L), decnabin(X1,L1),!.


decnabinL([X],[B]):-decnabin(X,B).
decnabinL([H|T],L):-decnabinL(T,LB), decnabin(H,BH), append([BH],LB,L).

podrzad([],0,0).
podrzad([X|T],LC,Prv):-podrzad(T,C1,X),C is C1+1, append(C,C1,LC),!.
podrzad([Y|T],LC,Prv):-podrzad(T,LC,X),X=\=Y.


dzielniki(N,N,[N]).
dzielniki(N,D,[D|T]):-D=<N,mod(N,D)=:=0,D1 is D+1, dzielniki(N,D1,T),!.
dzielniki(N,D,T):-D=<N,mod(N,D)=\=0,D1 is D+1, dzielniki(N,D1,T),!.


dzielnikiL([X],[D]):-dzielniki(X,1,D).
dzielnikiL([H|T],L):-dzielnikiL(T,LD),dzielniki(H,1,DH),append([DH],LD,L).


sumuj([X],X).
sumuj([H|T],S):-sumuj(T,S1),S is S1+H.

final(L,LF):-dzielniki(L,LD),szybkisort(LD,LF).

naliste(0,[]):-!.
naliste(A,L):-!,A>0, append(L1,[B],L), B is mod(A,10), A1 is div(A,10), naliste(A1,L1),!.
naliczbe(0,[]):-!.
naliczbe(A,L):-!,append(L1,[B],L), naliczbe(A1,L1), A is B + A1*10.

