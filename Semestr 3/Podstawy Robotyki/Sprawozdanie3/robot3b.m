#dane z tabeli 3, grupa 3
P1 = [540.45, 54.37, 779.72];
P2 = [309.49, 13.18, 709.13];
P3 = [361.46, 287.75, 834.45];
P4 = [326.16, 459.75, 746.63];

x1 = P1(1); y1 = P1(2); z1 = P1(3);
x2 = P2(1); y2 = P2(2); z2 = P2(3);
x3 = P3(1); y3 = P3(2); z3 = P3(3);
x4 = P4(1); y4 = P4(2); z4 = P4(3);

#równanie kuli:                    (x-h)^2 + (y-k)^2 + (z-l)^2 = r^2
#inna forma równania kuli:         x^2 + y^2 + z^2 + Dx + Ey + Fz + G = 0
#relacje pomiędzy współczynnikami: D=-2h, E=-2k, F=-2l, G=h^2+k^2+l^2-R^2
#zatem: R=sqrt(D^2 + E^2 + F^2 - 4*G)/2, środek kuli: (-D/2, -E/2, -F/2)

#Obliczenie współczynników D,E,F i G z układu równań za pomocą metody Cramera
t1 = -(x1^2+y1^2+z1^2);
t2 = -(x2^2+y2^2+z2^2);
t3 = -(x3^2+y3^2+z3^2);
t4 = -(x4^2+y4^2+z4^2);


M = [x1 y1 z1 1
     x2 y2 z2 1
     x3 y3 z3 1
     x4 y4 z4 1];
     
T = det(M);

MD = [t1 y1 z1 1; t2 y2 z2 1; t3 y3 z3 1; t4 y4 z4 1];
ME = [x1 t1 z1 1; x2 t2 z2 1; x3 t3 z3 1; x4 t4 z4 1];
MF = [x1 y1 t1 1; x2 y2 t2 1; x3 y3 t3 1; x4 y4 t4 1];
MG = [x1 y1 z1 t1; x2 y2 z2 t2; x3 y3 z3 t3; x4 y4 z4 t4];

D = det(MD)/T;
E = det(ME)/T;
F = det(MF)/T;
G = det(MG)/T;

#położenie punktu TCP (Tool Center Point)
TCP = [-D/2, -E/2, -F/2]

#odległość punktu TCP od środka kołnierza (początku układu $FLANGE)
R = sqrt(D^2 + E^2 + F^2 - 4*G)/2
