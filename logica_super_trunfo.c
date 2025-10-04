#include <stdio.h>
#include <string.h>
#include <stdlib.h>


// Estrutura ( Struct) para representar uma carta de Super Trunfo
// Agrupa todas as propriedades de uma cidade em um unico tipo de dado.
struct CartaSuperTrunfo{
    char Estado;
    char Codigo_carta[5]; // Ex: "A01", "B02" 
    char Nome_Cidade[50]; // Tamanho suficiente 
    unsigned long int populacao; // para acomodar grandes numeros
    float area_km2; // Área em km²
    float pib; // PIB em Bilhões de Reais
    int num_pontos_turisticos;

    // Atributos calculados
    float densidade_populacional; // hab/km²
    float pib_per_capita;
    float super_poder; // Soma dos atributos ponderados
};

// Prototipos das funções
// Funções para ler e exibir os dados e cálculo de estatísticas.
void lerDadosCarta(struct CartaSuperTrunfo *carta);
void exibirDadosCarta(const struct CartaSuperTrunfo *carta);
void calcularAtributosEstatisticos(struct CartaSuperTrunfo *carta);
void compararCartas(const struct CartaSuperTrunfo *carta1, const struct CartaSuperTrunfo *carta2);
// Nova Função: Compara apenas um atributo específico.
void compararAtributoUnico(const struct CartaSuperTrunfo *c1, const struct CartaSuperTrunfo *c2);


int main(){
    // Declara duas variaveis do tipo CartaSuperTrunfo
    struct CartaSuperTrunfo carta1, carta2;

    printf("\n =================================\n");
    printf(" || CADASTRO DE CARTAS SUPER TRUNFO ||\n");
    printf(" ====================================\n");

    // Leitura dos dados da primeira carta
    printf("\n Cadastro da Primeira Carta\n");
    lerDadosCarta(&carta1);

    // Leitura dos dados da segunda carta
    printf("\n Cadastro da Segunda Carta\n");
    lerDadosCarta(&carta2);
    
    // Cálculo de todos os atributos estatísticos para ambas as cartas
    calcularAtributosEstatisticos(&carta1);
    calcularAtributosEstatisticos(&carta2);

    // Exibição dos dados cadastrados e cálculos
    printf("\n\n Dados das Cartas Cadastradas\n");

    printf("\nCarta 1 (%s):\n", carta1.Nome_Cidade);
    exibirDadosCarta(&carta1);

    printf("\nCarta 2 (%s):\n", carta2.Nome_Cidade);
    exibirDadosCarta(&carta2);

    // Desafio final: Comparação das Cartas (Batalha Completa)
    printf("\n\n ======================\n");
    printf("|| RESULTADO DA BATALHA DE TODOS OS ATRIBUTOS ||\n");
    printf("==============================\n");
    compararCartas(&carta1, &carta2);

    // Requisito do Desafio: Batalha por atributo único (PIB per Capita)
    printf("\n\n ===============================\n");
    printf("|| BATALHA ESCOLHIDA (PIB PER CAPITA) ||\n");
    printf("=====================================\n");
    compararAtributoUnico(&carta1, &carta2);

    return 0;
}

// Implementação da Função para ler os dados de uma Carta
void lerDadosCarta(struct CartaSuperTrunfo *carta){
    int c;

    printf(" Estado ");
    scanf(" %c", &carta->Estado);

    printf("Código da Carta: ");
    scanf("%s", carta->Codigo_carta);

    // Limpa o buffer de entrada (CRUCIAL para o scanf com [^\n])
    while ((c = getchar()) != '\n' && c != EOF) { }

    printf("Nome da Cidade: ");
    scanf("%49[^\n]", carta->Nome_Cidade);

    printf("Populacao: (unsigned long int): ");
    scanf("%lu", &carta->populacao); //lu para unsigned long int

    printf("Area (km2): ");
    scanf("%f", &carta->area_km2);

    printf(" PIB (em bilhões de R$): ");
    scanf("%f", &carta->pib);

    printf("Número de Pontos Turísticos: ");
    scanf("%d", &carta->num_pontos_turisticos);

}


// Implementação da função para exibir os dados de uma carta
void exibirDadosCarta(const struct CartaSuperTrunfo *carta){

    printf(" Estado: %c\n", carta->Estado);
    printf(" Codigo: %s\n", carta->Codigo_carta);
    printf(" Nome da Cidade: %s\n", carta->Nome_Cidade);
    printf(" Populacao: %lu\n", carta->populacao);
    printf(" Area: %.2f Km²\n", carta->area_km2);
    printf(" PIB: %.2f bilhões de reais\n", carta->pib);
    printf(" Pontos Turísticos: %d\n", carta->num_pontos_turisticos);
    printf(" Densidade Populacional: %.2f hab/km²\n", carta->densidade_populacional);
    printf(" PIB per Capita: R$ %.2f", carta->pib_per_capita);
    printf(" Super Poder: %.4f\n", carta->super_poder);
    
}

