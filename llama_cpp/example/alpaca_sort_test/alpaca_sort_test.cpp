#include <iostream>
#include <iterator>
#include <Sort/hpSort.h>

using namespace std;

int main(int argc, const char * argv[]) {
    int array[11];
    auto restore = [&](int * x){
        x[0]=12; x[1] = 2; x[2]=16;
        x[3]=30; x[4] = 8; x[5]=28;
        x[6]= 4; x[7] =10; x[8]=20;
        x[9]= 6; x[10]=18;
    };

    restore(array);
    alpaca::sort<int>(alpaca::BUBBLE_SORT, array, 11);
    copy(array, array+11, ostream_iterator<int>(cout, " "));
    cout<<'\n';

    restore(array);
    alpaca::sort<int>(alpaca::COCKTAIL_SORT, array, 11);
    copy(array, array+11, ostream_iterator<int>(cout, " "));
    cout<<'\n';

    restore(array);
    alpaca::sort<int>(alpaca::INSERTION_SORT, array, 11);
    copy(array, array+11, ostream_iterator<int>(cout, " "));
    cout<<'\n';

    restore(array);
    alpaca::sort<int>(alpaca::SELECTION_SORT, array, 11);
    copy(array, array+11, ostream_iterator<int>(cout, " "));
    cout<<'\n';

    restore(array);
    alpaca::sort<int>(alpaca::SHELL_SORT, array, 11);
    copy(array, array+11, ostream_iterator<int>(cout, " "));
    cout<<'\n';

    restore(array);
    alpaca::sort<int>(alpaca::QUICK_SORT, array, 11);
    copy(array, array+11, ostream_iterator<int>(cout, " "));
    cout<<'\n';
    return 0;
}
