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

#ifndef CLPP_DETAIL_PARAMETERS_EXISTENCE_HPP
#define CLPP_DETAIL_PARAMETERS_EXISTENCE_HPP

#include "common_checker.hpp"
#include "../parameter.hpp"
#include "../parameter_parts_extractor.hpp"

/// \namespace clpp
/// \brief Main namespace of library.
namespace clpp {

/// \namespace clpp::detail
/// \brief Details of realization.
namespace detail {

typedef common_checker< parameters, parameter_parts_extractor, std::string > checker;

/// \class parameters_existence_checker
/// \brief Parameter's existence checker.
///
/// Checks existence of registered parameters.
class parameters_existence_checker : public checker {
public:
    parameters_existence_checker( const parameters&                     registered_parameters
                                  , const parameter_parts_extractor&    extractor
                                  , const std::string&                  name_value_separator ) :
            checker( registered_parameters, extractor, name_value_separator ) {}
public:
    void check( const str_storage& inputed_parameters ) const {
        if ( registered_parameters.empty() && !inputed_parameters.empty() ) {
            notify_about_parameters_absence();
        } else {} 
    }
private:
    void notify_about_parameters_absence() const {
        const std::string what_happened = lib_prefix() + "You inputs some parameter(s), but no one registered!";
        throw std::runtime_error( what_happened );
    }
};

} // namespace detail
} // namespace clpp

#endif // CLPP_DETAIL_PARAMETERS_EXISTENCE_HPP
