#include <SOIL/SOIL.h>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <curses.h>
#include"barra.h"
#include"personagem.h"
#include"objeto.h"
#include"botao.h"
#include"vetor.h"

int LARGURA_TELA=420;
int modo=1;
int telaM=0;
int tipo_personagem=0;
int ALTURA_TELA=420;
int FPS=50;
int INTERVALO_ENTRE_AS_FRAMES;
int TEMPO=0;
int TEMPO_MAX=100;
int CONTADOR_FRAMES=0;
int NUMERO_DE_OBSTACULOS=5;
int anda_direita=0;
int anda_esquerda=0;
int tamanho_objeto=10;
int contador_de_vitoria=0;
int velocidade_objeto=5;
int tempo_para_aumentar_dificuldade;
float fator_de_dificuldade=1;
int regulador_do_tempo_de_dificuldade=10;
int largura_moldura=5;
float xmin_menu =-210;
float xmax_menu =210;
int contador_impulso=0;
float ymin_menu =-210;
float ymax_menu =210;
float incrementoAngulo;
int pausado=0;
float anguloDeRotacao=30;
int NUMERO_PASSAROS=10;
int w1;
int h1;
int flag=0;

personagem p1;
barra b1;

GLuint texturaCeu;
GLuint texturaSolo;
GLuint texturaBotao1;
GLuint texturaBotao2;
GLuint texturaBotao3;
GLuint texturaBotao4;
GLuint texturaBotao5;
GLuint texturaBotao6;
GLuint texturaBotao7;
GLuint texturaBixo;
GLuint texturaTela;
GLuint texturaTelap;
GLuint texturaTela2;
GLuint texturaTela3;
GLuint texturaTela4;
GLuint texturaTelaM1;
GLuint texturaTelaM2;
GLuint texturaTelaM3;
GLuint texturaBixoAndano;
GLuint texturaBixo2Andano;
GLuint texturaCoracao;
GLuint texturaBixo2;
GLuint texturaShuriken;
GLuint texturaShuriken2;
GLuint texturaShuriken11;
GLuint texturaShuriken22;
GLuint texturaPassaros;

float porcentagemX;
float porcentagemY;

objeto o[50];
objeto bird[50];

botao botao1;
botao botao2;
botao botao3;
botao botao4;

v mouse;
v mouse2;

void gera_posisoes_birds(int numero_de_birds){
    int i=0;
    for(i=0;i<numero_de_birds;i++){
        gera_cordendas_dos_passaros(&bird[i],velocidade_objeto,30);
    }
}

v converte_cordenadas_mouse(v mouse){
    porcentagemX=mouse.x/w1;
    porcentagemY=mouse.y/h1;
    float parte_andadax,parte_andaday;
    float meia_largura_tela,meia_altura_tela;
    meia_largura_tela=LARGURA_TELA/2;
    parte_andadax=porcentagemX*LARGURA_TELA;
    meia_altura_tela=ALTURA_TELA/2;
    parte_andaday=porcentagemY*LARGURA_TELA;
    mouse.x=parte_andadax-meia_largura_tela;
    mouse.y=meia_altura_tela-parte_andaday;
    return mouse;
}

