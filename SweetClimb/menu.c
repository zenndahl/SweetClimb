#include <stdlib.h>
#include <stdio.h>
#include <GL/freeglut.h>
#include <GL/glut.h>
#include <GL/gl.h>
#include <math.h>

//Declaracao de Variaveis Globais
int posx = 0, posy =5, posz = 20; //Variaveis que definem a posicao da camera
int oy = 0,ox = 0,oz = 0;          //Variaveis que definem para onde a camera olha
int lx = 0, ly = 1,  lz = 0;       //Variaveis que definem qual eixo estara na vertical do monitor. //NAO MUDAR
//variaveis para movimentacao do personagem
float player_x = -4, player_y = 1;
int lateral = 1;

void Display(){
   
   glEnable(GL_DEPTH_TEST);

   glEnable(GL_LINE_SMOOTH);
   glEnable(GL_POLYGON_SMOOTH); 

   glEnable(GL_SMOOTH);
   glEnable(GL_BLEND);

   // Inicializa par�metros de rendering
   // Define a cor de fundo da janela de visualizacao como preta
   //glClearColor(0.3, 0.0, 1.0, 0.0);
   glClearColor(0, 0, 0, 0);

   glMatrixMode(GL_PROJECTION);
   //glMatrixMode()- define qual matriz ser� alterada. SEMPRE defina o tipo de apresentacao 
   //(Ortogonal ou Perspectiva) na matriz PROJECTION.
   glLoadIdentity();//"Limpa" ou "transforma" a matriz em identidade, reduzindo possiveis erros.

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

   glColor3ub(255, 0, 0);
   glScalef(2, 0.5, 0);
   glutSolidCube(2);

  
   glutSwapBuffers(); //Executa a Cena. SwapBuffers d� suporte para mais de um buffer, permitindo execu��o de anima��es sem cintila��es. 
}//fim display

void keyboard(unsigned char key, int x, int y){//Key - recebe o codigo ASCII da tecla
    
   
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

   glutInit(&argc, argv); // Initializes glut
   
   glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH); 
   //Define as caracteristicas do espaco vetorial. 
   // Nesse caso, permite animacoes (sem cintilacoes), cores compostas por Verm. Verde e Azul,
   // Buffer que permite trablhar com profundidade e elimina faces escondidas.          
  
   glutInitWindowSize(800, 800);
   glutInitWindowPosition(100, 100);
   glutCreateWindow("Sweet Climb 0.8");
   //glutFullScreen();
   glutDisplayFunc(Display);
   glutMouseFunc(Mouse);
   glutKeyboardFunc(keyboard);
   glutSpecialFunc(TeclasEspeciais);
   glutMainLoop();
   return 0; 
}