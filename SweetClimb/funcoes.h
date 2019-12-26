//colisao com a maçã e aumento de nivel (para todas as outras funcoes)
//FUNCIONA?

void delay(int number_of_seconds){ 
    // Converting time into milli_seconds 
    int milli_seconds = 1000 * number_of_seconds; 
  
    // Stroing start time 
    clock_t start_time = clock(); 
  
    // looping till required time is not acheived 
    while (clock() < start_time + milli_seconds); 
}

void posiciona_personagem(){
   glPushMatrix();  
      glTranslatef(player_x, player_y, 0);
      personagem();
   glPopMatrix();
}

void posiciona_brigadeiro(float x, float y){
   glPushMatrix();
      glRotatef(1, 0, 0, 1);
      glColor3ub(123,63,0);
      glTranslatef(x, y, 0);
      glutSolidSphere(0.3, 20,20);
   glPopMatrix();
}

void lvl_up(){
   //aumenta o level
   lvl++;
   // //gera o fator para reposicionamento das escadas
   // lvl_factor = (float)rand()/(float)(RAND_MAX) * 0.5;
   // int sinal = rand()%20;
   // if(sinal >= 1 && sinal <= 10) lvl_factor = -lvl_factor;
   // printf("%.2f\t", lvl_factor);
   // criar_escadas();
   // criar_plataformas();
   
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
   delay(500); 
}

void collision_apple(){
   if(player_y > plat_y[6]){
      if(player_x <= -0.8){
         lvl_up();
      }
   }
}

//Função para imprimir no terminal as posicoes do chao de cada plataforma
void imprime(){
    for(int i = 0; i < 6; i++){
        printf("%2.f\t", plat_y[i]);
    }
}

//Função responsável por resetar as variáveis da câmera
void resetar_visao(){
      posx = 0;
      posy = 0;
      posz = 0;
      ox   = 0;
      oy   = 0;
      oz   = 0;
}

void move_brigadeiro(){
   if(plat_brig%2 == 0){
      if(bx >= e2[1])
         bx -= 0.025;
      if(bx <= e2[1]){
         by -= 0.025;
      }
      if(by <= plat_y[plat_brig-1] - 0.3)
         plat_brig--;
   }
   else{
      if(bx <= e1[1])
         bx += 0.025;
      if(bx >= e1[1]){
         by -= 0.025;
      }
      if(by <= plat_y[plat_brig-1] - 0.3)
         plat_brig--;
   }
   int rotate = 1;

   posiciona_brigadeiro(bx, by);
}

void cria_brigadeiro(){
   int cria = rand()%20 + 1;
   if(cria >=1 && cria <= 6)
      posiciona_brigadeiro(bx_default, by_default);
}