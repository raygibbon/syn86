#include "opl.h"
#include "imf.h"
#include <SDL3/SDL.h>
#include <stdio.h>
static int key_note(SDL_Keycode k){
    switch(k){
        case SDLK_Z:return 0;case SDLK_S:return 1;case SDLK_X:return 2;
        case SDLK_D:return 3;case SDLK_C:return 4;case SDLK_V:return 5;
        case SDLK_G:return 6;case SDLK_B:return 7;case SDLK_H:return 8;
        case SDLK_N:return 9;case SDLK_J:return 10;case SDLK_M:return 11;
        default:return -1;
    }
}
int main(int argc,char **argv){
    if(argc==2){
        if(!imf_demo(argv[1])){fprintf(stderr,"Cannot write IMF: %s\n",argv[1]);return 1;}
        printf("Wrote original IMF: %s\n",argv[1]);return 0;
    }
    if(argc!=1){fprintf(stderr,"Usage: syn86 [output.imf]\n");return 1;}
    if(!SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO)){fprintf(stderr,"%s\n",SDL_GetError());return 1;}
    SDL_Window *window=SDL_CreateWindow("SYN86 - Z S X D C V G B H N J M",760,240,0);
    syn_opl *s=syn_opl_create();
    SDL_AudioSpec spec={SDL_AUDIO_S16,2,48000};
    SDL_AudioStream *stream=SDL_OpenAudioDeviceStream(SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK,&spec,NULL,NULL);
    if(!window||!s||!stream){fprintf(stderr,"SYN86 startup: %s\n",SDL_GetError());goto cleanup;}
    if(!SDL_ResumeAudioStreamDevice(stream)){fprintf(stderr,"Audio: %s\n",SDL_GetError());goto cleanup;}
    int playing=-1,active=1;
    while(active){
        SDL_Event e;
        while(SDL_PollEvent(&e)){
            if(e.type==SDL_EVENT_QUIT)active=0;
            if(e.type==SDL_EVENT_KEY_DOWN&&!e.key.repeat){
                if(e.key.key==SDLK_ESCAPE)active=0;
                int n=key_note(e.key.key);
                if(n>=0){playing=n;syn_opl_note(s,(unsigned)n,1);}
            }
            if(e.type==SDL_EVENT_KEY_UP){
                int n=key_note(e.key.key);
                if(n>=0&&n==playing){syn_opl_note(s,0,0);playing=-1;}
            }
        }
        int queued=SDL_GetAudioStreamQueued(stream);
        if(queued<0){fprintf(stderr,"Audio queue: %s\n",SDL_GetError());break;}
        for(int blocks=0;queued<48000*4/10&&blocks<16;blocks++){
            int16_t pcm[384*2];syn_opl_audio(s,pcm,384);
            if(!SDL_PutAudioStreamData(stream,pcm,(int)sizeof(pcm))){active=0;break;}
            queued=SDL_GetAudioStreamQueued(stream);
            if(queued<0){active=0;break;}
        }
        SDL_Delay(5);
    }
cleanup:
    if(stream)SDL_DestroyAudioStream(stream);
    syn_opl_destroy(s);
    if(window)SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
