#include <iostream>
#include <fstream>
#include<windows.h>
#include <chrono>

using namespace std;

struct Node //Структура элемента списка
{
    char Data; //Данные, которые он содержит
    Node* next = nullptr; //Следующий элемент списка
};

struct List //Структура списка
{
    Node* head = nullptr; //Первый элемент списка
    Node* tail = nullptr; //Последний элемент списка
    
    void Push_Back(char element) //Метод добавления элемента в конец списка
    {
        Node* new_node = new Node; //Создаем новый элемент
        new_node->Data = element; //Записываем в новый элемент нужные данные

        if (head == nullptr) //Если список пуст
        {
            //Голова и хвост = новый элемент
            head = new_node;
            tail = new_node;
        }
        else
        {
            tail->next = new_node; //После текущего хвоста встал новый элемент
            tail = new_node; //Хвостом теперь является новый элемент
        }
    }

    void Push_Front(char element) //Метод добавления элемента в начало списка
    {
        Node* new_node = new Node; //Создаем новый элемент
        new_node->Data = element; //Записываем в новый элемента нужные данные

        if (head == nullptr) //Если список пуст
        {
            //Голова и хвост = новый элемент
            head = new_node;
            tail = new_node;
        }
        else
        {
            new_node->next = head; //Следующий элемент после нового = текущая голова
            head = new_node; //Головой теперь является новый элемент
        }
    }

    void print() //Метод печати списка
    {
        Node* current = head; //Инициализируем переменную, которая хранит в себе текущий элемент списка

        if (current == nullptr) //Если самый первый элемент списка оказался пустым
            cout << "Ваш список оказался пустым" << endl; //Значит список пуст

        else
        {
            cout << "Ваш список:" << endl;

            while (current != nullptr) //Пока не дошли до конца списка
            {
                cout << current->Data << " "; //Выводим данные текущего элемента

                current = current->next; //Переходим к следующему элементу
            }

            cout << endl;
        }
    }

    void Remove(char key) //Метод для удаления элемента списка по ключу
    {
        Node* curren = new Node; //Инициализируем переменную, обозначающую текущий элемент списка
        curren->next = head; //Следующий после этого элемент - голова

        bool flag = false; //Флаг
        
        while (curren->next != nullptr) //Пока следующий элемент не будет пустым
        {
            if (curren->next->Data == key) //Если данные следующего элемента равны ключу
            {
                Node* tmp; //Выделяем память под временную переменную
                 
                if (curren->next == head) //Если следующий элемент = голова списка
                {
                    tmp = head; //Записываем голову во временную переменую
                    head = head->next; //Делаем головой следующий элемент списка
                    curren->next = head; //Следующий элемент после текущего = голова
                }

                else if (curren->next == tail) //Иначе eсли следующий элемент = хвост списка
                {
                    tmp = tail; //Записываем хвост во временную переменую
                    tail = curren; //Хвостом теперь является текущая переменная
                    curren->next = nullptr; //После текущей переменной ничего нет
                }

                else //Иначе
                {
                    tmp = curren->next; //Записываем следующий элемент во временную переменую
                    curren->next = tmp->next; //Следующий элемент после текущего = следующий элемент временной переменой
                }
                
                delete tmp; //Удаляем содержимое временной переменой
            }
            else //Иначе
            { 
                curren = curren->next; //Двигаемся к следующей переменной
                flag = true; //Переключаем флаг на истину
            }      
        }

        if (!flag) //Флаг обозначает, что хотя бы один элемент списка не был удален
            delete curren; //Если удалили все элементы списка, то очищаем память переменной текущего элемента
    }

    int GetSize() //Метод получения размера списка
    {
        int counter = 0; //Счетчик

        Node* current = head; //Переменная текущего элемента

        while (current != nullptr) //Пока не дошли до конца списка
        {
            current = current->next; //Переходим на следующий элемент
            counter++; //Увеличиваем счетчик
        }

        return counter; //Возвращаем счетчик
    }

