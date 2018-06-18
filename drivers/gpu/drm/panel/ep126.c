/*
 * Copyright (C) 2018, SamsungSDS Corporation.  All rights reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sub license,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice (including the
 * next paragraph) shall be included in all copies or substantial portions
 * of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT. IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 */

#include <linux/backlight.h>
#include <linux/gpio/consumer.h>
#include <linux/module.h>
#include <linux/of_platform.h>
#include <linux/platform_device.h>
#include <linux/regulator/consumer.h>

#include <drm/drmP.h>
#include <drm/drm_crtc.h>
#include <drm/drm_mipi_dsi.h>
#include <drm/drm_panel.h>

#include <video/display_timing.h>
#include <video/videomode.h>

#include <linux/interrupt.h>
#include <linux/irq.h>
#include <linux/gpio.h>
#include <linux/of_gpio.h>

#include "ep126.h"

AUX_LINK_STATE AUX_State;

uint8_t Cache_EP146_AUX_Flags;
// set parameter
uint8_t forceRate = 0;
uint8_t forceLanes = 0;
uint8_t backupRate;
uint8_t backupLanes;
uint8_t now_port = 0;
uint8_t Swing_PreEmph[4];
static uint8_t DDC_Data[EDID_READ_STEP];
uint8_t EnhFraming, Lanes, Link_Rate;
uint8_t TPG_TIMING_DATA_1080P[16] = {
	0x80, 0x07, 0x58, 0x00, 0x94, 0x00, 0x2C, 0x00, 0x38, 0x04, 0x04, 0x00, 0x24, 0x00, 0x05, 0x00
};
uint8_t TPG_TIMING_DATA_1366P[16] = {
	HTOTAL_L, HTOTAL_H, VTOTAL_L, VTOTAL_H, HSTART_L, HSTART_H, VSTART_L, VSTART_H, HACT_L, HACT_H, VACT_L, VACT_H, HWIDTH_L, HWIDTH_H, VWIDTH_L, VWIDTH_H
};

// Debug
static int debug = 1;
#define dprintk(msg...)	if(debug)	{printk("lcd_ep126> " msg);}

#define EP126_SLAVE_ADDR 0x38
static int i2c_write(struct i2c_adapter *adap, uint8_t wreg, uint8_t wdata)
{
	//dev_err(dbg_dev, "i2c_write(%02x, %02x)\n", wreg, wdata);	// KJW
	static uint8_t data[2];
	struct i2c_msg write_msg;
	
	data[0] = wreg;
	data[1] = wdata;
	write_msg.addr = EP126_SLAVE_ADDR;
	write_msg.flags = 0;
	write_msg.len = 2;
	write_msg.buf = data;
	
	i2c_transfer(adap, &write_msg, 1);
}

static int i2c_write_len(struct i2c_adapter *adap, uint8_t wreg, uint8_t *wdata, int len)
{
	//dev_err(dbg_dev, "i2c_write_len(%02x, %02x, %d)\n", wreg, *wdata, len);	// KJW
	static uint8_t data[5];
	struct i2c_msg write_msg;
	int i = 0;
	
	data[0] = wreg;
	for(i=0; i<len; i++)
		data[1+i] = *(wdata+i);
	write_msg.addr = EP126_SLAVE_ADDR;
	write_msg.flags = 0;
	write_msg.len = i+1;
	write_msg.buf = data;
	
	i2c_transfer(adap, &write_msg, 1);
}

static uint8_t i2c_read(struct i2c_adapter *adap, uint8_t rreg)
{
	//dev_err(dbg_dev, "i2c_read(%02x)\n", rreg);	// KJW
	static uint8_t reg_addr[1];
	static uint8_t data[1];
	struct i2c_msg read_msg[2];
	int ret = 0;
	
	reg_addr[0] = rreg;
	read_msg[0].addr = EP126_SLAVE_ADDR;
	read_msg[0].flags = 0;
	read_msg[0].len = 1;
	read_msg[0].buf = reg_addr;
	
	data[0] = 0x00;
	read_msg[1].addr = EP126_SLAVE_ADDR;
	read_msg[1].flags = I2C_M_RD;
	read_msg[1].len = 1;
	read_msg[1].buf = data;
	
	ret = i2c_transfer(adap, read_msg, 2);
	//dev_err(dbg_dev, "i2c_read : len = %d, val = %02x\n", ret, data[0]);	// KJW
	return data[0];
}

static int i2c_read_len(struct i2c_adapter *adap, uint8_t rreg, uint8_t* rdata, int len)
{
	//dev_err(dbg_dev, "i2c_read(%02x)\n", rreg);	// KJW
	static uint8_t reg_addr[1];
	static uint8_t data[5];
	struct i2c_msg read_msg[2];
	int ret = 0;
	
	reg_addr[0] = rreg;
	read_msg[0].addr = EP126_SLAVE_ADDR;
	read_msg[0].flags = 0;
	read_msg[0].len = 1;
	read_msg[0].buf = reg_addr;
	
	//data[0] = 0x00;
	read_msg[1].addr = EP126_SLAVE_ADDR;
	read_msg[1].flags = I2C_M_RD;
	read_msg[1].len = len;
	read_msg[1].buf = data;
	
	ret = i2c_transfer(adap, read_msg, 2);
	//dev_err(dbg_dev, "i2c_read : len = %d, val = %02x\n", ret, data[0]);	// KJW
	memcpy(rdata, data, len);
	return true;
}

int init_ep126(struct i2c_adapter *adap)
{
	dprintk("init_ep126()\n");	// KJW
	
	uint8_t tmp;
	int data[16], i;
	
	AUX_State = AUX_LINK_STATE__Idel;
	Cache_EP146_AUX_Flags = 0x00;
	// initial after reset
	i2c_write(adap, EP146_AUX_Control, EP146_AUX_Control__HPD_IE);
	i2c_write(adap, EP146_TU_SIZE, 0x30);
	i2c_write(adap, EP146_General_Control_3, 0x00);
	// 1080p output
	//i2c_write_len(adap, 0x26, &TPG_TIMING_DATA_1080P, 16);
	// 1366*768p output
	i2c_write_len(adap, 0x26, &TPG_TIMING_DATA_1366P, 16);

	// DP TX power down
	tmp = i2c_read(adap, EP146_General_Control_0);
	tmp &= ~EP146_General_Control_0__TX_PU;
	i2c_write(adap, EP146_General_Control_0, tmp);
	
	// LVDS DIG in
	tmp = i2c_read(adap, EP146_General_Control_0);
	tmp |= EP146_General_Control_0__DIG_IN;
	i2c_write(adap, EP146_General_Control_0, tmp);
	
	LVDS_Port_setting(adap, 0x01);	// YH : 0x02 -> 0x01
	
	backupRate = forceRate = 0x0A;	// 2.7G
	//forceRate = 0x06;	// 1.62G
	backupLanes = forceLanes = 1;		// YH : 2 -> 1
	
	// DCLK POL
	tmp = i2c_read(adap, EP146_General_Control_0);
	tmp |= EP146_General_Control_0__DCLK_POL;
	i2c_write(adap, EP146_General_Control_0, tmp);
	
	// LVDS DIG
	tmp = i2c_read(adap, EP146_General_Control_0);
	tmp &= ~EP146_General_Control_0__DIG_IN;
	i2c_write(adap, EP146_General_Control_0, tmp);
	
	// LVDS PLL band width
	tmp = i2c_read(adap, EP146_General_Control_1);
	tmp &= ~EP146_General_Control_1__LVDS_BW;
	i2c_write(adap, EP146_General_Control_1, tmp);
	
	// LVDS RX power up
	tmp = i2c_read(adap, EP146_General_Control_0);
	tmp |= EP146_General_Control_0__PU;
	i2c_write(adap, EP146_General_Control_0, tmp);
	/*
	// LVDS single port
	tmp = i2c_read(adap, 0x01);
	tmp &= ~0x03;
	i2c_write(adap, 0x01, tmp);
	i2c_write(adap, 0x23, 0x00);
	i2c_write(adap, 0x24, 0x80);
	i2c_write(adap, 0x25, 0x00);
	*/
	/*
	// eDP TX output
	i2c_write(adap, 0x05, 0x85);
	
	// DP TX power up
	tmp = i2c_read(adap, 0x00);
	tmp |= 0x02;
	i2c_write(adap, 0x00, tmp);
	*/
		
	return 0;
}

