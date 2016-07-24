#include <iostream>
#include <Cryptography/Cryptography.h>

using namespace std;

int main(int argc, const char * argv[]) {
    cout<<alpaca::cryptography::decode(alpaca::cryptography::encode("Hello, World!\n", "public.pem"), "private.pem");
}
