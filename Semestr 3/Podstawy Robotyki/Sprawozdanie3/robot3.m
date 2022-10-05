#dane z tabeli 3, grupa 3
P1 = [111.67, 451.8, 242.17];
P2 = [393.23, 388.98, 45.33];
P3 = [134.38, 316.94, 373.42];

#obliczenia wektorów jednostkowych
P12 = [P2(1)-P1(1),P2(2)-P1(2),P2(3)-P1(3)];
P12_l = sqrt(P12(1)^2+P12(2)^2+P12(3)^2);
i = 1/P12_l * P12;

P13 = [P3(1)-P1(1),P3(2)-P1(2),P3(3)-P1(3)];
P13_l = sqrt(P13(1)^2+P13(2)^2+P13(3)^2);
u = 1/P13_l * P13;

k = cross(i,u);
j = cross(k,i);

#macierz rotacji
TB0 = [i
       j
       k].'
       
#obliczanie kątów rotacji
function [alfa,beta,gamma] = m2a(M)
  
  alfa = atan2 (M(2,1), M(1,1));
  sinAlfa = sin(alfa);   
  cosAlfa = cos(alfa);
  
  sinBeta = -M(3,1);
  cosBeta = cosAlfa * M(1,1) + sinAlfa * M(2,1);
  beta = atan2(sinBeta, cosBeta);
  
  sinGamma =  sinAlfa * M(1,3) - cosAlfa * M(2,3);
  cosGamma = -sinAlfa * M(1,2) + cosAlfa * M(2,2);
  gamma = atan2(sinGamma, cosGamma);
  
endfunction


[A,B,C]=m2a(TB0)