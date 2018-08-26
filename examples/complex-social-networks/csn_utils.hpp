#pragma once

// C includes
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include <errno.h>
#include <stdio.h>
#include <math.h>

// C++ includes
#include <iostream>
#include <string>
using namespace std;

namespace csn_utils {

	// Compares two strings
	int estrcmp(const string& s1, const char *s2);

	char parse_uli(const char *str, unsigned long int *v);
	char parse_float(const char *str, float *s);
	char parse_double(const char *str, double *s);

}
