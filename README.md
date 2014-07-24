spark-internet-button
=====================

This app uses the Spark Core to send e-mail when a button is pushed or released

This program implements an "internet button" using the Spark Core: 
when the button is pushed (or released), it sends an e-mail.

### Prerequsites

To create an Internet-enabled button, you will need:

* A Spark Core from www.spark.io
* An SPST button or switch (I use a magnetic reed switch detect a door opening)
* An account on http://pushingbox.com/ with two scenarios (one for switch opened and one for switch closed)

### Setup

Connect one lead of your button or switch to A0 on the Spark Core.  Connect the other lead to GND.

Edit internet-button.ino and change the values for `SWITCH_OPENED` and `SWITCH_CLOSED` to match the DevIDs assigned to you by PushingBox.

Flash the Spark Core with internet-button.ino
