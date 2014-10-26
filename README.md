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
