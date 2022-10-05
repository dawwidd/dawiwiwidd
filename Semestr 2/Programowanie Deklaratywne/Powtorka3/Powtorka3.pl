%potwierdzenie wyboru reguly

suma_do(1,1):-!.
suma_do(N,Razem):-
	N1 is N-1,
	suma_do(N1,Razem1),
	Razem is Razem1 + N.

%konczenie generowania mozliwych rozwiazan

zawiera(X,[X|_]).
zawiera(X,[_|T]):-zawiera(X,T).

zawiera_przyn_1(X,[X|_]):-!.
zawiera_przyn_1(X,[_|T]):-zawiera_przyn_1(X,T).

%technika fail

kobieta(maria).
kobieta(ewa).

mezczyzna(darek).
mezczyzna(tomek).

malzenstwo(maria,darek).
malzenstwo(ewa,tomek).

obcokrajowiec(tomek).

zarobek(darek,100).
zarobek(tomek,200).
zarobek(maria,300).
zarobek(ewa,400).

przecietny_podatnik(X):-
	\+obcokrajowiec(X), % \+ not
	\+(((malzenstwo(X,Y) ; malzenstwo(Y,X)), zarobek(Y,Z),Z<200)),
	zarobek(X,Z),Z<300.


przecietny_podatnik2(X):-obcokrajowiec(X),!,fail.
przecietny_podatnik2(X):-(malzenstwo(X,Y) ; malzenstwo(Y,X)),
	zarobek(Y,Z),Z<200,!,fail.
przecietny_podatnik2(X):-zarobek(X,Z),Z<300.
