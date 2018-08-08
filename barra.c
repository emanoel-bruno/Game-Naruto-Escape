#include <SOIL/SOIL.h>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include"barra.h"
barra calcula_dimencoes(barra b1,int tempo_atual,int tempo_max,int largura_tela,int altura_tela){
    float porcentagem_do_tempo;
    porcentagem_do_tempo=(float)tempo_atual/tempo_max;
    b1.largura=porcentagem_do_tempo*largura_tela;
    b1.altura=20;
    b1.x=-1*largura_tela/2;
    b1.y=-1*altura_tela/2;
    return b1;
}
void desenha_barra_comum(float x,float y,float altura,float largura){
    float i;
    glBegin(GL_POLYGON);
        glVertex3f(x,y, 0.0);
        glVertex3f(x,y+altura, 0.0);
        glVertex3f(x+largura,y+altura, 0.0);
        glVertex3f(x+largura,y, 0.0);
    glEnd();
}
void desenha_barra(barra b1,int largura_tela,int altura_tela){
    int i;
    int numero_de_divisoes=10;
    glColor3f(0,1,0);
    glColor3f(0,1,0);
    glBegin(GL_POLYGON);
        glVertex3f(b1.x,b1.y, 0.0);
        glVertex3f(b1.x,b1.y+b1.altura, 0.0);
        glVertex3f(b1.x+b1.largura,b1.y+b1.altura, 0.0);
        glVertex3f(b1.x+b1.largura,b1.y, 0.0);
    glEnd();
    glColor3f(0.3,0,1);
    float porcentagem_por_intervalo;
    porcentagem_por_intervalo=(float)1/numero_de_divisoes;
    int numero_de_vezes_que_ja_foi=1;
    int x_da_linha;
    for(i=1;i<numero_de_divisoes;i++){
        x_da_linha=numero_de_vezes_que_ja_foi*porcentagem_por_intervalo*largura_tela;
        float x_da_barra2=b1.x+x_da_linha;
        float y_da_barra2=b1.y;
        desenha_barra_comum(x_da_barra2,y_da_barra2,b1.altura,2);
        numero_de_vezes_que_ja_foi++;
        }
    desenha_barra_comum(b1.x,b1.y,5,largura_tela);
    desenha_barra_comum(b1.x,b1.y+b1.altura,5,largura_tela);
    desenha_barra_comum(b1.x,b1.y+altura_tela-5,5,largura_tela);
    desenha_barra_comum(b1.x,b1.y,altura_tela,5);
    desenha_barra_comum(b1.x-5+largura_tela,b1.y,altura_tela,5);
    }
//largura da moldura e 5;

