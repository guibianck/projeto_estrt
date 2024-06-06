#include <iostream>
#include <vector>
#include <fstream>
#include <chrono>

using namespace std;
using namespace chrono;

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
void imprimirVetor(const vector<int> &arr) {
    for (int num : arr) {
        cout << num << " ";
    }
    cout << endl;
}

// Função para salvar o vetor ordenado em um arquivo
void salvarVetor(const vector<int> &arr, const string &filename) {
    ofstream outputFile(filename);
    if (outputFile.is_open()) {
        for (int num : arr) {
            outputFile << num << " ";
        }
        outputFile.close();
    } else {
        cerr << "Erro ao abrir o arquivo " << filename << " para escrita." << endl;
    }
}

int main() {
    string filename;
    cout << "Digite o nome do arquivo de entrada: ";
    cin >> filename;

    ifstream inputFile(filename);
    if (!inputFile) {
        cerr << "Erro ao abrir o arquivo " << filename << endl;
        return 1;
    }

    vector<int> arr;
    int number;
    while (inputFile >> number) {
        arr.push_back(number);
    }
    inputFile.close();

    cout << "Escolha o método de ordenação: \n1. Bubble Sort \n2. Insertion Sort \n3. Quick Sort\n";
    int escolha;
    cin >> escolha;

    auto start = high_resolution_clock::now();

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

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(stop - start);

    cout << "Vetor ordenado:\n";
    imprimirVetor(arr);

    cout << "Tempo de execução da ordenação: " << duration.count() << " milissegundos\n";

    salvarVetor(arr, "vetor_ordenado.txt");
    cout << "Vetor ordenado salvo em 'vetor_ordenado.txt'.\n";

    return 0;
}

