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

#include "ex.h"
#include "screen.h"

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


#endif