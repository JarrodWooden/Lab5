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