void click_mouse(int butom,int state,int x, int y){
    mouse.x=x;
    mouse.y=y;
    mouse.status=state;
    mouse=converte_cordenadas_mouse(mouse);
    if(modo==1){
        if(mouse.x<=botao1.xmax && mouse.x>=botao1.xmin){
            if(mouse.y<=botao1.ymax && mouse.y>=botao1.ymin){
                modo=5;
            }
        }
        if(mouse.x<=botao2.xmax && mouse.x>=botao2.xmin){
            if(mouse.y<=botao2.ymax && mouse.y>=botao2.ymin){
                modo=2;
            }
        }
        if(mouse.x<=botao3.xmax && mouse.x>=botao3.xmin){
            if(mouse.y<=botao3.ymax && mouse.y>=botao3.ymin){
                exit(0);
            }
        }
    }
    if(modo==2){
        if(mouse.x<=botao4.xmax && mouse.x>=botao4.xmin){
            if(mouse.y<=botao4.ymax && mouse.y>=botao4.ymin){
                modo=1;
            }
        }
    }
    if(modo==4){
        if(mouse.x<=botao1.xmax && mouse.x>=botao1.xmin){
            if(mouse.y<=botao1.ymax && mouse.y>=botao1.ymin){
                modo=0;
            }
        }
        if(mouse.x<=botao2.xmax && mouse.x>=botao2.xmin){
            if(mouse.y<=botao2.ymax && mouse.y>=botao2.ymin){
                exit(0);
            }
        }
    }
    if(modo==5){
        if(mouse.x<=botao2.xmax && mouse.x>=botao2.xmin){
            if(mouse.y<=botao2.ymax && mouse.y>=botao2.ymin){
                modo=0;
            }
        }
        if(mouse.x<=botao3.xmax && mouse.x>=botao3.xmin){
            if(mouse.y<=botao3.ymax && mouse.y>=botao3.ymin){
                tipo_personagem=1;
                modo=0;
            }
        }
    }
    if(modo==3){
        if(mouse.x<=botao1.xmax && mouse.x>=botao1.xmin){
            if(mouse.y<=botao1.ymax && mouse.y>=botao1.ymin){
                exit(0);
            }
        }
    }
}
void mouse_motion(int x, int y){
    mouse2.x=x;
    mouse2.y=y;
    mouse=converte_cordenadas_mouse(mouse2);
    if(modo==5){
        if(mouse.x<=botao2.xmax && mouse.x>=botao2.xmin){
            if(mouse.y<=botao2.ymax && mouse.y>=botao2.ymin){
                telaM=1;
            }
        }
        if(mouse.x<=botao3.xmax && mouse.x>=botao3.xmin){
            if(mouse.y<=botao3.ymax && mouse.y>=botao3.ymin){
               telaM=2;
            }
        }
        if(!(mouse.x<=botao2.xmax && mouse.x>=botao2.xmin && mouse.y<=botao2.ymax && mouse.y>=botao2.ymin) &&
             !(mouse.x<=botao3.xmax && mouse.x>=botao3.xmin && mouse.y<=botao3.ymax && mouse.y>=botao3.ymin )){
                telaM=0;
             }
    }
}
void faz_quadrado(float x,float y,int tamanho){
    glBegin(GL_POLYGON);
        glVertex3f(x,y, 0.0);
        glVertex3f(x,y+tamanho, 0.0);
        glVertex3f(x+tamanho,y+tamanho, 0.0);
        glVertex3f(x+tamanho,y, 0.0);
    glEnd();
}
void desenha_menu(){
    glClear(GL_COLOR_BUFFER_BIT);
    glColor4f(1,1,1,1);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texturaTela);
    glBegin(GL_QUADS);
        glTexCoord2f(0, 0); glVertex3f(xmin_menu,ymin_menu,  0);
        glTexCoord2f(1, 0); glVertex3f(xmax_menu,ymin_menu,  0);
        glTexCoord2f(1, 1); glVertex3f(xmax_menu,ymax_menu,  0);
        glTexCoord2f(0, 1); glVertex3f(xmin_menu,ymax_menu,  0);
    glEnd();
    glBindTexture(GL_TEXTURE_2D, texturaBotao1);
    glBegin(GL_QUADS);
        glTexCoord2f(0, 0); glVertex3f(botao1.xmin,botao1.ymin,  0);
        glTexCoord2f(1, 0); glVertex3f(botao1.xmax,botao1.ymin,  0);
        glTexCoord2f(1, 1); glVertex3f(botao1.xmax,botao1.ymax,  0);
        glTexCoord2f(0, 1); glVertex3f(botao1.xmin,botao1.ymax,  0);
    glEnd();
    glBindTexture(GL_TEXTURE_2D, texturaBotao2);
    glBegin(GL_QUADS);
        glTexCoord2f(0, 0); glVertex3f(botao2.xmin,botao2.ymin,  0);
        glTexCoord2f(1, 0); glVertex3f(botao2.xmax,botao2.ymin,  0);
        glTexCoord2f(1, 1); glVertex3f(botao2.xmax,botao2.ymax,  0);
        glTexCoord2f(0, 1); glVertex3f(botao2.xmin,botao2.ymax,  0);
    glEnd();
    glBindTexture(GL_TEXTURE_2D, texturaBotao3);
    glBegin(GL_QUADS);
        glTexCoord2f(0, 0); glVertex3f(botao3.xmin,botao3.ymin,  0);
        glTexCoord2f(1, 0); glVertex3f(botao3.xmax,botao3.ymin,  0);
        glTexCoord2f(1, 1); glVertex3f(botao3.xmax,botao3.ymax,  0);
        glTexCoord2f(0, 1); glVertex3f(botao3.xmin,botao3.ymax,  0);
    glEnd();
    glDisable(GL_TEXTURE_2D);
    glutSwapBuffers();
}
void desenha_menu6(){
    glClear(GL_COLOR_BUFFER_BIT);
    glColor4f(1,1,1,1);
    glEnable(GL_TEXTURE_2D);
    if(telaM==0){
        glBindTexture(GL_TEXTURE_2D, texturaTelaM1);
        glBegin(GL_QUADS);
            glTexCoord2f(0, 0); glVertex3f(xmin_menu,ymin_menu,  0);
            glTexCoord2f(1, 0); glVertex3f(xmax_menu,ymin_menu,  0);
            glTexCoord2f(1, 1); glVertex3f(xmax_menu,ymax_menu,  0);
            glTexCoord2f(0, 1); glVertex3f(xmin_menu,ymax_menu,  0);
        glEnd();
    }
    if(telaM==1){
        glBindTexture(GL_TEXTURE_2D, texturaTelaM2);
        glBegin(GL_QUADS);
            glTexCoord2f(0, 0); glVertex3f(xmin_menu,ymin_menu,  0);
            glTexCoord2f(1, 0); glVertex3f(xmax_menu,ymin_menu,  0);
            glTexCoord2f(1, 1); glVertex3f(xmax_menu,ymax_menu,  0);
            glTexCoord2f(0, 1); glVertex3f(xmin_menu,ymax_menu,  0);
        glEnd();
    }
    if(telaM==2){
        glBindTexture(GL_TEXTURE_2D, texturaTelaM3);
        glBegin(GL_QUADS);
            glTexCoord2f(0, 0); glVertex3f(xmin_menu,ymin_menu,  0);
            glTexCoord2f(1, 0); glVertex3f(xmax_menu,ymin_menu,  0);
            glTexCoord2f(1, 1); glVertex3f(xmax_menu,ymax_menu,  0);
            glTexCoord2f(0, 1); glVertex3f(xmin_menu,ymax_menu,  0);
        glEnd();
    }
    glBindTexture(GL_TEXTURE_2D, texturaBotao6);
    glBegin(GL_QUADS);
        glTexCoord2f(0, 0); glVertex3f(botao2.xmin,botao2.ymin,  0);
        glTexCoord2f(1, 0); glVertex3f(botao2.xmax,botao2.ymin,  0);
        glTexCoord2f(1, 1); glVertex3f(botao2.xmax,botao2.ymax,  0);
        glTexCoord2f(0, 1); glVertex3f(botao2.xmin,botao2.ymax,  0);
    glEnd();
    glBindTexture(GL_TEXTURE_2D, texturaBotao7);
    glBegin(GL_QUADS);
        glTexCoord2f(0, 0); glVertex3f(botao3.xmin,botao3.ymin,  0);
        glTexCoord2f(1, 0); glVertex3f(botao3.xmax,botao3.ymin,  0);
        glTexCoord2f(1, 1); glVertex3f(botao3.xmax,botao3.ymax,  0);
        glTexCoord2f(0, 1); glVertex3f(botao3.xmin,botao3.ymax,  0);
    glEnd();
    glDisable(GL_TEXTURE_2D);
    glutSwapBuffers();
}
void desenha_menu5(){
    glClear(GL_COLOR_BUFFER_BIT);
    glColor4f(1,1,1,1);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texturaTela4);
    glBegin(GL_QUADS);
        glTexCoord2f(0, 0); glVertex3f(xmin_menu,ymin_menu,  0);
        glTexCoord2f(1, 0); glVertex3f(xmax_menu,ymin_menu,  0);
        glTexCoord2f(1, 1); glVertex3f(xmax_menu,ymax_menu,  0);
        glTexCoord2f(0, 1); glVertex3f(xmin_menu,ymax_menu,  0);
    glEnd();
    glBindTexture(GL_TEXTURE_2D, texturaBotao5);
    glBegin(GL_QUADS);
        glTexCoord2f(0, 0); glVertex3f(botao1.xmin,botao1.ymin,  0);
        glTexCoord2f(1, 0); glVertex3f(botao1.xmax,botao1.ymin,  0);
        glTexCoord2f(1, 1); glVertex3f(botao1.xmax,botao1.ymax,  0);
        glTexCoord2f(0, 1); glVertex3f(botao1.xmin,botao1.ymax,  0);
    glEnd();
    glBindTexture(GL_TEXTURE_2D, texturaBotao3);
    glBegin(GL_QUADS);
        glTexCoord2f(0, 0); glVertex3f(botao2.xmin,botao2.ymin,  0);
        glTexCoord2f(1, 0); glVertex3f(botao2.xmax,botao2.ymin,  0);
        glTexCoord2f(1, 1); glVertex3f(botao2.xmax,botao2.ymax,  0);
        glTexCoord2f(0, 1); glVertex3f(botao2.xmin,botao2.ymax,  0);
    glEnd();
    glDisable(GL_TEXTURE_2D);
    glutSwapBuffers();
}
void desenha_menu2(){
    glClear(GL_COLOR_BUFFER_BIT);
    glColor4f(1,1,1,1);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texturaTela2);
    glBegin(GL_QUADS);
        glTexCoord2f(0, 0); glVertex3f(xmin_menu,ymin_menu,  0);
        glTexCoord2f(1, 0); glVertex3f(xmax_menu,ymin_menu,  0);
        glTexCoord2f(1, 1); glVertex3f(xmax_menu,ymax_menu,  0);
        glTexCoord2f(0, 1); glVertex3f(xmin_menu,ymax_menu,  0);
    glEnd();
    glBindTexture(GL_TEXTURE_2D, texturaBotao4);
    glBegin(GL_QUADS);
        glTexCoord2f(0, 0); glVertex3f(botao4.xmin,botao4.ymin,  0);
        glTexCoord2f(1, 0); glVertex3f(botao4.xmax,botao4.ymin,  0);
        glTexCoord2f(1, 1); glVertex3f(botao4.xmax,botao4.ymax,  0);
        glTexCoord2f(0, 1); glVertex3f(botao4.xmin,botao4.ymax,  0);
    glEnd();
    glDisable(GL_TEXTURE_2D);
    glutSwapBuffers();
}
void desenha_menu4(){
    glClear(GL_COLOR_BUFFER_BIT);
    glColor4f(1,1,1,1);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texturaTela3);
    glBegin(GL_QUADS);
        glTexCoord2f(0, 0); glVertex3f(xmin_menu,ymin_menu,  0);
        glTexCoord2f(1, 0); glVertex3f(xmax_menu,ymin_menu,  0);
        glTexCoord2f(1, 1); glVertex3f(xmax_menu,ymax_menu,  0);
        glTexCoord2f(0, 1); glVertex3f(xmin_menu,ymax_menu,  0);
    glEnd();
    glBindTexture(GL_TEXTURE_2D, texturaBotao3);
    glBegin(GL_QUADS);
        glTexCoord2f(0, 0); glVertex3f(botao1.xmin,botao1.ymin,  0);
        glTexCoord2f(1, 0); glVertex3f(botao1.xmax,botao1.ymin,  0);
        glTexCoord2f(1, 1); glVertex3f(botao1.xmax,botao1.ymax,  0);
        glTexCoord2f(0, 1); glVertex3f(botao1.xmin,botao1.ymax,  0);
    glEnd();
    glDisable(GL_TEXTURE_2D);
    glutSwapBuffers();
}
void desenha_menu3(){
    glClear(GL_COLOR_BUFFER_BIT);
    glColor4f(1,1,1,1);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texturaTelap);
    glBegin(GL_QUADS);
        glTexCoord2f(0, 0); glVertex3f(xmin_menu,ymin_menu,  0);
        glTexCoord2f(1, 0); glVertex3f(xmax_menu,ymin_menu,  0);
        glTexCoord2f(1, 1); glVertex3f(xmax_menu,ymax_menu,  0);
        glTexCoord2f(0, 1); glVertex3f(xmin_menu,ymax_menu,  0);
    glEnd();
    glDisable(GL_TEXTURE_2D);
    glutSwapBuffers();
}
void inicializa(void){
    glClearColor(1, 1, 1, 0);
    botao1.x=-190;
    botao1.y=20;
    botao1.altura=50;
    botao1.largura=80;
    botao1.xmin=botao1.x;
    botao1.xmax=botao1.x+botao1.largura;
    botao1.ymin=botao1.y;
    botao1.ymax=botao1.y+botao1.altura;
    botao2.x=-190;
    botao2.y=-50;
    botao2.altura=50;
    botao2.largura=80;
    botao2.xmin=botao2.x;
    botao2.xmax=botao2.x+botao2.largura;
    botao2.ymin=botao2.y;
    botao2.ymax=botao2.y+botao2.altura;
    botao3.x=-190;
    botao3.y=-120;
    botao3.altura=50;
    botao3.largura=80;
    botao3.xmin=botao3.x;
    botao3.xmax=botao3.x+botao3.largura;
    botao3.ymin=botao3.y;
    botao3.ymax=botao3.y+botao3.altura;
    botao4.x=-190;
    botao4.y=-170;
    botao4.altura=50;
    botao4.largura=80;
    botao4.xmin=botao4.x;
    botao4.xmax=botao4.x+botao4.largura;
    botao4.ymin=botao4.y;
    botao4.ymax=botao4.y+botao4.altura;

}

