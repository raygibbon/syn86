#ifndef SYN86_IMF_H
#define SYN86_IMF_H
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
typedef struct { uint8_t reg, value; uint16_t delay; } imf_event;
int imf_write(FILE *out, const imf_event *events, size_t count);
int imf_demo(const char *path);
#endif
