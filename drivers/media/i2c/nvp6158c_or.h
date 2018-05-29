#ifndef __NVP6158C_H__
#define __NVP6158C_H__

int sensor_i2c_read_reg(struct i2c_client *client, u8 reg, u8 *val);
int sensor_i2c_write_reg(struct i2c_client *client, u8 reg, u8 val);
#define  gpio_i2c_read   sensor_i2c_read_reg
#define  gpio_i2c_write  sensor_i2c_write_reg

#define DRIVER_VER "17.0.xx.00"

//For Test
#define FPGA_TEST	1

#define HI_CHIPID_BASE 0x12050000
#define HI_CHIPID0 IO_ADDRESS(HI_CHIPID_BASE + 0xEEC)
#define HI_CHIPID1 IO_ADDRESS(HI_CHIPID_BASE + 0xEE8)
#define HI_CHIPID2 IO_ADDRESS(HI_CHIPID_BASE + 0xEE4)
#define HI_CHIPID3 IO_ADDRESS(HI_CHIPID_BASE + 0xEE0)
#define HW_REG(reg) *((volatile unsigned int *)(reg))

#define _SET_BIT(data,bit) ((data)|=(1<<(bit)))
#define _CLE_BIT(data,bit) ((data)&=(~(1<<(bit))))

#define PORTA		0x00
#define PORTB		0x01
#define PORTC		0x02
#define PORTD		0x03
#define PORTAB		0x04
#define PORTCD		0x05

#define FUNC_ON		0x01
#define FUNC_OFF		0x00

#define SEQUENCE_CH01	0x00
#define SEQUENCE_CH23  0x01

#define VO_WORK_MODE_1MUX	0X00
#define VO_WORK_MODE_2MUX	0X02
#define VO_WORK_MODE_4MUX	0X08

unsigned char __vport_out[4] = {
	0,
	1,
	2,
	3
};

typedef enum NC_CH
{
	CH1 = 0,
	CH2,
	CH3,
	CH4,
} NC_CH;

typedef struct _NC_VD_VO_SEQ_STR{
	unsigned char Port;					// PORT_A, PORTB, PORTC, PORTD
	unsigned char ChNum01;                // [7:4] Sequence2, [3:0] Sequence1
	unsigned char ChNum23;                // [7:4] Sequence4, [3:0] Sequence3
	unsigned char devnum;
	unsigned char Fmt_Def;
}NC_VD_VO_SEQ_STR;

typedef struct _NC_VD_VO_SEQ_REG_STR{
	unsigned char Port;					// PORT_A, PORTB, PORTC, PORTD
	unsigned char b1c0;
	unsigned char b1c1;
	unsigned char b1c2;
	unsigned char b1c3;
	unsigned char b1c4;
	unsigned char b1c5;
	unsigned char b1c6;
	unsigned char devnum;
}NC_VD_VO_SEQ_REG_STR;

typedef struct _NC_VD_VO_PORT_MUX_MODE_STR{
	unsigned char Port;					//PORTAB PORTCD
	unsigned char Mode;               	//[7:4] PORTB or D [3:0] PORTA or C
	unsigned char devnum;
}NC_VD_VO_PORT_MUX_MODE_STR;

typedef struct _NC_VD_VO_PORT_MUX_CHID_STR{
	unsigned char Port;				// PORTA, PORTB 0x55 / PORTC, PORTD 0x56
	unsigned char ChId;               	//[7:4] PORTB or D [3:0] PORTA or C
	unsigned char devnum;
}NC_VD_VO_PORT_MUX_CHID_STR;

typedef struct _NC_VD_VI_FMT_STR{
	unsigned char Ch;
	unsigned char Format;			//B0       0x08/9/A/B
	unsigned char SpecialMode;		//B0       0x81/2/3/4
	unsigned char SdAhdMode;		//B0       0x85/6/7/8
}NC_VD_VI_FMT_STR;

typedef struct _NC_VD_VI_CHROMA_STR{
	unsigned char Ch;
	unsigned char PalCmOff;		//B0       	0x21/5/9/D
	unsigned char SPoint	;		//B5/6/7/8	0x28	
	unsigned char FscLockMode;	//B5/5/6/7	0x25
	unsigned char Hue;			//B0      	0x41/2/3/4
	unsigned char CombMode;		//B5/6/7/8	0x90
	unsigned char BurstDelay;	//B5/6/7/8 	0xD1
}NC_VD_VI_CHROMA_STR;

typedef struct _NC_VD_VI_H_TIMING_STR{
	unsigned char Ch;
	unsigned char devnum;
	unsigned char SyncRs;			//B5/6/7/8 0x47
	unsigned char HDelayLsb;		//B0       0x58/9/A/B
	unsigned char HMaskOn;			//B0       0x89/A/B/C
	unsigned char HMaskSel;		//B0       0x8E/8F/90/91
	unsigned char MemRdp;			//B5/6/7/8 0x64
}NC_VD_VI_H_TIMING_STR;

typedef struct _NC_VD_VI_H_SCALER_STR{
	unsigned char Ch;
	unsigned char HDownScaler;		//B9		0x96/B6/D6/F6
	unsigned char HScalerMode;		//B9		0x97/B7/D7/F7
	unsigned char RefBaseLsb;		//B9        0x98/B8/D8/F8
	unsigned char RefBaseMsb;		//B9        0x99/B9/D9/F9
	unsigned char LineMemMode;		//B0		0x34/5/6/7
}NC_VD_VI_H_SCALER_STR;

typedef struct _NC_VD_VI_CHID_STR{
	unsigned char Ch01;				//B0	    0x55
	unsigned char Ch23;				//B0        0x56
}NC_VD_VI_CHID_STR;

// Auto Detection
typedef struct _NC_VD_VI_VAFE_STR{
	unsigned char PowerDown;   		//B0  0x01/2/3/4 	  [0]
	unsigned char GainSel;			//B0  0x01/2/3/4	  [4]

	unsigned char ClpSPD;  			//B5/6/7/8 0x00       [5:4]

	unsigned char Ctrl_Reg;  		//B5/6/7/8 0x01       [6]
	unsigned char Ctrl_Ibs;  		//B5/6/7/8 0x01       [5:4]
	unsigned char AdcSPD;			//B5/6/7/8 0x01       [2]
	unsigned char ClpLevel;			//B5/6/7/8 0x01       [1:0]

	unsigned char EQBand;   		//B5/6/7/8 0x58       [6:4]
	unsigned char LPFFrontBand; 	//B5/6/7/8 0x58       [2:0]

	unsigned char ClpMode;			//B5/6/7/8 0x59       [7]
	unsigned char F_LPFBypass;		//B5/6/7/8 0x59       [4]
	unsigned char ClpROff;			//B5/6/7/8 0x59       [3]
	unsigned char B_LPFBypass;		//B5/6/7/8 0x59       [0]

	unsigned char Duty;		   		//B5/6/7/8 0x5B    	  [6:4]
	unsigned char REFVol;   		//B5/6/7/8 0x5B       [1:0]

	unsigned char LPFBackBand;  	//B5/6/7/8 0x5C       [6:4]
	unsigned char ClkSel;  			//B5/6/7/8 0x5C       [3]
	unsigned char EQGainSel;		//B5/6/7/8 0x5C       [2:0]

}NC_VD_VI_VAFE_STR;

// HPLL Setup // 170203 HPLL
typedef struct _NC_VD_VI_HPLL_STR{
 unsigned char Ch;
 unsigned char MaskOn;			//B5/6/7/8 0x50
/* 170222 HPLL MASK ON
 unsigned char BYPTh_E;			//B5/6/7/8 0xBB
 unsigned char BYPTh_S;			//B5/6/7/8 0xB7
*/
 unsigned char OpMd;				//B5/6/7/8 0xB8

}NC_VD_VI_HPLL_STR;

// 170223 HZOOM SET
typedef struct _NC_VD_VI_HZOOM_STR{
 unsigned char Ch;
 unsigned char Hzoom;				// B0 0x93/0x94/0x95/0x96
 unsigned char ZoomDto;				// B0 0x98/0x99/0x9A/0x9B
}NC_VD_VI_HZOOM_STR;

// 170223  SET
typedef struct _NC_VD_VI_AGC_STR{
 unsigned char Ch;
 unsigned char Agc;					// B5/B6/B7/B8 0x05
}NC_VD_VI_AGC_STR;

// 170223 HZOOM SET
typedef struct _NC_VD_VI_COMB_TH_STR{
 unsigned char Ch;
 unsigned char Comb_Th_A;			// B5/B6/B7/B8 0x1B
}NC_VD_VI_COMB_TH_STR;

// 170223 HZOOM SET
typedef struct _NC_VD_VI_YLPF_STR{
 unsigned char Ch;
 unsigned char Y_lpf;				// B0 0x18/0x19/0x1A/0x1B
}NC_VD_VI_YLPF_STR;

// 170314 SYNC_EN SET
typedef struct _NC_VD_VI_SYNC_EN_STR{
 unsigned char Ch;
 unsigned char SyncEnLsb;				// B5/B6/B7/B8 0x84
 unsigned char SyncEnMsb;				// B5/B6/B7/B8 0x86
}NC_VD_VI_SYNC_EN_STR;

// 170314 VBLK_END SET
typedef struct _NC_VD_VI_VBLK_END_EXT_STR{
 unsigned char Ch;
 unsigned char VblkEndLsb;				// B5/B6/B7/B8 0x6E
 unsigned char VblkEndMsb;				// B5/B6/B7/B8 0x6F
}NC_VD_VI_VBLK_END_EXT_STR;

typedef struct _NC_VD_VI_FB_YDELAY_STR{
	unsigned char Ch;
	unsigned char devnum;
	unsigned char DF_YDelay;			//B0 0xA0/0xA1/0xA2/0xA3 [3:0]
	unsigned char DB_YDelay;			//B0 0xA4/0xA5/0xA6/0xA7 [3:0]
}NC_VD_VI_FB_YDELAY_STR;

typedef struct _NC_VD_VI_FB_CDELAY_STR{
	unsigned char Ch;
	unsigned char DF_CDelay;			//B0 0xA0/0xA1/0xA2/0xA3 [7:4]
	unsigned char DB_CDelay;			//B0 0xA4/0xA5/0xA6/0xA7 [7:4]
}NC_VD_VI_FB_CDELAY_STR;

typedef struct _NC_VD_DEV_CH_INFO_STR{
	unsigned char Ch;
	unsigned char Dev_Num;
	unsigned char Fmt_Def;
}NC_VD_DEV_CH_INFO_STR;

typedef struct _NC_VD_DEV_PORT_ENABLE_STR{
	unsigned char Ch;
	unsigned char Dev_Num;
	unsigned char Fmt_Def;
	unsigned char enable;
}NC_VD_DEV_PORT_ENABLE_STR;

typedef struct _decoder_get_information_str
{
	unsigned char chip_id[4];
	unsigned char chip_rev[4];
	unsigned char chip_addr[4];

	unsigned char Total_Port_Num;
	unsigned char Total_Chip_Cnt;

}decoder_get_information_str;

typedef struct _decoder_dev_ch_info_s
{
	unsigned char ch;
	unsigned char devnum;
	unsigned char fmt_def;
}decoder_dev_ch_info_s;

typedef struct _video_input_basic_timing_init_s{
	unsigned char	sync_rs;		//B5/6/7/8	0x47
	unsigned char	h_delay_lsb;	//B0 		0x58/0x59/0x5a/0x5b
	unsigned char	h_mask_on;		//B0		0x89/0x8a/0x8b/0x8c
	unsigned char	h_mask_sel;     //B0		0x8e/0x8f/0x90/0x91
	unsigned char 	mem_rdp;		//B5/6/7/8	0x64
	unsigned char	v_blk_end_b;	//B5/6/7/8	0xA9
	unsigned char	y_delay;		//B0		0xA0/0xA1/0xA2/0xA3
	unsigned char	fld_inv;		//B0		0x54[4]/[5]/[6]/[7]
	unsigned char	v_blk_end_a;	//B0		0x64/0x65/0x66/0x67

	unsigned char reserved1;
	unsigned char reserved2;
	unsigned char reserved3;
	unsigned char reserved4;
	unsigned char reserved5;
	unsigned char reserved6;

}video_input_basic_timing_init_s;

typedef enum NC_VIVO_CH_FORMATDEF
{
	NC_VIVO_CH_FORMATDEF_UNKNOWN = 0,
	NC_VIVO_CH_FORMATDEF_AUTO,

	AHD20_SD_H960_NT,
	AHD20_SD_H960_PAL,
	AHD20_SD_SH720_NT,
	AHD20_SD_SH720_PAL,
	AHD20_SD_H1280_NT,
	AHD20_SD_H1280_PAL,
	AHD20_SD_H1440_NT,
	AHD20_SD_H1440_PAL,
	AHD20_SD_H960_EX_NT,
	AHD20_SD_H960_EX_PAL,
	AHD20_SD_H960_2EX_NT,
	AHD20_SD_H960_2EX_PAL,
	AHD20_SD_H960_2EX_Btype_NT,
	AHD20_SD_H960_2EX_Btype_PAL,

	AHD20_1080P_60P, // For Test
	AHD20_1080P_50P, // For Test

	AHD20_1080P_30P,
	AHD20_1080P_25P,

	AHD20_960P_60P,	// For Test
	AHD20_960P_50P, // For Test
	AHD20_960P_30P, // For Test
	AHD20_960P_25P, // For Test

	AHD20_720P_60P,
	AHD20_720P_50P,
	AHD20_720P_30P,
	AHD20_720P_25P,
	AHD20_720P_30P_EX,
	AHD20_720P_25P_EX,
	AHD20_720P_30P_EX_Btype,
	AHD20_720P_25P_EX_Btype,

	AHD30_4M_30P,
	AHD30_4M_25P,
	AHD30_4M_15P,
	AHD30_3M_30P,
	AHD30_3M_25P,
	AHD30_3M_18P,
	AHD30_5M_12_5P,
	AHD30_5M_20P,


	AHD30_5_3M_20P,
	AHD30_6M_18P,
	AHD30_6M_20P,
	AHD30_8M_X_30P,
	AHD30_8M_X_25P,
	AHD30_8M_7_5P,
	AHD30_8M_12_5P,
	AHD30_8M_15P,

	TVI_FHD_30P,
	TVI_FHD_25P,
	TVI_HD_60P,
	TVI_HD_50P,
	TVI_HD_30P,
	TVI_HD_25P,
	TVI_HD_30P_EX,
	TVI_HD_25P_EX,
	TVI_HD_B_30P,
	TVI_HD_B_25P,
	TVI_HD_B_30P_EX,
	TVI_HD_B_25P_EX,
	TVI_3M_18P,
	TVI_5M_12_5P,

	TVI_5M_20P, /*By Edward for testing when 170912 */

	TVI_4M_30P,
	TVI_4M_25P,
	TVI_4M_15P,  /*By Edward for testing when 170912 */

	CVI_FHD_30P,
	CVI_FHD_25P,
	CVI_HD_60P,
	CVI_HD_50P,
	CVI_HD_30P,
	CVI_HD_25P,
	CVI_HD_30P_EX,
	CVI_HD_25P_EX,
	CVI_4M_30P,
	CVI_4M_25P,
	CVI_8M_15P,
	CVI_8M_12_5P,

	NC_VIVO_CH_FORMATDEF_MAX,

} NC_VIVO_CH_FORMATDEF;

typedef enum NC_FORMAT_FPS
{
	FMT_FPS_UNKNOWN = 0,
	FMT_NT = 1,
	FMT_PAL,
	FMT_12_5P,
	FMT_7_5P,
	FMT_30P,
	FMT_25P,
	FMT_50P,
	FMT_60P,
	FMT_15P,
	FMT_18P,
	FMT_18_75P,
	FMT_20P,

	FMT_FPS_MAX,

} NC_FORMAT_FPS;

//#define FMT_AUTO (-1)

typedef enum NC_FORMAT_STANDARD
{
	FMT_STD_UNKNOWN = 0,
	FMT_SD,
	FMT_AHD20,
	FMT_AHD30,
	FMT_TVI,
	FMT_CVI,

	FMT_AUTO,		// FIXME

	FMT_STD_MAX,

} NC_FORMAT_STANDARD;


typedef enum NC_FORMAT_RESOLUTION
{
	FMT_RESOL_UNKNOWN = 0,
	FMT_SH720,
	FMT_H960,
	FMT_H1280,
	FMT_H1440,
	FMT_H960_EX,
	FMT_H960_2EX,
	FMT_H960_Btype_2EX,
	FMT_720P,
	FMT_720P_EX,
	FMT_720P_Btype,
	FMT_720P_Btype_EX,
	FMT_1080P,
	FMT_3M,
	FMT_4M,
	FMT_5M,
	FMT_5_3M,
	FMT_6M,
	FMT_8M_X,
	FMT_8M,
	FMT_RESOL_MAX,

	FMT_H960_Btype_2EX_SP,
	FMT_720P_Btype_EX_SP,

	FMT_960P,

} NC_FORMAT_RESOLUTION;

unsigned char __fmtdef[4] = {
	TVI_FHD_30P,
	TVI_FHD_30P,
	TVI_FHD_30P,
	TVI_FHD_30P
};
/*
// CVBS
unsigned char __fmtdef[4] = {
	AHD20_SD_H960_NT,
	AHD20_SD_H960_NT,
	AHD20_SD_H960_NT,
	AHD20_SD_H960_NT
};
*/
typedef struct _video_equalizer_info{
	unsigned char Ch;
	unsigned char devnum;
	unsigned char distance;
	unsigned char FmtDef;
} video_equalizer_info_s;

typedef struct _video_equalizer_base_s{
	unsigned char eq_bypass[11];			// B5x01
	unsigned char eq_band_sel[11];		// B5x58
	unsigned char eq_gain_sel[11];		// B5x5C

	unsigned char deq_a_on[11];			// BAx3d
	unsigned char deq_a_sel[11];			// BAx3C
	unsigned char deq_b_sel[11];			// B9x80

} video_equalizer_base_s;

typedef struct _video_equalizer_coeff_s{

	unsigned char deqA_01[11];	// BankA 0x30
	unsigned char deqA_02[11];	// BankA 0x31
	unsigned char deqA_03[11];   // BankA 0x32
	unsigned char deqA_04[11];   // BankA 0x33
	unsigned char deqA_05[11];   // BankA 0x34
	unsigned char deqA_06[11];   // BankA 0x35
	unsigned char deqA_07[11];   // BankA 0x36
	unsigned char deqA_08[11];   // BankA 0x37
	unsigned char deqA_09[11];   // BankA 0x38
	unsigned char deqA_10[11];   // BankA 0x39
	unsigned char deqA_11[11];   // BankA 0x3A
	unsigned char deqA_12[11];   // BankA 0x3B

} video_equalizer_coeff_s;

typedef struct _video_equalizer_color_s{
	unsigned char contrast[11];			// Bank0 0x10
	unsigned char h_peaking[11];			// Bank0 0x18
	unsigned char c_filter[11];			// Bank0 0x21
	unsigned char hue[11];				// Bank0 0x40
	unsigned char u_gain[11];			// Bank0 0x44
	unsigned char v_gain[11];			// Bank0 0x48
	unsigned char u_offset[11];			// Bank0 0x4c
	unsigned char v_offset[11];			// Bank0 0x50

	unsigned char black_level[11];		// Bank5 0x20
	unsigned char acc_ref[11];			// Bank5 0x27

	unsigned char cti_delay[11];			// Bank5 0x28
	unsigned char sub_saturation[11];    // Bank5 0x2B
	unsigned char burst_dec_a[11];       // Bank5 0x24
	unsigned char burst_dec_b[11];       // Bank5 0x5F
	unsigned char burst_dec_c[11];       // Bank5 0xD1
	unsigned char c_option[11];          // Bank5 0xD5

	unsigned char y_filter_b[11];		// BankA 0x25
	unsigned char y_filter_b_sel[11];	// BankA 0x27

} video_equalizer_color_s;

typedef struct _video_equalizer_timing_a_s{
	unsigned char h_delay_a[11];			// Bank0 0x58
	unsigned char h_delay_b[11];			// Bank0 0x89
	unsigned char h_delay_c[11];			// Bank0 0x8E
	unsigned char y_delay[11];			// Bank0 0xA0

} video_equalizer_timing_a_s;

typedef struct _video_equalizer_clk_s{
	unsigned char clk_adc[11];			// Bank1 0x84
	unsigned char clk_dec[11];			// Bank1 0x8C

} video_equalizer_clk_s;

typedef struct _video_equalizer_timing_b_s{
	unsigned char h_scaler1[11];		// B9x96 + ch*0x20
	unsigned char h_scaler2[11];		// B9x97 + ch*0x20
	unsigned char h_scaler3[11];		// B9x98 + ch*0x20
	unsigned char h_scaler4[11];		// B9x99 + ch*0x20
	unsigned char h_scaler5[11];		// B9x9a + ch*0x20
	unsigned char h_scaler6[11];		// B9x9b + ch*0x20
	unsigned char h_scaler7[11];		// B9x9c + ch*0x20
	unsigned char h_scaler8[11];		// B9x9d + ch*0x20
	unsigned char h_scaler9[11];		// B9x9e + ch*0x20

	unsigned char pn_auto[11];		// B9x40 + ch

	unsigned char comb_mode[11];		// B5x90
	unsigned char h_pll_op_a[11];	// B5xB9
	unsigned char mem_path[11];		// B5x57
	unsigned char fsc_lock_speed[11]; //B5x25

	unsigned char format_set1[11];	// B0x81
	unsigned char format_set2[11];	// B0x85

	unsigned char v_delay[11];		// B0x64
} video_equalizer_timing_b_s;

typedef struct _video_equalizer_value_table_s{
	video_equalizer_base_s		eq_base;
	video_equalizer_coeff_s 	eq_coeff;
	video_equalizer_color_s 	eq_color;

	video_equalizer_timing_a_s 	eq_timing_a;
	video_equalizer_clk_s		eq_clk;
	video_equalizer_timing_b_s	eq_timing_b;

} video_equalizer_value_table_s;

typedef struct _video_output_sequence
{
	unsigned char port;       // PORT_A, PORTB, PORTC, PORTD
	unsigned char ch01;			// [7:4] Sequence2 or 4, [3:0] Sequence1 or 3
	unsigned char ch23;			// [7:4] Sequence2 or 4, [3:0] Sequence1 or 3
	unsigned char devnum;
	unsigned char fmt;
}video_output_sequence;

typedef struct _video_output_data_out_mode{
	unsigned char ch;
	unsigned char devnum;
	unsigned char set_val;
}video_output_data_out_mode;

typedef struct _video_input_basic_hscaler_mode_init_s{
	unsigned char	h_down_scaler;	//B9		0x96/0xb6/0xd6/0xf6
	unsigned char	h_scaler_mode;	//B9	 	0x97/0xb7/0xd7/0xf7
	unsigned char	ref_base_lsb;	//B9		0x98/0xb8/0xd8/0xf8
	unsigned char	ref_base_msb;  	//B9		0x99/0xb9/0xd9/0xf9
	unsigned char	line_mem_mode;	//B0		0x34/0x35/0x36/0x37

	unsigned char reserved1;
	unsigned char reserved2;
	unsigned char reserved3;
	unsigned char reserved4;
	unsigned char reserved5;
	unsigned char reserved6;

}video_input_basic_hscaler_mode_init_s;

typedef struct _video_input_vafe{
	unsigned char powerdown;		//B0       0x00/1/2/3 [0]
	unsigned char gain;			//B0       0x00/1/2/3 [4]
	unsigned char spd;				//B5/6/7/8 0x00       [5:4]

	unsigned char ctrlreg;			//B5/6/7/8 0x01       [6]
	unsigned char ctrlibs;			//B5/6/7/8 0x01       [5:4]
	unsigned char adcspd;			//B5/6/7/8 0x01       [2]
	unsigned char clplevel;		//B5/6/7/8 0x01       [1:0]


	unsigned char eq_band;			//B5/6/7/8 0x58       [6:4]
	unsigned char lpf_front_band;	//B5/6/7/8 0x58       [1:0]

	unsigned char clpmode;			//B5/6/7/8 0x59       [7]
	unsigned char f_lpf_bypass;	//B5/6/7/8 0x59       [4]
	unsigned char clproff;			//B5/6/7/8 0x59       [3]
	unsigned char b_lpf_bypass;	//B5/6/7/8 0x59       [0]

	unsigned char duty;		   	//B5/6/7/8 0x5B    	  [6:4]
	unsigned char ref_vol;			//B5/6/7/8 0x5B       [1:0]

	unsigned char lpf_back_band;	//B5/6/7/8 0x5C       [6:4]
	unsigned char clk_sel;			//B5/6/7/8 0x5C       [3]
	unsigned char eq_gainsel;		//B5/6/7/8 0x5C       [2:0]

}video_input_vafe;

typedef struct _video_input_auto_detect{
	unsigned char ch;
	unsigned char devnum;

	unsigned char d_cmp;				//B5/6/7/8 0x03
	unsigned char slice_level;		//B5/6/7/8 0x08
	unsigned char control_mode;		//B5/6/7/8 0x47
	unsigned char gdf_fix_coeff;		//B5/6/7/8 0x50
	unsigned char dfe_ref_sel;		//B5/6/7/8 0x76
	unsigned char wpd_77;				//B5/6/7/8 0x77
	unsigned char wpd_78;				//B5/6/7/8 0x78
	unsigned char wpd_79;				//B5/6/7/8 0x79
	unsigned char auto_gnos_mode;		//B5/6/7/8 0x82
	unsigned char auto_sync_mode;		//B5/6/7/8 0x83
	unsigned char hafc_bypass;			//B5/6/7/8 0xB8

	unsigned char novid_vfc_init;	//B13		0x31
	unsigned char stable_mode_1;	//B13		0x0
	unsigned char stable_mode_2;	//B13		0x1

	unsigned char novid_det;		//B0		0x23/0x27/0x2B/0x2F
	video_input_vafe vafe;
}video_input_auto_detect;

video_input_basic_timing_init_s decoder_basic_timing_fmtdef[ NC_VIVO_CH_FORMATDEF_MAX ] =
{

		[ AHD20_SD_H960_2EX_Btype_NT ] = {
		    .sync_rs = 0x4,
		    .h_delay_lsb = 0x80,
		    .h_mask_on = 0x0,
		    .h_mask_sel = 0x0,
		    .mem_rdp = 0x0,
		    .v_blk_end_b = 0x0,
		    .y_delay = 0x12,
		    .fld_inv = 0x1,
		    .v_blk_end_a = 0x80,
		},

		[ AHD20_SD_H960_2EX_Btype_PAL ] = {
		    .sync_rs = 0x4,
		    .h_delay_lsb = 0x7C,
		    .h_mask_on = 0x0,
		    .h_mask_sel = 0x0,
		    .mem_rdp = 0x0,
		    .v_blk_end_b = 0x0,
		    .y_delay = 0x12,
		    .fld_inv = 0x0,
		    .v_blk_end_a = 0x80,
		},

		[ AHD20_SD_H960_NT ] = {
		    .sync_rs = 0x4,
		    .h_delay_lsb = 0x80,
		    .h_mask_on = 0x0,
		    .h_mask_sel = 0x0,
		    .mem_rdp = 0x0,
		    .v_blk_end_b = 0x0,
		    .y_delay = 0x12,
		    .fld_inv = 0x1,
		    .v_blk_end_a = 0x80,
		},

		[ AHD20_SD_H960_PAL ] = {
		    .sync_rs = 0x4,
		    .h_delay_lsb = 0x80,
		    .h_mask_on = 0x0,
		    .h_mask_sel = 0x0,
		    .mem_rdp = 0x0,
		    .v_blk_end_b = 0x0,
		    .y_delay = 0x12,
		    .fld_inv = 0x0,
		    .v_blk_end_a = 0x80,
		},

		[ AHD20_SD_H1280_NT ] = {
		    .sync_rs = 0x4,
		    .h_delay_lsb = 0x80,
		    .h_mask_on = 0x0,
		    .h_mask_sel = 0x0,
		    .mem_rdp = 0x0,
		    .v_blk_end_b = 0x0,
		    .y_delay = 0x12,
		    .fld_inv = 0x1,
		    .v_blk_end_a = 0x80,
		},

		[ AHD20_SD_H1280_PAL ] = {
		    .sync_rs = 0x4,
		    .h_delay_lsb = 0x80,
		    .h_mask_on = 0x0,
		    .h_mask_sel = 0x0,
		    .mem_rdp = 0x0,
		    .v_blk_end_b = 0x0,
		    .y_delay = 0x12,
		    .fld_inv = 0x0,
		    .v_blk_end_a = 0x80,
		},

		[ AHD20_SD_H1440_NT ] = {
		    .sync_rs = 0x4,
		    .h_delay_lsb = 0x80,
		    .h_mask_on = 0x0,
		    .h_mask_sel = 0x0,
		    .mem_rdp = 0x0,
		    .v_blk_end_b = 0x0,
		    .y_delay = 0x12,
		    .fld_inv = 0x1,
		    .v_blk_end_a = 0x80,
		},

		[ AHD20_SD_H1440_PAL ] = {
		    .sync_rs = 0x4,
		    .h_delay_lsb = 0x80,
		    .h_mask_on = 0x0,
		    .h_mask_sel = 0x0,
		    .mem_rdp = 0x0,
		    .v_blk_end_b = 0x0,
		    .y_delay = 0x12,
		    .fld_inv = 0x0,
		    .v_blk_end_a = 0x80,
		},

		[ AHD20_SD_H960_EX_NT ] = {
		    .sync_rs = 0x4,
		    .h_delay_lsb = 0x80,
		    .h_mask_on = 0x0,
		    .h_mask_sel = 0x0,
		    .mem_rdp = 0x0,
		    .v_blk_end_b = 0x0,
		    .y_delay = 0x12,
		    .fld_inv = 0x1,
		    .v_blk_end_a = 0x80,
		},

		[ AHD20_SD_H960_EX_PAL ] = {
		    .sync_rs = 0x4,
		    .h_delay_lsb = 0x80,
		    .h_mask_on = 0x0,
		    .h_mask_sel = 0x0,
		    .mem_rdp = 0x0,
		    .v_blk_end_b = 0x0,
		    .y_delay = 0x12,
		    .fld_inv = 0x0,
		    .v_blk_end_a = 0x80,
		},

		[ AHD20_SD_H960_2EX_NT ] = {
		    .sync_rs = 0x4,
		    .h_delay_lsb = 0x80,
		    .h_mask_on = 0x0,
		    .h_mask_sel = 0x0,
		    .mem_rdp = 0x0,
		    .v_blk_end_b = 0x0,
		    .y_delay = 0x12,
		    .fld_inv = 0x1,
		    .v_blk_end_a = 0x80,
		},

		[ AHD20_SD_H960_2EX_PAL ] = {
		    .sync_rs = 0x4,
		    .h_delay_lsb = 0x80,
		    .h_mask_on = 0x0,
		    .h_mask_sel = 0x0,
		    .mem_rdp = 0x0,
		    .v_blk_end_b = 0x0,
		    .y_delay = 0x12,
		    .fld_inv = 0x0,
		    .v_blk_end_a = 0x80,
		},

		[ AHD20_1080P_30P ] = {
		    .sync_rs = 0xEE,
		    .h_delay_lsb = 0x7C,
		    .h_mask_on = 0x10,
		    .h_mask_sel = 0x4,
		    .mem_rdp = 0x0,
		    .v_blk_end_b = 0x0,
		    .y_delay = 0x5,
		    .fld_inv = 0x0,
		    .v_blk_end_a = 0x80,
		},

		[ AHD20_1080P_25P ] = {
		    .sync_rs = 0xEE,
		    .h_delay_lsb = 0x88,
		    .h_mask_on = 0x10,
		    .h_mask_sel = 0x3,
		    .mem_rdp = 0x0,
		    .v_blk_end_b = 0x0,
		    .y_delay = 0x5,
		    .fld_inv = 0x0,
		    .v_blk_end_a = 0x80,
		},

		[ AHD20_960P_60P ] = {
		.sync_rs = 0xEE,
		.h_delay_lsb = 0x88,
		.h_mask_on = 0x10,
		.h_mask_sel = 0x3,
		.mem_rdp = 0x0,
		.v_blk_end_b = 0x0,
		.y_delay = 0x5,
		.fld_inv = 0x0,
		.v_blk_end_a = 0x80,
		},

		[ AHD20_960P_50P ] = {
		.sync_rs = 0xEE,
		.h_delay_lsb = 0x88,
		.h_mask_on = 0x10,
		.h_mask_sel = 0x3,
		.mem_rdp = 0x0,
		.v_blk_end_b = 0x0,
		.y_delay = 0x5,
		.fld_inv = 0x0,
		.v_blk_end_a = 0x80,
		},

		[ AHD20_960P_30P ] = {
		.sync_rs = 0xEE,
		.h_delay_lsb = 0x88,
		.h_mask_on = 0x10,
		.h_mask_sel = 0x3,
		.mem_rdp = 0x0,
		.v_blk_end_b = 0x0,
		.y_delay = 0x5,
		.fld_inv = 0x0,
		.v_blk_end_a = 0x80,
		},

		[ AHD20_960P_25P ] = {
		.sync_rs = 0xEE,
		.h_delay_lsb = 0x88,
		.h_mask_on = 0x10,
		.h_mask_sel = 0x3,
		.mem_rdp = 0x0,
		.v_blk_end_b = 0x0,
		.y_delay = 0x5,
		.fld_inv = 0x0,
		.v_blk_end_a = 0x80,
		},

		[ AHD20_1080P_60P ] = {
			.sync_rs = 0xEE,
			.h_delay_lsb = 0x7C,
			.h_mask_on = 0x10,
			.h_mask_sel = 0x4,
			.mem_rdp = 0x0,
			.v_blk_end_b = 0x0,
			.y_delay = 0x5,
			.fld_inv = 0x0,
			.v_blk_end_a = 0x80,
		},

		[ AHD20_1080P_50P ] = {
			.sync_rs = 0xEE,
			.h_delay_lsb = 0x88,
			.h_mask_on = 0x10,
			.h_mask_sel = 0x3,
			.mem_rdp = 0x0,
			.v_blk_end_b = 0x0,
			.y_delay = 0x5,
			.fld_inv = 0x0,
			.v_blk_end_a = 0x80,
		},


		[ AHD20_720P_60P ] = {
		    .sync_rs = 0xEE,
		    .h_delay_lsb = 0x80,
		    .h_mask_on = 0x0,
		    .h_mask_sel = 0x0,
		    .mem_rdp = 0x0,
		    .v_blk_end_b = 0x0,
		    .y_delay = 0x5,
		    .fld_inv = 0x0,
		    .v_blk_end_a = 0x80,
		},

		[ AHD20_720P_50P ] = {
		    .sync_rs = 0xEE,
		    .h_delay_lsb = 0x80,
		    .h_mask_on = 0x0,
		    .h_mask_sel = 0x0,
		    .mem_rdp = 0x0,
		    .v_blk_end_b = 0x0,
		    .y_delay = 0x5,
		    .fld_inv = 0x0,
		    .v_blk_end_a = 0x80,
		},

		[ AHD20_720P_30P ] = {
		    .sync_rs = 0xEE,
		    .h_delay_lsb = 0x80,
		    .h_mask_on = 0x0,
		    .h_mask_sel = 0x0,
		    .mem_rdp = 0x0,
		    .v_blk_end_b = 0x0,
		    .y_delay = 0x5,
		    .fld_inv = 0x0,
		    .v_blk_end_a = 0x80,
		},

		[ AHD20_720P_25P ] = {
		    .sync_rs = 0xEE,
		    .h_delay_lsb = 0x80,
		    .h_mask_on = 0x0,
		    .h_mask_sel = 0x0,
		    .mem_rdp = 0x0,
		    .v_blk_end_b = 0x0,
		    .y_delay = 0x5,
		    .fld_inv = 0x0,
		    .v_blk_end_a = 0x80,
		},

		[ AHD20_720P_30P_EX ] = {
		    .sync_rs = 0xEE,
		    .h_delay_lsb = 0x80,
		    .h_mask_on = 0x0,
		    .h_mask_sel = 0x0,
		    .mem_rdp = 0x0,
		    .v_blk_end_b = 0x0,
		    .y_delay = 0x5,
		    .fld_inv = 0x0,
		    .v_blk_end_a = 0x80,
		},

		[ AHD20_720P_25P_EX ] = {
		    .sync_rs = 0xEE,
		    .h_delay_lsb = 0x80,
		    .h_mask_on = 0x0,
		    .h_mask_sel = 0x0,
		    .mem_rdp = 0x0,
		    .v_blk_end_b = 0x0,
		    .y_delay = 0x5,
		    .fld_inv = 0x0,
		    .v_blk_end_a = 0x80,
		},

		[ AHD20_720P_30P_EX_Btype ] = {
		    .sync_rs = 0xEE,
		    .h_delay_lsb = 0x80,
		    .h_mask_on = 0x10,
		    .h_mask_sel = 0x5,
		    .mem_rdp = 0x0,
		    .v_blk_end_b = 0x0,
		    .y_delay = 0x12,
		    .fld_inv = 0x0,
		    .v_blk_end_a = 0x80,
		},

		[ AHD20_720P_25P_EX_Btype ] = {
		    .sync_rs = 0xEE,
		    .h_delay_lsb = 0x80,
		    .h_mask_on = 0x10,
		    .h_mask_sel = 0x5,
		    .mem_rdp = 0x0,
		    .v_blk_end_b = 0x0,
		    .y_delay = 0x13,
		    .fld_inv = 0x0,
		    .v_blk_end_a = 0x80,
		},

		[ AHD30_3M_30P ] = {
		    .sync_rs = 0xEE,
		    .h_delay_lsb = 0x83,
		    .h_mask_on = 0x10,
		    .h_mask_sel = 0x3,
		    .mem_rdp = 0x0,
		    .v_blk_end_b = 0x0,
		    .y_delay = 0x3,
		    .fld_inv = 0x0,
		    .v_blk_end_a = 0x80,
		},

		[ AHD30_3M_25P ] = {
		    .sync_rs = 0xEE,
		    .h_delay_lsb = 0x80,
		    .h_mask_on = 0x10,
		    .h_mask_sel = 0x3,
		    .mem_rdp = 0x0,
		    .v_blk_end_b = 0x0,
		    .y_delay = 0x3,
		    .fld_inv = 0x0,
		    .v_blk_end_a = 0x80,
		},

		[ AHD30_3M_18P ] = {
		    .sync_rs = 0xEE,
		    .h_delay_lsb = 0x80,
		    .h_mask_on = 0x10,
		    .h_mask_sel = 0x4,
		    .mem_rdp = 0x0,
		    .v_blk_end_b = 0x0,
		    .y_delay = 0x4,
		    .fld_inv = 0x0,
		    .v_blk_end_a = 0x80,
		},

		[ AHD30_4M_30P ] = {
		    .sync_rs = 0xEE,
		    .h_delay_lsb = 0x80,
		    .h_mask_on = 0x10,
		    .h_mask_sel = 0x2,
		    .mem_rdp = 0x0,
		    .v_blk_end_b = 0x0,
		    .y_delay = 0x5,
		    .fld_inv = 0x0,
		    .v_blk_end_a = 0x80,
		},

		[ AHD30_4M_25P ] = {
		    .sync_rs = 0xEE,
		    .h_delay_lsb = 0x80,
		    .h_mask_on = 0x10,
		    .h_mask_sel = 0x2,
		    .mem_rdp = 0x0,
		    .v_blk_end_b = 0x0,
		    .y_delay = 0x5,
		    .fld_inv = 0x0,
		    .v_blk_end_a = 0x80,
		},

		[ AHD30_4M_15P ] = {
		    .sync_rs = 0xEE,
		    .h_delay_lsb = 0x72,
		    .h_mask_on = 0x0,
		    .h_mask_sel = 0x0,
		    .mem_rdp = 0x0,
		    .v_blk_end_b = 0x0,
		    .y_delay = 0x5,
		    .fld_inv = 0x0,
		    .v_blk_end_a = 0x80,
		},

	        [ AHD30_5M_20P ] = {
		    .sync_rs = 0xEE,
		    .h_delay_lsb = 0x80,
		    .h_mask_on = 0x10,
		    .h_mask_sel = 0x2,
		    .mem_rdp = 0x0,
		    .v_blk_end_b = 0x0,
		    .y_delay = 0x5,
		    .fld_inv = 0x0,
		    .v_blk_end_a = 0x80,
		},

		[ AHD30_5M_12_5P ] = {
		    .sync_rs = 0xEE,
		    .h_delay_lsb = 0x83,
		    .h_mask_on = 0x10,
		    .h_mask_sel = 0x2,
		    .mem_rdp = 0x0,
		    .v_blk_end_b = 0x0,
		    .y_delay = 0x5,
		    .fld_inv = 0x0,
		    .v_blk_end_a = 0x80,
		},

	        [ AHD30_8M_X_30P ] = {
		    .sync_rs = 0xEE,
		    .h_delay_lsb = 0x80,
		    .h_mask_on = 0x0,
		    .h_mask_sel = 0x0,
		    .mem_rdp = 0x0,
		    .v_blk_end_b = 0x0,
		    .y_delay = 0x5,
		    .fld_inv = 0x0,
		    .v_blk_end_a = 0x80,
		},

		[ AHD30_8M_X_25P ] = {
		    .sync_rs = 0xEE,
		    .h_delay_lsb = 0x80,
		    .h_mask_on = 0x0,
		    .h_mask_sel = 0x0,
		    .mem_rdp = 0x0,
		    .v_blk_end_b = 0x0,
		    .y_delay = 0x5,
		    .fld_inv = 0x0,
		    .v_blk_end_a = 0x80,
		},

		[ AHD30_5_3M_20P ] = {
		    .sync_rs = 0xEE,
		    .h_delay_lsb = 0x80,
		    .h_mask_on = 0x1,
		    .h_mask_sel = 0x2,
		    .mem_rdp = 0x0,
		    .v_blk_end_b = 0x0,
		    .y_delay = 0x5,
		    .fld_inv = 0x0,
		    .v_blk_end_a = 0x80,
		},

		[ AHD30_6M_18P ] = {
		    .sync_rs = 0xEE,
		    .h_delay_lsb = 0x80,
		    .h_mask_on = 0x0,
		    .h_mask_sel = 0x0,
		    .mem_rdp = 0x0,
		    .v_blk_end_b = 0x0,
		    .y_delay = 0x5,
		    .fld_inv = 0x0,
		    .v_blk_end_a = 0x80,
		},

		[ AHD30_6M_20P ] = {
		    .sync_rs = 0xEE,
		    .h_delay_lsb = 0x80,
		    .h_mask_on = 0x0,
		    .h_mask_sel = 0x0,
		    .mem_rdp = 0x0,
		    .v_blk_end_b = 0x0,
		    .y_delay = 0x5,
		    .fld_inv = 0x0,
		    .v_blk_end_a = 0x80,
		},

		[ AHD30_8M_7_5P ] = {
		    .sync_rs = 0xEE,
		    .h_delay_lsb = 0x80,
		    .h_mask_on = 0x0,
		    .h_mask_sel = 0x0,
		    .mem_rdp = 0x0,
		    .v_blk_end_b = 0x0,
		    .y_delay = 0x5,
		    .fld_inv = 0x0,
		    .v_blk_end_a = 0x80,
		},

		[ AHD30_8M_12_5P ] = {
		    .sync_rs = 0xEE,
		    .h_delay_lsb = 0x80,
		    .h_mask_on = 0x1,
		    .h_mask_sel = 0x2,
		    .mem_rdp = 0x0,
		    .v_blk_end_b = 0x0,
		    .y_delay = 0x5,
		    .fld_inv = 0x0,
		    .v_blk_end_a = 0x80,
		},

		[ AHD30_8M_15P ] = {
		    .sync_rs = 0xEE,
		    .h_delay_lsb = 0x80,
		    .h_mask_on = 0x0,
		    .h_mask_sel = 0x0,
		    .mem_rdp = 0x0,
		    .v_blk_end_b = 0x0,
		    .y_delay = 0x5,
		    .fld_inv = 0x0,
		    .v_blk_end_a = 0x80,
		},

		[ TVI_FHD_30P ] = {
		    .sync_rs = 0xEE,
		    .h_delay_lsb = 0x80,
		    .h_mask_on = 0x10,
		    .h_mask_sel = 0x2,
		    .mem_rdp = 0x0,
		    .v_blk_end_b = 0x0,
		    .y_delay = 0x5,
		    .fld_inv = 0x0,
		    .v_blk_end_a = 0x80,
		},

		[ TVI_FHD_25P ] = {
		    .sync_rs = 0xEE,
		    .h_delay_lsb = 0x88,
		    .h_mask_on = 0x10,
		    .h_mask_sel = 0x0,
		    .mem_rdp = 0x0,
		    .v_blk_end_b = 0x0,
		    .y_delay = 0x5,
		    .fld_inv = 0x0,
		    .v_blk_end_a = 0x80,
		},

		[ TVI_HD_60P ] = {
		    .sync_rs = 0xEE,
		    .h_delay_lsb = 0x80,
		    .h_mask_on = 0x0,
		    .h_mask_sel = 0x0,
		    .mem_rdp = 0x0,
		    .v_blk_end_b = 0x0,
		    .y_delay = 0x5,
		    .fld_inv = 0x0,
		    .v_blk_end_a = 0x80,
		},

		[ TVI_HD_50P ] = {
		    .sync_rs = 0xEE,
		    .h_delay_lsb = 0x80,
		    .h_mask_on = 0x0,
		    .h_mask_sel = 0x0,
		    .mem_rdp = 0x0,
		    .v_blk_end_b = 0x0,
		    .y_delay = 0x5,
		    .fld_inv = 0x0,
		    .v_blk_end_a = 0x80,
		},

		[ TVI_HD_30P ] = {
		    .sync_rs = 0xEE,
		    .h_delay_lsb = 0x80,
		    .h_mask_on = 0x0,
		    .h_mask_sel = 0x0,
		    .mem_rdp = 0x24,
		    .v_blk_end_b = 0x0,
		    .y_delay = 0x5,
		    .fld_inv = 0x0,
		    .v_blk_end_a = 0x80,
		},

		[ TVI_HD_25P ] = {
		    .sync_rs = 0xEE,
		    .h_delay_lsb = 0x80,
		    .h_mask_on = 0x0,
		    .h_mask_sel = 0x20,
		    .mem_rdp = 0x24,
		    .v_blk_end_b = 0x0,
		    .y_delay = 0x5,
		    .fld_inv = 0x0,
		    .v_blk_end_a = 0x80,
		},

		[ TVI_HD_30P_EX ] = {
		    .sync_rs = 0xEE,
		    .h_delay_lsb = 0x80,
		    .h_mask_on = 0x10,
		    .h_mask_sel = 0x5,
		    .mem_rdp = 0x0,
		    .v_blk_end_b = 0x0,
		    .y_delay = 0x5,
		    .fld_inv = 0x0,
		    .v_blk_end_a = 0x80,
		},

		[ TVI_HD_25P_EX ] = {
		    .sync_rs = 0xEE,
		    .h_delay_lsb = 0x70,
		    .h_mask_on = 0x0,
		    .h_mask_sel = 0x0,
		    .mem_rdp = 0x0,
		    .v_blk_end_b = 0x0,
		    .y_delay = 0x5,
		    .fld_inv = 0x0,
		    .v_blk_end_a = 0x80,
		},

		[ TVI_HD_B_30P ] = {
		    .sync_rs = 0xEE,
		    .h_delay_lsb = 0x80,
		    .h_mask_on = 0x0,
		    .h_mask_sel = 0x0,
		    .mem_rdp = 0x0,
		    .v_blk_end_b = 0x0,
		    .y_delay = 0x5,
		    .fld_inv = 0x0,
		    .v_blk_end_a = 0x80,
		},

		[ TVI_HD_B_25P ] = {
		    .sync_rs = 0xEE,
		    .h_delay_lsb = 0x80,
		    .h_mask_on = 0x0,
		    .h_mask_sel = 0x0,
		    .mem_rdp = 0x0,
		    .v_blk_end_b = 0x0,
		    .y_delay = 0x5,
		    .fld_inv = 0x0,
		    .v_blk_end_a = 0x80,
		},

		[ TVI_HD_B_30P_EX ] = {
		    .sync_rs = 0xEE,
		    .h_delay_lsb = 0x80,
		    .h_mask_on = 0x0,
		    .h_mask_sel = 0x0,
		    .mem_rdp = 0x0,
		    .v_blk_end_b = 0x0,
		    .y_delay = 0x5,
		    .fld_inv = 0x0,
		    .v_blk_end_a = 0x80,
		},

		[ TVI_HD_B_25P_EX ] = {
		    .sync_rs = 0xEE,
		    .h_delay_lsb = 0x80,
		    .h_mask_on = 0x0,
		    .h_mask_sel = 0x0,
		    .mem_rdp = 0x0,
		    .v_blk_end_b = 0x0,
		    .y_delay = 0x5,
		    .fld_inv = 0x0,
		    .v_blk_end_a = 0x80,
		},

		[ TVI_3M_18P ] = {
		    .sync_rs = 0xEE,
		    .h_delay_lsb = 0x80,
		    .h_mask_on = 0x10,
		    .h_mask_sel = 0x2,
		    .mem_rdp = 0x0,
		    .v_blk_end_b = 0x0,
		    .y_delay = 0x5,
		    .fld_inv = 0x0,
		    .v_blk_end_a = 0x80,
		},

		[ TVI_5M_12_5P  ] = {
		    .sync_rs = 0xEE,
		    .h_delay_lsb = 0x7B,
		    .h_mask_on = 0x0,
		    .h_mask_sel = 0x0,
		    .mem_rdp = 0x0,
		    .v_blk_end_b = 0x0,
		    .y_delay = 0x5,
		    .fld_inv = 0x0,
		    .v_blk_end_a = 0x80,
		},

		[ TVI_5M_20P ] = {
			.sync_rs = 0xEE,
			.h_delay_lsb = 0x80,
			.h_mask_on = 0x00,
			.h_mask_sel = 0x00,
			.mem_rdp = 0x0,
			.v_blk_end_b = 0x0,
			.y_delay = 0x15,
			.fld_inv = 0x0,
			.v_blk_end_a = 0x80,
		},

		[ TVI_4M_30P ] = {
		    .sync_rs = 0xEE,
		    .h_delay_lsb = 0x80,
		    .h_mask_on = 0x10,
		    .h_mask_sel = 0x2,
		    .mem_rdp = 0x0,
		    .v_blk_end_b = 0x0,
		    .y_delay = 0x7,
		    .fld_inv = 0x0,
		    .v_blk_end_a = 0x80,
		},

		[ TVI_4M_25P ] = {
		    .sync_rs = 0xEE,
		    .h_delay_lsb = 0x80,
		    .h_mask_on = 0x10,
		    .h_mask_sel = 0x2,
		    .mem_rdp = 0x0,
		    .v_blk_end_b = 0x0,
		    .y_delay = 0x7,
		    .fld_inv = 0x0,
		    .v_blk_end_a = 0x80,
		},

		[ CVI_FHD_30P ] = {
		    .sync_rs = 0xEE,
		    .h_delay_lsb = 0x80,
		    .h_mask_on = 0x10,
		    .h_mask_sel = 0x4,
		    .mem_rdp = 0x21,
		    .v_blk_end_b = 0x0,
		    .y_delay = 0x5,
		    .fld_inv = 0x0,
		    .v_blk_end_a = 0x80,
		},

		[ CVI_FHD_25P ] = {
		    .sync_rs = 0xEE,
		    .h_delay_lsb = 0x80,
		    .h_mask_on = 0x10,
		    .h_mask_sel = 0x2,
		    .mem_rdp = 0x22,
		    .v_blk_end_b = 0x0,
		    .y_delay = 0x5,
		    .fld_inv = 0x0,
		    .v_blk_end_a = 0x80,
		},

		[ CVI_HD_60P ] = {
		    .sync_rs = 0xEE,
		    .h_delay_lsb = 0x80,
		    .h_mask_on = 0x0,
		    .h_mask_sel = 0x0,
		    .mem_rdp = 0x0,
		    .v_blk_end_b = 0x0,
		    .y_delay = 0x5,
		    .fld_inv = 0x0,
		    .v_blk_end_a = 0x80,
		},

		[ CVI_HD_50P ] = {
		    .sync_rs = 0xEE,
		    .h_delay_lsb = 0x80,
		    .h_mask_on = 0x0,
		    .h_mask_sel = 0x0,
		    .mem_rdp = 0x0,
		    .v_blk_end_b = 0x0,
		    .y_delay = 0x5,
		    .fld_inv = 0x0,
		    .v_blk_end_a = 0x80,
		},

		[ CVI_HD_30P ] = {
		    .sync_rs = 0xEE,
		    .h_delay_lsb = 0x80,
		    .h_mask_on = 0x0,
		    .h_mask_sel = 0x0,
		    .mem_rdp = 0x0,
		    .v_blk_end_b = 0x0,
		    .y_delay = 0x5,
		    .fld_inv = 0x0,
		    .v_blk_end_a = 0x80,
		},

		[ CVI_HD_25P ] = {
		    .sync_rs = 0xEE,
		    .h_delay_lsb = 0x80,
		    .h_mask_on = 0x0,
		    .h_mask_sel = 0x0,
		    .mem_rdp = 0x0,
		    .v_blk_end_b = 0x0,
		    .y_delay = 0x5,
		    .fld_inv = 0x0,
		    .v_blk_end_a = 0x80,
		},

		[ CVI_HD_30P_EX ] = {
		    .sync_rs = 0xEE,
		    .h_delay_lsb = 0x80,
		    .h_mask_on = 0x10,
		    .h_mask_sel = 0x5,
		    .mem_rdp = 0x0,
		    .v_blk_end_b = 0x0,
		    .y_delay = 0x5,
		    .fld_inv = 0x0,
		    .v_blk_end_a = 0x80,
		},

		[ CVI_HD_25P_EX ] = {
		    .sync_rs = 0xEE,
		    .h_delay_lsb = 0x80,
		    .h_mask_on = 0x10,
		    .h_mask_sel = 0x1,
		    .mem_rdp = 0x0,
		    .v_blk_end_b = 0x0,
		    .y_delay = 0x5,
		    .fld_inv = 0x0,
		    .v_blk_end_a = 0x80,
		},

		[ CVI_4M_30P ] = {
		    .sync_rs = 0xEE,
		    .h_delay_lsb = 0x80,
		    .h_mask_on = 0x1,
		    .h_mask_sel = 0x2,
		    .mem_rdp = 0x0,
		    .v_blk_end_b = 0x0,
		    .y_delay = 0x5,
		    .fld_inv = 0x0,
		    .v_blk_end_a = 0x80,
		},

		[ CVI_4M_25P ] = {
		    .sync_rs = 0xEE,
		    .h_delay_lsb = 0x80,
		    .h_mask_on = 0x1,
		    .h_mask_sel = 0x2,
		    .mem_rdp = 0x0,
		    .v_blk_end_b = 0x0,
		    .y_delay = 0x5,
		    .fld_inv = 0x0,
		    .v_blk_end_a = 0x80,
		},

		[ CVI_8M_12_5P ] = {
		    .sync_rs = 0xEE,
		    .h_delay_lsb = 0x80,
		    .h_mask_on = 0x1,
		    .h_mask_sel = 0x2,
		    .mem_rdp = 0x0,
		    .v_blk_end_b = 0x0,
		    .y_delay = 0x5,
		    .fld_inv = 0x0,
		    .v_blk_end_a = 0x80,
		},

		[ CVI_8M_15P ] = {
		    .sync_rs = 0xEE,
		    .h_delay_lsb = 0x80,
		    .h_mask_on = 0x1,
		    .h_mask_sel = 0x2,
		    .mem_rdp = 0x0,
		    .v_blk_end_b = 0x0,
		    .y_delay = 0x5,
		    .fld_inv = 0x0,
		    .v_blk_end_a = 0x80,
		},

};


video_input_basic_hscaler_mode_init_s decoder_basic_hscaler_fmtdef[ NC_VIVO_CH_FORMATDEF_MAX ] =
{

		[ AHD20_SD_H960_2EX_Btype_NT ] = {
		    .h_down_scaler = 0x10,
		    .h_scaler_mode = 0x10,
		    .ref_base_lsb = 0x0,
		    .ref_base_msb = 0x0,
		    .line_mem_mode = 0x1,
		},

		[ AHD20_SD_H960_2EX_Btype_PAL ] = {
		    .h_down_scaler = 0x10,
		    .h_scaler_mode = 0x10,
		    .ref_base_lsb = 0x0,
		    .ref_base_msb = 0x0,
		    .line_mem_mode = 0x1,
		},

		[ AHD20_SD_H960_NT ] = {
		    .h_down_scaler = 0x0,
		    .h_scaler_mode = 0x0,
		    .ref_base_lsb = 0x0,
		    .ref_base_msb = 0x0,
		    .line_mem_mode = 0x0,
		},

		[ AHD20_SD_H960_PAL ] = {
		    .h_down_scaler = 0x0,
		    .h_scaler_mode = 0x0,
		    .ref_base_lsb = 0x0,
		    .ref_base_msb = 0x0,
		    .line_mem_mode = 0x0,
		},

		[ AHD20_SD_H1280_NT ] = {
		    .h_down_scaler = 0x0,
		    .h_scaler_mode = 0x0,
		    .ref_base_lsb = 0x0,
		    .ref_base_msb = 0x0,
		    .line_mem_mode = 0x0,
		},

		[ AHD20_SD_H1280_PAL ] = {
		    .h_down_scaler = 0x0,
		    .h_scaler_mode = 0x0,
		    .ref_base_lsb = 0x0,
		    .ref_base_msb = 0x0,
		    .line_mem_mode = 0x0,
		},

		[ AHD20_SD_H1440_NT ] = {
		    .h_down_scaler = 0x0,
		    .h_scaler_mode = 0x0,
		    .ref_base_lsb = 0x0,
		    .ref_base_msb = 0x0,
		    .line_mem_mode = 0x0,
		},

		[ AHD20_SD_H1440_PAL ] = {
		    .h_down_scaler = 0x0,
		    .h_scaler_mode = 0x0,
		    .ref_base_lsb = 0x0,
		    .ref_base_msb = 0x0,
		    .line_mem_mode = 0x0,
		},

		[ AHD20_SD_H960_EX_NT ] = {
		    .h_down_scaler = 0x0,
		    .h_scaler_mode = 0x0,
		    .ref_base_lsb = 0x0,
		    .ref_base_msb = 0x0,
		    .line_mem_mode = 0x0,
		},

		[ AHD20_SD_H960_EX_PAL ] = {
		    .h_down_scaler = 0x0,
		    .h_scaler_mode = 0x0,
		    .ref_base_lsb = 0x0,
		    .ref_base_msb = 0x0,
		    .line_mem_mode = 0x0,
		},

		[ AHD20_SD_H960_2EX_NT ] = {
		    .h_down_scaler = 0x0,
		    .h_scaler_mode = 0x0,
		    .ref_base_lsb = 0x0,
		    .ref_base_msb = 0x0,
		    .line_mem_mode = 0x0,
		},

		[ AHD20_SD_H960_2EX_PAL ] = {
		    .h_down_scaler = 0x0,
		    .h_scaler_mode = 0x0,
		    .ref_base_lsb = 0x0,
		    .ref_base_msb = 0x0,
		    .line_mem_mode = 0x0,
		},

		[ AHD20_1080P_30P ] = {
		    .h_down_scaler = 0x0,
		    .h_scaler_mode = 0x0,
		    .ref_base_lsb = 0x0,
		    .ref_base_msb = 0x0,
		    .line_mem_mode = 0x0,
		},

		[ AHD20_1080P_25P ] = {
		    .h_down_scaler = 0x0,
		    .h_scaler_mode = 0x0,
		    .ref_base_lsb = 0x0,
		    .ref_base_msb = 0x0,
		    .line_mem_mode = 0x0,
		},
		[ AHD20_960P_60P ] = {
		.h_down_scaler = 0x0,
		.h_scaler_mode = 0x0,
		.ref_base_lsb = 0x0,
		.ref_base_msb = 0x0,
		.line_mem_mode = 0x0,
		},
		[ AHD20_960P_50P ] = {
		.h_down_scaler = 0x0,
		.h_scaler_mode = 0x0,
		.ref_base_lsb = 0x0,
		.ref_base_msb = 0x0,
		.line_mem_mode = 0x0,
		},
		[ AHD20_960P_30P ] = {
		.h_down_scaler = 0x0,
		.h_scaler_mode = 0x0,
		.ref_base_lsb = 0x0,
		.ref_base_msb = 0x0,
		.line_mem_mode = 0x0,
		},
		[ AHD20_960P_25P ] = {
		.h_down_scaler = 0x0,
		.h_scaler_mode = 0x0,
		.ref_base_lsb = 0x0,
		.ref_base_msb = 0x0,
		.line_mem_mode = 0x0,
		},


		[ AHD20_1080P_60P ] = {
			.h_down_scaler = 0x0,
			.h_scaler_mode = 0x0,
			.ref_base_lsb = 0x0,
			.ref_base_msb = 0x0,
			.line_mem_mode = 0x0,
		},

		[ AHD20_1080P_50P ] = {
			.h_down_scaler = 0x0,
			.h_scaler_mode = 0x0,
			.ref_base_lsb = 0x0,
			.ref_base_msb = 0x0,
			.line_mem_mode = 0x0,
		},

		[ AHD20_720P_60P ] = {
		    .h_down_scaler = 0x0,
		    .h_scaler_mode = 0x0,
		    .ref_base_lsb = 0x0,
		    .ref_base_msb = 0x0,
		    .line_mem_mode = 0x0,
		},

		[ AHD20_720P_50P ] = {
		    .h_down_scaler = 0x0,
		    .h_scaler_mode = 0x0,
		    .ref_base_lsb = 0x0,
		    .ref_base_msb = 0x0,
		    .line_mem_mode = 0x0,
		},

		[ AHD20_720P_30P ] = {
		    .h_down_scaler = 0x0,
		    .h_scaler_mode = 0x0,
		    .ref_base_lsb = 0x0,
		    .ref_base_msb = 0x0,
		    .line_mem_mode = 0x0,
		},

		[ AHD20_720P_25P ] = {
		    .h_down_scaler = 0x0,
		    .h_scaler_mode = 0x0,
		    .ref_base_lsb = 0x0,
		    .ref_base_msb = 0x0,
		    .line_mem_mode = 0x0,
		},

		[ AHD20_720P_30P_EX ] = {
		    .h_down_scaler = 0x0,
		    .h_scaler_mode = 0x0,
		    .ref_base_lsb = 0x0,
		    .ref_base_msb = 0x0,
		    .line_mem_mode = 0x0,
		},

		[ AHD20_720P_25P_EX ] = {
		    .h_down_scaler = 0x0,
		    .h_scaler_mode = 0x0,
		    .ref_base_lsb = 0x0,
		    .ref_base_msb = 0x0,
		    .line_mem_mode = 0x0,
		},

		[ AHD20_720P_30P_EX_Btype ] = {
		    .h_down_scaler = 0x0,
		    .h_scaler_mode = 0x0,
		    .ref_base_lsb = 0x0,
		    .ref_base_msb = 0x0,
		    .line_mem_mode = 0x1,
		},

		[ AHD20_720P_25P_EX_Btype ] = {
		    .h_down_scaler = 0x0,
		    .h_scaler_mode = 0x0,
		    .ref_base_lsb = 0x0,
		    .ref_base_msb = 0x0,
		    .line_mem_mode = 0x1,
		},

		[ AHD30_3M_30P ] = {
		    .h_down_scaler = 0x0,
		    .h_scaler_mode = 0x0,
		    .ref_base_lsb = 0x0,
		    .ref_base_msb = 0x0,
		    .line_mem_mode = 0x0,
		},

		[ AHD30_3M_25P ] = {
		    .h_down_scaler = 0x0,
		    .h_scaler_mode = 0x0,
		    .ref_base_lsb = 0x0,
		    .ref_base_msb = 0x0,
		    .line_mem_mode = 0x0,
		},

		[ AHD30_3M_18P ] = {
		    .h_down_scaler = 0x0,
		    .h_scaler_mode = 0x0,
		    .ref_base_lsb = 0x0,
		    .ref_base_msb = 0x0,
		    .line_mem_mode = 0x0,
		},

		[ AHD30_4M_30P ] = {
		    .h_down_scaler = 0x0,
		    .h_scaler_mode = 0x0,
		    .ref_base_lsb = 0x0,
		    .ref_base_msb = 0x0,
		    .line_mem_mode = 0x0,
		},

		[ AHD30_4M_25P ] = {
		    .h_down_scaler = 0x0,
		    .h_scaler_mode = 0x0,
		    .ref_base_lsb = 0x0,
		    .ref_base_msb = 0x0,
		    .line_mem_mode = 0x0,
		},

		[ AHD30_4M_15P ] = {
		    .h_down_scaler = 0x0,
		    .h_scaler_mode = 0x0,
		    .ref_base_lsb = 0x0,
		    .ref_base_msb = 0x0,
		    .line_mem_mode = 0x0,
		},

		[ AHD30_5M_20P ] = {
		    .h_down_scaler = 0x0,
		    .h_scaler_mode = 0x0,
		    .ref_base_lsb = 0x0,
		    .ref_base_msb = 0x0,
		    .line_mem_mode = 0x0,
		},

		[ AHD30_5M_12_5P ] = {
		    .h_down_scaler = 0x0,
		    .h_scaler_mode = 0x0,
		    .ref_base_lsb = 0x0,
		    .ref_base_msb = 0x0,
		    .line_mem_mode = 0x0,
		},

	        [ AHD30_8M_X_30P ] = {
		    .h_down_scaler = 0x0,
		    .h_scaler_mode = 0x0,
		    .ref_base_lsb = 0x0,
		    .ref_base_msb = 0x0,
		    .line_mem_mode = 0x0,
		},

		[ AHD30_8M_X_25P ] = {
		    .h_down_scaler = 0x0,
		    .h_scaler_mode = 0x0,
		    .ref_base_lsb = 0x0,
		    .ref_base_msb = 0x0,
		    .line_mem_mode = 0x0,
		},
		[ AHD30_5_3M_20P ] = {
		    .h_down_scaler = 0x0,
		    .h_scaler_mode = 0x0,
		    .ref_base_lsb = 0x0,
		    .ref_base_msb = 0x0,
		    .line_mem_mode = 0x0,
		},

		[ AHD30_6M_18P ] = {
		    .h_down_scaler = 0x0,
		    .h_scaler_mode = 0x0,
		    .ref_base_lsb = 0x0,
		    .ref_base_msb = 0x0,
		    .line_mem_mode = 0x0,
		},

		[ AHD30_6M_20P ] = {
		    .h_down_scaler = 0x0,
		    .h_scaler_mode = 0x0,
		    .ref_base_lsb = 0x0,
		    .ref_base_msb = 0x0,
		    .line_mem_mode = 0x0,
		},

		[ AHD30_8M_7_5P ] = {
		    .h_down_scaler = 0x0,
		    .h_scaler_mode = 0x0,
		    .ref_base_lsb = 0x0,
		    .ref_base_msb = 0x0,
		    .line_mem_mode = 0x0,
		},

		[ AHD30_8M_12_5P ] = {
		    .h_down_scaler = 0x0,
		    .h_scaler_mode = 0x0,
		    .ref_base_lsb = 0x0,
		    .ref_base_msb = 0x0,
		    .line_mem_mode = 0x0,
		},

		[ AHD30_8M_15P ] = {
		    .h_down_scaler = 0x0,
		    .h_scaler_mode = 0x0,
		    .ref_base_lsb = 0x0,
		    .ref_base_msb = 0x0,
		    .line_mem_mode = 0x0,
		},

		[ TVI_FHD_30P ] = {
		    .h_down_scaler = 0x1,
		    .h_scaler_mode = 0x0,
		    .ref_base_lsb = 0x0,
		    .ref_base_msb = 0x0,
		    .line_mem_mode = 0x0,
		},

		[ TVI_FHD_25P ] = {
		    .h_down_scaler = 0x1,
		    .h_scaler_mode = 0x0,
		    .ref_base_lsb = 0x0,
		    .ref_base_msb = 0x0,
		    .line_mem_mode = 0x0,
		},

		[ TVI_HD_60P ] = {
		    .h_down_scaler = 0x1,
		    .h_scaler_mode = 0x0,
		    .ref_base_lsb = 0x0,
		    .ref_base_msb = 0x0,
		    .line_mem_mode = 0x0,
		},

		[ TVI_HD_50P ] = {
		    .h_down_scaler = 0x1,
		    .h_scaler_mode = 0x0,
		    .ref_base_lsb = 0x0,
		    .ref_base_msb = 0x0,
		    .line_mem_mode = 0x0,
		},

		[ TVI_HD_30P ] = {
		    .h_down_scaler = 0x1,
		    .h_scaler_mode = 0x59,
		    .ref_base_lsb = 0x0,
		    .ref_base_msb = 0x0,
		    .line_mem_mode = 0x0,
		},

		[ TVI_HD_25P ] = {
		    .h_down_scaler = 0x1,
		    .h_scaler_mode = 0x59,
		    .ref_base_lsb = 0xc0,
		    .ref_base_msb = 0x01,
		    .line_mem_mode = 0x0,
		},

		[ TVI_HD_30P_EX ] = {
		    .h_down_scaler = 0x1,
		    .h_scaler_mode = 0x59,
		    .ref_base_lsb = 0x0,
		    .ref_base_msb = 0x0,
		    .line_mem_mode = 0x0,
		},

		[ TVI_HD_25P_EX ] = {
		    .h_down_scaler = 0x1,
		    .h_scaler_mode = 0x59,
		    .ref_base_lsb = 0x0,
		    .ref_base_msb = 0x0,
		    .line_mem_mode = 0x0,
		},

		[ TVI_HD_B_30P ] = {
		    .h_down_scaler = 0x0,
		    .h_scaler_mode = 0x0,
		    .ref_base_lsb = 0x0,
		    .ref_base_msb = 0x0,
		    .line_mem_mode = 0x0,
		},

		[ TVI_HD_B_25P ] = {
		    .h_down_scaler = 0x0,
		    .h_scaler_mode = 0x0,
		    .ref_base_lsb = 0x0,
		    .ref_base_msb = 0x0,
		    .line_mem_mode = 0x0,
		},

		[ TVI_HD_B_30P_EX ] = {
		    .h_down_scaler = 0x0,
		    .h_scaler_mode = 0x0,
		    .ref_base_lsb = 0x0,
		    .ref_base_msb = 0x0,
		    .line_mem_mode = 0x0,
		},

		[ TVI_HD_B_25P_EX ] = {
		    .h_down_scaler = 0x0,
		    .h_scaler_mode = 0x0,
		    .ref_base_lsb = 0x0,
		    .ref_base_msb = 0x0,
		    .line_mem_mode = 0x0,
		},

		[ TVI_3M_18P ] = {
		    .h_down_scaler = 0x0,
		    .h_scaler_mode = 0x0,
		    .ref_base_lsb = 0x0,
		    .ref_base_msb = 0x0,
		    .line_mem_mode = 0x0,
		},

		[ TVI_5M_12_5P  ] = {
		    .h_down_scaler = 0x0,
		    .h_scaler_mode = 0x0,
		    .ref_base_lsb = 0x0,
		    .ref_base_msb = 0x0,
		    .line_mem_mode = 0x0,
		},

		[ TVI_5M_20P ] = {
			.h_down_scaler = 0x0,
			.h_scaler_mode = 0x0,
			.ref_base_lsb = 0x0,
			.ref_base_msb = 0x0,
			.line_mem_mode = 0x0,
		},

		[ TVI_4M_30P ] = {
		    .h_down_scaler = 0x0,
		    .h_scaler_mode = 0x0,
		    .ref_base_lsb = 0x0,
		    .ref_base_msb = 0x0,
		    .line_mem_mode = 0x0,
		},

		[ TVI_4M_25P ] = {
		    .h_down_scaler = 0x0,
		    .h_scaler_mode = 0x0,
		    .ref_base_lsb = 0x0,
		    .ref_base_msb = 0x0,
		    .line_mem_mode = 0x0,
		},

		[ CVI_FHD_30P ] = {
		    .h_down_scaler = 0x1,
		    .h_scaler_mode = 0x39,
		    .ref_base_lsb = 0x78,
		    .ref_base_msb = 0x1,
		    .line_mem_mode = 0x0,
		},

		[ CVI_FHD_25P ] = {
		    .h_down_scaler = 0x1,
		    .h_scaler_mode = 0x49,
		    .ref_base_lsb = 0x4f,
		    .ref_base_msb = 0x2,
		    .line_mem_mode = 0x0,
		},

		[ CVI_HD_60P ] = {
		    .h_down_scaler = 0x1,
		    .h_scaler_mode = 0x11,
		    .ref_base_lsb = 0x0,
		    .ref_base_msb = 0x0,
		    .line_mem_mode = 0x0,
		},

		[ CVI_HD_50P ] = {
		    .h_down_scaler = 0x1,
		    .h_scaler_mode = 0x21,
		    .ref_base_lsb = 0x0,
		    .ref_base_msb = 0x0,
		    .line_mem_mode = 0x0,
		},

		[ CVI_HD_30P ] = {
		    .h_down_scaler = 0x1,
		    .h_scaler_mode = 0x19,
		    .ref_base_lsb = 0x0,
		    .ref_base_msb = 0x1,
		    .line_mem_mode = 0x0,
		},

		[ CVI_HD_25P ] = {
		    .h_down_scaler = 0x1,
		    .h_scaler_mode = 0x29,
		    .ref_base_lsb = 0xc0,
		    .ref_base_msb = 0x1,
		    .line_mem_mode = 0x0,
		},

		[ CVI_HD_30P_EX ] = {
		    .h_down_scaler = 0x1,
		    .h_scaler_mode = 0x19,
		    .ref_base_lsb = 0x0,
		    .ref_base_msb = 0x1,
		    .line_mem_mode = 0x0,
		},

		[ CVI_HD_25P_EX ] = {
		    .h_down_scaler = 0x1,
		    .h_scaler_mode = 0x29,
		    .ref_base_lsb = 0xc0,
		    .ref_base_msb = 0x1,
		    .line_mem_mode = 0x0,
		},

		[ CVI_4M_30P ] = {
		    .h_down_scaler = 0x1,
		    .h_scaler_mode = 0x69,
		    .ref_base_lsb = 0xF8,
		    .ref_base_msb = 0x0,
		    .line_mem_mode = 0x0,
		},

		[ CVI_4M_25P ] = {
		    .h_down_scaler = 0x1,
		    .h_scaler_mode = 0x79,
		    .ref_base_lsb = 0xC0,
		    .ref_base_msb = 0x1,
		    .line_mem_mode = 0x0,
		},

		[ CVI_8M_12_5P ] = {
		    .h_down_scaler = 0x1,
		    .h_scaler_mode = 0x9,
		    .ref_base_lsb = 0x68,
		    .ref_base_msb = 0x1,
		    .line_mem_mode = 0x0,
		},

		[ CVI_8M_15P ] = {
		    .h_down_scaler = 0x1,
		    .h_scaler_mode = 0x9,
		    .ref_base_lsb = 0xA8,
		    .ref_base_msb = 0x0,
		    .line_mem_mode = 0x0,
		},


};

typedef struct _video_input_color_init_s{
	unsigned char	brightnees;		//B0		0x0c/0x0d/0x0e/0x0f
	unsigned char	contrast;		//B0 		0x10/0x11/0x12/0x13
	unsigned char	hue;			//B0		0x40/0x41/0x42/0x43
	unsigned char	u_gain;         //B0		0x44/0x45/0x46/0x47
	unsigned char	v_gain;         //B0		0x48/0x49/0x4a/0x4b
	unsigned char	u_offset;       //B0		0x4c/0x4d/0x4e/0x4f
	unsigned char	v_offset;       //B0		0x50/0x51/0x52/0x53
	unsigned char	saturation_a;   //B0		0x3c/0x3d/0x3e/0x3f
	unsigned char	saturation_b;	//B5/6/7/8	0x2b
	unsigned char	black_level;  	 //B5/6/7/8	0x20
	unsigned char	burst_dec_a;	//B5/6/7/8	0x24
	unsigned char	burst_dec_b;    //B5/6/7/8	0x5f
	unsigned char	burst_dec_c;    //B5/6/7/8	0xd1
	unsigned char 	new_wpd_sel;	//B5/6/7/8 	0x75				[0]

	unsigned char reserved1;
	unsigned char reserved2;
	unsigned char reserved3;
	unsigned char reserved4;
	unsigned char reserved5;
	unsigned char reserved6;

}video_input_color_init_s;

video_input_color_init_s decoder_color_fmtdef[ NC_VIVO_CH_FORMATDEF_MAX ] =
{
		[ AHD20_1080P_30P ] = {
			    .new_wpd_sel = 0,
			    .brightnees = 0,
			    .contrast= 0x86,
			    .black_level = 0x80,
			    .hue = 0,
			    .u_gain = 0,
			    .v_gain = 0,
			    .u_offset = 0xF8,
			    .v_offset = 0xF8,
			    .saturation_a = 0x80,
			    .saturation_b = 0xA8,
			    .burst_dec_a = 0x2A,
			    .burst_dec_b = 0,
			    .burst_dec_c = 30,
		},
		[ AHD20_1080P_25P ] = {
			    .new_wpd_sel = 0,
			    .brightnees = 0,
			    .contrast= 0x86,
			    .black_level = 0x80,
			    .hue = 0,
			    .u_gain = 0,
			    .v_gain = 0,
			    .u_offset = 0xF8,
			    .v_offset = 0xF8,
			    .saturation_a = 0x80,
			    .saturation_b = 0xA8,
			    .burst_dec_a = 0x2A,
			    .burst_dec_b = 0,
			    .burst_dec_c = 0x30,
		},
		[ AHD20_960P_60P ] = {
		.new_wpd_sel = 0,
		.brightnees = 0,
		.contrast= 0x86,
		.black_level = 0x80,
		.hue = 0,
		.u_gain = 0,
		.v_gain = 0,
		.u_offset = 0xF8,
		.v_offset = 0xF8,
		.saturation_a = 0x80,
		.saturation_b = 0xA8,
		.burst_dec_a = 0x2A,
		.burst_dec_b = 0,
		.burst_dec_c = 0x30,
		},
		[ AHD20_960P_50P ] = {
		.new_wpd_sel = 0,
		.brightnees = 0,
		.contrast= 0x86,
		.black_level = 0x80,
		.hue = 0,
		.u_gain = 0,
		.v_gain = 0,
		.u_offset = 0xF8,
		.v_offset = 0xF8,
		.saturation_a = 0x80,
		.saturation_b = 0xA8,
		.burst_dec_a = 0x2A,
		.burst_dec_b = 0,
		.burst_dec_c = 0x30,
		},
		[ AHD20_960P_30P ] = {
		.new_wpd_sel = 0,
		.brightnees = 0,
		.contrast= 0x86,
		.black_level = 0x80,
		.hue = 0,
		.u_gain = 0,
		.v_gain = 0,
		.u_offset = 0xF8,
		.v_offset = 0xF8,
		.saturation_a = 0x80,
		.saturation_b = 0xA8,
		.burst_dec_a = 0x2A,
		.burst_dec_b = 0,
		.burst_dec_c = 0x30,
		},
		[ AHD20_960P_25P ] = {
		.new_wpd_sel = 0,
		.brightnees = 0,
		.contrast= 0x86,
		.black_level = 0x80,
		.hue = 0,
		.u_gain = 0,
		.v_gain = 0,
		.u_offset = 0xF8,
		.v_offset = 0xF8,
		.saturation_a = 0x80,
		.saturation_b = 0xA8,
		.burst_dec_a = 0x2A,
		.burst_dec_b = 0,
		.burst_dec_c = 0x30,
		},

		[ AHD20_1080P_60P ] = {
				    .new_wpd_sel = 0,
				    .brightnees = 0,
				    .contrast= 0x86,
				    .black_level = 0x80,
				    .hue = 0,
				    .u_gain = 0,
				    .v_gain = 0,
				    .u_offset = 0xF8,
				    .v_offset = 0xF8,
				    .saturation_a = 0x80,
				    .saturation_b = 0xA8,
				    .burst_dec_a = 0x2A,
				    .burst_dec_b = 0,
				    .burst_dec_c = 30,
		},
		[ AHD20_1080P_50P ] = {
				.new_wpd_sel = 0,
				.brightnees = 0,
				.contrast= 0x86,
				.black_level = 0x80,
				.hue = 0,
				.u_gain = 0,
				.v_gain = 0,
				.u_offset = 0xF8,
				.v_offset = 0xF8,
				.saturation_a = 0x80,
				.saturation_b = 0xA8,
				.burst_dec_a = 0x2A,
				.burst_dec_b = 0,
				.burst_dec_c = 0x30,
		},
		[ AHD30_4M_30P ] = {
			    .new_wpd_sel = 0,
			    .brightnees = 0,
			    .contrast= 0x82,
			    .black_level = 0x80,
			    .hue = 0x1,
			    .u_gain = 0x10,
			    .v_gain = 0x0,
			    .u_offset = 0xFE,
			    .v_offset = 0xFC,
			    .saturation_a = 0x80,
			    .saturation_b = 0xB0,
			    .burst_dec_a = 0x2A,
			    .burst_dec_b = 0,
			    .burst_dec_c = 0x40,


		},
		[ AHD30_4M_25P ] = {
			    .new_wpd_sel = 0,
			    .brightnees = 0,
			    .contrast= 0x82,
			    .black_level = 0x80,
			    .hue = 0x1,
			    .u_gain = 0x10,
			    .v_gain = 0,
			    .u_offset = 0xFE,
			    .v_offset = 0xFC,
			    .saturation_a = 0x80,
			    .saturation_b = 0xB0,
			    .burst_dec_a = 0x2A,
			    .burst_dec_b = 0,
			    .burst_dec_c = 0x40,


		},
		[ AHD30_4M_15P ] = {
			    .new_wpd_sel = 0x0,
			    .brightnees = 0x0,
			    .contrast= 0x82,
			    .black_level = 0x80,
			    .hue = 0x1,
			    .u_gain = 0x10,
			    .v_gain = 0,
			    .u_offset = 0xFE,
			    .v_offset = 0xFC,
			    .saturation_a = 0x80,
			    .saturation_b = 0xB0,
			    .burst_dec_a = 0x2A,
			    .burst_dec_b = 0,
			    .burst_dec_c = 0x40,
		},
#ifdef __FOR_IDIS_TVI_2M
		[ TVI_FHD_30P ] = {
		.new_wpd_sel = 0,
		.brightnees = 0x12,
		.contrast= 0x76,
		.black_level = 0x84,
		.hue = 0x3,
		.u_gain = 0xC,
		.v_gain = 0x1A,
		.u_offset = 0xFA,
		.v_offset = 0xFA,
		.saturation_a = 0x80,
		.saturation_b = 0xA8,
		.burst_dec_a = 0x2A,
		.burst_dec_b = 0,
		.burst_dec_c = 0x30,

		},

		[ TVI_FHD_25P ] = {
		.new_wpd_sel = 0,
		.brightnees = 0x12,
		.contrast= 0x75,
		.black_level = 0x84,
		.hue = 0x3,
		.u_gain = 0xC,
		.v_gain = 0x1A,
		.u_offset = 0xFA,
		.v_offset = 0xFA,
		.saturation_a = 0x80,
		.saturation_b = 0xA8,
		.burst_dec_a = 0x2A,
		.burst_dec_b = 0,
		.burst_dec_c = 0x30,

		},
#else
		[ TVI_FHD_30P ] = {
		.new_wpd_sel = 0,
		.brightnees = 0,
		.contrast= 0x76,
		.black_level = 0x84,
		.hue = 0x3,
		.u_gain = 0xC,
		.v_gain = 0x1A,
		.u_offset = 0xFA,
		.v_offset = 0xFA,
		.saturation_a = 0x80,
		.saturation_b = 0xA8,
		.burst_dec_a = 0x2A,
		.burst_dec_b = 0,
		.burst_dec_c = 0x30,

		},

		[ TVI_FHD_25P ] = {
		.new_wpd_sel = 0,
		.brightnees = 0,
		.contrast= 0x75,
		.black_level = 0x84,
		.hue = 0x3,
		.u_gain = 0xC,
		.v_gain = 0x1A,
		.u_offset = 0xFA,
		.v_offset = 0xFA,
		.saturation_a = 0x80,
		.saturation_b = 0xA8,
		.burst_dec_a = 0x2A,
		.burst_dec_b = 0,
		.burst_dec_c = 0x30,

		},
#endif
		[ TVI_5M_20P ] = {
			.new_wpd_sel = 0x0,
			.brightnees = 0x0,
			.contrast= 0x75,
			.black_level = 0x87,
			.hue = 0x0a,
			.u_gain = 0x30,
			.v_gain = 0x32,
			.u_offset = 0x02,
			.v_offset = 0xF8,
			.saturation_a = 0x80,
			.saturation_b = 0xC0,
			.burst_dec_a = 0x2A,
			.burst_dec_b = 0,
			.burst_dec_c = 0x30,

		},

		[ TVI_4M_30P ] = {
		.new_wpd_sel = 0x0,
		.brightnees = 0x0,
		.contrast= 0x75,
		.black_level = 0x87,
		.hue = 0x0,
		.u_gain = 0x30,
		.v_gain = 0x32,
		.u_offset = 0x02,
		.v_offset = 0xF8,
		.saturation_a = 0x80,
		.saturation_b = 0xC0,
		.burst_dec_a = 0x2A,
		.burst_dec_b = 0,
		.burst_dec_c = 0x30,

		},

		[ TVI_4M_25P ] = {
		.new_wpd_sel = 0x0,
		.brightnees = 0x0,
		.contrast= 0x75,
		.black_level = 0x87,
		.hue = 0x0,
		.u_gain = 0x30,
		.v_gain = 0x32,
		.u_offset = 0x02,
		.v_offset = 0xF8,
		.saturation_a = 0x80,
		.saturation_b = 0xC0,
		.burst_dec_a = 0x2A,
		.burst_dec_b = 0,
		.burst_dec_c = 0x30,

		},
		[ CVI_FHD_30P ] = {
		.new_wpd_sel = 0,
		.brightnees = 0,
		.contrast= 0x98,
		.black_level = 0x86,
		.hue = 0x3,
		.u_gain = 0xC,
		.v_gain = 0x1A,
		.u_offset = 0xFA,
		.v_offset = 0xFA,
		.saturation_a = 0x80,
		.saturation_b = 0xa8,
		.burst_dec_a = 0x2a,
		.burst_dec_b = 0,
		.burst_dec_c = 0x30,


		},
		[ CVI_FHD_25P ] = {
		.new_wpd_sel = 0,
		.brightnees = 0,
		.contrast= 0x98,
		.black_level = 0x86,
		.hue = 0x3,
		.u_gain = 0xC,
		.v_gain = 0x1A,
		.u_offset = 0xFA,
		.v_offset = 0xFA,
		.saturation_a = 0x80,
		.saturation_b = 0xa8,
		.burst_dec_a = 0x2a,
		.burst_dec_b = 0,
		.burst_dec_c = 0x30,


		},
		[ CVI_4M_30P ] = {
		.new_wpd_sel = 0,
		.brightnees = 0,
		.contrast= 0x7D,
		.black_level = 0x80,
		.hue = 0,
		.u_gain = 0,
		.v_gain = 0,
		.u_offset = 0x00,
		.v_offset = 0x00,
		.saturation_a = 0x80,
		.saturation_b = 0x98,
		.burst_dec_a = 0x2A,
		.burst_dec_b = 0x30,
		.burst_dec_c = 0x30,


		},

		[ CVI_4M_25P ] = {
		.new_wpd_sel = 0,
		.brightnees = 0,
		.contrast= 0x7D,
		.black_level = 0x80,
		.hue = 0,
		.u_gain = 0,
		.v_gain = 0,
		.u_offset = 0x00,
		.v_offset = 0x00,
		.saturation_a = 0x80,
		.saturation_b = 0x98,
		.burst_dec_a = 0x2A,
		.burst_dec_b = 0x30,
		.burst_dec_c = 0x30,


		},
};

typedef struct _video_input_vafe_init_s{
	unsigned char powerdown;		//B0       0x00/1/2/3 [0]
	unsigned char gain;			//B0       0x00/1/2/3 [4]
	unsigned char spd;				//B5/6/7/8 0x00       [5:4]

	unsigned char ctrlreg;			//B5/6/7/8 0x01       [6]
	unsigned char ctrlibs;			//B5/6/7/8 0x01       [5:4]
	unsigned char adcspd;			//B5/6/7/8 0x01       [2]
	unsigned char clplevel;		//B5/6/7/8 0x01       [1:0]


	unsigned char eq_band;			//B5/6/7/8 0x58       [6:4]
	unsigned char lpf_front_band;	//B5/6/7/8 0x58       [1:0]

	unsigned char clpmode;			//B5/6/7/8 0x59       [7]
	unsigned char f_lpf_bypass;	//B5/6/7/8 0x59       [4]
	unsigned char clproff;			//B5/6/7/8 0x59       [3]
	unsigned char b_lpf_bypass;	//B5/6/7/8 0x59       [0]

	unsigned char duty;		   	//B5/6/7/8 0x5B    	  [6:4]
	unsigned char ref_vol;			//B5/6/7/8 0x5B       [1:0]

	unsigned char lpf_back_band;	//B5/6/7/8 0x5C       [6:4]
	unsigned char clk_sel;			//B5/6/7/8 0x5C       [3]
	unsigned char eq_gainsel;		//B5/6/7/8 0x5C       [2:0]

	unsigned char reserved1;
	unsigned char reserved2;
	unsigned char reserved3;
	unsigned char reserved4;
	unsigned char reserved5;
	unsigned char reserved6;
}video_input_vafe_init_s;

video_input_vafe_init_s decoder_afe_fmtdef[ NC_VIVO_CH_FORMATDEF_MAX ] =
{
		[ AHD20_SD_H960_2EX_Btype_NT ] = {
		.powerdown 		= 0x00, //B0       0x00/1/2/3 [0]
		.gain 			= 0x01,	//B0       0x00/1/2/3 [4]
		.spd 			= 0x0D,	//B5/6/7/8 0x00       [5:4]
		.ctrlreg 		= 0x01,	//B5/6/7/8 0x01       [6]
		.ctrlibs 		= 0x02,	//B5/6/7/8 0x01       [5:4]
		.adcspd 		= 0x00,	//B5/6/7/8 0x01       [2]
		.clplevel 		= 0x02,	//B5/6/7/8 0x01       [1:0]
		.eq_band 		= 0x00,	//B5/6/7/8 0x58       [6:4]
		.lpf_front_band = 0x07,	//B5/6/7/8 0x58       [1:0]
		.clpmode 		= 0x00,	//B5/6/7/8 0x59       [7]
		.f_lpf_bypass 	= 0x00,	//B5/6/7/8 0x59       [4]
		.clproff 		= 0x00,	//B5/6/7/8 0x59       [3]
		.b_lpf_bypass 	= 0x00,	//B5/6/7/8 0x59       [0]
		.duty 			= 0x04,	//B5/6/7/8 0x5B    	  [6:4]
		.ref_vol 		= 0x03,	//B5/6/7/8 0x5B       [1:0]
		.lpf_back_band 	= 0x07,	//B5/6/7/8 0x5C       [6:4]
		.clk_sel 		= 0x01,	//B5/6/7/8 0x5C       [3]
		.eq_gainsel 	= 0x00,	//B5/6/7/8 0x5C       [2:0]
		},
		[ AHD20_SD_H960_2EX_Btype_PAL ] = {
		.powerdown 		= 0x00, //B0       0x00/1/2/3 [0]
		.gain 			= 0x01,	//B0       0x00/1/2/3 [4]
		.spd 			= 0x0D,	//B5/6/7/8 0x00       [5:4]
		.ctrlreg 		= 0x01,	//B5/6/7/8 0x01       [6]
		.ctrlibs 		= 0x02,	//B5/6/7/8 0x01       [5:4]
		.adcspd 		= 0x00,	//B5/6/7/8 0x01       [2]
		.clplevel 		= 0x02,	//B5/6/7/8 0x01       [1:0]
		.eq_band 		= 0x00,	//B5/6/7/8 0x58       [6:4]
		.lpf_front_band = 0x07,	//B5/6/7/8 0x58       [1:0]
		.clpmode 		= 0x00,	//B5/6/7/8 0x59       [7]
		.f_lpf_bypass 	= 0x00,	//B5/6/7/8 0x59       [4]
		.clproff 		= 0x00,	//B5/6/7/8 0x59       [3]
		.b_lpf_bypass 	= 0x00,	//B5/6/7/8 0x59       [0]
		.duty 			= 0x04,	//B5/6/7/8 0x5B    	  [6:4]
		.ref_vol 		= 0x03,	//B5/6/7/8 0x5B       [1:0]
		.lpf_back_band 	= 0x07,	//B5/6/7/8 0x5C       [6:4]
		.clk_sel 		= 0x01,	//B5/6/7/8 0x5C       [3]
		.eq_gainsel 	= 0x00,	//B5/6/7/8 0x5C       [2:0]
		},
		[ AHD20_1080P_30P ] = {
		.powerdown = 0x0,
		.gain =  0x1,
		.spd = 0xD,
		.ctrlreg= 0x1,
		.ctrlibs= 0x2,
		.adcspd = 0x0,
		.clplevel = 0x2,
		.eq_band = 0x0,
		.lpf_front_band = 0x7,
		.clpmode = 0x0,
		.f_lpf_bypass = 0x0,
		.clproff = 0x0,
		.b_lpf_bypass = 0x0,
		.duty = 0x4,
		.ref_vol = 0x1,
		.lpf_back_band = 0x7,
		.clk_sel = 0x1,
		.eq_gainsel = 0x0,

		},
		[ AHD20_1080P_25P ] = {
		.powerdown = 0x0,
		.gain =  0x1,
		.spd = 0xD,
		.ctrlreg= 0x1,
		.ctrlibs= 0x2,
		.adcspd = 0x0,
		.clplevel = 0x2,
		.eq_band = 0x0,
		.lpf_front_band = 0x7,
		.clpmode = 0x0,
		.f_lpf_bypass = 0x0,
		.clproff = 0x0,
		.b_lpf_bypass = 0x0,
		.duty = 0x4,
		.ref_vol = 0x1,
		.lpf_back_band = 0x7,
		.clk_sel = 0x1,
		.eq_gainsel = 0x0,

		},

		[ AHD20_960P_60P ] = {
		.powerdown = 0x0,
		.gain =  0x1,
		.spd = 0xD,
		.ctrlreg= 0x1,
		.ctrlibs= 0x2,
		.adcspd = 0x0,
		.clplevel = 0x2,
		.eq_band = 0x0,
		.lpf_front_band = 0x7,
		.clpmode = 0x0,
		.f_lpf_bypass = 0x0,
		.clproff = 0x0,
		.b_lpf_bypass = 0x0,
		.duty = 0x4,
		.ref_vol = 0x1,
		.lpf_back_band = 0x7,
		.clk_sel = 0x1,
		.eq_gainsel = 0x0,

		},

		[ AHD20_960P_50P ] = {
		.powerdown = 0x0,
		.gain =  0x1,
		.spd = 0xD,
		.ctrlreg= 0x1,
		.ctrlibs= 0x2,
		.adcspd = 0x0,
		.clplevel = 0x2,
		.eq_band = 0x0,
		.lpf_front_band = 0x7,
		.clpmode = 0x0,
		.f_lpf_bypass = 0x0,
		.clproff = 0x0,
		.b_lpf_bypass = 0x0,
		.duty = 0x4,
		.ref_vol = 0x1,
		.lpf_back_band = 0x7,
		.clk_sel = 0x1,
		.eq_gainsel = 0x0,

		},

		[ AHD20_960P_30P ] = {
		.powerdown = 0x0,
		.gain =  0x1,
		.spd = 0xD,
		.ctrlreg= 0x1,
		.ctrlibs= 0x2,
		.adcspd = 0x0,
		.clplevel = 0x2,
		.eq_band = 0x0,
		.lpf_front_band = 0x7,
		.clpmode = 0x0,
		.f_lpf_bypass = 0x0,
		.clproff = 0x0,
		.b_lpf_bypass = 0x0,
		.duty = 0x4,
		.ref_vol = 0x1,
		.lpf_back_band = 0x7,
		.clk_sel = 0x1,
		.eq_gainsel = 0x0,

		},

		[ AHD20_960P_25P ] = {
		.powerdown = 0x0,
		.gain =  0x1,
		.spd = 0xD,
		.ctrlreg= 0x1,
		.ctrlibs= 0x2,
		.adcspd = 0x0,
		.clplevel = 0x2,
		.eq_band = 0x0,
		.lpf_front_band = 0x7,
		.clpmode = 0x0,
		.f_lpf_bypass = 0x0,
		.clproff = 0x0,
		.b_lpf_bypass = 0x0,
		.duty = 0x4,
		.ref_vol = 0x1,
		.lpf_back_band = 0x7,
		.clk_sel = 0x1,
		.eq_gainsel = 0x0,

		},

		[ AHD20_720P_60P ] = {
		.powerdown 		= 0x00, //B0       0x00/1/2/3 [0]
		.gain 			= 0x01,	//B0       0x00/1/2/3 [4]
		.spd 			= 0x0D,	//B5/6/7/8 0x00       [5:4]
		.ctrlreg 		= 0x01,	//B5/6/7/8 0x01       [6]
		.ctrlibs 		= 0x02,	//B5/6/7/8 0x01       [5:4]
		.adcspd 		= 0x00,	//B5/6/7/8 0x01       [2]
		.clplevel 		= 0x02,	//B5/6/7/8 0x01       [1:0]
		.eq_band 		= 0x00,	//B5/6/7/8 0x58       [6:4]
		.lpf_front_band = 0x07,	//B5/6/7/8 0x58       [1:0]
		.clpmode 		= 0x00,	//B5/6/7/8 0x59       [7]
		.f_lpf_bypass 	= 0x00,	//B5/6/7/8 0x59       [4]
		.clproff 		= 0x00,	//B5/6/7/8 0x59       [3]
		.b_lpf_bypass 	= 0x00,	//B5/6/7/8 0x59       [0]
		.duty 			= 0x04,	//B5/6/7/8 0x5B    	  [6:4]
		.ref_vol 		= 0x03,	//B5/6/7/8 0x5B       [1:0]
		.lpf_back_band 	= 0x07,	//B5/6/7/8 0x5C       [6:4]
		.clk_sel 		= 0x01,	//B5/6/7/8 0x5C       [3]
		.eq_gainsel 	= 0x00,	//B5/6/7/8 0x5C       [2:0]
		},
		[ AHD20_720P_50P ] = {
		.powerdown 		= 0x00, //B0       0x00/1/2/3 [0]
		.gain 			= 0x01,	//B0       0x00/1/2/3 [4]
		.spd 			= 0x0D,	//B5/6/7/8 0x00       [5:4]
		.ctrlreg 		= 0x01,	//B5/6/7/8 0x01       [6]
		.ctrlibs 		= 0x02,	//B5/6/7/8 0x01       [5:4]
		.adcspd 		= 0x00,	//B5/6/7/8 0x01       [2]
		.clplevel 		= 0x02,	//B5/6/7/8 0x01       [1:0]
		.eq_band 		= 0x00,	//B5/6/7/8 0x58       [6:4]
		.lpf_front_band = 0x07,	//B5/6/7/8 0x58       [1:0]
		.clpmode 		= 0x00,	//B5/6/7/8 0x59       [7]
		.f_lpf_bypass 	= 0x00,	//B5/6/7/8 0x59       [4]
		.clproff 		= 0x00,	//B5/6/7/8 0x59       [3]
		.b_lpf_bypass 	= 0x00,	//B5/6/7/8 0x59       [0]
		.duty 			= 0x04,	//B5/6/7/8 0x5B    	  [6:4]
		.ref_vol 		= 0x03,	//B5/6/7/8 0x5B       [1:0]
		.lpf_back_band 	= 0x07,	//B5/6/7/8 0x5C       [6:4]
		.clk_sel 		= 0x01,	//B5/6/7/8 0x5C       [3]
		.eq_gainsel 	= 0x00,	//B5/6/7/8 0x5C       [2:0]
		},
		[ AHD20_720P_30P ] = {
		.powerdown 		= 0x00, //B0       0x00/1/2/3 [0]
		.gain 			= 0x01,	//B0       0x00/1/2/3 [4]
		.spd 			= 0x0D,	//B5/6/7/8 0x00       [5:4]
		.ctrlreg 		= 0x01,	//B5/6/7/8 0x01       [6]
		.ctrlibs 		= 0x02,	//B5/6/7/8 0x01       [5:4]
		.adcspd 		= 0x00,	//B5/6/7/8 0x01       [2]
		.clplevel 		= 0x02,	//B5/6/7/8 0x01       [1:0]
		.eq_band 		= 0x00,	//B5/6/7/8 0x58       [6:4]
		.lpf_front_band = 0x07,	//B5/6/7/8 0x58       [1:0]
		.clpmode 		= 0x00,	//B5/6/7/8 0x59       [7]
		.f_lpf_bypass 	= 0x00,	//B5/6/7/8 0x59       [4]
		.clproff 		= 0x00,	//B5/6/7/8 0x59       [3]
		.b_lpf_bypass 	= 0x00,	//B5/6/7/8 0x59       [0]
		.duty 			= 0x04,	//B5/6/7/8 0x5B    	  [6:4]
		.ref_vol 		= 0x03,	//B5/6/7/8 0x5B       [1:0]
		.lpf_back_band 	= 0x07,	//B5/6/7/8 0x5C       [6:4]
		.clk_sel 		= 0x01,	//B5/6/7/8 0x5C       [3]
		.eq_gainsel 	= 0x00,	//B5/6/7/8 0x5C       [2:0]
		},
		[ AHD20_720P_25P ] = {
		.powerdown 		= 0x00, //B0       0x00/1/2/3 [0]
		.gain 			= 0x01,	//B0       0x00/1/2/3 [4]
		.spd 			= 0x0D,	//B5/6/7/8 0x00       [5:4]
		.ctrlreg 		= 0x01,	//B5/6/7/8 0x01       [6]
		.ctrlibs 		= 0x02,	//B5/6/7/8 0x01       [5:4]
		.adcspd 		= 0x00,	//B5/6/7/8 0x01       [2]
		.clplevel 		= 0x02,	//B5/6/7/8 0x01       [1:0]
		.eq_band 		= 0x00,	//B5/6/7/8 0x58       [6:4]
		.lpf_front_band = 0x07,	//B5/6/7/8 0x58       [1:0]
		.clpmode 		= 0x00,	//B5/6/7/8 0x59       [7]
		.f_lpf_bypass 	= 0x00,	//B5/6/7/8 0x59       [4]
		.clproff 		= 0x00,	//B5/6/7/8 0x59       [3]
		.b_lpf_bypass 	= 0x00,	//B5/6/7/8 0x59       [0]
		.duty 			= 0x04,	//B5/6/7/8 0x5B    	  [6:4]
		.ref_vol 		= 0x03,	//B5/6/7/8 0x5B       [1:0]
		.lpf_back_band 	= 0x07,	//B5/6/7/8 0x5C       [6:4]
		.clk_sel 		= 0x01,	//B5/6/7/8 0x5C       [3]
		.eq_gainsel 	= 0x00,	//B5/6/7/8 0x5C       [2:0]
		},
		[ AHD20_720P_30P_EX ] = {
		.powerdown 		= 0x00, //B0       0x00/1/2/3 [0]
		.gain 			= 0x01,	//B0       0x00/1/2/3 [4]
		.spd 			= 0x0D,	//B5/6/7/8 0x00       [5:4]
		.ctrlreg 		= 0x01,	//B5/6/7/8 0x01       [6]
		.ctrlibs 		= 0x02,	//B5/6/7/8 0x01       [5:4]
		.adcspd 		= 0x00,	//B5/6/7/8 0x01       [2]
		.clplevel 		= 0x02,	//B5/6/7/8 0x01       [1:0]
		.eq_band 		= 0x00,	//B5/6/7/8 0x58       [6:4]
		.lpf_front_band = 0x07,	//B5/6/7/8 0x58       [1:0]
		.clpmode 		= 0x00,	//B5/6/7/8 0x59       [7]
		.f_lpf_bypass 	= 0x00,	//B5/6/7/8 0x59       [4]
		.clproff 		= 0x00,	//B5/6/7/8 0x59       [3]
		.b_lpf_bypass 	= 0x00,	//B5/6/7/8 0x59       [0]
		.duty 			= 0x04,	//B5/6/7/8 0x5B    	  [6:4]
		.ref_vol 		= 0x03,	//B5/6/7/8 0x5B       [1:0]
		.lpf_back_band 	= 0x07,	//B5/6/7/8 0x5C       [6:4]
		.clk_sel 		= 0x01,	//B5/6/7/8 0x5C       [3]
		.eq_gainsel 	= 0x00,	//B5/6/7/8 0x5C       [2:0]
		},
		[ AHD20_720P_25P_EX ] = {
		.powerdown 		= 0x00, //B0       0x00/1/2/3 [0]
		.gain 			= 0x01,	//B0       0x00/1/2/3 [4]
		.spd 			= 0x0D,	//B5/6/7/8 0x00       [5:4]
		.ctrlreg 		= 0x01,	//B5/6/7/8 0x01       [6]
		.ctrlibs 		= 0x02,	//B5/6/7/8 0x01       [5:4]
		.adcspd 		= 0x00,	//B5/6/7/8 0x01       [2]
		.clplevel 		= 0x02,	//B5/6/7/8 0x01       [1:0]
		.eq_band 		= 0x00,	//B5/6/7/8 0x58       [6:4]
		.lpf_front_band = 0x07,	//B5/6/7/8 0x58       [1:0]
		.clpmode 		= 0x00,	//B5/6/7/8 0x59       [7]
		.f_lpf_bypass 	= 0x00,	//B5/6/7/8 0x59       [4]
		.clproff 		= 0x00,	//B5/6/7/8 0x59       [3]
		.b_lpf_bypass 	= 0x00,	//B5/6/7/8 0x59       [0]
		.duty 			= 0x04,	//B5/6/7/8 0x5B    	  [6:4]
		.ref_vol 		= 0x03,	//B5/6/7/8 0x5B       [1:0]
		.lpf_back_band 	= 0x07,	//B5/6/7/8 0x5C       [6:4]
		.clk_sel 		= 0x01,	//B5/6/7/8 0x5C       [3]
		.eq_gainsel 	= 0x00,	//B5/6/7/8 0x5C       [2:0]
		},
		[ AHD20_720P_30P_EX_Btype ] = {
		.powerdown 		= 0x00, //B0       0x00/1/2/3 [0]
		.gain 			= 0x01,	//B0       0x00/1/2/3 [4]
		.spd 			= 0x0D,	//B5/6/7/8 0x00       [5:4]
		.ctrlreg 		= 0x01,	//B5/6/7/8 0x01       [6]
		.ctrlibs 		= 0x02,	//B5/6/7/8 0x01       [5:4]
		.adcspd 		= 0x00,	//B5/6/7/8 0x01       [2]
		.clplevel 		= 0x02,	//B5/6/7/8 0x01       [1:0]
		.eq_band 		= 0x00,	//B5/6/7/8 0x58       [6:4]
		.lpf_front_band = 0x07,	//B5/6/7/8 0x58       [1:0]
		.clpmode 		= 0x00,	//B5/6/7/8 0x59       [7]
		.f_lpf_bypass 	= 0x00,	//B5/6/7/8 0x59       [4]
		.clproff 		= 0x00,	//B5/6/7/8 0x59       [3]
		.b_lpf_bypass 	= 0x00,	//B5/6/7/8 0x59       [0]
		.duty 			= 0x04,	//B5/6/7/8 0x5B    	  [6:4]
		.ref_vol 		= 0x03,	//B5/6/7/8 0x5B       [1:0]
		.lpf_back_band 	= 0x07,	//B5/6/7/8 0x5C       [6:4]
		.clk_sel 		= 0x01,	//B5/6/7/8 0x5C       [3]
		.eq_gainsel 	= 0x00,	//B5/6/7/8 0x5C       [2:0]
		},
		[ AHD20_720P_25P_EX_Btype ] = {
		.powerdown 		= 0x00, //B0       0x00/1/2/3 [0]
		.gain 			= 0x01,	//B0       0x00/1/2/3 [4]
		.spd 			= 0x0D,	//B5/6/7/8 0x00       [5:4]
		.ctrlreg 		= 0x01,	//B5/6/7/8 0x01       [6]
		.ctrlibs 		= 0x02,	//B5/6/7/8 0x01       [5:4]
		.adcspd 		= 0x00,	//B5/6/7/8 0x01       [2]
		.clplevel 		= 0x02,	//B5/6/7/8 0x01       [1:0]
		.eq_band 		= 0x00,	//B5/6/7/8 0x58       [6:4]
		.lpf_front_band = 0x07,	//B5/6/7/8 0x58       [1:0]
		.clpmode 		= 0x00,	//B5/6/7/8 0x59       [7]
		.f_lpf_bypass 	= 0x00,	//B5/6/7/8 0x59       [4]
		.clproff 		= 0x00,	//B5/6/7/8 0x59       [3]
		.b_lpf_bypass 	= 0x00,	//B5/6/7/8 0x59       [0]
		.duty 			= 0x04,	//B5/6/7/8 0x5B    	  [6:4]
		.ref_vol 		= 0x03,	//B5/6/7/8 0x5B       [1:0]
		.lpf_back_band 	= 0x07,	//B5/6/7/8 0x5C       [6:4]
		.clk_sel 		= 0x01,	//B5/6/7/8 0x5C       [3]
		.eq_gainsel 	= 0x00,	//B5/6/7/8 0x5C       [2:0]
		},
		[ AHD30_4M_30P ] = {
			    .powerdown = 0,
			    .gain =  1,
			    .spd = 0xD,
			    .ctrlreg= 1,
			    .ctrlibs= 2,
			    .adcspd = 0,
			    .clplevel = 2,
			    .eq_band = 0,
			    .lpf_front_band = 7,
			    .clpmode = 0,
			    .f_lpf_bypass =0,
			    .clproff = 0,
			    .b_lpf_bypass = 0,
			    .duty = 4,
			    .ref_vol = 1,
			    .lpf_back_band = 7,
			    .clk_sel = 1,
			    .eq_gainsel = 0,

		},
		[ AHD30_4M_25P ] = {
			    .powerdown = 0,
			    .gain =  1,
			    .spd = 0xD,
			    .ctrlreg= 1,
			    .ctrlibs= 2,
			    .adcspd = 0,
			    .clplevel = 2,
			    .eq_band = 0,
			    .lpf_front_band = 7,
			    .clpmode = 0,
			    .f_lpf_bypass = 0,
			    .clproff = 0,
			    .b_lpf_bypass = 0,
			    .duty = 4,
			    .ref_vol = 1,
			    .lpf_back_band = 7,
			    .clk_sel = 1,
			    .eq_gainsel = 0,

		},
		[ AHD30_4M_15P ] = {
			    .powerdown = 0,
			    .gain =  1,
			    .spd = 0xD,
			    .ctrlreg= 1,
			    .ctrlibs= 2,
			    .adcspd = 0,
			    .clplevel = 2,
			    .eq_band = 0,
			    .lpf_front_band = 7,
			    .clpmode = 0,
			    .f_lpf_bypass = 0,
			    .clproff = 0,
			    .b_lpf_bypass = 0,
			    .duty = 4,
			    .ref_vol = 1,
			    .lpf_back_band = 7,
			    .clk_sel = 1,
			    .eq_gainsel = 0,

		},
		[ AHD30_3M_30P ] = {
		.powerdown 		= 0x00, //B0       0x00/1/2/3 [0]
		.gain 			= 0x01,	//B0       0x00/1/2/3 [4]
		.spd 			= 0x0D,	//B5/6/7/8 0x00       [5:4]
		.ctrlreg 		= 0x01,	//B5/6/7/8 0x01       [6]
		.ctrlibs 		= 0x02,	//B5/6/7/8 0x01       [5:4]
		.adcspd 		= 0x00,	//B5/6/7/8 0x01       [2]
		.clplevel 		= 0x02,	//B5/6/7/8 0x01       [1:0]
		.eq_band 		= 0x00,	//B5/6/7/8 0x58       [6:4]
		.lpf_front_band = 0x07,	//B5/6/7/8 0x58       [1:0]
		.clpmode 		= 0x00,	//B5/6/7/8 0x59       [7]
		.f_lpf_bypass 	= 0x00,	//B5/6/7/8 0x59       [4]
		.clproff 		= 0x00,	//B5/6/7/8 0x59       [3]
		.b_lpf_bypass 	= 0x00,	//B5/6/7/8 0x59       [0]
		.duty 			= 0x04,	//B5/6/7/8 0x5B    	  [6:4]
		.ref_vol 		= 0x03,	//B5/6/7/8 0x5B       [1:0]
		.lpf_back_band 	= 0x07,	//B5/6/7/8 0x5C       [6:4]
		.clk_sel 		= 0x01,	//B5/6/7/8 0x5C       [3]
		.eq_gainsel 	= 0x00,	//B5/6/7/8 0x5C       [2:0]
		},
		[ AHD30_3M_25P ] = {
		.powerdown 		= 0x00, //B0       0x00/1/2/3 [0]
		.gain 			= 0x01,	//B0       0x00/1/2/3 [4]
		.spd 			= 0x0D,	//B5/6/7/8 0x00       [5:4]
		.ctrlreg 		= 0x01,	//B5/6/7/8 0x01       [6]
		.ctrlibs 		= 0x02,	//B5/6/7/8 0x01       [5:4]
		.adcspd 		= 0x00,	//B5/6/7/8 0x01       [2]
		.clplevel 		= 0x02,	//B5/6/7/8 0x01       [1:0]
		.eq_band 		= 0x00,	//B5/6/7/8 0x58       [6:4]
		.lpf_front_band = 0x07,	//B5/6/7/8 0x58       [1:0]
		.clpmode 		= 0x00,	//B5/6/7/8 0x59       [7]
		.f_lpf_bypass 	= 0x00,	//B5/6/7/8 0x59       [4]
		.clproff 		= 0x00,	//B5/6/7/8 0x59       [3]
		.b_lpf_bypass 	= 0x00,	//B5/6/7/8 0x59       [0]
		.duty 			= 0x04,	//B5/6/7/8 0x5B    	  [6:4]
		.ref_vol 		= 0x03,	//B5/6/7/8 0x5B       [1:0]
		.lpf_back_band 	= 0x07,	//B5/6/7/8 0x5C       [6:4]
		.clk_sel 		= 0x01,	//B5/6/7/8 0x5C       [3]
		.eq_gainsel 	= 0x00,	//B5/6/7/8 0x5C       [2:0]
		},
		[ AHD30_3M_18P ] = {
		.powerdown 		= 0x00, //B0       0x00/1/2/3 [0]
		.gain 			= 0x01,	//B0       0x00/1/2/3 [4]
		.spd 			= 0x0D,	//B5/6/7/8 0x00       [5:4]
		.ctrlreg 		= 0x01,	//B5/6/7/8 0x01       [6]
		.ctrlibs 		= 0x02,	//B5/6/7/8 0x01       [5:4]
		.adcspd 		= 0x00,	//B5/6/7/8 0x01       [2]
		.clplevel 		= 0x02,	//B5/6/7/8 0x01       [1:0]
		.eq_band 		= 0x00,	//B5/6/7/8 0x58       [6:4]
		.lpf_front_band = 0x07,	//B5/6/7/8 0x58       [1:0]
		.clpmode 		= 0x00,	//B5/6/7/8 0x59       [7]
		.f_lpf_bypass 	= 0x00,	//B5/6/7/8 0x59       [4]
		.clproff 		= 0x00,	//B5/6/7/8 0x59       [3]
		.b_lpf_bypass 	= 0x00,	//B5/6/7/8 0x59       [0]
		.duty 			= 0x04,	//B5/6/7/8 0x5B    	  [6:4]
		.ref_vol 		= 0x03,	//B5/6/7/8 0x5B       [1:0]
		.lpf_back_band 	= 0x07,	//B5/6/7/8 0x5C       [6:4]
		.clk_sel 		= 0x01,	//B5/6/7/8 0x5C       [3]
		.eq_gainsel 	= 0x00,	//B5/6/7/8 0x5C       [2:0]
		},
		[ AHD30_5M_12_5P ] = {
		.powerdown 		= 0x00, //B0       0x00/1/2/3 [0]
		.gain 			= 0x01,	//B0       0x00/1/2/3 [4]
		.spd 			= 0x0D,	//B5/6/7/8 0x00       [5:4]
		.ctrlreg 		= 0x01,	//B5/6/7/8 0x01       [6]
		.ctrlibs 		= 0x02,	//B5/6/7/8 0x01       [5:4]
		.adcspd 		= 0x00,	//B5/6/7/8 0x01       [2]
		.clplevel 		= 0x02,	//B5/6/7/8 0x01       [1:0]
		.eq_band 		= 0x00,	//B5/6/7/8 0x58       [6:4]
		.lpf_front_band = 0x07,	//B5/6/7/8 0x58       [1:0]
		.clpmode 		= 0x00,	//B5/6/7/8 0x59       [7]
		.f_lpf_bypass 	= 0x00,	//B5/6/7/8 0x59       [4]
		.clproff 		= 0x00,	//B5/6/7/8 0x59       [3]
		.b_lpf_bypass 	= 0x00,	//B5/6/7/8 0x59       [0]
		.duty 			= 0x04,	//B5/6/7/8 0x5B    	  [6:4]
		.ref_vol 		= 0x03,	//B5/6/7/8 0x5B       [1:0]
		.lpf_back_band 	= 0x07,	//B5/6/7/8 0x5C       [6:4]
		.clk_sel 		= 0x01,	//B5/6/7/8 0x5C       [3]
		.eq_gainsel 	= 0x00,	//B5/6/7/8 0x5C       [2:0]
		},
		[ AHD30_5M_20P ] = {
		.powerdown 		= 0x00, //B0       0x00/1/2/3 [0]
		.gain 			= 0x01,	//B0       0x00/1/2/3 [4]
		.spd 			= 0x0D,	//B5/6/7/8 0x00       [5:4]
		.ctrlreg 		= 0x01,	//B5/6/7/8 0x01       [6]
		.ctrlibs 		= 0x02,	//B5/6/7/8 0x01       [5:4]
		.adcspd 		= 0x00,	//B5/6/7/8 0x01       [2]
		.clplevel 		= 0x02,	//B5/6/7/8 0x01       [1:0]
		.eq_band 		= 0x00,	//B5/6/7/8 0x58       [6:4]
		.lpf_front_band = 0x07,	//B5/6/7/8 0x58       [1:0]
		.clpmode 		= 0x00,	//B5/6/7/8 0x59       [7]
		.f_lpf_bypass 	= 0x00,	//B5/6/7/8 0x59       [4]
		.clproff 		= 0x00,	//B5/6/7/8 0x59       [3]
		.b_lpf_bypass 	= 0x00,	//B5/6/7/8 0x59       [0]
		.duty 			= 0x04,	//B5/6/7/8 0x5B    	  [6:4]
		.ref_vol 		= 0x03,	//B5/6/7/8 0x5B       [1:0]
		.lpf_back_band 	= 0x07,	//B5/6/7/8 0x5C       [6:4]
		.clk_sel 		= 0x01,	//B5/6/7/8 0x5C       [3]
		.eq_gainsel 	= 0x00,	//B5/6/7/8 0x5C       [2:0]
		},

		[ AHD30_5_3M_20P ] = {
		.powerdown 		= 0x00, //B0       0x00/1/2/3 [0]
		.gain 			= 0x01,	//B0       0x00/1/2/3 [4]
		.spd 			= 0x0D,	//B5/6/7/8 0x00       [5:4]
		.ctrlreg 		= 0x01,	//B5/6/7/8 0x01       [6]
		.ctrlibs 		= 0x02,	//B5/6/7/8 0x01       [5:4]
		.adcspd 		= 0x00,	//B5/6/7/8 0x01       [2]
		.clplevel 		= 0x02,	//B5/6/7/8 0x01       [1:0]
		.eq_band 		= 0x00,	//B5/6/7/8 0x58       [6:4]
		.lpf_front_band = 0x07,	//B5/6/7/8 0x58       [1:0]
		.clpmode 		= 0x00,	//B5/6/7/8 0x59       [7]
		.f_lpf_bypass 	= 0x00,	//B5/6/7/8 0x59       [4]
		.clproff 		= 0x00,	//B5/6/7/8 0x59       [3]
		.b_lpf_bypass 	= 0x00,	//B5/6/7/8 0x59       [0]
		.duty 			= 0x04,	//B5/6/7/8 0x5B    	  [6:4]
		.ref_vol 		= 0x03,	//B5/6/7/8 0x5B       [1:0]
		.lpf_back_band 	= 0x07,	//B5/6/7/8 0x5C       [6:4]
		.clk_sel 		= 0x01,	//B5/6/7/8 0x5C       [3]
		.eq_gainsel 	= 0x00,	//B5/6/7/8 0x5C       [2:0]
		},
		[ AHD30_6M_18P ] = {
		.powerdown 		= 0x00, //B0       0x00/1/2/3 [0]
		.gain 			= 0x01,	//B0       0x00/1/2/3 [4]
		.spd 			= 0x0D,	//B5/6/7/8 0x00       [5:4]
		.ctrlreg 		= 0x01,	//B5/6/7/8 0x01       [6]
		.ctrlibs 		= 0x02,	//B5/6/7/8 0x01       [5:4]
		.adcspd 		= 0x00,	//B5/6/7/8 0x01       [2]
		.clplevel 		= 0x02,	//B5/6/7/8 0x01       [1:0]
		.eq_band 		= 0x00,	//B5/6/7/8 0x58       [6:4]
		.lpf_front_band = 0x07,	//B5/6/7/8 0x58       [1:0]
		.clpmode 		= 0x00,	//B5/6/7/8 0x59       [7]
		.f_lpf_bypass 	= 0x00,	//B5/6/7/8 0x59       [4]
		.clproff 		= 0x00,	//B5/6/7/8 0x59       [3]
		.b_lpf_bypass 	= 0x00,	//B5/6/7/8 0x59       [0]
		.duty 			= 0x04,	//B5/6/7/8 0x5B    	  [6:4]
		.ref_vol 		= 0x03,	//B5/6/7/8 0x5B       [1:0]
		.lpf_back_band 	= 0x07,	//B5/6/7/8 0x5C       [6:4]
		.clk_sel 		= 0x01,	//B5/6/7/8 0x5C       [3]
		.eq_gainsel 	= 0x00,	//B5/6/7/8 0x5C       [2:0]
		},
		[ AHD30_6M_20P ] = {
		.powerdown 		= 0x00, //B0       0x00/1/2/3 [0]
		.gain 			= 0x01,	//B0       0x00/1/2/3 [4]
		.spd 			= 0x0D,	//B5/6/7/8 0x00       [5:4]
		.ctrlreg 		= 0x01,	//B5/6/7/8 0x01       [6]
		.ctrlibs 		= 0x02,	//B5/6/7/8 0x01       [5:4]
		.adcspd 		= 0x00,	//B5/6/7/8 0x01       [2]
		.clplevel 		= 0x02,	//B5/6/7/8 0x01       [1:0]
		.eq_band 		= 0x00,	//B5/6/7/8 0x58       [6:4]
		.lpf_front_band = 0x07,	//B5/6/7/8 0x58       [1:0]
		.clpmode 		= 0x00,	//B5/6/7/8 0x59       [7]
		.f_lpf_bypass 	= 0x00,	//B5/6/7/8 0x59       [4]
		.clproff 		= 0x00,	//B5/6/7/8 0x59       [3]
		.b_lpf_bypass 	= 0x00,	//B5/6/7/8 0x59       [0]
		.duty 			= 0x04,	//B5/6/7/8 0x5B    	  [6:4]
		.ref_vol 		= 0x03,	//B5/6/7/8 0x5B       [1:0]
		.lpf_back_band 	= 0x07,	//B5/6/7/8 0x5C       [6:4]
		.clk_sel 		= 0x01,	//B5/6/7/8 0x5C       [3]
		.eq_gainsel 	= 0x00,	//B5/6/7/8 0x5C       [2:0]
		},
		[ AHD30_8M_X_30P ] = {
		.powerdown 		= 0x00, //B0       0x00/1/2/3 [0]
		.gain 			= 0x01,	//B0       0x00/1/2/3 [4]
		.spd 			= 0x0D,	//B5/6/7/8 0x00       [5:4]
		.ctrlreg 		= 0x01,	//B5/6/7/8 0x01       [6]
		.ctrlibs 		= 0x02,	//B5/6/7/8 0x01       [5:4]
		.adcspd 		= 0x00,	//B5/6/7/8 0x01       [2]
		.clplevel 		= 0x02,	//B5/6/7/8 0x01       [1:0]
		.eq_band 		= 0x00,	//B5/6/7/8 0x58       [6:4]
		.lpf_front_band = 0x07,	//B5/6/7/8 0x58       [1:0]
		.clpmode 		= 0x00,	//B5/6/7/8 0x59       [7]
		.f_lpf_bypass 	= 0x00,	//B5/6/7/8 0x59       [4]
		.clproff 		= 0x00,	//B5/6/7/8 0x59       [3]
		.b_lpf_bypass 	= 0x00,	//B5/6/7/8 0x59       [0]
		.duty 			= 0x04,	//B5/6/7/8 0x5B    	  [6:4]
		.ref_vol 		= 0x03,	//B5/6/7/8 0x5B       [1:0]
		.lpf_back_band 	= 0x07,	//B5/6/7/8 0x5C       [6:4]
		.clk_sel 		= 0x01,	//B5/6/7/8 0x5C       [3]
		.eq_gainsel 	= 0x00,	//B5/6/7/8 0x5C       [2:0]
		},
		[ AHD30_8M_X_25P ] = {
		.powerdown 		= 0x00, //B0       0x00/1/2/3 [0]
		.gain 			= 0x01,	//B0       0x00/1/2/3 [4]
		.spd 			= 0x0D,	//B5/6/7/8 0x00       [5:4]
		.ctrlreg 		= 0x01,	//B5/6/7/8 0x01       [6]
		.ctrlibs 		= 0x02,	//B5/6/7/8 0x01       [5:4]
		.adcspd 		= 0x00,	//B5/6/7/8 0x01       [2]
		.clplevel 		= 0x02,	//B5/6/7/8 0x01       [1:0]
		.eq_band 		= 0x00,	//B5/6/7/8 0x58       [6:4]
		.lpf_front_band = 0x07,	//B5/6/7/8 0x58       [1:0]
		.clpmode 		= 0x00,	//B5/6/7/8 0x59       [7]
		.f_lpf_bypass 	= 0x00,	//B5/6/7/8 0x59       [4]
		.clproff 		= 0x00,	//B5/6/7/8 0x59       [3]
		.b_lpf_bypass 	= 0x00,	//B5/6/7/8 0x59       [0]
		.duty 			= 0x04,	//B5/6/7/8 0x5B    	  [6:4]
		.ref_vol 		= 0x03,	//B5/6/7/8 0x5B       [1:0]
		.lpf_back_band 	= 0x07,	//B5/6/7/8 0x5C       [6:4]
		.clk_sel 		= 0x01,	//B5/6/7/8 0x5C       [3]
		.eq_gainsel 	= 0x00,	//B5/6/7/8 0x5C       [2:0]
		},
		[ AHD30_8M_7_5P ] = {
		.powerdown 		= 0x00, //B0       0x00/1/2/3 [0]
		.gain 			= 0x01,	//B0       0x00/1/2/3 [4]
		.spd 			= 0x0D,	//B5/6/7/8 0x00       [5:4]
		.ctrlreg 		= 0x01,	//B5/6/7/8 0x01       [6]
		.ctrlibs 		= 0x02,	//B5/6/7/8 0x01       [5:4]
		.adcspd 		= 0x00,	//B5/6/7/8 0x01       [2]
		.clplevel 		= 0x02,	//B5/6/7/8 0x01       [1:0]
		.eq_band 		= 0x00,	//B5/6/7/8 0x58       [6:4]
		.lpf_front_band = 0x07,	//B5/6/7/8 0x58       [1:0]
		.clpmode 		= 0x00,	//B5/6/7/8 0x59       [7]
		.f_lpf_bypass 	= 0x00,	//B5/6/7/8 0x59       [4]
		.clproff 		= 0x00,	//B5/6/7/8 0x59       [3]
		.b_lpf_bypass 	= 0x00,	//B5/6/7/8 0x59       [0]
		.duty 			= 0x04,	//B5/6/7/8 0x5B    	  [6:4]
		.ref_vol 		= 0x03,	//B5/6/7/8 0x5B       [1:0]
		.lpf_back_band 	= 0x07,	//B5/6/7/8 0x5C       [6:4]
		.clk_sel 		= 0x01,	//B5/6/7/8 0x5C       [3]
		.eq_gainsel 	= 0x00,	//B5/6/7/8 0x5C       [2:0]
		},
		[ AHD30_8M_12_5P ] = {
		.powerdown 		= 0x00, //B0       0x00/1/2/3 [0]
		.gain 			= 0x01,	//B0       0x00/1/2/3 [4]
		.spd 			= 0x0D,	//B5/6/7/8 0x00       [5:4]
		.ctrlreg 		= 0x01,	//B5/6/7/8 0x01       [6]
		.ctrlibs 		= 0x02,	//B5/6/7/8 0x01       [5:4]
		.adcspd 		= 0x00,	//B5/6/7/8 0x01       [2]
		.clplevel 		= 0x02,	//B5/6/7/8 0x01       [1:0]
		.eq_band 		= 0x00,	//B5/6/7/8 0x58       [6:4]
		.lpf_front_band = 0x07,	//B5/6/7/8 0x58       [1:0]
		.clpmode 		= 0x00,	//B5/6/7/8 0x59       [7]
		.f_lpf_bypass 	= 0x00,	//B5/6/7/8 0x59       [4]
		.clproff 		= 0x00,	//B5/6/7/8 0x59       [3]
		.b_lpf_bypass 	= 0x00,	//B5/6/7/8 0x59       [0]
		.duty 			= 0x04,	//B5/6/7/8 0x5B    	  [6:4]
		.ref_vol 		= 0x03,	//B5/6/7/8 0x5B       [1:0]
		.lpf_back_band 	= 0x07,	//B5/6/7/8 0x5C       [6:4]
		.clk_sel 		= 0x01,	//B5/6/7/8 0x5C       [3]
		.eq_gainsel 	= 0x00,	//B5/6/7/8 0x5C       [2:0]
		},
		[ AHD30_8M_15P ] = {
		.powerdown 		= 0x00, //B0       0x00/1/2/3 [0]
		.gain 			= 0x01,	//B0       0x00/1/2/3 [4]
		.spd 			= 0x0D,	//B5/6/7/8 0x00       [5:4]
		.ctrlreg 		= 0x01,	//B5/6/7/8 0x01       [6]
		.ctrlibs 		= 0x02,	//B5/6/7/8 0x01       [5:4]
		.adcspd 		= 0x00,	//B5/6/7/8 0x01       [2]
		.clplevel 		= 0x02,	//B5/6/7/8 0x01       [1:0]
		.eq_band 		= 0x00,	//B5/6/7/8 0x58       [6:4]
		.lpf_front_band = 0x07,	//B5/6/7/8 0x58       [1:0]
		.clpmode 		= 0x00,	//B5/6/7/8 0x59       [7]
		.f_lpf_bypass 	= 0x00,	//B5/6/7/8 0x59       [4]
		.clproff 		= 0x00,	//B5/6/7/8 0x59       [3]
		.b_lpf_bypass 	= 0x00,	//B5/6/7/8 0x59       [0]
		.duty 			= 0x04,	//B5/6/7/8 0x5B    	  [6:4]
		.ref_vol 		= 0x03,	//B5/6/7/8 0x5B       [1:0]
		.lpf_back_band 	= 0x07,	//B5/6/7/8 0x5C       [6:4]
		.clk_sel 		= 0x01,	//B5/6/7/8 0x5C       [3]
		.eq_gainsel 	= 0x00,	//B5/6/7/8 0x5C       [2:0]
		},

		[ TVI_FHD_30P ] = {
			    .powerdown = 0,
			    .gain =  1,
			    .spd = 0xD,
			    .ctrlreg= 1,
			    .ctrlibs= 2,
			    .adcspd = 0,
			    .clplevel = 2,
			    .eq_band = 0,
			    .lpf_front_band = 7,
			    .clpmode = 0,
			    .f_lpf_bypass = 0,
			    .clproff = 0,
			    .b_lpf_bypass = 0,
			    .duty = 4,
			    .ref_vol = 1,
			    .lpf_back_band = 7,
			    .clk_sel = 1,
			    .eq_gainsel = 0,

		},
		[ TVI_FHD_25P ] = {
			    .powerdown = 0,
			    .gain =  1,
			    .spd = 0xD,
			    .ctrlreg= 1,
			    .ctrlibs= 2,
			    .adcspd = 0,
			    .clplevel = 2,
			    .eq_band = 0,
			    .lpf_front_band = 7,
			    .clpmode = 0,
			    .f_lpf_bypass = 0,
			    .clproff = 0,
			    .b_lpf_bypass = 0,
			    .duty = 4,
			    .ref_vol = 1,
			    .lpf_back_band = 7,
			    .clk_sel = 1,
			    .eq_gainsel = 0,

		},
		[ TVI_HD_60P ] = {
		.powerdown 		= 0x00, //B0       0x00/1/2/3 [0]
		.gain 			= 0x01,	//B0       0x00/1/2/3 [4]
		.spd 			= 0x0D,	//B5/6/7/8 0x00       [5:4]
		.ctrlreg 		= 0x01,	//B5/6/7/8 0x01       [6]
		.ctrlibs 		= 0x02,	//B5/6/7/8 0x01       [5:4]
		.adcspd 		= 0x00,	//B5/6/7/8 0x01       [2]
		.clplevel 		= 0x02,	//B5/6/7/8 0x01       [1:0]
		.eq_band 		= 0x00,	//B5/6/7/8 0x58       [6:4]
		.lpf_front_band = 0x07,	//B5/6/7/8 0x58       [1:0]
		.clpmode 		= 0x00,	//B5/6/7/8 0x59       [7]
		.f_lpf_bypass 	= 0x00,	//B5/6/7/8 0x59       [4]
		.clproff 		= 0x00,	//B5/6/7/8 0x59       [3]
		.b_lpf_bypass 	= 0x00,	//B5/6/7/8 0x59       [0]
		.duty 			= 0x04,	//B5/6/7/8 0x5B    	  [6:4]
		.ref_vol 		= 0x03,	//B5/6/7/8 0x5B       [1:0]
		.lpf_back_band 	= 0x07,	//B5/6/7/8 0x5C       [6:4]
		.clk_sel 		= 0x01,	//B5/6/7/8 0x5C       [3]
		.eq_gainsel 	= 0x00,	//B5/6/7/8 0x5C       [2:0]
		},
		[ TVI_HD_50P ] = {
		.powerdown 		= 0x00, //B0       0x00/1/2/3 [0]
		.gain 			= 0x01,	//B0       0x00/1/2/3 [4]
		.spd 			= 0x0D,	//B5/6/7/8 0x00       [5:4]
		.ctrlreg 		= 0x01,	//B5/6/7/8 0x01       [6]
		.ctrlibs 		= 0x02,	//B5/6/7/8 0x01       [5:4]
		.adcspd 		= 0x00,	//B5/6/7/8 0x01       [2]
		.clplevel 		= 0x02,	//B5/6/7/8 0x01       [1:0]
		.eq_band 		= 0x00,	//B5/6/7/8 0x58       [6:4]
		.lpf_front_band = 0x07,	//B5/6/7/8 0x58       [1:0]
		.clpmode 		= 0x00,	//B5/6/7/8 0x59       [7]
		.f_lpf_bypass 	= 0x00,	//B5/6/7/8 0x59       [4]
		.clproff 		= 0x00,	//B5/6/7/8 0x59       [3]
		.b_lpf_bypass 	= 0x00,	//B5/6/7/8 0x59       [0]
		.duty 			= 0x04,	//B5/6/7/8 0x5B    	  [6:4]
		.ref_vol 		= 0x03,	//B5/6/7/8 0x5B       [1:0]
		.lpf_back_band 	= 0x07,	//B5/6/7/8 0x5C       [6:4]
		.clk_sel 		= 0x01,	//B5/6/7/8 0x5C       [3]
		.eq_gainsel 	= 0x00,	//B5/6/7/8 0x5C       [2:0]
		},
		[ TVI_HD_30P ] = {
		.powerdown 		= 0x00, //B0       0x00/1/2/3 [0]
		.gain 			= 0x01,	//B0       0x00/1/2/3 [4]
		.spd 			= 0x0D,	//B5/6/7/8 0x00       [5:4]
		.ctrlreg 		= 0x01,	//B5/6/7/8 0x01       [6]
		.ctrlibs 		= 0x02,	//B5/6/7/8 0x01       [5:4]
		.adcspd 		= 0x00,	//B5/6/7/8 0x01       [2]
		.clplevel 		= 0x02,	//B5/6/7/8 0x01       [1:0]
		.eq_band 		= 0x00,	//B5/6/7/8 0x58       [6:4]
		.lpf_front_band = 0x07,	//B5/6/7/8 0x58       [1:0]
		.clpmode 		= 0x00,	//B5/6/7/8 0x59       [7]
		.f_lpf_bypass 	= 0x00,	//B5/6/7/8 0x59       [4]
		.clproff 		= 0x00,	//B5/6/7/8 0x59       [3]
		.b_lpf_bypass 	= 0x00,	//B5/6/7/8 0x59       [0]
		.duty 			= 0x04,	//B5/6/7/8 0x5B    	  [6:4]
		.ref_vol 		= 0x03,	//B5/6/7/8 0x5B       [1:0]
		.lpf_back_band 	= 0x07,	//B5/6/7/8 0x5C       [6:4]
		.clk_sel 		= 0x01,	//B5/6/7/8 0x5C       [3]
		.eq_gainsel 	= 0x00,	//B5/6/7/8 0x5C       [2:0]
		},
		[ TVI_HD_25P ] = {
		.powerdown 		= 0x00, //B0       0x00/1/2/3 [0]
		.gain 			= 0x01,	//B0       0x00/1/2/3 [4]
		.spd 			= 0x0D,	//B5/6/7/8 0x00       [5:4]
		.ctrlreg 		= 0x01,	//B5/6/7/8 0x01       [6]
		.ctrlibs 		= 0x02,	//B5/6/7/8 0x01       [5:4]
		.adcspd 		= 0x00,	//B5/6/7/8 0x01       [2]
		.clplevel 		= 0x02,	//B5/6/7/8 0x01       [1:0]
		.eq_band 		= 0x00,	//B5/6/7/8 0x58       [6:4]
		.lpf_front_band = 0x07,	//B5/6/7/8 0x58       [1:0]
		.clpmode 		= 0x00,	//B5/6/7/8 0x59       [7]
		.f_lpf_bypass 	= 0x00,	//B5/6/7/8 0x59       [4]
		.clproff 		= 0x00,	//B5/6/7/8 0x59       [3]
		.b_lpf_bypass 	= 0x00,	//B5/6/7/8 0x59       [0]
		.duty 			= 0x04,	//B5/6/7/8 0x5B    	  [6:4]
		.ref_vol 		= 0x03,	//B5/6/7/8 0x5B       [1:0]
		.lpf_back_band 	= 0x07,	//B5/6/7/8 0x5C       [6:4]
		.clk_sel 		= 0x01,	//B5/6/7/8 0x5C       [3]
		.eq_gainsel 	= 0x00,	//B5/6/7/8 0x5C       [2:0]
		},
		[ TVI_HD_30P_EX ] = {
		.powerdown 		= 0x00, //B0       0x00/1/2/3 [0]
		.gain 			= 0x01,	//B0       0x00/1/2/3 [4]
		.spd 			= 0x0D,	//B5/6/7/8 0x00       [5:4]
		.ctrlreg 		= 0x01,	//B5/6/7/8 0x01       [6]
		.ctrlibs 		= 0x02,	//B5/6/7/8 0x01       [5:4]
		.adcspd 		= 0x00,	//B5/6/7/8 0x01       [2]
		.clplevel 		= 0x02,	//B5/6/7/8 0x01       [1:0]
		.eq_band 		= 0x00,	//B5/6/7/8 0x58       [6:4]
		.lpf_front_band = 0x07,	//B5/6/7/8 0x58       [1:0]
		.clpmode 		= 0x00,	//B5/6/7/8 0x59       [7]
		.f_lpf_bypass 	= 0x00,	//B5/6/7/8 0x59       [4]
		.clproff 		= 0x00,	//B5/6/7/8 0x59       [3]
		.b_lpf_bypass 	= 0x00,	//B5/6/7/8 0x59       [0]
		.duty 			= 0x04,	//B5/6/7/8 0x5B    	  [6:4]
		.ref_vol 		= 0x03,	//B5/6/7/8 0x5B       [1:0]
		.lpf_back_band 	= 0x07,	//B5/6/7/8 0x5C       [6:4]
		.clk_sel 		= 0x01,	//B5/6/7/8 0x5C       [3]
		.eq_gainsel 	= 0x00,	//B5/6/7/8 0x5C       [2:0]
		},
		[ TVI_HD_25P_EX ] = {
		.powerdown 		= 0x00, //B0       0x00/1/2/3 [0]
		.gain 			= 0x01,	//B0       0x00/1/2/3 [4]
		.spd 			= 0x0D,	//B5/6/7/8 0x00       [5:4]
		.ctrlreg 		= 0x01,	//B5/6/7/8 0x01       [6]
		.ctrlibs 		= 0x02,	//B5/6/7/8 0x01       [5:4]
		.adcspd 		= 0x00,	//B5/6/7/8 0x01       [2]
		.clplevel 		= 0x02,	//B5/6/7/8 0x01       [1:0]
		.eq_band 		= 0x00,	//B5/6/7/8 0x58       [6:4]
		.lpf_front_band = 0x07,	//B5/6/7/8 0x58       [1:0]
		.clpmode 		= 0x00,	//B5/6/7/8 0x59       [7]
		.f_lpf_bypass 	= 0x00,	//B5/6/7/8 0x59       [4]
		.clproff 		= 0x00,	//B5/6/7/8 0x59       [3]
		.b_lpf_bypass 	= 0x00,	//B5/6/7/8 0x59       [0]
		.duty 			= 0x04,	//B5/6/7/8 0x5B    	  [6:4]
		.ref_vol 		= 0x03,	//B5/6/7/8 0x5B       [1:0]
		.lpf_back_band 	= 0x07,	//B5/6/7/8 0x5C       [6:4]
		.clk_sel 		= 0x01,	//B5/6/7/8 0x5C       [3]
		.eq_gainsel 	= 0x00,	//B5/6/7/8 0x5C       [2:0]
		},
		[ TVI_HD_B_30P ] = {
		.powerdown 		= 0x00, //B0       0x00/1/2/3 [0]
		.gain 			= 0x01,	//B0       0x00/1/2/3 [4]
		.spd 			= 0x0D,	//B5/6/7/8 0x00       [5:4]
		.ctrlreg 		= 0x01,	//B5/6/7/8 0x01       [6]
		.ctrlibs 		= 0x02,	//B5/6/7/8 0x01       [5:4]
		.adcspd 		= 0x00,	//B5/6/7/8 0x01       [2]
		.clplevel 		= 0x02,	//B5/6/7/8 0x01       [1:0]
		.eq_band 		= 0x00,	//B5/6/7/8 0x58       [6:4]
		.lpf_front_band = 0x07,	//B5/6/7/8 0x58       [1:0]
		.clpmode 		= 0x00,	//B5/6/7/8 0x59       [7]
		.f_lpf_bypass 	= 0x00,	//B5/6/7/8 0x59       [4]
		.clproff 		= 0x00,	//B5/6/7/8 0x59       [3]
		.b_lpf_bypass 	= 0x00,	//B5/6/7/8 0x59       [0]
		.duty 			= 0x04,	//B5/6/7/8 0x5B    	  [6:4]
		.ref_vol 		= 0x03,	//B5/6/7/8 0x5B       [1:0]
		.lpf_back_band 	= 0x07,	//B5/6/7/8 0x5C       [6:4]
		.clk_sel 		= 0x01,	//B5/6/7/8 0x5C       [3]
		.eq_gainsel 	= 0x00,	//B5/6/7/8 0x5C       [2:0]
		},
		[ TVI_HD_B_25P ] = {
		.powerdown 		= 0x00, //B0       0x00/1/2/3 [0]
		.gain 			= 0x01,	//B0       0x00/1/2/3 [4]
		.spd 			= 0x0D,	//B5/6/7/8 0x00       [5:4]
		.ctrlreg 		= 0x01,	//B5/6/7/8 0x01       [6]
		.ctrlibs 		= 0x02,	//B5/6/7/8 0x01       [5:4]
		.adcspd 		= 0x00,	//B5/6/7/8 0x01       [2]
		.clplevel 		= 0x02,	//B5/6/7/8 0x01       [1:0]
		.eq_band 		= 0x00,	//B5/6/7/8 0x58       [6:4]
		.lpf_front_band = 0x07,	//B5/6/7/8 0x58       [1:0]
		.clpmode 		= 0x00,	//B5/6/7/8 0x59       [7]
		.f_lpf_bypass 	= 0x00,	//B5/6/7/8 0x59       [4]
		.clproff 		= 0x00,	//B5/6/7/8 0x59       [3]
		.b_lpf_bypass 	= 0x00,	//B5/6/7/8 0x59       [0]
		.duty 			= 0x04,	//B5/6/7/8 0x5B    	  [6:4]
		.ref_vol 		= 0x03,	//B5/6/7/8 0x5B       [1:0]
		.lpf_back_band 	= 0x07,	//B5/6/7/8 0x5C       [6:4]
		.clk_sel 		= 0x01,	//B5/6/7/8 0x5C       [3]
		.eq_gainsel 	= 0x00,	//B5/6/7/8 0x5C       [2:0]
		},
		[ TVI_HD_B_30P_EX ] = {
		.powerdown 		= 0x00, //B0       0x00/1/2/3 [0]
		.gain 			= 0x01,	//B0       0x00/1/2/3 [4]
		.spd 			= 0x0D,	//B5/6/7/8 0x00       [5:4]
		.ctrlreg 		= 0x01,	//B5/6/7/8 0x01       [6]
		.ctrlibs 		= 0x02,	//B5/6/7/8 0x01       [5:4]
		.adcspd 		= 0x00,	//B5/6/7/8 0x01       [2]
		.clplevel 		= 0x02,	//B5/6/7/8 0x01       [1:0]
		.eq_band 		= 0x00,	//B5/6/7/8 0x58       [6:4]
		.lpf_front_band = 0x07,	//B5/6/7/8 0x58       [1:0]
		.clpmode 		= 0x00,	//B5/6/7/8 0x59       [7]
		.f_lpf_bypass 	= 0x00,	//B5/6/7/8 0x59       [4]
		.clproff 		= 0x00,	//B5/6/7/8 0x59       [3]
		.b_lpf_bypass 	= 0x00,	//B5/6/7/8 0x59       [0]
		.duty 			= 0x04,	//B5/6/7/8 0x5B    	  [6:4]
		.ref_vol 		= 0x03,	//B5/6/7/8 0x5B       [1:0]
		.lpf_back_band 	= 0x07,	//B5/6/7/8 0x5C       [6:4]
		.clk_sel 		= 0x01,	//B5/6/7/8 0x5C       [3]
		.eq_gainsel 	= 0x00,	//B5/6/7/8 0x5C       [2:0]
		},
		[ TVI_HD_B_25P_EX ] = {
		.powerdown 		= 0x00, //B0       0x00/1/2/3 [0]
		.gain 			= 0x01,	//B0       0x00/1/2/3 [4]
		.spd 			= 0x0D,	//B5/6/7/8 0x00       [5:4]
		.ctrlreg 		= 0x01,	//B5/6/7/8 0x01       [6]
		.ctrlibs 		= 0x02,	//B5/6/7/8 0x01       [5:4]
		.adcspd 		= 0x00,	//B5/6/7/8 0x01       [2]
		.clplevel 		= 0x02,	//B5/6/7/8 0x01       [1:0]
		.eq_band 		= 0x00,	//B5/6/7/8 0x58       [6:4]
		.lpf_front_band = 0x07,	//B5/6/7/8 0x58       [1:0]
		.clpmode 		= 0x00,	//B5/6/7/8 0x59       [7]
		.f_lpf_bypass 	= 0x00,	//B5/6/7/8 0x59       [4]
		.clproff 		= 0x00,	//B5/6/7/8 0x59       [3]
		.b_lpf_bypass 	= 0x00,	//B5/6/7/8 0x59       [0]
		.duty 			= 0x04,	//B5/6/7/8 0x5B    	  [6:4]
		.ref_vol 		= 0x03,	//B5/6/7/8 0x5B       [1:0]
		.lpf_back_band 	= 0x07,	//B5/6/7/8 0x5C       [6:4]
		.clk_sel 		= 0x01,	//B5/6/7/8 0x5C       [3]
		.eq_gainsel 	= 0x00,	//B5/6/7/8 0x5C       [2:0]
		},
		[ TVI_3M_18P ] = {
		.powerdown 		= 0x00, //B0       0x00/1/2/3 [0]
		.gain 			= 0x01,	//B0       0x00/1/2/3 [4]
		.spd 			= 0x0D,	//B5/6/7/8 0x00       [5:4]
		.ctrlreg 		= 0x01,	//B5/6/7/8 0x01       [6]
		.ctrlibs 		= 0x02,	//B5/6/7/8 0x01       [5:4]
		.adcspd 		= 0x00,	//B5/6/7/8 0x01       [2]
		.clplevel 		= 0x02,	//B5/6/7/8 0x01       [1:0]
		.eq_band 		= 0x00,	//B5/6/7/8 0x58       [6:4]
		.lpf_front_band = 0x07,	//B5/6/7/8 0x58       [1:0]
		.clpmode 		= 0x00,	//B5/6/7/8 0x59       [7]
		.f_lpf_bypass 	= 0x00,	//B5/6/7/8 0x59       [4]
		.clproff 		= 0x00,	//B5/6/7/8 0x59       [3]
		.b_lpf_bypass 	= 0x00,	//B5/6/7/8 0x59       [0]
		.duty 			= 0x04,	//B5/6/7/8 0x5B    	  [6:4]
		.ref_vol 		= 0x03,	//B5/6/7/8 0x5B       [1:0]
		.lpf_back_band 	= 0x07,	//B5/6/7/8 0x5C       [6:4]
		.clk_sel 		= 0x01,	//B5/6/7/8 0x5C       [3]
		.eq_gainsel 	= 0x00,	//B5/6/7/8 0x5C       [2:0]
		},
		[ TVI_5M_12_5P ] = {
		.powerdown 		= 0x00, //B0       0x00/1/2/3 [0]
		.gain 			= 0x01,	//B0       0x00/1/2/3 [4]
		.spd 			= 0x0D,	//B5/6/7/8 0x00       [5:4]
		.ctrlreg 		= 0x01,	//B5/6/7/8 0x01       [6]
		.ctrlibs 		= 0x02,	//B5/6/7/8 0x01       [5:4]
		.adcspd 		= 0x00,	//B5/6/7/8 0x01       [2]
		.clplevel 		= 0x02,	//B5/6/7/8 0x01       [1:0]
		.eq_band 		= 0x00,	//B5/6/7/8 0x58       [6:4]
		.lpf_front_band = 0x07,	//B5/6/7/8 0x58       [1:0]
		.clpmode 		= 0x00,	//B5/6/7/8 0x59       [7]
		.f_lpf_bypass 	= 0x00,	//B5/6/7/8 0x59       [4]
		.clproff 		= 0x00,	//B5/6/7/8 0x59       [3]
		.b_lpf_bypass 	= 0x00,	//B5/6/7/8 0x59       [0]
		.duty 			= 0x04,	//B5/6/7/8 0x5B    	  [6:4]
		.ref_vol 		= 0x03,	//B5/6/7/8 0x5B       [1:0]
		.lpf_back_band 	= 0x07,	//B5/6/7/8 0x5C       [6:4]
		.clk_sel 		= 0x01,	//B5/6/7/8 0x5C       [3]
		.eq_gainsel 	= 0x00,	//B5/6/7/8 0x5C       [2:0]
		},

		[ TVI_5M_20P ] = {
				.powerdown = 0,
				.gain =  1,
				.spd = 0xD,
				.ctrlreg= 1,
				.ctrlibs= 2,
				.adcspd = 0,
				.clplevel = 2,
				.eq_band = 0,
				.lpf_front_band = 7,
				.clpmode = 0,
				.f_lpf_bypass =0,
				.clproff = 0,
				.b_lpf_bypass = 0,
				.duty = 4,
				.ref_vol = 1,
				.lpf_back_band = 7,
				.clk_sel = 1,
				.eq_gainsel = 0,

		},



		[ TVI_4M_30P ] = {
			    .powerdown = 0,
			    .gain =  1,
			    .spd = 0xD,
			    .ctrlreg= 1,
			    .ctrlibs= 2,
			    .adcspd = 0,
			    .clplevel = 2,
			    .eq_band = 0,
			    .lpf_front_band = 7,
			    .clpmode = 0,
			    .f_lpf_bypass =0,
			    .clproff = 0,
			    .b_lpf_bypass = 0,
			    .duty = 4,
			    .ref_vol = 1,
			    .lpf_back_band = 7,
			    .clk_sel = 1,
			    .eq_gainsel = 0,

		},
		[ TVI_4M_25P ] = {
			    .powerdown = 0,
			    .gain =  1,
			    .spd = 0xD,
			    .ctrlreg= 1,
			    .ctrlibs= 2,
			    .adcspd = 0,
			    .clplevel = 2,
			    .eq_band = 0,
			    .lpf_front_band = 7,
			    .clpmode = 0,
			    .f_lpf_bypass = 0,
			    .clproff = 0,
			    .b_lpf_bypass = 0,
			    .duty = 4,
			    .ref_vol = 1,
			    .lpf_back_band = 7,
			    .clk_sel = 1,
			    .eq_gainsel = 0,
		},
		[ TVI_4M_15P ] = {
		.powerdown 		= 0x00, //B0       0x00/1/2/3 [0]
		.gain 			= 0x01,	//B0       0x00/1/2/3 [4]
		.spd 			= 0x0D,	//B5/6/7/8 0x00       [5:4]
		.ctrlreg 		= 0x01,	//B5/6/7/8 0x01       [6]
		.ctrlibs 		= 0x02,	//B5/6/7/8 0x01       [5:4]
		.adcspd 		= 0x00,	//B5/6/7/8 0x01       [2]
		.clplevel 		= 0x02,	//B5/6/7/8 0x01       [1:0]
		.eq_band 		= 0x00,	//B5/6/7/8 0x58       [6:4]
		.lpf_front_band = 0x07,	//B5/6/7/8 0x58       [1:0]
		.clpmode 		= 0x00,	//B5/6/7/8 0x59       [7]
		.f_lpf_bypass 	= 0x00,	//B5/6/7/8 0x59       [4]
		.clproff 		= 0x00,	//B5/6/7/8 0x59       [3]
		.b_lpf_bypass 	= 0x00,	//B5/6/7/8 0x59       [0]
		.duty 			= 0x04,	//B5/6/7/8 0x5B    	  [6:4]
		.ref_vol 		= 0x03,	//B5/6/7/8 0x5B       [1:0]
		.lpf_back_band 	= 0x07,	//B5/6/7/8 0x5C       [6:4]
		.clk_sel 		= 0x01,	//B5/6/7/8 0x5C       [3]
		.eq_gainsel 	= 0x00,	//B5/6/7/8 0x5C       [2:0]
		},
		[ CVI_FHD_30P ] = {
			    .powerdown = 0,
			    .gain =  1,
			    .spd = 0xD,
			    .ctrlreg= 1,
			    .ctrlibs= 2,
			    .adcspd = 0,
			    .clplevel = 2,
			    .eq_band = 0,
			    .lpf_front_band = 7,
			    .clpmode = 0,
			    .f_lpf_bypass = 0,
			    .clproff = 0,
			    .b_lpf_bypass = 0,
			    .duty = 4,
			    .ref_vol = 1,
			    .lpf_back_band = 7,
			    .clk_sel = 1,
			    .eq_gainsel = 0,

		},
		[ CVI_FHD_25P ] = {
			    .powerdown = 0,
			    .gain =  1,
			    .spd = 0xD,
			    .ctrlreg= 1,
			    .ctrlibs= 2,
			    .adcspd = 0,
			    .clplevel = 2,
			    .eq_band = 0,
			    .lpf_front_band = 7,
			    .clpmode = 0,
			    .f_lpf_bypass = 0,
			    .clproff = 0,
			    .b_lpf_bypass = 0,
			    .duty = 4,
			    .ref_vol = 1,
			    .lpf_back_band = 7,
			    .clk_sel = 1,
			    .eq_gainsel = 0,

		},
		[ CVI_HD_60P ] = {
		.powerdown 		= 0x00, //B0       0x00/1/2/3 [0]
		.gain 			= 0x01,	//B0       0x00/1/2/3 [4]
		.spd 			= 0x0D,	//B5/6/7/8 0x00       [5:4]
		.ctrlreg 		= 0x01,	//B5/6/7/8 0x01       [6]
		.ctrlibs 		= 0x02,	//B5/6/7/8 0x01       [5:4]
		.adcspd 		= 0x00,	//B5/6/7/8 0x01       [2]
		.clplevel 		= 0x02,	//B5/6/7/8 0x01       [1:0]
		.eq_band 		= 0x00,	//B5/6/7/8 0x58       [6:4]
		.lpf_front_band = 0x07,	//B5/6/7/8 0x58       [1:0]
		.clpmode 		= 0x00,	//B5/6/7/8 0x59       [7]
		.f_lpf_bypass 	= 0x00,	//B5/6/7/8 0x59       [4]
		.clproff 		= 0x00,	//B5/6/7/8 0x59       [3]
		.b_lpf_bypass 	= 0x00,	//B5/6/7/8 0x59       [0]
		.duty 			= 0x04,	//B5/6/7/8 0x5B    	  [6:4]
		.ref_vol 		= 0x03,	//B5/6/7/8 0x5B       [1:0]
		.lpf_back_band 	= 0x07,	//B5/6/7/8 0x5C       [6:4]
		.clk_sel 		= 0x01,	//B5/6/7/8 0x5C       [3]
		.eq_gainsel 	= 0x00,	//B5/6/7/8 0x5C       [2:0]
		},
		[ CVI_HD_50P ] = {
		.powerdown 		= 0x00, //B0       0x00/1/2/3 [0]
		.gain 			= 0x01,	//B0       0x00/1/2/3 [4]
		.spd 			= 0x0D,	//B5/6/7/8 0x00       [5:4]
		.ctrlreg 		= 0x01,	//B5/6/7/8 0x01       [6]
		.ctrlibs 		= 0x02,	//B5/6/7/8 0x01       [5:4]
		.adcspd 		= 0x00,	//B5/6/7/8 0x01       [2]
		.clplevel 		= 0x02,	//B5/6/7/8 0x01       [1:0]
		.eq_band 		= 0x00,	//B5/6/7/8 0x58       [6:4]
		.lpf_front_band = 0x07,	//B5/6/7/8 0x58       [1:0]
		.clpmode 		= 0x00,	//B5/6/7/8 0x59       [7]
		.f_lpf_bypass 	= 0x00,	//B5/6/7/8 0x59       [4]
		.clproff 		= 0x00,	//B5/6/7/8 0x59       [3]
		.b_lpf_bypass 	= 0x00,	//B5/6/7/8 0x59       [0]
		.duty 			= 0x04,	//B5/6/7/8 0x5B    	  [6:4]
		.ref_vol 		= 0x03,	//B5/6/7/8 0x5B       [1:0]
		.lpf_back_band 	= 0x07,	//B5/6/7/8 0x5C       [6:4]
		.clk_sel 		= 0x01,	//B5/6/7/8 0x5C       [3]
		.eq_gainsel 	= 0x00,	//B5/6/7/8 0x5C       [2:0]
		},
		[ CVI_HD_30P ] = {
		.powerdown 		= 0x00, //B0       0x00/1/2/3 [0]
		.gain 			= 0x01,	//B0       0x00/1/2/3 [4]
		.spd 			= 0x0D,	//B5/6/7/8 0x00       [5:4]
		.ctrlreg 		= 0x01,	//B5/6/7/8 0x01       [6]
		.ctrlibs 		= 0x02,	//B5/6/7/8 0x01       [5:4]
		.adcspd 		= 0x00,	//B5/6/7/8 0x01       [2]
		.clplevel 		= 0x02,	//B5/6/7/8 0x01       [1:0]
		.eq_band 		= 0x00,	//B5/6/7/8 0x58       [6:4]
		.lpf_front_band = 0x07,	//B5/6/7/8 0x58       [1:0]
		.clpmode 		= 0x00,	//B5/6/7/8 0x59       [7]
		.f_lpf_bypass 	= 0x00,	//B5/6/7/8 0x59       [4]
		.clproff 		= 0x00,	//B5/6/7/8 0x59       [3]
		.b_lpf_bypass 	= 0x00,	//B5/6/7/8 0x59       [0]
		.duty 			= 0x04,	//B5/6/7/8 0x5B    	  [6:4]
		.ref_vol 		= 0x03,	//B5/6/7/8 0x5B       [1:0]
		.lpf_back_band 	= 0x07,	//B5/6/7/8 0x5C       [6:4]
		.clk_sel 		= 0x01,	//B5/6/7/8 0x5C       [3]
		.eq_gainsel 	= 0x00,	//B5/6/7/8 0x5C       [2:0]
		},
		[ CVI_HD_25P ] = {
		.powerdown 		= 0x00, //B0       0x00/1/2/3 [0]
		.gain 			= 0x01,	//B0       0x00/1/2/3 [4]
		.spd 			= 0x0D,	//B5/6/7/8 0x00       [5:4]
		.ctrlreg 		= 0x01,	//B5/6/7/8 0x01       [6]
		.ctrlibs 		= 0x02,	//B5/6/7/8 0x01       [5:4]
		.adcspd 		= 0x00,	//B5/6/7/8 0x01       [2]
		.clplevel 		= 0x02,	//B5/6/7/8 0x01       [1:0]
		.eq_band 		= 0x00,	//B5/6/7/8 0x58       [6:4]
		.lpf_front_band = 0x07,	//B5/6/7/8 0x58       [1:0]
		.clpmode 		= 0x00,	//B5/6/7/8 0x59       [7]
		.f_lpf_bypass 	= 0x00,	//B5/6/7/8 0x59       [4]
		.clproff 		= 0x00,	//B5/6/7/8 0x59       [3]
		.b_lpf_bypass 	= 0x00,	//B5/6/7/8 0x59       [0]
		.duty 			= 0x04,	//B5/6/7/8 0x5B    	  [6:4]
		.ref_vol 		= 0x03,	//B5/6/7/8 0x5B       [1:0]
		.lpf_back_band 	= 0x07,	//B5/6/7/8 0x5C       [6:4]
		.clk_sel 		= 0x01,	//B5/6/7/8 0x5C       [3]
		.eq_gainsel 	= 0x00,	//B5/6/7/8 0x5C       [2:0]
		},
		[ CVI_HD_30P_EX ] = {
		.powerdown 		= 0x00, //B0       0x00/1/2/3 [0]
		.gain 			= 0x01,	//B0       0x00/1/2/3 [4]
		.spd 			= 0x0D,	//B5/6/7/8 0x00       [5:4]
		.ctrlreg 		= 0x01,	//B5/6/7/8 0x01       [6]
		.ctrlibs 		= 0x02,	//B5/6/7/8 0x01       [5:4]
		.adcspd 		= 0x00,	//B5/6/7/8 0x01       [2]
		.clplevel 		= 0x02,	//B5/6/7/8 0x01       [1:0]
		.eq_band 		= 0x00,	//B5/6/7/8 0x58       [6:4]
		.lpf_front_band = 0x07,	//B5/6/7/8 0x58       [1:0]
		.clpmode 		= 0x00,	//B5/6/7/8 0x59       [7]
		.f_lpf_bypass 	= 0x00,	//B5/6/7/8 0x59       [4]
		.clproff 		= 0x00,	//B5/6/7/8 0x59       [3]
		.b_lpf_bypass 	= 0x00,	//B5/6/7/8 0x59       [0]
		.duty 			= 0x04,	//B5/6/7/8 0x5B    	  [6:4]
		.ref_vol 		= 0x03,	//B5/6/7/8 0x5B       [1:0]
		.lpf_back_band 	= 0x07,	//B5/6/7/8 0x5C       [6:4]
		.clk_sel 		= 0x01,	//B5/6/7/8 0x5C       [3]
		.eq_gainsel 	= 0x00,	//B5/6/7/8 0x5C       [2:0]
		},
		[ CVI_HD_25P_EX ] = {
		.powerdown 		= 0x00, //B0       0x00/1/2/3 [0]
		.gain 			= 0x01,	//B0       0x00/1/2/3 [4]
		.spd 			= 0x0D,	//B5/6/7/8 0x00       [5:4]
		.ctrlreg 		= 0x01,	//B5/6/7/8 0x01       [6]
		.ctrlibs 		= 0x02,	//B5/6/7/8 0x01       [5:4]
		.adcspd 		= 0x00,	//B5/6/7/8 0x01       [2]
		.clplevel 		= 0x02,	//B5/6/7/8 0x01       [1:0]
		.eq_band 		= 0x00,	//B5/6/7/8 0x58       [6:4]
		.lpf_front_band = 0x07,	//B5/6/7/8 0x58       [1:0]
		.clpmode 		= 0x00,	//B5/6/7/8 0x59       [7]
		.f_lpf_bypass 	= 0x00,	//B5/6/7/8 0x59       [4]
		.clproff 		= 0x00,	//B5/6/7/8 0x59       [3]
		.b_lpf_bypass 	= 0x00,	//B5/6/7/8 0x59       [0]
		.duty 			= 0x04,	//B5/6/7/8 0x5B    	  [6:4]
		.ref_vol 		= 0x03,	//B5/6/7/8 0x5B       [1:0]
		.lpf_back_band 	= 0x07,	//B5/6/7/8 0x5C       [6:4]
		.clk_sel 		= 0x01,	//B5/6/7/8 0x5C       [3]
		.eq_gainsel 	= 0x00,	//B5/6/7/8 0x5C       [2:0]
		},
		[ CVI_4M_30P ] = {
			    .powerdown = 0,
			    .gain =  1,
			    .spd = 0xD,
			    .ctrlreg= 1,
			    .ctrlibs= 2,
			    .adcspd = 0,
			    .clplevel = 2,
			    .eq_band = 0,
			    .lpf_front_band = 7,
			    .clpmode = 0,
			    .f_lpf_bypass = 0,
			    .clproff = 0,
			    .b_lpf_bypass = 0,
			    .duty = 4,
			    .ref_vol = 1,
			    .lpf_back_band = 7,
			    .clk_sel = 1,
			    .eq_gainsel = 0,

		},
		[ CVI_4M_25P ] = {
			    .powerdown = 0,
			    .gain =  1,
			    .spd = 0xD,
			    .ctrlreg= 1,
			    .ctrlibs= 2,
			    .adcspd = 0,
			    .clplevel = 2,
			    .eq_band = 0,
			    .lpf_front_band = 7,
			    .clpmode = 0,
			    .f_lpf_bypass = 0,
			    .clproff = 0,
			    .b_lpf_bypass = 0,
			    .duty = 4,
			    .ref_vol = 1,
			    .lpf_back_band = 7,
			    .clk_sel = 1,
			    .eq_gainsel = 0,

		},
		[ CVI_8M_15P ] = {
		.powerdown 		= 0x00, //B0       0x00/1/2/3 [0]
		.gain 			= 0x01,	//B0       0x00/1/2/3 [4]
		.spd 			= 0x0D,	//B5/6/7/8 0x00       [5:4]
		.ctrlreg 		= 0x01,	//B5/6/7/8 0x01       [6]
		.ctrlibs 		= 0x02,	//B5/6/7/8 0x01       [5:4]
		.adcspd 		= 0x00,	//B5/6/7/8 0x01       [2]
		.clplevel 		= 0x02,	//B5/6/7/8 0x01       [1:0]
		.eq_band 		= 0x00,	//B5/6/7/8 0x58       [6:4]
		.lpf_front_band = 0x07,	//B5/6/7/8 0x58       [1:0]
		.clpmode 		= 0x00,	//B5/6/7/8 0x59       [7]
		.f_lpf_bypass 	= 0x00,	//B5/6/7/8 0x59       [4]
		.clproff 		= 0x00,	//B5/6/7/8 0x59       [3]
		.b_lpf_bypass 	= 0x00,	//B5/6/7/8 0x59       [0]
		.duty 			= 0x04,	//B5/6/7/8 0x5B    	  [6:4]
		.ref_vol 		= 0x03,	//B5/6/7/8 0x5B       [1:0]
		.lpf_back_band 	= 0x07,	//B5/6/7/8 0x5C       [6:4]
		.clk_sel 		= 0x01,	//B5/6/7/8 0x5C       [3]
		.eq_gainsel 	= 0x00,	//B5/6/7/8 0x5C       [2:0]
		},
		[ CVI_8M_12_5P ] = {
		.powerdown 		= 0x00, //B0       0x00/1/2/3 [0]
		.gain 			= 0x01,	//B0       0x00/1/2/3 [4]
		.spd 			= 0x0D,	//B5/6/7/8 0x00       [5:4]
		.ctrlreg 		= 0x01,	//B5/6/7/8 0x01       [6]
		.ctrlibs 		= 0x02,	//B5/6/7/8 0x01       [5:4]
		.adcspd 		= 0x00,	//B5/6/7/8 0x01       [2]
		.clplevel 		= 0x02,	//B5/6/7/8 0x01       [1:0]
		.eq_band 		= 0x00,	//B5/6/7/8 0x58       [6:4]
		.lpf_front_band = 0x07,	//B5/6/7/8 0x58       [1:0]
		.clpmode 		= 0x00,	//B5/6/7/8 0x59       [7]
		.f_lpf_bypass 	= 0x00,	//B5/6/7/8 0x59       [4]
		.clproff 		= 0x00,	//B5/6/7/8 0x59       [3]
		.b_lpf_bypass 	= 0x00,	//B5/6/7/8 0x59       [0]
		.duty 			= 0x04,	//B5/6/7/8 0x5B    	  [6:4]
		.ref_vol 		= 0x03,	//B5/6/7/8 0x5B       [1:0]
		.lpf_back_band 	= 0x07,	//B5/6/7/8 0x5C       [6:4]
		.clk_sel 		= 0x01,	//B5/6/7/8 0x5C       [3]
		.eq_gainsel 	= 0x00,	//B5/6/7/8 0x5C       [2:0]
		},
};

#if 1
/*
 *  EQ value
 */
video_equalizer_value_table_s equalizer_value_fmtdef[ NC_VIVO_CH_FORMATDEF_MAX ] =
{
	[ CVI_4M_25P ] = /* o */
	{
		/* base */
		{
			.eq_bypass[0] 	= 0x22, .eq_bypass[1] 	= 0x22, .eq_bypass[2] 	= 0x22, .eq_bypass[3] 	= 0x22, .eq_bypass[4] 	= 0x22, .eq_bypass[5] 	= 0x22,    // Bank5 0x30
			.eq_band_sel[0] = 0x77, .eq_band_sel[1] = 0x77, .eq_band_sel[2] = 0x77, .eq_band_sel[3] = 0x77, .eq_band_sel[4] = 0x57, .eq_band_sel[5] = 0x57,    // BankA 0x31
			.eq_gain_sel[0] = 0x78, .eq_gain_sel[1] = 0x7a, .eq_gain_sel[2] = 0x7f, .eq_gain_sel[3] = 0x7f, .eq_gain_sel[4] = 0x7f, .eq_gain_sel[5] = 0x7f,    // BankA 0x32
			.deq_a_on[0] 	= 0x00, .deq_a_on[1] 	= 0x01, .deq_a_on[2] 	= 0x01, .deq_a_on[3] 	= 0x01, .deq_a_on[4] 	= 0x01, .deq_a_on[5] 	= 0x01,    // BankA 0x33
			.deq_a_sel[0] 	= 0x00, .deq_a_sel[1] 	= 0x92, .deq_a_sel[2] 	= 0x93, .deq_a_sel[3] 	= 0x95, .deq_a_sel[4] 	= 0x94, .deq_a_sel[5] 	= 0x95,    // BankA 0x34
			.deq_b_sel[0] 	= 0x00, .deq_b_sel[1] 	= 0x00, .deq_b_sel[2] 	= 0x00, .deq_b_sel[3] 	= 0x00, .deq_b_sel[4] 	= 0x00, .deq_b_sel[5] 	= 0x00,    // BankA 0x35
		},
		/* coeff */
		{
			.deqA_01[0] = 0xAC, .deqA_01[1] = 0xAC, .deqA_01[2] = 0xAC, .deqA_01[3] = 0xAC, .deqA_01[4] = 0xAC, .deqA_01[5] = 0xAC,		// BankA 0x30
			.deqA_02[0] = 0x78, .deqA_02[1] = 0x78, .deqA_02[2] = 0x78, .deqA_02[3] = 0x78, .deqA_02[4] = 0x78, .deqA_02[5] = 0x78,		// BankA 0x31
			.deqA_03[0] = 0x17, .deqA_03[1] = 0x17, .deqA_03[2] = 0x17, .deqA_03[3] = 0x17, .deqA_03[4] = 0x17, .deqA_03[5] = 0x17,		// BankA 0x32
			.deqA_04[0] = 0xC1, .deqA_04[1] = 0xC1, .deqA_04[2] = 0xC1, .deqA_04[3] = 0xC1, .deqA_04[4] = 0xC1, .deqA_04[5] = 0xC1,     // BankA 0x33
			.deqA_05[0] = 0x40, .deqA_05[1] = 0x40, .deqA_05[2] = 0x40, .deqA_05[3] = 0x40, .deqA_05[4] = 0x40, .deqA_05[5] = 0x40,     // BankA 0x34
			.deqA_06[0] = 0x00, .deqA_06[1] = 0x00, .deqA_06[2] = 0x00, .deqA_06[3] = 0x00, .deqA_06[4] = 0x00, .deqA_06[5] = 0x00,     // BankA 0x35
			.deqA_07[0] = 0xC3, .deqA_07[1] = 0xC3, .deqA_07[2] = 0xC3, .deqA_07[3] = 0xC3, .deqA_07[4] = 0xC3, .deqA_07[5] = 0xC3,     // BankA 0x36
			.deqA_08[0] = 0x0A, .deqA_08[1] = 0x0A, .deqA_08[2] = 0x0A, .deqA_08[3] = 0x0A, .deqA_08[4] = 0x0A, .deqA_08[5] = 0x0A,     // BankA 0x37
			.deqA_09[0] = 0x00, .deqA_09[1] = 0x00, .deqA_09[2] = 0x00, .deqA_09[3] = 0x00, .deqA_09[4] = 0x00, .deqA_09[5] = 0x00,     // BankA 0x38
			.deqA_10[0] = 0x02, .deqA_10[1] = 0x02, .deqA_10[2] = 0x02, .deqA_10[3] = 0x02, .deqA_10[4] = 0x02, .deqA_10[5] = 0x02,     // BankA 0x39
			.deqA_11[0] = 0x00, .deqA_11[1] = 0x00, .deqA_11[2] = 0x00, .deqA_11[3] = 0x00, .deqA_11[4] = 0x00, .deqA_11[5] = 0x00,     // BankA 0x3a
			.deqA_12[0] = 0xB2, .deqA_12[1] = 0xB2, .deqA_12[2] = 0xB2, .deqA_12[3] = 0xB2, .deqA_12[4] = 0xB2, .deqA_12[5] = 0xB2,     // BankA 0x3b
		},
		/* color */
		{
			.contrast[0] 		= 0x81, .contrast[1] 		= 0x81, .contrast[2] 		= 0x7d, .contrast[3] 		= 0x7a, .contrast[4] 		= 0x7b, .contrast[5] 		= 0x82,
			.h_peaking[0] 		= 0x20, .h_peaking[1] 		= 0x20, .h_peaking[2] 		= 0x30, .h_peaking[3] 		= 0x30, .h_peaking[4] 		= 0x30, .h_peaking[5] 		= 0x30,
			.c_filter[0]		= 0x81, .c_filter[1] 		= 0x91, .c_filter[2]	 	= 0x91, .c_filter[3] 		= 0xa2, .c_filter[4] 		= 0xb2, .c_filter[5] 		= 0xb2,

			.hue[0] 			= 0x04, .hue[1] 			= 0x04, .hue[2] 			= 0x04, .hue[3] 			= 0x04, .hue[4] 			= 0x04, .hue[5] 			= 0x04,
			.u_gain[0] 			= 0xe3, .u_gain[1] 			= 0x00, .u_gain[2] 			= 0x04, .u_gain[3] 			= 0x14, .u_gain[4] 			= 0x14, .u_gain[5] 			= 0x14,
			.v_gain[0] 			= 0xe8, .v_gain[1] 			= 0x08, .v_gain[2] 			= 0x04, .v_gain[3] 			= 0x14, .v_gain[4] 			= 0x14, .v_gain[5] 			= 0x14,
			.u_offset[0] 		= 0xfe, .u_offset[1] 		= 0xfb, .u_offset[2] 		= 0xf6, .u_offset[3] 		= 0xf6, .u_offset[4] 		= 0xf6, .u_offset[5] 		= 0xf6,
			.v_offset[0] 		= 0xfa, .v_offset[1] 		= 0xfc, .v_offset[2] 		= 0xfc, .v_offset[3] 		= 0xfc, .v_offset[4] 		= 0xfc, .v_offset[5] 		= 0xfc,

			.black_level[0] 	= 0x81, .black_level[1] 	= 0x82, .black_level[2] 	= 0x83, .black_level[3] 	= 0x88, .black_level[4] 	= 0x90, .black_level[5] 	= 0x92,
			.acc_ref[0]			= 0x57, .acc_ref[1]			= 0x57, .acc_ref[2]			= 0x57, .acc_ref[3]			= 0x57, .acc_ref[4]			= 0x17, .acc_ref[5]			= 0x17,
			.cti_delay[0]		= 0x80, .cti_delay[1]		= 0x80, .cti_delay[2]		= 0x80, .cti_delay[3]		= 0x80, .cti_delay[4]		= 0x80, .cti_delay[5]		= 0x80,
			.sub_saturation[0] 	= 0xb0, .sub_saturation[1] 	= 0x90, .sub_saturation[2] 	= 0x90, .sub_saturation[3] 	= 0xa8, .sub_saturation[4] 	= 0xd0, .sub_saturation[5] 	= 0x40,

			.burst_dec_a[0] 	= 0x2a, .burst_dec_a[1] 	= 0x2a, .burst_dec_a[2] 	= 0x2a, .burst_dec_a[3] 	= 0x2a, .burst_dec_a[4] 	= 0x2a, .burst_dec_a[5] 	= 0x2a,
			.burst_dec_b[0] 	= 0x00, .burst_dec_b[1] 	= 0x00, .burst_dec_b[2] 	= 0x00, .burst_dec_b[3] 	= 0x00, .burst_dec_b[4] 	= 0x00, .burst_dec_b[5] 	= 0x00,
			.burst_dec_c[0] 	= 0x30, .burst_dec_c[1] 	= 0x30, .burst_dec_c[2] 	= 0x30, .burst_dec_c[3] 	= 0x30, .burst_dec_c[4] 	= 0x30, .burst_dec_c[5] 	= 0x30,

			.c_option[0] 		= 0x80, .c_option[1] 		= 0x80, .c_option[2] 		= 0x80, .c_option[3] 		= 0x90, .c_option[4] 		= 0xb0, .c_option[5] 		= 0xb0,

			.y_filter_b[0]		= 0x10, .y_filter_b[1]		= 0x10, .y_filter_b[2]		= 0x10, .y_filter_b[3]		= 0x10, .y_filter_b[4]		= 0x10, .y_filter_b[5]		= 0x10,
			.y_filter_b_sel[0]	= 0x1e,	.y_filter_b_sel[1]	= 0x1e,	.y_filter_b_sel[2]	= 0x1e, .y_filter_b_sel[3]	= 0x1e, .y_filter_b_sel[4]	= 0x1e, .y_filter_b_sel[5]	= 0x1e,
		},
		/* timing_a */
		{
			.h_delay_a[0] = 0x82, .h_delay_a[1] = 0x82, .h_delay_a[2] = 0x81, .h_delay_a[3] = 0x80, .h_delay_a[4] = 0x80, .h_delay_a[5] = 0x80,
			.h_delay_b[0] = 0x00, .h_delay_b[1] = 0x00, .h_delay_b[2] = 0x00, .h_delay_b[3] = 0x00, .h_delay_b[4] = 0x00, .h_delay_b[5] = 0x00,
			.h_delay_c[0] = 0x10, .h_delay_c[1] = 0x10, .h_delay_c[2] = 0x10, .h_delay_c[3] = 0x10, .h_delay_c[4] = 0x10, .h_delay_c[5] = 0x10,
			.y_delay[0]   = 0x04, .y_delay[1]   = 0x04, .y_delay[2]   = 0x04, .y_delay[3]   = 0x04, .y_delay[4]   = 0x04, .y_delay[5] = 0x04,

		},
		/* clk */
		{
			.clk_adc[0] = 0x05, .clk_adc[1] = 0x05, .clk_adc[2] = 0x05, .clk_adc[3] = 0x05, .clk_adc[4] = 0x05, .clk_adc[5] = 0x05,
			.clk_dec[0] = 0x44, .clk_dec[1] = 0x44, .clk_dec[2] = 0x44, .clk_dec[3] = 0x44, .clk_dec[4] = 0x44, .clk_dec[5] = 0x44,
		},
		/* timing_b */
		{
/*B9 0x96*/	.h_scaler1[0]  = 0x00, .h_scaler1[1]   = 0x00, .h_scaler1[2]   = 0x00, .h_scaler1[3]   = 0x00, .h_scaler1[4]   = 0x00, .h_scaler1[5]   = 0x00,
/*B9 0x97*/	.h_scaler2[0]  = 0xe9, .h_scaler2[1]   = 0xe9, .h_scaler2[2]   = 0xe9, .h_scaler2[3]   = 0xe9, .h_scaler2[4]   = 0xe9, .h_scaler2[5]   = 0xe9,
/*B9 0x98*/	.h_scaler3[0]  = 0x69, .h_scaler3[1]   = 0x69, .h_scaler3[2]   = 0x69, .h_scaler3[3]   = 0x69, .h_scaler3[4]   = 0x69, .h_scaler3[5]   = 0x69,
/*B9 0x99*/	.h_scaler4[0]  = 0x01, .h_scaler4[1]   = 0x01, .h_scaler4[2]   = 0x01, .h_scaler4[3]   = 0x01, .h_scaler4[4]   = 0x01, .h_scaler4[5]   = 0x01,
/*B9 0x9a*/	.h_scaler5[0]  = 0xc0, .h_scaler5[1]   = 0xc0, .h_scaler5[2]   = 0xc0, .h_scaler5[3]   = 0xc0, .h_scaler5[4]   = 0xc0, .h_scaler5[5]   = 0xc0,
/*B9 0x9b*/	.h_scaler6[0]  = 0x02, .h_scaler6[1]   = 0x02, .h_scaler6[2]   = 0x02, .h_scaler6[3]   = 0x02, .h_scaler6[4]   = 0x02, .h_scaler6[5]   = 0x02,
/*B9 0x9c*/	.h_scaler7[0]  = 0x9e, .h_scaler7[1]   = 0x9e, .h_scaler7[2]   = 0x9e, .h_scaler7[3]   = 0x9e, .h_scaler7[4]   = 0x9e, .h_scaler7[5]   = 0x9e,
/*B9 0x9d*/	.h_scaler8[0]  = 0x50, .h_scaler8[1]   = 0x50, .h_scaler8[2]   = 0x50, .h_scaler8[3]   = 0x50, .h_scaler8[4]   = 0x50, .h_scaler8[5]   = 0x50,
/*B9 0x9e*/	.h_scaler9[0]  = 0x14, .h_scaler9[1]   = 0x14, .h_scaler9[2]   = 0x14, .h_scaler9[3]   = 0x14, .h_scaler9[4]   = 0x14, .h_scaler9[5]   = 0x14,


/*B9 0x40*/	.pn_auto[0]    	= 0x00, .pn_auto[1]		= 0x00, .pn_auto[2]    	= 0x00, .pn_auto[3]    	= 0x00, .pn_auto[4]    	= 0x00, .pn_auto[5]    	= 0x00,

/*B5 0x90*/	.comb_mode[0]   = 0x05, .comb_mode[1]	= 0x05, .comb_mode[2]   = 0x05, .comb_mode[3]   = 0x05, .comb_mode[4]  	= 0x05, .comb_mode[5]   = 0x05,
/*B9 0xb9*/	.h_pll_op_a[0]  = 0x72, .h_pll_op_a[1]  = 0x72, .h_pll_op_a[2]  = 0x72, .h_pll_op_a[3]  = 0x72, .h_pll_op_a[4]  = 0x72, .h_pll_op_a[5]  = 0x72,
/*B9 0x57*/	.mem_path[0]	= 0x10, .mem_path[1]	= 0x10, .mem_path[2]	= 0x10, .mem_path[3]	= 0x10, .mem_path[4]	= 0x10, .mem_path[5]	= 0x10,
            .fsc_lock_speed[0] = 0xdc, .fsc_lock_speed[1] = 0xdc, .fsc_lock_speed[2] = 0xdc, .fsc_lock_speed[3] = 0xdc, .fsc_lock_speed[4] = 0xdc, .fsc_lock_speed[5] = 0xdc,
/*B0 0x81*/	.format_set1[0] = 0x0f, .format_set1[1] = 0x0f, .format_set1[2] = 0x0f, .format_set1[3] = 0x0f, .format_set1[4] = 0x0f, .format_set1[5] = 0x0f,
/*B0 0x85*/	.format_set2[0] = 0x02, .format_set2[1] = 0x02, .format_set2[2] = 0x02, .format_set2[3] = 0x02, .format_set2[4] = 0x02, .format_set2[5] = 0x02,

/*B0 0x64*/ .v_delay[0]     = 0x80, .v_delay[1]     = 0x80, .v_delay[2]     = 0x80, .v_delay[3]     = 0x80, .v_delay[4]     = 0x80, .v_delay[5]     = 0x80,
		},
	},
	[ CVI_4M_30P ] = { /* o */
		/* base */
		{
			.eq_bypass[0] 	= 0x22, .eq_bypass[1] 	= 0x22, .eq_bypass[2] 	= 0x22, .eq_bypass[3] 	= 0x22, .eq_bypass[4] 	= 0x22, .eq_bypass[5] 	= 0x22,    // Bank5 0x30
			.eq_band_sel[0] = 0x77, .eq_band_sel[1] = 0x77, .eq_band_sel[2] = 0x77, .eq_band_sel[3] = 0x77, .eq_band_sel[4] = 0x57, .eq_band_sel[5] = 0x57,    // BankA 0x31
			.eq_gain_sel[0] = 0x78, .eq_gain_sel[1] = 0x7a, .eq_gain_sel[2] = 0x7f, .eq_gain_sel[3] = 0x7f, .eq_gain_sel[4] = 0x7f, .eq_gain_sel[5] = 0x7f,    // BankA 0x32
			.deq_a_on[0] 	= 0x00, .deq_a_on[1] 	= 0x01, .deq_a_on[2] 	= 0x01, .deq_a_on[3] 	= 0x01, .deq_a_on[4] 	= 0x01, .deq_a_on[5] 	= 0x01,    // BankA 0x33
			.deq_a_sel[0] 	= 0x00, .deq_a_sel[1] 	= 0x92, .deq_a_sel[2] 	= 0x93, .deq_a_sel[3] 	= 0x95, .deq_a_sel[4] 	= 0x94, .deq_a_sel[5] 	= 0x95,    // BankA 0x34
			.deq_b_sel[0] 	= 0x00, .deq_b_sel[1] 	= 0x00, .deq_b_sel[2] 	= 0x00, .deq_b_sel[3] 	= 0x00, .deq_b_sel[4] 	= 0x00, .deq_b_sel[5] 	= 0x00,    // BankA 0x35
		},
		/* coeff */
		{
			.deqA_01[0] = 0xAC, .deqA_01[1] = 0xAC, .deqA_01[2] = 0xAC, .deqA_01[3] = 0xAC, .deqA_01[4] = 0xAC, .deqA_01[5] = 0xAC,		// BankA 0x30
			.deqA_02[0] = 0x78, .deqA_02[1] = 0x78, .deqA_02[2] = 0x78, .deqA_02[3] = 0x78, .deqA_02[4] = 0x78, .deqA_02[5] = 0x78,		// BankA 0x31
			.deqA_03[0] = 0x17, .deqA_03[1] = 0x17, .deqA_03[2] = 0x17, .deqA_03[3] = 0x17, .deqA_03[4] = 0x17, .deqA_03[5] = 0x17,		// BankA 0x32
			.deqA_04[0] = 0xC1, .deqA_04[1] = 0xC1, .deqA_04[2] = 0xC1, .deqA_04[3] = 0xC1, .deqA_04[4] = 0xC1, .deqA_04[5] = 0xC1,     // BankA 0x33
			.deqA_05[0] = 0x40, .deqA_05[1] = 0x40, .deqA_05[2] = 0x40, .deqA_05[3] = 0x40, .deqA_05[4] = 0x40, .deqA_05[5] = 0x40,     // BankA 0x34
			.deqA_06[0] = 0x00, .deqA_06[1] = 0x00, .deqA_06[2] = 0x00, .deqA_06[3] = 0x00, .deqA_06[4] = 0x00, .deqA_06[5] = 0x00,     // BankA 0x35
			.deqA_07[0] = 0xC3, .deqA_07[1] = 0xC3, .deqA_07[2] = 0xC3, .deqA_07[3] = 0xC3, .deqA_07[4] = 0xC3, .deqA_07[5] = 0xC3,     // BankA 0x36
			.deqA_08[0] = 0x0A, .deqA_08[1] = 0x0A, .deqA_08[2] = 0x0A, .deqA_08[3] = 0x0A, .deqA_08[4] = 0x0A, .deqA_08[5] = 0x0A,     // BankA 0x37
			.deqA_09[0] = 0x00, .deqA_09[1] = 0x00, .deqA_09[2] = 0x00, .deqA_09[3] = 0x00, .deqA_09[4] = 0x00, .deqA_09[5] = 0x00,     // BankA 0x38
			.deqA_10[0] = 0x02, .deqA_10[1] = 0x02, .deqA_10[2] = 0x02, .deqA_10[3] = 0x02, .deqA_10[4] = 0x02, .deqA_10[5] = 0x02,     // BankA 0x39
			.deqA_11[0] = 0x00, .deqA_11[1] = 0x00, .deqA_11[2] = 0x00, .deqA_11[3] = 0x00, .deqA_11[4] = 0x00, .deqA_11[5] = 0x00,     // BankA 0x3a
			.deqA_12[0] = 0xB2, .deqA_12[1] = 0xB2, .deqA_12[2] = 0xB2, .deqA_12[3] = 0xB2, .deqA_12[4] = 0xB2, .deqA_12[5] = 0xB2,     // BankA 0x3b
		},
		/* color */
		{
			.contrast[0] 		= 0x81, .contrast[1] 		= 0x81, .contrast[2] 		= 0x7d, .contrast[3] 		= 0x7a, .contrast[4] 		= 0x7b, .contrast[5] 		= 0x82,
			.h_peaking[0] 		= 0x20, .h_peaking[1] 		= 0x20, .h_peaking[2] 		= 0x30, .h_peaking[3] 		= 0x30, .h_peaking[4] 		= 0x30, .h_peaking[5] 		= 0x30,
			.c_filter[0]		= 0x81, .c_filter[1] 		= 0x91, .c_filter[2]	 	= 0x91, .c_filter[3] 		= 0xa2, .c_filter[4] 		= 0xb2, .c_filter[5] 		= 0xb2,

			.hue[0] 			= 0x04, .hue[1] 			= 0x04, .hue[2] 			= 0x04, .hue[3] 			= 0x04, .hue[4] 			= 0x04, .hue[5] 			= 0x04,
			.u_gain[0] 			= 0xe3, .u_gain[1] 			= 0x00, .u_gain[2] 			= 0x04, .u_gain[3] 			= 0x14, .u_gain[4] 			= 0x14, .u_gain[5] 			= 0x14,
			.v_gain[0] 			= 0xe8, .v_gain[1] 			= 0x08, .v_gain[2] 			= 0x04, .v_gain[3] 			= 0x14, .v_gain[4] 			= 0x14, .v_gain[5] 			= 0x14,
			.u_offset[0] 		= 0xfe, .u_offset[1] 		= 0xfb, .u_offset[2] 		= 0xf6, .u_offset[3] 		= 0xf6, .u_offset[4] 		= 0xf6, .u_offset[5] 		= 0xf6,
			.v_offset[0] 		= 0xfa, .v_offset[1] 		= 0xfc, .v_offset[2] 		= 0xfc, .v_offset[3] 		= 0xfc, .v_offset[4] 		= 0xfc, .v_offset[5] 		= 0xfc,

			.black_level[0] 	= 0x81, .black_level[1] 	= 0x82, .black_level[2] 	= 0x83, .black_level[3] 	= 0x88, .black_level[4] 	= 0x90, .black_level[5] 	= 0x92,
			.acc_ref[0]			= 0x57, .acc_ref[1]			= 0x57, .acc_ref[2]			= 0x57, .acc_ref[3]			= 0x57, .acc_ref[4]			= 0x17, .acc_ref[5]			= 0x17,
			.cti_delay[0]		= 0x80, .cti_delay[1]		= 0x80, .cti_delay[2]		= 0x80, .cti_delay[3]		= 0x80, .cti_delay[4]		= 0x80, .cti_delay[5]		= 0x80,
			.sub_saturation[0] 	= 0xb0, .sub_saturation[1] 	= 0x90, .sub_saturation[2] 	= 0x90, .sub_saturation[3] 	= 0xa8, .sub_saturation[4] 	= 0xd0, .sub_saturation[5] 	= 0x40,

			.burst_dec_a[0] 	= 0x2a, .burst_dec_a[1] 	= 0x2a, .burst_dec_a[2] 	= 0x2a, .burst_dec_a[3] 	= 0x2a, .burst_dec_a[4] 	= 0x2a, .burst_dec_a[5] 	= 0x2a,
			.burst_dec_b[0] 	= 0x00, .burst_dec_b[1] 	= 0x00, .burst_dec_b[2] 	= 0x00, .burst_dec_b[3] 	= 0x00, .burst_dec_b[4] 	= 0x00, .burst_dec_b[5] 	= 0x00,
			.burst_dec_c[0] 	= 0x30, .burst_dec_c[1] 	= 0x30, .burst_dec_c[2] 	= 0x30, .burst_dec_c[3] 	= 0x30, .burst_dec_c[4] 	= 0x30, .burst_dec_c[5] 	= 0x30,

			.c_option[0] 		= 0x80, .c_option[1] 		= 0x80, .c_option[2] 		= 0x80, .c_option[3] 		= 0x90, .c_option[4] 		= 0xb0, .c_option[5] 		= 0xb0,
			.y_filter_b[0]		= 0x10, .y_filter_b[1]		= 0x10, .y_filter_b[2]		= 0x10, .y_filter_b[3]		= 0x10, .y_filter_b[4]		= 0x10, .y_filter_b[5]		= 0x10,
			.y_filter_b_sel[0]	= 0x1e,	.y_filter_b_sel[1]	= 0x1e,	.y_filter_b_sel[2]	= 0x1e, .y_filter_b_sel[3]	= 0x1e, .y_filter_b_sel[4]	= 0x1e, .y_filter_b_sel[5]	= 0x1e,
		},
		/* timing_a */
		{
			.h_delay_a[0] = 0x80, .h_delay_a[1] = 0x80, .h_delay_a[2] = 0x80, .h_delay_a[3] = 0x80, .h_delay_a[4] = 0x80, .h_delay_a[5] = 0x80,
			.h_delay_b[0] = 0x00, .h_delay_b[1] = 0x00, .h_delay_b[2] = 0x00, .h_delay_b[3] = 0x00, .h_delay_b[4] = 0x00, .h_delay_b[5] = 0x00,
			.h_delay_c[0] = 0x00, .h_delay_c[1] = 0x00, .h_delay_c[2] = 0x00, .h_delay_c[3] = 0x00, .h_delay_c[4] = 0x00, .h_delay_c[5] = 0x00,
			.y_delay[0]   = 0x04, .y_delay[1]   = 0x04, .y_delay[2]   = 0x04, .y_delay[3]   = 0x04, .y_delay[4]   = 0x04, .y_delay[5]   = 0x04,

		},
		/* clk */
		{
			.clk_adc[0] = 0x05, .clk_adc[1] = 0x05, .clk_adc[2] = 0x05, .clk_adc[3] = 0x05, .clk_adc[4] = 0x05, .clk_adc[5] = 0x05,
			.clk_dec[0] = 0x44, .clk_dec[1] = 0x44, .clk_dec[2] = 0x44, .clk_dec[3] = 0x44, .clk_dec[4] = 0x44, .clk_dec[5] = 0x44,
		},
		/* timing_b */
		{
			.h_scaler1[0]  = 0x00, .h_scaler1[1]   = 0x00, .h_scaler1[2]   = 0x00, .h_scaler1[3]   = 0x00, .h_scaler1[4]   = 0x00, .h_scaler1[5]   = 0x00,
			.h_scaler2[0]  = 0xf9, .h_scaler2[1]   = 0xf9, .h_scaler2[2]   = 0xf9, .h_scaler2[3]   = 0xf9, .h_scaler2[4]   = 0xf9, .h_scaler2[5]   = 0xf9,
			.h_scaler3[0]  = 0x08, .h_scaler3[1]   = 0x08, .h_scaler3[2]   = 0x08, .h_scaler3[3]   = 0x08, .h_scaler3[4]   = 0x08, .h_scaler3[5]   = 0x08,
			.h_scaler4[0]  = 0x01, .h_scaler4[1]   = 0x01, .h_scaler4[2]   = 0x01, .h_scaler4[3]   = 0x01, .h_scaler4[4]   = 0x01, .h_scaler4[5]   = 0x01,
/*B9 0x9a*/	.h_scaler5[0]  = 0x00, .h_scaler5[1]   = 0x00, .h_scaler5[2]   = 0x00, .h_scaler5[3]   = 0x00, .h_scaler5[4]   = 0x00, .h_scaler5[5]   = 0x00,
/*B9 0x9b*/	.h_scaler6[0]  = 0x01, .h_scaler6[1]   = 0x01, .h_scaler6[2]   = 0x01, .h_scaler6[3]   = 0x01, .h_scaler6[4]   = 0x01, .h_scaler6[5]   = 0x01,
/*B9 0x9c*/	.h_scaler7[0]  = 0x83, .h_scaler7[1]   = 0x83, .h_scaler7[2]   = 0x83, .h_scaler7[3]   = 0x83, .h_scaler7[4]   = 0x83, .h_scaler7[5]   = 0x83,
/*B9 0x9d*/	.h_scaler8[0]  = 0x50, .h_scaler8[1]   = 0x50, .h_scaler8[2]   = 0x50, .h_scaler8[3]   = 0x50, .h_scaler8[4]   = 0x50, .h_scaler8[5]   = 0x50,
/*B9 0x9e*/	.h_scaler9[0]  = 0x14, .h_scaler9[1]   = 0x14, .h_scaler9[2]   = 0x14, .h_scaler9[3]   = 0x14, .h_scaler9[4]   = 0x14, .h_scaler9[5]   = 0x14,

			.pn_auto[0]    	= 0x00, .pn_auto[1]		= 0x00, .pn_auto[2]    	= 0x00, .pn_auto[3]    	= 0x00, .pn_auto[4]    	= 0x00, .pn_auto[5]    	= 0x00,
			.comb_mode[0]   = 0x05, .comb_mode[1]	= 0x05, .comb_mode[2]   = 0x05, .comb_mode[3]   = 0x05, .comb_mode[4]  	= 0x05, .comb_mode[5]   = 0x05,
			.h_pll_op_a[0]  = 0x72, .h_pll_op_a[1]  = 0x72, .h_pll_op_a[2]  = 0x72, .h_pll_op_a[3]  = 0x72, .h_pll_op_a[4]  = 0x72, .h_pll_op_a[5]  = 0x72,
			.mem_path[0]	= 0x10, .mem_path[1]	= 0x10, .mem_path[2]	= 0x10, .mem_path[3]	= 0x10, .mem_path[4]	= 0x10, .mem_path[5]	= 0x10,
			.fsc_lock_speed[0] = 0xdc, .fsc_lock_speed[1] = 0xdc, .fsc_lock_speed[2] = 0xdc, .fsc_lock_speed[3] = 0xdc, .fsc_lock_speed[4] = 0xdc, .fsc_lock_speed[5] = 0xdc,

			.format_set1[0] = 0x0e, .format_set1[1] = 0x0e, .format_set1[2] = 0x0e, .format_set1[3] = 0x0e, .format_set1[4] = 0x0e, .format_set1[5] = 0x0e,
			.format_set2[0] = 0x02, .format_set2[1] = 0x02, .format_set2[2] = 0x02, .format_set2[3] = 0x02, .format_set2[4] = 0x02, .format_set2[5] = 0x02,

			.v_delay[0]     = 0x80, .v_delay[1]     = 0x80, .v_delay[2]     = 0x80, .v_delay[3]     = 0x80, .v_delay[4]     = 0x80, .v_delay[5]     = 0x80,
		},
	},
	[ CVI_8M_12_5P ] = { /* o */
		/* base */
		{
			.eq_bypass[0] 	= 0x22, .eq_bypass[1] 	= 0x22, .eq_bypass[2] 	= 0x22, .eq_bypass[3] 	= 0x22, .eq_bypass[4] 	= 0x22, .eq_bypass[5] 	= 0x22,    // Bank5 0x30
			.eq_band_sel[0] = 0x77, .eq_band_sel[1] = 0x77, .eq_band_sel[2] = 0x77, .eq_band_sel[3] = 0x77, .eq_band_sel[4] = 0x57, .eq_band_sel[5] = 0x57,    // BankA 0x31
			.eq_gain_sel[0] = 0x78, .eq_gain_sel[1] = 0x7a, .eq_gain_sel[2] = 0x7f, .eq_gain_sel[3] = 0x7f, .eq_gain_sel[4] = 0x7f, .eq_gain_sel[5] = 0x7f,    // BankA 0x32
			.deq_a_on[0] 	= 0x00, .deq_a_on[1] 	= 0x01, .deq_a_on[2] 	= 0x01, .deq_a_on[3] 	= 0x01, .deq_a_on[4] 	= 0x01, .deq_a_on[5] 	= 0x01,    // BankA 0x33
			.deq_a_sel[0] 	= 0x00, .deq_a_sel[1] 	= 0x92, .deq_a_sel[2] 	= 0x93, .deq_a_sel[3] 	= 0x95, .deq_a_sel[4] 	= 0x94, .deq_a_sel[5] 	= 0x95,    // BankA 0x34
			.deq_b_sel[0] 	= 0x00, .deq_b_sel[1] 	= 0x00, .deq_b_sel[2] 	= 0x00, .deq_b_sel[3] 	= 0x00, .deq_b_sel[4] 	= 0x00, .deq_b_sel[5] 	= 0x00,    // BankA 0x35
		},
		/* coeff */
		{
			.deqA_01[0] = 0xAC, .deqA_01[1] = 0xAC, .deqA_01[2] = 0xAC, .deqA_01[3] = 0xAC, .deqA_01[4] = 0xAC, .deqA_01[5] = 0xAC,		// BankA 0x30
			.deqA_02[0] = 0x78, .deqA_02[1] = 0x78, .deqA_02[2] = 0x78, .deqA_02[3] = 0x78, .deqA_02[4] = 0x78, .deqA_02[5] = 0x78,		// BankA 0x31
			.deqA_03[0] = 0x17, .deqA_03[1] = 0x17, .deqA_03[2] = 0x17, .deqA_03[3] = 0x17, .deqA_03[4] = 0x17, .deqA_03[5] = 0x17,		// BankA 0x32
			.deqA_04[0] = 0xC1, .deqA_04[1] = 0xC1, .deqA_04[2] = 0xC1, .deqA_04[3] = 0xC1, .deqA_04[4] = 0xC1, .deqA_04[5] = 0xC1,     // BankA 0x33
			.deqA_05[0] = 0x40, .deqA_05[1] = 0x40, .deqA_05[2] = 0x40, .deqA_05[3] = 0x40, .deqA_05[4] = 0x40, .deqA_05[5] = 0x40,     // BankA 0x34
			.deqA_06[0] = 0x00, .deqA_06[1] = 0x00, .deqA_06[2] = 0x00, .deqA_06[3] = 0x00, .deqA_06[4] = 0x00, .deqA_06[5] = 0x00,     // BankA 0x35
			.deqA_07[0] = 0xC3, .deqA_07[1] = 0xC3, .deqA_07[2] = 0xC3, .deqA_07[3] = 0xC3, .deqA_07[4] = 0xC3, .deqA_07[5] = 0xC3,     // BankA 0x36
			.deqA_08[0] = 0x0A, .deqA_08[1] = 0x0A, .deqA_08[2] = 0x0A, .deqA_08[3] = 0x0A, .deqA_08[4] = 0x0A, .deqA_08[5] = 0x0A,     // BankA 0x37
			.deqA_09[0] = 0x00, .deqA_09[1] = 0x00, .deqA_09[2] = 0x00, .deqA_09[3] = 0x00, .deqA_09[4] = 0x00, .deqA_09[5] = 0x00,     // BankA 0x38
			.deqA_10[0] = 0x02, .deqA_10[1] = 0x02, .deqA_10[2] = 0x02, .deqA_10[3] = 0x02, .deqA_10[4] = 0x02, .deqA_10[5] = 0x02,     // BankA 0x39
			.deqA_11[0] = 0x00, .deqA_11[1] = 0x00, .deqA_11[2] = 0x00, .deqA_11[3] = 0x00, .deqA_11[4] = 0x00, .deqA_11[5] = 0x00,     // BankA 0x3a
			.deqA_12[0] = 0xB2, .deqA_12[1] = 0xB2, .deqA_12[2] = 0xB2, .deqA_12[3] = 0xB2, .deqA_12[4] = 0xB2, .deqA_12[5] = 0xB2,     // BankA 0x3b
		},
		/* color */
		{
			.contrast[0] 		= 0x7e, .contrast[1] 		= 0x7c, .contrast[2] 		= 0x7a, .contrast[3] 		= 0x79, .contrast[4] 		= 0x79, .contrast[5] 		= 0x79,
			.h_peaking[0] 		= 0x20, .h_peaking[1] 		= 0x20, .h_peaking[2] 		= 0x30, .h_peaking[3] 		= 0x30, .h_peaking[4] 		= 0x30, .h_peaking[5] 		= 0x30,
			.c_filter[0]		= 0x81, .c_filter[1] 		= 0x91, .c_filter[2]	 	= 0x91, .c_filter[3] 		= 0xa2, .c_filter[4] 		= 0xb2, .c_filter[5] 		= 0xb2,

			.hue[0] 			= 0x20, .hue[1] 			= 0x20, .hue[2] 			= 0x21, .hue[3] 			= 0x21, .hue[4] 			= 0x21, .hue[5] 			= 0x21,
			.u_gain[0] 			= 0xd8, .u_gain[1] 			= 0xf0, .u_gain[2] 			= 0x14, .u_gain[3] 			= 0x14, .u_gain[4] 			= 0x14, .u_gain[5] 			= 0x14,
			.v_gain[0] 			= 0xe0, .v_gain[1] 			= 0xf8, .v_gain[2] 			= 0x14, .v_gain[3] 			= 0x14, .v_gain[4] 			= 0x14, .v_gain[5] 			= 0x14,
			.u_offset[0] 		= 0xfb, .u_offset[1] 		= 0xfb, .u_offset[2] 		= 0xf6, .u_offset[3] 		= 0xf6, .u_offset[4] 		= 0xf6, .u_offset[5] 		= 0xf6,
			.v_offset[0] 		= 0xfc, .v_offset[1] 		= 0xfc, .v_offset[2] 		= 0xfc, .v_offset[3] 		= 0xfc, .v_offset[4] 		= 0xfc, .v_offset[5] 		= 0xfc,

			.black_level[0] 	= 0x85, .black_level[1] 	= 0x85, .black_level[2] 	= 0x88, .black_level[3] 	= 0x8b, .black_level[4] 	= 0x8b, .black_level[5] 	= 0x8b,
			.acc_ref[0]			= 0x57, .acc_ref[1]			= 0x57, .acc_ref[2]			= 0x57, .acc_ref[3]			= 0x57, .acc_ref[4]			= 0x47, .acc_ref[5]			= 0x37,
			.cti_delay[0]		= 0x80, .cti_delay[1]		= 0x80, .cti_delay[2]		= 0x80, .cti_delay[3]		= 0x80, .cti_delay[4]		= 0x80, .cti_delay[5]		= 0x80,
			.sub_saturation[0] 	= 0xb0, .sub_saturation[1] 	= 0x90, .sub_saturation[2] 	= 0x90, .sub_saturation[3] 	= 0x80, .sub_saturation[4] 	= 0x48, .sub_saturation[5] 	= 0x20,

			.burst_dec_a[0] 	= 0x2a, .burst_dec_a[1] 	= 0x2a, .burst_dec_a[2] 	= 0x2a, .burst_dec_a[3] 	= 0x2a, .burst_dec_a[4] 	= 0x2a, .burst_dec_a[5] 	= 0x2a,
			.burst_dec_b[0] 	= 0x00, .burst_dec_b[1] 	= 0x00, .burst_dec_b[2] 	= 0x00, .burst_dec_b[3] 	= 0x00, .burst_dec_b[4] 	= 0x00, .burst_dec_b[5] 	= 0x00,
			.burst_dec_c[0] 	= 0x30, .burst_dec_c[1] 	= 0x30, .burst_dec_c[2] 	= 0x30, .burst_dec_c[3] 	= 0x30, .burst_dec_c[4] 	= 0x30, .burst_dec_c[5] 	= 0x30,

			.c_option[0] 		= 0xc0, .c_option[1] 		= 0xc0, .c_option[2] 		= 0xc0, .c_option[3] 		= 0xc0, .c_option[4] 		= 0xc0, .c_option[5] 		= 0xc0,
			.y_filter_b[0]		= 0x10, .y_filter_b[1]		= 0x10, .y_filter_b[2]		= 0x10, .y_filter_b[3]		= 0x10, .y_filter_b[4]		= 0x10, .y_filter_b[5]		= 0x10,
			.y_filter_b_sel[0]	= 0x1e,	.y_filter_b_sel[1]	= 0x1e,	.y_filter_b_sel[2]	= 0x1e, .y_filter_b_sel[3]	= 0x1e, .y_filter_b_sel[4]	= 0x1e, .y_filter_b_sel[5]	= 0x1e,
		},
		/* timing_a */
		{
			.h_delay_a[0] = 0xc0, .h_delay_a[1] = 0xc0, .h_delay_a[2] = 0xc0, .h_delay_a[3] = 0xc0, .h_delay_a[4] = 0xc0, .h_delay_a[5] = 0xc0,
			.h_delay_b[0] = 0x00, .h_delay_b[1] = 0x00, .h_delay_b[2] = 0x00, .h_delay_b[3] = 0x00, .h_delay_b[4] = 0x00, .h_delay_b[5] = 0x00,
			.h_delay_c[0] = 0x20, .h_delay_c[1] = 0x20, .h_delay_c[2] = 0x20, .h_delay_c[3] = 0x20, .h_delay_c[4] = 0x20, .h_delay_c[5] = 0x20,
			.y_delay[0]   = 0x14, .y_delay[1]   = 0x14, .y_delay[2]   = 0x24, .y_delay[3]   = 0x24, .y_delay[4]   = 0x24, .y_delay[5]   = 0x24,

		},
		/* clk */
		{
			.clk_adc[0] = 0x05, .clk_adc[1] = 0x05, .clk_adc[2] = 0x05, .clk_adc[3] = 0x05, .clk_adc[4] = 0x05, .clk_adc[5] = 0x05,
			.clk_dec[0] = 0x44, .clk_dec[1] = 0x44, .clk_dec[2] = 0x44, .clk_dec[3] = 0x44, .clk_dec[4] = 0x44, .clk_dec[5] = 0x44,
		},
		/* timing_b */
		{
			.h_scaler1[0]   = 0x00, .h_scaler1[1]   = 0x00, .h_scaler1[2]   = 0x00, .h_scaler1[3]   = 0x00, .h_scaler1[4]   = 0x00, .h_scaler1[5]   = 0x00,
			.h_scaler2[0]   = 0xd9, .h_scaler2[1]   = 0xd9, .h_scaler2[2]   = 0xd9, .h_scaler2[3]   = 0xd9, .h_scaler2[4]   = 0xd9, .h_scaler2[5]   = 0xd9,
			.h_scaler3[0]   = 0x80, .h_scaler3[1]   = 0x80, .h_scaler3[2]   = 0x80, .h_scaler3[3]   = 0x80, .h_scaler3[4]   = 0x80, .h_scaler3[5]   = 0x80,
			.h_scaler4[0]   = 0x02, .h_scaler4[1]   = 0x02, .h_scaler4[2]   = 0x02, .h_scaler4[3]   = 0x02, .h_scaler4[4]   = 0x02, .h_scaler4[5]   = 0x02,
/*B9 0x9a*/	.h_scaler5[0]   = 0xc0, .h_scaler5[1]   = 0xc0, .h_scaler5[2]   = 0xc0, .h_scaler5[3]   = 0xc0, .h_scaler5[4]   = 0xc0, .h_scaler5[5]   = 0xc0,
/*B9 0x9b*/	.h_scaler6[0]   = 0x01, .h_scaler6[1]   = 0x01, .h_scaler6[2]   = 0x01, .h_scaler6[3]   = 0x01, .h_scaler6[4]   = 0x01, .h_scaler6[5]   = 0x01,
/*B9 0x9c*/	.h_scaler7[0]   = 0x8c, .h_scaler7[1]   = 0x8c, .h_scaler7[2]   = 0x8c, .h_scaler7[3]   = 0x8c, .h_scaler7[4]   = 0x8c, .h_scaler7[5]   = 0x8c,
/*B9 0x9d*/	.h_scaler8[0]   = 0xf0, .h_scaler8[1]   = 0xf0, .h_scaler8[2]   = 0xf0, .h_scaler8[3]   = 0xf0, .h_scaler8[4]   = 0xf0, .h_scaler8[5]   = 0xf0,
/*B9 0x9e*/	.h_scaler9[0]   = 0x0f, .h_scaler9[1]   = 0x0f, .h_scaler9[2]   = 0x0f, .h_scaler9[3]   = 0x0f, .h_scaler9[4]   = 0x0f, .h_scaler9[5]   = 0x0f,

			.pn_auto[0]    	= 0x00, .pn_auto[1]		= 0x00, .pn_auto[2]    	= 0x00, .pn_auto[3]    	= 0x00, .pn_auto[4]    	= 0x00, .pn_auto[5]    	= 0x00,
			.comb_mode[0]   = 0x05, .comb_mode[1]	= 0x05, .comb_mode[2]   = 0x05, .comb_mode[3]   = 0x05, .comb_mode[4]  	= 0x05, .comb_mode[5]   = 0x05,
			.h_pll_op_a[0]  = 0x72, .h_pll_op_a[1]  = 0x72, .h_pll_op_a[2]  = 0x72, .h_pll_op_a[3]  = 0x72, .h_pll_op_a[4]  = 0x72, .h_pll_op_a[5]  = 0x72,
			.mem_path[0]	= 0x10, .mem_path[1]	= 0x10, .mem_path[2]	= 0x10, .mem_path[3]	= 0x10, .mem_path[4]	= 0x10, .mem_path[5]	= 0x10,
			.fsc_lock_speed[0] = 0xdc, .fsc_lock_speed[1] = 0xdc, .fsc_lock_speed[2] = 0xdc, .fsc_lock_speed[3] = 0xdc, .fsc_lock_speed[4] = 0xdc, .fsc_lock_speed[5] = 0xdc,

			.format_set1[0] = 0x01, .format_set1[1] = 0x01, .format_set1[2] = 0x01, .format_set1[3] = 0x01, .format_set1[4] = 0x01, .format_set1[5] = 0x01,
			.format_set2[0] = 0x0a, .format_set2[1] = 0x0a, .format_set2[2] = 0x0a, .format_set2[3] = 0x0a, .format_set2[4] = 0x0a, .format_set2[5] = 0x0a,

			.v_delay[0]     = 0x80, .v_delay[1]     = 0x80, .v_delay[2]     = 0x80, .v_delay[3]     = 0x80, .v_delay[4]     = 0x80, .v_delay[5]     = 0x80,
		},
	},
	[ CVI_8M_15P ] = { /* o */
		/* base */
		{
			.eq_bypass[0] 	= 0x22, .eq_bypass[1] 	= 0x22, .eq_bypass[2] 	= 0x22, .eq_bypass[3] 	= 0x22, .eq_bypass[4] 	= 0x22, .eq_bypass[5] 	= 0x22,    // Bank5 0x30
			.eq_band_sel[0] = 0x77, .eq_band_sel[1] = 0x77, .eq_band_sel[2] = 0x77, .eq_band_sel[3] = 0x77, .eq_band_sel[4] = 0x57, .eq_band_sel[5] = 0x57,    // BankA 0x31
			.eq_gain_sel[0] = 0x78, .eq_gain_sel[1] = 0x7a, .eq_gain_sel[2] = 0x7f, .eq_gain_sel[3] = 0x7f, .eq_gain_sel[4] = 0x7f, .eq_gain_sel[5] = 0x7f,    // BankA 0x32
			.deq_a_on[0] 	= 0x00, .deq_a_on[1] 	= 0x01, .deq_a_on[2] 	= 0x01, .deq_a_on[3] 	= 0x01, .deq_a_on[4] 	= 0x01, .deq_a_on[5] 	= 0x01,    // BankA 0x33
			.deq_a_sel[0] 	= 0x00, .deq_a_sel[1] 	= 0x92, .deq_a_sel[2] 	= 0x93, .deq_a_sel[3] 	= 0x95, .deq_a_sel[4] 	= 0x94, .deq_a_sel[5] 	= 0x95,    // BankA 0x34
			.deq_b_sel[0] 	= 0x00, .deq_b_sel[1] 	= 0x00, .deq_b_sel[2] 	= 0x00, .deq_b_sel[3] 	= 0x00, .deq_b_sel[4] 	= 0x00, .deq_b_sel[5] 	= 0x00,    // BankA 0x35
		},
		/* coeff */
		{
			.deqA_01[0] = 0xAC, .deqA_01[1] = 0xAC, .deqA_01[2] = 0xAC, .deqA_01[3] = 0xAC, .deqA_01[4] = 0xAC, .deqA_01[5] = 0xAC,		// BankA 0x30
			.deqA_02[0] = 0x78, .deqA_02[1] = 0x78, .deqA_02[2] = 0x78, .deqA_02[3] = 0x78, .deqA_02[4] = 0x78, .deqA_02[5] = 0x78,		// BankA 0x31
			.deqA_03[0] = 0x17, .deqA_03[1] = 0x17, .deqA_03[2] = 0x17, .deqA_03[3] = 0x17, .deqA_03[4] = 0x17, .deqA_03[5] = 0x17,		// BankA 0x32
			.deqA_04[0] = 0xC1, .deqA_04[1] = 0xC1, .deqA_04[2] = 0xC1, .deqA_04[3] = 0xC1, .deqA_04[4] = 0xC1, .deqA_04[5] = 0xC1,     // BankA 0x33
			.deqA_05[0] = 0x40, .deqA_05[1] = 0x40, .deqA_05[2] = 0x40, .deqA_05[3] = 0x40, .deqA_05[4] = 0x40, .deqA_05[5] = 0x40,     // BankA 0x34
			.deqA_06[0] = 0x00, .deqA_06[1] = 0x00, .deqA_06[2] = 0x00, .deqA_06[3] = 0x00, .deqA_06[4] = 0x00, .deqA_06[5] = 0x00,     // BankA 0x35
			.deqA_07[0] = 0xC3, .deqA_07[1] = 0xC3, .deqA_07[2] = 0xC3, .deqA_07[3] = 0xC3, .deqA_07[4] = 0xC3, .deqA_07[5] = 0xC3,     // BankA 0x36
			.deqA_08[0] = 0x0A, .deqA_08[1] = 0x0A, .deqA_08[2] = 0x0A, .deqA_08[3] = 0x0A, .deqA_08[4] = 0x0A, .deqA_08[5] = 0x0A,     // BankA 0x37
			.deqA_09[0] = 0x00, .deqA_09[1] = 0x00, .deqA_09[2] = 0x00, .deqA_09[3] = 0x00, .deqA_09[4] = 0x00, .deqA_09[5] = 0x00,     // BankA 0x38
			.deqA_10[0] = 0x02, .deqA_10[1] = 0x02, .deqA_10[2] = 0x02, .deqA_10[3] = 0x02, .deqA_10[4] = 0x02, .deqA_10[5] = 0x02,     // BankA 0x39
			.deqA_11[0] = 0x00, .deqA_11[1] = 0x00, .deqA_11[2] = 0x00, .deqA_11[3] = 0x00, .deqA_11[4] = 0x00, .deqA_11[5] = 0x00,     // BankA 0x3a
			.deqA_12[0] = 0xB2, .deqA_12[1] = 0xB2, .deqA_12[2] = 0xB2, .deqA_12[3] = 0xB2, .deqA_12[4] = 0xB2, .deqA_12[5] = 0xB2,     // BankA 0x3b
		},
		/* color */
		{
			.contrast[0] 		= 0x7e, .contrast[1] 		= 0x7c, .contrast[2] 		= 0x7a, .contrast[3] 		= 0x79, .contrast[4] 		= 0x79, .contrast[5] 		= 0x79,
			.h_peaking[0] 		= 0x20, .h_peaking[1] 		= 0x20, .h_peaking[2] 		= 0x30, .h_peaking[3] 		= 0x30, .h_peaking[4] 		= 0x30, .h_peaking[5] 		= 0x30,
			.c_filter[0]		= 0x81, .c_filter[1] 		= 0x91, .c_filter[2]	 	= 0x91, .c_filter[3] 		= 0xa2, .c_filter[4] 		= 0xb2, .c_filter[5] 		= 0xb2,

			.hue[0] 			= 0x20, .hue[1] 			= 0x20, .hue[2] 			= 0x21, .hue[3] 			= 0x21, .hue[4] 			= 0x21, .hue[5] 			= 0x21,
			.u_gain[0] 			= 0xd8, .u_gain[1] 			= 0xf0, .u_gain[2] 			= 0x14, .u_gain[3] 			= 0x14, .u_gain[4] 			= 0x14, .u_gain[5] 			= 0x14,
			.v_gain[0] 			= 0xe0, .v_gain[1] 			= 0xf8, .v_gain[2] 			= 0x14, .v_gain[3] 			= 0x14, .v_gain[4] 			= 0x14, .v_gain[5] 			= 0x14,
			.u_offset[0] 		= 0xfb, .u_offset[1] 		= 0xfb, .u_offset[2] 		= 0xf6, .u_offset[3] 		= 0xf6, .u_offset[4] 		= 0xf6, .u_offset[5] 		= 0xf6,
			.v_offset[0] 		= 0xfc, .v_offset[1] 		= 0xfc, .v_offset[2] 		= 0xfc, .v_offset[3] 		= 0xfc, .v_offset[4] 		= 0xfc, .v_offset[5] 		= 0xfc,

			.black_level[0] 	= 0x85, .black_level[1] 	= 0x85, .black_level[2] 	= 0x88, .black_level[3] 	= 0x8b, .black_level[4] 	= 0x8b, .black_level[5] 	= 0x8b,
			.acc_ref[0]			= 0x57, .acc_ref[1]			= 0x57, .acc_ref[2]			= 0x57, .acc_ref[3]			= 0x57, .acc_ref[4]			= 0x47, .acc_ref[5]			= 0x37,
			.cti_delay[0]		= 0x80, .cti_delay[1]		= 0x80, .cti_delay[2]		= 0x80, .cti_delay[3]		= 0x80, .cti_delay[4]		= 0x80, .cti_delay[5]		= 0x80,
			.sub_saturation[0] 	= 0xb0, .sub_saturation[1] 	= 0x90, .sub_saturation[2] 	= 0x90, .sub_saturation[3] 	= 0x80, .sub_saturation[4] 	= 0x48, .sub_saturation[5] 	= 0x20,

			.burst_dec_a[0] 	= 0x2a, .burst_dec_a[1] 	= 0x2a, .burst_dec_a[2] 	= 0x2a, .burst_dec_a[3] 	= 0x2a, .burst_dec_a[4] 	= 0x2a, .burst_dec_a[5] 	= 0x2a,
			.burst_dec_b[0] 	= 0x00, .burst_dec_b[1] 	= 0x00, .burst_dec_b[2] 	= 0x00, .burst_dec_b[3] 	= 0x00, .burst_dec_b[4] 	= 0x00, .burst_dec_b[5] 	= 0x00,
			.burst_dec_c[0] 	= 0x30, .burst_dec_c[1] 	= 0x30, .burst_dec_c[2] 	= 0x30, .burst_dec_c[3] 	= 0x30, .burst_dec_c[4] 	= 0x30, .burst_dec_c[5] 	= 0x30,

			.c_option[0] 		= 0xc0, .c_option[1] 		= 0xc0, .c_option[2] 		= 0xc0, .c_option[3] 		= 0xc0, .c_option[4] 		= 0xc0, .c_option[5] 		= 0xc0,
			.y_filter_b[0]		= 0x10, .y_filter_b[1]		= 0x10, .y_filter_b[2]		= 0x10, .y_filter_b[3]		= 0x10, .y_filter_b[4]		= 0x10, .y_filter_b[5]		= 0x10,
			.y_filter_b_sel[0]	= 0x1e,	.y_filter_b_sel[1]	= 0x1e,	.y_filter_b_sel[2]	= 0x1e, .y_filter_b_sel[3]	= 0x1e, .y_filter_b_sel[4]	= 0x1e, .y_filter_b_sel[5]	= 0x1e,

		},
		/* timing_a */
		{
			.h_delay_a[0] = 0x80, .h_delay_a[1] = 0x80, .h_delay_a[2] = 0x80, .h_delay_a[3] = 0x80, .h_delay_a[4] = 0x80, .h_delay_a[5] = 0x80,
			.h_delay_b[0] = 0x10, .h_delay_b[1] = 0x10, .h_delay_b[2] = 0x10, .h_delay_b[3] = 0x10, .h_delay_b[4] = 0x10, .h_delay_b[5] = 0x10,
			.h_delay_c[0] = 0x00, .h_delay_c[1] = 0x00, .h_delay_c[2] = 0x00, .h_delay_c[3] = 0x00, .h_delay_c[4] = 0x00, .h_delay_c[5] = 0x00,
			.y_delay[0]   = 0x14, .y_delay[1]   = 0x14, .y_delay[2]   = 0x24, .y_delay[3]   = 0x24, .y_delay[4]   = 0x24, .y_delay[5]   = 0x24,

		},
		/* clk */
		{
			.clk_adc[0] = 0x05, .clk_adc[1] = 0x05, .clk_adc[2] = 0x05, .clk_adc[3] = 0x05, .clk_adc[4] = 0x05, .clk_adc[5] = 0x05,
			.clk_dec[0] = 0x44, .clk_dec[1] = 0x44, .clk_dec[2] = 0x44, .clk_dec[3] = 0x44, .clk_dec[4] = 0x44, .clk_dec[5] = 0x44,
		},
		/* timing_b */
		{
			.h_scaler1[0]   = 0x01, .h_scaler1[1]   = 0x01, .h_scaler1[2]   = 0x01, .h_scaler1[3]   = 0x01, .h_scaler1[4]   = 0x01, .h_scaler1[5]   = 0x01,
			.h_scaler2[0]   = 0x69, .h_scaler2[1]   = 0x69, .h_scaler2[2]   = 0x69, .h_scaler2[3]   = 0x69, .h_scaler2[4]   = 0x69, .h_scaler2[5]   = 0x69,
			.h_scaler3[0]   = 0xb8, .h_scaler3[1]   = 0xb8, .h_scaler3[2]   = 0xb8, .h_scaler3[3]   = 0xb8, .h_scaler3[4]   = 0xb8, .h_scaler3[5]   = 0xb8,
			.h_scaler4[0]   = 0x00, .h_scaler4[1]   = 0x00, .h_scaler4[2]   = 0x00, .h_scaler4[3]   = 0x00, .h_scaler4[4]   = 0x00, .h_scaler4[5]   = 0x00,
/*B9 0x9a*/	.h_scaler5[0]   = 0x00, .h_scaler5[1]   = 0x00, .h_scaler5[2]   = 0x00, .h_scaler5[3]   = 0x00, .h_scaler5[4]   = 0x00, .h_scaler5[5]   = 0x00,
/*B9 0x9b*/	.h_scaler6[0]   = 0x00, .h_scaler6[1]   = 0x00, .h_scaler6[2]   = 0x00, .h_scaler6[3]   = 0x00, .h_scaler6[4]   = 0x00, .h_scaler6[5]   = 0x00,
/*B9 0x9c*/	.h_scaler7[0]   = 0x00, .h_scaler7[1]   = 0x00, .h_scaler7[2]   = 0x00, .h_scaler7[3]   = 0x00, .h_scaler7[4]   = 0x00, .h_scaler7[5]   = 0x00,
/*B9 0x9d*/	.h_scaler8[0]   = 0x00, .h_scaler8[1]   = 0x00, .h_scaler8[2]   = 0x00, .h_scaler8[3]   = 0x00, .h_scaler8[4]   = 0x00, .h_scaler8[5]   = 0x00,
/*B9 0x9e*/	.h_scaler9[0]   = 0x00, .h_scaler9[1]   = 0x00, .h_scaler9[2]   = 0x00, .h_scaler9[3]   = 0x00, .h_scaler9[4]   = 0x00, .h_scaler9[5]   = 0x00,
			.pn_auto[0]    	= 0x00, .pn_auto[1]		= 0x00, .pn_auto[2]    	= 0x00, .pn_auto[3]    	= 0x00, .pn_auto[4]    	= 0x00, .pn_auto[5]    	= 0x00,
			.comb_mode[0]   = 0x05, .comb_mode[1]	= 0x05, .comb_mode[2]   = 0x05, .comb_mode[3]   = 0x05, .comb_mode[4]  	= 0x05, .comb_mode[5]   = 0x05,
			.h_pll_op_a[0]  = 0x72, .h_pll_op_a[1]  = 0x72, .h_pll_op_a[2]  = 0x72, .h_pll_op_a[3]  = 0x72, .h_pll_op_a[4]  = 0x72, .h_pll_op_a[5]  = 0x72,
			.mem_path[0]	= 0x10, .mem_path[1]	= 0x10, .mem_path[2]	= 0x10, .mem_path[3]	= 0x10, .mem_path[4]	= 0x10, .mem_path[5]	= 0x10,
			.fsc_lock_speed[0] = 0xdc, .fsc_lock_speed[1] = 0xdc, .fsc_lock_speed[2] = 0xdc, .fsc_lock_speed[3] = 0xdc, .fsc_lock_speed[4] = 0xdc, .fsc_lock_speed[5] = 0xdc,

			.format_set1[0] = 0x02, .format_set1[1] = 0x02, .format_set1[2] = 0x02, .format_set1[3] = 0x02, .format_set1[4] = 0x02, .format_set1[5] = 0x02,
			.format_set2[0] = 0x0a, .format_set2[1] = 0x0a, .format_set2[2] = 0x0a, .format_set2[3] = 0x0a, .format_set2[4] = 0x0a, .format_set2[5] = 0x0a,

			.v_delay[0]     = 0x80, .v_delay[1]     = 0x80, .v_delay[2]     = 0x80, .v_delay[3]     = 0x80, .v_delay[4]     = 0x80, .v_delay[5]     = 0x80,
		},
	},
	[ CVI_FHD_25P ] = { /* o */
		/* base */
		{
			.eq_bypass[0] 	= 0x62, .eq_bypass[1] 	= 0x22, .eq_bypass[2] 	= 0x22, .eq_bypass[3] 	= 0x22, .eq_bypass[4] 	= 0x22, .eq_bypass[5] 	= 0x22,    // Bank5 0x30
			.eq_band_sel[0] = 0x77, .eq_band_sel[1] = 0x77, .eq_band_sel[2] = 0x77, .eq_band_sel[3] = 0x77, .eq_band_sel[4] = 0x67, .eq_band_sel[5] = 0x47,    // BankA 0x31
			.eq_gain_sel[0] = 0x78, .eq_gain_sel[1] = 0x7f, .eq_gain_sel[2] = 0x6f, .eq_gain_sel[3] = 0x7f, .eq_gain_sel[4] = 0x7f, .eq_gain_sel[5] = 0x7f,    // BankA 0x32
			.deq_a_on[0] 	= 0x00, .deq_a_on[1] 	= 0x01, .deq_a_on[2] 	= 0x01, .deq_a_on[3] 	= 0x01, .deq_a_on[4] 	= 0x01, .deq_a_on[5] 	= 0x01,    // BankA 0x33
			.deq_a_sel[0] 	= 0x00, .deq_a_sel[1] 	= 0x92, .deq_a_sel[2] 	= 0x93, .deq_a_sel[3] 	= 0x94, .deq_a_sel[4] 	= 0x95, .deq_a_sel[5] 	= 0x93,    // BankA 0x34
			.deq_b_sel[0] 	= 0x00, .deq_b_sel[1] 	= 0x00, .deq_b_sel[2] 	= 0x00, .deq_b_sel[3] 	= 0x00, .deq_b_sel[4] 	= 0x00, .deq_b_sel[5] 	= 0x00,    // BankA 0x35
		},
		/* coeff */
		{
			.deqA_01[0] = 0xAC, .deqA_01[1] = 0xAC, .deqA_01[2] = 0xAC, .deqA_01[3] = 0xAC, .deqA_01[4] = 0xAC, .deqA_01[5] = 0xAC,		// BankA 0x30
			.deqA_02[0] = 0x78, .deqA_02[1] = 0x78, .deqA_02[2] = 0x78, .deqA_02[3] = 0x78, .deqA_02[4] = 0x78, .deqA_02[5] = 0x78,		// BankA 0x31
			.deqA_03[0] = 0x17, .deqA_03[1] = 0x17, .deqA_03[2] = 0x17, .deqA_03[3] = 0x17, .deqA_03[4] = 0x17, .deqA_03[5] = 0x17,		// BankA 0x32
			.deqA_04[0] = 0xC1, .deqA_04[1] = 0xC1, .deqA_04[2] = 0xC1, .deqA_04[3] = 0xC1, .deqA_04[4] = 0xC1, .deqA_04[5] = 0xC1,     // BankA 0x33
			.deqA_05[0] = 0x40, .deqA_05[1] = 0x40, .deqA_05[2] = 0x40, .deqA_05[3] = 0x40, .deqA_05[4] = 0x40, .deqA_05[5] = 0x40,     // BankA 0x34
			.deqA_06[0] = 0x00, .deqA_06[1] = 0x00, .deqA_06[2] = 0x00, .deqA_06[3] = 0x00, .deqA_06[4] = 0x00, .deqA_06[5] = 0x00,     // BankA 0x35
			.deqA_07[0] = 0xC3, .deqA_07[1] = 0xC3, .deqA_07[2] = 0xC3, .deqA_07[3] = 0xC3, .deqA_07[4] = 0xC3, .deqA_07[5] = 0xC3,     // BankA 0x36
			.deqA_08[0] = 0x0A, .deqA_08[1] = 0x0A, .deqA_08[2] = 0x0A, .deqA_08[3] = 0x0A, .deqA_08[4] = 0x0A, .deqA_08[5] = 0x0A,     // BankA 0x37
			.deqA_09[0] = 0x00, .deqA_09[1] = 0x00, .deqA_09[2] = 0x00, .deqA_09[3] = 0x00, .deqA_09[4] = 0x00, .deqA_09[5] = 0x00,     // BankA 0x38
			.deqA_10[0] = 0x02, .deqA_10[1] = 0x02, .deqA_10[2] = 0x02, .deqA_10[3] = 0x02, .deqA_10[4] = 0x02, .deqA_10[5] = 0x02,     // BankA 0x39
			.deqA_11[0] = 0x00, .deqA_11[1] = 0x00, .deqA_11[2] = 0x00, .deqA_11[3] = 0x00, .deqA_11[4] = 0x00, .deqA_11[5] = 0x00,     // BankA 0x3a
			.deqA_12[0] = 0xB2, .deqA_12[1] = 0xB2, .deqA_12[2] = 0xB2, .deqA_12[3] = 0xB2, .deqA_12[4] = 0xB2, .deqA_12[5] = 0xB2,     // BankA 0x3b
		},
		/* color */
		{
			.contrast[0] 		= 0x98, .contrast[1] 		= 0x98, .contrast[2] 		= 0x98, .contrast[3] 		= 0x98, .contrast[4] 		= 0x98, .contrast[5] 		= 0x98,
			.h_peaking[0] 		= 0x00, .h_peaking[1] 		= 0x00, .h_peaking[2] 		= 0x00, .h_peaking[3] 		= 0x00, .h_peaking[4] 		= 0x00, .h_peaking[5] 		= 0x00,
			.c_filter[0]		= 0x92, .c_filter[1] 		= 0x92, .c_filter[2]	 	= 0x92, .c_filter[3] 		= 0x92, .c_filter[4] 		= 0xb2, .c_filter[5] 		= 0xb2,

			.hue[0] 			= 0x03, .hue[1] 			= 0x03, .hue[2] 			= 0x04, .hue[3] 			= 0x04, .hue[4] 			= 0x04, .hue[5] 			= 0x04,
			.u_gain[0] 			= 0x0c, .u_gain[1] 			= 0x0c, .u_gain[2] 			= 0x0c, .u_gain[3] 			= 0x0c, .u_gain[4] 			= 0x0c, .u_gain[5] 			= 0x0c,
			.v_gain[0] 			= 0x1a, .v_gain[1] 			= 0x1a, .v_gain[2] 			= 0x1a, .v_gain[3] 			= 0x1a, .v_gain[4] 			= 0x1a, .v_gain[5] 			= 0x1a,
			.u_offset[0] 		= 0xfa, .u_offset[1] 		= 0xfa, .u_offset[2] 		= 0xfa, .u_offset[3] 		= 0xfa, .u_offset[4] 		= 0xfa, .u_offset[5] 		= 0xfa,
			.v_offset[0] 		= 0xfa, .v_offset[1] 		= 0xfa, .v_offset[2] 		= 0xfa, .v_offset[3] 		= 0xfa, .v_offset[4] 		= 0xfa, .v_offset[5] 		= 0xfa,

			.black_level[0] 	= 0x86, .black_level[1] 	= 0x7a, .black_level[2] 	= 0x88, .black_level[3] 	= 0x84, .black_level[4] 	= 0x84, .black_level[5] 	= 0x84,
			.acc_ref[0]			= 0x57, .acc_ref[1]			= 0x57, .acc_ref[2]			= 0x57, .acc_ref[3]			= 0x57, .acc_ref[4]			= 0x47, .acc_ref[5]			= 0x37,
			.cti_delay[0]		= 0x80, .cti_delay[1]		= 0x80, .cti_delay[2]		= 0x80, .cti_delay[3]		= 0x80, .cti_delay[4]		= 0x80, .cti_delay[5]		= 0x80,
			.sub_saturation[0] 	= 0xa8, .sub_saturation[1] 	= 0xa0, .sub_saturation[2] 	= 0xa0, .sub_saturation[3] 	= 0x90, .sub_saturation[4] 	= 0x90, .sub_saturation[5] 	= 0x90,

			.burst_dec_a[0] 	= 0x2a, .burst_dec_a[1] 	= 0x2a, .burst_dec_a[2] 	= 0x2a, .burst_dec_a[3] 	= 0x2a, .burst_dec_a[4] 	= 0x2a, .burst_dec_a[5] 	= 0x2a,
			.burst_dec_b[0] 	= 0x00, .burst_dec_b[1] 	= 0x00, .burst_dec_b[2] 	= 0x00, .burst_dec_b[3] 	= 0x00, .burst_dec_b[4] 	= 0x00, .burst_dec_b[5] 	= 0x00,
			.burst_dec_c[0] 	= 0x30, .burst_dec_c[1] 	= 0x30, .burst_dec_c[2] 	= 0x30, .burst_dec_c[3] 	= 0x30, .burst_dec_c[4] 	= 0x30, .burst_dec_c[5] 	= 0x30,

			.c_option[0] 		= 0xc0, .c_option[1] 		= 0xc0, .c_option[2] 		= 0xc0, .c_option[3] 		= 0xc0, .c_option[4] 		= 0xc0, .c_option[5] 		= 0xc0,
			.y_filter_b[0]		= 0x10, .y_filter_b[1]		= 0x10, .y_filter_b[2]		= 0x10, .y_filter_b[3]		= 0x10, .y_filter_b[4]		= 0x10, .y_filter_b[5]		= 0x10,
			.y_filter_b_sel[0]	= 0x1e,	.y_filter_b_sel[1]	= 0x1e,	.y_filter_b_sel[2]	= 0x1e, .y_filter_b_sel[3]	= 0x1e, .y_filter_b_sel[4]	= 0x1e, .y_filter_b_sel[5]	= 0x1e,
		},
		/* timing_a */
		{
			.h_delay_a[0] = 0x60, .h_delay_a[1] = 0x60, .h_delay_a[2] = 0x60, .h_delay_a[3] = 0x60, .h_delay_a[4] = 0x60, .h_delay_a[5] = 0x60,
			.h_delay_b[0] = 0x10, .h_delay_b[1] = 0x10, .h_delay_b[2] = 0x10, .h_delay_b[3] = 0x10, .h_delay_b[4] = 0x10, .h_delay_b[5] = 0x10,
			.h_delay_c[0] = 0x06, .h_delay_c[1] = 0x06, .h_delay_c[2] = 0x06, .h_delay_c[3] = 0x06, .h_delay_c[4] = 0x06, .h_delay_c[5] = 0x06,
			.y_delay[0]   = 0x02, .y_delay[1]   = 0x02, .y_delay[2]   = 0x02, .y_delay[3]   = 0x02, .y_delay[4]   = 0x02, .y_delay[5]   = 0x02,

		},
		/* clk */
		{
			.clk_adc[0] = 0x05, .clk_adc[1] = 0x05, .clk_adc[2] = 0x05, .clk_adc[3] = 0x05, .clk_adc[4] = 0x05, .clk_adc[5] = 0x05,
			.clk_dec[0] = 0x44, .clk_dec[1] = 0x44, .clk_dec[2] = 0x44, .clk_dec[3] = 0x44, .clk_dec[4] = 0x44, .clk_dec[5] = 0x44,
		},
		/* timing_b */
		{
			.h_scaler1[0]  = 0x01, .h_scaler1[1]   = 0x01, .h_scaler1[2]   = 0x01, .h_scaler1[3]   = 0x01, .h_scaler1[4]   = 0x01, .h_scaler1[5]   = 0x01,
			.h_scaler2[0]  = 0x49, .h_scaler2[1]   = 0x49, .h_scaler2[2]   = 0x49, .h_scaler2[3]   = 0x49, .h_scaler2[4]   = 0x49, .h_scaler2[5]   = 0x49,
			.h_scaler3[0]  = 0x4f, .h_scaler3[1]   = 0x4f, .h_scaler3[2]   = 0x4f, .h_scaler3[3]   = 0x4f, .h_scaler3[4]   = 0x4f, .h_scaler3[5]   = 0x4f,
			.h_scaler4[0]  = 0x02, .h_scaler4[1]   = 0x02, .h_scaler4[2]   = 0x02, .h_scaler4[3]   = 0x02, .h_scaler4[4]   = 0x02, .h_scaler4[5]   = 0x02,
/*B9 0x9a*/	.h_scaler5[0]  = 0x00, .h_scaler5[1]   = 0x00, .h_scaler5[2]   = 0x00, .h_scaler5[3]   = 0x00, .h_scaler5[4]   = 0x00, .h_scaler5[5]   = 0x00,
/*B9 0x9b*/	.h_scaler6[0]  = 0x00, .h_scaler6[1]   = 0x00, .h_scaler6[2]   = 0x00, .h_scaler6[3]   = 0x00, .h_scaler6[4]   = 0x00, .h_scaler6[5]   = 0x00,
/*B9 0x9c*/	.h_scaler7[0]  = 0x00, .h_scaler7[1]   = 0x00, .h_scaler7[2]   = 0x00, .h_scaler7[3]   = 0x00, .h_scaler7[4]   = 0x00, .h_scaler7[5]   = 0x00,
/*B9 0x9d*/	.h_scaler8[0]  = 0x00, .h_scaler8[1]   = 0x00, .h_scaler8[2]   = 0x00, .h_scaler8[3]   = 0x00, .h_scaler8[4]   = 0x00, .h_scaler8[5]   = 0x00,
/*B9 0x9e*/	.h_scaler9[0]  = 0x80, .h_scaler9[1]   = 0x80, .h_scaler9[2]   = 0x80, .h_scaler9[3]   = 0x80, .h_scaler9[4]   = 0x80, .h_scaler9[5]   = 0x80,

			.pn_auto[0]    	= 0x00, .pn_auto[1]		= 0x00, .pn_auto[2]    	= 0x00, .pn_auto[3]    	= 0x00, .pn_auto[4]    	= 0x00, .pn_auto[5]    	= 0x00,
			.comb_mode[0]   = 0x05, .comb_mode[1]	= 0x05, .comb_mode[2]   = 0x05, .comb_mode[3]   = 0x05, .comb_mode[4]  	= 0x05, .comb_mode[5]   = 0x05,
			.h_pll_op_a[0]  = 0x72, .h_pll_op_a[1]  = 0x72, .h_pll_op_a[2]  = 0x72, .h_pll_op_a[3]  = 0x72, .h_pll_op_a[4]  = 0x72, .h_pll_op_a[5]  = 0x72,
			.mem_path[0]	= 0x10, .mem_path[1]	= 0x10, .mem_path[2]	= 0x10, .mem_path[3]	= 0x10, .mem_path[4]	= 0x10, .mem_path[5]	= 0x10,
			.fsc_lock_speed[0] = 0xdc, .fsc_lock_speed[1] = 0xdc, .fsc_lock_speed[2] = 0xdc, .fsc_lock_speed[3] = 0xdc, .fsc_lock_speed[4] = 0xdc, .fsc_lock_speed[5] = 0xdc,

			.format_set1[0] = 0x03, .format_set1[1] = 0x03, .format_set1[2] = 0x03, .format_set1[3] = 0x03, .format_set1[4] = 0x03, .format_set1[5] = 0x03,
			.format_set2[0] = 0x02, .format_set2[1] = 0x02, .format_set2[2] = 0x02, .format_set2[3] = 0x02, .format_set2[4] = 0x02, .format_set2[5] = 0x02,

			.v_delay[0]     = 0x80, .v_delay[1]     = 0x80, .v_delay[2]     = 0x80, .v_delay[3]     = 0x80, .v_delay[4]     = 0x80, .v_delay[5]     = 0x80,
		},
	},
	[ CVI_FHD_30P ] = { /* o */
		/* base */
		{
			.eq_bypass[0] 	= 0x62, .eq_bypass[1] 	= 0x22, .eq_bypass[2] 	= 0x22, .eq_bypass[3] 	= 0x22, .eq_bypass[4] 	= 0x22, .eq_bypass[5] 	= 0x22,    // Bank5 0x30
			.eq_band_sel[0] = 0x77, .eq_band_sel[1] = 0x77, .eq_band_sel[2] = 0x77, .eq_band_sel[3] = 0x77, .eq_band_sel[4] = 0x67, .eq_band_sel[5] = 0x47,    // BankA 0x31
			.eq_gain_sel[0] = 0x78, .eq_gain_sel[1] = 0x7f, .eq_gain_sel[2] = 0x6f, .eq_gain_sel[3] = 0x7f, .eq_gain_sel[4] = 0x7f, .eq_gain_sel[5] = 0x7f,    // BankA 0x32
			.deq_a_on[0] 	= 0x00, .deq_a_on[1] 	= 0x01, .deq_a_on[2] 	= 0x01, .deq_a_on[3] 	= 0x01, .deq_a_on[4] 	= 0x01, .deq_a_on[5] 	= 0x01,    // BankA 0x33
			.deq_a_sel[0] 	= 0x00, .deq_a_sel[1] 	= 0x92, .deq_a_sel[2] 	= 0x93, .deq_a_sel[3] 	= 0x94, .deq_a_sel[4] 	= 0x95, .deq_a_sel[5] 	= 0x93,    // BankA 0x34
			.deq_b_sel[0] 	= 0x00, .deq_b_sel[1] 	= 0x00, .deq_b_sel[2] 	= 0x00, .deq_b_sel[3] 	= 0x00, .deq_b_sel[4] 	= 0x00, .deq_b_sel[5] 	= 0x00,    // BankA 0x35
		},
		/* coeff */
		{
			.deqA_01[0] = 0xAC, .deqA_01[1] = 0xAC, .deqA_01[2] = 0xAC, .deqA_01[3] = 0xAC, .deqA_01[4] = 0xAC, .deqA_01[5] = 0xAC,		// BankA 0x30
			.deqA_02[0] = 0x78, .deqA_02[1] = 0x78, .deqA_02[2] = 0x78, .deqA_02[3] = 0x78, .deqA_02[4] = 0x78, .deqA_02[5] = 0x78,		// BankA 0x31
			.deqA_03[0] = 0x17, .deqA_03[1] = 0x17, .deqA_03[2] = 0x17, .deqA_03[3] = 0x17, .deqA_03[4] = 0x17, .deqA_03[5] = 0x17,		// BankA 0x32
			.deqA_04[0] = 0xC1, .deqA_04[1] = 0xC1, .deqA_04[2] = 0xC1, .deqA_04[3] = 0xC1, .deqA_04[4] = 0xC1, .deqA_04[5] = 0xC1,     // BankA 0x33
			.deqA_05[0] = 0x40, .deqA_05[1] = 0x40, .deqA_05[2] = 0x40, .deqA_05[3] = 0x40, .deqA_05[4] = 0x40, .deqA_05[5] = 0x40,     // BankA 0x34
			.deqA_06[0] = 0x00, .deqA_06[1] = 0x00, .deqA_06[2] = 0x00, .deqA_06[3] = 0x00, .deqA_06[4] = 0x00, .deqA_06[5] = 0x00,     // BankA 0x35
			.deqA_07[0] = 0xC3, .deqA_07[1] = 0xC3, .deqA_07[2] = 0xC3, .deqA_07[3] = 0xC3, .deqA_07[4] = 0xC3, .deqA_07[5] = 0xC3,     // BankA 0x36
			.deqA_08[0] = 0x0A, .deqA_08[1] = 0x0A, .deqA_08[2] = 0x0A, .deqA_08[3] = 0x0A, .deqA_08[4] = 0x0A, .deqA_08[5] = 0x0A,     // BankA 0x37
			.deqA_09[0] = 0x00, .deqA_09[1] = 0x00, .deqA_09[2] = 0x00, .deqA_09[3] = 0x00, .deqA_09[4] = 0x00, .deqA_09[5] = 0x00,     // BankA 0x38
			.deqA_10[0] = 0x02, .deqA_10[1] = 0x02, .deqA_10[2] = 0x02, .deqA_10[3] = 0x02, .deqA_10[4] = 0x02, .deqA_10[5] = 0x02,     // BankA 0x39
			.deqA_11[0] = 0x00, .deqA_11[1] = 0x00, .deqA_11[2] = 0x00, .deqA_11[3] = 0x00, .deqA_11[4] = 0x00, .deqA_11[5] = 0x00,     // BankA 0x3a
			.deqA_12[0] = 0xB2, .deqA_12[1] = 0xB2, .deqA_12[2] = 0xB2, .deqA_12[3] = 0xB2, .deqA_12[4] = 0xB2, .deqA_12[5] = 0xB2,     // BankA 0x3b
		},
		/* color */
		{
			.contrast[0] 		= 0x98, .contrast[1] 		= 0x98, .contrast[2] 		= 0x98, .contrast[3] 		= 0x98, .contrast[4] 		= 0x98, .contrast[5] 		= 0x98,
			.h_peaking[0] 		= 0x00, .h_peaking[1] 		= 0x00, .h_peaking[2] 		= 0x00, .h_peaking[3] 		= 0x00, .h_peaking[4] 		= 0x00, .h_peaking[5] 		= 0x00,
			.c_filter[0]		= 0x92, .c_filter[1] 		= 0x92, .c_filter[2]	 	= 0x92, .c_filter[3] 		= 0x92, .c_filter[4] 		= 0xb2, .c_filter[5] 		= 0xb2,

			.hue[0] 			= 0x03, .hue[1] 			= 0x03, .hue[2] 			= 0x04, .hue[3] 			= 0x04, .hue[4] 			= 0x04, .hue[5] 			= 0x04,
			.u_gain[0] 			= 0x0c, .u_gain[1] 			= 0x0c, .u_gain[2] 			= 0x0c, .u_gain[3] 			= 0x0c, .u_gain[4] 			= 0x0c, .u_gain[5] 			= 0x0c,
			.v_gain[0] 			= 0x1a, .v_gain[1] 			= 0x1a, .v_gain[2] 			= 0x1a, .v_gain[3] 			= 0x1a, .v_gain[4] 			= 0x1a, .v_gain[5] 			= 0x1a,
			.u_offset[0] 		= 0xfa, .u_offset[1] 		= 0xfa, .u_offset[2] 		= 0xfa, .u_offset[3] 		= 0xfa, .u_offset[4] 		= 0xfa, .u_offset[5] 		= 0xfa,
			.v_offset[0] 		= 0xfa, .v_offset[1] 		= 0xfa, .v_offset[2] 		= 0xfa, .v_offset[3] 		= 0xfa, .v_offset[4] 		= 0xfa, .v_offset[5] 		= 0xfa,

			.black_level[0] 	= 0x86, .black_level[1] 	= 0x7a, .black_level[2] 	= 0x88, .black_level[3] 	= 0x84, .black_level[4] 	= 0x84, .black_level[5] 	= 0x84,
			.acc_ref[0]			= 0x57, .acc_ref[1]			= 0x57, .acc_ref[2]			= 0x57, .acc_ref[3]			= 0x57, .acc_ref[4]			= 0x47, .acc_ref[5]			= 0x37,
			.cti_delay[0]		= 0x80, .cti_delay[1]		= 0x80, .cti_delay[2]		= 0x80, .cti_delay[3]		= 0x80, .cti_delay[4]		= 0x80, .cti_delay[5]		= 0x80,
			.sub_saturation[0] 	= 0xa8, .sub_saturation[1] 	= 0xa0, .sub_saturation[2] 	= 0xa0, .sub_saturation[3] 	= 0x90, .sub_saturation[4] 	= 0x90, .sub_saturation[5] 	= 0x90,

			.burst_dec_a[0] 	= 0x2a, .burst_dec_a[1] 	= 0x2a, .burst_dec_a[2] 	= 0x2a, .burst_dec_a[3] 	= 0x2a, .burst_dec_a[4] 	= 0x2a, .burst_dec_a[5] 	= 0x2a,
			.burst_dec_b[0] 	= 0x00, .burst_dec_b[1] 	= 0x00, .burst_dec_b[2] 	= 0x00, .burst_dec_b[3] 	= 0x00, .burst_dec_b[4] 	= 0x00, .burst_dec_b[5] 	= 0x00,
			.burst_dec_c[0] 	= 0x30, .burst_dec_c[1] 	= 0x30, .burst_dec_c[2] 	= 0x30, .burst_dec_c[3] 	= 0x30, .burst_dec_c[4] 	= 0x30, .burst_dec_c[5] 	= 0x30,

			.c_option[0] 		= 0xc0, .c_option[1] 		= 0xc0, .c_option[2] 		= 0xc0, .c_option[3] 		= 0xc0, .c_option[4] 		= 0xc0, .c_option[5] 		= 0xc0,
			.y_filter_b[0]		= 0x10, .y_filter_b[1]		= 0x10, .y_filter_b[2]		= 0x10, .y_filter_b[3]		= 0x10, .y_filter_b[4]		= 0x10, .y_filter_b[5]		= 0x10,
			.y_filter_b_sel[0]	= 0x1e,	.y_filter_b_sel[1]	= 0x1e,	.y_filter_b_sel[2]	= 0x1e, .y_filter_b_sel[3]	= 0x1e, .y_filter_b_sel[4]	= 0x1e, .y_filter_b_sel[5]	= 0x1e,

		},
		/* timing_a */
		{
			.h_delay_a[0] = 0x90, .h_delay_a[1] = 0x90, .h_delay_a[2] = 0x90, .h_delay_a[3] = 0x90, .h_delay_a[4] = 0x90, .h_delay_a[5] = 0x90,
			.h_delay_b[0] = 0x10, .h_delay_b[1] = 0x10, .h_delay_b[2] = 0x10, .h_delay_b[3] = 0x10, .h_delay_b[4] = 0x10, .h_delay_b[5] = 0x10,
			.h_delay_c[0] = 0x06, .h_delay_c[1] = 0x06, .h_delay_c[2] = 0x06, .h_delay_c[3] = 0x06, .h_delay_c[4] = 0x06, .h_delay_c[5] = 0x06,
			.y_delay[0]   = 0x02, .y_delay[1]   = 0x02, .y_delay[2]   = 0x02, .y_delay[3]   = 0x02, .y_delay[4]   = 0x02, .y_delay[5]   = 0x02,

		},
		/* clk */
		{
			.clk_adc[0] = 0x05, .clk_adc[1] = 0x05, .clk_adc[2] = 0x05, .clk_adc[3] = 0x05, .clk_adc[4] = 0x05, .clk_adc[5] = 0x05,
			.clk_dec[0] = 0x44, .clk_dec[1] = 0x44, .clk_dec[2] = 0x44, .clk_dec[3] = 0x44, .clk_dec[4] = 0x44, .clk_dec[5] = 0x44,
		},
		/* timing_b */
		{
			.h_scaler1[0]   = 0x01, .h_scaler1[1]   = 0x01, .h_scaler1[2]   = 0x01, .h_scaler1[3]   = 0x01, .h_scaler1[4]   = 0x01, .h_scaler1[5]   = 0x01,
			.h_scaler2[0]   = 0x39, .h_scaler2[1]   = 0x39, .h_scaler2[2]   = 0x39, .h_scaler2[3]   = 0x39, .h_scaler2[4]   = 0x39, .h_scaler2[5]   = 0x39,
			.h_scaler3[0]   = 0x50, .h_scaler3[1]   = 0x50, .h_scaler3[2]   = 0x50, .h_scaler3[3]   = 0x50, .h_scaler3[4]   = 0x50, .h_scaler3[5]   = 0x50,
			.h_scaler4[0]   = 0x01, .h_scaler4[1]   = 0x01, .h_scaler4[2]   = 0x01, .h_scaler4[3]   = 0x01, .h_scaler4[4]   = 0x01, .h_scaler4[5]   = 0x01,
/*B9 0x9a*/	.h_scaler5[0]   = 0x00, .h_scaler5[1]   = 0x00, .h_scaler5[2]   = 0x00, .h_scaler5[3]   = 0x00, .h_scaler5[4]   = 0x00, .h_scaler5[5]   = 0x00,
/*B9 0x9b*/	.h_scaler6[0]   = 0x00, .h_scaler6[1]   = 0x00, .h_scaler6[2]   = 0x00, .h_scaler6[3]   = 0x00, .h_scaler6[4]   = 0x00, .h_scaler6[5]   = 0x00,
/*B9 0x9c*/	.h_scaler7[0]   = 0x00, .h_scaler7[1]   = 0x00, .h_scaler7[2]   = 0x00, .h_scaler7[3]   = 0x00, .h_scaler7[4]   = 0x00, .h_scaler7[5]   = 0x00,
/*B9 0x9d*/	.h_scaler8[0]   = 0x00, .h_scaler8[1]   = 0x00, .h_scaler8[2]   = 0x00, .h_scaler8[3]   = 0x00, .h_scaler8[4]   = 0x00, .h_scaler8[5]   = 0x00,
/*B9 0x9e*/	.h_scaler9[0]   = 0x80, .h_scaler9[1]   = 0x80, .h_scaler9[2]   = 0x80, .h_scaler9[3]   = 0x80, .h_scaler9[4]   = 0x80, .h_scaler9[5]   = 0x80,
			.pn_auto[0]    	= 0x00, .pn_auto[1]		= 0x00, .pn_auto[2]    	= 0x00, .pn_auto[3]    	= 0x00, .pn_auto[4]    	= 0x00, .pn_auto[5]    	= 0x00,
			.comb_mode[0]   = 0x05, .comb_mode[1]	= 0x05, .comb_mode[2]   = 0x05, .comb_mode[3]   = 0x05, .comb_mode[4]  	= 0x05, .comb_mode[5]   = 0x05,
			.h_pll_op_a[0]  = 0x72, .h_pll_op_a[1]  = 0x72, .h_pll_op_a[2]  = 0x72, .h_pll_op_a[3]  = 0x72, .h_pll_op_a[4]  = 0x72, .h_pll_op_a[5]  = 0x72,
			.mem_path[0]	= 0x10, .mem_path[1]	= 0x10, .mem_path[2]	= 0x10, .mem_path[3]	= 0x10, .mem_path[4]	= 0x10, .mem_path[5]	= 0x10,
			.fsc_lock_speed[0] = 0xdc, .fsc_lock_speed[1] = 0xdc, .fsc_lock_speed[2] = 0xdc, .fsc_lock_speed[3] = 0xdc, .fsc_lock_speed[4] = 0xdc, .fsc_lock_speed[5] = 0xdc,

			.format_set1[0] = 0x02, .format_set1[1] = 0x02, .format_set1[2] = 0x02, .format_set1[3] = 0x02, .format_set1[4] = 0x02, .format_set1[5] = 0x02,
			.format_set2[0] = 0x02, .format_set2[1] = 0x02, .format_set2[2] = 0x02, .format_set2[3] = 0x02, .format_set2[4] = 0x02, .format_set2[5] = 0x02,

			.v_delay[0]     = 0x80, .v_delay[1]     = 0x80, .v_delay[2]     = 0x80, .v_delay[3]     = 0x80, .v_delay[4]     = 0x80, .v_delay[5]     = 0x80,
		},
	},

#ifdef __FOR_HIK_DEMO_180208
	[ TVI_4M_25P ] = /* o */
	{
		/* base */
		{
			.eq_bypass[0] 	= 0x22, .eq_bypass[1] 	= 0x22, .eq_bypass[2] 	= 0x22, .eq_bypass[3] 	= 0x22, .eq_bypass[4] 	= 0x22, .eq_bypass[5] 	= 0x22,    // Bank5 0x30
			.eq_band_sel[0] = 0x77, .eq_band_sel[1] = 0x73, .eq_band_sel[2] = 0x77, .eq_band_sel[3] = 0x63, .eq_band_sel[4] = 0x43, .eq_band_sel[5] = 0x43,    // BankA 0x31
			.eq_gain_sel[0] = 0x78, .eq_gain_sel[1] = 0x7a, .eq_gain_sel[2] = 0x7f, .eq_gain_sel[3] = 0x7e, .eq_gain_sel[4] = 0x7e, .eq_gain_sel[5] = 0x7f,    // BankA 0x32
			.deq_a_on[0] 	= 0x00, .deq_a_on[1] 	= 0x01, .deq_a_on[2] 	= 0x01, .deq_a_on[3] 	= 0x01, .deq_a_on[4] 	= 0x01, .deq_a_on[5] 	= 0x01,    // BankA 0x33
			.deq_a_sel[0] 	= 0x00, .deq_a_sel[1] 	= 0x92, .deq_a_sel[2] 	= 0x93, .deq_a_sel[3] 	= 0x94, .deq_a_sel[4] 	= 0x92, .deq_a_sel[5] 	= 0x92,    // BankA 0x34
			.deq_b_sel[0] 	= 0x00, .deq_b_sel[1] 	= 0x00, .deq_b_sel[2] 	= 0x00, .deq_b_sel[3] 	= 0x20, .deq_b_sel[4] 	= 0x00, .deq_b_sel[5] 	= 0x00,    // BankA 0x35
		},
		/* coeff */
		{
			.deqA_01[0] = 0xAC, .deqA_01[1] = 0xAC, .deqA_01[2] = 0xAC, .deqA_01[3] = 0xAC, .deqA_01[4] = 0xAC, .deqA_01[5] = 0xAC,		// BankA 0x30
			.deqA_02[0] = 0x78, .deqA_02[1] = 0x78, .deqA_02[2] = 0x78, .deqA_02[3] = 0x78, .deqA_02[4] = 0x78, .deqA_02[5] = 0x78,		// BankA 0x31
			.deqA_03[0] = 0x17, .deqA_03[1] = 0x17, .deqA_03[2] = 0x17, .deqA_03[3] = 0x17, .deqA_03[4] = 0x17, .deqA_03[5] = 0x17,		// BankA 0x32
			.deqA_04[0] = 0xC1, .deqA_04[1] = 0xC1, .deqA_04[2] = 0xC1, .deqA_04[3] = 0xC1, .deqA_04[4] = 0xC1, .deqA_04[5] = 0xC1,     // BankA 0x33
			.deqA_05[0] = 0x40, .deqA_05[1] = 0x40, .deqA_05[2] = 0x40, .deqA_05[3] = 0x40, .deqA_05[4] = 0x40, .deqA_05[5] = 0x40,     // BankA 0x34
			.deqA_06[0] = 0x00, .deqA_06[1] = 0x00, .deqA_06[2] = 0x00, .deqA_06[3] = 0x00, .deqA_06[4] = 0x00, .deqA_06[5] = 0x00,     // BankA 0x35
			.deqA_07[0] = 0xC3, .deqA_07[1] = 0xC3, .deqA_07[2] = 0xC3, .deqA_07[3] = 0xC3, .deqA_07[4] = 0xC3, .deqA_07[5] = 0xC3,     // BankA 0x36
			.deqA_08[0] = 0x0A, .deqA_08[1] = 0x0A, .deqA_08[2] = 0x0A, .deqA_08[3] = 0x0A, .deqA_08[4] = 0x0A, .deqA_08[5] = 0x0A,     // BankA 0x37
			.deqA_09[0] = 0x00, .deqA_09[1] = 0x00, .deqA_09[2] = 0x00, .deqA_09[3] = 0x00, .deqA_09[4] = 0x00, .deqA_09[5] = 0x00,     // BankA 0x38
			.deqA_10[0] = 0x02, .deqA_10[1] = 0x02, .deqA_10[2] = 0x02, .deqA_10[3] = 0x02, .deqA_10[4] = 0x02, .deqA_10[5] = 0x02,     // BankA 0x39
			.deqA_11[0] = 0x00, .deqA_11[1] = 0x00, .deqA_11[2] = 0x00, .deqA_11[3] = 0x00, .deqA_11[4] = 0x00, .deqA_11[5] = 0x00,     // BankA 0x3a
			.deqA_12[0] = 0xB2, .deqA_12[1] = 0xB2, .deqA_12[2] = 0xB2, .deqA_12[3] = 0xB2, .deqA_12[4] = 0xB2, .deqA_12[5] = 0xB2,     // BankA 0x3b
		},
		/* color */
		{
			.contrast[0] 		= 0x80, .contrast[1] 		= 0x6b, .contrast[2] 		= 0x90, .contrast[3] 		= 0x66, .contrast[4] 		= 0x61, .contrast[5] 		= 0x65,
			.h_peaking[0] 		= 0x10, .h_peaking[1] 		= 0x10, .h_peaking[2] 		= 0x10, .h_peaking[3] 		= 0x00, .h_peaking[4] 		= 0x30, .h_peaking[5] 		= 0x20,
			.c_filter[0]		= 0x81, .c_filter[1] 		= 0x82, .c_filter[2]	 	= 0x92, .c_filter[3] 		= 0x92, .c_filter[4] 		= 0xc4, .c_filter[5] 		= 0xc4,

			.hue[0] 			= 0x00, .hue[1] 			= 0x00, .hue[2] 			= 0x02, .hue[3] 			= 0x02, .hue[4] 			= 0x02, .hue[5] 			= 0x02,
			.u_gain[0] 			= 0x30, .u_gain[1] 			= 0x28, .u_gain[2] 			= 0x30, .u_gain[3] 			= 0x34, .u_gain[4] 			= 0x34, .u_gain[5] 			= 0x34,
			.v_gain[0] 			= 0x3a, .v_gain[1] 			= 0x38, .v_gain[2] 			= 0x18, .v_gain[3] 			= 0x40, .v_gain[4] 			= 0x40, .v_gain[5] 			= 0x40,
			.u_offset[0] 		= 0x02, .u_offset[1] 		= 0x00, .u_offset[2] 		= 0x00, .u_offset[3] 		= 0x00, .u_offset[4] 		= 0x00, .u_offset[5] 		= 0x00,
			.v_offset[0] 		= 0xf8, .v_offset[1] 		= 0xf8, .v_offset[2] 		= 0xf8, .v_offset[3] 		= 0xf8, .v_offset[4] 		= 0xf8, .v_offset[5] 		= 0xf8,

			.black_level[0] 	= 0x7c, .black_level[1] 	= 0x87, .black_level[2] 	= 0x90, .black_level[3] 	= 0x8a, .black_level[4] 	= 0x8d, .black_level[5] 	= 0x8e,
			.acc_ref[0]			= 0x57, .acc_ref[1]			= 0x57, .acc_ref[2]			= 0x57, .acc_ref[3]			= 0x57, .acc_ref[4]			= 0x47, .acc_ref[5]			= 0x37,
			.cti_delay[0]		= 0x80, .cti_delay[1]		= 0x80, .cti_delay[2]		= 0x80, .cti_delay[3]		= 0x80, .cti_delay[4]		= 0x80, .cti_delay[5]		= 0x80,
			.sub_saturation[0] 	= 0xc0, .sub_saturation[1] 	= 0xc0, .sub_saturation[2] 	= 0xf0, .sub_saturation[3] 	= 0x9c, .sub_saturation[4] 	= 0xa0, .sub_saturation[5] 	= 0xa0,

			.burst_dec_a[0] 	= 0x2a, .burst_dec_a[1] 	= 0x2a, .burst_dec_a[2] 	= 0x2a, .burst_dec_a[3] 	= 0x2a, .burst_dec_a[4] 	= 0x00, .burst_dec_a[5] 	= 0x2a,
			.burst_dec_b[0] 	= 0x00, .burst_dec_b[1] 	= 0x00, .burst_dec_b[2] 	= 0x00, .burst_dec_b[3] 	= 0x00, .burst_dec_b[4] 	= 0x00, .burst_dec_b[5] 	= 0x00,
			.burst_dec_c[0] 	= 0x30, .burst_dec_c[1] 	= 0x30, .burst_dec_c[2] 	= 0x30, .burst_dec_c[3] 	= 0x00, .burst_dec_c[4] 	= 0x00, .burst_dec_c[5] 	= 0x00,

			.c_option[0] 		= 0x80, .c_option[1] 		= 0x80, .c_option[2] 		= 0x80, .c_option[3] 		= 0x90, .c_option[4] 		= 0xa0, .c_option[5] 		= 0xa0,

			.y_filter_b[0]		= 0x10, .y_filter_b[1]		= 0x10, .y_filter_b[2]		= 0x10, .y_filter_b[3]		= 0x10, .y_filter_b[4]		= 0x10, .y_filter_b[5]		= 0x10,
			.y_filter_b_sel[0]	= 0x1e,	.y_filter_b_sel[1]	= 0x1e,	.y_filter_b_sel[2]	= 0x1e, .y_filter_b_sel[3]	= 0x1e, .y_filter_b_sel[4]	= 0x1e, .y_filter_b_sel[5]	= 0x1e,
		},
		/* timing_a */
		{
			.h_delay_a[0] = 0x80, .h_delay_a[1] = 0x80, .h_delay_a[2] = 0x7e, .h_delay_a[3] = 0x7e, .h_delay_a[4] = 0x7e, .h_delay_a[5] = 0x7e,
			.h_delay_b[0] = 0x10, .h_delay_b[1] = 0x10, .h_delay_b[2] = 0x10, .h_delay_b[3] = 0x10, .h_delay_b[4] = 0x10, .h_delay_b[5] = 0x10,
			.h_delay_c[0] = 0x02, .h_delay_c[1] = 0x02, .h_delay_c[2] = 0x02, .h_delay_c[3] = 0x02, .h_delay_c[4] = 0x02, .h_delay_c[5] = 0x02,
			.y_delay[0]   = 0x00, .y_delay[1]   = 0x00, .y_delay[2]   = 0x00, .y_delay[3]   = 0x00, .y_delay[4]   = 0x00, .y_delay[5] = 0x00,

		},
		/* clk */
		{
			.clk_adc[0] = 0x05, .clk_adc[1] = 0x05, .clk_adc[2] = 0x05, .clk_adc[3] = 0x05, .clk_adc[4] = 0x05, .clk_adc[5] = 0x05,
			.clk_dec[0] = 0x44, .clk_dec[1] = 0x44, .clk_dec[2] = 0x44, .clk_dec[3] = 0x44, .clk_dec[4] = 0x44, .clk_dec[5] = 0x44,
		},
		/* timing_b */
		{
/*B9 0x96*/	.h_scaler1[0]  = 0x01, .h_scaler1[1]   = 0x01, .h_scaler1[2]   = 0x01, .h_scaler1[3]   = 0x01, .h_scaler1[4]   = 0x01, .h_scaler1[5]   = 0x01,
/*B9 0x97*/	.h_scaler2[0]  = 0x00, .h_scaler2[1]   = 0x00, .h_scaler2[2]   = 0x00, .h_scaler2[3]   = 0x00, .h_scaler2[4]   = 0x00, .h_scaler2[5]   = 0x00,
/*B9 0x98*/	.h_scaler3[0]  = 0x00, .h_scaler3[1]   = 0x00, .h_scaler3[2]   = 0x00, .h_scaler3[3]   = 0x00, .h_scaler3[4]   = 0x00, .h_scaler3[5]   = 0x00,
/*B9 0x99*/	.h_scaler4[0]  = 0x00, .h_scaler4[1]   = 0x00, .h_scaler4[2]   = 0x00, .h_scaler4[3]   = 0x00, .h_scaler4[4]   = 0x00, .h_scaler4[5]   = 0x00,
/*B9 0x9a*/	.h_scaler5[0]  = 0x00, .h_scaler5[1]   = 0x00, .h_scaler5[2]   = 0x00, .h_scaler5[3]   = 0x00, .h_scaler5[4]   = 0x00, .h_scaler5[5]   = 0x00,
/*B9 0x9b*/	.h_scaler6[0]  = 0x00, .h_scaler6[1]   = 0x00, .h_scaler6[2]   = 0x00, .h_scaler6[3]   = 0x00, .h_scaler6[4]   = 0x00, .h_scaler6[5]   = 0x00,
/*B9 0x9c*/	.h_scaler7[0]  = 0x00, .h_scaler7[1]   = 0x00, .h_scaler7[2]   = 0x00, .h_scaler7[3]   = 0x00, .h_scaler7[4]   = 0x00, .h_scaler7[5]   = 0x00,
/*B9 0x9d*/	.h_scaler8[0]  = 0x00, .h_scaler8[1]   = 0x00, .h_scaler8[2]   = 0x00, .h_scaler8[3]   = 0x00, .h_scaler8[4]   = 0x00, .h_scaler8[5]   = 0x00,
/*B9 0x9e*/	.h_scaler9[0]  = 0x00, .h_scaler9[1]   = 0x00, .h_scaler9[2]   = 0x00, .h_scaler9[3]   = 0x00, .h_scaler9[4]   = 0x00, .h_scaler9[5]   = 0x00,


/*B9 0x40*/	.pn_auto[0]    	= 0x00, .pn_auto[1]		= 0x00, .pn_auto[2]    	= 0x00, .pn_auto[3]    	= 0x00, .pn_auto[4]    	= 0x00, .pn_auto[5]    	= 0x00,

/*B5 0x90*/	.comb_mode[0]   = 0x05, .comb_mode[1]	= 0x05, .comb_mode[2]   = 0x05, .comb_mode[3]   = 0x05, .comb_mode[4]  	= 0x05, .comb_mode[5]   = 0x05,
/*B9 0xb9*/	.h_pll_op_a[0]  = 0x72, .h_pll_op_a[1]  = 0x72, .h_pll_op_a[2]  = 0x72, .h_pll_op_a[3]  = 0x72, .h_pll_op_a[4]  = 0x72, .h_pll_op_a[5]  = 0x72,
/*B9 0x57*/	.mem_path[0]	= 0x10, .mem_path[1]	= 0x10, .mem_path[2]	= 0x10, .mem_path[3]	= 0x10, .mem_path[4]	= 0x10, .mem_path[5]	= 0x10,
			.fsc_lock_speed[0] = 0xdc, .fsc_lock_speed[1] = 0xdc, .fsc_lock_speed[2] = 0xdc, .fsc_lock_speed[3] = 0xdc, .fsc_lock_speed[4] = 0xdc, .fsc_lock_speed[5] = 0xdc,

/*B0 0x81*/	.format_set1[0] = 0x0f, .format_set1[1] = 0x0f, .format_set1[2] = 0x0f, .format_set1[3] = 0x0f, .format_set1[4] = 0x0f, .format_set1[5] = 0x0f,
/*B0 0x85*/	.format_set2[0] = 0x03, .format_set2[1] = 0x03, .format_set2[2] = 0x03, .format_set2[3] = 0x03, .format_set2[4] = 0x03, .format_set2[5] = 0x03,

/*B0 0x64*/ .v_delay[0]     = 0x80, .v_delay[1]     = 0x80, .v_delay[2]     = 0x80, .v_delay[3]     = 0x80, .v_delay[4]     = 0x80, .v_delay[5]     = 0x80,
		},
	},
#else
	[ TVI_4M_25P ] = /* o */
		{
			/* base */
			{
				.eq_bypass[0] 	= 0x22, .eq_bypass[1] 	= 0x22, .eq_bypass[2] 	= 0x22, .eq_bypass[3] 	= 0x22, .eq_bypass[4] 	= 0x22, .eq_bypass[5] 	= 0x22,    // Bank5 0x30
				.eq_band_sel[0] = 0x77, .eq_band_sel[1] = 0x77, .eq_band_sel[2] = 0x77, .eq_band_sel[3] = 0x67, .eq_band_sel[4] = 0x47, .eq_band_sel[5] = 0x47,    // BankA 0x31
				.eq_gain_sel[0] = 0x78, .eq_gain_sel[1] = 0x7f, .eq_gain_sel[2] = 0x7f, .eq_gain_sel[3] = 0x7f, .eq_gain_sel[4] = 0x7f, .eq_gain_sel[5] = 0x7f,    // BankA 0x32
				.deq_a_on[0] 	= 0x00, .deq_a_on[1] 	= 0x01, .deq_a_on[2] 	= 0x01, .deq_a_on[3] 	= 0x01, .deq_a_on[4] 	= 0x01, .deq_a_on[5] 	= 0x01,    // BankA 0x33
				.deq_a_sel[0] 	= 0x00, .deq_a_sel[1] 	= 0x92, .deq_a_sel[2] 	= 0x93, .deq_a_sel[3] 	= 0x94, .deq_a_sel[4] 	= 0x92, .deq_a_sel[5] 	= 0x92,    // BankA 0x34
				.deq_b_sel[0] 	= 0x00, .deq_b_sel[1] 	= 0x00, .deq_b_sel[2] 	= 0x00, .deq_b_sel[3] 	= 0x20, .deq_b_sel[4] 	= 0x00, .deq_b_sel[5] 	= 0x00,    // BankA 0x35
			},
			/* coeff */
			{
				.deqA_01[0] = 0xAC, .deqA_01[1] = 0xAC, .deqA_01[2] = 0xAC, .deqA_01[3] = 0xAC, .deqA_01[4] = 0xAC, .deqA_01[5] = 0xAC,		// BankA 0x30
				.deqA_02[0] = 0x78, .deqA_02[1] = 0x78, .deqA_02[2] = 0x78, .deqA_02[3] = 0x78, .deqA_02[4] = 0x78, .deqA_02[5] = 0x78,		// BankA 0x31
				.deqA_03[0] = 0x17, .deqA_03[1] = 0x17, .deqA_03[2] = 0x17, .deqA_03[3] = 0x17, .deqA_03[4] = 0x17, .deqA_03[5] = 0x17,		// BankA 0x32
				.deqA_04[0] = 0xC1, .deqA_04[1] = 0xC1, .deqA_04[2] = 0xC1, .deqA_04[3] = 0xC1, .deqA_04[4] = 0xC1, .deqA_04[5] = 0xC1,     // BankA 0x33
				.deqA_05[0] = 0x40, .deqA_05[1] = 0x40, .deqA_05[2] = 0x40, .deqA_05[3] = 0x40, .deqA_05[4] = 0x40, .deqA_05[5] = 0x40,     // BankA 0x34
				.deqA_06[0] = 0x00, .deqA_06[1] = 0x00, .deqA_06[2] = 0x00, .deqA_06[3] = 0x00, .deqA_06[4] = 0x00, .deqA_06[5] = 0x00,     // BankA 0x35
				.deqA_07[0] = 0xC3, .deqA_07[1] = 0xC3, .deqA_07[2] = 0xC3, .deqA_07[3] = 0xC3, .deqA_07[4] = 0xC3, .deqA_07[5] = 0xC3,     // BankA 0x36
				.deqA_08[0] = 0x0A, .deqA_08[1] = 0x0A, .deqA_08[2] = 0x0A, .deqA_08[3] = 0x0A, .deqA_08[4] = 0x0A, .deqA_08[5] = 0x0A,     // BankA 0x37
				.deqA_09[0] = 0x00, .deqA_09[1] = 0x00, .deqA_09[2] = 0x00, .deqA_09[3] = 0x00, .deqA_09[4] = 0x00, .deqA_09[5] = 0x00,     // BankA 0x38
				.deqA_10[0] = 0x02, .deqA_10[1] = 0x02, .deqA_10[2] = 0x02, .deqA_10[3] = 0x02, .deqA_10[4] = 0x02, .deqA_10[5] = 0x02,     // BankA 0x39
				.deqA_11[0] = 0x00, .deqA_11[1] = 0x00, .deqA_11[2] = 0x00, .deqA_11[3] = 0x00, .deqA_11[4] = 0x00, .deqA_11[5] = 0x00,     // BankA 0x3a
				.deqA_12[0] = 0xB2, .deqA_12[1] = 0xB2, .deqA_12[2] = 0xB2, .deqA_12[3] = 0xB2, .deqA_12[4] = 0xB2, .deqA_12[5] = 0xB2,     // BankA 0x3b
			},
			/* color */
			{
				.contrast[0] 		= 0x6e, .contrast[1] 		= 0x6b, .contrast[2] 		= 0x98, .contrast[3] 		= 0x66, .contrast[4] 		= 0x61, .contrast[5] 		= 0x65,
				.h_peaking[0] 		= 0x10, .h_peaking[1] 		= 0x10, .h_peaking[2] 		= 0x10, .h_peaking[3] 		= 0x00, .h_peaking[4] 		= 0x30, .h_peaking[5] 		= 0x20,
				.c_filter[0]		= 0x81, .c_filter[1] 		= 0x92, .c_filter[2]	 	= 0xa2, .c_filter[3] 		= 0xa2, .c_filter[4] 		= 0xc4, .c_filter[5] 		= 0xc4,

				.hue[0] 			= 0x00, .hue[1] 			= 0x00, .hue[2] 			= 0x02, .hue[3] 			= 0x02, .hue[4] 			= 0x02, .hue[5] 			= 0x02,
				.u_gain[0] 			= 0x30, .u_gain[1] 			= 0x28, .u_gain[2] 			= 0x34, .u_gain[3] 			= 0x34, .u_gain[4] 			= 0x34, .u_gain[5] 			= 0x34,
				.v_gain[0] 			= 0x3a, .v_gain[1] 			= 0x38, .v_gain[2] 			= 0x40, .v_gain[3] 			= 0x40, .v_gain[4] 			= 0x40, .v_gain[5] 			= 0x40,
				.u_offset[0] 		= 0x02, .u_offset[1] 		= 0x00, .u_offset[2] 		= 0x00, .u_offset[3] 		= 0x00, .u_offset[4] 		= 0x00, .u_offset[5] 		= 0x00,
				.v_offset[0] 		= 0xf8, .v_offset[1] 		= 0xf8, .v_offset[2] 		= 0xf8, .v_offset[3] 		= 0xf8, .v_offset[4] 		= 0xf8, .v_offset[5] 		= 0xf8,

				.black_level[0] 	= 0x87, .black_level[1] 	= 0x87, .black_level[2] 	= 0x88, .black_level[3] 	= 0x8a, .black_level[4] 	= 0x8d, .black_level[5] 	= 0x8e,
				.acc_ref[0]			= 0x57, .acc_ref[1]			= 0x57, .acc_ref[2]			= 0x57, .acc_ref[3]			= 0x57, .acc_ref[4]			= 0x47, .acc_ref[5]			= 0x37,
				.cti_delay[0]		= 0x80, .cti_delay[1]		= 0x80, .cti_delay[2]		= 0x80, .cti_delay[3]		= 0x80, .cti_delay[4]		= 0xa0, .cti_delay[5]		= 0x80,
				.sub_saturation[0] 	= 0x80, .sub_saturation[1] 	= 0xa0, .sub_saturation[2] 	= 0xb0, .sub_saturation[3] 	= 0x9c, .sub_saturation[4] 	= 0x00, .sub_saturation[5] 	= 0xa0,

				.burst_dec_a[0] 	= 0x2a, .burst_dec_a[1] 	= 0x2a, .burst_dec_a[2] 	= 0x2a, .burst_dec_a[3] 	= 0x2a, .burst_dec_a[4] 	= 0x00, .burst_dec_a[5] 	= 0x2a,
				.burst_dec_b[0] 	= 0x00, .burst_dec_b[1] 	= 0x00, .burst_dec_b[2] 	= 0x00, .burst_dec_b[3] 	= 0x00, .burst_dec_b[4] 	= 0x00, .burst_dec_b[5] 	= 0x00,
				.burst_dec_c[0] 	= 0x30, .burst_dec_c[1] 	= 0x30, .burst_dec_c[2] 	= 0x30, .burst_dec_c[3] 	= 0x00, .burst_dec_c[4] 	= 0x00, .burst_dec_c[5] 	= 0x00,

				.c_option[0] 		= 0x80, .c_option[1] 		= 0xa0, .c_option[2] 		= 0x90, .c_option[3] 		= 0xa0, .c_option[4] 		= 0xb0, .c_option[5] 		= 0xb0,

				.y_filter_b[0]		= 0x10, .y_filter_b[1]		= 0x10, .y_filter_b[2]		= 0x10, .y_filter_b[3]		= 0x10, .y_filter_b[4]		= 0x10, .y_filter_b[5]		= 0x10,
				.y_filter_b_sel[0]	= 0x1e,	.y_filter_b_sel[1]	= 0x1e,	.y_filter_b_sel[2]	= 0x1e, .y_filter_b_sel[3]	= 0x1e, .y_filter_b_sel[4]	= 0x1e, .y_filter_b_sel[5]	= 0x1e,
			},
			/* timing_a */
			{
				.h_delay_a[0] = 0x80, .h_delay_a[1] = 0x80, .h_delay_a[2] = 0x7e, .h_delay_a[3] = 0x7e, .h_delay_a[4] = 0x7e, .h_delay_a[5] = 0x7e,
				.h_delay_b[0] = 0x10, .h_delay_b[1] = 0x10, .h_delay_b[2] = 0x10, .h_delay_b[3] = 0x10, .h_delay_b[4] = 0x10, .h_delay_b[5] = 0x10,
				.h_delay_c[0] = 0x02, .h_delay_c[1] = 0x02, .h_delay_c[2] = 0x02, .h_delay_c[3] = 0x02, .h_delay_c[4] = 0x02, .h_delay_c[5] = 0x02,
				.y_delay[0]   = 0x00, .y_delay[1]   = 0x00, .y_delay[2]   = 0x00, .y_delay[3]   = 0x00, .y_delay[4]   = 0x00, .y_delay[5] = 0x00,

			},
			/* clk */
			{
				.clk_adc[0] = 0x05, .clk_adc[1] = 0x05, .clk_adc[2] = 0x05, .clk_adc[3] = 0x05, .clk_adc[4] = 0x05, .clk_adc[5] = 0x05,
				.clk_dec[0] = 0x44, .clk_dec[1] = 0x44, .clk_dec[2] = 0x44, .clk_dec[3] = 0x44, .clk_dec[4] = 0x44, .clk_dec[5] = 0x44,
			},
			/* timing_b */
			{
	/*B9 0x96*/	.h_scaler1[0]  = 0x01, .h_scaler1[1]   = 0x01, .h_scaler1[2]   = 0x01, .h_scaler1[3]   = 0x01, .h_scaler1[4]   = 0x01, .h_scaler1[5]   = 0x01,
	/*B9 0x97*/	.h_scaler2[0]  = 0x00, .h_scaler2[1]   = 0x00, .h_scaler2[2]   = 0x00, .h_scaler2[3]   = 0x00, .h_scaler2[4]   = 0x00, .h_scaler2[5]   = 0x00,
	/*B9 0x98*/	.h_scaler3[0]  = 0x00, .h_scaler3[1]   = 0x00, .h_scaler3[2]   = 0x00, .h_scaler3[3]   = 0x00, .h_scaler3[4]   = 0x00, .h_scaler3[5]   = 0x00,
	/*B9 0x99*/	.h_scaler4[0]  = 0x00, .h_scaler4[1]   = 0x00, .h_scaler4[2]   = 0x00, .h_scaler4[3]   = 0x00, .h_scaler4[4]   = 0x00, .h_scaler4[5]   = 0x00,
	/*B9 0x9a*/	.h_scaler5[0]  = 0x00, .h_scaler5[1]   = 0x00, .h_scaler5[2]   = 0x00, .h_scaler5[3]   = 0x00, .h_scaler5[4]   = 0x00, .h_scaler5[5]   = 0x00,
	/*B9 0x9b*/	.h_scaler6[0]  = 0x00, .h_scaler6[1]   = 0x00, .h_scaler6[2]   = 0x00, .h_scaler6[3]   = 0x00, .h_scaler6[4]   = 0x00, .h_scaler6[5]   = 0x00,
	/*B9 0x9c*/	.h_scaler7[0]  = 0x00, .h_scaler7[1]   = 0x00, .h_scaler7[2]   = 0x00, .h_scaler7[3]   = 0x00, .h_scaler7[4]   = 0x00, .h_scaler7[5]   = 0x00,
	/*B9 0x9d*/	.h_scaler8[0]  = 0x00, .h_scaler8[1]   = 0x00, .h_scaler8[2]   = 0x00, .h_scaler8[3]   = 0x00, .h_scaler8[4]   = 0x00, .h_scaler8[5]   = 0x00,
	/*B9 0x9e*/	.h_scaler9[0]  = 0x00, .h_scaler9[1]   = 0x00, .h_scaler9[2]   = 0x00, .h_scaler9[3]   = 0x00, .h_scaler9[4]   = 0x00, .h_scaler9[5]   = 0x00,


	/*B9 0x40*/	.pn_auto[0]    	= 0x00, .pn_auto[1]		= 0x00, .pn_auto[2]    	= 0x00, .pn_auto[3]    	= 0x00, .pn_auto[4]    	= 0x00, .pn_auto[5]    	= 0x00,

	/*B5 0x90*/	.comb_mode[0]   = 0x05, .comb_mode[1]	= 0x05, .comb_mode[2]   = 0x05, .comb_mode[3]   = 0x05, .comb_mode[4]  	= 0x05, .comb_mode[5]   = 0x05,
	/*B9 0xb9*/	.h_pll_op_a[0]  = 0x72, .h_pll_op_a[1]  = 0x72, .h_pll_op_a[2]  = 0x72, .h_pll_op_a[3]  = 0x72, .h_pll_op_a[4]  = 0x72, .h_pll_op_a[5]  = 0x72,
	/*B9 0x57*/	.mem_path[0]	= 0x10, .mem_path[1]	= 0x10, .mem_path[2]	= 0x10, .mem_path[3]	= 0x10, .mem_path[4]	= 0x10, .mem_path[5]	= 0x10,
				.fsc_lock_speed[0] = 0xdc, .fsc_lock_speed[1] = 0xdc, .fsc_lock_speed[2] = 0xdc, .fsc_lock_speed[3] = 0xdc, .fsc_lock_speed[4] = 0xdc, .fsc_lock_speed[5] = 0xdc,

	/*B0 0x81*/	.format_set1[0] = 0x0f, .format_set1[1] = 0x0f, .format_set1[2] = 0x0f, .format_set1[3] = 0x0f, .format_set1[4] = 0x0f, .format_set1[5] = 0x0f,
	/*B0 0x85*/	.format_set2[0] = 0x03, .format_set2[1] = 0x03, .format_set2[2] = 0x03, .format_set2[3] = 0x03, .format_set2[4] = 0x03, .format_set2[5] = 0x03,

	/*B0 0x64*/ .v_delay[0]     = 0x80, .v_delay[1]     = 0x80, .v_delay[2]     = 0x80, .v_delay[3]     = 0x80, .v_delay[4]     = 0x80, .v_delay[5]     = 0x80,
			},
		},

#endif
	[ TVI_4M_30P ] = { /* o */
		/* base */
		{
			.eq_bypass[0] 	= 0x22, .eq_bypass[1] 	= 0x22, .eq_bypass[2] 	= 0x22, .eq_bypass[3] 	= 0x22, .eq_bypass[4] 	= 0x22, .eq_bypass[5] 	= 0x22,    // Bank5 0x30
			.eq_band_sel[0] = 0x77, .eq_band_sel[1] = 0x77, .eq_band_sel[2] = 0x77, .eq_band_sel[3] = 0x67, .eq_band_sel[4] = 0x47, .eq_band_sel[5] = 0x47,    // BankA 0x31
			.eq_gain_sel[0] = 0x78, .eq_gain_sel[1] = 0x7f, .eq_gain_sel[2] = 0x7f, .eq_gain_sel[3] = 0x7f, .eq_gain_sel[4] = 0x7f, .eq_gain_sel[5] = 0x7f,    // BankA 0x32
			.deq_a_on[0] 	= 0x00, .deq_a_on[1] 	= 0x01, .deq_a_on[2] 	= 0x01, .deq_a_on[3] 	= 0x01, .deq_a_on[4] 	= 0x01, .deq_a_on[5] 	= 0x01,    // BankA 0x33
			.deq_a_sel[0] 	= 0x00, .deq_a_sel[1] 	= 0x92, .deq_a_sel[2] 	= 0x93, .deq_a_sel[3] 	= 0x94, .deq_a_sel[4] 	= 0x92, .deq_a_sel[5] 	= 0x92,    // BankA 0x34
			.deq_b_sel[0] 	= 0x00, .deq_b_sel[1] 	= 0x00, .deq_b_sel[2] 	= 0x00, .deq_b_sel[3] 	= 0x20, .deq_b_sel[4] 	= 0x00, .deq_b_sel[5] 	= 0x00,    // BankA 0x35
		},
		/* coeff */
		{
			.deqA_01[0] = 0xAC, .deqA_01[1] = 0xAC, .deqA_01[2] = 0xAC, .deqA_01[3] = 0xAC, .deqA_01[4] = 0xAC, .deqA_01[5] = 0xAC,		// BankA 0x30
			.deqA_02[0] = 0x78, .deqA_02[1] = 0x78, .deqA_02[2] = 0x78, .deqA_02[3] = 0x78, .deqA_02[4] = 0x78, .deqA_02[5] = 0x78,		// BankA 0x31
			.deqA_03[0] = 0x17, .deqA_03[1] = 0x17, .deqA_03[2] = 0x17, .deqA_03[3] = 0x17, .deqA_03[4] = 0x17, .deqA_03[5] = 0x17,		// BankA 0x32
			.deqA_04[0] = 0xC1, .deqA_04[1] = 0xC1, .deqA_04[2] = 0xC1, .deqA_04[3] = 0xC1, .deqA_04[4] = 0xC1, .deqA_04[5] = 0xC1,     // BankA 0x33
			.deqA_05[0] = 0x40, .deqA_05[1] = 0x40, .deqA_05[2] = 0x40, .deqA_05[3] = 0x40, .deqA_05[4] = 0x40, .deqA_05[5] = 0x40,     // BankA 0x34
			.deqA_06[0] = 0x00, .deqA_06[1] = 0x00, .deqA_06[2] = 0x00, .deqA_06[3] = 0x00, .deqA_06[4] = 0x00, .deqA_06[5] = 0x00,     // BankA 0x35
			.deqA_07[0] = 0xC3, .deqA_07[1] = 0xC3, .deqA_07[2] = 0xC3, .deqA_07[3] = 0xC3, .deqA_07[4] = 0xC3, .deqA_07[5] = 0xC3,     // BankA 0x36
			.deqA_08[0] = 0x0A, .deqA_08[1] = 0x0A, .deqA_08[2] = 0x0A, .deqA_08[3] = 0x0A, .deqA_08[4] = 0x0A, .deqA_08[5] = 0x0A,     // BankA 0x37
			.deqA_09[0] = 0x00, .deqA_09[1] = 0x00, .deqA_09[2] = 0x00, .deqA_09[3] = 0x00, .deqA_09[4] = 0x00, .deqA_09[5] = 0x00,     // BankA 0x38
			.deqA_10[0] = 0x02, .deqA_10[1] = 0x02, .deqA_10[2] = 0x02, .deqA_10[3] = 0x02, .deqA_10[4] = 0x02, .deqA_10[5] = 0x02,     // BankA 0x39
			.deqA_11[0] = 0x00, .deqA_11[1] = 0x00, .deqA_11[2] = 0x00, .deqA_11[3] = 0x00, .deqA_11[4] = 0x00, .deqA_11[5] = 0x00,     // BankA 0x3a
			.deqA_12[0] = 0xB2, .deqA_12[1] = 0xB2, .deqA_12[2] = 0xB2, .deqA_12[3] = 0xB2, .deqA_12[4] = 0xB2, .deqA_12[5] = 0xB2,     // BankA 0x3b
		},
		/* color */
		{
			.contrast[0] 		= 0x6e, .contrast[1] 		= 0x6b, .contrast[2] 		= 0x98, .contrast[3] 		= 0x66, .contrast[4] 		= 0x61, .contrast[5] 		= 0x65,
			.h_peaking[0] 		= 0x10, .h_peaking[1] 		= 0x10, .h_peaking[2] 		= 0x10, .h_peaking[3] 		= 0x00, .h_peaking[4] 		= 0x30, .h_peaking[5] 		= 0x20,
			.c_filter[0]		= 0x81, .c_filter[1] 		= 0x92, .c_filter[2]	 	= 0xa2, .c_filter[3] 		= 0xa2, .c_filter[4] 		= 0xc4, .c_filter[5] 		= 0xc4,

			.hue[0] 			= 0x00, .hue[1] 			= 0x00, .hue[2] 			= 0x02, .hue[3] 			= 0x02, .hue[4] 			= 0x02, .hue[5] 			= 0x02,
			.u_gain[0] 			= 0x30, .u_gain[1] 			= 0x28, .u_gain[2] 			= 0x34, .u_gain[3] 			= 0x34, .u_gain[4] 			= 0x34, .u_gain[5] 			= 0x34,
			.v_gain[0] 			= 0x3a, .v_gain[1] 			= 0x38, .v_gain[2] 			= 0x40, .v_gain[3] 			= 0x40, .v_gain[4] 			= 0x40, .v_gain[5] 			= 0x40,
			.u_offset[0] 		= 0x02, .u_offset[1] 		= 0x00, .u_offset[2] 		= 0x00, .u_offset[3] 		= 0x00, .u_offset[4] 		= 0x00, .u_offset[5] 		= 0x00,
			.v_offset[0] 		= 0xf8, .v_offset[1] 		= 0xf8, .v_offset[2] 		= 0xf8, .v_offset[3] 		= 0xf8, .v_offset[4] 		= 0xf8, .v_offset[5] 		= 0xf8,

			.black_level[0] 	= 0x87, .black_level[1] 	= 0x87, .black_level[2] 	= 0x88, .black_level[3] 	= 0x8a, .black_level[4] 	= 0x8d, .black_level[5] 	= 0x8e,
			.acc_ref[0]			= 0x57, .acc_ref[1]			= 0x57, .acc_ref[2]			= 0x57, .acc_ref[3]			= 0x57, .acc_ref[4]			= 0x47, .acc_ref[5]			= 0x37,
			.cti_delay[0]		= 0x80, .cti_delay[1]		= 0x80, .cti_delay[2]		= 0x80, .cti_delay[3]		= 0x80, .cti_delay[4]		= 0xa0, .cti_delay[5]		= 0x80,
			.sub_saturation[0] 	= 0x80, .sub_saturation[1] 	= 0xa0, .sub_saturation[2] 	= 0xb0, .sub_saturation[3] 	= 0x9c, .sub_saturation[4] 	= 0x00, .sub_saturation[5] 	= 0xa0,

			.burst_dec_a[0] 	= 0x2a, .burst_dec_a[1] 	= 0x2a, .burst_dec_a[2] 	= 0x2a, .burst_dec_a[3] 	= 0x2a, .burst_dec_a[4] 	= 0x00, .burst_dec_a[5] 	= 0x2a,
			.burst_dec_b[0] 	= 0x00, .burst_dec_b[1] 	= 0x00, .burst_dec_b[2] 	= 0x00, .burst_dec_b[3] 	= 0x00, .burst_dec_b[4] 	= 0x00, .burst_dec_b[5] 	= 0x00,
			.burst_dec_c[0] 	= 0x30, .burst_dec_c[1] 	= 0x30, .burst_dec_c[2] 	= 0x30, .burst_dec_c[3] 	= 0x00, .burst_dec_c[4] 	= 0x00, .burst_dec_c[5] 	= 0x00,

			.c_option[0] 		= 0x80, .c_option[1] 		= 0xa0, .c_option[2] 		= 0x90, .c_option[3] 		= 0xa0, .c_option[4] 		= 0xb0, .c_option[5] 		= 0xb0,

			.y_filter_b[0]		= 0x10, .y_filter_b[1]		= 0x10, .y_filter_b[2]		= 0x10, .y_filter_b[3]		= 0x10, .y_filter_b[4]		= 0x10, .y_filter_b[5]		= 0x10,
			.y_filter_b_sel[0]	= 0x1e,	.y_filter_b_sel[1]	= 0x1e,	.y_filter_b_sel[2]	= 0x1e, .y_filter_b_sel[3]	= 0x1e, .y_filter_b_sel[4]	= 0x1e, .y_filter_b_sel[5]	= 0x1e,
		},
		/* timing_a */
		{
			.h_delay_a[0] = 0x80, .h_delay_a[1] = 0x80, .h_delay_a[2] = 0x7e, .h_delay_a[3] = 0x7e, .h_delay_a[4] = 0x7e, .h_delay_a[5] = 0x7e,
			.h_delay_b[0] = 0x10, .h_delay_b[1] = 0x10, .h_delay_b[2] = 0x10, .h_delay_b[3] = 0x10, .h_delay_b[4] = 0x10, .h_delay_b[5] = 0x10,
			.h_delay_c[0] = 0x02, .h_delay_c[1] = 0x02, .h_delay_c[2] = 0x02, .h_delay_c[3] = 0x02, .h_delay_c[4] = 0x02, .h_delay_c[5] = 0x02,
			.y_delay[0]   = 0x00, .y_delay[1]   = 0x00, .y_delay[2]   = 0x00, .y_delay[3]   = 0x00, .y_delay[4]   = 0x00, .y_delay[5]   = 0x00,

		},
		/* clk */
		{
			.clk_adc[0] = 0x05, .clk_adc[1] = 0x05, .clk_adc[2] = 0x05, .clk_adc[3] = 0x05, .clk_adc[4] = 0x05, .clk_adc[5] = 0x05,
			.clk_dec[0] = 0x44, .clk_dec[1] = 0x44, .clk_dec[2] = 0x44, .clk_dec[3] = 0x44, .clk_dec[4] = 0x44, .clk_dec[5] = 0x44,
		},
		/* timing_b */
		{
	/*B9 0x96*/	.h_scaler1[0]  = 0x01, .h_scaler1[1]   = 0x01, .h_scaler1[2]   = 0x01, .h_scaler1[3]   = 0x01, .h_scaler1[4]   = 0x01, .h_scaler1[5]   = 0x01,
	/*B9 0x97*/	.h_scaler2[0]  = 0x00, .h_scaler2[1]   = 0x00, .h_scaler2[2]   = 0x00, .h_scaler2[3]   = 0x00, .h_scaler2[4]   = 0x00, .h_scaler2[5]   = 0x00,
	/*B9 0x98*/	.h_scaler3[0]  = 0x00, .h_scaler3[1]   = 0x00, .h_scaler3[2]   = 0x00, .h_scaler3[3]   = 0x00, .h_scaler3[4]   = 0x00, .h_scaler3[5]   = 0x00,
	/*B9 0x99*/	.h_scaler4[0]  = 0x00, .h_scaler4[1]   = 0x00, .h_scaler4[2]   = 0x00, .h_scaler4[3]   = 0x00, .h_scaler4[4]   = 0x00, .h_scaler4[5]   = 0x00,
	/*B9 0x9a*/	.h_scaler5[0]  = 0x00, .h_scaler5[1]   = 0x00, .h_scaler5[2]   = 0x00, .h_scaler5[3]   = 0x00, .h_scaler5[4]   = 0x00, .h_scaler5[5]   = 0x00,
	/*B9 0x9b*/	.h_scaler6[0]  = 0x00, .h_scaler6[1]   = 0x00, .h_scaler6[2]   = 0x00, .h_scaler6[3]   = 0x00, .h_scaler6[4]   = 0x00, .h_scaler6[5]   = 0x00,
	/*B9 0x9c*/	.h_scaler7[0]  = 0x00, .h_scaler7[1]   = 0x00, .h_scaler7[2]   = 0x00, .h_scaler7[3]   = 0x00, .h_scaler7[4]   = 0x00, .h_scaler7[5]   = 0x00,
	/*B9 0x9d*/	.h_scaler8[0]  = 0x00, .h_scaler8[1]   = 0x00, .h_scaler8[2]   = 0x00, .h_scaler8[3]   = 0x00, .h_scaler8[4]   = 0x00, .h_scaler8[5]   = 0x00,
	/*B9 0x9e*/	.h_scaler9[0]  = 0x00, .h_scaler9[1]   = 0x00, .h_scaler9[2]   = 0x00, .h_scaler9[3]   = 0x00, .h_scaler9[4]   = 0x00, .h_scaler9[5]   = 0x00,


	/*B9 0x40*/	.pn_auto[0]    	= 0x00, .pn_auto[1]		= 0x00, .pn_auto[2]    	= 0x00, .pn_auto[3]    	= 0x00, .pn_auto[4]    	= 0x00, .pn_auto[5]    	= 0x00,

	/*B5 0x90*/	.comb_mode[0]   = 0x05, .comb_mode[1]	= 0x05, .comb_mode[2]   = 0x05, .comb_mode[3]   = 0x05, .comb_mode[4]  	= 0x05, .comb_mode[5]   = 0x05,
	/*B9 0xb9*/	.h_pll_op_a[0]  = 0x72, .h_pll_op_a[1]  = 0x72, .h_pll_op_a[2]  = 0x72, .h_pll_op_a[3]  = 0x72, .h_pll_op_a[4]  = 0x72, .h_pll_op_a[5]  = 0x72,
	/*B9 0x57*/	.mem_path[0]	= 0x10, .mem_path[1]	= 0x10, .mem_path[2]	= 0x10, .mem_path[3]	= 0x10, .mem_path[4]	= 0x10, .mem_path[5]	= 0x10,
			.fsc_lock_speed[0] = 0xdc, .fsc_lock_speed[1] = 0xdc, .fsc_lock_speed[2] = 0xdc, .fsc_lock_speed[3] = 0xdc, .fsc_lock_speed[4] = 0xdc, .fsc_lock_speed[5] = 0xdc,

	/*B0 0x81*/	.format_set1[0] = 0x0e, .format_set1[1] = 0x0e, .format_set1[2] = 0x0e, .format_set1[3] = 0x0e, .format_set1[4] = 0x0e, .format_set1[5] = 0x0e,
	/*B0 0x85*/	.format_set2[0] = 0x03, .format_set2[1] = 0x03, .format_set2[2] = 0x03, .format_set2[3] = 0x03, .format_set2[4] = 0x03, .format_set2[5] = 0x03,

	/*B0 0x64*/ .v_delay[0]     = 0x80, .v_delay[1]     = 0x80, .v_delay[2]     = 0x80, .v_delay[3]     = 0x80, .v_delay[4]     = 0x80, .v_delay[5]     = 0x80,
		},
	},

	[ TVI_5M_20P ] = { /* o */
			/* base */
			{
				.eq_bypass[0] 	= 0x22, .eq_bypass[1] 	= 0x22, .eq_bypass[2] 	= 0x22, .eq_bypass[3] 	= 0x22, .eq_bypass[4] 	= 0x22, .eq_bypass[5] 	= 0x22,    // Bank5 0x30
				.eq_band_sel[0] = 0x77, .eq_band_sel[1] = 0x77, .eq_band_sel[2] = 0x77, .eq_band_sel[3] = 0x67, .eq_band_sel[4] = 0x67, .eq_band_sel[5] = 0x57,    // BankA 0x31
				.eq_gain_sel[0] = 0x78, .eq_gain_sel[1] = 0x7f, .eq_gain_sel[2] = 0x7f, .eq_gain_sel[3] = 0x7f, .eq_gain_sel[4] = 0x7f, .eq_gain_sel[5] = 0x7f,    // BankA 0x32
				.deq_a_on[0] 	= 0x00, .deq_a_on[1] 	= 0x01, .deq_a_on[2] 	= 0x01, .deq_a_on[3] 	= 0x01, .deq_a_on[4] 	= 0x01, .deq_a_on[5] 	= 0x01,    // BankA 0x33
				.deq_a_sel[0] 	= 0x00, .deq_a_sel[1] 	= 0x92, .deq_a_sel[2] 	= 0x93, .deq_a_sel[3] 	= 0x94, .deq_a_sel[4] 	= 0x94, .deq_a_sel[5] 	= 0x94,    // BankA 0x34
				.deq_b_sel[0] 	= 0x00, .deq_b_sel[1] 	= 0x00, .deq_b_sel[2] 	= 0x00, .deq_b_sel[3] 	= 0x20, .deq_b_sel[4] 	= 0x00, .deq_b_sel[5] 	= 0x00,    // BankA 0x35
			},
			/* coeff */
			{
				.deqA_01[0] = 0xAC, .deqA_01[1] = 0xAC, .deqA_01[2] = 0xAC, .deqA_01[3] = 0xAC, .deqA_01[4] = 0xAC, .deqA_01[5] = 0xAC,		// BankA 0x30
				.deqA_02[0] = 0x78, .deqA_02[1] = 0x78, .deqA_02[2] = 0x78, .deqA_02[3] = 0x78, .deqA_02[4] = 0x78, .deqA_02[5] = 0x78,		// BankA 0x31
				.deqA_03[0] = 0x17, .deqA_03[1] = 0x17, .deqA_03[2] = 0x17, .deqA_03[3] = 0x17, .deqA_03[4] = 0x17, .deqA_03[5] = 0x17,		// BankA 0x32
				.deqA_04[0] = 0xC1, .deqA_04[1] = 0xC1, .deqA_04[2] = 0xC1, .deqA_04[3] = 0xC1, .deqA_04[4] = 0xC1, .deqA_04[5] = 0xC1,     // BankA 0x33
				.deqA_05[0] = 0x40, .deqA_05[1] = 0x40, .deqA_05[2] = 0x40, .deqA_05[3] = 0x40, .deqA_05[4] = 0x40, .deqA_05[5] = 0x40,     // BankA 0x34
				.deqA_06[0] = 0x00, .deqA_06[1] = 0x00, .deqA_06[2] = 0x00, .deqA_06[3] = 0x00, .deqA_06[4] = 0x00, .deqA_06[5] = 0x00,     // BankA 0x35
				.deqA_07[0] = 0xC3, .deqA_07[1] = 0xC3, .deqA_07[2] = 0xC3, .deqA_07[3] = 0xC3, .deqA_07[4] = 0xC3, .deqA_07[5] = 0xC3,     // BankA 0x36
				.deqA_08[0] = 0x0A, .deqA_08[1] = 0x0A, .deqA_08[2] = 0x0A, .deqA_08[3] = 0x0A, .deqA_08[4] = 0x0A, .deqA_08[5] = 0x0A,     // BankA 0x37
				.deqA_09[0] = 0x00, .deqA_09[1] = 0x00, .deqA_09[2] = 0x00, .deqA_09[3] = 0x00, .deqA_09[4] = 0x00, .deqA_09[5] = 0x00,     // BankA 0x38
				.deqA_10[0] = 0x02, .deqA_10[1] = 0x02, .deqA_10[2] = 0x02, .deqA_10[3] = 0x02, .deqA_10[4] = 0x02, .deqA_10[5] = 0x02,     // BankA 0x39
				.deqA_11[0] = 0x00, .deqA_11[1] = 0x00, .deqA_11[2] = 0x00, .deqA_11[3] = 0x00, .deqA_11[4] = 0x00, .deqA_11[5] = 0x00,     // BankA 0x3a
				.deqA_12[0] = 0xB2, .deqA_12[1] = 0xB2, .deqA_12[2] = 0xB2, .deqA_12[3] = 0xB2, .deqA_12[4] = 0xB2, .deqA_12[5] = 0xB2,     // BankA 0x3b
			},
			/* color */
			{
					.contrast[0] 		= 0x6e, .contrast[1] 		= 0x6b, .contrast[2] 		= 0x98, .contrast[3] 		= 0x66, .contrast[4] 		= 0x61, .contrast[5] 		= 0x65,
					.h_peaking[0] 		= 0x10, .h_peaking[1] 		= 0x10, .h_peaking[2] 		= 0x10, .h_peaking[3] 		= 0x00, .h_peaking[4] 		= 0x30, .h_peaking[5] 		= 0x20,
					.c_filter[0]		= 0x92, .c_filter[1] 		= 0xa2, .c_filter[2]	 	= 0xb2, .c_filter[3] 		= 0xb2, .c_filter[4] 		= 0xb2, .c_filter[5] 		= 0xb2,

					.hue[0] 			= 0x00, .hue[1] 			= 0x00, .hue[2] 			= 0x02, .hue[3] 			= 0x02, .hue[4] 			= 0x02, .hue[5] 			= 0x02,
					.u_gain[0] 			= 0x30, .u_gain[1] 			= 0x28, .u_gain[2] 			= 0x34, .u_gain[3] 			= 0x34, .u_gain[4] 			= 0x34, .u_gain[5] 			= 0x34,
					.v_gain[0] 			= 0x3a, .v_gain[1] 			= 0x38, .v_gain[2] 			= 0x40, .v_gain[3] 			= 0x40, .v_gain[4] 			= 0x40, .v_gain[5] 			= 0x40,
					.u_offset[0] 		= 0x02, .u_offset[1] 		= 0x00, .u_offset[2] 		= 0x00, .u_offset[3] 		= 0x00, .u_offset[4] 		= 0x00, .u_offset[5] 		= 0x00,
					.v_offset[0] 		= 0xf8, .v_offset[1] 		= 0xf8, .v_offset[2] 		= 0xf8, .v_offset[3] 		= 0xf8, .v_offset[4] 		= 0xf8, .v_offset[5] 		= 0xf8,

					.black_level[0] 	= 0x87, .black_level[1] 	= 0x87, .black_level[2] 	= 0x88, .black_level[3] 	= 0x8a, .black_level[4] 	= 0x8d, .black_level[5] 	= 0x8e,
					.acc_ref[0]			= 0x57, .acc_ref[1]			= 0x57, .acc_ref[2]			= 0x57, .acc_ref[3]			= 0x57, .acc_ref[4]			= 0x47, .acc_ref[5]			= 0x37,
					.cti_delay[0]		= 0x80, .cti_delay[1]		= 0x80, .cti_delay[2]		= 0x80, .cti_delay[3]		= 0x80, .cti_delay[4]		= 0xa0, .cti_delay[5]		= 0x80,
					.sub_saturation[0] 	= 0x80, .sub_saturation[1] 	= 0xa0, .sub_saturation[2] 	= 0xb0, .sub_saturation[3] 	= 0x9c, .sub_saturation[4] 	= 0x00, .sub_saturation[5] 	= 0xa0,

					.burst_dec_a[0] 	= 0x2a, .burst_dec_a[1] 	= 0x2a, .burst_dec_a[2] 	= 0x2a, .burst_dec_a[3] 	= 0x2a, .burst_dec_a[4] 	= 0x00, .burst_dec_a[5] 	= 0x2a,
					.burst_dec_b[0] 	= 0x00, .burst_dec_b[1] 	= 0x00, .burst_dec_b[2] 	= 0x00, .burst_dec_b[3] 	= 0x00, .burst_dec_b[4] 	= 0x00, .burst_dec_b[5] 	= 0x00,
					.burst_dec_c[0] 	= 0x30, .burst_dec_c[1] 	= 0x30, .burst_dec_c[2] 	= 0x30, .burst_dec_c[3] 	= 0x00, .burst_dec_c[4] 	= 0x00, .burst_dec_c[5] 	= 0x00,

					.c_option[0] 		= 0x80, .c_option[1] 		= 0xa0, .c_option[2] 		= 0xb0, .c_option[3] 		= 0xb0, .c_option[4] 		= 0xb0, .c_option[5] 		= 0xb0,

					.y_filter_b[0]		= 0x10, .y_filter_b[1]		= 0x10, .y_filter_b[2]		= 0x10, .y_filter_b[3]		= 0x10, .y_filter_b[4]		= 0x10, .y_filter_b[5]		= 0x10,
					.y_filter_b_sel[0]	= 0x1e,	.y_filter_b_sel[1]	= 0x1e,	.y_filter_b_sel[2]	= 0x1e, .y_filter_b_sel[3]	= 0x1e, .y_filter_b_sel[4]	= 0x1e, .y_filter_b_sel[5]	= 0x1e,
			},
			/* timing_a */
			{
				.h_delay_a[0] = 0x87, .h_delay_a[1] = 0x87, .h_delay_a[2] = 0x87, .h_delay_a[3] = 0x87, .h_delay_a[4] = 0x87, .h_delay_a[5] = 0x87,
				.h_delay_b[0] = 0x00, .h_delay_b[1] = 0x00, .h_delay_b[2] = 0x00, .h_delay_b[3] = 0x00, .h_delay_b[4] = 0x00, .h_delay_b[5] = 0x00,
				.h_delay_c[0] = 0x00, .h_delay_c[1] = 0x00, .h_delay_c[2] = 0x00, .h_delay_c[3] = 0x00, .h_delay_c[4] = 0x00, .h_delay_c[5] = 0x00,
				.y_delay[0]   = 0x15, .y_delay[1]   = 0x15, .y_delay[2]   = 0x15, .y_delay[3]   = 0x15, .y_delay[4]   = 0x15, .y_delay[5]   = 0x15,

			},
			/* clk */
			{
				.clk_adc[0] = 0x05, .clk_adc[1] = 0x05, .clk_adc[2] = 0x05, .clk_adc[3] = 0x05, .clk_adc[4] = 0x05, .clk_adc[5] = 0x05,
				.clk_dec[0] = 0x44, .clk_dec[1] = 0x44, .clk_dec[2] = 0x44, .clk_dec[3] = 0x44, .clk_dec[4] = 0x44, .clk_dec[5] = 0x44,
			},
			/* timing_b */
			{
		/*B9 0x96*/	.h_scaler1[0]  = 0x01, .h_scaler1[1]   = 0x01, .h_scaler1[2]   = 0x01, .h_scaler1[3]   = 0x01, .h_scaler1[4]   = 0x01, .h_scaler1[5]   = 0x01,
		/*B9 0x97*/	.h_scaler2[0]  = 0x00, .h_scaler2[1]   = 0x00, .h_scaler2[2]   = 0x00, .h_scaler2[3]   = 0x00, .h_scaler2[4]   = 0x00, .h_scaler2[5]   = 0x00,
		/*B9 0x98*/	.h_scaler3[0]  = 0x00, .h_scaler3[1]   = 0x00, .h_scaler3[2]   = 0x00, .h_scaler3[3]   = 0x00, .h_scaler3[4]   = 0x00, .h_scaler3[5]   = 0x00,
		/*B9 0x99*/	.h_scaler4[0]  = 0x00, .h_scaler4[1]   = 0x00, .h_scaler4[2]   = 0x00, .h_scaler4[3]   = 0x00, .h_scaler4[4]   = 0x00, .h_scaler4[5]   = 0x00,
		/*B9 0x9a*/	.h_scaler5[0]  = 0x00, .h_scaler5[1]   = 0x00, .h_scaler5[2]   = 0x00, .h_scaler5[3]   = 0x00, .h_scaler5[4]   = 0x00, .h_scaler5[5]   = 0x00,
		/*B9 0x9b*/	.h_scaler6[0]  = 0x00, .h_scaler6[1]   = 0x00, .h_scaler6[2]   = 0x00, .h_scaler6[3]   = 0x00, .h_scaler6[4]   = 0x00, .h_scaler6[5]   = 0x00,
		/*B9 0x9c*/	.h_scaler7[0]  = 0x00, .h_scaler7[1]   = 0x00, .h_scaler7[2]   = 0x00, .h_scaler7[3]   = 0x00, .h_scaler7[4]   = 0x00, .h_scaler7[5]   = 0x00,
		/*B9 0x9d*/	.h_scaler8[0]  = 0x00, .h_scaler8[1]   = 0x00, .h_scaler8[2]   = 0x00, .h_scaler8[3]   = 0x00, .h_scaler8[4]   = 0x00, .h_scaler8[5]   = 0x00,
		/*B9 0x9e*/	.h_scaler9[0]  = 0x00, .h_scaler9[1]   = 0x00, .h_scaler9[2]   = 0x00, .h_scaler9[3]   = 0x00, .h_scaler9[4]   = 0x00, .h_scaler9[5]   = 0x00,


		/*B9 0x40*/	.pn_auto[0]    	= 0x00, .pn_auto[1]		= 0x00, .pn_auto[2]    	= 0x00, .pn_auto[3]    	= 0x00, .pn_auto[4]    	= 0x00, .pn_auto[5]    	= 0x00,

		/*B5 0x90*/	.comb_mode[0]   = 0x05, .comb_mode[1]	= 0x05, .comb_mode[2]   = 0x05, .comb_mode[3]   = 0x05, .comb_mode[4]  	= 0x05, .comb_mode[5]   = 0x05,
		/*B9 0xb9*/	.h_pll_op_a[0]  = 0x72, .h_pll_op_a[1]  = 0x72, .h_pll_op_a[2]  = 0x72, .h_pll_op_a[3]  = 0x72, .h_pll_op_a[4]  = 0x72, .h_pll_op_a[5]  = 0x72,
		/*B9 0x57*/	.mem_path[0]	= 0x10, .mem_path[1]	= 0x10, .mem_path[2]	= 0x10, .mem_path[3]	= 0x10, .mem_path[4]	= 0x10, .mem_path[5]	= 0x10,
					.fsc_lock_speed[0] = 0xdc, .fsc_lock_speed[1] = 0xdc, .fsc_lock_speed[2] = 0xdc, .fsc_lock_speed[3] = 0xdc, .fsc_lock_speed[4] = 0xdc, .fsc_lock_speed[5] = 0xdc,

		/*B0 0x81*/	.format_set1[0] = 0x0e, .format_set1[1] = 0x0e, .format_set1[2] = 0x0e, .format_set1[3] = 0x0e, .format_set1[4] = 0x0e, .format_set1[5] = 0x0e,
		/*B0 0x85*/	.format_set2[0] = 0x03, .format_set2[1] = 0x03, .format_set2[2] = 0x03, .format_set2[3] = 0x03, .format_set2[4] = 0x03, .format_set2[5] = 0x03,

		/*B0 0x64*/ .v_delay[0]     = 0x80, .v_delay[1]     = 0x80, .v_delay[2]     = 0x80, .v_delay[3]     = 0x80, .v_delay[4]     = 0x80, .v_delay[5]     = 0x80,
			},
		},


	[ TVI_3M_18P ] = /* o */
		{
			/* base */
			{
				.eq_bypass[0] 	= 0x22, .eq_bypass[1] 	= 0x22, .eq_bypass[2] 	= 0x22, .eq_bypass[3] 	= 0x22, .eq_bypass[4] 	= 0x22, .eq_bypass[5] 	= 0x22,    // Bank5 0x30
				.eq_band_sel[0] = 0x77, .eq_band_sel[1] = 0x77, .eq_band_sel[2] = 0x77, .eq_band_sel[3] = 0x67, .eq_band_sel[4] = 0x47, .eq_band_sel[5] = 0x47,    // BankA 0x31
				.eq_gain_sel[0] = 0x78, .eq_gain_sel[1] = 0x7a, .eq_gain_sel[2] = 0x7f, .eq_gain_sel[3] = 0x7e, .eq_gain_sel[4] = 0x7e, .eq_gain_sel[5] = 0x7f,    // BankA 0x32
				.deq_a_on[0] 	= 0x00, .deq_a_on[1] 	= 0x01, .deq_a_on[2] 	= 0x01, .deq_a_on[3] 	= 0x01, .deq_a_on[4] 	= 0x01, .deq_a_on[5] 	= 0x01,    // BankA 0x33
				.deq_a_sel[0] 	= 0x00, .deq_a_sel[1] 	= 0x92, .deq_a_sel[2] 	= 0x93, .deq_a_sel[3] 	= 0x94, .deq_a_sel[4] 	= 0x92, .deq_a_sel[5] 	= 0x92,    // BankA 0x34
				.deq_b_sel[0] 	= 0x00, .deq_b_sel[1] 	= 0x00, .deq_b_sel[2] 	= 0x00, .deq_b_sel[3] 	= 0x20, .deq_b_sel[4] 	= 0x00, .deq_b_sel[5] 	= 0x00,    // BankA 0x35
			},
			/* coeff */
			{
				.deqA_01[0] = 0xAC, .deqA_01[1] = 0xAC, .deqA_01[2] = 0xAC, .deqA_01[3] = 0xAC, .deqA_01[4] = 0xAC, .deqA_01[5] = 0xAC,		// BankA 0x30
				.deqA_02[0] = 0x78, .deqA_02[1] = 0x78, .deqA_02[2] = 0x78, .deqA_02[3] = 0x78, .deqA_02[4] = 0x78, .deqA_02[5] = 0x78,		// BankA 0x31
				.deqA_03[0] = 0x17, .deqA_03[1] = 0x17, .deqA_03[2] = 0x17, .deqA_03[3] = 0x17, .deqA_03[4] = 0x17, .deqA_03[5] = 0x17,		// BankA 0x32
				.deqA_04[0] = 0xC1, .deqA_04[1] = 0xC1, .deqA_04[2] = 0xC1, .deqA_04[3] = 0xC1, .deqA_04[4] = 0xC1, .deqA_04[5] = 0xC1,     // BankA 0x33
				.deqA_05[0] = 0x40, .deqA_05[1] = 0x40, .deqA_05[2] = 0x40, .deqA_05[3] = 0x40, .deqA_05[4] = 0x40, .deqA_05[5] = 0x40,     // BankA 0x34
				.deqA_06[0] = 0x00, .deqA_06[1] = 0x00, .deqA_06[2] = 0x00, .deqA_06[3] = 0x00, .deqA_06[4] = 0x00, .deqA_06[5] = 0x00,     // BankA 0x35
				.deqA_07[0] = 0xC3, .deqA_07[1] = 0xC3, .deqA_07[2] = 0xC3, .deqA_07[3] = 0xC3, .deqA_07[4] = 0xC3, .deqA_07[5] = 0xC3,     // BankA 0x36
				.deqA_08[0] = 0x0A, .deqA_08[1] = 0x0A, .deqA_08[2] = 0x0A, .deqA_08[3] = 0x0A, .deqA_08[4] = 0x0A, .deqA_08[5] = 0x0A,     // BankA 0x37
				.deqA_09[0] = 0x00, .deqA_09[1] = 0x00, .deqA_09[2] = 0x00, .deqA_09[3] = 0x00, .deqA_09[4] = 0x00, .deqA_09[5] = 0x00,     // BankA 0x38
				.deqA_10[0] = 0x02, .deqA_10[1] = 0x02, .deqA_10[2] = 0x02, .deqA_10[3] = 0x02, .deqA_10[4] = 0x02, .deqA_10[5] = 0x02,     // BankA 0x39
				.deqA_11[0] = 0x00, .deqA_11[1] = 0x00, .deqA_11[2] = 0x00, .deqA_11[3] = 0x00, .deqA_11[4] = 0x00, .deqA_11[5] = 0x00,     // BankA 0x3a
				.deqA_12[0] = 0xB2, .deqA_12[1] = 0xB2, .deqA_12[2] = 0xB2, .deqA_12[3] = 0xB2, .deqA_12[4] = 0xB2, .deqA_12[5] = 0xB2,     // BankA 0x3b
			},
			/* color */
			{
				.contrast[0] 		= 0x6e, .contrast[1] 		= 0x6b, .contrast[2] 		= 0x98, .contrast[3] 		= 0x66, .contrast[4] 		= 0x61, .contrast[5] 		= 0x65,
				.h_peaking[0] 		= 0x10, .h_peaking[1] 		= 0x10, .h_peaking[2] 		= 0x10, .h_peaking[3] 		= 0x00, .h_peaking[4] 		= 0x30, .h_peaking[5] 		= 0x20,
				.c_filter[0]		= 0x81, .c_filter[1] 		= 0x82, .c_filter[2]	 	= 0x92, .c_filter[3] 		= 0x92, .c_filter[4] 		= 0xc4, .c_filter[5] 		= 0xc4,

				.hue[0] 			= 0x00, .hue[1] 			= 0x00, .hue[2] 			= 0x02, .hue[3] 			= 0x02, .hue[4] 			= 0x02, .hue[5] 			= 0x02,
				.u_gain[0] 			= 0x30, .u_gain[1] 			= 0x28, .u_gain[2] 			= 0x34, .u_gain[3] 			= 0x34, .u_gain[4] 			= 0x34, .u_gain[5] 			= 0x34,
				.v_gain[0] 			= 0x3a, .v_gain[1] 			= 0x38, .v_gain[2] 			= 0x40, .v_gain[3] 			= 0x40, .v_gain[4] 			= 0x40, .v_gain[5] 			= 0x40,
				.u_offset[0] 		= 0x02, .u_offset[1] 		= 0x00, .u_offset[2] 		= 0x00, .u_offset[3] 		= 0x00, .u_offset[4] 		= 0x00, .u_offset[5] 		= 0x00,
				.v_offset[0] 		= 0xf8, .v_offset[1] 		= 0xf8, .v_offset[2] 		= 0xf8, .v_offset[3] 		= 0xf8, .v_offset[4] 		= 0xf8, .v_offset[5] 		= 0xf8,

				.black_level[0] 	= 0x87, .black_level[1] 	= 0x87, .black_level[2] 	= 0x88, .black_level[3] 	= 0x8a, .black_level[4] 	= 0x8d, .black_level[5] 	= 0x8e,
				.acc_ref[0]			= 0x57, .acc_ref[1]			= 0x57, .acc_ref[2]			= 0x57, .acc_ref[3]			= 0x57, .acc_ref[4]			= 0x47, .acc_ref[5]			= 0x37,
				.cti_delay[0]		= 0x80, .cti_delay[1]		= 0x80, .cti_delay[2]		= 0x80, .cti_delay[3]		= 0x80, .cti_delay[4]		= 0xa0, .cti_delay[5]		= 0x80,
				.sub_saturation[0] 	= 0x80, .sub_saturation[1] 	= 0xc0, .sub_saturation[2] 	= 0x80, .sub_saturation[3] 	= 0x9c, .sub_saturation[4] 	= 0x00, .sub_saturation[5] 	= 0xa0,

				.burst_dec_a[0] 	= 0x2a, .burst_dec_a[1] 	= 0x2a, .burst_dec_a[2] 	= 0x2a, .burst_dec_a[3] 	= 0x2a, .burst_dec_a[4] 	= 0x00, .burst_dec_a[5] 	= 0x2a,
				.burst_dec_b[0] 	= 0x00, .burst_dec_b[1] 	= 0x00, .burst_dec_b[2] 	= 0x00, .burst_dec_b[3] 	= 0x00, .burst_dec_b[4] 	= 0x00, .burst_dec_b[5] 	= 0x00,
				.burst_dec_c[0] 	= 0x30, .burst_dec_c[1] 	= 0x30, .burst_dec_c[2] 	= 0x30, .burst_dec_c[3] 	= 0x00, .burst_dec_c[4] 	= 0x00, .burst_dec_c[5] 	= 0x00,

				.c_option[0] 		= 0x80, .c_option[1] 		= 0x80, .c_option[2] 		= 0x80, .c_option[3] 		= 0x90, .c_option[4] 		= 0xa0, .c_option[5] 		= 0xa0,

				.y_filter_b[0]		= 0x10, .y_filter_b[1]		= 0x10, .y_filter_b[2]		= 0x10, .y_filter_b[3]		= 0x10, .y_filter_b[4]		= 0x10, .y_filter_b[5]		= 0x10,
				.y_filter_b_sel[0]	= 0x1e,	.y_filter_b_sel[1]	= 0x1e,	.y_filter_b_sel[2]	= 0x1e, .y_filter_b_sel[3]	= 0x1e, .y_filter_b_sel[4]	= 0x1e, .y_filter_b_sel[5]	= 0x1e,
			},
			/* timing_a */
			{
				.h_delay_a[0] = 0x80, .h_delay_a[1] = 0x80, .h_delay_a[2] = 0x7e, .h_delay_a[3] = 0x7e, .h_delay_a[4] = 0x7e, .h_delay_a[5] = 0x7e,
				.h_delay_b[0] = 0x10, .h_delay_b[1] = 0x10, .h_delay_b[2] = 0x10, .h_delay_b[3] = 0x10, .h_delay_b[4] = 0x10, .h_delay_b[5] = 0x10,
				.h_delay_c[0] = 0x00, .h_delay_c[1] = 0x02, .h_delay_c[2] = 0x02, .h_delay_c[3] = 0x02, .h_delay_c[4] = 0x02, .h_delay_c[5] = 0x02,
				.y_delay[0]   = 0x00, .y_delay[1]   = 0x00, .y_delay[2]   = 0x00, .y_delay[3]   = 0x00, .y_delay[4]   = 0x00, .y_delay[5] = 0x00,

			},
			/* clk */
			{
				.clk_adc[0] = 0x05, .clk_adc[1] = 0x05, .clk_adc[2] = 0x05, .clk_adc[3] = 0x05, .clk_adc[4] = 0x05, .clk_adc[5] = 0x05,
				.clk_dec[0] = 0x44, .clk_dec[1] = 0x44, .clk_dec[2] = 0x44, .clk_dec[3] = 0x44, .clk_dec[4] = 0x44, .clk_dec[5] = 0x44,
			},
			/* timing_b */
			{
	/*B9 0x96*/	.h_scaler1[0]  = 0x01, .h_scaler1[1]   = 0x01, .h_scaler1[2]   = 0x01, .h_scaler1[3]   = 0x01, .h_scaler1[4]   = 0x01, .h_scaler1[5]   = 0x01,
	/*B9 0x97*/	.h_scaler2[0]  = 0x00, .h_scaler2[1]   = 0x00, .h_scaler2[2]   = 0x00, .h_scaler2[3]   = 0x00, .h_scaler2[4]   = 0x00, .h_scaler2[5]   = 0x00,
	/*B9 0x98*/	.h_scaler3[0]  = 0x00, .h_scaler3[1]   = 0x00, .h_scaler3[2]   = 0x00, .h_scaler3[3]   = 0x00, .h_scaler3[4]   = 0x00, .h_scaler3[5]   = 0x00,
	/*B9 0x99*/	.h_scaler4[0]  = 0x00, .h_scaler4[1]   = 0x00, .h_scaler4[2]   = 0x00, .h_scaler4[3]   = 0x00, .h_scaler4[4]   = 0x00, .h_scaler4[5]   = 0x00,
	/*B9 0x9a*/	.h_scaler5[0]  = 0x00, .h_scaler5[1]   = 0x00, .h_scaler5[2]   = 0x00, .h_scaler5[3]   = 0x00, .h_scaler5[4]   = 0x00, .h_scaler5[5]   = 0x00,
	/*B9 0x9b*/	.h_scaler6[0]  = 0x00, .h_scaler6[1]   = 0x00, .h_scaler6[2]   = 0x00, .h_scaler6[3]   = 0x00, .h_scaler6[4]   = 0x00, .h_scaler6[5]   = 0x00,
	/*B9 0x9c*/	.h_scaler7[0]  = 0x00, .h_scaler7[1]   = 0x00, .h_scaler7[2]   = 0x00, .h_scaler7[3]   = 0x00, .h_scaler7[4]   = 0x00, .h_scaler7[5]   = 0x00,
	/*B9 0x9d*/	.h_scaler8[0]  = 0x00, .h_scaler8[1]   = 0x00, .h_scaler8[2]   = 0x00, .h_scaler8[3]   = 0x00, .h_scaler8[4]   = 0x00, .h_scaler8[5]   = 0x00,
	/*B9 0x9e*/	.h_scaler9[0]  = 0x00, .h_scaler9[1]   = 0x00, .h_scaler9[2]   = 0x00, .h_scaler9[3]   = 0x00, .h_scaler9[4]   = 0x00, .h_scaler9[5]   = 0x00,


	/*B9 0x40*/	.pn_auto[0]    	= 0x00, .pn_auto[1]		= 0x00, .pn_auto[2]    	= 0x00, .pn_auto[3]    	= 0x00, .pn_auto[4]    	= 0x00, .pn_auto[5]    	= 0x00,

	/*B5 0x90*/	.comb_mode[0]   = 0x05, .comb_mode[1]	= 0x05, .comb_mode[2]   = 0x05, .comb_mode[3]   = 0x05, .comb_mode[4]  	= 0x05, .comb_mode[5]   = 0x05,
	/*B9 0xb9*/	.h_pll_op_a[0]  = 0x72, .h_pll_op_a[1]  = 0x72, .h_pll_op_a[2]  = 0x72, .h_pll_op_a[3]  = 0x72, .h_pll_op_a[4]  = 0x72, .h_pll_op_a[5]  = 0x72,
	/*B9 0x57*/	.mem_path[0]	= 0x10, .mem_path[1]	= 0x10, .mem_path[2]	= 0x10, .mem_path[3]	= 0x10, .mem_path[4]	= 0x10, .mem_path[5]	= 0x10,
				.fsc_lock_speed[0] = 0xdc, .fsc_lock_speed[1] = 0xdc, .fsc_lock_speed[2] = 0xdc, .fsc_lock_speed[3] = 0xdc, .fsc_lock_speed[4] = 0xdc, .fsc_lock_speed[5] = 0xdc,

	/*B0 0x81*/	.format_set1[0] = 0x08, .format_set1[1] = 0x08, .format_set1[2] = 0x08, .format_set1[3] = 0x08, .format_set1[4] = 0x08, .format_set1[5] = 0x08,
	/*B0 0x85*/	.format_set2[0] = 0x03, .format_set2[1] = 0x03, .format_set2[2] = 0x03, .format_set2[3] = 0x03, .format_set2[4] = 0x03, .format_set2[5] = 0x03,

	/*B0 0x64*/ .v_delay[0]     = 0x80, .v_delay[1]     = 0x80, .v_delay[2]     = 0x80, .v_delay[3]     = 0x80, .v_delay[4]     = 0x80, .v_delay[5]     = 0x80,
			},
		},
	[ TVI_4M_15P ] = /* o */
		{
			/* base */
			{
				.eq_bypass[0] 	= 0x22, .eq_bypass[1] 	= 0x22, .eq_bypass[2] 	= 0x22, .eq_bypass[3] 	= 0x22, .eq_bypass[4] 	= 0x22, .eq_bypass[5] 	= 0x22,    // Bank5 0x30
				.eq_band_sel[0] = 0x77, .eq_band_sel[1] = 0x77, .eq_band_sel[2] = 0x77, .eq_band_sel[3] = 0x67, .eq_band_sel[4] = 0x47, .eq_band_sel[5] = 0x47,    // BankA 0x31
				.eq_gain_sel[0] = 0x78, .eq_gain_sel[1] = 0x7a, .eq_gain_sel[2] = 0x7f, .eq_gain_sel[3] = 0x7e, .eq_gain_sel[4] = 0x7e, .eq_gain_sel[5] = 0x7f,    // BankA 0x32
				.deq_a_on[0] 	= 0x00, .deq_a_on[1] 	= 0x01, .deq_a_on[2] 	= 0x01, .deq_a_on[3] 	= 0x01, .deq_a_on[4] 	= 0x01, .deq_a_on[5] 	= 0x01,    // BankA 0x33
				.deq_a_sel[0] 	= 0x00, .deq_a_sel[1] 	= 0x92, .deq_a_sel[2] 	= 0x93, .deq_a_sel[3] 	= 0x94, .deq_a_sel[4] 	= 0x92, .deq_a_sel[5] 	= 0x92,    // BankA 0x34
				.deq_b_sel[0] 	= 0x00, .deq_b_sel[1] 	= 0x00, .deq_b_sel[2] 	= 0x00, .deq_b_sel[3] 	= 0x20, .deq_b_sel[4] 	= 0x00, .deq_b_sel[5] 	= 0x00,    // BankA 0x35
			},
			/* coeff */
			{
				.deqA_01[0] = 0xAC, .deqA_01[1] = 0xAC, .deqA_01[2] = 0xAC, .deqA_01[3] = 0xAC, .deqA_01[4] = 0xAC, .deqA_01[5] = 0xAC,		// BankA 0x30
				.deqA_02[0] = 0x78, .deqA_02[1] = 0x78, .deqA_02[2] = 0x78, .deqA_02[3] = 0x78, .deqA_02[4] = 0x78, .deqA_02[5] = 0x78,		// BankA 0x31
				.deqA_03[0] = 0x17, .deqA_03[1] = 0x17, .deqA_03[2] = 0x17, .deqA_03[3] = 0x17, .deqA_03[4] = 0x17, .deqA_03[5] = 0x17,		// BankA 0x32
				.deqA_04[0] = 0xC1, .deqA_04[1] = 0xC1, .deqA_04[2] = 0xC1, .deqA_04[3] = 0xC1, .deqA_04[4] = 0xC1, .deqA_04[5] = 0xC1,     // BankA 0x33
				.deqA_05[0] = 0x40, .deqA_05[1] = 0x40, .deqA_05[2] = 0x40, .deqA_05[3] = 0x40, .deqA_05[4] = 0x40, .deqA_05[5] = 0x40,     // BankA 0x34
				.deqA_06[0] = 0x00, .deqA_06[1] = 0x00, .deqA_06[2] = 0x00, .deqA_06[3] = 0x00, .deqA_06[4] = 0x00, .deqA_06[5] = 0x00,     // BankA 0x35
				.deqA_07[0] = 0xC3, .deqA_07[1] = 0xC3, .deqA_07[2] = 0xC3, .deqA_07[3] = 0xC3, .deqA_07[4] = 0xC3, .deqA_07[5] = 0xC3,     // BankA 0x36
				.deqA_08[0] = 0x0A, .deqA_08[1] = 0x0A, .deqA_08[2] = 0x0A, .deqA_08[3] = 0x0A, .deqA_08[4] = 0x0A, .deqA_08[5] = 0x0A,     // BankA 0x37
				.deqA_09[0] = 0x00, .deqA_09[1] = 0x00, .deqA_09[2] = 0x00, .deqA_09[3] = 0x00, .deqA_09[4] = 0x00, .deqA_09[5] = 0x00,     // BankA 0x38
				.deqA_10[0] = 0x02, .deqA_10[1] = 0x02, .deqA_10[2] = 0x02, .deqA_10[3] = 0x02, .deqA_10[4] = 0x02, .deqA_10[5] = 0x02,     // BankA 0x39
				.deqA_11[0] = 0x00, .deqA_11[1] = 0x00, .deqA_11[2] = 0x00, .deqA_11[3] = 0x00, .deqA_11[4] = 0x00, .deqA_11[5] = 0x00,     // BankA 0x3a
				.deqA_12[0] = 0xB2, .deqA_12[1] = 0xB2, .deqA_12[2] = 0xB2, .deqA_12[3] = 0xB2, .deqA_12[4] = 0xB2, .deqA_12[5] = 0xB2,     // BankA 0x3b
			},
			/* color */
			{
				.contrast[0] 		= 0x6e, .contrast[1] 		= 0x6b, .contrast[2] 		= 0x98, .contrast[3] 		= 0x66, .contrast[4] 		= 0x61, .contrast[5] 		= 0x65,
				.h_peaking[0] 		= 0x10, .h_peaking[1] 		= 0x10, .h_peaking[2] 		= 0x10, .h_peaking[3] 		= 0x00, .h_peaking[4] 		= 0x30, .h_peaking[5] 		= 0x20,
				.c_filter[0]		= 0x81, .c_filter[1] 		= 0x82, .c_filter[2]	 	= 0x92, .c_filter[3] 		= 0x92, .c_filter[4] 		= 0xc4, .c_filter[5] 		= 0xc4,

				.hue[0] 			= 0x00, .hue[1] 			= 0x00, .hue[2] 			= 0x02, .hue[3] 			= 0x02, .hue[4] 			= 0x02, .hue[5] 			= 0x02,
				.u_gain[0] 			= 0x30, .u_gain[1] 			= 0x28, .u_gain[2] 			= 0x34, .u_gain[3] 			= 0x34, .u_gain[4] 			= 0x34, .u_gain[5] 			= 0x34,
				.v_gain[0] 			= 0x3a, .v_gain[1] 			= 0x38, .v_gain[2] 			= 0x40, .v_gain[3] 			= 0x40, .v_gain[4] 			= 0x40, .v_gain[5] 			= 0x40,
				.u_offset[0] 		= 0x02, .u_offset[1] 		= 0x00, .u_offset[2] 		= 0x00, .u_offset[3] 		= 0x00, .u_offset[4] 		= 0x00, .u_offset[5] 		= 0x00,
				.v_offset[0] 		= 0xf8, .v_offset[1] 		= 0xf8, .v_offset[2] 		= 0xf8, .v_offset[3] 		= 0xf8, .v_offset[4] 		= 0xf8, .v_offset[5] 		= 0xf8,

				.black_level[0] 	= 0x87, .black_level[1] 	= 0x87, .black_level[2] 	= 0x88, .black_level[3] 	= 0x8a, .black_level[4] 	= 0x8d, .black_level[5] 	= 0x8e,
				.acc_ref[0]			= 0x57, .acc_ref[1]			= 0x57, .acc_ref[2]			= 0x57, .acc_ref[3]			= 0x57, .acc_ref[4]			= 0x47, .acc_ref[5]			= 0x37,
				.cti_delay[0]		= 0x80, .cti_delay[1]		= 0x80, .cti_delay[2]		= 0x80, .cti_delay[3]		= 0x80, .cti_delay[4]		= 0xa0, .cti_delay[5]		= 0x80,
				.sub_saturation[0] 	= 0x80, .sub_saturation[1] 	= 0xc0, .sub_saturation[2] 	= 0x80, .sub_saturation[3] 	= 0x9c, .sub_saturation[4] 	= 0x00, .sub_saturation[5] 	= 0xa0,

				.burst_dec_a[0] 	= 0x2a, .burst_dec_a[1] 	= 0x2a, .burst_dec_a[2] 	= 0x2a, .burst_dec_a[3] 	= 0x2a, .burst_dec_a[4] 	= 0x00, .burst_dec_a[5] 	= 0x2a,
				.burst_dec_b[0] 	= 0x00, .burst_dec_b[1] 	= 0x00, .burst_dec_b[2] 	= 0x00, .burst_dec_b[3] 	= 0x00, .burst_dec_b[4] 	= 0x00, .burst_dec_b[5] 	= 0x00,
				.burst_dec_c[0] 	= 0x30, .burst_dec_c[1] 	= 0x30, .burst_dec_c[2] 	= 0x30, .burst_dec_c[3] 	= 0x00, .burst_dec_c[4] 	= 0x00, .burst_dec_c[5] 	= 0x00,

				.c_option[0] 		= 0x80, .c_option[1] 		= 0x80, .c_option[2] 		= 0x80, .c_option[3] 		= 0x90, .c_option[4] 		= 0xa0, .c_option[5] 		= 0xa0,

				.y_filter_b[0]		= 0x10, .y_filter_b[1]		= 0x10, .y_filter_b[2]		= 0x10, .y_filter_b[3]		= 0x10, .y_filter_b[4]		= 0x10, .y_filter_b[5]		= 0x10,
				.y_filter_b_sel[0]	= 0x1e,	.y_filter_b_sel[1]	= 0x1e,	.y_filter_b_sel[2]	= 0x1e, .y_filter_b_sel[3]	= 0x1e, .y_filter_b_sel[4]	= 0x1e, .y_filter_b_sel[5]	= 0x1e,
			},
			/* timing_a */
			{
				.h_delay_a[0] = 0x80, .h_delay_a[1] = 0x80, .h_delay_a[2] = 0x7e, .h_delay_a[3] = 0x7e, .h_delay_a[4] = 0x7e, .h_delay_a[5] = 0x7e,
				.h_delay_b[0] = 0x10, .h_delay_b[1] = 0x10, .h_delay_b[2] = 0x10, .h_delay_b[3] = 0x10, .h_delay_b[4] = 0x10, .h_delay_b[5] = 0x10,
				.h_delay_c[0] = 0x00, .h_delay_c[1] = 0x02, .h_delay_c[2] = 0x02, .h_delay_c[3] = 0x02, .h_delay_c[4] = 0x02, .h_delay_c[5] = 0x02,
				.y_delay[0]   = 0x00, .y_delay[1]   = 0x00, .y_delay[2]   = 0x00, .y_delay[3]   = 0x00, .y_delay[4]   = 0x00, .y_delay[5] = 0x00,

			},
			/* clk */
			{
				.clk_adc[0] = 0x05, .clk_adc[1] = 0x05, .clk_adc[2] = 0x05, .clk_adc[3] = 0x05, .clk_adc[4] = 0x05, .clk_adc[5] = 0x05,
				.clk_dec[0] = 0x44, .clk_dec[1] = 0x44, .clk_dec[2] = 0x44, .clk_dec[3] = 0x44, .clk_dec[4] = 0x44, .clk_dec[5] = 0x44,
			},
			/* timing_b */
			{
	/*B9 0x96*/	.h_scaler1[0]  = 0x01, .h_scaler1[1]   = 0x01, .h_scaler1[2]   = 0x01, .h_scaler1[3]   = 0x01, .h_scaler1[4]   = 0x01, .h_scaler1[5]   = 0x01,
	/*B9 0x97*/	.h_scaler2[0]  = 0x00, .h_scaler2[1]   = 0x00, .h_scaler2[2]   = 0x00, .h_scaler2[3]   = 0x00, .h_scaler2[4]   = 0x00, .h_scaler2[5]   = 0x00,
	/*B9 0x98*/	.h_scaler3[0]  = 0x00, .h_scaler3[1]   = 0x00, .h_scaler3[2]   = 0x00, .h_scaler3[3]   = 0x00, .h_scaler3[4]   = 0x00, .h_scaler3[5]   = 0x00,
	/*B9 0x99*/	.h_scaler4[0]  = 0x00, .h_scaler4[1]   = 0x00, .h_scaler4[2]   = 0x00, .h_scaler4[3]   = 0x00, .h_scaler4[4]   = 0x00, .h_scaler4[5]   = 0x00,
	/*B9 0x9a*/	.h_scaler5[0]  = 0x00, .h_scaler5[1]   = 0x00, .h_scaler5[2]   = 0x00, .h_scaler5[3]   = 0x00, .h_scaler5[4]   = 0x00, .h_scaler5[5]   = 0x00,
	/*B9 0x9b*/	.h_scaler6[0]  = 0x00, .h_scaler6[1]   = 0x00, .h_scaler6[2]   = 0x00, .h_scaler6[3]   = 0x00, .h_scaler6[4]   = 0x00, .h_scaler6[5]   = 0x00,
	/*B9 0x9c*/	.h_scaler7[0]  = 0x00, .h_scaler7[1]   = 0x00, .h_scaler7[2]   = 0x00, .h_scaler7[3]   = 0x00, .h_scaler7[4]   = 0x00, .h_scaler7[5]   = 0x00,
	/*B9 0x9d*/	.h_scaler8[0]  = 0x00, .h_scaler8[1]   = 0x00, .h_scaler8[2]   = 0x00, .h_scaler8[3]   = 0x00, .h_scaler8[4]   = 0x00, .h_scaler8[5]   = 0x00,
	/*B9 0x9e*/	.h_scaler9[0]  = 0x00, .h_scaler9[1]   = 0x00, .h_scaler9[2]   = 0x00, .h_scaler9[3]   = 0x00, .h_scaler9[4]   = 0x00, .h_scaler9[5]   = 0x00,


	/*B9 0x40*/	.pn_auto[0]    	= 0x00, .pn_auto[1]		= 0x00, .pn_auto[2]    	= 0x00, .pn_auto[3]    	= 0x00, .pn_auto[4]    	= 0x00, .pn_auto[5]    	= 0x00,

	/*B5 0x90*/	.comb_mode[0]   = 0x05, .comb_mode[1]	= 0x05, .comb_mode[2]   = 0x05, .comb_mode[3]   = 0x05, .comb_mode[4]  	= 0x05, .comb_mode[5]   = 0x05,
	/*B9 0xb9*/	.h_pll_op_a[0]  = 0x72, .h_pll_op_a[1]  = 0x72, .h_pll_op_a[2]  = 0x72, .h_pll_op_a[3]  = 0x72, .h_pll_op_a[4]  = 0x72, .h_pll_op_a[5]  = 0x72,
	/*B9 0x57*/	.mem_path[0]	= 0x10, .mem_path[1]	= 0x10, .mem_path[2]	= 0x10, .mem_path[3]	= 0x10, .mem_path[4]	= 0x10, .mem_path[5]	= 0x10,
				.fsc_lock_speed[0] = 0xdc, .fsc_lock_speed[1] = 0xdc, .fsc_lock_speed[2] = 0xdc, .fsc_lock_speed[3] = 0xdc, .fsc_lock_speed[4] = 0xdc, .fsc_lock_speed[5] = 0xdc,

	/*B0 0x81*/	.format_set1[0] = 0x08, .format_set1[1] = 0x08, .format_set1[2] = 0x08, .format_set1[3] = 0x08, .format_set1[4] = 0x08, .format_set1[5] = 0x08,
	/*B0 0x85*/	.format_set2[0] = 0x03, .format_set2[1] = 0x03, .format_set2[2] = 0x03, .format_set2[3] = 0x03, .format_set2[4] = 0x03, .format_set2[5] = 0x03,

	/*B0 0x64*/ .v_delay[0]     = 0x80, .v_delay[1]     = 0x80, .v_delay[2]     = 0x80, .v_delay[3]     = 0x80, .v_delay[4]     = 0x80, .v_delay[5]     = 0x80,
			},
		},



	[ TVI_5M_12_5P ] = /* o */
	{
		/* base */
		{
			.eq_bypass[0] 	= 0x22, .eq_bypass[1] 	= 0x22, .eq_bypass[2] 	= 0x22, .eq_bypass[3] 	= 0x22, .eq_bypass[4] 	= 0x22, .eq_bypass[5] 	= 0x22,    // Bank5 0x30
			.eq_band_sel[0] = 0x77, .eq_band_sel[1] = 0x77, .eq_band_sel[2] = 0x77, .eq_band_sel[3] = 0x67, .eq_band_sel[4] = 0x47, .eq_band_sel[5] = 0x47,    // BankA 0x31
			.eq_gain_sel[0] = 0x78, .eq_gain_sel[1] = 0x7a, .eq_gain_sel[2] = 0x7f, .eq_gain_sel[3] = 0x7e, .eq_gain_sel[4] = 0x7e, .eq_gain_sel[5] = 0x7f,    // BankA 0x32
			.deq_a_on[0] 	= 0x00, .deq_a_on[1] 	= 0x01, .deq_a_on[2] 	= 0x01, .deq_a_on[3] 	= 0x01, .deq_a_on[4] 	= 0x01, .deq_a_on[5] 	= 0x01,    // BankA 0x33
			.deq_a_sel[0] 	= 0x00, .deq_a_sel[1] 	= 0x92, .deq_a_sel[2] 	= 0x93, .deq_a_sel[3] 	= 0x94, .deq_a_sel[4] 	= 0x92, .deq_a_sel[5] 	= 0x92,    // BankA 0x34
			.deq_b_sel[0] 	= 0x00, .deq_b_sel[1] 	= 0x00, .deq_b_sel[2] 	= 0x00, .deq_b_sel[3] 	= 0x20, .deq_b_sel[4] 	= 0x00, .deq_b_sel[5] 	= 0x00,    // BankA 0x35
		},
		/* coeff */
		{
			.deqA_01[0] = 0xAC, .deqA_01[1] = 0xAC, .deqA_01[2] = 0xAC, .deqA_01[3] = 0xAC, .deqA_01[4] = 0xAC, .deqA_01[5] = 0xAC,		// BankA 0x30
			.deqA_02[0] = 0x78, .deqA_02[1] = 0x78, .deqA_02[2] = 0x78, .deqA_02[3] = 0x78, .deqA_02[4] = 0x78, .deqA_02[5] = 0x78,		// BankA 0x31
			.deqA_03[0] = 0x17, .deqA_03[1] = 0x17, .deqA_03[2] = 0x17, .deqA_03[3] = 0x17, .deqA_03[4] = 0x17, .deqA_03[5] = 0x17,		// BankA 0x32
			.deqA_04[0] = 0xC1, .deqA_04[1] = 0xC1, .deqA_04[2] = 0xC1, .deqA_04[3] = 0xC1, .deqA_04[4] = 0xC1, .deqA_04[5] = 0xC1,     // BankA 0x33
			.deqA_05[0] = 0x40, .deqA_05[1] = 0x40, .deqA_05[2] = 0x40, .deqA_05[3] = 0x40, .deqA_05[4] = 0x40, .deqA_05[5] = 0x40,     // BankA 0x34
			.deqA_06[0] = 0x00, .deqA_06[1] = 0x00, .deqA_06[2] = 0x00, .deqA_06[3] = 0x00, .deqA_06[4] = 0x00, .deqA_06[5] = 0x00,     // BankA 0x35
			.deqA_07[0] = 0xC3, .deqA_07[1] = 0xC3, .deqA_07[2] = 0xC3, .deqA_07[3] = 0xC3, .deqA_07[4] = 0xC3, .deqA_07[5] = 0xC3,     // BankA 0x36
			.deqA_08[0] = 0x0A, .deqA_08[1] = 0x0A, .deqA_08[2] = 0x0A, .deqA_08[3] = 0x0A, .deqA_08[4] = 0x0A, .deqA_08[5] = 0x0A,     // BankA 0x37
			.deqA_09[0] = 0x00, .deqA_09[1] = 0x00, .deqA_09[2] = 0x00, .deqA_09[3] = 0x00, .deqA_09[4] = 0x00, .deqA_09[5] = 0x00,     // BankA 0x38
			.deqA_10[0] = 0x02, .deqA_10[1] = 0x02, .deqA_10[2] = 0x02, .deqA_10[3] = 0x02, .deqA_10[4] = 0x02, .deqA_10[5] = 0x02,     // BankA 0x39
			.deqA_11[0] = 0x00, .deqA_11[1] = 0x00, .deqA_11[2] = 0x00, .deqA_11[3] = 0x00, .deqA_11[4] = 0x00, .deqA_11[5] = 0x00,     // BankA 0x3a
			.deqA_12[0] = 0xB2, .deqA_12[1] = 0xB2, .deqA_12[2] = 0xB2, .deqA_12[3] = 0xB2, .deqA_12[4] = 0xB2, .deqA_12[5] = 0xB2,     // BankA 0x3b
		},
		/* color */
		{
			.contrast[0] 		= 0x6e, .contrast[1] 		= 0x6b, .contrast[2] 		= 0x98, .contrast[3] 		= 0x66, .contrast[4] 		= 0x61, .contrast[5] 		= 0x65,
			.h_peaking[0] 		= 0x10, .h_peaking[1] 		= 0x10, .h_peaking[2] 		= 0x10, .h_peaking[3] 		= 0x00, .h_peaking[4] 		= 0x30, .h_peaking[5] 		= 0x20,
			.c_filter[0]		= 0x81, .c_filter[1] 		= 0x82, .c_filter[2]	 	= 0x92, .c_filter[3] 		= 0x92, .c_filter[4] 		= 0xc4, .c_filter[5] 		= 0xc4,

			.hue[0] 			= 0x00, .hue[1] 			= 0x00, .hue[2] 			= 0x02, .hue[3] 			= 0x02, .hue[4] 			= 0x02, .hue[5] 			= 0x02,
			.u_gain[0] 			= 0x30, .u_gain[1] 			= 0x28, .u_gain[2] 			= 0x34, .u_gain[3] 			= 0x34, .u_gain[4] 			= 0x34, .u_gain[5] 			= 0x34,
			.v_gain[0] 			= 0x3a, .v_gain[1] 			= 0x38, .v_gain[2] 			= 0x40, .v_gain[3] 			= 0x40, .v_gain[4] 			= 0x40, .v_gain[5] 			= 0x40,
			.u_offset[0] 		= 0x02, .u_offset[1] 		= 0x00, .u_offset[2] 		= 0x00, .u_offset[3] 		= 0x00, .u_offset[4] 		= 0x00, .u_offset[5] 		= 0x00,
			.v_offset[0] 		= 0xf8, .v_offset[1] 		= 0xf8, .v_offset[2] 		= 0xf8, .v_offset[3] 		= 0xf8, .v_offset[4] 		= 0xf8, .v_offset[5] 		= 0xf8,

			.black_level[0] 	= 0x87, .black_level[1] 	= 0x87, .black_level[2] 	= 0x88, .black_level[3] 	= 0x8a, .black_level[4] 	= 0x8d, .black_level[5] 	= 0x8e,
			.acc_ref[0]			= 0x57, .acc_ref[1]			= 0x57, .acc_ref[2]			= 0x57, .acc_ref[3]			= 0x57, .acc_ref[4]			= 0x47, .acc_ref[5]			= 0x37,
			.cti_delay[0]		= 0x80, .cti_delay[1]		= 0x80, .cti_delay[2]		= 0x80, .cti_delay[3]		= 0x80, .cti_delay[4]		= 0xa0, .cti_delay[5]		= 0x80,
			.sub_saturation[0] 	= 0x80, .sub_saturation[1] 	= 0xc0, .sub_saturation[2] 	= 0x80, .sub_saturation[3] 	= 0x9c, .sub_saturation[4] 	= 0x00, .sub_saturation[5] 	= 0xa0,

			.burst_dec_a[0] 	= 0x2a, .burst_dec_a[1] 	= 0x2a, .burst_dec_a[2] 	= 0x2a, .burst_dec_a[3] 	= 0x2a, .burst_dec_a[4] 	= 0x00, .burst_dec_a[5] 	= 0x2a,
			.burst_dec_b[0] 	= 0x00, .burst_dec_b[1] 	= 0x00, .burst_dec_b[2] 	= 0x00, .burst_dec_b[3] 	= 0x00, .burst_dec_b[4] 	= 0x00, .burst_dec_b[5] 	= 0x00,
			.burst_dec_c[0] 	= 0x30, .burst_dec_c[1] 	= 0x30, .burst_dec_c[2] 	= 0x30, .burst_dec_c[3] 	= 0x00, .burst_dec_c[4] 	= 0x00, .burst_dec_c[5] 	= 0x00,

			.c_option[0] 		= 0x80, .c_option[1] 		= 0x80, .c_option[2] 		= 0x80, .c_option[3] 		= 0x90, .c_option[4] 		= 0xa0, .c_option[5] 		= 0xa0,

			.y_filter_b[0]		= 0x10, .y_filter_b[1]		= 0x10, .y_filter_b[2]		= 0x10, .y_filter_b[3]		= 0x10, .y_filter_b[4]		= 0x10, .y_filter_b[5]		= 0x10,
			.y_filter_b_sel[0]	= 0x1e,	.y_filter_b_sel[1]	= 0x1e,	.y_filter_b_sel[2]	= 0x1e, .y_filter_b_sel[3]	= 0x1e, .y_filter_b_sel[4]	= 0x1e, .y_filter_b_sel[5]	= 0x1e,
		},
		/* timing_a */
		{
			.h_delay_a[0] = 0x82, .h_delay_a[1] = 0x82, .h_delay_a[2] = 0x82, .h_delay_a[3] = 0x82, .h_delay_a[4] = 0x82, .h_delay_a[5] = 0x82,
			.h_delay_b[0] = 0x10, .h_delay_b[1] = 0x10, .h_delay_b[2] = 0x10, .h_delay_b[3] = 0x10, .h_delay_b[4] = 0x10, .h_delay_b[5] = 0x10,
			.h_delay_c[0] = 0x00, .h_delay_c[1] = 0x02, .h_delay_c[2] = 0x02, .h_delay_c[3] = 0x02, .h_delay_c[4] = 0x02, .h_delay_c[5] = 0x02,
			.y_delay[0]   = 0x00, .y_delay[1]   = 0x00, .y_delay[2]   = 0x00, .y_delay[3]   = 0x00, .y_delay[4]   = 0x00, .y_delay[5] = 0x00,

		},
		/* clk */
		{
			.clk_adc[0] = 0x05, .clk_adc[1] = 0x05, .clk_adc[2] = 0x05, .clk_adc[3] = 0x05, .clk_adc[4] = 0x05, .clk_adc[5] = 0x05,
			.clk_dec[0] = 0x44, .clk_dec[1] = 0x44, .clk_dec[2] = 0x44, .clk_dec[3] = 0x44, .clk_dec[4] = 0x44, .clk_dec[5] = 0x44,
		},
		/* timing_b */
		{
/*B9 0x96*/	.h_scaler1[0]  = 0x01, .h_scaler1[1]   = 0x01, .h_scaler1[2]   = 0x01, .h_scaler1[3]   = 0x01, .h_scaler1[4]   = 0x01, .h_scaler1[5]   = 0x01,
/*B9 0x97*/	.h_scaler2[0]  = 0x00, .h_scaler2[1]   = 0x00, .h_scaler2[2]   = 0x00, .h_scaler2[3]   = 0x00, .h_scaler2[4]   = 0x00, .h_scaler2[5]   = 0x00,
/*B9 0x98*/	.h_scaler3[0]  = 0x00, .h_scaler3[1]   = 0x00, .h_scaler3[2]   = 0x00, .h_scaler3[3]   = 0x00, .h_scaler3[4]   = 0x00, .h_scaler3[5]   = 0x00,
/*B9 0x99*/	.h_scaler4[0]  = 0x00, .h_scaler4[1]   = 0x00, .h_scaler4[2]   = 0x00, .h_scaler4[3]   = 0x00, .h_scaler4[4]   = 0x00, .h_scaler4[5]   = 0x00,
/*B9 0x9a*/	.h_scaler5[0]  = 0x00, .h_scaler5[1]   = 0x00, .h_scaler5[2]   = 0x00, .h_scaler5[3]   = 0x00, .h_scaler5[4]   = 0x00, .h_scaler5[5]   = 0x00,
/*B9 0x9b*/	.h_scaler6[0]  = 0x00, .h_scaler6[1]   = 0x00, .h_scaler6[2]   = 0x00, .h_scaler6[3]   = 0x00, .h_scaler6[4]   = 0x00, .h_scaler6[5]   = 0x00,
/*B9 0x9c*/	.h_scaler7[0]  = 0x00, .h_scaler7[1]   = 0x00, .h_scaler7[2]   = 0x00, .h_scaler7[3]   = 0x00, .h_scaler7[4]   = 0x00, .h_scaler7[5]   = 0x00,
/*B9 0x9d*/	.h_scaler8[0]  = 0x00, .h_scaler8[1]   = 0x00, .h_scaler8[2]   = 0x00, .h_scaler8[3]   = 0x00, .h_scaler8[4]   = 0x00, .h_scaler8[5]   = 0x00,
/*B9 0x9e*/	.h_scaler9[0]  = 0x00, .h_scaler9[1]   = 0x00, .h_scaler9[2]   = 0x00, .h_scaler9[3]   = 0x00, .h_scaler9[4]   = 0x00, .h_scaler9[5]   = 0x00,


/*B9 0x40*/	.pn_auto[0]    	= 0x00, .pn_auto[1]		= 0x00, .pn_auto[2]    	= 0x00, .pn_auto[3]    	= 0x00, .pn_auto[4]    	= 0x00, .pn_auto[5]    	= 0x00,

/*B5 0x90*/	.comb_mode[0]   = 0x05, .comb_mode[1]	= 0x05, .comb_mode[2]   = 0x05, .comb_mode[3]   = 0x05, .comb_mode[4]  	= 0x05, .comb_mode[5]   = 0x05,
/*B9 0xb9*/	.h_pll_op_a[0]  = 0x72, .h_pll_op_a[1]  = 0x72, .h_pll_op_a[2]  = 0x72, .h_pll_op_a[3]  = 0x72, .h_pll_op_a[4]  = 0x72, .h_pll_op_a[5]  = 0x72,
/*B9 0x57*/	.mem_path[0]	= 0x10, .mem_path[1]	= 0x10, .mem_path[2]	= 0x10, .mem_path[3]	= 0x10, .mem_path[4]	= 0x10, .mem_path[5]	= 0x10,
			.fsc_lock_speed[0] = 0xdc, .fsc_lock_speed[1] = 0xdc, .fsc_lock_speed[2] = 0xdc, .fsc_lock_speed[3] = 0xdc, .fsc_lock_speed[4] = 0xdc, .fsc_lock_speed[5] = 0xdc,

/*B0 0x81*/	.format_set1[0] = 0x09, .format_set1[1] = 0x09, .format_set1[2] = 0x09, .format_set1[3] = 0x09, .format_set1[4] = 0x09, .format_set1[5] = 0x09,
/*B0 0x85*/	.format_set2[0] = 0x03, .format_set2[1] = 0x03, .format_set2[2] = 0x03, .format_set2[3] = 0x03, .format_set2[4] = 0x03, .format_set2[5] = 0x03,

/*B0 0x64*/ .v_delay[0]     = 0x80, .v_delay[1]     = 0x80, .v_delay[2]     = 0x80, .v_delay[3]     = 0x80, .v_delay[4]     = 0x80, .v_delay[5]     = 0x80,
		},
	},

	[ AHD30_4M_15P ] = { /* o */
	/* base */
		{
			.eq_bypass[0] 	= 0x62, .eq_bypass[1] 	= 0x22, .eq_bypass[2] 	= 0x22, .eq_bypass[3] 	= 0x22, .eq_bypass[4] 	= 0x22, .eq_bypass[5] 	= 0x22,    // Bank5 0x30
			.eq_band_sel[0] = 0x77, .eq_band_sel[1] = 0x77, .eq_band_sel[2] = 0x77, .eq_band_sel[3] = 0x77, .eq_band_sel[4] = 0x57, .eq_band_sel[5] = 0x57,    // BankA 0x31
			.eq_gain_sel[0] = 0x78, .eq_gain_sel[1] = 0x7b, .eq_gain_sel[2] = 0x7f, .eq_gain_sel[3] = 0x7f, .eq_gain_sel[4] = 0x7f, .eq_gain_sel[5] = 0x7f,    // BankA 0x32
			.deq_a_on[0] 	= 0x00, .deq_a_on[1] 	= 0x01, .deq_a_on[2] 	= 0x01, .deq_a_on[3] 	= 0x01, .deq_a_on[4] 	= 0x01, .deq_a_on[5] 	= 0x01,    // BankA 0x33
			.deq_a_sel[0] 	= 0x00, .deq_a_sel[1] 	= 0x91, .deq_a_sel[2] 	= 0x87, .deq_a_sel[3] 	= 0x89, .deq_a_sel[4] 	= 0x93, .deq_a_sel[5] 	= 0x94,    // BankA 0x34
			.deq_b_sel[0] 	= 0x00, .deq_b_sel[1] 	= 0x00, .deq_b_sel[2] 	= 0x00, .deq_b_sel[3] 	= 0x00, .deq_b_sel[4] 	= 0x00, .deq_b_sel[5] 	= 0x00,    // BankA 0x35
		},
		/* coeff */
		{
			.deqA_01[0] = 0xAC, .deqA_01[1] = 0xAC, .deqA_01[2] = 0xAC, .deqA_01[3] = 0xAC, .deqA_01[4] = 0xAC, .deqA_01[5] = 0xAC,		// BankA 0x30
			.deqA_02[0] = 0x78, .deqA_02[1] = 0x78, .deqA_02[2] = 0x78, .deqA_02[3] = 0x78, .deqA_02[4] = 0x78, .deqA_02[5] = 0x78,		// BankA 0x31
			.deqA_03[0] = 0x17, .deqA_03[1] = 0x17, .deqA_03[2] = 0x17, .deqA_03[3] = 0x17, .deqA_03[4] = 0x17, .deqA_03[5] = 0x17,		// BankA 0x32
			.deqA_04[0] = 0xC1, .deqA_04[1] = 0xC1, .deqA_04[2] = 0xC1, .deqA_04[3] = 0xC1, .deqA_04[4] = 0xC1, .deqA_04[5] = 0xC1,     // BankA 0x33
			.deqA_05[0] = 0x40, .deqA_05[1] = 0x40, .deqA_05[2] = 0x40, .deqA_05[3] = 0x40, .deqA_05[4] = 0x40, .deqA_05[5] = 0x40,     // BankA 0x34
			.deqA_06[0] = 0x00, .deqA_06[1] = 0x00, .deqA_06[2] = 0x00, .deqA_06[3] = 0x00, .deqA_06[4] = 0x00, .deqA_06[5] = 0x00,     // BankA 0x35
			.deqA_07[0] = 0xC3, .deqA_07[1] = 0xC3, .deqA_07[2] = 0xC3, .deqA_07[3] = 0xC3, .deqA_07[4] = 0xC3, .deqA_07[5] = 0xC3,     // BankA 0x36
			.deqA_08[0] = 0x0A, .deqA_08[1] = 0x0A, .deqA_08[2] = 0x0A, .deqA_08[3] = 0x0A, .deqA_08[4] = 0x0A, .deqA_08[5] = 0x0A,     // BankA 0x37
			.deqA_09[0] = 0x00, .deqA_09[1] = 0x00, .deqA_09[2] = 0x00, .deqA_09[3] = 0x00, .deqA_09[4] = 0x00, .deqA_09[5] = 0x00,     // BankA 0x38
			.deqA_10[0] = 0x02, .deqA_10[1] = 0x02, .deqA_10[2] = 0x02, .deqA_10[3] = 0x02, .deqA_10[4] = 0x02, .deqA_10[5] = 0x02,     // BankA 0x39
			.deqA_11[0] = 0x00, .deqA_11[1] = 0x00, .deqA_11[2] = 0x00, .deqA_11[3] = 0x00, .deqA_11[4] = 0x00, .deqA_11[5] = 0x00,     // BankA 0x3a
			.deqA_12[0] = 0xB2, .deqA_12[1] = 0xB2, .deqA_12[2] = 0xB2, .deqA_12[3] = 0xB2, .deqA_12[4] = 0xB2, .deqA_12[5] = 0xB2,     // BankA 0x3b
		},
		/* color */
		{
			.contrast[0] 		= 0x86, .contrast[1] 		= 0x82, .contrast[2] 		= 0x82, .contrast[3] 		= 0x7e, .contrast[4] 		= 0x7c, .contrast[5] 		= 0x77,
			.h_peaking[0] 		= 0x0f, .h_peaking[1] 		= 0x0f, .h_peaking[2] 		= 0x0f, .h_peaking[3] 		= 0x0f, .h_peaking[4] 		= 0x0f, .h_peaking[5] 		= 0x0f,
			.c_filter[0]		= 0x82, .c_filter[1] 		= 0x82, .c_filter[2]	 	= 0x92, .c_filter[3] 		= 0x92, .c_filter[4] 		= 0xa2, .c_filter[5] 		= 0xb2,

			.hue[0] 			= 0x00, .hue[1] 			= 0x00, .hue[2] 			= 0x00, .hue[3] 			= 0x00, .hue[4] 			= 0x00, .hue[5] 			= 0x00,
			.u_gain[0] 			= 0x10, .u_gain[1] 			= 0x10, .u_gain[2] 			= 0x04, .u_gain[3] 			= 0xfc, .u_gain[4] 			= 0xfc, .u_gain[5] 			= 0xfc,
			.v_gain[0] 			= 0x10, .v_gain[1] 			= 0x10, .v_gain[2] 			= 0x04, .v_gain[3] 			= 0xf4, .v_gain[4] 			= 0x08, .v_gain[5] 			= 0x08,
			.u_offset[0] 		= 0xfb, .u_offset[1] 		= 0xfb, .u_offset[2] 		= 0xfb, .u_offset[3] 		= 0xfb, .u_offset[4] 		= 0xfb, .u_offset[5] 		= 0xfe,
			.v_offset[0] 		= 0xf8, .v_offset[1] 		= 0xf8, .v_offset[2] 		= 0xf8, .v_offset[3] 		= 0xf8, .v_offset[4] 		= 0xf8, .v_offset[5] 		= 0xfb,

			.black_level[0] 	= 0x80, .black_level[1] 	= 0x81, .black_level[2] 	= 0x81, .black_level[3] 	= 0x83, .black_level[4] 	= 0x85, .black_level[5] 	= 0x87,
			.acc_ref[0]			= 0x57, .acc_ref[1]			= 0x57, .acc_ref[2]			= 0x57, .acc_ref[3]			= 0x57, .acc_ref[4]			= 0x57, .acc_ref[5]			= 0x57,
			.cti_delay[0]		= 0x80, .cti_delay[1]		= 0x80, .cti_delay[2]		= 0x80, .cti_delay[3]		= 0x80, .cti_delay[4]		= 0x80, .cti_delay[5]		= 0x80,
			.sub_saturation[0] 	= 0xa8, .sub_saturation[1] 	= 0xa8, .sub_saturation[2] 	= 0xa8, .sub_saturation[3] 	= 0xa8, .sub_saturation[4] 	= 0x90, .sub_saturation[5] 	= 0x90,

			.burst_dec_a[0] 	= 0x2a, .burst_dec_a[1] 	= 0x2a, .burst_dec_a[2] 	= 0x2a, .burst_dec_a[3] 	= 0x2a, .burst_dec_a[4] 	= 0x2a, .burst_dec_a[5] 	= 0x2a,
			.burst_dec_b[0] 	= 0x00, .burst_dec_b[1] 	= 0x00, .burst_dec_b[2] 	= 0x00, .burst_dec_b[3] 	= 0x00, .burst_dec_b[4] 	= 0x00, .burst_dec_b[5] 	= 0x00,
			.burst_dec_c[0] 	= 0x30, .burst_dec_c[1] 	= 0x30, .burst_dec_c[2] 	= 0x30, .burst_dec_c[3] 	= 0x30, .burst_dec_c[4] 	= 0x30, .burst_dec_c[5] 	= 0x30,

			.c_option[0] 		= 0x80, .c_option[1] 		= 0x80, .c_option[2] 		= 0x90, .c_option[3] 		= 0x90, .c_option[4] 		= 0x90, .c_option[5] 		= 0xa0,

			.y_filter_b[0]		= 0x10, .y_filter_b[1]		= 0x10, .y_filter_b[2]		= 0x10, .y_filter_b[3]		= 0x10, .y_filter_b[4]		= 0x10, .y_filter_b[5]		= 0x10,
			.y_filter_b_sel[0]	= 0x1e,	.y_filter_b_sel[1]	= 0x1e,	.y_filter_b_sel[2]	= 0x1e, .y_filter_b_sel[3]	= 0x1e, .y_filter_b_sel[4]	= 0x1e, .y_filter_b_sel[5]	= 0x1e,
		},
		/* timing_a */
		{
			.h_delay_a[0] = 0x80, .h_delay_a[1] = 0x80, .h_delay_a[2] = 0x80, .h_delay_a[3] = 0x80, .h_delay_a[4] = 0x80, .h_delay_a[5] = 0x80,
			.h_delay_b[0] = 0x10, .h_delay_b[1] = 0x10, .h_delay_b[2] = 0x10, .h_delay_b[3] = 0x10, .h_delay_b[4] = 0x10, .h_delay_b[5] = 0x10,
			.h_delay_c[0] = 0x00, .h_delay_c[1] = 0x00, .h_delay_c[2] = 0x00, .h_delay_c[3] = 0x00, .h_delay_c[4] = 0x00, .h_delay_c[5] = 0x00,
			.y_delay[0]   = 0x05, .y_delay[1]   = 0x03, .y_delay[2]   = 0x03, .y_delay[3]   = 0x03, .y_delay[4]   = 0x03, .y_delay[5] =   0x03,

		},
		/* clk */
		{
			.clk_adc[0] = 0x02, .clk_adc[1] = 0x02, .clk_adc[2] = 0x02, .clk_adc[3] = 0x02, .clk_adc[4] = 0x02, .clk_adc[5] = 0x02,
			.clk_dec[0] = 0x40, .clk_dec[1] = 0x40, .clk_dec[2] = 0x40, .clk_dec[3] = 0x40, .clk_dec[4] = 0x40, .clk_dec[5] = 0x40,
		},
		/* timing_b */
		{
	/*B9 0x96*/	.h_scaler1[0]  = 0x00, .h_scaler1[1]   = 0x00, .h_scaler1[2]   = 0x00, .h_scaler1[3]   = 0x00, .h_scaler1[4]   = 0x00, .h_scaler1[5]   = 0x00,
	/*B9 0x97*/	.h_scaler2[0]  = 0x00, .h_scaler2[1]   = 0x00, .h_scaler2[2]   = 0x00, .h_scaler2[3]   = 0x00, .h_scaler2[4]   = 0x00, .h_scaler2[5]   = 0x00,
	/*B9 0x98*/	.h_scaler3[0]  = 0x00, .h_scaler3[1]   = 0x00, .h_scaler3[2]   = 0x00, .h_scaler3[3]   = 0x00, .h_scaler3[4]   = 0x00, .h_scaler3[5]   = 0x00,
	/*B9 0x99*/	.h_scaler4[0]  = 0x00, .h_scaler4[1]   = 0x00, .h_scaler4[2]   = 0x00, .h_scaler4[3]   = 0x00, .h_scaler4[4]   = 0x00, .h_scaler4[5]   = 0x00,
	/*B9 0x9a*/	.h_scaler5[0]  = 0x00, .h_scaler5[1]   = 0x00, .h_scaler5[2]   = 0x00, .h_scaler5[3]   = 0x00, .h_scaler5[4]   = 0x00, .h_scaler5[5]   = 0x00,
	/*B9 0x9b*/	.h_scaler6[0]  = 0x00, .h_scaler6[1]   = 0x00, .h_scaler6[2]   = 0x00, .h_scaler6[3]   = 0x00, .h_scaler6[4]   = 0x00, .h_scaler6[5]   = 0x00,
	/*B9 0x9c*/	.h_scaler7[0]  = 0x00, .h_scaler7[1]   = 0x00, .h_scaler7[2]   = 0x00, .h_scaler7[3]   = 0x00, .h_scaler7[4]   = 0x00, .h_scaler7[5]   = 0x00,
	/*B9 0x9d*/	.h_scaler8[0]  = 0x00, .h_scaler8[1]   = 0x00, .h_scaler8[2]   = 0x00, .h_scaler8[3]   = 0x00, .h_scaler8[4]   = 0x00, .h_scaler8[5]   = 0x00,
	/*B9 0x9e*/	.h_scaler9[0]  = 0x00, .h_scaler9[1]   = 0x00, .h_scaler9[2]   = 0x00, .h_scaler9[3]   = 0x00, .h_scaler9[4]   = 0x00, .h_scaler9[5]   = 0x00,


	/*B9 0x40*/	.pn_auto[0]    	= 0x00, .pn_auto[1]		= 0x00, .pn_auto[2]    	= 0x00, .pn_auto[3]    	= 0x00, .pn_auto[4]    	= 0x00, .pn_auto[5]    	= 0x00,

	/*B5 0x90*/	.comb_mode[0]      = 0x01, .comb_mode[1]	  = 0x01, .comb_mode[2]      = 0x01, .comb_mode[3]      = 0x01, .comb_mode[4]  	   = 0x01, .comb_mode[5]      = 0x01,
	/*B9 0xb9*/	.h_pll_op_a[0]     = 0x72, .h_pll_op_a[1]     = 0x72, .h_pll_op_a[2]     = 0x72, .h_pll_op_a[3]     = 0x72, .h_pll_op_a[4]     = 0x72, .h_pll_op_a[5]     = 0x72,
	/*B9 0x57*/	.mem_path[0]	   = 0x00, .mem_path[1]	      = 0x00, .mem_path[2]	     = 0x00, .mem_path[3]	    = 0x00, .mem_path[4]	   = 0x00, .mem_path[5]	      = 0x00,
				.fsc_lock_speed[0] = 0xdc, .fsc_lock_speed[1] = 0xdc, .fsc_lock_speed[2] = 0xdc, .fsc_lock_speed[3] = 0xdc, .fsc_lock_speed[4] = 0xdc, .fsc_lock_speed[5] = 0xdc,

	/*B0 0x81*/	.format_set1[0] = 0x0A, .format_set1[1] = 0x0A, .format_set1[2] = 0x0A, .format_set1[3] = 0x0A, .format_set1[4] = 0x0A, .format_set1[5] = 0x0A,
	/*B0 0x85*/	.format_set2[0] = 0x04, .format_set2[1] = 0x04, .format_set2[2] = 0x04, .format_set2[3] = 0x04, .format_set2[4] = 0x04, .format_set2[5] = 0x04,

	/*B0 0x64*/ .v_delay[0]     = 0x20, .v_delay[1]     = 0x20, .v_delay[2]     = 0x20, .v_delay[3]     = 0x20, .v_delay[4]     = 0x20, .v_delay[5]     = 0x20,
		},
	},

	[ AHD30_4M_25P ] = /* o */
	{
		/* base */
		{
			.eq_bypass[0] 	= 0x22, .eq_bypass[1] 	= 0x22, .eq_bypass[2] 	= 0x22, .eq_bypass[3] 	= 0x22, .eq_bypass[4] 	= 0x22, .eq_bypass[5] 	= 0x22,    // Bank5 0x30
			.eq_band_sel[0] = 0x77, .eq_band_sel[1] = 0x77, .eq_band_sel[2] = 0x77, .eq_band_sel[3] = 0x67, .eq_band_sel[4] = 0x57, .eq_band_sel[5] = 0x57,    // BankA 0x31
			.eq_gain_sel[0] = 0x78, .eq_gain_sel[1] = 0x7b, .eq_gain_sel[2] = 0x7f, .eq_gain_sel[3] = 0x7e, .eq_gain_sel[4] = 0x7f, .eq_gain_sel[5] = 0x7f,    // BankA 0x32
			.deq_a_on[0] 	= 0x00, .deq_a_on[1] 	= 0x01, .deq_a_on[2] 	= 0x01, .deq_a_on[3] 	= 0x01, .deq_a_on[4] 	= 0x01, .deq_a_on[5] 	= 0x01,    // BankA 0x33
			.deq_a_sel[0] 	= 0x00, .deq_a_sel[1] 	= 0x91, .deq_a_sel[2] 	= 0x93, .deq_a_sel[3] 	= 0x98, .deq_a_sel[4] 	= 0x98, .deq_a_sel[5] 	= 0x98,    // BankA 0x34
			.deq_b_sel[0] 	= 0x00, .deq_b_sel[1] 	= 0x00, .deq_b_sel[2] 	= 0x00, .deq_b_sel[3] 	= 0x00, .deq_b_sel[4] 	= 0x00, .deq_b_sel[5] 	= 0x00,    // BankA 0x35
		},
		/* coeff */
		{
			.deqA_01[0] = 0xAC, .deqA_01[1] = 0xAC, .deqA_01[2] = 0xAC, .deqA_01[3] = 0xAC, .deqA_01[4] = 0xAC, .deqA_01[5] = 0xAC,		// BankA 0x30
			.deqA_02[0] = 0x78, .deqA_02[1] = 0x78, .deqA_02[2] = 0x78, .deqA_02[3] = 0x78, .deqA_02[4] = 0x78, .deqA_02[5] = 0x78,		// BankA 0x31
			.deqA_03[0] = 0x17, .deqA_03[1] = 0x17, .deqA_03[2] = 0x17, .deqA_03[3] = 0x17, .deqA_03[4] = 0x17, .deqA_03[5] = 0x17,		// BankA 0x32
			.deqA_04[0] = 0xC1, .deqA_04[1] = 0xC1, .deqA_04[2] = 0xC1, .deqA_04[3] = 0xC1, .deqA_04[4] = 0xC1, .deqA_04[5] = 0xC1,     // BankA 0x33
			.deqA_05[0] = 0x40, .deqA_05[1] = 0x40, .deqA_05[2] = 0x40, .deqA_05[3] = 0x40, .deqA_05[4] = 0x40, .deqA_05[5] = 0x40,     // BankA 0x34
			.deqA_06[0] = 0x00, .deqA_06[1] = 0x00, .deqA_06[2] = 0x00, .deqA_06[3] = 0x00, .deqA_06[4] = 0x00, .deqA_06[5] = 0x00,     // BankA 0x35
			.deqA_07[0] = 0xC3, .deqA_07[1] = 0xC3, .deqA_07[2] = 0xC3, .deqA_07[3] = 0xC3, .deqA_07[4] = 0xC3, .deqA_07[5] = 0xC3,     // BankA 0x36
			.deqA_08[0] = 0x0A, .deqA_08[1] = 0x0A, .deqA_08[2] = 0x0A, .deqA_08[3] = 0x0A, .deqA_08[4] = 0x0A, .deqA_08[5] = 0x0A,     // BankA 0x37
			.deqA_09[0] = 0x00, .deqA_09[1] = 0x00, .deqA_09[2] = 0x00, .deqA_09[3] = 0x00, .deqA_09[4] = 0x00, .deqA_09[5] = 0x00,     // BankA 0x38
			.deqA_10[0] = 0x02, .deqA_10[1] = 0x02, .deqA_10[2] = 0x02, .deqA_10[3] = 0x02, .deqA_10[4] = 0x02, .deqA_10[5] = 0x02,     // BankA 0x39
			.deqA_11[0] = 0x00, .deqA_11[1] = 0x00, .deqA_11[2] = 0x00, .deqA_11[3] = 0x00, .deqA_11[4] = 0x00, .deqA_11[5] = 0x00,     // BankA 0x3a
			.deqA_12[0] = 0xB2, .deqA_12[1] = 0xB2, .deqA_12[2] = 0xB2, .deqA_12[3] = 0xB2, .deqA_12[4] = 0xB2, .deqA_12[5] = 0xB2,     // BankA 0x3b
		},
		/* color */
		{
			.contrast[0] 		= 0xa0, .contrast[1] 		= 0x9c, .contrast[2] 		= 0x90, .contrast[3] 		= 0x95, .contrast[4] 		= 0x90, .contrast[5] 		= 0x8a,
			.h_peaking[0] 		= 0x0f, .h_peaking[1] 		= 0x0f, .h_peaking[2] 		= 0x0f, .h_peaking[3] 		= 0x0f, .h_peaking[4] 		= 0x0f, .h_peaking[5] 		= 0x0f,
			.c_filter[0]		= 0x82, .c_filter[1] 		= 0x82, .c_filter[2]	 	= 0x92, .c_filter[3] 		= 0x92, .c_filter[4] 		= 0xa2, .c_filter[5] 		= 0xb2,

			.hue[0] 			= 0xff, .hue[1] 			= 0xff, .hue[2] 			= 0xff, .hue[3] 			= 0xff, .hue[4] 			= 0xff, .hue[5] 			= 0xff,
			.u_gain[0] 			= 0x70, .u_gain[1] 			= 0x70, .u_gain[2] 			= 0x64, .u_gain[3] 			= 0x5c, .u_gain[4] 			= 0x5c, .u_gain[5] 			= 0x5c,
			.v_gain[0] 			= 0xd8, .v_gain[1] 			= 0xd8, .v_gain[2] 			= 0xcc, .v_gain[3] 			= 0xbc, .v_gain[4] 			= 0xd0, .v_gain[5] 			= 0xd0,
			.u_offset[0] 		= 0xfc, .u_offset[1] 		= 0xfc, .u_offset[2] 		= 0xfc, .u_offset[3] 		= 0xfc, .u_offset[4] 		= 0xfc, .u_offset[5] 		= 0xfc,
			.v_offset[0] 		= 0xfa, .v_offset[1] 		= 0xfa, .v_offset[2] 		= 0xfa, .v_offset[3] 		= 0xfa, .v_offset[4] 		= 0xfa, .v_offset[5] 		= 0xfa,

			.black_level[0] 	= 0x8c, .black_level[1] 	= 0x8a, .black_level[2] 	= 0x8c, .black_level[3] 	= 0x8d, .black_level[4] 	= 0x91, .black_level[5] 	= 0x94,
			.acc_ref[0]			= 0x57, .acc_ref[1]			= 0x57, .acc_ref[2]			= 0x57, .acc_ref[3]			= 0x57, .acc_ref[4]			= 0x57, .acc_ref[5]			= 0x57,
			.cti_delay[0]		= 0x80, .cti_delay[1]		= 0x80, .cti_delay[2]		= 0x80, .cti_delay[3]		= 0x80, .cti_delay[4]		= 0x80, .cti_delay[5]		= 0x80,
			.sub_saturation[0] 	= 0xe0, .sub_saturation[1] 	= 0xe0, .sub_saturation[2] 	= 0xd0, .sub_saturation[3] 	= 0xe0, .sub_saturation[4] 	= 0xe4, .sub_saturation[5] 	= 0xc0,

			.burst_dec_a[0] 	= 0x2a, .burst_dec_a[1] 	= 0x2a, .burst_dec_a[2] 	= 0x2a, .burst_dec_a[3] 	= 0x2a, .burst_dec_a[4] 	= 0x2a, .burst_dec_a[5] 	= 0x2a,
			.burst_dec_b[0] 	= 0x00, .burst_dec_b[1] 	= 0x00, .burst_dec_b[2] 	= 0x00, .burst_dec_b[3] 	= 0x00, .burst_dec_b[4] 	= 0x00, .burst_dec_b[5] 	= 0x00,
			.burst_dec_c[0] 	= 0x50, .burst_dec_c[1] 	= 0x50, .burst_dec_c[2] 	= 0x50, .burst_dec_c[3] 	= 0x50, .burst_dec_c[4] 	= 0x50, .burst_dec_c[5] 	= 0x50,

			.c_option[0] 		= 0x80, .c_option[1] 		= 0x80, .c_option[2] 		= 0x80, .c_option[3] 		= 0x90, .c_option[4] 		= 0x90, .c_option[5] 		= 0x90,

			.y_filter_b[0]		= 0x10, .y_filter_b[1]		= 0x10, .y_filter_b[2]		= 0x10, .y_filter_b[3]		= 0x10, .y_filter_b[4]		= 0x10, .y_filter_b[5]		= 0x10,
			.y_filter_b_sel[0]	= 0x1e,	.y_filter_b_sel[1]	= 0x1e,	.y_filter_b_sel[2]	= 0x1e, .y_filter_b_sel[3]	= 0x1e, .y_filter_b_sel[4]	= 0x1e, .y_filter_b_sel[5]	= 0x1e,
		},
		/* timing_a */
		{
			.h_delay_a[0] = 0x84, .h_delay_a[1] = 0x82, .h_delay_a[2] = 0x80, .h_delay_a[3] = 0x7f, .h_delay_a[4] = 0x7f, .h_delay_a[5] = 0x7f,
			.h_delay_b[0] = 0x10, .h_delay_b[1] = 0x10, .h_delay_b[2] = 0x10, .h_delay_b[3] = 0x10, .h_delay_b[4] = 0x10, .h_delay_b[5] = 0x10,
			.h_delay_c[0] = 0x02, .h_delay_c[1] = 0x02, .h_delay_c[2] = 0x02, .h_delay_c[3] = 0x02, .h_delay_c[4] = 0x02, .h_delay_c[5] = 0x02,
			.y_delay[0]   = 0x05, .y_delay[1]   = 0x05, .y_delay[2]   = 0x05, .y_delay[3]   = 0x05, .y_delay[4]   = 0x05, .y_delay[5] =   0x05,

		},
		/* clk */
		{
			.clk_adc[0] = 0x05, .clk_adc[1] = 0x05, .clk_adc[2] = 0x05, .clk_adc[3] = 0x05, .clk_adc[4] = 0x05, .clk_adc[5] = 0x05,
			.clk_dec[0] = 0x44, .clk_dec[1] = 0x44, .clk_dec[2] = 0x44, .clk_dec[3] = 0x44, .clk_dec[4] = 0x44, .clk_dec[5] = 0x44,
		},
		/* timing_b */
		{
/*B9 0x96*/	.h_scaler1[0]  = 0x00, .h_scaler1[1]   = 0x00, .h_scaler1[2]   = 0x00, .h_scaler1[3]   = 0x00, .h_scaler1[4]   = 0x00, .h_scaler1[5]   = 0x00,
/*B9 0x97*/	.h_scaler2[0]  = 0x00, .h_scaler2[1]   = 0x00, .h_scaler2[2]   = 0x00, .h_scaler2[3]   = 0x00, .h_scaler2[4]   = 0x00, .h_scaler2[5]   = 0x00,
/*B9 0x98*/	.h_scaler3[0]  = 0x00, .h_scaler3[1]   = 0x00, .h_scaler3[2]   = 0x00, .h_scaler3[3]   = 0x00, .h_scaler3[4]   = 0x00, .h_scaler3[5]   = 0x00,
/*B9 0x99*/	.h_scaler4[0]  = 0x00, .h_scaler4[1]   = 0x00, .h_scaler4[2]   = 0x00, .h_scaler4[3]   = 0x00, .h_scaler4[4]   = 0x00, .h_scaler4[5]   = 0x00,
/*B9 0x9a*/	.h_scaler5[0]  = 0x00, .h_scaler5[1]   = 0x00, .h_scaler5[2]   = 0x00, .h_scaler5[3]   = 0x00, .h_scaler5[4]   = 0x00, .h_scaler5[5]   = 0x00,
/*B9 0x9b*/	.h_scaler6[0]  = 0x00, .h_scaler6[1]   = 0x00, .h_scaler6[2]   = 0x00, .h_scaler6[3]   = 0x00, .h_scaler6[4]   = 0x00, .h_scaler6[5]   = 0x00,
/*B9 0x9c*/	.h_scaler7[0]  = 0x00, .h_scaler7[1]   = 0x00, .h_scaler7[2]   = 0x00, .h_scaler7[3]   = 0x00, .h_scaler7[4]   = 0x00, .h_scaler7[5]   = 0x00,
/*B9 0x9d*/	.h_scaler8[0]  = 0x00, .h_scaler8[1]   = 0x00, .h_scaler8[2]   = 0x00, .h_scaler8[3]   = 0x00, .h_scaler8[4]   = 0x00, .h_scaler8[5]   = 0x00,
/*B9 0x9e*/	.h_scaler9[0]  = 0x00, .h_scaler9[1]   = 0x00, .h_scaler9[2]   = 0x00, .h_scaler9[3]   = 0x00, .h_scaler9[4]   = 0x00, .h_scaler9[5]   = 0x00,


/*B9 0x40*/	.pn_auto[0]    	= 0x00, .pn_auto[1]		= 0x00, .pn_auto[2]    	= 0x00, .pn_auto[3]    	= 0x00, .pn_auto[4]    	= 0x00, .pn_auto[5]    	= 0x00,

/*B5 0x90*/	.comb_mode[0]   = 0x01, .comb_mode[1]	= 0x01, .comb_mode[2]   = 0x01, .comb_mode[3]   = 0x01, .comb_mode[4]  	= 0x01, .comb_mode[5]   = 0x01,
/*B9 0xb9*/	.h_pll_op_a[0]  = 0x72, .h_pll_op_a[1]  = 0x72, .h_pll_op_a[2]  = 0x72, .h_pll_op_a[3]  = 0x72, .h_pll_op_a[4]  = 0x72, .h_pll_op_a[5]  = 0x72,
/*B9 0x57*/	.mem_path[0]	= 0x00, .mem_path[1]	= 0x00, .mem_path[2]	= 0x00, .mem_path[3]	= 0x00, .mem_path[4]	= 0x00, .mem_path[5]	= 0x00,
			.fsc_lock_speed[0] = 0xdc, .fsc_lock_speed[1] = 0xdc, .fsc_lock_speed[2] = 0xdc, .fsc_lock_speed[3] = 0xdc, .fsc_lock_speed[4] = 0xdc, .fsc_lock_speed[5] = 0xdc,

/*B0 0x81*/	.format_set1[0] = 0x0f, .format_set1[1] = 0x0f, .format_set1[2] = 0x0f, .format_set1[3] = 0x0f, .format_set1[4] = 0x0f, .format_set1[5] = 0x0f,
/*B0 0x85*/	.format_set2[0] = 0x00, .format_set2[1] = 0x00, .format_set2[2] = 0x00, .format_set2[3] = 0x00, .format_set2[4] = 0x00, .format_set2[5] = 0x00,

/*B0 0x64*/ .v_delay[0]     = 0x80, .v_delay[1]     = 0x80, .v_delay[2]     = 0x80, .v_delay[3]     = 0x80, .v_delay[4]     = 0x80, .v_delay[5]     = 0x80,
		},
	},
	[ AHD30_4M_30P ] = { /* o */
	/* base */
		{
			.eq_bypass[0] 	= 0x22, .eq_bypass[1] 	= 0x22, .eq_bypass[2] 	= 0x22, .eq_bypass[3] 	= 0x22, .eq_bypass[4] 	= 0x22, .eq_bypass[5] 	= 0x22,    // Bank5 0x30
			.eq_band_sel[0] = 0x77, .eq_band_sel[1] = 0x77, .eq_band_sel[2] = 0x77, .eq_band_sel[3] = 0x67, .eq_band_sel[4] = 0x57, .eq_band_sel[5] = 0x57,    // BankA 0x31
			.eq_gain_sel[0] = 0x78, .eq_gain_sel[1] = 0x7b, .eq_gain_sel[2] = 0x7f, .eq_gain_sel[3] = 0x7e, .eq_gain_sel[4] = 0x7f, .eq_gain_sel[5] = 0x7f,    // BankA 0x32
			.deq_a_on[0] 	= 0x00, .deq_a_on[1] 	= 0x01, .deq_a_on[2] 	= 0x01, .deq_a_on[3] 	= 0x01, .deq_a_on[4] 	= 0x01, .deq_a_on[5] 	= 0x01,    // BankA 0x33
			.deq_a_sel[0] 	= 0x00, .deq_a_sel[1] 	= 0x91, .deq_a_sel[2] 	= 0x93, .deq_a_sel[3] 	= 0x98, .deq_a_sel[4] 	= 0x98, .deq_a_sel[5] 	= 0x98,    // BankA 0x34
			.deq_b_sel[0] 	= 0x00, .deq_b_sel[1] 	= 0x00, .deq_b_sel[2] 	= 0x00, .deq_b_sel[3] 	= 0x00, .deq_b_sel[4] 	= 0x00, .deq_b_sel[5] 	= 0x00,    // BankA 0x35
		},
		/* coeff */
		{
			.deqA_01[0] = 0xAC, .deqA_01[1] = 0xAC, .deqA_01[2] = 0xAC, .deqA_01[3] = 0xAC, .deqA_01[4] = 0xAC, .deqA_01[5] = 0xAC,		// BankA 0x30
			.deqA_02[0] = 0x78, .deqA_02[1] = 0x78, .deqA_02[2] = 0x78, .deqA_02[3] = 0x78, .deqA_02[4] = 0x78, .deqA_02[5] = 0x78,		// BankA 0x31
			.deqA_03[0] = 0x17, .deqA_03[1] = 0x17, .deqA_03[2] = 0x17, .deqA_03[3] = 0x17, .deqA_03[4] = 0x17, .deqA_03[5] = 0x17,		// BankA 0x32
			.deqA_04[0] = 0xC1, .deqA_04[1] = 0xC1, .deqA_04[2] = 0xC1, .deqA_04[3] = 0xC1, .deqA_04[4] = 0xC1, .deqA_04[5] = 0xC1,     // BankA 0x33
			.deqA_05[0] = 0x40, .deqA_05[1] = 0x40, .deqA_05[2] = 0x40, .deqA_05[3] = 0x40, .deqA_05[4] = 0x40, .deqA_05[5] = 0x40,     // BankA 0x34
			.deqA_06[0] = 0x00, .deqA_06[1] = 0x00, .deqA_06[2] = 0x00, .deqA_06[3] = 0x00, .deqA_06[4] = 0x00, .deqA_06[5] = 0x00,     // BankA 0x35
			.deqA_07[0] = 0xC3, .deqA_07[1] = 0xC3, .deqA_07[2] = 0xC3, .deqA_07[3] = 0xC3, .deqA_07[4] = 0xC3, .deqA_07[5] = 0xC3,     // BankA 0x36
			.deqA_08[0] = 0x0A, .deqA_08[1] = 0x0A, .deqA_08[2] = 0x0A, .deqA_08[3] = 0x0A, .deqA_08[4] = 0x0A, .deqA_08[5] = 0x0A,     // BankA 0x37
			.deqA_09[0] = 0x00, .deqA_09[1] = 0x00, .deqA_09[2] = 0x00, .deqA_09[3] = 0x00, .deqA_09[4] = 0x00, .deqA_09[5] = 0x00,     // BankA 0x38
			.deqA_10[0] = 0x02, .deqA_10[1] = 0x02, .deqA_10[2] = 0x02, .deqA_10[3] = 0x02, .deqA_10[4] = 0x02, .deqA_10[5] = 0x02,     // BankA 0x39
			.deqA_11[0] = 0x00, .deqA_11[1] = 0x00, .deqA_11[2] = 0x00, .deqA_11[3] = 0x00, .deqA_11[4] = 0x00, .deqA_11[5] = 0x00,     // BankA 0x3a
			.deqA_12[0] = 0xB2, .deqA_12[1] = 0xB2, .deqA_12[2] = 0xB2, .deqA_12[3] = 0xB2, .deqA_12[4] = 0xB2, .deqA_12[5] = 0xB2,     // BankA 0x3b
		},
		/* color */
		{
			.contrast[0] 		= 0xa0, .contrast[1] 		= 0x9c, .contrast[2] 		= 0x90, .contrast[3] 		= 0x95, .contrast[4] 		= 0x90, .contrast[5] 		= 0x8a,
			.h_peaking[0] 		= 0x0f, .h_peaking[1] 		= 0x0f, .h_peaking[2] 		= 0x0f, .h_peaking[3] 		= 0x0f, .h_peaking[4] 		= 0x0f, .h_peaking[5] 		= 0x0f,
			.c_filter[0]		= 0x82, .c_filter[1] 		= 0x82, .c_filter[2]	 	= 0x92, .c_filter[3] 		= 0x92, .c_filter[4] 		= 0xa2, .c_filter[5] 		= 0xb2,

			.hue[0] 			= 0xff, .hue[1] 			= 0xff, .hue[2] 			= 0xff, .hue[3] 			= 0xff, .hue[4] 			= 0xff, .hue[5] 			= 0xff,
			.u_gain[0] 			= 0x70, .u_gain[1] 			= 0x70, .u_gain[2] 			= 0x64, .u_gain[3] 			= 0x5c, .u_gain[4] 			= 0x5c, .u_gain[5] 			= 0x5c,
			.v_gain[0] 			= 0xd8, .v_gain[1] 			= 0xd8, .v_gain[2] 			= 0xcc, .v_gain[3] 			= 0xbc, .v_gain[4] 			= 0xd0, .v_gain[5] 			= 0xd0,
			.u_offset[0] 		= 0xfc, .u_offset[1] 		= 0xfc, .u_offset[2] 		= 0xfc, .u_offset[3] 		= 0xfc, .u_offset[4] 		= 0xfc, .u_offset[5] 		= 0xfc,
			.v_offset[0] 		= 0xfa, .v_offset[1] 		= 0xfa, .v_offset[2] 		= 0xfa, .v_offset[3] 		= 0xfa, .v_offset[4] 		= 0xfa, .v_offset[5] 		= 0xfa,

			.black_level[0] 	= 0x8c, .black_level[1] 	= 0x8a, .black_level[2] 	= 0x8c, .black_level[3] 	= 0x8d, .black_level[4] 	= 0x91, .black_level[5] 	= 0x94,
			.acc_ref[0]			= 0x57, .acc_ref[1]			= 0x57, .acc_ref[2]			= 0x57, .acc_ref[3]			= 0x57, .acc_ref[4]			= 0x57, .acc_ref[5]			= 0x57,
			.cti_delay[0]		= 0x80, .cti_delay[1]		= 0x80, .cti_delay[2]		= 0x80, .cti_delay[3]		= 0x80, .cti_delay[4]		= 0x80, .cti_delay[5]		= 0x80,
			.sub_saturation[0] 	= 0xe0, .sub_saturation[1] 	= 0xe0, .sub_saturation[2] 	= 0xd0, .sub_saturation[3] 	= 0xe0, .sub_saturation[4] 	= 0xe4, .sub_saturation[5] 	= 0xc0,

			.burst_dec_a[0] 	= 0x2a, .burst_dec_a[1] 	= 0x2a, .burst_dec_a[2] 	= 0x2a, .burst_dec_a[3] 	= 0x2a, .burst_dec_a[4] 	= 0x2a, .burst_dec_a[5] 	= 0x2a,
			.burst_dec_b[0] 	= 0x00, .burst_dec_b[1] 	= 0x00, .burst_dec_b[2] 	= 0x00, .burst_dec_b[3] 	= 0x00, .burst_dec_b[4] 	= 0x00, .burst_dec_b[5] 	= 0x00,
			.burst_dec_c[0] 	= 0x50, .burst_dec_c[1] 	= 0x50, .burst_dec_c[2] 	= 0x50, .burst_dec_c[3] 	= 0x50, .burst_dec_c[4] 	= 0x50, .burst_dec_c[5] 	= 0x50,

			.c_option[0] 		= 0x80, .c_option[1] 		= 0x80, .c_option[2] 		= 0x80, .c_option[3] 		= 0x90, .c_option[4] 		= 0x90, .c_option[5] 		= 0x90,

			.y_filter_b[0]		= 0x10, .y_filter_b[1]		= 0x10, .y_filter_b[2]		= 0x10, .y_filter_b[3]		= 0x10, .y_filter_b[4]		= 0x10, .y_filter_b[5]		= 0x10,
			.y_filter_b_sel[0]	= 0x1e,	.y_filter_b_sel[1]	= 0x1e,	.y_filter_b_sel[2]	= 0x1e, .y_filter_b_sel[3]	= 0x1e, .y_filter_b_sel[4]	= 0x1e, .y_filter_b_sel[5]	= 0x1e,
		},
		/* timing_a */
		{
			.h_delay_a[0] = 0x84, .h_delay_a[1] = 0x84, .h_delay_a[2] = 0x84, .h_delay_a[3] = 0x83, .h_delay_a[4] = 0x83, .h_delay_a[5] = 0x83,
			.h_delay_b[0] = 0x10, .h_delay_b[1] = 0x10, .h_delay_b[2] = 0x10, .h_delay_b[3] = 0x10, .h_delay_b[4] = 0x10, .h_delay_b[5] = 0x10,
			.h_delay_c[0] = 0x02, .h_delay_c[1] = 0x02, .h_delay_c[2] = 0x02, .h_delay_c[3] = 0x02, .h_delay_c[4] = 0x02, .h_delay_c[5] = 0x02,
			.y_delay[0]   = 0x05, .y_delay[1]   = 0x05, .y_delay[2]   = 0x05, .y_delay[3]   = 0x05, .y_delay[4]   = 0x05, .y_delay[5] =   0x05,

		},
		/* clk */
		{
			.clk_adc[0] = 0x05, .clk_adc[1] = 0x05, .clk_adc[2] = 0x05, .clk_adc[3] = 0x05, .clk_adc[4] = 0x05, .clk_adc[5] = 0x05,
			.clk_dec[0] = 0x44, .clk_dec[1] = 0x44, .clk_dec[2] = 0x44, .clk_dec[3] = 0x44, .clk_dec[4] = 0x44, .clk_dec[5] = 0x44,
		},
		/* timing_b */
		{
	/*B9 0x96*/	.h_scaler1[0]  = 0x00, .h_scaler1[1]   = 0x00, .h_scaler1[2]   = 0x00, .h_scaler1[3]   = 0x00, .h_scaler1[4]   = 0x00, .h_scaler1[5]   = 0x00,
	/*B9 0x97*/	.h_scaler2[0]  = 0x00, .h_scaler2[1]   = 0x00, .h_scaler2[2]   = 0x00, .h_scaler2[3]   = 0x00, .h_scaler2[4]   = 0x00, .h_scaler2[5]   = 0x00,
	/*B9 0x98*/	.h_scaler3[0]  = 0x00, .h_scaler3[1]   = 0x00, .h_scaler3[2]   = 0x00, .h_scaler3[3]   = 0x00, .h_scaler3[4]   = 0x00, .h_scaler3[5]   = 0x00,
	/*B9 0x99*/	.h_scaler4[0]  = 0x00, .h_scaler4[1]   = 0x00, .h_scaler4[2]   = 0x00, .h_scaler4[3]   = 0x00, .h_scaler4[4]   = 0x00, .h_scaler4[5]   = 0x00,
	/*B9 0x9a*/	.h_scaler5[0]  = 0x00, .h_scaler5[1]   = 0x00, .h_scaler5[2]   = 0x00, .h_scaler5[3]   = 0x00, .h_scaler5[4]   = 0x00, .h_scaler5[5]   = 0x00,
	/*B9 0x9b*/	.h_scaler6[0]  = 0x00, .h_scaler6[1]   = 0x00, .h_scaler6[2]   = 0x00, .h_scaler6[3]   = 0x00, .h_scaler6[4]   = 0x00, .h_scaler6[5]   = 0x00,
	/*B9 0x9c*/	.h_scaler7[0]  = 0x00, .h_scaler7[1]   = 0x00, .h_scaler7[2]   = 0x00, .h_scaler7[3]   = 0x00, .h_scaler7[4]   = 0x00, .h_scaler7[5]   = 0x00,
	/*B9 0x9d*/	.h_scaler8[0]  = 0x00, .h_scaler8[1]   = 0x00, .h_scaler8[2]   = 0x00, .h_scaler8[3]   = 0x00, .h_scaler8[4]   = 0x00, .h_scaler8[5]   = 0x00,
	/*B9 0x9e*/	.h_scaler9[0]  = 0x00, .h_scaler9[1]   = 0x00, .h_scaler9[2]   = 0x00, .h_scaler9[3]   = 0x00, .h_scaler9[4]   = 0x00, .h_scaler9[5]   = 0x00,


	/*B9 0x40*/	.pn_auto[0]    	= 0x00, .pn_auto[1]		= 0x00, .pn_auto[2]    	= 0x00, .pn_auto[3]    	= 0x00, .pn_auto[4]    	= 0x00, .pn_auto[5]    	= 0x00,

	/*B5 0x90*/	.comb_mode[0]   = 0x01, .comb_mode[1]	= 0x01, .comb_mode[2]   = 0x01, .comb_mode[3]   = 0x01, .comb_mode[4]  	= 0x01, .comb_mode[5]   = 0x01,
	/*B9 0xb9*/	.h_pll_op_a[0]  = 0x72, .h_pll_op_a[1]  = 0x72, .h_pll_op_a[2]  = 0x72, .h_pll_op_a[3]  = 0x72, .h_pll_op_a[4]  = 0x72, .h_pll_op_a[5]  = 0x72,
	/*B9 0x57*/	.mem_path[0]	= 0x00, .mem_path[1]	= 0x00, .mem_path[2]	= 0x00, .mem_path[3]	= 0x00, .mem_path[4]	= 0x00, .mem_path[5]	= 0x00,
			.fsc_lock_speed[0] = 0xdc, .fsc_lock_speed[1] = 0xdc, .fsc_lock_speed[2] = 0xdc, .fsc_lock_speed[3] = 0xdc, .fsc_lock_speed[4] = 0xdc, .fsc_lock_speed[5] = 0xdc,

	/*B0 0x81*/	.format_set1[0] = 0x0e, .format_set1[1] = 0x0e, .format_set1[2] = 0x0e, .format_set1[3] = 0x0e, .format_set1[4] = 0x0e, .format_set1[5] = 0x0e,
	/*B0 0x85*/	.format_set2[0] = 0x00, .format_set2[1] = 0x00, .format_set2[2] = 0x00, .format_set2[3] = 0x00, .format_set2[4] = 0x00, .format_set2[5] = 0x00,

	/*B0 0x64*/ .v_delay[0]     = 0x80, .v_delay[1]     = 0x80, .v_delay[2]     = 0x80, .v_delay[3]     = 0x80, .v_delay[4]     = 0x80, .v_delay[5]     = 0x80,
		},
	},

	[ AHD30_5M_12_5P ] = { /* o */
	/* base */
		{
			.eq_bypass[0] 	= 0x62, .eq_bypass[1] 	= 0x22, .eq_bypass[2] 	= 0x22, .eq_bypass[3] 	= 0x22, .eq_bypass[4] 	= 0x22, .eq_bypass[5] 	= 0x22,    // Bank5 0x30
			.eq_band_sel[0] = 0x77, .eq_band_sel[1] = 0x77, .eq_band_sel[2] = 0x77, .eq_band_sel[3] = 0x77, .eq_band_sel[4] = 0x57, .eq_band_sel[5] = 0x57,    // BankA 0x31
			.eq_gain_sel[0] = 0x78, .eq_gain_sel[1] = 0x7b, .eq_gain_sel[2] = 0x7f, .eq_gain_sel[3] = 0x7f, .eq_gain_sel[4] = 0x7f, .eq_gain_sel[5] = 0x7f,    // BankA 0x32
			.deq_a_on[0] 	= 0x00, .deq_a_on[1] 	= 0x01, .deq_a_on[2] 	= 0x01, .deq_a_on[3] 	= 0x01, .deq_a_on[4] 	= 0x01, .deq_a_on[5] 	= 0x01,    // BankA 0x33
			.deq_a_sel[0] 	= 0x00, .deq_a_sel[1] 	= 0x91, .deq_a_sel[2] 	= 0x87, .deq_a_sel[3] 	= 0x89, .deq_a_sel[4] 	= 0x93, .deq_a_sel[5] 	= 0x94,    // BankA 0x34
			.deq_b_sel[0] 	= 0x00, .deq_b_sel[1] 	= 0x00, .deq_b_sel[2] 	= 0x00, .deq_b_sel[3] 	= 0x00, .deq_b_sel[4] 	= 0x00, .deq_b_sel[5] 	= 0x00,    // BankA 0x35
		},
		/* coeff */
		{
			.deqA_01[0] = 0xAC, .deqA_01[1] = 0xAC, .deqA_01[2] = 0xAC, .deqA_01[3] = 0xAC, .deqA_01[4] = 0xAC, .deqA_01[5] = 0xAC,		// BankA 0x30
			.deqA_02[0] = 0x78, .deqA_02[1] = 0x78, .deqA_02[2] = 0x78, .deqA_02[3] = 0x78, .deqA_02[4] = 0x78, .deqA_02[5] = 0x78,		// BankA 0x31
			.deqA_03[0] = 0x17, .deqA_03[1] = 0x17, .deqA_03[2] = 0x17, .deqA_03[3] = 0x17, .deqA_03[4] = 0x17, .deqA_03[5] = 0x17,		// BankA 0x32
			.deqA_04[0] = 0xC1, .deqA_04[1] = 0xC1, .deqA_04[2] = 0xC1, .deqA_04[3] = 0xC1, .deqA_04[4] = 0xC1, .deqA_04[5] = 0xC1,     // BankA 0x33
			.deqA_05[0] = 0x40, .deqA_05[1] = 0x40, .deqA_05[2] = 0x40, .deqA_05[3] = 0x40, .deqA_05[4] = 0x40, .deqA_05[5] = 0x40,     // BankA 0x34
			.deqA_06[0] = 0x00, .deqA_06[1] = 0x00, .deqA_06[2] = 0x00, .deqA_06[3] = 0x00, .deqA_06[4] = 0x00, .deqA_06[5] = 0x00,     // BankA 0x35
			.deqA_07[0] = 0xC3, .deqA_07[1] = 0xC3, .deqA_07[2] = 0xC3, .deqA_07[3] = 0xC3, .deqA_07[4] = 0xC3, .deqA_07[5] = 0xC3,     // BankA 0x36
			.deqA_08[0] = 0x0A, .deqA_08[1] = 0x0A, .deqA_08[2] = 0x0A, .deqA_08[3] = 0x0A, .deqA_08[4] = 0x0A, .deqA_08[5] = 0x0A,     // BankA 0x37
			.deqA_09[0] = 0x00, .deqA_09[1] = 0x00, .deqA_09[2] = 0x00, .deqA_09[3] = 0x00, .deqA_09[4] = 0x00, .deqA_09[5] = 0x00,     // BankA 0x38
			.deqA_10[0] = 0x02, .deqA_10[1] = 0x02, .deqA_10[2] = 0x02, .deqA_10[3] = 0x02, .deqA_10[4] = 0x02, .deqA_10[5] = 0x02,     // BankA 0x39
			.deqA_11[0] = 0x00, .deqA_11[1] = 0x00, .deqA_11[2] = 0x00, .deqA_11[3] = 0x00, .deqA_11[4] = 0x00, .deqA_11[5] = 0x00,     // BankA 0x3a
			.deqA_12[0] = 0xB2, .deqA_12[1] = 0xB2, .deqA_12[2] = 0xB2, .deqA_12[3] = 0xB2, .deqA_12[4] = 0xB2, .deqA_12[5] = 0xB2,     // BankA 0x3b
		},
		/* color */
		{
			.contrast[0] 		= 0x86, .contrast[1] 		= 0x82, .contrast[2] 		= 0x82, .contrast[3] 		= 0x7e, .contrast[4] 		= 0x7c, .contrast[5] 		= 0x77,
			.h_peaking[0] 		= 0x0f, .h_peaking[1] 		= 0x0f, .h_peaking[2] 		= 0x0f, .h_peaking[3] 		= 0x0f, .h_peaking[4] 		= 0x0f, .h_peaking[5] 		= 0x0f,
			.c_filter[0]		= 0x82, .c_filter[1] 		= 0x82, .c_filter[2]	 	= 0x92, .c_filter[3] 		= 0x92, .c_filter[4] 		= 0xa2, .c_filter[5] 		= 0xb2,

			.hue[0] 			= 0x00, .hue[1] 			= 0x00, .hue[2] 			= 0x00, .hue[3] 			= 0x00, .hue[4] 			= 0x00, .hue[5] 			= 0x00,
			.u_gain[0] 			= 0x10, .u_gain[1] 			= 0x10, .u_gain[2] 			= 0x04, .u_gain[3] 			= 0xfc, .u_gain[4] 			= 0xfc, .u_gain[5] 			= 0xfc,
			.v_gain[0] 			= 0x10, .v_gain[1] 			= 0x10, .v_gain[2] 			= 0x04, .v_gain[3] 			= 0xf4, .v_gain[4] 			= 0x08, .v_gain[5] 			= 0x08,
			.u_offset[0] 		= 0xfb, .u_offset[1] 		= 0xfb, .u_offset[2] 		= 0xfb, .u_offset[3] 		= 0xfb, .u_offset[4] 		= 0xfb, .u_offset[5] 		= 0xfe,
			.v_offset[0] 		= 0xf8, .v_offset[1] 		= 0xf8, .v_offset[2] 		= 0xf8, .v_offset[3] 		= 0xf8, .v_offset[4] 		= 0xf8, .v_offset[5] 		= 0xfb,

			.black_level[0] 	= 0x80, .black_level[1] 	= 0x81, .black_level[2] 	= 0x81, .black_level[3] 	= 0x83, .black_level[4] 	= 0x85, .black_level[5] 	= 0x87,
			.acc_ref[0]			= 0x57, .acc_ref[1]			= 0x57, .acc_ref[2]			= 0x57, .acc_ref[3]			= 0x57, .acc_ref[4]			= 0x57, .acc_ref[5]			= 0x57,
			.cti_delay[0]		= 0x80, .cti_delay[1]		= 0x80, .cti_delay[2]		= 0x80, .cti_delay[3]		= 0x80, .cti_delay[4]		= 0x80, .cti_delay[5]		= 0x80,
			.sub_saturation[0] 	= 0xa8, .sub_saturation[1] 	= 0xa8, .sub_saturation[2] 	= 0xa8, .sub_saturation[3] 	= 0xa8, .sub_saturation[4] 	= 0x90, .sub_saturation[5] 	= 0x90,

			.burst_dec_a[0] 	= 0x2a, .burst_dec_a[1] 	= 0x2a, .burst_dec_a[2] 	= 0x2a, .burst_dec_a[3] 	= 0x2a, .burst_dec_a[4] 	= 0x2a, .burst_dec_a[5] 	= 0x2a,
			.burst_dec_b[0] 	= 0x00, .burst_dec_b[1] 	= 0x00, .burst_dec_b[2] 	= 0x00, .burst_dec_b[3] 	= 0x00, .burst_dec_b[4] 	= 0x00, .burst_dec_b[5] 	= 0x00,
			.burst_dec_c[0] 	= 0x30, .burst_dec_c[1] 	= 0x30, .burst_dec_c[2] 	= 0x30, .burst_dec_c[3] 	= 0x30, .burst_dec_c[4] 	= 0x30, .burst_dec_c[5] 	= 0x30,

			.c_option[0] 		= 0x80, .c_option[1] 		= 0x80, .c_option[2] 		= 0x90, .c_option[3] 		= 0x90, .c_option[4] 		= 0x90, .c_option[5] 		= 0xa0,

			.y_filter_b[0]		= 0x10, .y_filter_b[1]		= 0x10, .y_filter_b[2]		= 0x10, .y_filter_b[3]		= 0x10, .y_filter_b[4]		= 0x10, .y_filter_b[5]		= 0x10,
			.y_filter_b_sel[0]	= 0x1e,	.y_filter_b_sel[1]	= 0x1e,	.y_filter_b_sel[2]	= 0x1e, .y_filter_b_sel[3]	= 0x1e, .y_filter_b_sel[4]	= 0x1e, .y_filter_b_sel[5]	= 0x1e,
		},
		/* timing_a */
		{
			.h_delay_a[0] = 0x80, .h_delay_a[1] = 0x80, .h_delay_a[2] = 0x80, .h_delay_a[3] = 0x80, .h_delay_a[4] = 0x80, .h_delay_a[5] = 0x80,
			.h_delay_b[0] = 0x10, .h_delay_b[1] = 0x10, .h_delay_b[2] = 0x10, .h_delay_b[3] = 0x10, .h_delay_b[4] = 0x10, .h_delay_b[5] = 0x10,
			.h_delay_c[0] = 0x03, .h_delay_c[1] = 0x03, .h_delay_c[2] = 0x03, .h_delay_c[3] = 0x03, .h_delay_c[4] = 0x03, .h_delay_c[5] = 0x03,
			.y_delay[0]   = 0x05, .y_delay[1]   = 0x03, .y_delay[2]   = 0x03, .y_delay[3]   = 0x03, .y_delay[4]   = 0x03, .y_delay[5] =   0x03,

		},
		/* clk */
		{
			.clk_adc[0] = 0x02, .clk_adc[1] = 0x02, .clk_adc[2] = 0x02, .clk_adc[3] = 0x02, .clk_adc[4] = 0x02, .clk_adc[5] = 0x02,
			.clk_dec[0] = 0x40, .clk_dec[1] = 0x40, .clk_dec[2] = 0x40, .clk_dec[3] = 0x40, .clk_dec[4] = 0x40, .clk_dec[5] = 0x40,
		},
		/* timing_b */
		{
	/*B9 0x96*/	.h_scaler1[0]  = 0x00, .h_scaler1[1]   = 0x00, .h_scaler1[2]   = 0x00, .h_scaler1[3]   = 0x00, .h_scaler1[4]   = 0x00, .h_scaler1[5]   = 0x00,
	/*B9 0x97*/	.h_scaler2[0]  = 0x00, .h_scaler2[1]   = 0x00, .h_scaler2[2]   = 0x00, .h_scaler2[3]   = 0x00, .h_scaler2[4]   = 0x00, .h_scaler2[5]   = 0x00,
	/*B9 0x98*/	.h_scaler3[0]  = 0x00, .h_scaler3[1]   = 0x00, .h_scaler3[2]   = 0x00, .h_scaler3[3]   = 0x00, .h_scaler3[4]   = 0x00, .h_scaler3[5]   = 0x00,
	/*B9 0x99*/	.h_scaler4[0]  = 0x00, .h_scaler4[1]   = 0x00, .h_scaler4[2]   = 0x00, .h_scaler4[3]   = 0x00, .h_scaler4[4]   = 0x00, .h_scaler4[5]   = 0x00,
	/*B9 0x9a*/	.h_scaler5[0]  = 0x00, .h_scaler5[1]   = 0x00, .h_scaler5[2]   = 0x00, .h_scaler5[3]   = 0x00, .h_scaler5[4]   = 0x00, .h_scaler5[5]   = 0x00,
	/*B9 0x9b*/	.h_scaler6[0]  = 0x00, .h_scaler6[1]   = 0x00, .h_scaler6[2]   = 0x00, .h_scaler6[3]   = 0x00, .h_scaler6[4]   = 0x00, .h_scaler6[5]   = 0x00,
	/*B9 0x9c*/	.h_scaler7[0]  = 0x00, .h_scaler7[1]   = 0x00, .h_scaler7[2]   = 0x00, .h_scaler7[3]   = 0x00, .h_scaler7[4]   = 0x00, .h_scaler7[5]   = 0x00,
	/*B9 0x9d*/	.h_scaler8[0]  = 0x00, .h_scaler8[1]   = 0x00, .h_scaler8[2]   = 0x00, .h_scaler8[3]   = 0x00, .h_scaler8[4]   = 0x00, .h_scaler8[5]   = 0x00,
	/*B9 0x9e*/	.h_scaler9[0]  = 0x00, .h_scaler9[1]   = 0x00, .h_scaler9[2]   = 0x00, .h_scaler9[3]   = 0x00, .h_scaler9[4]   = 0x00, .h_scaler9[5]   = 0x00,


	/*B9 0x40*/	.pn_auto[0]    	= 0x00, .pn_auto[1]		= 0x00, .pn_auto[2]    	= 0x00, .pn_auto[3]    	= 0x00, .pn_auto[4]    	= 0x00, .pn_auto[5]    	= 0x00,

	/*B5 0x90*/	.comb_mode[0]      = 0x01, .comb_mode[1]	  = 0x01, .comb_mode[2]      = 0x01, .comb_mode[3]      = 0x01, .comb_mode[4]  	   = 0x01, .comb_mode[5]      = 0x01,
	/*B9 0xb9*/	.h_pll_op_a[0]     = 0x72, .h_pll_op_a[1]     = 0x72, .h_pll_op_a[2]     = 0x72, .h_pll_op_a[3]     = 0x72, .h_pll_op_a[4]     = 0x72, .h_pll_op_a[5]     = 0x72,
	/*B9 0x57*/	.mem_path[0]	   = 0x00, .mem_path[1]	      = 0x00, .mem_path[2]	     = 0x00, .mem_path[3]	    = 0x00, .mem_path[4]	   = 0x00, .mem_path[5]	      = 0x00,
				.fsc_lock_speed[0] = 0xdc, .fsc_lock_speed[1] = 0xdc, .fsc_lock_speed[2] = 0xdc, .fsc_lock_speed[3] = 0xdc, .fsc_lock_speed[4] = 0xdc, .fsc_lock_speed[5] = 0xdc,

	/*B0 0x81*/	.format_set1[0] = 0x00, .format_set1[1] = 0x00, .format_set1[2] = 0x00, .format_set1[3] = 0x00, .format_set1[4] = 0x00, .format_set1[5] = 0x00,
	/*B0 0x85*/	.format_set2[0] = 0x05, .format_set2[1] = 0x05, .format_set2[2] = 0x05, .format_set2[3] = 0x05, .format_set2[4] = 0x05, .format_set2[5] = 0x05,

	/*B0 0x64*/ .v_delay[0]     = 0x20, .v_delay[1]     = 0x20, .v_delay[2]     = 0x20, .v_delay[3]     = 0x20, .v_delay[4]     = 0x20, .v_delay[5]     = 0x20,
		},
	},


	[ AHD30_5M_20P ] = { /* o */
	/* base */
		{
			.eq_bypass[0] 	= 0x22, .eq_bypass[1] 	= 0x22, .eq_bypass[2] 	= 0x22, .eq_bypass[3] 	= 0x22, .eq_bypass[4] 	= 0x22, .eq_bypass[5] 	= 0x22,    // Bank5 0x30
			.eq_band_sel[0] = 0x77, .eq_band_sel[1] = 0x77, .eq_band_sel[2] = 0x77, .eq_band_sel[3] = 0x67, .eq_band_sel[4] = 0x57, .eq_band_sel[5] = 0x57,    // BankA 0x31
			.eq_gain_sel[0] = 0x78, .eq_gain_sel[1] = 0x7b, .eq_gain_sel[2] = 0x7f, .eq_gain_sel[3] = 0x7e, .eq_gain_sel[4] = 0x7f, .eq_gain_sel[5] = 0x7f,    // BankA 0x32
			.deq_a_on[0] 	= 0x00, .deq_a_on[1] 	= 0x01, .deq_a_on[2] 	= 0x01, .deq_a_on[3] 	= 0x01, .deq_a_on[4] 	= 0x01, .deq_a_on[5] 	= 0x01,    // BankA 0x33
			.deq_a_sel[0] 	= 0x00, .deq_a_sel[1] 	= 0x91, .deq_a_sel[2] 	= 0x93, .deq_a_sel[3] 	= 0x98, .deq_a_sel[4] 	= 0x98, .deq_a_sel[5] 	= 0x98,    // BankA 0x34
			.deq_b_sel[0] 	= 0x00, .deq_b_sel[1] 	= 0x00, .deq_b_sel[2] 	= 0x00, .deq_b_sel[3] 	= 0x20, .deq_b_sel[4] 	= 0x00, .deq_b_sel[5] 	= 0x00,    // BankA 0x35
		},
		/* coeff */
		{
			.deqA_01[0] = 0xAC, .deqA_01[1] = 0xAC, .deqA_01[2] = 0xAC, .deqA_01[3] = 0xAC, .deqA_01[4] = 0xAC, .deqA_01[5] = 0xAC,		// BankA 0x30
			.deqA_02[0] = 0x78, .deqA_02[1] = 0x78, .deqA_02[2] = 0x78, .deqA_02[3] = 0x78, .deqA_02[4] = 0x78, .deqA_02[5] = 0x78,		// BankA 0x31
			.deqA_03[0] = 0x17, .deqA_03[1] = 0x17, .deqA_03[2] = 0x17, .deqA_03[3] = 0x17, .deqA_03[4] = 0x17, .deqA_03[5] = 0x17,		// BankA 0x32
			.deqA_04[0] = 0xC1, .deqA_04[1] = 0xC1, .deqA_04[2] = 0xC1, .deqA_04[3] = 0xC1, .deqA_04[4] = 0xC1, .deqA_04[5] = 0xC1,     // BankA 0x33
			.deqA_05[0] = 0x40, .deqA_05[1] = 0x40, .deqA_05[2] = 0x40, .deqA_05[3] = 0x40, .deqA_05[4] = 0x40, .deqA_05[5] = 0x40,     // BankA 0x34
			.deqA_06[0] = 0x00, .deqA_06[1] = 0x00, .deqA_06[2] = 0x00, .deqA_06[3] = 0x00, .deqA_06[4] = 0x00, .deqA_06[5] = 0x00,     // BankA 0x35
			.deqA_07[0] = 0xC3, .deqA_07[1] = 0xC3, .deqA_07[2] = 0xC3, .deqA_07[3] = 0xC3, .deqA_07[4] = 0xC3, .deqA_07[5] = 0xC3,     // BankA 0x36
			.deqA_08[0] = 0x0A, .deqA_08[1] = 0x0A, .deqA_08[2] = 0x0A, .deqA_08[3] = 0x0A, .deqA_08[4] = 0x0A, .deqA_08[5] = 0x0A,     // BankA 0x37
			.deqA_09[0] = 0x00, .deqA_09[1] = 0x00, .deqA_09[2] = 0x00, .deqA_09[3] = 0x00, .deqA_09[4] = 0x00, .deqA_09[5] = 0x00,     // BankA 0x38
			.deqA_10[0] = 0x02, .deqA_10[1] = 0x02, .deqA_10[2] = 0x02, .deqA_10[3] = 0x02, .deqA_10[4] = 0x02, .deqA_10[5] = 0x02,     // BankA 0x39
			.deqA_11[0] = 0x00, .deqA_11[1] = 0x00, .deqA_11[2] = 0x00, .deqA_11[3] = 0x00, .deqA_11[4] = 0x00, .deqA_11[5] = 0x00,     // BankA 0x3a
			.deqA_12[0] = 0xB2, .deqA_12[1] = 0xB2, .deqA_12[2] = 0xB2, .deqA_12[3] = 0xB2, .deqA_12[4] = 0xB2, .deqA_12[5] = 0xB2,     // BankA 0x3b
		},
		/* color */
		{
			.contrast[0] 		= 0x8b, .contrast[1] 		= 0x87, .contrast[2] 		= 0x8b, .contrast[3] 		= 0x80, .contrast[4] 		= 0x7b, .contrast[5] 		= 0x75,
			.h_peaking[0] 		= 0x0f, .h_peaking[1] 		= 0x0f, .h_peaking[2] 		= 0x0f, .h_peaking[3] 		= 0x0f, .h_peaking[4] 		= 0x0f, .h_peaking[5] 		= 0x0f,
			.c_filter[0]		= 0x82, .c_filter[1] 		= 0x82, .c_filter[2]	 	= 0x92, .c_filter[3] 		= 0x92, .c_filter[4] 		= 0xa2, .c_filter[5] 		= 0xb2,

			.hue[0] 			= 0xfe, .hue[1] 			= 0xfe, .hue[2] 			= 0xfe, .hue[3] 			= 0xfe, .hue[4] 			= 0xfe, .hue[5] 			= 0xfe,
			.u_gain[0] 			= 0x70, .u_gain[1] 			= 0x70, .u_gain[2] 			= 0x64, .u_gain[3] 			= 0x5c, .u_gain[4] 			= 0x5c, .u_gain[5] 			= 0x5c,
			.v_gain[0] 			= 0x10, .v_gain[1] 			= 0x10, .v_gain[2] 			= 0x04, .v_gain[3] 			= 0xf4, .v_gain[4] 			= 0x08, .v_gain[5] 			= 0x08,
			.u_offset[0] 		= 0xfc, .u_offset[1] 		= 0xfc, .u_offset[2] 		= 0xfc, .u_offset[3] 		= 0xfc, .u_offset[4] 		= 0xfc, .u_offset[5] 		= 0xfc,
			.v_offset[0] 		= 0xf7, .v_offset[1] 		= 0xf7, .v_offset[2] 		= 0xf7, .v_offset[3] 		= 0xf7, .v_offset[4] 		= 0xf7, .v_offset[5] 		= 0xf7,

			.black_level[0] 	= 0x80, .black_level[1] 	= 0x80, .black_level[2] 	= 0x80, .black_level[3] 	= 0x80, .black_level[4] 	= 0x80, .black_level[5] 	= 0x80,
			.acc_ref[0]			= 0x57, .acc_ref[1]			= 0x57, .acc_ref[2]			= 0x57, .acc_ref[3]			= 0x57, .acc_ref[4]			= 0x57, .acc_ref[5]			= 0x57,
			.cti_delay[0]		= 0x80, .cti_delay[1]		= 0x80, .cti_delay[2]		= 0x80, .cti_delay[3]		= 0x80, .cti_delay[4]		= 0x80, .cti_delay[5]		= 0x80,
			.sub_saturation[0] 	= 0xe8, .sub_saturation[1] 	= 0xe8, .sub_saturation[2] 	= 0xd8, .sub_saturation[3] 	= 0xf8, .sub_saturation[4] 	= 0xe8, .sub_saturation[5] 	= 0x90,

			.burst_dec_a[0] 	= 0x2a, .burst_dec_a[1] 	= 0x2a, .burst_dec_a[2] 	= 0x2a, .burst_dec_a[3] 	= 0x2a, .burst_dec_a[4] 	= 0x2a, .burst_dec_a[5] 	= 0x2a,
			.burst_dec_b[0] 	= 0x00, .burst_dec_b[1] 	= 0x00, .burst_dec_b[2] 	= 0x00, .burst_dec_b[3] 	= 0x00, .burst_dec_b[4] 	= 0x00, .burst_dec_b[5] 	= 0x00,
			.burst_dec_c[0] 	= 0x40, .burst_dec_c[1] 	= 0x40, .burst_dec_c[2] 	= 0x40, .burst_dec_c[3] 	= 0x40, .burst_dec_c[4] 	= 0x40, .burst_dec_c[5] 	= 0x40,

			.c_option[0] 		= 0x80, .c_option[1] 		= 0x80, .c_option[2] 		= 0xa0, .c_option[3] 		= 0x90, .c_option[4] 		= 0x90, .c_option[5] 		= 0x90,

			.y_filter_b[0]		= 0x10, .y_filter_b[1]		= 0x10, .y_filter_b[2]		= 0x10, .y_filter_b[3]		= 0x10, .y_filter_b[4]		= 0x10, .y_filter_b[5]		= 0x10,
			.y_filter_b_sel[0]	= 0x1e,	.y_filter_b_sel[1]	= 0x1e,	.y_filter_b_sel[2]	= 0x1e, .y_filter_b_sel[3]	= 0x1e, .y_filter_b_sel[4]	= 0x1e, .y_filter_b_sel[5]	= 0x1e,
		},
		/* timing_a */
		{
			.h_delay_a[0] = 0x80, .h_delay_a[1] = 0x80, .h_delay_a[2] = 0x80, .h_delay_a[3] = 0x7f, .h_delay_a[4] = 0x7f, .h_delay_a[5] = 0x7f,
			.h_delay_b[0] = 0x10, .h_delay_b[1] = 0x10, .h_delay_b[2] = 0x10, .h_delay_b[3] = 0x10, .h_delay_b[4] = 0x10, .h_delay_b[5] = 0x10,
			.h_delay_c[0] = 0x02, .h_delay_c[1] = 0x02, .h_delay_c[2] = 0x02, .h_delay_c[3] = 0x02, .h_delay_c[4] = 0x02, .h_delay_c[5] = 0x02,
			.y_delay[0]   = 0x05, .y_delay[1]   = 0x05, .y_delay[2]   = 0x05, .y_delay[3]   = 0x05, .y_delay[4]   = 0x05, .y_delay[5] =   0x05,

		},
		/* clk */
		{
			.clk_adc[0] = 0x05, .clk_adc[1] = 0x05, .clk_adc[2] = 0x05, .clk_adc[3] = 0x05, .clk_adc[4] = 0x05, .clk_adc[5] = 0x05,
			.clk_dec[0] = 0x44, .clk_dec[1] = 0x44, .clk_dec[2] = 0x44, .clk_dec[3] = 0x44, .clk_dec[4] = 0x44, .clk_dec[5] = 0x44,
		},
		/* timing_b */
		{
	/*B9 0x96*/	.h_scaler1[0]  = 0x00, .h_scaler1[1]   = 0x00, .h_scaler1[2]   = 0x00, .h_scaler1[3]   = 0x00, .h_scaler1[4]   = 0x00, .h_scaler1[5]   = 0x00,
	/*B9 0x97*/	.h_scaler2[0]  = 0x00, .h_scaler2[1]   = 0x00, .h_scaler2[2]   = 0x00, .h_scaler2[3]   = 0x00, .h_scaler2[4]   = 0x00, .h_scaler2[5]   = 0x00,
	/*B9 0x98*/	.h_scaler3[0]  = 0x00, .h_scaler3[1]   = 0x00, .h_scaler3[2]   = 0x00, .h_scaler3[3]   = 0x00, .h_scaler3[4]   = 0x00, .h_scaler3[5]   = 0x00,
	/*B9 0x99*/	.h_scaler4[0]  = 0x00, .h_scaler4[1]   = 0x00, .h_scaler4[2]   = 0x00, .h_scaler4[3]   = 0x00, .h_scaler4[4]   = 0x00, .h_scaler4[5]   = 0x00,
	/*B9 0x9a*/	.h_scaler5[0]  = 0x00, .h_scaler5[1]   = 0x00, .h_scaler5[2]   = 0x00, .h_scaler5[3]   = 0x00, .h_scaler5[4]   = 0x00, .h_scaler5[5]   = 0x00,
	/*B9 0x9b*/	.h_scaler6[0]  = 0x00, .h_scaler6[1]   = 0x00, .h_scaler6[2]   = 0x00, .h_scaler6[3]   = 0x00, .h_scaler6[4]   = 0x00, .h_scaler6[5]   = 0x00,
	/*B9 0x9c*/	.h_scaler7[0]  = 0x00, .h_scaler7[1]   = 0x00, .h_scaler7[2]   = 0x00, .h_scaler7[3]   = 0x00, .h_scaler7[4]   = 0x00, .h_scaler7[5]   = 0x00,
	/*B9 0x9d*/	.h_scaler8[0]  = 0x00, .h_scaler8[1]   = 0x00, .h_scaler8[2]   = 0x00, .h_scaler8[3]   = 0x00, .h_scaler8[4]   = 0x00, .h_scaler8[5]   = 0x00,
	/*B9 0x9e*/	.h_scaler9[0]  = 0x00, .h_scaler9[1]   = 0x00, .h_scaler9[2]   = 0x00, .h_scaler9[3]   = 0x00, .h_scaler9[4]   = 0x00, .h_scaler9[5]   = 0x00,


	/*B9 0x40*/	.pn_auto[0]    	= 0x00, .pn_auto[1]		= 0x00, .pn_auto[2]    	= 0x00, .pn_auto[3]    	= 0x00, .pn_auto[4]    	= 0x00, .pn_auto[5]    	= 0x00,

	/*B5 0x90*/	.comb_mode[0]   = 0x01, .comb_mode[1]	= 0x01, .comb_mode[2]   = 0x01, .comb_mode[3]   = 0x01, .comb_mode[4]  	= 0x01, .comb_mode[5]   = 0x01,
	/*B9 0xb9*/	.h_pll_op_a[0]  = 0x72, .h_pll_op_a[1]  = 0x72, .h_pll_op_a[2]  = 0x72, .h_pll_op_a[3]  = 0x72, .h_pll_op_a[4]  = 0x72, .h_pll_op_a[5]  = 0x72,
	/*B9 0x57*/	.mem_path[0]	= 0x00, .mem_path[1]	= 0x00, .mem_path[2]	= 0x00, .mem_path[3]	= 0x00, .mem_path[4]	= 0x00, .mem_path[5]	= 0x00,
			.fsc_lock_speed[0] = 0xdc, .fsc_lock_speed[1] = 0xdc, .fsc_lock_speed[2] = 0xdc, .fsc_lock_speed[3] = 0xdc, .fsc_lock_speed[4] = 0xdc, .fsc_lock_speed[5] = 0xdc,

	/*B0 0x81*/	.format_set1[0] = 0x01, .format_set1[1] = 0x01, .format_set1[2] = 0x01, .format_set1[3] = 0x01, .format_set1[4] = 0x01, .format_set1[5] = 0x01,
	/*B0 0x85*/	.format_set2[0] = 0x05, .format_set2[1] = 0x05, .format_set2[2] = 0x05, .format_set2[3] = 0x05, .format_set2[4] = 0x05, .format_set2[5] = 0x05,

	/*B0 0x64*/ .v_delay[0]     = 0x80, .v_delay[1]     = 0x80, .v_delay[2]     = 0x80, .v_delay[3]     = 0x80, .v_delay[4]     = 0x80, .v_delay[5]     = 0x80,
		},
	},

	[ AHD30_5_3M_20P ] = { /* o */
	/* base */
		{
			.eq_bypass[0] 	= 0x22, .eq_bypass[1] 	= 0x22, .eq_bypass[2] 	= 0x22, .eq_bypass[3] 	= 0x22, .eq_bypass[4] 	= 0x22, .eq_bypass[5] 	= 0x22,    // Bank5 0x30
			.eq_band_sel[0] = 0x77, .eq_band_sel[1] = 0x77, .eq_band_sel[2] = 0x77, .eq_band_sel[3] = 0x67, .eq_band_sel[4] = 0x57, .eq_band_sel[5] = 0x57,    // BankA 0x31
			.eq_gain_sel[0] = 0x78, .eq_gain_sel[1] = 0x7b, .eq_gain_sel[2] = 0x7f, .eq_gain_sel[3] = 0x7e, .eq_gain_sel[4] = 0x7f, .eq_gain_sel[5] = 0x7f,    // BankA 0x32
			.deq_a_on[0] 	= 0x00, .deq_a_on[1] 	= 0x01, .deq_a_on[2] 	= 0x01, .deq_a_on[3] 	= 0x01, .deq_a_on[4] 	= 0x01, .deq_a_on[5] 	= 0x01,    // BankA 0x33
			.deq_a_sel[0] 	= 0x00, .deq_a_sel[1] 	= 0x91, .deq_a_sel[2] 	= 0x93, .deq_a_sel[3] 	= 0x98, .deq_a_sel[4] 	= 0x98, .deq_a_sel[5] 	= 0x98,    // BankA 0x34
			.deq_b_sel[0] 	= 0x00, .deq_b_sel[1] 	= 0x00, .deq_b_sel[2] 	= 0x00, .deq_b_sel[3] 	= 0x00, .deq_b_sel[4] 	= 0x00, .deq_b_sel[5] 	= 0x00,    // BankA 0x35
		},
		/* coeff */
		{
			.deqA_01[0] = 0xAC, .deqA_01[1] = 0xAC, .deqA_01[2] = 0xAC, .deqA_01[3] = 0xAC, .deqA_01[4] = 0xAC, .deqA_01[5] = 0xAC,		// BankA 0x30
			.deqA_02[0] = 0x78, .deqA_02[1] = 0x78, .deqA_02[2] = 0x78, .deqA_02[3] = 0x78, .deqA_02[4] = 0x78, .deqA_02[5] = 0x78,		// BankA 0x31
			.deqA_03[0] = 0x17, .deqA_03[1] = 0x17, .deqA_03[2] = 0x17, .deqA_03[3] = 0x17, .deqA_03[4] = 0x17, .deqA_03[5] = 0x17,		// BankA 0x32
			.deqA_04[0] = 0xC1, .deqA_04[1] = 0xC1, .deqA_04[2] = 0xC1, .deqA_04[3] = 0xC1, .deqA_04[4] = 0xC1, .deqA_04[5] = 0xC1,     // BankA 0x33
			.deqA_05[0] = 0x40, .deqA_05[1] = 0x40, .deqA_05[2] = 0x40, .deqA_05[3] = 0x40, .deqA_05[4] = 0x40, .deqA_05[5] = 0x40,     // BankA 0x34
			.deqA_06[0] = 0x00, .deqA_06[1] = 0x00, .deqA_06[2] = 0x00, .deqA_06[3] = 0x00, .deqA_06[4] = 0x00, .deqA_06[5] = 0x00,     // BankA 0x35
			.deqA_07[0] = 0xC3, .deqA_07[1] = 0xC3, .deqA_07[2] = 0xC3, .deqA_07[3] = 0xC3, .deqA_07[4] = 0xC3, .deqA_07[5] = 0xC3,     // BankA 0x36
			.deqA_08[0] = 0x0A, .deqA_08[1] = 0x0A, .deqA_08[2] = 0x0A, .deqA_08[3] = 0x0A, .deqA_08[4] = 0x0A, .deqA_08[5] = 0x0A,     // BankA 0x37
			.deqA_09[0] = 0x00, .deqA_09[1] = 0x00, .deqA_09[2] = 0x00, .deqA_09[3] = 0x00, .deqA_09[4] = 0x00, .deqA_09[5] = 0x00,     // BankA 0x38
			.deqA_10[0] = 0x02, .deqA_10[1] = 0x02, .deqA_10[2] = 0x02, .deqA_10[3] = 0x02, .deqA_10[4] = 0x02, .deqA_10[5] = 0x02,     // BankA 0x39
			.deqA_11[0] = 0x00, .deqA_11[1] = 0x00, .deqA_11[2] = 0x00, .deqA_11[3] = 0x00, .deqA_11[4] = 0x00, .deqA_11[5] = 0x00,     // BankA 0x3a
			.deqA_12[0] = 0xB2, .deqA_12[1] = 0xB2, .deqA_12[2] = 0xB2, .deqA_12[3] = 0xB2, .deqA_12[4] = 0xB2, .deqA_12[5] = 0xB2,     // BankA 0x3b
		},
		/* color */
		{
			.contrast[0] 		= 0x8b, .contrast[1] 		= 0x87, .contrast[2] 		= 0x8b, .contrast[3] 		= 0x80, .contrast[4] 		= 0x7b, .contrast[5] 		= 0x75,
			.h_peaking[0] 		= 0x0f, .h_peaking[1] 		= 0x0f, .h_peaking[2] 		= 0x0f, .h_peaking[3] 		= 0x0f, .h_peaking[4] 		= 0x0f, .h_peaking[5] 		= 0x0f,
			.c_filter[0]		= 0x82, .c_filter[1] 		= 0x82, .c_filter[2]	 	= 0x92, .c_filter[3] 		= 0x92, .c_filter[4] 		= 0xa2, .c_filter[5] 		= 0xb2,

			.hue[0] 			= 0xfe, .hue[1] 			= 0xfe, .hue[2] 			= 0xfe, .hue[3] 			= 0xfe, .hue[4] 			= 0xfe, .hue[5] 			= 0xfe,
			.u_gain[0] 			= 0x70, .u_gain[1] 			= 0x70, .u_gain[2] 			= 0x64, .u_gain[3] 			= 0x5c, .u_gain[4] 			= 0x5c, .u_gain[5] 			= 0x5c,
			.v_gain[0] 			= 0x10, .v_gain[1] 			= 0x10, .v_gain[2] 			= 0x04, .v_gain[3] 			= 0xf4, .v_gain[4] 			= 0x08, .v_gain[5] 			= 0x08,
			.u_offset[0] 		= 0xfc, .u_offset[1] 		= 0xfc, .u_offset[2] 		= 0xfc, .u_offset[3] 		= 0xfc, .u_offset[4] 		= 0xfc, .u_offset[5] 		= 0xfc,
			.v_offset[0] 		= 0xf7, .v_offset[1] 		= 0xf7, .v_offset[2] 		= 0xf7, .v_offset[3] 		= 0xf7, .v_offset[4] 		= 0xf7, .v_offset[5] 		= 0xf7,

			.black_level[0] 	= 0x80, .black_level[1] 	= 0x80, .black_level[2] 	= 0x80, .black_level[3] 	= 0x80, .black_level[4] 	= 0x80, .black_level[5] 	= 0x80,
			.acc_ref[0]			= 0x57, .acc_ref[1]			= 0x57, .acc_ref[2]			= 0x57, .acc_ref[3]			= 0x57, .acc_ref[4]			= 0x57, .acc_ref[5]			= 0x57,
			.cti_delay[0]		= 0x80, .cti_delay[1]		= 0x80, .cti_delay[2]		= 0x80, .cti_delay[3]		= 0x80, .cti_delay[4]		= 0x80, .cti_delay[5]		= 0x80,
			.sub_saturation[0] 	= 0xe8, .sub_saturation[1] 	= 0xe8, .sub_saturation[2] 	= 0xd8, .sub_saturation[3] 	= 0xf8, .sub_saturation[4] 	= 0xe8, .sub_saturation[5] 	= 0x90,

			.burst_dec_a[0] 	= 0x2a, .burst_dec_a[1] 	= 0x2a, .burst_dec_a[2] 	= 0x2a, .burst_dec_a[3] 	= 0x2a, .burst_dec_a[4] 	= 0x2a, .burst_dec_a[5] 	= 0x2a,
			.burst_dec_b[0] 	= 0x00, .burst_dec_b[1] 	= 0x00, .burst_dec_b[2] 	= 0x00, .burst_dec_b[3] 	= 0x00, .burst_dec_b[4] 	= 0x00, .burst_dec_b[5] 	= 0x00,
			.burst_dec_c[0] 	= 0x40, .burst_dec_c[1] 	= 0x40, .burst_dec_c[2] 	= 0x40, .burst_dec_c[3] 	= 0x40, .burst_dec_c[4] 	= 0x40, .burst_dec_c[5] 	= 0x40,

			.c_option[0] 		= 0x80, .c_option[1] 		= 0x80, .c_option[2] 		= 0xa0, .c_option[3] 		= 0x90, .c_option[4] 		= 0x90, .c_option[5] 		= 0x90,

			.y_filter_b[0]		= 0x10, .y_filter_b[1]		= 0x10, .y_filter_b[2]		= 0x10, .y_filter_b[3]		= 0x10, .y_filter_b[4]		= 0x10, .y_filter_b[5]		= 0x10,
			.y_filter_b_sel[0]	= 0x1e,	.y_filter_b_sel[1]	= 0x1e,	.y_filter_b_sel[2]	= 0x1e, .y_filter_b_sel[3]	= 0x1e, .y_filter_b_sel[4]	= 0x1e, .y_filter_b_sel[5]	= 0x1e,
		},
		/* timing_a */
		{
			.h_delay_a[0] = 0x80, .h_delay_a[1] = 0x80, .h_delay_a[2] = 0x80, .h_delay_a[3] = 0x7f, .h_delay_a[4] = 0x7f, .h_delay_a[5] = 0x7f,
			.h_delay_b[0] = 0x10, .h_delay_b[1] = 0x10, .h_delay_b[2] = 0x10, .h_delay_b[3] = 0x10, .h_delay_b[4] = 0x10, .h_delay_b[5] = 0x10,
			.h_delay_c[0] = 0x02, .h_delay_c[1] = 0x02, .h_delay_c[2] = 0x02, .h_delay_c[3] = 0x02, .h_delay_c[4] = 0x02, .h_delay_c[5] = 0x02,
			.y_delay[0]   = 0x05, .y_delay[1]   = 0x05, .y_delay[2]   = 0x05, .y_delay[3]   = 0x05, .y_delay[4]   = 0x05, .y_delay[5] =   0x05,

		},
		/* clk */
		{
			.clk_adc[0] = 0x05, .clk_adc[1] = 0x05, .clk_adc[2] = 0x05, .clk_adc[3] = 0x05, .clk_adc[4] = 0x05, .clk_adc[5] = 0x05,
			.clk_dec[0] = 0x44, .clk_dec[1] = 0x44, .clk_dec[2] = 0x44, .clk_dec[3] = 0x44, .clk_dec[4] = 0x44, .clk_dec[5] = 0x44,
		},
		/* timing_b */
		{
	/*B9 0x96*/	.h_scaler1[0]  = 0x00, .h_scaler1[1]   = 0x00, .h_scaler1[2]   = 0x00, .h_scaler1[3]   = 0x00, .h_scaler1[4]   = 0x00, .h_scaler1[5]   = 0x00,
	/*B9 0x97*/	.h_scaler2[0]  = 0x00, .h_scaler2[1]   = 0x00, .h_scaler2[2]   = 0x00, .h_scaler2[3]   = 0x00, .h_scaler2[4]   = 0x00, .h_scaler2[5]   = 0x00,
	/*B9 0x98*/	.h_scaler3[0]  = 0x00, .h_scaler3[1]   = 0x00, .h_scaler3[2]   = 0x00, .h_scaler3[3]   = 0x00, .h_scaler3[4]   = 0x00, .h_scaler3[5]   = 0x00,
	/*B9 0x99*/	.h_scaler4[0]  = 0x00, .h_scaler4[1]   = 0x00, .h_scaler4[2]   = 0x00, .h_scaler4[3]   = 0x00, .h_scaler4[4]   = 0x00, .h_scaler4[5]   = 0x00,
	/*B9 0x9a*/	.h_scaler5[0]  = 0x00, .h_scaler5[1]   = 0x00, .h_scaler5[2]   = 0x00, .h_scaler5[3]   = 0x00, .h_scaler5[4]   = 0x00, .h_scaler5[5]   = 0x00,
	/*B9 0x9b*/	.h_scaler6[0]  = 0x00, .h_scaler6[1]   = 0x00, .h_scaler6[2]   = 0x00, .h_scaler6[3]   = 0x00, .h_scaler6[4]   = 0x00, .h_scaler6[5]   = 0x00,
	/*B9 0x9c*/	.h_scaler7[0]  = 0x00, .h_scaler7[1]   = 0x00, .h_scaler7[2]   = 0x00, .h_scaler7[3]   = 0x00, .h_scaler7[4]   = 0x00, .h_scaler7[5]   = 0x00,
	/*B9 0x9d*/	.h_scaler8[0]  = 0x00, .h_scaler8[1]   = 0x00, .h_scaler8[2]   = 0x00, .h_scaler8[3]   = 0x00, .h_scaler8[4]   = 0x00, .h_scaler8[5]   = 0x00,
	/*B9 0x9e*/	.h_scaler9[0]  = 0x00, .h_scaler9[1]   = 0x00, .h_scaler9[2]   = 0x00, .h_scaler9[3]   = 0x00, .h_scaler9[4]   = 0x00, .h_scaler9[5]   = 0x00,


	/*B9 0x40*/	.pn_auto[0]    	= 0x00, .pn_auto[1]		= 0x00, .pn_auto[2]    	= 0x00, .pn_auto[3]    	= 0x00, .pn_auto[4]    	= 0x00, .pn_auto[5]    	= 0x00,

	/*B5 0x90*/	.comb_mode[0]   = 0x01, .comb_mode[1]	= 0x01, .comb_mode[2]   = 0x01, .comb_mode[3]   = 0x01, .comb_mode[4]  	= 0x01, .comb_mode[5]   = 0x01,
	/*B9 0xb9*/	.h_pll_op_a[0]  = 0x72, .h_pll_op_a[1]  = 0x72, .h_pll_op_a[2]  = 0x72, .h_pll_op_a[3]  = 0x72, .h_pll_op_a[4]  = 0x72, .h_pll_op_a[5]  = 0x72,
	/*B9 0x57*/	.mem_path[0]	= 0x00, .mem_path[1]	= 0x00, .mem_path[2]	= 0x00, .mem_path[3]	= 0x00, .mem_path[4]	= 0x00, .mem_path[5]	= 0x00,
			.fsc_lock_speed[0] = 0xdc, .fsc_lock_speed[1] = 0xdc, .fsc_lock_speed[2] = 0xdc, .fsc_lock_speed[3] = 0xdc, .fsc_lock_speed[4] = 0xdc, .fsc_lock_speed[5] = 0xdc,

	/*B0 0x81*/	.format_set1[0] = 0x01, .format_set1[1] = 0x01, .format_set1[2] = 0x01, .format_set1[3] = 0x01, .format_set1[4] = 0x01, .format_set1[5] = 0x01,
	/*B0 0x85*/	.format_set2[0] = 0x06, .format_set2[1] = 0x06, .format_set2[2] = 0x06, .format_set2[3] = 0x06, .format_set2[4] = 0x06, .format_set2[5] = 0x06,

	/*B0 0x64*/ .v_delay[0]     = 0x80, .v_delay[1]     = 0x80, .v_delay[2]     = 0x80, .v_delay[3]     = 0x80, .v_delay[4]     = 0x80, .v_delay[5]     = 0x80,
		},
	},

	[ AHD30_3M_18P ] = { /* o */
	/* base */
		{
			.eq_bypass[0] 	= 0x62, .eq_bypass[1] 	= 0x22, .eq_bypass[2] 	= 0x22, .eq_bypass[3] 	= 0x22, .eq_bypass[4] 	= 0x22, .eq_bypass[5] 	= 0x22,    // Bank5 0x30
			.eq_band_sel[0] = 0x77, .eq_band_sel[1] = 0x77, .eq_band_sel[2] = 0x77, .eq_band_sel[3] = 0x77, .eq_band_sel[4] = 0x57, .eq_band_sel[5] = 0x57,    // BankA 0x31
			.eq_gain_sel[0] = 0x78, .eq_gain_sel[1] = 0x7b, .eq_gain_sel[2] = 0x7f, .eq_gain_sel[3] = 0x7f, .eq_gain_sel[4] = 0x7f, .eq_gain_sel[5] = 0x7f,    // BankA 0x32
			.deq_a_on[0] 	= 0x00, .deq_a_on[1] 	= 0x01, .deq_a_on[2] 	= 0x01, .deq_a_on[3] 	= 0x01, .deq_a_on[4] 	= 0x01, .deq_a_on[5] 	= 0x01,    // BankA 0x33
			.deq_a_sel[0] 	= 0x00, .deq_a_sel[1] 	= 0x91, .deq_a_sel[2] 	= 0x87, .deq_a_sel[3] 	= 0x89, .deq_a_sel[4] 	= 0x93, .deq_a_sel[5] 	= 0x94,    // BankA 0x34
			.deq_b_sel[0] 	= 0x00, .deq_b_sel[1] 	= 0x00, .deq_b_sel[2] 	= 0x00, .deq_b_sel[3] 	= 0x00, .deq_b_sel[4] 	= 0x00, .deq_b_sel[5] 	= 0x00,    // BankA 0x35
		},
		/* coeff */
		{
			.deqA_01[0] = 0xAC, .deqA_01[1] = 0xAC, .deqA_01[2] = 0xAC, .deqA_01[3] = 0xAC, .deqA_01[4] = 0xAC, .deqA_01[5] = 0xAC,		// BankA 0x30
			.deqA_02[0] = 0x78, .deqA_02[1] = 0x78, .deqA_02[2] = 0x78, .deqA_02[3] = 0x78, .deqA_02[4] = 0x78, .deqA_02[5] = 0x78,		// BankA 0x31
			.deqA_03[0] = 0x17, .deqA_03[1] = 0x17, .deqA_03[2] = 0x17, .deqA_03[3] = 0x17, .deqA_03[4] = 0x17, .deqA_03[5] = 0x17,		// BankA 0x32
			.deqA_04[0] = 0xC1, .deqA_04[1] = 0xC1, .deqA_04[2] = 0xC1, .deqA_04[3] = 0xC1, .deqA_04[4] = 0xC1, .deqA_04[5] = 0xC1,     // BankA 0x33
			.deqA_05[0] = 0x40, .deqA_05[1] = 0x40, .deqA_05[2] = 0x40, .deqA_05[3] = 0x40, .deqA_05[4] = 0x40, .deqA_05[5] = 0x40,     // BankA 0x34
			.deqA_06[0] = 0x00, .deqA_06[1] = 0x00, .deqA_06[2] = 0x00, .deqA_06[3] = 0x00, .deqA_06[4] = 0x00, .deqA_06[5] = 0x00,     // BankA 0x35
			.deqA_07[0] = 0xC3, .deqA_07[1] = 0xC3, .deqA_07[2] = 0xC3, .deqA_07[3] = 0xC3, .deqA_07[4] = 0xC3, .deqA_07[5] = 0xC3,     // BankA 0x36
			.deqA_08[0] = 0x0A, .deqA_08[1] = 0x0A, .deqA_08[2] = 0x0A, .deqA_08[3] = 0x0A, .deqA_08[4] = 0x0A, .deqA_08[5] = 0x0A,     // BankA 0x37
			.deqA_09[0] = 0x00, .deqA_09[1] = 0x00, .deqA_09[2] = 0x00, .deqA_09[3] = 0x00, .deqA_09[4] = 0x00, .deqA_09[5] = 0x00,     // BankA 0x38
			.deqA_10[0] = 0x02, .deqA_10[1] = 0x02, .deqA_10[2] = 0x02, .deqA_10[3] = 0x02, .deqA_10[4] = 0x02, .deqA_10[5] = 0x02,     // BankA 0x39
			.deqA_11[0] = 0x00, .deqA_11[1] = 0x00, .deqA_11[2] = 0x00, .deqA_11[3] = 0x00, .deqA_11[4] = 0x00, .deqA_11[5] = 0x00,     // BankA 0x3a
			.deqA_12[0] = 0xB2, .deqA_12[1] = 0xB2, .deqA_12[2] = 0xB2, .deqA_12[3] = 0xB2, .deqA_12[4] = 0xB2, .deqA_12[5] = 0xB2,     // BankA 0x3b
		},
		/* color */
		{
			.contrast[0] 		= 0x86, .contrast[1] 		= 0x82, .contrast[2] 		= 0x82, .contrast[3] 		= 0x7e, .contrast[4] 		= 0x7c, .contrast[5] 		= 0x77,
			.h_peaking[0] 		= 0x0f, .h_peaking[1] 		= 0x0f, .h_peaking[2] 		= 0x0f, .h_peaking[3] 		= 0x0f, .h_peaking[4] 		= 0x0f, .h_peaking[5] 		= 0x0f,
			.c_filter[0]		= 0x82, .c_filter[1] 		= 0x82, .c_filter[2]	 	= 0x92, .c_filter[3] 		= 0x92, .c_filter[4] 		= 0xa2, .c_filter[5] 		= 0xb2,

			.hue[0] 			= 0x00, .hue[1] 			= 0x00, .hue[2] 			= 0x00, .hue[3] 			= 0x00, .hue[4] 			= 0x00, .hue[5] 			= 0x00,
			.u_gain[0] 			= 0x10, .u_gain[1] 			= 0x10, .u_gain[2] 			= 0x04, .u_gain[3] 			= 0xfc, .u_gain[4] 			= 0xfc, .u_gain[5] 			= 0xfc,
			.v_gain[0] 			= 0x10, .v_gain[1] 			= 0x10, .v_gain[2] 			= 0x04, .v_gain[3] 			= 0xf4, .v_gain[4] 			= 0x08, .v_gain[5] 			= 0x08,
			.u_offset[0] 		= 0xfb, .u_offset[1] 		= 0xfb, .u_offset[2] 		= 0xfb, .u_offset[3] 		= 0xfb, .u_offset[4] 		= 0xfb, .u_offset[5] 		= 0xfe,
			.v_offset[0] 		= 0xf8, .v_offset[1] 		= 0xf8, .v_offset[2] 		= 0xf8, .v_offset[3] 		= 0xf8, .v_offset[4] 		= 0xf8, .v_offset[5] 		= 0xfb,

			.black_level[0] 	= 0x80, .black_level[1] 	= 0x81, .black_level[2] 	= 0x81, .black_level[3] 	= 0x83, .black_level[4] 	= 0x85, .black_level[5] 	= 0x87,
			.acc_ref[0]			= 0x57, .acc_ref[1]			= 0x57, .acc_ref[2]			= 0x57, .acc_ref[3]			= 0x57, .acc_ref[4]			= 0x57, .acc_ref[5]			= 0x57,
			.cti_delay[0]		= 0x80, .cti_delay[1]		= 0x80, .cti_delay[2]		= 0x80, .cti_delay[3]		= 0x80, .cti_delay[4]		= 0x80, .cti_delay[5]		= 0x80,
			.sub_saturation[0] 	= 0xa8, .sub_saturation[1] 	= 0xa8, .sub_saturation[2] 	= 0xa8, .sub_saturation[3] 	= 0xa8, .sub_saturation[4] 	= 0x90, .sub_saturation[5] 	= 0x90,

			.burst_dec_a[0] 	= 0x2a, .burst_dec_a[1] 	= 0x2a, .burst_dec_a[2] 	= 0x2a, .burst_dec_a[3] 	= 0x2a, .burst_dec_a[4] 	= 0x2a, .burst_dec_a[5] 	= 0x2a,
			.burst_dec_b[0] 	= 0x00, .burst_dec_b[1] 	= 0x00, .burst_dec_b[2] 	= 0x00, .burst_dec_b[3] 	= 0x00, .burst_dec_b[4] 	= 0x00, .burst_dec_b[5] 	= 0x00,
			.burst_dec_c[0] 	= 0x30, .burst_dec_c[1] 	= 0x30, .burst_dec_c[2] 	= 0x30, .burst_dec_c[3] 	= 0x30, .burst_dec_c[4] 	= 0x30, .burst_dec_c[5] 	= 0x30,

			.c_option[0] 		= 0x80, .c_option[1] 		= 0x80, .c_option[2] 		= 0x90, .c_option[3] 		= 0x90, .c_option[4] 		= 0x90, .c_option[5] 		= 0xa0,

			.y_filter_b[0]		= 0x10, .y_filter_b[1]		= 0x10, .y_filter_b[2]		= 0x10, .y_filter_b[3]		= 0x10, .y_filter_b[4]		= 0x10, .y_filter_b[5]		= 0x10,
			.y_filter_b_sel[0]	= 0x1e,	.y_filter_b_sel[1]	= 0x1e,	.y_filter_b_sel[2]	= 0x1e, .y_filter_b_sel[3]	= 0x1e, .y_filter_b_sel[4]	= 0x1e, .y_filter_b_sel[5]	= 0x1e,
		},
		/* timing_a */
		{
			.h_delay_a[0] = 0x80, .h_delay_a[1] = 0x80, .h_delay_a[2] = 0x80, .h_delay_a[3] = 0x80, .h_delay_a[4] = 0x80, .h_delay_a[5] = 0x80,
			.h_delay_b[0] = 0x10, .h_delay_b[1] = 0x10, .h_delay_b[2] = 0x10, .h_delay_b[3] = 0x10, .h_delay_b[4] = 0x10, .h_delay_b[5] = 0x10,
			.h_delay_c[0] = 0x03, .h_delay_c[1] = 0x03, .h_delay_c[2] = 0x03, .h_delay_c[3] = 0x03, .h_delay_c[4] = 0x03, .h_delay_c[5] = 0x03,
			.y_delay[0]   = 0x05, .y_delay[1]   = 0x03, .y_delay[2]   = 0x03, .y_delay[3]   = 0x03, .y_delay[4]   = 0x03, .y_delay[5] =   0x03,

		},
		/* clk */
		{
			.clk_adc[0] = 0x02, .clk_adc[1] = 0x02, .clk_adc[2] = 0x02, .clk_adc[3] = 0x02, .clk_adc[4] = 0x02, .clk_adc[5] = 0x02,
			.clk_dec[0] = 0x40, .clk_dec[1] = 0x40, .clk_dec[2] = 0x40, .clk_dec[3] = 0x40, .clk_dec[4] = 0x40, .clk_dec[5] = 0x40,
		},
		/* timing_b */
		{
	/*B9 0x96*/	.h_scaler1[0]  = 0x00, .h_scaler1[1]   = 0x00, .h_scaler1[2]   = 0x00, .h_scaler1[3]   = 0x00, .h_scaler1[4]   = 0x00, .h_scaler1[5]   = 0x00,
	/*B9 0x97*/	.h_scaler2[0]  = 0x00, .h_scaler2[1]   = 0x00, .h_scaler2[2]   = 0x00, .h_scaler2[3]   = 0x00, .h_scaler2[4]   = 0x00, .h_scaler2[5]   = 0x00,
	/*B9 0x98*/	.h_scaler3[0]  = 0x00, .h_scaler3[1]   = 0x00, .h_scaler3[2]   = 0x00, .h_scaler3[3]   = 0x00, .h_scaler3[4]   = 0x00, .h_scaler3[5]   = 0x00,
	/*B9 0x99*/	.h_scaler4[0]  = 0x00, .h_scaler4[1]   = 0x00, .h_scaler4[2]   = 0x00, .h_scaler4[3]   = 0x00, .h_scaler4[4]   = 0x00, .h_scaler4[5]   = 0x00,
	/*B9 0x9a*/	.h_scaler5[0]  = 0x00, .h_scaler5[1]   = 0x00, .h_scaler5[2]   = 0x00, .h_scaler5[3]   = 0x00, .h_scaler5[4]   = 0x00, .h_scaler5[5]   = 0x00,
	/*B9 0x9b*/	.h_scaler6[0]  = 0x00, .h_scaler6[1]   = 0x00, .h_scaler6[2]   = 0x00, .h_scaler6[3]   = 0x00, .h_scaler6[4]   = 0x00, .h_scaler6[5]   = 0x00,
	/*B9 0x9c*/	.h_scaler7[0]  = 0x00, .h_scaler7[1]   = 0x00, .h_scaler7[2]   = 0x00, .h_scaler7[3]   = 0x00, .h_scaler7[4]   = 0x00, .h_scaler7[5]   = 0x00,
	/*B9 0x9d*/	.h_scaler8[0]  = 0x00, .h_scaler8[1]   = 0x00, .h_scaler8[2]   = 0x00, .h_scaler8[3]   = 0x00, .h_scaler8[4]   = 0x00, .h_scaler8[5]   = 0x00,
	/*B9 0x9e*/	.h_scaler9[0]  = 0x00, .h_scaler9[1]   = 0x00, .h_scaler9[2]   = 0x00, .h_scaler9[3]   = 0x00, .h_scaler9[4]   = 0x00, .h_scaler9[5]   = 0x00,


	/*B9 0x40*/	.pn_auto[0]    	= 0x00, .pn_auto[1]		= 0x00, .pn_auto[2]    	= 0x00, .pn_auto[3]    	= 0x00, .pn_auto[4]    	= 0x00, .pn_auto[5]    	= 0x00,

	/*B5 0x90*/	.comb_mode[0]      = 0x01, .comb_mode[1]	  = 0x01, .comb_mode[2]      = 0x01, .comb_mode[3]      = 0x01, .comb_mode[4]  	   = 0x01, .comb_mode[5]      = 0x01,
	/*B9 0xb9*/	.h_pll_op_a[0]     = 0x72, .h_pll_op_a[1]     = 0x72, .h_pll_op_a[2]     = 0x72, .h_pll_op_a[3]     = 0x72, .h_pll_op_a[4]     = 0x72, .h_pll_op_a[5]     = 0x72,
	/*B9 0x57*/	.mem_path[0]	   = 0x00, .mem_path[1]	      = 0x00, .mem_path[2]	     = 0x00, .mem_path[3]	    = 0x00, .mem_path[4]	   = 0x00, .mem_path[5]	      = 0x00,
				.fsc_lock_speed[0] = 0xdc, .fsc_lock_speed[1] = 0xdc, .fsc_lock_speed[2] = 0xdc, .fsc_lock_speed[3] = 0xdc, .fsc_lock_speed[4] = 0xdc, .fsc_lock_speed[5] = 0xdc,

	/*B0 0x81*/	.format_set1[0] = 0x04, .format_set1[1] = 0x04, .format_set1[2] = 0x04, .format_set1[3] = 0x04, .format_set1[4] = 0x04, .format_set1[5] = 0x04,
	/*B0 0x85*/	.format_set2[0] = 0x04, .format_set2[1] = 0x04, .format_set2[2] = 0x04, .format_set2[3] = 0x04, .format_set2[4] = 0x04, .format_set2[5] = 0x04,

	/*B0 0x64*/ .v_delay[0]     = 0x20, .v_delay[1]     = 0x20, .v_delay[2]     = 0x20, .v_delay[3]     = 0x20, .v_delay[4]     = 0x20, .v_delay[5]     = 0x20,
		},
	},

	[ AHD30_3M_25P ] = /* o */
	{
		/* base */
		{
			.eq_bypass[0] 	= 0x22, .eq_bypass[1] 	= 0x22, .eq_bypass[2] 	= 0x22, .eq_bypass[3] 	= 0x22, .eq_bypass[4] 	= 0x22, .eq_bypass[5] 	= 0x22,    // Bank5 0x30
			.eq_band_sel[0] = 0x77, .eq_band_sel[1] = 0x77, .eq_band_sel[2] = 0x77, .eq_band_sel[3] = 0x67, .eq_band_sel[4] = 0x57, .eq_band_sel[5] = 0x57,    // BankA 0x31
			.eq_gain_sel[0] = 0x78, .eq_gain_sel[1] = 0x7b, .eq_gain_sel[2] = 0x7f, .eq_gain_sel[3] = 0x7e, .eq_gain_sel[4] = 0x7f, .eq_gain_sel[5] = 0x7f,    // BankA 0x32
			.deq_a_on[0] 	= 0x00, .deq_a_on[1] 	= 0x01, .deq_a_on[2] 	= 0x01, .deq_a_on[3] 	= 0x01, .deq_a_on[4] 	= 0x01, .deq_a_on[5] 	= 0x01,    // BankA 0x33
			.deq_a_sel[0] 	= 0x00, .deq_a_sel[1] 	= 0x91, .deq_a_sel[2] 	= 0x93, .deq_a_sel[3] 	= 0x98, .deq_a_sel[4] 	= 0x98, .deq_a_sel[5] 	= 0x98,    // BankA 0x34
			.deq_b_sel[0] 	= 0x00, .deq_b_sel[1] 	= 0x00, .deq_b_sel[2] 	= 0x00, .deq_b_sel[3] 	= 0x20, .deq_b_sel[4] 	= 0x00, .deq_b_sel[5] 	= 0x00,    // BankA 0x35
		},
		/* coeff */
		{
			.deqA_01[0] = 0xAC, .deqA_01[1] = 0xAC, .deqA_01[2] = 0xAC, .deqA_01[3] = 0xAC, .deqA_01[4] = 0xAC, .deqA_01[5] = 0xAC,		// BankA 0x30
			.deqA_02[0] = 0x78, .deqA_02[1] = 0x78, .deqA_02[2] = 0x78, .deqA_02[3] = 0x78, .deqA_02[4] = 0x78, .deqA_02[5] = 0x78,		// BankA 0x31
			.deqA_03[0] = 0x17, .deqA_03[1] = 0x17, .deqA_03[2] = 0x17, .deqA_03[3] = 0x17, .deqA_03[4] = 0x17, .deqA_03[5] = 0x17,		// BankA 0x32
			.deqA_04[0] = 0xC1, .deqA_04[1] = 0xC1, .deqA_04[2] = 0xC1, .deqA_04[3] = 0xC1, .deqA_04[4] = 0xC1, .deqA_04[5] = 0xC1,     // BankA 0x33
			.deqA_05[0] = 0x40, .deqA_05[1] = 0x40, .deqA_05[2] = 0x40, .deqA_05[3] = 0x40, .deqA_05[4] = 0x40, .deqA_05[5] = 0x40,     // BankA 0x34
			.deqA_06[0] = 0x00, .deqA_06[1] = 0x00, .deqA_06[2] = 0x00, .deqA_06[3] = 0x00, .deqA_06[4] = 0x00, .deqA_06[5] = 0x00,     // BankA 0x35
			.deqA_07[0] = 0xC3, .deqA_07[1] = 0xC3, .deqA_07[2] = 0xC3, .deqA_07[3] = 0xC3, .deqA_07[4] = 0xC3, .deqA_07[5] = 0xC3,     // BankA 0x36
			.deqA_08[0] = 0x0A, .deqA_08[1] = 0x0A, .deqA_08[2] = 0x0A, .deqA_08[3] = 0x0A, .deqA_08[4] = 0x0A, .deqA_08[5] = 0x0A,     // BankA 0x37
			.deqA_09[0] = 0x00, .deqA_09[1] = 0x00, .deqA_09[2] = 0x00, .deqA_09[3] = 0x00, .deqA_09[4] = 0x00, .deqA_09[5] = 0x00,     // BankA 0x38
			.deqA_10[0] = 0x02, .deqA_10[1] = 0x02, .deqA_10[2] = 0x02, .deqA_10[3] = 0x02, .deqA_10[4] = 0x02, .deqA_10[5] = 0x02,     // BankA 0x39
			.deqA_11[0] = 0x00, .deqA_11[1] = 0x00, .deqA_11[2] = 0x00, .deqA_11[3] = 0x00, .deqA_11[4] = 0x00, .deqA_11[5] = 0x00,     // BankA 0x3a
			.deqA_12[0] = 0xB2, .deqA_12[1] = 0xB2, .deqA_12[2] = 0xB2, .deqA_12[3] = 0xB2, .deqA_12[4] = 0xB2, .deqA_12[5] = 0xB2,     // BankA 0x3b
		},
		/* color */
		{
			.contrast[0] 		= 0x80, .contrast[1] 		= 0x7c, .contrast[2] 		= 0x79, .contrast[3] 		= 0x75, .contrast[4] 		= 0x70, .contrast[5] 		= 0x7a,
			.h_peaking[0] 		= 0x0f, .h_peaking[1] 		= 0x0f, .h_peaking[2] 		= 0x0f, .h_peaking[3] 		= 0x0f, .h_peaking[4] 		= 0x0f, .h_peaking[5] 		= 0x0f,
			.c_filter[0]		= 0x82, .c_filter[1] 		= 0x82, .c_filter[2]	 	= 0x92, .c_filter[3] 		= 0x92, .c_filter[4] 		= 0xa2, .c_filter[5] 		= 0xb2,

			.hue[0] 			= 0x04, .hue[1] 			= 0x04, .hue[2] 			= 0x04, .hue[3] 			= 0x04, .hue[4] 			= 0x04, .hue[5] 			= 0x04,
			.u_gain[0] 			= 0x10, .u_gain[1] 			= 0x10, .u_gain[2] 			= 0x04, .u_gain[3] 			= 0xfc, .u_gain[4] 			= 0xfc, .u_gain[5] 			= 0xfc,
			.v_gain[0] 			= 0x10, .v_gain[1] 			= 0x10, .v_gain[2] 			= 0x04, .v_gain[3] 			= 0xf4, .v_gain[4] 			= 0x08, .v_gain[5] 			= 0x08,
			.u_offset[0] 		= 0xfb, .u_offset[1] 		= 0xfb, .u_offset[2] 		= 0xfb, .u_offset[3] 		= 0xfb, .u_offset[4] 		= 0xfb, .u_offset[5] 		= 0xfb,
			.v_offset[0] 		= 0xf8, .v_offset[1] 		= 0xf8, .v_offset[2] 		= 0xf8, .v_offset[3] 		= 0xf8, .v_offset[4] 		= 0xf8, .v_offset[5] 		= 0xf8,

			.black_level[0] 	= 0x80, .black_level[1] 	= 0x82, .black_level[2] 	= 0x82, .black_level[3] 	= 0x85, .black_level[4] 	= 0x89, .black_level[5] 	= 0x8c,
			.acc_ref[0]			= 0x57, .acc_ref[1]			= 0x57, .acc_ref[2]			= 0x57, .acc_ref[3]			= 0x57, .acc_ref[4]			= 0x57, .acc_ref[5]			= 0x57,
			.cti_delay[0]		= 0x80, .cti_delay[1]		= 0x80, .cti_delay[2]		= 0x80, .cti_delay[3]		= 0x80, .cti_delay[4]		= 0x80, .cti_delay[5]		= 0x80,
			.sub_saturation[0] 	= 0xb0, .sub_saturation[1] 	= 0xb0, .sub_saturation[2] 	= 0xa0, .sub_saturation[3] 	= 0xd0, .sub_saturation[4] 	= 0xb4, .sub_saturation[5] 	= 0x90,

			.burst_dec_a[0] 	= 0x2a, .burst_dec_a[1] 	= 0x2a, .burst_dec_a[2] 	= 0x2a, .burst_dec_a[3] 	= 0x2a, .burst_dec_a[4] 	= 0x2a, .burst_dec_a[5] 	= 0x2a,
			.burst_dec_b[0] 	= 0x00, .burst_dec_b[1] 	= 0x00, .burst_dec_b[2] 	= 0x00, .burst_dec_b[3] 	= 0x00, .burst_dec_b[4] 	= 0x00, .burst_dec_b[5] 	= 0x00,
			.burst_dec_c[0] 	= 0x30, .burst_dec_c[1] 	= 0x30, .burst_dec_c[2] 	= 0x30, .burst_dec_c[3] 	= 0x30, .burst_dec_c[4] 	= 0x30, .burst_dec_c[5] 	= 0x30,

			.c_option[0] 		= 0x80, .c_option[1] 		= 0x80, .c_option[2] 		= 0x80, .c_option[3] 		= 0x90, .c_option[4] 		= 0x90, .c_option[5] 		= 0x90,

			.y_filter_b[0]		= 0x10, .y_filter_b[1]		= 0x10, .y_filter_b[2]		= 0x10, .y_filter_b[3]		= 0x10, .y_filter_b[4]		= 0x10, .y_filter_b[5]		= 0x10,
			.y_filter_b_sel[0]	= 0x1e,	.y_filter_b_sel[1]	= 0x1e,	.y_filter_b_sel[2]	= 0x1e, .y_filter_b_sel[3]	= 0x1e, .y_filter_b_sel[4]	= 0x1e, .y_filter_b_sel[5]	= 0x1e,
		},
		/* timing_a */
		{
			.h_delay_a[0] = 0x80, .h_delay_a[1] = 0x80, .h_delay_a[2] = 0x80, .h_delay_a[3] = 0x80, .h_delay_a[4] = 0x80, .h_delay_a[5] = 0x80,
			.h_delay_b[0] = 0x10, .h_delay_b[1] = 0x10, .h_delay_b[2] = 0x10, .h_delay_b[3] = 0x10, .h_delay_b[4] = 0x10, .h_delay_b[5] = 0x10,
			.h_delay_c[0] = 0x03, .h_delay_c[1] = 0x03, .h_delay_c[2] = 0x03, .h_delay_c[3] = 0x03, .h_delay_c[4] = 0x03, .h_delay_c[5] = 0x03,
			.y_delay[0]   = 0x05, .y_delay[1]   = 0x05, .y_delay[2]   = 0x05, .y_delay[3]   = 0x05, .y_delay[4]   = 0x05, .y_delay[5] =   0x05,

		},
		/* clk */
		{
			.clk_adc[0] = 0x05, .clk_adc[1] = 0x05, .clk_adc[2] = 0x05, .clk_adc[3] = 0x05, .clk_adc[4] = 0x05, .clk_adc[5] = 0x05,
			.clk_dec[0] = 0x44, .clk_dec[1] = 0x44, .clk_dec[2] = 0x44, .clk_dec[3] = 0x44, .clk_dec[4] = 0x44, .clk_dec[5] = 0x44,
		},
		/* timing_b */
		{
/*B9 0x96*/	.h_scaler1[0]  = 0x00, .h_scaler1[1]   = 0x00, .h_scaler1[2]   = 0x00, .h_scaler1[3]   = 0x00, .h_scaler1[4]   = 0x00, .h_scaler1[5]   = 0x00,
/*B9 0x97*/	.h_scaler2[0]  = 0x00, .h_scaler2[1]   = 0x00, .h_scaler2[2]   = 0x00, .h_scaler2[3]   = 0x00, .h_scaler2[4]   = 0x00, .h_scaler2[5]   = 0x00,
/*B9 0x98*/	.h_scaler3[0]  = 0x00, .h_scaler3[1]   = 0x00, .h_scaler3[2]   = 0x00, .h_scaler3[3]   = 0x00, .h_scaler3[4]   = 0x00, .h_scaler3[5]   = 0x00,
/*B9 0x99*/	.h_scaler4[0]  = 0x00, .h_scaler4[1]   = 0x00, .h_scaler4[2]   = 0x00, .h_scaler4[3]   = 0x00, .h_scaler4[4]   = 0x00, .h_scaler4[5]   = 0x00,
/*B9 0x9a*/	.h_scaler5[0]  = 0x00, .h_scaler5[1]   = 0x00, .h_scaler5[2]   = 0x00, .h_scaler5[3]   = 0x00, .h_scaler5[4]   = 0x00, .h_scaler5[5]   = 0x00,
/*B9 0x9b*/	.h_scaler6[0]  = 0x00, .h_scaler6[1]   = 0x00, .h_scaler6[2]   = 0x00, .h_scaler6[3]   = 0x00, .h_scaler6[4]   = 0x00, .h_scaler6[5]   = 0x00,
/*B9 0x9c*/	.h_scaler7[0]  = 0x00, .h_scaler7[1]   = 0x00, .h_scaler7[2]   = 0x00, .h_scaler7[3]   = 0x00, .h_scaler7[4]   = 0x00, .h_scaler7[5]   = 0x00,
/*B9 0x9d*/	.h_scaler8[0]  = 0x00, .h_scaler8[1]   = 0x00, .h_scaler8[2]   = 0x00, .h_scaler8[3]   = 0x00, .h_scaler8[4]   = 0x00, .h_scaler8[5]   = 0x00,
/*B9 0x9e*/	.h_scaler9[0]  = 0x00, .h_scaler9[1]   = 0x00, .h_scaler9[2]   = 0x00, .h_scaler9[3]   = 0x00, .h_scaler9[4]   = 0x00, .h_scaler9[5]   = 0x00,


/*B9 0x40*/	.pn_auto[0]    	= 0x00, .pn_auto[1]		= 0x00, .pn_auto[2]    	= 0x00, .pn_auto[3]    	= 0x00, .pn_auto[4]    	= 0x00, .pn_auto[5]    	= 0x00,

/*B5 0x90*/	.comb_mode[0]   = 0x01, .comb_mode[1]	= 0x01, .comb_mode[2]   = 0x01, .comb_mode[3]   = 0x01, .comb_mode[4]  	= 0x01, .comb_mode[5]   = 0x01,
/*B9 0xb9*/	.h_pll_op_a[0]  = 0x72, .h_pll_op_a[1]  = 0x72, .h_pll_op_a[2]  = 0x72, .h_pll_op_a[3]  = 0x72, .h_pll_op_a[4]  = 0x72, .h_pll_op_a[5]  = 0x72,
/*B9 0x57*/	.mem_path[0]	= 0x00, .mem_path[1]	= 0x00, .mem_path[2]	= 0x00, .mem_path[3]	= 0x00, .mem_path[4]	= 0x00, .mem_path[5]	= 0x00,
			.fsc_lock_speed[0] = 0xdc, .fsc_lock_speed[1] = 0xdc, .fsc_lock_speed[2] = 0xdc, .fsc_lock_speed[3] = 0xdc, .fsc_lock_speed[4] = 0xdc, .fsc_lock_speed[5] = 0xdc,

/*B0 0x81*/	.format_set1[0] = 0x03, .format_set1[1] = 0x03, .format_set1[2] = 0x03, .format_set1[3] = 0x03, .format_set1[4] = 0x03, .format_set1[5] = 0x03,
/*B0 0x85*/	.format_set2[0] = 0x04, .format_set2[1] = 0x04, .format_set2[2] = 0x04, .format_set2[3] = 0x04, .format_set2[4] = 0x04, .format_set2[5] = 0x04,

/*B0 0x64*/ .v_delay[0]     = 0x21, .v_delay[1]     = 0x21, .v_delay[2]     = 0x21, .v_delay[3]     = 0x21, .v_delay[4]     = 0x21, .v_delay[5]     = 0x21,
		},
	},
	[ AHD30_3M_30P ] = /* o */
	{
		/* base */
		{
			.eq_bypass[0] 	= 0x22, .eq_bypass[1] 	= 0x22, .eq_bypass[2] 	= 0x22, .eq_bypass[3] 	= 0x22, .eq_bypass[4] 	= 0x22, .eq_bypass[5] 	= 0x22,    // Bank5 0x30
			.eq_band_sel[0] = 0x77, .eq_band_sel[1] = 0x77, .eq_band_sel[2] = 0x77, .eq_band_sel[3] = 0x67, .eq_band_sel[4] = 0x57, .eq_band_sel[5] = 0x57,    // BankA 0x31
			.eq_gain_sel[0] = 0x78, .eq_gain_sel[1] = 0x7b, .eq_gain_sel[2] = 0x7f, .eq_gain_sel[3] = 0x7e, .eq_gain_sel[4] = 0x7f, .eq_gain_sel[5] = 0x7f,    // BankA 0x32
			.deq_a_on[0] 	= 0x00, .deq_a_on[1] 	= 0x01, .deq_a_on[2] 	= 0x01, .deq_a_on[3] 	= 0x01, .deq_a_on[4] 	= 0x01, .deq_a_on[5] 	= 0x01,    // BankA 0x33
			.deq_a_sel[0] 	= 0x00, .deq_a_sel[1] 	= 0x91, .deq_a_sel[2] 	= 0x93, .deq_a_sel[3] 	= 0x98, .deq_a_sel[4] 	= 0x98, .deq_a_sel[5] 	= 0x98,    // BankA 0x34
			.deq_b_sel[0] 	= 0x00, .deq_b_sel[1] 	= 0x00, .deq_b_sel[2] 	= 0x00, .deq_b_sel[3] 	= 0x20, .deq_b_sel[4] 	= 0x00, .deq_b_sel[5] 	= 0x00,    // BankA 0x35
		},
		/* coeff */
		{
			.deqA_01[0] = 0xAC, .deqA_01[1] = 0xAC, .deqA_01[2] = 0xAC, .deqA_01[3] = 0xAC, .deqA_01[4] = 0xAC, .deqA_01[5] = 0xAC,		// BankA 0x30
			.deqA_02[0] = 0x78, .deqA_02[1] = 0x78, .deqA_02[2] = 0x78, .deqA_02[3] = 0x78, .deqA_02[4] = 0x78, .deqA_02[5] = 0x78,		// BankA 0x31
			.deqA_03[0] = 0x17, .deqA_03[1] = 0x17, .deqA_03[2] = 0x17, .deqA_03[3] = 0x17, .deqA_03[4] = 0x17, .deqA_03[5] = 0x17,		// BankA 0x32
			.deqA_04[0] = 0xC1, .deqA_04[1] = 0xC1, .deqA_04[2] = 0xC1, .deqA_04[3] = 0xC1, .deqA_04[4] = 0xC1, .deqA_04[5] = 0xC1,     // BankA 0x33
			.deqA_05[0] = 0x40, .deqA_05[1] = 0x40, .deqA_05[2] = 0x40, .deqA_05[3] = 0x40, .deqA_05[4] = 0x40, .deqA_05[5] = 0x40,     // BankA 0x34
			.deqA_06[0] = 0x00, .deqA_06[1] = 0x00, .deqA_06[2] = 0x00, .deqA_06[3] = 0x00, .deqA_06[4] = 0x00, .deqA_06[5] = 0x00,     // BankA 0x35
			.deqA_07[0] = 0xC3, .deqA_07[1] = 0xC3, .deqA_07[2] = 0xC3, .deqA_07[3] = 0xC3, .deqA_07[4] = 0xC3, .deqA_07[5] = 0xC3,     // BankA 0x36
			.deqA_08[0] = 0x0A, .deqA_08[1] = 0x0A, .deqA_08[2] = 0x0A, .deqA_08[3] = 0x0A, .deqA_08[4] = 0x0A, .deqA_08[5] = 0x0A,     // BankA 0x37
			.deqA_09[0] = 0x00, .deqA_09[1] = 0x00, .deqA_09[2] = 0x00, .deqA_09[3] = 0x00, .deqA_09[4] = 0x00, .deqA_09[5] = 0x00,     // BankA 0x38
			.deqA_10[0] = 0x02, .deqA_10[1] = 0x02, .deqA_10[2] = 0x02, .deqA_10[3] = 0x02, .deqA_10[4] = 0x02, .deqA_10[5] = 0x02,     // BankA 0x39
			.deqA_11[0] = 0x00, .deqA_11[1] = 0x00, .deqA_11[2] = 0x00, .deqA_11[3] = 0x00, .deqA_11[4] = 0x00, .deqA_11[5] = 0x00,     // BankA 0x3a
			.deqA_12[0] = 0xB2, .deqA_12[1] = 0xB2, .deqA_12[2] = 0xB2, .deqA_12[3] = 0xB2, .deqA_12[4] = 0xB2, .deqA_12[5] = 0xB2,     // BankA 0x3b
		},
		/* color */
		{
			.contrast[0] 		= 0x80, .contrast[1] 		= 0x7c, .contrast[2] 		= 0x79, .contrast[3] 		= 0x75, .contrast[4] 		= 0x70, .contrast[5] 		= 0x7a,
			.h_peaking[0] 		= 0x0f, .h_peaking[1] 		= 0x0f, .h_peaking[2] 		= 0x0f, .h_peaking[3] 		= 0x0f, .h_peaking[4] 		= 0x0f, .h_peaking[5] 		= 0x0f,
			.c_filter[0]		= 0x82, .c_filter[1] 		= 0x82, .c_filter[2]	 	= 0x92, .c_filter[3] 		= 0x92, .c_filter[4] 		= 0xa2, .c_filter[5] 		= 0xb2,

			.hue[0] 			= 0x04, .hue[1] 			= 0x04, .hue[2] 			= 0x04, .hue[3] 			= 0x04, .hue[4] 			= 0x04, .hue[5] 			= 0x04,
			.u_gain[0] 			= 0x10, .u_gain[1] 			= 0x10, .u_gain[2] 			= 0x04, .u_gain[3] 			= 0xfc, .u_gain[4] 			= 0xfc, .u_gain[5] 			= 0xfc,
			.v_gain[0] 			= 0x10, .v_gain[1] 			= 0x10, .v_gain[2] 			= 0x04, .v_gain[3] 			= 0xf4, .v_gain[4] 			= 0x08, .v_gain[5] 			= 0x08,
			.u_offset[0] 		= 0xfb, .u_offset[1] 		= 0xfb, .u_offset[2] 		= 0xfb, .u_offset[3] 		= 0xfb, .u_offset[4] 		= 0xfb, .u_offset[5] 		= 0xfb,
			.v_offset[0] 		= 0xf8, .v_offset[1] 		= 0xf8, .v_offset[2] 		= 0xf8, .v_offset[3] 		= 0xf8, .v_offset[4] 		= 0xf8, .v_offset[5] 		= 0xf8,

			.black_level[0] 	= 0x80, .black_level[1] 	= 0x82, .black_level[2] 	= 0x82, .black_level[3] 	= 0x85, .black_level[4] 	= 0x89, .black_level[5] 	= 0x8c,
			.acc_ref[0]			= 0x57, .acc_ref[1]			= 0x57, .acc_ref[2]			= 0x57, .acc_ref[3]			= 0x57, .acc_ref[4]			= 0x57, .acc_ref[5]			= 0x57,
			.cti_delay[0]		= 0x80, .cti_delay[1]		= 0x80, .cti_delay[2]		= 0x80, .cti_delay[3]		= 0x80, .cti_delay[4]		= 0x80, .cti_delay[5]		= 0x80,
			.sub_saturation[0] 	= 0xb0, .sub_saturation[1] 	= 0xb0, .sub_saturation[2] 	= 0xa0, .sub_saturation[3] 	= 0xd0, .sub_saturation[4] 	= 0xb4, .sub_saturation[5] 	= 0x90,

			.burst_dec_a[0] 	= 0x2a, .burst_dec_a[1] 	= 0x2a, .burst_dec_a[2] 	= 0x2a, .burst_dec_a[3] 	= 0x2a, .burst_dec_a[4] 	= 0x2a, .burst_dec_a[5] 	= 0x2a,
			.burst_dec_b[0] 	= 0x00, .burst_dec_b[1] 	= 0x00, .burst_dec_b[2] 	= 0x00, .burst_dec_b[3] 	= 0x00, .burst_dec_b[4] 	= 0x00, .burst_dec_b[5] 	= 0x00,
			.burst_dec_c[0] 	= 0x30, .burst_dec_c[1] 	= 0x30, .burst_dec_c[2] 	= 0x30, .burst_dec_c[3] 	= 0x30, .burst_dec_c[4] 	= 0x30, .burst_dec_c[5] 	= 0x30,

			.c_option[0] 		= 0x80, .c_option[1] 		= 0x80, .c_option[2] 		= 0x80, .c_option[3] 		= 0x90, .c_option[4] 		= 0x90, .c_option[5] 		= 0x90,

			.y_filter_b[0]		= 0x10, .y_filter_b[1]		= 0x10, .y_filter_b[2]		= 0x10, .y_filter_b[3]		= 0x10, .y_filter_b[4]		= 0x10, .y_filter_b[5]		= 0x10,
			.y_filter_b_sel[0]	= 0x1e,	.y_filter_b_sel[1]	= 0x1e,	.y_filter_b_sel[2]	= 0x1e, .y_filter_b_sel[3]	= 0x1e, .y_filter_b_sel[4]	= 0x1e, .y_filter_b_sel[5]	= 0x1e,
		},
		/* timing_a */
		{
			.h_delay_a[0] = 0x80, .h_delay_a[1] = 0x80, .h_delay_a[2] = 0x80, .h_delay_a[3] = 0x80, .h_delay_a[4] = 0x80, .h_delay_a[5] = 0x80,
			.h_delay_b[0] = 0x10, .h_delay_b[1] = 0x10, .h_delay_b[2] = 0x10, .h_delay_b[3] = 0x10, .h_delay_b[4] = 0x10, .h_delay_b[5] = 0x10,
			.h_delay_c[0] = 0x04, .h_delay_c[1] = 0x04, .h_delay_c[2] = 0x04, .h_delay_c[3] = 0x04, .h_delay_c[4] = 0x04, .h_delay_c[5] = 0x04,
			.y_delay[0]   = 0x05, .y_delay[1]   = 0x05, .y_delay[2]   = 0x05, .y_delay[3]   = 0x05, .y_delay[4]   = 0x05, .y_delay[5] =   0x05,

		},
		/* clk */
		{
			.clk_adc[0] = 0x05, .clk_adc[1] = 0x05, .clk_adc[2] = 0x05, .clk_adc[3] = 0x05, .clk_adc[4] = 0x05, .clk_adc[5] = 0x05,
			.clk_dec[0] = 0x44, .clk_dec[1] = 0x44, .clk_dec[2] = 0x44, .clk_dec[3] = 0x44, .clk_dec[4] = 0x44, .clk_dec[5] = 0x44,
		},
		/* timing_b */
		{
/*B9 0x96*/	.h_scaler1[0]  = 0x00, .h_scaler1[1]   = 0x00, .h_scaler1[2]   = 0x00, .h_scaler1[3]   = 0x00, .h_scaler1[4]   = 0x00, .h_scaler1[5]   = 0x00,
/*B9 0x97*/	.h_scaler2[0]  = 0x00, .h_scaler2[1]   = 0x00, .h_scaler2[2]   = 0x00, .h_scaler2[3]   = 0x00, .h_scaler2[4]   = 0x00, .h_scaler2[5]   = 0x00,
/*B9 0x98*/	.h_scaler3[0]  = 0x00, .h_scaler3[1]   = 0x00, .h_scaler3[2]   = 0x00, .h_scaler3[3]   = 0x00, .h_scaler3[4]   = 0x00, .h_scaler3[5]   = 0x00,
/*B9 0x99*/	.h_scaler4[0]  = 0x00, .h_scaler4[1]   = 0x00, .h_scaler4[2]   = 0x00, .h_scaler4[3]   = 0x00, .h_scaler4[4]   = 0x00, .h_scaler4[5]   = 0x00,
/*B9 0x9a*/	.h_scaler5[0]  = 0x00, .h_scaler5[1]   = 0x00, .h_scaler5[2]   = 0x00, .h_scaler5[3]   = 0x00, .h_scaler5[4]   = 0x00, .h_scaler5[5]   = 0x00,
/*B9 0x9b*/	.h_scaler6[0]  = 0x00, .h_scaler6[1]   = 0x00, .h_scaler6[2]   = 0x00, .h_scaler6[3]   = 0x00, .h_scaler6[4]   = 0x00, .h_scaler6[5]   = 0x00,
/*B9 0x9c*/	.h_scaler7[0]  = 0x00, .h_scaler7[1]   = 0x00, .h_scaler7[2]   = 0x00, .h_scaler7[3]   = 0x00, .h_scaler7[4]   = 0x00, .h_scaler7[5]   = 0x00,
/*B9 0x9d*/	.h_scaler8[0]  = 0x00, .h_scaler8[1]   = 0x00, .h_scaler8[2]   = 0x00, .h_scaler8[3]   = 0x00, .h_scaler8[4]   = 0x00, .h_scaler8[5]   = 0x00,
/*B9 0x9e*/	.h_scaler9[0]  = 0x00, .h_scaler9[1]   = 0x00, .h_scaler9[2]   = 0x00, .h_scaler9[3]   = 0x00, .h_scaler9[4]   = 0x00, .h_scaler9[5]   = 0x00,


/*B9 0x40*/	.pn_auto[0]    	= 0x00, .pn_auto[1]		= 0x00, .pn_auto[2]    	= 0x00, .pn_auto[3]    	= 0x00, .pn_auto[4]    	= 0x00, .pn_auto[5]    	= 0x00,

/*B5 0x90*/	.comb_mode[0]   = 0x01, .comb_mode[1]	= 0x01, .comb_mode[2]   = 0x01, .comb_mode[3]   = 0x01, .comb_mode[4]  	= 0x01, .comb_mode[5]   = 0x01,
/*B9 0xb9*/	.h_pll_op_a[0]  = 0x72, .h_pll_op_a[1]  = 0x72, .h_pll_op_a[2]  = 0x72, .h_pll_op_a[3]  = 0x72, .h_pll_op_a[4]  = 0x72, .h_pll_op_a[5]  = 0x72,
/*B9 0x57*/	.mem_path[0]	= 0x00, .mem_path[1]	= 0x00, .mem_path[2]	= 0x00, .mem_path[3]	= 0x00, .mem_path[4]	= 0x00, .mem_path[5]	= 0x00,
			.fsc_lock_speed[0] = 0xdc, .fsc_lock_speed[1] = 0xdc, .fsc_lock_speed[2] = 0xdc, .fsc_lock_speed[3] = 0xdc, .fsc_lock_speed[4] = 0xdc, .fsc_lock_speed[5] = 0xdc,

/*B0 0x81*/	.format_set1[0] = 0x02, .format_set1[1] = 0x02, .format_set1[2] = 0x02, .format_set1[3] = 0x02, .format_set1[4] = 0x02, .format_set1[5] = 0x02,
/*B0 0x85*/	.format_set2[0] = 0x04, .format_set2[1] = 0x04, .format_set2[2] = 0x04, .format_set2[3] = 0x04, .format_set2[4] = 0x04, .format_set2[5] = 0x04,

/*B0 0x64*/ .v_delay[0]     = 0x21, .v_delay[1]     = 0x21, .v_delay[2]     = 0x21, .v_delay[3]     = 0x21, .v_delay[4]     = 0x21, .v_delay[5]     = 0x21,
		},
	},

		[ AHD20_960P_25P ] = { /* o */
		/* base */
		{
		.eq_bypass[0] 	= 0x62, .eq_bypass[1] 	= 0x22, .eq_bypass[2] 	= 0x22, .eq_bypass[3] 	= 0x22, .eq_bypass[4] 	= 0x22, .eq_bypass[5] 	= 0x22,    // Bank5 0x30
		.eq_band_sel[0] = 0x77, .eq_band_sel[1] = 0x77, .eq_band_sel[2] = 0x77, .eq_band_sel[3] = 0x77, .eq_band_sel[4] = 0x57, .eq_band_sel[5] = 0x57,    // BankA 0x31
		.eq_gain_sel[0] = 0x78, .eq_gain_sel[1] = 0x7b, .eq_gain_sel[2] = 0x7f, .eq_gain_sel[3] = 0x7f, .eq_gain_sel[4] = 0x7f, .eq_gain_sel[5] = 0x7f,    // BankA 0x32
		.deq_a_on[0] 	= 0x00, .deq_a_on[1] 	= 0x01, .deq_a_on[2] 	= 0x01, .deq_a_on[3] 	= 0x01, .deq_a_on[4] 	= 0x01, .deq_a_on[5] 	= 0x01,    // BankA 0x33
		.deq_a_sel[0] 	= 0x00, .deq_a_sel[1] 	= 0x91, .deq_a_sel[2] 	= 0x87, .deq_a_sel[3] 	= 0x89, .deq_a_sel[4] 	= 0x93, .deq_a_sel[5] 	= 0x94,    // BankA 0x34
		.deq_b_sel[0] 	= 0x00, .deq_b_sel[1] 	= 0x00, .deq_b_sel[2] 	= 0x00, .deq_b_sel[3] 	= 0x00, .deq_b_sel[4] 	= 0x00, .deq_b_sel[5] 	= 0x00,    // BankA 0x35
		},
		/* coeff */
		{
		.deqA_01[0] = 0xAC, .deqA_01[1] = 0xAC, .deqA_01[2] = 0xAC, .deqA_01[3] = 0xAC, .deqA_01[4] = 0xAC, .deqA_01[5] = 0xAC,		// BankA 0x30
		.deqA_02[0] = 0x78, .deqA_02[1] = 0x78, .deqA_02[2] = 0x78, .deqA_02[3] = 0x78, .deqA_02[4] = 0x78, .deqA_02[5] = 0x78,		// BankA 0x31
		.deqA_03[0] = 0x17, .deqA_03[1] = 0x17, .deqA_03[2] = 0x17, .deqA_03[3] = 0x17, .deqA_03[4] = 0x17, .deqA_03[5] = 0x17,		// BankA 0x32
		.deqA_04[0] = 0xC1, .deqA_04[1] = 0xC1, .deqA_04[2] = 0xC1, .deqA_04[3] = 0xC1, .deqA_04[4] = 0xC1, .deqA_04[5] = 0xC1,     // BankA 0x33
		.deqA_05[0] = 0x40, .deqA_05[1] = 0x40, .deqA_05[2] = 0x40, .deqA_05[3] = 0x40, .deqA_05[4] = 0x40, .deqA_05[5] = 0x40,     // BankA 0x34
		.deqA_06[0] = 0x00, .deqA_06[1] = 0x00, .deqA_06[2] = 0x00, .deqA_06[3] = 0x00, .deqA_06[4] = 0x00, .deqA_06[5] = 0x00,     // BankA 0x35
		.deqA_07[0] = 0xC3, .deqA_07[1] = 0xC3, .deqA_07[2] = 0xC3, .deqA_07[3] = 0xC3, .deqA_07[4] = 0xC3, .deqA_07[5] = 0xC3,     // BankA 0x36
		.deqA_08[0] = 0x0A, .deqA_08[1] = 0x0A, .deqA_08[2] = 0x0A, .deqA_08[3] = 0x0A, .deqA_08[4] = 0x0A, .deqA_08[5] = 0x0A,     // BankA 0x37
		.deqA_09[0] = 0x00, .deqA_09[1] = 0x00, .deqA_09[2] = 0x00, .deqA_09[3] = 0x00, .deqA_09[4] = 0x00, .deqA_09[5] = 0x00,     // BankA 0x38
		.deqA_10[0] = 0x02, .deqA_10[1] = 0x02, .deqA_10[2] = 0x02, .deqA_10[3] = 0x02, .deqA_10[4] = 0x02, .deqA_10[5] = 0x02,     // BankA 0x39
		.deqA_11[0] = 0x00, .deqA_11[1] = 0x00, .deqA_11[2] = 0x00, .deqA_11[3] = 0x00, .deqA_11[4] = 0x00, .deqA_11[5] = 0x00,     // BankA 0x3a
		.deqA_12[0] = 0xB2, .deqA_12[1] = 0xB2, .deqA_12[2] = 0xB2, .deqA_12[3] = 0xB2, .deqA_12[4] = 0xB2, .deqA_12[5] = 0xB2,     // BankA 0x3b
		},
		/* color */
		{
		.contrast[0] 		= 0x86, .contrast[1] 		= 0x82, .contrast[2] 		= 0x82, .contrast[3] 		= 0x7e, .contrast[4] 		= 0x7c, .contrast[5] 		= 0x77,
		.h_peaking[0] 		= 0x00, .h_peaking[1] 		= 0x00, .h_peaking[2] 		= 0x00, .h_peaking[3] 		= 0x00, .h_peaking[4] 		= 0x0f, .h_peaking[5] 		= 0x0f,
		.c_filter[0]		= 0x82, .c_filter[1] 		= 0x82, .c_filter[2]	 	= 0x82, .c_filter[3] 		= 0x82, .c_filter[4] 		= 0xa2, .c_filter[5] 		= 0xb2,

		.hue[0] 			= 0x00, .hue[1] 			= 0x00, .hue[2] 			= 0x00, .hue[3] 			= 0xfe, .hue[4] 			= 0xfe, .hue[5] 			= 0xfe,
		.u_gain[0] 			= 0x00, .u_gain[1] 			= 0x00, .u_gain[2] 			= 0x04, .u_gain[3] 			= 0x10, .u_gain[4] 			= 0x10, .u_gain[5] 			= 0x18,
		.v_gain[0] 			= 0x00, .v_gain[1] 			= 0x00, .v_gain[2] 			= 0xf0, .v_gain[3] 			= 0x0e, .v_gain[4] 			= 0x0e, .v_gain[5] 			= 0x14,
		.u_offset[0] 		= 0xfe, .u_offset[1] 		= 0xfe, .u_offset[2] 		= 0xfe, .u_offset[3] 		= 0xfe, .u_offset[4] 		= 0xfe, .u_offset[5] 		= 0xfe,
		.v_offset[0] 		= 0xfb, .v_offset[1] 		= 0xfb, .v_offset[2] 		= 0xfb, .v_offset[3] 		= 0xfb, .v_offset[4] 		= 0xfb, .v_offset[5] 		= 0xfb,

		.black_level[0] 	= 0x80, .black_level[1] 	= 0x81, .black_level[2] 	= 0x81, .black_level[3] 	= 0x83, .black_level[4] 	= 0x83, .black_level[5] 	= 0x87,
		.acc_ref[0]			= 0x57, .acc_ref[1]			= 0x57, .acc_ref[2]			= 0x57, .acc_ref[3]			= 0x57, .acc_ref[4]			= 0x57, .acc_ref[5]			= 0x57,
		.cti_delay[0]		= 0x80, .cti_delay[1]		= 0x80, .cti_delay[2]		= 0x80, .cti_delay[3]		= 0x80, .cti_delay[4]		= 0x80, .cti_delay[5]		= 0x80,
		.sub_saturation[0] 	= 0xa8, .sub_saturation[1] 	= 0xa8, .sub_saturation[2] 	= 0xa8, .sub_saturation[3] 	= 0xa8, .sub_saturation[4] 	= 0x90, .sub_saturation[5] 	= 0x90,

		.burst_dec_a[0] 	= 0x2a, .burst_dec_a[1] 	= 0x2a, .burst_dec_a[2] 	= 0x2a, .burst_dec_a[3] 	= 0x2a, .burst_dec_a[4] 	= 0x2a, .burst_dec_a[5] 	= 0x2a,
		.burst_dec_b[0] 	= 0x00, .burst_dec_b[1] 	= 0x00, .burst_dec_b[2] 	= 0x00, .burst_dec_b[3] 	= 0x00, .burst_dec_b[4] 	= 0x00, .burst_dec_b[5] 	= 0x00,
		.burst_dec_c[0] 	= 0x30, .burst_dec_c[1] 	= 0x30, .burst_dec_c[2] 	= 0x30, .burst_dec_c[3] 	= 0x30, .burst_dec_c[4] 	= 0x30, .burst_dec_c[5] 	= 0x30,

		.c_option[0] 		= 0x80, .c_option[1] 		= 0x80, .c_option[2] 		= 0x90, .c_option[3] 		= 0x90, .c_option[4] 		= 0x90, .c_option[5] 		= 0xa0,

		.y_filter_b[0]		= 0x10, .y_filter_b[1]		= 0x10, .y_filter_b[2]		= 0x10, .y_filter_b[3]		= 0x10, .y_filter_b[4]		= 0x10, .y_filter_b[5]		= 0x10,
		.y_filter_b_sel[0]	= 0x1e,	.y_filter_b_sel[1]	= 0x1e,	.y_filter_b_sel[2]	= 0x1e, .y_filter_b_sel[3]	= 0x1e, .y_filter_b_sel[4]	= 0x1e, .y_filter_b_sel[5]	= 0x1e,
		},
		/* timing_a */
		{
		.h_delay_a[0] = 0x86, .h_delay_a[1] = 0x84, .h_delay_a[2] = 0x80, .h_delay_a[3] = 0x80, .h_delay_a[4] = 0x80, .h_delay_a[5] = 0x80,
		.h_delay_b[0] = 0x10, .h_delay_b[1] = 0x10, .h_delay_b[2] = 0x10, .h_delay_b[3] = 0x10, .h_delay_b[4] = 0x10, .h_delay_b[5] = 0x10,
		.h_delay_c[0] = 0x03, .h_delay_c[1] = 0x03, .h_delay_c[2] = 0x03, .h_delay_c[3] = 0x03, .h_delay_c[4] = 0x03, .h_delay_c[5] = 0x03,
		.y_delay[0]   = 0x05, .y_delay[1]   = 0x03, .y_delay[2]   = 0x03, .y_delay[3]   = 0x03, .y_delay[4]   = 0x03, .y_delay[5] =   0x03,

		},
		/* clk */
		{
		.clk_adc[0] = 0x02, .clk_adc[1] = 0x02, .clk_adc[2] = 0x02, .clk_adc[3] = 0x02, .clk_adc[4] = 0x02, .clk_adc[5] = 0x02,
		.clk_dec[0] = 0x40, .clk_dec[1] = 0x40, .clk_dec[2] = 0x40, .clk_dec[3] = 0x40, .clk_dec[4] = 0x40, .clk_dec[5] = 0x40,
		},
		/* timing_b */
		{
		/*B9 0x96*/	.h_scaler1[0]  = 0x00, .h_scaler1[1]   = 0x00, .h_scaler1[2]   = 0x00, .h_scaler1[3]   = 0x00, .h_scaler1[4]   = 0x00, .h_scaler1[5]   = 0x00,
		/*B9 0x97*/	.h_scaler2[0]  = 0x00, .h_scaler2[1]   = 0x00, .h_scaler2[2]   = 0x00, .h_scaler2[3]   = 0x00, .h_scaler2[4]   = 0x00, .h_scaler2[5]   = 0x00,
		/*B9 0x98*/	.h_scaler3[0]  = 0x00, .h_scaler3[1]   = 0x00, .h_scaler3[2]   = 0x00, .h_scaler3[3]   = 0x00, .h_scaler3[4]   = 0x00, .h_scaler3[5]   = 0x00,
		/*B9 0x99*/	.h_scaler4[0]  = 0x00, .h_scaler4[1]   = 0x00, .h_scaler4[2]   = 0x00, .h_scaler4[3]   = 0x00, .h_scaler4[4]   = 0x00, .h_scaler4[5]   = 0x00,
		/*B9 0x9a*/	.h_scaler5[0]  = 0x00, .h_scaler5[1]   = 0x00, .h_scaler5[2]   = 0x00, .h_scaler5[3]   = 0x00, .h_scaler5[4]   = 0x00, .h_scaler5[5]   = 0x00,
		/*B9 0x9b*/	.h_scaler6[0]  = 0x00, .h_scaler6[1]   = 0x00, .h_scaler6[2]   = 0x00, .h_scaler6[3]   = 0x00, .h_scaler6[4]   = 0x00, .h_scaler6[5]   = 0x00,
		/*B9 0x9c*/	.h_scaler7[0]  = 0x00, .h_scaler7[1]   = 0x00, .h_scaler7[2]   = 0x00, .h_scaler7[3]   = 0x00, .h_scaler7[4]   = 0x00, .h_scaler7[5]   = 0x00,
		/*B9 0x9d*/	.h_scaler8[0]  = 0x00, .h_scaler8[1]   = 0x00, .h_scaler8[2]   = 0x00, .h_scaler8[3]   = 0x00, .h_scaler8[4]   = 0x00, .h_scaler8[5]   = 0x00,
		/*B9 0x9e*/	.h_scaler9[0]  = 0x00, .h_scaler9[1]   = 0x00, .h_scaler9[2]   = 0x00, .h_scaler9[3]   = 0x00, .h_scaler9[4]   = 0x00, .h_scaler9[5]   = 0x00,


		/*B9 0x40*/	.pn_auto[0]    	= 0x00, .pn_auto[1]		= 0x00, .pn_auto[2]    	= 0x00, .pn_auto[3]    	= 0x00, .pn_auto[4]    	= 0x00, .pn_auto[5]    	= 0x00,

		/*B5 0x90*/	.comb_mode[0]      = 0x01, .comb_mode[1]	  = 0x01, .comb_mode[2]      = 0x01, .comb_mode[3]      = 0x01, .comb_mode[4]  	   = 0x01, .comb_mode[5]      = 0x01,
		/*B9 0xb9*/	.h_pll_op_a[0]     = 0x72, .h_pll_op_a[1]     = 0x72, .h_pll_op_a[2]     = 0x72, .h_pll_op_a[3]     = 0x72, .h_pll_op_a[4]     = 0x72, .h_pll_op_a[5]     = 0x72,
		/*B9 0x57*/	.mem_path[0]	   = 0x00, .mem_path[1]	      = 0x00, .mem_path[2]	     = 0x00, .mem_path[3]	    = 0x00, .mem_path[4]	   = 0x00, .mem_path[5]	      = 0x00,
		.fsc_lock_speed[0] = 0xdc, .fsc_lock_speed[1] = 0xdc, .fsc_lock_speed[2] = 0xdc, .fsc_lock_speed[3] = 0xdc, .fsc_lock_speed[4] = 0xdc, .fsc_lock_speed[5] = 0xdc,

		/*B0 0x81*/	.format_set1[0] = 0x03, .format_set1[1] = 0x03, .format_set1[2] = 0x03, .format_set1[3] = 0x03, .format_set1[4] = 0x03, .format_set1[5] = 0x03,
		/*B0 0x85*/	.format_set2[0] = 0x00, .format_set2[1] = 0x00, .format_set2[2] = 0x00, .format_set2[3] = 0x00, .format_set2[4] = 0x00, .format_set2[5] = 0x00,

		/*B0 0x64*/ .v_delay[0]     = 0x21, .v_delay[1]     = 0x21, .v_delay[2]     = 0x21, .v_delay[3]     = 0x21, .v_delay[4]     = 0x21, .v_delay[5]     = 0x21,
		},
		},

		[ AHD20_960P_30P ] = { /* o */
		/* base */
		{
		.eq_bypass[0] 	= 0x62, .eq_bypass[1] 	= 0x22, .eq_bypass[2] 	= 0x22, .eq_bypass[3] 	= 0x22, .eq_bypass[4] 	= 0x22, .eq_bypass[5] 	= 0x22,    // Bank5 0x30
		.eq_band_sel[0] = 0x77, .eq_band_sel[1] = 0x77, .eq_band_sel[2] = 0x77, .eq_band_sel[3] = 0x77, .eq_band_sel[4] = 0x57, .eq_band_sel[5] = 0x57,    // BankA 0x31
		.eq_gain_sel[0] = 0x78, .eq_gain_sel[1] = 0x7b, .eq_gain_sel[2] = 0x7f, .eq_gain_sel[3] = 0x7f, .eq_gain_sel[4] = 0x7f, .eq_gain_sel[5] = 0x7f,    // BankA 0x32
		.deq_a_on[0] 	= 0x00, .deq_a_on[1] 	= 0x01, .deq_a_on[2] 	= 0x01, .deq_a_on[3] 	= 0x01, .deq_a_on[4] 	= 0x01, .deq_a_on[5] 	= 0x01,    // BankA 0x33
		.deq_a_sel[0] 	= 0x00, .deq_a_sel[1] 	= 0x91, .deq_a_sel[2] 	= 0x87, .deq_a_sel[3] 	= 0x89, .deq_a_sel[4] 	= 0x93, .deq_a_sel[5] 	= 0x94,    // BankA 0x34
		.deq_b_sel[0] 	= 0x00, .deq_b_sel[1] 	= 0x00, .deq_b_sel[2] 	= 0x00, .deq_b_sel[3] 	= 0x00, .deq_b_sel[4] 	= 0x00, .deq_b_sel[5] 	= 0x00,    // BankA 0x35
		},
		/* coeff */
		{
		.deqA_01[0] = 0xAC, .deqA_01[1] = 0xAC, .deqA_01[2] = 0xAC, .deqA_01[3] = 0xAC, .deqA_01[4] = 0xAC, .deqA_01[5] = 0xAC,		// BankA 0x30
		.deqA_02[0] = 0x78, .deqA_02[1] = 0x78, .deqA_02[2] = 0x78, .deqA_02[3] = 0x78, .deqA_02[4] = 0x78, .deqA_02[5] = 0x78,		// BankA 0x31
		.deqA_03[0] = 0x17, .deqA_03[1] = 0x17, .deqA_03[2] = 0x17, .deqA_03[3] = 0x17, .deqA_03[4] = 0x17, .deqA_03[5] = 0x17,		// BankA 0x32
		.deqA_04[0] = 0xC1, .deqA_04[1] = 0xC1, .deqA_04[2] = 0xC1, .deqA_04[3] = 0xC1, .deqA_04[4] = 0xC1, .deqA_04[5] = 0xC1,     // BankA 0x33
		.deqA_05[0] = 0x40, .deqA_05[1] = 0x40, .deqA_05[2] = 0x40, .deqA_05[3] = 0x40, .deqA_05[4] = 0x40, .deqA_05[5] = 0x40,     // BankA 0x34
		.deqA_06[0] = 0x00, .deqA_06[1] = 0x00, .deqA_06[2] = 0x00, .deqA_06[3] = 0x00, .deqA_06[4] = 0x00, .deqA_06[5] = 0x00,     // BankA 0x35
		.deqA_07[0] = 0xC3, .deqA_07[1] = 0xC3, .deqA_07[2] = 0xC3, .deqA_07[3] = 0xC3, .deqA_07[4] = 0xC3, .deqA_07[5] = 0xC3,     // BankA 0x36
		.deqA_08[0] = 0x0A, .deqA_08[1] = 0x0A, .deqA_08[2] = 0x0A, .deqA_08[3] = 0x0A, .deqA_08[4] = 0x0A, .deqA_08[5] = 0x0A,     // BankA 0x37
		.deqA_09[0] = 0x00, .deqA_09[1] = 0x00, .deqA_09[2] = 0x00, .deqA_09[3] = 0x00, .deqA_09[4] = 0x00, .deqA_09[5] = 0x00,     // BankA 0x38
		.deqA_10[0] = 0x02, .deqA_10[1] = 0x02, .deqA_10[2] = 0x02, .deqA_10[3] = 0x02, .deqA_10[4] = 0x02, .deqA_10[5] = 0x02,     // BankA 0x39
		.deqA_11[0] = 0x00, .deqA_11[1] = 0x00, .deqA_11[2] = 0x00, .deqA_11[3] = 0x00, .deqA_11[4] = 0x00, .deqA_11[5] = 0x00,     // BankA 0x3a
		.deqA_12[0] = 0xB2, .deqA_12[1] = 0xB2, .deqA_12[2] = 0xB2, .deqA_12[3] = 0xB2, .deqA_12[4] = 0xB2, .deqA_12[5] = 0xB2,     // BankA 0x3b
		},
		/* color */
		{
		.contrast[0] 		= 0x86, .contrast[1] 		= 0x82, .contrast[2] 		= 0x82, .contrast[3] 		= 0x7e, .contrast[4] 		= 0x7c, .contrast[5] 		= 0x77,
		.h_peaking[0] 		= 0x00, .h_peaking[1] 		= 0x00, .h_peaking[2] 		= 0x00, .h_peaking[3] 		= 0x00, .h_peaking[4] 		= 0x0f, .h_peaking[5] 		= 0x0f,
		.c_filter[0]		= 0x82, .c_filter[1] 		= 0x82, .c_filter[2]	 	= 0x82, .c_filter[3] 		= 0x82, .c_filter[4] 		= 0xa2, .c_filter[5] 		= 0xb2,

		.hue[0] 			= 0x00, .hue[1] 			= 0x00, .hue[2] 			= 0x00, .hue[3] 			= 0xfe, .hue[4] 			= 0xfe, .hue[5] 			= 0xfe,
		.u_gain[0] 			= 0x00, .u_gain[1] 			= 0x00, .u_gain[2] 			= 0x04, .u_gain[3] 			= 0x10, .u_gain[4] 			= 0x10, .u_gain[5] 			= 0x18,
		.v_gain[0] 			= 0x00, .v_gain[1] 			= 0x00, .v_gain[2] 			= 0xf0, .v_gain[3] 			= 0x0e, .v_gain[4] 			= 0x0e, .v_gain[5] 			= 0x14,
		.u_offset[0] 		= 0xfe, .u_offset[1] 		= 0xfe, .u_offset[2] 		= 0xfe, .u_offset[3] 		= 0xfe, .u_offset[4] 		= 0xfe, .u_offset[5] 		= 0xfe,
		.v_offset[0] 		= 0xfb, .v_offset[1] 		= 0xfb, .v_offset[2] 		= 0xfb, .v_offset[3] 		= 0xfb, .v_offset[4] 		= 0xfb, .v_offset[5] 		= 0xfb,

		.black_level[0] 	= 0x80, .black_level[1] 	= 0x81, .black_level[2] 	= 0x81, .black_level[3] 	= 0x83, .black_level[4] 	= 0x83, .black_level[5] 	= 0x87,
		.acc_ref[0]			= 0x57, .acc_ref[1]			= 0x57, .acc_ref[2]			= 0x57, .acc_ref[3]			= 0x57, .acc_ref[4]			= 0x57, .acc_ref[5]			= 0x57,
		.cti_delay[0]		= 0x80, .cti_delay[1]		= 0x80, .cti_delay[2]		= 0x80, .cti_delay[3]		= 0x80, .cti_delay[4]		= 0x80, .cti_delay[5]		= 0x80,
		.sub_saturation[0] 	= 0xa8, .sub_saturation[1] 	= 0xa8, .sub_saturation[2] 	= 0xa8, .sub_saturation[3] 	= 0xa8, .sub_saturation[4] 	= 0x90, .sub_saturation[5] 	= 0x90,

		.burst_dec_a[0] 	= 0x2a, .burst_dec_a[1] 	= 0x2a, .burst_dec_a[2] 	= 0x2a, .burst_dec_a[3] 	= 0x2a, .burst_dec_a[4] 	= 0x2a, .burst_dec_a[5] 	= 0x2a,
		.burst_dec_b[0] 	= 0x00, .burst_dec_b[1] 	= 0x00, .burst_dec_b[2] 	= 0x00, .burst_dec_b[3] 	= 0x00, .burst_dec_b[4] 	= 0x00, .burst_dec_b[5] 	= 0x00,
		.burst_dec_c[0] 	= 0x30, .burst_dec_c[1] 	= 0x30, .burst_dec_c[2] 	= 0x30, .burst_dec_c[3] 	= 0x30, .burst_dec_c[4] 	= 0x30, .burst_dec_c[5] 	= 0x30,

		.c_option[0] 		= 0x80, .c_option[1] 		= 0x80, .c_option[2] 		= 0x90, .c_option[3] 		= 0x90, .c_option[4] 		= 0x90, .c_option[5] 		= 0xa0,

		.y_filter_b[0]		= 0x10, .y_filter_b[1]		= 0x10, .y_filter_b[2]		= 0x10, .y_filter_b[3]		= 0x10, .y_filter_b[4]		= 0x10, .y_filter_b[5]		= 0x10,
		.y_filter_b_sel[0]	= 0x1e,	.y_filter_b_sel[1]	= 0x1e,	.y_filter_b_sel[2]	= 0x1e, .y_filter_b_sel[3]	= 0x1e, .y_filter_b_sel[4]	= 0x1e, .y_filter_b_sel[5]	= 0x1e,
		},
		/* timing_a */
		{
		.h_delay_a[0] = 0x86, .h_delay_a[1] = 0x84, .h_delay_a[2] = 0x80, .h_delay_a[3] = 0x80, .h_delay_a[4] = 0x80, .h_delay_a[5] = 0x80,
		.h_delay_b[0] = 0x10, .h_delay_b[1] = 0x10, .h_delay_b[2] = 0x10, .h_delay_b[3] = 0x10, .h_delay_b[4] = 0x10, .h_delay_b[5] = 0x10,
		.h_delay_c[0] = 0x03, .h_delay_c[1] = 0x03, .h_delay_c[2] = 0x03, .h_delay_c[3] = 0x03, .h_delay_c[4] = 0x03, .h_delay_c[5] = 0x03,
		.y_delay[0]   = 0x05, .y_delay[1]   = 0x03, .y_delay[2]   = 0x03, .y_delay[3]   = 0x03, .y_delay[4]   = 0x03, .y_delay[5] =   0x03,

		},
		/* clk */
		{
		.clk_adc[0] = 0x02, .clk_adc[1] = 0x02, .clk_adc[2] = 0x02, .clk_adc[3] = 0x02, .clk_adc[4] = 0x02, .clk_adc[5] = 0x02,
		.clk_dec[0] = 0x40, .clk_dec[1] = 0x40, .clk_dec[2] = 0x40, .clk_dec[3] = 0x40, .clk_dec[4] = 0x40, .clk_dec[5] = 0x40,
		},
		/* timing_b */
		{
		/*B9 0x96*/	.h_scaler1[0]  = 0x00, .h_scaler1[1]   = 0x00, .h_scaler1[2]   = 0x00, .h_scaler1[3]   = 0x00, .h_scaler1[4]   = 0x00, .h_scaler1[5]   = 0x00,
		/*B9 0x97*/	.h_scaler2[0]  = 0x00, .h_scaler2[1]   = 0x00, .h_scaler2[2]   = 0x00, .h_scaler2[3]   = 0x00, .h_scaler2[4]   = 0x00, .h_scaler2[5]   = 0x00,
		/*B9 0x98*/	.h_scaler3[0]  = 0x00, .h_scaler3[1]   = 0x00, .h_scaler3[2]   = 0x00, .h_scaler3[3]   = 0x00, .h_scaler3[4]   = 0x00, .h_scaler3[5]   = 0x00,
		/*B9 0x99*/	.h_scaler4[0]  = 0x00, .h_scaler4[1]   = 0x00, .h_scaler4[2]   = 0x00, .h_scaler4[3]   = 0x00, .h_scaler4[4]   = 0x00, .h_scaler4[5]   = 0x00,
		/*B9 0x9a*/	.h_scaler5[0]  = 0x00, .h_scaler5[1]   = 0x00, .h_scaler5[2]   = 0x00, .h_scaler5[3]   = 0x00, .h_scaler5[4]   = 0x00, .h_scaler5[5]   = 0x00,
		/*B9 0x9b*/	.h_scaler6[0]  = 0x00, .h_scaler6[1]   = 0x00, .h_scaler6[2]   = 0x00, .h_scaler6[3]   = 0x00, .h_scaler6[4]   = 0x00, .h_scaler6[5]   = 0x00,
		/*B9 0x9c*/	.h_scaler7[0]  = 0x00, .h_scaler7[1]   = 0x00, .h_scaler7[2]   = 0x00, .h_scaler7[3]   = 0x00, .h_scaler7[4]   = 0x00, .h_scaler7[5]   = 0x00,
		/*B9 0x9d*/	.h_scaler8[0]  = 0x00, .h_scaler8[1]   = 0x00, .h_scaler8[2]   = 0x00, .h_scaler8[3]   = 0x00, .h_scaler8[4]   = 0x00, .h_scaler8[5]   = 0x00,
		/*B9 0x9e*/	.h_scaler9[0]  = 0x00, .h_scaler9[1]   = 0x00, .h_scaler9[2]   = 0x00, .h_scaler9[3]   = 0x00, .h_scaler9[4]   = 0x00, .h_scaler9[5]   = 0x00,


		/*B9 0x40*/	.pn_auto[0]    	= 0x00, .pn_auto[1]		= 0x00, .pn_auto[2]    	= 0x00, .pn_auto[3]    	= 0x00, .pn_auto[4]    	= 0x00, .pn_auto[5]    	= 0x00,

		/*B5 0x90*/	.comb_mode[0]      = 0x01, .comb_mode[1]	  = 0x01, .comb_mode[2]      = 0x01, .comb_mode[3]      = 0x01, .comb_mode[4]  	   = 0x01, .comb_mode[5]      = 0x01,
		/*B9 0xb9*/	.h_pll_op_a[0]     = 0x72, .h_pll_op_a[1]     = 0x72, .h_pll_op_a[2]     = 0x72, .h_pll_op_a[3]     = 0x72, .h_pll_op_a[4]     = 0x72, .h_pll_op_a[5]     = 0x72,
		/*B9 0x57*/	.mem_path[0]	   = 0x00, .mem_path[1]	      = 0x00, .mem_path[2]	     = 0x00, .mem_path[3]	    = 0x00, .mem_path[4]	   = 0x00, .mem_path[5]	      = 0x00,
		.fsc_lock_speed[0] = 0xdc, .fsc_lock_speed[1] = 0xdc, .fsc_lock_speed[2] = 0xdc, .fsc_lock_speed[3] = 0xdc, .fsc_lock_speed[4] = 0xdc, .fsc_lock_speed[5] = 0xdc,

		/*B0 0x81*/	.format_set1[0] = 0x03, .format_set1[1] = 0x03, .format_set1[2] = 0x03, .format_set1[3] = 0x03, .format_set1[4] = 0x03, .format_set1[5] = 0x03,
		/*B0 0x85*/	.format_set2[0] = 0x00, .format_set2[1] = 0x00, .format_set2[2] = 0x00, .format_set2[3] = 0x00, .format_set2[4] = 0x00, .format_set2[5] = 0x00,

		/*B0 0x64*/ .v_delay[0]     = 0x21, .v_delay[1]     = 0x21, .v_delay[2]     = 0x21, .v_delay[3]     = 0x21, .v_delay[4]     = 0x21, .v_delay[5]     = 0x21,
		},
		},

		[ AHD20_960P_50P ] = { /* o */
		/* base */
		{
		.eq_bypass[0] 	= 0x62, .eq_bypass[1] 	= 0x22, .eq_bypass[2] 	= 0x22, .eq_bypass[3] 	= 0x22, .eq_bypass[4] 	= 0x22, .eq_bypass[5] 	= 0x22,    // Bank5 0x30
		.eq_band_sel[0] = 0x77, .eq_band_sel[1] = 0x77, .eq_band_sel[2] = 0x77, .eq_band_sel[3] = 0x77, .eq_band_sel[4] = 0x57, .eq_band_sel[5] = 0x57,    // BankA 0x31
		.eq_gain_sel[0] = 0x78, .eq_gain_sel[1] = 0x7b, .eq_gain_sel[2] = 0x7f, .eq_gain_sel[3] = 0x7f, .eq_gain_sel[4] = 0x7f, .eq_gain_sel[5] = 0x7f,    // BankA 0x32
		.deq_a_on[0] 	= 0x00, .deq_a_on[1] 	= 0x01, .deq_a_on[2] 	= 0x01, .deq_a_on[3] 	= 0x01, .deq_a_on[4] 	= 0x01, .deq_a_on[5] 	= 0x01,    // BankA 0x33
		.deq_a_sel[0] 	= 0x00, .deq_a_sel[1] 	= 0x91, .deq_a_sel[2] 	= 0x87, .deq_a_sel[3] 	= 0x89, .deq_a_sel[4] 	= 0x93, .deq_a_sel[5] 	= 0x94,    // BankA 0x34
		.deq_b_sel[0] 	= 0x00, .deq_b_sel[1] 	= 0x00, .deq_b_sel[2] 	= 0x00, .deq_b_sel[3] 	= 0x00, .deq_b_sel[4] 	= 0x00, .deq_b_sel[5] 	= 0x00,    // BankA 0x35
		},
		/* coeff */
		{
		.deqA_01[0] = 0xAC, .deqA_01[1] = 0xAC, .deqA_01[2] = 0xAC, .deqA_01[3] = 0xAC, .deqA_01[4] = 0xAC, .deqA_01[5] = 0xAC,		// BankA 0x30
		.deqA_02[0] = 0x78, .deqA_02[1] = 0x78, .deqA_02[2] = 0x78, .deqA_02[3] = 0x78, .deqA_02[4] = 0x78, .deqA_02[5] = 0x78,		// BankA 0x31
		.deqA_03[0] = 0x17, .deqA_03[1] = 0x17, .deqA_03[2] = 0x17, .deqA_03[3] = 0x17, .deqA_03[4] = 0x17, .deqA_03[5] = 0x17,		// BankA 0x32
		.deqA_04[0] = 0xC1, .deqA_04[1] = 0xC1, .deqA_04[2] = 0xC1, .deqA_04[3] = 0xC1, .deqA_04[4] = 0xC1, .deqA_04[5] = 0xC1,     // BankA 0x33
		.deqA_05[0] = 0x40, .deqA_05[1] = 0x40, .deqA_05[2] = 0x40, .deqA_05[3] = 0x40, .deqA_05[4] = 0x40, .deqA_05[5] = 0x40,     // BankA 0x34
		.deqA_06[0] = 0x00, .deqA_06[1] = 0x00, .deqA_06[2] = 0x00, .deqA_06[3] = 0x00, .deqA_06[4] = 0x00, .deqA_06[5] = 0x00,     // BankA 0x35
		.deqA_07[0] = 0xC3, .deqA_07[1] = 0xC3, .deqA_07[2] = 0xC3, .deqA_07[3] = 0xC3, .deqA_07[4] = 0xC3, .deqA_07[5] = 0xC3,     // BankA 0x36
		.deqA_08[0] = 0x0A, .deqA_08[1] = 0x0A, .deqA_08[2] = 0x0A, .deqA_08[3] = 0x0A, .deqA_08[4] = 0x0A, .deqA_08[5] = 0x0A,     // BankA 0x37
		.deqA_09[0] = 0x00, .deqA_09[1] = 0x00, .deqA_09[2] = 0x00, .deqA_09[3] = 0x00, .deqA_09[4] = 0x00, .deqA_09[5] = 0x00,     // BankA 0x38
		.deqA_10[0] = 0x02, .deqA_10[1] = 0x02, .deqA_10[2] = 0x02, .deqA_10[3] = 0x02, .deqA_10[4] = 0x02, .deqA_10[5] = 0x02,     // BankA 0x39
		.deqA_11[0] = 0x00, .deqA_11[1] = 0x00, .deqA_11[2] = 0x00, .deqA_11[3] = 0x00, .deqA_11[4] = 0x00, .deqA_11[5] = 0x00,     // BankA 0x3a
		.deqA_12[0] = 0xB2, .deqA_12[1] = 0xB2, .deqA_12[2] = 0xB2, .deqA_12[3] = 0xB2, .deqA_12[4] = 0xB2, .deqA_12[5] = 0xB2,     // BankA 0x3b
		},
		/* color */
		{
		.contrast[0] 		= 0x86, .contrast[1] 		= 0x82, .contrast[2] 		= 0x82, .contrast[3] 		= 0x7e, .contrast[4] 		= 0x7c, .contrast[5] 		= 0x77,
		.h_peaking[0] 		= 0x00, .h_peaking[1] 		= 0x00, .h_peaking[2] 		= 0x00, .h_peaking[3] 		= 0x00, .h_peaking[4] 		= 0x0f, .h_peaking[5] 		= 0x0f,
		.c_filter[0]		= 0x82, .c_filter[1] 		= 0x82, .c_filter[2]	 	= 0x82, .c_filter[3] 		= 0x82, .c_filter[4] 		= 0xa2, .c_filter[5] 		= 0xb2,

		.hue[0] 			= 0x00, .hue[1] 			= 0x00, .hue[2] 			= 0x00, .hue[3] 			= 0xfe, .hue[4] 			= 0xfe, .hue[5] 			= 0xfe,
		.u_gain[0] 			= 0x00, .u_gain[1] 			= 0x00, .u_gain[2] 			= 0x04, .u_gain[3] 			= 0x10, .u_gain[4] 			= 0x10, .u_gain[5] 			= 0x18,
		.v_gain[0] 			= 0x00, .v_gain[1] 			= 0x00, .v_gain[2] 			= 0xf0, .v_gain[3] 			= 0x0e, .v_gain[4] 			= 0x0e, .v_gain[5] 			= 0x14,
		.u_offset[0] 		= 0xfe, .u_offset[1] 		= 0xfe, .u_offset[2] 		= 0xfe, .u_offset[3] 		= 0xfe, .u_offset[4] 		= 0xfe, .u_offset[5] 		= 0xfe,
		.v_offset[0] 		= 0xfb, .v_offset[1] 		= 0xfb, .v_offset[2] 		= 0xfb, .v_offset[3] 		= 0xfb, .v_offset[4] 		= 0xfb, .v_offset[5] 		= 0xfb,

		.black_level[0] 	= 0x80, .black_level[1] 	= 0x81, .black_level[2] 	= 0x81, .black_level[3] 	= 0x83, .black_level[4] 	= 0x83, .black_level[5] 	= 0x87,
		.acc_ref[0]			= 0x57, .acc_ref[1]			= 0x57, .acc_ref[2]			= 0x57, .acc_ref[3]			= 0x57, .acc_ref[4]			= 0x57, .acc_ref[5]			= 0x57,
		.cti_delay[0]		= 0x80, .cti_delay[1]		= 0x80, .cti_delay[2]		= 0x80, .cti_delay[3]		= 0x80, .cti_delay[4]		= 0x80, .cti_delay[5]		= 0x80,
		.sub_saturation[0] 	= 0xa8, .sub_saturation[1] 	= 0xa8, .sub_saturation[2] 	= 0xa8, .sub_saturation[3] 	= 0xa8, .sub_saturation[4] 	= 0x90, .sub_saturation[5] 	= 0x90,

		.burst_dec_a[0] 	= 0x2a, .burst_dec_a[1] 	= 0x2a, .burst_dec_a[2] 	= 0x2a, .burst_dec_a[3] 	= 0x2a, .burst_dec_a[4] 	= 0x2a, .burst_dec_a[5] 	= 0x2a,
		.burst_dec_b[0] 	= 0x00, .burst_dec_b[1] 	= 0x00, .burst_dec_b[2] 	= 0x00, .burst_dec_b[3] 	= 0x00, .burst_dec_b[4] 	= 0x00, .burst_dec_b[5] 	= 0x00,
		.burst_dec_c[0] 	= 0x30, .burst_dec_c[1] 	= 0x30, .burst_dec_c[2] 	= 0x30, .burst_dec_c[3] 	= 0x30, .burst_dec_c[4] 	= 0x30, .burst_dec_c[5] 	= 0x30,

		.c_option[0] 		= 0x80, .c_option[1] 		= 0x80, .c_option[2] 		= 0x90, .c_option[3] 		= 0x90, .c_option[4] 		= 0x90, .c_option[5] 		= 0xa0,

		.y_filter_b[0]		= 0x10, .y_filter_b[1]		= 0x10, .y_filter_b[2]		= 0x10, .y_filter_b[3]		= 0x10, .y_filter_b[4]		= 0x10, .y_filter_b[5]		= 0x10,
		.y_filter_b_sel[0]	= 0x1e,	.y_filter_b_sel[1]	= 0x1e,	.y_filter_b_sel[2]	= 0x1e, .y_filter_b_sel[3]	= 0x1e, .y_filter_b_sel[4]	= 0x1e, .y_filter_b_sel[5]	= 0x1e,
		},
		/* timing_a */
		{
		.h_delay_a[0] = 0x86, .h_delay_a[1] = 0x84, .h_delay_a[2] = 0x80, .h_delay_a[3] = 0x80, .h_delay_a[4] = 0x80, .h_delay_a[5] = 0x80,
		.h_delay_b[0] = 0x10, .h_delay_b[1] = 0x10, .h_delay_b[2] = 0x10, .h_delay_b[3] = 0x10, .h_delay_b[4] = 0x10, .h_delay_b[5] = 0x10,
		.h_delay_c[0] = 0x03, .h_delay_c[1] = 0x03, .h_delay_c[2] = 0x03, .h_delay_c[3] = 0x03, .h_delay_c[4] = 0x03, .h_delay_c[5] = 0x03,
		.y_delay[0]   = 0x05, .y_delay[1]   = 0x03, .y_delay[2]   = 0x03, .y_delay[3]   = 0x03, .y_delay[4]   = 0x03, .y_delay[5] =   0x03,

		},
		/* clk */
		{
		.clk_adc[0] = 0x02, .clk_adc[1] = 0x02, .clk_adc[2] = 0x02, .clk_adc[3] = 0x02, .clk_adc[4] = 0x02, .clk_adc[5] = 0x02,
		.clk_dec[0] = 0x40, .clk_dec[1] = 0x40, .clk_dec[2] = 0x40, .clk_dec[3] = 0x40, .clk_dec[4] = 0x40, .clk_dec[5] = 0x40,
		},
		/* timing_b */
		{
		/*B9 0x96*/	.h_scaler1[0]  = 0x00, .h_scaler1[1]   = 0x00, .h_scaler1[2]   = 0x00, .h_scaler1[3]   = 0x00, .h_scaler1[4]   = 0x00, .h_scaler1[5]   = 0x00,
		/*B9 0x97*/	.h_scaler2[0]  = 0x00, .h_scaler2[1]   = 0x00, .h_scaler2[2]   = 0x00, .h_scaler2[3]   = 0x00, .h_scaler2[4]   = 0x00, .h_scaler2[5]   = 0x00,
		/*B9 0x98*/	.h_scaler3[0]  = 0x00, .h_scaler3[1]   = 0x00, .h_scaler3[2]   = 0x00, .h_scaler3[3]   = 0x00, .h_scaler3[4]   = 0x00, .h_scaler3[5]   = 0x00,
		/*B9 0x99*/	.h_scaler4[0]  = 0x00, .h_scaler4[1]   = 0x00, .h_scaler4[2]   = 0x00, .h_scaler4[3]   = 0x00, .h_scaler4[4]   = 0x00, .h_scaler4[5]   = 0x00,
		/*B9 0x9a*/	.h_scaler5[0]  = 0x00, .h_scaler5[1]   = 0x00, .h_scaler5[2]   = 0x00, .h_scaler5[3]   = 0x00, .h_scaler5[4]   = 0x00, .h_scaler5[5]   = 0x00,
		/*B9 0x9b*/	.h_scaler6[0]  = 0x00, .h_scaler6[1]   = 0x00, .h_scaler6[2]   = 0x00, .h_scaler6[3]   = 0x00, .h_scaler6[4]   = 0x00, .h_scaler6[5]   = 0x00,
		/*B9 0x9c*/	.h_scaler7[0]  = 0x00, .h_scaler7[1]   = 0x00, .h_scaler7[2]   = 0x00, .h_scaler7[3]   = 0x00, .h_scaler7[4]   = 0x00, .h_scaler7[5]   = 0x00,
		/*B9 0x9d*/	.h_scaler8[0]  = 0x00, .h_scaler8[1]   = 0x00, .h_scaler8[2]   = 0x00, .h_scaler8[3]   = 0x00, .h_scaler8[4]   = 0x00, .h_scaler8[5]   = 0x00,
		/*B9 0x9e*/	.h_scaler9[0]  = 0x00, .h_scaler9[1]   = 0x00, .h_scaler9[2]   = 0x00, .h_scaler9[3]   = 0x00, .h_scaler9[4]   = 0x00, .h_scaler9[5]   = 0x00,


		/*B9 0x40*/	.pn_auto[0]    	= 0x00, .pn_auto[1]		= 0x00, .pn_auto[2]    	= 0x00, .pn_auto[3]    	= 0x00, .pn_auto[4]    	= 0x00, .pn_auto[5]    	= 0x00,

		/*B5 0x90*/	.comb_mode[0]      = 0x01, .comb_mode[1]	  = 0x01, .comb_mode[2]      = 0x01, .comb_mode[3]      = 0x01, .comb_mode[4]  	   = 0x01, .comb_mode[5]      = 0x01,
		/*B9 0xb9*/	.h_pll_op_a[0]     = 0x72, .h_pll_op_a[1]     = 0x72, .h_pll_op_a[2]     = 0x72, .h_pll_op_a[3]     = 0x72, .h_pll_op_a[4]     = 0x72, .h_pll_op_a[5]     = 0x72,
		/*B9 0x57*/	.mem_path[0]	   = 0x00, .mem_path[1]	      = 0x00, .mem_path[2]	     = 0x00, .mem_path[3]	    = 0x00, .mem_path[4]	   = 0x00, .mem_path[5]	      = 0x00,
		.fsc_lock_speed[0] = 0xdc, .fsc_lock_speed[1] = 0xdc, .fsc_lock_speed[2] = 0xdc, .fsc_lock_speed[3] = 0xdc, .fsc_lock_speed[4] = 0xdc, .fsc_lock_speed[5] = 0xdc,

		/*B0 0x81*/	.format_set1[0] = 0x03, .format_set1[1] = 0x03, .format_set1[2] = 0x03, .format_set1[3] = 0x03, .format_set1[4] = 0x03, .format_set1[5] = 0x03,
		/*B0 0x85*/	.format_set2[0] = 0x00, .format_set2[1] = 0x00, .format_set2[2] = 0x00, .format_set2[3] = 0x00, .format_set2[4] = 0x00, .format_set2[5] = 0x00,

		/*B0 0x64*/ .v_delay[0]     = 0x21, .v_delay[1]     = 0x21, .v_delay[2]     = 0x21, .v_delay[3]     = 0x21, .v_delay[4]     = 0x21, .v_delay[5]     = 0x21,
		},
		},

		[ AHD20_960P_60P ] = { /* o */
		/* base */
		{
		.eq_bypass[0] 	= 0x62, .eq_bypass[1] 	= 0x22, .eq_bypass[2] 	= 0x22, .eq_bypass[3] 	= 0x22, .eq_bypass[4] 	= 0x22, .eq_bypass[5] 	= 0x22,    // Bank5 0x30
		.eq_band_sel[0] = 0x77, .eq_band_sel[1] = 0x77, .eq_band_sel[2] = 0x77, .eq_band_sel[3] = 0x77, .eq_band_sel[4] = 0x57, .eq_band_sel[5] = 0x57,    // BankA 0x31
		.eq_gain_sel[0] = 0x78, .eq_gain_sel[1] = 0x7b, .eq_gain_sel[2] = 0x7f, .eq_gain_sel[3] = 0x7f, .eq_gain_sel[4] = 0x7f, .eq_gain_sel[5] = 0x7f,    // BankA 0x32
		.deq_a_on[0] 	= 0x00, .deq_a_on[1] 	= 0x01, .deq_a_on[2] 	= 0x01, .deq_a_on[3] 	= 0x01, .deq_a_on[4] 	= 0x01, .deq_a_on[5] 	= 0x01,    // BankA 0x33
		.deq_a_sel[0] 	= 0x00, .deq_a_sel[1] 	= 0x91, .deq_a_sel[2] 	= 0x87, .deq_a_sel[3] 	= 0x89, .deq_a_sel[4] 	= 0x93, .deq_a_sel[5] 	= 0x94,    // BankA 0x34
		.deq_b_sel[0] 	= 0x00, .deq_b_sel[1] 	= 0x00, .deq_b_sel[2] 	= 0x00, .deq_b_sel[3] 	= 0x00, .deq_b_sel[4] 	= 0x00, .deq_b_sel[5] 	= 0x00,    // BankA 0x35
		},
		/* coeff */
		{
		.deqA_01[0] = 0xAC, .deqA_01[1] = 0xAC, .deqA_01[2] = 0xAC, .deqA_01[3] = 0xAC, .deqA_01[4] = 0xAC, .deqA_01[5] = 0xAC,		// BankA 0x30
		.deqA_02[0] = 0x78, .deqA_02[1] = 0x78, .deqA_02[2] = 0x78, .deqA_02[3] = 0x78, .deqA_02[4] = 0x78, .deqA_02[5] = 0x78,		// BankA 0x31
		.deqA_03[0] = 0x17, .deqA_03[1] = 0x17, .deqA_03[2] = 0x17, .deqA_03[3] = 0x17, .deqA_03[4] = 0x17, .deqA_03[5] = 0x17,		// BankA 0x32
		.deqA_04[0] = 0xC1, .deqA_04[1] = 0xC1, .deqA_04[2] = 0xC1, .deqA_04[3] = 0xC1, .deqA_04[4] = 0xC1, .deqA_04[5] = 0xC1,     // BankA 0x33
		.deqA_05[0] = 0x40, .deqA_05[1] = 0x40, .deqA_05[2] = 0x40, .deqA_05[3] = 0x40, .deqA_05[4] = 0x40, .deqA_05[5] = 0x40,     // BankA 0x34
		.deqA_06[0] = 0x00, .deqA_06[1] = 0x00, .deqA_06[2] = 0x00, .deqA_06[3] = 0x00, .deqA_06[4] = 0x00, .deqA_06[5] = 0x00,     // BankA 0x35
		.deqA_07[0] = 0xC3, .deqA_07[1] = 0xC3, .deqA_07[2] = 0xC3, .deqA_07[3] = 0xC3, .deqA_07[4] = 0xC3, .deqA_07[5] = 0xC3,     // BankA 0x36
		.deqA_08[0] = 0x0A, .deqA_08[1] = 0x0A, .deqA_08[2] = 0x0A, .deqA_08[3] = 0x0A, .deqA_08[4] = 0x0A, .deqA_08[5] = 0x0A,     // BankA 0x37
		.deqA_09[0] = 0x00, .deqA_09[1] = 0x00, .deqA_09[2] = 0x00, .deqA_09[3] = 0x00, .deqA_09[4] = 0x00, .deqA_09[5] = 0x00,     // BankA 0x38
		.deqA_10[0] = 0x02, .deqA_10[1] = 0x02, .deqA_10[2] = 0x02, .deqA_10[3] = 0x02, .deqA_10[4] = 0x02, .deqA_10[5] = 0x02,     // BankA 0x39
		.deqA_11[0] = 0x00, .deqA_11[1] = 0x00, .deqA_11[2] = 0x00, .deqA_11[3] = 0x00, .deqA_11[4] = 0x00, .deqA_11[5] = 0x00,     // BankA 0x3a
		.deqA_12[0] = 0xB2, .deqA_12[1] = 0xB2, .deqA_12[2] = 0xB2, .deqA_12[3] = 0xB2, .deqA_12[4] = 0xB2, .deqA_12[5] = 0xB2,     // BankA 0x3b
		},
		/* color */
		{
		.contrast[0] 		= 0x86, .contrast[1] 		= 0x82, .contrast[2] 		= 0x82, .contrast[3] 		= 0x7e, .contrast[4] 		= 0x7c, .contrast[5] 		= 0x77,
		.h_peaking[0] 		= 0x00, .h_peaking[1] 		= 0x00, .h_peaking[2] 		= 0x00, .h_peaking[3] 		= 0x00, .h_peaking[4] 		= 0x0f, .h_peaking[5] 		= 0x0f,
		.c_filter[0]		= 0x82, .c_filter[1] 		= 0x82, .c_filter[2]	 	= 0x82, .c_filter[3] 		= 0x82, .c_filter[4] 		= 0xa2, .c_filter[5] 		= 0xb2,

		.hue[0] 			= 0x00, .hue[1] 			= 0x00, .hue[2] 			= 0x00, .hue[3] 			= 0xfe, .hue[4] 			= 0xfe, .hue[5] 			= 0xfe,
		.u_gain[0] 			= 0x00, .u_gain[1] 			= 0x00, .u_gain[2] 			= 0x04, .u_gain[3] 			= 0x10, .u_gain[4] 			= 0x10, .u_gain[5] 			= 0x18,
		.v_gain[0] 			= 0x00, .v_gain[1] 			= 0x00, .v_gain[2] 			= 0xf0, .v_gain[3] 			= 0x0e, .v_gain[4] 			= 0x0e, .v_gain[5] 			= 0x14,
		.u_offset[0] 		= 0xfe, .u_offset[1] 		= 0xfe, .u_offset[2] 		= 0xfe, .u_offset[3] 		= 0xfe, .u_offset[4] 		= 0xfe, .u_offset[5] 		= 0xfe,
		.v_offset[0] 		= 0xfb, .v_offset[1] 		= 0xfb, .v_offset[2] 		= 0xfb, .v_offset[3] 		= 0xfb, .v_offset[4] 		= 0xfb, .v_offset[5] 		= 0xfb,

		.black_level[0] 	= 0x80, .black_level[1] 	= 0x81, .black_level[2] 	= 0x81, .black_level[3] 	= 0x83, .black_level[4] 	= 0x83, .black_level[5] 	= 0x87,
		.acc_ref[0]			= 0x57, .acc_ref[1]			= 0x57, .acc_ref[2]			= 0x57, .acc_ref[3]			= 0x57, .acc_ref[4]			= 0x57, .acc_ref[5]			= 0x57,
		.cti_delay[0]		= 0x80, .cti_delay[1]		= 0x80, .cti_delay[2]		= 0x80, .cti_delay[3]		= 0x80, .cti_delay[4]		= 0x80, .cti_delay[5]		= 0x80,
		.sub_saturation[0] 	= 0xa8, .sub_saturation[1] 	= 0xa8, .sub_saturation[2] 	= 0xa8, .sub_saturation[3] 	= 0xa8, .sub_saturation[4] 	= 0x90, .sub_saturation[5] 	= 0x90,

		.burst_dec_a[0] 	= 0x2a, .burst_dec_a[1] 	= 0x2a, .burst_dec_a[2] 	= 0x2a, .burst_dec_a[3] 	= 0x2a, .burst_dec_a[4] 	= 0x2a, .burst_dec_a[5] 	= 0x2a,
		.burst_dec_b[0] 	= 0x00, .burst_dec_b[1] 	= 0x00, .burst_dec_b[2] 	= 0x00, .burst_dec_b[3] 	= 0x00, .burst_dec_b[4] 	= 0x00, .burst_dec_b[5] 	= 0x00,
		.burst_dec_c[0] 	= 0x30, .burst_dec_c[1] 	= 0x30, .burst_dec_c[2] 	= 0x30, .burst_dec_c[3] 	= 0x30, .burst_dec_c[4] 	= 0x30, .burst_dec_c[5] 	= 0x30,

		.c_option[0] 		= 0x80, .c_option[1] 		= 0x80, .c_option[2] 		= 0x90, .c_option[3] 		= 0x90, .c_option[4] 		= 0x90, .c_option[5] 		= 0xa0,

		.y_filter_b[0]		= 0x10, .y_filter_b[1]		= 0x10, .y_filter_b[2]		= 0x10, .y_filter_b[3]		= 0x10, .y_filter_b[4]		= 0x10, .y_filter_b[5]		= 0x10,
		.y_filter_b_sel[0]	= 0x1e,	.y_filter_b_sel[1]	= 0x1e,	.y_filter_b_sel[2]	= 0x1e, .y_filter_b_sel[3]	= 0x1e, .y_filter_b_sel[4]	= 0x1e, .y_filter_b_sel[5]	= 0x1e,
		},
		/* timing_a */
		{
		.h_delay_a[0] = 0x86, .h_delay_a[1] = 0x84, .h_delay_a[2] = 0x80, .h_delay_a[3] = 0x80, .h_delay_a[4] = 0x80, .h_delay_a[5] = 0x80,
		.h_delay_b[0] = 0x10, .h_delay_b[1] = 0x10, .h_delay_b[2] = 0x10, .h_delay_b[3] = 0x10, .h_delay_b[4] = 0x10, .h_delay_b[5] = 0x10,
		.h_delay_c[0] = 0x03, .h_delay_c[1] = 0x03, .h_delay_c[2] = 0x03, .h_delay_c[3] = 0x03, .h_delay_c[4] = 0x03, .h_delay_c[5] = 0x03,
		.y_delay[0]   = 0x05, .y_delay[1]   = 0x03, .y_delay[2]   = 0x03, .y_delay[3]   = 0x03, .y_delay[4]   = 0x03, .y_delay[5] =   0x03,

		},
		/* clk */
		{
		.clk_adc[0] = 0x02, .clk_adc[1] = 0x02, .clk_adc[2] = 0x02, .clk_adc[3] = 0x02, .clk_adc[4] = 0x02, .clk_adc[5] = 0x02,
		.clk_dec[0] = 0x40, .clk_dec[1] = 0x40, .clk_dec[2] = 0x40, .clk_dec[3] = 0x40, .clk_dec[4] = 0x40, .clk_dec[5] = 0x40,
		},
		/* timing_b */
		{
		/*B9 0x96*/	.h_scaler1[0]  = 0x00, .h_scaler1[1]   = 0x00, .h_scaler1[2]   = 0x00, .h_scaler1[3]   = 0x00, .h_scaler1[4]   = 0x00, .h_scaler1[5]   = 0x00,
		/*B9 0x97*/	.h_scaler2[0]  = 0x00, .h_scaler2[1]   = 0x00, .h_scaler2[2]   = 0x00, .h_scaler2[3]   = 0x00, .h_scaler2[4]   = 0x00, .h_scaler2[5]   = 0x00,
		/*B9 0x98*/	.h_scaler3[0]  = 0x00, .h_scaler3[1]   = 0x00, .h_scaler3[2]   = 0x00, .h_scaler3[3]   = 0x00, .h_scaler3[4]   = 0x00, .h_scaler3[5]   = 0x00,
		/*B9 0x99*/	.h_scaler4[0]  = 0x00, .h_scaler4[1]   = 0x00, .h_scaler4[2]   = 0x00, .h_scaler4[3]   = 0x00, .h_scaler4[4]   = 0x00, .h_scaler4[5]   = 0x00,
		/*B9 0x9a*/	.h_scaler5[0]  = 0x00, .h_scaler5[1]   = 0x00, .h_scaler5[2]   = 0x00, .h_scaler5[3]   = 0x00, .h_scaler5[4]   = 0x00, .h_scaler5[5]   = 0x00,
		/*B9 0x9b*/	.h_scaler6[0]  = 0x00, .h_scaler6[1]   = 0x00, .h_scaler6[2]   = 0x00, .h_scaler6[3]   = 0x00, .h_scaler6[4]   = 0x00, .h_scaler6[5]   = 0x00,
		/*B9 0x9c*/	.h_scaler7[0]  = 0x00, .h_scaler7[1]   = 0x00, .h_scaler7[2]   = 0x00, .h_scaler7[3]   = 0x00, .h_scaler7[4]   = 0x00, .h_scaler7[5]   = 0x00,
		/*B9 0x9d*/	.h_scaler8[0]  = 0x00, .h_scaler8[1]   = 0x00, .h_scaler8[2]   = 0x00, .h_scaler8[3]   = 0x00, .h_scaler8[4]   = 0x00, .h_scaler8[5]   = 0x00,
		/*B9 0x9e*/	.h_scaler9[0]  = 0x00, .h_scaler9[1]   = 0x00, .h_scaler9[2]   = 0x00, .h_scaler9[3]   = 0x00, .h_scaler9[4]   = 0x00, .h_scaler9[5]   = 0x00,


		/*B9 0x40*/	.pn_auto[0]    	= 0x00, .pn_auto[1]		= 0x00, .pn_auto[2]    	= 0x00, .pn_auto[3]    	= 0x00, .pn_auto[4]    	= 0x00, .pn_auto[5]    	= 0x00,

		/*B5 0x90*/	.comb_mode[0]      = 0x01, .comb_mode[1]	  = 0x01, .comb_mode[2]      = 0x01, .comb_mode[3]      = 0x01, .comb_mode[4]  	   = 0x01, .comb_mode[5]      = 0x01,
		/*B9 0xb9*/	.h_pll_op_a[0]     = 0x72, .h_pll_op_a[1]     = 0x72, .h_pll_op_a[2]     = 0x72, .h_pll_op_a[3]     = 0x72, .h_pll_op_a[4]     = 0x72, .h_pll_op_a[5]     = 0x72,
		/*B9 0x57*/	.mem_path[0]	   = 0x00, .mem_path[1]	      = 0x00, .mem_path[2]	     = 0x00, .mem_path[3]	    = 0x00, .mem_path[4]	   = 0x00, .mem_path[5]	      = 0x00,
		.fsc_lock_speed[0] = 0xdc, .fsc_lock_speed[1] = 0xdc, .fsc_lock_speed[2] = 0xdc, .fsc_lock_speed[3] = 0xdc, .fsc_lock_speed[4] = 0xdc, .fsc_lock_speed[5] = 0xdc,

		/*B0 0x81*/	.format_set1[0] = 0x03, .format_set1[1] = 0x03, .format_set1[2] = 0x03, .format_set1[3] = 0x03, .format_set1[4] = 0x03, .format_set1[5] = 0x03,
		/*B0 0x85*/	.format_set2[0] = 0x00, .format_set2[1] = 0x00, .format_set2[2] = 0x00, .format_set2[3] = 0x00, .format_set2[4] = 0x00, .format_set2[5] = 0x00,

		/*B0 0x64*/ .v_delay[0]     = 0x21, .v_delay[1]     = 0x21, .v_delay[2]     = 0x21, .v_delay[3]     = 0x21, .v_delay[4]     = 0x21, .v_delay[5]     = 0x21,
		},
		},


	[ AHD20_1080P_25P ] = { /* o */
	/* base */
		{
			.eq_bypass[0] 	= 0x62, .eq_bypass[1] 	= 0x22, .eq_bypass[2] 	= 0x22, .eq_bypass[3] 	= 0x22, .eq_bypass[4] 	= 0x22, .eq_bypass[5] 	= 0x22,    // Bank5 0x30
			.eq_band_sel[0] = 0x77, .eq_band_sel[1] = 0x77, .eq_band_sel[2] = 0x77, .eq_band_sel[3] = 0x77, .eq_band_sel[4] = 0x57, .eq_band_sel[5] = 0x57,    // BankA 0x31
			.eq_gain_sel[0] = 0x78, .eq_gain_sel[1] = 0x7b, .eq_gain_sel[2] = 0x7f, .eq_gain_sel[3] = 0x7f, .eq_gain_sel[4] = 0x7f, .eq_gain_sel[5] = 0x7f,    // BankA 0x32
			.deq_a_on[0] 	= 0x00, .deq_a_on[1] 	= 0x01, .deq_a_on[2] 	= 0x01, .deq_a_on[3] 	= 0x01, .deq_a_on[4] 	= 0x01, .deq_a_on[5] 	= 0x01,    // BankA 0x33
			.deq_a_sel[0] 	= 0x00, .deq_a_sel[1] 	= 0x91, .deq_a_sel[2] 	= 0x87, .deq_a_sel[3] 	= 0x89, .deq_a_sel[4] 	= 0x93, .deq_a_sel[5] 	= 0x94,    // BankA 0x34
			.deq_b_sel[0] 	= 0x00, .deq_b_sel[1] 	= 0x00, .deq_b_sel[2] 	= 0x00, .deq_b_sel[3] 	= 0x00, .deq_b_sel[4] 	= 0x00, .deq_b_sel[5] 	= 0x00,    // BankA 0x35
		},
		/* coeff */
		{
			.deqA_01[0] = 0xAC, .deqA_01[1] = 0xAC, .deqA_01[2] = 0xAC, .deqA_01[3] = 0xAC, .deqA_01[4] = 0xAC, .deqA_01[5] = 0xAC,		// BankA 0x30
			.deqA_02[0] = 0x78, .deqA_02[1] = 0x78, .deqA_02[2] = 0x78, .deqA_02[3] = 0x78, .deqA_02[4] = 0x78, .deqA_02[5] = 0x78,		// BankA 0x31
			.deqA_03[0] = 0x17, .deqA_03[1] = 0x17, .deqA_03[2] = 0x17, .deqA_03[3] = 0x17, .deqA_03[4] = 0x17, .deqA_03[5] = 0x17,		// BankA 0x32
			.deqA_04[0] = 0xC1, .deqA_04[1] = 0xC1, .deqA_04[2] = 0xC1, .deqA_04[3] = 0xC1, .deqA_04[4] = 0xC1, .deqA_04[5] = 0xC1,     // BankA 0x33
			.deqA_05[0] = 0x40, .deqA_05[1] = 0x40, .deqA_05[2] = 0x40, .deqA_05[3] = 0x40, .deqA_05[4] = 0x40, .deqA_05[5] = 0x40,     // BankA 0x34
			.deqA_06[0] = 0x00, .deqA_06[1] = 0x00, .deqA_06[2] = 0x00, .deqA_06[3] = 0x00, .deqA_06[4] = 0x00, .deqA_06[5] = 0x00,     // BankA 0x35
			.deqA_07[0] = 0xC3, .deqA_07[1] = 0xC3, .deqA_07[2] = 0xC3, .deqA_07[3] = 0xC3, .deqA_07[4] = 0xC3, .deqA_07[5] = 0xC3,     // BankA 0x36
			.deqA_08[0] = 0x0A, .deqA_08[1] = 0x0A, .deqA_08[2] = 0x0A, .deqA_08[3] = 0x0A, .deqA_08[4] = 0x0A, .deqA_08[5] = 0x0A,     // BankA 0x37
			.deqA_09[0] = 0x00, .deqA_09[1] = 0x00, .deqA_09[2] = 0x00, .deqA_09[3] = 0x00, .deqA_09[4] = 0x00, .deqA_09[5] = 0x00,     // BankA 0x38
			.deqA_10[0] = 0x02, .deqA_10[1] = 0x02, .deqA_10[2] = 0x02, .deqA_10[3] = 0x02, .deqA_10[4] = 0x02, .deqA_10[5] = 0x02,     // BankA 0x39
			.deqA_11[0] = 0x00, .deqA_11[1] = 0x00, .deqA_11[2] = 0x00, .deqA_11[3] = 0x00, .deqA_11[4] = 0x00, .deqA_11[5] = 0x00,     // BankA 0x3a
			.deqA_12[0] = 0xB2, .deqA_12[1] = 0xB2, .deqA_12[2] = 0xB2, .deqA_12[3] = 0xB2, .deqA_12[4] = 0xB2, .deqA_12[5] = 0xB2,     // BankA 0x3b
		},
		/* color */
		{
			.contrast[0] 		= 0x86, .contrast[1] 		= 0x82, .contrast[2] 		= 0x82, .contrast[3] 		= 0x7e, .contrast[4] 		= 0x7c, .contrast[5] 		= 0x77,
			.h_peaking[0] 		= 0x00, .h_peaking[1] 		= 0x00, .h_peaking[2] 		= 0x00, .h_peaking[3] 		= 0x00, .h_peaking[4] 		= 0x0f, .h_peaking[5] 		= 0x0f,
			.c_filter[0]		= 0x82, .c_filter[1] 		= 0x82, .c_filter[2]	 	= 0x82, .c_filter[3] 		= 0x82, .c_filter[4] 		= 0xa2, .c_filter[5] 		= 0xb2,

			.hue[0] 			= 0x00, .hue[1] 			= 0x00, .hue[2] 			= 0x00, .hue[3] 			= 0xfe, .hue[4] 			= 0xfe, .hue[5] 			= 0xfe,
			.u_gain[0] 			= 0x00, .u_gain[1] 			= 0x00, .u_gain[2] 			= 0x04, .u_gain[3] 			= 0x10, .u_gain[4] 			= 0x10, .u_gain[5] 			= 0x18,
			.v_gain[0] 			= 0x00, .v_gain[1] 			= 0x00, .v_gain[2] 			= 0xf0, .v_gain[3] 			= 0x0e, .v_gain[4] 			= 0x0e, .v_gain[5] 			= 0x14,
			.u_offset[0] 		= 0xfe, .u_offset[1] 		= 0xfe, .u_offset[2] 		= 0xfe, .u_offset[3] 		= 0xfe, .u_offset[4] 		= 0xfe, .u_offset[5] 		= 0xfe,
			.v_offset[0] 		= 0xfb, .v_offset[1] 		= 0xfb, .v_offset[2] 		= 0xfb, .v_offset[3] 		= 0xfb, .v_offset[4] 		= 0xfb, .v_offset[5] 		= 0xfb,

			.black_level[0] 	= 0x80, .black_level[1] 	= 0x81, .black_level[2] 	= 0x81, .black_level[3] 	= 0x83, .black_level[4] 	= 0x83, .black_level[5] 	= 0x87,
			.acc_ref[0]			= 0x57, .acc_ref[1]			= 0x57, .acc_ref[2]			= 0x57, .acc_ref[3]			= 0x57, .acc_ref[4]			= 0x57, .acc_ref[5]			= 0x57,
			.cti_delay[0]		= 0x80, .cti_delay[1]		= 0x80, .cti_delay[2]		= 0x80, .cti_delay[3]		= 0x80, .cti_delay[4]		= 0x80, .cti_delay[5]		= 0x80,
			.sub_saturation[0] 	= 0xa8, .sub_saturation[1] 	= 0xa8, .sub_saturation[2] 	= 0xa8, .sub_saturation[3] 	= 0xa8, .sub_saturation[4] 	= 0x90, .sub_saturation[5] 	= 0x90,

			.burst_dec_a[0] 	= 0x2a, .burst_dec_a[1] 	= 0x2a, .burst_dec_a[2] 	= 0x2a, .burst_dec_a[3] 	= 0x2a, .burst_dec_a[4] 	= 0x2a, .burst_dec_a[5] 	= 0x2a,
			.burst_dec_b[0] 	= 0x00, .burst_dec_b[1] 	= 0x00, .burst_dec_b[2] 	= 0x00, .burst_dec_b[3] 	= 0x00, .burst_dec_b[4] 	= 0x00, .burst_dec_b[5] 	= 0x00,
			.burst_dec_c[0] 	= 0x30, .burst_dec_c[1] 	= 0x30, .burst_dec_c[2] 	= 0x30, .burst_dec_c[3] 	= 0x30, .burst_dec_c[4] 	= 0x30, .burst_dec_c[5] 	= 0x30,

			.c_option[0] 		= 0x80, .c_option[1] 		= 0x80, .c_option[2] 		= 0x90, .c_option[3] 		= 0x90, .c_option[4] 		= 0x90, .c_option[5] 		= 0xa0,

			.y_filter_b[0]		= 0x10, .y_filter_b[1]		= 0x10, .y_filter_b[2]		= 0x10, .y_filter_b[3]		= 0x10, .y_filter_b[4]		= 0x10, .y_filter_b[5]		= 0x10,
			.y_filter_b_sel[0]	= 0x1e,	.y_filter_b_sel[1]	= 0x1e,	.y_filter_b_sel[2]	= 0x1e, .y_filter_b_sel[3]	= 0x1e, .y_filter_b_sel[4]	= 0x1e, .y_filter_b_sel[5]	= 0x1e,
		},
		/* timing_a */
		{
			.h_delay_a[0] = 0x86, .h_delay_a[1] = 0x84, .h_delay_a[2] = 0x80, .h_delay_a[3] = 0x80, .h_delay_a[4] = 0x80, .h_delay_a[5] = 0x80,
			.h_delay_b[0] = 0x10, .h_delay_b[1] = 0x10, .h_delay_b[2] = 0x10, .h_delay_b[3] = 0x10, .h_delay_b[4] = 0x10, .h_delay_b[5] = 0x10,
			.h_delay_c[0] = 0x03, .h_delay_c[1] = 0x03, .h_delay_c[2] = 0x03, .h_delay_c[3] = 0x03, .h_delay_c[4] = 0x03, .h_delay_c[5] = 0x03,
			.y_delay[0]   = 0x05, .y_delay[1]   = 0x03, .y_delay[2]   = 0x03, .y_delay[3]   = 0x03, .y_delay[4]   = 0x03, .y_delay[5] =   0x03,

		},
		/* clk */
		{
			.clk_adc[0] = 0x02, .clk_adc[1] = 0x02, .clk_adc[2] = 0x02, .clk_adc[3] = 0x02, .clk_adc[4] = 0x02, .clk_adc[5] = 0x02,
			.clk_dec[0] = 0x40, .clk_dec[1] = 0x40, .clk_dec[2] = 0x40, .clk_dec[3] = 0x40, .clk_dec[4] = 0x40, .clk_dec[5] = 0x40,
		},
		/* timing_b */
		{
	/*B9 0x96*/	.h_scaler1[0]  = 0x00, .h_scaler1[1]   = 0x00, .h_scaler1[2]   = 0x00, .h_scaler1[3]   = 0x00, .h_scaler1[4]   = 0x00, .h_scaler1[5]   = 0x00,
	/*B9 0x97*/	.h_scaler2[0]  = 0x00, .h_scaler2[1]   = 0x00, .h_scaler2[2]   = 0x00, .h_scaler2[3]   = 0x00, .h_scaler2[4]   = 0x00, .h_scaler2[5]   = 0x00,
	/*B9 0x98*/	.h_scaler3[0]  = 0x00, .h_scaler3[1]   = 0x00, .h_scaler3[2]   = 0x00, .h_scaler3[3]   = 0x00, .h_scaler3[4]   = 0x00, .h_scaler3[5]   = 0x00,
	/*B9 0x99*/	.h_scaler4[0]  = 0x00, .h_scaler4[1]   = 0x00, .h_scaler4[2]   = 0x00, .h_scaler4[3]   = 0x00, .h_scaler4[4]   = 0x00, .h_scaler4[5]   = 0x00,
	/*B9 0x9a*/	.h_scaler5[0]  = 0x00, .h_scaler5[1]   = 0x00, .h_scaler5[2]   = 0x00, .h_scaler5[3]   = 0x00, .h_scaler5[4]   = 0x00, .h_scaler5[5]   = 0x00,
	/*B9 0x9b*/	.h_scaler6[0]  = 0x00, .h_scaler6[1]   = 0x00, .h_scaler6[2]   = 0x00, .h_scaler6[3]   = 0x00, .h_scaler6[4]   = 0x00, .h_scaler6[5]   = 0x00,
	/*B9 0x9c*/	.h_scaler7[0]  = 0x00, .h_scaler7[1]   = 0x00, .h_scaler7[2]   = 0x00, .h_scaler7[3]   = 0x00, .h_scaler7[4]   = 0x00, .h_scaler7[5]   = 0x00,
	/*B9 0x9d*/	.h_scaler8[0]  = 0x00, .h_scaler8[1]   = 0x00, .h_scaler8[2]   = 0x00, .h_scaler8[3]   = 0x00, .h_scaler8[4]   = 0x00, .h_scaler8[5]   = 0x00,
	/*B9 0x9e*/	.h_scaler9[0]  = 0x00, .h_scaler9[1]   = 0x00, .h_scaler9[2]   = 0x00, .h_scaler9[3]   = 0x00, .h_scaler9[4]   = 0x00, .h_scaler9[5]   = 0x00,


	/*B9 0x40*/	.pn_auto[0]    	= 0x00, .pn_auto[1]		= 0x00, .pn_auto[2]    	= 0x00, .pn_auto[3]    	= 0x00, .pn_auto[4]    	= 0x00, .pn_auto[5]    	= 0x00,

	/*B5 0x90*/	.comb_mode[0]      = 0x01, .comb_mode[1]	  = 0x01, .comb_mode[2]      = 0x01, .comb_mode[3]      = 0x01, .comb_mode[4]  	   = 0x01, .comb_mode[5]      = 0x01,
	/*B9 0xb9*/	.h_pll_op_a[0]     = 0x72, .h_pll_op_a[1]     = 0x72, .h_pll_op_a[2]     = 0x72, .h_pll_op_a[3]     = 0x72, .h_pll_op_a[4]     = 0x72, .h_pll_op_a[5]     = 0x72,
	/*B9 0x57*/	.mem_path[0]	   = 0x00, .mem_path[1]	      = 0x00, .mem_path[2]	     = 0x00, .mem_path[3]	    = 0x00, .mem_path[4]	   = 0x00, .mem_path[5]	      = 0x00,
			    .fsc_lock_speed[0] = 0xdc, .fsc_lock_speed[1] = 0xdc, .fsc_lock_speed[2] = 0xdc, .fsc_lock_speed[3] = 0xdc, .fsc_lock_speed[4] = 0xdc, .fsc_lock_speed[5] = 0xdc,

	/*B0 0x81*/	.format_set1[0] = 0x03, .format_set1[1] = 0x03, .format_set1[2] = 0x03, .format_set1[3] = 0x03, .format_set1[4] = 0x03, .format_set1[5] = 0x03,
	/*B0 0x85*/	.format_set2[0] = 0x00, .format_set2[1] = 0x00, .format_set2[2] = 0x00, .format_set2[3] = 0x00, .format_set2[4] = 0x00, .format_set2[5] = 0x00,

	/*B0 0x64*/ .v_delay[0]     = 0x21, .v_delay[1]     = 0x21, .v_delay[2]     = 0x21, .v_delay[3]     = 0x21, .v_delay[4]     = 0x21, .v_delay[5]     = 0x21,
		},
	},
	[ AHD20_1080P_30P ] = { /* o */
	/* base */
	{
		.eq_bypass[0] 	= 0x62, .eq_bypass[1] 	= 0x22, .eq_bypass[2] 	= 0x22, .eq_bypass[3] 	= 0x22, .eq_bypass[4] 	= 0x22, .eq_bypass[5] 	= 0x22,    // Bank5 0x30
		.eq_band_sel[0] = 0x77, .eq_band_sel[1] = 0x77, .eq_band_sel[2] = 0x77, .eq_band_sel[3] = 0x77, .eq_band_sel[4] = 0x57, .eq_band_sel[5] = 0x57,    // BankA 0x31
		.eq_gain_sel[0] = 0x78, .eq_gain_sel[1] = 0x7b, .eq_gain_sel[2] = 0x7f, .eq_gain_sel[3] = 0x7f, .eq_gain_sel[4] = 0x7f, .eq_gain_sel[5] = 0x7f,    // BankA 0x32
		.deq_a_on[0] 	= 0x00, .deq_a_on[1] 	= 0x01, .deq_a_on[2] 	= 0x01, .deq_a_on[3] 	= 0x01, .deq_a_on[4] 	= 0x01, .deq_a_on[5] 	= 0x01,    // BankA 0x33
		.deq_a_sel[0] 	= 0x00, .deq_a_sel[1] 	= 0x91, .deq_a_sel[2] 	= 0x87, .deq_a_sel[3] 	= 0x89, .deq_a_sel[4] 	= 0x93, .deq_a_sel[5] 	= 0x94,    // BankA 0x34
		.deq_b_sel[0] 	= 0x00, .deq_b_sel[1] 	= 0x00, .deq_b_sel[2] 	= 0x00, .deq_b_sel[3] 	= 0x00, .deq_b_sel[4] 	= 0x00, .deq_b_sel[5] 	= 0x00,    // BankA 0x35
	},
	/* coeff */
	{
		.deqA_01[0] = 0xAC, .deqA_01[1] = 0xAC, .deqA_01[2] = 0xAC, .deqA_01[3] = 0xAC, .deqA_01[4] = 0xAC, .deqA_01[5] = 0xAC,		// BankA 0x30
		.deqA_02[0] = 0x78, .deqA_02[1] = 0x78, .deqA_02[2] = 0x78, .deqA_02[3] = 0x78, .deqA_02[4] = 0x78, .deqA_02[5] = 0x78,		// BankA 0x31
		.deqA_03[0] = 0x17, .deqA_03[1] = 0x17, .deqA_03[2] = 0x17, .deqA_03[3] = 0x17, .deqA_03[4] = 0x17, .deqA_03[5] = 0x17,		// BankA 0x32
		.deqA_04[0] = 0xC1, .deqA_04[1] = 0xC1, .deqA_04[2] = 0xC1, .deqA_04[3] = 0xC1, .deqA_04[4] = 0xC1, .deqA_04[5] = 0xC1,     // BankA 0x33
		.deqA_05[0] = 0x40, .deqA_05[1] = 0x40, .deqA_05[2] = 0x40, .deqA_05[3] = 0x40, .deqA_05[4] = 0x40, .deqA_05[5] = 0x40,     // BankA 0x34
		.deqA_06[0] = 0x00, .deqA_06[1] = 0x00, .deqA_06[2] = 0x00, .deqA_06[3] = 0x00, .deqA_06[4] = 0x00, .deqA_06[5] = 0x00,     // BankA 0x35
		.deqA_07[0] = 0xC3, .deqA_07[1] = 0xC3, .deqA_07[2] = 0xC3, .deqA_07[3] = 0xC3, .deqA_07[4] = 0xC3, .deqA_07[5] = 0xC3,     // BankA 0x36
		.deqA_08[0] = 0x0A, .deqA_08[1] = 0x0A, .deqA_08[2] = 0x0A, .deqA_08[3] = 0x0A, .deqA_08[4] = 0x0A, .deqA_08[5] = 0x0A,     // BankA 0x37
		.deqA_09[0] = 0x00, .deqA_09[1] = 0x00, .deqA_09[2] = 0x00, .deqA_09[3] = 0x00, .deqA_09[4] = 0x00, .deqA_09[5] = 0x00,     // BankA 0x38
		.deqA_10[0] = 0x02, .deqA_10[1] = 0x02, .deqA_10[2] = 0x02, .deqA_10[3] = 0x02, .deqA_10[4] = 0x02, .deqA_10[5] = 0x02,     // BankA 0x39
		.deqA_11[0] = 0x00, .deqA_11[1] = 0x00, .deqA_11[2] = 0x00, .deqA_11[3] = 0x00, .deqA_11[4] = 0x00, .deqA_11[5] = 0x00,     // BankA 0x3a
		.deqA_12[0] = 0xB2, .deqA_12[1] = 0xB2, .deqA_12[2] = 0xB2, .deqA_12[3] = 0xB2, .deqA_12[4] = 0xB2, .deqA_12[5] = 0xB2,     // BankA 0x3b
	},
	/* color */
	{
		.contrast[0] 		= 0x86, .contrast[1] 		= 0x82, .contrast[2] 		= 0x82, .contrast[3] 		= 0x7e, .contrast[4] 		= 0x7c, .contrast[5] 		= 0x77,
		.h_peaking[0] 		= 0x00, .h_peaking[1] 		= 0x00, .h_peaking[2] 		= 0x00, .h_peaking[3] 		= 0x00, .h_peaking[4] 		= 0x0f, .h_peaking[5] 		= 0x0f,
		.c_filter[0]		= 0x82, .c_filter[1] 		= 0x82, .c_filter[2]	 	= 0x82, .c_filter[3] 		= 0x82, .c_filter[4] 		= 0xa2, .c_filter[5] 		= 0xb2,

		.hue[0] 			= 0x00, .hue[1] 			= 0x00, .hue[2] 			= 0x00, .hue[3] 			= 0xfe, .hue[4] 			= 0xfe, .hue[5] 			= 0xfe,
		.u_gain[0] 			= 0x00, .u_gain[1] 			= 0x00, .u_gain[2] 			= 0x04, .u_gain[3] 			= 0x10, .u_gain[4] 			= 0x10, .u_gain[5] 			= 0x18,
		.v_gain[0] 			= 0x00, .v_gain[1] 			= 0x00, .v_gain[2] 			= 0xf0, .v_gain[3] 			= 0x0e, .v_gain[4] 			= 0x0e, .v_gain[5] 			= 0x14,
		.u_offset[0] 		= 0xfe, .u_offset[1] 		= 0xfe, .u_offset[2] 		= 0xfe, .u_offset[3] 		= 0xfe, .u_offset[4] 		= 0xfe, .u_offset[5] 		= 0xfe,
		.v_offset[0] 		= 0xfb, .v_offset[1] 		= 0xfb, .v_offset[2] 		= 0xfb, .v_offset[3] 		= 0xfb, .v_offset[4] 		= 0xfb, .v_offset[5] 		= 0xfb,

		.black_level[0] 	= 0x80, .black_level[1] 	= 0x81, .black_level[2] 	= 0x81, .black_level[3] 	= 0x83, .black_level[4] 	= 0x83, .black_level[5] 	= 0x87,
		.acc_ref[0]			= 0x57, .acc_ref[1]			= 0x57, .acc_ref[2]			= 0x57, .acc_ref[3]			= 0x57, .acc_ref[4]			= 0x57, .acc_ref[5]			= 0x57,
		.cti_delay[0]		= 0x80, .cti_delay[1]		= 0x80, .cti_delay[2]		= 0x80, .cti_delay[3]		= 0x80, .cti_delay[4]		= 0x80, .cti_delay[5]		= 0x80,
		.sub_saturation[0] 	= 0xa8, .sub_saturation[1] 	= 0xa8, .sub_saturation[2] 	= 0xa8, .sub_saturation[3] 	= 0xa8, .sub_saturation[4] 	= 0x90, .sub_saturation[5] 	= 0x90,

		.burst_dec_a[0] 	= 0x2a, .burst_dec_a[1] 	= 0x2a, .burst_dec_a[2] 	= 0x2a, .burst_dec_a[3] 	= 0x2a, .burst_dec_a[4] 	= 0x2a, .burst_dec_a[5] 	= 0x2a,
		.burst_dec_b[0] 	= 0x00, .burst_dec_b[1] 	= 0x00, .burst_dec_b[2] 	= 0x00, .burst_dec_b[3] 	= 0x00, .burst_dec_b[4] 	= 0x00, .burst_dec_b[5] 	= 0x00,
		.burst_dec_c[0] 	= 0x30, .burst_dec_c[1] 	= 0x30, .burst_dec_c[2] 	= 0x30, .burst_dec_c[3] 	= 0x30, .burst_dec_c[4] 	= 0x30, .burst_dec_c[5] 	= 0x30,

		.c_option[0] 		= 0x80, .c_option[1] 		= 0x80, .c_option[2] 		= 0x90, .c_option[3] 		= 0x90, .c_option[4] 		= 0x90, .c_option[5] 		= 0xa0,

		.y_filter_b[0]		= 0x10, .y_filter_b[1]		= 0x10, .y_filter_b[2]		= 0x10, .y_filter_b[3]		= 0x10, .y_filter_b[4]		= 0x10, .y_filter_b[5]		= 0x10,
		.y_filter_b_sel[0]	= 0x1e,	.y_filter_b_sel[1]	= 0x1e,	.y_filter_b_sel[2]	= 0x1e, .y_filter_b_sel[3]	= 0x1e, .y_filter_b_sel[4]	= 0x1e, .y_filter_b_sel[5]	= 0x1e,
	},
	/* timing_a */
	{
		.h_delay_a[0] = 0x90, .h_delay_a[1] = 0x8e, .h_delay_a[2] = 0x8a, .h_delay_a[3] = 0x86, .h_delay_a[4] = 0x86, .h_delay_a[5] = 0x86,
		.h_delay_b[0] = 0x10, .h_delay_b[1] = 0x10, .h_delay_b[2] = 0x10, .h_delay_b[3] = 0x10, .h_delay_b[4] = 0x10, .h_delay_b[5] = 0x10,
		.h_delay_c[0] = 0x03, .h_delay_c[1] = 0x03, .h_delay_c[2] = 0x03, .h_delay_c[3] = 0x03, .h_delay_c[4] = 0x03, .h_delay_c[5] = 0x03,
		.y_delay[0]   = 0x05, .y_delay[1]   = 0x03, .y_delay[2]   = 0x03, .y_delay[3]   = 0x03, .y_delay[4]   = 0x03, .y_delay[5] =   0x03,

	},
	/* clk */
	{
		.clk_adc[0] = 0x02, .clk_adc[1] = 0x02, .clk_adc[2] = 0x02, .clk_adc[3] = 0x02, .clk_adc[4] = 0x02, .clk_adc[5] = 0x02,
		.clk_dec[0] = 0x40, .clk_dec[1] = 0x40, .clk_dec[2] = 0x40, .clk_dec[3] = 0x40, .clk_dec[4] = 0x40, .clk_dec[5] = 0x40,
	},
	/* timing_b */
	{
	/*B9 0x96*/	.h_scaler1[0]  = 0x00, .h_scaler1[1]   = 0x00, .h_scaler1[2]   = 0x00, .h_scaler1[3]   = 0x00, .h_scaler1[4]   = 0x00, .h_scaler1[5]   = 0x00,
	/*B9 0x97*/	.h_scaler2[0]  = 0x00, .h_scaler2[1]   = 0x00, .h_scaler2[2]   = 0x00, .h_scaler2[3]   = 0x00, .h_scaler2[4]   = 0x00, .h_scaler2[5]   = 0x00,
	/*B9 0x98*/	.h_scaler3[0]  = 0x00, .h_scaler3[1]   = 0x00, .h_scaler3[2]   = 0x00, .h_scaler3[3]   = 0x00, .h_scaler3[4]   = 0x00, .h_scaler3[5]   = 0x00,
	/*B9 0x99*/	.h_scaler4[0]  = 0x00, .h_scaler4[1]   = 0x00, .h_scaler4[2]   = 0x00, .h_scaler4[3]   = 0x00, .h_scaler4[4]   = 0x00, .h_scaler4[5]   = 0x00,
	/*B9 0x9a*/	.h_scaler5[0]  = 0x00, .h_scaler5[1]   = 0x00, .h_scaler5[2]   = 0x00, .h_scaler5[3]   = 0x00, .h_scaler5[4]   = 0x00, .h_scaler5[5]   = 0x00,
	/*B9 0x9b*/	.h_scaler6[0]  = 0x00, .h_scaler6[1]   = 0x00, .h_scaler6[2]   = 0x00, .h_scaler6[3]   = 0x00, .h_scaler6[4]   = 0x00, .h_scaler6[5]   = 0x00,
	/*B9 0x9c*/	.h_scaler7[0]  = 0x00, .h_scaler7[1]   = 0x00, .h_scaler7[2]   = 0x00, .h_scaler7[3]   = 0x00, .h_scaler7[4]   = 0x00, .h_scaler7[5]   = 0x00,
	/*B9 0x9d*/	.h_scaler8[0]  = 0x00, .h_scaler8[1]   = 0x00, .h_scaler8[2]   = 0x00, .h_scaler8[3]   = 0x00, .h_scaler8[4]   = 0x00, .h_scaler8[5]   = 0x00,
	/*B9 0x9e*/	.h_scaler9[0]  = 0x00, .h_scaler9[1]   = 0x00, .h_scaler9[2]   = 0x00, .h_scaler9[3]   = 0x00, .h_scaler9[4]   = 0x00, .h_scaler9[5]   = 0x00,


	/*B9 0x40*/	.pn_auto[0]    	= 0x00, .pn_auto[1]		= 0x00, .pn_auto[2]    	= 0x00, .pn_auto[3]    	= 0x00, .pn_auto[4]    	= 0x00, .pn_auto[5]    	= 0x00,

	/*B5 0x90*/	.comb_mode[0]      = 0x01, .comb_mode[1]	  = 0x01, .comb_mode[2]      = 0x01, .comb_mode[3]      = 0x01, .comb_mode[4]  	   = 0x01, .comb_mode[5]      = 0x01,
	/*B9 0xb9*/	.h_pll_op_a[0]     = 0x72, .h_pll_op_a[1]     = 0x72, .h_pll_op_a[2]     = 0x72, .h_pll_op_a[3]     = 0x72, .h_pll_op_a[4]     = 0x72, .h_pll_op_a[5]     = 0x72,
	/*B9 0x57*/	.mem_path[0]	   = 0x00, .mem_path[1]	      = 0x00, .mem_path[2]	     = 0x00, .mem_path[3]	    = 0x00, .mem_path[4]	   = 0x00, .mem_path[5]	      = 0x00,
				.fsc_lock_speed[0] = 0xdc, .fsc_lock_speed[1] = 0xdc, .fsc_lock_speed[2] = 0xdc, .fsc_lock_speed[3] = 0xdc, .fsc_lock_speed[4] = 0xdc, .fsc_lock_speed[5] = 0xdc,

	/*B0 0x81*/	.format_set1[0] = 0x02, .format_set1[1] = 0x02, .format_set1[2] = 0x02, .format_set1[3] = 0x02, .format_set1[4] = 0x02, .format_set1[5] = 0x02,
	/*B0 0x85*/	.format_set2[0] = 0x00, .format_set2[1] = 0x00, .format_set2[2] = 0x00, .format_set2[3] = 0x00, .format_set2[4] = 0x00, .format_set2[5] = 0x00,

	/*B0 0x64*/ .v_delay[0]     = 0x21, .v_delay[1]     = 0x21, .v_delay[2]     = 0x21, .v_delay[3]     = 0x21, .v_delay[4]     = 0x21, .v_delay[5]     = 0x21,
		},
	},

	[ AHD30_8M_7_5P ] = { /* o */
		/* base */
			{
				.eq_bypass[0] 	= 0x62, .eq_bypass[1] 	= 0x22, .eq_bypass[2] 	= 0x22, .eq_bypass[3] 	= 0x22, .eq_bypass[4] 	= 0x22, .eq_bypass[5] 	= 0x22,    // Bank5 0x30
				.eq_band_sel[0] = 0x77, .eq_band_sel[1] = 0x77, .eq_band_sel[2] = 0x77, .eq_band_sel[3] = 0x77, .eq_band_sel[4] = 0x57, .eq_band_sel[5] = 0x57,    // BankA 0x31
				.eq_gain_sel[0] = 0x78, .eq_gain_sel[1] = 0x7b, .eq_gain_sel[2] = 0x7f, .eq_gain_sel[3] = 0x7f, .eq_gain_sel[4] = 0x7f, .eq_gain_sel[5] = 0x7f,    // BankA 0x32
				.deq_a_on[0] 	= 0x00, .deq_a_on[1] 	= 0x01, .deq_a_on[2] 	= 0x01, .deq_a_on[3] 	= 0x01, .deq_a_on[4] 	= 0x01, .deq_a_on[5] 	= 0x01,    // BankA 0x33
				.deq_a_sel[0] 	= 0x00, .deq_a_sel[1] 	= 0x91, .deq_a_sel[2] 	= 0x87, .deq_a_sel[3] 	= 0x89, .deq_a_sel[4] 	= 0x93, .deq_a_sel[5] 	= 0x94,    // BankA 0x34
				.deq_b_sel[0] 	= 0x00, .deq_b_sel[1] 	= 0x00, .deq_b_sel[2] 	= 0x00, .deq_b_sel[3] 	= 0x00, .deq_b_sel[4] 	= 0x00, .deq_b_sel[5] 	= 0x00,    // BankA 0x35
			},
			/* coeff */
			{
				.deqA_01[0] = 0xAC, .deqA_01[1] = 0xAC, .deqA_01[2] = 0xAC, .deqA_01[3] = 0xAC, .deqA_01[4] = 0xAC, .deqA_01[5] = 0xAC,		// BankA 0x30
				.deqA_02[0] = 0x78, .deqA_02[1] = 0x78, .deqA_02[2] = 0x78, .deqA_02[3] = 0x78, .deqA_02[4] = 0x78, .deqA_02[5] = 0x78,		// BankA 0x31
				.deqA_03[0] = 0x17, .deqA_03[1] = 0x17, .deqA_03[2] = 0x17, .deqA_03[3] = 0x17, .deqA_03[4] = 0x17, .deqA_03[5] = 0x17,		// BankA 0x32
				.deqA_04[0] = 0xC1, .deqA_04[1] = 0xC1, .deqA_04[2] = 0xC1, .deqA_04[3] = 0xC1, .deqA_04[4] = 0xC1, .deqA_04[5] = 0xC1,     // BankA 0x33
				.deqA_05[0] = 0x40, .deqA_05[1] = 0x40, .deqA_05[2] = 0x40, .deqA_05[3] = 0x40, .deqA_05[4] = 0x40, .deqA_05[5] = 0x40,     // BankA 0x34
				.deqA_06[0] = 0x00, .deqA_06[1] = 0x00, .deqA_06[2] = 0x00, .deqA_06[3] = 0x00, .deqA_06[4] = 0x00, .deqA_06[5] = 0x00,     // BankA 0x35
				.deqA_07[0] = 0xC3, .deqA_07[1] = 0xC3, .deqA_07[2] = 0xC3, .deqA_07[3] = 0xC3, .deqA_07[4] = 0xC3, .deqA_07[5] = 0xC3,     // BankA 0x36
				.deqA_08[0] = 0x0A, .deqA_08[1] = 0x0A, .deqA_08[2] = 0x0A, .deqA_08[3] = 0x0A, .deqA_08[4] = 0x0A, .deqA_08[5] = 0x0A,     // BankA 0x37
				.deqA_09[0] = 0x00, .deqA_09[1] = 0x00, .deqA_09[2] = 0x00, .deqA_09[3] = 0x00, .deqA_09[4] = 0x00, .deqA_09[5] = 0x00,     // BankA 0x38
				.deqA_10[0] = 0x02, .deqA_10[1] = 0x02, .deqA_10[2] = 0x02, .deqA_10[3] = 0x02, .deqA_10[4] = 0x02, .deqA_10[5] = 0x02,     // BankA 0x39
				.deqA_11[0] = 0x00, .deqA_11[1] = 0x00, .deqA_11[2] = 0x00, .deqA_11[3] = 0x00, .deqA_11[4] = 0x00, .deqA_11[5] = 0x00,     // BankA 0x3a
				.deqA_12[0] = 0xB2, .deqA_12[1] = 0xB2, .deqA_12[2] = 0xB2, .deqA_12[3] = 0xB2, .deqA_12[4] = 0xB2, .deqA_12[5] = 0xB2,     // BankA 0x3b
			},
			/* color */
			{
				.contrast[0] 		= 0x86, .contrast[1] 		= 0x82, .contrast[2] 		= 0x82, .contrast[3] 		= 0x7e, .contrast[4] 		= 0x7c, .contrast[5] 		= 0x77,
				.h_peaking[0] 		= 0x0f, .h_peaking[1] 		= 0x0f, .h_peaking[2] 		= 0x0f, .h_peaking[3] 		= 0x0f, .h_peaking[4] 		= 0x0f, .h_peaking[5] 		= 0x0f,
				.c_filter[0]		= 0x82, .c_filter[1] 		= 0x82, .c_filter[2]	 	= 0x92, .c_filter[3] 		= 0x92, .c_filter[4] 		= 0xa2, .c_filter[5] 		= 0xb2,

				.hue[0] 			= 0x00, .hue[1] 			= 0x00, .hue[2] 			= 0x00, .hue[3] 			= 0x00, .hue[4] 			= 0x00, .hue[5] 			= 0x00,
				.u_gain[0] 			= 0x10, .u_gain[1] 			= 0x10, .u_gain[2] 			= 0x04, .u_gain[3] 			= 0xfc, .u_gain[4] 			= 0xfc, .u_gain[5] 			= 0xfc,
				.v_gain[0] 			= 0x10, .v_gain[1] 			= 0x10, .v_gain[2] 			= 0x04, .v_gain[3] 			= 0xf4, .v_gain[4] 			= 0x08, .v_gain[5] 			= 0x08,
				.u_offset[0] 		= 0xfb, .u_offset[1] 		= 0xfb, .u_offset[2] 		= 0xfb, .u_offset[3] 		= 0xfb, .u_offset[4] 		= 0xfb, .u_offset[5] 		= 0xfe,
				.v_offset[0] 		= 0xf8, .v_offset[1] 		= 0xf8, .v_offset[2] 		= 0xf8, .v_offset[3] 		= 0xf8, .v_offset[4] 		= 0xf8, .v_offset[5] 		= 0xfb,

				.black_level[0] 	= 0x80, .black_level[1] 	= 0x81, .black_level[2] 	= 0x81, .black_level[3] 	= 0x83, .black_level[4] 	= 0x85, .black_level[5] 	= 0x87,
				.acc_ref[0]			= 0x57, .acc_ref[1]			= 0x57, .acc_ref[2]			= 0x57, .acc_ref[3]			= 0x57, .acc_ref[4]			= 0x57, .acc_ref[5]			= 0x57,
				.cti_delay[0]		= 0x80, .cti_delay[1]		= 0x80, .cti_delay[2]		= 0x80, .cti_delay[3]		= 0x80, .cti_delay[4]		= 0x80, .cti_delay[5]		= 0x80,
				.sub_saturation[0] 	= 0xa8, .sub_saturation[1] 	= 0xa8, .sub_saturation[2] 	= 0xa8, .sub_saturation[3] 	= 0xa8, .sub_saturation[4] 	= 0x90, .sub_saturation[5] 	= 0x90,

				.burst_dec_a[0] 	= 0x2a, .burst_dec_a[1] 	= 0x2a, .burst_dec_a[2] 	= 0x2a, .burst_dec_a[3] 	= 0x2a, .burst_dec_a[4] 	= 0x2a, .burst_dec_a[5] 	= 0x2a,
				.burst_dec_b[0] 	= 0x00, .burst_dec_b[1] 	= 0x00, .burst_dec_b[2] 	= 0x00, .burst_dec_b[3] 	= 0x00, .burst_dec_b[4] 	= 0x00, .burst_dec_b[5] 	= 0x00,
				.burst_dec_c[0] 	= 0x30, .burst_dec_c[1] 	= 0x30, .burst_dec_c[2] 	= 0x30, .burst_dec_c[3] 	= 0x30, .burst_dec_c[4] 	= 0x30, .burst_dec_c[5] 	= 0x30,

				.c_option[0] 		= 0x80, .c_option[1] 		= 0x80, .c_option[2] 		= 0x90, .c_option[3] 		= 0x90, .c_option[4] 		= 0x90, .c_option[5] 		= 0xa0,

				.y_filter_b[0]		= 0x10, .y_filter_b[1]		= 0x10, .y_filter_b[2]		= 0x10, .y_filter_b[3]		= 0x10, .y_filter_b[4]		= 0x10, .y_filter_b[5]		= 0x10,
				.y_filter_b_sel[0]	= 0x1e,	.y_filter_b_sel[1]	= 0x1e,	.y_filter_b_sel[2]	= 0x1e, .y_filter_b_sel[3]	= 0x1e, .y_filter_b_sel[4]	= 0x1e, .y_filter_b_sel[5]	= 0x1e,
			},
			/* timing_a */
			{
				.h_delay_a[0] = 0x80, .h_delay_a[1] = 0x80, .h_delay_a[2] = 0x80, .h_delay_a[3] = 0x80, .h_delay_a[4] = 0x80, .h_delay_a[5] = 0x80,
				.h_delay_b[0] = 0x10, .h_delay_b[1] = 0x10, .h_delay_b[2] = 0x10, .h_delay_b[3] = 0x10, .h_delay_b[4] = 0x10, .h_delay_b[5] = 0x10,
				.h_delay_c[0] = 0x00, .h_delay_c[1] = 0x00, .h_delay_c[2] = 0x00, .h_delay_c[3] = 0x00, .h_delay_c[4] = 0x00, .h_delay_c[5] = 0x00,
				.y_delay[0]   = 0x05, .y_delay[1]   = 0x03, .y_delay[2]   = 0x03, .y_delay[3]   = 0x03, .y_delay[4]   = 0x03, .y_delay[5] =   0x03,

			},
			/* clk */
			{
				.clk_adc[0] = 0x02, .clk_adc[1] = 0x02, .clk_adc[2] = 0x02, .clk_adc[3] = 0x02, .clk_adc[4] = 0x02, .clk_adc[5] = 0x02,
				.clk_dec[0] = 0x40, .clk_dec[1] = 0x40, .clk_dec[2] = 0x40, .clk_dec[3] = 0x40, .clk_dec[4] = 0x40, .clk_dec[5] = 0x40,
			},
			/* timing_b */
			{
		/*B9 0x96*/	.h_scaler1[0]  = 0x00, .h_scaler1[1]   = 0x00, .h_scaler1[2]   = 0x00, .h_scaler1[3]   = 0x00, .h_scaler1[4]   = 0x00, .h_scaler1[5]   = 0x00,
		/*B9 0x97*/	.h_scaler2[0]  = 0x00, .h_scaler2[1]   = 0x00, .h_scaler2[2]   = 0x00, .h_scaler2[3]   = 0x00, .h_scaler2[4]   = 0x00, .h_scaler2[5]   = 0x00,
		/*B9 0x98*/	.h_scaler3[0]  = 0x00, .h_scaler3[1]   = 0x00, .h_scaler3[2]   = 0x00, .h_scaler3[3]   = 0x00, .h_scaler3[4]   = 0x00, .h_scaler3[5]   = 0x00,
		/*B9 0x99*/	.h_scaler4[0]  = 0x00, .h_scaler4[1]   = 0x00, .h_scaler4[2]   = 0x00, .h_scaler4[3]   = 0x00, .h_scaler4[4]   = 0x00, .h_scaler4[5]   = 0x00,
		/*B9 0x9a*/	.h_scaler5[0]  = 0x00, .h_scaler5[1]   = 0x00, .h_scaler5[2]   = 0x00, .h_scaler5[3]   = 0x00, .h_scaler5[4]   = 0x00, .h_scaler5[5]   = 0x00,
		/*B9 0x9b*/	.h_scaler6[0]  = 0x00, .h_scaler6[1]   = 0x00, .h_scaler6[2]   = 0x00, .h_scaler6[3]   = 0x00, .h_scaler6[4]   = 0x00, .h_scaler6[5]   = 0x00,
		/*B9 0x9c*/	.h_scaler7[0]  = 0x00, .h_scaler7[1]   = 0x00, .h_scaler7[2]   = 0x00, .h_scaler7[3]   = 0x00, .h_scaler7[4]   = 0x00, .h_scaler7[5]   = 0x00,
		/*B9 0x9d*/	.h_scaler8[0]  = 0x00, .h_scaler8[1]   = 0x00, .h_scaler8[2]   = 0x00, .h_scaler8[3]   = 0x00, .h_scaler8[4]   = 0x00, .h_scaler8[5]   = 0x00,
		/*B9 0x9e*/	.h_scaler9[0]  = 0x00, .h_scaler9[1]   = 0x00, .h_scaler9[2]   = 0x00, .h_scaler9[3]   = 0x00, .h_scaler9[4]   = 0x00, .h_scaler9[5]   = 0x00,


		/*B9 0x40*/	.pn_auto[0]    	= 0x00, .pn_auto[1]		= 0x00, .pn_auto[2]    	= 0x00, .pn_auto[3]    	= 0x00, .pn_auto[4]    	= 0x00, .pn_auto[5]    	= 0x00,

		/*B5 0x90*/	.comb_mode[0]      = 0x01, .comb_mode[1]	  = 0x01, .comb_mode[2]      = 0x01, .comb_mode[3]      = 0x01, .comb_mode[4]  	   = 0x01, .comb_mode[5]      = 0x01,
		/*B9 0xb9*/	.h_pll_op_a[0]     = 0x72, .h_pll_op_a[1]     = 0x72, .h_pll_op_a[2]     = 0x72, .h_pll_op_a[3]     = 0x72, .h_pll_op_a[4]     = 0x72, .h_pll_op_a[5]     = 0x72,
		/*B9 0x57*/	.mem_path[0]	   = 0x00, .mem_path[1]	      = 0x00, .mem_path[2]	     = 0x00, .mem_path[3]	    = 0x00, .mem_path[4]	   = 0x00, .mem_path[5]	      = 0x00,
					.fsc_lock_speed[0] = 0xdc, .fsc_lock_speed[1] = 0xdc, .fsc_lock_speed[2] = 0xdc, .fsc_lock_speed[3] = 0xdc, .fsc_lock_speed[4] = 0xdc, .fsc_lock_speed[5] = 0xdc,

		/*B0 0x81*/	.format_set1[0] = 0x00, .format_set1[1] = 0x00, .format_set1[2] = 0x00, .format_set1[3] = 0x00, .format_set1[4] = 0x00, .format_set1[5] = 0x00,
		/*B0 0x85*/	.format_set2[0] = 0x08, .format_set2[1] = 0x08, .format_set2[2] = 0x08, .format_set2[3] = 0x08, .format_set2[4] = 0x08, .format_set2[5] = 0x08,

		/*B0 0x64*/ .v_delay[0]     = 0x20, .v_delay[1]     = 0x20, .v_delay[2]     = 0x20, .v_delay[3]     = 0x20, .v_delay[4]     = 0x20, .v_delay[5]     = 0x20,
			},
		},

		[ AHD30_8M_12_5P ] = /* o */
		{
			/* base */
			{
				.eq_bypass[0] 	= 0x22, .eq_bypass[1] 	= 0x22, .eq_bypass[2] 	= 0x22, .eq_bypass[3] 	= 0x22, .eq_bypass[4] 	= 0x22, .eq_bypass[5] 	= 0x22,    // Bank5 0x30
				.eq_band_sel[0] = 0x77, .eq_band_sel[1] = 0x77, .eq_band_sel[2] = 0x77, .eq_band_sel[3] = 0x67, .eq_band_sel[4] = 0x57, .eq_band_sel[5] = 0x57,    // BankA 0x31
				.eq_gain_sel[0] = 0x78, .eq_gain_sel[1] = 0x7b, .eq_gain_sel[2] = 0x7f, .eq_gain_sel[3] = 0x7e, .eq_gain_sel[4] = 0x7f, .eq_gain_sel[5] = 0x7f,    // BankA 0x32
				.deq_a_on[0] 	= 0x00, .deq_a_on[1] 	= 0x01, .deq_a_on[2] 	= 0x01, .deq_a_on[3] 	= 0x01, .deq_a_on[4] 	= 0x01, .deq_a_on[5] 	= 0x01,    // BankA 0x33
				.deq_a_sel[0] 	= 0x00, .deq_a_sel[1] 	= 0x91, .deq_a_sel[2] 	= 0x93, .deq_a_sel[3] 	= 0x98, .deq_a_sel[4] 	= 0x98, .deq_a_sel[5] 	= 0x98,    // BankA 0x34
				.deq_b_sel[0] 	= 0x00, .deq_b_sel[1] 	= 0x00, .deq_b_sel[2] 	= 0x00, .deq_b_sel[3] 	= 0x20, .deq_b_sel[4] 	= 0x00, .deq_b_sel[5] 	= 0x00,    // BankA 0x35
			},
			/* coeff */
			{
				.deqA_01[0] = 0xAC, .deqA_01[1] = 0xAC, .deqA_01[2] = 0xAC, .deqA_01[3] = 0xAC, .deqA_01[4] = 0xAC, .deqA_01[5] = 0xAC,		// BankA 0x30
				.deqA_02[0] = 0x78, .deqA_02[1] = 0x78, .deqA_02[2] = 0x78, .deqA_02[3] = 0x78, .deqA_02[4] = 0x78, .deqA_02[5] = 0x78,		// BankA 0x31
				.deqA_03[0] = 0x17, .deqA_03[1] = 0x17, .deqA_03[2] = 0x17, .deqA_03[3] = 0x17, .deqA_03[4] = 0x17, .deqA_03[5] = 0x17,		// BankA 0x32
				.deqA_04[0] = 0xC1, .deqA_04[1] = 0xC1, .deqA_04[2] = 0xC1, .deqA_04[3] = 0xC1, .deqA_04[4] = 0xC1, .deqA_04[5] = 0xC1,     // BankA 0x33
				.deqA_05[0] = 0x40, .deqA_05[1] = 0x40, .deqA_05[2] = 0x40, .deqA_05[3] = 0x40, .deqA_05[4] = 0x40, .deqA_05[5] = 0x40,     // BankA 0x34
				.deqA_06[0] = 0x00, .deqA_06[1] = 0x00, .deqA_06[2] = 0x00, .deqA_06[3] = 0x00, .deqA_06[4] = 0x00, .deqA_06[5] = 0x00,     // BankA 0x35
				.deqA_07[0] = 0xC3, .deqA_07[1] = 0xC3, .deqA_07[2] = 0xC3, .deqA_07[3] = 0xC3, .deqA_07[4] = 0xC3, .deqA_07[5] = 0xC3,     // BankA 0x36
				.deqA_08[0] = 0x0A, .deqA_08[1] = 0x0A, .deqA_08[2] = 0x0A, .deqA_08[3] = 0x0A, .deqA_08[4] = 0x0A, .deqA_08[5] = 0x0A,     // BankA 0x37
				.deqA_09[0] = 0x00, .deqA_09[1] = 0x00, .deqA_09[2] = 0x00, .deqA_09[3] = 0x00, .deqA_09[4] = 0x00, .deqA_09[5] = 0x00,     // BankA 0x38
				.deqA_10[0] = 0x02, .deqA_10[1] = 0x02, .deqA_10[2] = 0x02, .deqA_10[3] = 0x02, .deqA_10[4] = 0x02, .deqA_10[5] = 0x02,     // BankA 0x39
				.deqA_11[0] = 0x00, .deqA_11[1] = 0x00, .deqA_11[2] = 0x00, .deqA_11[3] = 0x00, .deqA_11[4] = 0x00, .deqA_11[5] = 0x00,     // BankA 0x3a
				.deqA_12[0] = 0xB2, .deqA_12[1] = 0xB2, .deqA_12[2] = 0xB2, .deqA_12[3] = 0xB2, .deqA_12[4] = 0xB2, .deqA_12[5] = 0xB2,     // BankA 0x3b
			},
			/* color */
			{
				.contrast[0] 		= 0xa0, .contrast[1] 		= 0x9c, .contrast[2] 		= 0x90, .contrast[3] 		= 0x95, .contrast[4] 		= 0x90, .contrast[5] 		= 0x8a,
				.h_peaking[0] 		= 0x0f, .h_peaking[1] 		= 0x0f, .h_peaking[2] 		= 0x0f, .h_peaking[3] 		= 0x0f, .h_peaking[4] 		= 0x0f, .h_peaking[5] 		= 0x0f,
				.c_filter[0]		= 0x82, .c_filter[1] 		= 0x82, .c_filter[2]	 	= 0x92, .c_filter[3] 		= 0x92, .c_filter[4] 		= 0xa2, .c_filter[5] 		= 0xb2,

				.hue[0] 			= 0x04, .hue[1] 			= 0x04, .hue[2] 			= 0x04, .hue[3] 			= 0x04, .hue[4] 			= 0x04, .hue[5] 			= 0x04,
				.u_gain[0] 			= 0x10, .u_gain[1] 			= 0x10, .u_gain[2] 			= 0x04, .u_gain[3] 			= 0xfc, .u_gain[4] 			= 0xfc, .u_gain[5] 			= 0xfc,
				.v_gain[0] 			= 0x10, .v_gain[1] 			= 0x10, .v_gain[2] 			= 0x04, .v_gain[3] 			= 0xf4, .v_gain[4] 			= 0x08, .v_gain[5] 			= 0x08,
				.u_offset[0] 		= 0xfb, .u_offset[1] 		= 0xfb, .u_offset[2] 		= 0xfb, .u_offset[3] 		= 0xfb, .u_offset[4] 		= 0xfb, .u_offset[5] 		= 0xfb,
				.v_offset[0] 		= 0xf8, .v_offset[1] 		= 0xf8, .v_offset[2] 		= 0xf8, .v_offset[3] 		= 0xf8, .v_offset[4] 		= 0xf8, .v_offset[5] 		= 0xf8,

				.black_level[0] 	= 0x84, .black_level[1] 	= 0x82, .black_level[2] 	= 0x84, .black_level[3] 	= 0x85, .black_level[4] 	= 0x89, .black_level[5] 	= 0x8c,
				.acc_ref[0]			= 0x57, .acc_ref[1]			= 0x57, .acc_ref[2]			= 0x57, .acc_ref[3]			= 0x57, .acc_ref[4]			= 0x57, .acc_ref[5]			= 0x57,
				.cti_delay[0]		= 0x80, .cti_delay[1]		= 0x80, .cti_delay[2]		= 0x80, .cti_delay[3]		= 0x80, .cti_delay[4]		= 0x80, .cti_delay[5]		= 0x80,
				.sub_saturation[0] 	= 0xb0, .sub_saturation[1] 	= 0xb0, .sub_saturation[2] 	= 0xa0, .sub_saturation[3] 	= 0xd0, .sub_saturation[4] 	= 0xb4, .sub_saturation[5] 	= 0x90,

				.burst_dec_a[0] 	= 0x2a, .burst_dec_a[1] 	= 0x2a, .burst_dec_a[2] 	= 0x2a, .burst_dec_a[3] 	= 0x2a, .burst_dec_a[4] 	= 0x2a, .burst_dec_a[5] 	= 0x2a,
				.burst_dec_b[0] 	= 0x00, .burst_dec_b[1] 	= 0x00, .burst_dec_b[2] 	= 0x00, .burst_dec_b[3] 	= 0x00, .burst_dec_b[4] 	= 0x00, .burst_dec_b[5] 	= 0x00,
				.burst_dec_c[0] 	= 0x30, .burst_dec_c[1] 	= 0x30, .burst_dec_c[2] 	= 0x30, .burst_dec_c[3] 	= 0x30, .burst_dec_c[4] 	= 0x30, .burst_dec_c[5] 	= 0x30,

				.c_option[0] 		= 0x80, .c_option[1] 		= 0x80, .c_option[2] 		= 0x80, .c_option[3] 		= 0x90, .c_option[4] 		= 0x90, .c_option[5] 		= 0x90,

				.y_filter_b[0]		= 0x10, .y_filter_b[1]		= 0x10, .y_filter_b[2]		= 0x10, .y_filter_b[3]		= 0x10, .y_filter_b[4]		= 0x10, .y_filter_b[5]		= 0x10,
				.y_filter_b_sel[0]	= 0x1e,	.y_filter_b_sel[1]	= 0x1e,	.y_filter_b_sel[2]	= 0x1e, .y_filter_b_sel[3]	= 0x1e, .y_filter_b_sel[4]	= 0x1e, .y_filter_b_sel[5]	= 0x1e,
			},
			/* timing_a */
			{
				.h_delay_a[0] = 0x84, .h_delay_a[1] = 0x82, .h_delay_a[2] = 0x80, .h_delay_a[3] = 0x7f, .h_delay_a[4] = 0x7f, .h_delay_a[5] = 0x7f,
				.h_delay_b[0] = 0x10, .h_delay_b[1] = 0x10, .h_delay_b[2] = 0x10, .h_delay_b[3] = 0x10, .h_delay_b[4] = 0x10, .h_delay_b[5] = 0x10,
				.h_delay_c[0] = 0x02, .h_delay_c[1] = 0x02, .h_delay_c[2] = 0x02, .h_delay_c[3] = 0x02, .h_delay_c[4] = 0x02, .h_delay_c[5] = 0x02,
				.y_delay[0]   = 0x05, .y_delay[1]   = 0x05, .y_delay[2]   = 0x05, .y_delay[3]   = 0x05, .y_delay[4]   = 0x05, .y_delay[5] =   0x05,

			},
			/* clk */
			{
				.clk_adc[0] = 0x05, .clk_adc[1] = 0x05, .clk_adc[2] = 0x05, .clk_adc[3] = 0x05, .clk_adc[4] = 0x05, .clk_adc[5] = 0x05,
				.clk_dec[0] = 0x44, .clk_dec[1] = 0x44, .clk_dec[2] = 0x44, .clk_dec[3] = 0x44, .clk_dec[4] = 0x44, .clk_dec[5] = 0x44,
			},
			/* timing_b */
			{
	/*B9 0x96*/	.h_scaler1[0]  = 0x00, .h_scaler1[1]   = 0x00, .h_scaler1[2]   = 0x00, .h_scaler1[3]   = 0x00, .h_scaler1[4]   = 0x00, .h_scaler1[5]   = 0x00,
	/*B9 0x97*/	.h_scaler2[0]  = 0x00, .h_scaler2[1]   = 0x00, .h_scaler2[2]   = 0x00, .h_scaler2[3]   = 0x00, .h_scaler2[4]   = 0x00, .h_scaler2[5]   = 0x00,
	/*B9 0x98*/	.h_scaler3[0]  = 0x00, .h_scaler3[1]   = 0x00, .h_scaler3[2]   = 0x00, .h_scaler3[3]   = 0x00, .h_scaler3[4]   = 0x00, .h_scaler3[5]   = 0x00,
	/*B9 0x99*/	.h_scaler4[0]  = 0x00, .h_scaler4[1]   = 0x00, .h_scaler4[2]   = 0x00, .h_scaler4[3]   = 0x00, .h_scaler4[4]   = 0x00, .h_scaler4[5]   = 0x00,
	/*B9 0x9a*/	.h_scaler5[0]  = 0x00, .h_scaler5[1]   = 0x00, .h_scaler5[2]   = 0x00, .h_scaler5[3]   = 0x00, .h_scaler5[4]   = 0x00, .h_scaler5[5]   = 0x00,
	/*B9 0x9b*/	.h_scaler6[0]  = 0x00, .h_scaler6[1]   = 0x00, .h_scaler6[2]   = 0x00, .h_scaler6[3]   = 0x00, .h_scaler6[4]   = 0x00, .h_scaler6[5]   = 0x00,
	/*B9 0x9c*/	.h_scaler7[0]  = 0x00, .h_scaler7[1]   = 0x00, .h_scaler7[2]   = 0x00, .h_scaler7[3]   = 0x00, .h_scaler7[4]   = 0x00, .h_scaler7[5]   = 0x00,
	/*B9 0x9d*/	.h_scaler8[0]  = 0x00, .h_scaler8[1]   = 0x00, .h_scaler8[2]   = 0x00, .h_scaler8[3]   = 0x00, .h_scaler8[4]   = 0x00, .h_scaler8[5]   = 0x00,
	/*B9 0x9e*/	.h_scaler9[0]  = 0x00, .h_scaler9[1]   = 0x00, .h_scaler9[2]   = 0x00, .h_scaler9[3]   = 0x00, .h_scaler9[4]   = 0x00, .h_scaler9[5]   = 0x00,


	/*B9 0x40*/	.pn_auto[0]    	= 0x00, .pn_auto[1]		= 0x00, .pn_auto[2]    	= 0x00, .pn_auto[3]    	= 0x00, .pn_auto[4]    	= 0x00, .pn_auto[5]    	= 0x00,

	/*B5 0x90*/	.comb_mode[0]   = 0x01, .comb_mode[1]	= 0x01, .comb_mode[2]   = 0x01, .comb_mode[3]   = 0x01, .comb_mode[4]  	= 0x01, .comb_mode[5]   = 0x01,
	/*B9 0xb9*/	.h_pll_op_a[0]  = 0x72, .h_pll_op_a[1]  = 0x72, .h_pll_op_a[2]  = 0x72, .h_pll_op_a[3]  = 0x72, .h_pll_op_a[4]  = 0x72, .h_pll_op_a[5]  = 0x72,
	/*B9 0x57*/	.mem_path[0]	= 0x00, .mem_path[1]	= 0x00, .mem_path[2]	= 0x00, .mem_path[3]	= 0x00, .mem_path[4]	= 0x00, .mem_path[5]	= 0x00,
				.fsc_lock_speed[0] = 0xdc, .fsc_lock_speed[1] = 0xdc, .fsc_lock_speed[2] = 0xdc, .fsc_lock_speed[3] = 0xdc, .fsc_lock_speed[4] = 0xdc, .fsc_lock_speed[5] = 0xdc,

	/*B0 0x81*/	.format_set1[0] = 0x01, .format_set1[1] = 0x01, .format_set1[2] = 0x01, .format_set1[3] = 0x01, .format_set1[4] = 0x01, .format_set1[5] = 0x01,
	/*B0 0x85*/	.format_set2[0] = 0x08, .format_set2[1] = 0x08, .format_set2[2] = 0x08, .format_set2[3] = 0x08, .format_set2[4] = 0x08, .format_set2[5] = 0x08,

	/*B0 0x64*/ .v_delay[0]     = 0x80, .v_delay[1]     = 0x80, .v_delay[2]     = 0x80, .v_delay[3]     = 0x80, .v_delay[4]     = 0x80, .v_delay[5]     = 0x80,
			},
		},
		[ AHD30_8M_15P ] = { /* o */
		/* base */
			{
				.eq_bypass[0] 	= 0x22, .eq_bypass[1] 	= 0x22, .eq_bypass[2] 	= 0x22, .eq_bypass[3] 	= 0x22, .eq_bypass[4] 	= 0x22, .eq_bypass[5] 	= 0x22,    // Bank5 0x30
				.eq_band_sel[0] = 0x77, .eq_band_sel[1] = 0x77, .eq_band_sel[2] = 0x77, .eq_band_sel[3] = 0x67, .eq_band_sel[4] = 0x57, .eq_band_sel[5] = 0x57,    // BankA 0x31
				.eq_gain_sel[0] = 0x78, .eq_gain_sel[1] = 0x7b, .eq_gain_sel[2] = 0x7f, .eq_gain_sel[3] = 0x7e, .eq_gain_sel[4] = 0x7f, .eq_gain_sel[5] = 0x7f,    // BankA 0x32
				.deq_a_on[0] 	= 0x00, .deq_a_on[1] 	= 0x01, .deq_a_on[2] 	= 0x01, .deq_a_on[3] 	= 0x01, .deq_a_on[4] 	= 0x01, .deq_a_on[5] 	= 0x01,    // BankA 0x33
				.deq_a_sel[0] 	= 0x00, .deq_a_sel[1] 	= 0x91, .deq_a_sel[2] 	= 0x93, .deq_a_sel[3] 	= 0x98, .deq_a_sel[4] 	= 0x98, .deq_a_sel[5] 	= 0x98,    // BankA 0x34
				.deq_b_sel[0] 	= 0x00, .deq_b_sel[1] 	= 0x00, .deq_b_sel[2] 	= 0x00, .deq_b_sel[3] 	= 0x20, .deq_b_sel[4] 	= 0x00, .deq_b_sel[5] 	= 0x00,    // BankA 0x35
			},
			/* coeff */
			{
				.deqA_01[0] = 0xAC, .deqA_01[1] = 0xAC, .deqA_01[2] = 0xAC, .deqA_01[3] = 0xAC, .deqA_01[4] = 0xAC, .deqA_01[5] = 0xAC,		// BankA 0x30
				.deqA_02[0] = 0x78, .deqA_02[1] = 0x78, .deqA_02[2] = 0x78, .deqA_02[3] = 0x78, .deqA_02[4] = 0x78, .deqA_02[5] = 0x78,		// BankA 0x31
				.deqA_03[0] = 0x17, .deqA_03[1] = 0x17, .deqA_03[2] = 0x17, .deqA_03[3] = 0x17, .deqA_03[4] = 0x17, .deqA_03[5] = 0x17,		// BankA 0x32
				.deqA_04[0] = 0xC1, .deqA_04[1] = 0xC1, .deqA_04[2] = 0xC1, .deqA_04[3] = 0xC1, .deqA_04[4] = 0xC1, .deqA_04[5] = 0xC1,     // BankA 0x33
				.deqA_05[0] = 0x40, .deqA_05[1] = 0x40, .deqA_05[2] = 0x40, .deqA_05[3] = 0x40, .deqA_05[4] = 0x40, .deqA_05[5] = 0x40,     // BankA 0x34
				.deqA_06[0] = 0x00, .deqA_06[1] = 0x00, .deqA_06[2] = 0x00, .deqA_06[3] = 0x00, .deqA_06[4] = 0x00, .deqA_06[5] = 0x00,     // BankA 0x35
				.deqA_07[0] = 0xC3, .deqA_07[1] = 0xC3, .deqA_07[2] = 0xC3, .deqA_07[3] = 0xC3, .deqA_07[4] = 0xC3, .deqA_07[5] = 0xC3,     // BankA 0x36
				.deqA_08[0] = 0x0A, .deqA_08[1] = 0x0A, .deqA_08[2] = 0x0A, .deqA_08[3] = 0x0A, .deqA_08[4] = 0x0A, .deqA_08[5] = 0x0A,     // BankA 0x37
				.deqA_09[0] = 0x00, .deqA_09[1] = 0x00, .deqA_09[2] = 0x00, .deqA_09[3] = 0x00, .deqA_09[4] = 0x00, .deqA_09[5] = 0x00,     // BankA 0x38
				.deqA_10[0] = 0x02, .deqA_10[1] = 0x02, .deqA_10[2] = 0x02, .deqA_10[3] = 0x02, .deqA_10[4] = 0x02, .deqA_10[5] = 0x02,     // BankA 0x39
				.deqA_11[0] = 0x00, .deqA_11[1] = 0x00, .deqA_11[2] = 0x00, .deqA_11[3] = 0x00, .deqA_11[4] = 0x00, .deqA_11[5] = 0x00,     // BankA 0x3a
				.deqA_12[0] = 0xB2, .deqA_12[1] = 0xB2, .deqA_12[2] = 0xB2, .deqA_12[3] = 0xB2, .deqA_12[4] = 0xB2, .deqA_12[5] = 0xB2,     // BankA 0x3b
			},
			/* color */
			{
				.contrast[0] 		= 0xa0, .contrast[1] 		= 0x9c, .contrast[2] 		= 0x90, .contrast[3] 		= 0x95, .contrast[4] 		= 0x90, .contrast[5] 		= 0x8a,
				.h_peaking[0] 		= 0x0f, .h_peaking[1] 		= 0x0f, .h_peaking[2] 		= 0x0f, .h_peaking[3] 		= 0x0f, .h_peaking[4] 		= 0x0f, .h_peaking[5] 		= 0x0f,
				.c_filter[0]		= 0x82, .c_filter[1] 		= 0x82, .c_filter[2]	 	= 0x92, .c_filter[3] 		= 0x92, .c_filter[4] 		= 0xa2, .c_filter[5] 		= 0xb2,

				.hue[0] 			= 0x04, .hue[1] 			= 0x04, .hue[2] 			= 0x04, .hue[3] 			= 0x04, .hue[4] 			= 0x04, .hue[5] 			= 0x04,
				.u_gain[0] 			= 0x10, .u_gain[1] 			= 0x10, .u_gain[2] 			= 0x04, .u_gain[3] 			= 0xfc, .u_gain[4] 			= 0xfc, .u_gain[5] 			= 0xfc,
				.v_gain[0] 			= 0x10, .v_gain[1] 			= 0x10, .v_gain[2] 			= 0x04, .v_gain[3] 			= 0xf4, .v_gain[4] 			= 0x08, .v_gain[5] 			= 0x08,
				.u_offset[0] 		= 0xfb, .u_offset[1] 		= 0xfb, .u_offset[2] 		= 0xfb, .u_offset[3] 		= 0xfb, .u_offset[4] 		= 0xfb, .u_offset[5] 		= 0xfb,
				.v_offset[0] 		= 0xf8, .v_offset[1] 		= 0xf8, .v_offset[2] 		= 0xf8, .v_offset[3] 		= 0xf8, .v_offset[4] 		= 0xf8, .v_offset[5] 		= 0xf8,

				.black_level[0] 	= 0x84, .black_level[1] 	= 0x82, .black_level[2] 	= 0x84, .black_level[3] 	= 0x85, .black_level[4] 	= 0x89, .black_level[5] 	= 0x8c,
				.acc_ref[0]			= 0x57, .acc_ref[1]			= 0x57, .acc_ref[2]			= 0x57, .acc_ref[3]			= 0x57, .acc_ref[4]			= 0x57, .acc_ref[5]			= 0x57,
				.cti_delay[0]		= 0x80, .cti_delay[1]		= 0x80, .cti_delay[2]		= 0x80, .cti_delay[3]		= 0x80, .cti_delay[4]		= 0x80, .cti_delay[5]		= 0x80,
				.sub_saturation[0] 	= 0xb0, .sub_saturation[1] 	= 0xb0, .sub_saturation[2] 	= 0xa0, .sub_saturation[3] 	= 0xd0, .sub_saturation[4] 	= 0xb4, .sub_saturation[5] 	= 0x90,

				.burst_dec_a[0] 	= 0x2a, .burst_dec_a[1] 	= 0x2a, .burst_dec_a[2] 	= 0x2a, .burst_dec_a[3] 	= 0x2a, .burst_dec_a[4] 	= 0x2a, .burst_dec_a[5] 	= 0x2a,
				.burst_dec_b[0] 	= 0x00, .burst_dec_b[1] 	= 0x00, .burst_dec_b[2] 	= 0x00, .burst_dec_b[3] 	= 0x00, .burst_dec_b[4] 	= 0x00, .burst_dec_b[5] 	= 0x00,
				.burst_dec_c[0] 	= 0x30, .burst_dec_c[1] 	= 0x30, .burst_dec_c[2] 	= 0x30, .burst_dec_c[3] 	= 0x30, .burst_dec_c[4] 	= 0x30, .burst_dec_c[5] 	= 0x30,

				.c_option[0] 		= 0x80, .c_option[1] 		= 0x80, .c_option[2] 		= 0x80, .c_option[3] 		= 0x90, .c_option[4] 		= 0x90, .c_option[5] 		= 0x90,

				.y_filter_b[0]		= 0x10, .y_filter_b[1]		= 0x10, .y_filter_b[2]		= 0x10, .y_filter_b[3]		= 0x10, .y_filter_b[4]		= 0x10, .y_filter_b[5]		= 0x10,
				.y_filter_b_sel[0]	= 0x1e,	.y_filter_b_sel[1]	= 0x1e,	.y_filter_b_sel[2]	= 0x1e, .y_filter_b_sel[3]	= 0x1e, .y_filter_b_sel[4]	= 0x1e, .y_filter_b_sel[5]	= 0x1e,
			},
			/* timing_a */
			{
				.h_delay_a[0] = 0x80, .h_delay_a[1] = 0x80, .h_delay_a[2] = 0x80, .h_delay_a[3] = 0x7f, .h_delay_a[4] = 0x7f, .h_delay_a[5] = 0x7f,
				.h_delay_b[0] = 0x10, .h_delay_b[1] = 0x10, .h_delay_b[2] = 0x10, .h_delay_b[3] = 0x10, .h_delay_b[4] = 0x10, .h_delay_b[5] = 0x10,
				.h_delay_c[0] = 0x02, .h_delay_c[1] = 0x02, .h_delay_c[2] = 0x02, .h_delay_c[3] = 0x02, .h_delay_c[4] = 0x02, .h_delay_c[5] = 0x02,
				.y_delay[0]   = 0x05, .y_delay[1]   = 0x05, .y_delay[2]   = 0x05, .y_delay[3]   = 0x05, .y_delay[4]   = 0x05, .y_delay[5] =   0x05,

			},
			/* clk */
			{
				.clk_adc[0] = 0x05, .clk_adc[1] = 0x05, .clk_adc[2] = 0x05, .clk_adc[3] = 0x05, .clk_adc[4] = 0x05, .clk_adc[5] = 0x05,
				.clk_dec[0] = 0x44, .clk_dec[1] = 0x44, .clk_dec[2] = 0x44, .clk_dec[3] = 0x44, .clk_dec[4] = 0x44, .clk_dec[5] = 0x44,
			},
			/* timing_b */
			{
		/*B9 0x96*/	.h_scaler1[0]  = 0x00, .h_scaler1[1]   = 0x00, .h_scaler1[2]   = 0x00, .h_scaler1[3]   = 0x00, .h_scaler1[4]   = 0x00, .h_scaler1[5]   = 0x00,
		/*B9 0x97*/	.h_scaler2[0]  = 0x00, .h_scaler2[1]   = 0x00, .h_scaler2[2]   = 0x00, .h_scaler2[3]   = 0x00, .h_scaler2[4]   = 0x00, .h_scaler2[5]   = 0x00,
		/*B9 0x98*/	.h_scaler3[0]  = 0x00, .h_scaler3[1]   = 0x00, .h_scaler3[2]   = 0x00, .h_scaler3[3]   = 0x00, .h_scaler3[4]   = 0x00, .h_scaler3[5]   = 0x00,
		/*B9 0x99*/	.h_scaler4[0]  = 0x00, .h_scaler4[1]   = 0x00, .h_scaler4[2]   = 0x00, .h_scaler4[3]   = 0x00, .h_scaler4[4]   = 0x00, .h_scaler4[5]   = 0x00,
		/*B9 0x9a*/	.h_scaler5[0]  = 0x00, .h_scaler5[1]   = 0x00, .h_scaler5[2]   = 0x00, .h_scaler5[3]   = 0x00, .h_scaler5[4]   = 0x00, .h_scaler5[5]   = 0x00,
		/*B9 0x9b*/	.h_scaler6[0]  = 0x00, .h_scaler6[1]   = 0x00, .h_scaler6[2]   = 0x00, .h_scaler6[3]   = 0x00, .h_scaler6[4]   = 0x00, .h_scaler6[5]   = 0x00,
		/*B9 0x9c*/	.h_scaler7[0]  = 0x00, .h_scaler7[1]   = 0x00, .h_scaler7[2]   = 0x00, .h_scaler7[3]   = 0x00, .h_scaler7[4]   = 0x00, .h_scaler7[5]   = 0x00,
		/*B9 0x9d*/	.h_scaler8[0]  = 0x00, .h_scaler8[1]   = 0x00, .h_scaler8[2]   = 0x00, .h_scaler8[3]   = 0x00, .h_scaler8[4]   = 0x00, .h_scaler8[5]   = 0x00,
		/*B9 0x9e*/	.h_scaler9[0]  = 0x00, .h_scaler9[1]   = 0x00, .h_scaler9[2]   = 0x00, .h_scaler9[3]   = 0x00, .h_scaler9[4]   = 0x00, .h_scaler9[5]   = 0x00,


		/*B9 0x40*/	.pn_auto[0]    	= 0x00, .pn_auto[1]		= 0x00, .pn_auto[2]    	= 0x00, .pn_auto[3]    	= 0x00, .pn_auto[4]    	= 0x00, .pn_auto[5]    	= 0x00,

		/*B5 0x90*/	.comb_mode[0]   = 0x01, .comb_mode[1]	= 0x01, .comb_mode[2]   = 0x01, .comb_mode[3]   = 0x01, .comb_mode[4]  	= 0x01, .comb_mode[5]   = 0x01,
		/*B9 0xb9*/	.h_pll_op_a[0]  = 0x72, .h_pll_op_a[1]  = 0x72, .h_pll_op_a[2]  = 0x72, .h_pll_op_a[3]  = 0x72, .h_pll_op_a[4]  = 0x72, .h_pll_op_a[5]  = 0x72,
		/*B9 0x57*/	.mem_path[0]	= 0x00, .mem_path[1]	= 0x00, .mem_path[2]	= 0x00, .mem_path[3]	= 0x00, .mem_path[4]	= 0x00, .mem_path[5]	= 0x00,
				.fsc_lock_speed[0] = 0xdc, .fsc_lock_speed[1] = 0xdc, .fsc_lock_speed[2] = 0xdc, .fsc_lock_speed[3] = 0xdc, .fsc_lock_speed[4] = 0xdc, .fsc_lock_speed[5] = 0xdc,

		/*B0 0x81*/	.format_set1[0] = 0x02, .format_set1[1] = 0x02, .format_set1[2] = 0x02, .format_set1[3] = 0x02, .format_set1[4] = 0x02, .format_set1[5] = 0x02,
		/*B0 0x85*/	.format_set2[0] = 0x08, .format_set2[1] = 0x08, .format_set2[2] = 0x08, .format_set2[3] = 0x08, .format_set2[4] = 0x08, .format_set2[5] = 0x08,

		/*B0 0x64*/ .v_delay[0]     = 0x80, .v_delay[1]     = 0x80, .v_delay[2]     = 0x80, .v_delay[3]     = 0x80, .v_delay[4]     = 0x80, .v_delay[5]     = 0x80,
			},
		},

#ifdef __FOR_IDIS_TVI_2M
	[ TVI_FHD_25P ] = /* o */
	{
		/* base */
		{
			.eq_bypass[0] 	= 0x22, .eq_bypass[1] 	= 0x22, .eq_bypass[2] 	= 0x22, .eq_bypass[3] 	= 0x22, .eq_bypass[4] 	= 0x22, .eq_bypass[5] 	= 0x22,    // Bank5 0x30
			.eq_band_sel[0] = 0x77, .eq_band_sel[1] = 0x77, .eq_band_sel[2] = 0x77, .eq_band_sel[3] = 0x67, .eq_band_sel[4] = 0x57, .eq_band_sel[5] = 0x57,    // BankA 0x31
			.eq_gain_sel[0] = 0x78, .eq_gain_sel[1] = 0x7a, .eq_gain_sel[2] = 0x7f, .eq_gain_sel[3] = 0x7f, .eq_gain_sel[4] = 0x7f, .eq_gain_sel[5] = 0x7f,    // BankA 0x32
			.deq_a_on[0] 	= 0x00, .deq_a_on[1] 	= 0x01, .deq_a_on[2] 	= 0x01, .deq_a_on[3] 	= 0x01, .deq_a_on[4] 	= 0x01, .deq_a_on[5] 	= 0x01,    // BankA 0x33
			.deq_a_sel[0] 	= 0x00, .deq_a_sel[1] 	= 0x92, .deq_a_sel[2] 	= 0x93, .deq_a_sel[3] 	= 0x98, .deq_a_sel[4] 	= 0x94, .deq_a_sel[5] 	= 0x95,    // BankA 0x34
			.deq_b_sel[0] 	= 0x00, .deq_b_sel[1] 	= 0x00, .deq_b_sel[2] 	= 0x00, .deq_b_sel[3] 	= 0x00, .deq_b_sel[4] 	= 0x00, .deq_b_sel[5] 	= 0x00,    // BankA 0x35
		},
		/* coeff */
		{
			.deqA_01[0] = 0xAC, .deqA_01[1] = 0xAC, .deqA_01[2] = 0xAC, .deqA_01[3] = 0xAC, .deqA_01[4] = 0xAC, .deqA_01[5] = 0xAC,		// BankA 0x30
			.deqA_02[0] = 0x78, .deqA_02[1] = 0x78, .deqA_02[2] = 0x78, .deqA_02[3] = 0x78, .deqA_02[4] = 0x78, .deqA_02[5] = 0x78,		// BankA 0x31
			.deqA_03[0] = 0x17, .deqA_03[1] = 0x17, .deqA_03[2] = 0x17, .deqA_03[3] = 0x17, .deqA_03[4] = 0x17, .deqA_03[5] = 0x17,		// BankA 0x32
			.deqA_04[0] = 0xC1, .deqA_04[1] = 0xC1, .deqA_04[2] = 0xC1, .deqA_04[3] = 0xC1, .deqA_04[4] = 0xC1, .deqA_04[5] = 0xC1,     // BankA 0x33
			.deqA_05[0] = 0x40, .deqA_05[1] = 0x40, .deqA_05[2] = 0x40, .deqA_05[3] = 0x40, .deqA_05[4] = 0x40, .deqA_05[5] = 0x40,     // BankA 0x34
			.deqA_06[0] = 0x00, .deqA_06[1] = 0x00, .deqA_06[2] = 0x00, .deqA_06[3] = 0x00, .deqA_06[4] = 0x00, .deqA_06[5] = 0x00,     // BankA 0x35
			.deqA_07[0] = 0xC3, .deqA_07[1] = 0xC3, .deqA_07[2] = 0xC3, .deqA_07[3] = 0xC3, .deqA_07[4] = 0xC3, .deqA_07[5] = 0xC3,     // BankA 0x36
			.deqA_08[0] = 0x0A, .deqA_08[1] = 0x0A, .deqA_08[2] = 0x0A, .deqA_08[3] = 0x0A, .deqA_08[4] = 0x0A, .deqA_08[5] = 0x0A,     // BankA 0x37
			.deqA_09[0] = 0x00, .deqA_09[1] = 0x00, .deqA_09[2] = 0x00, .deqA_09[3] = 0x00, .deqA_09[4] = 0x00, .deqA_09[5] = 0x00,     // BankA 0x38
			.deqA_10[0] = 0x02, .deqA_10[1] = 0x02, .deqA_10[2] = 0x02, .deqA_10[3] = 0x02, .deqA_10[4] = 0x02, .deqA_10[5] = 0x02,     // BankA 0x39
			.deqA_11[0] = 0x00, .deqA_11[1] = 0x00, .deqA_11[2] = 0x00, .deqA_11[3] = 0x00, .deqA_11[4] = 0x00, .deqA_11[5] = 0x00,     // BankA 0x3a
			.deqA_12[0] = 0xB2, .deqA_12[1] = 0xB2, .deqA_12[2] = 0xB2, .deqA_12[3] = 0xB2, .deqA_12[4] = 0xB2, .deqA_12[5] = 0xB2,     // BankA 0x3b
		},
		/* color */
		{
			.contrast[0] 		= 0x90, .contrast[1] 		= 0x90, .contrast[2] 		= 0x90, .contrast[3] 		= 0x90, .contrast[4] 		= 0x90, .contrast[5] 		= 0x90,
			.h_peaking[0] 		= 0x20, .h_peaking[1] 		= 0x20, .h_peaking[2] 		= 0x20, .h_peaking[3] 		= 0x20, .h_peaking[4] 		= 0x20, .h_peaking[5] 		= 0x20,
			.c_filter[0]		= 0x82, .c_filter[1] 		= 0x82, .c_filter[2]	 	= 0x92, .c_filter[3] 		= 0xb2, .c_filter[4] 		= 0xb2, .c_filter[5] 		= 0xb2,

			.hue[0] 			= 0x04, .hue[1] 			= 0x04, .hue[2] 			= 0x04, .hue[3] 			= 0x04, .hue[4] 			= 0x04, .hue[5] 			= 0x04,
			.u_gain[0] 			= 0x70, .u_gain[1] 			= 0x70, .u_gain[2] 			= 0x70, .u_gain[3] 			= 0x70, .u_gain[4] 			= 0x70, .u_gain[5] 			= 0x70,
			.v_gain[0] 			= 0xe8, .v_gain[1] 			= 0x00, .v_gain[2] 			= 0x00, .v_gain[3] 			= 0x00, .v_gain[4] 			= 0x00, .v_gain[5] 			= 0x00,
			.u_offset[0] 		= 0xf4, .u_offset[1] 		= 0xf4, .u_offset[2] 		= 0xf4, .u_offset[3] 		= 0xf4, .u_offset[4] 		= 0xf4, .u_offset[5] 		= 0xf4,
			.v_offset[0] 		= 0xf4, .v_offset[1] 		= 0xf4, .v_offset[2] 		= 0xf4, .v_offset[3] 		= 0xf4, .v_offset[4] 		= 0xf4, .v_offset[5] 		= 0xf4,

			.black_level[0] 	= 0x8c, .black_level[1] 	= 0x88, .black_level[2] 	= 0x88, .black_level[3] 	= 0x8c, .black_level[4] 	= 0x8c, .black_level[5] 	= 0x8c,
			.acc_ref[0]			= 0x57, .acc_ref[1]			= 0x57, .acc_ref[2]			= 0x57, .acc_ref[3]			= 0x57, .acc_ref[4]			= 0x57, .acc_ref[5]			= 0x27,
			.cti_delay[0]		= 0x80, .cti_delay[1]		= 0x80, .cti_delay[2]		= 0x80, .cti_delay[3]		= 0x80, .cti_delay[4]		= 0x80, .cti_delay[5]		= 0x80,
			.sub_saturation[0] 	= 0xff, .sub_saturation[1] 	= 0xff, .sub_saturation[2] 	= 0xff, .sub_saturation[3] 	= 0xff, .sub_saturation[4] 	= 0xff, .sub_saturation[5] 	= 0xff,

			.burst_dec_a[0] 	= 0x2a, .burst_dec_a[1] 	= 0x2a, .burst_dec_a[2] 	= 0x2a, .burst_dec_a[3] 	= 0x2a, .burst_dec_a[4] 	= 0x2a, .burst_dec_a[5] 	= 0x2a,
			.burst_dec_b[0] 	= 0x00, .burst_dec_b[1] 	= 0x00, .burst_dec_b[2] 	= 0x00, .burst_dec_b[3] 	= 0x00, .burst_dec_b[4] 	= 0x00, .burst_dec_b[5] 	= 0x00,
			.burst_dec_c[0] 	= 0x30, .burst_dec_c[1] 	= 0x30, .burst_dec_c[2] 	= 0x30, .burst_dec_c[3] 	= 0x30, .burst_dec_c[4] 	= 0x30, .burst_dec_c[5] 	= 0x30,

			.c_option[0] 		= 0x80, .c_option[1] 		= 0x80, .c_option[2] 		= 0x80, .c_option[3] 		= 0xa0, .c_option[4] 		= 0xb0, .c_option[5] 		= 0xb0,

			.y_filter_b[0]		= 0x10, .y_filter_b[1]		= 0x10, .y_filter_b[2]		= 0x10, .y_filter_b[3]		= 0x10, .y_filter_b[4]		= 0x10, .y_filter_b[5]		= 0x10,
			.y_filter_b_sel[0]	= 0x1e,	.y_filter_b_sel[1]	= 0x1e,	.y_filter_b_sel[2]	= 0x1e, .y_filter_b_sel[3]	= 0x1e, .y_filter_b_sel[4]	= 0x1e, .y_filter_b_sel[5]	= 0x1e,
		},
		/* timing_a */
		{
			.h_delay_a[0] = 0x82, .h_delay_a[1] = 0x82, .h_delay_a[2] = 0x82, .h_delay_a[3] = 0x82, .h_delay_a[4] = 0x82, .h_delay_a[5] = 0x82,
			.h_delay_b[0] = 0x10, .h_delay_b[1] = 0x10, .h_delay_b[2] = 0x10, .h_delay_b[3] = 0x10, .h_delay_b[4] = 0x10, .h_delay_b[5] = 0x10,
			.h_delay_c[0] = 0x02, .h_delay_c[1] = 0x02, .h_delay_c[2] = 0x02, .h_delay_c[3] = 0x02, .h_delay_c[4] = 0x02, .h_delay_c[5] = 0x02,
			.y_delay[0]   = 0x05, .y_delay[1]   = 0x05, .y_delay[2]   = 0x05, .y_delay[3]   = 0x05, .y_delay[4]   = 0x20, .y_delay[5] =   0x20,

		},
		/* clk */
		{
			.clk_adc[0] = 0x05, .clk_adc[1] = 0x05, .clk_adc[2] = 0x05, .clk_adc[3] = 0x05, .clk_adc[4] = 0x05, .clk_adc[5] = 0x05,
			.clk_dec[0] = 0x44, .clk_dec[1] = 0x44, .clk_dec[2] = 0x44, .clk_dec[3] = 0x44, .clk_dec[4] = 0x44, .clk_dec[5] = 0x44,
		},
		/* timing_b */
		{
/*B9 0x96*/	.h_scaler1[0]  = 0x01, .h_scaler1[1]   = 0x01, .h_scaler1[2]   = 0x01, .h_scaler1[3]   = 0x01, .h_scaler1[4]   = 0x01, .h_scaler1[5]   = 0x01,
/*B9 0x97*/	.h_scaler2[0]  = 0x00, .h_scaler2[1]   = 0x00, .h_scaler2[2]   = 0x00, .h_scaler2[3]   = 0x00, .h_scaler2[4]   = 0x00, .h_scaler2[5]   = 0x00,
/*B9 0x98*/	.h_scaler3[0]  = 0x00, .h_scaler3[1]   = 0x00, .h_scaler3[2]   = 0x00, .h_scaler3[3]   = 0x00, .h_scaler3[4]   = 0x00, .h_scaler3[5]   = 0x00,
/*B9 0x99*/	.h_scaler4[0]  = 0x00, .h_scaler4[1]   = 0x00, .h_scaler4[2]   = 0x00, .h_scaler4[3]   = 0x00, .h_scaler4[4]   = 0x00, .h_scaler4[5]   = 0x00,
/*B9 0x9a*/	.h_scaler5[0]  = 0x00, .h_scaler5[1]   = 0x00, .h_scaler5[2]   = 0x00, .h_scaler5[3]   = 0x00, .h_scaler5[4]   = 0x00, .h_scaler5[5]   = 0x00,
/*B9 0x9b*/	.h_scaler6[0]  = 0x00, .h_scaler6[1]   = 0x00, .h_scaler6[2]   = 0x00, .h_scaler6[3]   = 0x00, .h_scaler6[4]   = 0x00, .h_scaler6[5]   = 0x00,
/*B9 0x9c*/	.h_scaler7[0]  = 0x00, .h_scaler7[1]   = 0x00, .h_scaler7[2]   = 0x00, .h_scaler7[3]   = 0x00, .h_scaler7[4]   = 0x00, .h_scaler7[5]   = 0x00,
/*B9 0x9d*/	.h_scaler8[0]  = 0x00, .h_scaler8[1]   = 0x00, .h_scaler8[2]   = 0x00, .h_scaler8[3]   = 0x00, .h_scaler8[4]   = 0x00, .h_scaler8[5]   = 0x00,
/*B9 0x9e*/	.h_scaler9[0]  = 0x00, .h_scaler9[1]   = 0x00, .h_scaler9[2]   = 0x00, .h_scaler9[3]   = 0x00, .h_scaler9[4]   = 0x00, .h_scaler9[5]   = 0x00,


/*B9 0x40*/	.pn_auto[0]    	= 0x00, .pn_auto[1]		= 0x00, .pn_auto[2]    	= 0x00, .pn_auto[3]    	= 0x00, .pn_auto[4]    	= 0x00, .pn_auto[5]    	= 0x00,

/*B5 0x90*/	.comb_mode[0]   = 0x05, .comb_mode[1]	= 0x05, .comb_mode[2]   = 0x05, .comb_mode[3]   = 0x05, .comb_mode[4]  	= 0x05, .comb_mode[5]   = 0x05,
/*B9 0xb9*/	.h_pll_op_a[0]  = 0x72, .h_pll_op_a[1]  = 0x72, .h_pll_op_a[2]  = 0x72, .h_pll_op_a[3]  = 0x72, .h_pll_op_a[4]  = 0x72, .h_pll_op_a[5]  = 0x72,
/*B9 0x57*/	.mem_path[0]	= 0x00, .mem_path[1]	= 0x00, .mem_path[2]	= 0x00, .mem_path[3]	= 0x10, .mem_path[4]	= 0x10, .mem_path[5]	= 0x10,
			.fsc_lock_speed[0] = 0xdc, .fsc_lock_speed[1] = 0xdc, .fsc_lock_speed[2] = 0xdc, .fsc_lock_speed[3] = 0xdc, .fsc_lock_speed[4] = 0xdc, .fsc_lock_speed[5] = 0xdc,

/*B0 0x81*/	.format_set1[0] = 0x03, .format_set1[1] = 0x03, .format_set1[2] = 0x03, .format_set1[3] = 0x03, .format_set1[4] = 0x03, .format_set1[5] = 0x03,
/*B0 0x85*/	.format_set2[0] = 0x01, .format_set2[1] = 0x01, .format_set2[2] = 0x01, .format_set2[3] = 0x01, .format_set2[4] = 0x01, .format_set2[5] = 0x01,

/*B0 0x64*/ .v_delay[0]     = 0x20, .v_delay[1]     = 0x20, .v_delay[2]     = 0x20, .v_delay[3]     = 0x20, .v_delay[4]     = 0x20, .v_delay[5]     = 0x20,
		},
	},
	[ TVI_FHD_30P ] =
	{
		/* base */
		{
			.eq_bypass[0] 	= 0x22, .eq_bypass[1] 	= 0x22, .eq_bypass[2] 	= 0x22, .eq_bypass[3] 	= 0x22, .eq_bypass[4] 	= 0x22, .eq_bypass[5] 	= 0x22,    // Bank5 0x30
			.eq_band_sel[0] = 0x77, .eq_band_sel[1] = 0x77, .eq_band_sel[2] = 0x77, .eq_band_sel[3] = 0x67, .eq_band_sel[4] = 0x57, .eq_band_sel[5] = 0x57,    // BankA 0x31
			.eq_gain_sel[0] = 0x78, .eq_gain_sel[1] = 0x7a, .eq_gain_sel[2] = 0x7f, .eq_gain_sel[3] = 0x7f, .eq_gain_sel[4] = 0x7f, .eq_gain_sel[5] = 0x7f,    // BankA 0x32
			.deq_a_on[0] 	= 0x00, .deq_a_on[1] 	= 0x01, .deq_a_on[2] 	= 0x01, .deq_a_on[3] 	= 0x01, .deq_a_on[4] 	= 0x01, .deq_a_on[5] 	= 0x01,    // BankA 0x33
			.deq_a_sel[0] 	= 0x00, .deq_a_sel[1] 	= 0x92, .deq_a_sel[2] 	= 0x93, .deq_a_sel[3] 	= 0x98, .deq_a_sel[4] 	= 0x94, .deq_a_sel[5] 	= 0x95,    // BankA 0x34
			.deq_b_sel[0] 	= 0x00, .deq_b_sel[1] 	= 0x00, .deq_b_sel[2] 	= 0x00, .deq_b_sel[3] 	= 0x00, .deq_b_sel[4] 	= 0x00, .deq_b_sel[5] 	= 0x00,    // BankA 0x35
		},
		/* coeff */
		{
			.deqA_01[0] = 0xAC, .deqA_01[1] = 0xAC, .deqA_01[2] = 0xAC, .deqA_01[3] = 0xAC, .deqA_01[4] = 0xAC, .deqA_01[5] = 0xAC,		// BankA 0x30
			.deqA_02[0] = 0x78, .deqA_02[1] = 0x78, .deqA_02[2] = 0x78, .deqA_02[3] = 0x78, .deqA_02[4] = 0x78, .deqA_02[5] = 0x78,		// BankA 0x31
			.deqA_03[0] = 0x17, .deqA_03[1] = 0x17, .deqA_03[2] = 0x17, .deqA_03[3] = 0x17, .deqA_03[4] = 0x17, .deqA_03[5] = 0x17,		// BankA 0x32
			.deqA_04[0] = 0xC1, .deqA_04[1] = 0xC1, .deqA_04[2] = 0xC1, .deqA_04[3] = 0xC1, .deqA_04[4] = 0xC1, .deqA_04[5] = 0xC1,     // BankA 0x33
			.deqA_05[0] = 0x40, .deqA_05[1] = 0x40, .deqA_05[2] = 0x40, .deqA_05[3] = 0x40, .deqA_05[4] = 0x40, .deqA_05[5] = 0x40,     // BankA 0x34
			.deqA_06[0] = 0x00, .deqA_06[1] = 0x00, .deqA_06[2] = 0x00, .deqA_06[3] = 0x00, .deqA_06[4] = 0x00, .deqA_06[5] = 0x00,     // BankA 0x35
			.deqA_07[0] = 0xC3, .deqA_07[1] = 0xC3, .deqA_07[2] = 0xC3, .deqA_07[3] = 0xC3, .deqA_07[4] = 0xC3, .deqA_07[5] = 0xC3,     // BankA 0x36
			.deqA_08[0] = 0x0A, .deqA_08[1] = 0x0A, .deqA_08[2] = 0x0A, .deqA_08[3] = 0x0A, .deqA_08[4] = 0x0A, .deqA_08[5] = 0x0A,     // BankA 0x37
			.deqA_09[0] = 0x00, .deqA_09[1] = 0x00, .deqA_09[2] = 0x00, .deqA_09[3] = 0x00, .deqA_09[4] = 0x00, .deqA_09[5] = 0x00,     // BankA 0x38
			.deqA_10[0] = 0x02, .deqA_10[1] = 0x02, .deqA_10[2] = 0x02, .deqA_10[3] = 0x02, .deqA_10[4] = 0x02, .deqA_10[5] = 0x02,     // BankA 0x39
			.deqA_11[0] = 0x00, .deqA_11[1] = 0x00, .deqA_11[2] = 0x00, .deqA_11[3] = 0x00, .deqA_11[4] = 0x00, .deqA_11[5] = 0x00,     // BankA 0x3a
			.deqA_12[0] = 0xB2, .deqA_12[1] = 0xB2, .deqA_12[2] = 0xB2, .deqA_12[3] = 0xB2, .deqA_12[4] = 0xB2, .deqA_12[5] = 0xB2,     // BankA 0x3b
		},
		/* color */
		{
			.contrast[0] 		= 0x90, .contrast[1] 		= 0x90, .contrast[2] 		= 0x90, .contrast[3] 		= 0x90, .contrast[4] 		= 0x90, .contrast[5] 		= 0x90,
			.h_peaking[0] 		= 0x20, .h_peaking[1] 		= 0x20, .h_peaking[2] 		= 0x20, .h_peaking[3] 		= 0x20, .h_peaking[4] 		= 0x20, .h_peaking[5] 		= 0x20,
			.c_filter[0]		= 0x82, .c_filter[1] 		= 0x82, .c_filter[2]	 	= 0x92, .c_filter[3] 		= 0xb2, .c_filter[4] 		= 0xb2, .c_filter[5] 		= 0xb2,

			.hue[0] 			= 0x04, .hue[1] 			= 0x04, .hue[2] 			= 0x04, .hue[3] 			= 0x04, .hue[4] 			= 0x04, .hue[5] 			= 0x04,
			.u_gain[0] 			= 0x70, .u_gain[1] 			= 0x70, .u_gain[2] 			= 0x70, .u_gain[3] 			= 0x70, .u_gain[4] 			= 0x70, .u_gain[5] 			= 0x70,
			.v_gain[0] 			= 0xe8, .v_gain[1] 			= 0x00, .v_gain[2] 			= 0x00, .v_gain[3] 			= 0x00, .v_gain[4] 			= 0x00, .v_gain[5] 			= 0x00,
			.u_offset[0] 		= 0xf4, .u_offset[1] 		= 0xf4, .u_offset[2] 		= 0xf4, .u_offset[3] 		= 0xf4, .u_offset[4] 		= 0xf4, .u_offset[5] 		= 0xf4,
			.v_offset[0] 		= 0xf4, .v_offset[1] 		= 0xf4, .v_offset[2] 		= 0xf4, .v_offset[3] 		= 0xf4, .v_offset[4] 		= 0xf4, .v_offset[5] 		= 0xf4,

			.black_level[0] 	= 0x8c, .black_level[1] 	= 0x88, .black_level[2] 	= 0x88, .black_level[3] 	= 0x8c, .black_level[4] 	= 0x8c, .black_level[5] 	= 0x8c,
			.acc_ref[0]			= 0x57, .acc_ref[1]			= 0x57, .acc_ref[2]			= 0x57, .acc_ref[3]			= 0x57, .acc_ref[4]			= 0x57, .acc_ref[5]			= 0x27,
			.cti_delay[0]		= 0x80, .cti_delay[1]		= 0x80, .cti_delay[2]		= 0x80, .cti_delay[3]		= 0x80, .cti_delay[4]		= 0x80, .cti_delay[5]		= 0x80,
			.sub_saturation[0] 	= 0xff, .sub_saturation[1] 	= 0xff, .sub_saturation[2] 	= 0xff, .sub_saturation[3] 	= 0xff, .sub_saturation[4] 	= 0xff, .sub_saturation[5] 	= 0xff,

			.burst_dec_a[0] 	= 0x2a, .burst_dec_a[1] 	= 0x2a, .burst_dec_a[2] 	= 0x2a, .burst_dec_a[3] 	= 0x2a, .burst_dec_a[4] 	= 0x2a, .burst_dec_a[5] 	= 0x2a,
			.burst_dec_b[0] 	= 0x00, .burst_dec_b[1] 	= 0x00, .burst_dec_b[2] 	= 0x00, .burst_dec_b[3] 	= 0x00, .burst_dec_b[4] 	= 0x00, .burst_dec_b[5] 	= 0x00,
			.burst_dec_c[0] 	= 0x30, .burst_dec_c[1] 	= 0x30, .burst_dec_c[2] 	= 0x30, .burst_dec_c[3] 	= 0x30, .burst_dec_c[4] 	= 0x30, .burst_dec_c[5] 	= 0x30,

			.c_option[0] 		= 0x80, .c_option[1] 		= 0x80, .c_option[2] 		= 0x80, .c_option[3] 		= 0xa0, .c_option[4] 		= 0xb0, .c_option[5] 		= 0xb0,

			.y_filter_b[0]		= 0x10, .y_filter_b[1]		= 0x10, .y_filter_b[2]		= 0x10, .y_filter_b[3]		= 0x10, .y_filter_b[4]		= 0x10, .y_filter_b[5]		= 0x10,
			.y_filter_b_sel[0]	= 0x1e,	.y_filter_b_sel[1]	= 0x1e,	.y_filter_b_sel[2]	= 0x1e, .y_filter_b_sel[3]	= 0x1e, .y_filter_b_sel[4]	= 0x1e, .y_filter_b_sel[5]	= 0x1e,
		},
		/* timing_a */
		{
			.h_delay_a[0] = 0x80, .h_delay_a[1] = 0x80, .h_delay_a[2] = 0x80, .h_delay_a[3] = 0x80, .h_delay_a[4] = 0x80, .h_delay_a[5] = 0x80,
			.h_delay_b[0] = 0x10, .h_delay_b[1] = 0x10, .h_delay_b[2] = 0x10, .h_delay_b[3] = 0x10, .h_delay_b[4] = 0x10, .h_delay_b[5] = 0x10,
			.h_delay_c[0] = 0x03, .h_delay_c[1] = 0x03, .h_delay_c[2] = 0x03, .h_delay_c[3] = 0x02, .h_delay_c[4] = 0x03, .h_delay_c[5] = 0x03,
			.y_delay[0]   = 0x07, .y_delay[1]   = 0x07, .y_delay[2]   = 0x07, .y_delay[3]   = 0x05, .y_delay[4]   = 0x20, .y_delay[5] =   0x20,

		},
		/* clk */
		{
			.clk_adc[0] = 0x05, .clk_adc[1] = 0x05, .clk_adc[2] = 0x05, .clk_adc[3] = 0x05, .clk_adc[4] = 0x05, .clk_adc[5] = 0x05,
			.clk_dec[0] = 0x44, .clk_dec[1] = 0x44, .clk_dec[2] = 0x44, .clk_dec[3] = 0x44, .clk_dec[4] = 0x44, .clk_dec[5] = 0x44,
		},
		/* timing_b */
		{
/*B9 0x96*/	.h_scaler1[0]  = 0x01, .h_scaler1[1]   = 0x01, .h_scaler1[2]   = 0x01, .h_scaler1[3]   = 0x01, .h_scaler1[4]   = 0x01, .h_scaler1[5]   = 0x01,
/*B9 0x97*/	.h_scaler2[0]  = 0x00, .h_scaler2[1]   = 0x00, .h_scaler2[2]   = 0x00, .h_scaler2[3]   = 0x00, .h_scaler2[4]   = 0x00, .h_scaler2[5]   = 0x00,
/*B9 0x98*/	.h_scaler3[0]  = 0x00, .h_scaler3[1]   = 0x00, .h_scaler3[2]   = 0x00, .h_scaler3[3]   = 0x00, .h_scaler3[4]   = 0x00, .h_scaler3[5]   = 0x00,
/*B9 0x99*/	.h_scaler4[0]  = 0x00, .h_scaler4[1]   = 0x00, .h_scaler4[2]   = 0x00, .h_scaler4[3]   = 0x00, .h_scaler4[4]   = 0x00, .h_scaler4[5]   = 0x00,
/*B9 0x9a*/	.h_scaler5[0]  = 0x00, .h_scaler5[1]   = 0x00, .h_scaler5[2]   = 0x00, .h_scaler5[3]   = 0x00, .h_scaler5[4]   = 0x00, .h_scaler5[5]   = 0x00,
/*B9 0x9b*/	.h_scaler6[0]  = 0x00, .h_scaler6[1]   = 0x00, .h_scaler6[2]   = 0x00, .h_scaler6[3]   = 0x00, .h_scaler6[4]   = 0x00, .h_scaler6[5]   = 0x00,
/*B9 0x9c*/	.h_scaler7[0]  = 0x00, .h_scaler7[1]   = 0x00, .h_scaler7[2]   = 0x00, .h_scaler7[3]   = 0x00, .h_scaler7[4]   = 0x00, .h_scaler7[5]   = 0x00,
/*B9 0x9d*/	.h_scaler8[0]  = 0x00, .h_scaler8[1]   = 0x00, .h_scaler8[2]   = 0x00, .h_scaler8[3]   = 0x00, .h_scaler8[4]   = 0x00, .h_scaler8[5]   = 0x00,
/*B9 0x9e*/	.h_scaler9[0]  = 0x00, .h_scaler9[1]   = 0x00, .h_scaler9[2]   = 0x00, .h_scaler9[3]   = 0x00, .h_scaler9[4]   = 0x00, .h_scaler9[5]   = 0x00,


/*B9 0x40*/	.pn_auto[0]    	= 0x00, .pn_auto[1]		= 0x00, .pn_auto[2]    	= 0x00, .pn_auto[3]    	= 0x00, .pn_auto[4]    	= 0x00, .pn_auto[5]    	= 0x00,

/*B5 0x90*/	.comb_mode[0]   = 0x05, .comb_mode[1]	= 0x05, .comb_mode[2]   = 0x05, .comb_mode[3]   = 0x05, .comb_mode[4]  	= 0x05, .comb_mode[5]   = 0x05,
/*B9 0xb9*/	.h_pll_op_a[0]     = 0x72, .h_pll_op_a[1]     = 0x72, .h_pll_op_a[2]     = 0x72, .h_pll_op_a[3]     = 0x72, .h_pll_op_a[4]     = 0x72, .h_pll_op_a[5]     = 0x72,
/*B9 0x57*/	.mem_path[0]	= 0x00, .mem_path[1]	= 0x00, .mem_path[2]	= 0x00, .mem_path[3]	= 0x10, .mem_path[4]	= 0x10, .mem_path[5]	= 0x10,
			.fsc_lock_speed[0] = 0xdc, .fsc_lock_speed[1] = 0xdc, .fsc_lock_speed[2] = 0xdc, .fsc_lock_speed[3] = 0xdc, .fsc_lock_speed[4] = 0xdc, .fsc_lock_speed[5] = 0xdc,

/*B0 0x81*/	.format_set1[0] = 0x02, .format_set1[1] = 0x02, .format_set1[2] = 0x02, .format_set1[3] = 0x02, .format_set1[4] = 0x02, .format_set1[5] = 0x02,
/*B0 0x85*/	.format_set2[0] = 0x01, .format_set2[1] = 0x01, .format_set2[2] = 0x01, .format_set2[3] = 0x01, .format_set2[4] = 0x01, .format_set2[5] = 0x01,

/*B0 0x64*/ .v_delay[0]     = 0x20, .v_delay[1]     = 0x20, .v_delay[2]     = 0x20, .v_delay[3]     = 0x20, .v_delay[4]     = 0x20, .v_delay[5]     = 0x20,
		},
	},

#elif __FOR_HIK_DEMO_180208
	[ TVI_FHD_25P ] = /* o */
	{
		/* base */
		{
			.eq_bypass[0] 	= 0x22, .eq_bypass[1] 	= 0x22, .eq_bypass[2] 	= 0x22, .eq_bypass[3] 	= 0x22, .eq_bypass[4] 	= 0x22, .eq_bypass[5] 	= 0x22,    // Bank5 0x30
			.eq_band_sel[0] = 0x77, .eq_band_sel[1] = 0x77, .eq_band_sel[2] = 0x77, .eq_band_sel[3] = 0x63, .eq_band_sel[4] = 0x53, .eq_band_sel[5] = 0x57,    // BankA 0x31
			.eq_gain_sel[0] = 0x78, .eq_gain_sel[1] = 0x78, .eq_gain_sel[2] = 0x6f, .eq_gain_sel[3] = 0x7f, .eq_gain_sel[4] = 0x7d, .eq_gain_sel[5] = 0x7d,    // BankA 0x32
			.deq_a_on[0] 	= 0x00, .deq_a_on[1] 	= 0x01, .deq_a_on[2] 	= 0x01, .deq_a_on[3] 	= 0x01, .deq_a_on[4] 	= 0x01, .deq_a_on[5] 	= 0x01,    // BankA 0x33
			.deq_a_sel[0] 	= 0x00, .deq_a_sel[1] 	= 0x91, .deq_a_sel[2] 	= 0x93, .deq_a_sel[3] 	= 0x94, .deq_a_sel[4] 	= 0x93, .deq_a_sel[5] 	= 0x93,    // BankA 0x34
			.deq_b_sel[0] 	= 0x00, .deq_b_sel[1] 	= 0x00, .deq_b_sel[2] 	= 0x00, .deq_b_sel[3] 	= 0x00, .deq_b_sel[4] 	= 0x00, .deq_b_sel[5] 	= 0x00,    // BankA 0x35
		},
		/* coeff */
		{
			.deqA_01[0] = 0xAC, .deqA_01[1] = 0xAC, .deqA_01[2] = 0xAC, .deqA_01[3] = 0xAC, .deqA_01[4] = 0xAC, .deqA_01[5] = 0xAC,		// BankA 0x30
			.deqA_02[0] = 0x78, .deqA_02[1] = 0x78, .deqA_02[2] = 0x78, .deqA_02[3] = 0x78, .deqA_02[4] = 0x78, .deqA_02[5] = 0x78,		// BankA 0x31
			.deqA_03[0] = 0x17, .deqA_03[1] = 0x17, .deqA_03[2] = 0x17, .deqA_03[3] = 0x17, .deqA_03[4] = 0x17, .deqA_03[5] = 0x17,		// BankA 0x32
			.deqA_04[0] = 0xC1, .deqA_04[1] = 0xC1, .deqA_04[2] = 0xC1, .deqA_04[3] = 0xC1, .deqA_04[4] = 0xC1, .deqA_04[5] = 0xC1,     // BankA 0x33
			.deqA_05[0] = 0x40, .deqA_05[1] = 0x40, .deqA_05[2] = 0x40, .deqA_05[3] = 0x40, .deqA_05[4] = 0x40, .deqA_05[5] = 0x40,     // BankA 0x34
			.deqA_06[0] = 0x00, .deqA_06[1] = 0x00, .deqA_06[2] = 0x00, .deqA_06[3] = 0x00, .deqA_06[4] = 0x00, .deqA_06[5] = 0x00,     // BankA 0x35
			.deqA_07[0] = 0xC3, .deqA_07[1] = 0xC3, .deqA_07[2] = 0xC3, .deqA_07[3] = 0xC3, .deqA_07[4] = 0xC3, .deqA_07[5] = 0xC3,     // BankA 0x36
			.deqA_08[0] = 0x0A, .deqA_08[1] = 0x0A, .deqA_08[2] = 0x0A, .deqA_08[3] = 0x0A, .deqA_08[4] = 0x0A, .deqA_08[5] = 0x0A,     // BankA 0x37
			.deqA_09[0] = 0x00, .deqA_09[1] = 0x00, .deqA_09[2] = 0x00, .deqA_09[3] = 0x00, .deqA_09[4] = 0x00, .deqA_09[5] = 0x00,     // BankA 0x38
			.deqA_10[0] = 0x02, .deqA_10[1] = 0x02, .deqA_10[2] = 0x02, .deqA_10[3] = 0x02, .deqA_10[4] = 0x02, .deqA_10[5] = 0x02,     // BankA 0x39
			.deqA_11[0] = 0x00, .deqA_11[1] = 0x00, .deqA_11[2] = 0x00, .deqA_11[3] = 0x00, .deqA_11[4] = 0x00, .deqA_11[5] = 0x00,     // BankA 0x3a
			.deqA_12[0] = 0xB2, .deqA_12[1] = 0xB2, .deqA_12[2] = 0xB2, .deqA_12[3] = 0xB2, .deqA_12[4] = 0xB2, .deqA_12[5] = 0xB2,     // BankA 0x3b
		},
		/* color */
		{
			.contrast[0] 		= 0x82, .contrast[1] 		= 0x7c, .contrast[2] 		= 0x78, .contrast[3] 		= 0x6c, .contrast[4] 		= 0x80, .contrast[5] 		= 0x80,
			.h_peaking[0] 		= 0x00, .h_peaking[1] 		= 0x3f, .h_peaking[2] 		= 0x3f, .h_peaking[3] 		= 0x3f, .h_peaking[4] 		= 0x00, .h_peaking[5] 		= 0x00,
			.c_filter[0]		= 0x82, .c_filter[1] 		= 0x82, .c_filter[2]	 	= 0x92, .c_filter[3] 		= 0x92, .c_filter[4] 		= 0x92, .c_filter[5] 		= 0xc4,

			.hue[0] 			= 0x00, .hue[1] 			= 0xfe, .hue[2] 			= 0xfe, .hue[3] 			= 0xfe, .hue[4] 			= 0x00, .hue[5] 			= 0x00,
			.u_gain[0] 			= 0x20, .u_gain[1] 			= 0x00, .u_gain[2] 			= 0x00, .u_gain[3] 			= 0x00, .u_gain[4] 			= 0x30, .u_gain[5] 			= 0x30,
			.v_gain[0] 			= 0x00, .v_gain[1] 			= 0xf8, .v_gain[2] 			= 0xf8, .v_gain[3] 			= 0xf8, .v_gain[4] 			= 0xf0, .v_gain[5] 			= 0xf0,
			.u_offset[0] 		= 0x04, .u_offset[1] 		= 0x04, .u_offset[2] 		= 0x04, .u_offset[3] 		= 0x04, .u_offset[4] 		= 0x04, .u_offset[5] 		= 0x04,
			.v_offset[0] 		= 0xf8, .v_offset[1] 		= 0xf8, .v_offset[2] 		= 0xf8, .v_offset[3] 		= 0xf8, .v_offset[4] 		= 0xf8, .v_offset[5] 		= 0xf8,

			.black_level[0] 	= 0x86, .black_level[1] 	= 0x88, .black_level[2] 	= 0x88, .black_level[3] 	= 0x88, .black_level[4] 	= 0x90, .black_level[5] 	= 0x90,
			.acc_ref[0]			= 0x57, .acc_ref[1]			= 0x57, .acc_ref[2]			= 0x57, .acc_ref[3]			= 0x57, .acc_ref[4]			= 0x40, .acc_ref[5]			= 0x40,
			.cti_delay[0]		= 0x80, .cti_delay[1]		= 0x80, .cti_delay[2]		= 0x80, .cti_delay[3]		= 0x80, .cti_delay[4]		= 0x80, .cti_delay[5]		= 0x80,
			.sub_saturation[0] 	= 0xf0, .sub_saturation[1] 	= 0xe0, .sub_saturation[2] 	= 0xe0, .sub_saturation[3] 	= 0xe0, .sub_saturation[4] 	= 0xf0, .sub_saturation[5] 	= 0xf0,

			.burst_dec_a[0] 	= 0x2a, .burst_dec_a[1] 	= 0x2a, .burst_dec_a[2] 	= 0x2a, .burst_dec_a[3] 	= 0x2a, .burst_dec_a[4] 	= 0x2a, .burst_dec_a[5] 	= 0x2a,
			.burst_dec_b[0] 	= 0x00, .burst_dec_b[1] 	= 0x00, .burst_dec_b[2] 	= 0x00, .burst_dec_b[3] 	= 0x00, .burst_dec_b[4] 	= 0x00, .burst_dec_b[5] 	= 0x00,
			.burst_dec_c[0] 	= 0x30, .burst_dec_c[1] 	= 0x30, .burst_dec_c[2] 	= 0x30, .burst_dec_c[3] 	= 0x30, .burst_dec_c[4] 	= 0x30, .burst_dec_c[5] 	= 0x30,

			.c_option[0] 		= 0x80, .c_option[1] 		= 0x80, .c_option[2] 		= 0x80, .c_option[3] 		= 0x80, .c_option[4] 		= 0xb0, .c_option[5] 		= 0xb0,

			.y_filter_b[0]		= 0x10, .y_filter_b[1]		= 0x10, .y_filter_b[2]		= 0x10, .y_filter_b[3]		= 0x10, .y_filter_b[4]		= 0x10, .y_filter_b[5]		= 0x10,
			.y_filter_b_sel[0]	= 0x1e,	.y_filter_b_sel[1]	= 0x1e,	.y_filter_b_sel[2]	= 0x1e, .y_filter_b_sel[3]	= 0x1e, .y_filter_b_sel[4]	= 0x1e, .y_filter_b_sel[5]	= 0x1e,
		},
		/* timing_a */
		{
			.h_delay_a[0] = 0x82, .h_delay_a[1] = 0x82, .h_delay_a[2] = 0x82, .h_delay_a[3] = 0x82, .h_delay_a[4] = 0x82, .h_delay_a[5] = 0x82,
			.h_delay_b[0] = 0x10, .h_delay_b[1] = 0x10, .h_delay_b[2] = 0x10, .h_delay_b[3] = 0x10, .h_delay_b[4] = 0x10, .h_delay_b[5] = 0x10,
			.h_delay_c[0] = 0x02, .h_delay_c[1] = 0x02, .h_delay_c[2] = 0x02, .h_delay_c[3] = 0x02, .h_delay_c[4] = 0x02, .h_delay_c[5] = 0x02,
			.y_delay[0]   = 0x05, .y_delay[1]   = 0x05, .y_delay[2]   = 0x05, .y_delay[3]   = 0x05, .y_delay[4]   = 0x20, .y_delay[5] =   0x20,

		},
		/* clk */
		{
			.clk_adc[0] = 0x05, .clk_adc[1] = 0x05, .clk_adc[2] = 0x05, .clk_adc[3] = 0x05, .clk_adc[4] = 0x05, .clk_adc[5] = 0x05,
			.clk_dec[0] = 0x44, .clk_dec[1] = 0x44, .clk_dec[2] = 0x44, .clk_dec[3] = 0x44, .clk_dec[4] = 0x44, .clk_dec[5] = 0x44,
		},
		/* timing_b */
		{
/*B9 0x96*/	.h_scaler1[0]  = 0x01, .h_scaler1[1]   = 0x01, .h_scaler1[2]   = 0x01, .h_scaler1[3]   = 0x01, .h_scaler1[4]   = 0x01, .h_scaler1[5]   = 0x01,
/*B9 0x97*/	.h_scaler2[0]  = 0x00, .h_scaler2[1]   = 0x00, .h_scaler2[2]   = 0x00, .h_scaler2[3]   = 0x00, .h_scaler2[4]   = 0x00, .h_scaler2[5]   = 0x00,
/*B9 0x98*/	.h_scaler3[0]  = 0x00, .h_scaler3[1]   = 0x00, .h_scaler3[2]   = 0x00, .h_scaler3[3]   = 0x00, .h_scaler3[4]   = 0x00, .h_scaler3[5]   = 0x00,
/*B9 0x99*/	.h_scaler4[0]  = 0x00, .h_scaler4[1]   = 0x00, .h_scaler4[2]   = 0x00, .h_scaler4[3]   = 0x00, .h_scaler4[4]   = 0x00, .h_scaler4[5]   = 0x00,
/*B9 0x9a*/	.h_scaler5[0]  = 0x00, .h_scaler5[1]   = 0x00, .h_scaler5[2]   = 0x00, .h_scaler5[3]   = 0x00, .h_scaler5[4]   = 0x00, .h_scaler5[5]   = 0x00,
/*B9 0x9b*/	.h_scaler6[0]  = 0x00, .h_scaler6[1]   = 0x00, .h_scaler6[2]   = 0x00, .h_scaler6[3]   = 0x00, .h_scaler6[4]   = 0x00, .h_scaler6[5]   = 0x00,
/*B9 0x9c*/	.h_scaler7[0]  = 0x00, .h_scaler7[1]   = 0x00, .h_scaler7[2]   = 0x00, .h_scaler7[3]   = 0x00, .h_scaler7[4]   = 0x00, .h_scaler7[5]   = 0x00,
/*B9 0x9d*/	.h_scaler8[0]  = 0x00, .h_scaler8[1]   = 0x00, .h_scaler8[2]   = 0x00, .h_scaler8[3]   = 0x00, .h_scaler8[4]   = 0x00, .h_scaler8[5]   = 0x00,
/*B9 0x9e*/	.h_scaler9[0]  = 0x00, .h_scaler9[1]   = 0x00, .h_scaler9[2]   = 0x00, .h_scaler9[3]   = 0x00, .h_scaler9[4]   = 0x00, .h_scaler9[5]   = 0x00,


/*B9 0x40*/	.pn_auto[0]    	= 0x00, .pn_auto[1]		= 0x00, .pn_auto[2]    	= 0x00, .pn_auto[3]    	= 0x00, .pn_auto[4]    	= 0x00, .pn_auto[5]    	= 0x00,

/*B5 0x90*/	.comb_mode[0]   = 0x05, .comb_mode[1]	= 0x05, .comb_mode[2]   = 0x05, .comb_mode[3]   = 0x05, .comb_mode[4]  	= 0x05, .comb_mode[5]   = 0x05,
/*B9 0xb9*/	.h_pll_op_a[0]  = 0x72, .h_pll_op_a[1]  = 0x72, .h_pll_op_a[2]  = 0x72, .h_pll_op_a[3]  = 0x72, .h_pll_op_a[4]  = 0x72, .h_pll_op_a[5]  = 0x72,
/*B9 0x57*/	.mem_path[0]	= 0x00, .mem_path[1]	= 0x00, .mem_path[2]	= 0x00, .mem_path[3]	= 0x10, .mem_path[4]	= 0x10, .mem_path[5]	= 0x10,
			.fsc_lock_speed[0] = 0xdc, .fsc_lock_speed[1] = 0xdc, .fsc_lock_speed[2] = 0xdc, .fsc_lock_speed[3] = 0xdc, .fsc_lock_speed[4] = 0xdc, .fsc_lock_speed[5] = 0xdc,

/*B0 0x81*/	.format_set1[0] = 0x03, .format_set1[1] = 0x03, .format_set1[2] = 0x03, .format_set1[3] = 0x03, .format_set1[4] = 0x03, .format_set1[5] = 0x03,
/*B0 0x85*/	.format_set2[0] = 0x01, .format_set2[1] = 0x01, .format_set2[2] = 0x01, .format_set2[3] = 0x01, .format_set2[4] = 0x01, .format_set2[5] = 0x01,

/*B0 0x64*/ .v_delay[0]     = 0x20, .v_delay[1]     = 0x20, .v_delay[2]     = 0x20, .v_delay[3]     = 0x20, .v_delay[4]     = 0x20, .v_delay[5]     = 0x20,
		},
	},
	[ TVI_FHD_30P ] =
	{
		/* base */
		{
			.eq_bypass[0] 	= 0x22, .eq_bypass[1] 	= 0x22, .eq_bypass[2] 	= 0x22, .eq_bypass[3] 	= 0x22, .eq_bypass[4] 	= 0x22, .eq_bypass[5] 	= 0x22,    // Bank5 0x30
			.eq_band_sel[0] = 0x77, .eq_band_sel[1] = 0x77, .eq_band_sel[2] = 0x77, .eq_band_sel[3] = 0x67, .eq_band_sel[4] = 0x57, .eq_band_sel[5] = 0x57,    // BankA 0x31
			.eq_gain_sel[0] = 0x78, .eq_gain_sel[1] = 0x7a, .eq_gain_sel[2] = 0x7f, .eq_gain_sel[3] = 0x7f, .eq_gain_sel[4] = 0x7f, .eq_gain_sel[5] = 0x7f,    // BankA 0x32
			.deq_a_on[0] 	= 0x00, .deq_a_on[1] 	= 0x01, .deq_a_on[2] 	= 0x01, .deq_a_on[3] 	= 0x01, .deq_a_on[4] 	= 0x01, .deq_a_on[5] 	= 0x01,    // BankA 0x33
			.deq_a_sel[0] 	= 0x00, .deq_a_sel[1] 	= 0x92, .deq_a_sel[2] 	= 0x93, .deq_a_sel[3] 	= 0x98, .deq_a_sel[4] 	= 0x94, .deq_a_sel[5] 	= 0x95,    // BankA 0x34
			.deq_b_sel[0] 	= 0x00, .deq_b_sel[1] 	= 0x00, .deq_b_sel[2] 	= 0x00, .deq_b_sel[3] 	= 0x00, .deq_b_sel[4] 	= 0x00, .deq_b_sel[5] 	= 0x00,    // BankA 0x35
		},
		/* coeff */
		{
			.deqA_01[0] = 0xAC, .deqA_01[1] = 0xAC, .deqA_01[2] = 0xAC, .deqA_01[3] = 0xAC, .deqA_01[4] = 0xAC, .deqA_01[5] = 0xAC,		// BankA 0x30
			.deqA_02[0] = 0x78, .deqA_02[1] = 0x78, .deqA_02[2] = 0x78, .deqA_02[3] = 0x78, .deqA_02[4] = 0x78, .deqA_02[5] = 0x78,		// BankA 0x31
			.deqA_03[0] = 0x17, .deqA_03[1] = 0x17, .deqA_03[2] = 0x17, .deqA_03[3] = 0x17, .deqA_03[4] = 0x17, .deqA_03[5] = 0x17,		// BankA 0x32
			.deqA_04[0] = 0xC1, .deqA_04[1] = 0xC1, .deqA_04[2] = 0xC1, .deqA_04[3] = 0xC1, .deqA_04[4] = 0xC1, .deqA_04[5] = 0xC1,     // BankA 0x33
			.deqA_05[0] = 0x40, .deqA_05[1] = 0x40, .deqA_05[2] = 0x40, .deqA_05[3] = 0x40, .deqA_05[4] = 0x40, .deqA_05[5] = 0x40,     // BankA 0x34
			.deqA_06[0] = 0x00, .deqA_06[1] = 0x00, .deqA_06[2] = 0x00, .deqA_06[3] = 0x00, .deqA_06[4] = 0x00, .deqA_06[5] = 0x00,     // BankA 0x35
			.deqA_07[0] = 0xC3, .deqA_07[1] = 0xC3, .deqA_07[2] = 0xC3, .deqA_07[3] = 0xC3, .deqA_07[4] = 0xC3, .deqA_07[5] = 0xC3,     // BankA 0x36
			.deqA_08[0] = 0x0A, .deqA_08[1] = 0x0A, .deqA_08[2] = 0x0A, .deqA_08[3] = 0x0A, .deqA_08[4] = 0x0A, .deqA_08[5] = 0x0A,     // BankA 0x37
			.deqA_09[0] = 0x00, .deqA_09[1] = 0x00, .deqA_09[2] = 0x00, .deqA_09[3] = 0x00, .deqA_09[4] = 0x00, .deqA_09[5] = 0x00,     // BankA 0x38
			.deqA_10[0] = 0x02, .deqA_10[1] = 0x02, .deqA_10[2] = 0x02, .deqA_10[3] = 0x02, .deqA_10[4] = 0x02, .deqA_10[5] = 0x02,     // BankA 0x39
			.deqA_11[0] = 0x00, .deqA_11[1] = 0x00, .deqA_11[2] = 0x00, .deqA_11[3] = 0x00, .deqA_11[4] = 0x00, .deqA_11[5] = 0x00,     // BankA 0x3a
			.deqA_12[0] = 0xB2, .deqA_12[1] = 0xB2, .deqA_12[2] = 0xB2, .deqA_12[3] = 0xB2, .deqA_12[4] = 0xB2, .deqA_12[5] = 0xB2,     // BankA 0x3b
		},
		/* color */
		{
			.contrast[0] 		= 0x90, .contrast[1] 		= 0x90, .contrast[2] 		= 0x90, .contrast[3] 		= 0x90, .contrast[4] 		= 0x90, .contrast[5] 		= 0x90,
			.h_peaking[0] 		= 0x20, .h_peaking[1] 		= 0x20, .h_peaking[2] 		= 0x20, .h_peaking[3] 		= 0x20, .h_peaking[4] 		= 0x20, .h_peaking[5] 		= 0x20,
			.c_filter[0]		= 0x82, .c_filter[1] 		= 0x82, .c_filter[2]	 	= 0x92, .c_filter[3] 		= 0xb2, .c_filter[4] 		= 0xb2, .c_filter[5] 		= 0xb2,

			.hue[0] 			= 0x04, .hue[1] 			= 0x04, .hue[2] 			= 0x04, .hue[3] 			= 0x04, .hue[4] 			= 0x04, .hue[5] 			= 0x04,
			.u_gain[0] 			= 0x70, .u_gain[1] 			= 0x70, .u_gain[2] 			= 0x70, .u_gain[3] 			= 0x70, .u_gain[4] 			= 0x70, .u_gain[5] 			= 0x70,
			.v_gain[0] 			= 0xe8, .v_gain[1] 			= 0x00, .v_gain[2] 			= 0x00, .v_gain[3] 			= 0x00, .v_gain[4] 			= 0x00, .v_gain[5] 			= 0x00,
			.u_offset[0] 		= 0xf4, .u_offset[1] 		= 0xf4, .u_offset[2] 		= 0xf4, .u_offset[3] 		= 0xf4, .u_offset[4] 		= 0xf4, .u_offset[5] 		= 0xf4,
			.v_offset[0] 		= 0xf4, .v_offset[1] 		= 0xf4, .v_offset[2] 		= 0xf4, .v_offset[3] 		= 0xf4, .v_offset[4] 		= 0xf4, .v_offset[5] 		= 0xf4,

			.black_level[0] 	= 0x8c, .black_level[1] 	= 0x88, .black_level[2] 	= 0x88, .black_level[3] 	= 0x8c, .black_level[4] 	= 0x8c, .black_level[5] 	= 0x8c,
			.acc_ref[0]			= 0x57, .acc_ref[1]			= 0x57, .acc_ref[2]			= 0x57, .acc_ref[3]			= 0x57, .acc_ref[4]			= 0x57, .acc_ref[5]			= 0x27,
			.cti_delay[0]		= 0x80, .cti_delay[1]		= 0x80, .cti_delay[2]		= 0x80, .cti_delay[3]		= 0x80, .cti_delay[4]		= 0x80, .cti_delay[5]		= 0x80,
			.sub_saturation[0] 	= 0xff, .sub_saturation[1] 	= 0xff, .sub_saturation[2] 	= 0xff, .sub_saturation[3] 	= 0xff, .sub_saturation[4] 	= 0xff, .sub_saturation[5] 	= 0xff,

			.burst_dec_a[0] 	= 0x2a, .burst_dec_a[1] 	= 0x2a, .burst_dec_a[2] 	= 0x2a, .burst_dec_a[3] 	= 0x2a, .burst_dec_a[4] 	= 0x2a, .burst_dec_a[5] 	= 0x2a,
			.burst_dec_b[0] 	= 0x00, .burst_dec_b[1] 	= 0x00, .burst_dec_b[2] 	= 0x00, .burst_dec_b[3] 	= 0x00, .burst_dec_b[4] 	= 0x00, .burst_dec_b[5] 	= 0x00,
			.burst_dec_c[0] 	= 0x30, .burst_dec_c[1] 	= 0x30, .burst_dec_c[2] 	= 0x30, .burst_dec_c[3] 	= 0x30, .burst_dec_c[4] 	= 0x30, .burst_dec_c[5] 	= 0x30,

			.c_option[0] 		= 0x80, .c_option[1] 		= 0x80, .c_option[2] 		= 0x80, .c_option[3] 		= 0xa0, .c_option[4] 		= 0xb0, .c_option[5] 		= 0xb0,

			.y_filter_b[0]		= 0x10, .y_filter_b[1]		= 0x10, .y_filter_b[2]		= 0x10, .y_filter_b[3]		= 0x10, .y_filter_b[4]		= 0x10, .y_filter_b[5]		= 0x10,
			.y_filter_b_sel[0]	= 0x1e,	.y_filter_b_sel[1]	= 0x1e,	.y_filter_b_sel[2]	= 0x1e, .y_filter_b_sel[3]	= 0x1e, .y_filter_b_sel[4]	= 0x1e, .y_filter_b_sel[5]	= 0x1e,
		},
		/* timing_a */
		{
			.h_delay_a[0] = 0x80, .h_delay_a[1] = 0x80, .h_delay_a[2] = 0x80, .h_delay_a[3] = 0x80, .h_delay_a[4] = 0x80, .h_delay_a[5] = 0x80,
			.h_delay_b[0] = 0x10, .h_delay_b[1] = 0x10, .h_delay_b[2] = 0x10, .h_delay_b[3] = 0x10, .h_delay_b[4] = 0x10, .h_delay_b[5] = 0x10,
			.h_delay_c[0] = 0x03, .h_delay_c[1] = 0x03, .h_delay_c[2] = 0x03, .h_delay_c[3] = 0x02, .h_delay_c[4] = 0x03, .h_delay_c[5] = 0x03,
			.y_delay[0]   = 0x07, .y_delay[1]   = 0x07, .y_delay[2]   = 0x07, .y_delay[3]   = 0x05, .y_delay[4]   = 0x20, .y_delay[5] =   0x20,

		},
		/* clk */
		{
			.clk_adc[0] = 0x05, .clk_adc[1] = 0x05, .clk_adc[2] = 0x05, .clk_adc[3] = 0x05, .clk_adc[4] = 0x05, .clk_adc[5] = 0x05,
			.clk_dec[0] = 0x44, .clk_dec[1] = 0x44, .clk_dec[2] = 0x44, .clk_dec[3] = 0x44, .clk_dec[4] = 0x44, .clk_dec[5] = 0x44,
		},
		/* timing_b */
		{
/*B9 0x96*/	.h_scaler1[0]  = 0x01, .h_scaler1[1]   = 0x01, .h_scaler1[2]   = 0x01, .h_scaler1[3]   = 0x01, .h_scaler1[4]   = 0x01, .h_scaler1[5]   = 0x01,
/*B9 0x97*/	.h_scaler2[0]  = 0x00, .h_scaler2[1]   = 0x00, .h_scaler2[2]   = 0x00, .h_scaler2[3]   = 0x00, .h_scaler2[4]   = 0x00, .h_scaler2[5]   = 0x00,
/*B9 0x98*/	.h_scaler3[0]  = 0x00, .h_scaler3[1]   = 0x00, .h_scaler3[2]   = 0x00, .h_scaler3[3]   = 0x00, .h_scaler3[4]   = 0x00, .h_scaler3[5]   = 0x00,
/*B9 0x99*/	.h_scaler4[0]  = 0x00, .h_scaler4[1]   = 0x00, .h_scaler4[2]   = 0x00, .h_scaler4[3]   = 0x00, .h_scaler4[4]   = 0x00, .h_scaler4[5]   = 0x00,
/*B9 0x9a*/	.h_scaler5[0]  = 0x00, .h_scaler5[1]   = 0x00, .h_scaler5[2]   = 0x00, .h_scaler5[3]   = 0x00, .h_scaler5[4]   = 0x00, .h_scaler5[5]   = 0x00,
/*B9 0x9b*/	.h_scaler6[0]  = 0x00, .h_scaler6[1]   = 0x00, .h_scaler6[2]   = 0x00, .h_scaler6[3]   = 0x00, .h_scaler6[4]   = 0x00, .h_scaler6[5]   = 0x00,
/*B9 0x9c*/	.h_scaler7[0]  = 0x00, .h_scaler7[1]   = 0x00, .h_scaler7[2]   = 0x00, .h_scaler7[3]   = 0x00, .h_scaler7[4]   = 0x00, .h_scaler7[5]   = 0x00,
/*B9 0x9d*/	.h_scaler8[0]  = 0x00, .h_scaler8[1]   = 0x00, .h_scaler8[2]   = 0x00, .h_scaler8[3]   = 0x00, .h_scaler8[4]   = 0x00, .h_scaler8[5]   = 0x00,
/*B9 0x9e*/	.h_scaler9[0]  = 0x00, .h_scaler9[1]   = 0x00, .h_scaler9[2]   = 0x00, .h_scaler9[3]   = 0x00, .h_scaler9[4]   = 0x00, .h_scaler9[5]   = 0x00,


/*B9 0x40*/	.pn_auto[0]    	= 0x00, .pn_auto[1]		= 0x00, .pn_auto[2]    	= 0x00, .pn_auto[3]    	= 0x00, .pn_auto[4]    	= 0x00, .pn_auto[5]    	= 0x00,

/*B5 0x90*/	.comb_mode[0]   = 0x05, .comb_mode[1]	= 0x05, .comb_mode[2]   = 0x05, .comb_mode[3]   = 0x05, .comb_mode[4]  	= 0x05, .comb_mode[5]   = 0x05,
/*B9 0xb9*/	.h_pll_op_a[0]     = 0x72, .h_pll_op_a[1]     = 0x72, .h_pll_op_a[2]     = 0x72, .h_pll_op_a[3]     = 0x72, .h_pll_op_a[4]     = 0x72, .h_pll_op_a[5]     = 0x72,
/*B9 0x57*/	.mem_path[0]	= 0x00, .mem_path[1]	= 0x00, .mem_path[2]	= 0x00, .mem_path[3]	= 0x10, .mem_path[4]	= 0x10, .mem_path[5]	= 0x10,
			.fsc_lock_speed[0] = 0xdc, .fsc_lock_speed[1] = 0xdc, .fsc_lock_speed[2] = 0xdc, .fsc_lock_speed[3] = 0xdc, .fsc_lock_speed[4] = 0xdc, .fsc_lock_speed[5] = 0xdc,

/*B0 0x81*/	.format_set1[0] = 0x02, .format_set1[1] = 0x02, .format_set1[2] = 0x02, .format_set1[3] = 0x02, .format_set1[4] = 0x02, .format_set1[5] = 0x02,
/*B0 0x85*/	.format_set2[0] = 0x01, .format_set2[1] = 0x01, .format_set2[2] = 0x01, .format_set2[3] = 0x01, .format_set2[4] = 0x01, .format_set2[5] = 0x01,

/*B0 0x64*/ .v_delay[0]     = 0x20, .v_delay[1]     = 0x20, .v_delay[2]     = 0x20, .v_delay[3]     = 0x20, .v_delay[4]     = 0x20, .v_delay[5]     = 0x20,
		},
	},

#else
	[ TVI_FHD_25P ] = /* o */
	{
		/* base */
		{
			.eq_bypass[0] 	= 0x22, .eq_bypass[1] 	= 0x22, .eq_bypass[2] 	= 0x22, .eq_bypass[3] 	= 0x22, .eq_bypass[4] 	= 0x22, .eq_bypass[5] 	= 0x22,    // Bank5 0x30
			.eq_band_sel[0] = 0x77, .eq_band_sel[1] = 0x77, .eq_band_sel[2] = 0x77, .eq_band_sel[3] = 0x67, .eq_band_sel[4] = 0x57, .eq_band_sel[5] = 0x37,    // BankA 0x31
			.eq_gain_sel[0] = 0x78, .eq_gain_sel[1] = 0x78, .eq_gain_sel[2] = 0x6f, .eq_gain_sel[3] = 0x7f, .eq_gain_sel[4] = 0x7f, .eq_gain_sel[5] = 0x7f,    // BankA 0x32
			.deq_a_on[0] 	= 0x00, .deq_a_on[1] 	= 0x01, .deq_a_on[2] 	= 0x01, .deq_a_on[3] 	= 0x01, .deq_a_on[4] 	= 0x01, .deq_a_on[5] 	= 0x01,    // BankA 0x33
			.deq_a_sel[0] 	= 0x00, .deq_a_sel[1] 	= 0x91, .deq_a_sel[2] 	= 0x93, .deq_a_sel[3] 	= 0x94, .deq_a_sel[4] 	= 0x95, .deq_a_sel[5] 	= 0x93,    // BankA 0x34
			.deq_b_sel[0] 	= 0x00, .deq_b_sel[1] 	= 0x00, .deq_b_sel[2] 	= 0x00, .deq_b_sel[3] 	= 0x00, .deq_b_sel[4] 	= 0x00, .deq_b_sel[5] 	= 0x00,    // BankA 0x35
		},
		/* coeff */
		{
			.deqA_01[0] = 0xAC, .deqA_01[1] = 0xAC, .deqA_01[2] = 0xAC, .deqA_01[3] = 0xAC, .deqA_01[4] = 0xAC, .deqA_01[5] = 0xAC,		// BankA 0x30
			.deqA_02[0] = 0x78, .deqA_02[1] = 0x78, .deqA_02[2] = 0x78, .deqA_02[3] = 0x78, .deqA_02[4] = 0x78, .deqA_02[5] = 0x78,		// BankA 0x31
			.deqA_03[0] = 0x17, .deqA_03[1] = 0x17, .deqA_03[2] = 0x17, .deqA_03[3] = 0x17, .deqA_03[4] = 0x17, .deqA_03[5] = 0x17,		// BankA 0x32
			.deqA_04[0] = 0xC1, .deqA_04[1] = 0xC1, .deqA_04[2] = 0xC1, .deqA_04[3] = 0xC1, .deqA_04[4] = 0xC1, .deqA_04[5] = 0xC1,     // BankA 0x33
			.deqA_05[0] = 0x40, .deqA_05[1] = 0x40, .deqA_05[2] = 0x40, .deqA_05[3] = 0x40, .deqA_05[4] = 0x40, .deqA_05[5] = 0x40,     // BankA 0x34
			.deqA_06[0] = 0x00, .deqA_06[1] = 0x00, .deqA_06[2] = 0x00, .deqA_06[3] = 0x00, .deqA_06[4] = 0x00, .deqA_06[5] = 0x00,     // BankA 0x35
			.deqA_07[0] = 0xC3, .deqA_07[1] = 0xC3, .deqA_07[2] = 0xC3, .deqA_07[3] = 0xC3, .deqA_07[4] = 0xC3, .deqA_07[5] = 0xC3,     // BankA 0x36
			.deqA_08[0] = 0x0A, .deqA_08[1] = 0x0A, .deqA_08[2] = 0x0A, .deqA_08[3] = 0x0A, .deqA_08[4] = 0x0A, .deqA_08[5] = 0x0A,     // BankA 0x37
			.deqA_09[0] = 0x00, .deqA_09[1] = 0x00, .deqA_09[2] = 0x00, .deqA_09[3] = 0x00, .deqA_09[4] = 0x00, .deqA_09[5] = 0x00,     // BankA 0x38
			.deqA_10[0] = 0x02, .deqA_10[1] = 0x02, .deqA_10[2] = 0x02, .deqA_10[3] = 0x02, .deqA_10[4] = 0x02, .deqA_10[5] = 0x02,     // BankA 0x39
			.deqA_11[0] = 0x00, .deqA_11[1] = 0x00, .deqA_11[2] = 0x00, .deqA_11[3] = 0x00, .deqA_11[4] = 0x00, .deqA_11[5] = 0x00,     // BankA 0x3a
			.deqA_12[0] = 0xB2, .deqA_12[1] = 0xB2, .deqA_12[2] = 0xB2, .deqA_12[3] = 0xB2, .deqA_12[4] = 0xB2, .deqA_12[5] = 0xB2,     // BankA 0x3b
		},
		/* color */
		{
			.contrast[0] 		= 0x82, .contrast[1] 		= 0x7c, .contrast[2] 		= 0x78, .contrast[3] 		= 0x6c, .contrast[4] 		= 0x70, .contrast[5] 		= 0x68,
			.h_peaking[0] 		= 0x3f, .h_peaking[1] 		= 0x3f, .h_peaking[2] 		= 0x3f, .h_peaking[3] 		= 0x3f, .h_peaking[4] 		= 0x3f, .h_peaking[5] 		= 0x3f,
			.c_filter[0]		= 0x82, .c_filter[1] 		= 0x82, .c_filter[2]	 	= 0x92, .c_filter[3] 		= 0xb2, .c_filter[4] 		= 0xb2, .c_filter[5] 		= 0xb2,

			.hue[0] 			= 0x00, .hue[1] 			= 0xfe, .hue[2] 			= 0xfe, .hue[3] 			= 0xfe, .hue[4] 			= 0xfe, .hue[5] 			= 0xfe,
			.u_gain[0] 			= 0xe0, .u_gain[1] 			= 0x00, .u_gain[2] 			= 0x00, .u_gain[3] 			= 0x00, .u_gain[4] 			= 0x00, .u_gain[5] 			= 0x00,
			.v_gain[0] 			= 0x00, .v_gain[1] 			= 0xf8, .v_gain[2] 			= 0xf8, .v_gain[3] 			= 0xf8, .v_gain[4] 			= 0xf8, .v_gain[5] 			= 0xf8,
			.u_offset[0] 		= 0xff, .u_offset[1] 		= 0xff, .u_offset[2] 		= 0xff, .u_offset[3] 		= 0xff, .u_offset[4] 		= 0xff, .u_offset[5] 		= 0xff,
			.v_offset[0] 		= 0x00, .v_offset[1] 		= 0x00, .v_offset[2] 		= 0x00, .v_offset[3] 		= 0x00, .v_offset[4] 		= 0x00, .v_offset[5] 		= 0x00,

			.black_level[0] 	= 0x86, .black_level[1] 	= 0x88, .black_level[2] 	= 0x88, .black_level[3] 	= 0x8c, .black_level[4] 	= 0x8f, .black_level[5] 	= 0x8f,
			.acc_ref[0]			= 0x57, .acc_ref[1]			= 0x57, .acc_ref[2]			= 0x57, .acc_ref[3]			= 0x57, .acc_ref[4]			= 0x57, .acc_ref[5]			= 0x27,
			.cti_delay[0]		= 0x80, .cti_delay[1]		= 0x80, .cti_delay[2]		= 0x80, .cti_delay[3]		= 0x80, .cti_delay[4]		= 0x80, .cti_delay[5]		= 0x80,
			.sub_saturation[0] 	= 0xdf, .sub_saturation[1] 	= 0xe0, .sub_saturation[2] 	= 0xe0, .sub_saturation[3] 	= 0xe0, .sub_saturation[4] 	= 0xa0, .sub_saturation[5] 	= 0x80,

			.burst_dec_a[0] 	= 0x2a, .burst_dec_a[1] 	= 0x2a, .burst_dec_a[2] 	= 0x2a, .burst_dec_a[3] 	= 0x2a, .burst_dec_a[4] 	= 0x2a, .burst_dec_a[5] 	= 0x2a,
			.burst_dec_b[0] 	= 0x00, .burst_dec_b[1] 	= 0x00, .burst_dec_b[2] 	= 0x00, .burst_dec_b[3] 	= 0x00, .burst_dec_b[4] 	= 0x00, .burst_dec_b[5] 	= 0x00,
			.burst_dec_c[0] 	= 0x30, .burst_dec_c[1] 	= 0x30, .burst_dec_c[2] 	= 0x30, .burst_dec_c[3] 	= 0x30, .burst_dec_c[4] 	= 0x30, .burst_dec_c[5] 	= 0x30,

			.c_option[0] 		= 0x80, .c_option[1] 		= 0x80, .c_option[2] 		= 0x80, .c_option[3] 		= 0xa0, .c_option[4] 		= 0xb0, .c_option[5] 		= 0xb0,

			.y_filter_b[0]		= 0x10, .y_filter_b[1]		= 0x10, .y_filter_b[2]		= 0x10, .y_filter_b[3]		= 0x10, .y_filter_b[4]		= 0x10, .y_filter_b[5]		= 0x10,
			.y_filter_b_sel[0]	= 0x1e,	.y_filter_b_sel[1]	= 0x1e,	.y_filter_b_sel[2]	= 0x1e, .y_filter_b_sel[3]	= 0x1e, .y_filter_b_sel[4]	= 0x1e, .y_filter_b_sel[5]	= 0x1e,
		},
		/* timing_a */
		{
			.h_delay_a[0] = 0x82, .h_delay_a[1] = 0x82, .h_delay_a[2] = 0x82, .h_delay_a[3] = 0x82, .h_delay_a[4] = 0x82, .h_delay_a[5] = 0x82,
			.h_delay_b[0] = 0x10, .h_delay_b[1] = 0x10, .h_delay_b[2] = 0x10, .h_delay_b[3] = 0x10, .h_delay_b[4] = 0x10, .h_delay_b[5] = 0x10,
			.h_delay_c[0] = 0x02, .h_delay_c[1] = 0x02, .h_delay_c[2] = 0x02, .h_delay_c[3] = 0x02, .h_delay_c[4] = 0x02, .h_delay_c[5] = 0x02,
			.y_delay[0]   = 0x05, .y_delay[1]   = 0x05, .y_delay[2]   = 0x05, .y_delay[3]   = 0x05, .y_delay[4]   = 0x20, .y_delay[5] =   0x20,

		},
		/* clk */
		{
			.clk_adc[0] = 0x05, .clk_adc[1] = 0x05, .clk_adc[2] = 0x05, .clk_adc[3] = 0x05, .clk_adc[4] = 0x05, .clk_adc[5] = 0x05,
			.clk_dec[0] = 0x44, .clk_dec[1] = 0x44, .clk_dec[2] = 0x44, .clk_dec[3] = 0x44, .clk_dec[4] = 0x44, .clk_dec[5] = 0x44,
		},
		/* timing_b */
		{
/*B9 0x96*/	.h_scaler1[0]  = 0x01, .h_scaler1[1]   = 0x01, .h_scaler1[2]   = 0x01, .h_scaler1[3]   = 0x01, .h_scaler1[4]   = 0x01, .h_scaler1[5]   = 0x01,
/*B9 0x97*/	.h_scaler2[0]  = 0x00, .h_scaler2[1]   = 0x00, .h_scaler2[2]   = 0x00, .h_scaler2[3]   = 0x00, .h_scaler2[4]   = 0x00, .h_scaler2[5]   = 0x00,
/*B9 0x98*/	.h_scaler3[0]  = 0x00, .h_scaler3[1]   = 0x00, .h_scaler3[2]   = 0x00, .h_scaler3[3]   = 0x00, .h_scaler3[4]   = 0x00, .h_scaler3[5]   = 0x00,
/*B9 0x99*/	.h_scaler4[0]  = 0x00, .h_scaler4[1]   = 0x00, .h_scaler4[2]   = 0x00, .h_scaler4[3]   = 0x00, .h_scaler4[4]   = 0x00, .h_scaler4[5]   = 0x00,
/*B9 0x9a*/	.h_scaler5[0]  = 0x00, .h_scaler5[1]   = 0x00, .h_scaler5[2]   = 0x00, .h_scaler5[3]   = 0x00, .h_scaler5[4]   = 0x00, .h_scaler5[5]   = 0x00,
/*B9 0x9b*/	.h_scaler6[0]  = 0x00, .h_scaler6[1]   = 0x00, .h_scaler6[2]   = 0x00, .h_scaler6[3]   = 0x00, .h_scaler6[4]   = 0x00, .h_scaler6[5]   = 0x00,
/*B9 0x9c*/	.h_scaler7[0]  = 0x00, .h_scaler7[1]   = 0x00, .h_scaler7[2]   = 0x00, .h_scaler7[3]   = 0x00, .h_scaler7[4]   = 0x00, .h_scaler7[5]   = 0x00,
/*B9 0x9d*/	.h_scaler8[0]  = 0x00, .h_scaler8[1]   = 0x00, .h_scaler8[2]   = 0x00, .h_scaler8[3]   = 0x00, .h_scaler8[4]   = 0x00, .h_scaler8[5]   = 0x00,
/*B9 0x9e*/	.h_scaler9[0]  = 0x00, .h_scaler9[1]   = 0x00, .h_scaler9[2]   = 0x00, .h_scaler9[3]   = 0x00, .h_scaler9[4]   = 0x00, .h_scaler9[5]   = 0x00,


/*B9 0x40*/	.pn_auto[0]    	= 0x00, .pn_auto[1]		= 0x00, .pn_auto[2]    	= 0x00, .pn_auto[3]    	= 0x00, .pn_auto[4]    	= 0x00, .pn_auto[5]    	= 0x00,

/*B5 0x90*/	.comb_mode[0]   = 0x05, .comb_mode[1]	= 0x05, .comb_mode[2]   = 0x05, .comb_mode[3]   = 0x05, .comb_mode[4]  	= 0x05, .comb_mode[5]   = 0x05,
/*B9 0xb9*/	.h_pll_op_a[0]  = 0x72, .h_pll_op_a[1]  = 0x72, .h_pll_op_a[2]  = 0x72, .h_pll_op_a[3]  = 0x72, .h_pll_op_a[4]  = 0x72, .h_pll_op_a[5]  = 0x72,
/*B9 0x57*/	.mem_path[0]	= 0x00, .mem_path[1]	= 0x00, .mem_path[2]	= 0x00, .mem_path[3]	= 0x10, .mem_path[4]	= 0x10, .mem_path[5]	= 0x10,
			.fsc_lock_speed[0] = 0xdc, .fsc_lock_speed[1] = 0xdc, .fsc_lock_speed[2] = 0xdc, .fsc_lock_speed[3] = 0xdc, .fsc_lock_speed[4] = 0xdc, .fsc_lock_speed[5] = 0xdc,

/*B0 0x81*/	.format_set1[0] = 0x03, .format_set1[1] = 0x03, .format_set1[2] = 0x03, .format_set1[3] = 0x03, .format_set1[4] = 0x03, .format_set1[5] = 0x03,
/*B0 0x85*/	.format_set2[0] = 0x01, .format_set2[1] = 0x01, .format_set2[2] = 0x01, .format_set2[3] = 0x01, .format_set2[4] = 0x01, .format_set2[5] = 0x01,

/*B0 0x64*/ .v_delay[0]     = 0x20, .v_delay[1]     = 0x20, .v_delay[2]     = 0x20, .v_delay[3]     = 0x20, .v_delay[4]     = 0x20, .v_delay[5]     = 0x20,
		},
	},
	[ TVI_FHD_30P ] =
	{
		/* base */
		{
			.eq_bypass[0] 	= 0x22, .eq_bypass[1] 	= 0x22, .eq_bypass[2] 	= 0x22, .eq_bypass[3] 	= 0x22, .eq_bypass[4] 	= 0x22, .eq_bypass[5] 	= 0x22,    // Bank5 0x30
			.eq_band_sel[0] = 0x77, .eq_band_sel[1] = 0x77, .eq_band_sel[2] = 0x77, .eq_band_sel[3] = 0x67, .eq_band_sel[4] = 0x57, .eq_band_sel[5] = 0x37,    // BankA 0x31
			.eq_gain_sel[0] = 0x78, .eq_gain_sel[1] = 0x78, .eq_gain_sel[2] = 0x6f, .eq_gain_sel[3] = 0x7f, .eq_gain_sel[4] = 0x7f, .eq_gain_sel[5] = 0x7f,    // BankA 0x32
			.deq_a_on[0] 	= 0x00, .deq_a_on[1] 	= 0x01, .deq_a_on[2] 	= 0x01, .deq_a_on[3] 	= 0x01, .deq_a_on[4] 	= 0x01, .deq_a_on[5] 	= 0x01,    // BankA 0x33
			.deq_a_sel[0] 	= 0x00, .deq_a_sel[1] 	= 0x91, .deq_a_sel[2] 	= 0x93, .deq_a_sel[3] 	= 0x94, .deq_a_sel[4] 	= 0x95, .deq_a_sel[5] 	= 0x93,    // BankA 0x34
			.deq_b_sel[0] 	= 0x00, .deq_b_sel[1] 	= 0x00, .deq_b_sel[2] 	= 0x00, .deq_b_sel[3] 	= 0x00, .deq_b_sel[4] 	= 0x00, .deq_b_sel[5] 	= 0x00,    // BankA 0x35
		},
		/* coeff */
		{
			.deqA_01[0] = 0xAC, .deqA_01[1] = 0xAC, .deqA_01[2] = 0xAC, .deqA_01[3] = 0xAC, .deqA_01[4] = 0xAC, .deqA_01[5] = 0xAC,		// BankA 0x30
			.deqA_02[0] = 0x78, .deqA_02[1] = 0x78, .deqA_02[2] = 0x78, .deqA_02[3] = 0x78, .deqA_02[4] = 0x78, .deqA_02[5] = 0x78,		// BankA 0x31
			.deqA_03[0] = 0x17, .deqA_03[1] = 0x17, .deqA_03[2] = 0x17, .deqA_03[3] = 0x17, .deqA_03[4] = 0x17, .deqA_03[5] = 0x17,		// BankA 0x32
			.deqA_04[0] = 0xC1, .deqA_04[1] = 0xC1, .deqA_04[2] = 0xC1, .deqA_04[3] = 0xC1, .deqA_04[4] = 0xC1, .deqA_04[5] = 0xC1,     // BankA 0x33
			.deqA_05[0] = 0x40, .deqA_05[1] = 0x40, .deqA_05[2] = 0x40, .deqA_05[3] = 0x40, .deqA_05[4] = 0x40, .deqA_05[5] = 0x40,     // BankA 0x34
			.deqA_06[0] = 0x00, .deqA_06[1] = 0x00, .deqA_06[2] = 0x00, .deqA_06[3] = 0x00, .deqA_06[4] = 0x00, .deqA_06[5] = 0x00,     // BankA 0x35
			.deqA_07[0] = 0xC3, .deqA_07[1] = 0xC3, .deqA_07[2] = 0xC3, .deqA_07[3] = 0xC3, .deqA_07[4] = 0xC3, .deqA_07[5] = 0xC3,     // BankA 0x36
			.deqA_08[0] = 0x0A, .deqA_08[1] = 0x0A, .deqA_08[2] = 0x0A, .deqA_08[3] = 0x0A, .deqA_08[4] = 0x0A, .deqA_08[5] = 0x0A,     // BankA 0x37
			.deqA_09[0] = 0x00, .deqA_09[1] = 0x00, .deqA_09[2] = 0x00, .deqA_09[3] = 0x00, .deqA_09[4] = 0x00, .deqA_09[5] = 0x00,     // BankA 0x38
			.deqA_10[0] = 0x02, .deqA_10[1] = 0x02, .deqA_10[2] = 0x02, .deqA_10[3] = 0x02, .deqA_10[4] = 0x02, .deqA_10[5] = 0x02,     // BankA 0x39
			.deqA_11[0] = 0x00, .deqA_11[1] = 0x00, .deqA_11[2] = 0x00, .deqA_11[3] = 0x00, .deqA_11[4] = 0x00, .deqA_11[5] = 0x00,     // BankA 0x3a
			.deqA_12[0] = 0xB2, .deqA_12[1] = 0xB2, .deqA_12[2] = 0xB2, .deqA_12[3] = 0xB2, .deqA_12[4] = 0xB2, .deqA_12[5] = 0xB2,     // BankA 0x3b
		},
		/* color */
		{
			.contrast[0] 		= 0x82, .contrast[1] 		= 0x7c, .contrast[2] 		= 0x78, .contrast[3] 		= 0x6c, .contrast[4] 		= 0x70, .contrast[5] 		= 0x68,
			.h_peaking[0] 		= 0x3f, .h_peaking[1] 		= 0x3f, .h_peaking[2] 		= 0x3f, .h_peaking[3] 		= 0x3f, .h_peaking[4] 		= 0x3f, .h_peaking[5] 		= 0x3f,
			.c_filter[0]		= 0x82, .c_filter[1] 		= 0x82, .c_filter[2]	 	= 0x92, .c_filter[3] 		= 0xb2, .c_filter[4] 		= 0xb2, .c_filter[5] 		= 0xb2,

			.hue[0] 			= 0x00, .hue[1] 			= 0xfe, .hue[2] 			= 0xfe, .hue[3] 			= 0xfe, .hue[4] 			= 0xfe, .hue[5] 			= 0xfe,
			.u_gain[0] 			= 0xe0, .u_gain[1] 			= 0x00, .u_gain[2] 			= 0x00, .u_gain[3] 			= 0x00, .u_gain[4] 			= 0x00, .u_gain[5] 			= 0x00,
			.v_gain[0] 			= 0x00, .v_gain[1] 			= 0xf8, .v_gain[2] 			= 0xf8, .v_gain[3] 			= 0xf8, .v_gain[4] 			= 0xf8, .v_gain[5] 			= 0xf8,
			.u_offset[0] 		= 0xff, .u_offset[1] 		= 0xff, .u_offset[2] 		= 0xff, .u_offset[3] 		= 0xff, .u_offset[4] 		= 0xff, .u_offset[5] 		= 0xff,
			.v_offset[0] 		= 0x00, .v_offset[1] 		= 0x00, .v_offset[2] 		= 0x00, .v_offset[3] 		= 0x00, .v_offset[4] 		= 0x00, .v_offset[5] 		= 0x00,

			.black_level[0] 	= 0x86, .black_level[1] 	= 0x88, .black_level[2] 	= 0x88, .black_level[3] 	= 0x8c, .black_level[4] 	= 0x8f, .black_level[5] 	= 0x8f,
			.acc_ref[0]			= 0x57, .acc_ref[1]			= 0x57, .acc_ref[2]			= 0x57, .acc_ref[3]			= 0x57, .acc_ref[4]			= 0x57, .acc_ref[5]			= 0x27,
			.cti_delay[0]		= 0x80, .cti_delay[1]		= 0x80, .cti_delay[2]		= 0x80, .cti_delay[3]		= 0x80, .cti_delay[4]		= 0x80, .cti_delay[5]		= 0x80,
			.sub_saturation[0] 	= 0xdf, .sub_saturation[1] 	= 0xe0, .sub_saturation[2] 	= 0xe0, .sub_saturation[3] 	= 0xe0, .sub_saturation[4] 	= 0xa0, .sub_saturation[5] 	= 0x80,

			.burst_dec_a[0] 	= 0x2a, .burst_dec_a[1] 	= 0x2a, .burst_dec_a[2] 	= 0x2a, .burst_dec_a[3] 	= 0x2a, .burst_dec_a[4] 	= 0x2a, .burst_dec_a[5] 	= 0x2a,
			.burst_dec_b[0] 	= 0x00, .burst_dec_b[1] 	= 0x00, .burst_dec_b[2] 	= 0x00, .burst_dec_b[3] 	= 0x00, .burst_dec_b[4] 	= 0x00, .burst_dec_b[5] 	= 0x00,
			.burst_dec_c[0] 	= 0x30, .burst_dec_c[1] 	= 0x30, .burst_dec_c[2] 	= 0x30, .burst_dec_c[3] 	= 0x30, .burst_dec_c[4] 	= 0x30, .burst_dec_c[5] 	= 0x30,

			.c_option[0] 		= 0x80, .c_option[1] 		= 0x80, .c_option[2] 		= 0x80, .c_option[3] 		= 0xa0, .c_option[4] 		= 0xb0, .c_option[5] 		= 0xb0,

			.y_filter_b[0]		= 0x10, .y_filter_b[1]		= 0x10, .y_filter_b[2]		= 0x10, .y_filter_b[3]		= 0x10, .y_filter_b[4]		= 0x10, .y_filter_b[5]		= 0x10,
			.y_filter_b_sel[0]	= 0x1e,	.y_filter_b_sel[1]	= 0x1e,	.y_filter_b_sel[2]	= 0x1e, .y_filter_b_sel[3]	= 0x1e, .y_filter_b_sel[4]	= 0x1e, .y_filter_b_sel[5]	= 0x1e,
		},
		/* timing_a */
		{
			.h_delay_a[0] = 0x80, .h_delay_a[1] = 0x80, .h_delay_a[2] = 0x80, .h_delay_a[3] = 0x80, .h_delay_a[4] = 0x80, .h_delay_a[5] = 0x80,
			.h_delay_b[0] = 0x10, .h_delay_b[1] = 0x10, .h_delay_b[2] = 0x10, .h_delay_b[3] = 0x10, .h_delay_b[4] = 0x10, .h_delay_b[5] = 0x10,
			.h_delay_c[0] = 0x03, .h_delay_c[1] = 0x03, .h_delay_c[2] = 0x03, .h_delay_c[3] = 0x02, .h_delay_c[4] = 0x03, .h_delay_c[5] = 0x03,
			.y_delay[0]   = 0x07, .y_delay[1]   = 0x07, .y_delay[2]   = 0x07, .y_delay[3]   = 0x05, .y_delay[4]   = 0x20, .y_delay[5] =   0x20,

		},
		/* clk */
		{
			.clk_adc[0] = 0x05, .clk_adc[1] = 0x05, .clk_adc[2] = 0x05, .clk_adc[3] = 0x05, .clk_adc[4] = 0x05, .clk_adc[5] = 0x05,
			.clk_dec[0] = 0x44, .clk_dec[1] = 0x44, .clk_dec[2] = 0x44, .clk_dec[3] = 0x44, .clk_dec[4] = 0x44, .clk_dec[5] = 0x44,
		},
		/* timing_b */
		{
/*B9 0x96*/	.h_scaler1[0]  = 0x01, .h_scaler1[1]   = 0x01, .h_scaler1[2]   = 0x01, .h_scaler1[3]   = 0x01, .h_scaler1[4]   = 0x01, .h_scaler1[5]   = 0x01,
/*B9 0x97*/	.h_scaler2[0]  = 0x00, .h_scaler2[1]   = 0x00, .h_scaler2[2]   = 0x00, .h_scaler2[3]   = 0x00, .h_scaler2[4]   = 0x00, .h_scaler2[5]   = 0x00,
/*B9 0x98*/	.h_scaler3[0]  = 0x00, .h_scaler3[1]   = 0x00, .h_scaler3[2]   = 0x00, .h_scaler3[3]   = 0x00, .h_scaler3[4]   = 0x00, .h_scaler3[5]   = 0x00,
/*B9 0x99*/	.h_scaler4[0]  = 0x00, .h_scaler4[1]   = 0x00, .h_scaler4[2]   = 0x00, .h_scaler4[3]   = 0x00, .h_scaler4[4]   = 0x00, .h_scaler4[5]   = 0x00,
/*B9 0x9a*/	.h_scaler5[0]  = 0x00, .h_scaler5[1]   = 0x00, .h_scaler5[2]   = 0x00, .h_scaler5[3]   = 0x00, .h_scaler5[4]   = 0x00, .h_scaler5[5]   = 0x00,
/*B9 0x9b*/	.h_scaler6[0]  = 0x00, .h_scaler6[1]   = 0x00, .h_scaler6[2]   = 0x00, .h_scaler6[3]   = 0x00, .h_scaler6[4]   = 0x00, .h_scaler6[5]   = 0x00,
/*B9 0x9c*/	.h_scaler7[0]  = 0x00, .h_scaler7[1]   = 0x00, .h_scaler7[2]   = 0x00, .h_scaler7[3]   = 0x00, .h_scaler7[4]   = 0x00, .h_scaler7[5]   = 0x00,
/*B9 0x9d*/	.h_scaler8[0]  = 0x00, .h_scaler8[1]   = 0x00, .h_scaler8[2]   = 0x00, .h_scaler8[3]   = 0x00, .h_scaler8[4]   = 0x00, .h_scaler8[5]   = 0x00,
/*B9 0x9e*/	.h_scaler9[0]  = 0x00, .h_scaler9[1]   = 0x00, .h_scaler9[2]   = 0x00, .h_scaler9[3]   = 0x00, .h_scaler9[4]   = 0x00, .h_scaler9[5]   = 0x00,


/*B9 0x40*/	.pn_auto[0]    	= 0x00, .pn_auto[1]		= 0x00, .pn_auto[2]    	= 0x00, .pn_auto[3]    	= 0x00, .pn_auto[4]    	= 0x00, .pn_auto[5]    	= 0x00,

/*B5 0x90*/	.comb_mode[0]   = 0x05, .comb_mode[1]	= 0x05, .comb_mode[2]   = 0x05, .comb_mode[3]   = 0x05, .comb_mode[4]  	= 0x05, .comb_mode[5]   = 0x05,
/*B9 0xb9*/	.h_pll_op_a[0]     = 0x72, .h_pll_op_a[1]     = 0x72, .h_pll_op_a[2]     = 0x72, .h_pll_op_a[3]     = 0x72, .h_pll_op_a[4]     = 0x72, .h_pll_op_a[5]     = 0x72,
/*B9 0x57*/	.mem_path[0]	= 0x00, .mem_path[1]	= 0x00, .mem_path[2]	= 0x00, .mem_path[3]	= 0x10, .mem_path[4]	= 0x10, .mem_path[5]	= 0x10,
			.fsc_lock_speed[0] = 0xdc, .fsc_lock_speed[1] = 0xdc, .fsc_lock_speed[2] = 0xdc, .fsc_lock_speed[3] = 0xdc, .fsc_lock_speed[4] = 0xdc, .fsc_lock_speed[5] = 0xdc,

/*B0 0x81*/	.format_set1[0] = 0x02, .format_set1[1] = 0x02, .format_set1[2] = 0x02, .format_set1[3] = 0x02, .format_set1[4] = 0x02, .format_set1[5] = 0x02,
/*B0 0x85*/	.format_set2[0] = 0x01, .format_set2[1] = 0x01, .format_set2[2] = 0x01, .format_set2[3] = 0x01, .format_set2[4] = 0x01, .format_set2[5] = 0x01,

/*B0 0x64*/ .v_delay[0]     = 0x20, .v_delay[1]     = 0x20, .v_delay[2]     = 0x20, .v_delay[3]     = 0x20, .v_delay[4]     = 0x20, .v_delay[5]     = 0x20,
		},
	},

#endif

	[ AHD20_720P_25P_EX_Btype ] = /* o */
	{
		/* base */
		{
			.eq_bypass[0] 	= 0x62, .eq_bypass[1] 	= 0x62, .eq_bypass[2] 	= 0x22, .eq_bypass[3] 	= 0x22, .eq_bypass[4] 	= 0x22, .eq_bypass[5] 	= 0x22, .eq_bypass[6] 	= 0x22, .eq_bypass[7] 	= 0x22, .eq_bypass[8] 	= 0x22, .eq_bypass[9] 	= 0x22, .eq_bypass[10] 	 = 0x22,  // Bank5 0x30
			.eq_band_sel[0] = 0x77, .eq_band_sel[1] = 0x77, .eq_band_sel[2] = 0x77, .eq_band_sel[3] = 0x77, .eq_band_sel[4] = 0x67, .eq_band_sel[5] = 0x57, .eq_band_sel[6] = 0x47, .eq_band_sel[7] = 0x47, .eq_band_sel[8] = 0x27, .eq_band_sel[9] = 0x17, .eq_band_sel[10] = 0x17, // BankA 0x31
			.eq_gain_sel[0] = 0x78, .eq_gain_sel[1] = 0x78, .eq_gain_sel[2] = 0x7a, .eq_gain_sel[3] = 0x7f, .eq_gain_sel[4] = 0x7f, .eq_gain_sel[5] = 0x7f, .eq_gain_sel[6] = 0x7f, .eq_gain_sel[7] = 0x7f, .eq_gain_sel[8] = 0x7f, .eq_gain_sel[9] = 0x7f, .eq_gain_sel[10] = 0x7f, // BankA 0x32
			.deq_a_on[0] 	= 0x00, .deq_a_on[1] 	= 0x01, .deq_a_on[2] 	= 0x01, .deq_a_on[3] 	= 0x01, .deq_a_on[4] 	= 0x01, .deq_a_on[5] 	= 0x01, .deq_a_on[6] 	= 0x01, .deq_a_on[7] 	= 0x01, .deq_a_on[8] 	= 0x01, .deq_a_on[9] 	= 0x01, .deq_a_on[10] 	 = 0x01, // BankA 0x33
			.deq_a_sel[0] 	= 0x00, .deq_a_sel[1] 	= 0x86, .deq_a_sel[2] 	= 0x87, .deq_a_sel[3] 	= 0x93, .deq_a_sel[4] 	= 0x8e, .deq_a_sel[5] 	= 0x8e, .deq_a_sel[6] 	= 0x93, .deq_a_sel[7] 	= 0x93, .deq_a_sel[8] 	= 0x93, .deq_a_sel[9] 	= 0x8d, .deq_a_sel[10] 	 = 0x8d, // BankA 0x34
			.deq_b_sel[0] 	= 0x00, .deq_b_sel[1] 	= 0x00, .deq_b_sel[2] 	= 0x00, .deq_b_sel[3] 	= 0x00, .deq_b_sel[4] 	= 0x00, .deq_b_sel[5] 	= 0x00, .deq_b_sel[6] 	= 0x00, .deq_b_sel[7] 	= 0x00, .deq_b_sel[8] 	= 0x00, .deq_b_sel[9] 	= 0x00, .deq_b_sel[10] 	 = 0x00, // BankA 0x35
		},
		/* coeff */
		{
			.deqA_01[0] = 0xAC, .deqA_01[1] = 0xAC, .deqA_01[2] = 0xAC, .deqA_01[3] = 0xAC, .deqA_01[4] = 0xAC, .deqA_01[5] = 0xAC,	.deqA_01[6] = 0xAC,  .deqA_01[7] = 0xAC, .deqA_01[8] = 0xAC, .deqA_01[9] = 0xAC, .deqA_01[10] = 0xAC,	// BankA 0x30
			.deqA_02[0] = 0x78, .deqA_02[1] = 0x78, .deqA_02[2] = 0x78, .deqA_02[3] = 0x78, .deqA_02[4] = 0x78, .deqA_02[5] = 0x78,	.deqA_02[6] = 0x78,	 .deqA_02[7] = 0x78, .deqA_02[8] = 0x78, .deqA_02[9] = 0x78, .deqA_02[10] = 0x78,	// BankA 0x31
			.deqA_03[0] = 0x17, .deqA_03[1] = 0x17, .deqA_03[2] = 0x17, .deqA_03[3] = 0x17, .deqA_03[4] = 0x17, .deqA_03[5] = 0x17,	.deqA_03[6] = 0x17,	 .deqA_03[7] = 0x17, .deqA_03[8] = 0x17, .deqA_03[9] = 0x17, .deqA_03[10] = 0x17,	// BankA 0x32
			.deqA_04[0] = 0xC1, .deqA_04[1] = 0xC1, .deqA_04[2] = 0xC1, .deqA_04[3] = 0xC1, .deqA_04[4] = 0xC1, .deqA_04[5] = 0xC1, .deqA_04[6] = 0xC1,  .deqA_04[7] = 0xC1, .deqA_04[8] = 0xC1, .deqA_04[9] = 0xC1, .deqA_04[10] = 0xC1,	// BankA 0x33
			.deqA_05[0] = 0x40, .deqA_05[1] = 0x40, .deqA_05[2] = 0x40, .deqA_05[3] = 0x40, .deqA_05[4] = 0x40, .deqA_05[5] = 0x40, .deqA_05[6] = 0x40,  .deqA_05[7] = 0x40, .deqA_05[8] = 0x40, .deqA_05[9] = 0x40, .deqA_05[10] = 0x40,	// BankA 0x34
			.deqA_06[0] = 0x00, .deqA_06[1] = 0x00, .deqA_06[2] = 0x00, .deqA_06[3] = 0x00, .deqA_06[4] = 0x00, .deqA_06[5] = 0x00, .deqA_06[6] = 0x00,  .deqA_06[7] = 0x00, .deqA_06[8] = 0x00, .deqA_06[9] = 0x00, .deqA_06[10] = 0x00,	// BankA 0x35
			.deqA_07[0] = 0xC3, .deqA_07[1] = 0xC3, .deqA_07[2] = 0xC3, .deqA_07[3] = 0xC3, .deqA_07[4] = 0xC3, .deqA_07[5] = 0xC3, .deqA_07[6] = 0xC3,  .deqA_07[7] = 0xC3, .deqA_07[8] = 0xC3, .deqA_07[9] = 0xC3, .deqA_07[10] = 0xC3,	// BankA 0x36
			.deqA_08[0] = 0x0A, .deqA_08[1] = 0x0A, .deqA_08[2] = 0x0A, .deqA_08[3] = 0x0A, .deqA_08[4] = 0x0A, .deqA_08[5] = 0x0A, .deqA_08[6] = 0x0A,  .deqA_08[7] = 0x0A, .deqA_08[8] = 0x0A, .deqA_08[9] = 0x0A, .deqA_08[10] = 0x0A,	// BankA 0x37
			.deqA_09[0] = 0x00, .deqA_09[1] = 0x00, .deqA_09[2] = 0x00, .deqA_09[3] = 0x00, .deqA_09[4] = 0x00, .deqA_09[5] = 0x00, .deqA_09[6] = 0x00,  .deqA_09[7] = 0x00, .deqA_09[8] = 0x00, .deqA_09[9] = 0x00, .deqA_09[10] = 0x00,	// BankA 0x38
			.deqA_10[0] = 0x02, .deqA_10[1] = 0x02, .deqA_10[2] = 0x02, .deqA_10[3] = 0x02, .deqA_10[4] = 0x02, .deqA_10[5] = 0x02, .deqA_10[6] = 0x02,  .deqA_10[7] = 0x02, .deqA_10[8] = 0x02, .deqA_10[9] = 0x02, .deqA_10[10] = 0x02,	// BankA 0x39
			.deqA_11[0] = 0x00, .deqA_11[1] = 0x00, .deqA_11[2] = 0x00, .deqA_11[3] = 0x00, .deqA_11[4] = 0x00, .deqA_11[5] = 0x00, .deqA_11[6] = 0x00,  .deqA_11[7] = 0x00, .deqA_11[8] = 0x00, .deqA_11[9] = 0x00, .deqA_11[10] = 0x00,	// BankA 0x3a
			.deqA_12[0] = 0xB2, .deqA_12[1] = 0xB2, .deqA_12[2] = 0xB2, .deqA_12[3] = 0xB2, .deqA_12[4] = 0xB2, .deqA_12[5] = 0xB2, .deqA_12[6] = 0xB2,  .deqA_12[7] = 0xB2, .deqA_12[8] = 0xB2, .deqA_12[9] = 0xB2, .deqA_12[10] = 0xB2,	// BankA 0x3b
		},
		/* color */
		{
			.contrast[0] 		= 0x88, .contrast[1] 		= 0x88, .contrast[2] 		= 0x78, .contrast[3] 		= 0x88, .contrast[4] 		= 0x88, .contrast[5] 		= 0x7e, .contrast[6] 		= 0x78, .contrast[7] 		= 0x78, .contrast[8] 		= 0x74, .contrast[9] 		= 0x74, .contrast[10] 		= 0x74,
			.h_peaking[0] 		= 0x3f, .h_peaking[1] 		= 0x3f, .h_peaking[2] 		= 0x3f, .h_peaking[3] 		= 0x3f, .h_peaking[4] 		= 0x3f, .h_peaking[5] 		= 0x3f, .h_peaking[6] 		= 0x3f, .h_peaking[7] 		= 0x3f, .h_peaking[8] 		= 0x3f, .h_peaking[9] 		= 0x4f, .h_peaking[10] 		= 0x4f,
			.c_filter[0]		= 0x82, .c_filter[1] 		= 0x82, .c_filter[2]	 	= 0x82, .c_filter[3] 		= 0x82, .c_filter[4] 		= 0x92, .c_filter[5] 		= 0x92, .c_filter[6] 		= 0x92, .c_filter[7] 		= 0x92, .c_filter[8] 		= 0x92, .c_filter[9] 		= 0x92, .c_filter[10] 		= 0x92,

			.hue[0] 			= 0x00, .hue[1] 			= 0x00, .hue[2] 			= 0x00, .hue[3] 			= 0x00, .hue[4] 			= 0x00, .hue[5] 			= 0x00, .hue[6] 			= 0x00, .hue[7] 			= 0x00, .hue[8] 			= 0x00, .hue[9] 			= 0x00, .hue[10] 			= 0x00,
			.u_gain[0] 			= 0x00, .u_gain[1] 			= 0x00, .u_gain[2] 			= 0x00, .u_gain[3] 			= 0x00, .u_gain[4] 			= 0x00, .u_gain[5] 			= 0x00, .u_gain[6] 			= 0x00, .u_gain[7] 			= 0x00, .u_gain[8] 			= 0x00, .u_gain[9] 			= 0x00, .u_gain[10] 		= 0x00,
			.v_gain[0] 			= 0x00, .v_gain[1] 			= 0x00, .v_gain[2] 			= 0x00, .v_gain[3] 			= 0x00, .v_gain[4] 			= 0x00, .v_gain[5] 			= 0x00, .v_gain[6] 			= 0x00, .v_gain[7] 			= 0x00, .v_gain[8] 			= 0x00, .v_gain[9] 			= 0x00, .v_gain[10] 		= 0x00,
			.u_offset[0] 		= 0x00, .u_offset[1] 		= 0x00, .u_offset[2] 		= 0x00, .u_offset[3] 		= 0x00, .u_offset[4] 		= 0x00, .u_offset[5] 		= 0x00, .u_offset[6] 		= 0x00, .u_offset[7] 		= 0x00, .u_offset[8] 		= 0x00, .u_offset[9] 		= 0x00, .u_offset[10] 		= 0x00,
			.v_offset[0] 		= 0x00, .v_offset[1] 		= 0x00, .v_offset[2] 		= 0x00, .v_offset[3] 		= 0x00, .v_offset[4] 		= 0x00, .v_offset[5] 		= 0x00, .v_offset[6] 		= 0x00, .v_offset[7] 		= 0x00, .v_offset[8] 		= 0x00, .v_offset[9] 		= 0x00, .v_offset[10] 		= 0x00,

			.black_level[0] 	= 0x84, .black_level[1] 	= 0x84, .black_level[2] 	= 0x84, .black_level[3] 	= 0x84, .black_level[4] 	= 0x84, .black_level[5] 	= 0x86, .black_level[6] 	= 0x86, .black_level[7] 	= 0x8c, .black_level[8] 	= 0x8c, .black_level[9] 	= 0x90, .black_level[10] 	= 0x90,
			.acc_ref[0]			= 0x57, .acc_ref[1]			= 0x57, .acc_ref[2]			= 0x57, .acc_ref[3]			= 0x57, .acc_ref[4]			= 0x57, .acc_ref[5]			= 0x57, .acc_ref[6]			= 0x57, .acc_ref[7]			= 0x57, .acc_ref[8]			= 0x57, .acc_ref[9]			= 0x47, .acc_ref[10]		= 0x47,
			.cti_delay[0]		= 0x80, .cti_delay[1]		= 0x80, .cti_delay[2]		= 0x80, .cti_delay[3]		= 0x80, .cti_delay[4]		= 0x80, .cti_delay[5]		= 0x80, .cti_delay[6]		= 0x80, .cti_delay[7]		= 0x80, .cti_delay[8]		= 0x80, .cti_delay[9]		= 0x90, .cti_delay[10]		= 0x90,
			.sub_saturation[0] 	= 0xa8, .sub_saturation[1] 	= 0xab, .sub_saturation[2] 	= 0xb0, .sub_saturation[3] 	= 0xb0, .sub_saturation[4] 	= 0xa4, .sub_saturation[5] 	= 0xa0, .sub_saturation[6] 	= 0xa0, .sub_saturation[7] 	= 0xa0, .sub_saturation[8] 	= 0xa0, .sub_saturation[9] 	= 0x90, .sub_saturation[10] = 0x90,

			.burst_dec_a[0] 	= 0x2a, .burst_dec_a[1] 	= 0x2a, .burst_dec_a[2] 	= 0x2a, .burst_dec_a[3] 	= 0x2a, .burst_dec_a[4] 	= 0x2a, .burst_dec_a[5] 	= 0x2a, .burst_dec_a[6] 	= 0x2a, .burst_dec_a[7] 	= 0x2a, .burst_dec_a[8] 	= 0x2a, .burst_dec_a[9] 	= 0x2a, .burst_dec_a[10] 	= 0x2a,
			.burst_dec_b[0] 	= 0x00, .burst_dec_b[1] 	= 0x00, .burst_dec_b[2] 	= 0x00, .burst_dec_b[3] 	= 0x00, .burst_dec_b[4] 	= 0x00, .burst_dec_b[5] 	= 0x00, .burst_dec_b[6] 	= 0x00, .burst_dec_b[7] 	= 0x00, .burst_dec_b[8] 	= 0x00, .burst_dec_b[9] 	= 0x00, .burst_dec_b[10] 	= 0x00,
			.burst_dec_c[0] 	= 0x30, .burst_dec_c[1] 	= 0x30, .burst_dec_c[2] 	= 0x30, .burst_dec_c[3] 	= 0x30, .burst_dec_c[4] 	= 0x30, .burst_dec_c[5] 	= 0x30, .burst_dec_c[6] 	= 0x30, .burst_dec_c[7] 	= 0x30, .burst_dec_c[8] 	= 0x30, .burst_dec_c[9] 	= 0x30, .burst_dec_c[10] 	= 0x30,

			.c_option[0] 		= 0x80, .c_option[1] 		= 0x80, .c_option[2] 		= 0x80, .c_option[3] 		= 0x80, .c_option[4] 		= 0x90, .c_option[5] 		= 0x90, .c_option[6] 		= 0x90, .c_option[7] 		= 0x90, .c_option[8] 		= 0x90, .c_option[9] 		= 0x90, .c_option[10] 		= 0x90,

			.y_filter_b[0]		= 0x10, .y_filter_b[1]		= 0x10, .y_filter_b[2]		= 0x10, .y_filter_b[3]		= 0x10, .y_filter_b[4]		= 0x10, .y_filter_b[5]		= 0x10, .y_filter_b[6]		= 0x10, .y_filter_b[7]		= 0x10, .y_filter_b[8]		= 0x10, .y_filter_b[9]		= 0x10, .y_filter_b[10]		= 0x10,
			.y_filter_b_sel[0]	= 0x1e,	.y_filter_b_sel[1]	= 0x1e,	.y_filter_b_sel[2]	= 0x1e, .y_filter_b_sel[3]	= 0x1e, .y_filter_b_sel[4]	= 0x1e, .y_filter_b_sel[5]	= 0x1e, .y_filter_b_sel[6]	= 0x1e, .y_filter_b_sel[7]	= 0x1e, .y_filter_b_sel[8]	= 0x1e, .y_filter_b_sel[9]	= 0x1e, .y_filter_b_sel[10]	= 0x1e,
		},
		/* timing_a */
		{
#ifdef SUPPORT_720P_HDELAY_CONTROL_171226
			.h_delay_a[0] = 0x8d, .h_delay_a[1] = 0x8d, .h_delay_a[2] = 0x8d, .h_delay_a[3] = 0x8d, .h_delay_a[4] = 0x8d, .h_delay_a[5] = 0x8d, .h_delay_a[6] = 0x8d, .h_delay_a[7] = 0x8d, .h_delay_a[8] = 0x8d, .h_delay_a[9] = 0x8d, .h_delay_a[10] = 0x8d,
#else
			.h_delay_a[0] = 0xA0, .h_delay_a[1] = 0xa0, .h_delay_a[2] = 0x9e, .h_delay_a[3] = 0x9b, .h_delay_a[4] = 0x99, .h_delay_a[5] = 0x99, .h_delay_a[6] = 0x9b, .h_delay_a[7] = 0x98, .h_delay_a[8] = 0x98, .h_delay_a[9] = 0x98, .h_delay_a[10] = 0x98,
#endif
			.h_delay_b[0] = 0x00, .h_delay_b[1] = 0x00, .h_delay_b[2] = 0x00, .h_delay_b[3] = 0x00, .h_delay_b[4] = 0x00, .h_delay_b[5] = 0x00, .h_delay_b[6] = 0x00, .h_delay_b[7] = 0x00, .h_delay_b[8] = 0x00, .h_delay_b[9] = 0x00, .h_delay_b[10] = 0x00,
			.h_delay_c[0] = 0x00, .h_delay_c[1] = 0x00, .h_delay_c[2] = 0x00, .h_delay_c[3] = 0x00, .h_delay_c[4] = 0x00, .h_delay_c[5] = 0x00, .h_delay_c[6] = 0x00, .h_delay_c[7] = 0x00, .h_delay_c[8] = 0x00, .h_delay_c[9] = 0x00, .h_delay_c[10] = 0x00,
			.y_delay[0]   = 0x05, .y_delay[1]   = 0x05, .y_delay[2]   = 0x05, .y_delay[3]   = 0x05, .y_delay[4]   = 0x05, .y_delay[5] =   0x05, .y_delay[6] =   0x05, .y_delay[7] =   0x05, .y_delay[8] =   0x05, .y_delay[9] =   0x05, .y_delay[10] =   0x05,

		},
		/* clk */
		{
			.clk_adc[0] = 0x02, .clk_adc[1] = 0x02, .clk_adc[2] = 0x02, .clk_adc[3] = 0x02, .clk_adc[4] = 0x02, .clk_adc[5] = 0x02, .clk_adc[6] = 0x02, .clk_adc[7] = 0x02, .clk_adc[8] = 0x02, .clk_adc[9] = 0x02, .clk_adc[10] = 0x02,
			.clk_dec[0] = 0x40, .clk_dec[1] = 0x40, .clk_dec[2] = 0x40, .clk_dec[3] = 0x40, .clk_dec[4] = 0x40, .clk_dec[5] = 0x40, .clk_dec[6] = 0x40, .clk_dec[7] = 0x40, .clk_dec[8] = 0x40, .clk_dec[9] = 0x40, .clk_dec[10] = 0x40,
		},
		/* timing_b */
		{
/*B9 0x96*/	.h_scaler1[0]  = 0x00, .h_scaler1[1]   = 0x00, .h_scaler1[2]   = 0x00, .h_scaler1[3]   = 0x00, .h_scaler1[4]   = 0x00, .h_scaler1[5]   = 0x00, .h_scaler1[6]   = 0x00, .h_scaler1[7]   = 0x00, .h_scaler1[8]   = 0x00, .h_scaler1[9]   = 0x00, .h_scaler1[10]   = 0x00,
/*B9 0x97*/	.h_scaler2[0]  = 0x00, .h_scaler2[1]   = 0x00, .h_scaler2[2]   = 0x00, .h_scaler2[3]   = 0x00, .h_scaler2[4]   = 0x00, .h_scaler2[5]   = 0x00, .h_scaler2[6]   = 0x00, .h_scaler2[7]   = 0x00, .h_scaler2[8]   = 0x00, .h_scaler2[9]   = 0x00, .h_scaler2[10]   = 0x00,
/*B9 0x98*/	.h_scaler3[0]  = 0x00, .h_scaler3[1]   = 0x00, .h_scaler3[2]   = 0x00, .h_scaler3[3]   = 0x00, .h_scaler3[4]   = 0x00, .h_scaler3[5]   = 0x00, .h_scaler3[6]   = 0x00, .h_scaler3[7]   = 0x00, .h_scaler3[8]   = 0x00, .h_scaler3[9]   = 0x00, .h_scaler3[10]   = 0x00,
/*B9 0x99*/	.h_scaler4[0]  = 0x00, .h_scaler4[1]   = 0x00, .h_scaler4[2]   = 0x00, .h_scaler4[3]   = 0x00, .h_scaler4[4]   = 0x00, .h_scaler4[5]   = 0x00, .h_scaler4[6]   = 0x00, .h_scaler4[7]   = 0x00, .h_scaler4[8]   = 0x00, .h_scaler4[9]   = 0x00, .h_scaler4[10]   = 0x00,
/*B9 0x9a*/	.h_scaler5[0]  = 0x00, .h_scaler5[1]   = 0x00, .h_scaler5[2]   = 0x00, .h_scaler5[3]   = 0x00, .h_scaler5[4]   = 0x00, .h_scaler5[5]   = 0x00, .h_scaler5[6]   = 0x00, .h_scaler5[7]   = 0x00, .h_scaler5[8]   = 0x00, .h_scaler5[9]   = 0x00, .h_scaler5[10]   = 0x00,
/*B9 0x9b*/	.h_scaler6[0]  = 0x00, .h_scaler6[1]   = 0x00, .h_scaler6[2]   = 0x00, .h_scaler6[3]   = 0x00, .h_scaler6[4]   = 0x00, .h_scaler6[5]   = 0x00, .h_scaler6[6]   = 0x00, .h_scaler6[7]   = 0x00, .h_scaler6[8]   = 0x00, .h_scaler6[9]   = 0x00, .h_scaler6[10]   = 0x00,
/*B9 0x9c*/	.h_scaler7[0]  = 0x00, .h_scaler7[1]   = 0x00, .h_scaler7[2]   = 0x00, .h_scaler7[3]   = 0x00, .h_scaler7[4]   = 0x00, .h_scaler7[5]   = 0x00, .h_scaler7[6]   = 0x00, .h_scaler7[7]   = 0x00, .h_scaler7[8]   = 0x00, .h_scaler7[9]   = 0x00, .h_scaler7[10]   = 0x00,
/*B9 0x9d*/	.h_scaler8[0]  = 0x00, .h_scaler8[1]   = 0x00, .h_scaler8[2]   = 0x00, .h_scaler8[3]   = 0x00, .h_scaler8[4]   = 0x00, .h_scaler8[5]   = 0x00, .h_scaler8[6]   = 0x00, .h_scaler8[7]   = 0x00, .h_scaler8[8]   = 0x00, .h_scaler8[9]   = 0x00, .h_scaler8[10]   = 0x00,
/*B9 0x9e*/	.h_scaler9[0]  = 0x00, .h_scaler9[1]   = 0x00, .h_scaler9[2]   = 0x00, .h_scaler9[3]   = 0x00, .h_scaler9[4]   = 0x00, .h_scaler9[5]   = 0x00, .h_scaler9[6]   = 0x00, .h_scaler9[7]   = 0x00, .h_scaler9[8]   = 0x00, .h_scaler9[9]   = 0x00, .h_scaler9[10]   = 0x00,


/*B9 0x40*/	.pn_auto[0]    	= 0x00, .pn_auto[1]		= 0x00, .pn_auto[2]    	= 0x00, .pn_auto[3]    	= 0x00, .pn_auto[4]    	= 0x00, .pn_auto[5]    	= 0x00, .pn_auto[6]		= 0x00, .pn_auto[7]    	= 0x00, .pn_auto[8]    	= 0x00, .pn_auto[9]    	= 0x00, .pn_auto[10]    	= 0x00,

/*B5 0x90*/	.comb_mode[0]   = 0x01, .comb_mode[1]	= 0x01, .comb_mode[2]   = 0x01, .comb_mode[3]   = 0x01, .comb_mode[4]  	= 0x01, .comb_mode[5]   = 0x01, .comb_mode[6]	= 0x01, .comb_mode[7]   = 0x01, .comb_mode[8]   = 0x01, .comb_mode[9]  	= 0x01, .comb_mode[10]   = 0x01,
/*B9 0xb9*/	.h_pll_op_a[0]  = 0x72, .h_pll_op_a[1]  = 0x72, .h_pll_op_a[2]  = 0x72, .h_pll_op_a[3]  = 0x72, .h_pll_op_a[4]  = 0x72, .h_pll_op_a[5]  = 0x72, .h_pll_op_a[6]  = 0x72, .h_pll_op_a[7]  = 0x72, .h_pll_op_a[8]  = 0x72, .h_pll_op_a[9]  = 0x72, .h_pll_op_a[10]  = 0x72,
/*B9 0x57*/	.mem_path[0]	= 0x00, .mem_path[1]	= 0x00, .mem_path[2]	= 0x00, .mem_path[3]	= 0x00, .mem_path[4]	= 0x00, .mem_path[5]	= 0x00, .mem_path[6]	= 0x00, .mem_path[7]	= 0x00, .mem_path[8]	= 0x00, .mem_path[9]	= 0x00, .mem_path[10]	= 0x00,
			.fsc_lock_speed[0] = 0xdc, .fsc_lock_speed[1] = 0xdc, .fsc_lock_speed[2] = 0xdc, .fsc_lock_speed[3] = 0xdc, .fsc_lock_speed[4] = 0xdc, .fsc_lock_speed[5] = 0xdc, .fsc_lock_speed[6] = 0xdc, .fsc_lock_speed[7] = 0xdc, .fsc_lock_speed[8] = 0xdc, .fsc_lock_speed[9] = 0xdc, .fsc_lock_speed[10] = 0xdc,

/*B0 0x81*/	.format_set1[0] = 0x0d, .format_set1[1] = 0x0d, .format_set1[2] = 0x0d, .format_set1[3] = 0x0d, .format_set1[4] = 0x0d, .format_set1[5] = 0x0d, .format_set1[6] = 0x0d, .format_set1[7] = 0x0d, .format_set1[8] = 0x0d, .format_set1[9] = 0x0d, .format_set1[10] = 0x0d,
/*B0 0x85*/	.format_set2[0] = 0x00, .format_set2[1] = 0x00, .format_set2[2] = 0x00, .format_set2[3] = 0x00, .format_set2[4] = 0x00, .format_set2[5] = 0x00, .format_set2[6] = 0x00, .format_set2[7] = 0x00, .format_set2[8] = 0x00, .format_set2[9] = 0x00, .format_set2[10] = 0x00,

/*B0 0x64*/ .v_delay[0]     = 0x21, .v_delay[1]     = 0x21, .v_delay[2]     = 0x21, .v_delay[3]     = 0x21, .v_delay[4]     = 0x21, .v_delay[5]     = 0x21, .v_delay[6]     = 0x21, .v_delay[7]     = 0x21, .v_delay[8]     = 0x21, .v_delay[9]     = 0x21, .v_delay[10]     = 0x21,
		},
	},
	[ AHD20_720P_30P_EX_Btype ] = /* o */
	{
		/* base */
		{
			.eq_bypass[0] 	= 0x62, .eq_bypass[1] 	= 0x62, .eq_bypass[2] 	= 0x22, .eq_bypass[3] 	= 0x22, .eq_bypass[4] 	= 0x22, .eq_bypass[5] 	= 0x22, .eq_bypass[6] 	= 0x22, .eq_bypass[7] 	= 0x22, .eq_bypass[8] 	= 0x22, .eq_bypass[9] 	= 0x22, .eq_bypass[10] 	 = 0x22,  // Bank5 0x30
			.eq_band_sel[0] = 0x77, .eq_band_sel[1] = 0x77, .eq_band_sel[2] = 0x77, .eq_band_sel[3] = 0x77, .eq_band_sel[4] = 0x67, .eq_band_sel[5] = 0x57, .eq_band_sel[6] = 0x47, .eq_band_sel[7] = 0x47, .eq_band_sel[8] = 0x27, .eq_band_sel[9] = 0x17, .eq_band_sel[10] = 0x17, // BankA 0x31
			.eq_gain_sel[0] = 0x78, .eq_gain_sel[1] = 0x78, .eq_gain_sel[2] = 0x7a, .eq_gain_sel[3] = 0x7f, .eq_gain_sel[4] = 0x7f, .eq_gain_sel[5] = 0x7f, .eq_gain_sel[6] = 0x7f, .eq_gain_sel[7] = 0x7f, .eq_gain_sel[8] = 0x7f, .eq_gain_sel[9] = 0x7f, .eq_gain_sel[10] = 0x7f, // BankA 0x32
			.deq_a_on[0] 	= 0x00, .deq_a_on[1] 	= 0x01, .deq_a_on[2] 	= 0x01, .deq_a_on[3] 	= 0x01, .deq_a_on[4] 	= 0x01, .deq_a_on[5] 	= 0x01, .deq_a_on[6] 	= 0x01, .deq_a_on[7] 	= 0x01, .deq_a_on[8] 	= 0x01, .deq_a_on[9] 	= 0x01, .deq_a_on[10] 	 = 0x01, // BankA 0x33
			.deq_a_sel[0] 	= 0x00, .deq_a_sel[1] 	= 0x86, .deq_a_sel[2] 	= 0x87, .deq_a_sel[3] 	= 0x93, .deq_a_sel[4] 	= 0x8e, .deq_a_sel[5] 	= 0x8e, .deq_a_sel[6] 	= 0x93, .deq_a_sel[7] 	= 0x93, .deq_a_sel[8] 	= 0x93, .deq_a_sel[9] 	= 0x8d, .deq_a_sel[10] 	 = 0x8d, // BankA 0x34
			.deq_b_sel[0] 	= 0x00, .deq_b_sel[1] 	= 0x00, .deq_b_sel[2] 	= 0x00, .deq_b_sel[3] 	= 0x00, .deq_b_sel[4] 	= 0x00, .deq_b_sel[5] 	= 0x00, .deq_b_sel[6] 	= 0x00, .deq_b_sel[7] 	= 0x00, .deq_b_sel[8] 	= 0x00, .deq_b_sel[9] 	= 0x00, .deq_b_sel[10] 	 = 0x00, // BankA 0x35
		},
		/* coeff */
		{
			.deqA_01[0] = 0xAC, .deqA_01[1] = 0xAC, .deqA_01[2] = 0xAC, .deqA_01[3] = 0xAC, .deqA_01[4] = 0xAC, .deqA_01[5] = 0xAC,	.deqA_01[6] = 0xAC,  .deqA_01[7] = 0xAC, .deqA_01[8] = 0xAC, .deqA_01[9] = 0xAC, .deqA_01[10] = 0xAC,	// BankA 0x30
			.deqA_02[0] = 0x78, .deqA_02[1] = 0x78, .deqA_02[2] = 0x78, .deqA_02[3] = 0x78, .deqA_02[4] = 0x78, .deqA_02[5] = 0x78,	.deqA_02[6] = 0x78,	 .deqA_02[7] = 0x78, .deqA_02[8] = 0x78, .deqA_02[9] = 0x78, .deqA_02[10] = 0x78,	// BankA 0x31
			.deqA_03[0] = 0x17, .deqA_03[1] = 0x17, .deqA_03[2] = 0x17, .deqA_03[3] = 0x17, .deqA_03[4] = 0x17, .deqA_03[5] = 0x17,	.deqA_03[6] = 0x17,	 .deqA_03[7] = 0x17, .deqA_03[8] = 0x17, .deqA_03[9] = 0x17, .deqA_03[10] = 0x17,	// BankA 0x32
			.deqA_04[0] = 0xC1, .deqA_04[1] = 0xC1, .deqA_04[2] = 0xC1, .deqA_04[3] = 0xC1, .deqA_04[4] = 0xC1, .deqA_04[5] = 0xC1, .deqA_04[6] = 0xC1,  .deqA_04[7] = 0xC1, .deqA_04[8] = 0xC1, .deqA_04[9] = 0xC1, .deqA_04[10] = 0xC1,	// BankA 0x33
			.deqA_05[0] = 0x40, .deqA_05[1] = 0x40, .deqA_05[2] = 0x40, .deqA_05[3] = 0x40, .deqA_05[4] = 0x40, .deqA_05[5] = 0x40, .deqA_05[6] = 0x40,  .deqA_05[7] = 0x40, .deqA_05[8] = 0x40, .deqA_05[9] = 0x40, .deqA_05[10] = 0x40,	// BankA 0x34
			.deqA_06[0] = 0x00, .deqA_06[1] = 0x00, .deqA_06[2] = 0x00, .deqA_06[3] = 0x00, .deqA_06[4] = 0x00, .deqA_06[5] = 0x00, .deqA_06[6] = 0x00,  .deqA_06[7] = 0x00, .deqA_06[8] = 0x00, .deqA_06[9] = 0x00, .deqA_06[10] = 0x00,	// BankA 0x35
			.deqA_07[0] = 0xC3, .deqA_07[1] = 0xC3, .deqA_07[2] = 0xC3, .deqA_07[3] = 0xC3, .deqA_07[4] = 0xC3, .deqA_07[5] = 0xC3, .deqA_07[6] = 0xC3,  .deqA_07[7] = 0xC3, .deqA_07[8] = 0xC3, .deqA_07[9] = 0xC3, .deqA_07[10] = 0xC3,	// BankA 0x36
			.deqA_08[0] = 0x0A, .deqA_08[1] = 0x0A, .deqA_08[2] = 0x0A, .deqA_08[3] = 0x0A, .deqA_08[4] = 0x0A, .deqA_08[5] = 0x0A, .deqA_08[6] = 0x0A,  .deqA_08[7] = 0x0A, .deqA_08[8] = 0x0A, .deqA_08[9] = 0x0A, .deqA_08[10] = 0x0A,	// BankA 0x37
			.deqA_09[0] = 0x00, .deqA_09[1] = 0x00, .deqA_09[2] = 0x00, .deqA_09[3] = 0x00, .deqA_09[4] = 0x00, .deqA_09[5] = 0x00, .deqA_09[6] = 0x00,  .deqA_09[7] = 0x00, .deqA_09[8] = 0x00, .deqA_09[9] = 0x00, .deqA_09[10] = 0x00,	// BankA 0x38
			.deqA_10[0] = 0x02, .deqA_10[1] = 0x02, .deqA_10[2] = 0x02, .deqA_10[3] = 0x02, .deqA_10[4] = 0x02, .deqA_10[5] = 0x02, .deqA_10[6] = 0x02,  .deqA_10[7] = 0x02, .deqA_10[8] = 0x02, .deqA_10[9] = 0x02, .deqA_10[10] = 0x02,	// BankA 0x39
			.deqA_11[0] = 0x00, .deqA_11[1] = 0x00, .deqA_11[2] = 0x00, .deqA_11[3] = 0x00, .deqA_11[4] = 0x00, .deqA_11[5] = 0x00, .deqA_11[6] = 0x00,  .deqA_11[7] = 0x00, .deqA_11[8] = 0x00, .deqA_11[9] = 0x00, .deqA_11[10] = 0x00,	// BankA 0x3a
			.deqA_12[0] = 0xB2, .deqA_12[1] = 0xB2, .deqA_12[2] = 0xB2, .deqA_12[3] = 0xB2, .deqA_12[4] = 0xB2, .deqA_12[5] = 0xB2, .deqA_12[6] = 0xB2,  .deqA_12[7] = 0xB2, .deqA_12[8] = 0xB2, .deqA_12[9] = 0xB2, .deqA_12[10] = 0xB2,	// BankA 0x3b
		},
		/* color */
		{
			.contrast[0] 		= 0x88, .contrast[1] 		= 0x88, .contrast[2] 		= 0x78, .contrast[3] 		= 0x88, .contrast[4] 		= 0x88, .contrast[5] 		= 0x7e, .contrast[6] 		= 0x78, .contrast[7] 		= 0x78, .contrast[8] 		= 0x74, .contrast[9] 		= 0x74, .contrast[10] 		= 0x74,
			.h_peaking[0] 		= 0x3f, .h_peaking[1] 		= 0x3f, .h_peaking[2] 		= 0x3f, .h_peaking[3] 		= 0x3f, .h_peaking[4] 		= 0x3f, .h_peaking[5] 		= 0x3f, .h_peaking[6] 		= 0x3f, .h_peaking[7] 		= 0x3f, .h_peaking[8] 		= 0x3f, .h_peaking[9] 		= 0x4f, .h_peaking[10] 		= 0x4f,
			.c_filter[0]		= 0x82, .c_filter[1] 		= 0x82, .c_filter[2]	 	= 0x82, .c_filter[3] 		= 0x82, .c_filter[4] 		= 0x92, .c_filter[5] 		= 0x92, .c_filter[6] 		= 0x92, .c_filter[7] 		= 0x92, .c_filter[8] 		= 0x92, .c_filter[9] 		= 0x92, .c_filter[10] 		= 0x92,

			.hue[0] 			= 0x00, .hue[1] 			= 0x00, .hue[2] 			= 0x00, .hue[3] 			= 0x00, .hue[4] 			= 0x00, .hue[5] 			= 0x00, .hue[6] 			= 0x00, .hue[7] 			= 0x00, .hue[8] 			= 0x00, .hue[9] 			= 0x00, .hue[10] 			= 0x00,
			.u_gain[0] 			= 0x00, .u_gain[1] 			= 0x00, .u_gain[2] 			= 0x00, .u_gain[3] 			= 0x00, .u_gain[4] 			= 0x00, .u_gain[5] 			= 0x00, .u_gain[6] 			= 0x00, .u_gain[7] 			= 0x00, .u_gain[8] 			= 0x00, .u_gain[9] 			= 0x00, .u_gain[10] 		= 0x00,
			.v_gain[0] 			= 0x00, .v_gain[1] 			= 0x00, .v_gain[2] 			= 0x00, .v_gain[3] 			= 0x00, .v_gain[4] 			= 0x00, .v_gain[5] 			= 0x00, .v_gain[6] 			= 0x00, .v_gain[7] 			= 0x00, .v_gain[8] 			= 0x00, .v_gain[9] 			= 0x00, .v_gain[10] 		= 0x00,
			.u_offset[0] 		= 0x00, .u_offset[1] 		= 0x00, .u_offset[2] 		= 0x00, .u_offset[3] 		= 0x00, .u_offset[4] 		= 0x00, .u_offset[5] 		= 0x00, .u_offset[6] 		= 0x00, .u_offset[7] 		= 0x00, .u_offset[8] 		= 0x00, .u_offset[9] 		= 0x00, .u_offset[10] 		= 0x00,
			.v_offset[0] 		= 0x00, .v_offset[1] 		= 0x00, .v_offset[2] 		= 0x00, .v_offset[3] 		= 0x00, .v_offset[4] 		= 0x00, .v_offset[5] 		= 0x00, .v_offset[6] 		= 0x00, .v_offset[7] 		= 0x00, .v_offset[8] 		= 0x00, .v_offset[9] 		= 0x00, .v_offset[10] 		= 0x00,

			.black_level[0] 	= 0x84, .black_level[1] 	= 0x84, .black_level[2] 	= 0x84, .black_level[3] 	= 0x84, .black_level[4] 	= 0x84, .black_level[5] 	= 0x86, .black_level[6] 	= 0x86, .black_level[7] 	= 0x8c, .black_level[8] 	= 0x8c, .black_level[9] 	= 0x90, .black_level[10] 	= 0x90,
			.acc_ref[0]			= 0x57, .acc_ref[1]			= 0x57, .acc_ref[2]			= 0x57, .acc_ref[3]			= 0x57, .acc_ref[4]			= 0x57, .acc_ref[5]			= 0x57, .acc_ref[6]			= 0x57, .acc_ref[7]			= 0x57, .acc_ref[8]			= 0x57, .acc_ref[9]			= 0x47, .acc_ref[10]		= 0x47,
			.cti_delay[0]		= 0x80, .cti_delay[1]		= 0x80, .cti_delay[2]		= 0x80, .cti_delay[3]		= 0x80, .cti_delay[4]		= 0x80, .cti_delay[5]		= 0x80, .cti_delay[6]		= 0x80, .cti_delay[7]		= 0x80, .cti_delay[8]		= 0x80, .cti_delay[9]		= 0x90, .cti_delay[10]		= 0x90,
			.sub_saturation[0] 	= 0xa8, .sub_saturation[1] 	= 0xab, .sub_saturation[2] 	= 0xb0, .sub_saturation[3] 	= 0xb0, .sub_saturation[4] 	= 0xa4, .sub_saturation[5] 	= 0xa0, .sub_saturation[6] 	= 0xa0, .sub_saturation[7] 	= 0xa0, .sub_saturation[8] 	= 0xa0, .sub_saturation[9] 	= 0x90, .sub_saturation[10] = 0x90,

			.burst_dec_a[0] 	= 0x2a, .burst_dec_a[1] 	= 0x2a, .burst_dec_a[2] 	= 0x2a, .burst_dec_a[3] 	= 0x2a, .burst_dec_a[4] 	= 0x2a, .burst_dec_a[5] 	= 0x2a, .burst_dec_a[6] 	= 0x2a, .burst_dec_a[7] 	= 0x2a, .burst_dec_a[8] 	= 0x2a, .burst_dec_a[9] 	= 0x2a, .burst_dec_a[10] 	= 0x2a,
			.burst_dec_b[0] 	= 0x00, .burst_dec_b[1] 	= 0x00, .burst_dec_b[2] 	= 0x00, .burst_dec_b[3] 	= 0x00, .burst_dec_b[4] 	= 0x00, .burst_dec_b[5] 	= 0x00, .burst_dec_b[6] 	= 0x00, .burst_dec_b[7] 	= 0x00, .burst_dec_b[8] 	= 0x00, .burst_dec_b[9] 	= 0x00, .burst_dec_b[10] 	= 0x00,
			.burst_dec_c[0] 	= 0x30, .burst_dec_c[1] 	= 0x30, .burst_dec_c[2] 	= 0x30, .burst_dec_c[3] 	= 0x30, .burst_dec_c[4] 	= 0x30, .burst_dec_c[5] 	= 0x30, .burst_dec_c[6] 	= 0x30, .burst_dec_c[7] 	= 0x30, .burst_dec_c[8] 	= 0x30, .burst_dec_c[9] 	= 0x30, .burst_dec_c[10] 	= 0x30,

			.c_option[0] 		= 0x80, .c_option[1] 		= 0x80, .c_option[2] 		= 0x80, .c_option[3] 		= 0x80, .c_option[4] 		= 0x90, .c_option[5] 		= 0x90, .c_option[6] 		= 0x90, .c_option[7] 		= 0x90, .c_option[8] 		= 0x90, .c_option[9] 		= 0x90, .c_option[10] 		= 0x90,

			.y_filter_b[0]		= 0x10, .y_filter_b[1]		= 0x10, .y_filter_b[2]		= 0x10, .y_filter_b[3]		= 0x10, .y_filter_b[4]		= 0x10, .y_filter_b[5]		= 0x10, .y_filter_b[6]		= 0x10, .y_filter_b[7]		= 0x10, .y_filter_b[8]		= 0x10, .y_filter_b[9]		= 0x10, .y_filter_b[10]		= 0x10,
			.y_filter_b_sel[0]	= 0x1e,	.y_filter_b_sel[1]	= 0x1e,	.y_filter_b_sel[2]	= 0x1e, .y_filter_b_sel[3]	= 0x1e, .y_filter_b_sel[4]	= 0x1e, .y_filter_b_sel[5]	= 0x1e, .y_filter_b_sel[6]	= 0x1e, .y_filter_b_sel[7]	= 0x1e, .y_filter_b_sel[8]	= 0x1e, .y_filter_b_sel[9]	= 0x1e, .y_filter_b_sel[10]	= 0x1e,
		},
		/* timing_a */
		{
#ifdef SUPPORT_720P_HDELAY_CONTROL_171226
			.h_delay_a[0] = 0x8d, .h_delay_a[1] = 0x8d, .h_delay_a[2] = 0x8d, .h_delay_a[3] = 0x8d, .h_delay_a[4] = 0x8d, .h_delay_a[5] = 0x8d, .h_delay_a[6] = 0x8d, .h_delay_a[7] = 0x8d, .h_delay_a[8] = 0x8d, .h_delay_a[9] = 0x8d, .h_delay_a[10] = 0x8d,
#else
			.h_delay_a[0] = 0xa0, .h_delay_a[1] = 0xa0, .h_delay_a[2] = 0x9e, .h_delay_a[3] = 0x9b, .h_delay_a[4] = 0x99, .h_delay_a[5] = 0x99, .h_delay_a[6] = 0x9b, .h_delay_a[7] = 0x98, .h_delay_a[8] = 0x98, .h_delay_a[9] = 0x98, .h_delay_a[10] = 0x98,
#endif
			.h_delay_b[0] = 0x00, .h_delay_b[1] = 0x00, .h_delay_b[2] = 0x00, .h_delay_b[3] = 0x00, .h_delay_b[4] = 0x00, .h_delay_b[5] = 0x00, .h_delay_b[6] = 0x00, .h_delay_b[7] = 0x00, .h_delay_b[8] = 0x00, .h_delay_b[9] = 0x00, .h_delay_b[10] = 0x00,
			.h_delay_c[0] = 0x00, .h_delay_c[1] = 0x00, .h_delay_c[2] = 0x00, .h_delay_c[3] = 0x00, .h_delay_c[4] = 0x00, .h_delay_c[5] = 0x00, .h_delay_c[6] = 0x00, .h_delay_c[7] = 0x00, .h_delay_c[8] = 0x00, .h_delay_c[9] = 0x00, .h_delay_c[10] = 0x00,
			.y_delay[0]   = 0x05, .y_delay[1]   = 0x05, .y_delay[2]   = 0x05, .y_delay[3]   = 0x05, .y_delay[4]   = 0x05, .y_delay[5] =   0x05, .y_delay[6] =   0x05, .y_delay[7] =   0x05, .y_delay[8] =   0x05, .y_delay[9] =   0x05, .y_delay[10] =   0x05,

		},
		/* clk */
		{
			.clk_adc[0] = 0x02, .clk_adc[1] = 0x02, .clk_adc[2] = 0x02, .clk_adc[3] = 0x02, .clk_adc[4] = 0x02, .clk_adc[5] = 0x02, .clk_adc[6] = 0x02, .clk_adc[7] = 0x02, .clk_adc[8] = 0x02, .clk_adc[9] = 0x02, .clk_adc[10] = 0x02,
			.clk_dec[0] = 0x40, .clk_dec[1] = 0x40, .clk_dec[2] = 0x40, .clk_dec[3] = 0x40, .clk_dec[4] = 0x40, .clk_dec[5] = 0x40, .clk_dec[6] = 0x40, .clk_dec[7] = 0x40, .clk_dec[8] = 0x40, .clk_dec[9] = 0x40, .clk_dec[10] = 0x40,
		},
		/* timing_b */
		{
/*B9 0x96*/	.h_scaler1[0]  = 0x00, .h_scaler1[1]   = 0x00, .h_scaler1[2]   = 0x00, .h_scaler1[3]   = 0x00, .h_scaler1[4]   = 0x00, .h_scaler1[5]   = 0x00, .h_scaler1[6]   = 0x00, .h_scaler1[7]   = 0x00, .h_scaler1[8]   = 0x00, .h_scaler1[9]   = 0x00, .h_scaler1[10]   = 0x00,
/*B9 0x97*/	.h_scaler2[0]  = 0x00, .h_scaler2[1]   = 0x00, .h_scaler2[2]   = 0x00, .h_scaler2[3]   = 0x00, .h_scaler2[4]   = 0x00, .h_scaler2[5]   = 0x00, .h_scaler2[6]   = 0x00, .h_scaler2[7]   = 0x00, .h_scaler2[8]   = 0x00, .h_scaler2[9]   = 0x00, .h_scaler2[10]   = 0x00,
/*B9 0x98*/	.h_scaler3[0]  = 0x00, .h_scaler3[1]   = 0x00, .h_scaler3[2]   = 0x00, .h_scaler3[3]   = 0x00, .h_scaler3[4]   = 0x00, .h_scaler3[5]   = 0x00, .h_scaler3[6]   = 0x00, .h_scaler3[7]   = 0x00, .h_scaler3[8]   = 0x00, .h_scaler3[9]   = 0x00, .h_scaler3[10]   = 0x00,
/*B9 0x99*/	.h_scaler4[0]  = 0x00, .h_scaler4[1]   = 0x00, .h_scaler4[2]   = 0x00, .h_scaler4[3]   = 0x00, .h_scaler4[4]   = 0x00, .h_scaler4[5]   = 0x00, .h_scaler4[6]   = 0x00, .h_scaler4[7]   = 0x00, .h_scaler4[8]   = 0x00, .h_scaler4[9]   = 0x00, .h_scaler4[10]   = 0x00,
/*B9 0x9a*/	.h_scaler5[0]  = 0x00, .h_scaler5[1]   = 0x00, .h_scaler5[2]   = 0x00, .h_scaler5[3]   = 0x00, .h_scaler5[4]   = 0x00, .h_scaler5[5]   = 0x00, .h_scaler5[6]   = 0x00, .h_scaler5[7]   = 0x00, .h_scaler5[8]   = 0x00, .h_scaler5[9]   = 0x00, .h_scaler5[10]   = 0x00,
/*B9 0x9b*/	.h_scaler6[0]  = 0x00, .h_scaler6[1]   = 0x00, .h_scaler6[2]   = 0x00, .h_scaler6[3]   = 0x00, .h_scaler6[4]   = 0x00, .h_scaler6[5]   = 0x00, .h_scaler6[6]   = 0x00, .h_scaler6[7]   = 0x00, .h_scaler6[8]   = 0x00, .h_scaler6[9]   = 0x00, .h_scaler6[10]   = 0x00,
/*B9 0x9c*/	.h_scaler7[0]  = 0x00, .h_scaler7[1]   = 0x00, .h_scaler7[2]   = 0x00, .h_scaler7[3]   = 0x00, .h_scaler7[4]   = 0x00, .h_scaler7[5]   = 0x00, .h_scaler7[6]   = 0x00, .h_scaler7[7]   = 0x00, .h_scaler7[8]   = 0x00, .h_scaler7[9]   = 0x00, .h_scaler7[10]   = 0x00,
/*B9 0x9d*/	.h_scaler8[0]  = 0x00, .h_scaler8[1]   = 0x00, .h_scaler8[2]   = 0x00, .h_scaler8[3]   = 0x00, .h_scaler8[4]   = 0x00, .h_scaler8[5]   = 0x00, .h_scaler8[6]   = 0x00, .h_scaler8[7]   = 0x00, .h_scaler8[8]   = 0x00, .h_scaler8[9]   = 0x00, .h_scaler8[10]   = 0x00,
/*B9 0x9e*/	.h_scaler9[0]  = 0x00, .h_scaler9[1]   = 0x00, .h_scaler9[2]   = 0x00, .h_scaler9[3]   = 0x00, .h_scaler9[4]   = 0x00, .h_scaler9[5]   = 0x00, .h_scaler9[6]   = 0x00, .h_scaler9[7]   = 0x00, .h_scaler9[8]   = 0x00, .h_scaler9[9]   = 0x00, .h_scaler9[10]   = 0x00,


/*B9 0x40*/	.pn_auto[0]    	= 0x00, .pn_auto[1]		= 0x00, .pn_auto[2]    	= 0x00, .pn_auto[3]    	= 0x00, .pn_auto[4]    	= 0x00, .pn_auto[5]    	= 0x00, .pn_auto[6]		= 0x00, .pn_auto[7]    	= 0x00, .pn_auto[8]    	= 0x00, .pn_auto[9]    	= 0x00, .pn_auto[10]    	= 0x00,

/*B5 0x90*/	.comb_mode[0]   = 0x01, .comb_mode[1]	= 0x01, .comb_mode[2]   = 0x01, .comb_mode[3]   = 0x01, .comb_mode[4]  	= 0x01, .comb_mode[5]   = 0x01, .comb_mode[6]	= 0x01, .comb_mode[7]   = 0x01, .comb_mode[8]   = 0x01, .comb_mode[9]  	= 0x01, .comb_mode[10]   = 0x01,
/*B9 0xb9*/	.h_pll_op_a[0]  = 0x72, .h_pll_op_a[1]  = 0x72, .h_pll_op_a[2]  = 0x72, .h_pll_op_a[3]  = 0x72, .h_pll_op_a[4]  = 0x72, .h_pll_op_a[5]  = 0x72, .h_pll_op_a[6]  = 0x72, .h_pll_op_a[7]  = 0x72, .h_pll_op_a[8]  = 0x72, .h_pll_op_a[9]  = 0x72, .h_pll_op_a[10]  = 0x72,
/*B9 0x57*/	.mem_path[0]	= 0x00, .mem_path[1]	= 0x00, .mem_path[2]	= 0x00, .mem_path[3]	= 0x00, .mem_path[4]	= 0x00, .mem_path[5]	= 0x00, .mem_path[6]	= 0x00, .mem_path[7]	= 0x00, .mem_path[8]	= 0x00, .mem_path[9]	= 0x00, .mem_path[10]	= 0x00,
			.fsc_lock_speed[0] = 0xdc, .fsc_lock_speed[1] = 0xdc, .fsc_lock_speed[2] = 0xdc, .fsc_lock_speed[3] = 0xdc, .fsc_lock_speed[4] = 0xdc, .fsc_lock_speed[5] = 0xdc, .fsc_lock_speed[6] = 0xdc, .fsc_lock_speed[7] = 0xdc, .fsc_lock_speed[8] = 0xdc, .fsc_lock_speed[9] = 0xdc, .fsc_lock_speed[10] = 0xdc,

/*B0 0x81*/	.format_set1[0] = 0x0c, .format_set1[1] = 0x0c, .format_set1[2] = 0x0c, .format_set1[3] = 0x0c, .format_set1[4] = 0x0c, .format_set1[5] = 0x0c, .format_set1[6] = 0x0c, .format_set1[7] = 0x0c, .format_set1[8] = 0x0c, .format_set1[9] = 0x0c, .format_set1[10] = 0x0c,
/*B0 0x85*/	.format_set2[0] = 0x00, .format_set2[1] = 0x00, .format_set2[2] = 0x00, .format_set2[3] = 0x00, .format_set2[4] = 0x00, .format_set2[5] = 0x00, .format_set2[6] = 0x00, .format_set2[7] = 0x00, .format_set2[8] = 0x00, .format_set2[9] = 0x00, .format_set2[10] = 0x00,

/*B0 0x64*/ .v_delay[0]     = 0x21, .v_delay[1]     = 0x21, .v_delay[2]     = 0x21, .v_delay[3]     = 0x21, .v_delay[4]     = 0x21, .v_delay[5]     = 0x21, .v_delay[6]     = 0x21, .v_delay[7]     = 0x21, .v_delay[8]     = 0x21, .v_delay[9]     = 0x21, .v_delay[10]     = 0x21,
		},
	},

	[ AHD20_720P_25P ] = /* o */
		{
			/* base */
			{
				.eq_bypass[0] 	= 0x62, .eq_bypass[1] 	= 0x62, .eq_bypass[2] 	= 0x22, .eq_bypass[3] 	= 0x22, .eq_bypass[4] 	= 0x22, .eq_bypass[5] 	= 0x22, .eq_bypass[6] 	= 0x22, .eq_bypass[7] 	= 0x22, .eq_bypass[8] 	= 0x22, .eq_bypass[9] 	= 0x22, .eq_bypass[10] 	 = 0x22,  // Bank5 0x30
				.eq_band_sel[0] = 0x77, .eq_band_sel[1] = 0x77, .eq_band_sel[2] = 0x77, .eq_band_sel[3] = 0x77, .eq_band_sel[4] = 0x67, .eq_band_sel[5] = 0x57, .eq_band_sel[6] = 0x47, .eq_band_sel[7] = 0x47, .eq_band_sel[8] = 0x27, .eq_band_sel[9] = 0x17, .eq_band_sel[10] = 0x17, // BankA 0x31
				.eq_gain_sel[0] = 0x78, .eq_gain_sel[1] = 0x78, .eq_gain_sel[2] = 0x7a, .eq_gain_sel[3] = 0x7f, .eq_gain_sel[4] = 0x7f, .eq_gain_sel[5] = 0x7f, .eq_gain_sel[6] = 0x7f, .eq_gain_sel[7] = 0x7f, .eq_gain_sel[8] = 0x7f, .eq_gain_sel[9] = 0x7f, .eq_gain_sel[10] = 0x7f, // BankA 0x32
				.deq_a_on[0] 	= 0x00, .deq_a_on[1] 	= 0x01, .deq_a_on[2] 	= 0x01, .deq_a_on[3] 	= 0x01, .deq_a_on[4] 	= 0x01, .deq_a_on[5] 	= 0x01, .deq_a_on[6] 	= 0x01, .deq_a_on[7] 	= 0x01, .deq_a_on[8] 	= 0x01, .deq_a_on[9] 	= 0x01, .deq_a_on[10] 	 = 0x01, // BankA 0x33
				.deq_a_sel[0] 	= 0x00, .deq_a_sel[1] 	= 0x86, .deq_a_sel[2] 	= 0x87, .deq_a_sel[3] 	= 0x93, .deq_a_sel[4] 	= 0x8e, .deq_a_sel[5] 	= 0x8e, .deq_a_sel[6] 	= 0x93, .deq_a_sel[7] 	= 0x93, .deq_a_sel[8] 	= 0x93, .deq_a_sel[9] 	= 0x8d, .deq_a_sel[10] 	 = 0x8d, // BankA 0x34
				.deq_b_sel[0] 	= 0x00, .deq_b_sel[1] 	= 0x00, .deq_b_sel[2] 	= 0x00, .deq_b_sel[3] 	= 0x00, .deq_b_sel[4] 	= 0x00, .deq_b_sel[5] 	= 0x00, .deq_b_sel[6] 	= 0x00, .deq_b_sel[7] 	= 0x00, .deq_b_sel[8] 	= 0x00, .deq_b_sel[9] 	= 0x00, .deq_b_sel[10] 	 = 0x00, // BankA 0x35
			},
			/* coeff */
			{
				.deqA_01[0] = 0xAC, .deqA_01[1] = 0xAC, .deqA_01[2] = 0xAC, .deqA_01[3] = 0xAC, .deqA_01[4] = 0xAC, .deqA_01[5] = 0xAC,	.deqA_01[6] = 0xAC,  .deqA_01[7] = 0xAC, .deqA_01[8] = 0xAC, .deqA_01[9] = 0xAC, .deqA_01[10] = 0xAC,	// BankA 0x30
				.deqA_02[0] = 0x78, .deqA_02[1] = 0x78, .deqA_02[2] = 0x78, .deqA_02[3] = 0x78, .deqA_02[4] = 0x78, .deqA_02[5] = 0x78,	.deqA_02[6] = 0x78,	 .deqA_02[7] = 0x78, .deqA_02[8] = 0x78, .deqA_02[9] = 0x78, .deqA_02[10] = 0x78,	// BankA 0x31
				.deqA_03[0] = 0x17, .deqA_03[1] = 0x17, .deqA_03[2] = 0x17, .deqA_03[3] = 0x17, .deqA_03[4] = 0x17, .deqA_03[5] = 0x17,	.deqA_03[6] = 0x17,	 .deqA_03[7] = 0x17, .deqA_03[8] = 0x17, .deqA_03[9] = 0x17, .deqA_03[10] = 0x17,	// BankA 0x32
				.deqA_04[0] = 0xC1, .deqA_04[1] = 0xC1, .deqA_04[2] = 0xC1, .deqA_04[3] = 0xC1, .deqA_04[4] = 0xC1, .deqA_04[5] = 0xC1, .deqA_04[6] = 0xC1,  .deqA_04[7] = 0xC1, .deqA_04[8] = 0xC1, .deqA_04[9] = 0xC1, .deqA_04[10] = 0xC1,	// BankA 0x33
				.deqA_05[0] = 0x40, .deqA_05[1] = 0x40, .deqA_05[2] = 0x40, .deqA_05[3] = 0x40, .deqA_05[4] = 0x40, .deqA_05[5] = 0x40, .deqA_05[6] = 0x40,  .deqA_05[7] = 0x40, .deqA_05[8] = 0x40, .deqA_05[9] = 0x40, .deqA_05[10] = 0x40,	// BankA 0x34
				.deqA_06[0] = 0x00, .deqA_06[1] = 0x00, .deqA_06[2] = 0x00, .deqA_06[3] = 0x00, .deqA_06[4] = 0x00, .deqA_06[5] = 0x00, .deqA_06[6] = 0x00,  .deqA_06[7] = 0x00, .deqA_06[8] = 0x00, .deqA_06[9] = 0x00, .deqA_06[10] = 0x00,	// BankA 0x35
				.deqA_07[0] = 0xC3, .deqA_07[1] = 0xC3, .deqA_07[2] = 0xC3, .deqA_07[3] = 0xC3, .deqA_07[4] = 0xC3, .deqA_07[5] = 0xC3, .deqA_07[6] = 0xC3,  .deqA_07[7] = 0xC3, .deqA_07[8] = 0xC3, .deqA_07[9] = 0xC3, .deqA_07[10] = 0xC3,	// BankA 0x36
				.deqA_08[0] = 0x0A, .deqA_08[1] = 0x0A, .deqA_08[2] = 0x0A, .deqA_08[3] = 0x0A, .deqA_08[4] = 0x0A, .deqA_08[5] = 0x0A, .deqA_08[6] = 0x0A,  .deqA_08[7] = 0x0A, .deqA_08[8] = 0x0A, .deqA_08[9] = 0x0A, .deqA_08[10] = 0x0A,	// BankA 0x37
				.deqA_09[0] = 0x00, .deqA_09[1] = 0x00, .deqA_09[2] = 0x00, .deqA_09[3] = 0x00, .deqA_09[4] = 0x00, .deqA_09[5] = 0x00, .deqA_09[6] = 0x00,  .deqA_09[7] = 0x00, .deqA_09[8] = 0x00, .deqA_09[9] = 0x00, .deqA_09[10] = 0x00,	// BankA 0x38
				.deqA_10[0] = 0x02, .deqA_10[1] = 0x02, .deqA_10[2] = 0x02, .deqA_10[3] = 0x02, .deqA_10[4] = 0x02, .deqA_10[5] = 0x02, .deqA_10[6] = 0x02,  .deqA_10[7] = 0x02, .deqA_10[8] = 0x02, .deqA_10[9] = 0x02, .deqA_10[10] = 0x02,	// BankA 0x39
				.deqA_11[0] = 0x00, .deqA_11[1] = 0x00, .deqA_11[2] = 0x00, .deqA_11[3] = 0x00, .deqA_11[4] = 0x00, .deqA_11[5] = 0x00, .deqA_11[6] = 0x00,  .deqA_11[7] = 0x00, .deqA_11[8] = 0x00, .deqA_11[9] = 0x00, .deqA_11[10] = 0x00,	// BankA 0x3a
				.deqA_12[0] = 0xB2, .deqA_12[1] = 0xB2, .deqA_12[2] = 0xB2, .deqA_12[3] = 0xB2, .deqA_12[4] = 0xB2, .deqA_12[5] = 0xB2, .deqA_12[6] = 0xB2,  .deqA_12[7] = 0xB2, .deqA_12[8] = 0xB2, .deqA_12[9] = 0xB2, .deqA_12[10] = 0xB2,	// BankA 0x3b
			},
			/* color */
			{
				.contrast[0] 		= 0x88, .contrast[1] 		= 0x88, .contrast[2] 		= 0x78, .contrast[3] 		= 0x88, .contrast[4] 		= 0x88, .contrast[5] 		= 0x7e, .contrast[6] 		= 0x78, .contrast[7] 		= 0x78, .contrast[8] 		= 0x74, .contrast[9] 		= 0x74, .contrast[10] 		= 0x74,
				.h_peaking[0] 		= 0x3f, .h_peaking[1] 		= 0x3f, .h_peaking[2] 		= 0x3f, .h_peaking[3] 		= 0x3f, .h_peaking[4] 		= 0x3f, .h_peaking[5] 		= 0x3f, .h_peaking[6] 		= 0x3f, .h_peaking[7] 		= 0x3f, .h_peaking[8] 		= 0x3f, .h_peaking[9] 		= 0x4f, .h_peaking[10] 		= 0x4f,
				.c_filter[0]		= 0x82, .c_filter[1] 		= 0x82, .c_filter[2]	 	= 0x82, .c_filter[3] 		= 0x82, .c_filter[4] 		= 0x92, .c_filter[5] 		= 0x92, .c_filter[6] 		= 0x92, .c_filter[7] 		= 0x92, .c_filter[8] 		= 0x92, .c_filter[9] 		= 0x92, .c_filter[10] 		= 0x92,

				.hue[0] 			= 0x00, .hue[1] 			= 0x00, .hue[2] 			= 0x00, .hue[3] 			= 0x00, .hue[4] 			= 0x00, .hue[5] 			= 0x00, .hue[6] 			= 0x00, .hue[7] 			= 0x00, .hue[8] 			= 0x00, .hue[9] 			= 0x00, .hue[10] 			= 0x00,
				.u_gain[0] 			= 0x00, .u_gain[1] 			= 0x00, .u_gain[2] 			= 0x00, .u_gain[3] 			= 0x00, .u_gain[4] 			= 0x00, .u_gain[5] 			= 0x00, .u_gain[6] 			= 0x00, .u_gain[7] 			= 0x00, .u_gain[8] 			= 0x00, .u_gain[9] 			= 0x00, .u_gain[10] 		= 0x00,
				.v_gain[0] 			= 0x00, .v_gain[1] 			= 0x00, .v_gain[2] 			= 0x00, .v_gain[3] 			= 0x00, .v_gain[4] 			= 0x00, .v_gain[5] 			= 0x00, .v_gain[6] 			= 0x00, .v_gain[7] 			= 0x00, .v_gain[8] 			= 0x00, .v_gain[9] 			= 0x00, .v_gain[10] 		= 0x00,
				.u_offset[0] 		= 0x00, .u_offset[1] 		= 0x00, .u_offset[2] 		= 0x00, .u_offset[3] 		= 0x00, .u_offset[4] 		= 0x00, .u_offset[5] 		= 0x00, .u_offset[6] 		= 0x00, .u_offset[7] 		= 0x00, .u_offset[8] 		= 0x00, .u_offset[9] 		= 0x00, .u_offset[10] 		= 0x00,
				.v_offset[0] 		= 0x00, .v_offset[1] 		= 0x00, .v_offset[2] 		= 0x00, .v_offset[3] 		= 0x00, .v_offset[4] 		= 0x00, .v_offset[5] 		= 0x00, .v_offset[6] 		= 0x00, .v_offset[7] 		= 0x00, .v_offset[8] 		= 0x00, .v_offset[9] 		= 0x00, .v_offset[10] 		= 0x00,

				.black_level[0] 	= 0x84, .black_level[1] 	= 0x84, .black_level[2] 	= 0x84, .black_level[3] 	= 0x84, .black_level[4] 	= 0x84, .black_level[5] 	= 0x86, .black_level[6] 	= 0x86, .black_level[7] 	= 0x8c, .black_level[8] 	= 0x8c, .black_level[9] 	= 0x90, .black_level[10] 	= 0x90,
				.acc_ref[0]			= 0x57, .acc_ref[1]			= 0x57, .acc_ref[2]			= 0x57, .acc_ref[3]			= 0x57, .acc_ref[4]			= 0x57, .acc_ref[5]			= 0x57, .acc_ref[6]			= 0x57, .acc_ref[7]			= 0x57, .acc_ref[8]			= 0x57, .acc_ref[9]			= 0x47, .acc_ref[10]		= 0x47,
				.cti_delay[0]		= 0x80, .cti_delay[1]		= 0x80, .cti_delay[2]		= 0x80, .cti_delay[3]		= 0x80, .cti_delay[4]		= 0x80, .cti_delay[5]		= 0x80, .cti_delay[6]		= 0x80, .cti_delay[7]		= 0x80, .cti_delay[8]		= 0x80, .cti_delay[9]		= 0x90, .cti_delay[10]		= 0x90,
				.sub_saturation[0] 	= 0xa8, .sub_saturation[1] 	= 0xab, .sub_saturation[2] 	= 0xb0, .sub_saturation[3] 	= 0xb0, .sub_saturation[4] 	= 0xa4, .sub_saturation[5] 	= 0xa0, .sub_saturation[6] 	= 0xa0, .sub_saturation[7] 	= 0xa0, .sub_saturation[8] 	= 0xa0, .sub_saturation[9] 	= 0x90, .sub_saturation[10] = 0x90,

				.burst_dec_a[0] 	= 0x2a, .burst_dec_a[1] 	= 0x2a, .burst_dec_a[2] 	= 0x2a, .burst_dec_a[3] 	= 0x2a, .burst_dec_a[4] 	= 0x2a, .burst_dec_a[5] 	= 0x2a, .burst_dec_a[6] 	= 0x2a, .burst_dec_a[7] 	= 0x2a, .burst_dec_a[8] 	= 0x2a, .burst_dec_a[9] 	= 0x2a, .burst_dec_a[10] 	= 0x2a,
				.burst_dec_b[0] 	= 0x00, .burst_dec_b[1] 	= 0x00, .burst_dec_b[2] 	= 0x00, .burst_dec_b[3] 	= 0x00, .burst_dec_b[4] 	= 0x00, .burst_dec_b[5] 	= 0x00, .burst_dec_b[6] 	= 0x00, .burst_dec_b[7] 	= 0x00, .burst_dec_b[8] 	= 0x00, .burst_dec_b[9] 	= 0x00, .burst_dec_b[10] 	= 0x00,
				.burst_dec_c[0] 	= 0x30, .burst_dec_c[1] 	= 0x30, .burst_dec_c[2] 	= 0x30, .burst_dec_c[3] 	= 0x30, .burst_dec_c[4] 	= 0x30, .burst_dec_c[5] 	= 0x30, .burst_dec_c[6] 	= 0x30, .burst_dec_c[7] 	= 0x30, .burst_dec_c[8] 	= 0x30, .burst_dec_c[9] 	= 0x30, .burst_dec_c[10] 	= 0x30,

				.c_option[0] 		= 0x80, .c_option[1] 		= 0x80, .c_option[2] 		= 0x80, .c_option[3] 		= 0x80, .c_option[4] 		= 0x90, .c_option[5] 		= 0x90, .c_option[6] 		= 0x90, .c_option[7] 		= 0x90, .c_option[8] 		= 0x90, .c_option[9] 		= 0x90, .c_option[10] 		= 0x90,

				.y_filter_b[0]		= 0x10, .y_filter_b[1]		= 0x10, .y_filter_b[2]		= 0x10, .y_filter_b[3]		= 0x10, .y_filter_b[4]		= 0x10, .y_filter_b[5]		= 0x10, .y_filter_b[6]		= 0x10, .y_filter_b[7]		= 0x10, .y_filter_b[8]		= 0x10, .y_filter_b[9]		= 0x10, .y_filter_b[10]		= 0x10,
				.y_filter_b_sel[0]	= 0x1e,	.y_filter_b_sel[1]	= 0x1e,	.y_filter_b_sel[2]	= 0x1e, .y_filter_b_sel[3]	= 0x1e, .y_filter_b_sel[4]	= 0x1e, .y_filter_b_sel[5]	= 0x1e, .y_filter_b_sel[6]	= 0x1e, .y_filter_b_sel[7]	= 0x1e, .y_filter_b_sel[8]	= 0x1e, .y_filter_b_sel[9]	= 0x1e, .y_filter_b_sel[10]	= 0x1e,
			},
			/* timing_a */
			{
#ifdef SUPPORT_720P_HDELAY_CONTROL_171226
			.h_delay_a[0] = 0x8d, .h_delay_a[1] = 0x8d, .h_delay_a[2] = 0x8d, .h_delay_a[3] = 0x8d, .h_delay_a[4] = 0x8d, .h_delay_a[5] = 0x8d, .h_delay_a[6] = 0x8d, .h_delay_a[7] = 0x8d, .h_delay_a[8] = 0x8d, .h_delay_a[9] = 0x8d, .h_delay_a[10] = 0x8d,
#else
				.h_delay_a[0] = 0xa0, .h_delay_a[1] = 0xa0, .h_delay_a[2] = 0x9e, .h_delay_a[3] = 0x9b, .h_delay_a[4] = 0x99, .h_delay_a[5] = 0x99, .h_delay_a[6] = 0x9b, .h_delay_a[7] = 0x98, .h_delay_a[8] = 0x98, .h_delay_a[9] = 0x98, .h_delay_a[10] = 0x98,
#endif
				.h_delay_b[0] = 0x00, .h_delay_b[1] = 0x00, .h_delay_b[2] = 0x00, .h_delay_b[3] = 0x00, .h_delay_b[4] = 0x00, .h_delay_b[5] = 0x00, .h_delay_b[6] = 0x00, .h_delay_b[7] = 0x00, .h_delay_b[8] = 0x00, .h_delay_b[9] = 0x00, .h_delay_b[10] = 0x00,
				.h_delay_c[0] = 0x00, .h_delay_c[1] = 0x00, .h_delay_c[2] = 0x00, .h_delay_c[3] = 0x00, .h_delay_c[4] = 0x00, .h_delay_c[5] = 0x00, .h_delay_c[6] = 0x00, .h_delay_c[7] = 0x00, .h_delay_c[8] = 0x00, .h_delay_c[9] = 0x00, .h_delay_c[10] = 0x00,
				.y_delay[0]   = 0x05, .y_delay[1]   = 0x05, .y_delay[2]   = 0x05, .y_delay[3]   = 0x05, .y_delay[4]   = 0x05, .y_delay[5] =   0x05, .y_delay[6] =   0x05, .y_delay[7] =   0x05, .y_delay[8] =   0x05, .y_delay[9] =   0x05, .y_delay[10] =   0x05,

			},
			/* clk */
			{
				.clk_adc[0] = 0x02, .clk_adc[1] = 0x02, .clk_adc[2] = 0x02, .clk_adc[3] = 0x02, .clk_adc[4] = 0x02, .clk_adc[5] = 0x02, .clk_adc[6] = 0x02, .clk_adc[7] = 0x02, .clk_adc[8] = 0x02, .clk_adc[9] = 0x02, .clk_adc[10] = 0x02,
				.clk_dec[0] = 0x40, .clk_dec[1] = 0x40, .clk_dec[2] = 0x40, .clk_dec[3] = 0x40, .clk_dec[4] = 0x40, .clk_dec[5] = 0x40, .clk_dec[6] = 0x40, .clk_dec[7] = 0x40, .clk_dec[8] = 0x40, .clk_dec[9] = 0x40, .clk_dec[10] = 0x40,
			},
			/* timing_b */
			{
	/*B9 0x96*/	.h_scaler1[0]  = 0x00, .h_scaler1[1]   = 0x00, .h_scaler1[2]   = 0x00, .h_scaler1[3]   = 0x00, .h_scaler1[4]   = 0x00, .h_scaler1[5]   = 0x00, .h_scaler1[6]   = 0x00, .h_scaler1[7]   = 0x00, .h_scaler1[8]   = 0x00, .h_scaler1[9]   = 0x00, .h_scaler1[10]   = 0x00,
	/*B9 0x97*/	.h_scaler2[0]  = 0x00, .h_scaler2[1]   = 0x00, .h_scaler2[2]   = 0x00, .h_scaler2[3]   = 0x00, .h_scaler2[4]   = 0x00, .h_scaler2[5]   = 0x00, .h_scaler2[6]   = 0x00, .h_scaler2[7]   = 0x00, .h_scaler2[8]   = 0x00, .h_scaler2[9]   = 0x00, .h_scaler2[10]   = 0x00,
	/*B9 0x98*/	.h_scaler3[0]  = 0x00, .h_scaler3[1]   = 0x00, .h_scaler3[2]   = 0x00, .h_scaler3[3]   = 0x00, .h_scaler3[4]   = 0x00, .h_scaler3[5]   = 0x00, .h_scaler3[6]   = 0x00, .h_scaler3[7]   = 0x00, .h_scaler3[8]   = 0x00, .h_scaler3[9]   = 0x00, .h_scaler3[10]   = 0x00,
	/*B9 0x99*/	.h_scaler4[0]  = 0x00, .h_scaler4[1]   = 0x00, .h_scaler4[2]   = 0x00, .h_scaler4[3]   = 0x00, .h_scaler4[4]   = 0x00, .h_scaler4[5]   = 0x00, .h_scaler4[6]   = 0x00, .h_scaler4[7]   = 0x00, .h_scaler4[8]   = 0x00, .h_scaler4[9]   = 0x00, .h_scaler4[10]   = 0x00,
	/*B9 0x9a*/	.h_scaler5[0]  = 0x00, .h_scaler5[1]   = 0x00, .h_scaler5[2]   = 0x00, .h_scaler5[3]   = 0x00, .h_scaler5[4]   = 0x00, .h_scaler5[5]   = 0x00, .h_scaler5[6]   = 0x00, .h_scaler5[7]   = 0x00, .h_scaler5[8]   = 0x00, .h_scaler5[9]   = 0x00, .h_scaler5[10]   = 0x00,
	/*B9 0x9b*/	.h_scaler6[0]  = 0x00, .h_scaler6[1]   = 0x00, .h_scaler6[2]   = 0x00, .h_scaler6[3]   = 0x00, .h_scaler6[4]   = 0x00, .h_scaler6[5]   = 0x00, .h_scaler6[6]   = 0x00, .h_scaler6[7]   = 0x00, .h_scaler6[8]   = 0x00, .h_scaler6[9]   = 0x00, .h_scaler6[10]   = 0x00,
	/*B9 0x9c*/	.h_scaler7[0]  = 0x00, .h_scaler7[1]   = 0x00, .h_scaler7[2]   = 0x00, .h_scaler7[3]   = 0x00, .h_scaler7[4]   = 0x00, .h_scaler7[5]   = 0x00, .h_scaler7[6]   = 0x00, .h_scaler7[7]   = 0x00, .h_scaler7[8]   = 0x00, .h_scaler7[9]   = 0x00, .h_scaler7[10]   = 0x00,
	/*B9 0x9d*/	.h_scaler8[0]  = 0x00, .h_scaler8[1]   = 0x00, .h_scaler8[2]   = 0x00, .h_scaler8[3]   = 0x00, .h_scaler8[4]   = 0x00, .h_scaler8[5]   = 0x00, .h_scaler8[6]   = 0x00, .h_scaler8[7]   = 0x00, .h_scaler8[8]   = 0x00, .h_scaler8[9]   = 0x00, .h_scaler8[10]   = 0x00,
	/*B9 0x9e*/	.h_scaler9[0]  = 0x00, .h_scaler9[1]   = 0x00, .h_scaler9[2]   = 0x00, .h_scaler9[3]   = 0x00, .h_scaler9[4]   = 0x00, .h_scaler9[5]   = 0x00, .h_scaler9[6]   = 0x00, .h_scaler9[7]   = 0x00, .h_scaler9[8]   = 0x00, .h_scaler9[9]   = 0x00, .h_scaler9[10]   = 0x00,


	/*B9 0x40*/	.pn_auto[0]    	= 0x00, .pn_auto[1]		= 0x00, .pn_auto[2]    	= 0x00, .pn_auto[3]    	= 0x00, .pn_auto[4]    	= 0x00, .pn_auto[5]    	= 0x00, .pn_auto[6]		= 0x00, .pn_auto[7]    	= 0x00, .pn_auto[8]    	= 0x00, .pn_auto[9]    	= 0x00, .pn_auto[10]    	= 0x00,

	/*B5 0x90*/	.comb_mode[0]   = 0x01, .comb_mode[1]	= 0x01, .comb_mode[2]   = 0x01, .comb_mode[3]   = 0x01, .comb_mode[4]  	= 0x01, .comb_mode[5]   = 0x01, .comb_mode[6]	= 0x01, .comb_mode[7]   = 0x01, .comb_mode[8]   = 0x01, .comb_mode[9]  	= 0x01, .comb_mode[10]   = 0x01,
	/*B9 0xb9*/	.h_pll_op_a[0]  = 0x72, .h_pll_op_a[1]  = 0x72, .h_pll_op_a[2]  = 0x72, .h_pll_op_a[3]  = 0x72, .h_pll_op_a[4]  = 0x72, .h_pll_op_a[5]  = 0x72, .h_pll_op_a[6]  = 0x72, .h_pll_op_a[7]  = 0x72, .h_pll_op_a[8]  = 0x72, .h_pll_op_a[9]  = 0x72, .h_pll_op_a[10]  = 0x72,
	/*B9 0x57*/	.mem_path[0]	= 0x00, .mem_path[1]	= 0x00, .mem_path[2]	= 0x00, .mem_path[3]	= 0x00, .mem_path[4]	= 0x00, .mem_path[5]	= 0x00, .mem_path[6]	= 0x00, .mem_path[7]	= 0x00, .mem_path[8]	= 0x00, .mem_path[9]	= 0x00, .mem_path[10]	= 0x00,
				.fsc_lock_speed[0] = 0xdc, .fsc_lock_speed[1] = 0xdc, .fsc_lock_speed[2] = 0xdc, .fsc_lock_speed[3] = 0xdc, .fsc_lock_speed[4] = 0xdc, .fsc_lock_speed[5] = 0xdc, .fsc_lock_speed[6] = 0xdc, .fsc_lock_speed[7] = 0xdc, .fsc_lock_speed[8] = 0xdc, .fsc_lock_speed[9] = 0xdc, .fsc_lock_speed[10] = 0xdc,

	/*B0 0x81*/	.format_set1[0] = 0x0d, .format_set1[1] = 0x0d, .format_set1[2] = 0x0d, .format_set1[3] = 0x0d, .format_set1[4] = 0x0d, .format_set1[5] = 0x0d, .format_set1[6] = 0x0d, .format_set1[7] = 0x0d, .format_set1[8] = 0x0d, .format_set1[9] = 0x0d, .format_set1[10] = 0x0d,
	/*B0 0x85*/	.format_set2[0] = 0x00, .format_set2[1] = 0x00, .format_set2[2] = 0x00, .format_set2[3] = 0x00, .format_set2[4] = 0x00, .format_set2[5] = 0x00, .format_set2[6] = 0x00, .format_set2[7] = 0x00, .format_set2[8] = 0x00, .format_set2[9] = 0x00, .format_set2[10] = 0x00,

	/*B0 0x64*/ .v_delay[0]     = 0x21, .v_delay[1]     = 0x21, .v_delay[2]     = 0x21, .v_delay[3]     = 0x21, .v_delay[4]     = 0x21, .v_delay[5]     = 0x21, .v_delay[6]     = 0x21, .v_delay[7]     = 0x21, .v_delay[8]     = 0x21, .v_delay[9]     = 0x21, .v_delay[10]     = 0x21,
			},
		},
		[ AHD20_720P_30P ] = /* o */
		{
			/* base */
			{
				.eq_bypass[0] 	= 0x62, .eq_bypass[1] 	= 0x62, .eq_bypass[2] 	= 0x22, .eq_bypass[3] 	= 0x22, .eq_bypass[4] 	= 0x22, .eq_bypass[5] 	= 0x22, .eq_bypass[6] 	= 0x22, .eq_bypass[7] 	= 0x22, .eq_bypass[8] 	= 0x22, .eq_bypass[9] 	= 0x22, .eq_bypass[10] 	 = 0x22,  // Bank5 0x30
				.eq_band_sel[0] = 0x77, .eq_band_sel[1] = 0x77, .eq_band_sel[2] = 0x77, .eq_band_sel[3] = 0x77, .eq_band_sel[4] = 0x67, .eq_band_sel[5] = 0x57, .eq_band_sel[6] = 0x47, .eq_band_sel[7] = 0x47, .eq_band_sel[8] = 0x27, .eq_band_sel[9] = 0x17, .eq_band_sel[10] = 0x17, // BankA 0x31
				.eq_gain_sel[0] = 0x78, .eq_gain_sel[1] = 0x78, .eq_gain_sel[2] = 0x7a, .eq_gain_sel[3] = 0x7f, .eq_gain_sel[4] = 0x7f, .eq_gain_sel[5] = 0x7f, .eq_gain_sel[6] = 0x7f, .eq_gain_sel[7] = 0x7f, .eq_gain_sel[8] = 0x7f, .eq_gain_sel[9] = 0x7f, .eq_gain_sel[10] = 0x7f, // BankA 0x32
				.deq_a_on[0] 	= 0x00, .deq_a_on[1] 	= 0x01, .deq_a_on[2] 	= 0x01, .deq_a_on[3] 	= 0x01, .deq_a_on[4] 	= 0x01, .deq_a_on[5] 	= 0x01, .deq_a_on[6] 	= 0x01, .deq_a_on[7] 	= 0x01, .deq_a_on[8] 	= 0x01, .deq_a_on[9] 	= 0x01, .deq_a_on[10] 	 = 0x01, // BankA 0x33
				.deq_a_sel[0] 	= 0x00, .deq_a_sel[1] 	= 0x86, .deq_a_sel[2] 	= 0x87, .deq_a_sel[3] 	= 0x93, .deq_a_sel[4] 	= 0x8e, .deq_a_sel[5] 	= 0x8e, .deq_a_sel[6] 	= 0x93, .deq_a_sel[7] 	= 0x93, .deq_a_sel[8] 	= 0x93, .deq_a_sel[9] 	= 0x8d, .deq_a_sel[10] 	 = 0x8d, // BankA 0x34
				.deq_b_sel[0] 	= 0x00, .deq_b_sel[1] 	= 0x00, .deq_b_sel[2] 	= 0x00, .deq_b_sel[3] 	= 0x00, .deq_b_sel[4] 	= 0x00, .deq_b_sel[5] 	= 0x00, .deq_b_sel[6] 	= 0x00, .deq_b_sel[7] 	= 0x00, .deq_b_sel[8] 	= 0x00, .deq_b_sel[9] 	= 0x00, .deq_b_sel[10] 	 = 0x00, // BankA 0x35
			},
			/* coeff */
			{
				.deqA_01[0] = 0xAC, .deqA_01[1] = 0xAC, .deqA_01[2] = 0xAC, .deqA_01[3] = 0xAC, .deqA_01[4] = 0xAC, .deqA_01[5] = 0xAC,	.deqA_01[6] = 0xAC,  .deqA_01[7] = 0xAC, .deqA_01[8] = 0xAC, .deqA_01[9] = 0xAC, .deqA_01[10] = 0xAC,	// BankA 0x30
				.deqA_02[0] = 0x78, .deqA_02[1] = 0x78, .deqA_02[2] = 0x78, .deqA_02[3] = 0x78, .deqA_02[4] = 0x78, .deqA_02[5] = 0x78,	.deqA_02[6] = 0x78,	 .deqA_02[7] = 0x78, .deqA_02[8] = 0x78, .deqA_02[9] = 0x78, .deqA_02[10] = 0x78,	// BankA 0x31
				.deqA_03[0] = 0x17, .deqA_03[1] = 0x17, .deqA_03[2] = 0x17, .deqA_03[3] = 0x17, .deqA_03[4] = 0x17, .deqA_03[5] = 0x17,	.deqA_03[6] = 0x17,	 .deqA_03[7] = 0x17, .deqA_03[8] = 0x17, .deqA_03[9] = 0x17, .deqA_03[10] = 0x17,	// BankA 0x32
				.deqA_04[0] = 0xC1, .deqA_04[1] = 0xC1, .deqA_04[2] = 0xC1, .deqA_04[3] = 0xC1, .deqA_04[4] = 0xC1, .deqA_04[5] = 0xC1, .deqA_04[6] = 0xC1,  .deqA_04[7] = 0xC1, .deqA_04[8] = 0xC1, .deqA_04[9] = 0xC1, .deqA_04[10] = 0xC1,	// BankA 0x33
				.deqA_05[0] = 0x40, .deqA_05[1] = 0x40, .deqA_05[2] = 0x40, .deqA_05[3] = 0x40, .deqA_05[4] = 0x40, .deqA_05[5] = 0x40, .deqA_05[6] = 0x40,  .deqA_05[7] = 0x40, .deqA_05[8] = 0x40, .deqA_05[9] = 0x40, .deqA_05[10] = 0x40,	// BankA 0x34
				.deqA_06[0] = 0x00, .deqA_06[1] = 0x00, .deqA_06[2] = 0x00, .deqA_06[3] = 0x00, .deqA_06[4] = 0x00, .deqA_06[5] = 0x00, .deqA_06[6] = 0x00,  .deqA_06[7] = 0x00, .deqA_06[8] = 0x00, .deqA_06[9] = 0x00, .deqA_06[10] = 0x00,	// BankA 0x35
				.deqA_07[0] = 0xC3, .deqA_07[1] = 0xC3, .deqA_07[2] = 0xC3, .deqA_07[3] = 0xC3, .deqA_07[4] = 0xC3, .deqA_07[5] = 0xC3, .deqA_07[6] = 0xC3,  .deqA_07[7] = 0xC3, .deqA_07[8] = 0xC3, .deqA_07[9] = 0xC3, .deqA_07[10] = 0xC3,	// BankA 0x36
				.deqA_08[0] = 0x0A, .deqA_08[1] = 0x0A, .deqA_08[2] = 0x0A, .deqA_08[3] = 0x0A, .deqA_08[4] = 0x0A, .deqA_08[5] = 0x0A, .deqA_08[6] = 0x0A,  .deqA_08[7] = 0x0A, .deqA_08[8] = 0x0A, .deqA_08[9] = 0x0A, .deqA_08[10] = 0x0A,	// BankA 0x37
				.deqA_09[0] = 0x00, .deqA_09[1] = 0x00, .deqA_09[2] = 0x00, .deqA_09[3] = 0x00, .deqA_09[4] = 0x00, .deqA_09[5] = 0x00, .deqA_09[6] = 0x00,  .deqA_09[7] = 0x00, .deqA_09[8] = 0x00, .deqA_09[9] = 0x00, .deqA_09[10] = 0x00,	// BankA 0x38
				.deqA_10[0] = 0x02, .deqA_10[1] = 0x02, .deqA_10[2] = 0x02, .deqA_10[3] = 0x02, .deqA_10[4] = 0x02, .deqA_10[5] = 0x02, .deqA_10[6] = 0x02,  .deqA_10[7] = 0x02, .deqA_10[8] = 0x02, .deqA_10[9] = 0x02, .deqA_10[10] = 0x02,	// BankA 0x39
				.deqA_11[0] = 0x00, .deqA_11[1] = 0x00, .deqA_11[2] = 0x00, .deqA_11[3] = 0x00, .deqA_11[4] = 0x00, .deqA_11[5] = 0x00, .deqA_11[6] = 0x00,  .deqA_11[7] = 0x00, .deqA_11[8] = 0x00, .deqA_11[9] = 0x00, .deqA_11[10] = 0x00,	// BankA 0x3a
				.deqA_12[0] = 0xB2, .deqA_12[1] = 0xB2, .deqA_12[2] = 0xB2, .deqA_12[3] = 0xB2, .deqA_12[4] = 0xB2, .deqA_12[5] = 0xB2, .deqA_12[6] = 0xB2,  .deqA_12[7] = 0xB2, .deqA_12[8] = 0xB2, .deqA_12[9] = 0xB2, .deqA_12[10] = 0xB2,	// BankA 0x3b
			},
			/* color */
			{
				.contrast[0] 		= 0x88, .contrast[1] 		= 0x88, .contrast[2] 		= 0x78, .contrast[3] 		= 0x88, .contrast[4] 		= 0x88, .contrast[5] 		= 0x7e, .contrast[6] 		= 0x78, .contrast[7] 		= 0x78, .contrast[8] 		= 0x74, .contrast[9] 		= 0x74, .contrast[10] 		= 0x74,
				.h_peaking[0] 		= 0x3f, .h_peaking[1] 		= 0x3f, .h_peaking[2] 		= 0x3f, .h_peaking[3] 		= 0x3f, .h_peaking[4] 		= 0x3f, .h_peaking[5] 		= 0x3f, .h_peaking[6] 		= 0x3f, .h_peaking[7] 		= 0x3f, .h_peaking[8] 		= 0x3f, .h_peaking[9] 		= 0x4f, .h_peaking[10] 		= 0x4f,
				.c_filter[0]		= 0x82, .c_filter[1] 		= 0x82, .c_filter[2]	 	= 0x82, .c_filter[3] 		= 0x82, .c_filter[4] 		= 0x92, .c_filter[5] 		= 0x92, .c_filter[6] 		= 0x92, .c_filter[7] 		= 0x92, .c_filter[8] 		= 0x92, .c_filter[9] 		= 0x92, .c_filter[10] 		= 0x92,

				.hue[0] 			= 0x00, .hue[1] 			= 0x00, .hue[2] 			= 0x00, .hue[3] 			= 0x00, .hue[4] 			= 0x00, .hue[5] 			= 0x00, .hue[6] 			= 0x00, .hue[7] 			= 0x00, .hue[8] 			= 0x00, .hue[9] 			= 0x00, .hue[10] 			= 0x00,
				.u_gain[0] 			= 0x00, .u_gain[1] 			= 0x00, .u_gain[2] 			= 0x00, .u_gain[3] 			= 0x00, .u_gain[4] 			= 0x00, .u_gain[5] 			= 0x00, .u_gain[6] 			= 0x00, .u_gain[7] 			= 0x00, .u_gain[8] 			= 0x00, .u_gain[9] 			= 0x00, .u_gain[10] 		= 0x00,
				.v_gain[0] 			= 0x00, .v_gain[1] 			= 0x00, .v_gain[2] 			= 0x00, .v_gain[3] 			= 0x00, .v_gain[4] 			= 0x00, .v_gain[5] 			= 0x00, .v_gain[6] 			= 0x00, .v_gain[7] 			= 0x00, .v_gain[8] 			= 0x00, .v_gain[9] 			= 0x00, .v_gain[10] 		= 0x00,
				.u_offset[0] 		= 0x00, .u_offset[1] 		= 0x00, .u_offset[2] 		= 0x00, .u_offset[3] 		= 0x00, .u_offset[4] 		= 0x00, .u_offset[5] 		= 0x00, .u_offset[6] 		= 0x00, .u_offset[7] 		= 0x00, .u_offset[8] 		= 0x00, .u_offset[9] 		= 0x00, .u_offset[10] 		= 0x00,
				.v_offset[0] 		= 0x00, .v_offset[1] 		= 0x00, .v_offset[2] 		= 0x00, .v_offset[3] 		= 0x00, .v_offset[4] 		= 0x00, .v_offset[5] 		= 0x00, .v_offset[6] 		= 0x00, .v_offset[7] 		= 0x00, .v_offset[8] 		= 0x00, .v_offset[9] 		= 0x00, .v_offset[10] 		= 0x00,

				.black_level[0] 	= 0x84, .black_level[1] 	= 0x84, .black_level[2] 	= 0x84, .black_level[3] 	= 0x84, .black_level[4] 	= 0x84, .black_level[5] 	= 0x86, .black_level[6] 	= 0x86, .black_level[7] 	= 0x8c, .black_level[8] 	= 0x8c, .black_level[9] 	= 0x90, .black_level[10] 	= 0x90,
				.acc_ref[0]			= 0x57, .acc_ref[1]			= 0x57, .acc_ref[2]			= 0x57, .acc_ref[3]			= 0x57, .acc_ref[4]			= 0x57, .acc_ref[5]			= 0x57, .acc_ref[6]			= 0x57, .acc_ref[7]			= 0x57, .acc_ref[8]			= 0x57, .acc_ref[9]			= 0x47, .acc_ref[10]		= 0x47,
				.cti_delay[0]		= 0x80, .cti_delay[1]		= 0x80, .cti_delay[2]		= 0x80, .cti_delay[3]		= 0x80, .cti_delay[4]		= 0x80, .cti_delay[5]		= 0x80, .cti_delay[6]		= 0x80, .cti_delay[7]		= 0x80, .cti_delay[8]		= 0x80, .cti_delay[9]		= 0x90, .cti_delay[10]		= 0x90,
				.sub_saturation[0] 	= 0xa8, .sub_saturation[1] 	= 0xab, .sub_saturation[2] 	= 0xb0, .sub_saturation[3] 	= 0xb0, .sub_saturation[4] 	= 0xa4, .sub_saturation[5] 	= 0xa0, .sub_saturation[6] 	= 0xa0, .sub_saturation[7] 	= 0xa0, .sub_saturation[8] 	= 0xa0, .sub_saturation[9] 	= 0x90, .sub_saturation[10] = 0x90,

				.burst_dec_a[0] 	= 0x2a, .burst_dec_a[1] 	= 0x2a, .burst_dec_a[2] 	= 0x2a, .burst_dec_a[3] 	= 0x2a, .burst_dec_a[4] 	= 0x2a, .burst_dec_a[5] 	= 0x2a, .burst_dec_a[6] 	= 0x2a, .burst_dec_a[7] 	= 0x2a, .burst_dec_a[8] 	= 0x2a, .burst_dec_a[9] 	= 0x2a, .burst_dec_a[10] 	= 0x2a,
				.burst_dec_b[0] 	= 0x00, .burst_dec_b[1] 	= 0x00, .burst_dec_b[2] 	= 0x00, .burst_dec_b[3] 	= 0x00, .burst_dec_b[4] 	= 0x00, .burst_dec_b[5] 	= 0x00, .burst_dec_b[6] 	= 0x00, .burst_dec_b[7] 	= 0x00, .burst_dec_b[8] 	= 0x00, .burst_dec_b[9] 	= 0x00, .burst_dec_b[10] 	= 0x00,
				.burst_dec_c[0] 	= 0x30, .burst_dec_c[1] 	= 0x30, .burst_dec_c[2] 	= 0x30, .burst_dec_c[3] 	= 0x30, .burst_dec_c[4] 	= 0x30, .burst_dec_c[5] 	= 0x30, .burst_dec_c[6] 	= 0x30, .burst_dec_c[7] 	= 0x30, .burst_dec_c[8] 	= 0x30, .burst_dec_c[9] 	= 0x30, .burst_dec_c[10] 	= 0x30,

				.c_option[0] 		= 0x80, .c_option[1] 		= 0x80, .c_option[2] 		= 0x80, .c_option[3] 		= 0x80, .c_option[4] 		= 0x90, .c_option[5] 		= 0x90, .c_option[6] 		= 0x90, .c_option[7] 		= 0x90, .c_option[8] 		= 0x90, .c_option[9] 		= 0x90, .c_option[10] 		= 0x90,

				.y_filter_b[0]		= 0x10, .y_filter_b[1]		= 0x10, .y_filter_b[2]		= 0x10, .y_filter_b[3]		= 0x10, .y_filter_b[4]		= 0x10, .y_filter_b[5]		= 0x10, .y_filter_b[6]		= 0x10, .y_filter_b[7]		= 0x10, .y_filter_b[8]		= 0x10, .y_filter_b[9]		= 0x10, .y_filter_b[10]		= 0x10,
				.y_filter_b_sel[0]	= 0x1e,	.y_filter_b_sel[1]	= 0x1e,	.y_filter_b_sel[2]	= 0x1e, .y_filter_b_sel[3]	= 0x1e, .y_filter_b_sel[4]	= 0x1e, .y_filter_b_sel[5]	= 0x1e, .y_filter_b_sel[6]	= 0x1e, .y_filter_b_sel[7]	= 0x1e, .y_filter_b_sel[8]	= 0x1e, .y_filter_b_sel[9]	= 0x1e, .y_filter_b_sel[10]	= 0x1e,
			},
			/* timing_a */
			{
#ifdef SUPPORT_720P_HDELAY_CONTROL_171226
			.h_delay_a[0] = 0x8d, .h_delay_a[1] = 0x8d, .h_delay_a[2] = 0x8d, .h_delay_a[3] = 0x8d, .h_delay_a[4] = 0x8d, .h_delay_a[5] = 0x8d, .h_delay_a[6] = 0x8d, .h_delay_a[7] = 0x8d, .h_delay_a[8] = 0x8d, .h_delay_a[9] = 0x8d, .h_delay_a[10] = 0x8d,
#else
				.h_delay_a[0] = 0xa0, .h_delay_a[1] = 0xa0, .h_delay_a[2] = 0x9e, .h_delay_a[3] = 0x9b, .h_delay_a[4] = 0x99, .h_delay_a[5] = 0x99, .h_delay_a[6] = 0x9b, .h_delay_a[7] = 0x98, .h_delay_a[8] = 0x98, .h_delay_a[9] = 0x98, .h_delay_a[10] = 0x98,
#endif
				.h_delay_b[0] = 0x00, .h_delay_b[1] = 0x00, .h_delay_b[2] = 0x00, .h_delay_b[3] = 0x00, .h_delay_b[4] = 0x00, .h_delay_b[5] = 0x00, .h_delay_b[6] = 0x00, .h_delay_b[7] = 0x00, .h_delay_b[8] = 0x00, .h_delay_b[9] = 0x00, .h_delay_b[10] = 0x00,
				.h_delay_c[0] = 0x00, .h_delay_c[1] = 0x00, .h_delay_c[2] = 0x00, .h_delay_c[3] = 0x00, .h_delay_c[4] = 0x00, .h_delay_c[5] = 0x00, .h_delay_c[6] = 0x00, .h_delay_c[7] = 0x00, .h_delay_c[8] = 0x00, .h_delay_c[9] = 0x00, .h_delay_c[10] = 0x00,
				.y_delay[0]   = 0x05, .y_delay[1]   = 0x05, .y_delay[2]   = 0x05, .y_delay[3]   = 0x05, .y_delay[4]   = 0x05, .y_delay[5] =   0x05, .y_delay[6] =   0x05, .y_delay[7] =   0x05, .y_delay[8] =   0x05, .y_delay[9] =   0x05, .y_delay[10] =   0x05,

			},
			/* clk */
			{
				.clk_adc[0] = 0x02, .clk_adc[1] = 0x02, .clk_adc[2] = 0x02, .clk_adc[3] = 0x02, .clk_adc[4] = 0x02, .clk_adc[5] = 0x02, .clk_adc[6] = 0x02, .clk_adc[7] = 0x02, .clk_adc[8] = 0x02, .clk_adc[9] = 0x02, .clk_adc[10] = 0x02,
				.clk_dec[0] = 0x40, .clk_dec[1] = 0x40, .clk_dec[2] = 0x40, .clk_dec[3] = 0x40, .clk_dec[4] = 0x40, .clk_dec[5] = 0x40, .clk_dec[6] = 0x40, .clk_dec[7] = 0x40, .clk_dec[8] = 0x40, .clk_dec[9] = 0x40, .clk_dec[10] = 0x40,
			},
			/* timing_b */
			{
	/*B9 0x96*/	.h_scaler1[0]  = 0x00, .h_scaler1[1]   = 0x00, .h_scaler1[2]   = 0x00, .h_scaler1[3]   = 0x00, .h_scaler1[4]   = 0x00, .h_scaler1[5]   = 0x00, .h_scaler1[6]   = 0x00, .h_scaler1[7]   = 0x00, .h_scaler1[8]   = 0x00, .h_scaler1[9]   = 0x00, .h_scaler1[10]   = 0x00,
	/*B9 0x97*/	.h_scaler2[0]  = 0x00, .h_scaler2[1]   = 0x00, .h_scaler2[2]   = 0x00, .h_scaler2[3]   = 0x00, .h_scaler2[4]   = 0x00, .h_scaler2[5]   = 0x00, .h_scaler2[6]   = 0x00, .h_scaler2[7]   = 0x00, .h_scaler2[8]   = 0x00, .h_scaler2[9]   = 0x00, .h_scaler2[10]   = 0x00,
	/*B9 0x98*/	.h_scaler3[0]  = 0x00, .h_scaler3[1]   = 0x00, .h_scaler3[2]   = 0x00, .h_scaler3[3]   = 0x00, .h_scaler3[4]   = 0x00, .h_scaler3[5]   = 0x00, .h_scaler3[6]   = 0x00, .h_scaler3[7]   = 0x00, .h_scaler3[8]   = 0x00, .h_scaler3[9]   = 0x00, .h_scaler3[10]   = 0x00,
	/*B9 0x99*/	.h_scaler4[0]  = 0x00, .h_scaler4[1]   = 0x00, .h_scaler4[2]   = 0x00, .h_scaler4[3]   = 0x00, .h_scaler4[4]   = 0x00, .h_scaler4[5]   = 0x00, .h_scaler4[6]   = 0x00, .h_scaler4[7]   = 0x00, .h_scaler4[8]   = 0x00, .h_scaler4[9]   = 0x00, .h_scaler4[10]   = 0x00,
	/*B9 0x9a*/	.h_scaler5[0]  = 0x00, .h_scaler5[1]   = 0x00, .h_scaler5[2]   = 0x00, .h_scaler5[3]   = 0x00, .h_scaler5[4]   = 0x00, .h_scaler5[5]   = 0x00, .h_scaler5[6]   = 0x00, .h_scaler5[7]   = 0x00, .h_scaler5[8]   = 0x00, .h_scaler5[9]   = 0x00, .h_scaler5[10]   = 0x00,
	/*B9 0x9b*/	.h_scaler6[0]  = 0x00, .h_scaler6[1]   = 0x00, .h_scaler6[2]   = 0x00, .h_scaler6[3]   = 0x00, .h_scaler6[4]   = 0x00, .h_scaler6[5]   = 0x00, .h_scaler6[6]   = 0x00, .h_scaler6[7]   = 0x00, .h_scaler6[8]   = 0x00, .h_scaler6[9]   = 0x00, .h_scaler6[10]   = 0x00,
	/*B9 0x9c*/	.h_scaler7[0]  = 0x00, .h_scaler7[1]   = 0x00, .h_scaler7[2]   = 0x00, .h_scaler7[3]   = 0x00, .h_scaler7[4]   = 0x00, .h_scaler7[5]   = 0x00, .h_scaler7[6]   = 0x00, .h_scaler7[7]   = 0x00, .h_scaler7[8]   = 0x00, .h_scaler7[9]   = 0x00, .h_scaler7[10]   = 0x00,
	/*B9 0x9d*/	.h_scaler8[0]  = 0x00, .h_scaler8[1]   = 0x00, .h_scaler8[2]   = 0x00, .h_scaler8[3]   = 0x00, .h_scaler8[4]   = 0x00, .h_scaler8[5]   = 0x00, .h_scaler8[6]   = 0x00, .h_scaler8[7]   = 0x00, .h_scaler8[8]   = 0x00, .h_scaler8[9]   = 0x00, .h_scaler8[10]   = 0x00,
	/*B9 0x9e*/	.h_scaler9[0]  = 0x00, .h_scaler9[1]   = 0x00, .h_scaler9[2]   = 0x00, .h_scaler9[3]   = 0x00, .h_scaler9[4]   = 0x00, .h_scaler9[5]   = 0x00, .h_scaler9[6]   = 0x00, .h_scaler9[7]   = 0x00, .h_scaler9[8]   = 0x00, .h_scaler9[9]   = 0x00, .h_scaler9[10]   = 0x00,


	/*B9 0x40*/	.pn_auto[0]    	= 0x00, .pn_auto[1]		= 0x00, .pn_auto[2]    	= 0x00, .pn_auto[3]    	= 0x00, .pn_auto[4]    	= 0x00, .pn_auto[5]    	= 0x00, .pn_auto[6]		= 0x00, .pn_auto[7]    	= 0x00, .pn_auto[8]    	= 0x00, .pn_auto[9]    	= 0x00, .pn_auto[10]    	= 0x00,

	/*B5 0x90*/	.comb_mode[0]   = 0x01, .comb_mode[1]	= 0x01, .comb_mode[2]   = 0x01, .comb_mode[3]   = 0x01, .comb_mode[4]  	= 0x01, .comb_mode[5]   = 0x01, .comb_mode[6]	= 0x01, .comb_mode[7]   = 0x01, .comb_mode[8]   = 0x01, .comb_mode[9]  	= 0x01, .comb_mode[10]   = 0x01,
	/*B9 0xb9*/	.h_pll_op_a[0]  = 0x72, .h_pll_op_a[1]  = 0x72, .h_pll_op_a[2]  = 0x72, .h_pll_op_a[3]  = 0x72, .h_pll_op_a[4]  = 0x72, .h_pll_op_a[5]  = 0x72, .h_pll_op_a[6]  = 0x72, .h_pll_op_a[7]  = 0x72, .h_pll_op_a[8]  = 0x72, .h_pll_op_a[9]  = 0x72, .h_pll_op_a[10]  = 0x72,
	/*B9 0x57*/	.mem_path[0]	= 0x00, .mem_path[1]	= 0x00, .mem_path[2]	= 0x00, .mem_path[3]	= 0x00, .mem_path[4]	= 0x00, .mem_path[5]	= 0x00, .mem_path[6]	= 0x00, .mem_path[7]	= 0x00, .mem_path[8]	= 0x00, .mem_path[9]	= 0x00, .mem_path[10]	= 0x00,
				.fsc_lock_speed[0] = 0xdc, .fsc_lock_speed[1] = 0xdc, .fsc_lock_speed[2] = 0xdc, .fsc_lock_speed[3] = 0xdc, .fsc_lock_speed[4] = 0xdc, .fsc_lock_speed[5] = 0xdc, .fsc_lock_speed[6] = 0xdc, .fsc_lock_speed[7] = 0xdc, .fsc_lock_speed[8] = 0xdc, .fsc_lock_speed[9] = 0xdc, .fsc_lock_speed[10] = 0xdc,

	/*B0 0x81*/	.format_set1[0] = 0x0c, .format_set1[1] = 0x0c, .format_set1[2] = 0x0c, .format_set1[3] = 0x0c, .format_set1[4] = 0x0c, .format_set1[5] = 0x0c, .format_set1[6] = 0x0c, .format_set1[7] = 0x0c, .format_set1[8] = 0x0c, .format_set1[9] = 0x0c, .format_set1[10] = 0x0c,
	/*B0 0x85*/	.format_set2[0] = 0x00, .format_set2[1] = 0x00, .format_set2[2] = 0x00, .format_set2[3] = 0x00, .format_set2[4] = 0x00, .format_set2[5] = 0x00, .format_set2[6] = 0x00, .format_set2[7] = 0x00, .format_set2[8] = 0x00, .format_set2[9] = 0x00, .format_set2[10] = 0x00,

	/*B0 0x64*/ .v_delay[0]     = 0x21, .v_delay[1]     = 0x21, .v_delay[2]     = 0x21, .v_delay[3]     = 0x21, .v_delay[4]     = 0x21, .v_delay[5]     = 0x21, .v_delay[6]     = 0x21, .v_delay[7]     = 0x21, .v_delay[8]     = 0x21, .v_delay[9]     = 0x21, .v_delay[10]     = 0x21,
			},
		},

	[ CVI_HD_25P ] = /* o */
	{
		/* base */
		{
			.eq_bypass[0] 	= 0x22, .eq_bypass[1] 	= 0x22, .eq_bypass[2] 	= 0x22, .eq_bypass[3] 	= 0x22, .eq_bypass[4] 	= 0x22, .eq_bypass[5] 	= 0x22, .eq_bypass[6] 	= 0x22, .eq_bypass[7] 	= 0x22, .eq_bypass[8] 	= 0x22, .eq_bypass[9] 	= 0x22, .eq_bypass[10] 	 = 0x22,  // Bank5 0x30
			.eq_band_sel[0] = 0x77, .eq_band_sel[1] = 0x67, .eq_band_sel[2] = 0x57, .eq_band_sel[3] = 0x57, .eq_band_sel[4] = 0x57, .eq_band_sel[5] = 0x47, .eq_band_sel[6] = 0x37, .eq_band_sel[7] = 0x27, .eq_band_sel[8] = 0x17, .eq_band_sel[9] = 0x17, .eq_band_sel[10] = 0x07, // BankA 0x31
			.eq_gain_sel[0] = 0x78, .eq_gain_sel[1] = 0x78, .eq_gain_sel[2] = 0x78, .eq_gain_sel[3] = 0x7f, .eq_gain_sel[4] = 0x7f, .eq_gain_sel[5] = 0x7f, .eq_gain_sel[6] = 0x7f, .eq_gain_sel[7] = 0x7f, .eq_gain_sel[8] = 0x7f, .eq_gain_sel[9] = 0x7f, .eq_gain_sel[10] = 0x7f, // BankA 0x32
			.deq_a_on[0] 	= 0x00, .deq_a_on[1] 	= 0x01, .deq_a_on[2] 	= 0x01, .deq_a_on[3] 	= 0x01, .deq_a_on[4] 	= 0x01, .deq_a_on[5] 	= 0x01, .deq_a_on[6] 	= 0x01, .deq_a_on[7] 	= 0x01, .deq_a_on[8] 	= 0x01, .deq_a_on[9] 	= 0x01, .deq_a_on[10] 	 = 0x01, // BankA 0x33
			.deq_a_sel[0] 	= 0x00, .deq_a_sel[1] 	= 0x91, .deq_a_sel[2] 	= 0x92, .deq_a_sel[3] 	= 0x93, .deq_a_sel[4] 	= 0x93, .deq_a_sel[5] 	= 0x93, .deq_a_sel[6] 	= 0x93, .deq_a_sel[7] 	= 0x93, .deq_a_sel[8] 	= 0x93, .deq_a_sel[9] 	= 0x93, .deq_a_sel[10] 	 = 0x92, // BankA 0x34
			.deq_b_sel[0] 	= 0x00, .deq_b_sel[1] 	= 0x00, .deq_b_sel[2] 	= 0x00, .deq_b_sel[3] 	= 0x00, .deq_b_sel[4] 	= 0x00, .deq_b_sel[5] 	= 0x00, .deq_b_sel[6] 	= 0x00, .deq_b_sel[7] 	= 0x00, .deq_b_sel[8] 	= 0x00, .deq_b_sel[9] 	= 0x00, .deq_b_sel[10] 	 = 0x00, // BankA 0x35
		},
		/* coeff */
		{
			.deqA_01[0] = 0xAC, .deqA_01[1] = 0xAC, .deqA_01[2] = 0xAC, .deqA_01[3] = 0xAC, .deqA_01[4] = 0xAC, .deqA_01[5] = 0xAC,	.deqA_01[6] = 0xAC,  .deqA_01[7] = 0xAC, .deqA_01[8] = 0xAC, .deqA_01[9] = 0xAC, .deqA_01[10] = 0xAC,	// BankA 0x30
			.deqA_02[0] = 0x78, .deqA_02[1] = 0x78, .deqA_02[2] = 0x78, .deqA_02[3] = 0x78, .deqA_02[4] = 0x78, .deqA_02[5] = 0x78,	.deqA_02[6] = 0x78,	 .deqA_02[7] = 0x78, .deqA_02[8] = 0x78, .deqA_02[9] = 0x78, .deqA_02[10] = 0x78,	// BankA 0x31
			.deqA_03[0] = 0x17, .deqA_03[1] = 0x17, .deqA_03[2] = 0x17, .deqA_03[3] = 0x17, .deqA_03[4] = 0x17, .deqA_03[5] = 0x17,	.deqA_03[6] = 0x17,	 .deqA_03[7] = 0x17, .deqA_03[8] = 0x17, .deqA_03[9] = 0x17, .deqA_03[10] = 0x17,	// BankA 0x32
			.deqA_04[0] = 0xC1, .deqA_04[1] = 0xC1, .deqA_04[2] = 0xC1, .deqA_04[3] = 0xC1, .deqA_04[4] = 0xC1, .deqA_04[5] = 0xC1, .deqA_04[6] = 0xC1,  .deqA_04[7] = 0xC1, .deqA_04[8] = 0xC1, .deqA_04[9] = 0xC1, .deqA_04[10] = 0xC1,	// BankA 0x33
			.deqA_05[0] = 0x40, .deqA_05[1] = 0x40, .deqA_05[2] = 0x40, .deqA_05[3] = 0x40, .deqA_05[4] = 0x40, .deqA_05[5] = 0x40, .deqA_05[6] = 0x40,  .deqA_05[7] = 0x40, .deqA_05[8] = 0x40, .deqA_05[9] = 0x40, .deqA_05[10] = 0x40,	// BankA 0x34
			.deqA_06[0] = 0x00, .deqA_06[1] = 0x00, .deqA_06[2] = 0x00, .deqA_06[3] = 0x00, .deqA_06[4] = 0x00, .deqA_06[5] = 0x00, .deqA_06[6] = 0x00,  .deqA_06[7] = 0x00, .deqA_06[8] = 0x00, .deqA_06[9] = 0x00, .deqA_06[10] = 0x00,	// BankA 0x35
			.deqA_07[0] = 0xC3, .deqA_07[1] = 0xC3, .deqA_07[2] = 0xC3, .deqA_07[3] = 0xC3, .deqA_07[4] = 0xC3, .deqA_07[5] = 0xC3, .deqA_07[6] = 0xC3,  .deqA_07[7] = 0xC3, .deqA_07[8] = 0xC3, .deqA_07[9] = 0xC3, .deqA_07[10] = 0xC3,	// BankA 0x36
			.deqA_08[0] = 0x0A, .deqA_08[1] = 0x0A, .deqA_08[2] = 0x0A, .deqA_08[3] = 0x0A, .deqA_08[4] = 0x0A, .deqA_08[5] = 0x0A, .deqA_08[6] = 0x0A,  .deqA_08[7] = 0x0A, .deqA_08[8] = 0x0A, .deqA_08[9] = 0x0A, .deqA_08[10] = 0x0A,	// BankA 0x37
			.deqA_09[0] = 0x00, .deqA_09[1] = 0x00, .deqA_09[2] = 0x00, .deqA_09[3] = 0x00, .deqA_09[4] = 0x00, .deqA_09[5] = 0x00, .deqA_09[6] = 0x00,  .deqA_09[7] = 0x00, .deqA_09[8] = 0x00, .deqA_09[9] = 0x00, .deqA_09[10] = 0x00,	// BankA 0x38
			.deqA_10[0] = 0x02, .deqA_10[1] = 0x02, .deqA_10[2] = 0x02, .deqA_10[3] = 0x02, .deqA_10[4] = 0x02, .deqA_10[5] = 0x02, .deqA_10[6] = 0x02,  .deqA_10[7] = 0x02, .deqA_10[8] = 0x02, .deqA_10[9] = 0x02, .deqA_10[10] = 0x02,	// BankA 0x39
			.deqA_11[0] = 0x00, .deqA_11[1] = 0x00, .deqA_11[2] = 0x00, .deqA_11[3] = 0x00, .deqA_11[4] = 0x00, .deqA_11[5] = 0x00, .deqA_11[6] = 0x00,  .deqA_11[7] = 0x00, .deqA_11[8] = 0x00, .deqA_11[9] = 0x00, .deqA_11[10] = 0x00,	// BankA 0x3a
			.deqA_12[0] = 0xB2, .deqA_12[1] = 0xB2, .deqA_12[2] = 0xB2, .deqA_12[3] = 0xB2, .deqA_12[4] = 0xB2, .deqA_12[5] = 0xB2, .deqA_12[6] = 0xB2,  .deqA_12[7] = 0xB2, .deqA_12[8] = 0xB2, .deqA_12[9] = 0xB2, .deqA_12[10] = 0xB2,	// BankA 0x3b
		},
		/* color */
		{
			.contrast[0] 		= 0x88, .contrast[1] 		= 0x8c, .contrast[2] 		= 0x8a, .contrast[3] 		= 0x87, .contrast[4] 		= 0x85, .contrast[5] 		= 0x84, .contrast[6] 		= 0x80, .contrast[7] 		= 0x80, .contrast[8] 		= 0x79, .contrast[9] 		= 0x72, .contrast[10] 		= 0x72,
			.h_peaking[0] 		= 0x00, .h_peaking[1] 		= 0x00, .h_peaking[2] 		= 0x00, .h_peaking[3] 		= 0x00, .h_peaking[4] 		= 0x00, .h_peaking[5] 		= 0x00, .h_peaking[6] 		= 0x00, .h_peaking[7] 		= 0x3f, .h_peaking[8] 		= 0x3f, .h_peaking[9] 		= 0x3f, .h_peaking[10] 		= 0x3f,
			.c_filter[0]		= 0x82, .c_filter[1] 		= 0x92, .c_filter[2]	 	= 0x92, .c_filter[3] 		= 0x92, .c_filter[4] 		= 0xa2, .c_filter[5] 		= 0xa2, .c_filter[6] 		= 0xb2, .c_filter[7] 		= 0xb2, .c_filter[8] 		= 0xb2, .c_filter[9] 		= 0xb2, .c_filter[10] 		= 0xb2,
			.hue[0] 			= 0x00, .hue[1] 			= 0x00, .hue[2] 			= 0x00, .hue[3] 			= 0x00, .hue[4] 			= 0x00, .hue[5] 			= 0x00, .hue[6] 			= 0x00, .hue[7] 			= 0x00, .hue[8] 			= 0x00, .hue[9] 			= 0x00, .hue[10] 			= 0x00,
			.u_gain[0] 			= 0x00, .u_gain[1] 			= 0x00, .u_gain[2] 			= 0x00, .u_gain[3] 			= 0x00, .u_gain[4] 			= 0x00, .u_gain[5] 			= 0x00, .u_gain[6] 			= 0x00, .u_gain[7] 			= 0x00, .u_gain[8] 			= 0x00, .u_gain[9] 			= 0x00, .u_gain[10] 		= 0x00,
			.v_gain[0] 			= 0x00, .v_gain[1] 			= 0x00, .v_gain[2] 			= 0x00, .v_gain[3] 			= 0x00, .v_gain[4] 			= 0x00, .v_gain[5] 			= 0x00, .v_gain[6] 			= 0x00, .v_gain[7] 			= 0x00, .v_gain[8] 			= 0x00, .v_gain[9] 			= 0x00, .v_gain[10] 		= 0x00,
			.u_offset[0] 		= 0x00, .u_offset[1] 		= 0x00, .u_offset[2] 		= 0x00, .u_offset[3] 		= 0x00, .u_offset[4] 		= 0x00, .u_offset[5] 		= 0x00, .u_offset[6] 		= 0x00, .u_offset[7] 		= 0x00, .u_offset[8] 		= 0x00, .u_offset[9] 		= 0x00, .u_offset[10] 		= 0x00,
			.v_offset[0] 		= 0x00, .v_offset[1] 		= 0x00, .v_offset[2] 		= 0x00, .v_offset[3] 		= 0x00, .v_offset[4] 		= 0x00, .v_offset[5] 		= 0x00, .v_offset[6] 		= 0x00, .v_offset[7] 		= 0x00, .v_offset[8] 		= 0x00, .v_offset[9] 		= 0x00, .v_offset[10] 		= 0x00,

			.black_level[0] 	= 0x84, .black_level[1] 	= 0x86, .black_level[2] 	= 0x84, .black_level[3] 	= 0x84, .black_level[4] 	= 0x86, .black_level[5] 	= 0x88, .black_level[6] 	= 0x8a, .black_level[7] 	= 0x90, .black_level[8] 	= 0x93, .black_level[9] 	= 0x96, .black_level[10] 	= 0x96,
			.acc_ref[0]			= 0x57, .acc_ref[1]			= 0x57, .acc_ref[2]			= 0x57, .acc_ref[3]			= 0x57, .acc_ref[4]			= 0x57, .acc_ref[5]			= 0x57, .acc_ref[6]			= 0x57, .acc_ref[7]			= 0x37, .acc_ref[8]			= 0x20, .acc_ref[9]			= 0x20, .acc_ref[10]		= 0x57,
			.cti_delay[0]		= 0x80, .cti_delay[1]		= 0x80, .cti_delay[2]		= 0x80, .cti_delay[3]		= 0x80, .cti_delay[4]		= 0x80, .cti_delay[5]		= 0x80, .cti_delay[6]		= 0x80, .cti_delay[7]		= 0x80, .cti_delay[8]		= 0x80, .cti_delay[9]		= 0x80, .cti_delay[10]		= 0x80,
			.sub_saturation[0] 	= 0xa8, .sub_saturation[1] 	= 0xaa, .sub_saturation[2] 	= 0xaa, .sub_saturation[3] 	= 0xac, .sub_saturation[4] 	= 0xa8, .sub_saturation[5] 	= 0xa6, .sub_saturation[6] 	= 0x98, .sub_saturation[7] 	= 0xa0, .sub_saturation[8] 	= 0xa0, .sub_saturation[9] 	= 0x50, .sub_saturation[10] = 0x50,

			.burst_dec_a[0] 	= 0x2a, .burst_dec_a[1] 	= 0x2a, .burst_dec_a[2] 	= 0x2a, .burst_dec_a[3] 	= 0x2a, .burst_dec_a[4] 	= 0x2a, .burst_dec_a[5] 	= 0x2a, .burst_dec_a[6] 	= 0x2a, .burst_dec_a[7] 	= 0x2a, .burst_dec_a[8] 	= 0x2a, .burst_dec_a[9] 	= 0x2a, .burst_dec_a[10] 	= 0x2a,
			.burst_dec_b[0] 	= 0x00, .burst_dec_b[1] 	= 0x00, .burst_dec_b[2] 	= 0x00, .burst_dec_b[3] 	= 0x00, .burst_dec_b[4] 	= 0x00, .burst_dec_b[5] 	= 0x00, .burst_dec_b[6] 	= 0x00, .burst_dec_b[7] 	= 0x00, .burst_dec_b[8] 	= 0x00, .burst_dec_b[9] 	= 0x00, .burst_dec_b[10] 	= 0x00,
			.burst_dec_c[0] 	= 0x00, .burst_dec_c[1] 	= 0x00, .burst_dec_c[2] 	= 0x00, .burst_dec_c[3] 	= 0x00, .burst_dec_c[4] 	= 0x00, .burst_dec_c[5] 	= 0x00, .burst_dec_c[6] 	= 0x00, .burst_dec_c[7] 	= 0x00, .burst_dec_c[8] 	= 0x00, .burst_dec_c[9] 	= 0x00, .burst_dec_c[10] 	= 0x00,

			.c_option[0] 		= 0x80, .c_option[1] 		= 0x80, .c_option[2] 		= 0x80, .c_option[3] 		= 0x80, .c_option[4] 		= 0xa0, .c_option[5] 		= 0xa0, .c_option[6] 		= 0xb0, .c_option[7] 		= 0xb0, .c_option[8] 		= 0xb0, .c_option[9] 		= 0xb0, .c_option[10] 		= 0xb0,

			.y_filter_b[0]		= 0x10, .y_filter_b[1]		= 0x10, .y_filter_b[2]		= 0x10, .y_filter_b[3]		= 0x10, .y_filter_b[4]		= 0x10, .y_filter_b[5]		= 0x10, .y_filter_b[6]		= 0x10, .y_filter_b[7]		= 0x10, .y_filter_b[8]		= 0x10, .y_filter_b[9]		= 0x10, .y_filter_b[10]		= 0x10,
			.y_filter_b_sel[0]	= 0x1e,	.y_filter_b_sel[1]	= 0x1e,	.y_filter_b_sel[2]	= 0x1e, .y_filter_b_sel[3]	= 0x1e, .y_filter_b_sel[4]	= 0x1e, .y_filter_b_sel[5]	= 0x1e, .y_filter_b_sel[6]	= 0x1e, .y_filter_b_sel[7]	= 0x1e, .y_filter_b_sel[8]	= 0x1e, .y_filter_b_sel[9]	= 0x1e, .y_filter_b_sel[10]	= 0x1e,
		},
		/* timing_a */
		{
			.h_delay_a[0] = 0x60, .h_delay_a[1] = 0x60, .h_delay_a[2] = 0x5e, .h_delay_a[3] = 0x5b, .h_delay_a[4] = 0x59, .h_delay_a[5] = 0x59, .h_delay_a[6] = 0x5b, .h_delay_a[7] = 0x58, .h_delay_a[8] = 0x58, .h_delay_a[9] = 0x58, .h_delay_a[10] = 0x58,
			.h_delay_b[0] = 0x00, .h_delay_b[1] = 0x00, .h_delay_b[2] = 0x00, .h_delay_b[3] = 0x00, .h_delay_b[4] = 0x00, .h_delay_b[5] = 0x00, .h_delay_b[6] = 0x00, .h_delay_b[7] = 0x00, .h_delay_b[8] = 0x00, .h_delay_b[9] = 0x00, .h_delay_b[10] = 0x00,
			.h_delay_c[0] = 0x00, .h_delay_c[1] = 0x00, .h_delay_c[2] = 0x00, .h_delay_c[3] = 0x00, .h_delay_c[4] = 0x00, .h_delay_c[5] = 0x00, .h_delay_c[6] = 0x00, .h_delay_c[7] = 0x00, .h_delay_c[8] = 0x00, .h_delay_c[9] = 0x00, .h_delay_c[10] = 0x00,
			.y_delay[0]   = 0x05, .y_delay[1]   = 0x05, .y_delay[2]   = 0x05, .y_delay[3]   = 0x05, .y_delay[4]   = 0x05, .y_delay[5] =   0x05, .y_delay[6] =   0x05, .y_delay[7] =   0x05, .y_delay[8] =   0x05, .y_delay[9] =   0x05, .y_delay[10] =   0x05,

		},
		/* clk */
		{
			.clk_adc[0] = 0x02, .clk_adc[1] = 0x02, .clk_adc[2] = 0x02, .clk_adc[3] = 0x02, .clk_adc[4] = 0x02, .clk_adc[5] = 0x02, .clk_adc[6] = 0x02, .clk_adc[7] = 0x02, .clk_adc[8] = 0x02, .clk_adc[9] = 0x02, .clk_adc[10] = 0x02,
			.clk_dec[0] = 0x40, .clk_dec[1] = 0x40, .clk_dec[2] = 0x40, .clk_dec[3] = 0x40, .clk_dec[4] = 0x40, .clk_dec[5] = 0x40, .clk_dec[6] = 0x40, .clk_dec[7] = 0x40, .clk_dec[8] = 0x40, .clk_dec[9] = 0x40, .clk_dec[10] = 0x40,
		},
		/* timing_b */
		{
/*B9 0x96*/	.h_scaler1[0]  = 0x01, .h_scaler1[1]   = 0x01, .h_scaler1[2]   = 0x01, .h_scaler1[3]   = 0x01, .h_scaler1[4]   = 0x01, .h_scaler1[5]   = 0x01, .h_scaler1[6]   = 0x01, .h_scaler1[7]   = 0x01, .h_scaler1[8]   = 0x01, .h_scaler1[9]   = 0x01, .h_scaler1[10]   = 0x01,
/*B9 0x97*/	.h_scaler2[0]  = 0x29, .h_scaler2[1]   = 0x29, .h_scaler2[2]   = 0x29, .h_scaler2[3]   = 0x29, .h_scaler2[4]   = 0x29, .h_scaler2[5]   = 0x29, .h_scaler2[6]   = 0x29, .h_scaler2[7]   = 0x29, .h_scaler2[8]   = 0x29, .h_scaler2[9]   = 0x29, .h_scaler2[10]   = 0x29,
/*B9 0x98*/	.h_scaler3[0]  = 0xc0, .h_scaler3[1]   = 0xc0, .h_scaler3[2]   = 0xc0, .h_scaler3[3]   = 0xc0, .h_scaler3[4]   = 0xc0, .h_scaler3[5]   = 0xc0, .h_scaler3[6]   = 0xc0, .h_scaler3[7]   = 0xc0, .h_scaler3[8]   = 0xc0, .h_scaler3[9]   = 0xc0, .h_scaler3[10]   = 0xc0,
/*B9 0x99*/	.h_scaler4[0]  = 0xc1, .h_scaler4[1]   = 0xc1, .h_scaler4[2]   = 0xc1, .h_scaler4[3]   = 0xc1, .h_scaler4[4]   = 0xc1, .h_scaler4[5]   = 0xc1, .h_scaler4[6]   = 0xc1, .h_scaler4[7]   = 0xc1, .h_scaler4[8]   = 0xc1, .h_scaler4[9]   = 0xc1, .h_scaler4[10]   = 0xc1,
/*B9 0x9a*/	.h_scaler5[0]  = 0x00, .h_scaler5[1]   = 0x00, .h_scaler5[2]   = 0x00, .h_scaler5[3]   = 0x00, .h_scaler5[4]   = 0x00, .h_scaler5[5]   = 0x00, .h_scaler5[6]   = 0x00, .h_scaler5[7]   = 0x00, .h_scaler5[8]   = 0x00, .h_scaler5[9]   = 0x00, .h_scaler5[10]   = 0x00,
/*B9 0x9b*/	.h_scaler6[0]  = 0x00, .h_scaler6[1]   = 0x00, .h_scaler6[2]   = 0x00, .h_scaler6[3]   = 0x00, .h_scaler6[4]   = 0x00, .h_scaler6[5]   = 0x00, .h_scaler6[6]   = 0x00, .h_scaler6[7]   = 0x00, .h_scaler6[8]   = 0x00, .h_scaler6[9]   = 0x00, .h_scaler6[10]   = 0x00,
/*B9 0x9c*/	.h_scaler7[0]  = 0x00, .h_scaler7[1]   = 0x00, .h_scaler7[2]   = 0x00, .h_scaler7[3]   = 0x00, .h_scaler7[4]   = 0x00, .h_scaler7[5]   = 0x00, .h_scaler7[6]   = 0x00, .h_scaler7[7]   = 0x00, .h_scaler7[8]   = 0x00, .h_scaler7[9]   = 0x00, .h_scaler7[10]   = 0x00,
/*B9 0x9d*/	.h_scaler8[0]  = 0x00, .h_scaler8[1]   = 0x00, .h_scaler8[2]   = 0x00, .h_scaler8[3]   = 0x00, .h_scaler8[4]   = 0x00, .h_scaler8[5]   = 0x00, .h_scaler8[6]   = 0x00, .h_scaler8[7]   = 0x00, .h_scaler8[8]   = 0x00, .h_scaler8[9]   = 0x00, .h_scaler8[10]   = 0x00,
/*B9 0x9e*/	.h_scaler9[0]  = 0x00, .h_scaler9[1]   = 0x00, .h_scaler9[2]   = 0x00, .h_scaler9[3]   = 0x00, .h_scaler9[4]   = 0x00, .h_scaler9[5]   = 0x00, .h_scaler9[6]   = 0x00, .h_scaler9[7]   = 0x00, .h_scaler9[8]   = 0x00, .h_scaler9[9]   = 0x00, .h_scaler9[10]   = 0x00,


/*B9 0x40*/	.pn_auto[0]    	= 0x00, .pn_auto[1]		= 0x00, .pn_auto[2]    	= 0x00, .pn_auto[3]    	= 0x00, .pn_auto[4]    	= 0x00, .pn_auto[5]    	= 0x00, .pn_auto[6]		= 0x00, .pn_auto[7]    	= 0x00, .pn_auto[8]    	= 0x00, .pn_auto[9]    	= 0x00, .pn_auto[10]    	= 0x00,

/*B5 0x90*/	.comb_mode[0]   = 0x05, .comb_mode[1]	= 0x05, .comb_mode[2]   = 0x05, .comb_mode[3]   = 0x05, .comb_mode[4]  	= 0x05, .comb_mode[5]   = 0x05, .comb_mode[6]	= 0x05, .comb_mode[7]   = 0x05, .comb_mode[8]   = 0x05, .comb_mode[9]  	= 0x05, .comb_mode[10]   = 0x05,
/*B9 0xb9*/	.h_pll_op_a[0]  = 0x72, .h_pll_op_a[1]  = 0x72, .h_pll_op_a[2]  = 0x72, .h_pll_op_a[3]  = 0x72, .h_pll_op_a[4]  = 0x72, .h_pll_op_a[5]  = 0x72, .h_pll_op_a[6]  = 0x72, .h_pll_op_a[7]  = 0x72, .h_pll_op_a[8]  = 0x72, .h_pll_op_a[9]  = 0x72, .h_pll_op_a[10]  = 0x72,
/*B9 0x57*/	.mem_path[0]	= 0x10, .mem_path[1]	= 0x10, .mem_path[2]	= 0x10, .mem_path[3]	= 0x10, .mem_path[4]	= 0x10, .mem_path[5]	= 0x10, .mem_path[6]	= 0x10, .mem_path[7]	= 0x10, .mem_path[8]	= 0x10, .mem_path[9]	= 0x10, .mem_path[10]	 = 0x10,
			.fsc_lock_speed[0] = 0xdc, .fsc_lock_speed[1] = 0xdc, .fsc_lock_speed[2] = 0xdc, .fsc_lock_speed[3] = 0xdc, .fsc_lock_speed[4] = 0xdc, .fsc_lock_speed[5] = 0xdc, .fsc_lock_speed[6] = 0xdc, .fsc_lock_speed[7] = 0xdc, .fsc_lock_speed[8] = 0xdc, .fsc_lock_speed[9] = 0xdc, .fsc_lock_speed[10] = 0xdc,

/*B0 0x81*/	.format_set1[0] = 0x07, .format_set1[1] = 0x07, .format_set1[2] = 0x07, .format_set1[3] = 0x07, .format_set1[4] = 0x07, .format_set1[5] = 0x07, .format_set1[6] = 0x07, .format_set1[7] = 0x07, .format_set1[8] = 0x07, .format_set1[9] = 0x07, .format_set1[10] = 0x07,
/*B0 0x85*/	.format_set2[0] = 0x02, .format_set2[1] = 0x02, .format_set2[2] = 0x02, .format_set2[3] = 0x02, .format_set2[4] = 0x02, .format_set2[5] = 0x02, .format_set2[6] = 0x02, .format_set2[7] = 0x02, .format_set2[8] = 0x02, .format_set2[9] = 0x02, .format_set2[10] = 0x02,

/*B0 0x64*/ .v_delay[0]     = 0x21, .v_delay[1]     = 0x21, .v_delay[2]     = 0x21, .v_delay[3]     = 0x21, .v_delay[4]     = 0x21, .v_delay[5]     = 0x21, .v_delay[6]     = 0x21, .v_delay[7]     = 0x21, .v_delay[8]     = 0x21, .v_delay[9]     = 0x21, .v_delay[10]     = 0x21,
		},
	},
	[ CVI_HD_30P ] = /* o */
	{
	/* base */
		{
			.eq_bypass[0] 	= 0x22, .eq_bypass[1] 	= 0x22, .eq_bypass[2] 	= 0x22, .eq_bypass[3] 	= 0x22, .eq_bypass[4] 	= 0x22, .eq_bypass[5] 	= 0x22, .eq_bypass[6] 	= 0x22, .eq_bypass[7] 	= 0x22, .eq_bypass[8] 	= 0x22, .eq_bypass[9] 	= 0x22, .eq_bypass[10] 	 = 0x22,  // Bank5 0x30
			.eq_band_sel[0] = 0x77, .eq_band_sel[1] = 0x67, .eq_band_sel[2] = 0x57, .eq_band_sel[3] = 0x57, .eq_band_sel[4] = 0x57, .eq_band_sel[5] = 0x47, .eq_band_sel[6] = 0x37, .eq_band_sel[7] = 0x27, .eq_band_sel[8] = 0x17, .eq_band_sel[9] = 0x17, .eq_band_sel[10] = 0x07, // BankA 0x31
			.eq_gain_sel[0] = 0x78, .eq_gain_sel[1] = 0x78, .eq_gain_sel[2] = 0x78, .eq_gain_sel[3] = 0x7f, .eq_gain_sel[4] = 0x7f, .eq_gain_sel[5] = 0x7f, .eq_gain_sel[6] = 0x7f, .eq_gain_sel[7] = 0x7f, .eq_gain_sel[8] = 0x7f, .eq_gain_sel[9] = 0x7f, .eq_gain_sel[10] = 0x7f, // BankA 0x32
			.deq_a_on[0] 	= 0x00, .deq_a_on[1] 	= 0x01, .deq_a_on[2] 	= 0x01, .deq_a_on[3] 	= 0x01, .deq_a_on[4] 	= 0x01, .deq_a_on[5] 	= 0x01, .deq_a_on[6] 	= 0x01, .deq_a_on[7] 	= 0x01, .deq_a_on[8] 	= 0x01, .deq_a_on[9] 	= 0x01, .deq_a_on[10] 	 = 0x01, // BankA 0x33
			.deq_a_sel[0] 	= 0x00, .deq_a_sel[1] 	= 0x91, .deq_a_sel[2] 	= 0x92, .deq_a_sel[3] 	= 0x93, .deq_a_sel[4] 	= 0x93, .deq_a_sel[5] 	= 0x93, .deq_a_sel[6] 	= 0x93, .deq_a_sel[7] 	= 0x93, .deq_a_sel[8] 	= 0x93, .deq_a_sel[9] 	= 0x93, .deq_a_sel[10] 	 = 0x92, // BankA 0x34
			.deq_b_sel[0] 	= 0x00, .deq_b_sel[1] 	= 0x00, .deq_b_sel[2] 	= 0x00, .deq_b_sel[3] 	= 0x00, .deq_b_sel[4] 	= 0x00, .deq_b_sel[5] 	= 0x00, .deq_b_sel[6] 	= 0x00, .deq_b_sel[7] 	= 0x00, .deq_b_sel[8] 	= 0x00, .deq_b_sel[9] 	= 0x00, .deq_b_sel[10] 	 = 0x00, // BankA 0x35
		},
		/* coeff */
		{
			.deqA_01[0] = 0xAC, .deqA_01[1] = 0xAC, .deqA_01[2] = 0xAC, .deqA_01[3] = 0xAC, .deqA_01[4] = 0xAC, .deqA_01[5] = 0xAC,	.deqA_01[6] = 0xAC,  .deqA_01[7] = 0xAC, .deqA_01[8] = 0xAC, .deqA_01[9] = 0xAC, .deqA_01[10] = 0xAC,	// BankA 0x30
			.deqA_02[0] = 0x78, .deqA_02[1] = 0x78, .deqA_02[2] = 0x78, .deqA_02[3] = 0x78, .deqA_02[4] = 0x78, .deqA_02[5] = 0x78,	.deqA_02[6] = 0x78,	 .deqA_02[7] = 0x78, .deqA_02[8] = 0x78, .deqA_02[9] = 0x78, .deqA_02[10] = 0x78,	// BankA 0x31
			.deqA_03[0] = 0x17, .deqA_03[1] = 0x17, .deqA_03[2] = 0x17, .deqA_03[3] = 0x17, .deqA_03[4] = 0x17, .deqA_03[5] = 0x17,	.deqA_03[6] = 0x17,	 .deqA_03[7] = 0x17, .deqA_03[8] = 0x17, .deqA_03[9] = 0x17, .deqA_03[10] = 0x17,	// BankA 0x32
			.deqA_04[0] = 0xC1, .deqA_04[1] = 0xC1, .deqA_04[2] = 0xC1, .deqA_04[3] = 0xC1, .deqA_04[4] = 0xC1, .deqA_04[5] = 0xC1, .deqA_04[6] = 0xC1,  .deqA_04[7] = 0xC1, .deqA_04[8] = 0xC1, .deqA_04[9] = 0xC1, .deqA_04[10] = 0xC1,	// BankA 0x33
			.deqA_05[0] = 0x40, .deqA_05[1] = 0x40, .deqA_05[2] = 0x40, .deqA_05[3] = 0x40, .deqA_05[4] = 0x40, .deqA_05[5] = 0x40, .deqA_05[6] = 0x40,  .deqA_05[7] = 0x40, .deqA_05[8] = 0x40, .deqA_05[9] = 0x40, .deqA_05[10] = 0x40,	// BankA 0x34
			.deqA_06[0] = 0x00, .deqA_06[1] = 0x00, .deqA_06[2] = 0x00, .deqA_06[3] = 0x00, .deqA_06[4] = 0x00, .deqA_06[5] = 0x00, .deqA_06[6] = 0x00,  .deqA_06[7] = 0x00, .deqA_06[8] = 0x00, .deqA_06[9] = 0x00, .deqA_06[10] = 0x00,	// BankA 0x35
			.deqA_07[0] = 0xC3, .deqA_07[1] = 0xC3, .deqA_07[2] = 0xC3, .deqA_07[3] = 0xC3, .deqA_07[4] = 0xC3, .deqA_07[5] = 0xC3, .deqA_07[6] = 0xC3,  .deqA_07[7] = 0xC3, .deqA_07[8] = 0xC3, .deqA_07[9] = 0xC3, .deqA_07[10] = 0xC3,	// BankA 0x36
			.deqA_08[0] = 0x0A, .deqA_08[1] = 0x0A, .deqA_08[2] = 0x0A, .deqA_08[3] = 0x0A, .deqA_08[4] = 0x0A, .deqA_08[5] = 0x0A, .deqA_08[6] = 0x0A,  .deqA_08[7] = 0x0A, .deqA_08[8] = 0x0A, .deqA_08[9] = 0x0A, .deqA_08[10] = 0x0A,	// BankA 0x37
			.deqA_09[0] = 0x00, .deqA_09[1] = 0x00, .deqA_09[2] = 0x00, .deqA_09[3] = 0x00, .deqA_09[4] = 0x00, .deqA_09[5] = 0x00, .deqA_09[6] = 0x00,  .deqA_09[7] = 0x00, .deqA_09[8] = 0x00, .deqA_09[9] = 0x00, .deqA_09[10] = 0x00,	// BankA 0x38
			.deqA_10[0] = 0x02, .deqA_10[1] = 0x02, .deqA_10[2] = 0x02, .deqA_10[3] = 0x02, .deqA_10[4] = 0x02, .deqA_10[5] = 0x02, .deqA_10[6] = 0x02,  .deqA_10[7] = 0x02, .deqA_10[8] = 0x02, .deqA_10[9] = 0x02, .deqA_10[10] = 0x02,	// BankA 0x39
			.deqA_11[0] = 0x00, .deqA_11[1] = 0x00, .deqA_11[2] = 0x00, .deqA_11[3] = 0x00, .deqA_11[4] = 0x00, .deqA_11[5] = 0x00, .deqA_11[6] = 0x00,  .deqA_11[7] = 0x00, .deqA_11[8] = 0x00, .deqA_11[9] = 0x00, .deqA_11[10] = 0x00,	// BankA 0x3a
			.deqA_12[0] = 0xB2, .deqA_12[1] = 0xB2, .deqA_12[2] = 0xB2, .deqA_12[3] = 0xB2, .deqA_12[4] = 0xB2, .deqA_12[5] = 0xB2, .deqA_12[6] = 0xB2,  .deqA_12[7] = 0xB2, .deqA_12[8] = 0xB2, .deqA_12[9] = 0xB2, .deqA_12[10] = 0xB2,	// BankA 0x3b
		},
		/* color */
		{
			.contrast[0] 		= 0x88, .contrast[1] 		= 0x8c, .contrast[2] 		= 0x8a, .contrast[3] 		= 0x87, .contrast[4] 		= 0x85, .contrast[5] 		= 0x84, .contrast[6] 		= 0x80, .contrast[7] 		= 0x80, .contrast[8] 		= 0x79, .contrast[9] 		= 0x72, .contrast[10] 		= 0x72,
			.h_peaking[0] 		= 0x00, .h_peaking[1] 		= 0x00, .h_peaking[2] 		= 0x00, .h_peaking[3] 		= 0x00, .h_peaking[4] 		= 0x00, .h_peaking[5] 		= 0x00, .h_peaking[6] 		= 0x00, .h_peaking[7] 		= 0x3f, .h_peaking[8] 		= 0x3f, .h_peaking[9] 		= 0x3f, .h_peaking[10] 		= 0x3f,
			.c_filter[0]		= 0x82, .c_filter[1] 		= 0x92, .c_filter[2]	 	= 0x92, .c_filter[3] 		= 0x92, .c_filter[4] 		= 0xa2, .c_filter[5] 		= 0xa2, .c_filter[6] 		= 0xb2, .c_filter[7] 		= 0xb2, .c_filter[8] 		= 0xb2, .c_filter[9] 		= 0xb2, .c_filter[10] 		= 0xb2,
			.hue[0] 			= 0x00, .hue[1] 			= 0x00, .hue[2] 			= 0x00, .hue[3] 			= 0x00, .hue[4] 			= 0x00, .hue[5] 			= 0x00, .hue[6] 			= 0x00, .hue[7] 			= 0x00, .hue[8] 			= 0x00, .hue[9] 			= 0x00, .hue[10] 			= 0x00,
			.u_gain[0] 			= 0x00, .u_gain[1] 			= 0x00, .u_gain[2] 			= 0x00, .u_gain[3] 			= 0x00, .u_gain[4] 			= 0x00, .u_gain[5] 			= 0x00, .u_gain[6] 			= 0x00, .u_gain[7] 			= 0x00, .u_gain[8] 			= 0x00, .u_gain[9] 			= 0x00, .u_gain[10] 		= 0x00,
			.v_gain[0] 			= 0x00, .v_gain[1] 			= 0x00, .v_gain[2] 			= 0x00, .v_gain[3] 			= 0x00, .v_gain[4] 			= 0x00, .v_gain[5] 			= 0x00, .v_gain[6] 			= 0x00, .v_gain[7] 			= 0x00, .v_gain[8] 			= 0x00, .v_gain[9] 			= 0x00, .v_gain[10] 		= 0x00,
			.u_offset[0] 		= 0x00, .u_offset[1] 		= 0x00, .u_offset[2] 		= 0x00, .u_offset[3] 		= 0x00, .u_offset[4] 		= 0x00, .u_offset[5] 		= 0x00, .u_offset[6] 		= 0x00, .u_offset[7] 		= 0x00, .u_offset[8] 		= 0x00, .u_offset[9] 		= 0x00, .u_offset[10] 		= 0x00,
			.v_offset[0] 		= 0x00, .v_offset[1] 		= 0x00, .v_offset[2] 		= 0x00, .v_offset[3] 		= 0x00, .v_offset[4] 		= 0x00, .v_offset[5] 		= 0x00, .v_offset[6] 		= 0x00, .v_offset[7] 		= 0x00, .v_offset[8] 		= 0x00, .v_offset[9] 		= 0x00, .v_offset[10] 		= 0x00,

			.black_level[0] 	= 0x84, .black_level[1] 	= 0x86, .black_level[2] 	= 0x84, .black_level[3] 	= 0x84, .black_level[4] 	= 0x86, .black_level[5] 	= 0x88, .black_level[6] 	= 0x8a, .black_level[7] 	= 0x90, .black_level[8] 	= 0x93, .black_level[9] 	= 0x96, .black_level[10] 	= 0x96,
			.acc_ref[0]			= 0x57, .acc_ref[1]			= 0x57, .acc_ref[2]			= 0x57, .acc_ref[3]			= 0x57, .acc_ref[4]			= 0x57, .acc_ref[5]			= 0x57, .acc_ref[6]			= 0x57, .acc_ref[7]			= 0x37, .acc_ref[8]			= 0x20, .acc_ref[9]			= 0x20, .acc_ref[10]		= 0x57,
			.cti_delay[0]		= 0x80, .cti_delay[1]		= 0x80, .cti_delay[2]		= 0x80, .cti_delay[3]		= 0x80, .cti_delay[4]		= 0x80, .cti_delay[5]		= 0x80, .cti_delay[6]		= 0x80, .cti_delay[7]		= 0x80, .cti_delay[8]		= 0x80, .cti_delay[9]		= 0x80, .cti_delay[10]		= 0x80,
			.sub_saturation[0] 	= 0xa8, .sub_saturation[1] 	= 0xaa, .sub_saturation[2] 	= 0xaa, .sub_saturation[3] 	= 0xac, .sub_saturation[4] 	= 0xa8, .sub_saturation[5] 	= 0xa6, .sub_saturation[6] 	= 0x98, .sub_saturation[7] 	= 0xa0, .sub_saturation[8] 	= 0xa0, .sub_saturation[9] 	= 0x50, .sub_saturation[10] = 0x50,

			.burst_dec_a[0] 	= 0x2a, .burst_dec_a[1] 	= 0x2a, .burst_dec_a[2] 	= 0x2a, .burst_dec_a[3] 	= 0x2a, .burst_dec_a[4] 	= 0x2a, .burst_dec_a[5] 	= 0x2a, .burst_dec_a[6] 	= 0x2a, .burst_dec_a[7] 	= 0x2a, .burst_dec_a[8] 	= 0x2a, .burst_dec_a[9] 	= 0x2a, .burst_dec_a[10] 	= 0x2a,
			.burst_dec_b[0] 	= 0x00, .burst_dec_b[1] 	= 0x00, .burst_dec_b[2] 	= 0x00, .burst_dec_b[3] 	= 0x00, .burst_dec_b[4] 	= 0x00, .burst_dec_b[5] 	= 0x00, .burst_dec_b[6] 	= 0x00, .burst_dec_b[7] 	= 0x00, .burst_dec_b[8] 	= 0x00, .burst_dec_b[9] 	= 0x00, .burst_dec_b[10] 	= 0x00,
			.burst_dec_c[0] 	= 0x00, .burst_dec_c[1] 	= 0x00, .burst_dec_c[2] 	= 0x00, .burst_dec_c[3] 	= 0x00, .burst_dec_c[4] 	= 0x00, .burst_dec_c[5] 	= 0x00, .burst_dec_c[6] 	= 0x00, .burst_dec_c[7] 	= 0x00, .burst_dec_c[8] 	= 0x00, .burst_dec_c[9] 	= 0x00, .burst_dec_c[10] 	= 0x00,

			.c_option[0] 		= 0x80, .c_option[1] 		= 0x80, .c_option[2] 		= 0x80, .c_option[3] 		= 0x80, .c_option[4] 		= 0xa0, .c_option[5] 		= 0xa0, .c_option[6] 		= 0xb0, .c_option[7] 		= 0xb0, .c_option[8] 		= 0xb0, .c_option[9] 		= 0xb0, .c_option[10] 		= 0xb0,

			.y_filter_b[0]		= 0x10, .y_filter_b[1]		= 0x10, .y_filter_b[2]		= 0x10, .y_filter_b[3]		= 0x10, .y_filter_b[4]		= 0x10, .y_filter_b[5]		= 0x10, .y_filter_b[6]		= 0x10, .y_filter_b[7]		= 0x10, .y_filter_b[8]		= 0x10, .y_filter_b[9]		= 0x10, .y_filter_b[10]		= 0x10,
			.y_filter_b_sel[0]	= 0x1e,	.y_filter_b_sel[1]	= 0x1e,	.y_filter_b_sel[2]	= 0x1e, .y_filter_b_sel[3]	= 0x1e, .y_filter_b_sel[4]	= 0x1e, .y_filter_b_sel[5]	= 0x1e, .y_filter_b_sel[6]	= 0x1e, .y_filter_b_sel[7]	= 0x1e, .y_filter_b_sel[8]	= 0x1e, .y_filter_b_sel[9]	= 0x1e, .y_filter_b_sel[10]	= 0x1e,
		},
		/* timing_a */
		{
			.h_delay_a[0] = 0x60, .h_delay_a[1] = 0x60, .h_delay_a[2] = 0x5e, .h_delay_a[3] = 0x5b, .h_delay_a[4] = 0x59, .h_delay_a[5] = 0x59, .h_delay_a[6] = 0x5b, .h_delay_a[7] = 0x58, .h_delay_a[8] = 0x58, .h_delay_a[9] = 0x58, .h_delay_a[10] = 0x58,
			.h_delay_b[0] = 0x00, .h_delay_b[1] = 0x00, .h_delay_b[2] = 0x00, .h_delay_b[3] = 0x00, .h_delay_b[4] = 0x00, .h_delay_b[5] = 0x00, .h_delay_b[6] = 0x00, .h_delay_b[7] = 0x00, .h_delay_b[8] = 0x00, .h_delay_b[9] = 0x00, .h_delay_b[10] = 0x00,
			.h_delay_c[0] = 0x00, .h_delay_c[1] = 0x00, .h_delay_c[2] = 0x00, .h_delay_c[3] = 0x00, .h_delay_c[4] = 0x00, .h_delay_c[5] = 0x00, .h_delay_c[6] = 0x00, .h_delay_c[7] = 0x00, .h_delay_c[8] = 0x00, .h_delay_c[9] = 0x00, .h_delay_c[10] = 0x00,
			.y_delay[0]   = 0x05, .y_delay[1]   = 0x05, .y_delay[2]   = 0x05, .y_delay[3]   = 0x05, .y_delay[4]   = 0x05, .y_delay[5] =   0x05, .y_delay[6] =   0x05, .y_delay[7] =   0x05, .y_delay[8] =   0x05, .y_delay[9] =   0x05, .y_delay[10] =   0x05,

		},
		/* clk */
		{
			.clk_adc[0] = 0x02, .clk_adc[1] = 0x02, .clk_adc[2] = 0x02, .clk_adc[3] = 0x02, .clk_adc[4] = 0x02, .clk_adc[5] = 0x02, .clk_adc[6] = 0x02, .clk_adc[7] = 0x02, .clk_adc[8] = 0x02, .clk_adc[9] = 0x02, .clk_adc[10] = 0x02,
			.clk_dec[0] = 0x40, .clk_dec[1] = 0x40, .clk_dec[2] = 0x40, .clk_dec[3] = 0x40, .clk_dec[4] = 0x40, .clk_dec[5] = 0x40, .clk_dec[6] = 0x40, .clk_dec[7] = 0x40, .clk_dec[8] = 0x40, .clk_dec[9] = 0x40, .clk_dec[10] = 0x40,
		},
		/* timing_b */
		{
	/*B9 0x96*/	.h_scaler1[0]  = 0x01, .h_scaler1[1]   = 0x01, .h_scaler1[2]   = 0x01, .h_scaler1[3]   = 0x01, .h_scaler1[4]   = 0x01, .h_scaler1[5]   = 0x01, .h_scaler1[6]   = 0x01, .h_scaler1[7]   = 0x01, .h_scaler1[8]   = 0x01, .h_scaler1[9]   = 0x01, .h_scaler1[10]   = 0x01,
	/*B9 0x97*/	.h_scaler2[0]  = 0x29, .h_scaler2[1]   = 0x29, .h_scaler2[2]   = 0x29, .h_scaler2[3]   = 0x29, .h_scaler2[4]   = 0x29, .h_scaler2[5]   = 0x29, .h_scaler2[6]   = 0x29, .h_scaler2[7]   = 0x29, .h_scaler2[8]   = 0x29, .h_scaler2[9]   = 0x29, .h_scaler2[10]   = 0x29,
	/*B9 0x98*/	.h_scaler3[0]  = 0xc0, .h_scaler3[1]   = 0xc0, .h_scaler3[2]   = 0xc0, .h_scaler3[3]   = 0xc0, .h_scaler3[4]   = 0xc0, .h_scaler3[5]   = 0xc0, .h_scaler3[6]   = 0xc0, .h_scaler3[7]   = 0xc0, .h_scaler3[8]   = 0xc0, .h_scaler3[9]   = 0xc0, .h_scaler3[10]   = 0xc0,
	/*B9 0x99*/	.h_scaler4[0]  = 0xc1, .h_scaler4[1]   = 0xc1, .h_scaler4[2]   = 0xc1, .h_scaler4[3]   = 0xc1, .h_scaler4[4]   = 0xc1, .h_scaler4[5]   = 0xc1, .h_scaler4[6]   = 0xc1, .h_scaler4[7]   = 0xc1, .h_scaler4[8]   = 0xc1, .h_scaler4[9]   = 0xc1, .h_scaler4[10]   = 0xc1,
	/*B9 0x9a*/	.h_scaler5[0]  = 0x00, .h_scaler5[1]   = 0x00, .h_scaler5[2]   = 0x00, .h_scaler5[3]   = 0x00, .h_scaler5[4]   = 0x00, .h_scaler5[5]   = 0x00, .h_scaler5[6]   = 0x00, .h_scaler5[7]   = 0x00, .h_scaler5[8]   = 0x00, .h_scaler5[9]   = 0x00, .h_scaler5[10]   = 0x00,
	/*B9 0x9b*/	.h_scaler6[0]  = 0x00, .h_scaler6[1]   = 0x00, .h_scaler6[2]   = 0x00, .h_scaler6[3]   = 0x00, .h_scaler6[4]   = 0x00, .h_scaler6[5]   = 0x00, .h_scaler6[6]   = 0x00, .h_scaler6[7]   = 0x00, .h_scaler6[8]   = 0x00, .h_scaler6[9]   = 0x00, .h_scaler6[10]   = 0x00,
	/*B9 0x9c*/	.h_scaler7[0]  = 0x00, .h_scaler7[1]   = 0x00, .h_scaler7[2]   = 0x00, .h_scaler7[3]   = 0x00, .h_scaler7[4]   = 0x00, .h_scaler7[5]   = 0x00, .h_scaler7[6]   = 0x00, .h_scaler7[7]   = 0x00, .h_scaler7[8]   = 0x00, .h_scaler7[9]   = 0x00, .h_scaler7[10]   = 0x00,
	/*B9 0x9d*/	.h_scaler8[0]  = 0x00, .h_scaler8[1]   = 0x00, .h_scaler8[2]   = 0x00, .h_scaler8[3]   = 0x00, .h_scaler8[4]   = 0x00, .h_scaler8[5]   = 0x00, .h_scaler8[6]   = 0x00, .h_scaler8[7]   = 0x00, .h_scaler8[8]   = 0x00, .h_scaler8[9]   = 0x00, .h_scaler8[10]   = 0x00,
	/*B9 0x9e*/	.h_scaler9[0]  = 0x00, .h_scaler9[1]   = 0x00, .h_scaler9[2]   = 0x00, .h_scaler9[3]   = 0x00, .h_scaler9[4]   = 0x00, .h_scaler9[5]   = 0x00, .h_scaler9[6]   = 0x00, .h_scaler9[7]   = 0x00, .h_scaler9[8]   = 0x00, .h_scaler9[9]   = 0x00, .h_scaler9[10]   = 0x00,


	/*B9 0x40*/	.pn_auto[0]    	= 0x00, .pn_auto[1]		= 0x00, .pn_auto[2]    	= 0x00, .pn_auto[3]    	= 0x00, .pn_auto[4]    	= 0x00, .pn_auto[5]    	= 0x00, .pn_auto[6]		= 0x00, .pn_auto[7]    	= 0x00, .pn_auto[8]    	= 0x00, .pn_auto[9]    	= 0x00, .pn_auto[10]    	= 0x00,

	/*B5 0x90*/	.comb_mode[0]   = 0x05, .comb_mode[1]	= 0x05, .comb_mode[2]   = 0x05, .comb_mode[3]   = 0x05, .comb_mode[4]  	= 0x05, .comb_mode[5]   = 0x05, .comb_mode[6]	= 0x05, .comb_mode[7]   = 0x05, .comb_mode[8]   = 0x05, .comb_mode[9]  	= 0x05, .comb_mode[10]   = 0x05,
	/*B9 0xb9*/	.h_pll_op_a[0]  = 0x72, .h_pll_op_a[1]  = 0x72, .h_pll_op_a[2]  = 0x72, .h_pll_op_a[3]  = 0x72, .h_pll_op_a[4]  = 0x72, .h_pll_op_a[5]  = 0x72, .h_pll_op_a[6]  = 0x72, .h_pll_op_a[7]  = 0x72, .h_pll_op_a[8]  = 0x72, .h_pll_op_a[9]  = 0x72, .h_pll_op_a[10]  = 0x72,
	/*B9 0x57*/	.mem_path[0]	= 0x10, .mem_path[1]	= 0x10, .mem_path[2]	= 0x10, .mem_path[3]	= 0x10, .mem_path[4]	= 0x10, .mem_path[5]	= 0x10, .mem_path[6]	= 0x10, .mem_path[7]	= 0x10, .mem_path[8]	= 0x10, .mem_path[9]	= 0x10, .mem_path[10]	 = 0x10,
			.fsc_lock_speed[0] = 0xdc, .fsc_lock_speed[1] = 0xdc, .fsc_lock_speed[2] = 0xdc, .fsc_lock_speed[3] = 0xdc, .fsc_lock_speed[4] = 0xdc, .fsc_lock_speed[5] = 0xdc, .fsc_lock_speed[6] = 0xdc, .fsc_lock_speed[7] = 0xdc, .fsc_lock_speed[8] = 0xdc, .fsc_lock_speed[9] = 0xdc, .fsc_lock_speed[10] = 0xdc,

	/*B0 0x81*/	.format_set1[0] = 0x06, .format_set1[1] = 0x06, .format_set1[2] = 0x06, .format_set1[3] = 0x06, .format_set1[4] = 0x06, .format_set1[5] = 0x06, .format_set1[6] = 0x06, .format_set1[7] = 0x06, .format_set1[8] = 0x06, .format_set1[9] = 0x06, .format_set1[10] = 0x06,
	/*B0 0x85*/	.format_set2[0] = 0x02, .format_set2[1] = 0x02, .format_set2[2] = 0x02, .format_set2[3] = 0x02, .format_set2[4] = 0x02, .format_set2[5] = 0x02, .format_set2[6] = 0x02, .format_set2[7] = 0x02, .format_set2[8] = 0x02, .format_set2[9] = 0x02, .format_set2[10] = 0x02,

	/*B0 0x64*/ .v_delay[0]     = 0x21, .v_delay[1]     = 0x21, .v_delay[2]     = 0x21, .v_delay[3]     = 0x21, .v_delay[4]     = 0x21, .v_delay[5]     = 0x21, .v_delay[6]     = 0x21, .v_delay[7]     = 0x21, .v_delay[8]     = 0x21, .v_delay[9]     = 0x21, .v_delay[10]     = 0x21,
		},
	},

	[ CVI_HD_25P_EX ] = /* o */
	{
		/* base */
		{
			.eq_bypass[0] 	= 0x22, .eq_bypass[1] 	= 0x22, .eq_bypass[2] 	= 0x22, .eq_bypass[3] 	= 0x22, .eq_bypass[4] 	= 0x22, .eq_bypass[5] 	= 0x22, .eq_bypass[6] 	= 0x22, .eq_bypass[7] 	= 0x22, .eq_bypass[8] 	= 0x22, .eq_bypass[9] 	= 0x22, .eq_bypass[10] 	 = 0x22,  // Bank5 0x30
			.eq_band_sel[0] = 0x77, .eq_band_sel[1] = 0x67, .eq_band_sel[2] = 0x57, .eq_band_sel[3] = 0x57, .eq_band_sel[4] = 0x57, .eq_band_sel[5] = 0x47, .eq_band_sel[6] = 0x37, .eq_band_sel[7] = 0x27, .eq_band_sel[8] = 0x17, .eq_band_sel[9] = 0x17, .eq_band_sel[10] = 0x07, // BankA 0x31
			.eq_gain_sel[0] = 0x78, .eq_gain_sel[1] = 0x78, .eq_gain_sel[2] = 0x78, .eq_gain_sel[3] = 0x7f, .eq_gain_sel[4] = 0x7f, .eq_gain_sel[5] = 0x7f, .eq_gain_sel[6] = 0x7f, .eq_gain_sel[7] = 0x7f, .eq_gain_sel[8] = 0x7f, .eq_gain_sel[9] = 0x7f, .eq_gain_sel[10] = 0x7f, // BankA 0x32
			.deq_a_on[0] 	= 0x00, .deq_a_on[1] 	= 0x01, .deq_a_on[2] 	= 0x01, .deq_a_on[3] 	= 0x01, .deq_a_on[4] 	= 0x01, .deq_a_on[5] 	= 0x01, .deq_a_on[6] 	= 0x01, .deq_a_on[7] 	= 0x01, .deq_a_on[8] 	= 0x01, .deq_a_on[9] 	= 0x01, .deq_a_on[10] 	 = 0x01, // BankA 0x33
			.deq_a_sel[0] 	= 0x00, .deq_a_sel[1] 	= 0x91, .deq_a_sel[2] 	= 0x92, .deq_a_sel[3] 	= 0x93, .deq_a_sel[4] 	= 0x93, .deq_a_sel[5] 	= 0x93, .deq_a_sel[6] 	= 0x93, .deq_a_sel[7] 	= 0x93, .deq_a_sel[8] 	= 0x93, .deq_a_sel[9] 	= 0x93, .deq_a_sel[10] 	 = 0x92, // BankA 0x34
			.deq_b_sel[0] 	= 0x00, .deq_b_sel[1] 	= 0x00, .deq_b_sel[2] 	= 0x00, .deq_b_sel[3] 	= 0x00, .deq_b_sel[4] 	= 0x00, .deq_b_sel[5] 	= 0x00, .deq_b_sel[6] 	= 0x00, .deq_b_sel[7] 	= 0x00, .deq_b_sel[8] 	= 0x00, .deq_b_sel[9] 	= 0x00, .deq_b_sel[10] 	 = 0x00, // BankA 0x35
		},
		/* coeff */
		{
			.deqA_01[0] = 0xAC, .deqA_01[1] = 0xAC, .deqA_01[2] = 0xAC, .deqA_01[3] = 0xAC, .deqA_01[4] = 0xAC, .deqA_01[5] = 0xAC,	.deqA_01[6] = 0xAC,  .deqA_01[7] = 0xAC, .deqA_01[8] = 0xAC, .deqA_01[9] = 0xAC, .deqA_01[10] = 0xAC,	// BankA 0x30
			.deqA_02[0] = 0x78, .deqA_02[1] = 0x78, .deqA_02[2] = 0x78, .deqA_02[3] = 0x78, .deqA_02[4] = 0x78, .deqA_02[5] = 0x78,	.deqA_02[6] = 0x78,	 .deqA_02[7] = 0x78, .deqA_02[8] = 0x78, .deqA_02[9] = 0x78, .deqA_02[10] = 0x78,	// BankA 0x31
			.deqA_03[0] = 0x17, .deqA_03[1] = 0x17, .deqA_03[2] = 0x17, .deqA_03[3] = 0x17, .deqA_03[4] = 0x17, .deqA_03[5] = 0x17,	.deqA_03[6] = 0x17,	 .deqA_03[7] = 0x17, .deqA_03[8] = 0x17, .deqA_03[9] = 0x17, .deqA_03[10] = 0x17,	// BankA 0x32
			.deqA_04[0] = 0xC1, .deqA_04[1] = 0xC1, .deqA_04[2] = 0xC1, .deqA_04[3] = 0xC1, .deqA_04[4] = 0xC1, .deqA_04[5] = 0xC1, .deqA_04[6] = 0xC1,  .deqA_04[7] = 0xC1, .deqA_04[8] = 0xC1, .deqA_04[9] = 0xC1, .deqA_04[10] = 0xC1,	// BankA 0x33
			.deqA_05[0] = 0x40, .deqA_05[1] = 0x40, .deqA_05[2] = 0x40, .deqA_05[3] = 0x40, .deqA_05[4] = 0x40, .deqA_05[5] = 0x40, .deqA_05[6] = 0x40,  .deqA_05[7] = 0x40, .deqA_05[8] = 0x40, .deqA_05[9] = 0x40, .deqA_05[10] = 0x40,	// BankA 0x34
			.deqA_06[0] = 0x00, .deqA_06[1] = 0x00, .deqA_06[2] = 0x00, .deqA_06[3] = 0x00, .deqA_06[4] = 0x00, .deqA_06[5] = 0x00, .deqA_06[6] = 0x00,  .deqA_06[7] = 0x00, .deqA_06[8] = 0x00, .deqA_06[9] = 0x00, .deqA_06[10] = 0x00,	// BankA 0x35
			.deqA_07[0] = 0xC3, .deqA_07[1] = 0xC3, .deqA_07[2] = 0xC3, .deqA_07[3] = 0xC3, .deqA_07[4] = 0xC3, .deqA_07[5] = 0xC3, .deqA_07[6] = 0xC3,  .deqA_07[7] = 0xC3, .deqA_07[8] = 0xC3, .deqA_07[9] = 0xC3, .deqA_07[10] = 0xC3,	// BankA 0x36
			.deqA_08[0] = 0x0A, .deqA_08[1] = 0x0A, .deqA_08[2] = 0x0A, .deqA_08[3] = 0x0A, .deqA_08[4] = 0x0A, .deqA_08[5] = 0x0A, .deqA_08[6] = 0x0A,  .deqA_08[7] = 0x0A, .deqA_08[8] = 0x0A, .deqA_08[9] = 0x0A, .deqA_08[10] = 0x0A,	// BankA 0x37
			.deqA_09[0] = 0x00, .deqA_09[1] = 0x00, .deqA_09[2] = 0x00, .deqA_09[3] = 0x00, .deqA_09[4] = 0x00, .deqA_09[5] = 0x00, .deqA_09[6] = 0x00,  .deqA_09[7] = 0x00, .deqA_09[8] = 0x00, .deqA_09[9] = 0x00, .deqA_09[10] = 0x00,	// BankA 0x38
			.deqA_10[0] = 0x02, .deqA_10[1] = 0x02, .deqA_10[2] = 0x02, .deqA_10[3] = 0x02, .deqA_10[4] = 0x02, .deqA_10[5] = 0x02, .deqA_10[6] = 0x02,  .deqA_10[7] = 0x02, .deqA_10[8] = 0x02, .deqA_10[9] = 0x02, .deqA_10[10] = 0x02,	// BankA 0x39
			.deqA_11[0] = 0x00, .deqA_11[1] = 0x00, .deqA_11[2] = 0x00, .deqA_11[3] = 0x00, .deqA_11[4] = 0x00, .deqA_11[5] = 0x00, .deqA_11[6] = 0x00,  .deqA_11[7] = 0x00, .deqA_11[8] = 0x00, .deqA_11[9] = 0x00, .deqA_11[10] = 0x00,	// BankA 0x3a
			.deqA_12[0] = 0xB2, .deqA_12[1] = 0xB2, .deqA_12[2] = 0xB2, .deqA_12[3] = 0xB2, .deqA_12[4] = 0xB2, .deqA_12[5] = 0xB2, .deqA_12[6] = 0xB2,  .deqA_12[7] = 0xB2, .deqA_12[8] = 0xB2, .deqA_12[9] = 0xB2, .deqA_12[10] = 0xB2,	// BankA 0x3b
		},
		/* color */
		{
			.contrast[0] 		= 0x88, .contrast[1] 		= 0x8c, .contrast[2] 		= 0x8a, .contrast[3] 		= 0x87, .contrast[4] 		= 0x85, .contrast[5] 		= 0x84, .contrast[6] 		= 0x80, .contrast[7] 		= 0x80, .contrast[8] 		= 0x79, .contrast[9] 		= 0x72, .contrast[10] 		= 0x72,
			.h_peaking[0] 		= 0x00, .h_peaking[1] 		= 0x00, .h_peaking[2] 		= 0x00, .h_peaking[3] 		= 0x00, .h_peaking[4] 		= 0x00, .h_peaking[5] 		= 0x00, .h_peaking[6] 		= 0x00, .h_peaking[7] 		= 0x3f, .h_peaking[8] 		= 0x3f, .h_peaking[9] 		= 0x3f, .h_peaking[10] 		= 0x3f,
			.c_filter[0]		= 0x82, .c_filter[1] 		= 0x92, .c_filter[2]	 	= 0x92, .c_filter[3] 		= 0x92, .c_filter[4] 		= 0xa2, .c_filter[5] 		= 0xa2, .c_filter[6] 		= 0xb2, .c_filter[7] 		= 0xb2, .c_filter[8] 		= 0xb2, .c_filter[9] 		= 0xb2, .c_filter[10] 		= 0xb2,
			.hue[0] 			= 0x00, .hue[1] 			= 0x00, .hue[2] 			= 0x00, .hue[3] 			= 0x00, .hue[4] 			= 0x00, .hue[5] 			= 0x00, .hue[6] 			= 0x00, .hue[7] 			= 0x00, .hue[8] 			= 0x00, .hue[9] 			= 0x00, .hue[10] 			= 0x00,
			.u_gain[0] 			= 0x00, .u_gain[1] 			= 0x00, .u_gain[2] 			= 0x00, .u_gain[3] 			= 0x00, .u_gain[4] 			= 0x00, .u_gain[5] 			= 0x00, .u_gain[6] 			= 0x00, .u_gain[7] 			= 0x00, .u_gain[8] 			= 0x00, .u_gain[9] 			= 0x00, .u_gain[10] 		= 0x00,
			.v_gain[0] 			= 0x00, .v_gain[1] 			= 0x00, .v_gain[2] 			= 0x00, .v_gain[3] 			= 0x00, .v_gain[4] 			= 0x00, .v_gain[5] 			= 0x00, .v_gain[6] 			= 0x00, .v_gain[7] 			= 0x00, .v_gain[8] 			= 0x00, .v_gain[9] 			= 0x00, .v_gain[10] 		= 0x00,
			.u_offset[0] 		= 0x00, .u_offset[1] 		= 0x00, .u_offset[2] 		= 0x00, .u_offset[3] 		= 0x00, .u_offset[4] 		= 0x00, .u_offset[5] 		= 0x00, .u_offset[6] 		= 0x00, .u_offset[7] 		= 0x00, .u_offset[8] 		= 0x00, .u_offset[9] 		= 0x00, .u_offset[10] 		= 0x00,
			.v_offset[0] 		= 0x00, .v_offset[1] 		= 0x00, .v_offset[2] 		= 0x00, .v_offset[3] 		= 0x00, .v_offset[4] 		= 0x00, .v_offset[5] 		= 0x00, .v_offset[6] 		= 0x00, .v_offset[7] 		= 0x00, .v_offset[8] 		= 0x00, .v_offset[9] 		= 0x00, .v_offset[10] 		= 0x00,

			.black_level[0] 	= 0x84, .black_level[1] 	= 0x86, .black_level[2] 	= 0x84, .black_level[3] 	= 0x84, .black_level[4] 	= 0x86, .black_level[5] 	= 0x88, .black_level[6] 	= 0x8a, .black_level[7] 	= 0x90, .black_level[8] 	= 0x93, .black_level[9] 	= 0x96, .black_level[10] 	= 0x96,
			.acc_ref[0]			= 0x57, .acc_ref[1]			= 0x57, .acc_ref[2]			= 0x57, .acc_ref[3]			= 0x57, .acc_ref[4]			= 0x57, .acc_ref[5]			= 0x57, .acc_ref[6]			= 0x57, .acc_ref[7]			= 0x37, .acc_ref[8]			= 0x20, .acc_ref[9]			= 0x20, .acc_ref[10]		= 0x57,
			.cti_delay[0]		= 0x80, .cti_delay[1]		= 0x80, .cti_delay[2]		= 0x80, .cti_delay[3]		= 0x80, .cti_delay[4]		= 0x80, .cti_delay[5]		= 0x80, .cti_delay[6]		= 0x80, .cti_delay[7]		= 0x80, .cti_delay[8]		= 0x80, .cti_delay[9]		= 0x80, .cti_delay[10]		= 0x80,
			.sub_saturation[0] 	= 0xa8, .sub_saturation[1] 	= 0xaa, .sub_saturation[2] 	= 0xaa, .sub_saturation[3] 	= 0xac, .sub_saturation[4] 	= 0xa8, .sub_saturation[5] 	= 0xa6, .sub_saturation[6] 	= 0x98, .sub_saturation[7] 	= 0xa0, .sub_saturation[8] 	= 0xa0, .sub_saturation[9] 	= 0x50, .sub_saturation[10] = 0x50,

			.burst_dec_a[0] 	= 0x2a, .burst_dec_a[1] 	= 0x2a, .burst_dec_a[2] 	= 0x2a, .burst_dec_a[3] 	= 0x2a, .burst_dec_a[4] 	= 0x2a, .burst_dec_a[5] 	= 0x2a, .burst_dec_a[6] 	= 0x2a, .burst_dec_a[7] 	= 0x2a, .burst_dec_a[8] 	= 0x2a, .burst_dec_a[9] 	= 0x2a, .burst_dec_a[10] 	= 0x2a,
			.burst_dec_b[0] 	= 0x00, .burst_dec_b[1] 	= 0x00, .burst_dec_b[2] 	= 0x00, .burst_dec_b[3] 	= 0x00, .burst_dec_b[4] 	= 0x00, .burst_dec_b[5] 	= 0x00, .burst_dec_b[6] 	= 0x00, .burst_dec_b[7] 	= 0x00, .burst_dec_b[8] 	= 0x00, .burst_dec_b[9] 	= 0x00, .burst_dec_b[10] 	= 0x00,
			.burst_dec_c[0] 	= 0x30, .burst_dec_c[1] 	= 0x30, .burst_dec_c[2] 	= 0x30, .burst_dec_c[3] 	= 0x30, .burst_dec_c[4] 	= 0x30, .burst_dec_c[5] 	= 0x30, .burst_dec_c[6] 	= 0x30, .burst_dec_c[7] 	= 0x30, .burst_dec_c[8] 	= 0x30, .burst_dec_c[9] 	= 0x30, .burst_dec_c[10] 	= 0x30,

			.c_option[0] 		= 0x80, .c_option[1] 		= 0x80, .c_option[2] 		= 0x80, .c_option[3] 		= 0x80, .c_option[4] 		= 0xa0, .c_option[5] 		= 0xa0, .c_option[6] 		= 0xb0, .c_option[7] 		= 0xb0, .c_option[8] 		= 0xb0, .c_option[9] 		= 0xb0, .c_option[10] 		= 0xb0,

			.y_filter_b[0]		= 0x10, .y_filter_b[1]		= 0x10, .y_filter_b[2]		= 0x10, .y_filter_b[3]		= 0x10, .y_filter_b[4]		= 0x10, .y_filter_b[5]		= 0x10, .y_filter_b[6]		= 0x10, .y_filter_b[7]		= 0x10, .y_filter_b[8]		= 0x10, .y_filter_b[9]		= 0x10, .y_filter_b[10]		= 0x10,
			.y_filter_b_sel[0]	= 0x1e,	.y_filter_b_sel[1]	= 0x1e,	.y_filter_b_sel[2]	= 0x1e, .y_filter_b_sel[3]	= 0x1e, .y_filter_b_sel[4]	= 0x1e, .y_filter_b_sel[5]	= 0x1e, .y_filter_b_sel[6]	= 0x1e, .y_filter_b_sel[7]	= 0x1e, .y_filter_b_sel[8]	= 0x1e, .y_filter_b_sel[9]	= 0x1e, .y_filter_b_sel[10]	= 0x1e,
		},
		/* timing_a */
		{
			.h_delay_a[0] = 0x7b, .h_delay_a[1] = 0x7b, .h_delay_a[2] = 0x7a, .h_delay_a[3] = 0x79, .h_delay_a[4] = 0x79, .h_delay_a[5] = 0x7a, .h_delay_a[6] = 0x7a, .h_delay_a[7] = 0x7a, .h_delay_a[8] = 0x7a, .h_delay_a[9] = 0x7a, .h_delay_a[10] = 0x7a,
			.h_delay_b[0] = 0x10, .h_delay_b[1] = 0x10, .h_delay_b[2] = 0x10, .h_delay_b[3] = 0x10, .h_delay_b[4] = 0x10, .h_delay_b[5] = 0x10, .h_delay_b[6] = 0x10, .h_delay_b[7] = 0x10, .h_delay_b[8] = 0x10, .h_delay_b[9] = 0x10, .h_delay_b[10] = 0x10,
			.h_delay_c[0] = 0x00, .h_delay_c[1] = 0x00, .h_delay_c[2] = 0x00, .h_delay_c[3] = 0x00, .h_delay_c[4] = 0x00, .h_delay_c[5] = 0x00, .h_delay_c[6] = 0x00, .h_delay_c[7] = 0x00, .h_delay_c[8] = 0x00, .h_delay_c[9] = 0x00, .h_delay_c[10] = 0x00,
			.y_delay[0]   = 0x05, .y_delay[1]   = 0x05, .y_delay[2]   = 0x05, .y_delay[3]   = 0x05, .y_delay[4]   = 0x05, .y_delay[5] =   0x05, .y_delay[6] =   0x05, .y_delay[7] =   0x05, .y_delay[8] =   0x05, .y_delay[9] =   0x05, .y_delay[10] =   0x05,

		},
		/* clk */
		{
			.clk_adc[0] = 0x02, .clk_adc[1] = 0x02, .clk_adc[2] = 0x02, .clk_adc[3] = 0x02, .clk_adc[4] = 0x02, .clk_adc[5] = 0x02, .clk_adc[6] = 0x02, .clk_adc[7] = 0x02, .clk_adc[8] = 0x02, .clk_adc[9] = 0x02, .clk_adc[10] = 0x02,
			.clk_dec[0] = 0x40, .clk_dec[1] = 0x40, .clk_dec[2] = 0x40, .clk_dec[3] = 0x40, .clk_dec[4] = 0x40, .clk_dec[5] = 0x40, .clk_dec[6] = 0x40, .clk_dec[7] = 0x40, .clk_dec[8] = 0x40, .clk_dec[9] = 0x40, .clk_dec[10] = 0x40,
		},
		/* timing_b */
		{
/*B9 0x96*/	.h_scaler1[0]  = 0x01, .h_scaler1[1]   = 0x01, .h_scaler1[2]   = 0x01, .h_scaler1[3]   = 0x01, .h_scaler1[4]   = 0x01, .h_scaler1[5]   = 0x01, .h_scaler1[6]   = 0x01, .h_scaler1[7]   = 0x01, .h_scaler1[8]   = 0x01, .h_scaler1[9]   = 0x01, .h_scaler1[10]   = 0x01,
/*B9 0x97*/	.h_scaler2[0]  = 0x29, .h_scaler2[1]   = 0x29, .h_scaler2[2]   = 0x29, .h_scaler2[3]   = 0x29, .h_scaler2[4]   = 0x29, .h_scaler2[5]   = 0x29, .h_scaler2[6]   = 0x29, .h_scaler2[7]   = 0x29, .h_scaler2[8]   = 0x29, .h_scaler2[9]   = 0x29, .h_scaler2[10]   = 0x29,
/*B9 0x98*/	.h_scaler3[0]  = 0xc0, .h_scaler3[1]   = 0xc0, .h_scaler3[2]   = 0xc0, .h_scaler3[3]   = 0xc0, .h_scaler3[4]   = 0xc0, .h_scaler3[5]   = 0xc0, .h_scaler3[6]   = 0xc0, .h_scaler3[7]   = 0xc0, .h_scaler3[8]   = 0xc0, .h_scaler3[9]   = 0xc0, .h_scaler3[10]   = 0xc0,
/*B9 0x99*/	.h_scaler4[0]  = 0x01, .h_scaler4[1]   = 0x01, .h_scaler4[2]   = 0x01, .h_scaler4[3]   = 0x01, .h_scaler4[4]   = 0x01, .h_scaler4[5]   = 0x01, .h_scaler4[6]   = 0x01, .h_scaler4[7]   = 0x01, .h_scaler4[8]   = 0x01, .h_scaler4[9]   = 0x01, .h_scaler4[10]   = 0x01,
/*B9 0x9a*/	.h_scaler5[0]  = 0x00, .h_scaler5[1]   = 0x00, .h_scaler5[2]   = 0x00, .h_scaler5[3]   = 0x00, .h_scaler5[4]   = 0x00, .h_scaler5[5]   = 0x00, .h_scaler5[6]   = 0x00, .h_scaler5[7]   = 0x00, .h_scaler5[8]   = 0x00, .h_scaler5[9]   = 0x00, .h_scaler5[10]   = 0x00,
/*B9 0x9b*/	.h_scaler6[0]  = 0x00, .h_scaler6[1]   = 0x00, .h_scaler6[2]   = 0x00, .h_scaler6[3]   = 0x00, .h_scaler6[4]   = 0x00, .h_scaler6[5]   = 0x00, .h_scaler6[6]   = 0x00, .h_scaler6[7]   = 0x00, .h_scaler6[8]   = 0x00, .h_scaler6[9]   = 0x00, .h_scaler6[10]   = 0x00,
/*B9 0x9c*/	.h_scaler7[0]  = 0x00, .h_scaler7[1]   = 0x00, .h_scaler7[2]   = 0x00, .h_scaler7[3]   = 0x00, .h_scaler7[4]   = 0x00, .h_scaler7[5]   = 0x00, .h_scaler7[6]   = 0x00, .h_scaler7[7]   = 0x00, .h_scaler7[8]   = 0x00, .h_scaler7[9]   = 0x00, .h_scaler7[10]   = 0x00,
/*B9 0x9d*/	.h_scaler8[0]  = 0x00, .h_scaler8[1]   = 0x00, .h_scaler8[2]   = 0x00, .h_scaler8[3]   = 0x00, .h_scaler8[4]   = 0x00, .h_scaler8[5]   = 0x00, .h_scaler8[6]   = 0x00, .h_scaler8[7]   = 0x00, .h_scaler8[8]   = 0x00, .h_scaler8[9]   = 0x00, .h_scaler8[10]   = 0x00,
/*B9 0x9e*/	.h_scaler9[0]  = 0x80, .h_scaler9[1]   = 0x80, .h_scaler9[2]   = 0x80, .h_scaler9[3]   = 0x80, .h_scaler9[4]   = 0x80, .h_scaler9[5]   = 0x80, .h_scaler9[6]   = 0x80, .h_scaler9[7]   = 0x80, .h_scaler9[8]   = 0x80, .h_scaler9[9]   = 0x80, .h_scaler9[10]   = 0x80,


/*B9 0x40*/	.pn_auto[0]    	= 0x00, .pn_auto[1]		= 0x00, .pn_auto[2]    	= 0x00, .pn_auto[3]    	= 0x00, .pn_auto[4]    	= 0x00, .pn_auto[5]    	= 0x00, .pn_auto[6]		= 0x00, .pn_auto[7]    	= 0x00, .pn_auto[8]    	= 0x00, .pn_auto[9]    	= 0x00, .pn_auto[10]    	= 0x00,

/*B5 0x90*/	.comb_mode[0]   = 0x05, .comb_mode[1]	= 0x05, .comb_mode[2]   = 0x05, .comb_mode[3]   = 0x05, .comb_mode[4]  	= 0x05, .comb_mode[5]   = 0x05, .comb_mode[6]	= 0x05, .comb_mode[7]   = 0x05, .comb_mode[8]   = 0x05, .comb_mode[9]  	= 0x05, .comb_mode[10]   = 0x05,
/*B9 0xb9*/	.h_pll_op_a[0]  = 0x72, .h_pll_op_a[1]  = 0x72, .h_pll_op_a[2]  = 0x72, .h_pll_op_a[3]  = 0x72, .h_pll_op_a[4]  = 0x72, .h_pll_op_a[5]  = 0x72, .h_pll_op_a[6]  = 0x72, .h_pll_op_a[7]  = 0x72, .h_pll_op_a[8]  = 0x72, .h_pll_op_a[9]  = 0x72, .h_pll_op_a[10]  = 0x72,
/*B9 0x57*/	.mem_path[0]	= 0x10, .mem_path[1]	= 0x10, .mem_path[2]	= 0x10, .mem_path[3]	= 0x10, .mem_path[4]	= 0x10, .mem_path[5]	= 0x10, .mem_path[6]	= 0x10, .mem_path[7]	= 0x10, .mem_path[8]	= 0x10, .mem_path[9]	= 0x10, .mem_path[10]	 = 0x10,
			.fsc_lock_speed[0] = 0xdc, .fsc_lock_speed[1] = 0xdc, .fsc_lock_speed[2] = 0xdc, .fsc_lock_speed[3] = 0xdc, .fsc_lock_speed[4] = 0xdc, .fsc_lock_speed[5] = 0xdc, .fsc_lock_speed[6] = 0xdc, .fsc_lock_speed[7] = 0xdc, .fsc_lock_speed[8] = 0xdc, .fsc_lock_speed[9] = 0xdc, .fsc_lock_speed[10] = 0xdc,

/*B0 0x81*/	.format_set1[0] = 0x0b, .format_set1[1] = 0x0b, .format_set1[2] = 0x0b, .format_set1[3] = 0x0b, .format_set1[4] = 0x0b, .format_set1[5] = 0x0b, .format_set1[6] = 0x0b, .format_set1[7] = 0x0b, .format_set1[8] = 0x0b, .format_set1[9] = 0x0b, .format_set1[10] = 0x0b,
/*B0 0x85*/	.format_set2[0] = 0x02, .format_set2[1] = 0x02, .format_set2[2] = 0x02, .format_set2[3] = 0x02, .format_set2[4] = 0x02, .format_set2[5] = 0x02, .format_set2[6] = 0x02, .format_set2[7] = 0x02, .format_set2[8] = 0x02, .format_set2[9] = 0x02, .format_set2[10] = 0x02,

/*B0 0x64*/ .v_delay[0]     = 0x21, .v_delay[1]     = 0x21, .v_delay[2]     = 0x21, .v_delay[3]     = 0x21, .v_delay[4]     = 0x21, .v_delay[5]     = 0x21, .v_delay[6]     = 0x21, .v_delay[7]     = 0x21, .v_delay[8]     = 0x21, .v_delay[9]     = 0x21, .v_delay[10]     = 0x21,
		},
	},
	[ CVI_HD_30P_EX ] = /* o */
	{
	/* base */
		{
			.eq_bypass[0] 	= 0x22, .eq_bypass[1] 	= 0x22, .eq_bypass[2] 	= 0x22, .eq_bypass[3] 	= 0x22, .eq_bypass[4] 	= 0x22, .eq_bypass[5] 	= 0x22, .eq_bypass[6] 	= 0x22, .eq_bypass[7] 	= 0x22, .eq_bypass[8] 	= 0x22, .eq_bypass[9] 	= 0x22, .eq_bypass[10] 	 = 0x22,  // Bank5 0x30
			.eq_band_sel[0] = 0x77, .eq_band_sel[1] = 0x67, .eq_band_sel[2] = 0x57, .eq_band_sel[3] = 0x57, .eq_band_sel[4] = 0x57, .eq_band_sel[5] = 0x47, .eq_band_sel[6] = 0x37, .eq_band_sel[7] = 0x27, .eq_band_sel[8] = 0x17, .eq_band_sel[9] = 0x17, .eq_band_sel[10] = 0x07, // BankA 0x31
			.eq_gain_sel[0] = 0x78, .eq_gain_sel[1] = 0x78, .eq_gain_sel[2] = 0x78, .eq_gain_sel[3] = 0x7f, .eq_gain_sel[4] = 0x7f, .eq_gain_sel[5] = 0x7f, .eq_gain_sel[6] = 0x7f, .eq_gain_sel[7] = 0x7f, .eq_gain_sel[8] = 0x7f, .eq_gain_sel[9] = 0x7f, .eq_gain_sel[10] = 0x7f, // BankA 0x32
			.deq_a_on[0] 	= 0x00, .deq_a_on[1] 	= 0x01, .deq_a_on[2] 	= 0x01, .deq_a_on[3] 	= 0x01, .deq_a_on[4] 	= 0x01, .deq_a_on[5] 	= 0x01, .deq_a_on[6] 	= 0x01, .deq_a_on[7] 	= 0x01, .deq_a_on[8] 	= 0x01, .deq_a_on[9] 	= 0x01, .deq_a_on[10] 	 = 0x01, // BankA 0x33
			.deq_a_sel[0] 	= 0x00, .deq_a_sel[1] 	= 0x91, .deq_a_sel[2] 	= 0x92, .deq_a_sel[3] 	= 0x93, .deq_a_sel[4] 	= 0x93, .deq_a_sel[5] 	= 0x93, .deq_a_sel[6] 	= 0x93, .deq_a_sel[7] 	= 0x93, .deq_a_sel[8] 	= 0x93, .deq_a_sel[9] 	= 0x93, .deq_a_sel[10] 	 = 0x92, // BankA 0x34
			.deq_b_sel[0] 	= 0x00, .deq_b_sel[1] 	= 0x00, .deq_b_sel[2] 	= 0x00, .deq_b_sel[3] 	= 0x00, .deq_b_sel[4] 	= 0x00, .deq_b_sel[5] 	= 0x00, .deq_b_sel[6] 	= 0x00, .deq_b_sel[7] 	= 0x00, .deq_b_sel[8] 	= 0x00, .deq_b_sel[9] 	= 0x00, .deq_b_sel[10] 	 = 0x00, // BankA 0x35
		},
		/* coeff */
		{
			.deqA_01[0] = 0xAC, .deqA_01[1] = 0xAC, .deqA_01[2] = 0xAC, .deqA_01[3] = 0xAC, .deqA_01[4] = 0xAC, .deqA_01[5] = 0xAC,	.deqA_01[6] = 0xAC,  .deqA_01[7] = 0xAC, .deqA_01[8] = 0xAC, .deqA_01[9] = 0xAC, .deqA_01[10] = 0xAC,	// BankA 0x30
			.deqA_02[0] = 0x78, .deqA_02[1] = 0x78, .deqA_02[2] = 0x78, .deqA_02[3] = 0x78, .deqA_02[4] = 0x78, .deqA_02[5] = 0x78,	.deqA_02[6] = 0x78,	 .deqA_02[7] = 0x78, .deqA_02[8] = 0x78, .deqA_02[9] = 0x78, .deqA_02[10] = 0x78,	// BankA 0x31
			.deqA_03[0] = 0x17, .deqA_03[1] = 0x17, .deqA_03[2] = 0x17, .deqA_03[3] = 0x17, .deqA_03[4] = 0x17, .deqA_03[5] = 0x17,	.deqA_03[6] = 0x17,	 .deqA_03[7] = 0x17, .deqA_03[8] = 0x17, .deqA_03[9] = 0x17, .deqA_03[10] = 0x17,	// BankA 0x32
			.deqA_04[0] = 0xC1, .deqA_04[1] = 0xC1, .deqA_04[2] = 0xC1, .deqA_04[3] = 0xC1, .deqA_04[4] = 0xC1, .deqA_04[5] = 0xC1, .deqA_04[6] = 0xC1,  .deqA_04[7] = 0xC1, .deqA_04[8] = 0xC1, .deqA_04[9] = 0xC1, .deqA_04[10] = 0xC1,	// BankA 0x33
			.deqA_05[0] = 0x40, .deqA_05[1] = 0x40, .deqA_05[2] = 0x40, .deqA_05[3] = 0x40, .deqA_05[4] = 0x40, .deqA_05[5] = 0x40, .deqA_05[6] = 0x40,  .deqA_05[7] = 0x40, .deqA_05[8] = 0x40, .deqA_05[9] = 0x40, .deqA_05[10] = 0x40,	// BankA 0x34
			.deqA_06[0] = 0x00, .deqA_06[1] = 0x00, .deqA_06[2] = 0x00, .deqA_06[3] = 0x00, .deqA_06[4] = 0x00, .deqA_06[5] = 0x00, .deqA_06[6] = 0x00,  .deqA_06[7] = 0x00, .deqA_06[8] = 0x00, .deqA_06[9] = 0x00, .deqA_06[10] = 0x00,	// BankA 0x35
			.deqA_07[0] = 0xC3, .deqA_07[1] = 0xC3, .deqA_07[2] = 0xC3, .deqA_07[3] = 0xC3, .deqA_07[4] = 0xC3, .deqA_07[5] = 0xC3, .deqA_07[6] = 0xC3,  .deqA_07[7] = 0xC3, .deqA_07[8] = 0xC3, .deqA_07[9] = 0xC3, .deqA_07[10] = 0xC3,	// BankA 0x36
			.deqA_08[0] = 0x0A, .deqA_08[1] = 0x0A, .deqA_08[2] = 0x0A, .deqA_08[3] = 0x0A, .deqA_08[4] = 0x0A, .deqA_08[5] = 0x0A, .deqA_08[6] = 0x0A,  .deqA_08[7] = 0x0A, .deqA_08[8] = 0x0A, .deqA_08[9] = 0x0A, .deqA_08[10] = 0x0A,	// BankA 0x37
			.deqA_09[0] = 0x00, .deqA_09[1] = 0x00, .deqA_09[2] = 0x00, .deqA_09[3] = 0x00, .deqA_09[4] = 0x00, .deqA_09[5] = 0x00, .deqA_09[6] = 0x00,  .deqA_09[7] = 0x00, .deqA_09[8] = 0x00, .deqA_09[9] = 0x00, .deqA_09[10] = 0x00,	// BankA 0x38
			.deqA_10[0] = 0x02, .deqA_10[1] = 0x02, .deqA_10[2] = 0x02, .deqA_10[3] = 0x02, .deqA_10[4] = 0x02, .deqA_10[5] = 0x02, .deqA_10[6] = 0x02,  .deqA_10[7] = 0x02, .deqA_10[8] = 0x02, .deqA_10[9] = 0x02, .deqA_10[10] = 0x02,	// BankA 0x39
			.deqA_11[0] = 0x00, .deqA_11[1] = 0x00, .deqA_11[2] = 0x00, .deqA_11[3] = 0x00, .deqA_11[4] = 0x00, .deqA_11[5] = 0x00, .deqA_11[6] = 0x00,  .deqA_11[7] = 0x00, .deqA_11[8] = 0x00, .deqA_11[9] = 0x00, .deqA_11[10] = 0x00,	// BankA 0x3a
			.deqA_12[0] = 0xB2, .deqA_12[1] = 0xB2, .deqA_12[2] = 0xB2, .deqA_12[3] = 0xB2, .deqA_12[4] = 0xB2, .deqA_12[5] = 0xB2, .deqA_12[6] = 0xB2,  .deqA_12[7] = 0xB2, .deqA_12[8] = 0xB2, .deqA_12[9] = 0xB2, .deqA_12[10] = 0xB2,	// BankA 0x3b
		},
		/* color */
		{
			.contrast[0] 		= 0x88, .contrast[1] 		= 0x8c, .contrast[2] 		= 0x8a, .contrast[3] 		= 0x87, .contrast[4] 		= 0x85, .contrast[5] 		= 0x84, .contrast[6] 		= 0x80, .contrast[7] 		= 0x80, .contrast[8] 		= 0x79, .contrast[9] 		= 0x72, .contrast[10] 		= 0x72,
			.h_peaking[0] 		= 0x00, .h_peaking[1] 		= 0x00, .h_peaking[2] 		= 0x00, .h_peaking[3] 		= 0x00, .h_peaking[4] 		= 0x00, .h_peaking[5] 		= 0x00, .h_peaking[6] 		= 0x00, .h_peaking[7] 		= 0x3f, .h_peaking[8] 		= 0x3f, .h_peaking[9] 		= 0x3f, .h_peaking[10] 		= 0x3f,
			.c_filter[0]		= 0x82, .c_filter[1] 		= 0x92, .c_filter[2]	 	= 0x92, .c_filter[3] 		= 0x92, .c_filter[4] 		= 0xa2, .c_filter[5] 		= 0xa2, .c_filter[6] 		= 0xb2, .c_filter[7] 		= 0xb2, .c_filter[8] 		= 0xb2, .c_filter[9] 		= 0xb2, .c_filter[10] 		= 0xb2,
			.hue[0] 			= 0x00, .hue[1] 			= 0x00, .hue[2] 			= 0x00, .hue[3] 			= 0x00, .hue[4] 			= 0x00, .hue[5] 			= 0x00, .hue[6] 			= 0x00, .hue[7] 			= 0x00, .hue[8] 			= 0x00, .hue[9] 			= 0x00, .hue[10] 			= 0x00,
			.u_gain[0] 			= 0x00, .u_gain[1] 			= 0x00, .u_gain[2] 			= 0x00, .u_gain[3] 			= 0x00, .u_gain[4] 			= 0x00, .u_gain[5] 			= 0x00, .u_gain[6] 			= 0x00, .u_gain[7] 			= 0x00, .u_gain[8] 			= 0x00, .u_gain[9] 			= 0x00, .u_gain[10] 		= 0x00,
			.v_gain[0] 			= 0x00, .v_gain[1] 			= 0x00, .v_gain[2] 			= 0x00, .v_gain[3] 			= 0x00, .v_gain[4] 			= 0x00, .v_gain[5] 			= 0x00, .v_gain[6] 			= 0x00, .v_gain[7] 			= 0x00, .v_gain[8] 			= 0x00, .v_gain[9] 			= 0x00, .v_gain[10] 		= 0x00,
			.u_offset[0] 		= 0x00, .u_offset[1] 		= 0x00, .u_offset[2] 		= 0x00, .u_offset[3] 		= 0x00, .u_offset[4] 		= 0x00, .u_offset[5] 		= 0x00, .u_offset[6] 		= 0x00, .u_offset[7] 		= 0x00, .u_offset[8] 		= 0x00, .u_offset[9] 		= 0x00, .u_offset[10] 		= 0x00,
			.v_offset[0] 		= 0x00, .v_offset[1] 		= 0x00, .v_offset[2] 		= 0x00, .v_offset[3] 		= 0x00, .v_offset[4] 		= 0x00, .v_offset[5] 		= 0x00, .v_offset[6] 		= 0x00, .v_offset[7] 		= 0x00, .v_offset[8] 		= 0x00, .v_offset[9] 		= 0x00, .v_offset[10] 		= 0x00,

			.black_level[0] 	= 0x84, .black_level[1] 	= 0x86, .black_level[2] 	= 0x84, .black_level[3] 	= 0x84, .black_level[4] 	= 0x86, .black_level[5] 	= 0x88, .black_level[6] 	= 0x8a, .black_level[7] 	= 0x90, .black_level[8] 	= 0x93, .black_level[9] 	= 0x96, .black_level[10] 	= 0x96,
			.acc_ref[0]			= 0x57, .acc_ref[1]			= 0x57, .acc_ref[2]			= 0x57, .acc_ref[3]			= 0x57, .acc_ref[4]			= 0x57, .acc_ref[5]			= 0x57, .acc_ref[6]			= 0x57, .acc_ref[7]			= 0x37, .acc_ref[8]			= 0x20, .acc_ref[9]			= 0x20, .acc_ref[10]		= 0x57,
			.cti_delay[0]		= 0x80, .cti_delay[1]		= 0x80, .cti_delay[2]		= 0x80, .cti_delay[3]		= 0x80, .cti_delay[4]		= 0x80, .cti_delay[5]		= 0x80, .cti_delay[6]		= 0x80, .cti_delay[7]		= 0x80, .cti_delay[8]		= 0x80, .cti_delay[9]		= 0x80, .cti_delay[10]		= 0x80,
			.sub_saturation[0] 	= 0xa8, .sub_saturation[1] 	= 0xaa, .sub_saturation[2] 	= 0xaa, .sub_saturation[3] 	= 0xac, .sub_saturation[4] 	= 0xa8, .sub_saturation[5] 	= 0xa6, .sub_saturation[6] 	= 0x98, .sub_saturation[7] 	= 0xa0, .sub_saturation[8] 	= 0xa0, .sub_saturation[9] 	= 0x50, .sub_saturation[10] = 0x50,

			.burst_dec_a[0] 	= 0x2a, .burst_dec_a[1] 	= 0x2a, .burst_dec_a[2] 	= 0x2a, .burst_dec_a[3] 	= 0x2a, .burst_dec_a[4] 	= 0x2a, .burst_dec_a[5] 	= 0x2a, .burst_dec_a[6] 	= 0x2a, .burst_dec_a[7] 	= 0x2a, .burst_dec_a[8] 	= 0x2a, .burst_dec_a[9] 	= 0x2a, .burst_dec_a[10] 	= 0x2a,
			.burst_dec_b[0] 	= 0x00, .burst_dec_b[1] 	= 0x00, .burst_dec_b[2] 	= 0x00, .burst_dec_b[3] 	= 0x00, .burst_dec_b[4] 	= 0x00, .burst_dec_b[5] 	= 0x00, .burst_dec_b[6] 	= 0x00, .burst_dec_b[7] 	= 0x00, .burst_dec_b[8] 	= 0x00, .burst_dec_b[9] 	= 0x00, .burst_dec_b[10] 	= 0x00,
			.burst_dec_c[0] 	= 0x30, .burst_dec_c[1] 	= 0x30, .burst_dec_c[2] 	= 0x30, .burst_dec_c[3] 	= 0x30, .burst_dec_c[4] 	= 0x30, .burst_dec_c[5] 	= 0x30, .burst_dec_c[6] 	= 0x30, .burst_dec_c[7] 	= 0x30, .burst_dec_c[8] 	= 0x30, .burst_dec_c[9] 	= 0x30, .burst_dec_c[10] 	= 0x30,

			.c_option[0] 		= 0x80, .c_option[1] 		= 0x80, .c_option[2] 		= 0x80, .c_option[3] 		= 0x80, .c_option[4] 		= 0xa0, .c_option[5] 		= 0xa0, .c_option[6] 		= 0xb0, .c_option[7] 		= 0xb0, .c_option[8] 		= 0xb0, .c_option[9] 		= 0xb0, .c_option[10] 		= 0xb0,

			.y_filter_b[0]		= 0x10, .y_filter_b[1]		= 0x10, .y_filter_b[2]		= 0x10, .y_filter_b[3]		= 0x10, .y_filter_b[4]		= 0x10, .y_filter_b[5]		= 0x10, .y_filter_b[6]		= 0x10, .y_filter_b[7]		= 0x10, .y_filter_b[8]		= 0x10, .y_filter_b[9]		= 0x10, .y_filter_b[10]		= 0x10,
			.y_filter_b_sel[0]	= 0x1e,	.y_filter_b_sel[1]	= 0x1e,	.y_filter_b_sel[2]	= 0x1e, .y_filter_b_sel[3]	= 0x1e, .y_filter_b_sel[4]	= 0x1e, .y_filter_b_sel[5]	= 0x1e, .y_filter_b_sel[6]	= 0x1e, .y_filter_b_sel[7]	= 0x1e, .y_filter_b_sel[8]	= 0x1e, .y_filter_b_sel[9]	= 0x1e, .y_filter_b_sel[10]	= 0x1e,
		},
		/* timing_a */
		{
			.h_delay_a[0] = 0x7b, .h_delay_a[1] = 0x7b, .h_delay_a[2] = 0x7a, .h_delay_a[3] = 0x79, .h_delay_a[4] = 0x79, .h_delay_a[5] = 0x7a, .h_delay_a[6] = 0x7a, .h_delay_a[7] = 0x7a, .h_delay_a[8] = 0x7a, .h_delay_a[9] = 0x7a, .h_delay_a[10] = 0x7a,
			.h_delay_b[0] = 0x10, .h_delay_b[1] = 0x10, .h_delay_b[2] = 0x10, .h_delay_b[3] = 0x10, .h_delay_b[4] = 0x10, .h_delay_b[5] = 0x10, .h_delay_b[6] = 0x10, .h_delay_b[7] = 0x10, .h_delay_b[8] = 0x10, .h_delay_b[9] = 0x10, .h_delay_b[10] = 0x10,
			.h_delay_c[0] = 0x00, .h_delay_c[1] = 0x00, .h_delay_c[2] = 0x00, .h_delay_c[3] = 0x00, .h_delay_c[4] = 0x00, .h_delay_c[5] = 0x00, .h_delay_c[6] = 0x00, .h_delay_c[7] = 0x00, .h_delay_c[8] = 0x00, .h_delay_c[9] = 0x00, .h_delay_c[10] = 0x00,
			.y_delay[0]   = 0x05, .y_delay[1]   = 0x05, .y_delay[2]   = 0x05, .y_delay[3]   = 0x05, .y_delay[4]   = 0x05, .y_delay[5] =   0x05, .y_delay[6] =   0x05, .y_delay[7] =   0x05, .y_delay[8] =   0x05, .y_delay[9] =   0x05, .y_delay[10] =   0x05,

		},
		/* clk */
		{
			.clk_adc[0] = 0x02, .clk_adc[1] = 0x02, .clk_adc[2] = 0x02, .clk_adc[3] = 0x02, .clk_adc[4] = 0x02, .clk_adc[5] = 0x02, .clk_adc[6] = 0x02, .clk_adc[7] = 0x02, .clk_adc[8] = 0x02, .clk_adc[9] = 0x02, .clk_adc[10] = 0x02,
			.clk_dec[0] = 0x40, .clk_dec[1] = 0x40, .clk_dec[2] = 0x40, .clk_dec[3] = 0x40, .clk_dec[4] = 0x40, .clk_dec[5] = 0x40, .clk_dec[6] = 0x40, .clk_dec[7] = 0x40, .clk_dec[8] = 0x40, .clk_dec[9] = 0x40, .clk_dec[10] = 0x40,
		},
		/* timing_b */
		{
	/*B9 0x96*/	.h_scaler1[0]  = 0x01, .h_scaler1[1]   = 0x01, .h_scaler1[2]   = 0x01, .h_scaler1[3]   = 0x01, .h_scaler1[4]   = 0x01, .h_scaler1[5]   = 0x01, .h_scaler1[6]   = 0x01, .h_scaler1[7]   = 0x01, .h_scaler1[8]   = 0x01, .h_scaler1[9]   = 0x01, .h_scaler1[10]   = 0x01,
	/*B9 0x97*/	.h_scaler2[0]  = 0x19, .h_scaler2[1]   = 0x19, .h_scaler2[2]   = 0x19, .h_scaler2[3]   = 0x19, .h_scaler2[4]   = 0x19, .h_scaler2[5]   = 0x19, .h_scaler2[6]   = 0x19, .h_scaler2[7]   = 0x19, .h_scaler2[8]   = 0x19, .h_scaler2[9]   = 0x19, .h_scaler2[10]   = 0x19,
	/*B9 0x98*/	.h_scaler3[0]  = 0x20, .h_scaler3[1]   = 0x20, .h_scaler3[2]   = 0x20, .h_scaler3[3]   = 0x20, .h_scaler3[4]   = 0x20, .h_scaler3[5]   = 0x20, .h_scaler3[6]   = 0x20, .h_scaler3[7]   = 0x20, .h_scaler3[8]   = 0x20, .h_scaler3[9]   = 0x20, .h_scaler3[10]   = 0x20,
	/*B9 0x99*/	.h_scaler4[0]  = 0x01, .h_scaler4[1]   = 0x01, .h_scaler4[2]   = 0x01, .h_scaler4[3]   = 0x01, .h_scaler4[4]   = 0x01, .h_scaler4[5]   = 0x01, .h_scaler4[6]   = 0x01, .h_scaler4[7]   = 0x01, .h_scaler4[8]   = 0x01, .h_scaler4[9]   = 0x01, .h_scaler4[10]   = 0x01,
	/*B9 0x9a*/	.h_scaler5[0]  = 0x00, .h_scaler5[1]   = 0x00, .h_scaler5[2]   = 0x00, .h_scaler5[3]   = 0x00, .h_scaler5[4]   = 0x00, .h_scaler5[5]   = 0x00, .h_scaler5[6]   = 0x00, .h_scaler5[7]   = 0x00, .h_scaler5[8]   = 0x00, .h_scaler5[9]   = 0x00, .h_scaler5[10]   = 0x00,
	/*B9 0x9b*/	.h_scaler6[0]  = 0x00, .h_scaler6[1]   = 0x00, .h_scaler6[2]   = 0x00, .h_scaler6[3]   = 0x00, .h_scaler6[4]   = 0x00, .h_scaler6[5]   = 0x00, .h_scaler6[6]   = 0x00, .h_scaler6[7]   = 0x00, .h_scaler6[8]   = 0x00, .h_scaler6[9]   = 0x00, .h_scaler6[10]   = 0x00,
	/*B9 0x9c*/	.h_scaler7[0]  = 0x00, .h_scaler7[1]   = 0x00, .h_scaler7[2]   = 0x00, .h_scaler7[3]   = 0x00, .h_scaler7[4]   = 0x00, .h_scaler7[5]   = 0x00, .h_scaler7[6]   = 0x00, .h_scaler7[7]   = 0x00, .h_scaler7[8]   = 0x00, .h_scaler7[9]   = 0x00, .h_scaler7[10]   = 0x00,
	/*B9 0x9d*/	.h_scaler8[0]  = 0x00, .h_scaler8[1]   = 0x00, .h_scaler8[2]   = 0x00, .h_scaler8[3]   = 0x00, .h_scaler8[4]   = 0x00, .h_scaler8[5]   = 0x00, .h_scaler8[6]   = 0x00, .h_scaler8[7]   = 0x00, .h_scaler8[8]   = 0x00, .h_scaler8[9]   = 0x00, .h_scaler8[10]   = 0x00,
	/*B9 0x9e*/	.h_scaler9[0]  = 0x80, .h_scaler9[1]   = 0x80, .h_scaler9[2]   = 0x80, .h_scaler9[3]   = 0x80, .h_scaler9[4]   = 0x80, .h_scaler9[5]   = 0x80, .h_scaler9[6]   = 0x80, .h_scaler9[7]   = 0x80, .h_scaler9[8]   = 0x80, .h_scaler9[9]   = 0x80, .h_scaler9[10]   = 0x80,


	/*B9 0x40*/	.pn_auto[0]    	= 0x00, .pn_auto[1]		= 0x00, .pn_auto[2]    	= 0x00, .pn_auto[3]    	= 0x00, .pn_auto[4]    	= 0x00, .pn_auto[5]    	= 0x00, .pn_auto[6]		= 0x00, .pn_auto[7]    	= 0x00, .pn_auto[8]    	= 0x00, .pn_auto[9]    	= 0x00, .pn_auto[10]    	= 0x00,

	/*B5 0x90*/	.comb_mode[0]   = 0x05, .comb_mode[1]	= 0x05, .comb_mode[2]   = 0x05, .comb_mode[3]   = 0x05, .comb_mode[4]  	= 0x05, .comb_mode[5]   = 0x05, .comb_mode[6]	= 0x05, .comb_mode[7]   = 0x05, .comb_mode[8]   = 0x05, .comb_mode[9]  	= 0x05, .comb_mode[10]   = 0x05,
	/*B9 0xb9*/	.h_pll_op_a[0]  = 0x72, .h_pll_op_a[1]  = 0x72, .h_pll_op_a[2]  = 0x72, .h_pll_op_a[3]  = 0x72, .h_pll_op_a[4]  = 0x72, .h_pll_op_a[5]  = 0x72, .h_pll_op_a[6]  = 0x72, .h_pll_op_a[7]  = 0x72, .h_pll_op_a[8]  = 0x72, .h_pll_op_a[9]  = 0x72, .h_pll_op_a[10]  = 0x72,
	/*B9 0x57*/	.mem_path[0]	= 0x10, .mem_path[1]	= 0x10, .mem_path[2]	= 0x10, .mem_path[3]	= 0x10, .mem_path[4]	= 0x10, .mem_path[5]	= 0x10, .mem_path[6]	= 0x10, .mem_path[7]	= 0x10, .mem_path[8]	= 0x10, .mem_path[9]	= 0x10, .mem_path[10]	 = 0x10,
			.fsc_lock_speed[0] = 0xdc, .fsc_lock_speed[1] = 0xdc, .fsc_lock_speed[2] = 0xdc, .fsc_lock_speed[3] = 0xdc, .fsc_lock_speed[4] = 0xdc, .fsc_lock_speed[5] = 0xdc, .fsc_lock_speed[6] = 0xdc, .fsc_lock_speed[7] = 0xdc, .fsc_lock_speed[8] = 0xdc, .fsc_lock_speed[9] = 0xdc, .fsc_lock_speed[10] = 0xdc,

	/*B0 0x81*/	.format_set1[0] = 0x0a, .format_set1[1] = 0x0a, .format_set1[2] = 0x0a, .format_set1[3] = 0x0a, .format_set1[4] = 0x0a, .format_set1[5] = 0x0a, .format_set1[6] = 0x0a, .format_set1[7] = 0x0a, .format_set1[8] = 0x0a, .format_set1[9] = 0x0a, .format_set1[10] = 0x0a,
	/*B0 0x85*/	.format_set2[0] = 0x02, .format_set2[1] = 0x02, .format_set2[2] = 0x02, .format_set2[3] = 0x02, .format_set2[4] = 0x02, .format_set2[5] = 0x02, .format_set2[6] = 0x02, .format_set2[7] = 0x02, .format_set2[8] = 0x02, .format_set2[9] = 0x02, .format_set2[10] = 0x02,

	/*B0 0x64*/ .v_delay[0]     = 0x20, .v_delay[1]     = 0x20, .v_delay[2]     = 0x20, .v_delay[3]     = 0x20, .v_delay[4]     = 0x20, .v_delay[5]     = 0x20, .v_delay[6]     = 0x20, .v_delay[7]     = 0x20, .v_delay[8]     = 0x20, .v_delay[9]     = 0x20, .v_delay[10]     = 0x20,
		},
	},
	[ CVI_HD_50P ] = { /* o */
		/* base */
		{
			.eq_bypass[0] 	= 0x62, .eq_bypass[1] 	= 0x22, .eq_bypass[2] 	= 0x22, .eq_bypass[3] 	= 0x22, .eq_bypass[4] 	= 0x22, .eq_bypass[5] 	= 0x22,    // Bank5 0x30
			.eq_band_sel[0] = 0x77, .eq_band_sel[1] = 0x77, .eq_band_sel[2] = 0x77, .eq_band_sel[3] = 0x77, .eq_band_sel[4] = 0x67, .eq_band_sel[5] = 0x47,    // BankA 0x31
			.eq_gain_sel[0] = 0x78, .eq_gain_sel[1] = 0x7f, .eq_gain_sel[2] = 0x6f, .eq_gain_sel[3] = 0x7f, .eq_gain_sel[4] = 0x7f, .eq_gain_sel[5] = 0x7f,    // BankA 0x32
			.deq_a_on[0] 	= 0x00, .deq_a_on[1] 	= 0x01, .deq_a_on[2] 	= 0x01, .deq_a_on[3] 	= 0x01, .deq_a_on[4] 	= 0x01, .deq_a_on[5] 	= 0x01,    // BankA 0x33
			.deq_a_sel[0] 	= 0x00, .deq_a_sel[1] 	= 0x92, .deq_a_sel[2] 	= 0x93, .deq_a_sel[3] 	= 0x94, .deq_a_sel[4] 	= 0x95, .deq_a_sel[5] 	= 0x93,    // BankA 0x34
			.deq_b_sel[0] 	= 0x00, .deq_b_sel[1] 	= 0x00, .deq_b_sel[2] 	= 0x00, .deq_b_sel[3] 	= 0x00, .deq_b_sel[4] 	= 0x00, .deq_b_sel[5] 	= 0x00,    // BankA 0x35
		},
		/* coeff */
		{
			.deqA_01[0] = 0xAC, .deqA_01[1] = 0xAC, .deqA_01[2] = 0xAC, .deqA_01[3] = 0xAC, .deqA_01[4] = 0xAC, .deqA_01[5] = 0xAC,		// BankA 0x30
			.deqA_02[0] = 0x78, .deqA_02[1] = 0x78, .deqA_02[2] = 0x78, .deqA_02[3] = 0x78, .deqA_02[4] = 0x78, .deqA_02[5] = 0x78,		// BankA 0x31
			.deqA_03[0] = 0x17, .deqA_03[1] = 0x17, .deqA_03[2] = 0x17, .deqA_03[3] = 0x17, .deqA_03[4] = 0x17, .deqA_03[5] = 0x17,		// BankA 0x32
			.deqA_04[0] = 0xC1, .deqA_04[1] = 0xC1, .deqA_04[2] = 0xC1, .deqA_04[3] = 0xC1, .deqA_04[4] = 0xC1, .deqA_04[5] = 0xC1,     // BankA 0x33
			.deqA_05[0] = 0x40, .deqA_05[1] = 0x40, .deqA_05[2] = 0x40, .deqA_05[3] = 0x40, .deqA_05[4] = 0x40, .deqA_05[5] = 0x40,     // BankA 0x34
			.deqA_06[0] = 0x00, .deqA_06[1] = 0x00, .deqA_06[2] = 0x00, .deqA_06[3] = 0x00, .deqA_06[4] = 0x00, .deqA_06[5] = 0x00,     // BankA 0x35
			.deqA_07[0] = 0xC3, .deqA_07[1] = 0xC3, .deqA_07[2] = 0xC3, .deqA_07[3] = 0xC3, .deqA_07[4] = 0xC3, .deqA_07[5] = 0xC3,     // BankA 0x36
			.deqA_08[0] = 0x0A, .deqA_08[1] = 0x0A, .deqA_08[2] = 0x0A, .deqA_08[3] = 0x0A, .deqA_08[4] = 0x0A, .deqA_08[5] = 0x0A,     // BankA 0x37
			.deqA_09[0] = 0x00, .deqA_09[1] = 0x00, .deqA_09[2] = 0x00, .deqA_09[3] = 0x00, .deqA_09[4] = 0x00, .deqA_09[5] = 0x00,     // BankA 0x38
			.deqA_10[0] = 0x02, .deqA_10[1] = 0x02, .deqA_10[2] = 0x02, .deqA_10[3] = 0x02, .deqA_10[4] = 0x02, .deqA_10[5] = 0x02,     // BankA 0x39
			.deqA_11[0] = 0x00, .deqA_11[1] = 0x00, .deqA_11[2] = 0x00, .deqA_11[3] = 0x00, .deqA_11[4] = 0x00, .deqA_11[5] = 0x00,     // BankA 0x3a
			.deqA_12[0] = 0xB2, .deqA_12[1] = 0xB2, .deqA_12[2] = 0xB2, .deqA_12[3] = 0xB2, .deqA_12[4] = 0xB2, .deqA_12[5] = 0xB2,     // BankA 0x3b
	},
		/* color */
		{
			.contrast[0] 		= 0x98, .contrast[1] 		= 0x98, .contrast[2] 		= 0x98, .contrast[3] 		= 0x98, .contrast[4] 		= 0x98, .contrast[5] 		= 0x98,
			.h_peaking[0] 		= 0x00, .h_peaking[1] 		= 0x00, .h_peaking[2] 		= 0x00, .h_peaking[3] 		= 0x00, .h_peaking[4] 		= 0x00, .h_peaking[5] 		= 0x00,
			.c_filter[0]		= 0x92, .c_filter[1] 		= 0x92, .c_filter[2]	 	= 0x92, .c_filter[3] 		= 0x92, .c_filter[4] 		= 0xb2, .c_filter[5] 		= 0xb2,

			.hue[0] 			= 0x03, .hue[1] 			= 0x03, .hue[2] 			= 0x04, .hue[3] 			= 0x04, .hue[4] 			= 0x04, .hue[5] 			= 0x04,
			.u_gain[0] 			= 0x0c, .u_gain[1] 			= 0x0c, .u_gain[2] 			= 0x0c, .u_gain[3] 			= 0x0c, .u_gain[4] 			= 0x0c, .u_gain[5] 			= 0x0c,
			.v_gain[0] 			= 0x1a, .v_gain[1] 			= 0x1a, .v_gain[2] 			= 0x1a, .v_gain[3] 			= 0x1a, .v_gain[4] 			= 0x1a, .v_gain[5] 			= 0x1a,
			.u_offset[0] 		= 0xfa, .u_offset[1] 		= 0xfa, .u_offset[2] 		= 0xfa, .u_offset[3] 		= 0xfa, .u_offset[4] 		= 0xfa, .u_offset[5] 		= 0xfa,
			.v_offset[0] 		= 0xfa, .v_offset[1] 		= 0xfa, .v_offset[2] 		= 0xfa, .v_offset[3] 		= 0xfa, .v_offset[4] 		= 0xfa, .v_offset[5] 		= 0xfa,

			.black_level[0] 	= 0x86, .black_level[1] 	= 0x7a, .black_level[2] 	= 0x88, .black_level[3] 	= 0x84, .black_level[4] 	= 0x84, .black_level[5] 	= 0x84,
			.acc_ref[0]			= 0x57, .acc_ref[1]			= 0x57, .acc_ref[2]			= 0x57, .acc_ref[3]			= 0x57, .acc_ref[4]			= 0x47, .acc_ref[5]			= 0x37,
			.cti_delay[0]		= 0x80, .cti_delay[1]		= 0x80, .cti_delay[2]		= 0x80, .cti_delay[3]		= 0x80, .cti_delay[4]		= 0x80, .cti_delay[5]		= 0x80,
			.sub_saturation[0] 	= 0xa8, .sub_saturation[1] 	= 0xa0, .sub_saturation[2] 	= 0xa0, .sub_saturation[3] 	= 0x90, .sub_saturation[4] 	= 0x90, .sub_saturation[5] 	= 0x90,

			.burst_dec_a[0] 	= 0x2a, .burst_dec_a[1] 	= 0x2a, .burst_dec_a[2] 	= 0x2a, .burst_dec_a[3] 	= 0x2a, .burst_dec_a[4] 	= 0x2a, .burst_dec_a[5] 	= 0x2a,
			.burst_dec_b[0] 	= 0x00, .burst_dec_b[1] 	= 0x00, .burst_dec_b[2] 	= 0x00, .burst_dec_b[3] 	= 0x00, .burst_dec_b[4] 	= 0x00, .burst_dec_b[5] 	= 0x00,
			.burst_dec_c[0] 	= 0x30, .burst_dec_c[1] 	= 0x30, .burst_dec_c[2] 	= 0x30, .burst_dec_c[3] 	= 0x30, .burst_dec_c[4] 	= 0x30, .burst_dec_c[5] 	= 0x30,

			.c_option[0] 		= 0xc0, .c_option[1] 		= 0xc0, .c_option[2] 		= 0xc0, .c_option[3] 		= 0xc0, .c_option[4] 		= 0xc0, .c_option[5] 		= 0xc0,
			.y_filter_b[0]		= 0x10, .y_filter_b[1]		= 0x10, .y_filter_b[2]		= 0x10, .y_filter_b[3]		= 0x10, .y_filter_b[4]		= 0x10, .y_filter_b[5]		= 0x10,
			.y_filter_b_sel[0]	= 0x1e,	.y_filter_b_sel[1]	= 0x1e,	.y_filter_b_sel[2]	= 0x1e, .y_filter_b_sel[3]	= 0x1e, .y_filter_b_sel[4]	= 0x1e, .y_filter_b_sel[5]	= 0x1e,
		},
		/* timing_a */
		{
			.h_delay_a[0] = 0x80, .h_delay_a[1] = 0x80, .h_delay_a[2] = 0x80, .h_delay_a[3] = 0x80, .h_delay_a[4] = 0x80, .h_delay_a[5] = 0x80,
			.h_delay_b[0] = 0x10, .h_delay_b[1] = 0x10, .h_delay_b[2] = 0x10, .h_delay_b[3] = 0x10, .h_delay_b[4] = 0x10, .h_delay_b[5] = 0x10,
			.h_delay_c[0] = 0x01, .h_delay_c[1] = 0x01, .h_delay_c[2] = 0x01, .h_delay_c[3] = 0x01, .h_delay_c[4] = 0x01, .h_delay_c[5] = 0x01,
			.y_delay[0]   = 0x02, .y_delay[1]   = 0x02, .y_delay[2]   = 0x02, .y_delay[3]   = 0x02, .y_delay[4]   = 0x02, .y_delay[5]   = 0x02,

		},
		/* clk */
		{
			.clk_adc[0] = 0x05, .clk_adc[1] = 0x05, .clk_adc[2] = 0x05, .clk_adc[3] = 0x05, .clk_adc[4] = 0x05, .clk_adc[5] = 0x05,
			.clk_dec[0] = 0x44, .clk_dec[1] = 0x44, .clk_dec[2] = 0x44, .clk_dec[3] = 0x44, .clk_dec[4] = 0x44, .clk_dec[5] = 0x44,
		},
		/* timing_b */
		{
			.h_scaler1[0]  = 0x01, .h_scaler1[1]   = 0x01, .h_scaler1[2]   = 0x01, .h_scaler1[3]   = 0x01, .h_scaler1[4]   = 0x01, .h_scaler1[5]   = 0x01,
			.h_scaler2[0]  = 0x29, .h_scaler2[1]   = 0x29, .h_scaler2[2]   = 0x29, .h_scaler2[3]   = 0x29, .h_scaler2[4]   = 0x29, .h_scaler2[5]   = 0x29,
			.h_scaler3[0]  = 0xc0, .h_scaler3[1]   = 0xc0, .h_scaler3[2]   = 0xc0, .h_scaler3[3]   = 0xc0, .h_scaler3[4]   = 0xc0, .h_scaler3[5]   = 0xc0,
			.h_scaler4[0]  = 0x01, .h_scaler4[1]   = 0x01, .h_scaler4[2]   = 0x01, .h_scaler4[3]   = 0x01, .h_scaler4[4]   = 0x01, .h_scaler4[5]   = 0x01,
/*B9 0x9a*/	.h_scaler5[0]  = 0x00, .h_scaler5[1]   = 0x00, .h_scaler5[2]   = 0x00, .h_scaler5[3]   = 0x00, .h_scaler5[4]   = 0x00, .h_scaler5[5]   = 0x00,
/*B9 0x9b*/	.h_scaler6[0]  = 0x00, .h_scaler6[1]   = 0x00, .h_scaler6[2]   = 0x00, .h_scaler6[3]   = 0x00, .h_scaler6[4]   = 0x00, .h_scaler6[5]   = 0x00,
/*B9 0x9c*/	.h_scaler7[0]  = 0x00, .h_scaler7[1]   = 0x00, .h_scaler7[2]   = 0x00, .h_scaler7[3]   = 0x00, .h_scaler7[4]   = 0x00, .h_scaler7[5]   = 0x00,
/*B9 0x9d*/	.h_scaler8[0]  = 0x00, .h_scaler8[1]   = 0x00, .h_scaler8[2]   = 0x00, .h_scaler8[3]   = 0x00, .h_scaler8[4]   = 0x00, .h_scaler8[5]   = 0x00,
/*B9 0x9e*/	.h_scaler9[0]  = 0x80, .h_scaler9[1]   = 0x80, .h_scaler9[2]   = 0x80, .h_scaler9[3]   = 0x80, .h_scaler9[4]   = 0x80, .h_scaler9[5]   = 0x80,

			.pn_auto[0]    	= 0x00, .pn_auto[1]		= 0x00, .pn_auto[2]    	= 0x00, .pn_auto[3]    	= 0x00, .pn_auto[4]    	= 0x00, .pn_auto[5]    	= 0x00,
			.comb_mode[0]   = 0x05, .comb_mode[1]	= 0x05, .comb_mode[2]   = 0x05, .comb_mode[3]   = 0x05, .comb_mode[4]  	= 0x05, .comb_mode[5]   = 0x05,
			.h_pll_op_a[0]  = 0x72, .h_pll_op_a[1]  = 0x72, .h_pll_op_a[2]  = 0x72, .h_pll_op_a[3]  = 0x72, .h_pll_op_a[4]  = 0x72, .h_pll_op_a[5]  = 0x72,
			.mem_path[0]	= 0x10, .mem_path[1]	= 0x10, .mem_path[2]	= 0x10, .mem_path[3]	= 0x10, .mem_path[4]	= 0x10, .mem_path[5]	= 0x10,
			.fsc_lock_speed[0] = 0xdc, .fsc_lock_speed[1] = 0xdc, .fsc_lock_speed[2] = 0xdc, .fsc_lock_speed[3] = 0xdc, .fsc_lock_speed[4] = 0xdc, .fsc_lock_speed[5] = 0xdc,

			.format_set1[0] = 0x05, .format_set1[1] = 0x05, .format_set1[2] = 0x05, .format_set1[3] = 0x05, .format_set1[4] = 0x05, .format_set1[5] = 0x05,
			.format_set2[0] = 0x02, .format_set2[1] = 0x02, .format_set2[2] = 0x02, .format_set2[3] = 0x02, .format_set2[4] = 0x02, .format_set2[5] = 0x02,

			.v_delay[0]     = 0x21, .v_delay[1]     = 0x21, .v_delay[2]     = 0x21, .v_delay[3]     = 0x21, .v_delay[4]     = 0x21, .v_delay[5]     = 0x21,
		},
	},
	[ CVI_HD_60P ] = { /* o */
		/* base */
		{
			.eq_bypass[0] 	= 0x62, .eq_bypass[1] 	= 0x22, .eq_bypass[2] 	= 0x22, .eq_bypass[3] 	= 0x22, .eq_bypass[4] 	= 0x22, .eq_bypass[5] 	= 0x22,    // Bank5 0x30
			.eq_band_sel[0] = 0x77, .eq_band_sel[1] = 0x77, .eq_band_sel[2] = 0x77, .eq_band_sel[3] = 0x77, .eq_band_sel[4] = 0x67, .eq_band_sel[5] = 0x47,    // BankA 0x31
			.eq_gain_sel[0] = 0x78, .eq_gain_sel[1] = 0x7f, .eq_gain_sel[2] = 0x6f, .eq_gain_sel[3] = 0x7f, .eq_gain_sel[4] = 0x7f, .eq_gain_sel[5] = 0x7f,    // BankA 0x32
			.deq_a_on[0] 	= 0x00, .deq_a_on[1] 	= 0x01, .deq_a_on[2] 	= 0x01, .deq_a_on[3] 	= 0x01, .deq_a_on[4] 	= 0x01, .deq_a_on[5] 	= 0x01,    // BankA 0x33
			.deq_a_sel[0] 	= 0x00, .deq_a_sel[1] 	= 0x92, .deq_a_sel[2] 	= 0x93, .deq_a_sel[3] 	= 0x94, .deq_a_sel[4] 	= 0x95, .deq_a_sel[5] 	= 0x93,    // BankA 0x34
			.deq_b_sel[0] 	= 0x00, .deq_b_sel[1] 	= 0x00, .deq_b_sel[2] 	= 0x00, .deq_b_sel[3] 	= 0x00, .deq_b_sel[4] 	= 0x00, .deq_b_sel[5] 	= 0x00,    // BankA 0x35
		},
		/* coeff */
		{
			.deqA_01[0] = 0xAC, .deqA_01[1] = 0xAC, .deqA_01[2] = 0xAC, .deqA_01[3] = 0xAC, .deqA_01[4] = 0xAC, .deqA_01[5] = 0xAC,		// BankA 0x30
			.deqA_02[0] = 0x78, .deqA_02[1] = 0x78, .deqA_02[2] = 0x78, .deqA_02[3] = 0x78, .deqA_02[4] = 0x78, .deqA_02[5] = 0x78,		// BankA 0x31
			.deqA_03[0] = 0x17, .deqA_03[1] = 0x17, .deqA_03[2] = 0x17, .deqA_03[3] = 0x17, .deqA_03[4] = 0x17, .deqA_03[5] = 0x17,		// BankA 0x32
			.deqA_04[0] = 0xC1, .deqA_04[1] = 0xC1, .deqA_04[2] = 0xC1, .deqA_04[3] = 0xC1, .deqA_04[4] = 0xC1, .deqA_04[5] = 0xC1,     // BankA 0x33
			.deqA_05[0] = 0x40, .deqA_05[1] = 0x40, .deqA_05[2] = 0x40, .deqA_05[3] = 0x40, .deqA_05[4] = 0x40, .deqA_05[5] = 0x40,     // BankA 0x34
			.deqA_06[0] = 0x00, .deqA_06[1] = 0x00, .deqA_06[2] = 0x00, .deqA_06[3] = 0x00, .deqA_06[4] = 0x00, .deqA_06[5] = 0x00,     // BankA 0x35
			.deqA_07[0] = 0xC3, .deqA_07[1] = 0xC3, .deqA_07[2] = 0xC3, .deqA_07[3] = 0xC3, .deqA_07[4] = 0xC3, .deqA_07[5] = 0xC3,     // BankA 0x36
			.deqA_08[0] = 0x0A, .deqA_08[1] = 0x0A, .deqA_08[2] = 0x0A, .deqA_08[3] = 0x0A, .deqA_08[4] = 0x0A, .deqA_08[5] = 0x0A,     // BankA 0x37
			.deqA_09[0] = 0x00, .deqA_09[1] = 0x00, .deqA_09[2] = 0x00, .deqA_09[3] = 0x00, .deqA_09[4] = 0x00, .deqA_09[5] = 0x00,     // BankA 0x38
			.deqA_10[0] = 0x02, .deqA_10[1] = 0x02, .deqA_10[2] = 0x02, .deqA_10[3] = 0x02, .deqA_10[4] = 0x02, .deqA_10[5] = 0x02,     // BankA 0x39
			.deqA_11[0] = 0x00, .deqA_11[1] = 0x00, .deqA_11[2] = 0x00, .deqA_11[3] = 0x00, .deqA_11[4] = 0x00, .deqA_11[5] = 0x00,     // BankA 0x3a
			.deqA_12[0] = 0xB2, .deqA_12[1] = 0xB2, .deqA_12[2] = 0xB2, .deqA_12[3] = 0xB2, .deqA_12[4] = 0xB2, .deqA_12[5] = 0xB2,     // BankA 0x3b
		},
		/* color */
		{
			.contrast[0] 		= 0x98, .contrast[1] 		= 0x98, .contrast[2] 		= 0x98, .contrast[3] 		= 0x98, .contrast[4] 		= 0x98, .contrast[5] 		= 0x98,
			.h_peaking[0] 		= 0x00, .h_peaking[1] 		= 0x00, .h_peaking[2] 		= 0x00, .h_peaking[3] 		= 0x00, .h_peaking[4] 		= 0x00, .h_peaking[5] 		= 0x00,
			.c_filter[0]		= 0x92, .c_filter[1] 		= 0x92, .c_filter[2]	 	= 0x92, .c_filter[3] 		= 0x92, .c_filter[4] 		= 0xb2, .c_filter[5] 		= 0xb2,

			.hue[0] 			= 0x03, .hue[1] 			= 0x03, .hue[2] 			= 0x04, .hue[3] 			= 0x04, .hue[4] 			= 0x04, .hue[5] 			= 0x04,
			.u_gain[0] 			= 0x0c, .u_gain[1] 			= 0x0c, .u_gain[2] 			= 0x0c, .u_gain[3] 			= 0x0c, .u_gain[4] 			= 0x0c, .u_gain[5] 			= 0x0c,
			.v_gain[0] 			= 0x1a, .v_gain[1] 			= 0x1a, .v_gain[2] 			= 0x1a, .v_gain[3] 			= 0x1a, .v_gain[4] 			= 0x1a, .v_gain[5] 			= 0x1a,
			.u_offset[0] 		= 0xfa, .u_offset[1] 		= 0xfa, .u_offset[2] 		= 0xfa, .u_offset[3] 		= 0xfa, .u_offset[4] 		= 0xfa, .u_offset[5] 		= 0xfa,
			.v_offset[0] 		= 0xfa, .v_offset[1] 		= 0xfa, .v_offset[2] 		= 0xfa, .v_offset[3] 		= 0xfa, .v_offset[4] 		= 0xfa, .v_offset[5] 		= 0xfa,

			.black_level[0] 	= 0x86, .black_level[1] 	= 0x7a, .black_level[2] 	= 0x88, .black_level[3] 	= 0x84, .black_level[4] 	= 0x84, .black_level[5] 	= 0x84,
			.acc_ref[0]			= 0x57, .acc_ref[1]			= 0x57, .acc_ref[2]			= 0x57, .acc_ref[3]			= 0x57, .acc_ref[4]			= 0x47, .acc_ref[5]			= 0x37,
			.cti_delay[0]		= 0x80, .cti_delay[1]		= 0x80, .cti_delay[2]		= 0x80, .cti_delay[3]		= 0x80, .cti_delay[4]		= 0x80, .cti_delay[5]		= 0x80,
			.sub_saturation[0] 	= 0xa8, .sub_saturation[1] 	= 0xa0, .sub_saturation[2] 	= 0xa0, .sub_saturation[3] 	= 0x90, .sub_saturation[4] 	= 0x90, .sub_saturation[5] 	= 0x90,

			.burst_dec_a[0] 	= 0x2a, .burst_dec_a[1] 	= 0x2a, .burst_dec_a[2] 	= 0x2a, .burst_dec_a[3] 	= 0x2a, .burst_dec_a[4] 	= 0x2a, .burst_dec_a[5] 	= 0x2a,
			.burst_dec_b[0] 	= 0x00, .burst_dec_b[1] 	= 0x00, .burst_dec_b[2] 	= 0x00, .burst_dec_b[3] 	= 0x00, .burst_dec_b[4] 	= 0x00, .burst_dec_b[5] 	= 0x00,
			.burst_dec_c[0] 	= 0x30, .burst_dec_c[1] 	= 0x30, .burst_dec_c[2] 	= 0x30, .burst_dec_c[3] 	= 0x30, .burst_dec_c[4] 	= 0x30, .burst_dec_c[5] 	= 0x30,

			.c_option[0] 		= 0xc0, .c_option[1] 		= 0xc0, .c_option[2] 		= 0xc0, .c_option[3] 		= 0xc0, .c_option[4] 		= 0xc0, .c_option[5] 		= 0xc0,
			.y_filter_b[0]		= 0x10, .y_filter_b[1]		= 0x10, .y_filter_b[2]		= 0x10, .y_filter_b[3]		= 0x10, .y_filter_b[4]		= 0x10, .y_filter_b[5]		= 0x10,
			.y_filter_b_sel[0]	= 0x1e,	.y_filter_b_sel[1]	= 0x1e,	.y_filter_b_sel[2]	= 0x1e, .y_filter_b_sel[3]	= 0x1e, .y_filter_b_sel[4]	= 0x1e, .y_filter_b_sel[5]	= 0x1e,

		},
		/* timing_a */
		{
			.h_delay_a[0] = 0x80, .h_delay_a[1] = 0x80, .h_delay_a[2] = 0x80, .h_delay_a[3] = 0x80, .h_delay_a[4] = 0x80, .h_delay_a[5] = 0x80,
			.h_delay_b[0] = 0x00, .h_delay_b[1] = 0x00, .h_delay_b[2] = 0x00, .h_delay_b[3] = 0x00, .h_delay_b[4] = 0x00, .h_delay_b[5] = 0x00,
			.h_delay_c[0] = 0x00, .h_delay_c[1] = 0x00, .h_delay_c[2] = 0x00, .h_delay_c[3] = 0x00, .h_delay_c[4] = 0x00, .h_delay_c[5] = 0x00,
			.y_delay[0]   = 0x02, .y_delay[1]   = 0x02, .y_delay[2]   = 0x02, .y_delay[3]   = 0x02, .y_delay[4]   = 0x02, .y_delay[5]   = 0x02,

		},
		/* clk */
		{
			.clk_adc[0] = 0x05, .clk_adc[1] = 0x05, .clk_adc[2] = 0x05, .clk_adc[3] = 0x05, .clk_adc[4] = 0x05, .clk_adc[5] = 0x05,
			.clk_dec[0] = 0x44, .clk_dec[1] = 0x44, .clk_dec[2] = 0x44, .clk_dec[3] = 0x44, .clk_dec[4] = 0x44, .clk_dec[5] = 0x44,
		},
		/* timing_b */
		{
			.h_scaler1[0]   = 0x01, .h_scaler1[1]   = 0x01, .h_scaler1[2]   = 0x01, .h_scaler1[3]   = 0x01, .h_scaler1[4]   = 0x01, .h_scaler1[5]   = 0x01,
			.h_scaler2[0]   = 0x19, .h_scaler2[1]   = 0x19, .h_scaler2[2]   = 0x19, .h_scaler2[3]   = 0x19, .h_scaler2[4]   = 0x19, .h_scaler2[5]   = 0x19,
			.h_scaler3[0]   = 0x19, .h_scaler3[1]   = 0x19, .h_scaler3[2]   = 0x19, .h_scaler3[3]   = 0x19, .h_scaler3[4]   = 0x19, .h_scaler3[5]   = 0x19,
			.h_scaler4[0]   = 0x01, .h_scaler4[1]   = 0x01, .h_scaler4[2]   = 0x01, .h_scaler4[3]   = 0x01, .h_scaler4[4]   = 0x01, .h_scaler4[5]   = 0x01,
/*B9 0x9a*/	.h_scaler5[0]   = 0x00, .h_scaler5[1]   = 0x00, .h_scaler5[2]   = 0x00, .h_scaler5[3]   = 0x00, .h_scaler5[4]   = 0x00, .h_scaler5[5]   = 0x00,
/*B9 0x9b*/	.h_scaler6[0]   = 0x00, .h_scaler6[1]   = 0x00, .h_scaler6[2]   = 0x00, .h_scaler6[3]   = 0x00, .h_scaler6[4]   = 0x00, .h_scaler6[5]   = 0x00,
/*B9 0x9c*/	.h_scaler7[0]   = 0x00, .h_scaler7[1]   = 0x00, .h_scaler7[2]   = 0x00, .h_scaler7[3]   = 0x00, .h_scaler7[4]   = 0x00, .h_scaler7[5]   = 0x00,
/*B9 0x9d*/	.h_scaler8[0]   = 0x00, .h_scaler8[1]   = 0x00, .h_scaler8[2]   = 0x00, .h_scaler8[3]   = 0x00, .h_scaler8[4]   = 0x00, .h_scaler8[5]   = 0x00,
/*B9 0x9e*/	.h_scaler9[0]   = 0x80, .h_scaler9[1]   = 0x80, .h_scaler9[2]   = 0x80, .h_scaler9[3]   = 0x80, .h_scaler9[4]   = 0x80, .h_scaler9[5]   = 0x80,
			.pn_auto[0]    	= 0x00, .pn_auto[1]		= 0x00, .pn_auto[2]    	= 0x00, .pn_auto[3]    	= 0x00, .pn_auto[4]    	= 0x00, .pn_auto[5]    	= 0x00,
			.comb_mode[0]   = 0x05, .comb_mode[1]	= 0x05, .comb_mode[2]   = 0x05, .comb_mode[3]   = 0x05, .comb_mode[4]  	= 0x05, .comb_mode[5]   = 0x05,
			.h_pll_op_a[0]  = 0x72, .h_pll_op_a[1]  = 0x72, .h_pll_op_a[2]  = 0x72, .h_pll_op_a[3]  = 0x72, .h_pll_op_a[4]  = 0x72, .h_pll_op_a[5]  = 0x72,
			.mem_path[0]	= 0x10, .mem_path[1]	= 0x10, .mem_path[2]	= 0x10, .mem_path[3]	= 0x10, .mem_path[4]	= 0x10, .mem_path[5]	= 0x10,
			.fsc_lock_speed[0] = 0xdc, .fsc_lock_speed[1] = 0xdc, .fsc_lock_speed[2] = 0xdc, .fsc_lock_speed[3] = 0xdc, .fsc_lock_speed[4] = 0xdc, .fsc_lock_speed[5] = 0xdc,

			.format_set1[0] = 0x04, .format_set1[1] = 0x04, .format_set1[2] = 0x04, .format_set1[3] = 0x04, .format_set1[4] = 0x04, .format_set1[5] = 0x04,
			.format_set2[0] = 0x02, .format_set2[1] = 0x02, .format_set2[2] = 0x02, .format_set2[3] = 0x02, .format_set2[4] = 0x02, .format_set2[5] = 0x02,

			.v_delay[0]     = 0x21, .v_delay[1]     = 0x21, .v_delay[2]     = 0x21, .v_delay[3]     = 0x21, .v_delay[4]     = 0x21, .v_delay[5]     = 0x21,
		},
	},

	[ TVI_HD_25P ] = /* o */
	{
		/* base */
		{
			.eq_bypass[0] 	= 0x22, .eq_bypass[1] 	= 0x22, .eq_bypass[2] 	= 0x22, .eq_bypass[3] 	= 0x22, .eq_bypass[4] 	= 0x22, .eq_bypass[5] 	= 0x22, .eq_bypass[6] 	= 0x22, .eq_bypass[7] 	= 0x22, .eq_bypass[8] 	= 0x22, .eq_bypass[9] 	= 0x22, .eq_bypass[10] 	 = 0x22,  // Bank5 0x30
			.eq_band_sel[0] = 0x77, .eq_band_sel[1] = 0x67, .eq_band_sel[2] = 0x57, .eq_band_sel[3] = 0x57, .eq_band_sel[4] = 0x57, .eq_band_sel[5] = 0x47, .eq_band_sel[6] = 0x37, .eq_band_sel[7] = 0x27, .eq_band_sel[8] = 0x17, .eq_band_sel[9] = 0x17, .eq_band_sel[10] = 0x07, // BankA 0x31
			.eq_gain_sel[0] = 0x78, .eq_gain_sel[1] = 0x78, .eq_gain_sel[2] = 0x78, .eq_gain_sel[3] = 0x7f, .eq_gain_sel[4] = 0x7f, .eq_gain_sel[5] = 0x7f, .eq_gain_sel[6] = 0x7f, .eq_gain_sel[7] = 0x7f, .eq_gain_sel[8] = 0x7f, .eq_gain_sel[9] = 0x7f, .eq_gain_sel[10] = 0x7f, // BankA 0x32
			.deq_a_on[0] 	= 0x00, .deq_a_on[1] 	= 0x01, .deq_a_on[2] 	= 0x01, .deq_a_on[3] 	= 0x01, .deq_a_on[4] 	= 0x01, .deq_a_on[5] 	= 0x01, .deq_a_on[6] 	= 0x01, .deq_a_on[7] 	= 0x01, .deq_a_on[8] 	= 0x01, .deq_a_on[9] 	= 0x01, .deq_a_on[10] 	 = 0x01, // BankA 0x33
			.deq_a_sel[0] 	= 0x00, .deq_a_sel[1] 	= 0x91, .deq_a_sel[2] 	= 0x92, .deq_a_sel[3] 	= 0x93, .deq_a_sel[4] 	= 0x93, .deq_a_sel[5] 	= 0x93, .deq_a_sel[6] 	= 0x93, .deq_a_sel[7] 	= 0x93, .deq_a_sel[8] 	= 0x93, .deq_a_sel[9] 	= 0x93, .deq_a_sel[10] 	 = 0x92, // BankA 0x34
			.deq_b_sel[0] 	= 0x00, .deq_b_sel[1] 	= 0x00, .deq_b_sel[2] 	= 0x00, .deq_b_sel[3] 	= 0x00, .deq_b_sel[4] 	= 0x00, .deq_b_sel[5] 	= 0x00, .deq_b_sel[6] 	= 0x00, .deq_b_sel[7] 	= 0x00, .deq_b_sel[8] 	= 0x00, .deq_b_sel[9] 	= 0x00, .deq_b_sel[10] 	 = 0x00, // BankA 0x35
		},
		/* coeff */
		{
			.deqA_01[0] = 0xAC, .deqA_01[1] = 0xAC, .deqA_01[2] = 0xAC, .deqA_01[3] = 0xAC, .deqA_01[4] = 0xAC, .deqA_01[5] = 0xAC,	.deqA_01[6] = 0xAC,  .deqA_01[7] = 0xAC, .deqA_01[8] = 0xAC, .deqA_01[9] = 0xAC, .deqA_01[10] = 0xAC,	// BankA 0x30
			.deqA_02[0] = 0x78, .deqA_02[1] = 0x78, .deqA_02[2] = 0x78, .deqA_02[3] = 0x78, .deqA_02[4] = 0x78, .deqA_02[5] = 0x78,	.deqA_02[6] = 0x78,	 .deqA_02[7] = 0x78, .deqA_02[8] = 0x78, .deqA_02[9] = 0x78, .deqA_02[10] = 0x78,	// BankA 0x31
			.deqA_03[0] = 0x17, .deqA_03[1] = 0x17, .deqA_03[2] = 0x17, .deqA_03[3] = 0x17, .deqA_03[4] = 0x17, .deqA_03[5] = 0x17,	.deqA_03[6] = 0x17,	 .deqA_03[7] = 0x17, .deqA_03[8] = 0x17, .deqA_03[9] = 0x17, .deqA_03[10] = 0x17,	// BankA 0x32
			.deqA_04[0] = 0xC1, .deqA_04[1] = 0xC1, .deqA_04[2] = 0xC1, .deqA_04[3] = 0xC1, .deqA_04[4] = 0xC1, .deqA_04[5] = 0xC1, .deqA_04[6] = 0xC1,  .deqA_04[7] = 0xC1, .deqA_04[8] = 0xC1, .deqA_04[9] = 0xC1, .deqA_04[10] = 0xC1,	// BankA 0x33
			.deqA_05[0] = 0x40, .deqA_05[1] = 0x40, .deqA_05[2] = 0x40, .deqA_05[3] = 0x40, .deqA_05[4] = 0x40, .deqA_05[5] = 0x40, .deqA_05[6] = 0x40,  .deqA_05[7] = 0x40, .deqA_05[8] = 0x40, .deqA_05[9] = 0x40, .deqA_05[10] = 0x40,	// BankA 0x34
			.deqA_06[0] = 0x00, .deqA_06[1] = 0x00, .deqA_06[2] = 0x00, .deqA_06[3] = 0x00, .deqA_06[4] = 0x00, .deqA_06[5] = 0x00, .deqA_06[6] = 0x00,  .deqA_06[7] = 0x00, .deqA_06[8] = 0x00, .deqA_06[9] = 0x00, .deqA_06[10] = 0x00,	// BankA 0x35
			.deqA_07[0] = 0xC3, .deqA_07[1] = 0xC3, .deqA_07[2] = 0xC3, .deqA_07[3] = 0xC3, .deqA_07[4] = 0xC3, .deqA_07[5] = 0xC3, .deqA_07[6] = 0xC3,  .deqA_07[7] = 0xC3, .deqA_07[8] = 0xC3, .deqA_07[9] = 0xC3, .deqA_07[10] = 0xC3,	// BankA 0x36
			.deqA_08[0] = 0x0A, .deqA_08[1] = 0x0A, .deqA_08[2] = 0x0A, .deqA_08[3] = 0x0A, .deqA_08[4] = 0x0A, .deqA_08[5] = 0x0A, .deqA_08[6] = 0x0A,  .deqA_08[7] = 0x0A, .deqA_08[8] = 0x0A, .deqA_08[9] = 0x0A, .deqA_08[10] = 0x0A,	// BankA 0x37
			.deqA_09[0] = 0x00, .deqA_09[1] = 0x00, .deqA_09[2] = 0x00, .deqA_09[3] = 0x00, .deqA_09[4] = 0x00, .deqA_09[5] = 0x00, .deqA_09[6] = 0x00,  .deqA_09[7] = 0x00, .deqA_09[8] = 0x00, .deqA_09[9] = 0x00, .deqA_09[10] = 0x00,	// BankA 0x38
			.deqA_10[0] = 0x02, .deqA_10[1] = 0x02, .deqA_10[2] = 0x02, .deqA_10[3] = 0x02, .deqA_10[4] = 0x02, .deqA_10[5] = 0x02, .deqA_10[6] = 0x02,  .deqA_10[7] = 0x02, .deqA_10[8] = 0x02, .deqA_10[9] = 0x02, .deqA_10[10] = 0x02,	// BankA 0x39
			.deqA_11[0] = 0x00, .deqA_11[1] = 0x00, .deqA_11[2] = 0x00, .deqA_11[3] = 0x00, .deqA_11[4] = 0x00, .deqA_11[5] = 0x00, .deqA_11[6] = 0x00,  .deqA_11[7] = 0x00, .deqA_11[8] = 0x00, .deqA_11[9] = 0x00, .deqA_11[10] = 0x00,	// BankA 0x3a
			.deqA_12[0] = 0xB2, .deqA_12[1] = 0xB2, .deqA_12[2] = 0xB2, .deqA_12[3] = 0xB2, .deqA_12[4] = 0xB2, .deqA_12[5] = 0xB2, .deqA_12[6] = 0xB2,  .deqA_12[7] = 0xB2, .deqA_12[8] = 0xB2, .deqA_12[9] = 0xB2, .deqA_12[10] = 0xB2,	// BankA 0x3b
		},
		/* color */
		{
			.contrast[0] 		= 0x82, .contrast[1] 		= 0x86, .contrast[2] 		= 0x84, .contrast[3] 		= 0x81, .contrast[4] 		= 0x7f, .contrast[5] 		= 0x7e, .contrast[6] 		= 0x7a, .contrast[7] 		= 0x7a, .contrast[8] 		= 0x72, .contrast[9] 		= 0x6d, .contrast[10] 		= 0x6d,
			.h_peaking[0] 		= 0x00, .h_peaking[1] 		= 0x00, .h_peaking[2] 		= 0x00, .h_peaking[3] 		= 0x00, .h_peaking[4] 		= 0x00, .h_peaking[5] 		= 0x00, .h_peaking[6] 		= 0x00, .h_peaking[7] 		= 0x3f, .h_peaking[8] 		= 0x3f, .h_peaking[9] 		= 0x3f, .h_peaking[10] 		= 0x3f,
			.c_filter[0]		= 0x82, .c_filter[1] 		= 0x92, .c_filter[2]	 	= 0x92, .c_filter[3] 		= 0xa2, .c_filter[4] 		= 0xa2, .c_filter[5] 		= 0xa2, .c_filter[6] 		= 0xb2, .c_filter[7] 		= 0xb2, .c_filter[8] 		= 0xb2, .c_filter[9] 		= 0xb2, .c_filter[10] 		= 0xb2,
			.hue[0] 			= 0x00, .hue[1] 			= 0x00, .hue[2] 			= 0x00, .hue[3] 			= 0x00, .hue[4] 			= 0x00, .hue[5] 			= 0x00, .hue[6] 			= 0x00, .hue[7] 			= 0x00, .hue[8] 			= 0x00, .hue[9] 			= 0x00, .hue[10] 			= 0x00,
			.u_gain[0] 			= 0xe0, .u_gain[1] 			= 0xe0, .u_gain[2] 			= 0xe0, .u_gain[3] 			= 0xe0, .u_gain[4] 			= 0xe0, .u_gain[5] 			= 0xe0, .u_gain[6] 			= 0xe0, .u_gain[7] 			= 0xe0, .u_gain[8] 			= 0xe0, .u_gain[9] 			= 0x00, .u_gain[10] 		= 0x00,
			.v_gain[0] 			= 0x00, .v_gain[1] 			= 0x00, .v_gain[2] 			= 0x00, .v_gain[3] 			= 0x00, .v_gain[4] 			= 0x00, .v_gain[5] 			= 0x00, .v_gain[6] 			= 0x00, .v_gain[7] 			= 0x00, .v_gain[8] 			= 0x00, .v_gain[9] 			= 0x00, .v_gain[10] 		= 0x00,
			.u_offset[0] 		= 0xff, .u_offset[1] 		= 0xff, .u_offset[2] 		= 0xff, .u_offset[3] 		= 0xff, .u_offset[4] 		= 0xff, .u_offset[5] 		= 0xff, .u_offset[6] 		= 0xff, .u_offset[7] 		= 0xff, .u_offset[8] 		= 0xff, .u_offset[9] 		= 0x00, .u_offset[10] 		= 0x00,
			.v_offset[0] 		= 0x00, .v_offset[1] 		= 0x00, .v_offset[2] 		= 0x00, .v_offset[3] 		= 0x00, .v_offset[4] 		= 0x00, .v_offset[5] 		= 0x00, .v_offset[6] 		= 0x00, .v_offset[7] 		= 0x00, .v_offset[8] 		= 0x00, .v_offset[9] 		= 0x00, .v_offset[10] 		= 0x00,

			.black_level[0] 	= 0x86, .black_level[1] 	= 0x88, .black_level[2] 	= 0x86, .black_level[3] 	= 0x86, .black_level[4] 	= 0x88, .black_level[5] 	= 0x8a, .black_level[6] 	= 0x8c, .black_level[7] 	= 0x92, .black_level[8] 	= 0x95, .black_level[9] 	= 0x98, .black_level[10] 	= 0x98,
			.acc_ref[0]			= 0x57, .acc_ref[1]			= 0x57, .acc_ref[2]			= 0x57, .acc_ref[3]			= 0x57, .acc_ref[4]			= 0x57, .acc_ref[5]			= 0x57, .acc_ref[6]			= 0x57, .acc_ref[7]			= 0x37, .acc_ref[8]			= 0x20, .acc_ref[9]			= 0x20, .acc_ref[10]		= 0x57,
			.cti_delay[0]		= 0x80, .cti_delay[1]		= 0x80, .cti_delay[2]		= 0x80, .cti_delay[3]		= 0x80, .cti_delay[4]		= 0x80, .cti_delay[5]		= 0x80, .cti_delay[6]		= 0x80, .cti_delay[7]		= 0x80, .cti_delay[8]		= 0x80, .cti_delay[9]		= 0x80, .cti_delay[10]		= 0x80,
			.sub_saturation[0] 	= 0xa8, .sub_saturation[1] 	= 0xaa, .sub_saturation[2] 	= 0xaa, .sub_saturation[3] 	= 0xac, .sub_saturation[4] 	= 0xa8, .sub_saturation[5] 	= 0xa6, .sub_saturation[6] 	= 0x98, .sub_saturation[7] 	= 0xa0, .sub_saturation[8] 	= 0xa0, .sub_saturation[9] 	= 0x50, .sub_saturation[10] = 0x50,

			.burst_dec_a[0] 	= 0x2a, .burst_dec_a[1] 	= 0x2a, .burst_dec_a[2] 	= 0x2a, .burst_dec_a[3] 	= 0x2a, .burst_dec_a[4] 	= 0x2a, .burst_dec_a[5] 	= 0x2a, .burst_dec_a[6] 	= 0x2a, .burst_dec_a[7] 	= 0x2a, .burst_dec_a[8] 	= 0x2a, .burst_dec_a[9] 	= 0x2a, .burst_dec_a[10] 	= 0x2a,
			.burst_dec_b[0] 	= 0x00, .burst_dec_b[1] 	= 0x00, .burst_dec_b[2] 	= 0x00, .burst_dec_b[3] 	= 0x00, .burst_dec_b[4] 	= 0x00, .burst_dec_b[5] 	= 0x00, .burst_dec_b[6] 	= 0x00, .burst_dec_b[7] 	= 0x00, .burst_dec_b[8] 	= 0x00, .burst_dec_b[9] 	= 0x00, .burst_dec_b[10] 	= 0x00,
			.burst_dec_c[0] 	= 0x00, .burst_dec_c[1] 	= 0x00, .burst_dec_c[2] 	= 0x00, .burst_dec_c[3] 	= 0x00, .burst_dec_c[4] 	= 0x00, .burst_dec_c[5] 	= 0x00, .burst_dec_c[6] 	= 0x00, .burst_dec_c[7] 	= 0x00, .burst_dec_c[8] 	= 0x00, .burst_dec_c[9] 	= 0x00, .burst_dec_c[10] 	= 0x00,

			.c_option[0] 		= 0x80, .c_option[1] 		= 0x80, .c_option[2] 		= 0x80, .c_option[3] 		= 0xb0, .c_option[4] 		= 0xb0, .c_option[5] 		= 0xb0, .c_option[6] 		= 0xb0, .c_option[7] 		= 0xb0, .c_option[8] 		= 0xb0, .c_option[9] 		= 0xb0, .c_option[10] 		= 0xb0,

			.y_filter_b[0]		= 0x10, .y_filter_b[1]		= 0x10, .y_filter_b[2]		= 0x10, .y_filter_b[3]		= 0x10, .y_filter_b[4]		= 0x10, .y_filter_b[5]		= 0x10, .y_filter_b[6]		= 0x10, .y_filter_b[7]		= 0x10, .y_filter_b[8]		= 0x10, .y_filter_b[9]		= 0x10, .y_filter_b[10]		= 0x10,
			.y_filter_b_sel[0]	= 0x1e,	.y_filter_b_sel[1]	= 0x1e,	.y_filter_b_sel[2]	= 0x1e, .y_filter_b_sel[3]	= 0x1e, .y_filter_b_sel[4]	= 0x1e, .y_filter_b_sel[5]	= 0x1e, .y_filter_b_sel[6]	= 0x1e, .y_filter_b_sel[7]	= 0x1e, .y_filter_b_sel[8]	= 0x1e, .y_filter_b_sel[9]	= 0x1e, .y_filter_b_sel[10]	= 0x1e,
		},
		/* timing_a */
		{
			.h_delay_a[0] = 0x80, .h_delay_a[1] = 0x7e, .h_delay_a[2] = 0x7d, .h_delay_a[3] = 0x7c, .h_delay_a[4] = 0x5c, .h_delay_a[5] = 0x7d, .h_delay_a[6] = 0x7d, .h_delay_a[7] = 0x7d, .h_delay_a[8] = 0x7d, .h_delay_a[9] = 0x7d, .h_delay_a[10] = 0x7d,
			.h_delay_b[0] = 0x00, .h_delay_b[1] = 0x00, .h_delay_b[2] = 0x00, .h_delay_b[3] = 0x00, .h_delay_b[4] = 0x00, .h_delay_b[5] = 0x00, .h_delay_b[6] = 0x00, .h_delay_b[7] = 0x00, .h_delay_b[8] = 0x00, .h_delay_b[9] = 0x00, .h_delay_b[10] = 0x00,
			.h_delay_c[0] = 0x20, .h_delay_c[1] = 0x20, .h_delay_c[2] = 0x20, .h_delay_c[3] = 0x20, .h_delay_c[4] = 0x20, .h_delay_c[5] = 0x20, .h_delay_c[6] = 0x20, .h_delay_c[7] = 0x20, .h_delay_c[8] = 0x20, .h_delay_c[9] = 0x20, .h_delay_c[10] = 0x20,
			.y_delay[0]   = 0x05, .y_delay[1]   = 0x05, .y_delay[2]   = 0x05, .y_delay[3]   = 0x05, .y_delay[4]   = 0x05, .y_delay[5] =   0x05, .y_delay[6] =   0x05, .y_delay[7] =   0x05, .y_delay[8] =   0x05, .y_delay[9] =   0x05, .y_delay[10] =   0x05,

		},
		/* clk */
		{
			.clk_adc[0] = 0x05, .clk_adc[1] = 0x05, .clk_adc[2] = 0x05, .clk_adc[3] = 0x05, .clk_adc[4] = 0x05, .clk_adc[5] = 0x05, .clk_adc[6] = 0x05, .clk_adc[7] = 0x05, .clk_adc[8] = 0x05, .clk_adc[9] = 0x05, .clk_adc[10] = 0x05,
			.clk_dec[0] = 0x04, .clk_dec[1] = 0x04, .clk_dec[2] = 0x04, .clk_dec[3] = 0x04, .clk_dec[4] = 0x04, .clk_dec[5] = 0x04, .clk_dec[6] = 0x04, .clk_dec[7] = 0x04, .clk_dec[8] = 0x04, .clk_dec[9] = 0x04, .clk_dec[10] = 0x04,
		},
		/* timing_b */
		{
/*B9 0x96*/	.h_scaler1[0]  = 0x01, .h_scaler1[1]   = 0x01, .h_scaler1[2]   = 0x01, .h_scaler1[3]   = 0x01, .h_scaler1[4]   = 0x01, .h_scaler1[5]   = 0x01, .h_scaler1[6]   = 0x01, .h_scaler1[7]   = 0x01, .h_scaler1[8]   = 0x01, .h_scaler1[9]   = 0x01, .h_scaler1[10]   = 0x01,
/*B9 0x97*/	.h_scaler2[0]  = 0x59, .h_scaler2[1]   = 0x59, .h_scaler2[2]   = 0x59, .h_scaler2[3]   = 0x59, .h_scaler2[4]   = 0x59, .h_scaler2[5]   = 0x59, .h_scaler2[6]   = 0x59, .h_scaler2[7]   = 0x59, .h_scaler2[8]   = 0x59, .h_scaler2[9]   = 0x59, .h_scaler2[10]   = 0x59,
/*B9 0x98*/	.h_scaler3[0]  = 0xc0, .h_scaler3[1]   = 0xc0, .h_scaler3[2]   = 0xc0, .h_scaler3[3]   = 0x00, .h_scaler3[4]   = 0xc0, .h_scaler3[5]   = 0xc0, .h_scaler3[6]   = 0xc0, .h_scaler3[7]   = 0xc0, .h_scaler3[8]   = 0xc0, .h_scaler3[9]   = 0xc0, .h_scaler3[10]   = 0xc0,
/*B9 0x99*/	.h_scaler4[0]  = 0x01, .h_scaler4[1]   = 0x01, .h_scaler4[2]   = 0x01, .h_scaler4[3]   = 0x00, .h_scaler4[4]   = 0x01, .h_scaler4[5]   = 0x01, .h_scaler4[6]   = 0x01, .h_scaler4[7]   = 0x01, .h_scaler4[8]   = 0x01, .h_scaler4[9]   = 0x01, .h_scaler4[10]   = 0x01,
/*B9 0x9a*/	.h_scaler5[0]  = 0x00, .h_scaler5[1]   = 0x00, .h_scaler5[2]   = 0x00, .h_scaler5[3]   = 0x00, .h_scaler5[4]   = 0x00, .h_scaler5[5]   = 0x00, .h_scaler5[6]   = 0x00, .h_scaler5[7]   = 0x00, .h_scaler5[8]   = 0x00, .h_scaler5[9]   = 0x00, .h_scaler5[10]   = 0x00,
/*B9 0x9b*/	.h_scaler6[0]  = 0x00, .h_scaler6[1]   = 0x00, .h_scaler6[2]   = 0x00, .h_scaler6[3]   = 0x00, .h_scaler6[4]   = 0x00, .h_scaler6[5]   = 0x00, .h_scaler6[6]   = 0x00, .h_scaler6[7]   = 0x00, .h_scaler6[8]   = 0x00, .h_scaler6[9]   = 0x00, .h_scaler6[10]   = 0x00,
/*B9 0x9c*/	.h_scaler7[0]  = 0x00, .h_scaler7[1]   = 0x00, .h_scaler7[2]   = 0x00, .h_scaler7[3]   = 0x00, .h_scaler7[4]   = 0x00, .h_scaler7[5]   = 0x00, .h_scaler7[6]   = 0x00, .h_scaler7[7]   = 0x00, .h_scaler7[8]   = 0x00, .h_scaler7[9]   = 0x00, .h_scaler7[10]   = 0x00,
/*B9 0x9d*/	.h_scaler8[0]  = 0x00, .h_scaler8[1]   = 0x00, .h_scaler8[2]   = 0x00, .h_scaler8[3]   = 0x00, .h_scaler8[4]   = 0x00, .h_scaler8[5]   = 0x00, .h_scaler8[6]   = 0x00, .h_scaler8[7]   = 0x00, .h_scaler8[8]   = 0x00, .h_scaler8[9]   = 0x00, .h_scaler8[10]   = 0x00,
/*B9 0x9e*/	.h_scaler9[0]  = 0x00, .h_scaler9[1]   = 0x00, .h_scaler9[2]   = 0x00, .h_scaler9[3]   = 0x00, .h_scaler9[4]   = 0x00, .h_scaler9[5]   = 0x00, .h_scaler9[6]   = 0x00, .h_scaler9[7]   = 0x00, .h_scaler9[8]   = 0x00, .h_scaler9[9]   = 0x00, .h_scaler9[10]   = 0x00,


/*B9 0x40*/	.pn_auto[0]    	= 0x00, .pn_auto[1]		= 0x00, .pn_auto[2]    	= 0x00, .pn_auto[3]    	= 0x00, .pn_auto[4]    	= 0x00, .pn_auto[5]    	= 0x00, .pn_auto[6]		= 0x00, .pn_auto[7]    	= 0x00, .pn_auto[8]    	= 0x00, .pn_auto[9]    	= 0x00, .pn_auto[10]    	= 0x00,

/*B5 0x90*/	.comb_mode[0]   = 0x05, .comb_mode[1]	= 0x05, .comb_mode[2]   = 0x05, .comb_mode[3]   = 0x05, .comb_mode[4]  	= 0x05, .comb_mode[5]   = 0x05, .comb_mode[6]	= 0x05, .comb_mode[7]   = 0x05, .comb_mode[8]   = 0x05, .comb_mode[9]  	= 0x05, .comb_mode[10]   = 0x05,
/*B9 0xb9*/	.h_pll_op_a[0]  = 0x72, .h_pll_op_a[1]  = 0x72, .h_pll_op_a[2]  = 0x72, .h_pll_op_a[3]  = 0x72, .h_pll_op_a[4]  = 0x72, .h_pll_op_a[5]  = 0x72, .h_pll_op_a[6]  = 0x72, .h_pll_op_a[7]  = 0x72, .h_pll_op_a[8]  = 0x72, .h_pll_op_a[9]  = 0x72, .h_pll_op_a[10]  = 0x72,
/*B9 0x57*/	.mem_path[0]	= 0x10, .mem_path[1]	= 0x10, .mem_path[2]	= 0x10, .mem_path[3]	= 0x10, .mem_path[4]	= 0x10, .mem_path[5]	= 0x10, .mem_path[6]	= 0x10, .mem_path[7]	= 0x10, .mem_path[8]	= 0x10, .mem_path[9]	= 0x10, .mem_path[10]	 = 0x10,
			.fsc_lock_speed[0] = 0xdc, .fsc_lock_speed[1] = 0xdc, .fsc_lock_speed[2] = 0xdc, .fsc_lock_speed[3] = 0xdc, .fsc_lock_speed[4] = 0xdc, .fsc_lock_speed[5] = 0xdc, .fsc_lock_speed[6] = 0xdc, .fsc_lock_speed[7] = 0xdc, .fsc_lock_speed[8] = 0xdc, .fsc_lock_speed[9] = 0xdc, .fsc_lock_speed[10] = 0xdc,

/*B0 0x81*/	.format_set1[0] = 0x07, .format_set1[1] = 0x07, .format_set1[2] = 0x07, .format_set1[3] = 0x07, .format_set1[4] = 0x07, .format_set1[5] = 0x07, .format_set1[6] = 0x07, .format_set1[7] = 0x07, .format_set1[8] = 0x07, .format_set1[9] = 0x07, .format_set1[10] = 0x07,
/*B0 0x85*/	.format_set2[0] = 0x01, .format_set2[1] = 0x01, .format_set2[2] = 0x01, .format_set2[3] = 0x01, .format_set2[4] = 0x01, .format_set2[5] = 0x01, .format_set2[6] = 0x01, .format_set2[7] = 0x01, .format_set2[8] = 0x01, .format_set2[9] = 0x01, .format_set2[10] = 0x01,

/*B0 0x64*/ .v_delay[0]     = 0x21, .v_delay[1]     = 0x21, .v_delay[2]     = 0x21, .v_delay[3]     = 0x21, .v_delay[4]     = 0x21, .v_delay[5]     = 0x21, .v_delay[6]     = 0x21, .v_delay[7]     = 0x21, .v_delay[8]     = 0x21, .v_delay[9]     = 0x21, .v_delay[10]     = 0x21,
		},
	},
	[ TVI_HD_30P ] = /* o */
	{
	/* base */
		{
			.eq_bypass[0] 	= 0x22, .eq_bypass[1] 	= 0x22, .eq_bypass[2] 	= 0x22, .eq_bypass[3] 	= 0x22, .eq_bypass[4] 	= 0x22, .eq_bypass[5] 	= 0x22, .eq_bypass[6] 	= 0x22, .eq_bypass[7] 	= 0x22, .eq_bypass[8] 	= 0x22, .eq_bypass[9] 	= 0x22, .eq_bypass[10] 	 = 0x22,  // Bank5 0x30
			.eq_band_sel[0] = 0x77, .eq_band_sel[1] = 0x67, .eq_band_sel[2] = 0x57, .eq_band_sel[3] = 0x57, .eq_band_sel[4] = 0x57, .eq_band_sel[5] = 0x47, .eq_band_sel[6] = 0x37, .eq_band_sel[7] = 0x27, .eq_band_sel[8] = 0x17, .eq_band_sel[9] = 0x17, .eq_band_sel[10] = 0x07, // BankA 0x31
			.eq_gain_sel[0] = 0x78, .eq_gain_sel[1] = 0x78, .eq_gain_sel[2] = 0x78, .eq_gain_sel[3] = 0x7f, .eq_gain_sel[4] = 0x7f, .eq_gain_sel[5] = 0x7f, .eq_gain_sel[6] = 0x7f, .eq_gain_sel[7] = 0x7f, .eq_gain_sel[8] = 0x7f, .eq_gain_sel[9] = 0x7f, .eq_gain_sel[10] = 0x7f, // BankA 0x32
			.deq_a_on[0] 	= 0x00, .deq_a_on[1] 	= 0x01, .deq_a_on[2] 	= 0x01, .deq_a_on[3] 	= 0x01, .deq_a_on[4] 	= 0x01, .deq_a_on[5] 	= 0x01, .deq_a_on[6] 	= 0x01, .deq_a_on[7] 	= 0x01, .deq_a_on[8] 	= 0x01, .deq_a_on[9] 	= 0x01, .deq_a_on[10] 	 = 0x01, // BankA 0x33
			.deq_a_sel[0] 	= 0x00, .deq_a_sel[1] 	= 0x91, .deq_a_sel[2] 	= 0x92, .deq_a_sel[3] 	= 0x93, .deq_a_sel[4] 	= 0x93, .deq_a_sel[5] 	= 0x93, .deq_a_sel[6] 	= 0x93, .deq_a_sel[7] 	= 0x93, .deq_a_sel[8] 	= 0x93, .deq_a_sel[9] 	= 0x93, .deq_a_sel[10] 	 = 0x92, // BankA 0x34
			.deq_b_sel[0] 	= 0x00, .deq_b_sel[1] 	= 0x00, .deq_b_sel[2] 	= 0x00, .deq_b_sel[3] 	= 0x00, .deq_b_sel[4] 	= 0x00, .deq_b_sel[5] 	= 0x00, .deq_b_sel[6] 	= 0x00, .deq_b_sel[7] 	= 0x00, .deq_b_sel[8] 	= 0x00, .deq_b_sel[9] 	= 0x00, .deq_b_sel[10] 	 = 0x00, // BankA 0x35
		},
		/* coeff */
		{
			.deqA_01[0] = 0xAC, .deqA_01[1] = 0xAC, .deqA_01[2] = 0xAC, .deqA_01[3] = 0xAC, .deqA_01[4] = 0xAC, .deqA_01[5] = 0xAC,	.deqA_01[6] = 0xAC,  .deqA_01[7] = 0xAC, .deqA_01[8] = 0xAC, .deqA_01[9] = 0xAC, .deqA_01[10] = 0xAC,	// BankA 0x30
			.deqA_02[0] = 0x78, .deqA_02[1] = 0x78, .deqA_02[2] = 0x78, .deqA_02[3] = 0x78, .deqA_02[4] = 0x78, .deqA_02[5] = 0x78,	.deqA_02[6] = 0x78,	 .deqA_02[7] = 0x78, .deqA_02[8] = 0x78, .deqA_02[9] = 0x78, .deqA_02[10] = 0x78,	// BankA 0x31
			.deqA_03[0] = 0x17, .deqA_03[1] = 0x17, .deqA_03[2] = 0x17, .deqA_03[3] = 0x17, .deqA_03[4] = 0x17, .deqA_03[5] = 0x17,	.deqA_03[6] = 0x17,	 .deqA_03[7] = 0x17, .deqA_03[8] = 0x17, .deqA_03[9] = 0x17, .deqA_03[10] = 0x17,	// BankA 0x32
			.deqA_04[0] = 0xC1, .deqA_04[1] = 0xC1, .deqA_04[2] = 0xC1, .deqA_04[3] = 0xC1, .deqA_04[4] = 0xC1, .deqA_04[5] = 0xC1, .deqA_04[6] = 0xC1,  .deqA_04[7] = 0xC1, .deqA_04[8] = 0xC1, .deqA_04[9] = 0xC1, .deqA_04[10] = 0xC1,	// BankA 0x33
			.deqA_05[0] = 0x40, .deqA_05[1] = 0x40, .deqA_05[2] = 0x40, .deqA_05[3] = 0x40, .deqA_05[4] = 0x40, .deqA_05[5] = 0x40, .deqA_05[6] = 0x40,  .deqA_05[7] = 0x40, .deqA_05[8] = 0x40, .deqA_05[9] = 0x40, .deqA_05[10] = 0x40,	// BankA 0x34
			.deqA_06[0] = 0x00, .deqA_06[1] = 0x00, .deqA_06[2] = 0x00, .deqA_06[3] = 0x00, .deqA_06[4] = 0x00, .deqA_06[5] = 0x00, .deqA_06[6] = 0x00,  .deqA_06[7] = 0x00, .deqA_06[8] = 0x00, .deqA_06[9] = 0x00, .deqA_06[10] = 0x00,	// BankA 0x35
			.deqA_07[0] = 0xC3, .deqA_07[1] = 0xC3, .deqA_07[2] = 0xC3, .deqA_07[3] = 0xC3, .deqA_07[4] = 0xC3, .deqA_07[5] = 0xC3, .deqA_07[6] = 0xC3,  .deqA_07[7] = 0xC3, .deqA_07[8] = 0xC3, .deqA_07[9] = 0xC3, .deqA_07[10] = 0xC3,	// BankA 0x36
			.deqA_08[0] = 0x0A, .deqA_08[1] = 0x0A, .deqA_08[2] = 0x0A, .deqA_08[3] = 0x0A, .deqA_08[4] = 0x0A, .deqA_08[5] = 0x0A, .deqA_08[6] = 0x0A,  .deqA_08[7] = 0x0A, .deqA_08[8] = 0x0A, .deqA_08[9] = 0x0A, .deqA_08[10] = 0x0A,	// BankA 0x37
			.deqA_09[0] = 0x00, .deqA_09[1] = 0x00, .deqA_09[2] = 0x00, .deqA_09[3] = 0x00, .deqA_09[4] = 0x00, .deqA_09[5] = 0x00, .deqA_09[6] = 0x00,  .deqA_09[7] = 0x00, .deqA_09[8] = 0x00, .deqA_09[9] = 0x00, .deqA_09[10] = 0x00,	// BankA 0x38
			.deqA_10[0] = 0x02, .deqA_10[1] = 0x02, .deqA_10[2] = 0x02, .deqA_10[3] = 0x02, .deqA_10[4] = 0x02, .deqA_10[5] = 0x02, .deqA_10[6] = 0x02,  .deqA_10[7] = 0x02, .deqA_10[8] = 0x02, .deqA_10[9] = 0x02, .deqA_10[10] = 0x02,	// BankA 0x39
			.deqA_11[0] = 0x00, .deqA_11[1] = 0x00, .deqA_11[2] = 0x00, .deqA_11[3] = 0x00, .deqA_11[4] = 0x00, .deqA_11[5] = 0x00, .deqA_11[6] = 0x00,  .deqA_11[7] = 0x00, .deqA_11[8] = 0x00, .deqA_11[9] = 0x00, .deqA_11[10] = 0x00,	// BankA 0x3a
			.deqA_12[0] = 0xB2, .deqA_12[1] = 0xB2, .deqA_12[2] = 0xB2, .deqA_12[3] = 0xB2, .deqA_12[4] = 0xB2, .deqA_12[5] = 0xB2, .deqA_12[6] = 0xB2,  .deqA_12[7] = 0xB2, .deqA_12[8] = 0xB2, .deqA_12[9] = 0xB2, .deqA_12[10] = 0xB2,	// BankA 0x3b
		},
		/* color */
		{
			.contrast[0] 		= 0x82, .contrast[1] 		= 0x86, .contrast[2] 		= 0x84, .contrast[3] 		= 0x81, .contrast[4] 		= 0x7f, .contrast[5] 		= 0x7e, .contrast[6] 		= 0x7a, .contrast[7] 		= 0x7a, .contrast[8] 		= 0x72, .contrast[9] 		= 0x6d, .contrast[10] 		= 0x6d,
			.h_peaking[0] 		= 0x00, .h_peaking[1] 		= 0x00, .h_peaking[2] 		= 0x00, .h_peaking[3] 		= 0x00, .h_peaking[4] 		= 0x00, .h_peaking[5] 		= 0x00, .h_peaking[6] 		= 0x00, .h_peaking[7] 		= 0x3f, .h_peaking[8] 		= 0x3f, .h_peaking[9] 		= 0x3f, .h_peaking[10] 		= 0x3f,
			.c_filter[0]		= 0x82, .c_filter[1] 		= 0x92, .c_filter[2]	 	= 0x92, .c_filter[3] 		= 0xa2, .c_filter[4] 		= 0xa2, .c_filter[5] 		= 0xa2, .c_filter[6] 		= 0xb2, .c_filter[7] 		= 0xb2, .c_filter[8] 		= 0xb2, .c_filter[9] 		= 0xb2, .c_filter[10] 		= 0xb2,
			.hue[0] 			= 0x00, .hue[1] 			= 0x00, .hue[2] 			= 0x00, .hue[3] 			= 0x00, .hue[4] 			= 0x00, .hue[5] 			= 0x00, .hue[6] 			= 0x00, .hue[7] 			= 0x00, .hue[8] 			= 0x00, .hue[9] 			= 0x00, .hue[10] 			= 0x00,
			.u_gain[0] 			= 0xe0, .u_gain[1] 			= 0xe0, .u_gain[2] 			= 0xe0, .u_gain[3] 			= 0xe0, .u_gain[4] 			= 0xe0, .u_gain[5] 			= 0xe0, .u_gain[6] 			= 0xe0, .u_gain[7] 			= 0xe0, .u_gain[8] 			= 0xe0, .u_gain[9] 			= 0xe0, .u_gain[10] 		= 0xe0,
			.v_gain[0] 			= 0x00, .v_gain[1] 			= 0x00, .v_gain[2] 			= 0x00, .v_gain[3] 			= 0x00, .v_gain[4] 			= 0x00, .v_gain[5] 			= 0x00, .v_gain[6] 			= 0x00, .v_gain[7] 			= 0x00, .v_gain[8] 			= 0x00, .v_gain[9] 			= 0x00, .v_gain[10] 		= 0x00,
			.u_offset[0] 		= 0xff, .u_offset[1] 		= 0xff, .u_offset[2] 		= 0xff, .u_offset[3] 		= 0xff, .u_offset[4] 		= 0xff, .u_offset[5] 		= 0xff, .u_offset[6] 		= 0xff, .u_offset[7] 		= 0xff, .u_offset[8] 		= 0xff, .u_offset[9] 		= 0xff, .u_offset[10] 		= 0xff,
			.v_offset[0] 		= 0x00, .v_offset[1] 		= 0x00, .v_offset[2] 		= 0x00, .v_offset[3] 		= 0x00, .v_offset[4] 		= 0x00, .v_offset[5] 		= 0x00, .v_offset[6] 		= 0x00, .v_offset[7] 		= 0x00, .v_offset[8] 		= 0x00, .v_offset[9] 		= 0x00, .v_offset[10] 		= 0x00,

			.black_level[0] 	= 0x86, .black_level[1] 	= 0x88, .black_level[2] 	= 0x86, .black_level[3] 	= 0x86, .black_level[4] 	= 0x88, .black_level[5] 	= 0x8a, .black_level[6] 	= 0x8c, .black_level[7] 	= 0x92, .black_level[8] 	= 0x95, .black_level[9] 	= 0x98, .black_level[10] 	= 0x98,
			.acc_ref[0]			= 0x57, .acc_ref[1]			= 0x57, .acc_ref[2]			= 0x57, .acc_ref[3]			= 0x57, .acc_ref[4]			= 0x57, .acc_ref[5]			= 0x57, .acc_ref[6]			= 0x57, .acc_ref[7]			= 0x37, .acc_ref[8]			= 0x20, .acc_ref[9]			= 0x20, .acc_ref[10]		= 0x57,
			.cti_delay[0]		= 0x80, .cti_delay[1]		= 0x80, .cti_delay[2]		= 0x80, .cti_delay[3]		= 0x80, .cti_delay[4]		= 0x80, .cti_delay[5]		= 0x80, .cti_delay[6]		= 0x80, .cti_delay[7]		= 0x80, .cti_delay[8]		= 0x80, .cti_delay[9]		= 0x80, .cti_delay[10]		= 0x80,
			.sub_saturation[0] 	= 0xa8, .sub_saturation[1] 	= 0xaa, .sub_saturation[2] 	= 0xaa, .sub_saturation[3] 	= 0xac, .sub_saturation[4] 	= 0xa8, .sub_saturation[5] 	= 0xa6, .sub_saturation[6] 	= 0x98, .sub_saturation[7] 	= 0xa0, .sub_saturation[8] 	= 0xa0, .sub_saturation[9] 	= 0x50, .sub_saturation[10] = 0x50,

			.burst_dec_a[0] 	= 0x2a, .burst_dec_a[1] 	= 0x2a, .burst_dec_a[2] 	= 0x2a, .burst_dec_a[3] 	= 0x2a, .burst_dec_a[4] 	= 0x2a, .burst_dec_a[5] 	= 0x2a, .burst_dec_a[6] 	= 0x2a, .burst_dec_a[7] 	= 0x2a, .burst_dec_a[8] 	= 0x2a, .burst_dec_a[9] 	= 0x2a, .burst_dec_a[10] 	= 0x2a,
			.burst_dec_b[0] 	= 0x00, .burst_dec_b[1] 	= 0x00, .burst_dec_b[2] 	= 0x00, .burst_dec_b[3] 	= 0x00, .burst_dec_b[4] 	= 0x00, .burst_dec_b[5] 	= 0x00, .burst_dec_b[6] 	= 0x00, .burst_dec_b[7] 	= 0x00, .burst_dec_b[8] 	= 0x00, .burst_dec_b[9] 	= 0x00, .burst_dec_b[10] 	= 0x00,
			.burst_dec_c[0] 	= 0x00, .burst_dec_c[1] 	= 0x00, .burst_dec_c[2] 	= 0x00, .burst_dec_c[3] 	= 0x00, .burst_dec_c[4] 	= 0x00, .burst_dec_c[5] 	= 0x00, .burst_dec_c[6] 	= 0x00, .burst_dec_c[7] 	= 0x00, .burst_dec_c[8] 	= 0x00, .burst_dec_c[9] 	= 0x00, .burst_dec_c[10] 	= 0x00,

			.c_option[0] 		= 0x80, .c_option[1] 		= 0x80, .c_option[2] 		= 0x80, .c_option[3] 		= 0xb0, .c_option[4] 		= 0xb0, .c_option[5] 		= 0xb0, .c_option[6] 		= 0xb0, .c_option[7] 		= 0xb0, .c_option[8] 		= 0xb0, .c_option[9] 		= 0xb0, .c_option[10] 		= 0xb0,

			.y_filter_b[0]		= 0x10, .y_filter_b[1]		= 0x10, .y_filter_b[2]		= 0x10, .y_filter_b[3]		= 0x10, .y_filter_b[4]		= 0x10, .y_filter_b[5]		= 0x10, .y_filter_b[6]		= 0x10, .y_filter_b[7]		= 0x10, .y_filter_b[8]		= 0x10, .y_filter_b[9]		= 0x10, .y_filter_b[10]		= 0x10,
			.y_filter_b_sel[0]	= 0x1e,	.y_filter_b_sel[1]	= 0x1e,	.y_filter_b_sel[2]	= 0x1e, .y_filter_b_sel[3]	= 0x1e, .y_filter_b_sel[4]	= 0x1e, .y_filter_b_sel[5]	= 0x1e, .y_filter_b_sel[6]	= 0x1e, .y_filter_b_sel[7]	= 0x1e, .y_filter_b_sel[8]	= 0x1e, .y_filter_b_sel[9]	= 0x1e, .y_filter_b_sel[10]	= 0x1e,
		},
		/* timing_a */
		{
			.h_delay_a[0] = 0x20, .h_delay_a[1] = 0x1e, .h_delay_a[2] = 0x1d, .h_delay_a[3] = 0x1c, .h_delay_a[4] = 0x1c, .h_delay_a[5] = 0x1d, .h_delay_a[6] = 0x1d, .h_delay_a[7] = 0x1d, .h_delay_a[8] = 0x1d, .h_delay_a[9] = 0x1d, .h_delay_a[10] = 0x1d,
			.h_delay_b[0] = 0x00, .h_delay_b[1] = 0x00, .h_delay_b[2] = 0x00, .h_delay_b[3] = 0x00, .h_delay_b[4] = 0x00, .h_delay_b[5] = 0x00, .h_delay_b[6] = 0x00, .h_delay_b[7] = 0x00, .h_delay_b[8] = 0x00, .h_delay_b[9] = 0x00, .h_delay_b[10] = 0x00,
			.h_delay_c[0] = 0x10, .h_delay_c[1] = 0x10, .h_delay_c[2] = 0x10, .h_delay_c[3] = 0x10, .h_delay_c[4] = 0x10, .h_delay_c[5] = 0x10, .h_delay_c[6] = 0x10, .h_delay_c[7] = 0x10, .h_delay_c[8] = 0x10, .h_delay_c[9] = 0x10, .h_delay_c[10] = 0x10,
			.y_delay[0]   = 0x05, .y_delay[1]   = 0x05, .y_delay[2]   = 0x05, .y_delay[3]   = 0x05, .y_delay[4]   = 0x05, .y_delay[5] =   0x05, .y_delay[6] =   0x05, .y_delay[7] =   0x05, .y_delay[8] =   0x05, .y_delay[9] =   0x05, .y_delay[10] =   0x05,

		},
		/* clk */
		{
			.clk_adc[0] = 0x05, .clk_adc[1] = 0x05, .clk_adc[2] = 0x05, .clk_adc[3] = 0x05, .clk_adc[4] = 0x05, .clk_adc[5] = 0x05, .clk_adc[6] = 0x05, .clk_adc[7] = 0x05, .clk_adc[8] = 0x05, .clk_adc[9] = 0x05, .clk_adc[10] = 0x05,
			.clk_dec[0] = 0x44, .clk_dec[1] = 0x44, .clk_dec[2] = 0x44, .clk_dec[3] = 0x44, .clk_dec[4] = 0x44, .clk_dec[5] = 0x44, .clk_dec[6] = 0x44, .clk_dec[7] = 0x44, .clk_dec[8] = 0x44, .clk_dec[9] = 0x44, .clk_dec[10] = 0x44,
		},
		/* timing_b */
		{
	/*B9 0x96*/	.h_scaler1[0]  = 0x01, .h_scaler1[1]   = 0x01, .h_scaler1[2]   = 0x01, .h_scaler1[3]   = 0x01, .h_scaler1[4]   = 0x01, .h_scaler1[5]   = 0x01, .h_scaler1[6]   = 0x01, .h_scaler1[7]   = 0x01, .h_scaler1[8]   = 0x01, .h_scaler1[9]   = 0x01, .h_scaler1[10]   = 0x01,
	/*B9 0x97*/	.h_scaler2[0]  = 0x59, .h_scaler2[1]   = 0x59, .h_scaler2[2]   = 0x59, .h_scaler2[3]   = 0x59, .h_scaler2[4]   = 0x59, .h_scaler2[5]   = 0x59, .h_scaler2[6]   = 0x59, .h_scaler2[7]   = 0x59, .h_scaler2[8]   = 0x59, .h_scaler2[9]   = 0x59, .h_scaler2[10]   = 0x59,
	/*B9 0x98*/	.h_scaler3[0]  = 0xff, .h_scaler3[1]   = 0x30, .h_scaler3[2]   = 0x30, .h_scaler3[3]   = 0x30, .h_scaler3[4]   = 0x30, .h_scaler3[5]   = 0x30, .h_scaler3[6]   = 0x30, .h_scaler3[7]   = 0x30, .h_scaler3[8]   = 0x30, .h_scaler3[9]   = 0x30, .h_scaler3[10]   = 0x30,
	/*B9 0x99*/	.h_scaler4[0]  = 0x001, .h_scaler4[1]   = 0x00, .h_scaler4[2]   = 0x00, .h_scaler4[3]   = 0x00, .h_scaler4[4]   = 0x00, .h_scaler4[5]   = 0x00, .h_scaler4[6]   = 0x00, .h_scaler4[7]   = 0x00, .h_scaler4[8]   = 0x00, .h_scaler4[9]   = 0x00, .h_scaler4[10]   = 0x00,
	/*B9 0x9a*/	.h_scaler5[0]  = 0x00, .h_scaler5[1]   = 0x00, .h_scaler5[2]   = 0x00, .h_scaler5[3]   = 0x00, .h_scaler5[4]   = 0x00, .h_scaler5[5]   = 0x00, .h_scaler5[6]   = 0x00, .h_scaler5[7]   = 0x00, .h_scaler5[8]   = 0x00, .h_scaler5[9]   = 0x00, .h_scaler5[10]   = 0x00,
	/*B9 0x9b*/	.h_scaler6[0]  = 0x00, .h_scaler6[1]   = 0x00, .h_scaler6[2]   = 0x00, .h_scaler6[3]   = 0x00, .h_scaler6[4]   = 0x00, .h_scaler6[5]   = 0x00, .h_scaler6[6]   = 0x00, .h_scaler6[7]   = 0x00, .h_scaler6[8]   = 0x00, .h_scaler6[9]   = 0x00, .h_scaler6[10]   = 0x00,
	/*B9 0x9c*/	.h_scaler7[0]  = 0x00, .h_scaler7[1]   = 0x00, .h_scaler7[2]   = 0x00, .h_scaler7[3]   = 0x00, .h_scaler7[4]   = 0x00, .h_scaler7[5]   = 0x00, .h_scaler7[6]   = 0x00, .h_scaler7[7]   = 0x00, .h_scaler7[8]   = 0x00, .h_scaler7[9]   = 0x00, .h_scaler7[10]   = 0x00,
	/*B9 0x9d*/	.h_scaler8[0]  = 0x00, .h_scaler8[1]   = 0x00, .h_scaler8[2]   = 0x00, .h_scaler8[3]   = 0x00, .h_scaler8[4]   = 0x00, .h_scaler8[5]   = 0x00, .h_scaler8[6]   = 0x00, .h_scaler8[7]   = 0x00, .h_scaler8[8]   = 0x00, .h_scaler8[9]   = 0x00, .h_scaler8[10]   = 0x00,
	/*B9 0x9e*/	.h_scaler9[0]  = 0x00, .h_scaler9[1]   = 0x00, .h_scaler9[2]   = 0x00, .h_scaler9[3]   = 0x00, .h_scaler9[4]   = 0x00, .h_scaler9[5]   = 0x00, .h_scaler9[6]   = 0x00, .h_scaler9[7]   = 0x00, .h_scaler9[8]   = 0x00, .h_scaler9[9]   = 0x00, .h_scaler9[10]   = 0x00,


	/*B9 0x40*/	.pn_auto[0]    	= 0x00, .pn_auto[1]		= 0x00, .pn_auto[2]    	= 0x00, .pn_auto[3]    	= 0x00, .pn_auto[4]    	= 0x00, .pn_auto[5]    	= 0x00, .pn_auto[6]		= 0x00, .pn_auto[7]    	= 0x00, .pn_auto[8]    	= 0x00, .pn_auto[9]    	= 0x00, .pn_auto[10]    	= 0x00,

	/*B5 0x90*/	.comb_mode[0]   = 0x05, .comb_mode[1]	= 0x05, .comb_mode[2]   = 0x05, .comb_mode[3]   = 0x05, .comb_mode[4]  	= 0x05, .comb_mode[5]   = 0x05, .comb_mode[6]	= 0x05, .comb_mode[7]   = 0x05, .comb_mode[8]   = 0x05, .comb_mode[9]  	= 0x05, .comb_mode[10]   = 0x05,
	/*B9 0xb9*/	.h_pll_op_a[0]  = 0x72, .h_pll_op_a[1]  = 0x72, .h_pll_op_a[2]  = 0x72, .h_pll_op_a[3]  = 0x72, .h_pll_op_a[4]  = 0x72, .h_pll_op_a[5]  = 0x72, .h_pll_op_a[6]  = 0x72, .h_pll_op_a[7]  = 0x72, .h_pll_op_a[8]  = 0x72, .h_pll_op_a[9]  = 0x72, .h_pll_op_a[10]  = 0x72,
	/*B9 0x57*/	.mem_path[0]	= 0x10, .mem_path[1]	= 0x10, .mem_path[2]	= 0x10, .mem_path[3]	= 0x10, .mem_path[4]	= 0x10, .mem_path[5]	= 0x10, .mem_path[6]	= 0x10, .mem_path[7]	= 0x10, .mem_path[8]	= 0x10, .mem_path[9]	= 0x10, .mem_path[10]	 = 0x10,
			.fsc_lock_speed[0] = 0xdc, .fsc_lock_speed[1] = 0xdc, .fsc_lock_speed[2] = 0xdc, .fsc_lock_speed[3] = 0xdc, .fsc_lock_speed[4] = 0xdc, .fsc_lock_speed[5] = 0xdc, .fsc_lock_speed[6] = 0xdc, .fsc_lock_speed[7] = 0xdc, .fsc_lock_speed[8] = 0xdc, .fsc_lock_speed[9] = 0xdc, .fsc_lock_speed[10] = 0xdc,

	/*B0 0x81*/	.format_set1[0] = 0x06, .format_set1[1] = 0x06, .format_set1[2] = 0x06, .format_set1[3] = 0x06, .format_set1[4] = 0x06, .format_set1[5] = 0x06, .format_set1[6] = 0x06, .format_set1[7] = 0x06, .format_set1[8] = 0x06, .format_set1[9] = 0x06, .format_set1[10] = 0x06,
	/*B0 0x85*/	.format_set2[0] = 0x01, .format_set2[1] = 0x01, .format_set2[2] = 0x01, .format_set2[3] = 0x01, .format_set2[4] = 0x01, .format_set2[5] = 0x01, .format_set2[6] = 0x01, .format_set2[7] = 0x01, .format_set2[8] = 0x01, .format_set2[9] = 0x01, .format_set2[10] = 0x01,

	/*B0 0x64*/ .v_delay[0]     = 0x20, .v_delay[1]     = 0x20, .v_delay[2]     = 0x20, .v_delay[3]     = 0x20, .v_delay[4]     = 0x20, .v_delay[5]     = 0x20, .v_delay[6]     = 0x20, .v_delay[7]     = 0x20, .v_delay[8]     = 0x20, .v_delay[9]     = 0x20, .v_delay[10]     = 0x20,
		},
	},

	[ TVI_HD_B_25P ] = /* o */
	{
	/* base */
		{
			.eq_bypass[0] 	= 0x22, .eq_bypass[1] 	= 0x22, .eq_bypass[2] 	= 0x22, .eq_bypass[3] 	= 0x22, .eq_bypass[4] 	= 0x22, .eq_bypass[5] 	= 0x22, .eq_bypass[6] 	= 0x22, .eq_bypass[7] 	= 0x22, .eq_bypass[8] 	= 0x22, .eq_bypass[9] 	= 0x22, .eq_bypass[10] 	 = 0x22,  // Bank5 0x30
			.eq_band_sel[0] = 0x77, .eq_band_sel[1] = 0x67, .eq_band_sel[2] = 0x57, .eq_band_sel[3] = 0x57, .eq_band_sel[4] = 0x57, .eq_band_sel[5] = 0x47, .eq_band_sel[6] = 0x37, .eq_band_sel[7] = 0x27, .eq_band_sel[8] = 0x17, .eq_band_sel[9] = 0x17, .eq_band_sel[10] = 0x07, // BankA 0x31
			.eq_gain_sel[0] = 0x78, .eq_gain_sel[1] = 0x78, .eq_gain_sel[2] = 0x78, .eq_gain_sel[3] = 0x7f, .eq_gain_sel[4] = 0x7f, .eq_gain_sel[5] = 0x7f, .eq_gain_sel[6] = 0x7f, .eq_gain_sel[7] = 0x7f, .eq_gain_sel[8] = 0x7f, .eq_gain_sel[9] = 0x7f, .eq_gain_sel[10] = 0x7f, // BankA 0x32
			.deq_a_on[0] 	= 0x00, .deq_a_on[1] 	= 0x01, .deq_a_on[2] 	= 0x01, .deq_a_on[3] 	= 0x01, .deq_a_on[4] 	= 0x01, .deq_a_on[5] 	= 0x01, .deq_a_on[6] 	= 0x01, .deq_a_on[7] 	= 0x01, .deq_a_on[8] 	= 0x01, .deq_a_on[9] 	= 0x01, .deq_a_on[10] 	 = 0x01, // BankA 0x33
			.deq_a_sel[0] 	= 0x00, .deq_a_sel[1] 	= 0x91, .deq_a_sel[2] 	= 0x92, .deq_a_sel[3] 	= 0x93, .deq_a_sel[4] 	= 0x93, .deq_a_sel[5] 	= 0x93, .deq_a_sel[6] 	= 0x93, .deq_a_sel[7] 	= 0x93, .deq_a_sel[8] 	= 0x93, .deq_a_sel[9] 	= 0x93, .deq_a_sel[10] 	 = 0x92, // BankA 0x34
			.deq_b_sel[0] 	= 0x00, .deq_b_sel[1] 	= 0x00, .deq_b_sel[2] 	= 0x00, .deq_b_sel[3] 	= 0x00, .deq_b_sel[4] 	= 0x00, .deq_b_sel[5] 	= 0x00, .deq_b_sel[6] 	= 0x00, .deq_b_sel[7] 	= 0x00, .deq_b_sel[8] 	= 0x00, .deq_b_sel[9] 	= 0x00, .deq_b_sel[10] 	 = 0x00, // BankA 0x35
		},
		/* coeff */
		{
			.deqA_01[0] = 0xAC, .deqA_01[1] = 0xAC, .deqA_01[2] = 0xAC, .deqA_01[3] = 0xAC, .deqA_01[4] = 0xAC, .deqA_01[5] = 0xAC,	.deqA_01[6] = 0xAC,  .deqA_01[7] = 0xAC, .deqA_01[8] = 0xAC, .deqA_01[9] = 0xAC, .deqA_01[10] = 0xAC,	// BankA 0x30
			.deqA_02[0] = 0x78, .deqA_02[1] = 0x78, .deqA_02[2] = 0x78, .deqA_02[3] = 0x78, .deqA_02[4] = 0x78, .deqA_02[5] = 0x78,	.deqA_02[6] = 0x78,	 .deqA_02[7] = 0x78, .deqA_02[8] = 0x78, .deqA_02[9] = 0x78, .deqA_02[10] = 0x78,	// BankA 0x31
			.deqA_03[0] = 0x17, .deqA_03[1] = 0x17, .deqA_03[2] = 0x17, .deqA_03[3] = 0x17, .deqA_03[4] = 0x17, .deqA_03[5] = 0x17,	.deqA_03[6] = 0x17,	 .deqA_03[7] = 0x17, .deqA_03[8] = 0x17, .deqA_03[9] = 0x17, .deqA_03[10] = 0x17,	// BankA 0x32
			.deqA_04[0] = 0xC1, .deqA_04[1] = 0xC1, .deqA_04[2] = 0xC1, .deqA_04[3] = 0xC1, .deqA_04[4] = 0xC1, .deqA_04[5] = 0xC1, .deqA_04[6] = 0xC1,  .deqA_04[7] = 0xC1, .deqA_04[8] = 0xC1, .deqA_04[9] = 0xC1, .deqA_04[10] = 0xC1,	// BankA 0x33
			.deqA_05[0] = 0x40, .deqA_05[1] = 0x40, .deqA_05[2] = 0x40, .deqA_05[3] = 0x40, .deqA_05[4] = 0x40, .deqA_05[5] = 0x40, .deqA_05[6] = 0x40,  .deqA_05[7] = 0x40, .deqA_05[8] = 0x40, .deqA_05[9] = 0x40, .deqA_05[10] = 0x40,	// BankA 0x34
			.deqA_06[0] = 0x00, .deqA_06[1] = 0x00, .deqA_06[2] = 0x00, .deqA_06[3] = 0x00, .deqA_06[4] = 0x00, .deqA_06[5] = 0x00, .deqA_06[6] = 0x00,  .deqA_06[7] = 0x00, .deqA_06[8] = 0x00, .deqA_06[9] = 0x00, .deqA_06[10] = 0x00,	// BankA 0x35
			.deqA_07[0] = 0xC3, .deqA_07[1] = 0xC3, .deqA_07[2] = 0xC3, .deqA_07[3] = 0xC3, .deqA_07[4] = 0xC3, .deqA_07[5] = 0xC3, .deqA_07[6] = 0xC3,  .deqA_07[7] = 0xC3, .deqA_07[8] = 0xC3, .deqA_07[9] = 0xC3, .deqA_07[10] = 0xC3,	// BankA 0x36
			.deqA_08[0] = 0x0A, .deqA_08[1] = 0x0A, .deqA_08[2] = 0x0A, .deqA_08[3] = 0x0A, .deqA_08[4] = 0x0A, .deqA_08[5] = 0x0A, .deqA_08[6] = 0x0A,  .deqA_08[7] = 0x0A, .deqA_08[8] = 0x0A, .deqA_08[9] = 0x0A, .deqA_08[10] = 0x0A,	// BankA 0x37
			.deqA_09[0] = 0x00, .deqA_09[1] = 0x00, .deqA_09[2] = 0x00, .deqA_09[3] = 0x00, .deqA_09[4] = 0x00, .deqA_09[5] = 0x00, .deqA_09[6] = 0x00,  .deqA_09[7] = 0x00, .deqA_09[8] = 0x00, .deqA_09[9] = 0x00, .deqA_09[10] = 0x00,	// BankA 0x38
			.deqA_10[0] = 0x02, .deqA_10[1] = 0x02, .deqA_10[2] = 0x02, .deqA_10[3] = 0x02, .deqA_10[4] = 0x02, .deqA_10[5] = 0x02, .deqA_10[6] = 0x02,  .deqA_10[7] = 0x02, .deqA_10[8] = 0x02, .deqA_10[9] = 0x02, .deqA_10[10] = 0x02,	// BankA 0x39
			.deqA_11[0] = 0x00, .deqA_11[1] = 0x00, .deqA_11[2] = 0x00, .deqA_11[3] = 0x00, .deqA_11[4] = 0x00, .deqA_11[5] = 0x00, .deqA_11[6] = 0x00,  .deqA_11[7] = 0x00, .deqA_11[8] = 0x00, .deqA_11[9] = 0x00, .deqA_11[10] = 0x00,	// BankA 0x3a
			.deqA_12[0] = 0xB2, .deqA_12[1] = 0xB2, .deqA_12[2] = 0xB2, .deqA_12[3] = 0xB2, .deqA_12[4] = 0xB2, .deqA_12[5] = 0xB2, .deqA_12[6] = 0xB2,  .deqA_12[7] = 0xB2, .deqA_12[8] = 0xB2, .deqA_12[9] = 0xB2, .deqA_12[10] = 0xB2,	// BankA 0x3b
		},
		/* color */
		{
			.contrast[0] 		= 0x82, .contrast[1] 		= 0x86, .contrast[2] 		= 0x84, .contrast[3] 		= 0x81, .contrast[4] 		= 0x7f, .contrast[5] 		= 0x7e, .contrast[6] 		= 0x7a, .contrast[7] 		= 0x7a, .contrast[8] 		= 0x72, .contrast[9] 		= 0x6d, .contrast[10] 		= 0x6d,
			.h_peaking[0] 		= 0x00, .h_peaking[1] 		= 0x00, .h_peaking[2] 		= 0x00, .h_peaking[3] 		= 0x00, .h_peaking[4] 		= 0x00, .h_peaking[5] 		= 0x00, .h_peaking[6] 		= 0x00, .h_peaking[7] 		= 0x3f, .h_peaking[8] 		= 0x3f, .h_peaking[9] 		= 0x3f, .h_peaking[10] 		= 0x3f,
			.c_filter[0]		= 0x82, .c_filter[1] 		= 0x92, .c_filter[2]	 	= 0x92, .c_filter[3] 		= 0xa2, .c_filter[4] 		= 0xa2, .c_filter[5] 		= 0xa2, .c_filter[6] 		= 0xb2, .c_filter[7] 		= 0xb2, .c_filter[8] 		= 0xb2, .c_filter[9] 		= 0xb2, .c_filter[10] 		= 0xb2,
			.hue[0] 			= 0x00, .hue[1] 			= 0x00, .hue[2] 			= 0x00, .hue[3] 			= 0x00, .hue[4] 			= 0x00, .hue[5] 			= 0x00, .hue[6] 			= 0x00, .hue[7] 			= 0x00, .hue[8] 			= 0x00, .hue[9] 			= 0x00, .hue[10] 			= 0x00,
			.u_gain[0] 			= 0xe0, .u_gain[1] 			= 0x00, .u_gain[2] 			= 0x00, .u_gain[3] 			= 0x00, .u_gain[4] 			= 0x00, .u_gain[5] 			= 0x00, .u_gain[6] 			= 0x00, .u_gain[7] 			= 0x00, .u_gain[8] 			= 0x00, .u_gain[9] 			= 0x00, .u_gain[10] 		= 0x00,
			.v_gain[0] 			= 0x00, .v_gain[1] 			= 0x00, .v_gain[2] 			= 0x00, .v_gain[3] 			= 0x00, .v_gain[4] 			= 0x00, .v_gain[5] 			= 0x00, .v_gain[6] 			= 0x00, .v_gain[7] 			= 0x00, .v_gain[8] 			= 0x00, .v_gain[9] 			= 0x00, .v_gain[10] 		= 0x00,
			.u_offset[0] 		= 0xff, .u_offset[1] 		= 0x00, .u_offset[2] 		= 0x00, .u_offset[3] 		= 0x00, .u_offset[4] 		= 0x00, .u_offset[5] 		= 0x00, .u_offset[6] 		= 0x00, .u_offset[7] 		= 0x00, .u_offset[8] 		= 0x00, .u_offset[9] 		= 0x00, .u_offset[10] 		= 0x00,
			.v_offset[0] 		= 0x00, .v_offset[1] 		= 0x00, .v_offset[2] 		= 0x00, .v_offset[3] 		= 0x00, .v_offset[4] 		= 0x00, .v_offset[5] 		= 0x00, .v_offset[6] 		= 0x00, .v_offset[7] 		= 0x00, .v_offset[8] 		= 0x00, .v_offset[9] 		= 0x00, .v_offset[10] 		= 0x00,

			.black_level[0] 	= 0x86, .black_level[1] 	= 0x88, .black_level[2] 	= 0x86, .black_level[3] 	= 0x86, .black_level[4] 	= 0x88, .black_level[5] 	= 0x8a, .black_level[6] 	= 0x8c, .black_level[7] 	= 0x92, .black_level[8] 	= 0x95, .black_level[9] 	= 0x98, .black_level[10] 	= 0x98,
			.acc_ref[0]			= 0x57, .acc_ref[1]			= 0x57, .acc_ref[2]			= 0x57, .acc_ref[3]			= 0x57, .acc_ref[4]			= 0x57, .acc_ref[5]			= 0x57, .acc_ref[6]			= 0x57, .acc_ref[7]			= 0x37, .acc_ref[8]			= 0x20, .acc_ref[9]			= 0x20, .acc_ref[10]		= 0x57,
			.cti_delay[0]		= 0x80, .cti_delay[1]		= 0x80, .cti_delay[2]		= 0x80, .cti_delay[3]		= 0x80, .cti_delay[4]		= 0x80, .cti_delay[5]		= 0x80, .cti_delay[6]		= 0x80, .cti_delay[7]		= 0x80, .cti_delay[8]		= 0x80, .cti_delay[9]		= 0x80, .cti_delay[10]		= 0x80,
			.sub_saturation[0] 	= 0xa8, .sub_saturation[1] 	= 0xaa, .sub_saturation[2] 	= 0xaa, .sub_saturation[3] 	= 0xac, .sub_saturation[4] 	= 0xa8, .sub_saturation[5] 	= 0xa6, .sub_saturation[6] 	= 0x98, .sub_saturation[7] 	= 0xa0, .sub_saturation[8] 	= 0xa0, .sub_saturation[9] 	= 0x50, .sub_saturation[10] = 0x50,

			.burst_dec_a[0] 	= 0x2a, .burst_dec_a[1] 	= 0x2a, .burst_dec_a[2] 	= 0x2a, .burst_dec_a[3] 	= 0x2a, .burst_dec_a[4] 	= 0x2a, .burst_dec_a[5] 	= 0x2a, .burst_dec_a[6] 	= 0x2a, .burst_dec_a[7] 	= 0x2a, .burst_dec_a[8] 	= 0x2a, .burst_dec_a[9] 	= 0x2a, .burst_dec_a[10] 	= 0x2a,
			.burst_dec_b[0] 	= 0x00, .burst_dec_b[1] 	= 0x00, .burst_dec_b[2] 	= 0x00, .burst_dec_b[3] 	= 0x00, .burst_dec_b[4] 	= 0x00, .burst_dec_b[5] 	= 0x00, .burst_dec_b[6] 	= 0x00, .burst_dec_b[7] 	= 0x00, .burst_dec_b[8] 	= 0x00, .burst_dec_b[9] 	= 0x00, .burst_dec_b[10] 	= 0x00,
			.burst_dec_c[0] 	= 0x00, .burst_dec_c[1] 	= 0x00, .burst_dec_c[2] 	= 0x00, .burst_dec_c[3] 	= 0x00, .burst_dec_c[4] 	= 0x00, .burst_dec_c[5] 	= 0x00, .burst_dec_c[6] 	= 0x00, .burst_dec_c[7] 	= 0x00, .burst_dec_c[8] 	= 0x00, .burst_dec_c[9] 	= 0x00, .burst_dec_c[10] 	= 0x00,

			.c_option[0] 		= 0x80, .c_option[1] 		= 0x80, .c_option[2] 		= 0x80, .c_option[3] 		= 0xb0, .c_option[4] 		= 0xb0, .c_option[5] 		= 0xb0, .c_option[6] 		= 0xb0, .c_option[7] 		= 0xb0, .c_option[8] 		= 0xb0, .c_option[9] 		= 0xb0, .c_option[10] 		= 0xb0,

			.y_filter_b[0]		= 0x10, .y_filter_b[1]		= 0x10, .y_filter_b[2]		= 0x10, .y_filter_b[3]		= 0x10, .y_filter_b[4]		= 0x10, .y_filter_b[5]		= 0x10, .y_filter_b[6]		= 0x10, .y_filter_b[7]		= 0x10, .y_filter_b[8]		= 0x10, .y_filter_b[9]		= 0x10, .y_filter_b[10]		= 0x10,
			.y_filter_b_sel[0]	= 0x1e,	.y_filter_b_sel[1]	= 0x1e,	.y_filter_b_sel[2]	= 0x1e, .y_filter_b_sel[3]	= 0x1e, .y_filter_b_sel[4]	= 0x1e, .y_filter_b_sel[5]	= 0x1e, .y_filter_b_sel[6]	= 0x1e, .y_filter_b_sel[7]	= 0x1e, .y_filter_b_sel[8]	= 0x1e, .y_filter_b_sel[9]	= 0x1e, .y_filter_b_sel[10]	= 0x1e,
		},
		/* timing_a */
		{
			.h_delay_a[0] = 0x82, .h_delay_a[1] = 0x80, .h_delay_a[2] = 0x7f, .h_delay_a[3] = 0x7e, .h_delay_a[4] = 0x7e, .h_delay_a[5] = 0x7f, .h_delay_a[6] = 0x7f, .h_delay_a[7] = 0x7f, .h_delay_a[8] = 0x7f, .h_delay_a[9] = 0x7f, .h_delay_a[10] = 0x7f,
			.h_delay_b[0] = 0x10, .h_delay_b[1] = 0x10, .h_delay_b[2] = 0x10, .h_delay_b[3] = 0x10, .h_delay_b[4] = 0x10, .h_delay_b[5] = 0x10, .h_delay_b[6] = 0x10, .h_delay_b[7] = 0x10, .h_delay_b[8] = 0x10, .h_delay_b[9] = 0x10, .h_delay_b[10] = 0x10,
			.h_delay_c[0] = 0x01, .h_delay_c[1] = 0x01, .h_delay_c[2] = 0x01, .h_delay_c[3] = 0x01, .h_delay_c[4] = 0x01, .h_delay_c[5] = 0x01, .h_delay_c[6] = 0x01, .h_delay_c[7] = 0x01, .h_delay_c[8] = 0x01, .h_delay_c[9] = 0x01, .h_delay_c[10] = 0x01,
			.y_delay[0]   = 0x05, .y_delay[1]   = 0x05, .y_delay[2]   = 0x05, .y_delay[3]   = 0x05, .y_delay[4]   = 0x05, .y_delay[5] =   0x05, .y_delay[6] =   0x05, .y_delay[7] =   0x05, .y_delay[8] =   0x05, .y_delay[9] =   0x05, .y_delay[10] =   0x05,

		},
		/* clk */
		{
			.clk_adc[0] = 0x02, .clk_adc[1] = 0x02, .clk_adc[2] = 0x02, .clk_adc[3] = 0x02, .clk_adc[4] = 0x02, .clk_adc[5] = 0x02, .clk_adc[6] = 0x02, .clk_adc[7] = 0x02, .clk_adc[8] = 0x02, .clk_adc[9] = 0x02, .clk_adc[10] = 0x02,
			.clk_dec[0] = 0x40, .clk_dec[1] = 0x40, .clk_dec[2] = 0x40, .clk_dec[3] = 0x40, .clk_dec[4] = 0x40, .clk_dec[5] = 0x40, .clk_dec[6] = 0x40, .clk_dec[7] = 0x40, .clk_dec[8] = 0x40, .clk_dec[9] = 0x40, .clk_dec[10] = 0x40,
		},
		/* timing_b */
		{
	/*B9 0x96*/	.h_scaler1[0]  = 0x01, .h_scaler1[1]   = 0x01, .h_scaler1[2]   = 0x01, .h_scaler1[3]   = 0x01, .h_scaler1[4]   = 0x01, .h_scaler1[5]   = 0x01, .h_scaler1[6]   = 0x01, .h_scaler1[7]   = 0x01, .h_scaler1[8]   = 0x01, .h_scaler1[9]   = 0x01, .h_scaler1[10]   = 0x01,
	/*B9 0x97*/	.h_scaler2[0]  = 0x00, .h_scaler2[1]   = 0x00, .h_scaler2[2]   = 0x00, .h_scaler2[3]   = 0x00, .h_scaler2[4]   = 0x00, .h_scaler2[5]   = 0x00, .h_scaler2[6]   = 0x00, .h_scaler2[7]   = 0x00, .h_scaler2[8]   = 0x00, .h_scaler2[9]   = 0x00, .h_scaler2[10]   = 0x59,
	/*B9 0x98*/	.h_scaler3[0]  = 0x00, .h_scaler3[1]   = 0x00, .h_scaler3[2]   = 0x00, .h_scaler3[3]   = 0x00, .h_scaler3[4]   = 0x00, .h_scaler3[5]   = 0x00, .h_scaler3[6]   = 0x00, .h_scaler3[7]   = 0x00, .h_scaler3[8]   = 0x00, .h_scaler3[9]   = 0x00, .h_scaler3[10]   = 0x00,
	/*B9 0x99*/	.h_scaler4[0]  = 0x00, .h_scaler4[1]   = 0x00, .h_scaler4[2]   = 0x00, .h_scaler4[3]   = 0x00, .h_scaler4[4]   = 0x00, .h_scaler4[5]   = 0x00, .h_scaler4[6]   = 0x00, .h_scaler4[7]   = 0x00, .h_scaler4[8]   = 0x00, .h_scaler4[9]   = 0x00, .h_scaler4[10]   = 0x00,
	/*B9 0x9a*/	.h_scaler5[0]  = 0x00, .h_scaler5[1]   = 0x00, .h_scaler5[2]   = 0x00, .h_scaler5[3]   = 0x00, .h_scaler5[4]   = 0x00, .h_scaler5[5]   = 0x00, .h_scaler5[6]   = 0x00, .h_scaler5[7]   = 0x00, .h_scaler5[8]   = 0x00, .h_scaler5[9]   = 0x00, .h_scaler5[10]   = 0x00,
	/*B9 0x9b*/	.h_scaler6[0]  = 0x00, .h_scaler6[1]   = 0x00, .h_scaler6[2]   = 0x00, .h_scaler6[3]   = 0x00, .h_scaler6[4]   = 0x00, .h_scaler6[5]   = 0x00, .h_scaler6[6]   = 0x00, .h_scaler6[7]   = 0x00, .h_scaler6[8]   = 0x00, .h_scaler6[9]   = 0x00, .h_scaler6[10]   = 0x00,
	/*B9 0x9c*/	.h_scaler7[0]  = 0x00, .h_scaler7[1]   = 0x00, .h_scaler7[2]   = 0x00, .h_scaler7[3]   = 0x00, .h_scaler7[4]   = 0x00, .h_scaler7[5]   = 0x00, .h_scaler7[6]   = 0x00, .h_scaler7[7]   = 0x00, .h_scaler7[8]   = 0x00, .h_scaler7[9]   = 0x00, .h_scaler7[10]   = 0x00,
	/*B9 0x9d*/	.h_scaler8[0]  = 0x00, .h_scaler8[1]   = 0x00, .h_scaler8[2]   = 0x00, .h_scaler8[3]   = 0x00, .h_scaler8[4]   = 0x00, .h_scaler8[5]   = 0x00, .h_scaler8[6]   = 0x00, .h_scaler8[7]   = 0x00, .h_scaler8[8]   = 0x00, .h_scaler8[9]   = 0x00, .h_scaler8[10]   = 0x00,
	/*B9 0x9e*/	.h_scaler9[0]  = 0x00, .h_scaler9[1]   = 0x00, .h_scaler9[2]   = 0x00, .h_scaler9[3]   = 0x00, .h_scaler9[4]   = 0x00, .h_scaler9[5]   = 0x00, .h_scaler9[6]   = 0x00, .h_scaler9[7]   = 0x00, .h_scaler9[8]   = 0x00, .h_scaler9[9]   = 0x00, .h_scaler9[10]   = 0x00,


	/*B9 0x40*/	.pn_auto[0]    	= 0x00, .pn_auto[1]		= 0x00, .pn_auto[2]    	= 0x00, .pn_auto[3]    	= 0x00, .pn_auto[4]    	= 0x00, .pn_auto[5]    	= 0x00, .pn_auto[6]		= 0x00, .pn_auto[7]    	= 0x00, .pn_auto[8]    	= 0x00, .pn_auto[9]    	= 0x00, .pn_auto[10]    	= 0x00,

	/*B5 0x90*/	.comb_mode[0]   = 0x05, .comb_mode[1]	= 0x05, .comb_mode[2]   = 0x05, .comb_mode[3]   = 0x05, .comb_mode[4]  	= 0x05, .comb_mode[5]   = 0x05, .comb_mode[6]	= 0x05, .comb_mode[7]   = 0x05, .comb_mode[8]   = 0x05, .comb_mode[9]  	= 0x05, .comb_mode[10]   = 0x05,
	/*B9 0xb9*/	.h_pll_op_a[0]  = 0x72, .h_pll_op_a[1]  = 0x72, .h_pll_op_a[2]  = 0x72, .h_pll_op_a[3]  = 0x72, .h_pll_op_a[4]  = 0x72, .h_pll_op_a[5]  = 0x72, .h_pll_op_a[6]  = 0x72, .h_pll_op_a[7]  = 0x72, .h_pll_op_a[8]  = 0x72, .h_pll_op_a[9]  = 0x72, .h_pll_op_a[10]  = 0x72,
	/*B9 0x57*/	.mem_path[0]	= 0x10, .mem_path[1]	= 0x10, .mem_path[2]	= 0x10, .mem_path[3]	= 0x10, .mem_path[4]	= 0x10, .mem_path[5]	= 0x10, .mem_path[6]	= 0x10, .mem_path[7]	= 0x10, .mem_path[8]	= 0x10, .mem_path[9]	= 0x10, .mem_path[10]	 = 0x10,
			.fsc_lock_speed[0] = 0xdc, .fsc_lock_speed[1] = 0xdc, .fsc_lock_speed[2] = 0xdc, .fsc_lock_speed[3] = 0xdc, .fsc_lock_speed[4] = 0xdc, .fsc_lock_speed[5] = 0xdc, .fsc_lock_speed[6] = 0xdc, .fsc_lock_speed[7] = 0xdc, .fsc_lock_speed[8] = 0xdc, .fsc_lock_speed[9] = 0xdc, .fsc_lock_speed[10] = 0xdc,

	/*B0 0x81*/	.format_set1[0] = 0x07, .format_set1[1] = 0x07, .format_set1[2] = 0x07, .format_set1[3] = 0x07, .format_set1[4] = 0x07, .format_set1[5] = 0x07, .format_set1[6] = 0x07, .format_set1[7] = 0x07, .format_set1[8] = 0x07, .format_set1[9] = 0x07, .format_set1[10] = 0x07,
	/*B0 0x85*/	.format_set2[0] = 0x03, .format_set2[1] = 0x03, .format_set2[2] = 0x03, .format_set2[3] = 0x03, .format_set2[4] = 0x03, .format_set2[5] = 0x03, .format_set2[6] = 0x03, .format_set2[7] = 0x03, .format_set2[8] = 0x03, .format_set2[9] = 0x03, .format_set2[10] = 0x03,

	/*B0 0x64*/ .v_delay[0]     = 0x20, .v_delay[1]     = 0x20, .v_delay[2]     = 0x20, .v_delay[3]     = 0x20, .v_delay[4]     = 0x20, .v_delay[5]     = 0x20, .v_delay[6]     = 0x20, .v_delay[7]     = 0x20, .v_delay[8]     = 0x20, .v_delay[9]     = 0x20, .v_delay[10]     = 0x20,
		},
	},
	[ TVI_HD_B_30P ] = /* o */
	{
/* base */
		{
			.eq_bypass[0] 	= 0x22, .eq_bypass[1] 	= 0x22, .eq_bypass[2] 	= 0x22, .eq_bypass[3] 	= 0x22, .eq_bypass[4] 	= 0x22, .eq_bypass[5] 	= 0x22, .eq_bypass[6] 	= 0x22, .eq_bypass[7] 	= 0x22, .eq_bypass[8] 	= 0x22, .eq_bypass[9] 	= 0x22, .eq_bypass[10] 	 = 0x22,  // Bank5 0x30
			.eq_band_sel[0] = 0x77, .eq_band_sel[1] = 0x67, .eq_band_sel[2] = 0x57, .eq_band_sel[3] = 0x57, .eq_band_sel[4] = 0x57, .eq_band_sel[5] = 0x47, .eq_band_sel[6] = 0x37, .eq_band_sel[7] = 0x27, .eq_band_sel[8] = 0x17, .eq_band_sel[9] = 0x17, .eq_band_sel[10] = 0x07, // BankA 0x31
			.eq_gain_sel[0] = 0x78, .eq_gain_sel[1] = 0x78, .eq_gain_sel[2] = 0x78, .eq_gain_sel[3] = 0x7f, .eq_gain_sel[4] = 0x7f, .eq_gain_sel[5] = 0x7f, .eq_gain_sel[6] = 0x7f, .eq_gain_sel[7] = 0x7f, .eq_gain_sel[8] = 0x7f, .eq_gain_sel[9] = 0x7f, .eq_gain_sel[10] = 0x7f, // BankA 0x32
			.deq_a_on[0] 	= 0x00, .deq_a_on[1] 	= 0x01, .deq_a_on[2] 	= 0x01, .deq_a_on[3] 	= 0x01, .deq_a_on[4] 	= 0x01, .deq_a_on[5] 	= 0x01, .deq_a_on[6] 	= 0x01, .deq_a_on[7] 	= 0x01, .deq_a_on[8] 	= 0x01, .deq_a_on[9] 	= 0x01, .deq_a_on[10] 	 = 0x01, // BankA 0x33
			.deq_a_sel[0] 	= 0x00, .deq_a_sel[1] 	= 0x91, .deq_a_sel[2] 	= 0x92, .deq_a_sel[3] 	= 0x93, .deq_a_sel[4] 	= 0x93, .deq_a_sel[5] 	= 0x93, .deq_a_sel[6] 	= 0x93, .deq_a_sel[7] 	= 0x93, .deq_a_sel[8] 	= 0x93, .deq_a_sel[9] 	= 0x93, .deq_a_sel[10] 	 = 0x92, // BankA 0x34
			.deq_b_sel[0] 	= 0x00, .deq_b_sel[1] 	= 0x00, .deq_b_sel[2] 	= 0x00, .deq_b_sel[3] 	= 0x00, .deq_b_sel[4] 	= 0x00, .deq_b_sel[5] 	= 0x00, .deq_b_sel[6] 	= 0x00, .deq_b_sel[7] 	= 0x00, .deq_b_sel[8] 	= 0x00, .deq_b_sel[9] 	= 0x00, .deq_b_sel[10] 	 = 0x00, // BankA 0x35
		},
		/* coeff */
		{
			.deqA_01[0] = 0xAC, .deqA_01[1] = 0xAC, .deqA_01[2] = 0xAC, .deqA_01[3] = 0xAC, .deqA_01[4] = 0xAC, .deqA_01[5] = 0xAC,	.deqA_01[6] = 0xAC,  .deqA_01[7] = 0xAC, .deqA_01[8] = 0xAC, .deqA_01[9] = 0xAC, .deqA_01[10] = 0xAC,	// BankA 0x30
			.deqA_02[0] = 0x78, .deqA_02[1] = 0x78, .deqA_02[2] = 0x78, .deqA_02[3] = 0x78, .deqA_02[4] = 0x78, .deqA_02[5] = 0x78,	.deqA_02[6] = 0x78,	 .deqA_02[7] = 0x78, .deqA_02[8] = 0x78, .deqA_02[9] = 0x78, .deqA_02[10] = 0x78,	// BankA 0x31
			.deqA_03[0] = 0x17, .deqA_03[1] = 0x17, .deqA_03[2] = 0x17, .deqA_03[3] = 0x17, .deqA_03[4] = 0x17, .deqA_03[5] = 0x17,	.deqA_03[6] = 0x17,	 .deqA_03[7] = 0x17, .deqA_03[8] = 0x17, .deqA_03[9] = 0x17, .deqA_03[10] = 0x17,	// BankA 0x32
			.deqA_04[0] = 0xC1, .deqA_04[1] = 0xC1, .deqA_04[2] = 0xC1, .deqA_04[3] = 0xC1, .deqA_04[4] = 0xC1, .deqA_04[5] = 0xC1, .deqA_04[6] = 0xC1,  .deqA_04[7] = 0xC1, .deqA_04[8] = 0xC1, .deqA_04[9] = 0xC1, .deqA_04[10] = 0xC1,	// BankA 0x33
			.deqA_05[0] = 0x40, .deqA_05[1] = 0x40, .deqA_05[2] = 0x40, .deqA_05[3] = 0x40, .deqA_05[4] = 0x40, .deqA_05[5] = 0x40, .deqA_05[6] = 0x40,  .deqA_05[7] = 0x40, .deqA_05[8] = 0x40, .deqA_05[9] = 0x40, .deqA_05[10] = 0x40,	// BankA 0x34
			.deqA_06[0] = 0x00, .deqA_06[1] = 0x00, .deqA_06[2] = 0x00, .deqA_06[3] = 0x00, .deqA_06[4] = 0x00, .deqA_06[5] = 0x00, .deqA_06[6] = 0x00,  .deqA_06[7] = 0x00, .deqA_06[8] = 0x00, .deqA_06[9] = 0x00, .deqA_06[10] = 0x00,	// BankA 0x35
			.deqA_07[0] = 0xC3, .deqA_07[1] = 0xC3, .deqA_07[2] = 0xC3, .deqA_07[3] = 0xC3, .deqA_07[4] = 0xC3, .deqA_07[5] = 0xC3, .deqA_07[6] = 0xC3,  .deqA_07[7] = 0xC3, .deqA_07[8] = 0xC3, .deqA_07[9] = 0xC3, .deqA_07[10] = 0xC3,	// BankA 0x36
			.deqA_08[0] = 0x0A, .deqA_08[1] = 0x0A, .deqA_08[2] = 0x0A, .deqA_08[3] = 0x0A, .deqA_08[4] = 0x0A, .deqA_08[5] = 0x0A, .deqA_08[6] = 0x0A,  .deqA_08[7] = 0x0A, .deqA_08[8] = 0x0A, .deqA_08[9] = 0x0A, .deqA_08[10] = 0x0A,	// BankA 0x37
			.deqA_09[0] = 0x00, .deqA_09[1] = 0x00, .deqA_09[2] = 0x00, .deqA_09[3] = 0x00, .deqA_09[4] = 0x00, .deqA_09[5] = 0x00, .deqA_09[6] = 0x00,  .deqA_09[7] = 0x00, .deqA_09[8] = 0x00, .deqA_09[9] = 0x00, .deqA_09[10] = 0x00,	// BankA 0x38
			.deqA_10[0] = 0x02, .deqA_10[1] = 0x02, .deqA_10[2] = 0x02, .deqA_10[3] = 0x02, .deqA_10[4] = 0x02, .deqA_10[5] = 0x02, .deqA_10[6] = 0x02,  .deqA_10[7] = 0x02, .deqA_10[8] = 0x02, .deqA_10[9] = 0x02, .deqA_10[10] = 0x02,	// BankA 0x39
			.deqA_11[0] = 0x00, .deqA_11[1] = 0x00, .deqA_11[2] = 0x00, .deqA_11[3] = 0x00, .deqA_11[4] = 0x00, .deqA_11[5] = 0x00, .deqA_11[6] = 0x00,  .deqA_11[7] = 0x00, .deqA_11[8] = 0x00, .deqA_11[9] = 0x00, .deqA_11[10] = 0x00,	// BankA 0x3a
			.deqA_12[0] = 0xB2, .deqA_12[1] = 0xB2, .deqA_12[2] = 0xB2, .deqA_12[3] = 0xB2, .deqA_12[4] = 0xB2, .deqA_12[5] = 0xB2, .deqA_12[6] = 0xB2,  .deqA_12[7] = 0xB2, .deqA_12[8] = 0xB2, .deqA_12[9] = 0xB2, .deqA_12[10] = 0xB2,	// BankA 0x3b
		},
		/* color */
		{
			.contrast[0] 		= 0x82, .contrast[1] 		= 0x86, .contrast[2] 		= 0x84, .contrast[3] 		= 0x81, .contrast[4] 		= 0x7f, .contrast[5] 		= 0x7e, .contrast[6] 		= 0x7a, .contrast[7] 		= 0x7a, .contrast[8] 		= 0x72, .contrast[9] 		= 0x6d, .contrast[10] 		= 0x6d,
			.h_peaking[0] 		= 0x00, .h_peaking[1] 		= 0x00, .h_peaking[2] 		= 0x00, .h_peaking[3] 		= 0x00, .h_peaking[4] 		= 0x00, .h_peaking[5] 		= 0x00, .h_peaking[6] 		= 0x00, .h_peaking[7] 		= 0x3f, .h_peaking[8] 		= 0x3f, .h_peaking[9] 		= 0x3f, .h_peaking[10] 		= 0x3f,
			.c_filter[0]		= 0x82, .c_filter[1] 		= 0x92, .c_filter[2]	 	= 0x92, .c_filter[3] 		= 0xa2, .c_filter[4] 		= 0xa2, .c_filter[5] 		= 0xa2, .c_filter[6] 		= 0xb2, .c_filter[7] 		= 0xb2, .c_filter[8] 		= 0xb2, .c_filter[9] 		= 0xb2, .c_filter[10] 		= 0xb2,
			.hue[0] 			= 0x00, .hue[1] 			= 0x00, .hue[2] 			= 0x00, .hue[3] 			= 0x00, .hue[4] 			= 0x00, .hue[5] 			= 0x00, .hue[6] 			= 0x00, .hue[7] 			= 0x00, .hue[8] 			= 0x00, .hue[9] 			= 0x00, .hue[10] 			= 0x00,
			.u_gain[0] 			= 0xe0, .u_gain[1] 			= 0xe0, .u_gain[2] 			= 0xe0, .u_gain[3] 			= 0xe0, .u_gain[4] 			= 0xe0, .u_gain[5] 			= 0xe0, .u_gain[6] 			= 0xe0, .u_gain[7] 			= 0xe0, .u_gain[8] 			= 0xe0, .u_gain[9] 			= 0xe0, .u_gain[10] 		= 0xe0,
			.v_gain[0] 			= 0x00, .v_gain[1] 			= 0x00, .v_gain[2] 			= 0x00, .v_gain[3] 			= 0x00, .v_gain[4] 			= 0x00, .v_gain[5] 			= 0x00, .v_gain[6] 			= 0x00, .v_gain[7] 			= 0x00, .v_gain[8] 			= 0x00, .v_gain[9] 			= 0x00, .v_gain[10] 		= 0x00,
			.u_offset[0] 		= 0xff, .u_offset[1] 		= 0xff, .u_offset[2] 		= 0xff, .u_offset[3] 		= 0xff, .u_offset[4] 		= 0xff, .u_offset[5] 		= 0xff, .u_offset[6] 		= 0xff, .u_offset[7] 		= 0xff, .u_offset[8] 		= 0xff, .u_offset[9] 		= 0xff, .u_offset[10] 		= 0xff,
			.v_offset[0] 		= 0x00, .v_offset[1] 		= 0x00, .v_offset[2] 		= 0x00, .v_offset[3] 		= 0x00, .v_offset[4] 		= 0x00, .v_offset[5] 		= 0x00, .v_offset[6] 		= 0x00, .v_offset[7] 		= 0x00, .v_offset[8] 		= 0x00, .v_offset[9] 		= 0x00, .v_offset[10] 		= 0x00,

			.black_level[0] 	= 0x86, .black_level[1] 	= 0x88, .black_level[2] 	= 0x86, .black_level[3] 	= 0x86, .black_level[4] 	= 0x88, .black_level[5] 	= 0x8a, .black_level[6] 	= 0x8c, .black_level[7] 	= 0x92, .black_level[8] 	= 0x95, .black_level[9] 	= 0x98, .black_level[10] 	= 0x98,
			.acc_ref[0]			= 0x57, .acc_ref[1]			= 0x57, .acc_ref[2]			= 0x57, .acc_ref[3]			= 0x57, .acc_ref[4]			= 0x57, .acc_ref[5]			= 0x57, .acc_ref[6]			= 0x57, .acc_ref[7]			= 0x37, .acc_ref[8]			= 0x20, .acc_ref[9]			= 0x20, .acc_ref[10]		= 0x57,
			.cti_delay[0]		= 0x80, .cti_delay[1]		= 0x80, .cti_delay[2]		= 0x80, .cti_delay[3]		= 0x80, .cti_delay[4]		= 0x80, .cti_delay[5]		= 0x80, .cti_delay[6]		= 0x80, .cti_delay[7]		= 0x80, .cti_delay[8]		= 0x80, .cti_delay[9]		= 0x80, .cti_delay[10]		= 0x80,
			.sub_saturation[0] 	= 0xa8, .sub_saturation[1] 	= 0xaa, .sub_saturation[2] 	= 0xaa, .sub_saturation[3] 	= 0xac, .sub_saturation[4] 	= 0xa8, .sub_saturation[5] 	= 0xa6, .sub_saturation[6] 	= 0x98, .sub_saturation[7] 	= 0xa0, .sub_saturation[8] 	= 0xa0, .sub_saturation[9] 	= 0x50, .sub_saturation[10] = 0x50,

			.burst_dec_a[0] 	= 0x2a, .burst_dec_a[1] 	= 0x2a, .burst_dec_a[2] 	= 0x2a, .burst_dec_a[3] 	= 0x2a, .burst_dec_a[4] 	= 0x2a, .burst_dec_a[5] 	= 0x2a, .burst_dec_a[6] 	= 0x2a, .burst_dec_a[7] 	= 0x2a, .burst_dec_a[8] 	= 0x2a, .burst_dec_a[9] 	= 0x2a, .burst_dec_a[10] 	= 0x2a,
			.burst_dec_b[0] 	= 0x00, .burst_dec_b[1] 	= 0x00, .burst_dec_b[2] 	= 0x00, .burst_dec_b[3] 	= 0x00, .burst_dec_b[4] 	= 0x00, .burst_dec_b[5] 	= 0x00, .burst_dec_b[6] 	= 0x00, .burst_dec_b[7] 	= 0x00, .burst_dec_b[8] 	= 0x00, .burst_dec_b[9] 	= 0x00, .burst_dec_b[10] 	= 0x00,
			.burst_dec_c[0] 	= 0x00, .burst_dec_c[1] 	= 0x00, .burst_dec_c[2] 	= 0x00, .burst_dec_c[3] 	= 0x00, .burst_dec_c[4] 	= 0x00, .burst_dec_c[5] 	= 0x00, .burst_dec_c[6] 	= 0x00, .burst_dec_c[7] 	= 0x00, .burst_dec_c[8] 	= 0x00, .burst_dec_c[9] 	= 0x00, .burst_dec_c[10] 	= 0x00,

			.c_option[0] 		= 0x80, .c_option[1] 		= 0x80, .c_option[2] 		= 0x80, .c_option[3] 		= 0xb0, .c_option[4] 		= 0xb0, .c_option[5] 		= 0xb0, .c_option[6] 		= 0xb0, .c_option[7] 		= 0xb0, .c_option[8] 		= 0xb0, .c_option[9] 		= 0xb0, .c_option[10] 		= 0xb0,

			.y_filter_b[0]		= 0x10, .y_filter_b[1]		= 0x10, .y_filter_b[2]		= 0x10, .y_filter_b[3]		= 0x10, .y_filter_b[4]		= 0x10, .y_filter_b[5]		= 0x10, .y_filter_b[6]		= 0x10, .y_filter_b[7]		= 0x10, .y_filter_b[8]		= 0x10, .y_filter_b[9]		= 0x10, .y_filter_b[10]		= 0x10,
			.y_filter_b_sel[0]	= 0x1e,	.y_filter_b_sel[1]	= 0x1e,	.y_filter_b_sel[2]	= 0x1e, .y_filter_b_sel[3]	= 0x1e, .y_filter_b_sel[4]	= 0x1e, .y_filter_b_sel[5]	= 0x1e, .y_filter_b_sel[6]	= 0x1e, .y_filter_b_sel[7]	= 0x1e, .y_filter_b_sel[8]	= 0x1e, .y_filter_b_sel[9]	= 0x1e, .y_filter_b_sel[10]	= 0x1e,
		},
		/* timing_a */
		{
			.h_delay_a[0] = 0x80, .h_delay_a[1] = 0x7e, .h_delay_a[2] = 0x7d, .h_delay_a[3] = 0x7c, .h_delay_a[4] = 0x7c, .h_delay_a[5] = 0x7d, .h_delay_a[6] = 0x7d, .h_delay_a[7] = 0x7d, .h_delay_a[8] = 0x7d, .h_delay_a[9] = 0x7d, .h_delay_a[10] = 0x7d,
			.h_delay_b[0] = 0x10, .h_delay_b[1] = 0x10, .h_delay_b[2] = 0x10, .h_delay_b[3] = 0x10, .h_delay_b[4] = 0x10, .h_delay_b[5] = 0x10, .h_delay_b[6] = 0x10, .h_delay_b[7] = 0x10, .h_delay_b[8] = 0x10, .h_delay_b[9] = 0x10, .h_delay_b[10] = 0x10,
			.h_delay_c[0] = 0x02, .h_delay_c[1] = 0x02, .h_delay_c[2] = 0x02, .h_delay_c[3] = 0x02, .h_delay_c[4] = 0x02, .h_delay_c[5] = 0x02, .h_delay_c[6] = 0x02, .h_delay_c[7] = 0x02, .h_delay_c[8] = 0x02, .h_delay_c[9] = 0x02, .h_delay_c[10] = 0x02,
			.y_delay[0]   = 0x05, .y_delay[1]   = 0x05, .y_delay[2]   = 0x05, .y_delay[3]   = 0x05, .y_delay[4]   = 0x05, .y_delay[5] =   0x05, .y_delay[6] =   0x05, .y_delay[7] =   0x05, .y_delay[8] =   0x05, .y_delay[9] =   0x05, .y_delay[10] =   0x05,

		},
		/* clk */
		{
			.clk_adc[0] = 0x02, .clk_adc[1] = 0x02, .clk_adc[2] = 0x02, .clk_adc[3] = 0x02, .clk_adc[4] = 0x02, .clk_adc[5] = 0x02, .clk_adc[6] = 0x02, .clk_adc[7] = 0x02, .clk_adc[8] = 0x02, .clk_adc[9] = 0x02, .clk_adc[10] = 0x02,
			.clk_dec[0] = 0x40, .clk_dec[1] = 0x40, .clk_dec[2] = 0x40, .clk_dec[3] = 0x40, .clk_dec[4] = 0x40, .clk_dec[5] = 0x40, .clk_dec[6] = 0x40, .clk_dec[7] = 0x40, .clk_dec[8] = 0x40, .clk_dec[9] = 0x40, .clk_dec[10] = 0x40,
		},
		/* timing_b */
		{
	/*B9 0x96*/	.h_scaler1[0]  = 0x01, .h_scaler1[1]   = 0x01, .h_scaler1[2]   = 0x01, .h_scaler1[3]   = 0x01, .h_scaler1[4]   = 0x01, .h_scaler1[5]   = 0x01, .h_scaler1[6]   = 0x01, .h_scaler1[7]   = 0x01, .h_scaler1[8]   = 0x01, .h_scaler1[9]   = 0x01, .h_scaler1[10]   = 0x01,
	/*B9 0x97*/	.h_scaler2[0]  = 0x00, .h_scaler2[1]   = 0x00, .h_scaler2[2]   = 0x00, .h_scaler2[3]   = 0x00, .h_scaler2[4]   = 0x00, .h_scaler2[5]   = 0x00, .h_scaler2[6]   = 0x00, .h_scaler2[7]   = 0x00, .h_scaler2[8]   = 0x00, .h_scaler2[9]   = 0x00, .h_scaler2[10]   = 0x00,
	/*B9 0x98*/	.h_scaler3[0]  = 0x00, .h_scaler3[1]   = 0x00, .h_scaler3[2]   = 0x00, .h_scaler3[3]   = 0x00, .h_scaler3[4]   = 0x00, .h_scaler3[5]   = 0x00, .h_scaler3[6]   = 0x00, .h_scaler3[7]   = 0x00, .h_scaler3[8]   = 0x00, .h_scaler3[9]   = 0x00, .h_scaler3[10]   = 0x00,
	/*B9 0x99*/	.h_scaler4[0]  = 0x00, .h_scaler4[1]   = 0x00, .h_scaler4[2]   = 0x00, .h_scaler4[3]   = 0x00, .h_scaler4[4]   = 0x00, .h_scaler4[5]   = 0x00, .h_scaler4[6]   = 0x00, .h_scaler4[7]   = 0x00, .h_scaler4[8]   = 0x00, .h_scaler4[9]   = 0x00, .h_scaler4[10]   = 0x00,
	/*B9 0x9a*/	.h_scaler5[0]  = 0x00, .h_scaler5[1]   = 0x00, .h_scaler5[2]   = 0x00, .h_scaler5[3]   = 0x00, .h_scaler5[4]   = 0x00, .h_scaler5[5]   = 0x00, .h_scaler5[6]   = 0x00, .h_scaler5[7]   = 0x00, .h_scaler5[8]   = 0x00, .h_scaler5[9]   = 0x00, .h_scaler5[10]   = 0x00,
	/*B9 0x9b*/	.h_scaler6[0]  = 0x00, .h_scaler6[1]   = 0x00, .h_scaler6[2]   = 0x00, .h_scaler6[3]   = 0x00, .h_scaler6[4]   = 0x00, .h_scaler6[5]   = 0x00, .h_scaler6[6]   = 0x00, .h_scaler6[7]   = 0x00, .h_scaler6[8]   = 0x00, .h_scaler6[9]   = 0x00, .h_scaler6[10]   = 0x00,
	/*B9 0x9c*/	.h_scaler7[0]  = 0x00, .h_scaler7[1]   = 0x00, .h_scaler7[2]   = 0x00, .h_scaler7[3]   = 0x00, .h_scaler7[4]   = 0x00, .h_scaler7[5]   = 0x00, .h_scaler7[6]   = 0x00, .h_scaler7[7]   = 0x00, .h_scaler7[8]   = 0x00, .h_scaler7[9]   = 0x00, .h_scaler7[10]   = 0x00,
	/*B9 0x9d*/	.h_scaler8[0]  = 0x00, .h_scaler8[1]   = 0x00, .h_scaler8[2]   = 0x00, .h_scaler8[3]   = 0x00, .h_scaler8[4]   = 0x00, .h_scaler8[5]   = 0x00, .h_scaler8[6]   = 0x00, .h_scaler8[7]   = 0x00, .h_scaler8[8]   = 0x00, .h_scaler8[9]   = 0x00, .h_scaler8[10]   = 0x00,
	/*B9 0x9e*/	.h_scaler9[0]  = 0x00, .h_scaler9[1]   = 0x00, .h_scaler9[2]   = 0x00, .h_scaler9[3]   = 0x00, .h_scaler9[4]   = 0x00, .h_scaler9[5]   = 0x00, .h_scaler9[6]   = 0x00, .h_scaler9[7]   = 0x00, .h_scaler9[8]   = 0x00, .h_scaler9[9]   = 0x00, .h_scaler9[10]   = 0x00,


	/*B9 0x40*/	.pn_auto[0]    	= 0x00, .pn_auto[1]		= 0x00, .pn_auto[2]    	= 0x00, .pn_auto[3]    	= 0x00, .pn_auto[4]    	= 0x00, .pn_auto[5]    	= 0x00, .pn_auto[6]		= 0x00, .pn_auto[7]    	= 0x00, .pn_auto[8]    	= 0x00, .pn_auto[9]    	= 0x00, .pn_auto[10]    	= 0x00,

	/*B5 0x90*/	.comb_mode[0]   = 0x05, .comb_mode[1]	= 0x05, .comb_mode[2]   = 0x05, .comb_mode[3]   = 0x05, .comb_mode[4]  	= 0x05, .comb_mode[5]   = 0x05, .comb_mode[6]	= 0x05, .comb_mode[7]   = 0x05, .comb_mode[8]   = 0x05, .comb_mode[9]  	= 0x05, .comb_mode[10]   = 0x05,
	/*B9 0xb9*/	.h_pll_op_a[0]  = 0x72, .h_pll_op_a[1]  = 0x72, .h_pll_op_a[2]  = 0x72, .h_pll_op_a[3]  = 0x72, .h_pll_op_a[4]  = 0x72, .h_pll_op_a[5]  = 0x72, .h_pll_op_a[6]  = 0x72, .h_pll_op_a[7]  = 0x72, .h_pll_op_a[8]  = 0x72, .h_pll_op_a[9]  = 0x72, .h_pll_op_a[10]  = 0x72,
	/*B9 0x57*/	.mem_path[0]	= 0x10, .mem_path[1]	= 0x10, .mem_path[2]	= 0x10, .mem_path[3]	= 0x10, .mem_path[4]	= 0x10, .mem_path[5]	= 0x10, .mem_path[6]	= 0x10, .mem_path[7]	= 0x10, .mem_path[8]	= 0x10, .mem_path[9]	= 0x10, .mem_path[10]	 = 0x10,
			.fsc_lock_speed[0] = 0xdc, .fsc_lock_speed[1] = 0xdc, .fsc_lock_speed[2] = 0xdc, .fsc_lock_speed[3] = 0xdc, .fsc_lock_speed[4] = 0xdc, .fsc_lock_speed[5] = 0xdc, .fsc_lock_speed[6] = 0xdc, .fsc_lock_speed[7] = 0xdc, .fsc_lock_speed[8] = 0xdc, .fsc_lock_speed[9] = 0xdc, .fsc_lock_speed[10] = 0xdc,

	/*B0 0x81*/	.format_set1[0] = 0x06, .format_set1[1] = 0x06, .format_set1[2] = 0x06, .format_set1[3] = 0x06, .format_set1[4] = 0x06, .format_set1[5] = 0x06, .format_set1[6] = 0x06, .format_set1[7] = 0x06, .format_set1[8] = 0x06, .format_set1[9] = 0x06, .format_set1[10] = 0x06,
	/*B0 0x85*/	.format_set2[0] = 0x03, .format_set2[1] = 0x03, .format_set2[2] = 0x03, .format_set2[3] = 0x03, .format_set2[4] = 0x03, .format_set2[5] = 0x03, .format_set2[6] = 0x03, .format_set2[7] = 0x03, .format_set2[8] = 0x03, .format_set2[9] = 0x03, .format_set2[10] = 0x03,

	/*B0 0x64*/ .v_delay[0]     = 0x20, .v_delay[1]     = 0x20, .v_delay[2]     = 0x20, .v_delay[3]     = 0x20, .v_delay[4]     = 0x20, .v_delay[5]     = 0x20, .v_delay[6]     = 0x20, .v_delay[7]     = 0x20, .v_delay[8]     = 0x20, .v_delay[9]     = 0x20, .v_delay[10]     = 0x20,
		},
	},

	[ TVI_HD_25P_EX ] = /* o */
	{
/* base */
		{
			.eq_bypass[0] 	= 0x22, .eq_bypass[1] 	= 0x22, .eq_bypass[2] 	= 0x22, .eq_bypass[3] 	= 0x22, .eq_bypass[4] 	= 0x22, .eq_bypass[5] 	= 0x22, .eq_bypass[6] 	= 0x22, .eq_bypass[7] 	= 0x22, .eq_bypass[8] 	= 0x22, .eq_bypass[9] 	= 0x22, .eq_bypass[10] 	 = 0x22,  // Bank5 0x30
			.eq_band_sel[0] = 0x77, .eq_band_sel[1] = 0x67, .eq_band_sel[2] = 0x57, .eq_band_sel[3] = 0x57, .eq_band_sel[4] = 0x57, .eq_band_sel[5] = 0x47, .eq_band_sel[6] = 0x37, .eq_band_sel[7] = 0x27, .eq_band_sel[8] = 0x17, .eq_band_sel[9] = 0x17, .eq_band_sel[10] = 0x07, // BankA 0x31
			.eq_gain_sel[0] = 0x78, .eq_gain_sel[1] = 0x78, .eq_gain_sel[2] = 0x78, .eq_gain_sel[3] = 0x7f, .eq_gain_sel[4] = 0x7f, .eq_gain_sel[5] = 0x7f, .eq_gain_sel[6] = 0x7f, .eq_gain_sel[7] = 0x7f, .eq_gain_sel[8] = 0x7f, .eq_gain_sel[9] = 0x7f, .eq_gain_sel[10] = 0x7f, // BankA 0x32
			.deq_a_on[0] 	= 0x00, .deq_a_on[1] 	= 0x01, .deq_a_on[2] 	= 0x01, .deq_a_on[3] 	= 0x01, .deq_a_on[4] 	= 0x01, .deq_a_on[5] 	= 0x01, .deq_a_on[6] 	= 0x01, .deq_a_on[7] 	= 0x01, .deq_a_on[8] 	= 0x01, .deq_a_on[9] 	= 0x01, .deq_a_on[10] 	 = 0x01, // BankA 0x33
			.deq_a_sel[0] 	= 0x00, .deq_a_sel[1] 	= 0x91, .deq_a_sel[2] 	= 0x92, .deq_a_sel[3] 	= 0x93, .deq_a_sel[4] 	= 0x93, .deq_a_sel[5] 	= 0x93, .deq_a_sel[6] 	= 0x93, .deq_a_sel[7] 	= 0x93, .deq_a_sel[8] 	= 0x93, .deq_a_sel[9] 	= 0x93, .deq_a_sel[10] 	 = 0x92, // BankA 0x34
			.deq_b_sel[0] 	= 0x00, .deq_b_sel[1] 	= 0x00, .deq_b_sel[2] 	= 0x00, .deq_b_sel[3] 	= 0x00, .deq_b_sel[4] 	= 0x00, .deq_b_sel[5] 	= 0x00, .deq_b_sel[6] 	= 0x00, .deq_b_sel[7] 	= 0x00, .deq_b_sel[8] 	= 0x00, .deq_b_sel[9] 	= 0x00, .deq_b_sel[10] 	 = 0x00, // BankA 0x35
		},
		/* coeff */
		{
			.deqA_01[0] = 0xAC, .deqA_01[1] = 0xAC, .deqA_01[2] = 0xAC, .deqA_01[3] = 0xAC, .deqA_01[4] = 0xAC, .deqA_01[5] = 0xAC,	.deqA_01[6] = 0xAC,  .deqA_01[7] = 0xAC, .deqA_01[8] = 0xAC, .deqA_01[9] = 0xAC, .deqA_01[10] = 0xAC,	// BankA 0x30
			.deqA_02[0] = 0x78, .deqA_02[1] = 0x78, .deqA_02[2] = 0x78, .deqA_02[3] = 0x78, .deqA_02[4] = 0x78, .deqA_02[5] = 0x78,	.deqA_02[6] = 0x78,	 .deqA_02[7] = 0x78, .deqA_02[8] = 0x78, .deqA_02[9] = 0x78, .deqA_02[10] = 0x78,	// BankA 0x31
			.deqA_03[0] = 0x17, .deqA_03[1] = 0x17, .deqA_03[2] = 0x17, .deqA_03[3] = 0x17, .deqA_03[4] = 0x17, .deqA_03[5] = 0x17,	.deqA_03[6] = 0x17,	 .deqA_03[7] = 0x17, .deqA_03[8] = 0x17, .deqA_03[9] = 0x17, .deqA_03[10] = 0x17,	// BankA 0x32
			.deqA_04[0] = 0xC1, .deqA_04[1] = 0xC1, .deqA_04[2] = 0xC1, .deqA_04[3] = 0xC1, .deqA_04[4] = 0xC1, .deqA_04[5] = 0xC1, .deqA_04[6] = 0xC1,  .deqA_04[7] = 0xC1, .deqA_04[8] = 0xC1, .deqA_04[9] = 0xC1, .deqA_04[10] = 0xC1,	// BankA 0x33
			.deqA_05[0] = 0x40, .deqA_05[1] = 0x40, .deqA_05[2] = 0x40, .deqA_05[3] = 0x40, .deqA_05[4] = 0x40, .deqA_05[5] = 0x40, .deqA_05[6] = 0x40,  .deqA_05[7] = 0x40, .deqA_05[8] = 0x40, .deqA_05[9] = 0x40, .deqA_05[10] = 0x40,	// BankA 0x34
			.deqA_06[0] = 0x00, .deqA_06[1] = 0x00, .deqA_06[2] = 0x00, .deqA_06[3] = 0x00, .deqA_06[4] = 0x00, .deqA_06[5] = 0x00, .deqA_06[6] = 0x00,  .deqA_06[7] = 0x00, .deqA_06[8] = 0x00, .deqA_06[9] = 0x00, .deqA_06[10] = 0x00,	// BankA 0x35
			.deqA_07[0] = 0xC3, .deqA_07[1] = 0xC3, .deqA_07[2] = 0xC3, .deqA_07[3] = 0xC3, .deqA_07[4] = 0xC3, .deqA_07[5] = 0xC3, .deqA_07[6] = 0xC3,  .deqA_07[7] = 0xC3, .deqA_07[8] = 0xC3, .deqA_07[9] = 0xC3, .deqA_07[10] = 0xC3,	// BankA 0x36
			.deqA_08[0] = 0x0A, .deqA_08[1] = 0x0A, .deqA_08[2] = 0x0A, .deqA_08[3] = 0x0A, .deqA_08[4] = 0x0A, .deqA_08[5] = 0x0A, .deqA_08[6] = 0x0A,  .deqA_08[7] = 0x0A, .deqA_08[8] = 0x0A, .deqA_08[9] = 0x0A, .deqA_08[10] = 0x0A,	// BankA 0x37
			.deqA_09[0] = 0x00, .deqA_09[1] = 0x00, .deqA_09[2] = 0x00, .deqA_09[3] = 0x00, .deqA_09[4] = 0x00, .deqA_09[5] = 0x00, .deqA_09[6] = 0x00,  .deqA_09[7] = 0x00, .deqA_09[8] = 0x00, .deqA_09[9] = 0x00, .deqA_09[10] = 0x00,	// BankA 0x38
			.deqA_10[0] = 0x02, .deqA_10[1] = 0x02, .deqA_10[2] = 0x02, .deqA_10[3] = 0x02, .deqA_10[4] = 0x02, .deqA_10[5] = 0x02, .deqA_10[6] = 0x02,  .deqA_10[7] = 0x02, .deqA_10[8] = 0x02, .deqA_10[9] = 0x02, .deqA_10[10] = 0x02,	// BankA 0x39
			.deqA_11[0] = 0x00, .deqA_11[1] = 0x00, .deqA_11[2] = 0x00, .deqA_11[3] = 0x00, .deqA_11[4] = 0x00, .deqA_11[5] = 0x00, .deqA_11[6] = 0x00,  .deqA_11[7] = 0x00, .deqA_11[8] = 0x00, .deqA_11[9] = 0x00, .deqA_11[10] = 0x00,	// BankA 0x3a
			.deqA_12[0] = 0xB2, .deqA_12[1] = 0xB2, .deqA_12[2] = 0xB2, .deqA_12[3] = 0xB2, .deqA_12[4] = 0xB2, .deqA_12[5] = 0xB2, .deqA_12[6] = 0xB2,  .deqA_12[7] = 0xB2, .deqA_12[8] = 0xB2, .deqA_12[9] = 0xB2, .deqA_12[10] = 0xB2,	// BankA 0x3b
		},
		/* color */
		{
			.contrast[0] 		= 0x82, .contrast[1] 		= 0x86, .contrast[2] 		= 0x84, .contrast[3] 		= 0x81, .contrast[4] 		= 0x7f, .contrast[5] 		= 0x7e, .contrast[6] 		= 0x7a, .contrast[7] 		= 0x7a, .contrast[8] 		= 0x72, .contrast[9] 		= 0x6d, .contrast[10] 		= 0x6d,
			.h_peaking[0] 		= 0x00, .h_peaking[1] 		= 0x00, .h_peaking[2] 		= 0x00, .h_peaking[3] 		= 0x00, .h_peaking[4] 		= 0x00, .h_peaking[5] 		= 0x00, .h_peaking[6] 		= 0x00, .h_peaking[7] 		= 0x3f, .h_peaking[8] 		= 0x3f, .h_peaking[9] 		= 0x3f, .h_peaking[10] 		= 0x3f,
			.c_filter[0]		= 0x82, .c_filter[1] 		= 0x92, .c_filter[2]	 	= 0x92, .c_filter[3] 		= 0xa2, .c_filter[4] 		= 0xa2, .c_filter[5] 		= 0xa2, .c_filter[6] 		= 0xb2, .c_filter[7] 		= 0xb2, .c_filter[8] 		= 0xb2, .c_filter[9] 		= 0xb2, .c_filter[10] 		= 0xb2,
			.hue[0] 			= 0x00, .hue[1] 			= 0x00, .hue[2] 			= 0x00, .hue[3] 			= 0x00, .hue[4] 			= 0x00, .hue[5] 			= 0x00, .hue[6] 			= 0x00, .hue[7] 			= 0x00, .hue[8] 			= 0x00, .hue[9] 			= 0x00, .hue[10] 			= 0x00,
			.u_gain[0] 			= 0xe0, .u_gain[1] 			= 0xe0, .u_gain[2] 			= 0xe0, .u_gain[3] 			= 0xe0, .u_gain[4] 			= 0xe0, .u_gain[5] 			= 0xe0, .u_gain[6] 			= 0xe0, .u_gain[7] 			= 0xe0, .u_gain[8] 			= 0xe0, .u_gain[9] 			= 0x00, .u_gain[10] 		= 0x00,
			.v_gain[0] 			= 0x00, .v_gain[1] 			= 0x00, .v_gain[2] 			= 0x00, .v_gain[3] 			= 0x00, .v_gain[4] 			= 0x00, .v_gain[5] 			= 0x00, .v_gain[6] 			= 0x00, .v_gain[7] 			= 0x00, .v_gain[8] 			= 0x00, .v_gain[9] 			= 0x00, .v_gain[10] 		= 0x00,
			.u_offset[0] 		= 0xff, .u_offset[1] 		= 0xff, .u_offset[2] 		= 0xff, .u_offset[3] 		= 0xff, .u_offset[4] 		= 0xff, .u_offset[5] 		= 0xff, .u_offset[6] 		= 0xff, .u_offset[7] 		= 0xff, .u_offset[8] 		= 0xff, .u_offset[9] 		= 0x00, .u_offset[10] 		= 0x00,
			.v_offset[0] 		= 0x00, .v_offset[1] 		= 0x00, .v_offset[2] 		= 0x00, .v_offset[3] 		= 0x00, .v_offset[4] 		= 0x00, .v_offset[5] 		= 0x00, .v_offset[6] 		= 0x00, .v_offset[7] 		= 0x00, .v_offset[8] 		= 0x00, .v_offset[9] 		= 0x00, .v_offset[10] 		= 0x00,

			.black_level[0] 	= 0x86, .black_level[1] 	= 0x88, .black_level[2] 	= 0x86, .black_level[3] 	= 0x86, .black_level[4] 	= 0x88, .black_level[5] 	= 0x8a, .black_level[6] 	= 0x8c, .black_level[7] 	= 0x92, .black_level[8] 	= 0x95, .black_level[9] 	= 0x98, .black_level[10] 	= 0x98,
			.acc_ref[0]			= 0x57, .acc_ref[1]			= 0x57, .acc_ref[2]			= 0x57, .acc_ref[3]			= 0x57, .acc_ref[4]			= 0x57, .acc_ref[5]			= 0x57, .acc_ref[6]			= 0x57, .acc_ref[7]			= 0x37, .acc_ref[8]			= 0x20, .acc_ref[9]			= 0x20, .acc_ref[10]		= 0x57,
			.cti_delay[0]		= 0x80, .cti_delay[1]		= 0x80, .cti_delay[2]		= 0x80, .cti_delay[3]		= 0x80, .cti_delay[4]		= 0x80, .cti_delay[5]		= 0x80, .cti_delay[6]		= 0x80, .cti_delay[7]		= 0x80, .cti_delay[8]		= 0x80, .cti_delay[9]		= 0x80, .cti_delay[10]		= 0x80,
			.sub_saturation[0] 	= 0xa8, .sub_saturation[1] 	= 0xaa, .sub_saturation[2] 	= 0xaa, .sub_saturation[3] 	= 0xac, .sub_saturation[4] 	= 0xa8, .sub_saturation[5] 	= 0xa6, .sub_saturation[6] 	= 0x98, .sub_saturation[7] 	= 0xa0, .sub_saturation[8] 	= 0xa0, .sub_saturation[9] 	= 0x50, .sub_saturation[10] = 0x50,

			.burst_dec_a[0] 	= 0x2a, .burst_dec_a[1] 	= 0x2a, .burst_dec_a[2] 	= 0x2a, .burst_dec_a[3] 	= 0x2a, .burst_dec_a[4] 	= 0x2a, .burst_dec_a[5] 	= 0x2a, .burst_dec_a[6] 	= 0x2a, .burst_dec_a[7] 	= 0x2a, .burst_dec_a[8] 	= 0x2a, .burst_dec_a[9] 	= 0x2a, .burst_dec_a[10] 	= 0x2a,
			.burst_dec_b[0] 	= 0x00, .burst_dec_b[1] 	= 0x00, .burst_dec_b[2] 	= 0x00, .burst_dec_b[3] 	= 0x00, .burst_dec_b[4] 	= 0x00, .burst_dec_b[5] 	= 0x00, .burst_dec_b[6] 	= 0x00, .burst_dec_b[7] 	= 0x00, .burst_dec_b[8] 	= 0x00, .burst_dec_b[9] 	= 0x00, .burst_dec_b[10] 	= 0x00,
			.burst_dec_c[0] 	= 0x00, .burst_dec_c[1] 	= 0x00, .burst_dec_c[2] 	= 0x00, .burst_dec_c[3] 	= 0x00, .burst_dec_c[4] 	= 0x00, .burst_dec_c[5] 	= 0x00, .burst_dec_c[6] 	= 0x00, .burst_dec_c[7] 	= 0x00, .burst_dec_c[8] 	= 0x00, .burst_dec_c[9] 	= 0x00, .burst_dec_c[10] 	= 0x00,

			.c_option[0] 		= 0x80, .c_option[1] 		= 0x80, .c_option[2] 		= 0x80, .c_option[3] 		= 0xb0, .c_option[4] 		= 0xb0, .c_option[5] 		= 0xb0, .c_option[6] 		= 0xb0, .c_option[7] 		= 0xb0, .c_option[8] 		= 0xb0, .c_option[9] 		= 0xb0, .c_option[10] 		= 0xb0,

			.y_filter_b[0]		= 0x10, .y_filter_b[1]		= 0x10, .y_filter_b[2]		= 0x10, .y_filter_b[3]		= 0x10, .y_filter_b[4]		= 0x10, .y_filter_b[5]		= 0x10, .y_filter_b[6]		= 0x10, .y_filter_b[7]		= 0x10, .y_filter_b[8]		= 0x10, .y_filter_b[9]		= 0x10, .y_filter_b[10]		= 0x10,
			.y_filter_b_sel[0]	= 0x1e,	.y_filter_b_sel[1]	= 0x1e,	.y_filter_b_sel[2]	= 0x1e, .y_filter_b_sel[3]	= 0x1e, .y_filter_b_sel[4]	= 0x1e, .y_filter_b_sel[5]	= 0x1e, .y_filter_b_sel[6]	= 0x1e, .y_filter_b_sel[7]	= 0x1e, .y_filter_b_sel[8]	= 0x1e, .y_filter_b_sel[9]	= 0x1e, .y_filter_b_sel[10]	= 0x1e,
		},
		/* timing_a */
		{
			.h_delay_a[0] = 0x60, .h_delay_a[1] = 0x5e, .h_delay_a[2] = 0x5d, .h_delay_a[3] = 0x5c, .h_delay_a[4] = 0x5c, .h_delay_a[5] = 0x5d, .h_delay_a[6] = 0x5d, .h_delay_a[7] = 0x5d, .h_delay_a[8] = 0x5d, .h_delay_a[9] = 0x5d, .h_delay_a[10] = 0x5d,
			.h_delay_b[0] = 0x00, .h_delay_b[1] = 0x00, .h_delay_b[2] = 0x00, .h_delay_b[3] = 0x00, .h_delay_b[4] = 0x00, .h_delay_b[5] = 0x00, .h_delay_b[6] = 0x00, .h_delay_b[7] = 0x00, .h_delay_b[8] = 0x00, .h_delay_b[9] = 0x00, .h_delay_b[10] = 0x00,
			.h_delay_c[0] = 0x00, .h_delay_c[1] = 0x00, .h_delay_c[2] = 0x00, .h_delay_c[3] = 0x00, .h_delay_c[4] = 0x00, .h_delay_c[5] = 0x00, .h_delay_c[6] = 0x00, .h_delay_c[7] = 0x00, .h_delay_c[8] = 0x00, .h_delay_c[9] = 0x00, .h_delay_c[10] = 0x00,
			.y_delay[0]   = 0x05, .y_delay[1]   = 0x05, .y_delay[2]   = 0x05, .y_delay[3]   = 0x05, .y_delay[4]   = 0x05, .y_delay[5] =   0x05, .y_delay[6] =   0x05, .y_delay[7] =   0x05, .y_delay[8] =   0x05, .y_delay[9] =   0x05, .y_delay[10] =   0x05,

		},
		/* clk */
		{
			.clk_adc[0] = 0x05, .clk_adc[1] = 0x05, .clk_adc[2] = 0x05, .clk_adc[3] = 0x05, .clk_adc[4] = 0x05, .clk_adc[5] = 0x05, .clk_adc[6] = 0x05, .clk_adc[7] = 0x05, .clk_adc[8] = 0x05, .clk_adc[9] = 0x05, .clk_adc[10] = 0x05,
			.clk_dec[0] = 0x44, .clk_dec[1] = 0x44, .clk_dec[2] = 0x44, .clk_dec[3] = 0x44, .clk_dec[4] = 0x44, .clk_dec[5] = 0x44, .clk_dec[6] = 0x44, .clk_dec[7] = 0x44, .clk_dec[8] = 0x44, .clk_dec[9] = 0x44, .clk_dec[10] = 0x44,
		},
		/* timing_b */
		{
/*B9 0x96*/	.h_scaler1[0]  = 0x01, .h_scaler1[1]   = 0x01, .h_scaler1[2]   = 0x01, .h_scaler1[3]   = 0x01, .h_scaler1[4]   = 0x01, .h_scaler1[5]   = 0x01, .h_scaler1[6]   = 0x01, .h_scaler1[7]   = 0x01, .h_scaler1[8]   = 0x01, .h_scaler1[9]   = 0x01, .h_scaler1[10]   = 0x01,
/*B9 0x97*/	.h_scaler2[0]  = 0x59, .h_scaler2[1]   = 0x59, .h_scaler2[2]   = 0x59, .h_scaler2[3]   = 0x59, .h_scaler2[4]   = 0x59, .h_scaler2[5]   = 0x59, .h_scaler2[6]   = 0x59, .h_scaler2[7]   = 0x59, .h_scaler2[8]   = 0x59, .h_scaler2[9]   = 0x59, .h_scaler2[10]   = 0x59,
/*B9 0x98*/	.h_scaler3[0]  = 0x00, .h_scaler3[1]   = 0x00, .h_scaler3[2]   = 0x00, .h_scaler3[3]   = 0x00, .h_scaler3[4]   = 0x00, .h_scaler3[5]   = 0x00, .h_scaler3[6]   = 0x00, .h_scaler3[7]   = 0x00, .h_scaler3[8]   = 0x00, .h_scaler3[9]   = 0x00, .h_scaler3[10]   = 0x00,
/*B9 0x99*/	.h_scaler4[0]  = 0x00, .h_scaler4[1]   = 0x00, .h_scaler4[2]   = 0x00, .h_scaler4[3]   = 0x00, .h_scaler4[4]   = 0x00, .h_scaler4[5]   = 0x00, .h_scaler4[6]   = 0x00, .h_scaler4[7]   = 0x00, .h_scaler4[8]   = 0x00, .h_scaler4[9]   = 0x00, .h_scaler4[10]   = 0x00,
/*B9 0x9a*/	.h_scaler5[0]  = 0x00, .h_scaler5[1]   = 0x00, .h_scaler5[2]   = 0x00, .h_scaler5[3]   = 0x00, .h_scaler5[4]   = 0x00, .h_scaler5[5]   = 0x00, .h_scaler5[6]   = 0x00, .h_scaler5[7]   = 0x00, .h_scaler5[8]   = 0x00, .h_scaler5[9]   = 0x00, .h_scaler5[10]   = 0x00,
/*B9 0x9b*/	.h_scaler6[0]  = 0x00, .h_scaler6[1]   = 0x00, .h_scaler6[2]   = 0x00, .h_scaler6[3]   = 0x00, .h_scaler6[4]   = 0x00, .h_scaler6[5]   = 0x00, .h_scaler6[6]   = 0x00, .h_scaler6[7]   = 0x00, .h_scaler6[8]   = 0x00, .h_scaler6[9]   = 0x00, .h_scaler6[10]   = 0x00,
/*B9 0x9c*/	.h_scaler7[0]  = 0x00, .h_scaler7[1]   = 0x00, .h_scaler7[2]   = 0x00, .h_scaler7[3]   = 0x00, .h_scaler7[4]   = 0x00, .h_scaler7[5]   = 0x00, .h_scaler7[6]   = 0x00, .h_scaler7[7]   = 0x00, .h_scaler7[8]   = 0x00, .h_scaler7[9]   = 0x00, .h_scaler7[10]   = 0x00,
/*B9 0x9d*/	.h_scaler8[0]  = 0x00, .h_scaler8[1]   = 0x00, .h_scaler8[2]   = 0x00, .h_scaler8[3]   = 0x00, .h_scaler8[4]   = 0x00, .h_scaler8[5]   = 0x00, .h_scaler8[6]   = 0x00, .h_scaler8[7]   = 0x00, .h_scaler8[8]   = 0x00, .h_scaler8[9]   = 0x00, .h_scaler8[10]   = 0x00,
/*B9 0x9e*/	.h_scaler9[0]  = 0x80, .h_scaler9[1]   = 0x80, .h_scaler9[2]   = 0x80, .h_scaler9[3]   = 0x80, .h_scaler9[4]   = 0x80, .h_scaler9[5]   = 0x80, .h_scaler9[6]   = 0x80, .h_scaler9[7]   = 0x80, .h_scaler9[8]   = 0x80, .h_scaler9[9]   = 0x80, .h_scaler9[10]   = 0x80,


/*B9 0x40*/	.pn_auto[0]    	= 0x00, .pn_auto[1]		= 0x00, .pn_auto[2]    	= 0x00, .pn_auto[3]    	= 0x00, .pn_auto[4]    	= 0x00, .pn_auto[5]    	= 0x00, .pn_auto[6]		= 0x00, .pn_auto[7]    	= 0x00, .pn_auto[8]    	= 0x00, .pn_auto[9]    	= 0x00, .pn_auto[10]    	= 0x00,

/*B5 0x90*/	.comb_mode[0]   = 0x05, .comb_mode[1]	= 0x05, .comb_mode[2]   = 0x05, .comb_mode[3]   = 0x05, .comb_mode[4]  	= 0x05, .comb_mode[5]   = 0x05, .comb_mode[6]	= 0x05, .comb_mode[7]   = 0x05, .comb_mode[8]   = 0x05, .comb_mode[9]  	= 0x05, .comb_mode[10]   = 0x05,
/*B9 0xb9*/	.h_pll_op_a[0]  = 0x72, .h_pll_op_a[1]  = 0x72, .h_pll_op_a[2]  = 0x72, .h_pll_op_a[3]  = 0x72, .h_pll_op_a[4]  = 0x72, .h_pll_op_a[5]  = 0x72, .h_pll_op_a[6]  = 0x72, .h_pll_op_a[7]  = 0x72, .h_pll_op_a[8]  = 0x72, .h_pll_op_a[9]  = 0x72, .h_pll_op_a[10]  = 0x72,
/*B9 0x57*/	.mem_path[0]	= 0x10, .mem_path[1]	= 0x10, .mem_path[2]	= 0x10, .mem_path[3]	= 0x10, .mem_path[4]	= 0x10, .mem_path[5]	= 0x10, .mem_path[6]	= 0x10, .mem_path[7]	= 0x10, .mem_path[8]	= 0x10, .mem_path[9]	= 0x10, .mem_path[10]	 = 0x10,
			.fsc_lock_speed[0] = 0xdc, .fsc_lock_speed[1] = 0xdc, .fsc_lock_speed[2] = 0xdc, .fsc_lock_speed[3] = 0xdc, .fsc_lock_speed[4] = 0xdc, .fsc_lock_speed[5] = 0xdc, .fsc_lock_speed[6] = 0xdc, .fsc_lock_speed[7] = 0xdc, .fsc_lock_speed[8] = 0xdc, .fsc_lock_speed[9] = 0xdc, .fsc_lock_speed[10] = 0xdc,

/*B0 0x81*/	.format_set1[0] = 0x0b, .format_set1[1] = 0x0b, .format_set1[2] = 0x0b, .format_set1[3] = 0x0b, .format_set1[4] = 0x0b, .format_set1[5] = 0x0b, .format_set1[6] = 0x0b, .format_set1[7] = 0x0b, .format_set1[8] = 0x0b, .format_set1[9] = 0x0b, .format_set1[10] = 0x0b,
/*B0 0x85*/	.format_set2[0] = 0x01, .format_set2[1] = 0x01, .format_set2[2] = 0x01, .format_set2[3] = 0x01, .format_set2[4] = 0x01, .format_set2[5] = 0x01, .format_set2[6] = 0x01, .format_set2[7] = 0x01, .format_set2[8] = 0x01, .format_set2[9] = 0x01, .format_set2[10] = 0x01,

/*B0 0x64*/ .v_delay[0]     = 0x20, .v_delay[1]     = 0x20, .v_delay[2]     = 0x20, .v_delay[3]     = 0x20, .v_delay[4]     = 0x20, .v_delay[5]     = 0x20, .v_delay[6]     = 0x20, .v_delay[7]     = 0x20, .v_delay[8]     = 0x20, .v_delay[9]     = 0x20, .v_delay[10]     = 0x20,
		},
	},
	[ TVI_HD_30P_EX ] = /* o */
	{
/* base */
		{
			.eq_bypass[0] 	= 0x22, .eq_bypass[1] 	= 0x22, .eq_bypass[2] 	= 0x22, .eq_bypass[3] 	= 0x22, .eq_bypass[4] 	= 0x22, .eq_bypass[5] 	= 0x22, .eq_bypass[6] 	= 0x22, .eq_bypass[7] 	= 0x22, .eq_bypass[8] 	= 0x22, .eq_bypass[9] 	= 0x22, .eq_bypass[10] 	 = 0x22,  // Bank5 0x30
			.eq_band_sel[0] = 0x77, .eq_band_sel[1] = 0x67, .eq_band_sel[2] = 0x57, .eq_band_sel[3] = 0x57, .eq_band_sel[4] = 0x57, .eq_band_sel[5] = 0x47, .eq_band_sel[6] = 0x37, .eq_band_sel[7] = 0x27, .eq_band_sel[8] = 0x17, .eq_band_sel[9] = 0x17, .eq_band_sel[10] = 0x07, // BankA 0x31
			.eq_gain_sel[0] = 0x78, .eq_gain_sel[1] = 0x78, .eq_gain_sel[2] = 0x78, .eq_gain_sel[3] = 0x7f, .eq_gain_sel[4] = 0x7f, .eq_gain_sel[5] = 0x7f, .eq_gain_sel[6] = 0x7f, .eq_gain_sel[7] = 0x7f, .eq_gain_sel[8] = 0x7f, .eq_gain_sel[9] = 0x7f, .eq_gain_sel[10] = 0x7f, // BankA 0x32
			.deq_a_on[0] 	= 0x00, .deq_a_on[1] 	= 0x01, .deq_a_on[2] 	= 0x01, .deq_a_on[3] 	= 0x01, .deq_a_on[4] 	= 0x01, .deq_a_on[5] 	= 0x01, .deq_a_on[6] 	= 0x01, .deq_a_on[7] 	= 0x01, .deq_a_on[8] 	= 0x01, .deq_a_on[9] 	= 0x01, .deq_a_on[10] 	 = 0x01, // BankA 0x33
			.deq_a_sel[0] 	= 0x00, .deq_a_sel[1] 	= 0x91, .deq_a_sel[2] 	= 0x92, .deq_a_sel[3] 	= 0x93, .deq_a_sel[4] 	= 0x93, .deq_a_sel[5] 	= 0x93, .deq_a_sel[6] 	= 0x93, .deq_a_sel[7] 	= 0x93, .deq_a_sel[8] 	= 0x93, .deq_a_sel[9] 	= 0x93, .deq_a_sel[10] 	 = 0x92, // BankA 0x34
			.deq_b_sel[0] 	= 0x00, .deq_b_sel[1] 	= 0x00, .deq_b_sel[2] 	= 0x00, .deq_b_sel[3] 	= 0x00, .deq_b_sel[4] 	= 0x00, .deq_b_sel[5] 	= 0x00, .deq_b_sel[6] 	= 0x00, .deq_b_sel[7] 	= 0x00, .deq_b_sel[8] 	= 0x00, .deq_b_sel[9] 	= 0x00, .deq_b_sel[10] 	 = 0x00, // BankA 0x35
		},
		/* coeff */
		{
			.deqA_01[0] = 0xAC, .deqA_01[1] = 0xAC, .deqA_01[2] = 0xAC, .deqA_01[3] = 0xAC, .deqA_01[4] = 0xAC, .deqA_01[5] = 0xAC,	.deqA_01[6] = 0xAC,  .deqA_01[7] = 0xAC, .deqA_01[8] = 0xAC, .deqA_01[9] = 0xAC, .deqA_01[10] = 0xAC,	// BankA 0x30
			.deqA_02[0] = 0x78, .deqA_02[1] = 0x78, .deqA_02[2] = 0x78, .deqA_02[3] = 0x78, .deqA_02[4] = 0x78, .deqA_02[5] = 0x78,	.deqA_02[6] = 0x78,	 .deqA_02[7] = 0x78, .deqA_02[8] = 0x78, .deqA_02[9] = 0x78, .deqA_02[10] = 0x78,	// BankA 0x31
			.deqA_03[0] = 0x17, .deqA_03[1] = 0x17, .deqA_03[2] = 0x17, .deqA_03[3] = 0x17, .deqA_03[4] = 0x17, .deqA_03[5] = 0x17,	.deqA_03[6] = 0x17,	 .deqA_03[7] = 0x17, .deqA_03[8] = 0x17, .deqA_03[9] = 0x17, .deqA_03[10] = 0x17,	// BankA 0x32
			.deqA_04[0] = 0xC1, .deqA_04[1] = 0xC1, .deqA_04[2] = 0xC1, .deqA_04[3] = 0xC1, .deqA_04[4] = 0xC1, .deqA_04[5] = 0xC1, .deqA_04[6] = 0xC1,  .deqA_04[7] = 0xC1, .deqA_04[8] = 0xC1, .deqA_04[9] = 0xC1, .deqA_04[10] = 0xC1,	// BankA 0x33
			.deqA_05[0] = 0x40, .deqA_05[1] = 0x40, .deqA_05[2] = 0x40, .deqA_05[3] = 0x40, .deqA_05[4] = 0x40, .deqA_05[5] = 0x40, .deqA_05[6] = 0x40,  .deqA_05[7] = 0x40, .deqA_05[8] = 0x40, .deqA_05[9] = 0x40, .deqA_05[10] = 0x40,	// BankA 0x34
			.deqA_06[0] = 0x00, .deqA_06[1] = 0x00, .deqA_06[2] = 0x00, .deqA_06[3] = 0x00, .deqA_06[4] = 0x00, .deqA_06[5] = 0x00, .deqA_06[6] = 0x00,  .deqA_06[7] = 0x00, .deqA_06[8] = 0x00, .deqA_06[9] = 0x00, .deqA_06[10] = 0x00,	// BankA 0x35
			.deqA_07[0] = 0xC3, .deqA_07[1] = 0xC3, .deqA_07[2] = 0xC3, .deqA_07[3] = 0xC3, .deqA_07[4] = 0xC3, .deqA_07[5] = 0xC3, .deqA_07[6] = 0xC3,  .deqA_07[7] = 0xC3, .deqA_07[8] = 0xC3, .deqA_07[9] = 0xC3, .deqA_07[10] = 0xC3,	// BankA 0x36
			.deqA_08[0] = 0x0A, .deqA_08[1] = 0x0A, .deqA_08[2] = 0x0A, .deqA_08[3] = 0x0A, .deqA_08[4] = 0x0A, .deqA_08[5] = 0x0A, .deqA_08[6] = 0x0A,  .deqA_08[7] = 0x0A, .deqA_08[8] = 0x0A, .deqA_08[9] = 0x0A, .deqA_08[10] = 0x0A,	// BankA 0x37
			.deqA_09[0] = 0x00, .deqA_09[1] = 0x00, .deqA_09[2] = 0x00, .deqA_09[3] = 0x00, .deqA_09[4] = 0x00, .deqA_09[5] = 0x00, .deqA_09[6] = 0x00,  .deqA_09[7] = 0x00, .deqA_09[8] = 0x00, .deqA_09[9] = 0x00, .deqA_09[10] = 0x00,	// BankA 0x38
			.deqA_10[0] = 0x02, .deqA_10[1] = 0x02, .deqA_10[2] = 0x02, .deqA_10[3] = 0x02, .deqA_10[4] = 0x02, .deqA_10[5] = 0x02, .deqA_10[6] = 0x02,  .deqA_10[7] = 0x02, .deqA_10[8] = 0x02, .deqA_10[9] = 0x02, .deqA_10[10] = 0x02,	// BankA 0x39
			.deqA_11[0] = 0x00, .deqA_11[1] = 0x00, .deqA_11[2] = 0x00, .deqA_11[3] = 0x00, .deqA_11[4] = 0x00, .deqA_11[5] = 0x00, .deqA_11[6] = 0x00,  .deqA_11[7] = 0x00, .deqA_11[8] = 0x00, .deqA_11[9] = 0x00, .deqA_11[10] = 0x00,	// BankA 0x3a
			.deqA_12[0] = 0xB2, .deqA_12[1] = 0xB2, .deqA_12[2] = 0xB2, .deqA_12[3] = 0xB2, .deqA_12[4] = 0xB2, .deqA_12[5] = 0xB2, .deqA_12[6] = 0xB2,  .deqA_12[7] = 0xB2, .deqA_12[8] = 0xB2, .deqA_12[9] = 0xB2, .deqA_12[10] = 0xB2,	// BankA 0x3b
		},
		/* color */
		{
			.contrast[0] 		= 0x82, .contrast[1] 		= 0x86, .contrast[2] 		= 0x84, .contrast[3] 		= 0x81, .contrast[4] 		= 0x7f, .contrast[5] 		= 0x7e, .contrast[6] 		= 0x7a, .contrast[7] 		= 0x7a, .contrast[8] 		= 0x72, .contrast[9] 		= 0x6d, .contrast[10] 		= 0x6d,
			.h_peaking[0] 		= 0x00, .h_peaking[1] 		= 0x00, .h_peaking[2] 		= 0x00, .h_peaking[3] 		= 0x00, .h_peaking[4] 		= 0x00, .h_peaking[5] 		= 0x00, .h_peaking[6] 		= 0x00, .h_peaking[7] 		= 0x3f, .h_peaking[8] 		= 0x3f, .h_peaking[9] 		= 0x3f, .h_peaking[10] 		= 0x3f,
			.c_filter[0]		= 0x82, .c_filter[1] 		= 0x92, .c_filter[2]	 	= 0x92, .c_filter[3] 		= 0xa2, .c_filter[4] 		= 0xa2, .c_filter[5] 		= 0xa2, .c_filter[6] 		= 0xb2, .c_filter[7] 		= 0xb2, .c_filter[8] 		= 0xb2, .c_filter[9] 		= 0xb2, .c_filter[10] 		= 0xb2,
			.hue[0] 			= 0x00, .hue[1] 			= 0x00, .hue[2] 			= 0x00, .hue[3] 			= 0x00, .hue[4] 			= 0x00, .hue[5] 			= 0x00, .hue[6] 			= 0x00, .hue[7] 			= 0x00, .hue[8] 			= 0x00, .hue[9] 			= 0x00, .hue[10] 			= 0x00,
			.u_gain[0] 			= 0xe0, .u_gain[1] 			= 0xe0, .u_gain[2] 			= 0xe0, .u_gain[3] 			= 0xe0, .u_gain[4] 			= 0xe0, .u_gain[5] 			= 0xe0, .u_gain[6] 			= 0xe0, .u_gain[7] 			= 0xe0, .u_gain[8] 			= 0xe0, .u_gain[9] 			= 0xe0, .u_gain[10] 		= 0xe0,
			.v_gain[0] 			= 0x00, .v_gain[1] 			= 0x00, .v_gain[2] 			= 0x00, .v_gain[3] 			= 0x00, .v_gain[4] 			= 0x00, .v_gain[5] 			= 0x00, .v_gain[6] 			= 0x00, .v_gain[7] 			= 0x00, .v_gain[8] 			= 0x00, .v_gain[9] 			= 0x00, .v_gain[10] 		= 0x00,
			.u_offset[0] 		= 0xff, .u_offset[1] 		= 0xff, .u_offset[2] 		= 0xff, .u_offset[3] 		= 0xff, .u_offset[4] 		= 0xff, .u_offset[5] 		= 0xff, .u_offset[6] 		= 0xff, .u_offset[7] 		= 0xff, .u_offset[8] 		= 0xff, .u_offset[9] 		= 0xff, .u_offset[10] 		= 0xff,
			.v_offset[0] 		= 0x00, .v_offset[1] 		= 0x00, .v_offset[2] 		= 0x00, .v_offset[3] 		= 0x00, .v_offset[4] 		= 0x00, .v_offset[5] 		= 0x00, .v_offset[6] 		= 0x00, .v_offset[7] 		= 0x00, .v_offset[8] 		= 0x00, .v_offset[9] 		= 0x00, .v_offset[10] 		= 0x00,

			.black_level[0] 	= 0x86, .black_level[1] 	= 0x88, .black_level[2] 	= 0x86, .black_level[3] 	= 0x86, .black_level[4] 	= 0x88, .black_level[5] 	= 0x8a, .black_level[6] 	= 0x8c, .black_level[7] 	= 0x92, .black_level[8] 	= 0x95, .black_level[9] 	= 0x98, .black_level[10] 	= 0x98,
			.acc_ref[0]			= 0x57, .acc_ref[1]			= 0x57, .acc_ref[2]			= 0x57, .acc_ref[3]			= 0x57, .acc_ref[4]			= 0x57, .acc_ref[5]			= 0x57, .acc_ref[6]			= 0x57, .acc_ref[7]			= 0x37, .acc_ref[8]			= 0x20, .acc_ref[9]			= 0x20, .acc_ref[10]		= 0x57,
			.cti_delay[0]		= 0x80, .cti_delay[1]		= 0x80, .cti_delay[2]		= 0x80, .cti_delay[3]		= 0x80, .cti_delay[4]		= 0x80, .cti_delay[5]		= 0x80, .cti_delay[6]		= 0x80, .cti_delay[7]		= 0x80, .cti_delay[8]		= 0x80, .cti_delay[9]		= 0x80, .cti_delay[10]		= 0x80,
			.sub_saturation[0] 	= 0xa8, .sub_saturation[1] 	= 0xaa, .sub_saturation[2] 	= 0xaa, .sub_saturation[3] 	= 0xac, .sub_saturation[4] 	= 0xa8, .sub_saturation[5] 	= 0xa6, .sub_saturation[6] 	= 0x98, .sub_saturation[7] 	= 0xa0, .sub_saturation[8] 	= 0xa0, .sub_saturation[9] 	= 0x50, .sub_saturation[10] = 0x50,

			.burst_dec_a[0] 	= 0x2a, .burst_dec_a[1] 	= 0x2a, .burst_dec_a[2] 	= 0x2a, .burst_dec_a[3] 	= 0x2a, .burst_dec_a[4] 	= 0x2a, .burst_dec_a[5] 	= 0x2a, .burst_dec_a[6] 	= 0x2a, .burst_dec_a[7] 	= 0x2a, .burst_dec_a[8] 	= 0x2a, .burst_dec_a[9] 	= 0x2a, .burst_dec_a[10] 	= 0x2a,
			.burst_dec_b[0] 	= 0x00, .burst_dec_b[1] 	= 0x00, .burst_dec_b[2] 	= 0x00, .burst_dec_b[3] 	= 0x00, .burst_dec_b[4] 	= 0x00, .burst_dec_b[5] 	= 0x00, .burst_dec_b[6] 	= 0x00, .burst_dec_b[7] 	= 0x00, .burst_dec_b[8] 	= 0x00, .burst_dec_b[9] 	= 0x00, .burst_dec_b[10] 	= 0x00,
			.burst_dec_c[0] 	= 0x00, .burst_dec_c[1] 	= 0x00, .burst_dec_c[2] 	= 0x00, .burst_dec_c[3] 	= 0x00, .burst_dec_c[4] 	= 0x00, .burst_dec_c[5] 	= 0x00, .burst_dec_c[6] 	= 0x00, .burst_dec_c[7] 	= 0x00, .burst_dec_c[8] 	= 0x00, .burst_dec_c[9] 	= 0x00, .burst_dec_c[10] 	= 0x00,

			.c_option[0] 		= 0x80, .c_option[1] 		= 0x80, .c_option[2] 		= 0x80, .c_option[3] 		= 0xb0, .c_option[4] 		= 0xb0, .c_option[5] 		= 0xb0, .c_option[6] 		= 0xb0, .c_option[7] 		= 0xb0, .c_option[8] 		= 0xb0, .c_option[9] 		= 0xb0, .c_option[10] 		= 0xb0,

			.y_filter_b[0]		= 0x10, .y_filter_b[1]		= 0x10, .y_filter_b[2]		= 0x10, .y_filter_b[3]		= 0x10, .y_filter_b[4]		= 0x10, .y_filter_b[5]		= 0x10, .y_filter_b[6]		= 0x10, .y_filter_b[7]		= 0x10, .y_filter_b[8]		= 0x10, .y_filter_b[9]		= 0x10, .y_filter_b[10]		= 0x10,
			.y_filter_b_sel[0]	= 0x1e,	.y_filter_b_sel[1]	= 0x1e,	.y_filter_b_sel[2]	= 0x1e, .y_filter_b_sel[3]	= 0x1e, .y_filter_b_sel[4]	= 0x1e, .y_filter_b_sel[5]	= 0x1e, .y_filter_b_sel[6]	= 0x1e, .y_filter_b_sel[7]	= 0x1e, .y_filter_b_sel[8]	= 0x1e, .y_filter_b_sel[9]	= 0x1e, .y_filter_b_sel[10]	= 0x1e,
		},
		/* timing_a */
		{
			.h_delay_a[0] = 0x80, .h_delay_a[1] = 0x7e, .h_delay_a[2] = 0x7d, .h_delay_a[3] = 0x7c, .h_delay_a[4] = 0x7c, .h_delay_a[5] = 0x7d, .h_delay_a[6] = 0x7d, .h_delay_a[7] = 0x7d, .h_delay_a[8] = 0x7d, .h_delay_a[9] = 0x7d, .h_delay_a[10] = 0x7d,
			.h_delay_b[0] = 0x00, .h_delay_b[1] = 0x00, .h_delay_b[2] = 0x00, .h_delay_b[3] = 0x00, .h_delay_b[4] = 0x00, .h_delay_b[5] = 0x00, .h_delay_b[6] = 0x00, .h_delay_b[7] = 0x00, .h_delay_b[8] = 0x00, .h_delay_b[9] = 0x00, .h_delay_b[10] = 0x00,
			.h_delay_c[0] = 0x00, .h_delay_c[1] = 0x00, .h_delay_c[2] = 0x00, .h_delay_c[3] = 0x00, .h_delay_c[4] = 0x00, .h_delay_c[5] = 0x00, .h_delay_c[6] = 0x00, .h_delay_c[7] = 0x00, .h_delay_c[8] = 0x00, .h_delay_c[9] = 0x00, .h_delay_c[10] = 0x00,
			.y_delay[0]   = 0x05, .y_delay[1]   = 0x05, .y_delay[2]   = 0x05, .y_delay[3]   = 0x05, .y_delay[4]   = 0x05, .y_delay[5] =   0x05, .y_delay[6] =   0x05, .y_delay[7] =   0x05, .y_delay[8] =   0x05, .y_delay[9] =   0x05, .y_delay[10] =   0x05,

		},
		/* clk */
		{
			.clk_adc[0] = 0x05, .clk_adc[1] = 0x05, .clk_adc[2] = 0x05, .clk_adc[3] = 0x05, .clk_adc[4] = 0x05, .clk_adc[5] = 0x05, .clk_adc[6] = 0x05, .clk_adc[7] = 0x05, .clk_adc[8] = 0x05, .clk_adc[9] = 0x05, .clk_adc[10] = 0x05,
			.clk_dec[0] = 0x44, .clk_dec[1] = 0x44, .clk_dec[2] = 0x44, .clk_dec[3] = 0x44, .clk_dec[4] = 0x44, .clk_dec[5] = 0x44, .clk_dec[6] = 0x44, .clk_dec[7] = 0x44, .clk_dec[8] = 0x44, .clk_dec[9] = 0x44, .clk_dec[10] = 0x44,
		},
		/* timing_b */
		{
	/*B9 0x96*/	.h_scaler1[0]  = 0x01, .h_scaler1[1]   = 0x01, .h_scaler1[2]   = 0x01, .h_scaler1[3]   = 0x01, .h_scaler1[4]   = 0x01, .h_scaler1[5]   = 0x01, .h_scaler1[6]   = 0x01, .h_scaler1[7]   = 0x01, .h_scaler1[8]   = 0x01, .h_scaler1[9]   = 0x01, .h_scaler1[10]   = 0x01,
	/*B9 0x97*/	.h_scaler2[0]  = 0x59, .h_scaler2[1]   = 0x59, .h_scaler2[2]   = 0x59, .h_scaler2[3]   = 0x59, .h_scaler2[4]   = 0x59, .h_scaler2[5]   = 0x59, .h_scaler2[6]   = 0x59, .h_scaler2[7]   = 0x59, .h_scaler2[8]   = 0x59, .h_scaler2[9]   = 0x59, .h_scaler2[10]   = 0x59,
	/*B9 0x98*/	.h_scaler3[0]  = 0x30, .h_scaler3[1]   = 0x30, .h_scaler3[2]   = 0x30, .h_scaler3[3]   = 0x30, .h_scaler3[4]   = 0x30, .h_scaler3[5]   = 0x30, .h_scaler3[6]   = 0x30, .h_scaler3[7]   = 0x30, .h_scaler3[8]   = 0x30, .h_scaler3[9]   = 0x30, .h_scaler3[10]   = 0x30,
	/*B9 0x99*/	.h_scaler4[0]  = 0x00, .h_scaler4[1]   = 0x00, .h_scaler4[2]   = 0x00, .h_scaler4[3]   = 0x00, .h_scaler4[4]   = 0x00, .h_scaler4[5]   = 0x00, .h_scaler4[6]   = 0x00, .h_scaler4[7]   = 0x00, .h_scaler4[8]   = 0x00, .h_scaler4[9]   = 0x00, .h_scaler4[10]   = 0x00,
	/*B9 0x9a*/	.h_scaler5[0]  = 0x00, .h_scaler5[1]   = 0x00, .h_scaler5[2]   = 0x00, .h_scaler5[3]   = 0x00, .h_scaler5[4]   = 0x00, .h_scaler5[5]   = 0x00, .h_scaler5[6]   = 0x00, .h_scaler5[7]   = 0x00, .h_scaler5[8]   = 0x00, .h_scaler5[9]   = 0x00, .h_scaler5[10]   = 0x00,
	/*B9 0x9b*/	.h_scaler6[0]  = 0x00, .h_scaler6[1]   = 0x00, .h_scaler6[2]   = 0x00, .h_scaler6[3]   = 0x00, .h_scaler6[4]   = 0x00, .h_scaler6[5]   = 0x00, .h_scaler6[6]   = 0x00, .h_scaler6[7]   = 0x00, .h_scaler6[8]   = 0x00, .h_scaler6[9]   = 0x00, .h_scaler6[10]   = 0x00,
	/*B9 0x9c*/	.h_scaler7[0]  = 0x00, .h_scaler7[1]   = 0x00, .h_scaler7[2]   = 0x00, .h_scaler7[3]   = 0x00, .h_scaler7[4]   = 0x00, .h_scaler7[5]   = 0x00, .h_scaler7[6]   = 0x00, .h_scaler7[7]   = 0x00, .h_scaler7[8]   = 0x00, .h_scaler7[9]   = 0x00, .h_scaler7[10]   = 0x00,
	/*B9 0x9d*/	.h_scaler8[0]  = 0x00, .h_scaler8[1]   = 0x00, .h_scaler8[2]   = 0x00, .h_scaler8[3]   = 0x00, .h_scaler8[4]   = 0x00, .h_scaler8[5]   = 0x00, .h_scaler8[6]   = 0x00, .h_scaler8[7]   = 0x00, .h_scaler8[8]   = 0x00, .h_scaler8[9]   = 0x00, .h_scaler8[10]   = 0x00,
	/*B9 0x9e*/	.h_scaler9[0]  = 0x80, .h_scaler9[1]   = 0x80, .h_scaler9[2]   = 0x80, .h_scaler9[3]   = 0x80, .h_scaler9[4]   = 0x80, .h_scaler9[5]   = 0x80, .h_scaler9[6]   = 0x80, .h_scaler9[7]   = 0x80, .h_scaler9[8]   = 0x80, .h_scaler9[9]   = 0x80, .h_scaler9[10]   = 0x80,


	/*B9 0x40*/	.pn_auto[0]    	= 0x00, .pn_auto[1]		= 0x00, .pn_auto[2]    	= 0x00, .pn_auto[3]    	= 0x00, .pn_auto[4]    	= 0x00, .pn_auto[5]    	= 0x00, .pn_auto[6]		= 0x00, .pn_auto[7]    	= 0x00, .pn_auto[8]    	= 0x00, .pn_auto[9]    	= 0x00, .pn_auto[10]    	= 0x00,

	/*B5 0x90*/	.comb_mode[0]   = 0x05, .comb_mode[1]	= 0x05, .comb_mode[2]   = 0x05, .comb_mode[3]   = 0x05, .comb_mode[4]  	= 0x05, .comb_mode[5]   = 0x05, .comb_mode[6]	= 0x05, .comb_mode[7]   = 0x05, .comb_mode[8]   = 0x05, .comb_mode[9]  	= 0x05, .comb_mode[10]   = 0x05,
	/*B9 0xb9*/	.h_pll_op_a[0]  = 0x72, .h_pll_op_a[1]  = 0x72, .h_pll_op_a[2]  = 0x72, .h_pll_op_a[3]  = 0x72, .h_pll_op_a[4]  = 0x72, .h_pll_op_a[5]  = 0x72, .h_pll_op_a[6]  = 0x72, .h_pll_op_a[7]  = 0x72, .h_pll_op_a[8]  = 0x72, .h_pll_op_a[9]  = 0x72, .h_pll_op_a[10]  = 0x72,
	/*B9 0x57*/	.mem_path[0]	= 0x10, .mem_path[1]	= 0x10, .mem_path[2]	= 0x10, .mem_path[3]	= 0x10, .mem_path[4]	= 0x10, .mem_path[5]	= 0x10, .mem_path[6]	= 0x10, .mem_path[7]	= 0x10, .mem_path[8]	= 0x10, .mem_path[9]	= 0x10, .mem_path[10]	 = 0x10,
			.fsc_lock_speed[0] = 0xdc, .fsc_lock_speed[1] = 0xdc, .fsc_lock_speed[2] = 0xdc, .fsc_lock_speed[3] = 0xdc, .fsc_lock_speed[4] = 0xdc, .fsc_lock_speed[5] = 0xdc, .fsc_lock_speed[6] = 0xdc, .fsc_lock_speed[7] = 0xdc, .fsc_lock_speed[8] = 0xdc, .fsc_lock_speed[9] = 0xdc, .fsc_lock_speed[10] = 0xdc,

	/*B0 0x81*/	.format_set1[0] = 0x0A, .format_set1[1] = 0x0A, .format_set1[2] = 0x0A, .format_set1[3] = 0x0A, .format_set1[4] = 0x0A, .format_set1[5] = 0x0A, .format_set1[6] = 0x0A, .format_set1[7] = 0x0A, .format_set1[8] = 0x0A, .format_set1[9] = 0x0A, .format_set1[10] = 0x0A,
	/*B0 0x85*/	.format_set2[0] = 0x01, .format_set2[1] = 0x01, .format_set2[2] = 0x01, .format_set2[3] = 0x01, .format_set2[4] = 0x01, .format_set2[5] = 0x01, .format_set2[6] = 0x01, .format_set2[7] = 0x01, .format_set2[8] = 0x01, .format_set2[9] = 0x01, .format_set2[10] = 0x01,

	/*B0 0x64*/ .v_delay[0]     = 0x20, .v_delay[1]     = 0x20, .v_delay[2]     = 0x20, .v_delay[3]     = 0x20, .v_delay[4]     = 0x20, .v_delay[5]     = 0x20, .v_delay[6]     = 0x20, .v_delay[7]     = 0x20, .v_delay[8]     = 0x20, .v_delay[9]     = 0x20, .v_delay[10]     = 0x20,
		},
	},

#ifdef __FOR_HIK_DEMO_180208

	[ TVI_HD_B_25P_EX ] = /* o */
		{
		/* base */
			{
				.eq_bypass[0] 	= 0x22, .eq_bypass[1] 	= 0x22, .eq_bypass[2] 	= 0x22, .eq_bypass[3] 	= 0x22, .eq_bypass[4] 	= 0x22, .eq_bypass[5] 	= 0x22, .eq_bypass[6] 	= 0x22, .eq_bypass[7] 	= 0x22, .eq_bypass[8] 	= 0x22, .eq_bypass[9] 	= 0x22, .eq_bypass[10] 	 = 0x22,  // Bank5 0x30
				.eq_band_sel[0] = 0x77, .eq_band_sel[1] = 0x67, .eq_band_sel[2] = 0x57, .eq_band_sel[3] = 0x57, .eq_band_sel[4] = 0x57, .eq_band_sel[5] = 0x47, .eq_band_sel[6] = 0x37, .eq_band_sel[7] = 0x27, .eq_band_sel[8] = 0x17, .eq_band_sel[9] = 0x17, .eq_band_sel[10] = 0x07, // BankA 0x31
				.eq_gain_sel[0] = 0x78, .eq_gain_sel[1] = 0x78, .eq_gain_sel[2] = 0x78, .eq_gain_sel[3] = 0x7f, .eq_gain_sel[4] = 0x7f, .eq_gain_sel[5] = 0x7f, .eq_gain_sel[6] = 0x7f, .eq_gain_sel[7] = 0x7f, .eq_gain_sel[8] = 0x7f, .eq_gain_sel[9] = 0x7f, .eq_gain_sel[10] = 0x7f, // BankA 0x32
				.deq_a_on[0] 	= 0x00, .deq_a_on[1] 	= 0x01, .deq_a_on[2] 	= 0x01, .deq_a_on[3] 	= 0x01, .deq_a_on[4] 	= 0x01, .deq_a_on[5] 	= 0x01, .deq_a_on[6] 	= 0x01, .deq_a_on[7] 	= 0x01, .deq_a_on[8] 	= 0x01, .deq_a_on[9] 	= 0x01, .deq_a_on[10] 	 = 0x01, // BankA 0x33
				.deq_a_sel[0] 	= 0x00, .deq_a_sel[1] 	= 0x91, .deq_a_sel[2] 	= 0x92, .deq_a_sel[3] 	= 0x93, .deq_a_sel[4] 	= 0x93, .deq_a_sel[5] 	= 0x93, .deq_a_sel[6] 	= 0x93, .deq_a_sel[7] 	= 0x93, .deq_a_sel[8] 	= 0x93, .deq_a_sel[9] 	= 0x93, .deq_a_sel[10] 	 = 0x92, // BankA 0x34
				.deq_b_sel[0] 	= 0x00, .deq_b_sel[1] 	= 0x00, .deq_b_sel[2] 	= 0x00, .deq_b_sel[3] 	= 0x00, .deq_b_sel[4] 	= 0x00, .deq_b_sel[5] 	= 0x00, .deq_b_sel[6] 	= 0x00, .deq_b_sel[7] 	= 0x00, .deq_b_sel[8] 	= 0x00, .deq_b_sel[9] 	= 0x00, .deq_b_sel[10] 	 = 0x00, // BankA 0x35
		},
			/* coeff */
			{
				.deqA_01[0] = 0xAC, .deqA_01[1] = 0xAC, .deqA_01[2] = 0xAC, .deqA_01[3] = 0xAC, .deqA_01[4] = 0xAC, .deqA_01[5] = 0xAC,	.deqA_01[6] = 0xAC,  .deqA_01[7] = 0xAC, .deqA_01[8] = 0xAC, .deqA_01[9] = 0xAC, .deqA_01[10] = 0xAC,	// BankA 0x30
				.deqA_02[0] = 0x78, .deqA_02[1] = 0x78, .deqA_02[2] = 0x78, .deqA_02[3] = 0x78, .deqA_02[4] = 0x78, .deqA_02[5] = 0x78,	.deqA_02[6] = 0x78,	 .deqA_02[7] = 0x78, .deqA_02[8] = 0x78, .deqA_02[9] = 0x78, .deqA_02[10] = 0x78,	// BankA 0x31
				.deqA_03[0] = 0x17, .deqA_03[1] = 0x17, .deqA_03[2] = 0x17, .deqA_03[3] = 0x17, .deqA_03[4] = 0x17, .deqA_03[5] = 0x17,	.deqA_03[6] = 0x17,	 .deqA_03[7] = 0x17, .deqA_03[8] = 0x17, .deqA_03[9] = 0x17, .deqA_03[10] = 0x17,	// BankA 0x32
				.deqA_04[0] = 0xC1, .deqA_04[1] = 0xC1, .deqA_04[2] = 0xC1, .deqA_04[3] = 0xC1, .deqA_04[4] = 0xC1, .deqA_04[5] = 0xC1, .deqA_04[6] = 0xC1,  .deqA_04[7] = 0xC1, .deqA_04[8] = 0xC1, .deqA_04[9] = 0xC1, .deqA_04[10] = 0xC1,	// BankA 0x33
				.deqA_05[0] = 0x40, .deqA_05[1] = 0x40, .deqA_05[2] = 0x40, .deqA_05[3] = 0x40, .deqA_05[4] = 0x40, .deqA_05[5] = 0x40, .deqA_05[6] = 0x40,  .deqA_05[7] = 0x40, .deqA_05[8] = 0x40, .deqA_05[9] = 0x40, .deqA_05[10] = 0x40,	// BankA 0x34
				.deqA_06[0] = 0x00, .deqA_06[1] = 0x00, .deqA_06[2] = 0x00, .deqA_06[3] = 0x00, .deqA_06[4] = 0x00, .deqA_06[5] = 0x00, .deqA_06[6] = 0x00,  .deqA_06[7] = 0x00, .deqA_06[8] = 0x00, .deqA_06[9] = 0x00, .deqA_06[10] = 0x00,	// BankA 0x35
				.deqA_07[0] = 0xC3, .deqA_07[1] = 0xC3, .deqA_07[2] = 0xC3, .deqA_07[3] = 0xC3, .deqA_07[4] = 0xC3, .deqA_07[5] = 0xC3, .deqA_07[6] = 0xC3,  .deqA_07[7] = 0xC3, .deqA_07[8] = 0xC3, .deqA_07[9] = 0xC3, .deqA_07[10] = 0xC3,	// BankA 0x36
				.deqA_08[0] = 0x0A, .deqA_08[1] = 0x0A, .deqA_08[2] = 0x0A, .deqA_08[3] = 0x0A, .deqA_08[4] = 0x0A, .deqA_08[5] = 0x0A, .deqA_08[6] = 0x0A,  .deqA_08[7] = 0x0A, .deqA_08[8] = 0x0A, .deqA_08[9] = 0x0A, .deqA_08[10] = 0x0A,	// BankA 0x37
				.deqA_09[0] = 0x00, .deqA_09[1] = 0x00, .deqA_09[2] = 0x00, .deqA_09[3] = 0x00, .deqA_09[4] = 0x00, .deqA_09[5] = 0x00, .deqA_09[6] = 0x00,  .deqA_09[7] = 0x00, .deqA_09[8] = 0x00, .deqA_09[9] = 0x00, .deqA_09[10] = 0x00,	// BankA 0x38
				.deqA_10[0] = 0x02, .deqA_10[1] = 0x02, .deqA_10[2] = 0x02, .deqA_10[3] = 0x02, .deqA_10[4] = 0x02, .deqA_10[5] = 0x02, .deqA_10[6] = 0x02,  .deqA_10[7] = 0x02, .deqA_10[8] = 0x02, .deqA_10[9] = 0x02, .deqA_10[10] = 0x02,	// BankA 0x39
				.deqA_11[0] = 0x00, .deqA_11[1] = 0x00, .deqA_11[2] = 0x00, .deqA_11[3] = 0x00, .deqA_11[4] = 0x00, .deqA_11[5] = 0x00, .deqA_11[6] = 0x00,  .deqA_11[7] = 0x00, .deqA_11[8] = 0x00, .deqA_11[9] = 0x00, .deqA_11[10] = 0x00,	// BankA 0x3a
				.deqA_12[0] = 0xB2, .deqA_12[1] = 0xB2, .deqA_12[2] = 0xB2, .deqA_12[3] = 0xB2, .deqA_12[4] = 0xB2, .deqA_12[5] = 0xB2, .deqA_12[6] = 0xB2,  .deqA_12[7] = 0xB2, .deqA_12[8] = 0xB2, .deqA_12[9] = 0xB2, .deqA_12[10] = 0xB2,	// BankA 0x3b
			},
			/* color */
			{
				.contrast[0] 		= 0x80, .contrast[1] 		= 0x80, .contrast[2] 		= 0x80, .contrast[3] 		= 0x80, .contrast[4] 		= 0x80, .contrast[5] 		= 0x80, .contrast[6] 		= 0x80, .contrast[7] 		= 0x80, .contrast[8] 		= 0x80, .contrast[9] 		= 0x6d, .contrast[10] 		= 0x6d,
				.h_peaking[0] 		= 0x00, .h_peaking[1] 		= 0x00, .h_peaking[2] 		= 0x00, .h_peaking[3] 		= 0x00, .h_peaking[4] 		= 0x00, .h_peaking[5] 		= 0x00, .h_peaking[6] 		= 0x00, .h_peaking[7] 		= 0x00, .h_peaking[8] 		= 0x00, .h_peaking[9] 		= 0x3f, .h_peaking[10] 		= 0x3f,
				.c_filter[0]		= 0x82, .c_filter[1] 		= 0x82, .c_filter[2]	 	= 0x82, .c_filter[3] 		= 0x82, .c_filter[4] 		= 0x82, .c_filter[5] 		= 0x82, .c_filter[6] 		= 0x82, .c_filter[7] 		= 0x82, .c_filter[8] 		= 0x82, .c_filter[9] 		= 0xb2, .c_filter[10] 		= 0xb2,
				.hue[0] 			= 0x02, .hue[1] 			= 0x02, .hue[2] 			= 0x02, .hue[3] 			= 0x02, .hue[4] 			= 0x02, .hue[5] 			= 0x02, .hue[6] 			= 0x02, .hue[7] 			= 0x02, .hue[8] 			= 0x02, .hue[9] 			= 0x00, .hue[10] 			= 0x00,
				.u_gain[0] 			= 0x20, .u_gain[1] 			= 0x28, .u_gain[2] 			= 0x40, .u_gain[3] 			= 0x40, .u_gain[4] 			= 0x40, .u_gain[5] 			= 0x40, .u_gain[6] 			= 0x40, .u_gain[7] 			= 0x40, .u_gain[8] 			= 0x40, .u_gain[9] 			= 0x00, .u_gain[10] 		= 0x00,
				.v_gain[0] 			= 0x00, .v_gain[1] 			= 0x08, .v_gain[2] 			= 0x20, .v_gain[3] 			= 0x20, .v_gain[4] 			= 0x10, .v_gain[5] 			= 0x10, .v_gain[6] 			= 0x10, .v_gain[7] 			= 0x10, .v_gain[8] 			= 0x10, .v_gain[9] 			= 0x00, .v_gain[10] 		= 0x00,
				.u_offset[0] 		= 0x00, .u_offset[1] 		= 0x00, .u_offset[2] 		= 0x00, .u_offset[3] 		= 0x00, .u_offset[4] 		= 0xfc, .u_offset[5] 		= 0xfc, .u_offset[6] 		= 0xfc, .u_offset[7] 		= 0xfc, .u_offset[8] 		= 0xfc, .u_offset[9] 		= 0x00, .u_offset[10] 		= 0x00,
				.v_offset[0] 		= 0xf0, .v_offset[1] 		= 0xf0, .v_offset[2] 		= 0xf0, .v_offset[3] 		= 0xf0, .v_offset[4] 		= 0xf4, .v_offset[5] 		= 0xf4, .v_offset[6] 		= 0xf0, .v_offset[7] 		= 0xf0, .v_offset[8] 		= 0xf0, .v_offset[9] 		= 0x00, .v_offset[10] 		= 0x00,

				.black_level[0] 	= 0x8c, .black_level[1] 	= 0x8c, .black_level[2] 	= 0x90, .black_level[3] 	= 0x90, .black_level[4] 	= 0x92, .black_level[5] 	= 0x92, .black_level[6] 	= 0x92, .black_level[7] 	= 0x92, .black_level[8] 	= 0x92, .black_level[9] 	= 0x98, .black_level[10] 	= 0x98,
				.acc_ref[0]			= 0x57, .acc_ref[1]			= 0x57, .acc_ref[2]			= 0x57, .acc_ref[3]			= 0x57, .acc_ref[4]			= 0x57, .acc_ref[5]			= 0x57, .acc_ref[6]			= 0x57, .acc_ref[7]			= 0x47, .acc_ref[8]			= 0x47, .acc_ref[9]			= 0x20, .acc_ref[10]		= 0x57,
				.cti_delay[0]		= 0x80, .cti_delay[1]		= 0x80, .cti_delay[2]		= 0x80, .cti_delay[3]		= 0x80, .cti_delay[4]		= 0x80, .cti_delay[5]		= 0x80, .cti_delay[6]		= 0x80, .cti_delay[7]		= 0x80, .cti_delay[8]		= 0x80, .cti_delay[9]		= 0x80, .cti_delay[10]		= 0x80,
				.sub_saturation[0] 	= 0xf0, .sub_saturation[1] 	= 0xf0, .sub_saturation[2] 	= 0xf0, .sub_saturation[3] 	= 0xf0, .sub_saturation[4] 	= 0xf0, .sub_saturation[5] 	= 0xf0, .sub_saturation[6] 	= 0xf0, .sub_saturation[7] 	= 0xf0, .sub_saturation[8] 	= 0xf0, .sub_saturation[9] 	= 0x50, .sub_saturation[10] = 0x50,

				.burst_dec_a[0] 	= 0x2a, .burst_dec_a[1] 	= 0x2a, .burst_dec_a[2] 	= 0x2a, .burst_dec_a[3] 	= 0x2a, .burst_dec_a[4] 	= 0x2a, .burst_dec_a[5] 	= 0x2a, .burst_dec_a[6] 	= 0x2a, .burst_dec_a[7] 	= 0x2a, .burst_dec_a[8] 	= 0x2a, .burst_dec_a[9] 	= 0x2a, .burst_dec_a[10] 	= 0x2a,
				.burst_dec_b[0] 	= 0x00, .burst_dec_b[1] 	= 0x00, .burst_dec_b[2] 	= 0x00, .burst_dec_b[3] 	= 0x00, .burst_dec_b[4] 	= 0x00, .burst_dec_b[5] 	= 0x00, .burst_dec_b[6] 	= 0x00, .burst_dec_b[7] 	= 0x00, .burst_dec_b[8] 	= 0x00, .burst_dec_b[9] 	= 0x00, .burst_dec_b[10] 	= 0x00,
				.burst_dec_c[0] 	= 0x00, .burst_dec_c[1] 	= 0x00, .burst_dec_c[2] 	= 0x00, .burst_dec_c[3] 	= 0x00, .burst_dec_c[4] 	= 0x00, .burst_dec_c[5] 	= 0x00, .burst_dec_c[6] 	= 0x00, .burst_dec_c[7] 	= 0x00, .burst_dec_c[8] 	= 0x00, .burst_dec_c[9] 	= 0x00, .burst_dec_c[10] 	= 0x00,

				.c_option[0] 		= 0x80, .c_option[1] 		= 0x80, .c_option[2] 		= 0x80, .c_option[3] 		= 0x80, .c_option[4] 		= 0xb0, .c_option[5] 		= 0xb0, .c_option[6] 		= 0xb0, .c_option[7] 		= 0xb0, .c_option[8] 		= 0xb0, .c_option[9] 		= 0xb0, .c_option[10] 		= 0xb0,

				.y_filter_b[0]		= 0x10, .y_filter_b[1]		= 0x10, .y_filter_b[2]		= 0x10, .y_filter_b[3]		= 0x10, .y_filter_b[4]		= 0x10, .y_filter_b[5]		= 0x10, .y_filter_b[6]		= 0x10, .y_filter_b[7]		= 0x10, .y_filter_b[8]		= 0x10, .y_filter_b[9]		= 0x10, .y_filter_b[10]		= 0x10,
				.y_filter_b_sel[0]	= 0x1e,	.y_filter_b_sel[1]	= 0x1e,	.y_filter_b_sel[2]	= 0x1e, .y_filter_b_sel[3]	= 0x1e, .y_filter_b_sel[4]	= 0x1e, .y_filter_b_sel[5]	= 0x1e, .y_filter_b_sel[6]	= 0x1e, .y_filter_b_sel[7]	= 0x1e, .y_filter_b_sel[8]	= 0x1e, .y_filter_b_sel[9]	= 0x1e, .y_filter_b_sel[10]	= 0x1e,
			},
			/* timing_a */
			{
				.h_delay_a[0] = 0x82, .h_delay_a[1] = 0x80, .h_delay_a[2] = 0x7f, .h_delay_a[3] = 0x7e, .h_delay_a[4] = 0x7e, .h_delay_a[5] = 0x7f, .h_delay_a[6] = 0x7f, .h_delay_a[7] = 0x7f, .h_delay_a[8] = 0x7f, .h_delay_a[9] = 0x7f, .h_delay_a[10] = 0x7f,
				.h_delay_b[0] = 0x10, .h_delay_b[1] = 0x10, .h_delay_b[2] = 0x10, .h_delay_b[3] = 0x10, .h_delay_b[4] = 0x10, .h_delay_b[5] = 0x10, .h_delay_b[6] = 0x10, .h_delay_b[7] = 0x10, .h_delay_b[8] = 0x10, .h_delay_b[9] = 0x10, .h_delay_b[10] = 0x10,
				.h_delay_c[0] = 0x01, .h_delay_c[1] = 0x01, .h_delay_c[2] = 0x01, .h_delay_c[3] = 0x01, .h_delay_c[4] = 0x01, .h_delay_c[5] = 0x01, .h_delay_c[6] = 0x01, .h_delay_c[7] = 0x01, .h_delay_c[8] = 0x01, .h_delay_c[9] = 0x01, .h_delay_c[10] = 0x01,
				.y_delay[0]   = 0x05, .y_delay[1]   = 0x05, .y_delay[2]   = 0x05, .y_delay[3]   = 0x05, .y_delay[4]   = 0x05, .y_delay[5] =   0x05, .y_delay[6] =   0x05, .y_delay[7] =   0x05, .y_delay[8] =   0x05, .y_delay[9] =   0x05, .y_delay[10] =   0x05,

			},
			/* clk */
			{
				.clk_adc[0] = 0x02, .clk_adc[1] = 0x02, .clk_adc[2] = 0x02, .clk_adc[3] = 0x02, .clk_adc[4] = 0x02, .clk_adc[5] = 0x02, .clk_adc[6] = 0x02, .clk_adc[7] = 0x02, .clk_adc[8] = 0x02, .clk_adc[9] = 0x02, .clk_adc[10] = 0x02,
				.clk_dec[0] = 0x40, .clk_dec[1] = 0x40, .clk_dec[2] = 0x40, .clk_dec[3] = 0x40, .clk_dec[4] = 0x40, .clk_dec[5] = 0x40, .clk_dec[6] = 0x40, .clk_dec[7] = 0x40, .clk_dec[8] = 0x40, .clk_dec[9] = 0x40, .clk_dec[10] = 0x40,
			},
			/* timing_b */
			{
		/*B9 0x96*/	.h_scaler1[0]  = 0x01, .h_scaler1[1]   = 0x01, .h_scaler1[2]   = 0x01, .h_scaler1[3]   = 0x01, .h_scaler1[4]   = 0x01, .h_scaler1[5]   = 0x01, .h_scaler1[6]   = 0x01, .h_scaler1[7]   = 0x01, .h_scaler1[8]   = 0x01, .h_scaler1[9]   = 0x01, .h_scaler1[10]   = 0x01,
		/*B9 0x97*/	.h_scaler2[0]  = 0x00, .h_scaler2[1]   = 0x00, .h_scaler2[2]   = 0x00, .h_scaler2[3]   = 0x00, .h_scaler2[4]   = 0x00, .h_scaler2[5]   = 0x00, .h_scaler2[6]   = 0x00, .h_scaler2[7]   = 0x00, .h_scaler2[8]   = 0x00, .h_scaler2[9]   = 0x00, .h_scaler2[10]   = 0x59,
		/*B9 0x98*/	.h_scaler3[0]  = 0x00, .h_scaler3[1]   = 0x00, .h_scaler3[2]   = 0x00, .h_scaler3[3]   = 0x00, .h_scaler3[4]   = 0x00, .h_scaler3[5]   = 0x00, .h_scaler3[6]   = 0x00, .h_scaler3[7]   = 0x00, .h_scaler3[8]   = 0x00, .h_scaler3[9]   = 0x00, .h_scaler3[10]   = 0x00,
		/*B9 0x99*/	.h_scaler4[0]  = 0x00, .h_scaler4[1]   = 0x00, .h_scaler4[2]   = 0x00, .h_scaler4[3]   = 0x00, .h_scaler4[4]   = 0x00, .h_scaler4[5]   = 0x00, .h_scaler4[6]   = 0x00, .h_scaler4[7]   = 0x00, .h_scaler4[8]   = 0x00, .h_scaler4[9]   = 0x00, .h_scaler4[10]   = 0x00,
		/*B9 0x9a*/	.h_scaler5[0]  = 0x00, .h_scaler5[1]   = 0x00, .h_scaler5[2]   = 0x00, .h_scaler5[3]   = 0x00, .h_scaler5[4]   = 0x00, .h_scaler5[5]   = 0x00, .h_scaler5[6]   = 0x00, .h_scaler5[7]   = 0x00, .h_scaler5[8]   = 0x00, .h_scaler5[9]   = 0x00, .h_scaler5[10]   = 0x00,
		/*B9 0x9b*/	.h_scaler6[0]  = 0x00, .h_scaler6[1]   = 0x00, .h_scaler6[2]   = 0x00, .h_scaler6[3]   = 0x00, .h_scaler6[4]   = 0x00, .h_scaler6[5]   = 0x00, .h_scaler6[6]   = 0x00, .h_scaler6[7]   = 0x00, .h_scaler6[8]   = 0x00, .h_scaler6[9]   = 0x00, .h_scaler6[10]   = 0x00,
		/*B9 0x9c*/	.h_scaler7[0]  = 0x00, .h_scaler7[1]   = 0x00, .h_scaler7[2]   = 0x00, .h_scaler7[3]   = 0x00, .h_scaler7[4]   = 0x00, .h_scaler7[5]   = 0x00, .h_scaler7[6]   = 0x00, .h_scaler7[7]   = 0x00, .h_scaler7[8]   = 0x00, .h_scaler7[9]   = 0x00, .h_scaler7[10]   = 0x00,
		/*B9 0x9d*/	.h_scaler8[0]  = 0x00, .h_scaler8[1]   = 0x00, .h_scaler8[2]   = 0x00, .h_scaler8[3]   = 0x00, .h_scaler8[4]   = 0x00, .h_scaler8[5]   = 0x00, .h_scaler8[6]   = 0x00, .h_scaler8[7]   = 0x00, .h_scaler8[8]   = 0x00, .h_scaler8[9]   = 0x00, .h_scaler8[10]   = 0x00,
		/*B9 0x9e*/	.h_scaler9[0]  = 0x00, .h_scaler9[1]   = 0x00, .h_scaler9[2]   = 0x00, .h_scaler9[3]   = 0x00, .h_scaler9[4]   = 0x00, .h_scaler9[5]   = 0x00, .h_scaler9[6]   = 0x00, .h_scaler9[7]   = 0x00, .h_scaler9[8]   = 0x00, .h_scaler9[9]   = 0x00, .h_scaler9[10]   = 0x00,


		/*B9 0x40*/	.pn_auto[0]    	= 0x00, .pn_auto[1]		= 0x00, .pn_auto[2]    	= 0x00, .pn_auto[3]    	= 0x00, .pn_auto[4]    	= 0x00, .pn_auto[5]    	= 0x00, .pn_auto[6]		= 0x00, .pn_auto[7]    	= 0x00, .pn_auto[8]    	= 0x00, .pn_auto[9]    	= 0x00, .pn_auto[10]    	= 0x00,

		/*B5 0x90*/	.comb_mode[0]   = 0x05, .comb_mode[1]	= 0x05, .comb_mode[2]   = 0x05, .comb_mode[3]   = 0x05, .comb_mode[4]  	= 0x05, .comb_mode[5]   = 0x05, .comb_mode[6]	= 0x05, .comb_mode[7]   = 0x05, .comb_mode[8]   = 0x05, .comb_mode[9]  	= 0x05, .comb_mode[10]   = 0x05,
		/*B9 0xb9*/	.h_pll_op_a[0]  = 0x72, .h_pll_op_a[1]  = 0x72, .h_pll_op_a[2]  = 0x72, .h_pll_op_a[3]  = 0x72, .h_pll_op_a[4]  = 0x72, .h_pll_op_a[5]  = 0x72, .h_pll_op_a[6]  = 0x72, .h_pll_op_a[7]  = 0x72, .h_pll_op_a[8]  = 0x72, .h_pll_op_a[9]  = 0x72, .h_pll_op_a[10]  = 0x72,
		/*B9 0x57*/	.mem_path[0]	= 0x10, .mem_path[1]	= 0x10, .mem_path[2]	= 0x10, .mem_path[3]	= 0x10, .mem_path[4]	= 0x10, .mem_path[5]	= 0x10, .mem_path[6]	= 0x10, .mem_path[7]	= 0x10, .mem_path[8]	= 0x10, .mem_path[9]	= 0x10, .mem_path[10]	 = 0x10,
					.fsc_lock_speed[0] = 0xdc, .fsc_lock_speed[1] = 0xdc, .fsc_lock_speed[2] = 0xdc, .fsc_lock_speed[3] = 0xdc, .fsc_lock_speed[4] = 0xdc, .fsc_lock_speed[5] = 0xdc, .fsc_lock_speed[6] = 0xdc, .fsc_lock_speed[7] = 0xdc, .fsc_lock_speed[8] = 0xdc, .fsc_lock_speed[9] = 0xdc, .fsc_lock_speed[10] = 0xdc,

		/*B0 0x81*/	.format_set1[0] = 0x0b, .format_set1[1] = 0x0b, .format_set1[2] = 0x0b, .format_set1[3] = 0x0b, .format_set1[4] = 0x0b, .format_set1[5] = 0x0b, .format_set1[6] = 0x0b, .format_set1[7] = 0x0b, .format_set1[8] = 0x0b, .format_set1[9] = 0x0b, .format_set1[10] = 0x0b,
		/*B0 0x85*/	.format_set2[0] = 0x03, .format_set2[1] = 0x03, .format_set2[2] = 0x03, .format_set2[3] = 0x03, .format_set2[4] = 0x03, .format_set2[5] = 0x03, .format_set2[6] = 0x03, .format_set2[7] = 0x03, .format_set2[8] = 0x03, .format_set2[9] = 0x03, .format_set2[10] = 0x03,

		/*B0 0x64*/ .v_delay[0]     = 0x20, .v_delay[1]     = 0x20, .v_delay[2]     = 0x20, .v_delay[3]     = 0x20, .v_delay[4]     = 0x20, .v_delay[5]     = 0x20, .v_delay[6]     = 0x20, .v_delay[7]     = 0x20, .v_delay[8]     = 0x20, .v_delay[9]     = 0x20, .v_delay[10]     = 0x20,
			},
		},

#else

	[ TVI_HD_B_25P_EX ] = /* o */
	{
	/* base */
		{
			.eq_bypass[0] 	= 0x22, .eq_bypass[1] 	= 0x22, .eq_bypass[2] 	= 0x22, .eq_bypass[3] 	= 0x22, .eq_bypass[4] 	= 0x22, .eq_bypass[5] 	= 0x22, .eq_bypass[6] 	= 0x22, .eq_bypass[7] 	= 0x22, .eq_bypass[8] 	= 0x22, .eq_bypass[9] 	= 0x22, .eq_bypass[10] 	 = 0x22,  // Bank5 0x30
			.eq_band_sel[0] = 0x77, .eq_band_sel[1] = 0x67, .eq_band_sel[2] = 0x57, .eq_band_sel[3] = 0x57, .eq_band_sel[4] = 0x57, .eq_band_sel[5] = 0x47, .eq_band_sel[6] = 0x37, .eq_band_sel[7] = 0x27, .eq_band_sel[8] = 0x17, .eq_band_sel[9] = 0x17, .eq_band_sel[10] = 0x07, // BankA 0x31
			.eq_gain_sel[0] = 0x78, .eq_gain_sel[1] = 0x78, .eq_gain_sel[2] = 0x78, .eq_gain_sel[3] = 0x7f, .eq_gain_sel[4] = 0x7f, .eq_gain_sel[5] = 0x7f, .eq_gain_sel[6] = 0x7f, .eq_gain_sel[7] = 0x7f, .eq_gain_sel[8] = 0x7f, .eq_gain_sel[9] = 0x7f, .eq_gain_sel[10] = 0x7f, // BankA 0x32
			.deq_a_on[0] 	= 0x00, .deq_a_on[1] 	= 0x01, .deq_a_on[2] 	= 0x01, .deq_a_on[3] 	= 0x01, .deq_a_on[4] 	= 0x01, .deq_a_on[5] 	= 0x01, .deq_a_on[6] 	= 0x01, .deq_a_on[7] 	= 0x01, .deq_a_on[8] 	= 0x01, .deq_a_on[9] 	= 0x01, .deq_a_on[10] 	 = 0x01, // BankA 0x33
			.deq_a_sel[0] 	= 0x00, .deq_a_sel[1] 	= 0x91, .deq_a_sel[2] 	= 0x92, .deq_a_sel[3] 	= 0x93, .deq_a_sel[4] 	= 0x93, .deq_a_sel[5] 	= 0x93, .deq_a_sel[6] 	= 0x93, .deq_a_sel[7] 	= 0x93, .deq_a_sel[8] 	= 0x93, .deq_a_sel[9] 	= 0x93, .deq_a_sel[10] 	 = 0x92, // BankA 0x34
			.deq_b_sel[0] 	= 0x00, .deq_b_sel[1] 	= 0x00, .deq_b_sel[2] 	= 0x00, .deq_b_sel[3] 	= 0x00, .deq_b_sel[4] 	= 0x00, .deq_b_sel[5] 	= 0x00, .deq_b_sel[6] 	= 0x00, .deq_b_sel[7] 	= 0x00, .deq_b_sel[8] 	= 0x00, .deq_b_sel[9] 	= 0x00, .deq_b_sel[10] 	 = 0x00, // BankA 0x35
	},
		/* coeff */
		{
			.deqA_01[0] = 0xAC, .deqA_01[1] = 0xAC, .deqA_01[2] = 0xAC, .deqA_01[3] = 0xAC, .deqA_01[4] = 0xAC, .deqA_01[5] = 0xAC,	.deqA_01[6] = 0xAC,  .deqA_01[7] = 0xAC, .deqA_01[8] = 0xAC, .deqA_01[9] = 0xAC, .deqA_01[10] = 0xAC,	// BankA 0x30
			.deqA_02[0] = 0x78, .deqA_02[1] = 0x78, .deqA_02[2] = 0x78, .deqA_02[3] = 0x78, .deqA_02[4] = 0x78, .deqA_02[5] = 0x78,	.deqA_02[6] = 0x78,	 .deqA_02[7] = 0x78, .deqA_02[8] = 0x78, .deqA_02[9] = 0x78, .deqA_02[10] = 0x78,	// BankA 0x31
			.deqA_03[0] = 0x17, .deqA_03[1] = 0x17, .deqA_03[2] = 0x17, .deqA_03[3] = 0x17, .deqA_03[4] = 0x17, .deqA_03[5] = 0x17,	.deqA_03[6] = 0x17,	 .deqA_03[7] = 0x17, .deqA_03[8] = 0x17, .deqA_03[9] = 0x17, .deqA_03[10] = 0x17,	// BankA 0x32
			.deqA_04[0] = 0xC1, .deqA_04[1] = 0xC1, .deqA_04[2] = 0xC1, .deqA_04[3] = 0xC1, .deqA_04[4] = 0xC1, .deqA_04[5] = 0xC1, .deqA_04[6] = 0xC1,  .deqA_04[7] = 0xC1, .deqA_04[8] = 0xC1, .deqA_04[9] = 0xC1, .deqA_04[10] = 0xC1,	// BankA 0x33
			.deqA_05[0] = 0x40, .deqA_05[1] = 0x40, .deqA_05[2] = 0x40, .deqA_05[3] = 0x40, .deqA_05[4] = 0x40, .deqA_05[5] = 0x40, .deqA_05[6] = 0x40,  .deqA_05[7] = 0x40, .deqA_05[8] = 0x40, .deqA_05[9] = 0x40, .deqA_05[10] = 0x40,	// BankA 0x34
			.deqA_06[0] = 0x00, .deqA_06[1] = 0x00, .deqA_06[2] = 0x00, .deqA_06[3] = 0x00, .deqA_06[4] = 0x00, .deqA_06[5] = 0x00, .deqA_06[6] = 0x00,  .deqA_06[7] = 0x00, .deqA_06[8] = 0x00, .deqA_06[9] = 0x00, .deqA_06[10] = 0x00,	// BankA 0x35
			.deqA_07[0] = 0xC3, .deqA_07[1] = 0xC3, .deqA_07[2] = 0xC3, .deqA_07[3] = 0xC3, .deqA_07[4] = 0xC3, .deqA_07[5] = 0xC3, .deqA_07[6] = 0xC3,  .deqA_07[7] = 0xC3, .deqA_07[8] = 0xC3, .deqA_07[9] = 0xC3, .deqA_07[10] = 0xC3,	// BankA 0x36
			.deqA_08[0] = 0x0A, .deqA_08[1] = 0x0A, .deqA_08[2] = 0x0A, .deqA_08[3] = 0x0A, .deqA_08[4] = 0x0A, .deqA_08[5] = 0x0A, .deqA_08[6] = 0x0A,  .deqA_08[7] = 0x0A, .deqA_08[8] = 0x0A, .deqA_08[9] = 0x0A, .deqA_08[10] = 0x0A,	// BankA 0x37
			.deqA_09[0] = 0x00, .deqA_09[1] = 0x00, .deqA_09[2] = 0x00, .deqA_09[3] = 0x00, .deqA_09[4] = 0x00, .deqA_09[5] = 0x00, .deqA_09[6] = 0x00,  .deqA_09[7] = 0x00, .deqA_09[8] = 0x00, .deqA_09[9] = 0x00, .deqA_09[10] = 0x00,	// BankA 0x38
			.deqA_10[0] = 0x02, .deqA_10[1] = 0x02, .deqA_10[2] = 0x02, .deqA_10[3] = 0x02, .deqA_10[4] = 0x02, .deqA_10[5] = 0x02, .deqA_10[6] = 0x02,  .deqA_10[7] = 0x02, .deqA_10[8] = 0x02, .deqA_10[9] = 0x02, .deqA_10[10] = 0x02,	// BankA 0x39
			.deqA_11[0] = 0x00, .deqA_11[1] = 0x00, .deqA_11[2] = 0x00, .deqA_11[3] = 0x00, .deqA_11[4] = 0x00, .deqA_11[5] = 0x00, .deqA_11[6] = 0x00,  .deqA_11[7] = 0x00, .deqA_11[8] = 0x00, .deqA_11[9] = 0x00, .deqA_11[10] = 0x00,	// BankA 0x3a
			.deqA_12[0] = 0xB2, .deqA_12[1] = 0xB2, .deqA_12[2] = 0xB2, .deqA_12[3] = 0xB2, .deqA_12[4] = 0xB2, .deqA_12[5] = 0xB2, .deqA_12[6] = 0xB2,  .deqA_12[7] = 0xB2, .deqA_12[8] = 0xB2, .deqA_12[9] = 0xB2, .deqA_12[10] = 0xB2,	// BankA 0x3b
		},
		/* color */
		{
			.contrast[0] 		= 0x82, .contrast[1] 		= 0x86, .contrast[2] 		= 0x84, .contrast[3] 		= 0x81, .contrast[4] 		= 0x7f, .contrast[5] 		= 0x7e, .contrast[6] 		= 0x7a, .contrast[7] 		= 0x7a, .contrast[8] 		= 0x72, .contrast[9] 		= 0x6d, .contrast[10] 		= 0x6d,
			.h_peaking[0] 		= 0x00, .h_peaking[1] 		= 0x00, .h_peaking[2] 		= 0x00, .h_peaking[3] 		= 0x00, .h_peaking[4] 		= 0x00, .h_peaking[5] 		= 0x00, .h_peaking[6] 		= 0x00, .h_peaking[7] 		= 0x3f, .h_peaking[8] 		= 0x3f, .h_peaking[9] 		= 0x3f, .h_peaking[10] 		= 0x3f,
			.c_filter[0]		= 0x82, .c_filter[1] 		= 0x92, .c_filter[2]	 	= 0x92, .c_filter[3] 		= 0xa2, .c_filter[4] 		= 0xa2, .c_filter[5] 		= 0xa2, .c_filter[6] 		= 0xb2, .c_filter[7] 		= 0xb2, .c_filter[8] 		= 0xb2, .c_filter[9] 		= 0xb2, .c_filter[10] 		= 0xb2,
			.hue[0] 			= 0x00, .hue[1] 			= 0x00, .hue[2] 			= 0x00, .hue[3] 			= 0x00, .hue[4] 			= 0x00, .hue[5] 			= 0x00, .hue[6] 			= 0x00, .hue[7] 			= 0x00, .hue[8] 			= 0x00, .hue[9] 			= 0x00, .hue[10] 			= 0x00,
			.u_gain[0] 			= 0xe0, .u_gain[1] 			= 0x00, .u_gain[2] 			= 0x00, .u_gain[3] 			= 0x00, .u_gain[4] 			= 0x00, .u_gain[5] 			= 0x00, .u_gain[6] 			= 0x00, .u_gain[7] 			= 0x00, .u_gain[8] 			= 0x00, .u_gain[9] 			= 0x00, .u_gain[10] 		= 0x00,
			.v_gain[0] 			= 0x00, .v_gain[1] 			= 0x00, .v_gain[2] 			= 0x00, .v_gain[3] 			= 0x00, .v_gain[4] 			= 0x00, .v_gain[5] 			= 0x00, .v_gain[6] 			= 0x00, .v_gain[7] 			= 0x00, .v_gain[8] 			= 0x00, .v_gain[9] 			= 0x00, .v_gain[10] 		= 0x00,
			.u_offset[0] 		= 0xff, .u_offset[1] 		= 0x00, .u_offset[2] 		= 0x00, .u_offset[3] 		= 0x00, .u_offset[4] 		= 0x00, .u_offset[5] 		= 0x00, .u_offset[6] 		= 0x00, .u_offset[7] 		= 0x00, .u_offset[8] 		= 0x00, .u_offset[9] 		= 0x00, .u_offset[10] 		= 0x00,
			.v_offset[0] 		= 0x00, .v_offset[1] 		= 0x00, .v_offset[2] 		= 0x00, .v_offset[3] 		= 0x00, .v_offset[4] 		= 0x00, .v_offset[5] 		= 0x00, .v_offset[6] 		= 0x00, .v_offset[7] 		= 0x00, .v_offset[8] 		= 0x00, .v_offset[9] 		= 0x00, .v_offset[10] 		= 0x00,

			.black_level[0] 	= 0x86, .black_level[1] 	= 0x88, .black_level[2] 	= 0x86, .black_level[3] 	= 0x86, .black_level[4] 	= 0x88, .black_level[5] 	= 0x8a, .black_level[6] 	= 0x8c, .black_level[7] 	= 0x92, .black_level[8] 	= 0x95, .black_level[9] 	= 0x98, .black_level[10] 	= 0x98,
			.acc_ref[0]			= 0x57, .acc_ref[1]			= 0x57, .acc_ref[2]			= 0x57, .acc_ref[3]			= 0x57, .acc_ref[4]			= 0x57, .acc_ref[5]			= 0x57, .acc_ref[6]			= 0x57, .acc_ref[7]			= 0x37, .acc_ref[8]			= 0x20, .acc_ref[9]			= 0x20, .acc_ref[10]		= 0x57,
			.cti_delay[0]		= 0x80, .cti_delay[1]		= 0x80, .cti_delay[2]		= 0x80, .cti_delay[3]		= 0x80, .cti_delay[4]		= 0x80, .cti_delay[5]		= 0x80, .cti_delay[6]		= 0x80, .cti_delay[7]		= 0x80, .cti_delay[8]		= 0x80, .cti_delay[9]		= 0x80, .cti_delay[10]		= 0x80,
			.sub_saturation[0] 	= 0xa8, .sub_saturation[1] 	= 0xaa, .sub_saturation[2] 	= 0xaa, .sub_saturation[3] 	= 0xac, .sub_saturation[4] 	= 0xa8, .sub_saturation[5] 	= 0xa6, .sub_saturation[6] 	= 0x98, .sub_saturation[7] 	= 0xa0, .sub_saturation[8] 	= 0xa0, .sub_saturation[9] 	= 0x50, .sub_saturation[10] = 0x50,

			.burst_dec_a[0] 	= 0x2a, .burst_dec_a[1] 	= 0x2a, .burst_dec_a[2] 	= 0x2a, .burst_dec_a[3] 	= 0x2a, .burst_dec_a[4] 	= 0x2a, .burst_dec_a[5] 	= 0x2a, .burst_dec_a[6] 	= 0x2a, .burst_dec_a[7] 	= 0x2a, .burst_dec_a[8] 	= 0x2a, .burst_dec_a[9] 	= 0x2a, .burst_dec_a[10] 	= 0x2a,
			.burst_dec_b[0] 	= 0x00, .burst_dec_b[1] 	= 0x00, .burst_dec_b[2] 	= 0x00, .burst_dec_b[3] 	= 0x00, .burst_dec_b[4] 	= 0x00, .burst_dec_b[5] 	= 0x00, .burst_dec_b[6] 	= 0x00, .burst_dec_b[7] 	= 0x00, .burst_dec_b[8] 	= 0x00, .burst_dec_b[9] 	= 0x00, .burst_dec_b[10] 	= 0x00,
			.burst_dec_c[0] 	= 0x00, .burst_dec_c[1] 	= 0x00, .burst_dec_c[2] 	= 0x00, .burst_dec_c[3] 	= 0x00, .burst_dec_c[4] 	= 0x00, .burst_dec_c[5] 	= 0x00, .burst_dec_c[6] 	= 0x00, .burst_dec_c[7] 	= 0x00, .burst_dec_c[8] 	= 0x00, .burst_dec_c[9] 	= 0x00, .burst_dec_c[10] 	= 0x00,

			.c_option[0] 		= 0x80, .c_option[1] 		= 0x80, .c_option[2] 		= 0x80, .c_option[3] 		= 0xb0, .c_option[4] 		= 0xb0, .c_option[5] 		= 0xb0, .c_option[6] 		= 0xb0, .c_option[7] 		= 0xb0, .c_option[8] 		= 0xb0, .c_option[9] 		= 0xb0, .c_option[10] 		= 0xb0,

			.y_filter_b[0]		= 0x10, .y_filter_b[1]		= 0x10, .y_filter_b[2]		= 0x10, .y_filter_b[3]		= 0x10, .y_filter_b[4]		= 0x10, .y_filter_b[5]		= 0x10, .y_filter_b[6]		= 0x10, .y_filter_b[7]		= 0x10, .y_filter_b[8]		= 0x10, .y_filter_b[9]		= 0x10, .y_filter_b[10]		= 0x10,
			.y_filter_b_sel[0]	= 0x1e,	.y_filter_b_sel[1]	= 0x1e,	.y_filter_b_sel[2]	= 0x1e, .y_filter_b_sel[3]	= 0x1e, .y_filter_b_sel[4]	= 0x1e, .y_filter_b_sel[5]	= 0x1e, .y_filter_b_sel[6]	= 0x1e, .y_filter_b_sel[7]	= 0x1e, .y_filter_b_sel[8]	= 0x1e, .y_filter_b_sel[9]	= 0x1e, .y_filter_b_sel[10]	= 0x1e,
		},
		/* timing_a */
		{
			.h_delay_a[0] = 0x82, .h_delay_a[1] = 0x80, .h_delay_a[2] = 0x7f, .h_delay_a[3] = 0x7e, .h_delay_a[4] = 0x7e, .h_delay_a[5] = 0x7f, .h_delay_a[6] = 0x7f, .h_delay_a[7] = 0x7f, .h_delay_a[8] = 0x7f, .h_delay_a[9] = 0x7f, .h_delay_a[10] = 0x7f,
			.h_delay_b[0] = 0x10, .h_delay_b[1] = 0x10, .h_delay_b[2] = 0x10, .h_delay_b[3] = 0x10, .h_delay_b[4] = 0x10, .h_delay_b[5] = 0x10, .h_delay_b[6] = 0x10, .h_delay_b[7] = 0x10, .h_delay_b[8] = 0x10, .h_delay_b[9] = 0x10, .h_delay_b[10] = 0x10,
			.h_delay_c[0] = 0x01, .h_delay_c[1] = 0x01, .h_delay_c[2] = 0x01, .h_delay_c[3] = 0x01, .h_delay_c[4] = 0x01, .h_delay_c[5] = 0x01, .h_delay_c[6] = 0x01, .h_delay_c[7] = 0x01, .h_delay_c[8] = 0x01, .h_delay_c[9] = 0x01, .h_delay_c[10] = 0x01,
			.y_delay[0]   = 0x05, .y_delay[1]   = 0x05, .y_delay[2]   = 0x05, .y_delay[3]   = 0x05, .y_delay[4]   = 0x05, .y_delay[5] =   0x05, .y_delay[6] =   0x05, .y_delay[7] =   0x05, .y_delay[8] =   0x05, .y_delay[9] =   0x05, .y_delay[10] =   0x05,

		},
		/* clk */
		{
			.clk_adc[0] = 0x02, .clk_adc[1] = 0x02, .clk_adc[2] = 0x02, .clk_adc[3] = 0x02, .clk_adc[4] = 0x02, .clk_adc[5] = 0x02, .clk_adc[6] = 0x02, .clk_adc[7] = 0x02, .clk_adc[8] = 0x02, .clk_adc[9] = 0x02, .clk_adc[10] = 0x02,
			.clk_dec[0] = 0x40, .clk_dec[1] = 0x40, .clk_dec[2] = 0x40, .clk_dec[3] = 0x40, .clk_dec[4] = 0x40, .clk_dec[5] = 0x40, .clk_dec[6] = 0x40, .clk_dec[7] = 0x40, .clk_dec[8] = 0x40, .clk_dec[9] = 0x40, .clk_dec[10] = 0x40,
		},
		/* timing_b */
		{
	/*B9 0x96*/	.h_scaler1[0]  = 0x01, .h_scaler1[1]   = 0x01, .h_scaler1[2]   = 0x01, .h_scaler1[3]   = 0x01, .h_scaler1[4]   = 0x01, .h_scaler1[5]   = 0x01, .h_scaler1[6]   = 0x01, .h_scaler1[7]   = 0x01, .h_scaler1[8]   = 0x01, .h_scaler1[9]   = 0x01, .h_scaler1[10]   = 0x01,
	/*B9 0x97*/	.h_scaler2[0]  = 0x00, .h_scaler2[1]   = 0x00, .h_scaler2[2]   = 0x00, .h_scaler2[3]   = 0x00, .h_scaler2[4]   = 0x00, .h_scaler2[5]   = 0x00, .h_scaler2[6]   = 0x00, .h_scaler2[7]   = 0x00, .h_scaler2[8]   = 0x00, .h_scaler2[9]   = 0x00, .h_scaler2[10]   = 0x59,
	/*B9 0x98*/	.h_scaler3[0]  = 0x00, .h_scaler3[1]   = 0x00, .h_scaler3[2]   = 0x00, .h_scaler3[3]   = 0x00, .h_scaler3[4]   = 0x00, .h_scaler3[5]   = 0x00, .h_scaler3[6]   = 0x00, .h_scaler3[7]   = 0x00, .h_scaler3[8]   = 0x00, .h_scaler3[9]   = 0x00, .h_scaler3[10]   = 0x00,
	/*B9 0x99*/	.h_scaler4[0]  = 0x00, .h_scaler4[1]   = 0x00, .h_scaler4[2]   = 0x00, .h_scaler4[3]   = 0x00, .h_scaler4[4]   = 0x00, .h_scaler4[5]   = 0x00, .h_scaler4[6]   = 0x00, .h_scaler4[7]   = 0x00, .h_scaler4[8]   = 0x00, .h_scaler4[9]   = 0x00, .h_scaler4[10]   = 0x00,
	/*B9 0x9a*/	.h_scaler5[0]  = 0x00, .h_scaler5[1]   = 0x00, .h_scaler5[2]   = 0x00, .h_scaler5[3]   = 0x00, .h_scaler5[4]   = 0x00, .h_scaler5[5]   = 0x00, .h_scaler5[6]   = 0x00, .h_scaler5[7]   = 0x00, .h_scaler5[8]   = 0x00, .h_scaler5[9]   = 0x00, .h_scaler5[10]   = 0x00,
	/*B9 0x9b*/	.h_scaler6[0]  = 0x00, .h_scaler6[1]   = 0x00, .h_scaler6[2]   = 0x00, .h_scaler6[3]   = 0x00, .h_scaler6[4]   = 0x00, .h_scaler6[5]   = 0x00, .h_scaler6[6]   = 0x00, .h_scaler6[7]   = 0x00, .h_scaler6[8]   = 0x00, .h_scaler6[9]   = 0x00, .h_scaler6[10]   = 0x00,
	/*B9 0x9c*/	.h_scaler7[0]  = 0x00, .h_scaler7[1]   = 0x00, .h_scaler7[2]   = 0x00, .h_scaler7[3]   = 0x00, .h_scaler7[4]   = 0x00, .h_scaler7[5]   = 0x00, .h_scaler7[6]   = 0x00, .h_scaler7[7]   = 0x00, .h_scaler7[8]   = 0x00, .h_scaler7[9]   = 0x00, .h_scaler7[10]   = 0x00,
	/*B9 0x9d*/	.h_scaler8[0]  = 0x00, .h_scaler8[1]   = 0x00, .h_scaler8[2]   = 0x00, .h_scaler8[3]   = 0x00, .h_scaler8[4]   = 0x00, .h_scaler8[5]   = 0x00, .h_scaler8[6]   = 0x00, .h_scaler8[7]   = 0x00, .h_scaler8[8]   = 0x00, .h_scaler8[9]   = 0x00, .h_scaler8[10]   = 0x00,
	/*B9 0x9e*/	.h_scaler9[0]  = 0x00, .h_scaler9[1]   = 0x00, .h_scaler9[2]   = 0x00, .h_scaler9[3]   = 0x00, .h_scaler9[4]   = 0x00, .h_scaler9[5]   = 0x00, .h_scaler9[6]   = 0x00, .h_scaler9[7]   = 0x00, .h_scaler9[8]   = 0x00, .h_scaler9[9]   = 0x00, .h_scaler9[10]   = 0x00,


	/*B9 0x40*/	.pn_auto[0]    	= 0x00, .pn_auto[1]		= 0x00, .pn_auto[2]    	= 0x00, .pn_auto[3]    	= 0x00, .pn_auto[4]    	= 0x00, .pn_auto[5]    	= 0x00, .pn_auto[6]		= 0x00, .pn_auto[7]    	= 0x00, .pn_auto[8]    	= 0x00, .pn_auto[9]    	= 0x00, .pn_auto[10]    	= 0x00,

	/*B5 0x90*/	.comb_mode[0]   = 0x05, .comb_mode[1]	= 0x05, .comb_mode[2]   = 0x05, .comb_mode[3]   = 0x05, .comb_mode[4]  	= 0x05, .comb_mode[5]   = 0x05, .comb_mode[6]	= 0x05, .comb_mode[7]   = 0x05, .comb_mode[8]   = 0x05, .comb_mode[9]  	= 0x05, .comb_mode[10]   = 0x05,
	/*B9 0xb9*/	.h_pll_op_a[0]  = 0x72, .h_pll_op_a[1]  = 0x72, .h_pll_op_a[2]  = 0x72, .h_pll_op_a[3]  = 0x72, .h_pll_op_a[4]  = 0x72, .h_pll_op_a[5]  = 0x72, .h_pll_op_a[6]  = 0x72, .h_pll_op_a[7]  = 0x72, .h_pll_op_a[8]  = 0x72, .h_pll_op_a[9]  = 0x72, .h_pll_op_a[10]  = 0x72,
	/*B9 0x57*/	.mem_path[0]	= 0x10, .mem_path[1]	= 0x10, .mem_path[2]	= 0x10, .mem_path[3]	= 0x10, .mem_path[4]	= 0x10, .mem_path[5]	= 0x10, .mem_path[6]	= 0x10, .mem_path[7]	= 0x10, .mem_path[8]	= 0x10, .mem_path[9]	= 0x10, .mem_path[10]	 = 0x10,
			.fsc_lock_speed[0] = 0xdc, .fsc_lock_speed[1] = 0xdc, .fsc_lock_speed[2] = 0xdc, .fsc_lock_speed[3] = 0xdc, .fsc_lock_speed[4] = 0xdc, .fsc_lock_speed[5] = 0xdc, .fsc_lock_speed[6] = 0xdc, .fsc_lock_speed[7] = 0xdc, .fsc_lock_speed[8] = 0xdc, .fsc_lock_speed[9] = 0xdc, .fsc_lock_speed[10] = 0xdc,

	/*B0 0x81*/	.format_set1[0] = 0x0b, .format_set1[1] = 0x0b, .format_set1[2] = 0x0b, .format_set1[3] = 0x0b, .format_set1[4] = 0x0b, .format_set1[5] = 0x0b, .format_set1[6] = 0x0b, .format_set1[7] = 0x0b, .format_set1[8] = 0x0b, .format_set1[9] = 0x0b, .format_set1[10] = 0x0b,
	/*B0 0x85*/	.format_set2[0] = 0x03, .format_set2[1] = 0x03, .format_set2[2] = 0x03, .format_set2[3] = 0x03, .format_set2[4] = 0x03, .format_set2[5] = 0x03, .format_set2[6] = 0x03, .format_set2[7] = 0x03, .format_set2[8] = 0x03, .format_set2[9] = 0x03, .format_set2[10] = 0x03,

	/*B0 0x64*/ .v_delay[0]     = 0x20, .v_delay[1]     = 0x20, .v_delay[2]     = 0x20, .v_delay[3]     = 0x20, .v_delay[4]     = 0x20, .v_delay[5]     = 0x20, .v_delay[6]     = 0x20, .v_delay[7]     = 0x20, .v_delay[8]     = 0x20, .v_delay[9]     = 0x20, .v_delay[10]     = 0x20,
		},
	},
#endif

	[ TVI_HD_B_30P_EX ] = /* o */
	{
/* base */
		{
			.eq_bypass[0] 	= 0x22, .eq_bypass[1] 	= 0x22, .eq_bypass[2] 	= 0x22, .eq_bypass[3] 	= 0x22, .eq_bypass[4] 	= 0x22, .eq_bypass[5] 	= 0x22, .eq_bypass[6] 	= 0x22, .eq_bypass[7] 	= 0x22, .eq_bypass[8] 	= 0x22, .eq_bypass[9] 	= 0x22, .eq_bypass[10] 	 = 0x22,  // Bank5 0x30
			.eq_band_sel[0] = 0x77, .eq_band_sel[1] = 0x67, .eq_band_sel[2] = 0x57, .eq_band_sel[3] = 0x57, .eq_band_sel[4] = 0x57, .eq_band_sel[5] = 0x47, .eq_band_sel[6] = 0x37, .eq_band_sel[7] = 0x27, .eq_band_sel[8] = 0x17, .eq_band_sel[9] = 0x17, .eq_band_sel[10] = 0x07, // BankA 0x31
			.eq_gain_sel[0] = 0x78, .eq_gain_sel[1] = 0x78, .eq_gain_sel[2] = 0x78, .eq_gain_sel[3] = 0x7f, .eq_gain_sel[4] = 0x7f, .eq_gain_sel[5] = 0x7f, .eq_gain_sel[6] = 0x7f, .eq_gain_sel[7] = 0x7f, .eq_gain_sel[8] = 0x7f, .eq_gain_sel[9] = 0x7f, .eq_gain_sel[10] = 0x7f, // BankA 0x32
			.deq_a_on[0] 	= 0x00, .deq_a_on[1] 	= 0x01, .deq_a_on[2] 	= 0x01, .deq_a_on[3] 	= 0x01, .deq_a_on[4] 	= 0x01, .deq_a_on[5] 	= 0x01, .deq_a_on[6] 	= 0x01, .deq_a_on[7] 	= 0x01, .deq_a_on[8] 	= 0x01, .deq_a_on[9] 	= 0x01, .deq_a_on[10] 	 = 0x01, // BankA 0x33
			.deq_a_sel[0] 	= 0x00, .deq_a_sel[1] 	= 0x91, .deq_a_sel[2] 	= 0x92, .deq_a_sel[3] 	= 0x93, .deq_a_sel[4] 	= 0x93, .deq_a_sel[5] 	= 0x93, .deq_a_sel[6] 	= 0x93, .deq_a_sel[7] 	= 0x93, .deq_a_sel[8] 	= 0x93, .deq_a_sel[9] 	= 0x93, .deq_a_sel[10] 	 = 0x92, // BankA 0x34
			.deq_b_sel[0] 	= 0x00, .deq_b_sel[1] 	= 0x00, .deq_b_sel[2] 	= 0x00, .deq_b_sel[3] 	= 0x00, .deq_b_sel[4] 	= 0x00, .deq_b_sel[5] 	= 0x00, .deq_b_sel[6] 	= 0x00, .deq_b_sel[7] 	= 0x00, .deq_b_sel[8] 	= 0x00, .deq_b_sel[9] 	= 0x00, .deq_b_sel[10] 	 = 0x00, // BankA 0x35
		},
		/* coeff */
		{
			.deqA_01[0] = 0xAC, .deqA_01[1] = 0xAC, .deqA_01[2] = 0xAC, .deqA_01[3] = 0xAC, .deqA_01[4] = 0xAC, .deqA_01[5] = 0xAC,	.deqA_01[6] = 0xAC,  .deqA_01[7] = 0xAC, .deqA_01[8] = 0xAC, .deqA_01[9] = 0xAC, .deqA_01[10] = 0xAC,	// BankA 0x30
			.deqA_02[0] = 0x78, .deqA_02[1] = 0x78, .deqA_02[2] = 0x78, .deqA_02[3] = 0x78, .deqA_02[4] = 0x78, .deqA_02[5] = 0x78,	.deqA_02[6] = 0x78,	 .deqA_02[7] = 0x78, .deqA_02[8] = 0x78, .deqA_02[9] = 0x78, .deqA_02[10] = 0x78,	// BankA 0x31
			.deqA_03[0] = 0x17, .deqA_03[1] = 0x17, .deqA_03[2] = 0x17, .deqA_03[3] = 0x17, .deqA_03[4] = 0x17, .deqA_03[5] = 0x17,	.deqA_03[6] = 0x17,	 .deqA_03[7] = 0x17, .deqA_03[8] = 0x17, .deqA_03[9] = 0x17, .deqA_03[10] = 0x17,	// BankA 0x32
			.deqA_04[0] = 0xC1, .deqA_04[1] = 0xC1, .deqA_04[2] = 0xC1, .deqA_04[3] = 0xC1, .deqA_04[4] = 0xC1, .deqA_04[5] = 0xC1, .deqA_04[6] = 0xC1,  .deqA_04[7] = 0xC1, .deqA_04[8] = 0xC1, .deqA_04[9] = 0xC1, .deqA_04[10] = 0xC1,	// BankA 0x33
			.deqA_05[0] = 0x40, .deqA_05[1] = 0x40, .deqA_05[2] = 0x40, .deqA_05[3] = 0x40, .deqA_05[4] = 0x40, .deqA_05[5] = 0x40, .deqA_05[6] = 0x40,  .deqA_05[7] = 0x40, .deqA_05[8] = 0x40, .deqA_05[9] = 0x40, .deqA_05[10] = 0x40,	// BankA 0x34
			.deqA_06[0] = 0x00, .deqA_06[1] = 0x00, .deqA_06[2] = 0x00, .deqA_06[3] = 0x00, .deqA_06[4] = 0x00, .deqA_06[5] = 0x00, .deqA_06[6] = 0x00,  .deqA_06[7] = 0x00, .deqA_06[8] = 0x00, .deqA_06[9] = 0x00, .deqA_06[10] = 0x00,	// BankA 0x35
			.deqA_07[0] = 0xC3, .deqA_07[1] = 0xC3, .deqA_07[2] = 0xC3, .deqA_07[3] = 0xC3, .deqA_07[4] = 0xC3, .deqA_07[5] = 0xC3, .deqA_07[6] = 0xC3,  .deqA_07[7] = 0xC3, .deqA_07[8] = 0xC3, .deqA_07[9] = 0xC3, .deqA_07[10] = 0xC3,	// BankA 0x36
			.deqA_08[0] = 0x0A, .deqA_08[1] = 0x0A, .deqA_08[2] = 0x0A, .deqA_08[3] = 0x0A, .deqA_08[4] = 0x0A, .deqA_08[5] = 0x0A, .deqA_08[6] = 0x0A,  .deqA_08[7] = 0x0A, .deqA_08[8] = 0x0A, .deqA_08[9] = 0x0A, .deqA_08[10] = 0x0A,	// BankA 0x37
			.deqA_09[0] = 0x00, .deqA_09[1] = 0x00, .deqA_09[2] = 0x00, .deqA_09[3] = 0x00, .deqA_09[4] = 0x00, .deqA_09[5] = 0x00, .deqA_09[6] = 0x00,  .deqA_09[7] = 0x00, .deqA_09[8] = 0x00, .deqA_09[9] = 0x00, .deqA_09[10] = 0x00,	// BankA 0x38
			.deqA_10[0] = 0x02, .deqA_10[1] = 0x02, .deqA_10[2] = 0x02, .deqA_10[3] = 0x02, .deqA_10[4] = 0x02, .deqA_10[5] = 0x02, .deqA_10[6] = 0x02,  .deqA_10[7] = 0x02, .deqA_10[8] = 0x02, .deqA_10[9] = 0x02, .deqA_10[10] = 0x02,	// BankA 0x39
			.deqA_11[0] = 0x00, .deqA_11[1] = 0x00, .deqA_11[2] = 0x00, .deqA_11[3] = 0x00, .deqA_11[4] = 0x00, .deqA_11[5] = 0x00, .deqA_11[6] = 0x00,  .deqA_11[7] = 0x00, .deqA_11[8] = 0x00, .deqA_11[9] = 0x00, .deqA_11[10] = 0x00,	// BankA 0x3a
			.deqA_12[0] = 0xB2, .deqA_12[1] = 0xB2, .deqA_12[2] = 0xB2, .deqA_12[3] = 0xB2, .deqA_12[4] = 0xB2, .deqA_12[5] = 0xB2, .deqA_12[6] = 0xB2,  .deqA_12[7] = 0xB2, .deqA_12[8] = 0xB2, .deqA_12[9] = 0xB2, .deqA_12[10] = 0xB2,	// BankA 0x3b
		},
		/* color */
		{
			.contrast[0] 		= 0x82, .contrast[1] 		= 0x86, .contrast[2] 		= 0x84, .contrast[3] 		= 0x81, .contrast[4] 		= 0x7f, .contrast[5] 		= 0x7e, .contrast[6] 		= 0x7a, .contrast[7] 		= 0x7a, .contrast[8] 		= 0x72, .contrast[9] 		= 0x6d, .contrast[10] 			= 0x6d,
			.h_peaking[0] 		= 0x00, .h_peaking[1] 		= 0x00, .h_peaking[2] 		= 0x00, .h_peaking[3] 		= 0x00, .h_peaking[4] 		= 0x00, .h_peaking[5] 		= 0x00, .h_peaking[6] 		= 0x00, .h_peaking[7] 		= 0x3f, .h_peaking[8] 		= 0x3f, .h_peaking[9] 		= 0x3f, .h_peaking[10] 			= 0x3f,
			.c_filter[0]		= 0x82, .c_filter[1] 		= 0x92, .c_filter[2]	 	= 0x92, .c_filter[3] 		= 0xa2, .c_filter[4] 		= 0xa2, .c_filter[5] 		= 0xa2, .c_filter[6] 		= 0xb2, .c_filter[7] 		= 0xb2, .c_filter[8] 		= 0xb2, .c_filter[9] 		= 0xb2, .c_filter[10] 			= 0xb2,
			.hue[0] 			= 0x00, .hue[1] 			= 0x00, .hue[2] 			= 0x00, .hue[3] 			= 0x00, .hue[4] 			= 0x00, .hue[5] 			= 0x00, .hue[6] 			= 0x00, .hue[7] 			= 0x00, .hue[8] 			= 0x00, .hue[9] 			= 0x00, .hue[10] 				= 0x00,
			.u_gain[0] 			= 0xe0, .u_gain[1] 			= 0xe0, .u_gain[2] 			= 0xe0, .u_gain[3] 			= 0xe0, .u_gain[4] 			= 0xe0, .u_gain[5] 			= 0xe0, .u_gain[6] 			= 0xe0, .u_gain[7] 			= 0xe0, .u_gain[8] 			= 0xe0, .u_gain[9] 			= 0xe0, .u_gain[10] 			= 0xe0,
			.v_gain[0] 			= 0x00, .v_gain[1] 			= 0x00, .v_gain[2] 			= 0x00, .v_gain[3] 			= 0x00, .v_gain[4] 			= 0x00, .v_gain[5] 			= 0x00, .v_gain[6] 			= 0x00, .v_gain[7] 			= 0x00, .v_gain[8] 			= 0x00, .v_gain[9] 			= 0x00, .v_gain[10] 			= 0x00,
			.u_offset[0] 		= 0xff, .u_offset[1] 		= 0xff, .u_offset[2] 		= 0xff, .u_offset[3] 		= 0xff, .u_offset[4] 		= 0xff, .u_offset[5] 		= 0xff, .u_offset[6] 		= 0xff, .u_offset[7] 		= 0xff, .u_offset[8] 		= 0xff, .u_offset[9] 		= 0xff, .u_offset[10] 			= 0xff,
			.v_offset[0] 		= 0x00, .v_offset[1] 		= 0x00, .v_offset[2] 		= 0x00, .v_offset[3] 		= 0x00, .v_offset[4] 		= 0x00, .v_offset[5] 		= 0x00, .v_offset[6] 		= 0x00, .v_offset[7] 		= 0x00, .v_offset[8] 		= 0x00, .v_offset[9] 		= 0x00, .v_offset[10] 			= 0x00,

			.black_level[0] 	= 0x86, .black_level[1] 	= 0x88, .black_level[2] 	= 0x86, .black_level[3] 	= 0x86, .black_level[4] 	= 0x88, .black_level[5] 	= 0x8a, .black_level[6] 	= 0x8c, .black_level[7] 	= 0x92, .black_level[8] 	= 0x95, .black_level[9] 	= 0x98, .black_level[10] 	= 0x98,
			.acc_ref[0]			= 0x57, .acc_ref[1]			= 0x57, .acc_ref[2]			= 0x57, .acc_ref[3]			= 0x57, .acc_ref[4]			= 0x57, .acc_ref[5]			= 0x57, .acc_ref[6]			= 0x57, .acc_ref[7]			= 0x37, .acc_ref[8]			= 0x20, .acc_ref[9]			= 0x20, .acc_ref[10]			= 0x57,
			.cti_delay[0]		= 0x80, .cti_delay[1]		= 0x80, .cti_delay[2]		= 0x80, .cti_delay[3]		= 0x80, .cti_delay[4]		= 0x80, .cti_delay[5]		= 0x80, .cti_delay[6]		= 0x80, .cti_delay[7]		= 0x80, .cti_delay[8]		= 0x80, .cti_delay[9]		= 0x80, .cti_delay[10]			= 0x80,
			.sub_saturation[0] 	= 0xa8, .sub_saturation[1] 	= 0xaa, .sub_saturation[2] 	= 0xaa, .sub_saturation[3] 	= 0xac, .sub_saturation[4] 	= 0xa8, .sub_saturation[5] 	= 0xa6, .sub_saturation[6] 	= 0x98, .sub_saturation[7] 	= 0xa0, .sub_saturation[8] 	= 0xa0, .sub_saturation[9] 	= 0x50, .sub_saturation[10] = 0x50,

			.burst_dec_a[0] 	= 0x2a, .burst_dec_a[1] 	= 0x2a, .burst_dec_a[2] 	= 0x2a, .burst_dec_a[3] 	= 0x2a, .burst_dec_a[4] 	= 0x2a, .burst_dec_a[5] 	= 0x2a, .burst_dec_a[6] 	= 0x2a, .burst_dec_a[7] 	= 0x2a, .burst_dec_a[8] 	= 0x2a, .burst_dec_a[9] 	= 0x2a, .burst_dec_a[10] 	= 0x2a,
			.burst_dec_b[0] 	= 0x00, .burst_dec_b[1] 	= 0x00, .burst_dec_b[2] 	= 0x00, .burst_dec_b[3] 	= 0x00, .burst_dec_b[4] 	= 0x00, .burst_dec_b[5] 	= 0x00, .burst_dec_b[6] 	= 0x00, .burst_dec_b[7] 	= 0x00, .burst_dec_b[8] 	= 0x00, .burst_dec_b[9] 	= 0x00, .burst_dec_b[10] 	= 0x00,
			.burst_dec_c[0] 	= 0x00, .burst_dec_c[1] 	= 0x00, .burst_dec_c[2] 	= 0x00, .burst_dec_c[3] 	= 0x00, .burst_dec_c[4] 	= 0x00, .burst_dec_c[5] 	= 0x00, .burst_dec_c[6] 	= 0x00, .burst_dec_c[7] 	= 0x00, .burst_dec_c[8] 	= 0x00, .burst_dec_c[9] 	= 0x00, .burst_dec_c[10] 	= 0x00,

			.c_option[0] 		= 0x80, .c_option[1] 		= 0x80, .c_option[2] 		= 0x80, .c_option[3] 		= 0xb0, .c_option[4] 		= 0xb0, .c_option[5] 		= 0xb0, .c_option[6] 		= 0xb0, .c_option[7] 		= 0xb0, .c_option[8] 		= 0xb0, .c_option[9] 		= 0xb0, .c_option[10] 			= 0xb0,

			.y_filter_b[0]		= 0x10, .y_filter_b[1]		= 0x10, .y_filter_b[2]		= 0x10, .y_filter_b[3]		= 0x10, .y_filter_b[4]		= 0x10, .y_filter_b[5]		= 0x10, .y_filter_b[6]		= 0x10, .y_filter_b[7]		= 0x10, .y_filter_b[8]		= 0x10, .y_filter_b[9]		= 0x10, .y_filter_b[10]			= 0x10,
			.y_filter_b_sel[0]	= 0x1e,	.y_filter_b_sel[1]	= 0x1e,	.y_filter_b_sel[2]	= 0x1e, .y_filter_b_sel[3]	= 0x1e, .y_filter_b_sel[4]	= 0x1e, .y_filter_b_sel[5]	= 0x1e, .y_filter_b_sel[6]	= 0x1e, .y_filter_b_sel[7]	= 0x1e, .y_filter_b_sel[8]	= 0x1e, .y_filter_b_sel[9]	= 0x1e, .y_filter_b_sel[10]	= 0x1e,
		},
		/* timing_a */
		{
			.h_delay_a[0] = 0x80, .h_delay_a[1] = 0x7e, .h_delay_a[2] = 0x7d, .h_delay_a[3] = 0x7c, .h_delay_a[4] = 0x7c, .h_delay_a[5] = 0x7d, .h_delay_a[6] = 0x7d, .h_delay_a[7] = 0x7d, .h_delay_a[8] = 0x7d, .h_delay_a[9] = 0x7d, .h_delay_a[10] = 0x7d,
			.h_delay_b[0] = 0x10, .h_delay_b[1] = 0x10, .h_delay_b[2] = 0x10, .h_delay_b[3] = 0x10, .h_delay_b[4] = 0x10, .h_delay_b[5] = 0x10, .h_delay_b[6] = 0x10, .h_delay_b[7] = 0x10, .h_delay_b[8] = 0x10, .h_delay_b[9] = 0x10, .h_delay_b[10] = 0x10,
			.h_delay_c[0] = 0x02, .h_delay_c[1] = 0x02, .h_delay_c[2] = 0x02, .h_delay_c[3] = 0x02, .h_delay_c[4] = 0x02, .h_delay_c[5] = 0x02, .h_delay_c[6] = 0x02, .h_delay_c[7] = 0x02, .h_delay_c[8] = 0x02, .h_delay_c[9] = 0x02, .h_delay_c[10] = 0x02,
			.y_delay[0]   = 0x05, .y_delay[1]   = 0x05, .y_delay[2]   = 0x05, .y_delay[3]   = 0x05, .y_delay[4]   = 0x05, .y_delay[5] =   0x05, .y_delay[6] =   0x05, .y_delay[7] =   0x05, .y_delay[8] =   0x05, .y_delay[9] =   0x05, .y_delay[10] =   0x05,

		},
		/* clk */
		{
			.clk_adc[0] = 0x02, .clk_adc[1] = 0x02, .clk_adc[2] = 0x02, .clk_adc[3] = 0x02, .clk_adc[4] = 0x02, .clk_adc[5] = 0x02, .clk_adc[6] = 0x02, .clk_adc[7] = 0x02, .clk_adc[8] = 0x02, .clk_adc[9] = 0x02, .clk_adc[10] = 0x02,
			.clk_dec[0] = 0x40, .clk_dec[1] = 0x40, .clk_dec[2] = 0x40, .clk_dec[3] = 0x40, .clk_dec[4] = 0x40, .clk_dec[5] = 0x40, .clk_dec[6] = 0x40, .clk_dec[7] = 0x40, .clk_dec[8] = 0x40, .clk_dec[9] = 0x40, .clk_dec[10] = 0x40,
		},
		/* timing_b */
		{
	/*B9 0x96*/	.h_scaler1[0]  = 0x01, .h_scaler1[1]   = 0x01, .h_scaler1[2]   = 0x01, .h_scaler1[3]   = 0x01, .h_scaler1[4]   = 0x01, .h_scaler1[5]   = 0x01, .h_scaler1[6]   = 0x01, .h_scaler1[7]   = 0x01, .h_scaler1[8]   = 0x01, .h_scaler1[9]   = 0x01, .h_scaler1[10]   = 0x01,
	/*B9 0x97*/	.h_scaler2[0]  = 0x00, .h_scaler2[1]   = 0x00, .h_scaler2[2]   = 0x00, .h_scaler2[3]   = 0x00, .h_scaler2[4]   = 0x00, .h_scaler2[5]   = 0x00, .h_scaler2[6]   = 0x00, .h_scaler2[7]   = 0x00, .h_scaler2[8]   = 0x00, .h_scaler2[9]   = 0x00, .h_scaler2[10]   = 0x00,
	/*B9 0x98*/	.h_scaler3[0]  = 0x00, .h_scaler3[1]   = 0x00, .h_scaler3[2]   = 0x00, .h_scaler3[3]   = 0x00, .h_scaler3[4]   = 0x00, .h_scaler3[5]   = 0x00, .h_scaler3[6]   = 0x00, .h_scaler3[7]   = 0x00, .h_scaler3[8]   = 0x00, .h_scaler3[9]   = 0x00, .h_scaler3[10]   = 0x00,
	/*B9 0x99*/	.h_scaler4[0]  = 0x00, .h_scaler4[1]   = 0x00, .h_scaler4[2]   = 0x00, .h_scaler4[3]   = 0x00, .h_scaler4[4]   = 0x00, .h_scaler4[5]   = 0x00, .h_scaler4[6]   = 0x00, .h_scaler4[7]   = 0x00, .h_scaler4[8]   = 0x00, .h_scaler4[9]   = 0x00, .h_scaler4[10]   = 0x00,
	/*B9 0x9a*/	.h_scaler5[0]  = 0x00, .h_scaler5[1]   = 0x00, .h_scaler5[2]   = 0x00, .h_scaler5[3]   = 0x00, .h_scaler5[4]   = 0x00, .h_scaler5[5]   = 0x00, .h_scaler5[6]   = 0x00, .h_scaler5[7]   = 0x00, .h_scaler5[8]   = 0x00, .h_scaler5[9]   = 0x00, .h_scaler5[10]   = 0x00,
	/*B9 0x9b*/	.h_scaler6[0]  = 0x00, .h_scaler6[1]   = 0x00, .h_scaler6[2]   = 0x00, .h_scaler6[3]   = 0x00, .h_scaler6[4]   = 0x00, .h_scaler6[5]   = 0x00, .h_scaler6[6]   = 0x00, .h_scaler6[7]   = 0x00, .h_scaler6[8]   = 0x00, .h_scaler6[9]   = 0x00, .h_scaler6[10]   = 0x00,
	/*B9 0x9c*/	.h_scaler7[0]  = 0x00, .h_scaler7[1]   = 0x00, .h_scaler7[2]   = 0x00, .h_scaler7[3]   = 0x00, .h_scaler7[4]   = 0x00, .h_scaler7[5]   = 0x00, .h_scaler7[6]   = 0x00, .h_scaler7[7]   = 0x00, .h_scaler7[8]   = 0x00, .h_scaler7[9]   = 0x00, .h_scaler7[10]   = 0x00,
	/*B9 0x9d*/	.h_scaler8[0]  = 0x00, .h_scaler8[1]   = 0x00, .h_scaler8[2]   = 0x00, .h_scaler8[3]   = 0x00, .h_scaler8[4]   = 0x00, .h_scaler8[5]   = 0x00, .h_scaler8[6]   = 0x00, .h_scaler8[7]   = 0x00, .h_scaler8[8]   = 0x00, .h_scaler8[9]   = 0x00, .h_scaler8[10]   = 0x00,
	/*B9 0x9e*/	.h_scaler9[0]  = 0x00, .h_scaler9[1]   = 0x00, .h_scaler9[2]   = 0x00, .h_scaler9[3]   = 0x00, .h_scaler9[4]   = 0x00, .h_scaler9[5]   = 0x00, .h_scaler9[6]   = 0x00, .h_scaler9[7]   = 0x00, .h_scaler9[8]   = 0x00, .h_scaler9[9]   = 0x00, .h_scaler9[10]   = 0x00,


	/*B9 0x40*/	.pn_auto[0]    	= 0x00, .pn_auto[1]		= 0x00, .pn_auto[2]    	= 0x00, .pn_auto[3]    	= 0x00, .pn_auto[4]    	= 0x00, .pn_auto[5]    	= 0x00, .pn_auto[6]		= 0x00, .pn_auto[7]    	= 0x00, .pn_auto[8]    	= 0x00, .pn_auto[9]    	= 0x00, .pn_auto[10]    	= 0x00,

	/*B5 0x90*/	.comb_mode[0]   = 0x05, .comb_mode[1]	= 0x05, .comb_mode[2]   = 0x05, .comb_mode[3]   = 0x05, .comb_mode[4]  	= 0x05, .comb_mode[5]   = 0x05, .comb_mode[6]	= 0x05, .comb_mode[7]   = 0x05, .comb_mode[8]   = 0x05, .comb_mode[9]  	= 0x05, .comb_mode[10]   = 0x05,
	/*B9 0xb9*/	.h_pll_op_a[0]  = 0x72, .h_pll_op_a[1]  = 0x72, .h_pll_op_a[2]  = 0x72, .h_pll_op_a[3]  = 0x72, .h_pll_op_a[4]  = 0x72, .h_pll_op_a[5]  = 0x72, .h_pll_op_a[6]  = 0x72, .h_pll_op_a[7]  = 0x72, .h_pll_op_a[8]  = 0x72, .h_pll_op_a[9]  = 0x72, .h_pll_op_a[10]  = 0x72,
	/*B9 0x57*/	.mem_path[0]	= 0x10, .mem_path[1]	= 0x10, .mem_path[2]	= 0x10, .mem_path[3]	= 0x10, .mem_path[4]	= 0x10, .mem_path[5]	= 0x10, .mem_path[6]	= 0x10, .mem_path[7]	= 0x10, .mem_path[8]	= 0x10, .mem_path[9]	= 0x10, .mem_path[10]	 = 0x10,
			.fsc_lock_speed[0] = 0xdc, .fsc_lock_speed[1] = 0xdc, .fsc_lock_speed[2] = 0xdc, .fsc_lock_speed[3] = 0xdc, .fsc_lock_speed[4] = 0xdc, .fsc_lock_speed[5] = 0xdc, .fsc_lock_speed[6] = 0xdc, .fsc_lock_speed[7] = 0xdc, .fsc_lock_speed[8] = 0xdc, .fsc_lock_speed[9] = 0xdc, .fsc_lock_speed[10] = 0xdc,

	/*B0 0x81*/	.format_set1[0] = 0x0A, .format_set1[1] = 0x0A, .format_set1[2] = 0x0A, .format_set1[3] = 0x0A, .format_set1[4] = 0x0A, .format_set1[5] = 0x0A, .format_set1[6] = 0x0A, .format_set1[7] = 0x0A, .format_set1[8] = 0x0A, .format_set1[9] = 0x0A, .format_set1[10] = 0x0A,
	/*B0 0x85*/	.format_set2[0] = 0x03, .format_set2[1] = 0x03, .format_set2[2] = 0x03, .format_set2[3] = 0x03, .format_set2[4] = 0x03, .format_set2[5] = 0x03, .format_set2[6] = 0x03, .format_set2[7] = 0x03, .format_set2[8] = 0x03, .format_set2[9] = 0x03, .format_set2[10] = 0x03,

	/*B0 0x64*/ .v_delay[0]     = 0x20, .v_delay[1]     = 0x20, .v_delay[2]     = 0x20, .v_delay[3]     = 0x20, .v_delay[4]     = 0x20, .v_delay[5]     = 0x20, .v_delay[6]     = 0x20, .v_delay[7]     = 0x20, .v_delay[8]     = 0x20, .v_delay[9]     = 0x20, .v_delay[10]     = 0x20,
		},
	},
	[ AHD20_SD_H960_NT ] = { /* o */
	/* base */
		{
			.eq_bypass[0] 	= 0x22,    // Bank5 0x30
			.eq_band_sel[0] = 0x77,    // BankA 0x31
			.eq_gain_sel[0] = 0x78,    // BankA 0x32
			.deq_a_on[0] 	= 0x00,    // BankA 0x33
			.deq_a_sel[0] 	= 0x00,    // BankA 0x34
			.deq_b_sel[0] 	= 0x00,    // BankA 0x35
		},
		/* coeff */
		{
			.deqA_01[0] = 0xAC,	// BankA 0x30
			.deqA_02[0] = 0x78,	// BankA 0x31
			.deqA_03[0] = 0x17,	// BankA 0x32
			.deqA_04[0] = 0xC1, // BankA 0x33
			.deqA_05[0] = 0x40, // BankA 0x34
			.deqA_06[0] = 0x00, // BankA 0x35
			.deqA_07[0] = 0xC3, // BankA 0x36
			.deqA_08[0] = 0x0A, // BankA 0x37
			.deqA_09[0] = 0x00, // BankA 0x38
			.deqA_10[0] = 0x02, // BankA 0x39
			.deqA_11[0] = 0x00, // BankA 0x3a
			.deqA_12[0] = 0xB2, // BankA 0x3b
		},
		/* color */
		{
			.contrast[0] 		= 0x90,
			.h_peaking[0] 		= 0x08,
			.c_filter[0]		= 0x82,

			.hue[0] 			= 0x00,
			.u_gain[0] 			= 0x00,
			.v_gain[0] 			= 0x00,
			.u_offset[0] 		= 0x00,
			.v_offset[0] 		= 0x00,

			.black_level[0] 	= 0x90,
			.acc_ref[0]			= 0x57,
			.cti_delay[0]		= 0x80,
			.sub_saturation[0] 	= 0xc0,

			.burst_dec_a[0] 	= 0x2a,
			.burst_dec_b[0] 	= 0x00,
			.burst_dec_c[0] 	= 0x30,

			.c_option[0] 		= 0x80,

			.y_filter_b[0]		= 0x10,
			.y_filter_b_sel[0]	= 0x1e,
		},
		/* timing_a */
		{
			.h_delay_a[0] = 0x80,
			.h_delay_b[0] = 0x10,
			.h_delay_c[0] = 0x04,
			.y_delay[0]   = 0x27,

		},
		/* clk */
		{
			.clk_adc[0] = 0x06,
			.clk_dec[0] = 0xa6,
		},
		/* timing_b */
		{
	/*B9 0x96*/	.h_scaler1[0]  = 0x10,
	/*B9 0x97*/	.h_scaler2[0]  = 0x10,
	/*B9 0x98*/	.h_scaler3[0]  = 0x00,
	/*B9 0x99*/	.h_scaler4[0]  = 0x00,
	/*B9 0x9a*/	.h_scaler5[0]  = 0x00,
	/*B9 0x9b*/	.h_scaler6[0]  = 0x00,
	/*B9 0x9c*/	.h_scaler7[0]  = 0x00,
	/*B9 0x9d*/	.h_scaler8[0]  = 0x00,
	/*B9 0x9e*/	.h_scaler9[0]  = 0x00,


	/*B9 0x40*/	.pn_auto[0]    	= 0x60,

	/*B5 0x90*/	.comb_mode[0]      = 0x01,
	/*B9 0xb9*/	.h_pll_op_a[0]     = 0x72,
	/*B9 0x57*/	.mem_path[0]	   = 0x00,
				.fsc_lock_speed[0] = 0xdc,

	/*B0 0x81*/	.format_set1[0] = 0x00,
	/*B0 0x85*/	.format_set2[0] = 0x00,

	/*B0 0x64*/ .v_delay[0]     = 0xc0,
		},
	},

	[ AHD20_SD_H960_PAL ] = { /* o */
	/* base */
		{
			.eq_bypass[0] 	= 0x22,    // Bank5 0x30
			.eq_band_sel[0] = 0x77,    // BankA 0x31
			.eq_gain_sel[0] = 0x78,    // BankA 0x32
			.deq_a_on[0] 	= 0x00,    // BankA 0x33
			.deq_a_sel[0] 	= 0x00,    // BankA 0x34
			.deq_b_sel[0] 	= 0x00,    // BankA 0x35
		},
		/* coeff */
		{
			.deqA_01[0] = 0xAC,	// BankA 0x30
			.deqA_02[0] = 0x78,	// BankA 0x31
			.deqA_03[0] = 0x17,	// BankA 0x32
			.deqA_04[0] = 0xC1, // BankA 0x33
			.deqA_05[0] = 0x40, // BankA 0x34
			.deqA_06[0] = 0x00, // BankA 0x35
			.deqA_07[0] = 0xC3, // BankA 0x36
			.deqA_08[0] = 0x0A, // BankA 0x37
			.deqA_09[0] = 0x00, // BankA 0x38
			.deqA_10[0] = 0x02, // BankA 0x39
			.deqA_11[0] = 0x00, // BankA 0x3a
			.deqA_12[0] = 0xB2, // BankA 0x3b
		},
		/* color */
		{
			.contrast[0] 		= 0x90,
			.h_peaking[0] 		= 0x08,
			.c_filter[0]		= 0x82,

			.hue[0] 			= 0x00,
			.u_gain[0] 			= 0x00,
			.v_gain[0] 			= 0x00,
			.u_offset[0] 		= 0x00,
			.v_offset[0] 		= 0x00,

			.black_level[0] 	= 0x90,
			.acc_ref[0]			= 0x57,
			.cti_delay[0]		= 0x80,
			.sub_saturation[0] 	= 0xc0,

			.burst_dec_a[0] 	= 0x2a,
			.burst_dec_b[0] 	= 0x00,
			.burst_dec_c[0] 	= 0x30,

			.c_option[0] 		= 0x80,

			.y_filter_b[0]		= 0x10,
			.y_filter_b_sel[0]	= 0x1e,
		},
		/* timing_a */
		{
			.h_delay_a[0] = 0x80,
			.h_delay_b[0] = 0x10,
			.h_delay_c[0] = 0x07,
			.y_delay[0]   = 0x18,

		},
		/* clk */
		{
			.clk_adc[0] = 0x06,
			.clk_dec[0] = 0xa6,
		},
		/* timing_b */
		{
	/*B9 0x96*/	.h_scaler1[0]  = 0x10,
	/*B9 0x97*/	.h_scaler2[0]  = 0x10,
	/*B9 0x98*/	.h_scaler3[0]  = 0x00,
	/*B9 0x99*/	.h_scaler4[0]  = 0x00,
	/*B9 0x9a*/	.h_scaler5[0]  = 0x00,
	/*B9 0x9b*/	.h_scaler6[0]  = 0x00,
	/*B9 0x9c*/	.h_scaler7[0]  = 0x00,
	/*B9 0x9d*/	.h_scaler8[0]  = 0x00,
	/*B9 0x9e*/	.h_scaler9[0]  = 0x00,


	/*B9 0x40*/	.pn_auto[0]    	= 0x00,

	/*B5 0x90*/	.comb_mode[0]      = 0x01,
	/*B9 0xb9*/	.h_pll_op_a[0]     = 0x72,
	/*B9 0x57*/	.mem_path[0]	   = 0x00,
				.fsc_lock_speed[0] = 0xdc,

	/*B0 0x81*/	.format_set1[0] = 0x10,
	/*B0 0x85*/	.format_set2[0] = 0x00,

	/*B0 0x64*/ .v_delay[0]     = 0x80,
		},
	},

	[ AHD20_SD_H960_2EX_Btype_NT ] = { /* o */
	/* base */
		{
			.eq_bypass[0] 	= 0x22,    // Bank5 0x30
			.eq_band_sel[0] = 0x77,    // BankA 0x31
			.eq_gain_sel[0] = 0x78,    // BankA 0x32
			.deq_a_on[0] 	= 0x00,    // BankA 0x33
			.deq_a_sel[0] 	= 0x00,    // BankA 0x34
			.deq_b_sel[0] 	= 0x00,    // BankA 0x35
		},
		/* coeff */
		{
			.deqA_01[0] = 0xAC,	// BankA 0x30
			.deqA_02[0] = 0x78,	// BankA 0x31
			.deqA_03[0] = 0x17,	// BankA 0x32
			.deqA_04[0] = 0xC1, // BankA 0x33
			.deqA_05[0] = 0x40, // BankA 0x34
			.deqA_06[0] = 0x00, // BankA 0x35
			.deqA_07[0] = 0xC3, // BankA 0x36
			.deqA_08[0] = 0x0A, // BankA 0x37
			.deqA_09[0] = 0x00, // BankA 0x38
			.deqA_10[0] = 0x02, // BankA 0x39
			.deqA_11[0] = 0x00, // BankA 0x3a
			.deqA_12[0] = 0xB2, // BankA 0x3b
		},
		/* color */
		{
			.contrast[0] 		= 0x90,
			.h_peaking[0] 		= 0x08,
			.c_filter[0]		= 0x82,

			.hue[0] 			= 0x00,
			.u_gain[0] 			= 0x00,
			.v_gain[0] 			= 0x00,
			.u_offset[0] 		= 0x00,
			.v_offset[0] 		= 0x00,

			.black_level[0] 	= 0x90,
			.acc_ref[0]			= 0x57,
			.cti_delay[0]		= 0x80,
			.sub_saturation[0] 	= 0xc0,

			.burst_dec_a[0] 	= 0x2a,
			.burst_dec_b[0] 	= 0x00,
			.burst_dec_c[0] 	= 0x30,

			.c_option[0] 		= 0x80,

			.y_filter_b[0]		= 0x10,
			.y_filter_b_sel[0]	= 0x1e,
		},
		/* timing_a */
		{
			.h_delay_a[0] = 0xC0,
			.h_delay_b[0] = 0x00,
			.h_delay_c[0] = 0x00,
			.y_delay[0]   = 0x18,

		},
		/* clk */
		{
			.clk_adc[0] = 0x02,
			.clk_dec[0] = 0x40,
		},
		/* timing_b */
		{
	/*B9 0x96*/	.h_scaler1[0]  = 0x10,
	/*B9 0x97*/	.h_scaler2[0]  = 0x10,
	/*B9 0x98*/	.h_scaler3[0]  = 0x00,
	/*B9 0x99*/	.h_scaler4[0]  = 0x00,
	/*B9 0x9a*/	.h_scaler5[0]  = 0x00,
	/*B9 0x9b*/	.h_scaler6[0]  = 0x00,
	/*B9 0x9c*/	.h_scaler7[0]  = 0x00,
	/*B9 0x9d*/	.h_scaler8[0]  = 0x00,
	/*B9 0x9e*/	.h_scaler9[0]  = 0x00,


	/*B9 0x40*/	.pn_auto[0]    	= 0x60,

	/*B5 0x90*/	.comb_mode[0]      = 0x01,
	/*B9 0xb9*/	.h_pll_op_a[0]     = 0x72,
	/*B9 0x57*/	.mem_path[0]	   = 0x00,
				.fsc_lock_speed[0] = 0xdc,

	/*B0 0x81*/	.format_set1[0] = 0xe0,
	/*B0 0x85*/	.format_set2[0] = 0x00,

	/*B0 0x64*/ .v_delay[0]     = 0xc0,
		},
	},

	[ AHD20_SD_H960_2EX_Btype_PAL ] = { /* o */
	/* base */
		{
			.eq_bypass[0] 	= 0x22,    // Bank5 0x30
			.eq_band_sel[0] = 0x77,    // BankA 0x31
			.eq_gain_sel[0] = 0x78,    // BankA 0x32
			.deq_a_on[0] 	= 0x00,    // BankA 0x33
			.deq_a_sel[0] 	= 0x00,    // BankA 0x34
			.deq_b_sel[0] 	= 0x00,    // BankA 0x35
		},
		/* coeff */
		{
			.deqA_01[0] = 0xAC,	// BankA 0x30
			.deqA_02[0] = 0x78,	// BankA 0x31
			.deqA_03[0] = 0x17,	// BankA 0x32
			.deqA_04[0] = 0xC1, // BankA 0x33
			.deqA_05[0] = 0x40, // BankA 0x34
			.deqA_06[0] = 0x00, // BankA 0x35
			.deqA_07[0] = 0xC3, // BankA 0x36
			.deqA_08[0] = 0x0A, // BankA 0x37
			.deqA_09[0] = 0x00, // BankA 0x38
			.deqA_10[0] = 0x02, // BankA 0x39
			.deqA_11[0] = 0x00, // BankA 0x3a
			.deqA_12[0] = 0xB2, // BankA 0x3b
		},
		/* color */
		{
			.contrast[0] 		= 0x90,
			.h_peaking[0] 		= 0x08,
			.c_filter[0]		= 0x82,

			.hue[0] 			= 0x00,
			.u_gain[0] 			= 0x00,
			.v_gain[0] 			= 0x00,
			.u_offset[0] 		= 0x00,
			.v_offset[0] 		= 0x00,

			.black_level[0] 	= 0x90,
			.acc_ref[0]			= 0x57,
			.cti_delay[0]		= 0x80,
			.sub_saturation[0] 	= 0xc0,

			.burst_dec_a[0] 	= 0x2a,
			.burst_dec_b[0] 	= 0x00,
			.burst_dec_c[0] 	= 0x30,

			.c_option[0] 		= 0x80,

			.y_filter_b[0]		= 0x10,
			.y_filter_b_sel[0]	= 0x1e,
		},
		/* timing_a */
		{
			.h_delay_a[0] = 0xe0,
			.h_delay_b[0] = 0x00,
			.h_delay_c[0] = 0x00,
			.y_delay[0]   = 0x18,

		},
		/* clk */
		{
			.clk_adc[0] = 0x02,
			.clk_dec[0] = 0x40,
		},
		/* timing_b */
		{
	/*B9 0x96*/	.h_scaler1[0]  = 0x10,
	/*B9 0x97*/	.h_scaler2[0]  = 0x10,
	/*B9 0x98*/	.h_scaler3[0]  = 0x00,
	/*B9 0x99*/	.h_scaler4[0]  = 0x00,
	/*B9 0x9a*/	.h_scaler5[0]  = 0x00,
	/*B9 0x9b*/	.h_scaler6[0]  = 0x00,
	/*B9 0x9c*/	.h_scaler7[0]  = 0x00,
	/*B9 0x9d*/	.h_scaler8[0]  = 0x00,
	/*B9 0x9e*/	.h_scaler9[0]  = 0x00,


	/*B9 0x40*/	.pn_auto[0]    	= 0x60,

	/*B5 0x90*/	.comb_mode[0]      = 0x01,
	/*B9 0xb9*/	.h_pll_op_a[0]     = 0x72,
	/*B9 0x57*/	.mem_path[0]	   = 0x00,
				.fsc_lock_speed[0] = 0xdc,

	/*B0 0x81*/	.format_set1[0] = 0xf0,
	/*B0 0x85*/	.format_set2[0] = 0x00,

	/*B0 0x64*/ .v_delay[0]     = 0x80,
		},
	},

	[ AHD20_1080P_50P ] = { /* o */
		/* base */
			{
				.eq_bypass[0] 	= 0x62, .eq_bypass[1] 	= 0x22, .eq_bypass[2] 	= 0x22, .eq_bypass[3] 	= 0x22, .eq_bypass[4] 	= 0x22, .eq_bypass[5] 	= 0x22,    // Bank5 0x30
				.eq_band_sel[0] = 0x77, .eq_band_sel[1] = 0x77, .eq_band_sel[2] = 0x77, .eq_band_sel[3] = 0x77, .eq_band_sel[4] = 0x57, .eq_band_sel[5] = 0x57,    // BankA 0x31
				.eq_gain_sel[0] = 0x78, .eq_gain_sel[1] = 0x7b, .eq_gain_sel[2] = 0x7f, .eq_gain_sel[3] = 0x7f, .eq_gain_sel[4] = 0x7f, .eq_gain_sel[5] = 0x7f,    // BankA 0x32
				.deq_a_on[0] 	= 0x00, .deq_a_on[1] 	= 0x01, .deq_a_on[2] 	= 0x01, .deq_a_on[3] 	= 0x01, .deq_a_on[4] 	= 0x01, .deq_a_on[5] 	= 0x01,    // BankA 0x33
				.deq_a_sel[0] 	= 0x00, .deq_a_sel[1] 	= 0x91, .deq_a_sel[2] 	= 0x87, .deq_a_sel[3] 	= 0x89, .deq_a_sel[4] 	= 0x93, .deq_a_sel[5] 	= 0x94,    // BankA 0x34
				.deq_b_sel[0] 	= 0x00, .deq_b_sel[1] 	= 0x00, .deq_b_sel[2] 	= 0x00, .deq_b_sel[3] 	= 0x00, .deq_b_sel[4] 	= 0x00, .deq_b_sel[5] 	= 0x00,    // BankA 0x35
			},
			/* coeff */
			{
				.deqA_01[0] = 0xAC, .deqA_01[1] = 0xAC, .deqA_01[2] = 0xAC, .deqA_01[3] = 0xAC, .deqA_01[4] = 0xAC, .deqA_01[5] = 0xAC,		// BankA 0x30
				.deqA_02[0] = 0x78, .deqA_02[1] = 0x78, .deqA_02[2] = 0x78, .deqA_02[3] = 0x78, .deqA_02[4] = 0x78, .deqA_02[5] = 0x78,		// BankA 0x31
				.deqA_03[0] = 0x17, .deqA_03[1] = 0x17, .deqA_03[2] = 0x17, .deqA_03[3] = 0x17, .deqA_03[4] = 0x17, .deqA_03[5] = 0x17,		// BankA 0x32
				.deqA_04[0] = 0xC1, .deqA_04[1] = 0xC1, .deqA_04[2] = 0xC1, .deqA_04[3] = 0xC1, .deqA_04[4] = 0xC1, .deqA_04[5] = 0xC1,     // BankA 0x33
				.deqA_05[0] = 0x40, .deqA_05[1] = 0x40, .deqA_05[2] = 0x40, .deqA_05[3] = 0x40, .deqA_05[4] = 0x40, .deqA_05[5] = 0x40,     // BankA 0x34
				.deqA_06[0] = 0x00, .deqA_06[1] = 0x00, .deqA_06[2] = 0x00, .deqA_06[3] = 0x00, .deqA_06[4] = 0x00, .deqA_06[5] = 0x00,     // BankA 0x35
				.deqA_07[0] = 0xC3, .deqA_07[1] = 0xC3, .deqA_07[2] = 0xC3, .deqA_07[3] = 0xC3, .deqA_07[4] = 0xC3, .deqA_07[5] = 0xC3,     // BankA 0x36
				.deqA_08[0] = 0x0A, .deqA_08[1] = 0x0A, .deqA_08[2] = 0x0A, .deqA_08[3] = 0x0A, .deqA_08[4] = 0x0A, .deqA_08[5] = 0x0A,     // BankA 0x37
				.deqA_09[0] = 0x00, .deqA_09[1] = 0x00, .deqA_09[2] = 0x00, .deqA_09[3] = 0x00, .deqA_09[4] = 0x00, .deqA_09[5] = 0x00,     // BankA 0x38
				.deqA_10[0] = 0x02, .deqA_10[1] = 0x02, .deqA_10[2] = 0x02, .deqA_10[3] = 0x02, .deqA_10[4] = 0x02, .deqA_10[5] = 0x02,     // BankA 0x39
				.deqA_11[0] = 0x00, .deqA_11[1] = 0x00, .deqA_11[2] = 0x00, .deqA_11[3] = 0x00, .deqA_11[4] = 0x00, .deqA_11[5] = 0x00,     // BankA 0x3a
				.deqA_12[0] = 0xB2, .deqA_12[1] = 0xB2, .deqA_12[2] = 0xB2, .deqA_12[3] = 0xB2, .deqA_12[4] = 0xB2, .deqA_12[5] = 0xB2,     // BankA 0x3b
			},
			/* color */
			{
				.contrast[0] 		= 0x86, .contrast[1] 		= 0x82, .contrast[2] 		= 0x82, .contrast[3] 		= 0x7e, .contrast[4] 		= 0x7c, .contrast[5] 		= 0x77,
				.h_peaking[0] 		= 0x00, .h_peaking[1] 		= 0x00, .h_peaking[2] 		= 0x00, .h_peaking[3] 		= 0x00, .h_peaking[4] 		= 0x0f, .h_peaking[5] 		= 0x0f,
				.c_filter[0]		= 0x82, .c_filter[1] 		= 0x82, .c_filter[2]	 	= 0x82, .c_filter[3] 		= 0x82, .c_filter[4] 		= 0xa2, .c_filter[5] 		= 0xb2,

				.hue[0] 			= 0x00, .hue[1] 			= 0x00, .hue[2] 			= 0x00, .hue[3] 			= 0xfe, .hue[4] 			= 0xfe, .hue[5] 			= 0xfe,
				.u_gain[0] 			= 0x00, .u_gain[1] 			= 0x00, .u_gain[2] 			= 0x04, .u_gain[3] 			= 0x10, .u_gain[4] 			= 0x10, .u_gain[5] 			= 0x18,
				.v_gain[0] 			= 0x00, .v_gain[1] 			= 0x00, .v_gain[2] 			= 0xf0, .v_gain[3] 			= 0x0e, .v_gain[4] 			= 0x0e, .v_gain[5] 			= 0x14,
				.u_offset[0] 		= 0xfe, .u_offset[1] 		= 0xfe, .u_offset[2] 		= 0xfe, .u_offset[3] 		= 0xfe, .u_offset[4] 		= 0xfe, .u_offset[5] 		= 0xfe,
				.v_offset[0] 		= 0xfb, .v_offset[1] 		= 0xfb, .v_offset[2] 		= 0xfb, .v_offset[3] 		= 0xfb, .v_offset[4] 		= 0xfb, .v_offset[5] 		= 0xfb,

				.black_level[0] 	= 0x80, .black_level[1] 	= 0x81, .black_level[2] 	= 0x81, .black_level[3] 	= 0x83, .black_level[4] 	= 0x83, .black_level[5] 	= 0x87,
				.acc_ref[0]			= 0x57, .acc_ref[1]			= 0x57, .acc_ref[2]			= 0x57, .acc_ref[3]			= 0x57, .acc_ref[4]			= 0x57, .acc_ref[5]			= 0x57,
				.cti_delay[0]		= 0x80, .cti_delay[1]		= 0x80, .cti_delay[2]		= 0x80, .cti_delay[3]		= 0x80, .cti_delay[4]		= 0x80, .cti_delay[5]		= 0x80,
				.sub_saturation[0] 	= 0xa8, .sub_saturation[1] 	= 0xa8, .sub_saturation[2] 	= 0xa8, .sub_saturation[3] 	= 0xa8, .sub_saturation[4] 	= 0x90, .sub_saturation[5] 	= 0x90,

				.burst_dec_a[0] 	= 0x2a, .burst_dec_a[1] 	= 0x2a, .burst_dec_a[2] 	= 0x2a, .burst_dec_a[3] 	= 0x2a, .burst_dec_a[4] 	= 0x2a, .burst_dec_a[5] 	= 0x2a,
				.burst_dec_b[0] 	= 0x00, .burst_dec_b[1] 	= 0x00, .burst_dec_b[2] 	= 0x00, .burst_dec_b[3] 	= 0x00, .burst_dec_b[4] 	= 0x00, .burst_dec_b[5] 	= 0x00,
				.burst_dec_c[0] 	= 0x30, .burst_dec_c[1] 	= 0x30, .burst_dec_c[2] 	= 0x30, .burst_dec_c[3] 	= 0x30, .burst_dec_c[4] 	= 0x30, .burst_dec_c[5] 	= 0x30,

				.c_option[0] 		= 0x80, .c_option[1] 		= 0x80, .c_option[2] 		= 0x90, .c_option[3] 		= 0x90, .c_option[4] 		= 0x90, .c_option[5] 		= 0xa0,

				.y_filter_b[0]		= 0x10, .y_filter_b[1]		= 0x10, .y_filter_b[2]		= 0x10, .y_filter_b[3]		= 0x10, .y_filter_b[4]		= 0x10, .y_filter_b[5]		= 0x10,
				.y_filter_b_sel[0]	= 0x1e,	.y_filter_b_sel[1]	= 0x1e,	.y_filter_b_sel[2]	= 0x1e, .y_filter_b_sel[3]	= 0x1e, .y_filter_b_sel[4]	= 0x1e, .y_filter_b_sel[5]	= 0x1e,
			},
			/* timing_a */
			{
				.h_delay_a[0] = 0x86, .h_delay_a[1] = 0x84, .h_delay_a[2] = 0x80, .h_delay_a[3] = 0x80, .h_delay_a[4] = 0x80, .h_delay_a[5] = 0x80,
				.h_delay_b[0] = 0x10, .h_delay_b[1] = 0x10, .h_delay_b[2] = 0x10, .h_delay_b[3] = 0x10, .h_delay_b[4] = 0x10, .h_delay_b[5] = 0x10,
				.h_delay_c[0] = 0x03, .h_delay_c[1] = 0x03, .h_delay_c[2] = 0x03, .h_delay_c[3] = 0x03, .h_delay_c[4] = 0x03, .h_delay_c[5] = 0x03,
				.y_delay[0]   = 0x05, .y_delay[1]   = 0x03, .y_delay[2]   = 0x03, .y_delay[3]   = 0x03, .y_delay[4]   = 0x03, .y_delay[5] =   0x03,

			},
			/* clk */
			{
				.clk_adc[0] = 0x02, .clk_adc[1] = 0x02, .clk_adc[2] = 0x02, .clk_adc[3] = 0x02, .clk_adc[4] = 0x02, .clk_adc[5] = 0x02,
				.clk_dec[0] = 0x40, .clk_dec[1] = 0x40, .clk_dec[2] = 0x40, .clk_dec[3] = 0x40, .clk_dec[4] = 0x40, .clk_dec[5] = 0x40,
			},
			/* timing_b */
			{
		/*B9 0x96*/	.h_scaler1[0]  = 0x00, .h_scaler1[1]   = 0x00, .h_scaler1[2]   = 0x00, .h_scaler1[3]   = 0x00, .h_scaler1[4]   = 0x00, .h_scaler1[5]   = 0x00,
		/*B9 0x97*/	.h_scaler2[0]  = 0x00, .h_scaler2[1]   = 0x00, .h_scaler2[2]   = 0x00, .h_scaler2[3]   = 0x00, .h_scaler2[4]   = 0x00, .h_scaler2[5]   = 0x00,
		/*B9 0x98*/	.h_scaler3[0]  = 0x00, .h_scaler3[1]   = 0x00, .h_scaler3[2]   = 0x00, .h_scaler3[3]   = 0x00, .h_scaler3[4]   = 0x00, .h_scaler3[5]   = 0x00,
		/*B9 0x99*/	.h_scaler4[0]  = 0x00, .h_scaler4[1]   = 0x00, .h_scaler4[2]   = 0x00, .h_scaler4[3]   = 0x00, .h_scaler4[4]   = 0x00, .h_scaler4[5]   = 0x00,
		/*B9 0x9a*/	.h_scaler5[0]  = 0x00, .h_scaler5[1]   = 0x00, .h_scaler5[2]   = 0x00, .h_scaler5[3]   = 0x00, .h_scaler5[4]   = 0x00, .h_scaler5[5]   = 0x00,
		/*B9 0x9b*/	.h_scaler6[0]  = 0x00, .h_scaler6[1]   = 0x00, .h_scaler6[2]   = 0x00, .h_scaler6[3]   = 0x00, .h_scaler6[4]   = 0x00, .h_scaler6[5]   = 0x00,
		/*B9 0x9c*/	.h_scaler7[0]  = 0x00, .h_scaler7[1]   = 0x00, .h_scaler7[2]   = 0x00, .h_scaler7[3]   = 0x00, .h_scaler7[4]   = 0x00, .h_scaler7[5]   = 0x00,
		/*B9 0x9d*/	.h_scaler8[0]  = 0x00, .h_scaler8[1]   = 0x00, .h_scaler8[2]   = 0x00, .h_scaler8[3]   = 0x00, .h_scaler8[4]   = 0x00, .h_scaler8[5]   = 0x00,
		/*B9 0x9e*/	.h_scaler9[0]  = 0x00, .h_scaler9[1]   = 0x00, .h_scaler9[2]   = 0x00, .h_scaler9[3]   = 0x00, .h_scaler9[4]   = 0x00, .h_scaler9[5]   = 0x00,


		/*B9 0x40*/	.pn_auto[0]    	= 0x00, .pn_auto[1]		= 0x00, .pn_auto[2]    	= 0x00, .pn_auto[3]    	= 0x00, .pn_auto[4]    	= 0x00, .pn_auto[5]    	= 0x00,

		/*B5 0x90*/	.comb_mode[0]      = 0x01, .comb_mode[1]	  = 0x01, .comb_mode[2]      = 0x01, .comb_mode[3]      = 0x01, .comb_mode[4]  	   = 0x01, .comb_mode[5]      = 0x01,
		/*B9 0xb9*/	.h_pll_op_a[0]     = 0x72, .h_pll_op_a[1]     = 0x72, .h_pll_op_a[2]     = 0x72, .h_pll_op_a[3]     = 0x72, .h_pll_op_a[4]     = 0x72, .h_pll_op_a[5]     = 0x72,
		/*B9 0x57*/	.mem_path[0]	   = 0x00, .mem_path[1]	      = 0x00, .mem_path[2]	     = 0x00, .mem_path[3]	    = 0x00, .mem_path[4]	   = 0x00, .mem_path[5]	      = 0x00,
				    .fsc_lock_speed[0] = 0xdc, .fsc_lock_speed[1] = 0xdc, .fsc_lock_speed[2] = 0xdc, .fsc_lock_speed[3] = 0xdc, .fsc_lock_speed[4] = 0xdc, .fsc_lock_speed[5] = 0xdc,

		/*B0 0x81*/	.format_set1[0] = 0x03, .format_set1[1] = 0x03, .format_set1[2] = 0x03, .format_set1[3] = 0x03, .format_set1[4] = 0x03, .format_set1[5] = 0x03,
		/*B0 0x85*/	.format_set2[0] = 0x00, .format_set2[1] = 0x00, .format_set2[2] = 0x00, .format_set2[3] = 0x00, .format_set2[4] = 0x00, .format_set2[5] = 0x00,

		/*B0 0x64*/ .v_delay[0]     = 0x21, .v_delay[1]     = 0x21, .v_delay[2]     = 0x21, .v_delay[3]     = 0x21, .v_delay[4]     = 0x21, .v_delay[5]     = 0x21,
			},
		},
		[ AHD20_1080P_60P ] = { /* o */
		/* base */
			{
				.eq_bypass[0] 	= 0x62, .eq_bypass[1] 	= 0x22, .eq_bypass[2] 	= 0x22, .eq_bypass[3] 	= 0x22, .eq_bypass[4] 	= 0x22, .eq_bypass[5] 	= 0x22,    // Bank5 0x30
				.eq_band_sel[0] = 0x77, .eq_band_sel[1] = 0x77, .eq_band_sel[2] = 0x77, .eq_band_sel[3] = 0x77, .eq_band_sel[4] = 0x57, .eq_band_sel[5] = 0x57,    // BankA 0x31
				.eq_gain_sel[0] = 0x78, .eq_gain_sel[1] = 0x7b, .eq_gain_sel[2] = 0x7f, .eq_gain_sel[3] = 0x7f, .eq_gain_sel[4] = 0x7f, .eq_gain_sel[5] = 0x7f,    // BankA 0x32
				.deq_a_on[0] 	= 0x00, .deq_a_on[1] 	= 0x01, .deq_a_on[2] 	= 0x01, .deq_a_on[3] 	= 0x01, .deq_a_on[4] 	= 0x01, .deq_a_on[5] 	= 0x01,    // BankA 0x33
				.deq_a_sel[0] 	= 0x00, .deq_a_sel[1] 	= 0x91, .deq_a_sel[2] 	= 0x87, .deq_a_sel[3] 	= 0x89, .deq_a_sel[4] 	= 0x93, .deq_a_sel[5] 	= 0x94,    // BankA 0x34
				.deq_b_sel[0] 	= 0x00, .deq_b_sel[1] 	= 0x00, .deq_b_sel[2] 	= 0x00, .deq_b_sel[3] 	= 0x00, .deq_b_sel[4] 	= 0x00, .deq_b_sel[5] 	= 0x00,    // BankA 0x35
			},
			/* coeff */
			{
				.deqA_01[0] = 0xAC, .deqA_01[1] = 0xAC, .deqA_01[2] = 0xAC, .deqA_01[3] = 0xAC, .deqA_01[4] = 0xAC, .deqA_01[5] = 0xAC,		// BankA 0x30
				.deqA_02[0] = 0x78, .deqA_02[1] = 0x78, .deqA_02[2] = 0x78, .deqA_02[3] = 0x78, .deqA_02[4] = 0x78, .deqA_02[5] = 0x78,		// BankA 0x31
				.deqA_03[0] = 0x17, .deqA_03[1] = 0x17, .deqA_03[2] = 0x17, .deqA_03[3] = 0x17, .deqA_03[4] = 0x17, .deqA_03[5] = 0x17,		// BankA 0x32
				.deqA_04[0] = 0xC1, .deqA_04[1] = 0xC1, .deqA_04[2] = 0xC1, .deqA_04[3] = 0xC1, .deqA_04[4] = 0xC1, .deqA_04[5] = 0xC1,     // BankA 0x33
				.deqA_05[0] = 0x40, .deqA_05[1] = 0x40, .deqA_05[2] = 0x40, .deqA_05[3] = 0x40, .deqA_05[4] = 0x40, .deqA_05[5] = 0x40,     // BankA 0x34
				.deqA_06[0] = 0x00, .deqA_06[1] = 0x00, .deqA_06[2] = 0x00, .deqA_06[3] = 0x00, .deqA_06[4] = 0x00, .deqA_06[5] = 0x00,     // BankA 0x35
				.deqA_07[0] = 0xC3, .deqA_07[1] = 0xC3, .deqA_07[2] = 0xC3, .deqA_07[3] = 0xC3, .deqA_07[4] = 0xC3, .deqA_07[5] = 0xC3,     // BankA 0x36
				.deqA_08[0] = 0x0A, .deqA_08[1] = 0x0A, .deqA_08[2] = 0x0A, .deqA_08[3] = 0x0A, .deqA_08[4] = 0x0A, .deqA_08[5] = 0x0A,     // BankA 0x37
				.deqA_09[0] = 0x00, .deqA_09[1] = 0x00, .deqA_09[2] = 0x00, .deqA_09[3] = 0x00, .deqA_09[4] = 0x00, .deqA_09[5] = 0x00,     // BankA 0x38
				.deqA_10[0] = 0x02, .deqA_10[1] = 0x02, .deqA_10[2] = 0x02, .deqA_10[3] = 0x02, .deqA_10[4] = 0x02, .deqA_10[5] = 0x02,     // BankA 0x39
				.deqA_11[0] = 0x00, .deqA_11[1] = 0x00, .deqA_11[2] = 0x00, .deqA_11[3] = 0x00, .deqA_11[4] = 0x00, .deqA_11[5] = 0x00,     // BankA 0x3a
				.deqA_12[0] = 0xB2, .deqA_12[1] = 0xB2, .deqA_12[2] = 0xB2, .deqA_12[3] = 0xB2, .deqA_12[4] = 0xB2, .deqA_12[5] = 0xB2,     // BankA 0x3b
			},
			/* color */
			{
				.contrast[0] 		= 0x86, .contrast[1] 		= 0x82, .contrast[2] 		= 0x82, .contrast[3] 		= 0x7e, .contrast[4] 		= 0x7c, .contrast[5] 		= 0x77,
				.h_peaking[0] 		= 0x00, .h_peaking[1] 		= 0x00, .h_peaking[2] 		= 0x00, .h_peaking[3] 		= 0x00, .h_peaking[4] 		= 0x0f, .h_peaking[5] 		= 0x0f,
				.c_filter[0]		= 0x82, .c_filter[1] 		= 0x82, .c_filter[2]	 	= 0x82, .c_filter[3] 		= 0x82, .c_filter[4] 		= 0xa2, .c_filter[5] 		= 0xb2,

				.hue[0] 			= 0x00, .hue[1] 			= 0x00, .hue[2] 			= 0x00, .hue[3] 			= 0xfe, .hue[4] 			= 0xfe, .hue[5] 			= 0xfe,
				.u_gain[0] 			= 0x00, .u_gain[1] 			= 0x00, .u_gain[2] 			= 0x04, .u_gain[3] 			= 0x10, .u_gain[4] 			= 0x10, .u_gain[5] 			= 0x18,
				.v_gain[0] 			= 0x00, .v_gain[1] 			= 0x00, .v_gain[2] 			= 0xf0, .v_gain[3] 			= 0x0e, .v_gain[4] 			= 0x0e, .v_gain[5] 			= 0x14,
				.u_offset[0] 		= 0xfe, .u_offset[1] 		= 0xfe, .u_offset[2] 		= 0xfe, .u_offset[3] 		= 0xfe, .u_offset[4] 		= 0xfe, .u_offset[5] 		= 0xfe,
				.v_offset[0] 		= 0xfb, .v_offset[1] 		= 0xfb, .v_offset[2] 		= 0xfb, .v_offset[3] 		= 0xfb, .v_offset[4] 		= 0xfb, .v_offset[5] 		= 0xfb,

				.black_level[0] 	= 0x80, .black_level[1] 	= 0x81, .black_level[2] 	= 0x81, .black_level[3] 	= 0x83, .black_level[4] 	= 0x83, .black_level[5] 	= 0x87,
				.acc_ref[0]			= 0x57, .acc_ref[1]			= 0x57, .acc_ref[2]			= 0x57, .acc_ref[3]			= 0x57, .acc_ref[4]			= 0x57, .acc_ref[5]			= 0x57,
				.cti_delay[0]		= 0x80, .cti_delay[1]		= 0x80, .cti_delay[2]		= 0x80, .cti_delay[3]		= 0x80, .cti_delay[4]		= 0x80, .cti_delay[5]		= 0x80,
				.sub_saturation[0] 	= 0xa8, .sub_saturation[1] 	= 0xa8, .sub_saturation[2] 	= 0xa8, .sub_saturation[3] 	= 0xa8, .sub_saturation[4] 	= 0x90, .sub_saturation[5] 	= 0x90,

				.burst_dec_a[0] 	= 0x2a, .burst_dec_a[1] 	= 0x2a, .burst_dec_a[2] 	= 0x2a, .burst_dec_a[3] 	= 0x2a, .burst_dec_a[4] 	= 0x2a, .burst_dec_a[5] 	= 0x2a,
				.burst_dec_b[0] 	= 0x00, .burst_dec_b[1] 	= 0x00, .burst_dec_b[2] 	= 0x00, .burst_dec_b[3] 	= 0x00, .burst_dec_b[4] 	= 0x00, .burst_dec_b[5] 	= 0x00,
				.burst_dec_c[0] 	= 0x30, .burst_dec_c[1] 	= 0x30, .burst_dec_c[2] 	= 0x30, .burst_dec_c[3] 	= 0x30, .burst_dec_c[4] 	= 0x30, .burst_dec_c[5] 	= 0x30,

				.c_option[0] 		= 0x80, .c_option[1] 		= 0x80, .c_option[2] 		= 0x90, .c_option[3] 		= 0x90, .c_option[4] 		= 0x90, .c_option[5] 		= 0xa0,

				.y_filter_b[0]		= 0x10, .y_filter_b[1]		= 0x10, .y_filter_b[2]		= 0x10, .y_filter_b[3]		= 0x10, .y_filter_b[4]		= 0x10, .y_filter_b[5]		= 0x10,
				.y_filter_b_sel[0]	= 0x1e,	.y_filter_b_sel[1]	= 0x1e,	.y_filter_b_sel[2]	= 0x1e, .y_filter_b_sel[3]	= 0x1e, .y_filter_b_sel[4]	= 0x1e, .y_filter_b_sel[5]	= 0x1e,
			},
			/* timing_a */
			{
				.h_delay_a[0] = 0x86, .h_delay_a[1] = 0x84, .h_delay_a[2] = 0x80, .h_delay_a[3] = 0x80, .h_delay_a[4] = 0x80, .h_delay_a[5] = 0x80,
				.h_delay_b[0] = 0x10, .h_delay_b[1] = 0x10, .h_delay_b[2] = 0x10, .h_delay_b[3] = 0x10, .h_delay_b[4] = 0x10, .h_delay_b[5] = 0x10,
				.h_delay_c[0] = 0x03, .h_delay_c[1] = 0x03, .h_delay_c[2] = 0x03, .h_delay_c[3] = 0x03, .h_delay_c[4] = 0x03, .h_delay_c[5] = 0x03,
				.y_delay[0]   = 0x05, .y_delay[1]   = 0x03, .y_delay[2]   = 0x03, .y_delay[3]   = 0x03, .y_delay[4]   = 0x03, .y_delay[5] =   0x03,

			},
			/* clk */
			{
				.clk_adc[0] = 0x02, .clk_adc[1] = 0x02, .clk_adc[2] = 0x02, .clk_adc[3] = 0x02, .clk_adc[4] = 0x02, .clk_adc[5] = 0x02,
				.clk_dec[0] = 0x40, .clk_dec[1] = 0x40, .clk_dec[2] = 0x40, .clk_dec[3] = 0x40, .clk_dec[4] = 0x40, .clk_dec[5] = 0x40,
			},
			/* timing_b */
			{
		/*B9 0x96*/	.h_scaler1[0]  = 0x00, .h_scaler1[1]   = 0x00, .h_scaler1[2]   = 0x00, .h_scaler1[3]   = 0x00, .h_scaler1[4]   = 0x00, .h_scaler1[5]   = 0x00,
		/*B9 0x97*/	.h_scaler2[0]  = 0x00, .h_scaler2[1]   = 0x00, .h_scaler2[2]   = 0x00, .h_scaler2[3]   = 0x00, .h_scaler2[4]   = 0x00, .h_scaler2[5]   = 0x00,
		/*B9 0x98*/	.h_scaler3[0]  = 0x00, .h_scaler3[1]   = 0x00, .h_scaler3[2]   = 0x00, .h_scaler3[3]   = 0x00, .h_scaler3[4]   = 0x00, .h_scaler3[5]   = 0x00,
		/*B9 0x99*/	.h_scaler4[0]  = 0x00, .h_scaler4[1]   = 0x00, .h_scaler4[2]   = 0x00, .h_scaler4[3]   = 0x00, .h_scaler4[4]   = 0x00, .h_scaler4[5]   = 0x00,
		/*B9 0x9a*/	.h_scaler5[0]  = 0x00, .h_scaler5[1]   = 0x00, .h_scaler5[2]   = 0x00, .h_scaler5[3]   = 0x00, .h_scaler5[4]   = 0x00, .h_scaler5[5]   = 0x00,
		/*B9 0x9b*/	.h_scaler6[0]  = 0x00, .h_scaler6[1]   = 0x00, .h_scaler6[2]   = 0x00, .h_scaler6[3]   = 0x00, .h_scaler6[4]   = 0x00, .h_scaler6[5]   = 0x00,
		/*B9 0x9c*/	.h_scaler7[0]  = 0x00, .h_scaler7[1]   = 0x00, .h_scaler7[2]   = 0x00, .h_scaler7[3]   = 0x00, .h_scaler7[4]   = 0x00, .h_scaler7[5]   = 0x00,
		/*B9 0x9d*/	.h_scaler8[0]  = 0x00, .h_scaler8[1]   = 0x00, .h_scaler8[2]   = 0x00, .h_scaler8[3]   = 0x00, .h_scaler8[4]   = 0x00, .h_scaler8[5]   = 0x00,
		/*B9 0x9e*/	.h_scaler9[0]  = 0x00, .h_scaler9[1]   = 0x00, .h_scaler9[2]   = 0x00, .h_scaler9[3]   = 0x00, .h_scaler9[4]   = 0x00, .h_scaler9[5]   = 0x00,


		/*B9 0x40*/	.pn_auto[0]    	= 0x00, .pn_auto[1]		= 0x00, .pn_auto[2]    	= 0x00, .pn_auto[3]    	= 0x00, .pn_auto[4]    	= 0x00, .pn_auto[5]    	= 0x00,

		/*B5 0x90*/	.comb_mode[0]      = 0x01, .comb_mode[1]	  = 0x01, .comb_mode[2]      = 0x01, .comb_mode[3]      = 0x01, .comb_mode[4]  	   = 0x01, .comb_mode[5]      = 0x01,
		/*B9 0xb9*/	.h_pll_op_a[0]     = 0x72, .h_pll_op_a[1]     = 0x72, .h_pll_op_a[2]     = 0x72, .h_pll_op_a[3]     = 0x72, .h_pll_op_a[4]     = 0x72, .h_pll_op_a[5]     = 0x72,
		/*B9 0x57*/	.mem_path[0]	   = 0x00, .mem_path[1]	      = 0x00, .mem_path[2]	     = 0x00, .mem_path[3]	    = 0x00, .mem_path[4]	   = 0x00, .mem_path[5]	      = 0x00,
					.fsc_lock_speed[0] = 0xdc, .fsc_lock_speed[1] = 0xdc, .fsc_lock_speed[2] = 0xdc, .fsc_lock_speed[3] = 0xdc, .fsc_lock_speed[4] = 0xdc, .fsc_lock_speed[5] = 0xdc,

		/*B0 0x81*/	.format_set1[0] = 0x02, .format_set1[1] = 0x02, .format_set1[2] = 0x02, .format_set1[3] = 0x02, .format_set1[4] = 0x02, .format_set1[5] = 0x02,
		/*B0 0x85*/	.format_set2[0] = 0x00, .format_set2[1] = 0x00, .format_set2[2] = 0x00, .format_set2[3] = 0x00, .format_set2[4] = 0x00, .format_set2[5] = 0x00,

		/*B0 0x64*/ .v_delay[0]     = 0x21, .v_delay[1]     = 0x21, .v_delay[2]     = 0x21, .v_delay[3]     = 0x21, .v_delay[4]     = 0x21, .v_delay[5]     = 0x21,
			},
		},
};
#endif


#define UNUSED(x) ((void)(x))

#if 0
#define dbg_printk(...) _kernel_dbg_printk( __VA_ARGS__)

static void _kernel_dbg_printk(const char* s, ...)
{
	unsigned char buffer[128];
	char *pS = buffer;

	va_list args;
	va_start(args, s);
	vsprintf(buffer, s, args);
	va_end(args);


	while(*pS) { if( *pS == '\n' ) *pS= ' '; pS++; }

	printk("\033[33m\033[1m [KERENL] \033[0m:\033[32m\033[1m %s \033[0m\n", buffer);
}
#endif


//driver function
void raptor3_on_video_set(struct i2c_client *client, int ch, unsigned char fmt);
void video_input_onvideo_set(struct i2c_client *client, decoder_dev_ch_info_s *decoder_info);
void raptor3_output_set(struct i2c_client *client, int input_ch, int out_port);
unsigned char __IsOver3MRTVideoFormat( const char *poFmtName );
void video_input_vafe_reset(struct i2c_client *client, decoder_dev_ch_info_s *decoder_info);
void video_input_h_timing_set(struct i2c_client *client, decoder_dev_ch_info_s *pDevChInfo);
void video_input_color_set(struct i2c_client *client, decoder_dev_ch_info_s *decoder_info);
void video_input_vafe_init(struct i2c_client *client, decoder_dev_ch_info_s *decoder_info);
void video_input_new_format_set(struct i2c_client *client, decoder_dev_ch_info_s *decoder_info);
void video_input_eq_val_set(struct i2c_client *client, video_equalizer_info_s *pvin_eq_set);
void __eq_base_set_value(struct i2c_client *client, video_equalizer_info_s *pvin_eq_set, video_equalizer_base_s *pbase );
void __eq_coeff_set_value(struct i2c_client *client, video_equalizer_info_s *pvin_eq_set, video_equalizer_coeff_s *pcoeff );
void __eq_color_set_value(struct i2c_client *client, video_equalizer_info_s *pvin_eq_set, video_equalizer_color_s *pcolor );
void __eq_timing_a_set_value(struct i2c_client *client, video_equalizer_info_s *pvin_eq_set, video_equalizer_timing_a_s *ptiming_a );
void __eq_clk_set_value(struct i2c_client *client, video_equalizer_info_s *pvin_eq_set, video_equalizer_clk_s *pclk );
void __eq_timing_b_set_value(struct i2c_client *client, video_equalizer_info_s *pvin_eq_set, video_equalizer_timing_b_s *ptiming_b );
void video_output_channel_sequence_set(struct i2c_client *client, video_output_sequence *vout_seq);
void video_output_data_out_mode_set(struct i2c_client *client, video_output_data_out_mode *vo_data_out_mode);
void video_output_colorbar_set(struct i2c_client *client);
void raptor3_def_set(struct i2c_client *client);
void video_input_auto_detect_set(struct i2c_client *client, video_input_auto_detect *vin_auto_det);
void _video_input_auto_detect_vafe_set(struct i2c_client *client, video_input_auto_detect *vin_auto_det);

#endif