void loadTexture(GLuint* texture, char* s){
    *texture = SOIL_load_OGL_texture(
        s,
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
		SOIL_FLAG_INVERT_Y
	);
    glEnable( GL_BLEND );
    glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
}

void init(void){
    glClearColor (1, 1, 1, 0);
    gera_posisoes_birds(NUMERO_PASSAROS);

    loadTexture(&texturaCeu, "img/ceu.png");
    loadTexture(&texturaTela, "img/fundo_inicio.png");
    loadTexture(&texturaTelap, "img/fundo_iniciop.png");
    loadTexture(&texturaTela3, "img/dead.png");
    loadTexture(&texturaTela4, "img/venceu.png");
    loadTexture(&texturaSolo, "img/solo.png");
    loadTexture(&texturaBixo, "img/naruto_inicial2.png");
    loadTexture(&texturaBixo2, "img/super_naruto.png");
    loadTexture(&texturaBixoAndano, "img/naruto_andano.png");
    loadTexture(&texturaBixo2Andano, "img/naruto_andano2.png");
    loadTexture(&texturaCoracao, "img/coracao.png");
    loadTexture(&texturaShuriken, "img/shuriken1.png");
    loadTexture(&texturaShuriken2, "img/shuriken2.png");
    loadTexture(&texturaShuriken11, "img/shuriken1.2.png");
    loadTexture(&texturaShuriken22, "img/shuriken2.2.png");
    loadTexture(&texturaPassaros, "img/birds.png");
    loadTexture(&texturaBotao1, "img/botao1.png");
    loadTexture(&texturaBotao2, "img/botao3.png");
    loadTexture(&texturaBotao3, "img/botao2.png");
    loadTexture(&texturaBotao4, "img/botao4.png");
    loadTexture(&texturaBotao5, "img/botao5.png");
    loadTexture(&texturaBotao6, "img/botao6.png");
    loadTexture(&texturaBotao7, "img/botao7.png");
    loadTexture(&texturaTela2, "img/fundo_inicio22.png");
    loadTexture(&texturaTelaM1, "img/tela_fundoM0.png");
    loadTexture(&texturaTelaM2, "img/tela_fundoM1.png");
    loadTexture(&texturaTelaM3, "img/tela_fundoM2.png");
}

void inicializa_personagem(){
    p1.x=-3;
    p1.y=-130;
    p1.numero_de_vidas=12;
    p1.numero_frames=1;
    p1.status=1;
    p1.movimento=0;
    p1.tempo=0;
    p1.x_minimo=p1.x;
    p1.largura=20;
    p1.comprimento=30;
    p1.diferenca_altura_largura=p1.comprimento-p1.largura;
    p1.x_maximo=p1.x+p1.largura;
    p1.y_minimo=p1.y;
    p1.y_maximo=p1.y+p1.comprimento;
}

void inicializa_barra(){
    b1=calcula_dimencoes(b1,TEMPO,TEMPO_MAX,LARGURA_TELA,ALTURA_TELA);
}

