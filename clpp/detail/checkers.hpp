// Command line parameters parser.
// File: checkers.hpp
//
// Copyright (C) Denis Shevchenko, 2010.
// shev.denis@gmail.com
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

#ifndef DETAIL__CHECKERS_HPP
#define DETAIL__CHECKERS_HPP

#include <boost/filesystem/operations.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/asio/ip/address_v4.hpp>
#include <boost/asio/ip/address_v6.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/foreach.hpp>

#include <string>
#include <vector>

/// \namespace clp_parser
/// \brief Main namespace of library.
namespace clp_parser {

/// \namespace clp_parser::detail
/// \brief Details of realisation.
namespace detail {

typedef std::vector< std::string > 
		str_storage;

/// \brief Check IPv4-address validity.
/// \param address IP-address.
/// \throw std::invalid_argument If address incorrect.
void check_ipv4_validity( const std::string& address ) {
    try {
        boost::asio::ip::address_v4 a( boost::asio::ip::address_v4::from_string( address ) );
    } catch ( const std::exception& /* exc */ ) {
        throw std::invalid_argument( "Invalid IPv4 '" + address + "'!" );
    }
}

/// \brief Check IPv6-address validity.
/// \param address IP-address.
/// \throw std::invalid_argument If address incorrect.
void check_ipv6_validity( const std::string& address ) {
    try {
        boost::asio::ip::address_v6 a( boost::asio::ip::address_v6::from_string( address ) );
    } catch ( const std::exception& /* exc */ ) {
        throw std::invalid_argument( "Invalid IPv6 '" + address + "'!" );
    }
}

/// \brief Check IP-address validity.
/// You can check IPv4 or IPv6.
/// \param address IP-address.
/// \throw std::invalid_argument If address incorrect.
void check_ip_validity( const std::string& address ) {
    try {
        check_ipv4_validity( address );
    } catch ( const std::exception& /* exc */ ) {
        try {
            check_ipv6_validity( address );
        } catch ( const std::exception& /* exc */ ) {
            throw std::invalid_argument( "Invalid IP '" + address + "' (not IPv4, not IPv6)!" );
        }
    }
}

/// \brief Check path validity.
/// \param path some path in filesystem.
/// \throw std::invalid_argument If path not exist.
void check_path_validity( const std::string& path ) {
	if ( !boost::filesystem::exists( path ) ) {
        throw std::invalid_argument( "Path '" + path + "' not exist!" );
    } else {}
}

/// \brief Check integer type of value.
/// \param value Value.
/// \throw std::invalid_argument If value' type is not integer.
void check_integer( const std::string& value ) {
    try { 
		boost::lexical_cast< int >( value );
    } catch ( const std::exception& /* exc */ ) {
        throw std::invalid_argument( "Value '" + value + "' is not <integer> type!" );
    }
}

/// \brief Check unsigned integer type of value.
/// \param value Value.
/// \throw std::invalid_argument If value' type is not unsigned integer.
void check_unsigned_integer( const std::string& value ) {
    try { 
		boost::lexical_cast< unsigned int >( value );
    } catch ( const std::exception& /* exc */ ) {
        throw std::invalid_argument( "Value '" + value + "' is not <unsigned integer> type!" );
    }
}

/// \brief Check real type of value.
/// \param value Value.
/// \throw std::invalid_argument If value' type is not real.
void check_real( const std::string& value ) {
    try { 
		boost::lexical_cast< double >( value );
    } catch ( const std::exception& /* exc */ ) {
        throw std::invalid_argument( "Value '" + value + "' is not <real> type!" );
    }
}

} // namespace detail
} // namespace clp_parser

#endif // DETAIL__CHECKERS_HPP
