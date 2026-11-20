#include "opl.h"
#include "../third_party/emu8950/emu8950.h"
#include <stdlib.h>
struct syn_opl{
    OPL *chip;
    uint64_t phase;
    int32_t previous[2],next[2];
    unsigned rate;
};
syn_opl *syn_opl_create(void){
    syn_opl *s=calloc(1,sizeof(*s));if(!s)return NULL;
    s->chip=OPL_new(3579545,49716);
    if(!s->chip){free(s);return NULL;}
    s->rate=48000;s->phase=s->rate;
    OPL_setChipType(s->chip,2);OPL_reset(s->chip);
    static const struct{unsigned reg,val;} init[]={
        {0x01,0x20},{0x20,0x01},{0x23,0x01},
        {0x40,0x20},{0x43,0x00},{0x60,0xf2},{0x63,0xf3},
        {0x80,0x57},{0x83,0x37},{0xc0,0x01}
    };
    for(size_t i=0;i<sizeof(init)/sizeof(init[0]);++i)
        OPL_writeReg(s->chip,init[i].reg,(uint8_t)init[i].val);
    return s;
}
void syn_opl_destroy(syn_opl *s){if(s){OPL_delete(s->chip);free(s);}}
void syn_opl_note(syn_opl *s,unsigned semitone,int on){
    if(!s)return;
    if(!on){OPL_writeReg(s->chip,0xb0,0x11);return;}
    static const uint16_t fnum[12]={343,363,385,408,432,458,485,514,544,577,611,647};
    unsigned n=semitone%12U;
    OPL_writeReg(s->chip,0xa0,(uint8_t)(fnum[n]&255U));
    OPL_writeReg(s->chip,0xb0,(uint8_t)(0x20U|(4U<<2)|(fnum[n]>>8)));
}
void syn_opl_audio(syn_opl *s,int16_t *dst,size_t frames){
    if(!dst)return;
    for(size_t i=0;i<frames;i++){
        if(!s){dst[i*2]=dst[i*2+1]=0;continue;}
        while(s->phase>=s->rate){
            s->phase-=s->rate;
            s->previous[0]=s->next[0];s->previous[1]=s->next[1];
            OPL_calcStereo(s->chip,s->next);
        }
        for(unsigned ch=0;ch<2;ch++){
            int64_t v=(int64_t)s->previous[ch]+
              ((int64_t)s->next[ch]-s->previous[ch])*(int64_t)s->phase/s->rate;
            v*=3;if(v>32767)v=32767;if(v< -32768)v=-32768;
            dst[2*i+ch]=(int16_t)v;
        }
        s->phase+=49716;
    }
}