void DP_Tx_Power_Down(struct i2c_adapter *adap)
{
	dprintk("HPD go low\n");
	AUX_State = AUX_LINK_STATE__Idel;

	uint8_t Temp_Data;
	Temp_Data = i2c_read(adap, EP146_General_Control_0);
	Temp_Data &= ~ EP146_General_Control_0__TX_PU;
	i2c_write(adap, EP146_General_Control_0, Temp_Data);
}

void AUX_DP_Streaming(struct i2c_adapter *adap)
{
	dprintk("DP Streaming\n");
	
	uint8_t Temp_Byte[1];
	Temp_Byte[0] = 0x00; // Streaming with SCRAMBLING Enable
	DP_AUX_Write(adap, 0x102, 1, &Temp_Byte[0]);
	DP_Tx_Mode(adap, DP_TX_MODE__STREAM_EN);
}

bool DP_AUX_Write(struct i2c_adapter *adap, uint16_t Address, int Len, uint8_t *pData)
{
	int i, j;
	uint8_t Temp_Data[12];
	
	// Constrain the Len size
	if(Len > 8) printk("Err: AUX RQ Len %bu > 8\n", Len);
	
	for(j=0; j<AUX_CMD_RETRY_TIME; ++j) {
	
		// Command
		Temp_Data[1] = 0x80; // RQ_CMD[3:0] : RQ_ADDD[19:16]
			
		// Address
		Temp_Data[1] |= Address >> 16;
		Temp_Data[2] = Address >> 8;
		Temp_Data[3] = Address;
	
		// Len Check
		if(Len) {
			// Len
			Temp_Data[4] = Len - 1;
			
			// Data
			memcpy(&Temp_Data[5], pData, Len);
			
			// Copy Data
			//EP146_Reg_Write(EP146_AUX_RQ_Command, &Temp_Data[1], Len+4);
			i2c_write_len(adap, EP146_AUX_RQ_Command, &Temp_Data[1], Len+4);
			
			// RQ Start
			Temp_Data[0] = EP146_AUX_Control__RQ_START; // Normal mode
			//EP146_Reg_Write(EP146_AUX_Control, &Temp_Data[0], 1);
			i2c_write_len(adap, EP146_AUX_Control, &Temp_Data[0], 1);
		}
		else {
			// Copy Data
			//EP146_Reg_Write(EP146_AUX_RQ_Command, &Temp_Data[1], 3);
			i2c_write_len(adap, EP146_AUX_RQ_Command, &Temp_Data[1], 3);
			
			// RQ Start
			Temp_Data[0] = EP146_AUX_Control__RQ_START | EP146_AUX_Control__RQ_MODE; // Short mode. LEN and DATA bytes are not sent.
			//EP146_Reg_Write(EP146_AUX_Control, &Temp_Data[0], 1);	
			i2c_write_len(adap, EP146_AUX_Control, &Temp_Data[0], 1);
		}
		
		// Wait...
		for(i=0; i<AUX_TIMEOUT; i++) {
			//EP146_Reg_Read(EP146_AUX_Control, &Temp_Data[0], 1);
			Temp_Data[0] = i2c_read(adap, EP146_AUX_Control);
			Cache_EP146_AUX_Flags |= Temp_Data[0] & 0xE0;
		
			if(Temp_Data[0] & EP146_AUX_Control__RP_F) {
				break;
			}
		}
		if(Temp_Data[0] & EP146_AUX_Control__RP_F) {
		
			// Check Reply
			//EP146_Reg_Read(EP146_AUX_RP_Data, &Temp_Data[1], 1);
			Temp_Data[1] = i2c_read(adap, EP146_AUX_RP_Data);
			if(Temp_Data[1] == 0) { // ACK
				return true;
			}
			else if(Temp_Data[1] == 0x10) { // NACK
				//DBG_printf(("Warn: AUX RQ NACK\n"));
				dprintk("Warn: AUX RQ NACK\n");
			}
			else if(Temp_Data[1] == 0x20) { // DEFER
				//DBG_printf(("Warn: AUX RQ DEFER\n"));
				dprintk("Warn: AUX RQ DEFER\n");
			}	
		}
		else {
			//DBG_printf(("Err: DP_AUX RQ Timeout\n"));
			//dev_err(dbg_dev, "Err: DP_AUX RQ Timeout\n");
		}		
	}
	//DBG_printf(("Err: AUX Write Fail\n"));
	printk("Err: AUX Write Fail\n");
	return false;
}

bool DP_AUX_Read(struct i2c_adapter *adap, uint16_t Address, uint8_t Len, uint8_t *pData)
{
	int i, j;
	uint8_t Temp_Data[6];
	
	// Constrain the Len size
	if(Len > 8) //DBG_printf(("Err: AUX RQ Len %bu > 8\n", Len));
		printk("Err: AUX RQ Len %bu > 8\n", Len);
	
	for(j=0; j<AUX_CMD_RETRY_TIME; ++j) {
	
		// Command
		Temp_Data[1] = 0x90; // RQ_CMD[3:0] : RQ_ADDD[19:16]
		
		// Address
		Temp_Data[1] |= Address >> 16;
		Temp_Data[2] = Address >> 8;
		Temp_Data[3] = Address;
	
		// Len Check
		if(Len) {
			// Len
			Temp_Data[4] = Len - 1;
			
			// Copy Data
			//EP146_Reg_Write(EP146_AUX_RQ_Command, &Temp_Data[1], 4);
			i2c_write_len(adap, EP146_AUX_RQ_Command, &Temp_Data[1], 4);
			
			// RQ Start
			Temp_Data[0] = EP146_AUX_Control__RQ_START; // Normal mode
			//EP146_Reg_Write(EP146_AUX_Control, &Temp_Data[0], 1);
			i2c_write_len(adap, EP146_AUX_Control, &Temp_Data[0], 1);
		}
		else {
			// Copy Data
			//EP146_Reg_Write(EP146_AUX_RQ_Command, &Temp_Data[1], 3);
			i2c_write_len(adap, EP146_AUX_RQ_Command, &Temp_Data[1], 3);
			
			// RQ Start
			Temp_Data[0] = EP146_AUX_Control__RQ_START | EP146_AUX_Control__RQ_MODE; // Short mode. LEN and DATA bytes are not sent.
			//EP146_Reg_Write(EP146_AUX_Control, &Temp_Data[0], 1);	
			i2c_write_len(adap, EP146_AUX_Control, &Temp_Data[0], 1);
		}
		
		// Wait...
		for(i=0; i<AUX_TIMEOUT; i++) {
			//EP146_Reg_Read(EP146_AUX_Control, &Temp_Data[0], 1);
			Temp_Data[0] = i2c_read(adap, EP146_AUX_Control);
			Cache_EP146_AUX_Flags |= Temp_Data[0] & 0xE0;
		
			if(Temp_Data[0] & EP146_AUX_Control__RP_F) {
				break;
			}
		}
		if(Temp_Data[0] & EP146_AUX_Control__RP_F) {
			// Check Reply
			//EP146_Reg_Read(EP146_AUX_RP_Len, &Temp_Data[0], 1);
			//EP146_Reg_Read(EP146_AUX_RP_Data, &Temp_Data[1], Temp_Data[0]);
			Temp_Data[0] = i2c_read(adap, EP146_AUX_RP_Len);
			i2c_read_len(adap, EP146_AUX_RP_Data, &Temp_Data[1], Temp_Data[0]);
			if(Temp_Data[1] == 0) { // ACK
				if((Len+1) != Temp_Data[0]) {
					//DBG_printf(("Err: AUX RQ LEN\n"));
					printk("Err: AUX RQ LEN\n");
					return false;
				}
				memcpy(pData, &Temp_Data[2], Len);
				return true;
			}
			else if(Temp_Data[1] == 0x10) { // NACK
				//DBG_printf(("Warn: AUX RQ NACK\n"));
				dprintk("Warn: AUX RQ NACK\n");
			}
			else if(Temp_Data[1] == 0x20) { // DEFER
				//DBG_printf(("Warn: AUX RQ DEFER\n"));
				dprintk("Warn: AUX RQ DEFER\n");
			}
		}
		else {
			//DBG_printf(("Err: DP_AUX RQ Timeout\n"));
			//dev_err(dbg_dev, "Err: DP_AUX RQ Timeout\n");
		}
	}
	//DBG_printf(("Err: AUX Read Fail\n"));
	printk("Err: AUX Read Fail\n");
	return false;
}

