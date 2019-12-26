//Programa exemplo para representacoes de elementos bidimensionais e tridimensionais.
//A estrutura permite manipular diferentes projecoes.

#include <stdlib.h>
#include <stdio.h>
#include <GL/freeglut.h>
#include <GL/glut.h>
#include <GL/gl.h>
#include <math.h>
#include <time.h>

/****************************************************
Valores Importantes

Valores de x para as plataformas:
   -5.5 a 5.5 (plataformas grandes)

Valores de y para as plataformas:
   *os valores de y em plat_y sao os valores do chao de cada plataforma (y + 0.9)
   valores de plat_y:
      1, 4, 7, 10, 13, 16

Valores Iniciais do Jogador:
   x: -4
   y:  1

Valores de x para as escadas normais
   4.75  (escadas da direita)
   -4.25 (escadas da esquerda)
   1.0   (ultima escada)

Valores de movimentacao
   Movimento na horizontal: 0.125
   Movimento na vertical  : 0.15

*Todos os valores foram testados empiricamente e foram os melhores encontrados
*Cuidado ao fazer qualquer alteracao, pode baguncar o cenario
****************************************************/

#define incr_radia 0.017453293

//Declaracao de Variaveis Globais
int projecao = 0; //Variavel Logica para Definir o Tipo de Projecao (Perspectiva ou Ortogonal)
int posx = 0, posy = 10, posz = 28; //Variaveis que definem a posicao da camera
int oy = 9,ox = 0,oz = 0;          //Variaveis que definem para onde a camera olha
int lx = 0, ly = 1,  lz = 0;       //Variaveis que definem qual eixo estara na vertical do monitor. //NAO MUDAR
//variaveis para movimentacao do personagem
float player_x = -4, player_y = 1;
int lateral = 1;
//personagem subiu ou desceu de plataforma 
int subir = 0;
int descer = 0;
//posicao das plataformas
float plat_y[10];
int plat_num = 1;
int plat_fim[2];
//posições das escadas
float e1[2];
float e2[2];
float e3[2];
float lvl_factor = 0; //modifica a posição das escadas conforme o level do jogo
//variavel para controlar o tipo de visao
int visao;
//variavel para controlar o level do jogo
int lvl = 0;

//Prototipos das Funcoes
void Inicializa();
void Display();
void Mouse(int botao, int estado, int x, int y);
void keyboard (unsigned char key, int x, int y);
void TeclasEspeciais (int key, int x, int y);
void posiciona_personagem();

// struct boneco{
//    float yMax = 0.7;
//    float yMin = -1.5;
//    float xMax = 0.7;
//    float xMin = -0.7;
// };

//background
void nuvens(float pontox, float pontoy){

   glPushMatrix();
      glColor3ub(230,230,230);
      glTranslatef(pontox, pontoy, -10);
      glutSolidSphere(1,20,20);
   glPopMatrix();

   glPushMatrix();
      glColor3ub(230,230,230);
      glTranslatef(pontox-0.5, pontoy-0.5, -10);
      glutSolidSphere(1,20,20);   
   glPopMatrix();

   glPushMatrix();
      glColor3ub(230,230,230);
      glTranslatef(pontox+0.5, pontoy-0.5, -10);
      glutSolidSphere(1,20,20);   
   glPopMatrix();

   glPushMatrix();
      glColor3ub(230,230,230);
      glTranslatef(pontox, pontoy-0.5, -10);
      glutSolidSphere(1,20,20);
   glPopMatrix();
}

void dados_nuvens(){
   //x positivo y positivo
   nuvens(3, 5);
   nuvens(12, 15);
   nuvens(9, 7);
   nuvens(5, 15);

   //x negativo y positivo
   nuvens(-4, 3);
   nuvens(-8, 5);
   nuvens(-3, 13);
   nuvens(-12, 17);
  
}

void chao(){
   glPushMatrix();
      glColor3ub(100, 190, 50);
      glTranslatef(0, 0, 3);
      glScalef(35, 0, 12);
      glutSolidCube(1);
   glPopMatrix();
}

