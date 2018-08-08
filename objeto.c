#include <SOIL/SOIL.h>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include"objeto.h"
#include<time.h>
int numero_aleatorio(int limite){
        return rand()%limite;
}
void gera_cordendas_dos_objetos(objeto *o1,int velocidade,int tamanho,float fator_de_dificuldade){
    //getchar();
    int flag=5;
    int flag2=3;
    int fps =50;
    int numero_frames_para_aumentar_velocidade;
    int inicio_terreno=-130;
    float diferenca_entre_chao_e_proxima_posicao_objeto;
    float proxima_posicao;
    if((*o1).status!=flag){
        int a=numero_aleatorio(401);
        (*o1).x=-205+a;
        int b=numero_aleatorio(96);
        (*o1).y=b+150;
        (*o1).numero_frames=1;
        (*o1).aceleracao=4;
        (*o1).velocidade=velocidade;
        (*o1).numero_frames=1;
        (*o1).status=flag;
        (*o1).tamanho=tamanho;
        (*o1).tipo=numero_aleatorio(2);
        //getchar();
    }
    proxima_posicao=(*o1).y-(*o1).velocidade;
    numero_frames_para_aumentar_velocidade=fps/fator_de_dificuldade;
    if((*o1).status==flag){
        if((*o1).numero_frames%numero_frames_para_aumentar_velocidade==0)
            (*o1).velocidade+=(*o1).aceleracao;
        //printf("3_x,y=(%f,%f) status=%d velocidade=%d,proxima_posicao=%f diferença proxima posicao e o terreno=%f\n",(*o1).x,(*o1).y,(*o1).status,(*o1).velocidade,proxima_posicao,diferenca_entre_chao_e_proxima_posicao_objeto);
        if((*o1).y==inicio_terreno){
            (*o1).status=flag2;
            //printf("4_x,y=(%f,%f) status=%d velocidade=%d,proxima_posicao=%f diferença proxima posicao e o terreno=%f\n",(*o1).x,(*o1).y,(*o1).status,(*o1).velocidade,proxima_posicao,diferenca_entre_chao_e_proxima_posicao_objeto);
        }
        else if(proxima_posicao>inicio_terreno){
            (*o1).y=proxima_posicao;
            //printf("5_x,y=(%f,%f) status=%d velocidade=%d,proxima_posicao=%f diferença proxima posicao e o terreno=%f\n",(*o1).x,(*o1).y,(*o1).status,(*o1).velocidade,proxima_posicao,diferenca_entre_chao_e_proxima_posicao_objeto);
        }
        else if(proxima_posicao<=inicio_terreno){
            diferenca_entre_chao_e_proxima_posicao_objeto=abs(proxima_posicao-inicio_terreno);
            (*o1).y=proxima_posicao+diferenca_entre_chao_e_proxima_posicao_objeto;
            //printf("6_x,y=(%f,%f) status=%d velocidade=%d,proxima_posicao=%f diferença proxima posicao e o terreno=%f\n",(*o1).x,(*o1).y,(*o1).status,(*o1).velocidade,proxima_posicao,diferenca_entre_chao_e_proxima_posicao_objeto);
        }
    }
 }
void gera_cordendas_dos_passaros(objeto *o1,int velocidade,int tamanho){
        int a=numero_aleatorio(20);
        if(rand()%2==1)
            (*o1).x=-195+a;
        if(rand()%2==0)
            (*o1).x=195-a;
        int b=numero_aleatorio(146);
        (*o1).y=b+40;
        (*o1).numero_frames=1;
        (*o1).aceleracao=4;
        (*o1).velocidade=velocidade;
        if(rand()%2==1)
            (*o1).status=1;
        if(rand()%2==0)
            (*o1).status=0;
        (*o1).status=0;
        (*o1).tamanho=tamanho;
        (*o1).tipo=0;


        //status 1 direita
        //status 0esquerda
}
void andou_direita_p(objeto *p1){
    if((*p1).status==1){
        if((*p1).x<=184){
            (*p1).x+=3;
        }
        if((*p1).x>184){
            (*p1).status=0;
        }
    }
}
void andou_esquerda_p(objeto *p1){
    if((*p1).status==0){
        if((*p1).x>=-204)
            (*p1).x=(*p1).x-3;
        if((*p1).x<-204)
            (*p1).status=1;
    }
}


