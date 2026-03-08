# FPGA Hardware Bring-Up

This stage of the project focuses on the initial hardware bring-up of the FPGA fabric on the **Zybo Z7-10 (Xilinx Zynq-7000)** development board using the **Xilinx Vivado design flow**.

The objective is to establish familiarity with FPGA-based digital design, the Vivado development environment, constraint-based pin mapping, and programming the FPGA fabric. Several hardware modules were implemented and verified on the board to demonstrate basic synchronous digital system design.

---

# Development Environment

**Hardware Platform**

- Zybo Z7-10 Development Board  
- Xilinx Zynq-7000 SoC  
- FPGA Device: `xc7z010clg400-1`

**Tools**

- Vivado Design Suite 2023.1
- Verilog HDL
- Xilinx Design Constraints (XDC)

---

# Project Overview

Three progressively complex FPGA designs were implemented and tested on hardware.

1. Switch-to-LED Mapping  
2. 4-bit Counter with Button Control  
3. LED Jackpot Game with Edge Detection  

These designs demonstrate fundamental FPGA design principles including combinational logic, synchronous counters, clock division, and simple state-based control.

---

# Design 1: Switch-to-LED Interface

The first design verifies the FPGA toolchain and board connectivity by directly mapping the Zybo board DIP switches to LEDs.

## Implementation

- A Verilog module was created with:
  - **4-bit input** representing DIP switches
  - **4-bit output** representing LEDs
- Each switch input is directly connected to the corresponding LED output using a continuous assignment.
- FPGA pin assignments were defined using an **XDC constraint file**.

## Functional Behavior
Switch[3:0] → LED[3:0]


Toggling a DIP switch immediately updates the corresponding LED.

This design confirms:

- Correct FPGA configuration
- Proper constraint mapping
- Functional RTL synthesis and implementation

---

# Design 2: 4-Bit Counter

A synchronous **4-bit up/down counter** was implemented using push buttons for control and LEDs for output.

## Key Features

- Counter output displayed on **4 LEDs**
- Push buttons control counter operation
- A clock divider generates human-visible timing from the **125 MHz system clock**

## Functional Controls

| Button | Function |
|------|------|
| BTN0 | Increment counter |
| BTN1 | Decrement counter |
| BTN2 | Reset counter |

## Clock Divider

Since the board clock operates at **125 MHz**, a clock divider was implemented to generate an approximately **1-second enable pulse**, allowing LED transitions to be visible.

---

# Design 3: Jackpot LED Game

The final design implements a simple interactive LED game.

A **one-hot LED rotation pattern** moves across the LEDs, and a jackpot condition occurs when the user toggles the correct switch while its corresponding LED is active.

## Core Concepts Used

- One-hot state rotation
- Edge detection on switch inputs
- State latching for jackpot condition

## Game Logic

1. A single LED rotates sequentially across the LED array.
2. The system monitors switch transitions.
3. If the correct switch is toggled while its LED is active:
   - The jackpot condition is triggered.
   - All LEDs illuminate.

## Edge Detection

To detect switch toggles reliably, previous switch values are stored and compared against current values to detect **rising edges**.

---

# FPGA Design Flow

Each design follows the standard Vivado workflow:

1. Create RTL design in **Verilog**
2. Define **pin mappings using XDC constraints**
3. Run **Synthesis**
4. Run **Implementation**
5. Generate **Bitstream**
6. Program the FPGA using **Vivado Hardware Manager**
7. Verify operation on hardware

---

# Key Concepts Demonstrated

This stage of the project demonstrates several fundamental FPGA design concepts:

- Verilog RTL development
- FPGA pin constraint mapping using XDC
- Synchronous digital design
- Clock division
- Edge detection logic
- State-based control systems
- Hardware verification on FPGA boards

---

# Source Files

The following source files are included in this stage:

**Verilog Modules**
- switch.v
- counter.v
- jackpot.v

**Constraint Files**
- switch.xdc
- counter.xdc
- jackpot.xdc


---

# Outcome

The FPGA hardware bring-up was successfully completed, confirming that the Vivado toolchain, board interfaces, and FPGA configuration process are functioning correctly. The implemented designs establish a foundation for more advanced system development involving embedded processors, custom peripherals, and Linux-based software integration in later stages of the project.