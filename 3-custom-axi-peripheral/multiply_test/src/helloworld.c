/******************************************************************************
*
* Copyright (C) 2009 - 2014 Xilinx, Inc.  All rights reserved.
*
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in
* all copies or substantial portions of the Software.
*
* Use of the Software is limited solely to applications:
* (a) running on a Xilinx device, or
* (b) that interact with a Xilinx device through a bus or interconnect.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
* XILINX  BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
* WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF
* OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
* SOFTWARE.
*
* Except as contained in this notice, the name of the Xilinx shall not be used
* in advertising or otherwise to promote the sale, use or other dealings in
* this Software without prior written authorization from Xilinx.
*
******************************************************************************/

/*
 * helloworld.c: simple test application
 *
 * This application configures UART 16550 to baud rate 9600.
 * PS7 UART (Zynq) is not initialized by this application, since
 * bootrom/bsp configures it to baud rate 115200
 *
 * ------------------------------------------------
 * | UART TYPE   BAUD RATE                        |
 * ------------------------------------------------
 *   uartns550   9600
 *   uartlite    Configurable only in HW design
 *   ps7_uart    115200 (configured by bootrom/bsp)
 */

#include <stdio.h>
#include "platform.h"
#include "xil_printf.h"
#include "xparameters.h"
#include "multiply.h"
#include "xil_io.h"



int main()
{
    init_platform();	// Initialize the platform

    int reg_0, reg_1, reg_2;

    for( reg_0 = 0; reg_0 <= 16; reg_0++)	// First number for multiplication -> reg_0
    {
    	// Write reg_0 with the outer loop values as operand 1
    	MULTIPLY_mWriteReg(XPAR_MULTIPLY_0_S00_AXI_BASEADDR, MULTIPLY_S00_AXI_SLV_REG0_OFFSET, reg_0);

    	for( reg_1 = 0; reg_1 <= 16; reg_1++)	// Second number for multiplication -> reg_1
    	{
    		printf("Operand 1 = %d; \t", reg_0 );

    		// Write reg_1 with the inner loop values as operand 2
    		MULTIPLY_mWriteReg(XPAR_MULTIPLY_0_S00_AXI_BASEADDR, MULTIPLY_S00_AXI_SLV_REG1_OFFSET, reg_1);
    		printf("Operand 2 = %d \t -> \t", reg_1 );

    		// Store the computed result of multiplication from slv_reg2 in the created "multiply" IP
    		reg_2 = MULTIPLY_mReadReg(XPAR_MULTIPLY_0_S00_AXI_BASEADDR, MULTIPLY_S00_AXI_SLV_REG2_OFFSET);
    		printf("Multiplied Result = %d \n", reg_2);
    	}
    }

    cleanup_platform();	// Default cleanup code
    return 0;
}
