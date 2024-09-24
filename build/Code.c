#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void preencherVetor(int vetor[], int tamanho) { // definição da função, 2 parâmetros (vetor e tamanho)
    srand(time(NULL)); // Inicializa a semente para números aleatórios
    for (int i = 0; i < tamanho; i++) {
        vetor[i] = rand() % 100; // Gera números aleatórios de 0 a 99
    }
}

void imprimirVetor(int vetor[], int tamanho) { // função para imprimir o vetor
    for (int i = 0; i < tamanho; i++) {
        printf("%d ", vetor[i]);
    }
    printf("\n");
}

void shellSort(int vetor[], int tamanho) {  // implementação do ShellSort
    for (int gap = tamanho/2; gap > 0; gap /= 2) {
        for (int i = gap; i < tamanho; i++) { // declaração de variáveis: i para controle do laço principal,
            int temp = vetor[i];              //j para controle do laço interno e aux para armazenar o item comparado
            int j;
            for (j = i; j >= gap && vetor[j-gap] > temp; j -= gap) {
                vetor[j] = vetor[j-gap]; //Ao comparar cada elemento com os elementos anteriores em intervalos de gap,
            }                             //o algoritmo garante que os elementos maiores sejam movidos para suas posições corretas,
            vetor[j] = temp;               //criando subconjuntos ordenados.
        }
    }
}
// implementação do HeapSort
void heapify(int vetor[], int n, int i) {  //Reconstrói a propriedade de heap a partir de um determinado nó.
    int maior = i;
    int esquerda = 2*i + 1;
    int direita = 2*i + 2;

   //Garante que o maior elemento sempre esteja na raiz, assim o Heap Sort pode ordenar os elementos de forma eficiente:
    if (esquerda < n && vetor[esquerda] > vetor[maior]) //Verifica se o índice do filho esquerdo está dentro dos limites do vetor.
        maior = esquerda; //Se o filho esquerdo for maior, atualiza o índice do maior elemento para o filho esquerdo.
    if (direita < n && vetor[direita] > vetor[maior])
        maior = direita; //Se o filho direito for maior, atualiza o índice do maior elemento para o filho direito.

    if (maior != i) { //Verifica se o maior elemento encontrado não é o próprio nó raiz da subárvore. Se for diferente, significa que a propriedade de heap foi violada e precisa ser restaurada.
        int temp = vetor[i]; //Cria uma variável temporária para armazenar o valor do nó raiz.
        vetor[i] = vetor[maior]; //Substitui o valor do nó raiz pelo valor do maior filho.
        vetor[maior] = temp; //Substitui o valor do maior filho pelo valor original do nó raiz, que foi armazenado na variável temporária.
        heapify(vetor, n, maior); //Chama a função heapify para a subárvore com raiz no maior filho.
    }
}

void heapSort(int vetor[], int tamanho) {  // Constrói o heap inicial e, em seguida, extrai repetidamente
    for (int i = tamanho / 2 - 1; i >= 0; i--) // o maior elemento e o coloca no final do vetor.
        heapify(vetor, tamanho, i);


  //O Heap Sort responsável por extrair o maior elemento do heap repetidamente e colocá-lo na sua posição final:
    for (int i = tamanho - 1; i >= 0; i--) { //i é inicializado com o índice do último elemento do vetor.
        int temp = vetor[0];
        vetor[0] = vetor[i];
        vetor[i] = temp;
        heapify(vetor, i, 0); //O loop continua enquanto i for maior ou igual a 0, ou seja, enquanto houver elementos a serem ordenados.
    } //i é decrementado em 1 a cada iteração, movendo-se para o próximo elemento.
}

int main() {
    int vetor[6];
    preencherVetor(vetor, 6);

    printf("Vetor antes da ordenacao:\n");
    imprimirVetor(vetor, 6);

    // Chamando o Shell Sort
    // shellSort(vetor, 6);

    // Chamando o Heap Sort
    heapSort(vetor, 6);

    printf("Vetor apos a ordenacao:\n"); //impressão da lista ordenada
    imprimirVetor(vetor, 6);

    return 0;
}