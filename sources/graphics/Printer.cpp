#include "Printer.h"
#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include "Vector3.h"
#include <string>
#include <stdlib.h>

Printer::Printer() {}

float Printer::baseLetterHeight = 0.3;
void Printer::surfacePrint(Vector3 position, string text, float fontSize, bool zBufferOff) {
    
    if(zBufferOff)
        glDisable(GL_DEPTH_TEST);
    
    glPushMatrix();
        glTranslatef(position.x, position.y, position.z);
        
        for(int cursor=0; cursor<text.size(); cursor++) {
            string letter = text.substr(cursor, 1);
            int letterId = (letter.c_str())[0];
            
            float baseUVX = Printer::getLetterBaseLocalization(letterId).x;
            float baseUVY = Printer::getLetterBaseLocalization(letterId).y;
            
            glBindTexture(GL_TEXTURE_2D, 1);
            glBegin(GL_QUADS);
                glTexCoord2f(baseUVX, baseUVY);
                glVertex3f((float)cursor + 0.0, 0.0, 0.0);
                glTexCoord2f(baseUVX, baseUVY+Printer::baseLetterHeight);
                glVertex3f((float)cursor + 0.0, 0.0, 1.0);
                glTexCoord2f(baseUVX+Printer::getBaseLetterWidth(letterId), baseUVY+Printer::baseLetterHeight);
                glVertex3f((float)cursor + 1.0, 0.0, 1.0);
                glTexCoord2f(baseUVX+Printer::getBaseLetterWidth(letterId), baseUVY);
                glVertex3f((float)cursor + 1.0, 0.0, 0.0);
            glEnd();
            glBindTexture(GL_TEXTURE_2D, 0);
        }
        
        
        
    glPopMatrix();
    if(zBufferOff)
        glEnable(GL_DEPTH_TEST);
    
}

float Printer::getBaseLetterWidth(char letter) {
    return 0.3;
}
Vector3 Printer::getLetterBaseLocalization(char letter) {
    return Vector3(0.0, 0.0, 0.0);
}

Printer::~Printer() {}

