# Power Optimization of Photovoltaic Systems Using a Single-Axis Solar Tracker and AM-P&O Based MPPT

## Overview
This repository contains the MATLAB Simulink model, Arduino microcontroller source code, and the resulting datasets generated during the research study: **"Power Optimization of Photovoltaic Systems Using a Single-Axis Solar Tracker and AM-P&O Based MPPT."** 

## Repository Structure

### 1. MATLAB Simulation (`/MATLAB_Simulation`)
This directory contains the simulation model evaluating the AM-P&O MPPT algorithm applied to a SEPIC converter topology, alongside the consolidated results data.
*   `.slx` file: The Simulink model of the PV system and converter.
*   `MATLAB_Simulation_Results.xlsx`: Comprehensive datasets of the simulation results, including steady-state power oscillations, dynamic tracking responses, and daily performance comparisons between P&O and AM-P&O algorithms.

### 2. Arduino Code (`/Arduino_Code`)
*   `Single_Axis_Solar_Tracker.ino`: Microcontroller source code implementing real-time clock (RTC) data and astronomical geometry kinematics to drive the single-axis solar tracker servos.

## How to Use
*   **Simulation**: Navigate to the `/MATLAB_Simulation` folder. Open the `.slx` file directly in MATLAB/Simulink to observe the MPPT performance, or open the `.xlsx` file to review the extracted data and performance metrics.
*   **Arduino Code**: Navigate to the `/Arduino_Code` folder. Open the `Single_Axis_Solar_Tracker.ino` file using Arduino IDE, ensure the required libraries (`RTClib` and `Servo`) are installed, select your board (e.g., Arduino Nano), and upload the script to the microcontroller.

## Author
Lanang Timur Anjo
