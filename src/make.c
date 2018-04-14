#include "interface.h" //por comment
#include "stdio.h"
#include "tests.h"


int main(int argc, char** argv){
  if(argc > 1){
    char tnt[15];
    strcpy(tnt, argv[1]);
    if(!strcmp(tnt, "unit")) unit_test();
  }
  else{

    TAD_community cum = init();

    load(cum, "/home/pimonteiro/Desktop/android");
    //LONG_list a = both_participated(cum, 136, 52, 1);
    Date begin = createDate(15, 2, 2010);
    Date end   = createDate(15, 6, 2010);

    USER c = get_user_info(cum, 114);

    STR_pair b = info_from_post(cum, 5);
    LONG_list a = most_answered_questions(cum, 5, begin, end);
    //long list = get_list(a,0);
    //long list2 = get_list(a,1);
    //printf("%ld ------ %ld\n", list, list2);
    cum = clean(cum);
  }
  return 0;
}
