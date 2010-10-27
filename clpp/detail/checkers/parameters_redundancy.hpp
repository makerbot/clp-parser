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

#ifndef CLPP_DETAIL_PARAMETERS_REDUNDANCY_HPP
#define CLPP_DETAIL_PARAMETERS_REDUNDANCY_HPP

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

/// \class parameters_redundancy_checker
/// \brief Parameter's redundancy checker.
///
/// Check redundancy of inputed parameters. 
/// Assumed that each of the parameters can be inputed only once,
/// so quantity of inputed parameters cannot be greater than 
/// quantity of registered parameters.
class parameters_redundancy_checker : public checker {
public:
    parameters_redundancy_checker( const parameters&                    registered_parameters
                                   , const parameter_parts_extractor&   extractor
                                   , const std::string&                 name_value_separator ) :
            checker( registered_parameters, extractor, name_value_separator ) {}
public:
    void check( const str_storage& inputed_parameters ) const {
        const size_t inputed_parameters_quantity = inputed_parameters.size();
        const size_t registered_parameters_quantity = registered_parameters.size();
        if ( inputed_parameters_quantity > registered_parameters_quantity ) {
            notify_about_parameters_redundancy( inputed_parameters_quantity, registered_parameters_quantity );
        } else {} 
    }
private:
    void notify_about_parameters_redundancy( size_t   inputed_parameters_quantity
                                             , size_t registered_parameters_quantity ) const {
        o_stream what_happened;
        what_happened << lib_prefix() 
                      << "You inputs " << inputed_parameters_quantity << " parameters, "
                      << "but only " << registered_parameters_quantity << " registered!";
        throw std::runtime_error( what_happened.str() );
    }
};

} // namespace detail
} // namespace clpp

#endif // CLPP_DETAIL_PARAMETERS_REDUNDANCY_HPP
