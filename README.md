Lab4
====

Functionality Objectives: Etch-A-Sketch; Bouncing Ball; Pong

Met Functionalities:
1) Etch-A-Sketch - check off by Captain Trimble
2) Bouncing Ball - check off by Captain Trimble
3) Pong - check off by Captain Trimble
4) Bonus: Inverting the Screen - check off by Dr. York


#Objectives For Lab 4

You've spent the last 5 lessons transitioning from programming in assembly language to C. In this lab, you'll use C to create an etch-a-sketch-type program that utilizes some subroutines from Lab 3. You'll be expected to write clean, maintainable, modular code that is committed regularly to Git.

#Required Functionality

Modify your assembly drawBlock function to take in 3 values: an x coordinate, a y coordinate, and a color.

Create an etch-a-sketch program using the directional buttons of the LCD booster pack to control the position of the paint brush. The paint brush will draw 8x8 blocks of pixels. The user will change the position of the paint brush by pressing the directional buttons. Each button press will move the cursor 8 pixels in the direction pressed (see table below). Pressing the auxiliary button (SW3) will toggle the mode of the paint brush between filling squares and clearing squares.

This program must be written in C and call many of the subroutines written as part of lab 3, including drawBlock and changePosition.

**Note: All code and files are above in the ~~Lab4_ScrollingText File (Don't mind the name I originally believed that the objective for the lav was different)

We were given the code for the functionality from Lab3 (refer to the Lab three project) that moves a square around on the nokia LCD screen.

However, this project uses C to poll the buttons. The most important change I had to make in order to achieve required functionality is to poll the aux button first of all and then send in a parameter that I called "color" to change whether or not the square is "Painting" on the screen or "erasing the black on the screen.

The code that was important for polling the AUX button in C is below:

```
else if (AUX_BUTTON == 0) {
			while (AUX_BUTTON == 0)
				;
			if (color == TRUE) {
				color = FALSE;
			} else {
				color = TRUE;
			}

		}
```

The method in assembly what was needed to change whether or not the square was "Painting" or erasing was:

```
extern void drawBlock(unsigned char row, unsigned char col, unsigned char color);
```

The code that I needed to add to assembly was "pushing and popping" another register to save the register that I would use for the color parameter within the method.

**So the row was R12, colomn was R13, and color was R14
```
	push	R5
	push	R12
	push	R13
	push	R14
```

Then I needed to check if the color was white or black and I needed to to assign the block either a clear square or a black square.

```
	cmp		#1, R14
	jz		black
	jmp		white

black:	mov		#0xFF, R13
		jmp		loop

white: 	mov		#0x00, R13

loop:	mov.w	#0x08, R5
```

So if the square is needs to be black it will jump to the black line and then jump over the white portion after it moves FF into R13.

Then I have to make sure that the screen isn't cleared when I am painting so that the square where the block was will either stay black or white when I move the square around the screen.

Which was just taken away from the C code. In other words the cleardisplay() was taken away from the polling the buttons loop.

#B Functionality

Create a bouncing block! This block should move across the screen with no more than 8 pixels per jump. It should bounce off the walls appropriately, similar to assignment 6. An adequate delay movement should be added between each block movement. Your starting position and starting x and y velocities should be initialized in your header, or should be randomly generated.

First needed to define the screen dimensions:

```
#define		TRUE			1
#define		FALSE			0
#define		WIDTH			11
#define		HEIGHT			8
```

I used the pong header and source file from an assignment we had in class that I made. It was to design a header a source file to be able to make a ball object and be able to bounce it around on a defined screen.

```
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
```

The above code creates a ball object and then a method that I can call that will move the ball. In move ball, it checks whether it collided with any of the walls and it will reverse the direction of the velocity before it increments the ball in the opposite direction.

In the main.c for B functionality, I create the ball (which is a square) and in an infinite loop call moveBall() and then it keeps redrawing the square passing drawblock the coordinates of the "ball" object, and I keep on clearing the diplay before redrawing the block.

Also there needed to be some kind of delay or else the ball would fly across the screen too fast. I simply just made nested for loops to get an exact time delay that looked good on the screen when I ran the program.

```
		for (x = 500; x>0; x--) { //delay a second
			for (y = 1279; y>0; y--);
		}
```

After that bouncing the ball across the screen worked!!

#A Functionality

Objective: Create Pong on your display! Create a single paddle that will move up and down on one side of the display, controlled by the up and down buttons. The block will bounce off the paddle like it bounces off the wall. When the block misses hitting the paddle, the game will end.

The first thing I needed to decide was how I was going to make the paddle for pong. I thought it was easiest and it made the most sense to just make a paddle with two more square that can only move up and down on the far left side of the screen.

All I needed to do was to create a new object for the paddle in the header and source files so that I could check whether or not the ball ran into the paddle. Below is how I made the object for the paddle:

```
	paddle createPaddle(int xPos, int yPos) {
		paddle paddleToCreate;

		paddleToCreate.position.x = xPos;
		paddleToCreate.position.y = yPos;

		return paddleToCreate;
	}
```

Then I had to make a new collision method to check if the ball ran into the paddle, which the code for is below:

```
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
```

In the main.c I first initialized "two paddles" but it is really one it was to make it easier to draw the paddle using the drawBlock() method in the assembly nokia.asm file.

Initialization:
```
    static paddle thePaddle1;
    static paddle thePaddle2;

    thePaddle1.position.x = 0;
    thePaddle1.position.y = 0;

    //just for drawing purposes
    thePaddle2.position.x = 0;
    thePaddle2.position.y = 1;
```

This is how I drew the "ball" and the "paddle" each time through the infinite loop:

```
			clearDisplay();

			drawBlock(theBall.position.y, theBall.position.x, color);
			drawBlock(thePaddle1.position.y, thePaddle1.position.x, color);
			drawBlock(thePaddle2.position.y, thePaddle2.position.x, color);
```

Then when I needed to delay for the movement of the ball and needing to poll for button presses (to move the paddle up and down the screen) then I needed to make sure that the paddle didn't move off the screen when I clicked up or down:

```
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
```

#Bonus Functionality: Inverting the Screen

I added on to A Functionality that whenver the aux button is pressed it sends clear display the parameter "color" that we used in the required functionality and would swap the drawing the paddle and ball from black to white or vice versa, and the display from white to black or vice versa. The cleardisplay() method in assembly needed to be modified to accept the parameter color and to be able to draw an all black screen if it needed to.



Documentation: Austin Bolinger talked about some concepts that were needed to accomplish required functionality so that I could get a head start and know what direction to take required functionality. It just saved me on time.

#Have a Great Air Force Day and Thanks for Reading!


