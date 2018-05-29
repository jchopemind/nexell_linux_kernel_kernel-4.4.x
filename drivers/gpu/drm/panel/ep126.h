#ifndef __EP126_H__
#define __EP126_H__

// YH 
#define AUX_CMD_RETRY_TIME 					4
#define AUX_TIMEOUT							5 // 400us timeout
#define EDID_READ_STEP						16
#define EDID_SEGMENT_PTR					0x60
#define EDID_ADDR       					0xA0     // EDID Address

// Registers								Word	BitMask
#define EP146_General_Control_0				0x00
#define EP146_General_Control_0__PU					0x01
#define EP146_General_Control_0__TX_PU				0x02
#define EP146_General_Control_0__SOFT_RST			0x04
#define EP146_General_Control_0__DIG_IN				0x20
#define EP146_General_Control_0__DCLK_POL			0x40
#define EP146_General_Control_0__INT_POL			0x80
#define EP146_General_Control_1				0x01
#define EP146_General_Control_1__LVDS_BW			0xC0
#define EP146_General_Control_1__DE_ONLY			0x20
#define EP146_General_Control_1__LVDS_MAP			0x10
#define EP146_General_Control_1__01_SWAP			0x08
#define EP146_General_Control_1__EO_SWAP			0x04
#define EP146_General_Control_1__LVDS_MODE			0x03
#define EP146_General_Control_2				0x02
#define EP146_General_Control_2__PLL_MODE			0x08
#define EP146_General_Control_2__F_ORDER			0x04
#define EP146_General_Control_2__nLANE				0x03
#define EP146_General_Control_3				0x03
#define EP146_General_Control_3__NOvid				0x10
#define EP146_General_Control_3__INrange			0x08
#define EP146_General_Control_3__INcs				0x04
#define EP146_General_Control_3__INcd				0x02
#define EP146_General_Control_3__INycc				0x01
#define EP146_General_Control_4				0x04
#define EP146_General_Control_4__SWING				0x0C	
#define EP146_General_Control_4__PRE				0x03
#define EP146_AUX_RQ_Command 				0x41
#define EP146_AUX_Control					0x40
#define EP146_AUX_Control__HPD_F					0x80
#define EP146_AUX_Control__HPD_IE					0x80
#define EP146_AUX_Control__RP_F						0x40
#define EP146_AUX_Control__RP_IE					0x40
#define EP146_AUX_Control__RQ_F						0x20
#define EP146_AUX_Control__RQ_IE					0x20
#define EP146_AUX_Control__HPD_STATE				0x10
#define EP146_AUX_Control__RP_ACT					0x08
#define EP146_AUX_Control__RQ_ACT					0x04
#define EP146_AUX_Control__RQ_START					0x02
#define EP146_AUX_Control__RQ_MODE					0x01
#define EP146_General_Control_5				0x05
#define EP146_General_Control_5__eDP				0x80
#define EP146_General_Control_5__DP_BW				0x40
#define EP146_General_Control_5__ENH_FRAME			0x20
#define EP146_General_Control_5__VTA_MODE			0x10
#define EP146_General_Control_5__SCRAM_DIS			0x08
#define EP146_General_Control_5__STREAM_EN			0x04
#define EP146_General_Control_5__ALIGN_EN			0x02
#define EP146_General_Control_5__CR_EN				0x01
#define EP146_TU_SIZE						0x06
#define EP146_MSA_R							0x20
#define EP146_MSA_R_N_vid					0x23
#define EP146_AUX_RQ_Len					0x44
#define EP146_AUX_RP_Len					0x44

#define EP146_AUX_RQ_Data					0x45
#define EP146_AUX_RP_Data					0x45
#define EP146_TX_PHY_Control_0				0x09

#define HTOTAL_H			0x06
#define HTOTAL_L			0x38			//1592
#define VTOTAL_H			0x03
#define VTOTAL_L			0x16			//790
#define HSTART_H			0x00
#define HSTART_L			0x64			//100
#define VSTART_H			0x00
#define VSTART_L			0x0A			//10
#define HACT_H				0x05	
#define HACT_L				0x56			//1366
#define VACT_H				0x03
#define VACT_L				0x00			//768
#define HWIDTH_H			0x00		
#define HWIDTH_L			0x1A			//26
#define VWIDTH_H			0x00
#define VWIDTH_L			0x02			//2

