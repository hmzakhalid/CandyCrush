/*
 * Candy.h
 *
 *  Created on: Jun 9, 2020
 *      Author: hamza
 */

#ifndef CANDY_H_
#define CANDY_H_

#include<iostream>
#include "util.h"
using namespace std;

class Candy{
public:
	int x;
	int y;
	int value;

	Candy(){
		x = 25;
		y = 940-250;
		value = 0;
	}
	Candy(const Candy &cpy){
		x = cpy.x;
		y = cpy.y;
		value = cpy.value;
	}
	void draw(){
		switch(value){
			case 0:
				DrawTriangle( x, y , x+40, y , x+20 , y+40, colors[MISTY_ROSE] );
				break;
			case 1:
				DrawSquare( x , y ,40,colors[RED]);
				break;
			case 2:
				DrawRoundRect(x,y,40,40,colors[LIME_GREEN],10);
				break;
			case 3:
				DrawCircle(x+18, y+18, 20, colors[DARK_SLATE_GRAY]);
				break;
			case 4:
				DrawRoundRect(x+10,y,20,40,colors[DARK_OLIVE_GREEN],10);
				break;
			case 5:
				DrawSquare( x , y ,60,colors[CHOCOLATE]);
				break;
		}
	}
};



#endif /* CANDY_H_ */
