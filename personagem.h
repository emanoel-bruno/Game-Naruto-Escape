
typedef struct personagem_principal{
    float x;
    float y;
    float x_minimo;
    float x_maximo;
    float y_minimo;
    float y_maximo;
    int velocidade;
    int largura;
    int comprimento;
    int diferenca_altura_largura;
    int numero_frames;
    int tempo;
    int movimento;
    int status;
    int numero_de_vidas;
}personagem;
void andou_esquerda(personagem *p1,int esquerda);
void andou_direita(personagem *p1,int direita);
void impulsu(personagem *p1,int direita,int esquerda);