void sol(){
   glPushMatrix();
      glColor3ub(253, 184, 53);
      glTranslatef(15, 23, -10);
      glutSolidSphere(3, 50, 50);
   glPopMatrix();
}

//criacao das plataformas --------------------------------------------------------------
void criar_plataforma(float px, float py, float tamanho, int i, float tx){

   tamanho *= 2;
   glPushMatrix();
      glPushMatrix();
         glColor3ub(232, 100, 155);
         glTranslatef(px, py, 0);
         glScalef(tamanho, 0.5, 1.625);
         //todas as plataformas, exeto a ultima, tem tamanhos iguais (11)
         glutSolidCube(1);
      glPopMatrix();

      //cria as passagens pelas plataformas
      if(i%2 == 0){
         //sobre a escada da ultima plataforma
         if(i == 6){
            glPushMatrix();
               glColor3ub(20, 165, 165);
               glTranslatef(0.95, 18, -0.2);
               glScalef(0.9, 0.6, 1);
               glutSolidCube(1);
            glPopMatrix();
         }
         //sobre as escadas da direita
         else{
            glPushMatrix();
               glColor3ub(20, 165, 165);
               glTranslatef(tx+0.2, py+3, 0);
               glScalef(0.9, 0.6, 1);
               glutSolidCube(1);
            glPopMatrix();
         }
      }
      //sobre as escadas da esquerda
      else{
         glPushMatrix();
            glColor3ub(20, 165, 165);
            glTranslatef(-tx+0.2, py+3, 0);
            glScalef(0.9, 0.6, 1);
            glutSolidCube(1);
         glPopMatrix();
      }
   glPopMatrix();
   plat_y[i] = py + 0.9;
   if(py = 18){
      plat_fim[0] = px-tamanho/2 - 0.2;
      plat_fim[1] = px+tamanho/2 + 0.2;
   }
}

//criacao das escadas ------------------------------------------------------------------

//cria os vetores com as posicoes de x das escadas em que sera possivel subi-las
void init_vet_escadas(){
   //escadas da direita
   e1[0] = 4.75 + lvl_factor;
   //escadas da esquerda
   e2[0] = -4.25 + lvl_factor;

   //escada da ultima plataforma
   e3[0] = 1;
}


void cria_escada(float tx, float ty, float tz){

   glColor3ub(200, 200, 200);
   //escada
   glPushMatrix();
   //degrais
      glPushMatrix();

         glTranslatef(tx+0.25, ty-0.5, tz);
         //glRotatef(90, 0, 0, 1);
         glScalef(0.7, 0.1, 0.1);
         glutSolidCube(1);

      glPopMatrix();

      glPushMatrix();

         glTranslatef(tx+0.25, ty, tz);
         //glRotatef(90, 0, 0, 1);
         glScalef(0.7, 0.1, 0.1);
         glutSolidCube(1);

      glPopMatrix();

      glPushMatrix();

         glTranslatef(tx+0.25, ty+0.5, tz);
         //glRotatef(90, 0, 0, 1);
         glScalef(0.7, 0.1, 0.1);
         glutSolidCube(1);

      glPopMatrix();

      glPushMatrix();

         glTranslatef(tx+0.25, ty+1, tz);
         //glRotatef(90, 0, 0, 1);
         glScalef(0.7, 0.1, 0.1);
         glutSolidCube(1);

      glPopMatrix();

      glPushMatrix();

         glTranslatef(tx+0.25, ty-1, tz);
         //glRotatef(90, 0, 0, 1);
         glScalef(0.7, 0.1, 0.1);
         glutSolidCube(1);

      glPopMatrix();
      //fim degrais

      //laterais
      glPushMatrix();
         //lateral direita
         glTranslatef(tx+0.5, ty, tz);
         glRotatef(90, 0, 0, 1);
         glScalef(2.8, 0.1, 0.1);
         glutSolidCube(1);

      glPopMatrix();

      //lateral esquerda
      glTranslatef(tx, ty, tz);
      glRotatef(90, 0, 0, 1);
      glScalef(2.8, 0.1, 0.1);
      glutSolidCube(1);
      //fim laterais

   glPopMatrix();

   glutPostRedisplay();
}//fim escadas

