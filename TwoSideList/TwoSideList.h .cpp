#include <cassert>
#include "TwoSideList.h"

TwoSideList::Node::Node(const ValueType& value, Node* next, Node* prev){
    this->value = value;
    this->next = next;
    this->prev = prev;
}

TwoSideList::Node::~Node(){
    // ничего не удаляем, т.к. агрегация
}

void TwoSideList::Node::insertNext(const ValueType& value){
    Node* newNode = new Node(value, this->next, this);
    this->next->prev = newNode;
    this->next = newNode;
}

void TwoSideList::Node::insertPrev(const ValueType &value){
    Node* newNode = new Node(value, this, this->prev);
    this->prev->next = newNode;
    this->prev = newNode;
}

void TwoSideList::Node::removeNext(){
    Node *deleteNode = this->next;
    this->next = deleteNode->next;
    deleteNode->next->prev = this;
    delete deleteNode;
}

void TwoSideList::Node::removePrev(){
    Node *deleteNode = this->prev;
    this->prev = deleteNode->prev;
    deleteNode->prev->next = this;
    delete deleteNode;
}

TwoSideList::TwoSideList()
        : _head(nullptr), _tail(nullptr), _size(0){

}

TwoSideList::TwoSideList(const TwoSideList& copyList)
{
    this->_size = copyList._size;
    if (this->_size == 0) {
        this->_head = nullptr;
        this->_tail = nullptr;
        return;
    }

    this->_head = new Node(copyList._head->value);
    this->_tail = new Node(copyList._tail->value);

    Node* currentNode = this->_head;
    Node* currentCopyNode = copyList._head->next;

    while (currentCopyNode) {
        currentNode->next = new Node(currentCopyNode->value);
        currentCopyNode = currentCopyNode->next;
        currentNode = currentNode->next;
    }
}

TwoSideList& TwoSideList::operator=(const TwoSideList& copyList)
{
    if (this == &copyList) {
        return *this;
    }
    TwoSideList bufList(copyList);
    this->_size = bufList._size;
    this->_head = bufList._head;
    this->_tail = bufList._tail;

    return *this;
}

TwoSideList::TwoSideList(TwoSideList&& moveList) noexcept
{
    this->_size = moveList._size;
    this->_head = moveList._head;
    this->_tail = moveList._tail;

    moveList._size = 0;
    moveList._head = nullptr;
    moveList._tail = nullptr;
}

TwoSideList& TwoSideList::operator=(TwoSideList&& moveList) noexcept
{
    if (this == &moveList) {
        return *this;
    }
    forceNodeDelete(_head);
    this->_size = moveList._size;
    this->_head = moveList._head;
    this->_tail = moveList._tail;

    moveList._size = 0;
    moveList._head = nullptr;
    moveList._tail = nullptr;

    return *this;
}

TwoSideList::~TwoSideList(){
    forceNodeDelete(_head);
}

ValueType& TwoSideList::operator[](const size_t pos) const{
    return getNode(pos)->value;
}

TwoSideList::Node* TwoSideList::getNode(const size_t pos) const{
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

void TwoSideList::insert(const size_t pos, const ValueType& value)
{
    if (pos < 0) {
        assert(pos < 0);
    }
    else if (pos >= this->_size) {
        assert(pos >= this->_size);
    }

    if (pos == 0)
        pushFront(value);
    else if (pos == _size - 1)
        pushBack(value);
    else {
        int middle = (_size-1)/2;
        bool f = pos/middle;
        if(f)
            insertBeforeNode(getNode(pos + 1), value);
        else
            insertAfterNode(getNode(pos - 1), value);
    }
}

void TwoSideList::insertAfterNode(Node* node, const ValueType& value){
    if(node->next == nullptr){
        pushBack(value);
    }
    else {
        node->insertNext(value);
        _size++;
    }
}

void TwoSideList::insertBeforeNode(Node* node, const ValueType& value){
    if(node->prev == nullptr){
        pushFront(value);
    }
    else {
        node->insertPrev(value);
        _size++;
    }
}

void TwoSideList::pushBack(const ValueType& value){

    Node *n = new Node(value, nullptr, _tail);
    if(_size == 0){
        _head = n;
        _tail = n;
    }
    else{
        _tail->next = n;
        _tail = n;
    }
    ++_size;
}

void TwoSideList::pushFront(const ValueType& value){

    Node *n = new Node(value, _head, nullptr);
    if(_size == 0){
        _head = n;
        _tail = n;
    }
    else{
        _head->prev = n;
        _head = n;
    }
    ++_size;
}

void TwoSideList::remove(const size_t pos){
    if (pos < 0) {
        assert(pos < 0);
    }
    else if (pos >= this->_size) {
        assert(pos >= this->_size);
    }

    if (pos == 0)
        removeFront();
    else if (pos == _size - 1)
        removeBack();
    else {
        int middle = (_size-1)/2;
        bool f = pos/middle;
        if(f)
            removePrevNode(getNode(pos + 1));
        else
            removeNextNode(getNode(pos - 1));
    }
}

void TwoSideList::removeNextNode(Node* node){
    if(node->next == nullptr);
    else if(node->next == _tail){
        removeBack();
    }
    else {
        node->removeNext();
        _size--;
    }
}

void TwoSideList::removePrevNode(Node* node){
    if(node->prev == nullptr);
    else if(node->prev == _head){
        removeFront();
    }
    else {
        node->removePrev();
        _size--;
    }
}

void TwoSideList::removeFront(){
    Node *deleteHead = getNode(0);
    Node *newHead = getNode(1);
    newHead->prev = nullptr;
    _head = newHead;
    delete deleteHead;
    _size--;
}

void TwoSideList::removeBack(){
    Node *newTail = getNode(_size - 2);
    newTail->next = nullptr;
    Node *deleteTail = getNode(_size - 1);
    _tail = newTail;
    delete deleteTail;
    _size--;
}

long long int TwoSideList::findIndex(const ValueType& value) const
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

TwoSideList::Node* TwoSideList::findNode(const ValueType& value) const
{
    int index = findIndex(value);
    assert(index != -1);
    return getNode(index);
}

void TwoSideList::reverse()
{
        int index = _size-1;
        long double n;
        for(int i = 0; i <= int((_size-1)/2); ++i){
            n = getNode(i)->value;
            getNode(i)->value = getNode(_size - 1 - i)->value;
            getNode(_size - 1 - i)->value = n;
        }

}


TwoSideList TwoSideList::reverse() const
{
    TwoSideList buf(*this);
    buf.reverse();
    return buf;
}

TwoSideList TwoSideList::getReverseList() const
{
    TwoSideList buf(*this);
    buf.reverse();
    return buf;

}

size_t TwoSideList::size() const
{
    return _size;
}

void TwoSideList::forceNodeDelete(Node* node)
{
    if (node == nullptr) {
        return;
    }

    Node* nextDeleteNode = node->next;
    delete node;
    forceNodeDelete(nextDeleteNode);
}