void textura_personagem(){
    glColor4f(1,1,1,1);
    int contador=CONTADOR_FRAMES%2;
    if(tipo_personagem==0){
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, texturaBixo);
        if(CONTADOR_FRAMES%5==0){
            if(anda_direita==1 && anda_esquerda==0 || anda_direita==0 && anda_esquerda==1){
                p1.movimento++;
            }
            if(p1.movimento>6){
                p1.movimento=1;
            }
            if(anda_direita==0 && anda_esquerda==0 || anda_direita==1 && anda_esquerda==1){
                p1.movimento=0;
            }
        }
        if(p1.movimento==0){
            glBegin(GL_QUADS);
                glTexCoord2f(0, 0); glVertex3f(p1.x_minimo,p1.y_minimo,  0);
                glTexCoord2f(1, 0); glVertex3f(p1.x_maximo+p1.diferenca_altura_largura,p1.y_minimo,  0);
                glTexCoord2f(1, 1); glVertex3f(p1.x_maximo+p1.diferenca_altura_largura,p1.y_maximo,  0);
                glTexCoord2f(0, 1); glVertex3f(p1.x_minimo,p1.y_maximo,  0);
            glEnd();
        }
        glBindTexture(GL_TEXTURE_2D, texturaBixoAndano);
        if(anda_direita==1 && anda_esquerda==0){
            switch(p1.movimento)
            {
                case 1:
                    glBegin(GL_QUADS);
                        glTexCoord2f(0, 0); glVertex3f(p1.x_minimo,p1.y_minimo,  0);
                        glTexCoord2f(0.16, 0); glVertex3f(p1.x_maximo+p1.diferenca_altura_largura,p1.y_minimo,  0);
                        glTexCoord2f(0.16, 1); glVertex3f(p1.x_maximo+p1.diferenca_altura_largura,p1.y_maximo,  0);
                        glTexCoord2f(0, 1); glVertex3f(p1.x_minimo,p1.y_maximo,  0);
                    glEnd();
                    break;
                case 2:
                    glBegin(GL_QUADS);
                        glTexCoord2f(0.16, 0); glVertex3f(p1.x_minimo,p1.y_minimo,  0);
                        glTexCoord2f(0.33, 0); glVertex3f(p1.x_maximo+p1.diferenca_altura_largura,p1.y_minimo,  0);
                        glTexCoord2f(0.33, 1); glVertex3f(p1.x_maximo+p1.diferenca_altura_largura,p1.y_maximo,  0);
                        glTexCoord2f(0.16, 1); glVertex3f(p1.x_minimo,p1.y_maximo,  0);
                    glEnd();
                    break;
                case 3:
                    glBegin(GL_QUADS);
                        glTexCoord2f(0.33, 0); glVertex3f(p1.x_minimo,p1.y_minimo,  0);
                        glTexCoord2f(0.48, 0); glVertex3f(p1.x_maximo+p1.diferenca_altura_largura,p1.y_minimo,  0);
                        glTexCoord2f(0.48, 1); glVertex3f(p1.x_maximo+p1.diferenca_altura_largura,p1.y_maximo,  0);
                        glTexCoord2f(0.33, 1); glVertex3f(p1.x_minimo,p1.y_maximo,  0);
                    glEnd();
                    break;
                case 4:
                    glBegin(GL_QUADS);
                        glTexCoord2f(0.48, 0); glVertex3f(p1.x_minimo,p1.y_minimo,  0);
                        glTexCoord2f(0.64, 0); glVertex3f(p1.x_maximo+p1.diferenca_altura_largura,p1.y_minimo,  0);
                        glTexCoord2f(0.64, 1); glVertex3f(p1.x_maximo+p1.diferenca_altura_largura,p1.y_maximo,  0);
                        glTexCoord2f(0.48, 1); glVertex3f(p1.x_minimo,p1.y_maximo,  0);
                    glEnd();
                    break;
                case 5:
                    glBegin(GL_QUADS);
                        glTexCoord2f(0.64, 0); glVertex3f(p1.x_minimo,p1.y_minimo,  0);
                        glTexCoord2f(0.83, 0); glVertex3f(p1.x_maximo+p1.diferenca_altura_largura,p1.y_minimo,  0);
                        glTexCoord2f(0.83, 1); glVertex3f(p1.x_maximo+p1.diferenca_altura_largura,p1.y_maximo,  0);
                        glTexCoord2f(0.64, 1); glVertex3f(p1.x_minimo,p1.y_maximo,  0);
                    glEnd();
                    break;
                case 6:
                    glBegin(GL_QUADS);
                        glTexCoord2f(0.83, 0); glVertex3f(p1.x_minimo,p1.y_minimo,  0);
                        glTexCoord2f(1., 0); glVertex3f(p1.x_maximo+p1.diferenca_altura_largura,p1.y_minimo,  0);
                        glTexCoord2f(1, 1); glVertex3f(p1.x_maximo+p1.diferenca_altura_largura,p1.y_maximo,  0);
                        glTexCoord2f(0.83, 1); glVertex3f(p1.x_minimo,p1.y_maximo,  0);
                    glEnd();
                    break;
                default:
                    break;

            }
        }
        if(anda_direita==0 && anda_esquerda==1){
            switch(p1.movimento)
            {
                case 1:
                    glBegin(GL_QUADS);
                        glTexCoord2f(0, 0);    glVertex3f(p1.x_maximo+p1.diferenca_altura_largura,p1.y_minimo,  0);
                        glTexCoord2f(0.16, 0); glVertex3f(p1.x_minimo,p1.y_minimo,  0);
                        glTexCoord2f(0.16, 1); glVertex3f(p1.x_minimo,p1.y_maximo,  0);
                        glTexCoord2f(0, 1);    glVertex3f(p1.x_maximo+p1.diferenca_altura_largura,p1.y_maximo,  0);
                    glEnd();
                    break;
                case 2:
                    glBegin(GL_QUADS);
                        glTexCoord2f(0.16, 0); glVertex3f(p1.x_maximo+p1.diferenca_altura_largura,p1.y_minimo,  0);
                        glTexCoord2f(0.33, 0); glVertex3f(p1.x_minimo,p1.y_minimo,  0);
                        glTexCoord2f(0.33, 1); glVertex3f(p1.x_minimo,p1.y_maximo,  0);
                        glTexCoord2f(0.16, 1); glVertex3f(p1.x_maximo+p1.diferenca_altura_largura,p1.y_maximo,  0);
                    glEnd();
                    break;
                case 3:
                    glBegin(GL_QUADS);
                        glTexCoord2f(0.33, 0); glVertex3f(p1.x_maximo+p1.diferenca_altura_largura,p1.y_minimo,  0);
                        glTexCoord2f(0.48, 0); glVertex3f(p1.x_minimo,p1.y_minimo,  0);
                        glTexCoord2f(0.48, 1); glVertex3f(p1.x_minimo,p1.y_maximo,  0);
                        glTexCoord2f(0.33, 1); glVertex3f(p1.x_maximo+p1.diferenca_altura_largura,p1.y_maximo,  0);
                    glEnd();
                    break;
                case 4:
                    glBegin(GL_QUADS);
                        glTexCoord2f(0.48, 0); glVertex3f(p1.x_maximo+p1.diferenca_altura_largura,p1.y_minimo,  0);
                        glTexCoord2f(0.64, 0); glVertex3f(p1.x_minimo,p1.y_minimo,  0);
                        glTexCoord2f(0.64, 1); glVertex3f(p1.x_minimo,p1.y_maximo,  0);
                        glTexCoord2f(0.48, 1); glVertex3f(p1.x_maximo+p1.diferenca_altura_largura,p1.y_maximo,  0);
                    glEnd();
                    break;
                case 5:
                    glBegin(GL_QUADS);
                        glTexCoord2f(0.64, 0); glVertex3f(p1.x_maximo+p1.diferenca_altura_largura,p1.y_minimo,  0);
                        glTexCoord2f(0.83, 0); glVertex3f(p1.x_minimo,p1.y_minimo,  0);
                        glTexCoord2f(0.83, 1); glVertex3f(p1.x_minimo,p1.y_maximo,  0);
                        glTexCoord2f(0.64, 1); glVertex3f(p1.x_maximo+p1.diferenca_altura_largura,p1.y_maximo,  0);
                    glEnd();
                    break;
                case 6:
                    glBegin(GL_QUADS);
                        glTexCoord2f(0.83, 0); glVertex3f(p1.x_maximo+p1.diferenca_altura_largura,p1.y_minimo,  0);
                        glTexCoord2f(1., 0); glVertex3f(p1.x_minimo,p1.y_minimo,  0);
                        glTexCoord2f(1, 1); glVertex3f(p1.x_minimo,p1.y_maximo,  0);
                        glTexCoord2f(0.83, 1); glVertex3f(p1.x_maximo+p1.diferenca_altura_largura,p1.y_maximo,  0);
                    glEnd();
                    break;
                default:
                    break;

            }
        }
        glDisable(GL_TEXTURE_2D);
    }

    if(tipo_personagem==1){
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, texturaBixo2);
        if(CONTADOR_FRAMES%5==0){
            if(anda_direita==1 && anda_esquerda==0 || anda_direita==0 && anda_esquerda==1){
                p1.movimento++;
            }
            if(p1.movimento>6){
                p1.movimento=1;
            }
            if(anda_direita==0 && anda_esquerda==0 || anda_direita==1 && anda_esquerda==1){
                p1.movimento=0;
            }
        }
        if(p1.movimento==0){
            glBegin(GL_QUADS);
                        glTexCoord2f(0, 0); glVertex3f(p1.x_minimo,p1.y_minimo,  0);
                        glTexCoord2f(1, 0); glVertex3f(p1.x_maximo,p1.y_minimo,  0);
                        glTexCoord2f(1, 1); glVertex3f(p1.x_maximo,p1.y_maximo,  0);
                        glTexCoord2f(0, 1); glVertex3f(p1.x_minimo,p1.y_maximo,  0);
            glEnd();
        }
        glBindTexture(GL_TEXTURE_2D, texturaBixo2Andano);
        if(anda_direita==1 && anda_esquerda==0){
            switch(p1.movimento)
            {
                case 1:
                    glBegin(GL_QUADS);
                        glTexCoord2f(0, 0); glVertex3f(p1.x_minimo,p1.y_minimo,  0);
                        glTexCoord2f(0.14, 0); glVertex3f(p1.x_maximo+p1.diferenca_altura_largura,p1.y_minimo,  0);
                        glTexCoord2f(0.14, 1); glVertex3f(p1.x_maximo+p1.diferenca_altura_largura,p1.y_maximo,  0);
                        glTexCoord2f(0, 1); glVertex3f(p1.x_minimo,p1.y_maximo,  0);
                    glEnd();
                    break;
                case 2:
                    glBegin(GL_QUADS);
                        glTexCoord2f(0.14, 0); glVertex3f(p1.x_minimo,p1.y_minimo,  0);
                        glTexCoord2f(0.33, 0); glVertex3f(p1.x_maximo+p1.diferenca_altura_largura,p1.y_minimo,  0);
                        glTexCoord2f(0.33, 1); glVertex3f(p1.x_maximo+p1.diferenca_altura_largura,p1.y_maximo,  0);
                        glTexCoord2f(0.14, 1); glVertex3f(p1.x_minimo,p1.y_maximo,  0);
                    glEnd();
                    break;
                case 3:
                    glBegin(GL_QUADS);
                        glTexCoord2f(0.33, 0); glVertex3f(p1.x_minimo,p1.y_minimo,  0);
                        glTexCoord2f(0.48, 0); glVertex3f(p1.x_maximo+p1.diferenca_altura_largura,p1.y_minimo,  0);
                        glTexCoord2f(0.48, 1); glVertex3f(p1.x_maximo+p1.diferenca_altura_largura,p1.y_maximo,  0);
                        glTexCoord2f(0.33, 1); glVertex3f(p1.x_minimo,p1.y_maximo,  0);
                    glEnd();
                    break;
                case 4:
                    glBegin(GL_QUADS);
                        glTexCoord2f(0.48, 0); glVertex3f(p1.x_minimo,p1.y_minimo,  0);
                        glTexCoord2f(0.64, 0); glVertex3f(p1.x_maximo+p1.diferenca_altura_largura,p1.y_minimo,  0);
                        glTexCoord2f(0.64, 1); glVertex3f(p1.x_maximo+p1.diferenca_altura_largura,p1.y_maximo,  0);
                        glTexCoord2f(0.48, 1); glVertex3f(p1.x_minimo,p1.y_maximo,  0);
                    glEnd();
                    break;
                case 5:
                    glBegin(GL_QUADS);
                        glTexCoord2f(0.64, 0); glVertex3f(p1.x_minimo,p1.y_minimo,  0);
                        glTexCoord2f(0.83, 0); glVertex3f(p1.x_maximo+p1.diferenca_altura_largura,p1.y_minimo,  0);
                        glTexCoord2f(0.83, 1); glVertex3f(p1.x_maximo+p1.diferenca_altura_largura,p1.y_maximo,  0);
                        glTexCoord2f(0.64, 1); glVertex3f(p1.x_minimo,p1.y_maximo,  0);
                    glEnd();
                    break;
                case 6:
                    glBegin(GL_QUADS);
                        glTexCoord2f(0.83, 0); glVertex3f(p1.x_minimo,p1.y_minimo,  0);
                        glTexCoord2f(1., 0); glVertex3f(p1.x_maximo+p1.diferenca_altura_largura,p1.y_minimo,  0);
                        glTexCoord2f(1, 1); glVertex3f(p1.x_maximo+p1.diferenca_altura_largura,p1.y_maximo,  0);
                        glTexCoord2f(0.83, 1); glVertex3f(p1.x_minimo,p1.y_maximo,  0);
                    glEnd();
                    break;
                default:
                    break;

            }
        }
        if(anda_direita==0 && anda_esquerda==1){
            switch(p1.movimento)
            {
                case 1:
                    glBegin(GL_QUADS);
                        glTexCoord2f(0, 0);    glVertex3f(p1.x_maximo+p1.diferenca_altura_largura,p1.y_minimo,  0);
                        glTexCoord2f(0.14, 0); glVertex3f(p1.x_minimo,p1.y_minimo,  0);
                        glTexCoord2f(0.14, 1); glVertex3f(p1.x_minimo,p1.y_maximo,  0);
                        glTexCoord2f(0, 1);    glVertex3f(p1.x_maximo+p1.diferenca_altura_largura,p1.y_maximo,  0);
                    glEnd();
                    break;
                case 2:
                    glBegin(GL_QUADS);
                        glTexCoord2f(0.14, 0); glVertex3f(p1.x_maximo+p1.diferenca_altura_largura,p1.y_minimo,  0);
                        glTexCoord2f(0.33, 0); glVertex3f(p1.x_minimo,p1.y_minimo,  0);
                        glTexCoord2f(0.33, 1); glVertex3f(p1.x_minimo,p1.y_maximo,  0);
                        glTexCoord2f(0.14, 1); glVertex3f(p1.x_maximo+p1.diferenca_altura_largura,p1.y_maximo,  0);
                    glEnd();
                    break;
                case 3:
                    glBegin(GL_QUADS);
                        glTexCoord2f(0.33, 0); glVertex3f(p1.x_maximo+p1.diferenca_altura_largura,p1.y_minimo,  0);
                        glTexCoord2f(0.48, 0); glVertex3f(p1.x_minimo,p1.y_minimo,  0);
                        glTexCoord2f(0.48, 1); glVertex3f(p1.x_minimo,p1.y_maximo,  0);
                        glTexCoord2f(0.33, 1); glVertex3f(p1.x_maximo+p1.diferenca_altura_largura,p1.y_maximo,  0);
                    glEnd();
                    break;
                case 4:
                    glBegin(GL_QUADS);
                        glTexCoord2f(0.48, 0); glVertex3f(p1.x_maximo+p1.diferenca_altura_largura,p1.y_minimo,  0);
                        glTexCoord2f(0.64, 0); glVertex3f(p1.x_minimo,p1.y_minimo,  0);
                        glTexCoord2f(0.64, 1); glVertex3f(p1.x_minimo,p1.y_maximo,  0);
                        glTexCoord2f(0.48, 1); glVertex3f(p1.x_maximo+p1.diferenca_altura_largura,p1.y_maximo,  0);
                    glEnd();
                    break;
                case 5:
                    glBegin(GL_QUADS);
                        glTexCoord2f(0.64, 0); glVertex3f(p1.x_maximo+p1.diferenca_altura_largura,p1.y_minimo,  0);
                        glTexCoord2f(0.83, 0); glVertex3f(p1.x_minimo,p1.y_minimo,  0);
                        glTexCoord2f(0.83, 1); glVertex3f(p1.x_minimo,p1.y_maximo,  0);
                        glTexCoord2f(0.64, 1); glVertex3f(p1.x_maximo+p1.diferenca_altura_largura,p1.y_maximo,  0);
                    glEnd();
                    break;
                case 6:
                    glBegin(GL_QUADS);
                        glTexCoord2f(0.83, 0); glVertex3f(p1.x_maximo+p1.diferenca_altura_largura,p1.y_minimo,  0);
                        glTexCoord2f(1., 0); glVertex3f(p1.x_minimo,p1.y_minimo,  0);
                        glTexCoord2f(1, 1); glVertex3f(p1.x_minimo,p1.y_maximo,  0);
                        glTexCoord2f(0.83, 1); glVertex3f(p1.x_maximo+p1.diferenca_altura_largura,p1.y_maximo,  0);
                    glEnd();
                    break;
                default:
                    break;

            }
        }
        glDisable(GL_TEXTURE_2D);
    }
}