void DP_Tx_Mode(struct i2c_adapter *adap, DP_TX_MODE Mode)
{	
	uint8_t Temp_Data[1];
	//EP146_Reg_Read(EP146_General_Control_5, &Temp_Data[0], 1);
	Temp_Data[0] = i2c_read(adap, EP146_General_Control_5);
	Temp_Data[0] &= ~(EP146_General_Control_5__STREAM_EN | EP146_General_Control_5__ALIGN_EN | EP146_General_Control_5__CR_EN | EP146_General_Control_5__SCRAM_DIS);
	
	// clean for reset train pattern
	if(Mode != DP_TX_MODE__CR_EN)
		//EP146_Reg_Write(EP146_General_Control_5, &Temp_Data[0], 1);
		i2c_write(adap, EP146_General_Control_5, Temp_Data[0]);
	
	switch(Mode) {
		case DP_TX_MODE__CR_EN:
			Temp_Data[0] |= EP146_General_Control_5__CR_EN | EP146_General_Control_5__SCRAM_DIS;
			break;
		case DP_TX_MODE__ALIGN_EN:
			Temp_Data[0] |= EP146_General_Control_5__ALIGN_EN | EP146_General_Control_5__SCRAM_DIS;
			break;
		case DP_TX_MODE__STREAM_EN:
			Temp_Data[0] |= EP146_General_Control_5__STREAM_EN;
			break;
		case DP_TX_MODE__STREAM_EN_NO_SCRAM:
			Temp_Data[0] |= EP146_General_Control_5__STREAM_EN | EP146_General_Control_5__SCRAM_DIS;
			break;
	}
	
	//EP146_Reg_Write(EP146_General_Control_5, &Temp_Data[0], 1);
	i2c_write_len(adap, EP146_General_Control_5, &Temp_Data[0], 1);
}

uint8_t DP_AUX_Get_Flags(struct i2c_adapter *adap)
{
	uint8_t Temp_Data;
	//EP146_Reg_Read(EP146_AUX_Control, &Temp_Data[0], 1);
	Temp_Data = i2c_read(adap, EP146_AUX_Control);
	Temp_Data |= Cache_EP146_AUX_Flags;
	Cache_EP146_AUX_Flags = 0;
	return Temp_Data;
}

// This functions should be called when interrupt is detected.
bool HTPLG_Low = 0;
uint16_t HTPLG_LowTime = 0;
void EP146Control_IRQ_Event(struct i2c_adapter *adap) 
{
	dprintk("EP146Control_IRQ_Event!\n");
	uint8_t IntFlag_Byte, Temp_Data;

	// MHL Interrupt
	IntFlag_Byte = DP_AUX_Get_Flags(adap);
	if(IntFlag_Byte & EP146_AUX_Control__HPD_F) {

		//DBG_printf(("HPD flag\n"));
		dprintk("HPD flag\n");
				
		//if(DP_Tx_HPD()) {
		Temp_Data = i2c_read(adap, 	EP146_AUX_Control);
		Cache_EP146_AUX_Flags |= Temp_Data & 0xE0;
		if(Temp_Data & EP146_AUX_Control__HPD_STATE) {
			if(AUX_State == AUX_LINK_STATE__Idel) {
				//DBG_printf(("HPD go high\n"));
				dprintk("HPD go high\n");
				EP146Control_Link_Task(adap);
			}
			HTPLG_Low = 0;
			HTPLG_LowTime = 0;
		}
		else {
			HTPLG_Low = 1;
			
			//DBG_printf(("HPD go low\n"));
			if(AUX_State != AUX_LINK_STATE__Idel){
				dprintk("HPD go low\n");
				AUX_State = AUX_LINK_STATE__Idel;
			
				//LVDS_Rx_Power_Down();
				//DP_Tx_Power_Down();
				Temp_Data = i2c_read(adap, EP146_General_Control_0);
				Temp_Data &= ~ EP146_General_Control_0__TX_PU;
				i2c_write(adap, EP146_General_Control_0, Temp_Data);
			}
			
		}			
	}
	/*
	if(HTPLG_Low)
	{
		if(HTPLG_LowTime++ > 240 / 10)
		{
			HTPLG_LowTime = 0;
			
			if(AUX_State != AUX_LINK_STATE__Idel)
			{
				DBG_printf(("HPD go low\n"));
				AUX_State = AUX_LINK_STATE__Idel;
				
				//EP196_Power_Down();
				DP_Tx_Power_Down();
			}
		}
	}
	*/

	if((backupLanes != forceLanes)||(backupRate != forceRate))
	{
		dprintk("backupLanes=%d, forceLanes=%d, backupRate=%d, forceRate=%d!\n",backupLanes,forceLanes,backupRate,forceRate);
		backupLanes = forceLanes;
		backupRate = forceRate;
		EP146Control_Link_Task(adap);
	}
	// interrupt enable
	//i2c_write(adap, 0x40, 0x80);
}

void AUX_Read_Information(struct i2c_adapter *adap, uint8_t tRate, uint8_t tLanes)
{
	uint8_t tmp;
	uint8_t Temp_Byte[256];
	
	//DBG_printf(("DP Read Information\n"));
	dprintk("DP Read Information\n");
	
	//Downstream_Rx_read_EDID(adap, Temp_Byte);	// YH : ??�떒 留됱??

	/////////////////////////////////////////////////////////
	//
	// Source May Check EDID here
	//
	/////////////////////////////////////////////////////////
	
		
	if(!DP_AUX_Read(adap, 0x0, 3, Temp_Byte)) return;
	
	// Byte 0
	//DBG_printf(("DPCD = 0x%02bX\n", Temp_Byte[0]));
	dprintk("DPCD = 0x%02x\n", Temp_Byte[0]);
	
	// Byte 1
	switch(tRate)	{
		case 0x06:
			Temp_Byte[1] = 0x06;
			//DBG_printf(("Fixed 1.62Gbps per lane\n"));
			dprintk("Fixed 1.62Gbps per lane\n");
			break;
		case 0x0A:
			Temp_Byte[1] = 0x0A;
			//DBG_printf(("Fixed 2.7Gbps per lane\n"));
			dprintk("Fixed 2.7Gbps per lane\n");
			break;
	}

// Force to use 1.62Gbps
//Temp_Byte[1] = 0x06;
	if(Temp_Byte[1] == 0x0A) {
		//DBG_printf(("2.7Gbps per lane\n"));
		dprintk("2.7Gbps per lane\n");
		//DP_Tx_Link_Rate(1);
		tmp = i2c_read(adap, EP146_General_Control_5);
		tmp |= EP146_General_Control_5__DP_BW;
		i2c_write(adap, EP146_General_Control_5, tmp);
	}
	else {
		//DBG_printf(("1.62Gbps per lane\n"));
		dprintk("1.62Gbps per lane\n");
		//DP_Tx_Link_Rate(0);
		tmp = i2c_read(adap, EP146_General_Control_5);
		tmp &= ~EP146_General_Control_5__DP_BW;
		i2c_write(adap, EP146_General_Control_5, tmp);
	}
	Link_Rate = Temp_Byte[1];
	DP_AUX_Write(adap, 0x100, 1, &Link_Rate); // Write Back to Sink
	
	// Byte 2
// Force to use 1 lane
	switch(tLanes){
		
		case 1:
			//DBG_printf(("Fixed to 1 lane\n"));
			dprintk("Fixed to 1 lane\n");
			Temp_Byte[2]  &= ~0x0F; 			  
    		Temp_Byte[2]  |= 1;
			break;
		case 2:
			//DBG_printf(("Fixed to 2 lane\n"));
			dprintk("Fixed to 2 lane\n");
			Temp_Byte[2]  &= ~0x0F; 			  
    		Temp_Byte[2]  |= 2;
			break;
		case 4:
			//DBG_printf(("Fixed to 4 lane\n"));
			dprintk("Fixed to 4 lane\n");
			Temp_Byte[2]  &= ~0x0F; 			  
    		Temp_Byte[2]  |= 4;
			break;
		default:
			break;
	}

	switch(Temp_Byte[2] & 0x0F) {
		default:
		case 1: // One lane
			//DBG_printf(("Total 1 lane\n"));
			dprintk("Total 1 lane\n");
			Lanes = 1;
			DP_Tx_Lanes(adap, 0);
			break;
		case 2: // Two lane
			//DBG_printf(("Total 2 lane\n"));
			dprintk("Total 2 lane\n");
			Lanes = 2;
			DP_Tx_Lanes(adap, 1);
			break;
		case 4: // Four lane
			//DBG_printf(("Total 4 lane\n"));
			dprintk("Total 4 lane\n");
			Lanes = 4;
			DP_Tx_Lanes(adap, 2);
			break;
	}
	if(Temp_Byte[2] & 0x80) {
		// Enhanced Framing
		//DBG_printf(("Enhanced Framing\n"));
		dprintk("Enhanced Framing\n");
		EnhFraming = 1;
		//DP_Tx_Enhance_Framing(1);
		tmp = i2c_read(adap, EP146_General_Control_5);
		tmp |= EP146_General_Control_5__ENH_FRAME;
		i2c_write(adap, EP146_General_Control_5, tmp);
	}
	else {
		EnhFraming = 0;
		//DP_Tx_Enhance_Framing(0);
		tmp = i2c_read(adap, EP146_General_Control_5);
		tmp &= ~EP146_General_Control_5__ENH_FRAME;
		i2c_write(adap, EP146_General_Control_5, tmp);
	}
	DP_AUX_Write(adap, 0x101, 1, &Temp_Byte[2]); // Write Back to Sink
}

