//Programa exemplo para representacoes de elementos bidimensionais e tridimensionais.
//A estrutura permite manipular diferentes projecoes.
#include "bibliotecas.h"

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
   4.6  (escadas da direita)
   -3.5 (escadas da esquerda)

*Todos os valores foram testados empiricamente e foram os melhores encontrados
*Cuidado ao fazer qualquer alteracao, pode baguncar o cenario
****************************************************/

//Prototipos das Funcoes
void Display();
void Mouse(int botao, int estado, int x, int y);
void keyboard (unsigned char key, int x, int y);
void TeclasEspeciais (int key, int x, int y);

//Função responsáel por mostrar as informações e objetos na tela
void Display(){   
   glEnable(GL_DEPTH_TEST);
   glEnable(GL_LINE_SMOOTH);
   glEnable(GL_POLYGON_SMOOTH);
   glEnable(GL_SMOOTH);
   glEnable(GL_BLEND);

   glClearColor(0.1, 0.65, 0.65, 0);

   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();

   if (projecao == 1)
      glOrtho(-12, 12, -12, 12, -30, 50); //Define a projecao como ortogonal
   else
      gluPerspective(45,1,1,50); //Define a projecao como perspectiva

   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity(); 

   gluLookAt(posx,posy,posz,ox,oy,oz,lx,ly,lz); //Define a posicao da camera, para onde olha e qual eixo esta na vertical.
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 

   criar_plataformas();
   criar_escadas(); 
   init_vet_escadas();
   criar_nuvens();
   //sol();
   //chao();

   //imprime();

   glPushMatrix();  
      glTranslatef(player_x, player_y, 0);
      personagem();
   glPopMatrix();

   glPushMatrix();
      glTranslatef(-4, 18.5, 0);
      apple();
   glPopMatrix();

   glPushMatrix();
   glTranslatef(-4, 15.5, 0);
      cria_vilao();
   glPopMatrix();
   collision_apple();

   //posiciona_brigadeiro(0);

   move_brigadeiro();
   //cria_brigadeiro();
   
   //printf("\n%.1f\t%.1f\n", player_x, player_y);
   
   glutSwapBuffers(); //Executa a Cena. SwapBuffers d� suporte para mais de um buffer, permitindo execu��o de anima��es sem cintila��es. 
}//fim display

//Função responsável pela iteração com o teclado
void keyboard(unsigned char key, int x, int y){
   //Key - recebe o codigo ASCII da tecla
   //posicoes da camera

   //visao diagonal
   if(key == 'k'){
      visao = 1;
      resetar_visao();
      //ajustando variaveis para visao diagonal
      posz = 4;
      posx = 10;
      posy = 5;
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

   //Movimentacao horizontal à esquerda ao pressionar 'a'
   if(key == 'a'){
      if(lateral == 1){
         //se estiver na ultima plataforma, o limite da movimentacao e diferente
         if(plat_num > 6){
            if(player_x > plat_fim[0]){
               player_x -= 0.15;// + lvl_factor;
               if(visao == 1 || visao == 2) posx -= 0.15;// + lvl_factor/2;  
            }  
         }
         else{
            if(player_x > -5.35){
               player_x -= 0.15;// + lvl_factor/2;
               if(visao == 1 || visao == 2) posx -= 0.15;// + lvl_factor;  
            }
         }
      }
   }
   //Movimentacao horizontal à direita ao pressionar 'd'
   if(key == 'd'){
      if(lateral == 1){
         //se estiver na ultima plataforma, o limite da movimentacao e diferente
         if(plat_num > 6){
            if(player_x < plat_fim[1])
               player_x += 0.15;
         }
         else{
            if(player_x < 5.35){
               player_x += 0.15;// + lvl_factor;
               if(visao == 1 || visao == 2) posx += 0.15;// + lvl_factor;
            }
         }
      }
   }

   //Movimentacao vertical para cima ao pressionar 'w'
   if(key == 'w'){
      //se nao estiver na ultima plataforma
      if(player_y <= plat_y[6]){
         //se estiver em uma plataforma com escada a direita
         if(subir == 0){
            if(player_x >= e1[0] && player_x <= e1[1]){
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
            if(player_x <= e2[0] && player_x >= e2[1]){
               player_y += 0.15; 
               lateral = 0; 
               if(visao == 1 || visao == 2) posy += 0.15;             
            }
            //ultima escada
            if(player_x >= e3[0] && player_x<= e3[1]){
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

   //Movimentacao vertical para baixo ao pressionar 's'
   if(key == 's'){
      if(subir == 0){
         if(player_x >= e1[0] && player_x<= e1[1]){
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
         if(player_x <= e2[0] && player_x >= e2[1]){
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
         if(player_x >= e3[0] && player_x<= e3[1]){
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

   if(key == ' '){
      Pulo();
      velocidade = -0.4;
      
   }

   glutPostRedisplay();
}

//Função responsável pela iteração com o mouse
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

//Função responsável pela iteraçãgio com as setas do teclado
void TeclasEspeciais (int key, int x, int y){
   //x, y - recebem respectivamente as posi��es mouse na tela (permite tratar os dois dispositivos)
      
   if (key==GLUT_KEY_RIGHT){
   }
   else if (key==GLUT_KEY_PAGE_UP){
      
   }
   else if (key==GLUT_KEY_UP){
      if(posy < 20){
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

//Função main do programa, responsável por chamar as outras funções
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