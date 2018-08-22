#include "csn_utils.hpp"

namespace csn_utils {

	int strcmp(const string& s1, const string& s2) {
		return strcmp(s1.c_str(), s2.c_str());
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

	char parse_ulli(const char *str, unsigned long long int *v) {
		char *err;
		long long int s = strtoll(str, &err, 10);

		/*
		according to the manual:

		If  no conversion is performed, zero is returned and the value of
		nptr is stored in the location referenced by endptr.
		*/
		if (err == str) {
			cerr << "Error: no conversion of '" << string(str) << "' into unsigned long long int be performed" << endl;
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

	char parse_size_t(const char *str, size_t *v) {
		char *err;
		long long int s = strtoll(str, &err, 10);

		/*
		according to the manual:

		If  no conversion is performed, zero is returned and the value of
		nptr is stored in the location referenced by endptr.
		*/
		if (err == str) {
			cerr << "Error: no conversion of '" << string(str) << "' into unsigned long long int be performed" << endl;
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

		*v = static_cast<size_t>(s);
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
