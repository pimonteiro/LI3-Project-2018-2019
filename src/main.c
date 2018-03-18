#include <stdio.h>
#include "interface.h"
#include <string.h>
#include "parser.h"


#define RED "\033[31m"
#define BLUE "\033[34m"
#define GREEN "\033[32m"

#define RESET "\033[0m"
int main(int argc, char *argv[]){
  Date d = createDate(1,2,2017);
  printf("Dia: %i\n", get_day(d));


 int i;
 for(i=1; i<argc;i++){
  printf("Ficheiro: %s%s%s ", BLUE, argv[i], RESET);
  if(isFile(argv[i]) == 2)
    printf("%sPosts%s\n", GREEN, RESET);
  else if(isFile(argv[i]) == 1)
    printf("%sUsers%s\n", GREEN, RESET);
  else printf("%sNão importa%s\n", RED, RESET);
 }
}

int isFile(const char *str)
{
    if (!str)
        return 0;
    size_t lenStr = strlen(str);
    // -4 = .xml
    // -2 = usErs.xml or poSts.xml
    // 6
    if(*(str + lenStr - 7) == 'e')
        return 1;
    else if(*(str + lenStr - 7) == 's')
        return 2;
    else
        return -1;
}
