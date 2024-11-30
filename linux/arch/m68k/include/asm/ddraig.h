#ifndef _DDRAIG_H
#define _DDRAIG_H

#define IRQ_NUM_DUART 3
#define IRQ_NUM_TIMER 2
#define IRQ_NUM_IDE 1

// XR68C681 DUART
#define DUART1_BASE 0x00F7F000

#define DUART1_MR1A (DUART1_BASE + 0x00)
#define DUART1_MR2A (DUART1_BASE + 0x00)
#define DUART1_SRA (DUART1_BASE + 0x02)
#define DUART1_CSRA (DUART1_BASE + 0x02)
#define DUART1_CRA (DUART1_BASE + 0x04)
#define DUART1_MISR (DUART1_BASE + 0x04)
#define DUART1_RBA (DUART1_BASE + 0x06)
#define DUART1_TBA (DUART1_BASE + 0x06)
#define DUART1_ACR (DUART1_BASE + 0x08)
#define DUART1_ISR (DUART1_BASE + 0x0A)
#define DUART1_IMR (DUART1_BASE + 0x0A)
#define DUART1_CUR (DUART1_BASE + 0x0C)
#define DUART1_CLR (DUART1_BASE + 0x0E)
#define DUART1_MR1B (DUART1_BASE + 0x10)
#define DUART1_MR2B (DUART1_BASE + 0x10)
#define DUART1_SRB (DUART1_BASE + 0x12)
#define DUART1_CSRB (DUART1_BASE + 0x12)
#define DUART1_CRB (DUART1_BASE + 0x14)
#define DUART1_RBB (DUART1_BASE + 0x16)
#define DUART1_TBB (DUART1_BASE + 0x16)
#define DUART1_IVR (DUART1_BASE + 0x18)
#define DUART1_OPCR (DUART1_BASE + 0x1A)
#define DUART1_OPR (DUART1_BASE + 0x1C)
#define DUART1_OPR_RESET (DUART1_BASE + 0x1E)

// IDE
#define DDRAIG_IDE_BASE 0x00F7F300
#define DDRAIG_IDE_DATA DDRAIG_IDE_BASE + 0x00
#define DDRAIG_IDE_FEATURE DDRAIG_IDE_BASE + 0x02
#define DDRAIG_IDE_SECTOR_COUNT DDRAIG_IDE_BASE + 0x04
#define DDRAIG_IDE_SECTOR_START DDRAIG_IDE_BASE + 0x06
#define DDRAIG_IDE_LBA_MID DDRAIG_IDE_BASE + 0x08
#define DDRAIG_IDE_LBA_HIGH DDRAIG_IDE_BASE + 0x0A
#define DDRAIG_IDE_DRIVE_SEL DDRAIG_IDE_BASE + 0x0C
#define DDRAIG_IDE_STATUS DDRAIG_IDE_BASE + 0x0E
#define DDRAIG_IDE_COMMAND DDRAIG_IDE_BASE + 0x0E

#define DDRAIG_IDE_ALT_STATUS 0x00F7F300 + 0x8C  // aka Device Control

// Interrupt bits
#define DUART_INTR_COUNTER 0b0001000
#define DUART_INTR_RXRDY 0b00100000

// Get the value at a memory address
#define MEM(address) (*(volatile unsigned char *)(address))
#define MEM16(address) (*(volatile unsigned short *)(address))
#define MEM32(address) (*(volatile unsigned int *)(address))

// DUART
void duart_putc(char c);
char duart_getc(void);

#endif
