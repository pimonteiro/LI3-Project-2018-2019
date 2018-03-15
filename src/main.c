#include <stdio.h>
#include "interface.h"

int main(int argc, char *argv[]){
  Date d = createDate(1,2,2017);
  printf("Dia: %i\n", get_day(d));

//  int i = parse(argv[1]);

//  printf("%d", i);
  return 0;
}
