/*
 * - math_operators.cpp
 * Copyright (C) 2025-2026  Michal Sobotka
 * Licensed under GPLv3 - see LICENSE or github:
 * https://github.com/slowtimer/pc
 */

#include "math_operators.hpp"
#include <cmath>

int math_operators::sum(int n) {
	number s = number(0);
	int count = 0;
	for (int i = 0; i < n; i++) {
		if (!can_count(1))
			break;
		s = s + _stack->pop();
		count++;
	}
	_stack->push(s);
	return count;
}

void math_operators::avrg(int n) {
	int count = sum(n);
	double s = _stack->pop().as_double();
	_stack->push(number(s / count));
}

bool math_operators::operate(std::string arg) {
	carg = arg;

	// --- limiter ---
	if (!can_count(1))
		return false;

	// analytics
	if (can("sum")) {
		sum();
		return true;
	}

	if (can("sumn")) {
		sum(_stack->pop().as_int());
		return true;
	}

	if (can("avrg")) {
		avrg();
		return true;
	}

	if (can("avrgn")) {
		avrg(_stack->pop().as_int());
		return true;
	}

	#define OPCODE(key, func) if (can(key)) { \
		double a = _stack->pop().as_double(); \
		_stack->push(number(func(a))); \
		return true; }

	OPCODE("sin", sin);
	OPCODE("cos", cos);
	OPCODE("tg", tan);
	OPCODE("cotg", 1 / tan);
	OPCODE("asin", asin);
	OPCODE("acos", acos);
	OPCODE("atg", atan);
	OPCODE("acotg", 1 / atan);
	#undef OPCODE

	if (can("sqrt")) {
		number a = _stack->pop();
		_stack->push(number(sqrt(a.as_double())));
		return true;
	}

	// --- limiter ---
	if (!can_count(2))
		return false;

	if (can("pow") || can("^") || can("**") || can("xx")) {
		number b = _stack->pop();
		number a = _stack->pop();
		if (a.is_int() && b.is_int())
			_stack->push(number((long int)pow(a.as_int(), b.as_int())));
		else
			_stack->push(number(pow(a.as_double(), b.as_double())));
		return true;
	}

	#define OPCODE(key, opcode) if (can(key)) { \
		number a = _stack->pop(); \
		number b = _stack->pop(); \
		_stack->push(b opcode a); \
		return true; }
	OPCODE("+", +);
	OPCODE("-", -);
	OPCODE("*", *);
	OPCODE("x", *);
	#undef OPCODE

	if (can("/")) {
		number a = _stack->pop();
		number b = _stack->pop();
		_stack->push(b / a);
		return true;
	}

	if (can("%")) {
		long int a = _stack->pop().as_int();
		long int b = _stack->pop().as_int();
		_stack->push(number(b % a));
		return true;
	}

	return false;
}
