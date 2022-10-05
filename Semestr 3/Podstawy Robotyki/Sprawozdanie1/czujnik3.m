SRED = [];
SRED(1) = mean(raw_measurement15);
SRED(2) = mean(raw_measurement20);
SRED(3) = mean(raw_measurement25);
SRED(4) = mean(raw_measurement30);
SRED(5) = mean(raw_measurement35);
SRED(6) = mean(raw_measurement40);
SRED(7) = mean(raw_measurement45);
SRED(8) = mean(raw_measurement50);
SRED(9) = mean(raw_measurement55);
SRED(10) = mean(raw_measurement60);
SRED(11) = mean(raw_measurement65);

ODL = [15,20,25,30,35,40,45,50,55,60,65];

global a_i6 = polyfit(SRED, ODL, 6);
# 6.
function LiczOdleglosc(u)
  global a_i6
  d = polyval(a_i6,u)
endfunction

# PK_0_180_C0  Rad = deg2rad(Q_ODL);
Deg = 0:0.9:179.1;
Rad = deg2rad(Deg);
Odl1 = polyval(a_i6,PK_0_180_C0)
[xData1,yData1] = pol2cart(Rad, Odl1)
figure
plot(xData1,yData1, '.c')
hold on;

Odl2 = polyval(a_i6,PK_0_180_C180)
[xData2,yData2] = pol2cart(Rad, Odl2)

plot(xData2,yData2, '.m')

Odl3 = polyval(a_i6,PK_0_180_C90)
[xData3,yData3] = pol2cart(Rad, Odl3)

plot(xData3,yData3, '.g')

Odl4 = polyval(a_i6,PK_180_0_C0)
[xData4,yData4] = pol2cart(Rad, Odl4)

plot(xData4,yData4, '.k')
hold off;
Rad2 = 0:0.225:179.9
Odl5 = polyval(a_i6,MK_0_180_C0)
[xData5,yData5] = pol2cart(Rad2, Odl5)
figure
plot(xData5,abs(yData5), '.')