void escada_quebrada(float tx, float ty, float tz, int set){
   //para fazer o calculo da alternancia da posicao das escadas
   float space;
   if(set == 1){
      space = 3*set;
   }
   else{
      space = set;
      ty -= 0.1;
   }

   //escada
   glColor3ub(102, 72, 56);
   glPushMatrix();
      //degrais
      glPushMatrix();
         //primeiro degrau
         
         glTranslatef(set*tx-2.3-space, ty-0.5, tz);
         glScalef(0.6, 0.1, 0.1);
         glutSolidCube(1);

      glPopMatrix();

      glPushMatrix();
         //segundo degrau
         //glColor3ub(40, 45, 40);
         glTranslatef(set*tx-2.4-space, ty, tz);
         glRotatef(3, 0, 0, 1);
         glScalef(0.5, 0.1, 0.1);
         glutSolidCube(1);

      glPopMatrix();

      glPushMatrix();
         //degrau superior
         //glColor3ub(40, 45, 40);
         glTranslatef(set*tx-2.4-space, ty+1, tz);
         glRotatef(-10, 0, 0, 1);
         glScalef(0.5, 0.1, 0.1);
         glutSolidCube(1);

      glPopMatrix();
      //fim degrais

      //laterais

      //laterais direitas
      glPushMatrix();
         //lateral direita inferior
         //glColor3ub(40, 45, 40);
         glTranslatef(set*tx-2-space, ty-0.3, tz);
         glRotatef(90, 0, 0, 1);
         glScalef(1.5, 0.1, 0.1);
         glutSolidCube(1);

      glPopMatrix();

      glPushMatrix();
         //lateral direita superior
         //glColor3ub(40, 45, 40);
         glTranslatef(set*tx-2-space, ty+1.2, tz);
         glRotatef(90, 0, 0, 1);
         glScalef(1, 0.1, 0.1);
         glutSolidCube(1);

      glPopMatrix();

      //esquerdas
      glPushMatrix();
         //lateral direita inferior
         //glColor3ub(40, 45, 40);
         glTranslatef(set*tx-2.6-space, ty-0.3, tz);
         glRotatef(90, 0, 0, 1);
         glScalef(1.5, 0.1, 0.1);
         glutSolidCube(1);

      glPopMatrix();

      //lateral direita superior
      //glColor3ub(40, 45, 40);
      glTranslatef(set*tx-2.6-space, ty+1.2, tz);
      glRotatef(90, 0, 0, 1);
      glScalef(1, 0.1, 0.1);
      glutSolidCube(1);
      //fim laterais
   glPopMatrix();

   // quebradas[cont_quebradas++] = (set*tx-2.6-space) + 0.3;
   // quebradas[cont_quebradas++] = (set*tx-2.6-space) + 0.4;

}//fim escadas quebradas

void gera_dados(){
   //dados das plataformas
   float ey = 0;
   float plat_y[10];
   int i = 0;

   //dados das escadas
   float tx = 4.6, ty = 1, tz = -0.65;
   int set = 1;

   //cria as plataformas grandes
   for(i = 0; i < 6; i++){
      criar_plataforma(0,  ey, 5.5, i, tx+lvl_factor);
      ey += 3;
   }
   //plataforma da maçã
   criar_plataforma(0, 18, 1.5, 6, 1.15);

   //cria todas as escadas em suas devidas posicoes
   for(int i = 0; i < 5; i++){
      cria_escada(tx+lvl_factor, ty, tz);
      escada_quebrada(tx-lvl_factor, ty-0.3, tz, set);
      tx = -tx;
      ty += 3.2;
      set *= -1;
   }
   //escada da ultima plataforma
   cria_escada(0.8, 16.5, tz);

   init_vet_escadas();
}

