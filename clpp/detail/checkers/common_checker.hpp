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

#ifndef CLPP_DETAIL_COMMON_CHECKER_HPP
#define CLPP_DETAIL_COMMON_CHECKER_HPP

#include "../types.hpp"

/// \namespace clpp
/// \brief Main namespace of library.
namespace clpp {

/// \namespace clpp::detail
/// \brief Details of realization.
namespace detail {

/// \struct common_checker
/// \brief Superclass for all checkers.
///
/// Need for polymorphic use of checkers. Parameterized for "file independence".
template
<
    typename Parameters
    , typename Extractor
    , typename Separator
>
struct common_checker {
    common_checker( const Parameters&  _registered_parameters
                    , const Extractor& _extractor
                    , const Separator& _name_value_separator ) :
            registered_parameters( _registered_parameters )
            , extractor( _extractor )
            , name_value_separator( _name_value_separator ) {}
public:
    const Parameters& registered_parameters;
    const Extractor&  extractor;
    const Separator&  name_value_separator;
public:
    virtual void check( const str_storage& inputed_parameters ) const = 0;
};

} // namespace detail
} // namespace clpp

#endif // CLPP_DETAIL_COMMON_CHECKER_HPP
