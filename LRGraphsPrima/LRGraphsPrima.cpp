#include <iostream>
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <iomanip>

using namespace std;

typedef struct Node Node;
// Number of vertices in the graph
#define V 10

struct Node {
    int s; // начальный номер вершины (стартовый)
    int c; // конечный номер вершины (финишный)
    int v; //"вес" пути
    Node* next; // указатель на след. элемент
};

int minKey(int key[], bool mstSet[]);
void printMST(int parent[], int graph[V][V]);
void primMST(int graph[V][V]);
void primMST(Node* list);
void printMST(int parent[], Node* list);
void print(Node* list);
void set_edge(Node** plist, int s, int c, int v);
int find(Node* list, int s, int c);
void initData();
bool step(Node* list, int s, int f, int p);

int paths = 0; //количество путей по графу
const int vertices = 11; //количество вершин графа

int tempRoad[vertices]; //номера узлов текущей "дороги"
bool includedVert[vertices]; //true, если i-ая вершина включена в путь
int shortestWay[vertices]; //искомый самый короткий путь
int tempWayLen; //его длина
int start, finish; //начальная и конечная вершины
bool found;
int weightLen; //найденный "вес" маршрута
int cur_len; //текущий "вес" маршрута

int find(Node* list, int s, int c) { //вес пути из startVerticle и currientVerticle или 0, если пути нет
    int index = 1;
    for (Node* p = list; p != NULL; p = p->next) {

        if (p->s == s && p->c == c ||
            p->s == c && p->c == s) return p->v;
        index++;
    }

    return 0;
}
bool step(Node* list, int startVerticle, int finishVerticle, int p) { //рекурсивный поиск шага пути
    int currientVerticle; // стоимость пути в след. вершину
    if (startVerticle == finishVerticle) { //начальная вершина совпала с конечной
        
        weightLen = cur_len; //запомнить общий вес пути
        tempWayLen = p; //запомнить длину пути (количество узлов)
        for (int i = 0; i < tempWayLen; i++) {
            shortestWay[i] = tempRoad[i]; //запомнить сам путь
            cout << shortestWay[i] << " ~> ";
        }
        found = true; //поставить флажок "найдено"
        cout << "Вес промежуточный " << cur_len << endl;
        return found;
    }
    else { //промежуточный номер вершины, у которой определяем стоимость
        for (currientVerticle = 0; currientVerticle < vertices; currientVerticle++) { //идем по всем возможным вершинам
            int w = find(list, startVerticle, currientVerticle); //есть ли путь из startVerticle в currientVerticle
            if (w && !includedVert[currientVerticle] && (weightLen == 0 || cur_len + w < weightLen)) { //нужная точка не включена?
                tempRoad[p] = currientVerticle; //включить точку в путь
                includedVert[currientVerticle] = true; //пометить как включенную
                cur_len += w; //учесть в общем весе пути
                step(list, currientVerticle, finishVerticle, p + 1); //вызвать себя для поиска следующей точки
                tempRoad[p] = 0; //вернуть всё как было
                includedVert[currientVerticle] = false;
                cur_len -= w;
            }
        }
        
        return found;
    }

}

