#include <stdio.h>
#include <stdlib.h>

#include "watermark.h"

int main()
{
    unsigned short cc[1000][1000];
    CWaterMark wm(0,0,1000,1000,&cc[0][0], 0);

    return 0;
}
