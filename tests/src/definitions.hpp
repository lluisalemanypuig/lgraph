#pragma once

// C inlcudes
#include <stddef.h>

#define ERROR(file, func) \
	"Error [file " << file << ", function '" \
	<< func << "', line " << __LINE__ << "]:"

#define FV_PREC 3

enum class err_type : int8_t {
	// The test completed successfully
	no_error = 0,

	// wrong parameter value
	invalid_param,

	// The input file was not formatted correctly
	test_format_error,
	// The format for the input graph is not supported
	graph_format_error,
	// first field is not 'TYPE'
	first_no_TYPE,

	// Some error occurred while performing the test
	test_error,

	// wrong keyword: either it is not known or it is
	// incorrect given its parent test type
	wrong_keyword,
	// too many keywords
	too_many_keywords,

	// an error occurred when reading a file
	io_error,

	// test not implemented
	not_implemented
};
