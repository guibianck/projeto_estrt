#include <iostream>
#include <vector>
#include <fstream>
#include <chrono>

using namespace std;
using namespace chrono;

//ATENÇÃO, PARA RODAR O CÓDIGO A SEGUIR É NECESSÁRIO USAR UMA VERSÃO DE COMPILADOR QUE SUPORTE A ISO C++ 2011, ALGUMAS BIBLIOTECAS SÓ FUNCIONAM NESSA VERSÃO!!!!!!!!!!!!!!
// Funções de ordenação

void bubbleSort(vector<int> &arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; ++i) {
        for (int j = 0; j < n - i - 1; ++j) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
            }
        }
    }
}

void insertionSort(vector<int> &arr) {
    for (int i = 1; i < arr.size(); i++) {
        int temp = arr[i];
        int j = i - 1;

        while (j >= 0 && arr[j] > temp) {
            arr[j + 1] = arr[j];
            --j;
        }
        arr[j + 1] = temp;
    }
}

int particao_qck(vector<int> &arr, int menor, int maior) {
    int pivo = arr[maior];
    int i = menor - 1;

    for (int j = menor; j <= maior - 1; j++) {
        if (arr[j] < pivo) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[maior]);
    return i + 1;
}

void quickSort(vector<int> &arr, int menor, int maior) {
    if (menor < maior) {
        int pi = particao_qck(arr, menor, maior);

        quickSort(arr, menor, pi - 1);
        quickSort(arr, pi + 1, maior);
    }
}

// Função para imprimir o vetor
void imprimir_vetor(const vector<int> &arr) {
    for (int num : arr) {
        cout << num << " ";
    }
    cout << endl;
}

// Função para salvar o vetor ordenado em um arquivo
void salvar_vetor(const vector<int> &arr, const string &nome_arquivo) {
    ofstream arquivo_saida(nome_arquivo);
    if (arquivo_saida.is_open()) {
        for (int num : arr) {
            arquivo_saida << num << " ";
        }
        arquivo_saida.close();
    } else {
        cerr << "Erro ao abrir o arquivo " << nome_arquivo << endl;
    }
}

int main() {
    string nome_arquivo;
    cout << "Digite o nome do arquivo de entrada: ";
    cin >> nome_arquivo;

    ifstream arquivo_entrada(nome_arquivo);
    if (!arquivo_entrada) {
        cerr << "Erro ao abrir o arquivo " << nome_arquivo << endl;
        return 1;
    }

    vector<int> arr;
    int numero;
    while (arquivo_entrada >> numero) {
        arr.push_back(numero);
    }
    arquivo_entrada.close();

    cout << "Escolha o método de ordenação: \n1. Bubble Sort \n2. Insertion Sort \n3. Quick Sort\n";
    int escolha;
    cin >> escolha;

    auto inicio = high_resolution_clock::now();

    switch (escolha) {
        case 1:
            bubbleSort(arr);
            break;
        case 2:
            insertionSort(arr);
            break;
        case 3:
            quickSort(arr, 0, arr.size() - 1);
            break;
        default:
            cerr << "Escolha inválida!" << endl;
            return 1;
    }

    auto fim = high_resolution_clock::now();
    auto duracao = duration_cast<milliseconds>(fim - inicio);

    cout << "Vetor ordenado:\n";
    imprimir_vetor(arr);

    cout << "Tempo de execução da ordenação: " << duracao.count() << " milissegundos\n";

    salvar_vetor(arr, "vetor_ordenado.txt");
    cout << "Vetor ordenado salvo em 'vetor_ordenado.txt'.\n";

    return 0;
}

