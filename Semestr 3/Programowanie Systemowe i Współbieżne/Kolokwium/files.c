#include <unistd.h> //read & write & close
#include <fcntl.h> //open
#include <stdio.h> //printf
#include <string.h> //strcpy

int main(int argc, char const *argv[]) { //argc - arguments count, argv - values (łącznie z nazwą programu)
  //deskryptory w tablicy otwartych  plików: 0-stdin, 1-stdout, 2-stderr, ...

  int fd = open("file1.txt", O_RDONLY);   //fd = -1 jeżeli wystąpi błąd
  int fd_write = open("file2.txt", O_WRONLY|O_CREAT, 0644); //jeśli nie istnieje, tworzy z prawami dost. 644
      //O_RDWR, O_APPEND - nadpisuje, O_TRUNC - usuwa (odcina) zawartość
  int n = 0;
  char buff[255]; //`buff` to wskaźnik!
  strcpy(buff, "");
      //strncpy(destination, source, nr_of_bytes); //maksymalnie nr_of_bytes bitów

  while((n = read(fd, buff, 255))>0){  //czytanie całego pliku po kolei do bufora, n - liczba odczytanych bajtów
    write(fd_write, buff, n); //zapis n bajtów z bufora do pliku
  }

  int file_size = lseek(fd, 0, SEEK_END); //przesunięcie wskaźnika na 0. bit od końca
      //file_size - liczba bitów od początku pliku do wskaźnika
      //0 - offset, wielkość przesunięcia
      //SEEK_END - koniec pliku, SEEK_SET - początek, SEEK_CUR - obecna pozycja

  close(fd); //usuwa deskryptor pliku z tablicy otwartych plików
  close(fd_write);
  unlink("file2.txt"); //usuwa plik
  return 0;
}
