# Embedded Linux Hardware Platform Integration

This stage of the project focuses on preparing a **hardware platform capable of running Embedded Linux** on the ARM Cortex-A9 processor of the **Zynq-7000 SoC** on the Zybo Z7-10 development board.

Unlike the previous stage, which demonstrated a custom hardware accelerator interacting with software applications, this stage prepares the system architecture required to support **Linux-based embedded software development**. The design integrates the **Zynq Processing System**, the previously developed **custom AXI multiplier IP**, and exports the complete hardware platform for use with the Linux software stack.

This step is critical in transitioning from bare-metal software applications to **full operating system environments** in embedded FPGA systems.

---

## Development Environment

### Hardware Platform

- Zybo Z7-10 Development Board  
- Xilinx Zynq-7000 SoC  
- ARM Cortex-A9 Processing System  
- Programmable Logic (FPGA fabric)

### Tools

- Vivado Design Suite  
- AXI Interconnect  
- Custom AXI Hardware IP  
- Embedded Linux Software Stack

---

## System Architecture

The hardware platform integrates the **Zynq Processing System** with the **custom multiplier IP** created earlier. The processor communicates with the hardware peripheral through the **AXI interconnect**, enabling Linux-based applications to access hardware registers through memory-mapped interfaces.

### Block Diagram

![Zynq Linux Hardware Platform](block_diagram_lab4.png)


This architecture enables Linux software to interact with hardware peripherals implemented in programmable logic.

---

## Hardware Platform Creation

The hardware platform was created using **Vivado IP Integrator**.

The design includes:

- Zynq Processing System
- AXI Interconnect
- Custom Multiply IP
- Clock and reset infrastructure

The custom multiplier IP was added to the block diagram from a **local IP repository** and connected to the processing system using AXI.

After completing the design:

1. The block design was validated  
2. An HDL wrapper was generated  
3. The FPGA bitstream was generated  
4. The hardware platform was exported  

The exported hardware platform is used by the embedded software environment to build applications and operating system components.

---

## Hardware Platform Export

The Vivado hardware design was exported as an **XSA hardware platform file**, which contains:

- FPGA bitstream
- hardware address mapping
- processor configuration
- peripheral definitions

This file serves as the hardware description used by embedded software tools.
- linux_boot_wrapper.xsa

---

## Repository Structure

The following files are included in this stage.

### Vivado Hardware Project
- lab4_new.xpr
- lab4_new.srcs/
- lab4_new.runs/
- lab4_new.hw/

These files contain the complete hardware design project created using Vivado.

---

### Custom IP Repository
- ip_repo/

This directory contains the packaged **custom AXI multiplier IP** used in the hardware design.

---

### Hardware Platform Export
- linux_boot_wrapper.xsa

This file represents the exported hardware platform used for embedded software development.

---

### Results Directory
- _Results/

This directory stores captured outputs, screenshots, and verification artifacts produced during system validation.

---

## Key Concepts Demonstrated

This stage demonstrates several important concepts in embedded FPGA system development:

- Integration of custom AXI hardware peripherals
- Hardware platform design for embedded Linux systems
- Interaction between processing system and programmable logic
- Hardware platform export for embedded software environments
- Preparation of FPGA hardware for Linux-based software stacks

---

## Outcome

The hardware platform was successfully created and exported for use in an embedded Linux environment. The system integrates the Zynq processing system with a custom hardware peripheral, establishing the foundation for developing Linux-based applications and device drivers that interact with programmable logic hardware accelerators.