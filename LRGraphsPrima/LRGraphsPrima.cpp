#include <iostream>
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <iomanip>

using namespace std;

#define Verticles 10 // Кол-во вершин

int minKey(int key[], bool mstSet[]);
void printOstov(int parent[], int graph[Verticles][Verticles]);
void primOstov(int graph[Verticles][Verticles]);

int main() {

    setlocale(LC_ALL, "Russian");
    system("color F0");

    int graph[Verticles][Verticles] = { { 0, 5, 0, 3, 6, 0, 0, 0, 0, 8 },
                        { 5, 0, 2, 0, 0, 0, 2, 0, 0, 0 },
                        { 0, 3, 0, 0, 0, 1, 0, 5, 0, 0 },
                        { 3, 0, 0, 0, 0, 0, 2, 0, 0, 0 },
                        { 6, 0, 0, 0, 0, 0, 0, 9, 0, 7 },
                        { 0, 0, 1, 0, 0, 0, 3, 0, 8, 0 },
                        { 0, 2, 0, 2, 0, 3, 0, 0, 0, 0 },
                        { 0, 0, 5, 0, 9, 0, 0, 0, 7, 1 },
                        { 0, 0, 0, 0, 0, 8, 0, 7, 0, 0 },
                        { 8, 0, 0, 0, 7, 0, 0, 1, 0, 0 }, };

    cout << "Остовное дерево построенное по алгоритму Прима\n\n";
    
    primOstov(graph); // построение по Приме

    return 0;
}

//Функция для поиска вершины с минимальным значением ключа из набора вершин, еще не включенных в остов
int minKey(int key[], bool mstSet[])
{
    //Инициализировать минимальное значение
    int min = INT_MAX;
    int min_index = 0;

    for (int v = 0; v < Verticles; v++)
        if (mstSet[v] == false && key[v] < min) {
            min = key[v], min_index = v;
            cout << "Вес текущий " << min << " номер вершины " << min_index + 1 << endl;
        }

    return min_index;
}

//Служебная функция для печати
//построенного остова, хранящегося в родительском массиве[]
void printOstov(int parent[], int graph[Verticles][Verticles])
{
    cout << "Вершины \tВес\n";
    for (int i = 1; i < Verticles; i++)
        cout << parent[i] + 1 << " - " << i  << " \t\t" << graph[i][parent[i]] << " \n";
}

//Функция для построения и печати остова для график, представленный с использованием смежности
// матричное представление
void primOstov(int graph[Verticles][Verticles])
{
    int parent[Verticles]; // Массив вершин графа для хранения построенного остова
    int key[Verticles]; // Значение весов в остовном графе
    bool mstSet[Verticles]; // Отметок набора вершин, включенных в остов

    for (int i = 0; i < Verticles; i++) // Инициализируйте все ключи бесконечностью
        key[i] = INT_MAX, mstSet[i] = false;

    key[0] = 0; // Включаем первую 1-ю вершину в остов. Значение веса 0
    parent[0] = -1; // Первый узел является корнем остова

    // Остов будет иметь Verticles вершин
    for (int count = 0; count < Verticles - 1; count++)
    {
        //Выбор минимальной вершину из набора вершин, еще не включенных в остов
        int u = minKey(key, mstSet);

        mstSet[u] = true; // Добавляем выбранную вершину в набор остова
        cout << "Добавляем вершину с минимальным весом остова " << u + 1<< "\n" << endl;
        // Обновляем значение веса ребра и вершину старта
        
        for (int v = 0; v < Verticles; v++)            
            if (graph[u][v] && mstSet[v] == false && graph[u][v] < key[v]) { // Рассматривайте только те вершины, которые не являются все еще включенный в остов
                parent[v] = u, key[v] = graph[u][v];
                cout << "Индекс стартовой вершины " << v + 1 << " Вершина остова " << u + 1 << " Значение " << key[v] << endl;
            }
    }

    // распечатать построенный MST
    printOstov(parent, graph);
}