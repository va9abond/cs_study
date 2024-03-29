﻿/*****************************************************************//**
 * \file   LinkedList.h
 * \brief  Файл реализации параметризованного класса `LinkedList`.
 *
 * \author  Sirazetdinov Rustem
 * \version
 * \date    October 2022
 *********************************************************************/
#pragma once

#include "IList.h"
#include <iostream>
#include <fstream>

/**
 * /brief Класс представляет собой параметризованный двусвязный список.
 */
template<class Type> class LinkedList : public IList<Type> {
public:

    LinkedList();

    LinkedList (const LinkedList<Type> &otherList) noexcept;

    LinkedList<Type> &operator= (const LinkedList<Type> &otherList) noexcept;

    virtual ~LinkedList();


    // ----------------------------------------------------------------------
    // ----------------------------------------------------------------------


    Type &front() const noexcept;

    Type &back() const noexcept;


    // ----------------------------------------------------------------------
    // ----------------------------------------------------------------------


    bool empty() const noexcept override;

    size_t size() const noexcept override;


    // ----------------------------------------------------------------------
    // ----------------------------------------------------------------------


    virtual void clear() noexcept override;

    virtual void insert (const int &pos, const Type &data) override;

    virtual Type &erase (const int &pos) override;

    virtual void push_back (const Type &data) noexcept override;

    virtual Type &pop_back();

    virtual void push_front (const Type &data) noexcept override;

    virtual Type &pop_front() override;


    // ----------------------------------------------------------------------
    // ----------------------------------------------------------------------


    Node<Type> *getBegin() const noexcept;

    Node<Type> *getEnd() const noexcept;

    void setBegin (const Node<Type> *begin);

    void setBegin (const Type &data);

    void setEnd (const Node<Type> *end);

    void setEnd (const Type & data);


    // ----------------------------------------------------------------------
    // ----------------------------------------------------------------------


    Node<Type> *operator[] (const int &pos) const;


    // ----------------------------------------------------------------------
    // ----------------------------------------------------------------------


    virtual void print() const noexcept;

    virtual void print_reverse() const noexcept;

    template<class otherType> friend std::ostream &operator<< (std::ostream &output,
                                                               LinkedList<otherType> &list) noexcept(false);

    // ----------------------------------------------------------------------
    // ----------------------------------------------------------------------

protected:
    Node<Type> *_begin;
    Node<Type> *_end;
    size_t      _size;
};


// ----------------------------------------------------------------------
// ----------------------------------------------------------------------
// ----------------------------------------------------------------------
// ----------------------------------------------------------------------
// ----------------------------------------------------------------------
// ----------------------------------------------------------------------


template<class Type> LinkedList<Type>::LinkedList() {
    _begin = _end = nullptr;
    _size = 0;
}


template<class Type> LinkedList<Type>::LinkedList (const LinkedList<Type> &otherList) noexcept {

    if ( otherList._size != 0 ) {
        _begin = new Node<Type>(otherList._begin->getData());

        Node<Type> *ptrCurrent = _begin;
        Node<Type> *ptrCurrentOther = otherList._begin;

        while ( ptrCurrentOther != otherList._end ) {

            Node<Type> *ptrCurrentNext = new Node<Type>((ptrCurrentOther->getSucessor())->getData(), nullptr, ptrCurrent);

            ptrCurrent->setSucessor(ptrCurrentNext);

            ptrCurrent = ptrCurrentNext;
            ptrCurrentOther = ptrCurrentOther->getSucessor();
        }
        _end = ptrCurrent;
    }
    else {
        _begin = _end = nullptr;
    }

    _size = otherList._size;
}


template<class Type> LinkedList<Type> &LinkedList<Type>::operator= (const LinkedList<Type> &otherList) noexcept {
    this->clear();

    _size = otherList._size;
    _begin = _end = nullptr;

    if ( _size > 0 ) {
        Node<Type> *nodeOther = otherList._begin;
        Node<Type> *nodeThis = new Node<Type>(nodeOther->getData());
        Node<Type> *nextToThis = nullptr;

        _begin = nodeThis;
        nodeOther = nodeOther->getSucessor();

        while ( nodeOther != nullptr ) {
            nextToThis = new Node<Type>(nodeOther->getData(), nullptr, nodeThis);
            nodeThis->setSucessor(nextToThis);
            nodeThis = nextToThis;
            nodeOther = nodeOther->getSucessor();
        }
    }


    return *this;
}


