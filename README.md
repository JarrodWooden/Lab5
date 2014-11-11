Lab5
====

Functionality Objectives: Read and Decode button presses from an IR Remote, Make the LED's on the MSP430 turn ON and OFF with button presses from the remote control, and implement a game on the LED screen that you can use button presses from the MSP430 to control.

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

Now I need to change the main method that will actually read the packet and decide what to do with it.





#Have a Great Air Force Day and Thanks for Reading!