int main() {

    setlocale(LC_ALL, "Russian");
    system("color F0");
    Node* list = NULL;

    int x = 0;
    int value = 0;

    set_edge(&list, 1, 2, 5);
    set_edge(&list, 1, 4, 3);
    set_edge(&list, 1, 5, 6);

    set_edge(&list, 2, 7, 2);
    set_edge(&list, 2, 3, 2);

    set_edge(&list, 3, 6, 1);

    set_edge(&list, 4, 7, 2);

    set_edge(&list, 5, 8, 9);
    set_edge(&list, 5, 10, 7);

    set_edge(&list, 7, 6, 3);

    set_edge(&list, 8, 3, 5);
    set_edge(&list, 8, 9, 7);

    set_edge(&list, 9, 6, 8);

    set_edge(&list, 10, 1, 8);
    set_edge(&list, 10, 8, 1);


    int graph[V][V] = { { 0, 5, 0, 3, 6, 0, 0, 0, 0, 8 },
                        { 5, 0, 2, 0, 0, 0, 2, 0, 0, 0 },
                        { 0, 3, 0, 0, 0, 1, 0, 5, 0, 0 },
                        { 3, 0, 0, 0, 0, 0, 2, 0, 0, 0 },
                        { 6, 0, 0, 0, 0, 0, 0, 9, 0, 7 },
                        { 0, 0, 1, 0, 0, 0, 3, 0, 8, 0 },
                        { 0, 2, 0, 2, 0, 3, 0, 0, 0, 0 },
                        { 0, 0, 5, 0, 9, 0, 0, 0, 7, 1 },
                        { 0, 0, 0, 0, 0, 8, 0, 7, 0, 0 },
                        { 8, 0, 0, 0, 7, 0, 0, 1, 0, 0 }, };

    // Print the solution
    primMST(graph);
    primMST(list);
    /*for (int i = 1; i < vertices - 1; i++) {
        
            
            start = i; //начало пути - нумерация с 1
            for(int j = start; j < vertices; j++ ){
                
                if (find(list, start, j)) //вес пути из startVerticle и currientVerticle или 0, если пути нет
                {
                    initData();
                    finish = j; //конец пути - нумерация с 1
                    tempRoad[0] = start; //первую точку внесли в маршрут
                    includedVert[start] = true; //и пометили как включённую
                    found = false; //путь пока не найден
                    cout << "\nВершина " << start << endl;
                    if (step(list, start, finish, 1)) { //ищем кратчайший путь 

                        cout << "Вес: " << start << " ~> " << finish << " равен " << setw(6) << left << weightLen << "\t";
                        cout << "Путь: ";
                        for (int i = 0; i < tempWayLen; i++) cout << " ~ " << shortestWay[i];
                    }
                    else cout << "Путь не найден! " << j;
                    cout << endl;
                }
                else {} //переход к следующей вершине
             }
            
    } 
    initData();
    start = 1; //начало пути - нумерация с 1
    finish = 10; //конец пути - нумерация с 1
    tempRoad[0] = start; //первую точку внесли в маршрут
    includedVert[start] = true; //и пометили как включённую
    found = false; //путь пока не найден
    cout << "\nВершина " << start << endl;
    if (step(list, start, finish, 1)) { //ищем кратчайший путь 

        cout << "Вес: " << start << " ~> " << finish << " равен " << setw(6) << left << weightLen << "\t";
        cout << "Путь: ";
        for (int i = 0; i < tempWayLen; i++) cout << " ~ " << shortestWay[i];
    }
    else cout << "Путь не найден!";
    cout << endl;
    */

    return 0;
}

void print(Node* list) { // вывести на экран
    int index = 0;
    for (Node* p = list; p != NULL; p = p->next) {
        printf("[%d] = %d, %d, %d\n", index, p->s, p->c, p->v);
        index++;
    }

    printf("\n");
}
void set_edge(Node** plist, int s, int c, int v) { // положить элемент в начало
    Node* p = (struct Node*)malloc(sizeof(Node));
    p->s = s;
    p->c = c;
    p->v = v;
    p->next = *plist;
    *plist = p;
    paths++;
    
}
void initData() {
    //Инициализация данных:
    for (int i = 0; i < vertices; i++) {
        shortestWay[i] = 0;
        tempRoad[i] = 0;
        includedVert[i] = false;
    }
    weightLen = 0;
    cur_len = 0;
    tempWayLen = 0;
}

//Функция для поиска вершины с
//минимальное значение ключа из набора вершин
//еще не включен в остов
int minKey(int key[], bool mstSet[])
{
    //Инициализировать минимальное значение
    int min = INT_MAX;
    int min_index = 0;

    for (int v = 0; v < V; v++)
        if (mstSet[v] == false && key[v] < min)
            min = key[v], min_index = v;

    return min_index;
}

