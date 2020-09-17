//============================================================================
// Name        : .cpp
// Author      : Sibt ul Hussain
// Version     :
// Copyright   : (c) Reserved
// Description : Basic 2D game of Centipede...
//============================================================================

#ifndef CENTIPEDE_CPP_
#define CENTIPEDE_CPP_
#include "util.h"
#include "Menu.h"
#include "Candy.h"
#include "Board.h"
#include <iostream>
#include <cmath>
#include <string>
#include <time.h>
#include <fstream>
using namespace std;



void SetCanvasSize(int width, int height) {
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, width, 0, height, -1, 1); // set the screen size to given width and height.
	glMatrixMode (GL_MODELVIEW);
	glLoadIdentity();
}


/*
 * Main Canvas drawing function.
 * */
Board myGame;
void GameDisplay()/**/{
	glClearColor(0/*Red Component*/, 0,	//148.0/255/*Green Component*/,
		 		0.0/*Blue Component*/, 0 /*Alpha component*/); // Red==Green==Blue==1 --> White Colour
	glClear (GL_COLOR_BUFFER_BIT); //Update the colors


	static bool once = false;
	static bool game = false;
	// set the background color using function glClearColor.
	// to change the background play with the red, green and blue values below.
	// Note that r, g and b values must be in the range [0,1] where 0 means dim rid and 1 means pure red and so on.
	if(myGame.gameStatus() == 0){
		myGame.draw_menu();
	}
	else if(myGame.gameStatus() == 1){

		if(myGame.getLevelMode() == 0){ // NORMAL MODE
			if(myGame.getHint() == true){
				myGame.drawHint();
			}
			myGame.draw_board();
			myGame.draw_candies();
			myGame.Score();
			if(myGame.getLives()==0){
				myGame.setGameStatus(7);
				myGame.SaveHighScore();
			}

		}else if(myGame.getLevelMode() == 1){ // TIME TRIAL

			if(myGame.getGame() == false){
				myGame.setTimeScore((myGame.getLevel()*1000)/2);
				myGame.setGame(true);
				if(game == false){
					myGame.setScore(0);
					game = true;
				}

			}
			if(myGame.getGame() == true){
				if(myGame.getHint() == true){
					myGame.drawHint();
				}
				myGame.draw_board();
				myGame.draw_candies();
				myGame.Score();
				if(myGame.getLives()==0){
					myGame.setGameStatus(7);
					myGame.SaveHighScore();
				}
				if(myGame.getTimeScore()<=0){
					myGame.setGameStatus(7);
					myGame.SaveHighScore();
				}
			}
		}

	}else if(myGame.gameStatus() == 2){
		myGame.draw_pause();
	}else if(myGame.gameStatus() == 3){
		myGame.start_menu();
	}else if(myGame.gameStatus() == 4){
		myGame.level_menu();
	}else if(myGame.gameStatus() == 5){
		myGame.level_mode();
	}else if(myGame.gameStatus() == 6){
		myGame.name_menu();
	}else if(myGame.gameStatus() == 7){
		myGame.game_over();
		myGame.delete_game();
	}else if(myGame.gameStatus() == 9){
		myGame.No_Save();
	}else if(myGame.gameStatus() == 10){
		if(once == false){
			myGame.LoadHighScore();
			once = true;
		}

		myGame.ShowHighScore();
	}else if(myGame.gameStatus() == 11){
		myGame.help_menu();
	}

	//DrawSquare( 25 , 250 ,40,colors[RED]);

	 // Trianlge Vertices v1(300,50) , v2(500,50) , v3(400,250)


//	 DrawRoundRect(500,200,50,100,colors[DARK_SEA_GREEN],70);
//	 DrawRoundRect(100,200,100,50,colors[DARK_OLIVE_GREEN],20);
//	 DrawRoundRect(100,100,50,100,colors[DARK_OLIVE_GREEN],30);
//	 DrawRoundRect(200,100,100,50,colors[LIME_GREEN],40);
//	 DrawRoundRect(350,100,100,50,colors[LIME_GREEN],20);
	
	glutSwapBuffers(); // do not modify this line..

}