void lvl_up(){
   //aumenta o level
   lvl++;
   //gera o fator para reposicionamento das escadas
   lvl_factor = (float)rand()/(float)(RAND_MAX) * 0.5;
   int sinal = rand()%20;
   if(sinal >= 1 && sinal <= 10) lvl_factor = -lvl_factor;
   printf("%.2f\t", lvl_factor);
   gera_dados();

   //reinicia vetor das escadas
   init_vet_escadas();

   //reinicia variaveis de controle
   plat_num = 1;
   subir = 0;
   descer = 0;
   lateral = 1; //acho que nao precisa, mas ta aqui pra garantir

   //reinicia o personagem
   player_x = -4;
   player_y = 1;
   posiciona_personagem();
}

//criacao do personagem e do vilao ------------------------------------------------------

//Função para construir partes do corpo formadas por cubo
void CorpoCubo(float transx, float transy, float transz, float scalx, float scaly, float scalz, int colorx, int colory, int colorz, float tamC){
    glTranslatef(transx, transy, transz); //A origem do cubo foi transladada para a posição (transx, transy, transz).
    glScalef(scalx, scaly, scalz);
    glColor3ub(colorx, colory, colorz);
    glutSolidCube(tamC);
}

//Função para construir partes do corpo formadas por esfera
void CorpoEsfera(float transx, float transy, float transz, int colorx, int colory, int colorz, float esfx, float esfy, float esfz){
   glTranslatef(transx, transy, transz); //A origem da esfera foi transladada para a posição (transx, transy, ftransz).
   glColor3ub(colorx, colory, colorz); //Define a cor
   glutSolidSphere(esfx, esfy, esfz); //Definição (criação) da esfera
}

void apple(){
   glPushMatrix();
      CorpoEsfera(3, 0, 0.3, 250, 50, 30, 0.3, 50, 50);
   glPopMatrix();
   glPushMatrix();
      glRotatef(45, 1, 0, 0);
      CorpoCubo(3, 1, 0.3, 0.1, 0.6, 0.1, 127, 255, 14, 0.6);
   glPopMatrix();
}

void cria_vilao(){
   //Criação das pernas
   glPushMatrix();
   //glScalef(0.5, 0.5, 0.5);
      CorpoCubo(0, 0, 0, 0.3, 0.7, 0.3, 0, 0, 139, 1.0);
   glPopMatrix();

   //Criação do tronco do corpo
   glPushMatrix();
   //glScalef(0.5, 0.5, 0.5);
      CorpoCubo(0, 0.6, 0, 0.3, 0.5, 0.3, 144, 238, 144, 1.0);
   glPopMatrix();

   //Braço direito do personagem
   glPushMatrix();
   //glScalef(0.5, 0.5, 0.5);
      CorpoCubo(0.2, 0.5, 0, 0.1, 0.7, 0.3, 0, 100, 0, 1.0);
   glPopMatrix();

   //Braço esquerdo do personagem
   glPushMatrix();
   //glScalef(0.5, 0.5, 0.5);
      CorpoCubo(-0.2, 0.5, 0, 0.1, 0.7, 0.3, 0, 100, 0, 1.0);
   glPopMatrix();

   //Cabeça
   //glScalef(0.5, 0.5, 0.5);
   CorpoEsfera(0, 1, 0, 255, 182, 193, 0.25, 20, 20); 

   //OlhoEsquerdo
   glPushMatrix();
   //glScalef(0.5, 0.5, 0.5);
      CorpoEsfera(-0.04, 0, 0.7, 0, 0, 0, 0.02, 50, 50);
   glPopMatrix();

   //OlhoDireito
   glPushMatrix();
   //glScalef(0.5, 0.5, 0.5);
      CorpoEsfera(0.09, 0, 0.7, 0, 0, 0, 0.02, 50, 50);      
   glPopMatrix();
}

