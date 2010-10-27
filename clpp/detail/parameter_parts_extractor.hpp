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

#ifndef CLPP_DETAIL_PARAMETER_PARTS_EXTRACTOR_HPP
#define CLPP_DETAIL_PARAMETER_PARTS_EXTRACTOR_HPP

#include "types.hpp"

#include <boost/algorithm/string.hpp>
#include <boost/scoped_ptr.hpp>

/// \namespace clpp
/// \brief Main namespace of library.
namespace clpp {

/// \namespace clpp::detail
/// \brief Details of realization.
namespace detail {

/// \class parameter_parts_extractor
/// \brief Extracts name or value from inputed parameter.
class parameter_parts_extractor {
public:
    explicit parameter_parts_extractor( const std::string& _name_value_separator ) :
            name_value_separator( _name_value_separator ) {}
private:
    const std::string name_value_separator;
public:
    std::string extract_name_from( const std::string& inputed_parameter ) const {
        str_storage inputed_parameter_parts = obtain_parts_of( inputed_parameter );
        const size_t parts_quantity = inputed_parameter_parts.size();
        std::string name = inputed_parameter;
        if ( 2 == parts_quantity ) {
            name = inputed_parameter_parts.front();
        } else if ( parts_quantity > 2 ) {
            notify_about_name_value_separator_repetition_in( inputed_parameter );
        }
        return name;
    }

    std::string extract_value_from( const std::string& inputed_parameter ) const {
        str_storage inputed_parameter_parts = obtain_parts_of( inputed_parameter );
        const size_t parts_quantity = inputed_parameter_parts.size();
        std::string value = inputed_parameter;
        if ( 2 == parts_quantity ) {
            value = inputed_parameter_parts.back();
        } else if ( parts_quantity > 2 ) {
            notify_about_name_value_separator_repetition_in( inputed_parameter );
        }
        return value;
    }
private:
    str_storage obtain_parts_of( const std::string& inputed_parameter ) const {
        str_storage parts;
		boost::split( parts, inputed_parameter, boost::is_any_of( name_value_separator ) );
        return parts;
    }

    void notify_about_name_value_separator_repetition_in( const std::string& inputed_parameter ) const {
        const std::string what_happened = lib_prefix() 
                                          + "Name-value separator repetition detected in parameter '" 
                                          + inputed_parameter + "'!";
		throw std::runtime_error( what_happened );
    }
};

typedef boost::scoped_ptr< parameter_parts_extractor > parameter_parts_extractor_p;

} // namespace detail
} // namespace clpp

#endif // CLPP_DETAIL_PARAMETER_PARTS_EXTRACTOR_HPP
