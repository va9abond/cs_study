﻿#include <map>
#include <set>

#include <utility>
#include <string>
#include <iostream>
#include <vector>





namespace ds {

// ---------------------------------------------------------------------------------------------
// ---------------------------------------------------------------------------------------------


template <typename Type1, typename Type2> class ipair {
public:

	virtual Type1 first () const noexcept = 0;
	virtual Type2 second () const noexcept = 0;

};

// ---------------------------------------------------------------------------------------------
// ---------------------------------------------------------------------------------------------


template<typename Type1, typename Type2> class pair : ipair<Type1, Type2> {
public:

	pair (const Type1 &value1, const Type2 &value2) {
		_value1 = value1;
		_value2 = value2;
	}


	pair (const pair &pair_other) {
		_value1 = pair_other._value1;
		_value2 = pair_other._value2;
	}



	virtual ~pair() = default;



	virtual Type1 first ()  const noexcept override final { return _value1; }
	virtual Type2 second () const noexcept override final { return _value2; }



	virtual bool operator == (const pair &pair_other) const noexcept {
		return (_value1 == pair_other._value1 && _value2 == pair_other._value2 ? true : false);
	}

	virtual bool operator > (const pair &pair_other) const noexcept {
		if ( _value1 > pair_other._value1 ) {
			return true;
		}
		else if ( _value1 == pair_other._value1 ) {
			return (_value2 > pair_other._value2 ? true : false);
		}


		return false;
	}

	bool operator < (const pair &pair_other) const noexcept {
		return !(*this >= pair_other );
	}

	bool operator >= (const pair &pair_other) const noexcept {
		return (*this > pair_other || *this == pair_other);
	}

	bool operator <= (const pair &pair_other) const noexcept {
		return !(*this > pair_other);
	}



protected:
	Type1 _value1;
	Type2 _value2;
};

template<typename Type1, typename Type2>
std::ostream &operator<< (std::ostream &output, const pair<Type1, Type2> &pair) {
	// output << '\n' << "first: " << pair.first() << '\n' << "second: " << pair.second() << '\n';
	// output << '\n' << "{first, second} : {" << pair.first() << ", " << pair.second() << "}; " << '\n';
	output << "(" << pair.first() << ", " << pair.second() << ")";

	return output;
}


template<typename Type1, typename Type2>
ds::pair<Type1, Type2> &make_pair (const Type1 &value1, const Type2 &value2) noexcept {
	return ds::pair<Type1, Type2>(value1, value2);
}

template<typename Type1, typename Type2>
std::pair<Type1, Type2> &make_std_pair (const Type1 &value1, const Type2 &value2) noexcept {
	return std::make_pair(value1, value2);
}

// ---------------------------------------------------------------------------------------------
// ---------------------------------------------------------------------------------------------


class bike_key final : public ds::pair<std::string, int> {
public:

	bike_key (const std::string &brand = "", int diameter = -1) : pair (brand, diameter) {};

	//bike_key (const bike_key &key_other) {
	//	_value1 = key_other._value1;
	//	_value2 = key_other._value2;
	//}

	bool operator > (const pair &pair_other) const noexcept override {
		if ( _value2 > pair_other.second() ) {
			return true;
		}
		

		return false;
	}


	virtual ~bike_key() = default;

};


// ---------------------------------------------------------------------------------------------
// ---------------------------------------------------------------------------------------------


class bike_value final : public ds::pair<std::string, bool> {
public:

	bike_value (const std::string &type, bool is_absorb) : pair (type, is_absorb) {};

	virtual ~bike_value() = default;
};


// ---------------------------------------------------------------------------------------------
// ---------------------------------------------------------------------------------------------


}


// ---------------------------------------------------------------------------------------------
// ---------------------------------------------------------------------------------------------

// ---------------------------------------------------------------------------------------------
// ------------------------------------------task(2.1.2)----------------------------------------
// ---------------------------------------------------------------------------------------------
// CONSTANT realisation
// TODO: doesn't work with `&find_value`, mb because result_iter is pointer and &(pointer) is undefined
//std::map<ds::bike_key, ds::bike_value>::const_iterator find_value (const std::map<ds::bike_key, ds::bike_value> &map,
//																			 const ds::bike_key &key) noexcept {
//	auto result_iter = map.find(key);
//	return result_iter;
//}

