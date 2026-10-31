# solar-tracker
Research data and source codes for PV power optimization using a single-axis solar tracker and AM-P&amp;O based MPPT.
# Power Optimization of Photovoltaic Systems Using a Single-Axis Solar Tracker and AM-P&O Based MPPT

## Overview
This repository contains the datasets, MATLAB simulation models, and microcontroller source codes generated during the research study: **"Power Optimization of Photovoltaic Systems Using a Single-Axis Solar Tracker and AM-P&O Based MPPT."** 

To accurately reflect the research methodology, the files are separated into two main workflows: Simulation and Physical Prototyping.

## Repository Structure

### 1. MATLAB Simulation (`/MATLAB_Simulation`)
This directory contains the simulation models evaluating the AM-P&O MPPT algorithm applied to a SEPIC converter topology.
*   `.slx` files: Simulink models of the PV system and converter.
*   `.m` files: MATLAB scripts for initialization and data plotting.
*   `.mat` files: Saved workspace data from the simulation results.

### 2. Hardware Prototyping & Datasets (`/Hardware_Data`)
This directory contains the experimental datasets and Arduino codes used to evaluate the physical performance of the fixed-tilt versus single-axis solar tracker configurations over specific time parameters. *(Note: The hardware testing focuses on the tracking system performance, independent of the MPPT hardware performance).*
*   **Arduino Code**: Source code for controlling the single-axis solar tracker.
*   **Irradiance Data**: Secondary solar irradiance data retrieved from Solcast.
*   **Tracker Data**: Solar tracker angle logs recorded via the Arduino IDE serial monitor.
*   **Power Output Data**: Comparative power output datasets between the fixed-tilt and single-axis tracker setups.

## How to Use
*   **Simulation**: Navigate to the `/MATLAB_Simulation` folder. Run the initialization `.m` script before executing the `.slx` Simulink model to observe the MPPT performance.
*   **Data Analysis**: The hardware datasets can be opened using standard spreadsheet software (e.g., Excel, CSV viewers) or imported into MATLAB for further data processing.

## Author
Lanang Timur Anjo
