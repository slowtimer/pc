/*
 * - over.hpp
 * Copyright (C) 2025-2026  Michal Sobotka
 * Licensed under GPLv3 - see LICENSE or github:
 * https://github.com/slowtimer/pc
 */

#pragma once

class over {
private:
	int _up;
	int _down;

	// nejmensi spol nasobek
	int euklid(int a, int b) {
		if (b)
			return euklid(b, a % b);
		return a;
	}

	void shorten() {
		if (!_down)
			throw std::invalid_argument("over: cannot use x/0 (zero division)");

		// 0/x to 0/1
		if (!_up) {
			_down = 1;
			return;
		}

		// 5/10 to 1/2 (shorting)
		int c = euklid(_up, _down);
		_down /= c;
		_up /= c;

		// -x/-y to x/y OR
		// x/-y to -x/y
		if (_down < 0) {
			_up *= -1;
			_down *= -1;
		}
	}

public:
	over() {
		_up = 0;
		_down = 1;
	}

	over(int up, int down) {
		_up = up;
		_down = down;
		shorten();
	}

	static over parse(std::string str) {
		int slash_offset = 0;
		for (int i = 0; i < str.size(); i++) {
			char c = str[i];
			if (c == '/') {
				if (slash_offset) {
					throw std::invalid_argument("over: parse() invalid input - too many '/'");
				}
				slash_offset = i;
				continue;
			}

			if (c == '-')
				continue;

			if (c < '0' || c > '9')
				throw std::invalid_argument("over: parse() invalid input - not a number (-0-9/)");
		}

		int u = std::stoi(str);
		int d = std::stoi(&str[slash_offset+1]);
		return over(u, d);
	}

	int upper() { return _up; }
	int lower() { return _down; }

	over operator+(over n) { return over(this->upper() * n.lower() + this->lower() * n.upper(), this->lower() * n.lower()); }
	over operator-(over n) { return over(this->upper() * n.lower() - this->lower() * n.upper(), this->lower() * n.lower()); }
	over operator*(over n) { return over(this->upper() * n.upper(), this->lower() * n.lower()); }
	over operator/(over n) { return over(this->upper() * n.lower(), this->lower() * n.upper()); }
//	over operator%(over n) { return over(); }
	operator std::string() {
		const int u = this->upper();
		const int l = this->lower();
		return std::to_string(u) + "/" + std::to_string(l);
	}
};
