#include "mybiguint.h"



int main(){
    
    std::vector<uint64_t> a={1,7};
    std::vector<uint64_t> b={0,3};
    MyBigUint<512> x;
    MyBigUint<512> y;
    MyBigUint<512> res;

    x.setNumber(a);
    y.setNumber(b);

    res = x/y;

    res.print();

    return 0;
}