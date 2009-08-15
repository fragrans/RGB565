#include <ostream>
#include <iostream>
#include <fstream>
#include "bitmap.h"

using namespace std;

typedef unsigned char BYTE;
typedef unsigned short WORD;
inline BYTE LOBYTE(WORD w) { return 0xff & w;}
inline BYTE HIBYTE(WORD w) { return 0xff & (w >> 8);}

void ColorConversion32To16 ( BYTE *lpBits32, int Width, int Height, BYTE *lpBits16   )
{
  int nPos16 = 0;
  int Size = Width*Height*4;
  for ( int nPos24 = 0 ; nPos24 < Size ; nPos24+=4 ,nPos16+=2)
  {
    BYTE Red24   = lpBits32[nPos24+0]; // 8-bit red
    BYTE Green24 = lpBits32[nPos24+1]; // 8-bit green
    BYTE Blue24  = lpBits32[nPos24+2]; // 8-bit blue

    BYTE Red16   = Red24   >> 3;  // 5-bit red
    BYTE Green16 = Green24 >> 2;  // 6-bit green
    BYTE Blue16  = Blue24  >> 3;  // 5-bit blue

    unsigned short RGB2Bytes = Blue16 + (Green16<<5) + (Red16<<(5+6));

    lpBits16[nPos16]  = LOBYTE(RGB2Bytes);
    lpBits16[nPos16+1]= HIBYTE(RGB2Bytes);
  }
}

void GenArrayFromRGB16(ostream& os, BYTE *lpBits16, int Width, int Height)
{
  WORD *lp = (WORD*)lpBits16;
  os << "#pragma once \n";
  os << "const int Width = " << Width << ";\n";  
  os << "const int Height = " << Height << ";\n";

  os << "unsigned short Arr[Height][Width] = { \n";
  for (int i=0; i<Height; i++) {
    os << "{";
    for (int j=0; j<Width; j++) {
      if (!(j%8) && j) { os << "\n"; }
      os << hex << "0x" <<  *(lp + Width*(Height-i-1) + j) << ", ";
    }
    os << "},\n";
  }
  os << "}; \n";
}

int main()
{
    const char *fn = "pic.bmp";
    CBitmap bmp(fn);
    
    // usage
    unsigned int Width  = bmp.GetWidth();
    unsigned int Height = bmp.GetHeight();
  
    cout << "Width: " << Width << "\n";    
    cout << "Height: " << Height << "\n";
    BYTE *lpBits32 = new BYTE[Width*Height*4];
    BYTE *lpBits16 = new BYTE[Width*Height*2];
  
    unsigned int copied = Width*Height*4;
    ofstream of("mark.h");
    bmp.GetBits(lpBits32, copied);
    if(copied != Width*Height*4) {
        cout << "Hi Error again!\n";
        exit(0);
    }
    ColorConversion32To16( lpBits32, Width,Height, lpBits16);
  
    GenArrayFromRGB16(of, lpBits16, Width, Height);
    of.close();
    delete [] lpBits32;
    delete [] lpBits16;
    return 0;
}