void DP_Tx_Lanes(struct i2c_adapter *adap, uint8_t Lanes)
{
	uint8_t Temp_Data[1];
	//EP146_Reg_Read(EP146_General_Control_2, &Temp_Data[0], 1);
	Temp_Data[0] = i2c_read(adap, EP146_General_Control_2);
	Temp_Data[0] &= ~EP146_General_Control_2__nLANE;
	Temp_Data[0] |= Lanes;
	//EP146_Reg_Write(EP146_General_Control_2, &Temp_Data[0], 1);
	i2c_write_len(adap, EP146_General_Control_2, &Temp_Data[0], 1);
}

void DP_Tx_Power_Up(struct i2c_adapter *adap)
{
	uint8_t tmp;
	// Software power up
	//EP146_Reg_Set_Bit(EP146_General_Control_0, EP146_General_Control_0__TX_PU);	
	tmp = i2c_read(adap, EP146_General_Control_0);
	tmp |= EP146_General_Control_0__TX_PU;
	i2c_write(adap, EP146_General_Control_0, tmp);
	//DBG_printf(("Set TX Power Up\n"));	
	dprintk("Set TX Power Up\n");

	LVDS_Port_setting(adap, now_port);
}

void LVDS_Port_setting(struct i2c_adapter *adap, uint8_t port)
{
	uint8_t Temp_Data[5];
	#define NOW_LVDS_BW	0x40
	
	now_port = port;
	if(port == 0)
	{
		//DBG_printf(("Do nothing\n"));
		dprintk("Do nothing\n");	
	}
	else if(port == 1)
	{
		//Temp_Data[0] = NOW_LVDS_BW | EP146_General_Control_1__DE_ONLY | EP146_General_Control_1__LVDS_MAP;
		// YH : VESA
		Temp_Data[0] = NOW_LVDS_BW | EP146_General_Control_1__LVDS_MAP;
		//EP146_Reg_Write(EP146_General_Control_1, Temp_Data, 1);
		i2c_write(adap, EP146_General_Control_1, Temp_Data[0]);
		Temp_Data[0] = 0x00;
		Temp_Data[1] = 0x80;
		Temp_Data[2] = 0x00;
		//EP146_Reg_Write(EP146_MSA_R_N_vid,Temp_Data, 3 );
		i2c_write_len(adap, EP146_MSA_R_N_vid, Temp_Data, 3 );
		//DBG_printf(("LVDS input set to 1 port\n"));
		//dev_err(dbg_dev, "LVDS input set to 1 port\n");
	}
	else if(port == 2)
	{
		//Temp_Data[0] = NOW_LVDS_BW | 0x01 | EP146_General_Control_1__DE_ONLY | EP146_General_Control_1__LVDS_MAP;
		Temp_Data[0] = NOW_LVDS_BW | 0x01;
		//EP146_Reg_Write(EP146_General_Control_1, Temp_Data, 1);
		i2c_write(adap, EP146_General_Control_1, Temp_Data[0]);
		Temp_Data[0] = 0x00;
		Temp_Data[1] = 0x40;
		Temp_Data[2] = 0x00;
		//EP146_Reg_Write(EP146_MSA_R_N_vid,Temp_Data, 3 );
		i2c_write_len(adap, EP146_MSA_R_N_vid, Temp_Data, 3 );
		//DBG_printf(("LVDS input set to 2 ports\n"));
		dprintk("LVDS input set to 2 ports\n");
	}
	else if(port == 3)
	{
		//Temp_Data[0] = NOW_LVDS_BW | 0x02 | EP146_General_Control_1__DE_ONLY | EP146_General_Control_1__LVDS_MAP;
		Temp_Data[0] = NOW_LVDS_BW | 0x02;
		//EP146_Reg_Write(EP146_General_Control_1, Temp_Data, 1);
		i2c_write(adap, EP146_General_Control_1, Temp_Data[0]);
		Temp_Data[0] = 0x00;
		Temp_Data[1] = 0x20;
		Temp_Data[2] = 0x00;
		//EP146_Reg_Write(EP146_MSA_R_N_vid,Temp_Data, 3 );
		i2c_write_len(adap, EP146_MSA_R_N_vid, Temp_Data, 3 );
		//DBG_printf(("LVDS input set to 4 ports\n"));
		dprintk("LVDS input set to 4 ports\n");
	}	
}