void textura_sprite_bird(objeto *bird){
    glColor4f(1,1,1,1);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texturaPassaros);
    if(CONTADOR_FRAMES%5==0){
        (*bird).tipo++;
        if((*bird).tipo>9){
            (*bird).tipo=0;
        }
        if((*bird).tipo<0){
            (*bird).tipo=0;
        }
    }
    if((*bird).status==1){
        switch((*bird).tipo)
        {
            case 0:
                glBegin(GL_QUADS);
                    glTexCoord2f(0, 0.5); glVertex3f((*bird).x_minimo,(*bird).y_minimo,  0);
                    glTexCoord2f(0.2,0.5); glVertex3f((*bird).x_maximo,(*bird).y_minimo,  0);
                    glTexCoord2f(0.2,1); glVertex3f((*bird).x_maximo,(*bird).y_maximo,  0);
                    glTexCoord2f(0, 1); glVertex3f((*bird).x_minimo,(*bird).y_maximo,  0);
                glEnd();
                break;
            case 1:
                glBegin(GL_QUADS);
                    glTexCoord2f(0.2, 0.5); glVertex3f((*bird).x_minimo,(*bird).y_minimo,  0);
                    glTexCoord2f(0.4, 0.5); glVertex3f((*bird).x_maximo,(*bird).y_minimo,  0);
                    glTexCoord2f(0.4, 1); glVertex3f((*bird).x_maximo,(*bird).y_maximo,  0);
                    glTexCoord2f(0.2, 1); glVertex3f((*bird).x_minimo,(*bird).y_maximo,  0);
                glEnd();
                break;
            case 2:
                glBegin(GL_QUADS);
                    glTexCoord2f(0.4, 0.5); glVertex3f((*bird).x_minimo,(*bird).y_minimo,  0);
                    glTexCoord2f(0.6, 0.5); glVertex3f((*bird).x_maximo,(*bird).y_minimo,  0);
                    glTexCoord2f(0.6, 1); glVertex3f((*bird).x_maximo,(*bird).y_maximo,  0);
                    glTexCoord2f(0.4, 1); glVertex3f((*bird).x_minimo,(*bird).y_maximo,  0);
                glEnd();
                break;
            case 3:
                glBegin(GL_QUADS);
                    glTexCoord2f(0.6, 0.5); glVertex3f((*bird).x_minimo,(*bird).y_minimo,  0);
                    glTexCoord2f(0.8, 0.5); glVertex3f((*bird).x_maximo,(*bird).y_minimo,  0);
                    glTexCoord2f(0.8, 1); glVertex3f((*bird).x_maximo,(*bird).y_maximo,  0);
                    glTexCoord2f(0.6, 1); glVertex3f((*bird).x_minimo,(*bird).y_maximo,  0);
                glEnd();
                break;
            case 4:
                glBegin(GL_QUADS);
                    glTexCoord2f(0.8, 0.5); glVertex3f((*bird).x_minimo,(*bird).y_minimo,  0);
                    glTexCoord2f(1, 0.5); glVertex3f((*bird).x_maximo,(*bird).y_minimo,  0);
                    glTexCoord2f(1, 1); glVertex3f((*bird).x_maximo,(*bird).y_maximo,  0);
                    glTexCoord2f(0.8, 1); glVertex3f((*bird).x_minimo,(*bird).y_maximo,  0);
                glEnd();
                break;
            case 5:
                glBegin(GL_QUADS);
                    glTexCoord2f(0, 0); glVertex3f((*bird).x_minimo,(*bird).y_minimo,  0);
                    glTexCoord2f(0.2, 0); glVertex3f((*bird).x_maximo,(*bird).y_minimo,  0);
                    glTexCoord2f(0.2, 0.5); glVertex3f((*bird).x_maximo,(*bird).y_maximo,  0);
                    glTexCoord2f(0, 0.5); glVertex3f((*bird).x_minimo,(*bird).y_maximo,  0);
                glEnd();
                break;
            case 6:
                glBegin(GL_QUADS);
                    glTexCoord2f(0.2, 0); glVertex3f((*bird).x_minimo,(*bird).y_minimo,  0);
                    glTexCoord2f(0.4, 0); glVertex3f((*bird).x_maximo,(*bird).y_minimo,  0);
                    glTexCoord2f(0.4, 0.5); glVertex3f((*bird).x_maximo,(*bird).y_maximo,  0);
                    glTexCoord2f(0.2, 0.5); glVertex3f((*bird).x_minimo,(*bird).y_maximo,  0);
                glEnd();
                break;
            case 7:
                glBegin(GL_QUADS);
                    glTexCoord2f(0.4, 0); glVertex3f((*bird).x_minimo,(*bird).y_minimo,  0);
                    glTexCoord2f(0.6, 0); glVertex3f((*bird).x_maximo,(*bird).y_minimo,  0);
                    glTexCoord2f(0.6, 0.5); glVertex3f((*bird).x_maximo,(*bird).y_maximo,  0);
                    glTexCoord2f(0.4, 0.5); glVertex3f((*bird).x_minimo,(*bird).y_maximo,  0);
                glEnd();
                break;
            case 8:
                glBegin(GL_QUADS);
                    glTexCoord2f(0.6, 0); glVertex3f((*bird).x_minimo,(*bird).y_minimo,  0);
                    glTexCoord2f(0.8, 0); glVertex3f((*bird).x_maximo,(*bird).y_minimo,  0);
                    glTexCoord2f(0.8, 0.5); glVertex3f((*bird).x_maximo,(*bird).y_maximo,  0);
                    glTexCoord2f(0.6, 0.5); glVertex3f((*bird).x_minimo,(*bird).y_maximo,  0);
                glEnd();
                break;
            case 9:
                glBegin(GL_QUADS);
                    glTexCoord2f(0.8, 0); glVertex3f((*bird).x_minimo,(*bird).y_minimo,  0);
                    glTexCoord2f(1, 0); glVertex3f((*bird).x_maximo,(*bird).y_minimo,  0);
                    glTexCoord2f(1, 0.5); glVertex3f((*bird).x_maximo,(*bird).y_maximo,  0);
                    glTexCoord2f(0.8, 0.5); glVertex3f((*bird).x_minimo,(*bird).y_maximo,  0);
                glEnd();
                break;
            default:
                break;

        }
    }
    if((*bird).status==0){
        switch((*bird).tipo)
        {
            case 0:
                glBegin(GL_QUADS);
                    glTexCoord2f(0.2,0.5); glVertex3f((*bird).x_minimo,(*bird).y_minimo,  0);
                    glTexCoord2f(0, 0.5); glVertex3f((*bird).x_maximo,(*bird).y_minimo,  0);
                    glTexCoord2f(0.2,1); glVertex3f((*bird).x_minimo,(*bird).y_maximo,  0);
                    glTexCoord2f(0, 1); glVertex3f((*bird).x_maximo,(*bird).y_maximo,  0);
                glEnd();
                break;
            case 1:
                glBegin(GL_QUADS);
                    glTexCoord2f(0.4, 0.5); glVertex3f((*bird).x_minimo,(*bird).y_minimo,  0);
                    glTexCoord2f(0.2, 0.5); glVertex3f((*bird).x_maximo,(*bird).y_minimo,  0);
                    glTexCoord2f(0.4, 1); glVertex3f((*bird).x_minimo,(*bird).y_maximo,  0);
                    glTexCoord2f(0.2, 1); glVertex3f((*bird).x_maximo,(*bird).y_maximo,  0);
                glEnd();
                break;
            case 2:
                glBegin(GL_QUADS);
                    glTexCoord2f(0.6, 0.5); glVertex3f((*bird).x_minimo,(*bird).y_minimo,  0);
                    glTexCoord2f(0.4, 0.5); glVertex3f((*bird).x_maximo,(*bird).y_minimo,  0);
                    glTexCoord2f(0.6, 1); glVertex3f((*bird).x_minimo,(*bird).y_maximo,  0);
                    glTexCoord2f(0.4, 1); glVertex3f((*bird).x_maximo,(*bird).y_maximo,  0);
                glEnd();
                break;
            case 3:
                glBegin(GL_QUADS);
                    glTexCoord2f(0.8, 0.5); glVertex3f((*bird).x_minimo,(*bird).y_minimo,  0);
                    glTexCoord2f(0.6, 0.5); glVertex3f((*bird).x_maximo,(*bird).y_minimo,  0);
                    glTexCoord2f(0.8, 1); glVertex3f((*bird).x_minimo,(*bird).y_maximo,  0);
                    glTexCoord2f(0.6, 1); glVertex3f((*bird).x_maximo,(*bird).y_maximo,  0);
                glEnd();
                break;
            case 4:
                glBegin(GL_QUADS);
                    glTexCoord2f(1, 0.5); glVertex3f((*bird).x_minimo,(*bird).y_minimo,  0);
                    glTexCoord2f(0.8, 0.5); glVertex3f((*bird).x_maximo,(*bird).y_minimo,  0);
                    glTexCoord2f(1, 1); glVertex3f((*bird).x_minimo,(*bird).y_maximo,  0);
                    glTexCoord2f(0.8, 1); glVertex3f((*bird).x_maximo,(*bird).y_maximo,  0);
                glEnd();
                break;
            case 5:
                glBegin(GL_QUADS);
                    glTexCoord2f(0.2, 0); glVertex3f((*bird).x_minimo,(*bird).y_minimo,  0);
                    glTexCoord2f(0, 0); glVertex3f((*bird).x_maximo,(*bird).y_minimo,  0);
                    glTexCoord2f(0.2, 0.5); glVertex3f((*bird).x_minimo,(*bird).y_maximo,  0);
                    glTexCoord2f(0, 0.5); glVertex3f((*bird).x_maximo,(*bird).y_maximo,  0);
                glEnd();
                break;
            case 6:
                glBegin(GL_QUADS);
                    glTexCoord2f(0.4, 0); glVertex3f((*bird).x_minimo,(*bird).y_minimo,  0);
                    glTexCoord2f(0.2, 0); glVertex3f((*bird).x_maximo,(*bird).y_minimo,  0);
                    glTexCoord2f(0.4, 0.5); glVertex3f((*bird).x_minimo,(*bird).y_maximo,  0);
                    glTexCoord2f(0.2, 0.5); glVertex3f((*bird).x_maximo,(*bird).y_maximo,  0);
                glEnd();
                break;
            case 7:
                glBegin(GL_QUADS);
                    glTexCoord2f(0.6, 0); glVertex3f((*bird).x_minimo,(*bird).y_minimo,  0);
                    glTexCoord2f(0.4, 0); glVertex3f((*bird).x_maximo,(*bird).y_minimo,  0);
                    glTexCoord2f(0.6, 0.5); glVertex3f((*bird).x_minimo,(*bird).y_maximo,  0);
                    glTexCoord2f(0.4, 0.5); glVertex3f((*bird).x_maximo,(*bird).y_maximo,  0);
                glEnd();
                break;
            case 8:
                glBegin(GL_QUADS);
                    glTexCoord2f(0.8, 0); glVertex3f((*bird).x_minimo,(*bird).y_minimo,  0);
                    glTexCoord2f(0.6, 0); glVertex3f((*bird).x_maximo,(*bird).y_minimo,  0);
                    glTexCoord2f(0.8, 0.5); glVertex3f((*bird).x_minimo,(*bird).y_maximo,  0);
                    glTexCoord2f(0.6, 0.5); glVertex3f((*bird).x_maximo,(*bird).y_maximo,  0);
                glEnd();
                break;
            case 9:
                glBegin(GL_QUADS);
                    glTexCoord2f(1, 0); glVertex3f((*bird).x_minimo,(*bird).y_minimo,  0);
                    glTexCoord2f(0.8, 0); glVertex3f((*bird).x_maximo,(*bird).y_minimo,  0);
                    glTexCoord2f(1, 0.5); glVertex3f((*bird).x_minimo,(*bird).y_maximo,  0);
                    glTexCoord2f(0.8, 0.5); glVertex3f((*bird).x_maximo,(*bird).y_maximo,  0);
                glEnd();
                break;
            default:
                break;

        }
    }
    glDisable(GL_TEXTURE_2D);
}

