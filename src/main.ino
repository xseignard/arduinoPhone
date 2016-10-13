#include <Button.h>
#include <SoftwareSerial.h>
#include <MP3.h>

MP3 mp3;

/**
 * RED/WHITE, BLUE/WHITE, and the one from the swithc to GND
 * dialing is the BLUE one
 * number is the RED one
 * the last wire is handle
 */
Button handle = Button(2, INPUT_PULLUP);
Button dialing = Button(4, INPUT_PULLUP);
Button number = Button(6, INPUT_PULLUP);

int count = 0;
boolean handled = false;
boolean dialEnded = false;

void setup() {
	Serial.begin(9600);
	mp3.begin(MP3_SOFTWARE_SERIAL);
	mp3.volume(0x1A);
	mp3.set_mode(MP3::SINGLE);
}

void loop() {
	computePhone();
}

void computePhone() {
	if (handle.isPressed()) {
		handled = true;
		dialEnded = false;

		if (dialing.isPressed()) {
			if (number.uniquePress()) count++;
		}
		else dialEnded = true;

		if (dialEnded && count != 0) {
			Serial.println(count);
			playSound(count);
			count = 0;
		}
	}
	else if (handled) {
		handled = false;
		mp3.stop();
	}
	delay(10);
}

void playSound(int id) {
	mp3.play_usb_disk(id);
}
