/*
 * pong.h
 *
 *  Created on: Oct 13, 2014
 *      Author: C16Jarrod.Wooden
 *      Date: 13 October 2014
 *      Description: implements a subset of the pong game
 *      Documentation: Started with the pong.h from Captain Todd Branchflower's pong.h file
 *      that he provided to us.
 */

#ifndef PONG_H_
#define PONG_H_

#define SCREEN_WIDTH 11
#define SCREEN_HEIGHT 7

typedef struct {
    int x;
    int y;
} vector2d_t;

typedef struct {
    vector2d_t position;
    vector2d_t velocity;
} ball_t;


//need to implement the below functions in pong.c
ball_t createBall(int xPos, int yPos, int xVel, int yVel);

ball_t moveBall(ball_t ballToMove);

static signed int collisionX(int xPos);

static signed int collisionY(int yPos);

#endif /* PONG_H_ */