void desenha_cenario(){
    float altura_ceu,altura_terra;
    altura_terra=55;
    altura_ceu=ALTURA_TELA-altura_terra-25;
    float x_inicial_terra=b1.x+5;
    float y_inicial_terra=b1.altura+5+b1.y;
    float x_inicial_ceu=b1.x+5;
    float y_inicial_ceu=b1.altura+altura_terra+b1.y;
    float largura_ceu=LARGURA_TELA-10;
    float largura_terra=LARGURA_TELA-10;
    glColor3f(0.2, 0, 0.3);
    desenha_barra_comum( x_inicial_terra,y_inicial_terra,altura_terra,largura_terra);
    glColor3f(0, 0.2, 0.3);
    desenha_barra_comum(x_inicial_ceu,y_inicial_ceu,altura_ceu,largura_ceu);

    glColor4f(1,1,1,1);


    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texturaCeu);
    glBegin(GL_QUADS);
        glTexCoord2f(0, 0); glVertex3f(x_inicial_ceu,y_inicial_ceu,  0);
        glTexCoord2f(1, 0); glVertex3f(x_inicial_ceu+largura_ceu,y_inicial_ceu,  0);
        glTexCoord2f(1, 1); glVertex3f(x_inicial_ceu+largura_ceu,y_inicial_ceu+altura_ceu,  0);
        glTexCoord2f(0, 1); glVertex3f(x_inicial_ceu,y_inicial_ceu+altura_ceu,  0);
    glEnd();
    glDisable(GL_TEXTURE_2D);

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texturaSolo);
    glBegin(GL_QUADS);
        glTexCoord2f(0, 0); glVertex3f(x_inicial_terra, y_inicial_terra,  0);
        glTexCoord2f(1, 0); glVertex3f(x_inicial_terra+largura_terra, y_inicial_terra,  0);
        glTexCoord2f(1, 1); glVertex3f(x_inicial_terra+largura_terra, y_inicial_terra+altura_terra,  0);
        glTexCoord2f(0, 1); glVertex3f(x_inicial_terra, y_inicial_terra+altura_terra,  0);
    glDisable(GL_TEXTURE_2D);

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texturaBixo);
    glBegin(GL_QUADS);
        glTexCoord2f(0, 0); glVertex3f(500,500,  0);
        glTexCoord2f(1, 0); glVertex3f(501,500,  0);
        glTexCoord2f(1, 1); glVertex3f(501,501,  0);
        glTexCoord2f(0, 1); glVertex3f(500,501,  0);
    glEnd();
    glDisable(GL_TEXTURE_2D);

    //textura_sprite();

}

