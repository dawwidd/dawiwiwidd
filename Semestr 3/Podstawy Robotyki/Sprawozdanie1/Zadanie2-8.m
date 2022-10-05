war = [];
u_sred = [];
war(1) = var(raw_measurement15);
war(2) = var(raw_measurement20);
war(3) = var(raw_measurement25);
war(4) = var(raw_measurement30);
war(5) = var(raw_measurement35);
war(6) = var(raw_measurement40);
war(7) = var(raw_measurement45);
war(8) = var(raw_measurement50);
war(9) = var(raw_measurement55);
war(10) = var(raw_measurement60);
war(11) = var(raw_measurement65);

u_sred(1) = mean(raw_measurement15);
u_sred(2) = mean(raw_measurement20);
u_sred(3) = mean(raw_measurement25);
u_sred(4) = mean(raw_measurement30);
u_sred(5) = mean(raw_measurement35);
u_sred(6) = mean(raw_measurement40);
u_sred(7) = mean(raw_measurement45);
u_sred(8) = mean(raw_measurement50);
u_sred(9) = mean(raw_measurement55);
u_sred(10) = mean(raw_measurement60);
u_sred(11) = mean(raw_measurement65);

d = [0.15, 0.20, 0.25, 0.30, 0.35, 0.40, 0.45, 0.50, 0.55, 0.60, 0.65];

figure
hold on;
plot(d, u_sred, "o")

#współczynniki wielomianów aproksymacyjnych
global k = polyfit(d, u_sred, 3);
global l = polyfit(d, u_sred, 4);
global m = polyfit(d, u_sred, 5);
global n = polyfit(d, u_sred, 6);

#seria danych do funkcji aproksymacyjnych, przedział <u_sred_min;u_sred_max>
#z krokiem 0.01
u_min = min(u_sred)
u_max = max(u_sred)
d_apr = u_min:0.01:u_max;

#funkcje aproksymacyjne (wielomiany stopnia od 3 do 6)
k_apr = k(1)*d_apr.^3+k(2)*d_apr.^2+k(3)*d_apr.^1+k(4);
l_apr = l(1)*d_apr.^4+l(2)*d_apr.^3+l(3)*d_apr.^2+l(4)*d_apr.^1+l(5);
m_apr = m(1)*d_apr.^5+m(2)*d_apr.^4+m(3)*d_apr.^3+m(4)*d_apr.^2+m(5)*d_apr.^1+m(6);
n_apr = n(1)*d_apr.^6+n(2)*d_apr.^5+n(3)*d_apr.^4+n(4)*d_apr.^3+n(5)*d_apr.^2+n(6)*d_apr.^1+n(7);

plot(d_apr, k_apr, "r--");
plot(d_apr, l_apr, "g--");
plot(d_apr, m_apr, "b--");
plot(d_apr, n_apr, "m--");
legend('d(u)', 'w_3', 'w_4', 'w_5', 'w_6');
axis([0 inf 0 inf]);
hold off;

#Liczenie przyblizonej odleglosci na podstawie sygnału z czujnika odleglosci
function d = LiczOdleglosc(u)
  global n;
  d = polyval(n,u);
endfunction

figure
#MK_0_180_C0
p = 0:0.225:180-0.225;
[xp,yp] = pol2cart(deg2rad(p), LiczOdleglosc(MK_0_180_C0));

#PK_0_180_C180
q = 0:0.9:180-0.9;
[xq,yq] = pol2cart(deg2rad(q), LiczOdleglosc(PK_0_180_C180));

#PK_0_180_C0
r = 0:0.9:180-0.9;
[xr,yr] = pol2cart(deg2rad(r), LiczOdleglosc(PK_0_180_C0));

#PK_0_180_C90
s = 0:0.9:180-0.9;
[xs,ys] = pol2cart(deg2rad(s), LiczOdleglosc(PK_0_180_C90));

#PK_180_0_C0
t = 180:-0.9:0+0.9;
[xt,yt] = pol2cart(deg2rad(t), LiczOdleglosc(PK_180_0_C0));


hold on
plot(xp,yp, "r.", 'MarkerSize', 15)
plot(xq,yq, "g.", 'MarkerSize', 15)
plot(xr,yr, "b.", 'MarkerSize', 15)
plot(xs,ys, "c.", 'MarkerSize', 15)
plot(xt,yt, "m.", 'MarkerSize', 15)
axis([-0.5 0.5 0 0.5])
legend('MK\_0\_180\_C0', 'PK\_0\_180\_C180', 'PK\_0\_180\_C0', 'PK\_0\_180\_C90', 'PK\_180\_0\_C0');
hold off


