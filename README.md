# 🐶 Happy Dog Project

## Overview

The **Happy Dog Project** was developed as part of the Machine Design and Mechatronics classes. This project utilizes an **Arduino UNO** with components such as a distance sensor, DC motors, and a push button to create an interactive dog toy for a Paper Arcade. The goal of the project was to create a simple, fun, and responsive toy where a dog reacts to a ball.

## Project Aim

The purpose of this project is to design a simple system where a dog reacts to a ball. The main idea is that the dog moves its ears when the ball gets close, and when the ball is super close, the dog's tail starts to rotate. 

This project is designed to be beginner-friendly for learning Arduino and electronics.

## Components Used

- **Arduino UNO**: The main controller for the project.
- **Distance Sensor HC-SR04**: To detect how close the ball is to the dog.
- **Two DC Motors**: One for ear movement and another for tail rotation.
- **Motor Driver L298N**: To control the DC motors.
- **Push Button**: To reset the system or trigger certain actions.
- **Power Supply**: To power the motors and Arduino.
- **Additional Components**: Resistors, wires, breadboard, LED diode.

### Main Functions:
- **Distance Sensing**: The ultrasonic sensor measures the distance to the ball.
- **Ear Movement**: When the ball is detected within a certain distance, the motors controlling the ears will start to move.
- **Tail Rotation**: If the ball gets even closer, the tail motor will start rotating.
- **Push Button Control**: Checking where is the ball is triggered by the push button.

## How to Use
- **Start Game**: Pushe the button and see if LED diode is on!
- **Play**: Place the ball near the dog to watch its ears and tail react based on the proximity of the ball!

## Future Improvements

- Add sound effects when the ball is detected.
- Improve the responsiveness of the motors to make the movement more natural.
- Enhance the project by introducing additional sensors (e.g., color sensor).
