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
#include <lgraph/io/edge_list_ux.hpp>
#include <lgraph/io/edge_list_wx.hpp>
#include <lgraph/io/gsd6.hpp>