/*This function is called (automatically) whenever any non-printable key (such as up-arrow, down-arraw)
 * is pressed from the keyboard
 *
 * You will have to add the necessary code here when the arrow keys are pressed or any other key is pressed...
 *
 * This function has three argument variable key contains the ASCII of the key pressed, while x and y tells the
 * program coordinates of mouse pointer when key was pressed.
 *
 * */

void NonPrintableKeys(int key, int x, int y) {
	if (key
			== GLUT_KEY_LEFT /*GLUT_KEY_LEFT is constant and contains ASCII for left arrow key*/) {
		// what to do when left key is pressed...

	} else if (key
			== GLUT_KEY_RIGHT /*GLUT_KEY_RIGHT is constant and contains ASCII for right arrow key*/) {

	} else if (key
			== GLUT_KEY_UP/*GLUT_KEY_UP is constant and contains ASCII for up arrow key*/) {

	}

	else if (key
			== GLUT_KEY_DOWN/*GLUT_KEY_DOWN is constant and contains ASCII for down arrow key*/) {

	}

	/* This function calls the Display function to redo the drawing. Whenever you need to redraw just call
	 * this function*/

	glutPostRedisplay();

}

/*This function is called (automatically) whenever any printable key (such as x,b, enter, etc.)
 * is pressed from the keyboard
 * This function has three argument variable key contains the ASCII of the key pressed, while x and y tells the
 * program coordinates of mouse pointer when key was pressed.
 * */
void PrintableKeys(unsigned char key, int x, int y) {
	if (key == 27/* Escape key ASCII*/) {
		exit(1); // exit the program when escape key is pressed.
	}

	if(myGame.gameStatus() == 6){
		myGame.setName(key);
	}

	if (key == 'b' || key == 'B') //Key for placing the bomb
			{
		//do something if b is pressed
		cout << "b pressed" << endl;

	}
	glutPostRedisplay();
}

/*
 * This function is called after every 1000.0/FPS milliseconds
 * (FPS is defined on in the beginning).
 * You can use this function to animate objects and control the
 * speed of different moving objects by varying the constant FPS.
 *
 * */
void Timer(int m) {
	static int newScore;
	// implement your functionality here
	if(myGame.getLevelMode() == 1){
		newScore = myGame.getTimeScore();
		newScore-= myGame.getLevel()*10;
		myGame.setTimeScore(newScore);
	}

	// once again we tell the library to call our Timer function after next 1000/FPS
	glutPostRedisplay();
	glutTimerFunc(500.0, Timer, 0);
}

void MyTimer(int m){

	myGame.check();
	// once again we tell the library to call our Timer function after next 1000/FPS
	glutPostRedisplay();
	glutTimerFunc(10.0, MyTimer, 0);
}

/*This function is called (automatically) whenever your mouse moves witin inside the game window
 *
 * You will have to add the necessary code here for finding the direction of shooting
 *
 * This function has two arguments: x & y that tells the coordinate of current position of move mouse
 *
 * */
void MousePressedAndMoved(int x, int y) {
	//cout << x << " " << y << endl;
	glutPostRedisplay();
}
void MouseMoved(int x, int y) {
	y = 940 - y;
	if(myGame.gameStatus() == 0){
		if(y <= 630 && y > 590){
			myGame.setCursorY(590);
		}else if(y < 580 && y > 540){
			myGame.setCursorY(540);
		}else if(y < 530 && y > 490){
			myGame.setCursorY(490);
		}else if(y < 480 && y > 440){
			myGame.setCursorY(440);
		}else if(y < 420 && y > 380){
			myGame.setCursorY(390);
		}
	}else if(myGame.gameStatus() == 2){
		if(y <= 630 && y > 590){
			myGame.setCursorY(590);
		}else if(y < 580 && y > 540){
			myGame.setCursorY(540);
		}else if(y < 530 && y > 490){
			myGame.setCursorY(490);
		}
	}else if(myGame.gameStatus() == 4){
		if(y <= 630 && y > 590){
			myGame.setCursorY(590);
		}else if(y < 580 && y > 540){
			myGame.setCursorY(540);
		}else if(y < 530 && y > 490){
			myGame.setCursorY(490);
		}else if(y < 480 && y > 440){
			myGame.setCursorY(440);
		}else if(y < 430 && y > 390){
			myGame.setCursorY(390);
		}else if(y < 380 && y > 340){
			myGame.setCursorY(340);
		}
	}else if(myGame.gameStatus() == 3){
		if(y <= 630 && y > 590){
			myGame.setCursorY(590);
		}else if(y < 580 && y > 540){
			myGame.setCursorY(540);
		}else if(y < 530 && y > 490){
			myGame.setCursorY(490);
		}
	}else if(myGame.gameStatus() == 5){
		if(y <= 630 && y > 590){
			myGame.setCursorY(590);
		}else if(y < 580 && y > 540){
			myGame.setCursorY(540);
		}
	}
	//cout << x << " " << y << endl;
	glutPostRedisplay();
}

