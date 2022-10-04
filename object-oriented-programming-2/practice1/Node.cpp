﻿/*****************************************************************//**
 * \file   Node.cpp
 * \brief  Файл опеределения класса `Node`.
 *
 * Вспомогательный класс для контейнеров. Выступает в роли
 * элемента контейнера. Класс реализован через указатели.
 * Опеределение класса смотри в файле `Node.h`.
 *
 * \author averu
 * \version
 * \date   September 2022
 *********************************************************************/
#include "Node.h"

/**
 * Конструктор класса `Node<Type>`.
 *
 * \param data
 * \param sucessor
 * \param predecessor
 */
template<class Type> Node<Type>::Node(const Type &data,
									  Node<Type> *sucessor,
									  Node<Type> *predecessor) {
	_sucessor = sucessor;
	_predecessor = predecessor;
	_data = data;
}

/**
 * Деструктор класса `Node<Type>`.
 *
 * /waring Деструктор определен компилятором.
 */
template<class Type> Node<Type>::~Node () = default;

/**
 * Предоставляет возможность получить доступ к полю `_sucessor`.
 *
 * \return Указатель на следующий узел.
 */
template<class Type> const Node<Type> *Node<Type>::GetSucessor() const noexcept {
	return _sucessor;
}

/**
 * Предоставляет возможность получить доступ к полю `_predecessor`.
 *
 * \return Указатель на предыдущий узел.
 */
template<class Type> const Node<Type> *Node<Type>::GetPredecessor() const noexcept {
	return _predecessor;
}

/**
 * Предоставляет возможность получить доступ к полю `_data`.
 *
 * \return Копию данных, которые содержит текущий узел.
 */
template<class Type> const Type &Node<Type>::GetData() const noexcept {
	return _data;
}

/**
 * Предоставляет возможность установить новое значение для поля `_sucessor`.
 *
 * \param sucessor
 * \return
 */
template<class Type> void Node<Type>::SetSucessor (const Node<Type> *sucessor) noexcept {
	_sucessor = sucessor;
}

/**
 * Предоставляет возможность установить новое значение для поля `_predecessor`.
 *
 * \param predecessor
 */
template<class Type> void Node<Type>::SetPredecessor (const Node<Type> *predecessor) noexcept {
	_predecessor = predecessor;
}

/**
 * Предоставляет возможность установить новое значения для поля `_data`.
 *
 * \param data
 */
template<class Type> void Node<Type>::SetData (const Type & data) noexcept {
	_data = data;
}

/**
 * Проверка равенства объектов(deep).
 *
 *
 * \param node
 * \return
 */
template<class Type> bool Node<Type>::DeepEqual (const Node<Type> &node) const noexcept {
	if ( _data == node._data &&
		_sucessor == node._sucessor &&
		_predecessor == node._predecessor ) {
		return true;
	}


	retunr false;
}

/**
 * Проверка равенства объектов(shallow).
 *
 * \param node
 * \return
 */
template<class Type> bool Node<Type>::operator== (const Node<Type> &node) const noexcept {
	if ( _data == node._data &&
		_sucessor._data == node._sucessor._data &&
		_predecessor._data == node._predecessor._data ) {
		return true;
	}


	retunr false;
}

/**
 * Проверка неравенства объектов(shallow).
 *
 * \param node
 * \return
 */
template<class Type> bool Node<Type>::operator!= (const Node<Type> &node) const noexcept {
	return !(*this == node);
}

/**
 * Перегрузка оператора разыменования.
 *
 * \return Ссылка на константный объект типа `Type`.
 */
template<class Type> const Type &Node<Type>::operator*() const {
	if ( this == nullptr ) {
		throw std::invalid_argument("Node<Type> : operator*");
	}


	return _data;
}

/**
 * Перегрузка оператора `operator<<`.
 *
 * \param output
 * \param node
 * \return Ссылку на стандартный поток вывода.
 */
template<class Type> std::ostream &operator<< (std::ostream & output,
											   const Node<Type> &node) {
	output << node._data;


	return output;
}