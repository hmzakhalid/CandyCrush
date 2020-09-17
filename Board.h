/*
 * Board.h
 *
 *  Created on: Jun 9, 2020
 *      Author: hamza
 */

#ifndef BOARD_H_
#define BOARD_H_


#include "util.h"
#include "Menu.h"
#include "Candy.h"
#include <fstream>
#include <iostream>
using namespace std;

class Board: public Menu{
	bool hint;
	bool game;
	int timeScore;
	int score;
	int level;
	int lives;
	int NumHints;
	string saveName[10];
	int saveScore[10];
	Candy Hint[2];
	Candy candy[9][9];
public:
	Board(){
		//int y = 165;
		int sx = 25, sy = 250;
		hint = false;
		game = false;
		level= 1;
		score = 0;
		lives = 3;
		NumHints = 3;
		timeScore = 0;
		srand(time(NULL));
		for(int i=0; i<9;i++){
			for(int j=0; j<9; j++){
				candy[i][j].value = rand()%5;
				candy[i][j].x = sx;
				candy[i][j].y = sy;
				sx+=65;
			}
			sx = 25;
			sy += 65;
		}
	}
	void makeCandies(){
		int sx = 25, sy = 250;
		srand(time(NULL));
		for(int i=0; i<9;i++){
			for(int j=0; j<9; j++){
				candy[i][j].value = rand()%5;
				candy[i][j].x = sx;
				candy[i][j].y = sy;
				sx+=65;
			}
			sx = 25;
			sy += 65;
		}
	}
	void draw_board(){
		int border = 15;
		int width = 610;
		int height = 940;
		int m = 75, n=300;
		DrawRectangle(0, 0, border, height, colors[MISTY_ROSE]);
		DrawRectangle( width-border, 0, border ,height, colors[MISTY_ROSE]);
		DrawRectangle(0, 0, width,border, colors[MISTY_ROSE]);
		DrawRectangle(0, height-border, width,border, colors[MISTY_ROSE]);
		DrawRectangle(0, (height-100)-border, width,border, colors[MISTY_ROSE]);
		DrawRectangle(0, (height-700)-border, width,border, colors[MISTY_ROSE]); // middle one
		for(int i = 0; i< 8; i++){
			DrawRectangle(m,235, 6, 600, colors[MISTY_ROSE]);
			m+=65;
			DrawRectangle(15,n, 600, 6, colors[MISTY_ROSE]);
			n+=65;
		}

		//Pause Button
		DrawCircle(305, 65, 40, colors[MISTY_ROSE]);
		DrawRectangle(288,45, 10, 40, colors[BLACKO]);
		DrawRectangle(312,45, 10, 40, colors[BLACKO]);
	}
	void draw_candies(){
		for(int i = 0; i< 9; i++){
			for(int j=0; j<9; j++){
//				cout << "Candy (" << i << "," << j<<") X: "<<candy[i][j].x << endl;
//				cout << "Candy (" << i << "," << j<<") Y: "<<candy[i][j].y << endl << endl;
				candy[i][j].draw();
			}
		}
	}

