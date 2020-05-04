#include "rtc.h"
#include "utils.h"
#include <minix/sysutil.h>

static uint8_t hour   = 0;
static uint8_t minute = 0;
static uint8_t second = 0;

static int rtc_hook_id = RTC_HOOK_ID;

static uint32_t rtc_counter = 0;

uint8_t rtc_get_hour  () {return hour;}
uint8_t rtc_get_minute() {return minute;}
uint8_t rtc_get_second() {return second;}



bool rtc_ih() {
    rtc_counter++;
    uint8_t reg_c = rtc_read_reg(RTC_REGISTER_C);

    if ((reg_c & RTC_REG_C_UF) != 0) {
        hour   = bcd_to_decimal(rtc_read_reg(RTC_HOURS));
        minute = bcd_to_decimal(rtc_read_reg(RTC_MINUTES));
        second = bcd_to_decimal(rtc_read_reg(RTC_SECONDS));
    }

    if ((reg_c & RTC_REG_C_AF) != 0) {
        return true;
    } else {
        return false;
    }
}

int rtc_ih_subscribe() {
    rtc_hook_id = RTC_HOOK_ID;
    return sys_irqsetpolicy(RTC_IRQ, IRQ_REENABLE, &rtc_hook_id);
}

int rtc_ih_unsubscribe() {
    return sys_irqrmpolicy(&rtc_hook_id);
}

int rtc_ih_disable() {
    return sys_irqdisable(&rtc_hook_id);
}

int rtc_ih_enable() {
    return sys_irqenable(&rtc_hook_id);
}

void    rtc_write_reg(uint8_t reg, uint8_t data){
    sys_outb(RTC_ADDR_REG, reg);
    sys_outb(RTC_DATA_REG, data);
}

uint8_t rtc_read_reg(uint8_t reg) {
    sys_outb(RTC_ADDR_REG, reg);
    uint8_t res;
    util_sys_inb(RTC_DATA_REG, &res);
    return res;
}
