next(swinoujscie,kolobrzeg).
next(swinoujscie, szczecin).
next(kolobrzeg,ustka).
next(ustka, gdansk).
next(gdansk,torun).
next(gdansk,olsztyn).
next(olsztyn,torun).
next(olsztyn,bialystok).
next(szczecin,bydgoszcz).
next(szczecin, gorzow-wlkp).
next(bydgoszcz,torun).
next(bydgoszcz,poznan).
next(poznan,torun).
next(gorzow-wlkp,poznan).
next(gorzow-wlkp,zielona-gora).
next(zielona-gora,poznan).
next(zielona-góra,wroclaw).
next(torun,lodz).
next(torun,warszawa).
next(bialystok, warszawa).
next(bialystok,lublin).
next(poznan,lodz).
next(warszawa,radom).
next(warszawa,lodz).
next(radom,lublin).
next(radom,kielce).
next(wroclaw,lodz).
next(lodz,radom).
next(lodz,czêstochowa).
next(czestochowa,kielce).
next(czestochowa,katowice).
next(katowice,krakow).
next(kielce,krakow).
next(kielce,rzeszow).
next(lublin,kielce).
next(lublin,rzeszow).
next(krakow,rzeszow).

polaczenie(X,Y):-next(X,Y).
polaczenie(X,Y):-next(X,Z),polaczenie(Z,Y).

zjazd(X,Y,Z):-next(X,Y),Z=Y.
zjazd(X,Y,Z):-next(X,K),zjazd(K,Y,Z).

trasa(D,E,obok(D,E)):-next(D,E).
trasa(D,E,obok(D,X)):-next(D,Z),trasa(Z,E,X).

trasa2(D,E,obok(D,E)):-next(D,E).
trasa2(D,E,obok(X,E)):-next(Z,E),trasa(D,Z,X).


%%%%%%%%%%%%%%%%%%%%%%%%%%%
%przeszukiwanie rekurencyjne

zawiera(X,[X|_]).
zawiera(X,[_|T]):-zawiera(X,T).

%odwzorowywanie

przesun(a,b).
przesun(b,c).
przesun(c,d).

szyfruj([],[]).
szyfruj([H|T], [G|O]):-przesun(H,G),szyfruj(T,O).

%laczenie (append)

zlacz([],L,L).
zlacz([X|L1],L2,[X|L3]):-zlacz(L1,L2,L3).

%akumulatory

dlugosc([],0).
dlugosc([_|Tail],Len):-dlugosc(Tail,LenTail),Len is Lentail + 1.

lenA(List,Len):-lenA(List,0,Len).
lenA([],Len,Len).
lenA([_|Tail],Acc,Len):-NewAcc is Acc + 1, lenA(Tail, NewAcc, Len).

%top down

fibTD(0,0).
fibTD(1,1).
fibTD(N,X):-N>1,
	N1 is N-1,
	N2 is N-2,
	fibTD(N1,X1),
	fibTD(N2,X2),
	X is X1 + X2.

%bottom up

%fibBU(N,X):-fibBU(0,0,1,N,X).
%fibBU(N,X,_,N,X).
%fibBU(N1,X1,X2,N,X):-
	%N1<N,

