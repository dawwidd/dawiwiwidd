pokrycie(kura,pióra).
pokrycie(wróbel,pióra).
pokrycie(sikorka,pióra).
ruch(kura,chodzenie).
ruch(wróbel,latanie).
ruch(sikorka,latanie).

ptak(X):-pokrycie(X,pióra),ruch(X,latanie).
