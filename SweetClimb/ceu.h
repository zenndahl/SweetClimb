
//Função para definição das nuvens
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

void criar_nuvens(){
   //x positivo y positivo
   nuvens(3, 5);
   nuvens(12, 15);
   nuvens(9, 7);
   nuvens(5, 17);

   //x negativo y positivo
   nuvens(-2, 3);
   nuvens(-8, 5);
   nuvens(-3, 13);
   nuvens(-12, 17);
  
}

/*void chao(){
   glPushMatrix();
      glColor3ub(100, 190, 50);
      glTranslatef(0, 0, 3);
      glScalef(35, 0, 12);
      glutSolidCube(1);
   glPopMatrix();
}*/

//Funlçao para criar o Sol
/*void sol(){
   glPushMatrix();
      glColor3ub(253, 184, 53);
      glTranslatef(15, 23, -10);
      glutSolidSphere(3, 50, 50);
   glPopMatrix();
}*/