template<class Type> LinkedList<Type>::~LinkedList() {
    while ( _begin != nullptr ) {
        Node<Type> *nodeToDelete = _begin->getSucessor();
        delete _begin; _begin = nodeToDelete;
    }
    _size = 0;
}


// ----------------------------------------------------------------------
// ----------------------------------------------------------------------


template<class Type> Type &LinkedList<Type>::front() const noexcept {
    return const_cast<Type &>(_begin->getData());
}


template<class Type> Type &LinkedList<Type>::back() const noexcept {
    return const_cast<Type &>(_end->getData());
}


// ----------------------------------------------------------------------
// ----------------------------------------------------------------------


template<class Type> bool LinkedList<Type>::empty() const noexcept {
    return (_size == 0 ? 1 : 0);
}


template<class Type> size_t LinkedList<Type>::size() const noexcept {
    return _size;
}


// ----------------------------------------------------------------------
// ----------------------------------------------------------------------


template<class Type> void LinkedList<Type>::clear() noexcept {
    while ( _begin != nullptr ) {
        Node<Type> *nodeToDelete = _begin->getSucessor();
        delete _begin; _begin = nodeToDelete;
    }
    _size = 0;
}


template<class Type> void LinkedList<Type>::insert (const int &pos, const Type &data) {
    if ( pos <= 0 || pos >= _size ) {
        throw std::out_of_range("LinkedList<Type>::insert(...): pos out of range");
    }

    if ( pos == _size - 1 ) {
        return this->push_back(data);
    }
    else if ( pos == 0 ) {
        return this->push_front(data);
    }
    else {
        Node<Type> *nodeBeforeInsert = _begin;
        for ( int i = 0; i < pos; i++ ) {
            nodeBeforeInsert = nodeBeforeInsert->getSucessor();
        }

        Node<Type> *nodeInsert = new Node<Type>(data, nodeBeforeInsert->getSucessor(), nodeBeforeInsert);

        nodeBeforeInsert->setSucessor(nodeInsert);
        (nodeInsert->getSucessor())->setPredecessor(nodeInsert);

        _size += 1;
    }
}


template<class Type> Type &LinkedList<Type>::erase (const int &pos) {
    if ( _size == 0 ) {
        throw std::exception("Method LinkedList<Type>::erase(...): size = 0");
    }

    if ( pos == _size - 1 ) {
        return this->pop_back();
    }
    else if ( pos == 0 ) {
        return this->pop_front();
    }
    else {
        Node<Type> *nodeErased = _begin;
        for ( int i = 0; i < pos; i++ ) {
            nodeErased = nodeErased->getSucessor();
        }

        Type &dataErased = const_cast<Type &>(nodeErased->getData());

        (nodeErased->getPredecessor())->setSucessor(nodeErased->getSucessor());
        (nodeErased->getSucessor())->setPredecessor(nodeErased->getPredecessor());
        delete nodeErased;

        _size -= 1;
        return dataErased;
    }
}


template<class Type> void LinkedList<Type>::push_back (const Type &data) noexcept {
    Node<Type> *endNew = new Node<Type>(data, nullptr, _end);
    if ( _size != 0 ) {
        _end->setSucessor(endNew);
    }
    else {
        _begin = endNew;
    }

    _end = endNew;
    _size += 1;
}


template<class Type> Type &LinkedList<Type>::pop_back() {
    if ( _size == 0 ) {
        throw std::exception("Method LinkedList<Type>::pop_back(): size = 0");
    }

    Type &dataErased = const_cast<Type &>(_end->getData());
    if ( _size == 1 ) {
        delete _end;
        _begin = _end = nullptr;
    }
    else {
        _end = _end->getPredecessor();
        delete (_end->getSucessor());
        _end->setSucessor(nullptr);
    }


    _size -= 1;
    return dataErased;
}


