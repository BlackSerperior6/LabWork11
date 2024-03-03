#include <iostream>
#include <fstream>
#include<windows.h>
#include <chrono>

using namespace std;

struct Node //Структура элемента очереди
{
    char Data; //Данные очереди
    Node* next = nullptr; //Следующий в очереди
};

struct Queue
{
    Node* head = nullptr; //Первый в очереди
    Node* tail = nullptr; //Последний в очереди
    int size = 0; //Размер очереди

    void print()
    {
        if (size == 0) //Если размер очереди = 0
            cout << "Ваша очередь пуст" << endl; //То просто сообщаем, что очередь пуста
        else //Иначе
        {
            cout << "Ваша очередь:" << endl;

            Node* current = head; //Начинаем поход по очереди

            for (int i = 0; i < size; i++)
            {
                //Печатаем каждый элемент очереди
                cout << current->Data << " ";
                current = current->next;
            }

            cout << endl;
        }
    }

    void Push_Front(char element) //Метод вставки элемента в начало очереди
    {
        Node* node = new Node; //Новый элемент очереди
        node->Data = element; //С нужными данными

        if (head == nullptr) //Если очередь пуста
        {
            //Голова и хвост = новый элемент очереди
            head = node;
            tail = node;
        }
        else
        {
            tail->next = node; //Ставим новый элемент за последним элементом очереди
            tail = node; //Теперь новый элемент = последний элемент очереди
        } 

        size++;  //Увеличиваем размер очереди
    }

    void Push_Back(char element) //Метод вставки элемента в конец очереди
    {
        Queue* buffer = new Queue; //Создаем буфферную очередь
        buffer->Push_Front(element); //Записываем в неё новый элемент

        for (int i = 0; i < size; i++) //Записываем в буфферную очередь каждый элемент нашей очереди
        {
            buffer->Push_Front(head->Data);

            Node* tmp = head;
            head = head->next;
            delete tmp;
        }

        size = 0; //Размер нашей очереди = 0
        Node* current = buffer->head; //Начинаем поход по буфферной очереди

        for (int i = 0; i < buffer->size; i++)
        {
            Push_Front(current->Data); //Каждый элемент буфферной очереди записываем в новую очередь
            current = current->next;
        }

        buffer->Clear(); //Очищаем буфферную очередь
        delete buffer; //Удаляем буфферную очередь
    }

    void Remove(char Key) //Метод удаления элемента из очереди по ключу
    {
        for (int i = 0; i < size; i++) //Начинаем поход по очереди
        {
            if (head->Data != Key) //Если данные элемента очереди не совпадают с ключом
                Push_Front(head->Data); //Записываем голову
            else
                i--; //Иначе уменьшаем i переменную

            Node* tmp = head; //Записываем голову в временную переменную
            head = head->next; //Сдвигаем очередь
            size--; //Уменьшаем размер
            delete tmp; //Удаляем временный элемент
        }
    }

    void Write_Into_File(ofstream* f) //Метод для записи очереди в файл
    {
        Node* current = head; //Переменная текущего элемента

        while (current != nullptr) //Пока не дошли до конца очереди
        {
            f->write((char*)& (current->Data), sizeof(char)); //Записываем данные текущего элемента в файл
            current = current->next; //Переходим на следующий элемент
        }
    }

    void Read_From_File(ifstream* f, int x) //Метод для востановления очереди из файла
    {
        for (int i = 0; i < x; i++)
        {
            char element;
            f->read((char*)&element, sizeof(char)); //Считываем символ из файла
            Push_Front(element); //Записываем его в очередь
        }
    }

    void Clear() //Метод на очистку очереди
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

    cout << "Введите кол-во элементов списка" << endl;

    cin >> n;

    if (n < 1)
    {
        cout << "Кол-во элементов должно быть >= 1" << endl;
        return 0;
    }

    Queue* queue = new Queue;

    for (int i = 0; i < n; i++)
    {
        char Char;

        cout << "Введите символ:" << endl;

        cin >> Char;


        queue->Push_Front(Char);
    }

    cout << endl;

    queue->print();

    char key;

    cout << "Введите символ, который вы хотите удалить:" << endl;

    cin >> key;

    queue->Remove(key);

    queue->print();

    cout << endl << "Введите сколько еще символов вы хотите добавить в начало очереди:" << endl;

    cin >> n;

    for (int i = 0; i < n; i++)
    {
        char Char;

        cout << "Введите символ:" << endl;

        cin >> Char;

        queue->Push_Front(Char);
    }

    cout << endl;

    if (n > 0)
        queue->print();

    cout << endl << "Введите сколько еще символов вы хотите добавить в конец очереди:" << endl;

    cin >> n;

    for (int i = 0; i < n; i++)
    {
        char Char;

        cout << "Введите символ:" << endl;

        cin >> Char;

        queue->Push_Back(Char);
    }

    cout << endl;

    if (n > 0)
    {
        queue->print();
        cout << endl;
    }

    if (queue->size > 0)
    {
        ofstream OutputStream("F1.bin", ios::binary);

        if (OutputStream.is_open())
        {
            cout << "Записываем список в файл" << endl;
            queue->Write_Into_File(&OutputStream);
            OutputStream.close();
            int Length = queue->size;
            queue->Clear();

            cout << "Очищаем список и считываем его из файла" << endl << endl;

            ifstream InputStream("F1.bin", ios::binary);

            queue->Read_From_File(&InputStream, Length);
            InputStream.close();
            queue->print();
        }

        queue->Clear();
    }

    delete queue;

    cout << endl << "Потребовалось времени: " << (chrono::high_resolution_clock::now() - start).count() << endl;
}
