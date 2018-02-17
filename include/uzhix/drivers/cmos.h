/*
  Uzhix Project

  (c) 2018 MrOnlineCoder (Nikita Kogut)
  github.com/MrOnlineCoder

  See license in LICENSE file
*/

#ifndef _CMOS_DRIVER_H
#define _CMOS_DRIVER_H

#define CMOS_CONTROL 0x70
#define CMOS_DATA 0x71

#define CMOS_STATUS_B 0x0B

#define BCD_TO_BIN(bcd) ((bcd / 16) * 10) + (bcd & 0xf)

typedef struct {
  unsigned char seconds;
  unsigned char minutes;
  unsigned char hours;
  unsigned char weekday;
  unsigned char dayofmonth;
  unsigned char month;
  unsigned char year;
} cmos_time;

unsigned char cmos_get_register(int reg);
void cmos_get_time(cmos_time* ts);
int cmos_is_rtc_binary();

#endif