void personagem(){
    
   glScalef(0.5, 0.5, 0.5);
   glPushMatrix();
   
      glColor3ub(255, 204, 102);
      glTranslatef(0,0,0); 
      glRotatef(90,1,0,0);
      glutSolidCone(0.5,1.5,20,10);

      //glColor3ub(255,0,0);
      //glTranslatef(0,0,0); 
      //glutSolidSphere(0.15,20,20);

      glColor3ub(255, 0, 102);
      glTranslatef(-0.2,0,-0.2); 
      glutSolidSphere(0.35,20,20);

      glColor3ub(255, 255, 204);
      glTranslatef(0.4,0,0); 
      glutSolidSphere(0.35,20,20);

      glColor3ub(153, 0, 0);
      glTranslatef(-0.2,0,-0.3); 
      glutSolidSphere(0.35,20,20);

         glColor3ub(255,255,255);
      glTranslatef(-0.2,0.5,0.8); 
      glutSolidSphere(0.15,20,20);

      glColor3ub(0,255,0);
      glTranslatef(0,0.15,0); 
      glutSolidSphere(0.1,20,20);

      glColor3ub(0,0,0);
      glTranslatef(0,0.1,0); 
      glutSolidSphere(0.05,20,20);

      glColor3ub(255,255,255);
      glTranslatef(0.4,-0.25,0); 
      glutSolidSphere(0.15,20,20);

      glColor3ub(0,255,0);
      glTranslatef(0,0.15,0); 
      glutSolidSphere(0.1,20,20);

      glColor3ub(0,0,0);
      glTranslatef(0,0.1,0); 
      glutSolidSphere(0.05,20,20);

      glColor3ub(165,42,10);
      glTranslatef(-0.1,0.05,-0.2); 
      glRotatef(90,0,1,0);
      glutSolidCylinder(0.02,0.25,20,10);

      glColor3ub(165,42,10);
      glTranslatef(0,0,-0.4); 
      glutSolidCylinder(0.02,0.25,20,10);

   glPopMatrix();
}

void posiciona_personagem(){
   glPushMatrix();  
      glTranslatef(player_x, player_y, 0);
      personagem();
   glPopMatrix();
}

//tratamento de colisoes ----------------------------------------------------------------

//colisao com a maca e aumento de nivel (para todas as outras funcoes)
void collision_apple(){
   if(player_y > plat_y[6]){
      // if(player_x <= -1.5){
         
      // }
      lvl_up();
   }
}

//Display de informacoes e da cena ------------------------------------------------------

//imprime no terminal as posicoes do chao de cada plataforma
void imprime(){
    for(int i = 0; i < 3; i++){
        printf("%2.f\t", plat_y[i]);
    }
}

