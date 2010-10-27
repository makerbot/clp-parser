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

#ifndef CLPP_DETAIL_MISC_HPP
#define CLPP_DETAIL_MISC_HPP

#include <boost/lexical_cast.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/ptr_container/ptr_vector.hpp>

/// \namespace clpp
/// \brief Main namespace of library.
namespace clpp {

inline std::string lib_prefix() { return "[CLPP] "; }

/// \enum value_semantic 
/// \brief Value semantic types (for check).
enum value_semantic {
    no_semantic			/*!< Default value. */
	, path				/*!< Path semantic check. */
	, ipv4				/*!< IPv4 semantic check. */
    , ipv6              /*!< IPv6 semantic check. */
    , ip                /*!< IP semantic check. */
};

/// \namespace clpp::detail
/// \brief Details of realization.
namespace detail {

template< typename T >
inline std::string to_str( const T& t ) {
    std::string as_string; 
    try {
        as_string = boost::lexical_cast< std::string >( t );
    } catch ( const std::exception& /* exc */ ) {
        std::string what_happened = lib_prefix() + "Value cannot be present as std::string!";
        throw std::invalid_argument( what_happened );
    }
    return as_string;
}

template
<
    typename STLContainer
    , typename Element
>
inline void delete_element( STLContainer& cont, const Element& element ) {
    cont.erase( std::remove( cont.begin(), cont.end(), element )
				, cont.end() );
}

} // namespace detail
} // namespace clpp

#endif // CLPP_DETAIL_MISC_HPP
