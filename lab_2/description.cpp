#include <stdlib.h>
#include <iostream>

struct TwoInts
{
    int a;
    int b;
};

struct StructWithArray
{
    int arr[4];
    int* someNumber;
};

int main()
{
    TwoInts i2 = { };
    i2.a = 5;
    i2.b = 7;

    //Вывод значений полей структуры TwoInts
    std::cout << i2.a << std::endl; 
    std::cout << i2.b << std::endl; 

    //Определяем переменную типа StructWithArray, называем её s и инициализируем поля переменной как нули
    StructWithArray s = { };
    s.arr[0] = 10;

    StructWithArray s1 = { };
    s1.arr[0] = 15;

    //Создание указателя sPointer, который указывает на структуру s
    StructWithArray* sPointer = &s;
    sPointer->arr[0] = 20;

    //Вывод значения первого элемента массива s через sPointer 
    std::cout << s.arr[0] << std::endl; 

    //Прямое изменение значения первого элемента массива s 
    s.arr[0] = 25;
    std::cout << s.arr[0] << std::endl; 

    //Изменение значения первого элемента массива s через sPointer 
    sPointer->arr[0] = 30;
    std::cout << s.arr[0] << std::endl; 

    //Теперь указатель sPointer указывает на переменную s1 дальнейшее использование sPointer будет влиять только на s1
    sPointer = &s1;
    sPointer->arr[0] = 35;

    //Вывод значения первого элемента массива s 
    std::cout << s.arr[0] << std::endl; 

    //Вывод значения первого элемента массива s1 
    std::cout << s1.arr[0] << std::endl; 

    //Создание массива из двух структур StructWithArray и инициализация элементов
    StructWithArray structArray[2] = { };
    structArray[0].arr[3] = 77;
    structArray[1].someNumber = &structArray[0].arr[3];

    sPointer = &s;

    //Создание указателя pointer, который указывает на четвертый элемент массива s
    int* pointer = &sPointer->arr[3];

    //Прямое изменение четвертого элемента массива s 
    s.arr[3] = 72;

    //Вывод значения, на которое указывает pointer 
    std::cout << *pointer; 

    //Создание структуры memory и заполнение ее памяти нулями
    StructWithArray memory;
    memset(&memory, 0, sizeof(StructWithArray));

    return 0;
}