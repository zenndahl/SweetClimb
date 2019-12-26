//Função para criacao das plataformas
void plataformas(float px, float py, float tamanho, int i, float tx){

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
                    glutSolidCube(0.9);
                glPopMatrix();
            }
            //sobre as escadas da direita
            else{
                glPushMatrix();
                glColor3ub(20, 165, 165);
                glTranslatef(tx+0.2, py+3, 0);
                glScalef(0.9, 0.6, 1);
                glutSolidCube(0.9);
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

    //COMENTAR
    plat_y[i] = py + 0.9;
    //COMENTAR
    if(py = 18){
        plat_fim[0] = px-tamanho/2 - 0.2;
        plat_fim[1] = px+tamanho/2 + 0.2;
    }
}

void criar_plataformas(){
   float ey = 0;
   float plat_y[10];
   int i = 0;

   //dados das escadas ------
   float tx = 4.6, ty = 1, tz = -0.65;
   int set = 1;

   //cria as plataformas grandes
   for(i = 0; i < 6; i++){
      plataformas(0,  ey, 5.5, i, tx+lvl_factor);
      ey += 3;
   }
    //plataforma da maçã
   plataformas(0, 18, 1.5, 6, 1.15);
}
   