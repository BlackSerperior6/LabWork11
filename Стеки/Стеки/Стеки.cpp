#include <iostream>
#include <fstream>
#include<windows.h>
#include <chrono>

using namespace std;

struct Node //Структура элемента стека
{
    char Data; //Данные элемента
    Node* next = nullptr; //Переход к следующему элементу
};

struct Stack //Структура стека
{
    Node* head = nullptr; //Голова стека
    int size = 0; //Размер стека

    void Push_Front(char element) //Метод для добавления элемента в начало стека 
    {
        Node* node = new Node; //Создаем новый элемент стека
        node->Data = element; //Записываем в новый элемент нужные данные

        if (head == nullptr) //Если стек пуст
            head = node; //Новый элемент становится головой стека
        else
        {
            node->next = head; //Ставим голову после нового элемента
            head = node; //Делаем новый элемент головой
        }

        size++; //Увеличиваем размер
    }

    void Push_Back(char element) //Метод для добавления элемента в конец стека 
    {
        Stack* buffer = new Stack; //Создаем стек - буффер

        for (int i = 0; i < size; i++)
        {
            buffer->Push_Front(head->Data); //Записываем в буфеер текущую голову

            //Сносим текущую голову, новая голова = следующий элемент
            Node* tmp = head;
            head = head->next;
            delete tmp;
        }

        size = 0; //Размер нашего стека = 0
        Push_Front(element); //Добавляем новый элемент в наш стек
        Node* current = buffer->head; //Начинаем поход по буфферному стеку

        for (int i = 0; i < buffer->size; i++)
        {
            //Каждый элемент буфферного стека записываем в наш
            Push_Front(current->Data); 
            current = current->next;
        }

        buffer->Clear(); //Очищаем буфферный стек
        delete buffer; //И удаляем его
    }

    void print() 
    {
        if (size == 0) //Если размер стека = 0
            cout << "Ваш стек пуст" << endl; //То просто сообщаем, что стек пуст
        else //Иначе
        {
            cout << "Ваш стек:" << endl;

            Node* current = head; //Начинаем поход по стеку

            for (int i = 0; i < size; i++)
            {
                //Печатаем каждый элемент стека
                cout << current->Data << " "; 
                current = current->next;
            }

            cout << endl;
        } 
    }

    void Write_Into_File(ofstream* f) //Метод для записи стека в файл
    {
        Node* current = head; //Переменная текущего элемента

        while (current != nullptr) //Пока не дошли до конца стека
        {
            f->write((char*)&(current->Data), sizeof(char)); //Записываем данные текущего элемента в файл
            current = current->next; //Переходим на следующий элемент
        }
    }

    void Read_From_File(ifstream* f, int x) //Метод для востановления стека из файла
    {
        for (int i = 0; i < x; i++)
        {
            char element;
            f->read((char*)&element, sizeof(char)); //Считываем символ из файла
            Push_Back(element); //Записываем его в стек
        }
    }

    void Remove(char key)
    {
        Stack* buffer = new Stack; //Буфферный стек

        for (int i = 0; i < size; i++) //Проходим по всему стеку 
        {
            if (head->Data != key) //Если данные головы не равны ключу
                buffer->Push_Front(head->Data); //Записываем его в буфферный стек
            
            //Сносим текущую голову, новая голова = следующий элемент
            Node* tmp = head;
            head = head->next;
            delete tmp;
        }

        size = 0; //Размер нашего стека = 0
        Node* current = buffer->head; //Начинаем поход по буфферному стеку

        for (int i = 0; i < buffer->size; i++)
        {
            //Каждый элемент буфферного стека записываем в наш
            Push_Front(current->Data);
            current = current->next;
        }

        buffer->Clear(); //Очищаем буфферный стек
        delete buffer; //И удаляем его
    }

    void Clear() //Метод на очистку стека
    {
        for (int i = 0; i < size; i++)
        {
            Node* tmp = head; //Заносим голову в временную переменную
            head = head->next; //Переносим голову на элемент ниже
            delete tmp; //Убиваем временную переменную
        }

        head = nullptr; //Голова = нулевой указатель

        size = 0; //Размер = 0
    }
};

int main()
{
    chrono::steady_clock::time_point start = chrono::high_resolution_clock::now();

    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);

    int n;

    cout << "Введите кол-во элементов стека" << endl;

    cin >> n;

    if (n < 1)
    {
        cout << "Кол-во элементов должно быть >= 1" << endl;
        return 0;
    }

    Stack* stack = new Stack;

    for (int i = 0; i < n; i++)
    {
        char Char;

        cout << "Введите символ:" << endl;

        cin >> Char;

        stack->Push_Front(Char);
    }

    cout << endl;

    stack->print();

    char key;

    cout << "Введите символ, который вы хотите удалить:" << endl;

    cin >> key;

    stack->Remove(key);

    stack->print();

    cout << endl << "Введите сколько еще символов вы хотите добавить в начало стека:" << endl;

    cin >> n;

    for (int i = 0; i < n; i++)
    {
        char Char;

        cout << "Введите символ:" << endl;

        cin >> Char;

        stack->Push_Front(Char);
    }

    cout << endl;

    if (n > 0)
        stack->print();

    cout << endl << "Введите сколько еще символов вы хотите добавить в конец стека:" << endl;

    cin >> n;

    for (int i = 0; i < n; i++)
    {
        char Char;

        cout << "Введите символ:" << endl;

        cin >> Char;

        stack->Push_Back(Char);
    }

    cout << endl;

    if (n > 0)
    {
        stack->print();
        cout << endl;
    }

    if (stack->size > 0)
    {
        ofstream OutputStream("F1.bin", ios::binary);

        if (OutputStream.is_open())
        {
            cout << "Записываем стек в файл" << endl;
            stack->Write_Into_File(&OutputStream);
            OutputStream.close();
            int Length = stack->size;
            stack->Clear();

            cout << "Очищаем стек и считываем его из файла" << endl << endl;

            ifstream InputStream("F1.bin", ios::binary);

            stack->Read_From_File(&InputStream, Length);
            InputStream.close();
            stack->print();
        }

        stack->Clear();
    }

    delete stack;

    cout << endl << "Потребовалось времени: " << (chrono::high_resolution_clock::now() - start).count() << endl;
}
