/*
 * - number.hpp
 * Copyright (C) 2025-2026  Michal Sobotka
 * Licensed under GPLv3 - see LICENSE or github:
 * https://github.com/slowtimer/pc
 */

#pragma once

#include "over.hpp"
#include <string>
#include <cmath>

class number {
protected:
	enum type_n {
		INT_N,
		OVER_N,
		DOUBLE_N
	} _type;
	long int _int;
	over _over;
	double _double;

	void convert(type_n t) {
		if (_type == t)
			return;

		number n;
		switch (t) {
			case INT_N:
				if (_type == OVER_N) {
					n = number(_over.upper() / _over.lower());
				}
				else { // DOUBLE_N
					n = number((long int)_double);
				}
				break;

			case OVER_N:
				if (_type == INT_N) {
					n = number(_int, 1);
				}
				else { // DOUBLE_N
					const int precision = 10000;
					n = number((int)(_double * precision), precision);
				}
				break;

			case DOUBLE_N:
				if (_type == INT_N) {
					n = number((double)_int);
				}
				else { // OVER_N
					n = number((double)_over.upper() / _over.lower());
				}
				break;
		}
		*this = n;
	}

	void to_same_type (number* n) { // args: this, n
		type_n t = _type;
		if (n->_type > t)
			t = n->_type;
		convert(t);
		n->convert(t);
	}

public:
	number() {
		_type = INT_N;
		_int = 0;
	}

	number(long int n) {
		_type = INT_N;
		_int = n;
	}

	number(int n) {
		_type = INT_N;
		_int = n;
	}

	number(int a, int b) {
		_type = OVER_N;
		_over = over(a, b);
	}

	number(over n) {
		_type = OVER_N;
		_over = n;
	}

	number(double n) {
		_type = DOUBLE_N;
		_double = n;
	}

	long int as_int() {
		number n = *this;
		n.convert(INT_N);
		return n._int;
	}

	over as_over() {
		number n = *this;
		n.convert(OVER_N);
		return n._over;
	}

	double as_double() {
		number n = *this;
		n.convert(DOUBLE_N);
		return n._double;
	}

	void to_int() { convert(INT_N); }
	void to_over() { convert(OVER_N); }
	void to_double() { convert(DOUBLE_N); }

	bool is_int() { return _type == INT_N; }
	bool is_over() { return _type == OVER_N; }
	bool is_double() { return _type == DOUBLE_N; }

	// true on success
	bool parse(std::string str) {
		if (!str.size())
			return false;

		if (str == "pi") {
			*this = number(M_PI);
			return true;
		}
		if (str == "c") {
			*this = number(299792458); // speed of light [m*s^-1]
			return true;
		}
		if (str == "inf") {
			*this = number(HUGE_VAL);
			return true;
		}
		if (str == "-inf") {
			*this = number(-HUGE_VAL);
			return true;
		}

		// parse value
		try {
			// 1/5
			if (str.find('/') <= str.size())
				*this = number(over::parse(str));
			// 20% => 0.2
			else if (str.size() > 1 && str[str.size() - 1] == '%')
				*this = number(std::stod(str) / 100);
			// 0.2
			else if (str.find('.') <= str.size())
				*this = number(std::stod(str));
			// 5
			else
				*this = number(std::stoi(str));
			return true;
		}
		catch (...) {}
		return false;
	}

	operator std::string() {
		switch (_type) {
			case INT_N:
				return std::to_string(_int);

			case OVER_N:
				return std::string(_over);

			case DOUBLE_N:
				return std::to_string(_double);

			default:
				return "<none>";
		}
	}

	#define OPCODE(opcode) switch (_type) { \
		case INT_N: return _int opcode n._int; \
		case OVER_N: return _over opcode n._over; \
		case DOUBLE_N: return _double opcode n._double; \
		default: return number(0); }

	number operator+(number n) { to_same_type(&n); OPCODE(+); }
	number operator-(number n) { to_same_type(&n); OPCODE(-); }
	number operator*(number n) { to_same_type(&n); OPCODE(*); }
	number operator/(number n) { to_same_type(&n); OPCODE(/); }
	#undef OPCODE
};
