Lab5
====

Functionality Objectives: Read and Decode button presses from an IR Remote, Make the LED's on the MSP430 turn ON and OFF with button presses from the remote control, and implement a game on the LED screen that you can use button presses from the MSP430 to control.

Documentation: Use of Dr Coulston's code to help me get started with the lab.

Met Functionalities: Day Two Activities - Checked by Dr York
                    Required Functionality - Checked by Dr York
                    A - Functionality - Checked by Dr York
                    

#Decoding button presses from an IR Remote

Connecting the IR Reader:

When you are looking at the sensor ball on your IR receiver module, the pin on the left is your signal pin; the pin in the middle is your ground pin; and the pin on the right is your Vcc.

On your MSP430, connect the signal pin to XIN/P2.6 on J2, the ground pin to the GND pin on J6, and the Vcc pin to Vcc on J6.

The Interrupt Method:

In the Interrupt Service Routine I needed to take the pulse Duration counts that are taken from the TAR and determine if the duration of the pulse should be considered a ONE, a ZERO, or the START_PULSE. If it is any other range of counts than it will be ignored.

The Range I used were determined from the Day One Activities, which can be found in the files above.

The range of values that I used for my specific remote for Logic0 pulse; Logic1 pulse; and Start Pulse can be seen in the code I used in the header "start5.h" file:

```
#define		averageLogic0Pulse	450
#define		averageLogic1Pulse	0x05DF
#define		averageStartPulse	22500
#define		minLogic0Pulse		averageLogic0Pulse - 200
#define		maxLogic0Pulse		averageLogic0Pulse + 200
#define		minLogic1Pulse		averageLogic1Pulse - 200
#define		maxLogic1Pulse		averageLogic1Pulse + 200
#define		minStartPulse		averageStartPulse - 1000
#define		maxStartPulse		averageStartPulse + 1000
```

Then the next thing I needed to define was the values for the important button presses that I might use on the IR Remote, which are defined as follows:

```
#define		PWR		0xC2D0
#define		ONE		0xC284
#define		TWO		0xC244
#define		THR		0xC2C4

#define		VOL_UP	0xC228 //right
#define		VOL_DW	0xC2A8 //left
#define		CH_UP	0xC298 //up
#define		CH_DW	0xC218 //down
```

Now that my ranges and my values for the button presses are defined I can start changing th Interrupt Service Routine to take the `pulseDuration` counts and set the values of the pulses to ones and zeros and a "Start Value" that I defined as a 2.

The code accomplishing this can be seen below:

```
if ((pulseDuration < maxStartPulse) && (pulseDuration > minStartPulse)) {
				pulseDuration = 2;
			} else if ((pulseDuration < maxLogic1Pulse) && (pulseDuration > minLogic1Pulse)) {
				pulseDuration = 1;
			} else if ((pulseDuration < maxLogic0Pulse) && (pulseDuration > minLogic0Pulse)) {
				pulseDuration = 0;
			}

			packetData[packetIndex++] = pulseDuration;
```

Now I needed to set a flag that says to the `main(void)` "Hey I got a new packet of data for you to look at!!"
The code to accomplish this is EASY and is below:
```
	if (packetIndex > 40) {
		newIrPacket = TRUE;
	}

	P2IFG &= ~BIT6;			// Clear the interrupt flag to prevent immediate ISR re-entry
```

One thing important about `packetIndex > 40` my message length is 16; however, I just decided I want to look at a bigger set of data to find what message is being sent by just finding the start Value.

It bounces out of the ISR if the pulse length is high for too long.

Now I need to change the main method that will actually read the packet and decide what to do with it.

initMSP430():

This method just simply says how we need to talk to the MSP430 to be able to better read the IR Sensor, such as what the timer needs to be... the watchdog timer etc. Here is the explanation of the method in my code that was written by Dr Coulston:

```
// The timer must be enabled so that we can tell how long the pulses
// last.  In some degenerate cases, we will need to generate a interrupt
// when the timer rolls over.  This will indicate the end of a packet
// and will be used to alert main that we have a new packet.
```

Also just setting up what pins we will be talking to.

At the end of the method it enables interrupts with `_enable_interrupt();`

My Main Method:

At the top of my main.c before the main method I initialized these values:

```
int8	newIrPacket = FALSE;
int16	packetData[40];
int16	bitString;
int8	packetIndex = 0;
int8	packetIndex2 = 0;
```

First thing to do in the main is initMSP430();

Then we go into an infinite while loop that will just wait till it is interrupted by the IR Sensor when it reads data from the IR Sensor in the ISR.

Infinite while loop:

First set my packetIndex (not the one that is used int he ISR) to zero.

Then check if we have a new packet.

If we do have a new packet disable interrupt (we don't want to get interrupted again while we are trying to read the packet of data.

Look for the Start Value!!:
```
			while ((packetData[packetIndex2] != 2) && (packetIndex2 < 40)) {
				packetIndex2++;
			}
```

Once we have found the start value let's read in the message!: (of length 16)
```
			int length = 0;

			while (length < 16) {
				bitString+=packetData[packetIndex2++];
				bitString<<=1;
				length++;
			}
```

Then check what button press the message was and LED's to turn on on the MSP430():
```
				if (bitString == CH_UP) {
					P1OUT |= BIT0;
						}
				if (bitString == CH_DW) {
					P1OUT &= ~BIT0;
						}
				if (bitString == ONE) {
					P1OUT ^= BIT0;
						}
				if (bitString == VOL_UP) {
					P1OUT |= BIT6;
						}
				if (bitString == VOL_DW) {
					P1OUT &= ~BIT6;
						}
				if (bitString == TWO) {
					P1OUT ^= BIT6;
				}
```

Then at the end of what we are doing if there is a new packet. Set the bitString that is the register that contains the message back to zero, set the packetIndex back to zero, and put the packet flag back to false.

Finally do a a little delay so that there aren't multiple button presses really fast.

```
			int i;
			for (i = 0; i<0xFFFF; i++);
```

Then continue in the infinite while loop waiting for more button presses read in from the IR Sensor.

#A Functionality

Objective: Take the decoded button presses and instead of turning the LED's on or off, talk to the LCD screen to implement the Etch-a-Sketch Lab that was in Lab4 Repository.

I used the nokia.asm to talk to the LCD Screen, so I included that file in my project.

I kept the same header file from the Required Functionality

I needed to define the values for the LCD Screen that I need for the Etch-a-Sketch routine:
```
//define stuff for the LCD Screen
extern void init();
extern void initNokia();
extern void clearDisplay();
extern void drawBlock(unsigned char row, unsigned char col, unsigned char color);

#define		TRUE			1
#define		FALSE			0
```

Initialize the things I need for the LCD Screen and for the MSP430 IR Sensor:
```
	unsigned char x, y, button_press, color;

	// === Initialize system ================================================
	IFG1 = 0; /* clear interrupt flag1 */
	WDTCTL = WDTPW + WDTHOLD; /* stop WD */
	button_press = FALSE;
	//above copied over from Lab 4 Required Functionality
	color = TRUE;



	initMSP430();				// Setup MSP to process IR and buttons

	//copy over from lab 4 Required Functionality
	init();
	initNokia();
	clearDisplay();
	x = 4;
	y = 4;
	drawBlock( y, x, color);

	_enable_interrupt();
```

After I get a newPacket and I'm going through what I want to do with message... After I get the message I need to talk to the LCD so I needed to init the things I need:
```
			init();
			initNokia();
```

Then for each button press I needed to do the things that I need to do for the Etch-a-Sketch:
```
				if (bitString == CH_UP) {

					if (y >= 1)
						y = y - 1;
					button_press = TRUE;
				}
				if (bitString == CH_DW) {

					if (y <= 6)
						y = y + 1;
					button_press = TRUE;
						}
				if (bitString == ONE) {
					if (color == TRUE) {
						color = FALSE;
					} else {
						color = TRUE;
					}
						}
				if (bitString == VOL_UP) {
					if (x <= 10)
						x = x + 1;
					button_press = TRUE;
						}
				if (bitString == VOL_DW) {
					if (x >= 1)
						x = x - 1;
					button_press = TRUE;
						}
				}
				if (button_press) {
					button_press = FALSE;
					drawBlock(y, x, color);
				}
```

Then I need to draw the block and re-initialize the MSP430 to continue talking to the MSP430 for recieve another data packet:
```
				drawBlock( y, x, color);
				initMSP430();
```

That is all :) Thank you for reading.

#Have a Great Air Force Day and Thanks for Reading!


