// Internet Button: Send e-mail when a button is pushed or released

/*
  ================================================================
  Copyright (C) 2014 Robert D. Poor
  
  Permission is hereby granted, free of charge, to any person obtaining
  a copy of this software and associated documentation files (the
  "Software"), to deal in the Software without restriction, including
  without limitation the rights to use, copy, modify, merge, publish,
  distribute, sublicense, and/or sell copies of the Software, and to
  permit persons to whom the Software is furnished to do so, subject to
  the following conditions:
  
  The above copyright notice and this permission notice shall be
  included in all copies or substantial portions of the Software.
  
  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
  EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
  MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
  NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
  LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
  OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
  WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
  ================================================================
*/

// ================================================================
// Description:
// 
// This program implements an "internet button" using the Spark Core: 
// when the button is pushed (or released), it sends an e-mail.
//
// Prerequsites:
//
// - a SPST button or switch (I use a magnetic reed switch detect a door 
//   opening) with one lead connected to A0 and the other lead connected 
//   to GND.
// - an account on http://pushingbox.com/ with two scenarios (one for 
//   switch opened and one for switch closed)
//
// The code here draws (in part) from:
//   https://github.com/Clement87/PushingBox-for-Spark-Core


// Secret DevIDs from PushingBox.com.
const char * serverName = "api.pushingbox.com";     // PushingBox API URL
const char * SWITCH_OPENED = "vXXXXXXXXXXXXXXX";    // Scenario: switch opened
const char * SWITCH_CLOSED = "vXXXXXXXXXXXXXXX";    // Scenario: switch closed

// Connect one side of the magnetic reed switch to A0.
// Connect the other to GND.  We'll use the internal
// pull-up so A0 goes high when the switch opens.
int reed_switch = A0;

// The on-board blue LED is programmed to follow the 
// switch state.
int blue_led = D7; 

int prev_switch_state = 0;

TCPClient client;

boolean DEBUG = true;                   // set true for serial debug printouts

void setup() {
    pinMode(blue_led, OUTPUT);
    pinMode(reed_switch, INPUT_PULLUP);
    Serial.begin(9600);                 // Start the USB Serial

    delay(1000);
    RGBBlink(255,127,0);                // flash orange at startup
    prev_switch_state = digitalRead(reed_switch);

    if (DEBUG) printNetworkParameters();
}

void loop() {
    int switch_state = digitalRead(reed_switch);
    if (prev_switch_state != switch_state) {
        // if switch has changed state, send an e-mail
        prev_switch_state = switch_state;
        digitalWrite(blue_led, switch_state);
        sendEMail((switch_state == HIGH) ? SWITCH_OPENED : SWITCH_CLOSED);
    }
    // slurp response from client
    while (client.available()) {
        char c = client.read();
        Serial.print(c);
    }
}

// Send an email via PushingBox
void sendEMail(const char * pushing_box_devid) {
    if (DEBUG) Serial.print("stopping...");
    client.stop();
    if (DEBUG) Serial.print("connecting...");
    if (client.connect(serverName, 80)) {
        client.print("GET /pushingbox?devid="); client.print(pushing_box_devid); client.println(" HTTP/1.1");
        client.print("Host: "); client.println(serverName);
        client.println("User-Agent: Spark");
        client.println();
        client.flush();
        if (DEBUG) Serial.println("sent!");
        RGBBlink(0,0,255);             // flash blue to show success

    } else {
        if (DEBUG) Serial.println("failed.");
        RGBBlink(255, 0, 0);           // flash red to show failure

    }
}

void RGBBlink(unsigned char r, unsigned char g, unsigned char b) {
    // Use the RGB led to indicate status:
    RGB.control(true);
    delay(250);
    for (int i=0; i<4; i++) {
        RGB.color(r, g, b);
        delay(250);
        RGB.color(0, 0, 0);
        delay(250);
    }
    RGB.control(false);
}

void printNetworkParameters( void ) {
    Serial.print("SSID: ");
    Serial.println(Network.SSID());
    Serial.print("Core IP: ");
    Serial.println(Network.localIP());    
    Serial.print("Gateway: ");
    Serial.println(Network.gatewayIP());
    Serial.print("Mask: ");
    Serial.println(Network.subnetMask());
    Serial.print("WiFi RSSI: ");
    Serial.println(Network.RSSI());    
}
