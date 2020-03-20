#include<avr/io.h>

#include<avr/interrupt.h>
//CAN_OP_MODE
const char
    _CAN_MODE_BITS    = 0x0A,   // Use this to access opmode  bits
    _CAN_MODE_STANDBY = 0x00,
    _CAN_MODE_ENABLE  = 0x02,
    _CAN_MODE_LISTEN  = 0x08

//CAN_CONFIG_FLAGS    
const char
    _CAN_CONFIG_SAMPLE_BIT      = 0x01,
    _CAN_CONFIG_SAMPLE_ONCE     = 0xFE,   // XXXX XXX0
    _CAN_CONFIG_SAMPLE_THRICE   = 0xFF,   // XXXX XXX1

    _CAN_CONFIG_MSG_TYPE_BIT    = 0x10,
    _CAN_CONFIG_STD_MSG         = 0xEF,   // XXX0 XXXX
    _CAN_CONFIG_XTD_MSG         = 0xFF;   // XXX1 XXXX


//CAN_TX_MSG_FLAGS    

const char
    _CAN_CONMOB_DIS        = 0x3F,   // 00XX XXXX   messsage objects work modes
    _CAN_CONMOB_EN_TX      = 0x7F,   // 01XX XXXX
    _CAN_CONMOB_EN_RX      = 0xBF,   // 10XX XXXX
    _CAN_CONMOB_EN_FRAME   = 0xFF,   // 11XX XXXX

    _CAN_IDE_FRAME_BIT     = 0x10,   // Identifier Extension
    _CAN_IDE_STD_FRAME     = 0xEF,   // XXX0 XXXX
    _CAN_IDE_XTD_FRAME     = 0xFF,   // XXX1 XXXX

    _CAN_RTR_BIT           = 0x20,
    _CAN_NO_RTR_FRAME      = 0xFF,   // XX1XXXXX
    _CAN_RTR_FRAME         = 0xDF,   // XX0XXXXX

    _CAN_TX                = 0x01,   // Transmitter Busy
    _CAN_TX_NO_BSY         = 0xFE,   // XXXX XXX0
    _CAN_TX_BSY            = 0xFF;   // XXXX XXX1

//CAN_RX_MSG_FLAGS

const char
    _CAN_RX                = 0x08,   // Receiver Busy
    _CAN_RX_NO_BSY         = 0xF7,   // XXXX 0XXX
    _CAN_RX_BSY            = 0xFF;   // XXXX 1XXX    

//CAN_MASK


const char
    CAN_RX_MASK_0  = 0x00,
    CAN_RX_MASK_1  = 0x01,
    CAN_RX_MASK_2  = 0x02,
    CAN_RX_MASK_3  = 0x03,
    CAN_RX_MASK_4  = 0x04,
    CAN_RX_MASK_5  = 0x05,
    CAN_RX_MASK_6  = 0x06,
    CAN_RX_MASK_7  = 0x07,
    CAN_RX_MASK_8  = 0x08,
    CAN_RX_MASK_9  = 0x09,
    CAN_RX_MASK_10 = 0x0A,
    CAN_RX_MASK_11 = 0x0B,
    CAN_RX_MASK_12 = 0x0C,
    CAN_RX_MASK_13 = 0x0D,
    CAN_RX_MASK_14 = 0x0E;


//CAN_FILTER


const char
    CAN_RX_FILTER_0  = 0x00,
    CAN_RX_FILTER_1  = 0x01,
    CAN_RX_FILTER_2  = 0x02,
    CAN_RX_FILTER_3  = 0x03,
    CAN_RX_FILTER_4  = 0x04,
    CAN_RX_FILTER_5  = 0x05,
    CAN_RX_FILTER_6  = 0x06,
    CAN_RX_FILTER_7  = 0x07,
    CAN_RX_FILTER_8  = 0x08,
    CAN_RX_FILTER_9  = 0x09,
    CAN_RX_FILTER_10 = 0x0A,
    CAN_RX_FILTER_11 = 0x0B,
    CAN_RX_FILTER_12 = 0x0C,
    CAN_RX_FILTER_13 = 0x0D,
    CAN_RX_FILTER_14 = 0x0E;


//CAN_MOB


const char
    _CAN_EN_MOB0_BIT    = 0x0001, // Flags, set to 1 if the appropriate MOb is in use. When the appropriate operation ends, TXOK or RXOK are set to 1
    _CAN_EN_MOB1_BIT    = 0x0002,
    _CAN_EN_MOB2_BIT    = 0x0004,
    _CAN_EN_MOB3_BIT    = 0x0008,
    _CAN_EN_MOB4_BIT    = 0x0010,
    _CAN_EN_MOB5_BIT    = 0x0020,
    _CAN_EN_MOB6_BIT    = 0x0040,
    _CAN_EN_MOB7_BIT    = 0x0080,
    _CAN_EN_MOB8_BIT    = 0x0100,
    _CAN_EN_MOB9_BIT    = 0x0200,
    _CAN_EN_MOB10_BIT   = 0x0400,
    _CAN_EN_MOB11_BIT   = 0x0800,
    _CAN_EN_MOB12_BIT   = 0x1000,
    _CAN_EN_MOB13_BIT   = 0x2000,
    _CAN_EN_MOB14_BIT   = 0x4000,

    _CAN_CONFIG_STMOB_TXOK  = 0x40,   // X1XX XXXX  From the CAN MOb Status Register
    _CAN_CONFIG_STMOB_RXOK  = 0x20,   // XX1X XXXX  Receive OK
    _CAN_CONFIG_STMOB_BERR  = 0x10,   // XXX1 XXXX  Bit Error (Only in transmission)
    _CAN_CONFIG_STMOB_SERR  = 0x08,   // XXXX 1XXX  Stuff Error
    _CAN_CONFIG_STMOB_CERR  = 0x04,   // XXXX X1XX  CRC Error
    _CAN_CONFIG_STMOB_FERR  = 0x02,   // XXXX XX1X  Form Error
    _CAN_CONFIG_STMOB_AERR  = 0x01;   // XXXX XXX1  Acknowledgment Error
            
