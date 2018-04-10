<h1 align="center"> Ping Lock :lock: </h1>

<p align = "center"> Ping Lock is an IoT solution designed with the intent of adding intelligence to an unlocked door by notifying the user of any movement in or out of the respective room via Slack or any other free realtime instant messaging service. </p>


[![PRs Welcome](https://img.shields.io/badge/PRs-welcome-brightgreen.svg)](http://makeapullrequest.com)
[![MIT License](https://img.shields.io/github/license/dawnlabs/carbon.svg)](https://github.com/dawnlabs/carbon/blob/master/LICENSE)


## Instructions for set up
### Technologies needed -
* Arduino IDE
* Python 2.7
* Slack mobile app

### Python modules needed -
* pyserial
* slackclient

### Hardware needed -
* 1 Arduino Uno
* 1 Breadboard
* 2 Ultrasonic sensors (HC-SR04)
* Jumper wires (Male-Male and Male-Female)
* 1 Arduino-USB Cable
* Laptop with internet connectivity
* Phone compatible with slack app

#### Estimated cost of design is ~1,250₹

## Set up of Arduino
* Connect the GND of Ultrasonic Sensors to the GND of Arduino
* Connect the TRIG of one of the Ultrasonic Sensors to pin 9 and the other to pin 2. *(You may change this if you also modify the arduino sketch accordingly)*
* Connect the ECHO of the corresponding Ultrasonic Sensors to pin 10 and the other to pin 3.
* Connect the VCC to a 5V power supply.

## Set up of Arduino sketch
* The sketch is well documented and is available in this repository.

## Set up of Slack API
* Register a developer account and acquire a (free) legacy token and input this into your Python Code.

![](https://github.com/RameshAditya/ping-lock/blob/master/sample_slack_code.png)

## Set up of Python Interfacing
* Ensure you mention the correct port number in the python code to help find the Arduino Board.
* Ensure you have a Slack Developer Account with a Token Code by now and have defined it in your python code.
* In the ```slack_message(message, channel)``` method, you may have to redefine some parameters in the ```sc.api_call()``` method to tailor this to your project.

![](https://github.com/RameshAditya/ping-lock/blob/master/sample_python_code.png)

## Challenges faced during the development of this project
* ThingSpeak API was the initial API, intended to be used but for some reason the HTTP POST Request wouldn't go through and data wouldn't write to the Cloud's Channel. Hence Slack was used, since Slack's API was well documented and is a popular messaging service for groups of people (relatable here in the use case of shared rooms; for roommates)
* GSM Shield was avoided due to its expense which could potentially render the solution infeasible cost-wise.
* The nature of the Arduino sketch's ```loop()``` method prevented us from easily being able to detect the direction of motion (i.e Entry or Exit) but the addition of a buffer time to detect if the other sensor went off too, helped get around this.
* Python and Arduino can not simultaneously access the Arduino through the same port, preventing us from testing both output windows simultaneously, which costed us more time relatively.

<p align = "center">Good luck! :slightly_smiling_face:</p>
