/*
  Uzhix Project

  (c) 2018 MrOnlineCoder (Nikita Kogut)
  github.com/MrOnlineCoder

  See license in LICENSE file
*/

#include <uzhix/drivers/cmos.h>
#include <uzhix/io.h>

unsigned char cmos_get_register(int reg) {
  outb(CMOS_CONTROL, reg);
  return inb(CMOS_DATA);
}

int cmos_is_rtc_binary() {
  return cmos_get_register(CMOS_STATUS_B) & 0x04;
}

void cmos_get_time(cmos_time* ts) {
  ts->seconds = cmos_get_register(0x00);
  ts->minutes = cmos_get_register(0x02);
  ts->hours = cmos_get_register(0x04);
  ts->weekday = cmos_get_register(0x06);
  ts->dayofmonth = cmos_get_register(0x07);
  ts->month = cmos_get_register(0x08);
  ts->year = cmos_get_register(0x09);

  //if 2nd bit is not set in CMOS status register B, then time is in BCD format
  //which must converted to binary one
  if (!cmos_is_rtc_binary()) {
    ts->year = BCD_TO_BIN(ts->year);
    ts->month = BCD_TO_BIN(ts->month);
    ts->dayofmonth = BCD_TO_BIN(ts->dayofmonth);
    ts->weekday = BCD_TO_BIN(ts->weekday);
    ts->hours = BCD_TO_BIN(ts->hours);
    ts->minutes = BCD_TO_BIN(ts->minutes);
    ts->seconds = BCD_TO_BIN(ts->seconds);
  }
}
