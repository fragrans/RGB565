#pragma once
#include "mark.h"

class CWaterMark
{
public:
    CWaterMark(int x, int y, int w, int h, void *buffer, unsigned int fmt)
    {
        if(w < Width) return;
        if(h < Height) return;
        if(w - x < Width) return;
        if(h - y < Height) return;
        unsigned short *p = (unsigned short*)buffer;
        for (int i=0;i<Height;i++) {
            for (int j=0;j<Width;j++) {
                int m = (x+j);
                int n = (y+i);
                p[w*n+m] ^= Arr[i][j];
            }
        }
    }
private:

};
