#include <iostream>
#include <fstream>
#include<windows.h>
#include <chrono>

using namespace std;

struct Node //Структура элемента списка
{
    char Data; //Данные, которые он содержит
    Node* next = nullptr; //Следующий элемент списка
    Node* prev = nullptr; //Предыдущий элемент списка
};

struct List
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
            tail->next = new_node; //Ставим новый элемент после хвоста
            new_node->prev = tail; //Ставим хвост перед новым элементом
            tail = new_node; //Новый элемент становится хвостом
        }
    }

    void Push_Front(char element) //Метод добавления элемента в конец списка
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
            new_node->next = head; //Ставим голову после нового элемента
            head->prev = new_node; //Ставим новый элемент перед головой
            head = new_node; //Голова = новый элемент
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

                current = current->next; //Переходим к следующему
            }

            cout << endl;
        }
    }

    void Remove(char key) //Метод для удаления элемента списка по ключу
    {
        Node* curren = new Node; //Инициализируем переменную, обозначающую текущий элемент списка
        curren->next = head; //Следующий после этого элемент - голова

        while (curren != nullptr) //Пока не дошли до конца списка
        {
            Node* tmp = curren; //Записываем текущий элемент в временный 
            curren = curren->next; //Идем дальше

            if (tmp->Data == key) //Если данные соответствуют ключу
            {
                if (tmp->next == nullptr && tmp->prev == nullptr) //Если в списке один элемент
                {
                    //Голова и хвост = нулевые указатели
                    head = nullptr;
                    tail = nullptr;
                }

                else if (tmp == head) // Если мы в голове
                {
                    head = tmp->next; //Голова = следующий элемент
                    head->prev = nullptr;  // Предыдущий элемент головы = нулевой указатель
                }

                else if (tmp == tail) //Если мы в хвосте
                {
                    tail = tmp->prev; //Хвост = предыдущий элемент
                    tail->next = nullptr; //Следующий элемент после хвоста = нулевой указатель
                }

                else //Если в другом месте списка
                {
                    tmp->prev->next = tmp->next; //Следующий элемент предыдущего = следующий элемент
                    tmp->next->prev = tmp->prev; //Предыдущий элемент предыдущего = предыдущий элемент
                }

                delete tmp; //Удаляем временную переменную
            }   
        }
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

    void Write_Into_File(ofstream* f) //Метод для записи списка в файл
    {
        Node* current = head; //Переменная текущего элемента

        while (current != nullptr) //Пока не дошли до конца списка
        {
            f->write((char*)&(current->Data), sizeof(char)); //Записываем данные текущего элемента в список
            current = current->next; //Переходим на следующий элемент
        }
    }

    void Read_From_File(ifstream* f, int x) //Метод для востановления списка из файла
    {
        for (int i = 0; i < x; i++)
        {
            char element;
            f->read((char*)&element, sizeof(char)); //Считываем символ из файла
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
    chrono::steady_clock::time_point start = chrono::high_resolution_clock::now();

    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);

    int n;

    cout << "Введите кол-во элементов списка" << endl;

    cin >> n;

    if (n < 1)
    {
        cout << "Кол-во элементов должно быть >= 1" << endl;
        return 0;
    }


    List* list = new List;

    for (int i = 0; i < n; i++)
    {
        char Char;

        cout << "Введите символ:" << endl;

        cin >> Char;

        list->Push_Back(Char);
    }

    cout << endl;

    list->print();

    char key;

    cout << "Введите символ, который вы хотите удалить:" << endl;

    cin >> key;

    list->Remove(key);

    list->print();

    cout << endl << "Введите сколько еще символов вы хотите добавить в начало списка:" << endl;

    cin >> n;

    for (int i = 0; i < n; i++)
    {
        char Char;

        cout << "Введите символ:" << endl;

        cin >> Char;

        list->Push_Front(Char);
    }

    cout << endl;

    if (n > 0)
        list->print();

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

    if (list->GetSize() > 0)
    {
        ofstream OutputStream("F1.bin", ios::binary);

        if (OutputStream.is_open())
        {
            cout << "Записываем список в файл" << endl;
            list->Write_Into_File(&OutputStream);
            OutputStream.close();
            int Length = list->GetSize();
            list->Clear();

            cout << "Очищаем список и считываем его из файла" << endl << endl;

            ifstream InputStream("F1.bin", ios::binary);

            list->Read_From_File(&InputStream, Length);
            InputStream.close();
            list->print();
        }

        list->Clear();
    }

    delete list;

    cout << endl << "Потребовалось времени: " << (chrono::high_resolution_clock::now() - start).count() << endl;
}
