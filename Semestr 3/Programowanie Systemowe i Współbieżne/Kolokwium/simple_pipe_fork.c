#include<unistd.h> // pipe
#include<stdio.h> // fork


int main(){
	
	int fd[2]; // tablica dwuelementowa
	pipe(fd);  // stworzenie łącza i przypisanie deskryptorów fd[0]- odczyt, fd[1] - zapis
	if(fork()==0) // fork() tworzy proces potomny, warunek fork()==0 jest prawdziwy dla potomka
	{
		close(fd[0]); // zamykamy niepotrzebny dekryptor do odczutu
		write(fd[1], "Hello",6); // zapisujemy na łącze string, 3 argument to rozmiar (ilosc znaków +1) można użyć sizeof(msg)
		close(fd[1]); // zamykamy deskryptor zapisu

	}
	else{ // gdy jestesmy w przodku (można dać exit() w potomku, wtedy nie trzeba 'else'
		char buf[6]; // tablica do zczytywania z łącza
		close(fd[1]); // zamykamy niepotrzebny deskryptor zapisu
		while(read(fd[0],buf,6)>0){ // odczytujemy to co jest na łączu fd z jego deskryptora odczytu [0]
			printf("%s\n",buf);
		}
	}
	return 0;
}
