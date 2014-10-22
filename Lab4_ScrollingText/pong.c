/*
 * pong.c
 *
 *  Created on: Oct 13, 2014
 *      Author: C16Jarrod.Wooden
 */

#include "pong.h"

	ball_t createBall(int xPos, int yPos, int xVel, int yVel, unsigned char radius) {
		ball_t ballToCreate;

		ballToCreate.position.x = xPos;
		ballToCreate.position.y = yPos;

		ballToCreate.velocity.x = xVel;
		ballToCreate.velocity.y = yVel;

		ballToCreate.radius = radius;

		return ballToCreate;
	}

	ball_t moveBall(ball_t ballToMove) {

		//check if ball is running into any of the side walls
		if (collisionX(ballToMove.position.x, ballToMove.velocity.x,ballToMove.radius)) {
			ballToMove.velocity.x = -1*ballToMove.velocity.x;
		}


		ballToMove.position.x += ballToMove.velocity.x;


		//check if the ball is running into the top or bottom and move the ball
		if (collisionY(ballToMove.position.y, ballToMove.velocity.y,ballToMove.radius)) {
			ballToMove.velocity.y = -1*ballToMove.velocity.y;
		}

		ballToMove.position.y += ballToMove.velocity.y;


		return ballToMove;
	}

	static signed int collisionX(int xPos, int xVel, int rad) {

		if (xPos >= (SCREEN_WIDTH - rad)) {
			return 1;
		}

		else if (xPos <= 0) {
			return 1;
		} else {
			return 0;
		}
	}

	static signed int collisionY(int yPos, int yVel, int rad) {

		if (yPos >= (SCREEN_HEIGHT - rad)) {
			return 1;
		}

		else if (yPos <= 0) {
			return 1;
		} else {
			return 0;
		}
	}









