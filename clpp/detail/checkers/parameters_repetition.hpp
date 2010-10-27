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

#ifndef CLPP_DETAIL_PARAMETERS_REPETITION_HPP
#define CLPP_DETAIL_PARAMETERS_REPETITION_HPP

#include "common_checker.hpp"
#include "../parameter.hpp"
#include "../parameter_parts_extractor.hpp"

#include <boost/assign.hpp>

/// \namespace clpp
/// \brief Main namespace of library.
namespace clpp {

/// \namespace clpp::detail
/// \brief Details of realization.
namespace detail {

typedef common_checker< parameters, parameter_parts_extractor, std::string > checker;

using namespace boost::assign;

/// \class parameters_repetition_checker 
/// \brief Parameters repetition checker.
///
/// Checks repetition of parameter(s).
/// Assumed that each of the parameters can be inputed only once.  
class parameters_repetition_checker : public checker {
public:
    parameters_repetition_checker( const parameters&                    registered_parameters
                                   , const parameter_parts_extractor&   extractor
                                   , const std::string&                 name_value_separator ) :
            checker( registered_parameters, extractor, name_value_separator ) {}
public:
    void check( const str_storage& inputed_parameters ) const {
        if ( inputed_parameters.size() < 2 ) {
            return;
        } else {} 
        
        str_storage sorted_parameters = get_sorted_inputed_parameters( inputed_parameters );
        str_storage unique_parameters = get_unique_parameters( sorted_parameters, inputed_parameters );

        if ( sorted_parameters != unique_parameters ) {
            notify_about_parameters_repetition();
        } else {}
    }
private:
    str_storage get_sorted_inputed_parameters( const str_storage& inputed_parameters ) const {
        str_storage parameters_for_sorting( inputed_parameters.begin(), inputed_parameters.end() );
        std::sort( parameters_for_sorting.begin(), parameters_for_sorting.end() );
        return parameters_for_sorting;
    }
    
    str_storage get_unique_parameters( const str_storage& sorted
                                       , const str_storage& inputed_parameters ) const {
        str_storage unique_parameters( inputed_parameters.size() );
        str_const_it it = std::unique_copy( sorted.begin(), sorted.end(), unique_parameters.begin() );
        unique_parameters.resize( it - unique_parameters.begin() );
        return unique_parameters;
    }

    void notify_about_parameters_repetition() const {
        const std::string what_happened = lib_prefix() + "Parameter(s) repetition detected!";
        throw std::runtime_error( what_happened );
    }
};

} // namespace detail
} // namespace clpp

#endif // CLPP_DETAIL_PARAMETERS_REPETITION_HPP
