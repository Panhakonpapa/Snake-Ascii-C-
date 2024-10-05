#include <iostream>
#include <ostream>
#include <unistd.h>
#include <sys/ioctl.h>
#include <termios.h>
#include <fcntl.h>  

#define WIDTH 20 
#define HEIGHT 20

char board[HEIGHT][WIDTH]; 

int snakeX, snakeY; 
int snakeBodyX[100], snakeBodyY[100]; 
int snake_lenght = 1; 

int dx = 0, dy = 0; 

int foodX, foodY; 

class Board{
public: 
	void initializeBoard() {
		for (int i = 0; i < HEIGHT; i++) {
			for (int j = 0; j < WIDTH; j++) {
				if (i == 0 || i == HEIGHT - 1 | j == 0 || j == WIDTH - 1) {	
					board[i][j] = '#';  
				}
				else {
					board[i][j] = ' '; 
				}
			}
		}
	}
	void draw() {
		for (int i =0; i < HEIGHT; i++) {
			for (int j = 0; j < WIDTH; j++) {
				std::cout << "" << board[i][j];  
			}
			std::cout << std::endl; 
		}
	}
}; 

class Snake{
public: 
	void initializeSnake() {
		snakeX = WIDTH / 2; 
		snakeY = HEIGHT / 2; 
		board[snakeX][snakeY] = 'O'; 
		snakeBodyX[0] = snakeX; 
		snakeBodyY[0] = snakeY; 

	} 

	void moveSnake() {	
		board[snakeBodyX[snake_lenght - 1]][snakeBodyY[snake_lenght - 1]] = ' '; 
		
		for (int i = snake_lenght - 1; i > 0; i--) {
			snakeBodyX[i] = snakeBodyX[i - 1]; 
			snakeBodyY[i] = snakeBodyY[i - 1]; 
		}
		
		/* Update Snake Body */
		snakeX += dx; 
		snakeY += dy; 
		
		snakeBodyX[0] = snakeX; 
		snakeBodyY[0] = snakeY; 

		board[snakeX][snakeY] = 'O'; 

		/* Update body */
		for (int i  = 1; i < snake_lenght; i++) {
			board[snakeBodyX[i]][snakeBodyY[i]] = '0'; 
		}
	}
	bool checkCollisin() {
	if (snakeX <= 0 || snakeX >= HEIGHT - 1 || snakeY <= 0 || snakeY >= WIDTH - 1) {
		return true; 
	    }
	    for (int i = 1; i < snake_lenght; i++) {
		if (snakeBodyX[i] == snakeX && snakeBodyY[i] == snakeY) {
		    return true; 
		}
	    }
	    return false; 
	}


}; 
class Food{
public: 
	void getFood() {
		do {
			foodX = rand() % (WIDTH - 2) + 1; 
			foodY = rand() % (HEIGHT - 2) + 1; 

		} while(board[foodX][foodY] == 'O'); 	
		
		board[foodX][foodY] = '*'; 
	}
	bool cheakCollisionFood() {
		if (snakeX == foodX && snakeY == foodY) {
			return true;  
		}
		return false; 
	}	
}; 
void processInput() {
    char key = getchar();
    switch (key) {
        case 'w': dx = -1; dy = 0; break;  // Move up
        case 's': dx = 1; dy = 0; break;   // Move down
        case 'a': dy = -1; dx = 0; break;  // Move left
        case 'd': dy = 1; dx = 0; break;   // Move right
    }
}
int main() {
	Board board;	
	Snake snake; 
	Food food; 
	board.initializeBoard(); 
	snake.initializeSnake(); 
	food.getFood(); 
	while (1) {
		system("clear"); 

		board.draw(); 
		snake.moveSnake(); 
		if (food.cheakCollisionFood()) {
			food.getFood(); 
			snake_lenght++; 
		}
		
		processInput(); 

		if (snake.checkCollisin()) {
			std::cout << "Game Over " << std::endl; 
			break; 
		}
		
		usleep(200000);
	}

	return 0; 
}
