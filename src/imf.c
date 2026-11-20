#include "imf.h"
static int put16(FILE *f,unsigned n){
    return fputc((int)(n&255U),f)!=EOF && fputc((int)((n>>8)&255U),f)!=EOF;
}
int imf_write(FILE *out,const imf_event *events,size_t count){
    if(!out||(!events&&count)||count>16383U)return 0;
    if(!put16(out,(unsigned)(count*4U)))return 0;
    for(size_t i=0;i<count;i++){
        if(fputc(events[i].reg,out)==EOF||fputc(events[i].value,out)==EOF||!put16(out,events[i].delay))return 0;
    }
    return !ferror(out);
}
int imf_demo(const char *path){
    if(!path)return 0;
    /* Independently authored four-note sample, not music from Wolfenstein. */
    static const imf_event events[]={
        {0x01,0x20,0},{0x20,0x01,0},{0x23,0x01,0},
        {0x40,0x20,0},{0x43,0x00,0},{0x60,0xf2,0},
        {0x63,0xf3,0},{0x80,0x57,0},{0x83,0x37,0},{0xc0,0x01,0},
        {0xa0,0x57,0},{0xb0,0x31,175},{0xb0,0x11,20},
        {0xa0,0x98,0},{0xb0,0x31,175},{0xb0,0x11,20},
        {0xa0,0xd6,0},{0xb0,0x31,175},{0xb0,0x11,20},
        {0xa0,0x57,0},{0xb0,0x31,280},{0xb0,0x11,35}
    };
    FILE *f=fopen(path,"wb");if(!f)return 0;
    int ok=imf_write(f,events,sizeof(events)/sizeof(events[0]));
    if(fclose(f))ok=0;
    return ok;
}