// Swing   = 0 ~ 3
// PreEmph = 0 ~ 3
void DP_Tx_Swing_PreEmph_Set(struct i2c_adapter *adap, uint8_t Swing, uint8_t PreEmph)
{
	int Temp_Data[1];
	//DBG_printf(("Swing and PreEm 0x%02bX, 0x%02bX\n", Swing, PreEmph));
	dprintk("Swing and PreEm 0x%02x, 0x%02x\n", Swing, PreEmph);

	switch(Swing){
		case 0:
			//EP146_Reg_Read( EP146_General_Control_4, &Temp_Data[0], 1);
			Temp_Data[0] = i2c_read(adap, EP146_General_Control_4);
			Temp_Data[0] &= ~EP146_General_Control_4__SWING;
			Temp_Data[0] |= 0x00;
 			//EP146_Reg_Write( EP146_General_Control_4 , &Temp_Data[0] , 1);
			i2c_write_len(adap, EP146_General_Control_4 , &Temp_Data[0] , 1);
			break;
		case 1:
			//EP146_Reg_Read( EP146_General_Control_4, &Temp_Data[0], 1);
			Temp_Data[0] = i2c_read(adap, EP146_General_Control_4);
			Temp_Data[0] &= ~EP146_General_Control_4__SWING;
			Temp_Data[0] |= 0x04;
 			//EP146_Reg_Write( EP146_General_Control_4 , &Temp_Data[0] , 1);
			i2c_write_len(adap, EP146_General_Control_4 , &Temp_Data[0] , 1);
			break;
		case 2:
			//EP146_Reg_Read( EP146_General_Control_4, &Temp_Data[0], 1);
			Temp_Data[0] = i2c_read(adap, EP146_General_Control_4);
			Temp_Data[0] &= ~EP146_General_Control_4__SWING;
			Temp_Data[0] |= 0x08;
			//EP146_Reg_Write( EP146_General_Control_4 , &Temp_Data[0] , 1);
			i2c_write_len(adap, EP146_General_Control_4 , &Temp_Data[0] , 1);
			break;
		case 3:
			//EP146_Reg_Read( EP146_General_Control_4, &Temp_Data[0], 1);
			Temp_Data[0] = i2c_read(adap, EP146_General_Control_4);
			Temp_Data[0] &= ~EP146_General_Control_4__SWING;
			Temp_Data[0] |= 0x0c;
			//EP146_Reg_Write( EP146_General_Control_4 , &Temp_Data[0] , 1);
			i2c_write_len(adap, EP146_General_Control_4 , &Temp_Data[0] , 1);
			break;
    }
	switch(PreEmph){
		case 0:
			//EP146_Reg_Read( EP146_General_Control_4, &Temp_Data[0], 1);
			Temp_Data[0] = i2c_read(adap, EP146_General_Control_4);
			Temp_Data[0] &= ~EP146_General_Control_4__PRE;
			Temp_Data[0] |= 0x00;
 			//EP146_Reg_Write( EP146_General_Control_4 , &Temp_Data[0] , 1);
			i2c_write_len(adap, EP146_General_Control_4 , &Temp_Data[0] , 1);
			break;
		case 1:
			//EP146_Reg_Read( EP146_General_Control_4, &Temp_Data[0], 1);
			Temp_Data[0] = i2c_read(adap, EP146_General_Control_4);
			Temp_Data[0] &= ~EP146_General_Control_4__PRE;
			Temp_Data[0] |= 0x01;
 			//EP146_Reg_Write( EP146_General_Control_4 , &Temp_Data[0] , 1);
			i2c_write_len(adap, EP146_General_Control_4 , &Temp_Data[0] , 1);
			break;
		case 2:
			//EP146_Reg_Read( EP146_General_Control_4, &Temp_Data[0], 1);
			Temp_Data[0] = i2c_read(adap, EP146_General_Control_4);
			Temp_Data[0] &= ~EP146_General_Control_4__PRE;
			Temp_Data[0] |= 0x02;
 			//EP146_Reg_Write( EP146_General_Control_4 , &Temp_Data[0] , 1);
			i2c_write_len(adap, EP146_General_Control_4 , &Temp_Data[0] , 1);
			break;
		case 3:
			//EP146_Reg_Read( EP146_General_Control_4, &Temp_Data[0], 1);
			Temp_Data[0] = i2c_read(adap, EP146_General_Control_4);
			Temp_Data[0] &= ~EP146_General_Control_4__PRE;
			Temp_Data[0] |= 0x03;
 			//EP146_Reg_Write( EP146_General_Control_4 , &Temp_Data[0] , 1);
			i2c_write_len(adap, EP146_General_Control_4 , &Temp_Data[0] , 1);
			break;
	}
	
}

bool AUX_Clock_Recovery_Start(struct i2c_adapter *adap)
{
	int i, Status;
	uint8_t Temp_Byte[6];
	//DBG_printf(("DP Clock Recovery Start\n"));
	dprintk("DP Clock Recovery Start\n");
	
	// Initialize the PHY settings
	memset(Swing_PreEmph,0, sizeof(Swing_PreEmph));
	DP_Tx_Swing_PreEmph_Set(adap, Swing_PreEmph[0] & 0x03, (Swing_PreEmph[0] >> 3) & 0x03);
	
	// Enable TP1
	DP_Tx_Mode(adap, DP_TX_MODE__CR_EN);
	
	Temp_Byte[0] = 0x21; // SCRAMBLING_DISABLE & Training Pattern 1
	Temp_Byte[1] = Swing_PreEmph[0]; 
	Temp_Byte[2] = Swing_PreEmph[1]; 
	Temp_Byte[3] = Swing_PreEmph[2]; 
	Temp_Byte[4] = Swing_PreEmph[3];
	if(!DP_AUX_Write(adap, 0x102, 5, &Temp_Byte[0])) return false;

	// Retry 5 times
	for(i=0; i<5; ++i) {
		// delay 100us
		//delay_1ms(1);
		msleep(1);
		
		DP_AUX_Read(adap, 0x202, 2, Temp_Byte);
		
		Status = true;
		if(Temp_Byte[0] & 0x01) {
			//DBG_printf(("DP Lane0 CR Done\n"));
			dprintk("DP Lane0 CR Done\n");
		}
		else {
			//DBG_printf(("DP Lane0 CR Fail %d\n", i));
			dprintk("DP Lane0 CR Fail %d\n", i);
			Status = false;
		}
		if(2 <= Lanes) {
			if(Temp_Byte[0] & 0x10) {
				//DBG_printf(("DP Lane1 CR Done\n"));
				dprintk("DP Lane1 CR Done\n");
			}
			else {
				//DBG_printf(("DP Lane1 CR Fail %d\n", i));
				dprintk("DP Lane1 CR Fail %d\n", i);
				Status = false;
			}	
		}
		if(4 <= Lanes) {
			if(Temp_Byte[1] & 0x11) {
				//DBG_printf(("DP Lane2/3 CR Done\n"));
				dprintk("DP Lane2/3 CR Done\n");
			}
			else {
				//DBG_printf(("DP Lane2/3 CR Fail %d\n", i));
				dprintk("DP Lane2/3 CR Fail %d\n", i);
				Status = false;
			}	
		}
		if(Status == true) {
			return true;
		}
		else {
			if(!AUX_DP_Adjust_Swing_PreEmph(adap)) {
				return false;
			}
		}
	}
	
	return false;
}

bool AUX_Channel_EQ_Start(struct i2c_adapter *adap)
{
	int i, Status;
	uint8_t Temp_Byte[6];
	//DBG_printf(("DP Channel EQ Start\n"));
	dprintk("DP Channel EQ Start\n");

	Temp_Byte[0] = 0x22; // SCRAMBLING_DISABLE & Training Pattern 2
	Temp_Byte[1] = Swing_PreEmph[0]; 
	Temp_Byte[2] = Swing_PreEmph[1]; 
	Temp_Byte[3] = Swing_PreEmph[2]; 
	Temp_Byte[4] = Swing_PreEmph[3];
	if(!DP_AUX_Write(adap, 0x102, 5, &Temp_Byte[0])) return false;
	
	// Retry 50 times
	for(i=0; i<50; ++i) {
	
		DP_Tx_Mode(adap, DP_TX_MODE__ALIGN_EN);
		
		Temp_Byte[0] = 0x22; // SCRAMBLING_DISABLE & Training Pattern 2
		Temp_Byte[1] = Swing_PreEmph[0]; 
		Temp_Byte[2] = Swing_PreEmph[1]; 
		Temp_Byte[3] = Swing_PreEmph[2]; 
		Temp_Byte[4] = Swing_PreEmph[3];
		if(!DP_AUX_Write(adap, 0x102, 5, &Temp_Byte[0])) return false;
		//if(!DP_AUX_Write(adap, 0x102, 5, &Temp_Byte[0])) return false;
	
		// delay 400us
		//delay_1ms(1);
		msleep(1);
		
		// Check EQ Done
		DP_AUX_Read(adap, 0x202, 2, Temp_Byte);
		
		Status = true;
		if((Temp_Byte[0] & 0x07) == 0x07) {
			//DBG_printf(("DP Lane0 EQ Done\n"));
			dprintk("DP Lane0 EQ Done\n");
		}
		else {
			//DBG_printf(("DP Lane0 EQ Fail %d\n", i));
			dprintk("DP Lane0 EQ Fail %d\n", i);
			Status = false;
		}
		if(2 <= Lanes) {
			if((Temp_Byte[0] & 0x70) == 0x70) {
				//DBG_printf(("DP Lane1 EQ Done\n"));
				dprintk("DP Lane1 EQ Done\n");
			}
			else {
				//DBG_printf(("DP Lane1 EQ Fail %d\n", i));
				dprintk("DP Lane1 EQ Fail %d\n", i);
				Status = false;
			}	
		}
		if(4 <= Lanes) {
			if((Temp_Byte[1] & 0x77) == 0x77) {
				//DBG_printf(("DP Lane2/3 EQ Done\n"));
				dprintk("DP Lane2/3 EQ Done\n");
			}
			else {
				//DBG_printf(("DP Lane2/3 EQ Fail %d\n", i));
				dprintk("DP Lane2/3 EQ Fail %d\n", i);
				Status = false;
			}	
		}
		
		if(Status == true) {
			return true;
		}
		else {
			if(!AUX_DP_Adjust_Swing_PreEmph(adap)) {
				return false;
			}
		}
		
		if(i == 20)
				return false;
		
		// EQ fail, re-do CR train
		AUX_Clock_Recovery_Start(adap);
		
	}

	return false;
}