// CONSTANT + TEMPLATE realisation
template <typename Key, typename Value>
typename std::map<Key, Value>::const_iterator find_value (const std::map<Key, Value> &map,
														  const ds::bike_key &key) noexcept {
	auto result_iter = map.find(key);
	return result_iter;
}

// NON CONSTANT realisation
//std::map<ds::bike_key, ds::bike_value>::iterator find_value (std::map<ds::bike_key, ds::bike_value> &map,
//																	   const ds::bike_key &key) noexcept {
//	auto result_iter = map.find(key);
//	return result_iter;
//}



// CONSTANT + TEMPLATE realisation
template <typename Key, typename Value>
typename std::map<Key, Value>::const_iterator find_key (const std::map<Key, Value> &map,
														const ds::bike_value &value) noexcept {
	auto iter = map.begin();

	while ( iter != map.end() ) {
		if ( iter->second == value ) { break; }

		iter++;
	}


	return iter;
}

const std::string foo (std::vector<std::string> vector) {
	std::string answer;
	for ( const auto &element : vector ) {
		if ( element == "key" ) {
			answer = element;
			break;
		}
	}


	return answer;
}

// ---------------------------------------------------------------------------------------------
// ------------------------------------------task(2.2.2)----------------------------------------
// ---------------------------------------------------------------------------------------------
// CONSTANT + TEMPLATE realisation
template <typename Key, typename Value>
typename std::multimap<Key, Value>::const_iterator find_value_multi (const std::multimap<Key, Value> &multimap,
														  			 const ds::bike_key &key) noexcept {
	auto result_iter = multimap.find(key);
	return result_iter;
}

template <typename Key, typename Value>
std::vector<typename std::multimap<Key, Value>::const_iterator> find_value_multi_variative (const std::multimap<Key, Value> &multimap,
														  			 						const ds::bike_key &key) noexcept {
	std::vector<typename std::multimap<Key, Value>::const_iterator>vector_result(0); 
	
	auto iter = multimap.begin();
	while ( iter != multimap.end() ) {
		if ( iter->first == key ) { vector_result.push_back(iter); }

		iter++;
	}
	return vector_result;
}


// CONSTANT + TEMPLATE realisation
template <typename Key, typename Value>
typename std::multimap<Key, Value>::const_iterator find_key_multi (const std::multimap<Key, Value> &multimap,
																   const ds::bike_value &value) noexcept {
	auto iter = multimap.begin();

	while ( iter != multimap.end() ) {
		if ( iter->second == value ) { break; }

		iter++;
	}


	return iter;
}


// ---------------------------------------------------------------------------------------------
// ------------------------------------------task(2.1.3)----------------------------------------
// ---------------------------------------------------------------------------------------------

template<typename Key, typename Value> void print_iter (const std::map<Key, Value> &map) {
	auto itt = map.begin();

	std::cout << "{" << '\n';
	while ( itt != map.end() ) {
		std::cout << (*itt).first << " --- " << (*itt).second << '\n';
		itt++;
	}
	std::cout << "};" << '\n';

}

// ---------------------------------------------------------------------------------------------
// ------------------------------------------task(2.2.3)----------------------------------------
// ---------------------------------------------------------------------------------------------


template<typename Iterator_type>
void print_iter (Iterator_type begin, Iterator_type end) {

	std::cout << "{" << '\n';

	while ( begin != end ) {
		std::cout << (*begin).first << " --- " << (*begin).second << '\n';
		begin++;
	}
	std::cout << "};" << '\n';
}

template<typename Iterator_type>
void print_iter_set (Iterator_type begin, Iterator_type end) {

	std::cout << "{" << '\n';

	while ( begin != end ) {
		std::cout << *begin << '\n';
		begin++;
	}
	std::cout << "};" << '\n';
}


// ---------------------------------------------------------------------------------------------
// ------------------------------------------task(2.1.4)----------------------------------------
// ---------------------------------------------------------------------------------------------

bool func_key (const ds::bike_value &value, const int &threshold = 0) {
	return (value.second() > threshold);
}

using func = bool(*)(const ds::bike_value &, const int &);
func func_task4 = &func_key;

// TODO: doesn't work with &filter, idk
template<typename Key, typename Value>
std::map<Key, Value> filter (const std::map<Key, Value> &map,
							 bool(*func_key)(const Value &, const int &),
							 const int &threshold) {
	std::map<Key, Value> map_result;

	for ( const auto &element : map ) {
		if ( func_key(element.second, threshold) == true ) {
			map_result.insert(element);
		}
	}

	// TODO: the code below doesn't work, idk what the problem
	/*auto iter = map.begin();
	while ( iter != map.end() ) {
		if (func_key( (*iter).second, threshold ) == true ) {
			map_result.insert(*iter);
		}
	}*/

	return map_result;
}

