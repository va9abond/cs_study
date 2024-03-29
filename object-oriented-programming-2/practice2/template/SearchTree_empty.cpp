﻿#include <iostream>

using namespace std;
//узел
template<class T>
class Node
{
protected:
	//закрытые переменные Node N; N.data = 10 вызовет ошибку
	T data;

	//не можем хранить Node, но имеем право хранить указатель
	Node* left;
	Node* right;
	Node* parent;

	//переменная, необходимая для поддержания баланса дерева
	int height;
public:
	//доступные извне переменные и функции
	virtual void setData(T d) { data = d; }
	virtual T getData() { return data; }
	int getHeight() { return height; }

	virtual Node* getLeft() { return left; }
	virtual Node* getRight() { return right; }
	virtual Node* getParent() { return parent; }

	virtual void setLeft(Node* N) { left = N; }
	virtual void setRight(Node* N) { right = N; }
	virtual void setParent(Node* N) { parent = N; }

	//Конструктор. Устанавливаем стартовые значения для указателей
	Node<T>(T n)
	{
		data = n;
		left = right = parent = NULL;
		height = 1;
	}

	Node<T>()
	{
		left = NULL;
		right = NULL;
		parent = NULL;
		data = 0;
		height = 1;
	}


	virtual void print()
	{
		cout << "\n" << data;
	}

	virtual void setHeight(int h)
	{
		height = h;
	}

	template<class T> friend ostream& operator<< (ostream& stream, Node<T>& N);
};

template<class T>
ostream& operator<< (ostream& stream, Node<T>& N)
{
	stream << "\nNode data: " << N.data << ", height: " << N.height;
	return stream;
}
template<class T>
void print(Node<T>* N) { cout << "\n" << N->getData(); }

template<class T>
class Tree
{
protected:
	//корень - его достаточно для хранения всего дерева
	Node<T>* root;

	//поиск узла в дереве. Второй параметр - в каком поддереве искать, первый - что искать
	virtual Node<T> *Find_R(T data, Node<T> *Current)
	{
		//база рекурсии
		if ( Current == nullptr  || Current->getData() == data ) return Current;

		//рекурсивный вызов
		if ( Current->getData() > data ) {
			return Find_R(data, Current->getLeft());
		}
		else {
			return Find_R(data, Current->getRight());
		}

	/*	while ( Current != nullptr || Current->getData() == data ) {
			if ( Current->getData() > data ) {
				Current = Current->getLeft();
			}
			else {
				Current = Current->getLeft();
			}
		}

		return Current;*/
	}


	//рекуррентная функция добавления узла. Интерфейс аналогичен (добавляется корень поддерева, 
	//куда нужно добавлять узел), но вызывает сама себя - добавление в левое или правое поддерево
	virtual Node<T> *insert_R(Node<T> *N, Node<T> *Current)
	{
		//не передан добавляемый узел
		if ( N == NULL ) return NULL;

		//пустое дерево - добавляем в корень
		if ( root == NULL ) {

		}
		// может тернарный
		if ( Current->getData() > N->getData() ) {
			//идем влево
			if ( Current->getLeft() != nullptr ) {
				return insert_R(N, Current->getLeft());
			}
		}
		else {
			Current->setLeft(N); N->setParent(Current);
		}
		if ( Current->getData() < N->getData() ) {
			//идем вправо
			if ( Current->getRight() != nullptr ) {
				return insert_R(N, Current->getRight());
			}
		}
		else {
			Current->setRight(N); N->setParent(Current);
		}
		
		// if ( Current->getData() == N->getData() )
		// TODO: что делать, если совпадение	
		//нашли совпадение
			
		//вернуть добавленный узел

		return N;
	}
public:
	//доступ к корневому элементу
	virtual Node<T>* getRoot() { return root; }

	//конструктор дерева: в момент создания дерева ни одного узла нет, корень смотрит в никуда
	Tree<T>() { root = NULL; }

	//функция добавления узла в дерево
	virtual Node<T>* insert(Node<T>* N)
	{
		return insert_R(N, root);
	}
	


	//функция для добавления числа. Делаем новый узел с этими данными и вызываем нужную функцию добавления в дерево
	
	virtual void insert(T n)
	{
		Node<T>* N = new Node<T>(n);
		insert_R(N);
	}

