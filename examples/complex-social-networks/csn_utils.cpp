/*********************************************************************
 * lgraph
 * Copyright (C) 2018-2019 Lluís Alemany Puig
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * Contact: Lluís Alemany Puig (lluis.alemany.puig@gmail.com)
 *
 ********************************************************************/

#include "csn_utils.hpp"

namespace csn_utils {

	int estrcmp(const string& s1, const char *s2) {
		return strcmp(s1.c_str(), s2);
	}

	char parse_uli(const char *str, unsigned long int *v) {
		char *err;
		long int s = strtol(str, &err, 10);

		/*
		according to the manual:

		If  no conversion is performed, zero is returned and the value of
		nptr is stored in the location referenced by endptr.
		*/
		if (err == str) {
			cerr << "Error: no conversion of '" << string(str) << "' into unsigned long int be performed" << endl;
			return 1;
		}

		/*
		according to the manual:

		If the correct value would cause overflow, plus or minus LONG_MAX,
		LONG_MIN is returned (according  to  the  sign  of the value),
		and ERANGE is stored in errno.

		If the correct value would cause underflow, zero is returned and
		ERANGE is stored in errno.
		*/

		if (errno == ERANGE && s == LONG_MAX) {
			cerr << "Error: value '" << string(str) << "' causes overflow" << endl;
			return 1;
		}
		if (errno == ERANGE && s == LONG_MIN) {
			cerr << "Error: value '" << string(str) << "' causes underflow" << endl;
			return 1;
		}

		if (s < 0) {
			cerr << "Error: value " << string(str) << " is negative - and were" << endl;
			cerr << "    trying to parse an unsigned integer" << endl;
			return 1;
		}

		*v = static_cast<unsigned long int>(s);
		return 0;
	}

	char parse_ulli(const char *str, size_t *v) {
		char *err;
		long long int s = strtoll(str, &err, 10);

		/*
		according to the manual:

		If  no conversion is performed, zero is returned and the value of
		nptr is stored in the location referenced by endptr.
		*/
		if (err == str) {
			cerr << "Error: no conversion of '" << string(str) << "' into unsigned long int be performed" << endl;
			return 1;
		}

		/*
		according to the manual:

		If the correct value would cause overflow, plus or minus LONG_MAX,
		LONG_MIN is returned (according  to  the  sign  of the value),
		and ERANGE is stored in errno.

		If the correct value would cause underflow, zero is returned and
		ERANGE is stored in errno.
		*/

		if (errno == ERANGE && s == LONG_MAX) {
			cerr << "Error: value '" << string(str) << "' causes overflow" << endl;
			return 1;
		}
		if (errno == ERANGE && s == LONG_MIN) {
			cerr << "Error: value '" << string(str) << "' causes underflow" << endl;
			return 1;
		}

		if (s < 0) {
			cerr << "Error: value " << string(str) << " is negative - and were" << endl;
			cerr << "    trying to parse an unsigned integer" << endl;
			return 1;
		}

		*v = static_cast<unsigned long long int>(s);
		return 0;
	}

	char parse_float(const char *str, float *s) {
		char *err;
		*s = strtof(str, &err);

		/*
		according to the manual:

		If  no conversion is performed, zero is returned and the value of
		nptr is stored in the location referenced by endptr.
		*/
		if (err == str) {
			cerr << "Error: no conversion of '" << string(str) << "' into double be performed" << endl;
			return 1;
		}

		/*
		according to the manual:

		If the correct value would cause overflow, plus or minus HUGE_VAL
		(HUGE_VALF, HUGE_VALL) is returned (according  to  the  sign  of
		the value), and ERANGE is stored in errno.

		If the correct value would cause underflow, zero is returned and
		ERANGE is stored in errno.
		*/
		if (errno == ERANGE && *s == HUGE_VALF) {
			cerr << "Error: value '" << string(str) << "' causes overflow" << endl;
			return 1;
		}
		if (errno == ERANGE && *s == 0.0f) {
			cerr << "Error: value '" << string(str) << "' causes underflow" << endl;
			return 1;
		}

		return 0;
	}

	char parse_double(const char *str, double *s) {
		char *err;
		*s = strtod(str, &err);

		/*
		according to the manual:

		If  no conversion is performed, zero is returned and the value of
		nptr is stored in the location referenced by endptr.
		*/
		if (err == str) {
			cerr << "Error: no conversion of '" << string(str) << "' into double be performed" << endl;
			return 1;
		}

		/*
		according to the manual:

		If the correct value would cause overflow, plus or minus HUGE_VAL
		(HUGE_VALF, HUGE_VALL) is returned (according  to  the  sign  of
		the value), and ERANGE is stored in errno.

		If the correct value would cause underflow, zero is returned and
		ERANGE is stored in errno.
		*/
		if (errno == ERANGE && *s == HUGE_VAL) {
			cerr << "Error: value '" << string(str) << "' causes overflow" << endl;
			return 1;
		}
		if (errno == ERANGE && *s == 0.0) {
			cerr << "Error: value '" << string(str) << "' causes underflow" << endl;
			return 1;
		}

		return 0;
	}

} // -- namespace csn_utils
