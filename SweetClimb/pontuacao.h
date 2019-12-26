//Função para cadastrar o nome do jogador
int cadastrar(){
    FILE *novo;
    char nome[20];    

    printf("\nDigite seu nome: ");
    scanf("%[^\n]", nome);
    getchar();
    
    //Abre o arquivo para escrita
    novo = fopen("score.txt", "a");
    fprintf(novo, "%s\n", nome);

    //Fechando arquivo
    fclose(novo);
}

//Função que salva a pontuação final do jogador
void pontuacao(int pontos){
    FILE *novo;
    
    //Abre o arquivo para escrita
    novo = fopen("score.txt", "a");
    fprintf(novo, "%d\n", pontos);

    //Fechando arquivo
    fclose(novo);
}

//Função para mostrar na tela o score dos jogadores
int mostrar_pontos(){
    FILE *novo;
    char nome[20];
    int pontos;
    
    //Abre o arquivo para leitura
    novo = fopen("score.txt", "r");
    while (!feof(novo)){
        fscanf(novo, "%[^\n]", nome);
        fscanf(novo, "%d", &pontos);
        if (pontos == EOF) break;
        printf("%s\t %d\n", nome, pontos);
    }
}