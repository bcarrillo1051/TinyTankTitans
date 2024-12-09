# Tiny Tank Titans

Tiny Tank Titans is a project inspired by the Wii Play Tanks minigame. This repository contains the code and resources needed to implement the following key features:
- **Infrared (IR) Signal Transmission and Processing**: Handle IR signal sending and receiving for gameplay interactions.
- **Motor Control**: Enable precise movement and control of the tank.
- **Bluetooth Communication**: Facilitate communication between a phone (client) and the ESP32 (server) using an app developed with **MIT App Inventor**.

---

## Table of Contents
- [Project Overview](#project-overview)
- [Features](#features)
- [Installation](#installation)
- [Usage](#usage)
- [Folder Structure](#folder-structure)
- [Contributing](#contributing)
- [License](#license)
- [Acknowledgments](#acknowledgments)

---

## Project Overview
Tiny Tank Titans recreates the fun and challenge of the Wii Play Tanks minigame. The project leverages the capabilities of the ESP32 microcontroller to manage tank motion, IR-based interaction, and Bluetooth-based communication with a smartphone app.

This project is built with the following goals:
- **Engaging Gameplay**: Emulating the strategic and skill-based gameplay of the original Tanks minigame.
- **Versatility**: Supporting a variety of control methods, including phone-based commands via Bluetooth.
- **Scalability**: The architecture is designed to support the addition of more features, like multiplayer functionality or additional sensor integration.

---

## Features
- **Infrared Communication**: 
  - Transmission and decoding of IR signals for gameplay events.
  - Example use case: Detecting when a tank is hit by a projectile.
- **Motor Control**:
  - Precise control of tank movement.
  - Compatibility with DC motors and stepper motors.
- **Bluetooth Communication**:
  - Phone-to-ESP32 connection for remote control.
  - Real-time command processing and feedback.
  - **App Development**: A custom app developed with **MIT App Inventor** simplifies interaction between the phone and the ESP32.

---

## Installation
1. Clone the repository:
   git clone https://github.com/bcarrillo1051/TinyTankTitans.git
   cd TinyTankTitans