    void Write_Into_File(ofstream* f) //Функция для записи списка в файл
    {
        Node* current = head; //Переменная текущего элемента

        while (current != nullptr) //Пока не дошли до конца списка
        {
            f->write((char*) &(current->Data), sizeof(char)); //Записываем данные текущего элемента в список
            current = current->next; //Переходим на следующий элемент
        }
    }

    void Read_From_File(ifstream* f, int x) //Функция для востановления списка из файла
    {
        for (int i = 0; i < x; i++)
        {
            char element;
            f->read((char*) &element, sizeof(char)); //Считываем символ из файла
            Push_Back(element); //Записываем его в список
        }
    }

    void Clear() //Метод очистки списка
    {
        while (head != nullptr) //Пока не дошли до конца списка
        {
            Node* tmp = head; //Записываем голову во временную переменную
            head = head->next; //Головой теперь является элемент после головы
            delete tmp; //Удалить текущий элемент
        }

        tail = nullptr; //Сделать хвост нулевым указателем
    }
};

int main()
{
    chrono::steady_clock::time_point start = chrono::high_resolution_clock::now(); //Засекаем таймер

    //Подключаем русский язык
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);

    int n;

    cout << "Введите кол-во элементов списка" << endl;

    cin >> n; //Получаем кол-во элементов от пользователя

    if (n < 1) //Проверка на валидность
    {
        cout << "Кол-во элементов должно быть >= 1" << endl;
        return 0;
    }

    List *list = new List; //Инициализируем список

    for (int i = 0; i < n; i++) //Заполняем список
    {
        char Char;

        cout << "Введите символ:" << endl;
       
        cin >> Char; //Получаем символ

        list->Push_Back(Char); //Вставляем его в конец списка
    }

    cout << endl;

    list->print(); //Печатаем список

    char key;

    cout << "Введите символ, который вы хотите удалить:" << endl;

    cin >> key; //Получаем ключ элемента, который надо удалить

    list->Remove(key); //Удаляем нужный элемент

    list->print(); //Вновь печатаем измененный список

    cout << endl << "Введите сколько еще символов вы хотите добавить в начало списка:" << endl;

    cin >> n; //Получаем, сколько элементов надо добавить в начало списка

    //Вставляем элементы в начало списка
    for (int i = 0; i < n; i++)
    {
        char Char;

        cout << "Введите символ:" << endl;

        cin >> Char;

        list->Push_Front(Char);
    }

    cout << endl;

    if (n > 0) //Печатаем измененный список, если кол-во элементов изменилось
        list->print();

    //До строки 262 по аналогичной логике добавляем элементы в конец списка
    cout << endl << "Введите сколько еще символов вы хотите добавить в конец списка:" << endl;

    cin >> n;

    for (int i = 0; i < n; i++)
    {
        char Char;

        cout << "Введите символ:" << endl;

        cin >> Char;

        list->Push_Back(Char);
    }

    cout << endl;

    if (n > 0)
    {
        list->print();
        cout << endl;
    }
        
    
    //Если в списке что - то осталось
    if (list->GetSize() > 0)
    {
        ofstream OutputStream("F1.bin", ios::binary); //Открываем файл в выходном потоке

        if (OutputStream.is_open()) //Если открылся
        {
            cout << "Записываем список в файл" << endl;
            list->Write_Into_File(&OutputStream); //Записываем весь список в файл
            OutputStream.close(); //Закрываем выходной поток
            int Length = list->GetSize(); //Получаем размер списка
            list->Clear(); //Чистим список

            cout << "Очищаем список и считываем его из файла" << endl << endl;

            ifstream InputStream("F1.bin", ios::binary); //Открываем файл в входном потоке

            list->Read_From_File(&InputStream, Length); //Считываем список из файла
            InputStream.close(); //Закрываем выходном поток
            list->print(); //Печатаем список
        }

        list->Clear(); //Чистим список
    }

    delete list; //Удаляем список

    cout << endl <<"Потребовалось времени: " << (chrono::high_resolution_clock::now() - start).count() << endl; //Выводим, сколько времени заняло исполнение программы
}
