#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

#define TAMANHO_PALAVRA 20
#define MAX_TENTATIVAS 5

/* Protótipos das funções */
int letraexiste(char letra);
int chuteserrados(void);
int enforcou(void);
int ganhou(void);
int jachutou(char letra);
int normalizapalavra(char palavra[]);
void descartalinha(void);
int lepalavra(FILE *arquivo, char palavra[]);
int contapalavras(void);
void abertura(void);
void chuta(void);
void desenhaforca(void);
void escolhepalavra(void);
void adicionapalavra(void);

char palavrasecreta[TAMANHO_PALAVRA];
char chutes[26];
int chutesdados = 0;

/* Verifica se uma letra pertence a palavra secreta */
int letraexiste(char letra) {
    for (int i = 0; palavrasecreta[i] != '\0'; i++) {
        if (letra == palavrasecreta[i]) {
            return 1;
        }
    }

    return 0;
}

/* Conta os chutes incorretos. */
int chuteserrados(void) {
    int erros = 0;

    for (int i = 0; i < chutesdados; i++) {
        if (!letraexiste(chutes[i])) {
            erros++;
        }
    }

    return erros;
}

/* Verifica se o jogador perdeu */
int enforcou(void) {
    return chuteserrados() >= MAX_TENTATIVAS;
}

/* Verifica se todas as letras foram descobertas */
int ganhou(void) {
    for (int i = 0; palavrasecreta[i] != '\0'; i++) {
        if (!jachutou(palavrasecreta[i])) {
            return 0;
        }
    }

    return 1;
}

/* Verifica se uma letra ja foi digitada */
int jachutou(char letra) {
    for (int i = 0; i < chutesdados; i++) {
        if (chutes[i] == letra) {
            return 1;
        }
    }

    return 0;
}

/* Converte uma palavra para maiusculas e valida seu conteudo.
   Esta versao aceita apenas letras de A a Z, sem acentos */
int normalizapalavra(char palavra[]) {
    palavra[strcspn(palavra, "\r\n")] = '\0';

    size_t tamanho = strlen(palavra);

    if (tamanho == 0 || tamanho >= TAMANHO_PALAVRA) {
        return 0;
    }

    for (size_t i = 0; i < tamanho; i++) {
        unsigned char caractere = (unsigned char) palavra[i];
        caractere = (unsigned char) toupper(caractere);

        if (caractere < 'A' || caractere > 'Z') {
            return 0;
        }

        palavra[i] = (char) caractere;
    }

    return 1;
}

/* Descarta o restante de uma linha muito longa */
void descartalinha(void) {
    int caractere;

    while ((caractere = getchar()) != '\n' && caractere != EOF) {
        /* Continua ate o fim da linha */
    }
}

/* Le uma linha do banco de palavras e retorna apenas palavras validas */
int lepalavra(FILE *arquivo, char palavra[]) {
    char linha[256];

    while (fgets(linha, sizeof(linha), arquivo) != NULL) {

        if (strchr(linha, '\n') == NULL && !feof(arquivo)) {
            descartalinha();
            continue;
        }

        if (!normalizapalavra(linha)) {
            continue;
        }

        strcpy(palavra, linha);
        return 1;
    }

    return 0;
}

/* Conta as palavras validas existentes no arquivo */
int contapalavras(void) {
    FILE *arquivo = fopen("palavras.txt", "r");

    if (arquivo == NULL) {
        return -1;
    }

    int quantidade = 0;
    char palavra[TAMANHO_PALAVRA];

    while (lepalavra(arquivo, palavra)) {
        quantidade++;
    }

    fclose(arquivo);
    return quantidade;
}

/* Apresentacao inicial do jogo */
void abertura(void) {
    printf("/****************/\n");
    printf("/ Jogo de Forca */\n");
    printf("/****************/\n\n");
}

/* Solicita e registra uma letra valida */
void chuta(void) {
    char entrada[128];
    char chute;

    while (1) {
        printf("Qual letra? ");

        if (fgets(entrada, sizeof(entrada), stdin) == NULL) {
            printf("\nEntrada encerrada.\n");
            exit(0);
        }

        if (strchr(entrada, '\n') == NULL && !feof(stdin)) {
            descartalinha();
            printf("Entrada muito longa. Digite apenas uma letra.\n\n");
            continue;
        }

        char *p = entrada;

        while (isspace((unsigned char) *p)) {
            p++;
        }

        if (*p == '\0') {
            printf("Digite uma letra de A a Z.\n\n");
            continue;
        }

        chute = (char) toupper((unsigned char) *p);
        p++;

        while (isspace((unsigned char) *p)) {
            p++;
        }

        if (chute < 'A' || chute > 'Z' || *p != '\0') {
            printf("Entrada inválida. Digite apenas uma letra de A a Z.\n\n");
            continue;
        }

        if (jachutou(chute)) {
            printf("Você já tentou essa letra! Escolha outra.\n\n");
            continue;
        }

        break;
    }

    chutes[chutesdados] = chute;
    chutesdados++;

    if (letraexiste(chute)) {
        printf("Você acertou! A palavra tem a letra %c.\n\n", chute);
    } else {
        printf("Você errou! A palavra não tem a letra %c.\n\n", chute);
    }
}