template<class Type> void LinkedList<Type>::push_front (const Type &data) noexcept {
    Node<Type> *beginNew = new Node<Type>(data, _begin, nullptr);
    if ( _size != 0 ) {
        _begin->setPredecessor(beginNew);
    }
    else {
        _end = beginNew;
    }

    _begin = beginNew;
    _size += 1;
}


template<class Type> Type &LinkedList<Type>::pop_front() {
    if ( _size == 0 ) {
        throw std::exception("Method LinkedList<Type>::pop_front(): size = 0");
    }

    Type &dataErased = const_cast<Type &>(_end->getData());
    if ( _size == 1 ) {
        delete _begin;
        _begin = _end = nullptr;
    }
    else {
        _begin = _begin->getSucessor();
        delete (_begin->getPredecessor());
        _begin->setPredecessor(nullptr);
    }

    _size -= 1;
    return dataErased;
}


// ----------------------------------------------------------------------
// ----------------------------------------------------------------------


template<class Type> Node<Type> *LinkedList<Type>::getBegin() const noexcept {
    return _begin;
}


template<class Type> Node<Type> *LinkedList<Type>::getEnd() const noexcept {
    return _end;
}


template<class Type> void LinkedList<Type>::setBegin (const Node<Type> *begin) {
    if ( begin->getSucessor() != _begin->getSucessor() ) {
        throw std::invalid_argument("Method LinkedList<Type>::setBegin(...): pointers to sucessors don't match");
    }
    _begin = begin;
}


template<class Type> void LinkedList<Type>::setBegin (const Type &data) {
    _begin->setData(data);
}


template<class Type> void LinkedList<Type>::setEnd (const Node<Type> *end) {
    if ( end->getPredecessor() != _end->getPredecessor() ) {
        throw std::invalid_argument("Method LinkedList<Type>::setEnd(...): pointers to predecessors don't match");
    }
    _end = end;
}


template<class Type> void LinkedList<Type>::setEnd (const Type &data) {
    _end->setData(data);
}


// ----------------------------------------------------------------------
// ----------------------------------------------------------------------


template<class Type> Node<Type> *LinkedList<Type>::operator[] (const int &pos) const {
    if ( pos < 0 || pos >= _size ) {
        throw std::out_of_range("Method LinkedList<Type>::operator[...] : pos out of range");
    }

    Node<Type> *node = _begin;

    for ( int i = 0; i < pos; i++ ) {
        node = node->getSucessor();
    }


    return node;
}


// ----------------------------------------------------------------------
// ----------------------------------------------------------------------


template<class Type> void LinkedList<Type>::print() const noexcept {
    Node<Type> *current = _begin;

    std::cout << nline << "{ : ";

    for ( int i = 0; i < _size; i++ ) {
        std::cout << current->getData() << " : ";
        current = current->getSucessor();
    }

    std::cout << "}; " << nline;
}


template<class Type> void LinkedList<Type>::print_reverse() const noexcept {
    Node<Type> *current = _end;

    std::cout << nline << "{ : ";

    for ( int i = 0; i < _size; i++ ) {
        std::cout << current->getData() << " : ";
        current = current->getPredecessor();
    }

    std::cout << "}; " << nline;
}


// ----------------------------------------------------------------------
// ----------------------------------------------------------------------


template<class Type> std::ostream &operator<< (std::ostream &output,
                                               LinkedList<Type> &list) noexcept(false) {
    if ( list.LinkedList<Type>::_size != 0 ) {
        Node<Type> *nodeCurrent = list.getBegin();

        if ( typeid(output).name() == typeid(std::ofstream).name() ) {
            if ( output.fail() ) {
                throw std::ios_base::failure("LinkedList<Type>::operator<<: could not open the file");
            }
            output << list.size() << nline;

            while ( nodeCurrent != nullptr ) {
                output << nodeCurrent->getData() << " ";
                nodeCurrent = nodeCurrent->getSucessor();
            }
        }
        else {
            output << nline << "Size: " << list._size << nline;

            int it = 0;
            while ( nodeCurrent != nullptr ) {
                output << "[" << it << "] = " << nodeCurrent->getData() << nline;
                nodeCurrent = nodeCurrent->getSucessor();
                it++;
            }
        }
    }


    return output;
}
