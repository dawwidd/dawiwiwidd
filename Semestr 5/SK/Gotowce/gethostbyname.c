#include <stdio.h>
#include <netdb.h>
#include <string.h>
#include <arpa/inet.h>
struct hostent *he;
struct in_addr a;

int main ()
{
  he = gethostbyname ("mail.google.com");
  if (he)
  {
    printf("name: %s\n", he->h_name);
    while (*he->h_aliases)
        printf("alias: %s\n", *he->h_aliases++);
    while (*he->h_addr_list)
    {
        bcopy(*he->h_addr_list++, (char *) &a, sizeof(a));
        printf("address: %s\n", inet_ntoa(a));
    }
 }
 else
    printf("error");
 return 0;
}