void Display(){
   
   glEnable(GL_DEPTH_TEST);

   glEnable(GL_LINE_SMOOTH);
   glEnable(GL_POLYGON_SMOOTH); 

   glEnable(GL_SMOOTH);
   glEnable(GL_BLEND);

   // Inicializa parametros de rendering
   
   glClearColor(0.1, 0.65, 0.65, 0);

   glMatrixMode(GL_PROJECTION);
   //glMatrixMode()- define qual matriz sera alterada. SEMPRE defina o tipo de apresentacao 
   //(Ortogonal ou Perspectiva) na matriz PROJECTION.
   glLoadIdentity();//"Limpa" ou "transforma" a matriz em identidade, reduzindo possiveis erros.

   if (projecao == 1)
      glOrtho(-250, 250, -250, 250, -250, 250); //Define a projecao como ortogonal
   else
      gluPerspective(45,1,1,50); //Define a projecao como perspectiva

   glMatrixMode(GL_MODELVIEW);
   //glMatrixMode()- define qual matriz sera alterada. SEMPRE defina a camera 
   //(Ortogonal ou Perspectiva) na matriz MODELVIEW (onde o desenho ocorrera).

   glLoadIdentity(); //"Limpa" ou "transforma" a matriz em identidade, reduzindo possiveis erros.

   gluLookAt(posx,posy,posz,ox,oy,oz,lx,ly,lz); //Define a posicao da camera, para onde olha e qual eixo esta na vertical.
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
   //"limpa" um buffer particular ou combinacoes de buffers, 
   //onde buffer e uma area de armazenamento para informacoes da imagem. 
   //Nesse caso, esta "limpando os buffers para suportarem animacoes 
   //Chamada para Funcao  ou funcoes para desenhar o objeto/cena...
   
   //glPushMatrix(); //Salva o estado atual da cena. O que for desenhado apos o Push nao influenciara o ja representado

   gera_dados();
   dados_nuvens();
   //sol();
   //chao();

   //imprime();

   posiciona_personagem();

   glPushMatrix();
      glTranslatef(-4, 18.5, 0);
      apple();
   glPopMatrix();

   glPushMatrix();
   glTranslatef(-4, 15.5, 0);
      cria_vilao();
   glPopMatrix();
   collision_apple();
   
   //printf("\n%.1f\t%.1f\n", player_x, player_y);
   
// glPopMatrix();  //Retorna ao estado anterior da cena. O que for desenhado ap�s o Push n�o influenciou o j� representado

   glutSwapBuffers(); //Executa a Cena. SwapBuffers d� suporte para mais de um buffer, permitindo execu��o de anima��es sem cintila��es. 
}//fim display

//reseta as variaveis da camera
void resetar_visao(){
      posx = 0;
      posy = 0;
      posz = 0;
      ox   = 0;
      oy   = 0;
      oz   = 0;
}

void keyboard(unsigned char key, int x, int y){//Key - recebe o codigo ASCII da tecla

   //posicoes da camera

   //visao diagonal
   if(key == 'k'){
      visao = 1;
      resetar_visao();
      //ajustando variaveis para visao diagonal
      posz = 4;
      posx = 10;
      posy = player_y;
   }
   //visao frontal
   if(key == 'j'){

      resetar_visao();
      //ajustando variaveis para visao frontal
      posz = 28;
      posx = 0;
      posy = 10;
      oy   = 9;
   }
   //visao lateral
   if(key == 'l'){

      resetar_visao();
      //ajustando variaveis para visao lateral
      posz = 0;
      posx = 10;
      posy = 2;
      oy   = 2;
   }

   //movimentacao horizontal
   if(key == 'a'){
      if(lateral == 1){
         //se estiver na ultima plataforma, o limite da movimentacao e diferente
         if(plat_num > 6){
            if(player_x > plat_fim[0]){
               player_x -= 0.125+lvl_factor/2;
               if(visao == 1 || visao == 2) posx -= 0.125+lvl_factor/2;  
            }  
         }
         else{
            if(player_x > -5.35){
               player_x -= 0.125+lvl_factor/2;
               if(visao == 1 || visao == 2) posx -= 0.125+lvl_factor/2;  
            }
         }
      }
   }
   if(key == 'd'){
      if(lateral == 1){
         //se estiver na ultima plataforma, o limite da movimentacao e diferente
         if(plat_num > 6){
            if(player_x < plat_fim[1]){
               player_x += 0.125+lvl_factor/2;
               if(visao == 1 || visao == 2) posx += 0.125+lvl_factor/2;
            }
         }
         else{
            if(player_x < 5.35){
               player_x += 0.125+lvl_factor/2;
               if(visao == 1 || visao == 2) posx += 0.125+lvl_factor/2;
            }
         }
      }
   }

   //movimentacao vertical
   if(key == 'w'){
      //se nao estiver na ultima plataforma
      if(player_y <= plat_y[6]){
         //se estiver em uma plataforma com escada a direita
         if(subir == 0){
            if(player_x == e1[0]){
               player_y += 0.15; 
               lateral = 0;
               if(visao == 1 || visao == 2) posy += 0.15;            
            }
            //subiu de plataforma
            if(player_y >= plat_y[plat_num]){
               subir = 1;
               lateral = 1;
               plat_num++;
            }
         //se estiver em uma plataforma com escada a esquerda
         }else{
            if(player_x == e2[0]){
               player_y += 0.15; 
               lateral = 0; 
               if(visao == 1 || visao == 2) posy += 0.15;             
            }
            //ultima escada
            if(player_x == e3[0]){
               player_y += 0.15; 
               lateral = 0; 
               if(visao == 1 || visao == 2) posy += 0.15;  
            }
            //subiu de plataforma
            if(player_y >= plat_y[plat_num]){
               subir = 0;
               lateral = 1;
               plat_num++;
            }
         }
      }
   }

   if(key == 's'){
      if(subir == 0){
         if(player_x == e1[0]){
            if(player_y - 0.15 >= plat_y[plat_num-1]){
               player_y -= 0.15; 
               lateral = 0;   
               if(visao == 1 || visao == 2) posy -= 0.15;   
            }      
         }
         if(player_y <= plat_y[plat_num]){
            lateral = 1;
         } 
      }else{
         if(player_x == e2[0]){
            if(player_y - 0.15 >= plat_y[plat_num-1]){
               player_y -= 0.15; 
               lateral = 0; 
               if(visao == 1 || visao == 2) posy -= 0.15;     
            }
            //alcançou a base da plataforma anterior
            if(player_y <= plat_y[plat_num-1]+1.1){
               lateral = 1;
            }         
         }
         //ultima escada
         if(player_x == e3[0]){
            if(player_y - 0.15 >= plat_y[plat_num-1]){
               player_y -= 0.15; 
               lateral = 0;  
               if(visao == 1 || visao == 2) posy -= 0.15;    
            }
            if(player_y <= plat_y[plat_num-1]+1){
               lateral = 1;
            }  
         }
      }
   }
   glutPostRedisplay();
}

