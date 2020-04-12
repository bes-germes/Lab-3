#pragma once
#include <iostream>

// потом поменяем на шаблоны
using ValueType = double;

class TwoSideList
{
    // класс узла списка
    // по своей сути, может содержать любые данные,
    // можно реализовать и ассоциативный массив, просто добавив
    // поле с ключем в узел и, с учетом этого, поменять методы LinkedList
    // (доступ по ключу, поиск по ключу и т.д.)
    struct Node {
        Node(const ValueType& value, Node* next = nullptr, Node *prev = nullptr); //Готово
        ~Node(); //Готово

        void insertNext(const ValueType& value);
        void insertPrev(const ValueType& value);
        void removeNext();
        void removePrev();

        ValueType value;
        Node* next;
        Node* prev;
    };

public:
    ////
    TwoSideList(); //Готово------------------
    TwoSideList(const TwoSideList& copyList);
    TwoSideList& operator=(const TwoSideList& copyList); //Готово

    TwoSideList(TwoSideList&& moveList) noexcept; //Готово
    TwoSideList& operator=(TwoSideList&& moveList) noexcept; //Готово

    ~TwoSideList(); //Готово
    ////

    // доступ к значению элемента по индексу
    ValueType& operator[](const size_t pos) const; //Готово----------------
    // доступ к узлу по индексу
    TwoSideList::Node* getNode(const size_t pos) const; //Готово----------------

    // вставка элемента по индексу, сначала ищем, куда вставлять (О(n)), потом вставляем (O(1))
    void insert(const size_t pos, const ValueType& value); //Готово-------------------
    // вставка элемента после узла, (O(1))
    void insertAfterNode(Node* node, const ValueType& value); //Готово------------------
    void insertBeforeNode(Node* node, const ValueType& value); //Готово------------
    // вставка в конец (О(n))
    void pushBack(const ValueType& value); //Готово-------------------
    // вставка в начало (О(1))
    void pushFront(const ValueType& value); //Готово-------------------

    // удаление
    void remove(const size_t pos);
    void removeNextNode(Node* node); //Готово-------------------
    void removePrevNode(Node* node); //Готово-------------------
    void removeFront(); //Готово-------------------
    void removeBack(); //Готово-------------------

    // поиск, О(n)
    long long int findIndex(const ValueType& value) const;
    Node* findNode(const ValueType& value) const;

    // разворот списка
    void reverse();						// изменение текущего списка
    TwoSideList reverse() const;			// полчение нового списка (для константных объектов)
    TwoSideList getReverseList() const;	// чтобы неконстантный объект тоже мог возвращать новый развернутый список

    size_t size() const; //Готово
private:
    Node*	_head;
    Node*	_tail;
    size_t	_size;

    void forceNodeDelete(Node* node);
};
