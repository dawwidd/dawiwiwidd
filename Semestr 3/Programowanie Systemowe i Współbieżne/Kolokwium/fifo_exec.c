#include <unistd.h> //fork, close & exec
#include <fcntl.h> //open
#include <sys/stat.h> //mkfifo

int main(int argc, char *argv[]) {
  char *const first[] = {"ls", "-a", NULL}; //polecenie i parametry zakończone NULLem
  int fd[2];
  mkfifo("kolejka", 0644); //ścieżka do pliku i prawa dostępu – tworzy plik specjalny typu pipe
    //mogą się komunikować procesy niespokrewnione
    //łącze musi być otwarte w trybie komplementarnym
    //może być kilka procesów piszących, przy kilku czytających tylko 1 dostanie dane
  if (fork() == 0){
    int fd = open("kolejka", O_WRONLY);
    dup2(fd,1); //duplikuje deskryptor fd  i przydziela mu nr 1 - stdout
    execvp(first[0], first); //vector - tablica z poleceniem i flagami, path - przeszukuje katalogi z PATH (np. /bin)
    close(fd); //jeżeli exec skończy się poprawnie, nie wykona się, bo proces się kończy
  }
  else{
    int fd = open("kolejka", O_RDONLY);
    dup2(fd, 0); //0 - stdin
    execl("/usr/bin/wc", "wc", NULL); //l - lista - wypisujemy polecenie i flagi, zakończone NULLem, nie ma p - podajemy pełną ścieżkę,
      //execle - e- modyfikujemy  środowisko (np. zmienne językowe)
    close(fd);
  }
  return 0;
}
