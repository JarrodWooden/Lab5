/*
 * pong.c
 *
 *  Created on: Oct 13, 2014
 *      Author: C16Jarrod.Wooden
 */

#include "pong.h"

	ball_t createBall(int xPos, int yPos, int xVel, int yVel) {
		ball_t ballToCreate;

		ballToCreate.position.x = xPos;
		ballToCreate.position.y = yPos;

		ballToCreate.velocity.x = xVel;
		ballToCreate.velocity.y = yVel;

		return ballToCreate;
	}

	ball_t moveBall(ball_t ballToMove) {

		//check if ball is running into any of the side walls
		if (collisionX(ballToMove.position.x)) {
			ballToMove.velocity.x = -1*ballToMove.velocity.x;
		}


		ballToMove.position.x += ballToMove.velocity.x;


		//check if the ball is running into the top or bottom and move the ball
		if (collisionY(ballToMove.position.y)) {
			ballToMove.velocity.y = -1*ballToMove.velocity.y;
		}

		ballToMove.position.y += ballToMove.velocity.y;


		return ballToMove;
	}

	static signed int collisionX(int xPos) {

		if (xPos >= (SCREEN_WIDTH)) {
			return 1;
		}

		else if (xPos <= 0) {
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









