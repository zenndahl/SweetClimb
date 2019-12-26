//Declaracao de Variaveis Globais
int projecao = 1;                      //Variavel Logica para Definir o Tipo de Projecao (Perspectiva ou Ortogonal)
int posx = 0, posy = 10, posz = 28;    //Variaveis que definem a posicao da camera
int oy = 9,ox = 0,oz = 0;              //Variaveis que definem para onde a camera olha
int lx = 0, ly = 1,  lz = 0;           //Variaveis que definem qual eixo estara na vertical do monitor. //NAO MUDAR

//variaveis para movimentacao do personagem
float player_x = -4, player_y = 1;
int lateral = 1;

//personagem subiu ou desceu de plataforma 
int subir = 0;
int descer = 0;

//variaveis para movimentacao do brigadeiro
float bx = 0, by = 15.5;
int plat_brig = 5;
float bx_default = 0, by_default = 15.5;

//variaveis para a ação de pulo;
float velocidade = -0.4;  
float gravidade = 0.05;  
float tempo = 0.5;

//posicao das plataformas
float plat_y[10];
int plat_num = 1;
int plat_fim[2];

//posições das escadas
float e1[2];
float e2[2];
float e3[2];
float q1[2];
float q2[2];

//variavel para controlar o tipo de visao
int visao;

//variaveis para controlar o level do jogo
int lvl = 0;
float lvl_factor = 0; //modifica a posição das escadas conforme o level do jogo

//pontuacao
int pontos = 0;