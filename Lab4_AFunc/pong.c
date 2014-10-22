/*
 * pong.c
 *
 *  Created on: Oct 13, 2014
 *      Author: C16Jarrod.Wooden
 */

#include "pong.h"
#include <msp430g2553.h>

extern void clearDisplay();

	ball_t createBall(int xPos, int yPos, int xVel, int yVel) {
		ball_t ballToCreate;

		ballToCreate.position.x = xPos;
		ballToCreate.position.y = yPos;

		ballToCreate.velocity.x = xVel;
		ballToCreate.velocity.y = yVel;

		return ballToCreate;
	}

	paddle createPaddle(int xPos, int yPos) {
		paddle paddleToCreate;

		paddleToCreate.position.x = xPos;
		paddleToCreate.position.y = yPos;

		return paddleToCreate;
	}

	ball_t moveBall(ball_t ballToMove, paddle thePaddle) {

		//check if the ball has collided with the paddle
		if (collisionObjects(ballToMove, thePaddle)) {
			ballToMove.velocity.x = -1*ballToMove.velocity.x;
		}

		//check if ball is running into any of the side walls
		if (collisionX(ballToMove.position.x)) {
			ballToMove.velocity.x = -1*ballToMove.velocity.x;
		}


		//check if the ball is running into the top or bottom and move the ball
		if (collisionY(ballToMove.position.y)) {
			ballToMove.velocity.y = -1*ballToMove.velocity.y;
		}

		ballToMove.position.y += ballToMove.velocity.y;
		ballToMove.position.x += ballToMove.velocity.x;


		return ballToMove;
	}

	static signed int collisionX(int xPos) {

		if (xPos >= (SCREEN_WIDTH)) {
			return 1;
		}

		else if (xPos <= 0) {
			while(1) {
				clearDisplay();		//just clear the display forever if the user loses.
			}
			return 1;
		} else {
			return 0;
		}
	}

	static signed int collisionY(int yPos) {

		if (yPos >= (SCREEN_HEIGHT)) {
			return 1;
		}

		else if (yPos <= 0) {
			return 1;
		} else {
			return 0;
		}
	}

	static signed int collisionObjects(ball_t theBall, paddle thePaddle) {
		//need to check whether or not the bouncing ball has collided with the
		//paddle

		//remember the way I'm doing it is that there are two boxes together to make the paddle.

		if (theBall.position.x <= (thePaddle.position.x+1)) {
			if (theBall.position.y >= thePaddle.position.y && theBall.position.y <= (thePaddle.position.y+1)) {
				return 1;
			}
		}

			return 0;

	}









