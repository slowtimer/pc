/*
 * - main.cpp
 * Copyright (C) 2025-2026  Michal Sobotka
 * Licensed under GPLv3 - see LICENSE or github:
 * https://github.com/slowtimer/pc
 */

#include "stack.hpp"
#include "number.hpp"
#include "math_operators.hpp"
#include "help.hpp"
#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>

using namespace std;

mem::stack<number> stack;
math_operators oper = math_operators(&stack);

bool interactive = false;
bool wrote_output = false;
bool error = false;
//int comment_depth = 0;

void precision(int p) {
	cerr << std::setprecision(p) << std::fixed;
	cout << std::setprecision(p) << std::fixed;
}

void safeprint(number n, ostream* oss) {
	if (n.is_double()) // for precision controll
		*oss << n.as_double();
	else
		*oss << std::string(n);
}

void step(std::string s) {
	// ignore comments
	/*
	if (s.size() > 0 && s[0] == '(') {
		comment_depth++;
		return;
	}

	if (s.size() > 0 && s[s.size()-1] == ')' && comment_depth) {
		comment_depth--;
		return;
	}

	if (comment_depth)
		return;
*/
	// input number
	number n;
	if(n.parse(s)) {
		stack.push(n);
		return;
	}

	// math operations + - * / etc.
	if (oper.operate(s))
		return;

	/* pattern matching -- keywords */
	if (s == ".") {
		wrote_output = true;
		if (stack.size()) {
			safeprint(stack.pop(), &cout);
			cout << endl;
		}
		else
			cerr << "<empty>\n";
		return;
	}

	if (s == "drop") {
		if (stack.size())
			stack.pop();
		else
			cerr << "<empty>\n";
		return;
	}

	if (s == "2drop") {
		if (stack.size())
			stack.pop();
		if (stack.size())
			stack.pop();
		else
			cerr << "<empty>\n";
		return;
	}

	if (s == "dup") {
		if (stack.size())
			stack.push(stack[0]);
		else
			cerr << "<empty>\n";
		return;
	}

	if (s == "swap") {
		if (stack.size() >= 2) {
			number n = stack[1];
			stack[1] = stack[0];
			stack[0] = n;
		}
		else
			cerr << "<missing_values>\n";
		return;
	}

	if (s == "rot") {
		if (stack.size() >= 3) {
			number n = stack[2];
			stack[2] = stack[1];
			stack[1] = stack[0];
			stack[0] = n;
		}
		else
			cerr << "<missing_values>\n";
		return;
	}

	if (s == ".S" || s == ".s") {
		wrote_output = true;
		cerr << "<" << stack.size() << ">";
		for (int i = stack.size() - 1; i >= 0; i--) {
			number iter = stack[i];
			cerr << ' ';
			safeprint(iter, &cerr);
		}
		cerr << '\n';
		return;
	}

	if (s == "cl" || s == "clear") {
		cerr << "\x1b[2J\x1b[H";
		return;
	}

	/* pattern matching -- casting */
	if (stack.size()) {
		number n = stack[0];
		if (s == "round") {
			number fixer = number(0.5);
			n = (n + fixer);
			n.to_int();
			stack[0] = n;
			return;
		}
		else if (s == "i") { n.to_int(); stack[0] = n; return; }
		else if (s == "o") { n.to_over(); stack[0] = n; return; }
		else if (s == "d") { n.to_double(); stack[0] = n; return; }
	}

	if (s == "help" || (!interactive && ( s == "-h" || s == "--help"))) {
		/*	print to:
			stdout if invoked from shell ( | less)
			print to stderr if invoked from stdin (clean stdout)
		*/
		ostream* oss = &cout;
		if (interactive)
			oss = &cerr;
		*oss << help_text_ptr;
		return;
	}

	// set double precision
	if (s.size() > 1 || s[0] == 'p') {
		try {
			int prec = stoi(&s[1]);
			precision(prec);
			return;
		}
		catch (...) {}
	}

	cerr << "<invalid: '" << s << "'>\n";
	error = true;
}

void tokenize(string keys) {
	stringstream ss(keys);
	string key;
	while (ss >> key) {
		if (key != "")
			step(key);
	}
}

int main(int argc, const char* args[]) {
	precision(4);
	if (argc > 1) {
		for (int i = 1; i < argc; i++) {
			tokenize(args[i]);
		}
		// print stack before exit
		if (!wrote_output)
			step(".S");

		return error;
	}

	interactive = true;
	cerr << help_license_ptr << flush;
	while (!cin.fail() || !cin.eof()) {
		string s;
		getline(cin, s);
		tokenize(s);
	}
	return 0;
}
