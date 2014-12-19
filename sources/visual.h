#ifndef VISUAL_H
#define VISUAL_H

class Visual {
	private:
		int x, 				// środek, lewy dolny róg czy lewy górny róg?
		    y, 
		    sizeX, 
		    sizeY;
		double angle; // radian

public:
		Visual(int x, int y, int sizeX, int sizeY, double angle);
		    
		int getX();
		int getY();
		int getSizeX();
		int getSizeY();
		double getAngle();
		
		void rotate(double a);
};

#endif
