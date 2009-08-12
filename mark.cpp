#include <iostream>
#include "test.h"
using namespace std;

int main()
{
    for (int i=0; i<Height; i++) {
        for (int j=0; j<Width; j++) {
            if (Arr[i][j] != 0xf810) cout << "Haha!!\n";
        }
    }
    return 0;
}
