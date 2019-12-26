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

//Função para criação da maçã
void apple(){
    glPushMatrix();
        CorpoEsfera(3, 0, 0.3, 250, 50, 30, 0.3, 50, 50);
    glPopMatrix();
    glPushMatrix();
        glRotatef(45, 1, 0, 0);
        CorpoCubo(3, 1, 0.3, 0.1, 0.6, 0.1, 127, 255, 14, 0.6);
    glPopMatrix();
}

//Função para criação da personagem principal (sorvete)
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