// ---------------------------------------------------------------------------------------------
// ------------------------------------------task(2.2.4)----------------------------------------
// ---------------------------------------------------------------------------------------------

template<typename Key, typename Value>
std::multimap<Key, Value> filter_multi (const std::multimap<Key, Value> &map,
							      		bool(*func_key)(const Value &, const int &),
							      		const int &threshold) {
	std::multimap<Key, Value> multimap_result;

	for ( const auto &element : map ) {
		if ( func_key(element.second, threshold) == true ) {
			multimap_result.insert(element);
		}
	}

	
	return multimap_result;
}

// ---------------------------------------------------------------------------------------------
// ------------------------------------------task(2.1.5)----------------------------------------
// ---------------------------------------------------------------------------------------------

class Exception : public std::exception {
public:

	Exception() {
		message_ = "";
	}

	Exception (const std::string &message) {
		message_ = std::string(message);
	}

	Exception (const Exception &exception) {
		message_ = exception.message_;
	}

	virtual ~Exception() = default;



	virtual void what() {
		std::cout << '\n' << "{Exception}: " << message_ << "; " << std::exception::what();
	}

protected:
	std::string message_; // error message
};

class invalid_key : public Exception {
public:
	
	invalid_key (const std::string &message,
				 ds::bike_key &key,
				 std::map<ds::bike_key, ds::bike_value> &map) : Exception(message) {
		key_ = key;
		map_ = map;
	}

	virtual ~invalid_key() = default;



	virtual void what() override {
		std::cout << '\n' << "{invalid_value} --> " << message_ << "; " << std::exception::what();
	}

protected:
	ds::bike_key key_;
	std::map<ds::bike_key, ds::bike_value> map_;
};




template <typename Key, typename Value>
std::pair<typename std::map<Key, Value>::iterator, bool> insert(std::map<Key, Value> &map,
																std::pair<ds::bike_key, ds::bike_value> &pair) {
	if ( find_key(map, pair.second) != map.end() ) {
		throw invalid_key("invalid_key: key already exists in container", pair.first, map);
	}
	else {
		auto pair_result = map.insert(pair);
		return pair_result;
	}
}

//using myIterator = typename std::map<ds::bike_key, ds::bike_value>::iterator;
//std::pair<myIterator, bool> &insert(std::map<ds::bike_key, ds::bike_value> &map,
//				                      std::pair<ds::bike_key, ds::bike_value> &pair) {
//	if ( find_key(map, pair.second) != map.end() ) {
//		throw invalid_key("invalid_kye: key already exists in container", pair.first, map);
//	}
//	else {
//		auto pair_result = map.insert(pair);
//		return pair_result;
//	}
//}

// ---------------------------------------------------------------------------------------------
// ------------------------------------------task(2.1.6)----------------------------------------
// ---------------------------------------------------------------------------------------------

template<typename Key, typename Value>
std::set<Value> filterSet (const std::map<Key, Value> &map,
						  bool(*func_key)(const Value &, const int &),
						  const int &threshold) {
	std::set<Value> set_result;

	for ( const auto &element : map ) {
		if ( func_key(element.second, threshold) == true ) {
			set_result.insert(element.second);
		}
	}


	return set_result;
}

// ---------------------------------------------------------------------------------------------
// ------------------------------------------task(2.2.6)----------------------------------------
// ---------------------------------------------------------------------------------------------

template<typename Key, typename Value>
std::multiset<Value> filterSet_multi (const std::multimap<Key, Value> &map,
						  bool(*func_key)(const Value &, const int &),
						  const int &threshold) {
	std::multiset<Value> multiset_result;

	for ( const auto &element : map ) {
		if ( func_key(element.second, threshold) == true ) {
			multiset_result.insert(element.second);
		}
	}


	return multiset_result;
}

// ---------------------------------------------------------------------------------------------
// ---------------------------------------------------------------------------------------------

