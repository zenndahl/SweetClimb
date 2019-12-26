void Velocidade()
{
    velocidade = velocidade*tempo - gravidade*tempo;
}

void Pulo (){
    float novo_y;
    novo_y =  player_y + velocidade*tempo - ((gravidade*tempo*tempo)/2);
    //condições para impedir de "pular para baixo" (ultrapassar o limite inferior da plataforma)
    if(novo_y<1.0 && plat_num==1)
    {
        novo_y = 2.0;
        velocidade = 0.0;
    }
    if(novo_y<3.0 && plat_num==2)
    {
        novo_y = 4.0;
        velocidade = 0.0;
    }
    if(novo_y<7.0 && plat_num==3)
    {
        novo_y = 8.0;
        velocidade = 0.0;
    }
    if(novo_y<10.0 && plat_num==4)
    {
        novo_y = 11.0;
        velocidade = 0.0;
    }
    if(novo_y<13.0 && plat_num==5)
    {
        novo_y = 14.0;
        velocidade = 0.0;
    }
    if(novo_y<16.0 && plat_num==6)
    {
        novo_y = 17.0;
        velocidade = 0.0;
        
    }

    //condições para impedir de pular demais (ultrapassar o limite superior da plataforma)
    if(novo_y>=2.0 && plat_num==1)
    {
        novo_y = 2.0;
        velocidade = 0.0;
    }
    if(novo_y>=5.0 && plat_num==2)
    {
        novo_y = 5.0;
        velocidade = 0.0;
    }
    if(novo_y>=8.0 && plat_num==3)
    {
        novo_y = 8.0;
        velocidade = 0.0;
    }
    if(novo_y>=11.0 && plat_num==4)
    {
        novo_y = 11.0;
        velocidade = 0.0;
    }
    if(novo_y>=14.0 && plat_num==5)
    {
        novo_y = 14.0;
        velocidade = 0.0;
    }
    if(novo_y>=17.0 && plat_num==6)
    {
        novo_y = 17.0;
        velocidade = 0.0;
    }

    player_y = novo_y;

    Velocidade();
    glutPostRedisplay();
}


void vilainDance (){
    glRotatef(180, 1, 0, 0);
}

/*void QuedaBrigadeiro(float x_brig, float y_brig)
{
    if(y_brig<)
    {
        x_brig = x_brig-0.4;
        y_brig = y_brig-0.44;
    }
    
}*/

void RotateBrigadeiro(float x_brig, float y_brig)
{
    glRotatef(45,0,0,1);
    x_brig = x_brig+0.3;
}