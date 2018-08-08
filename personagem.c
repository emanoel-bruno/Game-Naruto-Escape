#include"personagem.h"
void andou_direita(personagem *p1,int direita){
    if(direita==1){
        if((*p1).x<=184)
            (*p1).x+=3;
    }
}
void andou_esquerda(personagem *p1,int esquerda){
    if(esquerda==1){
        if((*p1).x>=-204)
            (*p1).x=(*p1).x-3;
    }
}
void impulsu(personagem *p1,int direita,int esquerda){
    if(direita==1){
        if((*p1).x<=147)
            (*p1).x+=40;
    }
    if(esquerda==1){
        if((*p1).x>=-161)
            (*p1).x=(*p1).x-40;
    }
}
