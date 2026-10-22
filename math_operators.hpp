/*
 * - math_operators.hpp
 * Copyright (C) 2025-2026  Michal Sobotka
 * Licensed under GPLv3 - see LICENSE or github:
 * https://github.com/slowtimer/pc
 */

#pragma once

#include "stack.hpp"
#include "number.hpp"

class math_operators {
private:
	mem::stack<number>* _stack;
	std::string carg; // current arg

	bool can(std::string key) { return key == carg; } // true on success
	bool can_count(int req_on_stack) { return _stack->size() >= req_on_stack; } // true on success
	int sum() { return sum(_stack->size()); }
	int sum(int n);
	void avrg() { return avrg(_stack->size()); }
	void avrg(int n);

public:
	math_operators(mem::stack<number>* stc) { _stack = stc; }
	bool operate(std::string arg); // true on success
};