/*This function is called (automatically) whenever your mouse button is clicked witin inside the game window
 *
 * You will have to add the necessary code here for shooting, etc.
 *
 * This function has four arguments: button (Left, Middle or Right), state (button is pressed or released),
 * x & y that +tells the coordinate of current position of move mouse
 *
 * */
void MouseClicked(int button, int state, int x, int y) {
	static int sx, sy;
	int ax, ay;
	y = 940-y;
	if (button == GLUT_LEFT_BUTTON){ // dealing only with left button
		if(myGame.gameStatus()==0){
			if(state == 0){
				if(y <= 630 && y > 590){
					myGame.setGameStatus(3); // Start Menu 3
				}else if(y < 580 && y > 540){
					myGame.setGameStatus(4);  // Level Menu
				}else if(y < 530 && y > 490){
					myGame.setGameStatus(10); // Highscore
				}else if(y < 480 && y > 440){
					myGame.setGameStatus(11);
				}else if(y < 420 && y > 380){
					exit(1);
				}
			}
		}else if(myGame.gameStatus()==1){
			// SWAPING GEMS
			if((y < 100 && y > 20)&& (x > 270 && x < 340)){
				myGame.setGameStatus(2);  // PAUSE
			}else if((y < 210 && y > 170)&& (x > 430 && x < 530)){
				if(state == 0)
					myGame.show_hint();
			}
			if(state == 0){
					sx = x;
					sy = y;
			}
			if(state == 1){
				ax = sx - x;
				ay = sy - y;
				cout << ax << " " << ay << endl;
				if(abs(ay) > abs(ax)) {
					if(ay < 0){
						cout << ay << endl;
						myGame.setHint(false);
						myGame.Switch(2, sx,sy);  // Switch Candy up

					}else if(ay > 0){
						myGame.setHint(false);
						myGame.Switch(3, sx,sy);  // Switch Candy Down

					}
				}else{
					if(ax < 0){
						myGame.setHint(false);
						myGame.Switch(0,sx,sy);   // Switch Candy Right

					}else if(ax > 0){
						myGame.setHint(false);
						myGame.Switch(1,sx,sy);   // Switch Candy left

					}
				}
			}
		}else if(myGame.gameStatus()==2){ // RESUME
			if(y <= 630 && y > 590){
				myGame.setGameStatus(1); // RESUME GAME
			}else if(y < 580 && y > 540){
				myGame.save_game(); // SAVE GAME
			}else if(y < 530 && y > 490){
				myGame.setGameStatus(0); // MAIN MENU
			}
		}else if(myGame.gameStatus()==3){  // NEW GAME
			if(state == 0){
				if(y <= 630 && y > 590){
					myGame.setGameStatus(6);
					myGame.setLevel(1);
					myGame.setLives(3);
					myGame.setScore(0);
				}else if(y < 580 && y > 540){
					if(state == 0){
						ifstream LoadFile("SaveGame.txt");
						if(LoadFile){
							myGame.load_game();        // LOAD GAME
							myGame.setGameStatus(1);
						}else{
							myGame.setGameStatus(9);
						}
						LoadFile.close();
					}
				}else if(y < 530 && y > 490){
					myGame.setGameStatus(0);
				}
			}
		}else if(myGame.gameStatus() == 4){
			if(state == 0){
				if(y <= 630 && y > 590){
					myGame.setGameStatus(6);
					myGame.setLevel(1);
				}else if(y < 580 && y > 540){
					myGame.setGameStatus(6);
					myGame.setLevel(2);
				}else if(y < 530 && y > 490){
					myGame.setGameStatus(6);
					myGame.setLevel(3);
				}else if(y < 480 && y > 440){
					myGame.setGameStatus(6);
					myGame.setLevel(4);
				}else if(y < 420 && y > 380){
					myGame.setGameStatus(6);
					myGame.setLevel(5);
				}else if(y < 380 && y > 340){
					myGame.setGameStatus(0);
				}
			}
		}else if(myGame.gameStatus()==5){  // LEVEL MODE
			if(state == 0){
				if(y <= 630 && y > 590){
					myGame.setGameStatus(1); // GAME START
					myGame.setLevelMode(0);
					myGame.setScore(0);
				}else if(y < 580 && y > 540){
					myGame.setGameStatus(1); // GAME START
					myGame.setLevelMode(1);
					myGame.setScore(0);
				}
			}
		}else if(myGame.gameStatus()==6){  // NAME MENU
			if(state == 0){
				if(y < 530 && y > 490){
					myGame.setGameStatus(5);
				}
			}
		}else if(myGame.gameStatus()==7){  // GAME OVER
			if(state == 0){
				if(y < 580 && y > 540){
					myGame.setGameStatus(0); // MAIN MENU
				}
			}
		}else if(myGame.gameStatus()==9){  // GAME OVER
			if(state == 0){
				if(y < 580 && y > 540){
					myGame.setGameStatus(0); // MAIN MENU
				}
			}
		}else if(myGame.gameStatus()==10){  // HighScore
			if(state == 0){
				if(y < 280 && y > 240){
					myGame.setGameStatus(0); // MAIN MENU
				}
			}
		}else if(myGame.gameStatus()==11){  // HighScore
			if(state == 0){
				if(y < 280 && y > 240){
					myGame.setGameStatus(0); // MAIN MENU
				}
			}
		}

		cout << myGame.getLevelMode() << endl;
		//cout << x << " " << y << endl;
			//cout << GLUT_DOWN << " " << GLUT_UP << endl;

	} else if (button == GLUT_RIGHT_BUTTON) // dealing with right button
			{
			cout<<"Right Button Pressed"<<endl;

	}
	glutPostRedisplay();
}
/*
 * our gateway main function
 * */
