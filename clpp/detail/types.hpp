// Command line parameters parser.
//
// Copyright (C) Denis Shevchenko, 2010.
// shev.denis @ gmail.com
//
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 2.1 of the License, or (at your option) any later version.
//
// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
// Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public
// License along with this library; if not, see http://www.gnu.org/licenses/lgpl.html
//
// http://clp-parser.sourceforge.net/

#ifndef CLPP_DETAIL_TYPES_HPP
#define CLPP_DETAIL_TYPES_HPP

#include <boost/any.hpp>

#include <vector>
#include <sstream>

/// \namespace clpp
/// \brief Main namespace of library.
namespace clpp {

/// \namespace clpp::detail
/// \brief Details of realization.
namespace detail {

typedef std::vector< std::string >  str_storage;
typedef str_storage::iterator       str_it;
typedef str_storage::const_iterator str_const_it;

typedef std::ostringstream          o_stream;

typedef boost::any                  any;

} // namespace detail
} // namespace clpp

#endif // CLPP_DETAIL_TYPES_HPP