	void Switch(int ori, int x, int y){
		for(int i = 0; i< 9; i++){
			for(int j=0; j<9; j++){
				if((x >= candy[i][j].x && x <= (candy[i][j].x + 40)) && (y >= candy[i][j].y && y <= (candy[i][j].y + 40))){
					Candy temp;
					if(ori == 0 && j !=8){
						candy[i][j].x += 65;
						candy[i][j+1].x -= 65;
						//Switching the position on the array Right
						temp = candy[i][j];
						candy[i][j] = candy[i][j+1];
						candy[i][j+1] = temp;
						if(check() == false){
							lives--;
							candy[i][j].x += 65;
							candy[i][j+1].x -= 65;
							//Switching the position on the array Right
							temp = candy[i][j];
							candy[i][j] = candy[i][j+1];
							candy[i][j+1] = temp;
						}

					}else if(ori == 1 && j!=0){
						candy[i][j-1].x += 65;
						candy[i][j].x -= 65;
						//Switching the position on the array Left
						temp = candy[i][j-1];
						candy[i][j-1] = candy[i][j];
						candy[i][j] = temp;
						if(check() == false){
							lives--;
							candy[i][j-1].x += 65;
							candy[i][j].x -= 65;
							//Switching the position on the array Left
							temp = candy[i][j-1];
							candy[i][j-1] = candy[i][j];
							candy[i][j] = temp;
						}
					}else if(ori == 2 && i!=8){
						candy[i][j].y += 65;
						candy[i+1][j].y -= 65;
						//Switching the position on the array Top
						temp = candy[i][j];
						candy[i][j] = candy[i+1][j];
						candy[i+1][j] = temp;
						if(check() == false){
							lives--;
							candy[i][j].y += 65;
							candy[i+1][j].y -= 65;
							//Switching the position on the array Top
							temp = candy[i][j];
							candy[i][j] = candy[i+1][j];
							candy[i+1][j] = temp;
						}
					}else if(ori == 3 && i!=0){
						candy[i-1][j].y += 65;
						candy[i][j].y -= 65;
						//Switching the position on the array Down
						temp = candy[i-1][j];
						candy[i-1][j] = candy[i][j];
						candy[i][j] = temp;
						if(check() == false){
							lives--;
							candy[i-1][j].y += 65;
							candy[i][j].y -= 65;
							//Switching the position on the array Down
							temp = candy[i-1][j];
							candy[i-1][j] = candy[i][j];
							candy[i][j] = temp;
						}
					}
					break;
				}
			}
		}
	}
	bool Switch_Hint(int ori, int i, int j){
			Candy temp;
			if(ori == 0){
				//Switching the position on the array Right
				temp = candy[i][j];
				candy[i][j] = candy[i][j+1];
				candy[i][j+1] = temp;
				if(check() == true){
					//Switching the position on the array Right
					temp = candy[i][j];
					candy[i][j] = candy[i][j+1];
					candy[i][j+1] = temp;
					return true;

				}else{
					temp = candy[i][j];
					candy[i][j] = candy[i][j+1];
					candy[i][j+1] = temp;
					return false;
				}


			}else if(ori == 1){
				//Switching the position on the array Left
				temp = candy[i][j-1];
				candy[i][j-1] = candy[i][j];
				candy[i][j] = temp;
				if(check() == true){
					//Switching the position on the array Left
					temp = candy[i][j-1];
					candy[i][j-1] = candy[i][j];
					candy[i][j] = temp;
					return true;
				}else{
					temp = candy[i][j-1];
					candy[i][j-1] = candy[i][j];
					candy[i][j] = temp;
					return false;
				}

			}else if(ori == 2){
				//Switching the position on the array Top
				temp = candy[i][j];
				candy[i][j] = candy[i+1][j];
				candy[i+1][j] = temp;
				if(check() == true){
					//Switching the position on the array Top
					temp = candy[i][j];
					candy[i][j] = candy[i+1][j];
					candy[i+1][j] = temp;
					return true;
				}else{
					temp = candy[i][j];
					candy[i][j] = candy[i+1][j];
					candy[i+1][j] = temp;
					return false;
				}
			}else if(ori == 3){

				//Switching the position on the array Down
				temp = candy[i-1][j];
				candy[i-1][j] = candy[i][j];
				candy[i][j] = temp;
				if(check() == true){
					//Switching the position on the array Down
					temp = candy[i-1][j];
					candy[i-1][j] = candy[i][j];
					candy[i][j] = temp;
					return true;
				}else{
					temp = candy[i-1][j];
					candy[i-1][j] = candy[i][j];
					candy[i][j] = temp;
					return false;
				}
			}
		return false;
	}
	bool check(){
		int count=0, shape=0;
		bool check = false;

		for(int i =0; i<9; i++){
			for(int j=0; j<9; j++){
				shape = candy[i][j].value;
				for(int k=j; k<9;k++){
					if(shape == candy[i][k].value){
						count++;
					}else{
						break;
					}
				}
				if(count >= 3){
					if(hint == false){
						score = score + (count * 10);
						timeScore += (count*10);
						fill_hor(i,j, count);
						count = 0;
					}

					check = true;

				}else{
					count = 0;
				}
			}
		}
		for(int j=0; j<9; j++){
			for(int i=0; i<9; i++){
				shape = candy[i][j].value;
				for(int k=i; k<9; k++){
					if(shape == candy[k][j].value){
						count++;
					}else{
						break;
					}
				}
				if(count >= 3){
					//cout << endl << "Count at (" << i << "," << j << "): " << count << endl;
					if(hint == false){
						score += (count*10);
						timeScore += (count*10);
						fill_vert(i,j,count);
						count = 0;
					}
					check = true;
				}else{
					count = 0;
				}
			}
		}
		return check;
	}
	void fill_hor(int a, int b, int c){
		for(int i = b; i<b+c; i++){
			candy[a][i].value = 9;
		}
		Candy temp;
		for(int i=a; i<8;i++){
			for(int j=b; j<b+c; j++){

				candy[i][j].y += 65;
				candy[i+1][j].y -= 65;
				//Switching the position on the array Top
				temp = candy[i][j];
				candy[i][j] = candy[i+1][j];
				candy[i+1][j] = temp;

			}
		}
		for(int i = b; i<b+c; i++){
			candy[8][i].value = rand()%5;
		}
	}
	void fill_vert(int a, int b, int c){

		for(int k=a; k<a+c; k++){
			candy[k][b].value = 9;

		}
		Candy temp;
		for(int i=(a+c)-1; i>=a; i--){
			for(int j = i; j < 8; j++){
				candy[j][b].y += 65;
				candy[j+1][b].y -= 65;
				//Switching the position on the array Top
				temp = candy[j][b];
				candy[j][b] = candy[j+1][b];
				candy[j+1][b] = temp;
			}
			candy[8][b].value = rand()%5;
		}



	}