void desenha_textura_coracao(int x,int y,int tamanho){
    glColor4f(1,1,1,1);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texturaCoracao);
    int x_minimo=x;
    int x_maximo=x+tamanho;
    int y_minimo=y;
    int y_maximo=y+tamanho;
    glBegin(GL_QUADS);
        glTexCoord2f(0, 0); glVertex3f(x_minimo,y_minimo,  0);
        glTexCoord2f(1, 0); glVertex3f(x_maximo,y_minimo,  0);
        glTexCoord2f(1, 1); glVertex3f(x_maximo,y_maximo,  0);
        glTexCoord2f(0, 1); glVertex3f(x_minimo,y_maximo,  0);
    glEnd();
    glDisable(GL_TEXTURE_2D);
}

void desenha_textura_objeto(objeto o){
    glColor4f(1,1,1,1);
    glEnable(GL_TEXTURE_2D);
    if(CONTADOR_FRAMES%2==0){
        if(flag==1){
            flag=0;
        }
        else{
            flag=1;
        }
    }
    if(o.tipo==1 && flag==0){
        glBindTexture(GL_TEXTURE_2D, texturaShuriken);
    }
    if(o.tipo==0 && flag==0){
        glBindTexture(GL_TEXTURE_2D, texturaShuriken2);
    }
    if(o.tipo==1 && flag==1){
        glBindTexture(GL_TEXTURE_2D, texturaShuriken11);
    }
    if(o.tipo==0 && flag==1){
        glBindTexture(GL_TEXTURE_2D, texturaShuriken22);
    }
    glBegin(GL_QUADS);
        glTexCoord2f(0, 0); glVertex3f(o.x_minimo,o.y_minimo,  0);
        glTexCoord2f(1, 0); glVertex3f(o.x_maximo,o.y_minimo,  0);
        glTexCoord2f(1, 1); glVertex3f(o.x_maximo,o.y_maximo,  0);
        glTexCoord2f(0, 1); glVertex3f(o.x_minimo,o.y_maximo,  0);
    glEnd();
    glDisable(GL_TEXTURE_2D);

}

int  verifica_colisao(personagem p1,objeto o1){
    if(p1.y_maximo>=o1.y_minimo){
        if(p1.x_minimo>=o1.x_minimo && p1.x_minimo<=o1.x_maximo){
            return 1;
        }
        if(p1.x_maximo>=o1.x_minimo && p1.x_maximo<=o1.x_maximo){
            return 1;
        }
        if(p1.x_minimo==o1.x_minimo && p1.x_maximo==o1.x_maximo){
            return 1;
        }
    }
    return 0;
}

