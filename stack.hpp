/*
 * - stack.hpp
 * Copyright (C) 2025-2026  Michal Sobotka
 * Licensed under GPLv3 - see LICENSE or github:
 * https://github.com/slowtimer/pc
 */

#pragma once

#include <stdexcept>
#include <iterator>

namespace mem {

template <typename T> class stack {
private:
	int _index = -1;
	int _size = 16;
	T* _data = NULL;

	void expand() {
		_size *= 2;
		T* data_new = new T[_size];
		for (int i = 0; i < _index; i++) {
			data_new[i] = _data[i];
		}
		delete[] _data;
		_data = data_new;
	}

	bool shold_expand() {
		return _index + 1 == _size;
	}

public:
	stack() {
		_data = new T[_size];
	}

	~stack() {
		delete[] _data;
	}

	void push(T item) {
		if (shold_expand())
			expand();
		_data[++_index] = item;
	}

	T pop() {
		if (size()) {
			return _data[_index--];
		}
		throw std::out_of_range("stack: pop() empty stack");
	}

	int size() {
		return _index + 1;
	}

	T& at(int index) {
		int pos = _index - index;
		if ((T*)&pos >= _data)
			return _data[pos];
		throw std::out_of_range("stack: at() out of range");
	}

	T& operator[](int index) { return at(index); }
	const T& operator[](int index) const { return at(index); }
};
}; // namespace end