using namespace ds;
int main() {

// ---------------------------------------------------------------------------------------------
// ------------------------------------------task(2.1.1)----------------------------------------
// ---------------------------------------------------------------------------------------------
	std::vector<ds::bike_key> vector_key;
	std::vector<ds::bike_value> vector_value;
	std::string value = "v";
	std::string key = "k";

	std::map<bike_key, bike_value> bike_map;

	for ( int i = 0; i < 13; i++ ) {
		vector_key.push_back(bike_key(key + std::to_string(i), std::rand()));
		vector_value.push_back(bike_value(value + std::to_string(i), std::rand() % 2));

		bike_map.insert({vector_key[i], vector_value[i]});
	}
	// Проверка правильного постороения(правилность сортировки по ключу) структуры std::map
	std::cout << "{" << '\n';
	for ( const auto element : bike_map ) {
		std::cout << element.first << " --- " << element.second << '\n';
	}
	std::cout << "};" << '\n';

// ---------------------------------------------------------------------------------------------
// ------------------------------------------task(2.1.2)----------------------------------------
// ---------------------------------------------------------------------------------------------

	// Поиск по ключу
	auto find_value_key1 = find_value(bike_map, vector_key[1]);
	auto find_value_key10 = find_value(bike_map, vector_key[10]);
	if ( find_value_key1 != bike_map.end() ) 		{
		std::cout << "RESULT VALUE: " << find_value_key1->second << " --> TRUE VALUE: " << vector_value[1] << '\n';
	}
	if ( find_value_key10 != bike_map.end() ) {
		std::cout << "RESULT VALUE: " << find_value_key10->second << " --> TRUE VALUE: " << vector_value[10] << '\n';
	}
	

	// Поиск по значению
	auto find_key_value1 = find_key(bike_map, vector_value[1]);
	auto find_key_value11 = find_key(bike_map, vector_value[11]);
	if ( find_key_value1 != bike_map.end() ) {
		std::cout << "RESULT KEY: " << find_key_value1->first << " --> TRUE KEY: " << vector_key[1] << '\n';
	}
	if ( find_key_value11 != bike_map.end() ) {
		std::cout << "RESULT KEY: " << find_key_value11->first << " --> TRUE KEY: " << vector_key[11] << '\n';
	}

	
	

	//std::cout << k1 << k2;

	// std::cout<< map[k1];

	//std::vector<std::string> vector{"gal;d", "g;fgs", "ert", "etewrt", "key", "adgs", "gterw"};
	//std::cout << foo(vector);

// ---------------------------------------------------------------------------------------------
// ------------------------------------------task(2.1.3)----------------------------------------
// ---------------------------------------------------------------------------------------------

	// Вывод через итераторы
	print_iter(bike_map);

// ---------------------------------------------------------------------------------------------
// ------------------------------------------task(2.1.4)----------------------------------------
// ---------------------------------------------------------------------------------------------

	std::cout << '\n' << "----------------------------------" << '\n';

	//auto iter = bike_map.begin();
	std::map<ds::bike_key, ds::bike_value> map_result;
	//std::map<ds::bike_key, ds::bike_value> map_train;
	//map_train.insert({vector_key[0], vector_value[0]});
	//map_train.insert({vector_key[1], vector_value[1]});


	map_result = filter(bike_map, func_task4, 0);
	print_iter(map_result.begin(), map_result.end());

// ---------------------------------------------------------------------------------------------
// ------------------------------------------task(2.1.6)----------------------------------------
// ---------------------------------------------------------------------------------------------
	
	std::cout << '\n' << "----------------------------------" << '\n';

	std::set<ds::bike_value> set_result;

	set_result = filterSet(bike_map, func_task4, 0);
	print_iter_set(set_result.begin(), set_result.end());

	std::cout << '\n' << "----------------------------------" << '\n';

// ---------------------------------------------------------------------------------------------
// ------------------------------------------task(2.1.5)----------------------------------------
// ---------------------------------------------------------------------------------------------

	auto pair_new = std::make_pair(ds::bike_key("key_new", 999), ds::bike_value("value_new", 1));
	std::cout << pair_new.first << pair_new.second;
	
	auto iter_pair_inserted = insert<ds::bike_key, ds::bike_value>(bike_map, pair_new);
	std::cout << '\n' << (*(iter_pair_inserted.first)).first << (*(iter_pair_inserted.first)).second << '\n';
	
	print_iter(bike_map.begin(), bike_map.end());

	try
	{
		insert<ds::bike_key, ds::bike_value>(bike_map, pair_new);
	}
	catch (invalid_key exceptionKey) 
	{
		exceptionKey.what();

		// exception handling ...
	}
	catch(...) {}

	for (int i = 0; i < 5; i++) {
		std::cout << '\n';
	}
	
	







// ---------------------------------------------------------------------------------------------
// ------------------------------------------task(2.2.0)----------------------------------------
// ---------------------------------------------------------------------------------------------



	// Контейнер может содержать значения с одинаковыми ключами.
	// insert - вставка всегда происходит успешно 
	// erase - удаляет все входящие в  контейнер элементы с заданным ключем
	// find - возвращает первый встретившийся элемент с заданным ключем
	std::multimap<int, int> m = {{1,10},{2,2},{3,3},{4,4},{5,5},{4,4},{3,3},{2,2},{1,100}};
 	for(auto& p: m) std::cout << p.first << ' ' << p.second << '\n';
	std::cout << (*( m.find(1) )).second;


	std::multimap<bike_key, bike_value> bike_multimap;

	for ( int i = 0; i < 13; i++ ) {
		vector_key.push_back(bike_key(key + std::to_string(i), std::rand()));
		vector_value.push_back(bike_value(value + std::to_string(i), std::rand() % 2));

		bike_multimap.insert({vector_key[i], vector_value[i]});
	}

	bike_multimap.insert({vector_key[2], vector_value[2]});
	bike_multimap.insert({vector_key[2], vector_value[2]});

	auto vector_result = find_value_multi_variative(bike_multimap, vector_key[2]);
	std::cout << '\n' << "{find_value_multi_variative:";
	for (auto element : vector_result) {
		std::cout << '\n' << element->first << " --- " << element->second; 
		  
	}
	std::cout << '\n' << "}" << '\n' << '\n';
	// Проверка правильного постороения(правилность сортировки по ключу) структуры std::map
	print_iter(bike_multimap.begin(), bike_multimap.end() );

// ---------------------------------------------------------------------------------------------
// ------------------------------------------task(2.2.2)----------------------------------------
// ---------------------------------------------------------------------------------------------

	// Поиск по ключу
	auto find_value_key2 = find_value_multi(bike_multimap, vector_key[2]);
	auto find_value_key11 = find_value_multi(bike_multimap, vector_key[11]);
	if ( find_value_key2 != bike_map.end() ) 		{
		std::cout << "RESULT VALUE: " << find_value_key2->second << " --> TRUE VALUE: " << vector_value[2] << '\n';
	}
	if ( find_value_key11 != bike_map.end() ) {
		std::cout << "RESULT VALUE: " << find_value_key11->second << " --> TRUE VALUE: " << vector_value[11] << '\n';
	}
	

	// Поиск по значению
	auto find_key_value2 = find_key_multi(bike_multimap, vector_value[2]);
	auto find_key_value12 = find_key_multi(bike_multimap, vector_value[12]);
	if ( find_key_value2 != bike_map.end() ) {
		std::cout << "RESULT KEY: " << find_key_value2->first << " --> TRUE KEY: " << vector_key[2] << '\n';
	}
	if ( find_key_value12 != bike_map.end() ) {
		std::cout << "RESULT KEY: " << find_key_value12->first << " --> TRUE KEY: " << vector_key[12] << '\n';
	}

// ---------------------------------------------------------------------------------------------
// ------------------------------------------task(2.2.3)----------------------------------------
// ---------------------------------------------------------------------------------------------

	// Вывод через итераторы
	print_iter(bike_multimap.begin(), bike_multimap.end() );

// ---------------------------------------------------------------------------------------------
// ------------------------------------------task(2.1.4)----------------------------------------
// ---------------------------------------------------------------------------------------------

	std::cout << '\n' << "----------------------------------" << '\n';

	//auto iter = bike_map.begin();
	std::multimap<ds::bike_key, ds::bike_value> map_result_multi;
	//std::map<ds::bike_key, ds::bike_value> map_train;
	//map_train.insert({vector_key[0], vector_value[0]});
	//map_train.insert({vector_key[1], vector_value[1]});


	map_result_multi = filter_multi(bike_multimap, func_task4, 0);
	print_iter(map_result_multi.begin(), map_result_multi.end());

// ---------------------------------------------------------------------------------------------
// ------------------------------------------task(2.2.6)----------------------------------------
// ---------------------------------------------------------------------------------------------
	
	std::cout << '\n' << "----------------------------------" << '\n';

	std::multiset<ds::bike_value> multi_set_result;

	multi_set_result = filterSet_multi(bike_multimap, func_task4, 0);
	print_iter_set(multi_set_result.begin(), multi_set_result.end());

	std::cout << '\n' << "----------------------------------" << '\n';


	return 0;
}