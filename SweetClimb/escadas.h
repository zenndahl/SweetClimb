//Função de criacao das escadas
void escadas(float tx, float ty, float tz){

   glColor3ub(255, 253, 208);
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

   // escadas[cont_escadas] = tx+0.3;
   // cont_escadas++;
   // escadas[cont_escadas] = tx+0.5;
   // cont_escadas++;

   glutPostRedisplay();
}//fim escadas

void escadas_quebradas(float tx, float ty, float tz, int set, int i){
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

   if(i%2 == 0){
      q1[0] = (set*tx-2.6-space) + 0.3;
      q1[1] = (set*tx-2.6-space) + 0.4;
   }
   else{
      q2[0] = (set*tx-2.6-space) + 0.3;
      q2[1] = (set*tx-2.6-space) + 0.4;
   }
   

}//fim escadas quebradas

//gera todos os dados necessarios para as criacoes das escadas e das escadas quebradas
void criar_escadas(){
   float tx = 4.6, ty = 1.2, tz = -0.65;
   //variavel para ajeitar a posicao das escadas quebradas
   int set = 1;

   //cria todas as escadas em suas devidas posicoes
   for(int i = 0; i < 5; i++){
      escadas(tx+lvl_factor, ty, tz);
      escadas_quebradas(tx-lvl_factor, ty-0.3, tz, set, i);
      tx = -tx;
      ty += 3;
      set *= -1;
   }
   //escada da ultima plataforma
   escadas(0.8, 16.5, tz);
}

//Cria os vetores com as posicoes de x das escadas em que será possível subí-las
void init_vet_escadas(){
   //escadas da direita
   e1[0] = 4.75;
   e1[1] = 4.95;

   //escadas da esquerda
   e2[0] = -4.25;
   e2[1] = -4.40;

   //escada da ultima plataforma
   e3[0] = 1;
   e3[1] = 1.15;
}