	void drawHint(){
		for(int i=0; i<2; i++){
			Hint[i].value = 5;
			Hint[i].draw();
		}
	}
	bool getHint(){
		return hint;
	}
	void setHint(bool a){
		hint = a;
	}
	bool show_hint(){
		bool check = false;
		if(NumHints > 0){
			NumHints--;

			hint = true;
			for(int i=1; i< 8; i++){
				for(int j=1; j <8; j++){
					for(int k=0; k<4; k++){
						if(Switch_Hint(k,i,j) == true){
							cout << i << " " << j << " " <<k << endl;
							Hint[0] = candy[i][j];
							Hint[0].x -=10;
							Hint[0].y -=10;
							if(k==0){
								Hint[1] = candy[i][j+1];
							}
							else if(k==1){
								Hint[1] = candy[i][j-1];
							}
							else if(k==2){
								Hint[1] = candy[i+1][j];
							}
							else if(k==3){
								Hint[1] = candy[i-1][j];
							}
							Hint[1].x -=10;
							Hint[1].y -=10;
							check = true;
							break;
						}
					}

					if(check == true)
						break;
				}
				if(check == true)
					break;

			}
		}
		return check;
	}

	void save_game(){
		ofstream saveFile("SaveGame.txt");
		if(saveFile.is_open()){
			saveFile << getName() << endl;
			saveFile << getScore() << endl;
			saveFile << getNumHint() << endl;
			saveFile << getLevel() << endl;
			saveFile << getLevelMode() << endl;
			if(getLevelMode() == 1){
				saveFile << getTimeScore() << endl;
			}
			saveFile << getLives() << endl;
			for(int i=0; i<9;i++){
				for(int j=0; j<9; j++){
					saveFile << candy[i][j].value;
				}
			}

		}
		saveFile.close();
	}
	void load_game(){

		string line;
		char c;
		ifstream loadFile;
		loadFile.open("SaveGame.txt", ios::in);
		if(loadFile.is_open()){
			getline(loadFile, line);
			setSaveName(line);
			getline(loadFile, line);
			setScore(stoi(line));
			getline(loadFile, line);
			setNumHint(stoi(line));
			getline(loadFile, line);
			setLevel(stoi(line));
			getline(loadFile, line);
			setLevelMode(stoi(line));
			if(getLevelMode() == 1){
				getline(loadFile, line);
				setTimeScore(stoi(line));
				game = true;
			}
			getline(loadFile, line);
			setLives(stoi(line));
			for(int i=0; i<9;i++){
				for(int j=0; j<9; j++){
					loadFile >> c;
					candy[i][j].value = (int)(c)-48;
					cout << c << " " ;
				}
				cout << endl;
			}
		}
		loadFile.close();
	}
	void delete_game(){
		remove("SaveGame.txt");
	}
	void setGame(bool a){
		game = a;
	}
	bool getGame(){
		return game;
	}
	void SaveHighScore(){
		static bool NewScore = false;
		string line, temp;
		ifstream loadFile("Highscore.txt");
		for(int i = 0; i<10; i++){
			getline(loadFile, line);
			temp = line;
			getline(loadFile, line);
			if(score >= stoi(line) && NewScore == false){
				saveScore[i] = score;
				saveName[i] = getName();
				i++;
				saveName[i] = temp;
				saveScore[i] = stoi(line);
				NewScore= true;
			}else{
				saveName[i] = temp;
				saveScore[i] = stoi(line);
			}

		}
		loadFile.close();
		ofstream saveFile("Highscore.txt");
		for(int i = 0; i<10; i++){
			saveFile << saveName[i] << endl;
			saveFile << saveScore[i] << endl;
		}
		saveFile.close();
	}
	void LoadHighScore(){
		string line;
		ifstream loadFile("Highscore.txt");
		if(loadFile.is_open()){
			for(int i=0; i< 10; i++){
				getline(loadFile, line);
				cout << line << endl;
				saveName[i] = line;
				getline(loadFile, line);
				cout << line << endl;
				saveScore[i] = stoi(line);
			}
		}
		loadFile.close();

	}
	void ShowHighScore(){
		int y = 750;
		DrawRoundRect(140, y+40, 230, 40, colors[RED], 0);
		DrawString( 180, y+50, "HIGHSCORE", colors[WHITE]);
		for(int i=0; i<10; i++){
			DrawString( 180, y, to_string(i+1) + ". "+ saveName[i] + " - " + to_string(saveScore[i]), colors[WHITE]);
			y-=50;
		}
		DrawRoundRect(140, y-10, 230, 40, colors[RED], 0);
		DrawString( 180, y, "BACK", colors[WHITE]);
	}
	void setNumHint(int x){
			NumHints = x;
		}
		int getNumHint(){
			return NumHints;
		}
	void setScore(int x){
		score = x;
	}
	int getScore(){
		return score;
	}
	void setTimeScore(int x){
		timeScore = x;
	}
	int getTimeScore(){
		return timeScore;
	}
	int getLevel(){
		return level;
	}
	void setLevel(int x){
		level = x;
	}
	int getLives(){
		return lives;
	}
	void setLives(int x){
		lives = x;
	}