	//удаление узла
	virtual void Remove(Node<T>* N)
	{ }

	//поиск минимума и максимума в дереве
	virtual Node<T>* Min(Node<T>* Current=NULL)
	{
		if ( root == nullptr ) { return nullptr; }
		
		if ( Current == nullptr ) {
			current = root;
		}


		while ( Current->getLeft() != nullptr ) {
			Node<T> *Current = Current->getLeft();
		}

		return Current;
	}

	virtual Node<T>* Max(Node<T>* Current = NULL)
	{
		if ( root == nullptr ) { return nullptr; }

		if ( Current == nullptr ) {
			current = root;
		}


		while ( Current->getRight() != nullptr ) {
			Node<T> *Current = Current->getRight();
		}

		return Current;
	}

	//поиск узла в дереве
	virtual Node<T>* Find(T data)
	{
		if (root == NULL) return NULL;
		return Find_R(data, root);
	}



	//три обхода дерева
	virtual void PreOrder(Node<T>* N, void (*f)(Node<T>*))
	{
		if (N != NULL)
			f(N);
		if (N != NULL && N->getLeft() != NULL)
			PreOrder(N->getLeft(), f);
		if (N != NULL && N->getRight() != NULL)
			PreOrder(N->getRight(), f);
	}

	//InOrder-обход даст отсортированную последовательность
	virtual void InOrder(Node<T>* N, void (*f)(Node<T>*))
	{
		if (N != NULL && N->getLeft() != NULL)
			InOrder(N->getLeft(), f);
		if (N != NULL)
			f(N);
		if (N != NULL && N->getRight() != NULL)
			InOrder(N->getRight(), f);
	}

	virtual void PostOrder(Node<T>* N, void (*f)(Node<T>*))
	{
		if (N != NULL && N->getLeft() != NULL)
			PostOrder(N->getLeft(), f);
		if (N != NULL && N->getRight() != NULL)
			PostOrder(N->getRight(), f);
		if (N != NULL)
			f(N);
	}
};

//класс итератор по дереву
template<typename ValueType>
class TreeIterator : public std::iterator<std::input_iterator_tag, ValueType>
{
private:
	Node<ValueType>* ptr;
public:
	TreeIterator() { ptr = NULL; }
	TreeIterator(Tree<ValueType>* t, Node<ValueType>* p) {  }
	TreeIterator(const TreeIterator& it) {  }

	TreeIterator& operator=(const TreeIterator& it) {  }
	TreeIterator& operator=(Node<ValueType>* p) {  }

	bool operator!=(TreeIterator const& other) const {  }
	bool operator==(TreeIterator const& other) const {  }
	Node<ValueType>& operator*(){}
	TreeIterator& operator++() 
	{ 
		
	}
	TreeIterator& operator++(int v) 
	{ 
		
	}
};

//класс итерируемое дерево поиска
template<class T>
class IteratedTree : public Tree<T>
{
public:
	IteratedTree<T>() : Tree<T>() {}

	TreeIterator<T> iterator;

	TreeIterator<T> begin() {  }
	TreeIterator<T> end() {  }
};



int main()
{
	Tree<double> T;
	int arr[15];
	int i = 0;
	for (i = 0; i < 15; i++) arr[i] = (int)(100 * cos(15 * double(i)));
	for (i = 0; i < 15; i++) T.insert(arr[i]);

	Node<double>* M = T.Min();
	cout << "\nMin = " << M->getData() << "\tFind " << arr[3] << ": " << T.Find(arr[3], T.getRoot());

	void (*f_ptr)(Node<double>*); f_ptr = print;
	/*cout << "\n-----\nPreorder:";
	T.PreOrder(T.getRoot(), f_ptr);*/
	cout << "\n-----\nInorder:";
	T.InOrder(T.getRoot(), f_ptr);
	/*cout << "\n-----\nPostorder:";
	T.PostOrder(T.getRoot(), f_ptr);*/
	/*cout << "\nIterators:\n";
	T.iterator = T.begin();
	while (T.iterator != T.end())
	{
		cout << *T.iterator << " ";
		T.iterator++;
	}
	cout << *T.iterator << " ";*/

	char c; cin >> c;
	return 0;
}