bool AUX_DP_Adjust_Swing_PreEmph(struct i2c_adapter *adap)
{	
	uint8_t Temp_Byte[2];
	//
	// Increase the Swing and PreEm then try again.
	//
	
	DP_AUX_Read(adap, 0x206, 2, Temp_Byte);
	//DBG_printf(("Increase the Swing and PreEm 0x%02bX, 0x%02bX\n", Temp_Byte[0], Temp_Byte[1]));
	dprintk("Increase the Swing and PreEm 0x%02x, 0x%02x\n", Temp_Byte[0], Temp_Byte[1]);
	
	// Copy Swing Level Settings
	Swing_PreEmph[0] = Temp_Byte[0] & 0x03;
	Swing_PreEmph[1] = (Temp_Byte[0] & 0x30) >> 4; 
	Swing_PreEmph[2] = Temp_Byte[1] & 0x03;
	Swing_PreEmph[3] = (Temp_Byte[1] & 0x30) >> 4; 
	
	// Copy Pre_Emph Settings
	Swing_PreEmph[0] |= (Temp_Byte[0] & 0x0C) << 1;
	Swing_PreEmph[1] |= (Temp_Byte[0] & 0xC0) >> 3; 
	Swing_PreEmph[2] |= (Temp_Byte[1] & 0x0C) << 1;
	Swing_PreEmph[3] |= (Temp_Byte[1] & 0xC0) >> 3; 
	

	//
	// Apply settings to the PHY
	//
	
	DP_Tx_Swing_PreEmph_Set(adap, Swing_PreEmph[0] & 0x03, (Swing_PreEmph[0] >> 3) & 0x03);
	
	
	//
	// Write to the AUX Sink
	//
	
	// Check Max Swing reached
	if((Swing_PreEmph[0] & 0x03) >= 3) Swing_PreEmph[0] |= 0x04;
	if((Swing_PreEmph[1] & 0x03) >= 3) Swing_PreEmph[1] |= 0x04;
	if((Swing_PreEmph[2] & 0x03) >= 3) Swing_PreEmph[2] |= 0x04;
	if((Swing_PreEmph[3] & 0x03) >= 3) Swing_PreEmph[3] |= 0x04;
	// Check Max PreEmph reached
	if(((Swing_PreEmph[0] >> 3) & 0x03) >= 2) Swing_PreEmph[0] |= 0x20;
	if(((Swing_PreEmph[1] >> 3) & 0x03) >= 2) Swing_PreEmph[1] |= 0x20;
	if(((Swing_PreEmph[2] >> 3) & 0x03) >= 2) Swing_PreEmph[2] |= 0x20;
	if(((Swing_PreEmph[3] >> 3) & 0x03) >= 2) Swing_PreEmph[3] |= 0x20;

	//DBG_printf(("Settings 0x%02bX, 0x%02bX, 0x%02bX, 0x%02bX\n", Swing_PreEmph[0], Swing_PreEmph[1], Swing_PreEmph[2], Swing_PreEmph[3]));
	dprintk("Settings 0x%02x, 0x%02x, 0x%02x, 0x%02x\n", Swing_PreEmph[0], Swing_PreEmph[1], Swing_PreEmph[2], Swing_PreEmph[3]);
	DP_AUX_Write(adap, 0x103, 4, Swing_PreEmph);
	
	return true;
}

// Call this Link Task to establish the connection
bool EP146Control_Link_Task(struct i2c_adapter *adap)
{
	dprintk("EP146Control_Link_Task()\n");
	uint8_t tmp, i;
	uint8_t Sys_Ram[1];
	AUX_Read_Information(adap, forceRate, forceLanes);
	
	//LVDS_Rx_Power_Up();
	tmp = i2c_read(adap, EP146_General_Control_0);
	tmp |= EP146_General_Control_0__PU;
	i2c_write(adap, EP146_General_Control_0, tmp);
	DP_Tx_Power_Up(adap);	// YH : enable tx power
	msleep(10);
		
	AUX_State = AUX_LINK_STATE__Clock_Recovery;
	
	///*	// YH : ??�떒 留됱??
	for(i=0; i<2; ++i) {
		if(AUX_Clock_Recovery_Start(adap)) {
			// CR Success
			AUX_State = AUX_LINK_STATE__Channel_EQ;
			break;
		}
		else {
			// If CR faile, down grade the Link Rate and try again.
//			if(Link_Rate == 0x0A) {
//				DBG_printf(("Try 1.62Gbps per lane\n"));
//				DP_Tx_Link_Rate(0);
//				Link_Rate = 0x06;
//				DP_AUX_Write(0x100, 1, &Link_Rate); // Write Back to Sink
//			}
//			else {
//				return FALSE;
//			}
		}
	}
	
	for(i=0; i<2; ++i) {
		if(AUX_Channel_EQ_Start(adap)) {
			// EQ Success
			AUX_DP_Streaming(adap);
			AUX_State = AUX_LINK_STATE__Streaming;
			break;
		}
		else {
			// If CR faile, down grade the Link Rate and try again.
//			if(Link_Rate == 0x0A) {
//				DBG_printf(("Try 1.62Gbps per lane\n"));
//				DP_Tx_Link_Rate(0);
//				Link_Rate = 0x06;
//				DP_AUX_Write(0x100, 1, &Link_Rate); // Write Back to Sink
//			}
//			else {
//				return FALSE;
//			}
		}
	}
	//*/
	AUX_DP_Streaming(adap);
	AUX_State = AUX_LINK_STATE__Streaming;
#if 1	
	DP_AUX_Read(adap, 0x000D, 1 , Sys_Ram);
	if(Sys_Ram[0] & 0x01 )
	{
		Sys_Ram[0] = 1;
		DP_AUX_Write(adap, 0x010a, 1, Sys_Ram);
		//EP146_Reg_Set_Bit(EP146_General_Control_5, EP146_General_Control_5__eDP);
		tmp = i2c_read(adap, EP146_General_Control_5);
		tmp |= EP146_General_Control_5__eDP;
		i2c_write(adap, EP146_General_Control_5, tmp);
		//DBG_printf(("eDP enable\n"));
		dprintk("eDP enable\n");
	}
	else
		//DBG_printf(("eDP not support\n"));
		dprintk("eDP not support\n");

#endif
	return true;
}