//Служебная функция для печати
//построенного MST, хранящегося в родительском массиве[]
void printMST(int parent[], int graph[V][V])
{
    cout << "Вершины \tВес\n";
    for (int i = 1; i < V; i++)
        cout << parent[i] << " - " << i << " \t" << graph[i][parent[i]] << " \n";
}
void printMST(int parent[], Node * list)
{
    cout << "Вершины \tВес\n";
    for (int i = 1; i < V; i++)
        cout << parent[i] << " - " << i << " \t" << find(list, i, parent[i]) << " \n";
}

void primMST(Node* list) {
    // Массив для хранения построенного остова
    int parent[V];

    //Ключевые значения, используемые для выбора минимального веса ребра
    int key[V];

    // Для прохождения набора вершин, включенных в остов
    bool mstSet[V];

    // Инициализируйте все ключи как БЕСКОНЕЧНЫЕ
    for (int i = 0; i < V; i++) {
        key[i] = INT_MAX;
        mstSet[i] = false;
    }
    // Всегда включайте первую 1-ю вершину в MST.
    // Сделайте ключ 0, чтобы эта вершина была выбрана в качестве первой вершины.
    key[0] = 0;
    parent[0] = -1; // Первый узел всегда является корнем  остова

    // остов будет иметь V вершин
    for (int count = 0; count < V - 1; count++)
    {
        //Выберите минимальную ключевую вершину из
        //набора вершин, еще не включенных в остов
        int u = minKey(key, mstSet);

        // Добавьте выбранную вершину в набор остова
        mstSet[u] = true;

        // Обновить значение ключа и родительский индекс
        // смежные вершины выбранной вершины.
        // Рассматривайте только те вершины, которые не являются
        // все еще включенный в MST
        for (int v = 0; v < V; v++)

            //граф[u][v] не равен нулю только для смежных вершин m
            //должно быть установлено значение [v] равно false для вершин, еще не включенных в MST
            //Обновляйте ключ только в том случае, если график[u][v] меньше, чем ключ[v]
            
            if (find(list, u, v) && mstSet[v] == false && find(list, u, v) < key[v])
                parent[v] = u, key[v] = find(list, u, v);
    }

    // распечатать построенный MST
    printMST(parent, list);
}

//Функция для построения и печати MST для
// график, представленный с использованием смежности
// матричное представление
void primMST(int graph[V][V])
{
    // Массив для хранения построенного остова
    int parent[V];

    //Ключевые значения, используемые для выбора минимального веса ребра
    int key[V];

    // Для прохождения набора вершин, включенных в остов
    bool mstSet[V];

    // Инициализируйте все ключи как БЕСКОНЕЧНЫЕ
    for (int i = 0; i < V; i++)
        key[i] = INT_MAX, mstSet[i] = false;

    // Всегда включайте первую 1-ю вершину в MST.
    //Сделайте ключ 0, чтобы эта вершина была выбрана в качестве первой вершины.
    key[0] = 0;
    parent[0] = -1; // Первый узел всегда является корнем  остова

    // остов будет иметь V вершин
    for (int count = 0; count < V - 1; count++)
    {
        //Выберите минимальную ключевую вершину из
        //набора вершин, еще не включенных в остов
        int u = minKey(key, mstSet);

        // Добавьте выбранную вершину в набор остова
        mstSet[u] = true;

        // Обновить значение ключа и родительский индекс
        // смежные вершины выбранной вершины.
        // Рассматривайте только те вершины, которые не являются
        // все еще включенный в MST
        for (int v = 0; v < V; v++)

            //граф[u][v] не равен нулю только для смежных вершин m
            //должно быть установлено значение [v] равно false для вершин, еще не включенных в MST
            //Обновляйте ключ только в том случае, если график[u][v] меньше, чем ключ[v]
            if (graph[u][v] && mstSet[v] == false && graph[u][v] < key[v])
                parent[v] = u, key[v] = graph[u][v];
    }

    // распечатать построенный MST
    printMST(parent, graph);
}