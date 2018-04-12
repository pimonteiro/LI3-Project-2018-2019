#include "interface.h" //por comment


int main(){
    TAD_community cum = init();

    load(cum, "/home/pimonteiro/Desktop/android");
    LONG_list a = both_participated(cum, 136, 52, 1);
    cum = clean(cum);

  	return 0;
}
