pokrycie(kura,pi�ra).
pokrycie(wr�bel,pi�ra).
pokrycie(sikorka,pi�ra).
ruch(kura,chodzenie).
ruch(wr�bel,latanie).
ruch(sikorka,latanie).

ptak(X):-pokrycie(X,pi�ra),ruch(X,latanie).