void Mouse(int botao, int estado, int x, int y){ 
   //botao  - recebe o codigo do botao pressionado
   //estado - recebe se esta pressionado ou nao
   //x, y   - recebem respectivamente as posicoes do mouse na tela
   switch (botao){
      case GLUT_LEFT_BUTTON:
         if(estado == GLUT_DOWN){
         }
      break;

      case GLUT_RIGHT_BUTTON:
         if(estado == GLUT_DOWN){
         }
      break;
   }
}

//Key - recebe o codigo ASCII da tecla
void TeclasEspeciais (int key, int x, int y){
   //x, y - recebem respectivamente as posi��es mouse na tela (permite tratar os dois dispositivos)
      
   if (key==GLUT_KEY_RIGHT){
   }
   else if (key==GLUT_KEY_PAGE_UP){
      
   }
   else if (key==GLUT_KEY_UP){
      if(posy < 17){
         posy++;
         oy++;
      }  
   }
   else if (key==GLUT_KEY_LEFT){ 
      
   }
   else if (key==GLUT_KEY_PAGE_DOWN){
      
   }
   else if (key==GLUT_KEY_DOWN){      
      if(posy > 0){
         posy--;
         oy--;
      }
   }
   glutPostRedisplay();
}

int main(int argc,char **argv){
   srand(time(NULL));

   glutInit(&argc, argv); // Initializes glut
   
   glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH); 
   //Define as caracteristicas do espaco vetorial. 
   // Nesse caso, permite animacoes (sem cintilacoes), cores compostas por Verm. Verde e Azul,
   // Buffer que permite trablhar com profundidade e elimina faces escondidas.          
  
   // glutInitWindowSize(800, 800);
   // glutInitWindowPosition(100, 100);
   glutCreateWindow("Sweet Climb 0.8");
   glutFullScreen();
   glutDisplayFunc(Display);
   glutMouseFunc(Mouse);
   glutKeyboardFunc(keyboard);
   glutSpecialFunc(TeclasEspeciais);
   glutMainLoop();
   return 0; 
}