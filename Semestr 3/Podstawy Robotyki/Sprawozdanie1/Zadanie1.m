#utworzenie portu 
s = serial('COM1');

#konfiguracja portu
set(s, 'BaudRate', 115200, 'DataBits', 8, 'Parity', 'None', 'StopBits', 1, 'FlowControl', 'none');

#otwarcie portu
fopen(s);

#obrót o krok w lewo
fwrite(s,[AA, 01, 1, 0, 0], uint8, sync);
ileDanych = s.BytesAvailable;
dane = fread(s, ileDanych, uint8);

#obrót o krok w prawo
fwrite(s,[AA, 01, 2, 0, 0], uint8, sync);
ileDanych = s.BytesAvailable;
dane = fread(s, ileDanych, uint8);

#odczytanie aktualnej wartości sygnału wyjściowego czujnika
fwrite(s,[AA, 02, 0, 0, 0], uint8, sync);
ileDanych = s.BytesAvailable;
dane = fread(s, ileDanych, uint8);

pomiar = dane(2) + dane(3)*16 + dane(4)*216;

fclose(s);
delete(s);
clear s; 