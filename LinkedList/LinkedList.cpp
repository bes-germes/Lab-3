#include "LinkedList.h"

#include <cassert>

LinkedList::Node::Node(const ValueType& value, Node* next)
{
    this->value = value;
    this->next = next;
}

LinkedList::Node::~Node()
{
    // ничего не удаляем, т.к. агрегация
}

void LinkedList::Node::insertNext(const ValueType& value)
{
    Node* newNode = new Node(value, this->next);
    this->next = newNode;

}

void LinkedList::Node::removeNext()
{
    Node* removeNode = this->next;
    Node* newNext = removeNode->next;
    delete removeNode;
    this->next = newNext;
}

LinkedList::LinkedList()
        : _head(nullptr), _size(0)//просто класс создан здесь
{

}

LinkedList::LinkedList(const LinkedList& copyList)
{
    this->_size = copyList._size;
    if (this->_size == 0) {
        this->_head = nullptr;
        return;
    }

    this->_head = new Node(copyList._head->value);

    Node* currentNode = this->_head;
    Node* currentCopyNode = copyList._head->next;

    while (currentCopyNode) {
        currentNode->next = new Node(currentCopyNode->value);
        currentCopyNode = currentCopyNode->next;
        currentNode = currentNode->next;
    }
}

LinkedList& LinkedList::operator=(const LinkedList& copyList)
{
    if (this == &copyList) {
        return *this;
    }
    LinkedList bufList(copyList);
    this->_size = bufList._size;
    this->_head = bufList._head;

    return *this;
}

LinkedList::LinkedList(LinkedList&& moveList) noexcept
{
    this->_size = moveList._size;
    this->_head = moveList._head;

    moveList._size = 0;
    moveList._head = nullptr;
}

LinkedList& LinkedList::operator=(LinkedList&& moveList) noexcept
{
    if (this == &moveList) {
        return *this;
    }
    forceNodeDelete(_head);
    this->_size = moveList._size;
    this->_head = moveList._head;

    moveList._size = 0;
    moveList._head = nullptr;

    return *this;
}

LinkedList::~LinkedList()
{
    forceNodeDelete(_head);
}

ValueType& LinkedList::operator[](const size_t pos) const
{
    return getNode(pos)->value;
}

LinkedList::Node* LinkedList::getNode(const size_t pos) const
{
    if (pos < 0) {
        assert(pos < 0);
    }
    else if (pos >= this->_size) {
        assert(pos >= this->_size);
    }

    Node* bufNode = this->_head;
    for (int i = 0; i < pos; ++i) {
        bufNode = bufNode->next;
    }

    return bufNode;
}

void LinkedList::insert(const size_t pos, const ValueType& value)
{

    if (pos < 0) {
        assert(pos < 0);
    }
    else if (pos > this->_size) {
        assert(pos > this->_size);
    }

    if (pos == 0) {
        pushFront(value);
    }
    else {
        Node* bufNode = this->_head;
        for (size_t i = 0; i < pos-1; ++i) {
            bufNode = bufNode->next;
        }
        bufNode->insertNext(value);
        ++_size;
    }
}

void LinkedList::insertAfterNode(Node* node, const ValueType& value)
{
    node->insertNext(value);
    ++_size;
}

void LinkedList::pushBack(const ValueType& value)
{
    if (_size == 0) {
        pushFront(value);
        return;
    }
    insert(_size, value);
}

void LinkedList::pushFront(const ValueType& value)//добавить новый элемент
{
    _head = new Node(value, _head);
    ++_size;
}

void LinkedList::remove(const size_t pos)
{

        if (pos < 0) {
        assert(pos < 0);
    }
    else if (pos > this->_size) {
        assert(pos > this->_size);
    }

    else if (pos == 0) {
        removeFront();
    }
    else if(pos == _size - 1)
    {
        removeBack();
    }
    else {

        Node *deleteNode = getNode(pos);
        Node *bufNode = getNode(pos + 1);
        getNode(pos - 1)->next = bufNode;
        delete deleteNode;
        --_size;
    }

}
void LinkedList::removeNode(Node* node)
{
    int index = findIndex(node->value);

    if(index == -1)
    {
     assert(index == -1);
    }

    else if (index == 0) {
        removeFront();
    }
    else if(index == _size - 1)
    {
        removeBack();
    }
    else {


        remove(index);
        --_size;
    }

}

void LinkedList::removeNextNode(Node* node)
{
    int index = findIndex(node->value);
    remove(index + 1);
}
void LinkedList::removeBack()
{

    Node *deleteNode = getNode(_size - 1);
    getNode(_size - 2)->next = nullptr;
    delete deleteNode;
    --_size;
}

void LinkedList::removeFront()
{
    Node *deleteBuf = getNode(0);
    this->_head = getNode(1);
    delete deleteBuf;
    --_size;
}

long long int LinkedList::findIndex(const ValueType& value) const
{
    Node *node = this->_head;

    for(int i = 0; i < _size; ++i)
    {
        if(node->value == value){
            return i;
        }
        node = node->next;
    }
    return -1;
}

LinkedList::Node* LinkedList::findNode(const ValueType& value) const
{
    int index = findIndex(value);
    assert(index != -1);
    return getNode(index);
}

void LinkedList::reverse()
{
    int index = _size-1;
    long double n;
        for(int i = 0; i <= int((_size-1)/2); ++i){
       n = getNode(i)->value;
       getNode(i)->value = getNode(_size - 1 - i)->value;
       getNode(_size - 1 - i)->value = n;
    }

}

LinkedList LinkedList::reverse1() const
{
    LinkedList buf(*this);
    buf.reverse();
    return buf;
    //return LinkedList();

}

LinkedList LinkedList::getReverseList() const
{
    LinkedList  buf(*this);
    buf.reverse();
    return buf;
}

size_t LinkedList::size() const
{
    return _size;
}


void LinkedList::forceNodeDelete(Node* node)
{
    if (node == nullptr) {
        return;
    }

    Node* nextDeleteNode = node->next;
    delete node;
    forceNodeDelete(nextDeleteNode);
}