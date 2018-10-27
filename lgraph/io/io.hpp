#pragma once

/* This file is used so that all files
 * related with i/o can be included in
 * a single file.
 *
 * Not recommended, though, as it will
 * very likely increase the compilation
 * time (many files are templates).
 *
 * Include only those that are actually
 * necessary.
 */

// lgraph includes
#include <lgraph/io/edge_list.hpp>
#include <lgraph/io/gsd6.hpp>