typedef enum {
	DP_TX_MODE__CR_EN = 0, 
	DP_TX_MODE__ALIGN_EN,
	DP_TX_MODE__STREAM_EN,
	DP_TX_MODE__STREAM_EN_NO_SCRAM
} DP_TX_MODE;

typedef enum {
	AUX_LINK_STATE__Idel = 0, 
	AUX_LINK_STATE__Clock_Recovery,
	AUX_LINK_STATE__Channel_EQ,
	AUX_LINK_STATE__Streaming
} AUX_LINK_STATE;

// EDID status error code
typedef enum {
	// Master
	EDID_STATUS_Success = 0x00,
	EDID_STATUS_Pending,//	SMBUS_STATUS_Abort,
	EDID_STATUS_NoAct = 0x02,
	EDID_STATUS_TimeOut,
	EDID_STATUS_ArbitrationLoss = 0x04,
	EDID_STATUS_ExtensionOverflow,
	EDID_STATUS_ChecksumError
} EDID_STATUS;

typedef enum {
	SMBUS_Normal = 0,
	SMBUS_SkipStop,
	SMBUS_SkipStart,
	SMBUS_DataOnly		// 3 = SMBUS_SkipStop | SMBUS_SkipStart
} SMBUS_MODE;

typedef enum {
	// Master
	SMBUS_STATUS_Success = 0x00,
	SMBUS_STATUS_Pending,//	SMBUS_STATUS_Abort,
	SMBUS_STATUS_NoAct = 0x02,
	SMBUS_STATUS_TimeOut,
	SMBUS_STATUS_ArbitrationLoss = 0x04
} SMBUS_STATUS;

int init_ep126(struct i2c_adapter *adap);
void AUX_DP_Streaming(struct i2c_adapter *adap);
bool DP_AUX_Write(struct i2c_adapter *adap, uint16_t Address, int Len, uint8_t *pData);
bool DP_AUX_Read(struct i2c_adapter *adap, uint16_t Address, uint8_t Len, uint8_t *pData);
void DP_Tx_Mode(struct i2c_adapter *adap, DP_TX_MODE Mode);
uint8_t DP_AUX_Get_Flags(struct i2c_adapter *adap);
void EP146Control_IRQ_Event(struct i2c_adapter *adap);
void AUX_Read_Information(struct i2c_adapter *adap, uint8_t tRate, uint8_t tLanes);
void DP_Tx_Lanes(struct i2c_adapter *adap, uint8_t Lanes);
void DP_Tx_Power_Up(struct i2c_adapter *adap);
void LVDS_Port_setting(struct i2c_adapter *adap, uint8_t port);
void DP_Tx_Swing_PreEmph_Set(struct i2c_adapter *adap, uint8_t Swing, uint8_t PreEmph);
bool AUX_Clock_Recovery_Start(struct i2c_adapter *adap);
bool AUX_Channel_EQ_Start(struct i2c_adapter *adap);
bool AUX_DP_Adjust_Swing_PreEmph(struct i2c_adapter *adap);
bool EP146Control_Link_Task(struct i2c_adapter *adap);
EDID_STATUS Downstream_Rx_read_EDID(struct i2c_adapter *adap, uint8_t *pEDID);
void DDC_Segment_Write(struct i2c_adapter *adap, uint8_t Segment);
SMBUS_STATUS DDC_Access(struct i2c_adapter *adap, uint8_t IICAddr, uint8_t RegAddr, void *Data, int Size);
SMBUS_STATUS DDC_Read(struct i2c_adapter *adap, uint8_t IICAddr, uint8_t RegAddr, void *Data, int Size);
SMBUS_STATUS DP_AUX_DDC_Cmd(struct i2c_adapter *adap, uint8_t Addr, uint8_t *pDatas, int Length, SMBUS_MODE Mode);
static int i2c_write(struct i2c_adapter *adap, uint8_t wreg, uint8_t wdata);
static int i2c_write_len(struct i2c_adapter *adap, uint8_t wreg, uint8_t *wdata, int len);
static uint8_t i2c_read(struct i2c_adapter *adap, uint8_t rreg);
static int i2c_read_len(struct i2c_adapter *adap, uint8_t rreg, uint8_t* rdata, int len);
void DP_Tx_Power_Down(struct i2c_adapter *adap);




#endif