void atualiza_frames_objetos(){
    int i;
    for(i=0;i<NUMERO_DE_OBSTACULOS;i++){
        o[i].numero_frames+=1;
        o[i].x_minimo=o[i].x;
        o[i].x_maximo=o[i].x+o[i].tamanho;
        o[i].y_minimo=o[i].y;
        o[i].y_maximo=o[i].y+o[i].tamanho;
    }
}

void atualiza_passaros(){
    int i;
    for(i=0;i<NUMERO_PASSAROS;i++){
        bird[i].x_minimo=bird[i].x;
        bird[i].x_maximo=bird[i].x+bird[i].tamanho;
        bird[i].y_minimo=bird[i].y;
        bird[i].y_maximo=bird[i].y+bird[i].tamanho;
        if(bird[i].status==0){
            andou_esquerda_p(&bird[i]);
        }

        else{
            andou_direita_p(&bird[i]);
        }
    }
}

void gera_posisoes_objetos(int numero_de_objetos){
    int i=0;
    int incremento_tamanho=1;
    int fator_corretor_tempo=5;
    int numero_de_frames_para_aumentar_tamanho=FPS*fator_corretor_tempo/fator_de_dificuldade;
    if(CONTADOR_FRAMES%numero_de_frames_para_aumentar_tamanho==0 && CONTADOR_FRAMES!=0){
        tamanho_objeto=tamanho_objeto+incremento_tamanho;
    }
    for(i=0;i<numero_de_objetos;i++){
        gera_cordendas_dos_objetos(&o[i],velocidade_objeto,tamanho_objeto,fator_de_dificuldade);
    }
}

void verifica_dano(){
    int i;
    int flag;
    for(i=0;i<NUMERO_DE_OBSTACULOS;i++){
        flag=verifica_colisao(p1,o[i]);
        if(flag==1){
            if(p1.status==1 && tipo_personagem==0){
                p1.numero_de_vidas-=1;
            }
            p1.status=0;
            o[i].status=3;
        }
    }
}

void atualiza_personagem(){
    andou_direita(&p1,anda_direita);
    andou_esquerda(&p1,anda_esquerda);
    p1.x_minimo=p1.x;
    p1.x_maximo=p1.x+p1.largura;
    p1.y_minimo=p1.y;
    p1.y_maximo=p1.y+p1.comprimento;
    p1.diferenca_altura_largura=p1.comprimento-p1.largura;
    if(p1.status==0){
        if(p1.numero_frames%FPS==0)
            p1.tempo+=1;
        p1.numero_frames++;
        if(p1.tempo==3){
            p1.tempo=0;
            p1.status=1;
            p1.numero_frames=0;
        }
    }
}


void desenha_jogo(void){

    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0, 0, 0.3);
    desenha_cenario();
    if(p1.status==1 || p1.status==0 && p1.numero_frames%2==0 && tipo_personagem==0){
            textura_personagem();
    }
    if(tipo_personagem==1){
            textura_personagem();
    }


    glColor3f(0, 0, 0.3);
    desenha_barra(b1,LARGURA_TELA,ALTURA_TELA);
    glColor3f(1, 0, 0);
    //faz_quadrado(p1.x,p1.y,10);
    glColor3f(0, 0, 0);
    int i;
    for(i=0;i<NUMERO_DE_OBSTACULOS;i++){
        desenha_textura_objeto(o[i]);
    }
    int k;
    for(k=0;k<NUMERO_PASSAROS;k++){
       textura_sprite_bird(&bird[k]);

    }
    int j;
    int tamanho_coracao=30;
    int espaso_entre_coracoes=5;
    int x_coracao=LARGURA_TELA/2-largura_moldura-tamanho_coracao;
    int altura_coracao=ALTURA_TELA/2-largura_moldura-tamanho_coracao;
    for(j=0;j<p1.numero_de_vidas;j++){
        desenha_textura_coracao(x_coracao,altura_coracao,tamanho_coracao);
        x_coracao=x_coracao-tamanho_coracao-espaso_entre_coracoes;
    }
    glutSwapBuffers();
}

void desenha(){
    if(modo==0){
        if(pausado==0){
            desenha_jogo();
        }
       else{
            desenha_menu3();
        }
    }
    if(modo==1){
        desenha_menu();
    }
    if(modo==2){
        desenha_menu2();
    }
    if(modo==3){
        desenha_menu4();
    }
    if(modo==4){
        desenha_menu5();
    }
    if(modo==5){
        desenha_menu6();
    }
}

void atualiza(){
    if(modo!=0){
        glutPostRedisplay();
     }
     if(modo==0 && pausado==1){
        glutPostRedisplay();
     }
    if(modo==0 && pausado==0){
        if(p1.numero_de_vidas==0){
            modo=3;
        }
        if(TEMPO==TEMPO_MAX && contador_de_vitoria==0){
            modo=4;
            contador_de_vitoria++;
        }
        CONTADOR_FRAMES++;
        anguloDeRotacao += incrementoAngulo;
        atualiza_frames_objetos();
        atualiza_passaros();
        atualiza_personagem();
        gera_posisoes_objetos(NUMERO_DE_OBSTACULOS);
        verifica_dano();
        glutPostRedisplay();
        if(CONTADOR_FRAMES%FPS==0){
            TEMPO++;
            b1=calcula_dimencoes(b1,TEMPO,TEMPO_MAX,LARGURA_TELA,ALTURA_TELA);
        }
        tempo_para_aumentar_dificuldade=FPS*fator_de_dificuldade*regulador_do_tempo_de_dificuldade;
        //printf("fator de dificuladade %.2f e tempo pra muda %d\n",fator_de_dificuldade,tempo_para_aumentar_dificuldade);
        if(CONTADOR_FRAMES%tempo_para_aumentar_dificuldade==0 && CONTADOR_FRAMES!=0){
            fator_de_dificuldade++;
            //NUMERO_DE_OBSTACULOS-=1;
            if(regulador_do_tempo_de_dificuldade>2)
                regulador_do_tempo_de_dificuldade-=2;
        }
    }
    glutTimerFunc(INTERVALO_ENTRE_AS_FRAMES,atualiza, 0);
}

void redimensiona(int w, int h){
    float razao = (float)h/w;
    w1=w;
    h1=h;
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-w/2,w/2,-h/2,h/2, -1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void teclado(unsigned char key, int x, int y){
   switch(key)
   {
      case 27:
         exit(0);
         break;
      case 'a':
          anda_esquerda=1;
          break;
      case 'w':
          break;
      case '+':
          incrementoAngulo += 0.5;
          break;
      case '-':
          incrementoAngulo -= 0.5;
          break;
      case 'd':
          anda_direita=1;
          break;
      case 's':
         break;
      case ' ':
          if(contador_impulso==0){
            impulsu(&p1,anda_direita,anda_esquerda);
          }
          contador_impulso++;
         break;
      default:
         break;

   }
}

void teclado2(unsigned char key, int x, int y){
   switch(key)
   {
      case 'a':
            anda_esquerda=0;
         break;
      case 'w':
         break;
      case 'd':
            anda_direita=0;
         break;
      case 's':
         break;
        case 'p':if(pausado==0){
            pausado=1;
          }
          else{
            pausado=0;
          }
         break;
         case ' ':
          if(contador_impulso!=0){
            contador_impulso=0;
          }

      default:
         break;

   }
}

int main(int argc, char **argv){
    srand(time(0));

    INTERVALO_ENTRE_AS_FRAMES=(float)1000/FPS;
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowSize(LARGURA_TELA, ALTURA_TELA);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("TP1");
    inicializa();
    inicializa_barra();
    inicializa_personagem();
    init();
    glutKeyboardFunc(teclado);
    glutKeyboardUpFunc(teclado2);
    glutReshapeFunc(redimensiona);
    glutDisplayFunc(desenha);
    glutMouseFunc(click_mouse);
    glutPassiveMotionFunc(mouse_motion);
    glutTimerFunc(INTERVALO_ENTRE_AS_FRAMES,atualiza, 0);
    glutMainLoop();
    return 0;
}