	void Score(){
		if(getLevelMode() == 0){
			if(score >= level*1000){
				score = 0;
				level++;
				makeCandies();
			}
			DrawRectangle(100, 130 , (400 * ((score*100)/(level*1000)))/100 ,15, colors[CHOCOLATE]);
		}else if(getLevelMode() == 1) {
			if(timeScore >= level*1000){
							level++;
							game = false;
							makeCandies();
				}
			DrawRectangle(100, 130 , (400 * ((timeScore*100)/(level*1000)))/100 ,15, colors[CHOCOLATE]);
		}

		DrawString( 50, 880, "Score = " + to_string(score), colors[MISTY_ROSE]);
		DrawString( 50, 850, "Hints = " + to_string(NumHints), colors[MISTY_ROSE]);
		DrawString( 450, 880, "Level = " + to_string(level), colors[MISTY_ROSE]);
		DrawString( 450, 850, "Lives = " + to_string(lives), colors[MISTY_ROSE]);
		DrawRoundRect(430, 170, 100, 40, colors[RED], 0);
		DrawString( 450, 180 , "HINT ", colors[MISTY_ROSE]);
		// PROGRESS BAR

		DrawString( 265, 180 , "Progress ", colors[MISTY_ROSE]);


		DrawRectangle(100, 145 , 415,15, colors[MISTY_ROSE]);
		DrawRectangle(100, 115 , 415,15, colors[MISTY_ROSE]);
		DrawRectangle(90, 115 , 15,45, colors[MISTY_ROSE]);
		DrawRectangle(500, 115 , 15,45, colors[MISTY_ROSE]);
		//cout << (400 * ((score*100)/1000))/100 << endl;
		}


};



#endif /* BOARD_H_ */
