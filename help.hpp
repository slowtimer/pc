/*
 * - help.hpp
 * Copyright (C) 2025-2026  Michal Sobotka
 * Licensed under GPLv3 - see LICENSE or github:
 * https://github.com/slowtimer/pc
 */

#pragma once

const char help_license_ptr[] =
"\n"
"pc  Copyright (C) 2025-2026  Michal Sobotka\n"
"This is free software, and you are welcome to redistribute it under\n"
"the terms and conditions of the GNU General Public License version 3.\n"
"For more information see LICENSE\n"
"\n"
"GitHub: https://github.com/slowtimer/pc\n"
"For basic usage type: help\n"
"\n"
;

const char help_text_ptr[] =
"pc - the reverse Polish notatation Calculator\n"
"data types:\n"
"\tint - eg: 10\n"
"\tover - eg: 3/5\n"
"\tdouble - eg: 0.1\t20% (0.2)\n"
"\n"
"casting (types):\n"
"\ti o d\n"
"\n"
"constants:\n"
"\tpi\n"
"\tc [m*s^-1]\n"
"\n"
"functions:\n"
"\t+ - * x / % - x is just * for shell scripts\n"
"\tsin cos tg cotg asin acos atg acotg sqrt\n"
"\tpow ^ ** xx - also takes exponent\n"
"\tsum avrg sumn avrgn - ...n pops number from stack to iter"
"\n"
"controll:\n"
"\t.s drop 2drop dup swap rot help\n"
"\t. - only one that writes to stdout\n"
"\tpN - sets double output format eg: p4 (x.yyyy)\n"
// "\t(hi this is a (comment) ) - brackets must match\n"
// "\t- '(' must be 1st; ')' must be last to count\n"
"\n"
"in scripts:\n"
"\tbash eg1: pc 5 5 x . > out.txt\n"
"\tbash eg2: pc \"5 5 * .\" > out.txt\n"
"\tout.txt => '25\\n'\n"
"\t- exit 1 only for shell scripts errors\n"
"\n"
"more info here: https://github.com/slowtimer/pc\n"
;
