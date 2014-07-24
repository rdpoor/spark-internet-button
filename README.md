spark-internet-button
=====================

This program implements an "Internet button": when the button is pushed (or released), it sends an e-mail.  It is built around the Spark Core WiFi Development kit, available from http://www.spark.io.

### Prerequsites

To create an Internet-enabled button, you will need:

* A Spark Core from http://www.spark.io
* An SPST button or switch (I use a magnetic reed switch detect a door opening)
* An account on http://pushingbox.com/ with two scenarios (one for switch opened and one for switch closed)

### Setup

Connect one lead of your button or switch to A0 on the Spark Core.  Connect the other lead to GND.

Edit internet-button.ino and change the values for `SWITCH_OPENED` and `SWITCH_CLOSED` to match the DevIDs assigned to you by PushingBox.

Apply power to the Spark Core and flash it with internet-button.ino
