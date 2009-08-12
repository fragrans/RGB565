#include <ostream>
#include <iostream>
using namespace std;

typedef unsigned char BYTE;
typedef unsigned short WORD;
inline BYTE LOBYTE(WORD w) { return 0xff & w;}
inline BYTE HIBYTE(WORD w) { return 0xff & (w >> 8);}

void ColorConversion24To16 ( BYTE *lpBits24, int Width, int Height, BYTE *lpBits16   )
{
  int nPos16 = 0;
  int Size = Width*Height*3;
  for ( int nPos24 = 0 ; nPos24 < Size ; nPos24+=3 ,nPos16+=2)
  {
    BYTE Red24   = lpBits24[nPos24+0]; // 8-bit red
    BYTE Green24 = lpBits24[nPos24+1]; // 8-bit green
    BYTE Blue24  = lpBits24[nPos24+2]; // 8-bit blue

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
  os << "unsigned short Arr[][] = { \n";
  for (int i=0; i< Height; i++) {
    os << "{";
    for (int j=0; j<Width; j++) {
      if (!(j%8) && j) { os << "\n"; }
      os << hex << "0x" <<  *(lp + Width*i + j) << ", ";
    }
    os << "},\n";
  }
  os << "}; \n";
}
int main()
{
  // usage
  int Width  = 100;
  int Height = 100;

  BYTE *lpBits24 = new BYTE[Width*Height*3];
  BYTE *lpBits16 = new BYTE[Width*Height*2];
  for (int i=0; i<Width*Height; i++) {
    BYTE *p = lpBits24 + i*3;
    *p = 0xff;
    *(p+1) = 0x00;
    *(p+2) = 0x80;
  }

  ColorConversion24To16( lpBits24,Width,Height,lpBits16);
  GenArrayFromRGB16(cout, lpBits16, Width, Height);

  delete [] lpBits24;
  delete [] lpBits16;
  return 0;
}
