﻿/*****************************************************************//**
 * \file   LinkedList.cpp
 * \brief  Файл определения класса `LinkedList`.
 *
 * Реализация контейнера std::list<Type> через указатели.
 * Использован вспомогательный класс `Node`.
 *
 * \author averu
 * \version
 * \date   September 2022
 *********************************************************************/
#include "LinkedList.h"
#include <iostream>
#include <ostream>
#include <filesystem>

#define nline '\n'

/**
 * Конструктор по умолчанию.
 *
 */
template<class Type> LinkedList<Type>::LinkedList() {
	_begin = _end = nullptr;
	_size = 0;
}

/**
 * Конструктор копий(Deep copy).
 *
 * \param otherList
 */
template<class Type> LinkedList<Type>::LinkedList(const LinkedList<Type> &otherList) {
	if ( otherList._size != 0 ) {
		_begin = new Node<Type>(otherList._begin->GetData());

		Node<Type> *ptrCurrent = _begin;
		Node<Type> *ptrCurrentOther = otherList._begin;

		while ( ptrCurrentOther != otherList._end ) {

			Node<Type> *ptrCurrentNext = new Node<Type>((ptrCurrentOther->GetSucessor())->GetData(), nullptr, ptrCurrent);

			ptrCurrent->SetSucessor(ptrCurrentNext);

			ptrCurrent = ptrCurrentNext;
			ptrCurrentOther = ptrCurrentOther->GetSucessor();
		}
		_end = ptrCurrent;
	}
	else {
		_begin = _end = nullptr;
	}

	_size = otherList._size;
}

/**
 * Перегрузка оператора `operator=`.
 *
 * \warning Глубокое копирование.
 *
 * \param otherList
 * \return Новый экземпляр класса `LinkedList<Type>`, данные которого идентичны
 * объекту `otherList`, но ячейки памяти не пресекаются.
 */
template<class Type>
LinkedList<Type> &LinkedList<Type>::operator=(const LinkedList &otherList) {

	Node<Type> *nodeCurrent = _begin;
	Node<Type> *nodeCurrentOther = otherList._begin;

	if ( _size == otherList._size ) {
		while ( nodeCurrentOther != nullptr ) {
			nodeCurrent._data = nodeCurrentOther._data;

			nodeCurrent = nodeCurrent->GetSucessor();
			nodeCurrentOther = nodeCurrentOther->GetSucessor();
		}
	}
	else {
		this->clear();

		if ( otherList._size == 0 ) {
			_begin = _end = nullptr;
		}
		else {
			_begin = new Node<Type>(nodeCurrentOther._data);
			nodeCurrent = _begin;
			nodeCurrentOther = nodeCurrentOther->GetSucessor();

			while ( nodeCurrentOther != nullptr ) {

				Node<Type> *nodeCurrentNext = new Node<Type>(nodeCurrentOther._data, nullptr, nodeCurrent);

				nodeCurrent->SetSucessor(nodeCurrentNext);

				nodeCurrent = nodeCurrentNext;
				nodeCurrentOther = nodeCurrentOther->GetSucessor();
			}

			_end = nodeCurrent;
			_size = otherList._size;
		}

	}
}

/**
 * Деструктор.
 *
 * Деструктор реализовани через вспомогательный метод `LinkedList<Type>::clear()`.
 *
 */
template<class Type> LinkedList<Type>::~LinkedList() {
	this->clear();
}



/**
 * Метод очищает экземпляр класса `LinkedList<Type>`.
 *
 */
template<class Type> void LinkedList<Type>::clear() {
	Node<Type> *deleteNext = _begin;

	while ( deleteNext != nullptr ) {
		Node<Type> *deleteNext = _begin->GetSucessor();
		delete _begin; _begin = deleteNext;
	}
	_size = 0;
}

/**
 * Метод позволяет узнать количество элементов класса `Node<Type`
 * в экземпляре класса `LinkedList<Type>.
 *
 * \return Количество элементов класса `Node<Type`
 */
template<class Type>
const size_t LinkedList<Type>::size() const noexcept { return _size; }


/**
 * Метод позволяет получить указатель на начало контейнера.
 *
 * \return Указатель на начало контейнера.
 */
template<class Type>
const Node<Type> *LinkedList<Type>::GetBegin() const noexcept {
	return _begin;
}

/**
 * Метод позволяет получить указатель на конец контейнера.
 *
 * \return Указатель на конец контейнера.
 */
template<class Type>
const Node<Type> *LinkedList<Type>::GetEnd() const noexcept {
	return _end;
}

/**
 * Метод позволяет задать новое значение указателя на
 * начало контейнера.
 *
 * \param newBegin
 */
template<class Type>
void LinkedList<Type>::SetBegin(const Node<Type> newBegin) noexcept {
	_begin = newBegin;
}

/**
 * Метод позволяет задать новое значение указателя на
 * начало контейнера.
 *
 * \param newEnd
 */
template<class Type>
void LinkedList<Type>::SetEnd(const Node<Type> newEnd) noexcept {
	_end = newEnd;
}



/**
 * Перегрузка оператора `operator[]`.
 *
 * \param pos
 * \return Объект класса `Node<Type>`, стоящий на позиции
 * `pos - 1` в контейнере.
 */
template<class Type>
const Node<Type> *LinkedList<Type>::operator[](const int &pos) noexcept(false) {

	if ( pos < 0 || pos >= _size ) {
		throw std::out_of_range("Method LinkedList<Type>::operator[] : pos out of range");
	}
	Node<Type> *nodeCurrent = _begin;

	for ( int it = 0; it < pos; it++ ) {
		nodeCurrent = nodeCurrent->GetSucessor();
	}


	return nodeCurrent;
}



/**
 * Перегрузка оператора `operator<<` вывода в поток `std::ostream` или `std::ofstream`.
 *
 * \param output
 * \param list
 * \return Ссылку на поток `std::ostream`.
 */
template<class Type> std::ostream &operator<< (std::ostream &output,
											   LinkedList<Type> &list) noexcept(false) {
	if ( list._size != 0 ) {
		Node<Type> *nodeCurrent = list.GetBegin();

		if ( typeid(output).name() == typeid(std::ofstream).name() ) {
			if ( output.fail() ) {
				throw std::filesystem::filesystem_error("LinkedList<Type>::operator<< : could not open the file");
			}
			output << list.size() << nline;

			while ( nodeCurrent != nullptr ) {
				output << nodeCurrent->_data << " ";
				nodeCurrent = nodeCurrent->GetSucessor();
			}
		}
		else {
			output << nline << "Size: " << list._size << nline;

			int it = 0;
			while ( nodeCurrent != nullptr ) {
				output << "[" << it << "] = " << nodeCurrent->_data << nline;
			}
		}
	}


	return output;
}

