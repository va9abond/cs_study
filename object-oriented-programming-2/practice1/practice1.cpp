﻿/*****************************************************************//**
 * \file   practice1.cpp
 * \brief  Практическая работа 1.
 *
 * \author Sirazetdinov Rustem
 * \version
 * \date   September 2022
 *********************************************************************/

#define nline '\n'


#include <iostream>
#include <fstream>


#include <list>
#include <iterator>
#include <algorithm>


#include "Computer.h"
#include "LinkedList.h"
#include "LinkedListIterated.h"
//#include "QueueIterated.h"

/**
 * Помещает объект в контейнер std::list, оставляя его отсортированным.
 *
 * \param list
 * \param object
 */
template<class Type> void push (std::list<Type> &list, const Type &object) {

	// auto it_pos = list.begin();
	std::list<Type>::template iterator it_pos = list.begin();

	while ( it_pos != list.end() ) {
		// >= лучше чем >, т.к. при > вставка сильно замедляется, 
		// если все объекты в списке равны между собой
		if ( *it_pos >= object ) { break; }
		it_pos++;
	}

	list.insert(it_pos, object);
}


/**
 * Удаление элемента из контейнера std::list.
 *
 * Функция удаляет элемент из контейнера и возвращает элемент, который имеет наибольший приоритет,
 * поскольку контейнер отсортирован, наибольший приоритет имеет объект, стоящий самым последним.
 * Если после удаления элемента из контейнера, контейнер оказывается пустым, то возвращается
 * последний удаленный объект.
 *
 * \param list
 * \param pos
 * \return Объект с наибольшим приоритетом.
 */
template<class Type> Type pop (std::list<Type> &list, const int &pos = list.size() - 1) {

	if ( pos > list.size() || pos < 0 ) {
		throw std::out_of_range("pop ( std::list<Type> &list, const int &pos = ... ) Index out of range");
	}

	Type object_remove = list.back();

	std::list<Type>::template iterator it_pos = std::next(list.begin(), pos);
	// or / auto it_pos = std::next(list.begin(), pos);
	// or / std::list<Type>::iterator it_pos = list.begin(); std::advance(it_pos, pos); 

	list.erase(it_pos);


	return object_remove;
}


/**
 * Фильтрация объектов контейнера по функции-ключу.
 *
 * \param list
 * \param *func_key
 * \return Новый контейнер, элементы которого удовлетворяют функции-ключу.
 */
// как передавать произвольный контейнер? 
// ответ: передача итератора начала и конца		
// или template<class Type1, class Type2> ...
template<class Type> std::list<Type> filter (const std::list<Type> &list,
											 bool (*func_key)(const Type, const Type), double param) {
	std::list<Type> ListResult;

	for ( Type object : list ) {
		if ( func_key(param, object) ) { push(ListResult, object); }
	}


	return ListResult;
}

//template< class Container, class Type>
//std::list filter(const Container<Type> &cont,
//				 )



/**
 * Вывод содержимого контейнера.
 *
 * Отправляет каждый элемент контейнера в поток вывода std::ostream.
 *
 * \param list
 */
template<class Type> void print (const std::list<Type> &list) {
	std::cout << nline << "{ ";
	std::for_each(list.begin(), list.end(), [](const Type n) { std::cout << n << ", "; });
	std::cout << "}; " << nline;
}


bool EvaluateFractionalPart (const double p, const double value) {
	int value_ceil = int(value);
	double diff = value - value_ceil;


	return (diff - p < 0);
}






template<class Type>
class QueueIterated : public LinkedListIterated<Type> {
public:

	//friend class Iterator<Type>;

	QueueIterated() {
		std::cout << '\n' << "QueueIterated has been created" << '\n';
	}

	~QueueIterated() = default;


	void master() const noexcept;
	
	//using LinkedListIterated<Type>::push;
	//using LinkedListIterated<Type>::pop;


	void push (const Type &data) override {
		std::cout << "hello" << '\n';
	}

	virtual const Node<Type> *pop() override;

};


template<class Type> void QueueIterated<Type>::master() const noexcept {
	std::cout << "YA ZDES TT";
}




template<class Type> const Node<Type> *QueueIterated<Type>::pop() {
	std::cout << "bingo" << '\n';


	return nullptr;
}

































































































































int main()
{

	// -------------- p.1 --------------
	// Cоздаем лист с элементами типа `int`
	//std::list<double> doubleList;
	//for ( int i = 0; i < 20; i++ ) {
	//	push(doubleList, (double) rand());
	//	//doubleList.push_back( (double)rand() );
	//}

	//// Проверка функции `print` для объектов типа std::list<Type>
	//print(doubleList);

	//// Проверка того, что функция `push` добавляет элементы в контейнер, оставляя его отсортированным
	//if ( std::is_sorted(doubleList.begin(), doubleList.end()) ) { std::cout << "SORTED" << nline; }
	//else { std::cout << "UNSORTED" << nline; }

	//print(doubleList); std::cout << nline;

	//// Удалим из листа несколько значений
	//auto hValue_temp = pop(doubleList, 1); std::cout << hValue_temp << " ";
	//print(doubleList); std::cout << nline;

	//hValue_temp = pop(doubleList, 9); std::cout << hValue_temp << " ";
	//print(doubleList); std::cout << nline;

	//hValue_temp = pop(doubleList, doubleList.size() - 1); std::cout << hValue_temp << " ";
	//print(doubleList); std::cout << nline;



	//// Выделим из нашего листа новый, элементы которого представляют собой
	//// числа типа `double` с дробной частью не превышающей числа `p`.
	////bool (*func_key)(const double, const double) = &EvaluateFractionalPart;
	//using func = bool(*)(const double, const double);
	//func efp = &EvaluateFractionalPart;

	//double param = 0.4567;
	//std::for_each(doubleList.begin(), doubleList.end(), [](double &n) {n /= 100; });


	//print(doubleList);
	////std::list<double> listFiltered = filter(doubleList, func_key, param);
	//std::list<double> listFiltered = filter(doubleList, efp, param);

	//std::cout << nline << "listFiltered is: ";
	//print(listFiltered);

	//doubleList.clear();
	//listFiltered.clear();



	//// -------------- p.2 --------------
	//std::list<Computer> computerList;

	//Computer Apple ((std::string) "apple", 1000, 16, 64, 17.8);
	//Computer Lenovo ((std::string) "lenovo", 500, 16, 16, 15.0);
	//Computer Huawei ((std::string) "huawei", 400, 16, 32, 16.7);
	//Computer HP ((std::string) "hp", 350, 4, 8, 14.5);
	//Computer Dell ((std::string) "dell", 200, 4, 8, 16.2);

	//push(computerList, Apple);
	//push(computerList, Lenovo);
	//push(computerList, Huawei);
	//push(computerList, HP);
	//push(computerList, Dell);

	//print(computerList);

	//auto hvalue = pop(computerList, 2);
	//std::cout << nline << "hvalue is: " << hvalue;

	//print(computerList);


	//Computer computer_undef; std::cout << computer_undef;

	
	QueueIterated<double> queue;

	//queue.push(1);
	//queue.print();

















	return 0;
}