EDID_STATUS Downstream_Rx_read_EDID(struct i2c_adapter *adap, uint8_t *pEDID)
{
	uint8_t seg_ptr, BlockCount, Block1Found, ChkSum;
	int i;
	EDID_STATUS status;

	// =========================================================
	// I. Read the block 0

	for(i=0; i<128; i+=EDID_READ_STEP) {
		// Segment Pointer Address
		DDC_Segment_Write(adap, 0); 

		// Read EDID data
		status = DDC_Read(adap, EDID_ADDR, i, &pEDID[i], EDID_READ_STEP);
		if(status != SMBUS_STATUS_Success) {
			//DBG_printf(("Err: EDID b0-%d read - DN DDC %bu\n", i, status));
			printk("Err: EDID b0-%d read - DN DDC %bu\n", i, status);
			return status;
		}
	}

	//DBG_printf(("EDID b0 read:"));
	dprintk("EDID b0 read:\n");
	for(i=0; i<128; ++i) {
		if(i%16 == 0) //DBG_printf(("\n"));
			dprintk("\n");
		if(i%8 == 0) //DBG_printf((" "));
			dprintk(" ");
		//DBG_printf(("0x%02bX,", pEDID[i] ));
		dprintk("0x%02x,", pEDID[i]);
	}
	//DBG_printf(("\n"));
	dprintk("\n");

	// Check EDID
	if(pEDID[126] > 8) {
		//DBG_printf(("Err: EDID Check failed, pEDID[126]=0x%02bX > 8\n\r", pEDID[126] ));
		printk("Err: EDID Check failed, pEDID[126]=0x%02x > 8\n\r", pEDID[126]);
		return EDID_STATUS_ExtensionOverflow;
	}

	// =========================================================
	// II. Read other blocks and find Timing Extension Block

	BlockCount = pEDID[126];
	Block1Found = 0;
	for (seg_ptr = 1; seg_ptr <= BlockCount; ++seg_ptr) {

		// Base Address and Read 128
		if(Block1Found) {		
			for(i=0; i<128; i+=EDID_READ_STEP) {
				// Segment Pointer Address
				DDC_Segment_Write(adap, seg_ptr >> 1); 
		
				// Read EDID data
				status = DDC_Read(adap, EDID_ADDR, ((seg_ptr & 0x01) << 7)+i, DDC_Data, EDID_READ_STEP);
				if(status != SMBUS_STATUS_Success) {
					//DBG_printf(("Err: EDID b%bu-%d read\n", seg_ptr, i));
					printk("Err: EDID b%bu-%d read\n", seg_ptr, i);
					return status;
				}
			}
		}
		else {	
			for(i=0; i<128; i+=EDID_READ_STEP) {
				// Segment Pointer Address
				DDC_Segment_Write(adap, seg_ptr >> 1); 
		
				// Read EDID data
				status = DDC_Read(adap, EDID_ADDR, ((seg_ptr & 0x01) << 7)+i, &pEDID[128+i], EDID_READ_STEP);
				if(status != SMBUS_STATUS_Success) {
					//DBG_printf(("Err: EDID b%bu-%d read\n", seg_ptr, i));
					printk("Err: EDID b%bu-%d read\n", seg_ptr, i);
					return status;
				}
			}
		}

		if(pEDID[128] == 0x02 && Block1Found == 0) {
			Block1Found = 1;

			//DBG_printf(("EDID b%bu read:", seg_ptr));
			dprintk("EDID b%bu read:", seg_ptr);
			for(i=0; i<128; ++i) {
				if(i%16 == 0) //DBG_printf(("\n"));
					dprintk("\n");
				if(i%8 == 0) //DBG_printf((" "));
					dprintk("\n");
				//DBG_printf(("0x%02bX,", pEDID[128+i] ));
				dprintk("0x%02x,", pEDID[128+i]);
			}
			//DBG_printf(("\n"));
			dprintk("\n");
		}
	}
	
	// Check CheckSum
	ChkSum = 0;
	for(i=0; i<((Block1Found)?256:128); ++i) {
		ChkSum += pEDID[i];
	}
	if(ChkSum != 0) {
		return EDID_STATUS_ChecksumError;
	}
	if(Block1Found) {
		pEDID[126] = 1;
	}
	else {
		pEDID[126] = 0;
	}
	return EDID_STATUS_Success;
}

void DDC_Segment_Write(struct i2c_adapter *adap, uint8_t Segment)
{
	SMBUS_STATUS status;
	status = DP_AUX_DDC_Cmd(adap, EDID_SEGMENT_PTR, &Segment, 0, SMBUS_SkipStop);
	if(!status) { // if no error
		DP_AUX_DDC_Cmd(adap, EDID_SEGMENT_PTR, &Segment, 1, SMBUS_DataOnly);
	}
}

SMBUS_STATUS DDC_Access(struct i2c_adapter *adap, uint8_t IICAddr, uint8_t RegAddr, void *Data, int Size)
{
	SMBUS_STATUS status;
	if(IICAddr & 0x01) { // Read
		status = DP_AUX_DDC_Cmd(adap, IICAddr-1, &RegAddr, 1, SMBUS_SkipStop);
		status |= DP_AUX_DDC_Cmd(adap, IICAddr, Data, Size, SMBUS_Normal);
	}
	else { // Write
		status = DP_AUX_DDC_Cmd(adap, IICAddr, &RegAddr, 1, SMBUS_SkipStop);
		status |= DP_AUX_DDC_Cmd(adap, IICAddr, Data, Size, SMBUS_SkipStart);
	}
	if(status) { // failed and retry
		//DBG_printf(("Err: DDC failed %bu, IICAddr=0x%02bX, RegAddr=0x%02bX\n", status, IICAddr, RegAddr));
		printk("Err: DDC failed %bu, IICAddr=0x%02x, RegAddr=0x%02x\n", status, IICAddr, RegAddr);
	
	}
	return status;
}

SMBUS_STATUS DDC_Read(struct i2c_adapter *adap, uint8_t IICAddr, uint8_t RegAddr, void *Data, int Size)
{
	if(!(IICAddr & 0x01)) IICAddr |= 1;
	return DDC_Access(adap, IICAddr, RegAddr, Data, Size);
}

//--------------------------------------------------------------------------------------------------
// MHL Access DDC

