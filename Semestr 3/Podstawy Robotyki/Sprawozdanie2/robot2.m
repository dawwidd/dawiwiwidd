a = pi/2;
b = pi/2;
g = pi/2;

function R=WyznaczMacierz(a,b,g)
  sa=sin(a);
  sb=sin(b);
  sg=sin(g);
  ca=cos(a);
  cb=cos(b);
  cg=cos(g);
  R= [ ca*cb*cg-sa*sg, -ca*cb*sg-sa*cg, ca*sb;
          sa*cb*cg+ca*sg, -sa*cb*sg+ca*cg, sa*sb;
          -sb*cg, sb*sg, cb];
endfunction


function [a,b,c] = WyznaczKaty(M)
  b=atan2(sqrt(pow2(M(1,3))+pow2(M(2,3))),M(3,3));
  if (b>0)
    
    a=atan2(M(2,3),M(1,3));
    b=atan2(sqrt(pow2(M(1,3))+pow2(M(2,3))),M(3,3));
    c=atan2(M(3,2), -M(3,1));
    
  else
    
    a=atan2(-M(2,3),-M(1,3));
    b=atan2(-sqrt(pow2(M(1,3))+pow2(M(2,3))),M(3,3));
    c=atan2(-M(3,2), M(3,1));
    
  endif
endfunction

function T = macierzT_DH(q)
  alfa=q(1);
  a=q(2);
  d=q(3);
  theta=q(4);
  T = [   cos(theta) -cos(alfa)*sin(theta)  sin(alfa)*sin(theta) a*cos(theta)
          sin(theta)  cos(alfa)*cos(theta) -sin(alfa)*cos(theta) a*sin(theta)
          0           sin(alfa)            cos(alfa)           d
          0           0                    0                   1];
endfunction

function T = macierzT_ZDH(q)
  alfa=q(1);
  a=q(2);
  d=q(3);
  theta=q(4);
  T = [   cos(theta)            -sin(theta)             0           a
          sin(theta)*cos(alfa)  cos(theta)*cos(alfa) -sin(alfa) -d*sin(alfa)
          sin(theta)*sin(alfa)  cos(theta)*cos(alfa)  cos(alfa)  d*cos(alfa)
          0                       0                     0           1];
endfunction

Rzyz=WyznaczMacierz(a,b,g)
[a,b,c]=WyznaczKaty(Rzyz)

#wszystkie katy theta przyjeto jako 30 stopni (pi/6)
#za d_i oraz a_i, tam gdzie to potrzebne, podstawiono 0,4m
theta = pi/2;
d = 1;
q1 = [ 0,    0, d, theta];
q2 = [ pi/2, 0, 0, theta];
q3 = [ 0,    d, 0, theta];
q4 = [ pi/2, 0, d, theta];
q5 = [-pi/2, 0, 0, theta];
q6 = [ pi/2, 0, d, theta];

T01 = macierzT_ZDH(q1);
T12 = macierzT_ZDH(q2);
T23 = macierzT_ZDH(q3);
T34 = macierzT_ZDH(q4);
T45 = macierzT_ZDH(q5);
T56 = macierzT_ZDH(q6);

T06 = T01*T12*T23*T34*T45*T56
