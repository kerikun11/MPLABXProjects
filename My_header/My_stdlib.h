/* 
 * File:   My_stdlib.h
 * Author: kerikun11
 *
 * Created on 2015/07/18, 16:46
 */

#ifndef MY_STDLIB_H
#define	MY_STDLIB_H

void my_utoa(char *str, uint16_t value, uint8_t digits) {
    uint16_t v;
    uint8_t d;
    while (digits--) {
        v = value;
        d = digits;
        while (d--) {
            v /= 10;
        }
        v %= 10;
        *str++ = '0' + v;
    }
    *str = '\0';
}

void my_utoa32(char *str, uint32_t value, uint8_t digits) {
    uint32_t v;
    uint8_t d;
    while (digits--) {
        v = (uint32_t) value;
        d = digits;
        while (d--) {
            v /= 10;
        }
        v %= 10;
        *str++ = '0' + v;
    }
    *str = '\0';
}

uint16_t my_atoi(const char *str) {
    uint16_t ret = 0;
    while (*str) {
        if (*str >= '0' && *str <= '9') {
            ret *= 10;
            ret += *str - '0';
        }
        str++;
    }
    return ret;
}

int8_t my_strcmp(const char *str1, const char*str2) {
    while (*str1 && *str2) {
        if (*str1 != *str2)return (*str1 - *str2);
        str1++;
        str2++;
    }
    return (*str1 - *str2);
}

#endif	/* MY_STDLIB_H */

