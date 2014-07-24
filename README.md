spark-internet-button
=====================

This program implements an "Internet-enabled button": when the button is pushed, it sends an e-mail.  When the button is released, it sends another e-mail.  It is built around the Spark Core WiFi Development kit, available from https://www.spark.io

### Prerequsites

To create an Internet-enabled button, you will need:

* A Spark Core from https://www.spark.io/dev-kits
* An SPST button or switch (I use a magnetic reed switch detect a door opening)
* An account on http://pushingbox.com/ with two scenarios: one for switch opened and one for switch closed

### Setup

* Connect one lead of your button or switch to A0 on the Spark Core.  Connect the other lead to GND.
* Edit internet-button.ino and change the values for `SWITCH_OPENED` and `SWITCH_CLOSED` to match the DevIDs assigned to you by PushingBox.
* Apply power to the Spark Core and flash it with internet-button.ino
* Push the button
* Check your e-mail

... that's all there is to it.

### Note

If your mobile carrier provides for it, you can use PushingBox to generate SMS messages rather than e-mails.  In my case, I address the e-mail to (e.g.) "61755555555@txt.att.net" and it shows up as an SMS on my phone.
