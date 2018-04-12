#include "interface.h" //por comment


int main(){
    TAD_community cum = init();

    load(cum, "/home/pimonteiro/Desktop/android");
    //LONG_list a = both_participated(cum, 136, 52, 1);
    Date begin = createDate(15, 2, 2010);
    Date end   = createDate(15, 6, 2010);
    LONG_list a = most_answered_questions(cum, 5, begin, end);
    cum = clean(cum);

  	return 0;
}