/* Desenha a forca e mostra as letras descobertas */
void desenhaforca(void) {
    int erros = chuteserrados();

    printf("  _______       \n");
    printf(" |/      |      \n");
    printf(" |      %c%c%c  \n",
           (erros >= 1 ? '(' : ' '),
           (erros >= 1 ? '_' : ' '),
           (erros >= 1 ? ')' : ' '));
    printf(" |      %c%c%c  \n",
           (erros >= 3 ? '\\' : ' '),
           (erros >= 2 ? '|' : ' '),
           (erros >= 3 ? '/' : ' '));
    printf(" |       %c     \n", (erros >= 2 ? '|' : ' '));
    printf(" |      %c %c   \n",
           (erros >= 4 ? '/' : ' '),
           (erros >= 4 ? '\\' : ' '));
    printf(" |              \n");
    printf("_|___           \n\n");

    printf("Erros: %d de %d\n\n", erros, MAX_TENTATIVAS);

    for (int i = 0; palavrasecreta[i] != '\0'; i++) {
        if (jachutou(palavrasecreta[i])) {
            printf("%c ", palavrasecreta[i]);
        } else {
            printf("_ ");
        }
    }

    printf("\n\n");
}

/* Escolhe uma palavra aleatoria do arquivo */
void escolhepalavra(void) {
    FILE *arquivo = fopen("palavras.txt", "r");

    if (arquivo == NULL) {
        printf("Não foi possível abrir o banco de palavras.\n");
        exit(1);
    }

    int quantidade = contapalavras();

    if (quantidade <= 0) {
        printf("O banco de palavras está vazio ou não contém palavras válidas.\n");
        fclose(arquivo);
        exit(1);
    }

    int sorteada = rand() % quantidade;
    char palavra[TAMANHO_PALAVRA];

    for (int i = 0; i <= sorteada; i++) {
        if (!lepalavra(arquivo, palavra)) {
            printf("Erro ao ler o banco de palavras.\n");
            fclose(arquivo);
            exit(1);
        }
    }

    strcpy(palavrasecreta, palavra);
    fclose(arquivo);
}

/* Permite adicionar palavras ao banco de dados */
void adicionapalavra(void) {
    char entrada[128];

    printf("Deseja adicionar uma nova palavra? (S/N): ");

    if (fgets(entrada, sizeof(entrada), stdin) == NULL) {
        return;
    }

    if (strchr(entrada, '\n') == NULL && !feof(stdin)) {
        descartalinha();
        printf("Entrada inválida.\n");
        return;
    }

    char resposta = (char) toupper((unsigned char) entrada[0]);

    if (resposta != 'S') {
        return;
    }

    char novapalavra[128];

    printf("Digite a nova palavra, sem acentos: ");

    if (fgets(novapalavra, sizeof(novapalavra), stdin) == NULL) {
        return;
    }

    if (strchr(novapalavra, '\n') == NULL && !feof(stdin)) {
        descartalinha();
        printf("Palavra muito longa.\n");
        return;
    }

    if (!normalizapalavra(novapalavra)) {
        printf("Palavra inválida. Use de 1 a %d letras, sem acentos.\n",
               TAMANHO_PALAVRA - 1);
        return;
    }

    FILE *arquivo = fopen("palavras.txt", "a+");

    if (arquivo == NULL) {
        printf("Não foi possível abrir o banco de palavras.\n");
        return;
    }

    /* Evita juntar a nova palavra a ultima linha do arquivo */
    if (fseek(arquivo, 0, SEEK_END) != 0) {
        printf("Não foi possível acessar o banco de palavras.\n");
        fclose(arquivo);
        return;
    }

    long tamanho = ftell(arquivo);

    if (tamanho > 0) {
        if (fseek(arquivo, -1, SEEK_END) != 0) {
            printf("Não foi possível acessar o banco de palavras.\n");
            fclose(arquivo);
            return;
        }

        int ultimo = fgetc(arquivo);

        if (ultimo != '\n') {
            if (fseek(arquivo, 0, SEEK_END) != 0 ||
                fputc('\n', arquivo) == EOF) {
                printf("Erro ao preparar o arquivo.\n");
                fclose(arquivo);
                return;
            }
        }
    }

    if (fprintf(arquivo, "%s\n", novapalavra) < 0 ||
        fclose(arquivo) != 0) {
        printf("Erro ao salvar a nova palavra.\n");
        return;
    }

    printf("Palavra adicionada com sucesso!\n");
}

int main(void) {
    srand((unsigned int) time(NULL));

    abertura();
    escolhepalavra();

    do {
        desenhaforca();
        chuta();
    } while (!ganhou() && !enforcou());

    desenhaforca();

    if (ganhou()) {
        printf("Parabéns, você ganhou!\n\n");

        printf("       ___________      \n");
        printf("      '._==_==_=_.'     \n");
        printf("      .-\\:      /-.    \n");
        printf("     | (|:.     |) |    \n");
        printf("      '-|:.     |-'     \n");
        printf("        \\::.    /      \n");
        printf("         '::. .'        \n");
        printf("           ) (          \n");
        printf("         _.' '._        \n");
        printf("        '-------'       \n\n");
    } else {
        printf("Puxa, você perdeu! A palavra era %s.\n\n", palavrasecreta);

        printf("    _______________         \n");
        printf("   /               \\       \n");
        printf("  /                 \\      \n");
        printf("//                   \\/\\  \n");
        printf("\\|   XXXX     XXXX   | /   \n");
        printf(" |   XXXX     XXXX   |/     \n");
        printf(" |   XXX       XXX   |      \n");
        printf(" |                   |      \n");
        printf(" \\__      XXX      __/     \n");
        printf("   |\\     XXX     /|       \n");
        printf("   | |           | |        \n");
        printf("   | I I I I I I I |        \n");
        printf("   |  I I I I I I  |        \n");
        printf("   \\_             _/       \n");
        printf("     \\_         _/         \n");
        printf("       \\_______/           \n\n");
    }

    adicionapalavra();

    return 0;
}