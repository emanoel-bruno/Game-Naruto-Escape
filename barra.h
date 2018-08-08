typedef struct barra_do_tempo
{
    float x,y;
    //x,y sao os pontos iniciais da barra;
    float largura;
    float altura;
}barra;
barra calcula_dimencoes(barra b1,int tempo_atual,int tempo_max,int largura_tela,int altura_tela);
void desenha_barra(barra b1,int largura_tela,int altura_tela);
void desenha_barra_comum(float x,float y,float altura,float largura);
