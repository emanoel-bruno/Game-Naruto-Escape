typedef struct objetos_do_jogo{
    int tipo;
    float x;
    float y;
    float x_minimo;
    float x_maximo;
    float y_minimo;
    float y_maximo;
    float tamanho;
    int status;
    int numero_frames;
    int aceleracao;
    int velocidade;
}objeto;
void gera_cordendas_dos_objetos(objeto *o1,int velocidade,int tamanho,float fator_de_dificuldade);
void atualiza_cordendas_dos_objetos(objeto *o1);
void gera_cordendas_dos_passaros(objeto *o1,int velocidade,int tamanho);
void andou_direita_p(objeto *p1);
void andou_esquerda_p(objeto *p1);


