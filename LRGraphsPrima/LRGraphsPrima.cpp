#include <iostream>
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <iomanip>

using namespace std;

typedef struct Node Node;

struct Node {
    int s; // начальный номер вершины (стартовый)
    int c; // конечный номер вершины (финишный)
    int v; //"вес" пути
    Node* next; // указатель на след. элемент
};


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


    for (int i = 1; i < vertices - 1; i++) {
        
            initData();
            start = i; //начало пути - нумерация с 1
            finish = i + 1; //конец пути - нумерация с 1
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
        } 
    

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