#include <iostream>
#include <Sort/Sort.hpp>

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
    llama::sort<int>(llama::BUBBLE_SORT, array, 11);
    copy(array, array+11, ostream_iterator<int>(cout, " "));
    cout<<'\n';
    
    restore(array);
    llama::sort<int>(llama::COCKTAIL_SORT, array, 11);
    copy(array, array+11, ostream_iterator<int>(cout, " "));
    cout<<'\n';
    
    restore(array);
    llama::sort<int>(llama::INSERTION_SORT, array, 11);
    copy(array, array+11, ostream_iterator<int>(cout, " "));
    cout<<'\n';
    
    restore(array);
    llama::sort<int>(llama::SELECTION_SORT, array, 11);
    copy(array, array+11, ostream_iterator<int>(cout, " "));
    cout<<'\n';
    
    restore(array);
    llama::sort<int>(llama::SHELL_SORT, array, 11);
    copy(array, array+11, ostream_iterator<int>(cout, " "));
    cout<<'\n';
    
    restore(array);
    llama::sort<int>(llama::QUICK_SORT, array, 11);
    copy(array, array+11, ostream_iterator<int>(cout, " "));
    cout<<'\n';
    return 0;
}