//Implementação da função de calcular os atributos estatísticos
void calcularAtributosEstatisticos(struct CartaSuperTrunfo *carta){
    // Calculo de Densidade Populacional: População / Área (hab/km²)
    // Conversão de ( unsigned long int) para (float)
    if (carta->area_km2 != 0.0f){
        carta->densidade_populacional = (float)carta->populacao / carta->area_km2;
    } else {
        carta->densidade_populacional = 0.0f;
    }

    // Calculo do PIB per capita: (PIB * 1.000.000.000) / população ( R$ )
    // PIB lido em bilhões, por isso a multiplicação (1,000,000,000.0f)
    if(carta->populacao > 0){
        carta->pib_per_capita = (carta->pib * 1000000000.0f) / carta->populacao;
    } else {
        carta->pib_per_capita = 0.0f;
    }

    // Calculo do Super Poder
    float inverso_densidade = 0.0f;
    if (carta->densidade_populacional > 0){
        // Quanto menor a Densidade, maior o poder (1/X)
        inverso_densidade = 1.0f / carta->densidade_populacional;
    }

    // A população é um termo muito grande, o que pode levar a um super_poder dominado por ela
    carta->super_poder = (float)carta->populacao + 
                      carta->area_km2 + 
                      carta->pib + 
                      (float)carta->num_pontos_turisticos + 
                      carta->pib_per_capita +
                      inverso_densidade;
}

// Implementação da função para comparar todas as cartas e exibir o resultado
void compararCartas(const struct CartaSuperTrunfo *c1, const struct CartaSuperTrunfo *c2) {
    int resultado; // 1 se carta 1 venceu, 0 se carta 2 venceu ( ou empate)

    printf("\nBatalha por Atributo:\n");

    // População ( Maior vence)
    // Conversão para long double para maior precisão na comparação de numeros grandes
    resultado = ((long double)c1->populacao > (long double)c2->populacao);
    printf(" - Populção: Carta %d venceu (C1: %lu, C2: %lu)\n",
           resultado ? 1: 2, c1->populacao, c2->populacao);

    // Área maior vence
    resultado = (c1->area_km2 > c2->area_km2);
    printf(" - Área: Carta %d venceu (C1: %.2f, C2: %.2f)\n",
          resultado ? 1: 2, c1->area_km2, c2->area_km2 );

    // PIB maior vence
    resultado = (c1->pib > c2->pib);
    printf(" - PIB: Carta %d venceu (C1: %.2f, C2: %.2f)\n",
          resultado ? 1: 2, c1->pib, c2->pib ); 
          
    // Pontos Turísticos maior vence
    resultado = (c1->num_pontos_turisticos > c2->num_pontos_turisticos);
    printf(" - Pontos Turísticos: Carta %d venceu (C1: %d, C2: %d)\n",
          resultado ? 1: 2, c1->num_pontos_turisticos, c2->num_pontos_turisticos);
    
    // Densidade Populacional (Menor vence)
    // Lógica invertida: C1 vence se C1 for MENOR que C2
    resultado = (c1->densidade_populacional < c2->densidade_populacional);
    printf(" - Densidade Populacional: Carta %d venceu (C1: %.2f, C2: %.2f)\n", 
           resultado ? 1 : 2, c1->densidade_populacional, c2->densidade_populacional);
    
    // PIB per Capita (Maior vence)
    resultado = (c1->pib_per_capita > c2->pib_per_capita);
    printf(" - PIB per Capita: Carta %d venceu (C1: %.2f, C2: %.2f)\n", 
           resultado ? 1 : 2, c1->pib_per_capita, c2->pib_per_capita);

    // Super Poder (Maior vence)
    resultado = (c1->super_poder > c2->super_poder);
    printf(" - Super Poder: Carta %d venceu (C1: %.4f, C2: %.4f)\n", 
           resultado ? 1 : 2, c1->super_poder, c2->super_poder);
}

//Implementação da função que compara UM ÚNICO atributo escolhido (PIB per Capita)
void compararAtributoUnico(const struct CartaSuperTrunfo *c1, const struct CartaSuperTrunfo *c2) {
    // Escolhemos 'PIB per Capita' como atributo de comparação (MAIOR VENCE).
    const char *atributo_nome = "PIB per Capita (O maior valor vence)";
    float valor1 = c1->pib_per_capita;
    float valor2 = c2->pib_per_capita;
    int carta_vencedora = 0; // 1 para carta1, 2 para carta2, 0 para empate.

    // Determina o vencedor. Para PIB per Capita, o MAIOR valor vence.
    if (valor1 > valor2) {
        carta_vencedora = 1; // Carta 1 venceu
    } else if (valor2 > valor1) {
        carta_vencedora = 2; // Carta 2 venceu
    } else {
        carta_vencedora = 0; // Empate
    }

    printf("\nComparação de Cartas (Atributo: %s):\n", atributo_nome);
    printf("Carta 1 - %s (%c): R$ %.2f\n", c1->Nome_Cidade, c1->Estado, valor1);
    printf("Carta 2 - %s (%c): R$ %.2f\n", c2->Nome_Cidade, c2->Estado, valor2);
    
    // Exibe o resultado final
    if (carta_vencedora == 1) {
        printf("Resultado: Carta 1 (%s) venceu!\n", c1->Nome_Cidade);
    } else if (carta_vencedora == 2) {
        printf("Resultado: Carta 2 (%s) venceu!\n", c2->Nome_Cidade);
    } else {
        printf("Resultado: Empate!\n");
    }
}

    /* data */
         

