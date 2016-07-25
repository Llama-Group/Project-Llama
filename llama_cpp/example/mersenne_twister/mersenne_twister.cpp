#include <iostream>
#include <RNG/MersenneTwister.h>

using namespace std;

int main(int argc, const char * argv[]) {
    llama::RNG::MersenneTwister mt(static_cast<uint32_t>(time(NULL)));
    for (int i = 0; i < 5; i++) {
        cout<<mt.rand()<<'\n';
    }
}
