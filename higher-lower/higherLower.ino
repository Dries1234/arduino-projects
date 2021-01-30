#define MAX 10
#define DEBUG

#define TUNIT 150 // Shortest time frame
#define BLINK (TUNIT * 20)  // Time light is on for 1
#define BETWEEN (TUNIT * 2) // Time between bits
#define PAUSE (TUNIT * 50)  // Time between numbers


void setup()
{
	#ifdef DEBUG
	// Setup Serial
	Serial.begin(9600);
	while (!Serial);

	Serial.println("Higher lower");
	#endif

	// if analog input pin 0 is unconnected, random analog
	// noise will cause the call to randomSeed() to generate
	// different seed numbers each time the sketch runs.
	// randomSeed() will then shuffle the random function.
	randomSeed(analogRead(0));
	
	pinMode(LED_BUILTIN, OUTPUT);
}

void loop()
{
	// Get random number
	int number = random(MAX) + 1;

	#ifdef DEBUG
	Serial.print("Number = ");
	Serial.print(number);
	Serial.print(": ");
	Serial.println(number, BIN);
	#endif

	// Pause between numbers
	delay(PAUSE);
	showNumber(number);
}

void showNumber(int n)
{
	int i = 8;	// A max of 8 bits or 255 in decimal

	// Wait for first 1
	while (!(n >> i-- & 0x0001));	// n cannot be 0

	// First 1
	flash(BLINK);

	// Delay between bits
	delay(BETWEEN);

	while (i >= 0)
	{
		if(n >> i-- & 0x0001)
		{
			// Long flash
			flash(BLINK);
		}
		else
		{
			// Short flash to indicate a new bit started
			flash(TUNIT);
			delay(BLINK - TUNIT);
		}

		// Delay between bits
		delay(BETWEEN);
	}

	// End of number indicated by 2 short flashes
	flash(TUNIT);
	delay(TUNIT);
	flash(TUNIT);
}

void flash(int delayTime)
{
	digitalWrite(LED_BUILTIN, HIGH);
	delay(delayTime);
	digitalWrite(LED_BUILTIN, LOW);
}