int main(int argc, char*argv[]) {

	int width = 610, height = 940; // i have set my window size to be 800 x 600

	InitRandomizer(); // seed the random number generator...
	glutInit(&argc, argv); // initialize the graphics library...
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA); // we will be using color display mode
	glutInitWindowPosition(50, 50); // set the initial position of our window
	glutInitWindowSize(width, height); // set the size of our window
	glutCreateWindow("Candy Crush by Hamza Khalid"); // set the title of our game window
	SetCanvasSize(width, height); // set the number of pixels...

//	glMatrixMode (GL_PROJECTION);
//	glLoadIdentity ();
//	glOrtho(0, width, height, 0, 0, 1);
//
//	glMatrixMode (GL_MODELVIEW);
//	glLoadIdentity ();

	// Register your functions to the library,
	// you are telling the library names of function to call for different tasks.
	//glutDisplayFunc(display); // tell library which function to call for drawing Canvas.

	glutDisplayFunc(GameDisplay); // tell library which function to call for drawing Canvas.
	glutSpecialFunc(NonPrintableKeys); // tell library which function to call for non-printable ASCII characters
	glutKeyboardFunc(PrintableKeys); // tell library which function to call for printable ASCII characters
	// This function tells the library to call our Timer function after 1000.0/FPS milliseconds...
	glutTimerFunc(1000.0, Timer, 0);
	glutTimerFunc(1000.0, MyTimer, 0);

	glutMouseFunc(MouseClicked);
	glutPassiveMotionFunc(MouseMoved); // Mouse
	glutMotionFunc(MousePressedAndMoved); // Mouse

	// now handle the control to library and it will call our registered functions when
	// it deems necessary...
	glutMainLoop();
	return 1;
}
#endif /* AsteroidS_CPP_ */
