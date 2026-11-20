#ifndef SYN86_OPL_H
#define SYN86_OPL_H
#include <stddef.h>
#include <stdint.h>
typedef struct syn_opl syn_opl;
syn_opl *syn_opl_create(void);
void syn_opl_destroy(syn_opl *);
void syn_opl_note(syn_opl *,unsigned semitone,int on);
void syn_opl_audio(syn_opl *,int16_t *dst,size_t frames);
#endif
