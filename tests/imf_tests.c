#include "imf.h"
#include <assert.h>
#include <stdio.h>
int main(void){
    FILE *f=tmpfile();assert(f);
    const imf_event e[]={{0x20,0x01,0},{0xa0,0x57,700}};
    assert(imf_write(f,e,2));assert(ftell(f)==10);rewind(f);
    const unsigned char expected[]={8,0,0x20,1,0,0,0xa0,0x57,188,2};
    for(size_t i=0;i<sizeof(expected);i++)assert(fgetc(f)==expected[i]);
    assert(fgetc(f)==EOF);fclose(f);
    assert(!imf_write(NULL,e,2));assert(!imf_write(stdout,NULL,1));
    puts("SYN86 IMF tests passed");return 0;
}
