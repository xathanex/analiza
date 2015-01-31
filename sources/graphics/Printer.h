#ifndef PRINTER_H
#define	PRINTER_H
#include <string>
#include <iostream>
#include "Vector3.h"

using namespace std;

class Printer {
public:
    static float baseLetterHeight;
    
    Printer();
    virtual ~Printer();
    static float getBaseLetterWidth(char letter);
    static Vector3 getLetterBaseLocalization(char letter);
    static void surfacePrint(Vector3 position, string text, float fontSize, bool zBufferOff);

    
private:

};

#endif	/* PRINTER_H */