SMBUS_STATUS DP_AUX_DDC_Cmd(struct i2c_adapter *adap, uint8_t Addr, uint8_t *pDatas, int Length, SMBUS_MODE Mode)
{
	int i=0, j=0, k=0;
	uint8_t Temp_Data[6];
	SMBUS_STATUS status = SMBUS_STATUS_Success;

	if(!(Mode & SMBUS_SkipStart)) {

		for(j=0; j<AUX_CMD_RETRY_TIME; ++j) {
		
			// Command
			if(Addr & 1) {
				// Read
				Temp_Data[1] = 0x50; // RQ_CMD[3:0] | 0000
			}
			else {
				// Write
				Temp_Data[1] = 0x40; // RQ_CMD[3:0] | 0000
			}
				
			// Address
			Temp_Data[2] = 0;
			Temp_Data[3] = Addr>>1;
		
			// Copy Data
			//EP146_Reg_Write(EP146_AUX_RQ_Command, &Temp_Data[1], 3);
			i2c_write_len(adap, EP146_AUX_RQ_Command, &Temp_Data[1], 3);
				
			// RQ Start
			Temp_Data[0] = EP146_AUX_Control__RQ_START | EP146_AUX_Control__RQ_MODE; // Short mode. LEN and DATA bytes are not sent.
			//EP146_Reg_Write(EP146_AUX_Control, &Temp_Data[0], 1);	
			i2c_write_len(adap, EP146_AUX_Control, &Temp_Data[0], 1);
			
			// Wait...
			for(i=0; i<AUX_TIMEOUT; i++) {
				//EP146_Reg_Read(EP146_AUX_Control, &Temp_Data[0], 1);
				Temp_Data[0] = i2c_read(adap, EP146_AUX_Control);
				Cache_EP146_AUX_Flags |= Temp_Data[0] & 0xE0;
			
				if(Temp_Data[0] & EP146_AUX_Control__RP_F) {
					break;
				}
			}
			if(Temp_Data[0] & EP146_AUX_Control__RP_F) {
			
				// Check Reply
				//EP146_Reg_Read(EP146_AUX_RP_Data, &Temp_Data[1], 1);
				Temp_Data[1] = i2c_read(adap, EP146_AUX_RP_Data);
				if(Temp_Data[1] == 0) { // ACK
					status = SMBUS_STATUS_Success;
					break;
				}
				else if(Temp_Data[1] == 0x10) { // NACK
					//DBG_printf(("Warn: AUX DDC Start NACK\n"));
					dprintk("Warn: AUX DDC Start NACK\n");
					status = SMBUS_STATUS_NoAct;
				}
				else if(Temp_Data[1] == 0x20) { // DEFER
					//DBG_printf(("Warn: AUX DDC Start DEFER\n"));
					dprintk("Warn: AUX DDC Start DEFER\n");
					status = SMBUS_STATUS_Pending;
				}	
			}
			else {
				//DBG_printf(("Err: DP_AUX DDC Start Timeout\n"));
				printk("Err: DP_AUX DDC Start Timeout\n");
				status = SMBUS_STATUS_TimeOut;
			}		
		}	  
	}

	if(status == SMBUS_STATUS_Success) {
		if(Addr & 0x01) {	// Read
			for(k = 0; (k < Length) && (status == 0); ++k) {

				for(j=0; j<AUX_CMD_RETRY_TIME; ++j) {
				
					// Command
					Temp_Data[1] = 0x50; // RQ_CMD[3:0] | 0000
						
					// Address
					Temp_Data[2] = 0;
					Temp_Data[3] = Addr>>1;
					
					Temp_Data[4] = 0;
				
					// Copy Data
					//EP146_Reg_Write(EP146_AUX_RQ_Command, &Temp_Data[1], 4);
					i2c_write_len(adap, EP146_AUX_RQ_Command, &Temp_Data[1], 4);
						
					// RQ Start
					Temp_Data[0] = EP146_AUX_Control__RQ_START; // Normal mode
					//EP146_Reg_Write(EP146_AUX_Control, &Temp_Data[0], 1);	
					i2c_write_len(adap, EP146_AUX_Control, &Temp_Data[0], 1);
					
					
					// Wait...
					for(i=0; i<AUX_TIMEOUT; i++) {
						//EP146_Reg_Read(EP146_AUX_Control, &Temp_Data[0], 1);
						Temp_Data[0] = i2c_read(adap, EP146_AUX_Control);
						Cache_EP146_AUX_Flags |= Temp_Data[0] & 0xE0;
					
						if(Temp_Data[0] & EP146_AUX_Control__RP_F) {
							break;
						}
					}
					if(Temp_Data[0] & EP146_AUX_Control__RP_F) {
					
						// Check Reply
						//EP146_Reg_Read(EP146_AUX_RP_Data, &Temp_Data[1], 2);
						i2c_read_len(adap, EP146_AUX_RP_Data, &Temp_Data[1], 2);
						if(Temp_Data[1] == 0) { // ACK
							pDatas[k] = Temp_Data[2];
							status = SMBUS_STATUS_Success;
							break;
						}
						else if(Temp_Data[1] == 0x10) { // NACK
							//DBG_printf(("Warn: AUX DDC Read NACK\n"));
							dprintk("Warn: AUX DDC Read NACK\n");
							status = SMBUS_STATUS_NoAct;
						}
						else if(Temp_Data[1] == 0x20) { // DEFER
							//DBG_printf(("Warn: AUX DDC Read DEFER\n"));
							dprintk("Warn: AUX DDC Read DEFER\n");
							status = SMBUS_STATUS_Pending;
						}	
					}
					else {
						//DBG_printf(("Err: DP_AUX DDC Read Timeout\n"));
						printk("Err: DP_AUX DDC Read Timeout\n");
						status = SMBUS_STATUS_TimeOut;
					}		
				}

			}
		}
		else {
			for(k = 0; (k < Length) && (status == 0); ++k) {
			
				for(j=0; j<AUX_CMD_RETRY_TIME; ++j) {
				
					// Command
					Temp_Data[1] = 0x40; // RQ_CMD[3:0] | 0000
						
					// Address
					Temp_Data[2] = 0;
					Temp_Data[3] = Addr>>1;
					
					Temp_Data[4] = 0;
					Temp_Data[5] = pDatas[k];
				
					// Copy Data
					//EP146_Reg_Write(EP146_AUX_RQ_Command, &Temp_Data[1], 5);
					i2c_write_len(adap, EP146_AUX_RQ_Command, &Temp_Data[1], 5);
						
					// RQ Start
					Temp_Data[0] = EP146_AUX_Control__RQ_START; // Normal mode
					//EP146_Reg_Write(EP146_AUX_Control, &Temp_Data[0], 1);	
					i2c_write_len(adap, EP146_AUX_Control, &Temp_Data[0], 1);	
					
					
					// Wait...
					for(i=0; i<AUX_TIMEOUT; i++) {
						//EP146_Reg_Read(EP146_AUX_Control, &Temp_Data[0], 1);
						Temp_Data[0] = i2c_read(adap, EP146_AUX_Control);
						Cache_EP146_AUX_Flags |= Temp_Data[0] & 0xE0;
					
						if(Temp_Data[0] & EP146_AUX_Control__RP_F) {
							break;
						}
					}
					if(Temp_Data[0] & EP146_AUX_Control__RP_F) {
					
						// Check Reply
						//EP146_Reg_Read(EP146_AUX_RP_Data, &Temp_Data[1], 1);
						Temp_Data[1] = i2c_read(adap, EP146_AUX_RP_Data);
						if(Temp_Data[1] == 0) { // ACK
							status = SMBUS_STATUS_Success;
							break;
						}
						else if(Temp_Data[1] == 0x10) { // NACK
							//DBG_printf(("Warn: AUX DDC Write NACK\n"));
							dprintk("Warn: AUX DDC Write NACK\n");
							status = SMBUS_STATUS_NoAct;
						}
						else if(Temp_Data[1] == 0x20) { // DEFER
							//DBG_printf(("Warn: AUX DDC Write DEFER\n"));
							dprintk("Warn: AUX DDC Write DEFER\n");
							status = SMBUS_STATUS_Pending;
						}	
					}
					else {
						//DBG_printf(("Err: DP_AUX DDC Write Timeout\n"));
						printk("Err: DP_AUX DDC Write Timeout\n");
						status = SMBUS_STATUS_TimeOut;
					}		
				}	
						
			}
		}
	}
	
	if(!(Mode & SMBUS_SkipStop)) {
	
		// Command
		if(Addr & 1) {
			// Read
			Temp_Data[1] = 0x10; // RQ_CMD[3:0] | 0000
		}
		else {
			// Write
			Temp_Data[1] = 0x00; // RQ_CMD[3:0] | 0000
		}
			
		// Address
		Temp_Data[2] = 0;
		Temp_Data[3] = Addr>>1;
			
		// Copy Data
		//EP146_Reg_Write(EP146_AUX_RQ_Command, &Temp_Data[1], 3);
		i2c_write_len(adap, EP146_AUX_RQ_Command, &Temp_Data[1], 3);
			
		// RQ Start
		Temp_Data[0] = EP146_AUX_Control__RQ_START | EP146_AUX_Control__RQ_MODE; // Short mode. LEN and DATA bytes are not sent.
		//EP146_Reg_Write(EP146_AUX_Control, &Temp_Data[0], 1);	
		i2c_write_len(adap, EP146_AUX_Control, &Temp_Data[0], 1);
		
		
		// Wait...
		for(i=0; i<AUX_TIMEOUT; i++) {
			//EP146_Reg_Read(EP146_AUX_Control, &Temp_Data[0], 1);
			Temp_Data[0] = i2c_read(adap, EP146_AUX_Control);
			Cache_EP146_AUX_Flags |= Temp_Data[0] & 0xE0;
		
			if(Temp_Data[0] & EP146_AUX_Control__RP_F) {
				break;
			}
		}
		if(Temp_Data[0] & EP146_AUX_Control__RP_F) {
		}
		else {
			//DBG_printf(("Err: DP_AUX DDC Stop Timeout\n"));
			printk("Err: DP_AUX DDC Stop Timeout\n");
		}		
	}

	return status;
}
/*
static irqreturn_t ep126_dp_interrupt(int irq, void *_data)
{
	struct panel_simple *panel = _data;
	
	EP146Control_IRQ_Event(panel->ddc);
	
	return IRQ_HANDLED;
}
*/