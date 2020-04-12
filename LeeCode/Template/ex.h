/*******************************************************************
*  Copyright(c) 2000-2021 Company Name
*  All rights reserved.
*
*  @file
*  @brief
*  @mail   tappanmorris@outlook.com
*  @date   2020-04-12
*  @author morris
*  @note
*
******************************************************************/
#ifndef EX_H
#define EX_H
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <bitset>

#include "ex.h"
#include "screen.h"
#include "vec.h"
// 16.4
template<class InputIt, class T>
InputIt Find(InputIt begin, InputIt end, const T& value){
	for (; begin != end; begin++)
	{
		if (*begin == value) {
			return begin;
		}
	}
	return end;
}

// 16.5 
template<class T, unsigned N>
void print_array(const T (&arr)[N])
{
	for (const auto& elem : arr) {
		std::cout << elem;
	}
	std::cout << std::endl;
}

// 16.7
template<class T, unsigned N>
constexpr unsigned sizeof_array(const T(&arr)[N])
{
	return N;
}

// 16.8
// C++程序员喜欢使用 != 而不喜欢<。解释这个习惯的原因。
// 主要是为了让代码的可用性更高。在 STL 中，所有的迭代器都支持!=操作，但是只有随机迭代器支持<操作。



void screen()
{
	Screen<10, 5> a('x');
	a.set(2, 2, 'o');

	std::cout << a << std::endl;

}

void vec16()
{
	Vec<std::string> vec;
	vec.reserve(6);
	std::cout << "capacity(reserve to 6): " << vec.capacity() << std::endl;

	vec.reserve(4);
	std::cout << "capacity(reserve to 4): " << vec.capacity() << std::endl;

	vec.push_back("hello");
	vec.push_back("world");

	vec.resize(4);

	for (auto i = vec.begin(); i != vec.end(); ++i)
		std::cout << *i << std::endl;
	std::cout << "-EOF-" << std::endl;

	vec.resize(1);

	for (auto i = vec.begin(); i != vec.end(); ++i)
		std::cout << *i << std::endl;
	std::cout << "-EOF-" << std::endl;

	Vec<std::string> vec_list{ "hello", "world", "pezy" };

	for (auto i = vec_list.begin(); i != vec_list.end(); ++i)
		std::cout << *i << " ";
	std::cout << std::endl;

	// Test operator==

	const Vec<std::string> const_vec_list{ "hello", "world", "pezy" };
	if (vec_list == const_vec_list)
		for (const auto& str : const_vec_list) std::cout << str << " ";
	std::cout << std::endl;

	// Test operator<
	const Vec<std::string> const_vec_list_small{ "hello", "pezy", "ok" };
	std::cout << (const_vec_list_small < const_vec_list) << std::endl;

	// Test []
	std::cout << const_vec_list_small[1] << std::endl;
}

// 16.19
template<class Container>
std::ostream& print(const Container& c, std::ostream& os = std::cout)
{
	using size_type = typename Container::size_type;
	for (size_type i = 0; i != c.size(); ++i) {
		os << c.at(i) << " ";
	}
	os << std::endl;
	return os;
}

void print19()
{
	std::vector<int> vec{ 2,4,6,8, 7, 5, 3, 1 };
	print(vec);
}


// 16.20
template<class InputIt>
std::ostream& print(InputIt& begin, InputIt& end, std::ostream& os=std::cout)
{
	for (; begin != end; ++begin) {
		os << *begin << " ";
	}
	os << std::endl;
return os;
}

void pirnt20()
{
	std::vector<int> vec{ 2,4,6,8, 7, 5, 3, 1 };
	print(vec.begin(), vec.end());

}

class DebugDelete {
public:
	DebugDelete(std::ostream& os = std::cerr) : os_(os) {}

	template<typename T> void operator()(T* p) const {
		os_ << "deleting unique_ptr by " << __FUNCTION__ << "\n";
		delete p;
	}

private:
	std::ostream& os_;
};

void print21()
{
	double* p = new double(8.0);
	DebugDelete d;
	d(p);
}


// 51, 52
template<class T, class ...Args>
void foo(T t, Args ... args)
{
	std::cout << sizeof...(Args) << std::endl;
	std::cout << sizeof...(args) << std::endl;
}

void print52()
{
	foo(1, 2);
	foo(1, 2, 3, 4, 5);
}

// 53, 54, 55

template<class T>
void printX(const T& t)
{
	std::cout << t << std::endl;
}

template<class T, class ... Args>
void printX(const T& t, Args ... args)
{
	std::cout << t << ",";
	printX(args...);
}

void print53()
{
	printX(1, 3.5, "string", std::bitset<16>(307));
}

//56, 57

template<typename T>
T debug_rep(const T& t)
{
	std::cout << "de:" << t << std::endl;;
	return t;
}


template<class ... Args>
void errorMsg(const Args ... args)
{
	printX(debug_rep(args)...);
}

void print56()
{
	errorMsg(1, 2, 3, 9.0f, "sss", "alan");
}

// 63 64

//! template
template<typename T>
std::size_t count(const std::vector<T>& vec, T value);

//! template specialization
template<>
std::size_t count(const std::vector<const char*> &vec, const char* value);

template<class T>
std::size_t count(const std::vector<T>& vec, const T& value)
{
	std::size_t count = 0;
	for (auto& item : vec)
		count += (item == value) ? 1 : 0;

	return count;
}

template<>
std::size_t count (const std::vector<const char*>& vec, const char* value)
{
	std::size_t count = 0;
	for (auto& item : vec)
		count += (strcmp(item, value) == 0) ? 1 : 0;

	return count;
}

void print63()
{
	std::vector<const char*> vcc = { "alan","alan","alan","alan","moophy" };
	std::cout << count(vcc, "alan");
}


#endif