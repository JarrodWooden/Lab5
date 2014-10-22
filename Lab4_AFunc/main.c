#include <msp430g2553.h>
#include "pong.h"

extern void init();
extern void initNokia();
extern void clearDisplay();
extern void drawBlock(unsigned char row, unsigned char col, unsigned char color);

#define		TRUE			1
#define		FALSE			0
#define		WIDTH			11
#define		HEIGHT			8
#define		UP_BUTTON		(P2IN & BIT5)
#define		DOWN_BUTTON		(P2IN & BIT4)
#define		AUX_BUTTON		(P2IN & BIT3)
#define		LEFT_BUTTON		(P2IN & BIT2)
#define		RIGHT_BUTTON	(P2IN & BIT1)

void main() {

	unsigned char button_press, color;
	int		x, y;

	// === Initialize system ================================================
	IFG1 = 0; /* clear interrupt flag1 */
	WDTCTL = WDTPW + WDTHOLD; /* stop WD */

    static ball_t theBall;

    theBall.position.x = 4;
    theBall.position.y = 5;

    theBall.velocity.x = 1;
    theBall.velocity.y = -1;

    static paddle thePaddle1;
    static paddle thePaddle2;

    thePaddle1.position.x = 0;
    thePaddle1.position.y = 0;

    //just for drawing purposes
    thePaddle2.position.x = 0;
    thePaddle2.position.y = 1;

	init();
	initNokia();
	clearDisplay();

	color = TRUE;
	drawBlock( theBall.position.y, theBall.position.x, color);
	drawBlock(thePaddle1.position.y, thePaddle1.position.x, color);
	drawBlock(thePaddle2.position.y, thePaddle2.position.x, color);

	while (1) {

		theBall = moveBall(theBall, thePaddle1);	//not actually moving the paddle though

		for (x = 500; x>0; x--) { //delay a second
			for (y = 1279; y>0; y--);
			if (UP_BUTTON == 0) {
				while (UP_BUTTON == 0)		//debouncing (kind of)
					;
				if (thePaddle1.position.y >= 1)
					thePaddle1.position.y = thePaddle1.position.y - 1;
					thePaddle2.position.y = thePaddle1.position.y - 1;
				button_press = TRUE;
			} else if (DOWN_BUTTON == 0) {
				while (DOWN_BUTTON == 0)	//debouncing
					;
				if (thePaddle2.position.y <= 6)
					thePaddle1.position.y = thePaddle1.position.y + 1;
					thePaddle2.position.y = thePaddle1.position.y + 1;
				button_press = TRUE;
			} else if (AUX_BUTTON == 0) {
				while (AUX_BUTTON == 0)		//debouncing
					;
				if (color == TRUE) {
					color = FALSE;
				} else {
					color = TRUE;
				}

			}
		}

			clearDisplay();

			drawBlock(theBall.position.y, theBall.position.x, color);
			drawBlock(thePaddle1.position.y, thePaddle1.position.x, color);
			drawBlock(thePaddle2.position.y, thePaddle2.position.x, color);


	}
}
