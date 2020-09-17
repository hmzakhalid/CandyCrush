/*
 * Menu.h
 *
 *  Created on: Jun 9, 2020
 *      Author: hamza
 */

#ifndef MENU_H_
#define MENU_H_
#include<iostream>
#include "util.h"
using namespace std;

class Menu{
	/* Status 0 = Main Menu
	 * Status 1 = Start Game
	 * Status 2 = Pause Game
	 * Status 3 = Start Menu
	 * Status 4 = Level Menu
	 * Status 5 = Level Mode
	 * Status 6 = Name Screen
	 * Status 7 = Game OVER
	 * Status 8 = HighScores
	 * Status 9 = No Save File
	 * Status 10 = Highscore
	 * Status 11 = HELP
	 */
	string name;
	int gamestatus;
	int timeTrial;
	int cursor_y;
public:
	Menu(){
			gamestatus = 0;
			timeTrial = 0;
			cursor_y = 590;
		}
	int gameStatus(){
		return gamestatus;
	}
	void setGameStatus(int x){
		gamestatus = x;
	}
	void setCursorY(int y){
		cursor_y =y;
	}
	void setLevelMode(int x){
		timeTrial = x;
	}
	int getLevelMode(){
		return timeTrial;
	}
	void setName(char c){
		name = name + c;
	}
	void setSaveName(string a){
		name = a;
	}
	string getName(){
		return name;
	}
	void draw_menu(){ // Status 0
		DrawRoundRect(180, cursor_y, 230, 40, colors[RED], 0);
		DrawString( 220, 600, "START", colors[WHITE]);
		DrawString( 220, 550, "LEVELS", colors[WHITE]);
		DrawString( 220, 500, "HIGHSCORES", colors[WHITE]);
		DrawString( 220, 450, "HELP", colors[WHITE]);
		DrawString( 220, 400, "EXIT", colors[WHITE]);
		DrawRectangle(180, 390, 10, 240, colors[MISTY_ROSE]);
	}
	void draw_pause(){ // Status 2
		DrawRoundRect(180, cursor_y, 230, 40, colors[RED], 0);
		DrawString( 220, 600, "RESUME", colors[WHITE]);
		DrawString( 220, 550, "SAVE GAME", colors[WHITE]);
		DrawString( 220, 500, "MAIN MENU", colors[WHITE]);
		DrawRectangle(180, 490, 10, 140, colors[MISTY_ROSE]);
	}
	void start_menu(){ // Status 3
		DrawRoundRect(180, cursor_y, 230, 40, colors[RED], 0);
		DrawString( 220, 600, "NEW GAME", colors[WHITE]);
		DrawString( 220, 550, "LOAD GAME", colors[WHITE]);
		DrawString( 220, 500, "BACK", colors[WHITE]);
		DrawRectangle(180, 490, 10, 140, colors[MISTY_ROSE]);
	}
	void level_menu(){ // Status 4
		DrawRoundRect(180, cursor_y, 230, 40, colors[RED], 0);
		DrawString( 220, 600, "LEVEL 1", colors[WHITE]);
		DrawString( 220, 550, "LEVEL 2", colors[WHITE]);
		DrawString( 220, 500, "LEVEL 3", colors[WHITE]);
		DrawString( 220, 450, "LEVEL 4", colors[WHITE]);
		DrawString( 220, 400, "LEVEL 5", colors[WHITE]);
		DrawString( 220, 350, "BACK", colors[WHITE]);
		DrawRectangle(180, 340, 10, 290, colors[MISTY_ROSE]);
	}
	void level_mode(){ // Status 5
		DrawRoundRect(180, cursor_y, 230, 40, colors[RED], 0);
		DrawString( 220, 600, "NORMAL", colors[WHITE]);
		DrawString( 220, 550, "TIME TRIAL", colors[WHITE]);
		DrawRectangle(180, 540, 10, 90, colors[MISTY_ROSE]);
	}
	void name_menu(){ // Status 6
		DrawRoundRect(180, 590, 230, 40, colors[RED], 0);
		DrawRoundRect(180, 490, 230, 40, colors[RED], 0);
		DrawString( 220, 600, "ENTER NAME", colors[WHITE]);
		DrawString( 220, 550, name, colors[WHITE]);
		DrawString( 220, 500, "NEXT", colors[WHITE]);
		DrawRectangle(180, 540, 10, 40, colors[MISTY_ROSE]);
	}
	void game_over(){
		DrawRoundRect(180, 540, 230, 40, colors[RED], 0);
		DrawString( 220, 600, "GAME OVER", colors[WHITE]);
		DrawString( 220, 550, "MAIN MENU", colors[WHITE]);
	}
	void No_Save(){
		DrawRoundRect(180, 540, 230, 40, colors[RED], 0);
		DrawString( 220, 600, "NO SAVE FILE DETECTED", colors[WHITE]);
		DrawString( 220, 550, "MAIN MENU", colors[WHITE]);
	}
	void help_menu(){
		DrawRoundRect(210, 685, 100, 50, colors[RED], 0);
		DrawString( 220, 700, "HELP", colors[WHITE]);
		DrawString( 150, 600, "-Use Mouse Press to Drag and Drop Gems", colors[WHITE]);
		DrawString( 150, 550, "-Form 3 or more Chains of Vertical or", colors[WHITE]);
		DrawString( 150, 500, "-Horizontal gems of same color.", colors[WHITE]);
		DrawString( 150, 400, "Your Goal is to Complete all 5 Levels", colors[WHITE]);
		DrawString( 150, 350, "to get the Highest score", colors[WHITE]);
		DrawString( 150, 300, "Complete All 5 Levels to Win the game.", colors[WHITE]);
		DrawRoundRect(210,240, 100, 40, colors[RED], 0);
		DrawString( 220, 250, "BACK", colors[WHITE]);
	}




};



#endif /* MENU_H_ */
