// Command line parameters parser.
// File: parameter.hpp
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

#ifndef DETAIL__PARAMETER_HPP
#define DETAIL__PARAMETER_HPP

#include <boost/signals2/signal.hpp>
#include <boost/lexical_cast.hpp>

#include <string>

/// \namespace clp_parser
/// \brief Main namespace of library.
namespace clp_parser {

/// \enum value_type 
/// \brief Value types (for checking).
enum value_type {
	no_type				/*!< Default value. */
	, integer			/*!< Integer type checking. */
	, unsigned_integer	/*!< Unsigned integer type checking. */
	, real				/*!< Real type checking. */
};

/// \enum value_semantic 
/// \brief Value semantic types (for checking).
enum value_semantic {
	no_semantic			/*!< Default value. */
	, path				/*!< Path semantic checking. */
	, ipv4				/*!< IPv4 semantic checking. */
    , ipv6              /*!< IPv6 semantic checking. */
    , ip                /*!< IP semantic checking. */
};

/// \namespace clp_parser::detail
/// \brief Details of realisation.
namespace detail {

typedef std::vector< std::string > 
		str_storage;

/// \brief Pointer on function without value.
/// Call for simple parameters.
typedef void (*f_no_value)();

/// \brief Pointer on function with string-value.
/// Call for parameters with values.
typedef void (*f_with_value)(const std::string&);

/// \struct parameter
/// \brief Command line parameter.
///
/// Presents one command line parameter
/// with necessary options.
struct parameter : private boost::noncopyable {
public:
    typedef boost::signals2::signal< void () >
    		sig_type;
    typedef boost::signals2::signal< void ( const std::string& /* value */ ) >
            sig_with_value_type;
    typedef std::pair< std::string /* short_name */, std::string /* full_name */ >
            parameter_name;
public:
	/// \brief Overloaded ctor, for callable functions without values.
	/// \param nm Parameter's name.
	/// \param callable Pointer on function.
    explicit parameter( const parameter_name& 	nm, 
      					detail::f_no_value 		callable ) :
            name( nm )
            , is_necessary( false )
            , value_t( no_type )
            , value_s( no_semantic ) {
        if ( boost::contains( name.first, " " ) 
             || 
             boost::contains( name.second, " " ) ) {
        	std::string error = "Invalid parameter's name '" 
        						+ name.first 
        						+ "', it shouldn't contains space(s)!";
        	throw std::runtime_error( error );
        } else {}
        sig.connect( callable );
    }
    
   	/// \brief Overloaded ctor, for callable functions with values.
   	/// \param nm Parameter's name.
   	/// \param callable Pointer on function.
    explicit parameter( const parameter_name& 	nm, 
      					detail::f_with_value 	callable ) :
            name( nm )
            , is_necessary( false )
            , value_t( no_type )
            , value_s( no_semantic ) {
        if ( boost::contains( name.first, " " ) 
             || 
             boost::contains( name.second, " " ) ) {
        	std::string error = "Invalid parameter's name '" 
        						+ name.first 
        						+ "', it shouldn't contains space(s)!";
        	throw std::runtime_error( error );
        } else {}
        sig_with_value.connect( callable );
    }
    
    /// \brief Overloaded ctor, for callable object's function without values.
   	/// \param nm Parameter's name.
   	/// \param obj Pointer on object.
   	/// \param callable Pointer on object's function.
    template< typename T >
    explicit parameter( const parameter_name& 	nm, 
      					T* 						obj,
      					void (T::*callable)() ) :
            name( nm )
            , is_necessary( false )
            , value_t( no_type )
            , value_s( no_semantic ) {
        if ( boost::contains( name.first, " " ) 
             || 
             boost::contains( name.second, " " ) ) {
        	std::string error = "Invalid parameter's name '" 
        						+ name.first 
        						+ "', it shouldn't contains space(s)!";
        	throw std::runtime_error( error );
        } else {}
        sig.connect( boost::bind( callable, obj ) );
    }
    
    /// \brief Overloaded ctor, for callable object's function with values.
   	/// \param nm Parameter's name.
   	/// \param obj Pointer on object.
   	/// \param callable Pointer on object's function.
    template< typename T >
    explicit parameter( const parameter_name& 	nm, 
      					T* 						obj,
      					void (T::*callable)( const std::string& /* value */ ) ) :
            name( nm )
            , is_necessary( false )
            , value_t( no_type )
            , value_s( no_semantic ) {
        if ( boost::contains( name.first, " " ) 
             || 
             boost::contains( name.second, " " ) ) {
        	std::string error = "Invalid parameter's name '" 
        						+ name.first 
        						+ "', it shouldn't contains space(s)!";
        	throw std::runtime_error( error );
        } else {}
        sig_with_value.connect( boost::bind( callable, obj, _1 ) );
    }
public:
	/// \brief Parameter's name.
	parameter_name  	name;
	
	/// \brief Necessity flag.
	/// If it true, this parameter _must_
	/// be in command line.
	bool 				is_necessary;
	
	/// \brief Parameter's default value.
	std::string			def_value;

	/// \brief Signal for callback correspond function.
	/// Must be used for parameters without value.
    sig_type          	sig;
    
    /// \brief Signal for callback correspond function.
	/// Must be used for parameters with value.
    sig_with_value_type sig_with_value;
    
    /// \brief Value's type label.
	value_type 			value_t;
	
	/// \brief Value's semantis label.
	value_semantic 		value_s;
public:
	/// \brief Define parameter with type's checked value.
	/// \param vt Value's type field.
	/// \return *this
	parameter& check_type( const value_type& vt ) {
		value_t = vt;
		return *this;
	}
	
	/// \brief Define parameter with semantic's checked value.
	/// \param vs Value's semantic field.
	/// \return *this
	parameter& check_semantic( const value_semantic& vs ) {
		value_s = vs;
		return *this;
	}
	
	/// \brief Define parameter as necessary.
	/// \return *this
	parameter& necessary() {
		if ( !def_value.empty() ) {
			std::string error = "Option '" 
			                    + name.first 
			                    + "' already have default value, so it cannot define in necessary mode!"; 
			throw std::runtime_error( error );
		} else {}
		is_necessary = true;
		return *this;
	}
	
	/// \brief Define parameter's default value.
	/// \param value Default value.
	/// \return *this
	template< typename T >
	parameter& default_value( const T& value ) {
		if ( is_necessary ) {
			std::string error = "Option '" 
			                    + name.first 
			                    + "' already define in necessary mode, so it cannot have default value!"; 
			throw std::invalid_argument( error );
		} else {}
		def_value = boost::lexical_cast< std::string >( value );
		if ( boost::contains( def_value, " " ) ) {
        	std::string error = "Invalid default parameter's value '" 
        						+ name.first 
        						+ "': it shouldn't contains space(s)!";
        	throw std::invalid_argument( error );
        } else {}
		return *this;
	}
};







///////////////////////////////////////////////////////////////////////////////////////////////////
// 1.0rc
/*

/// \struct abstract_parameter
/// \brief Abstract parameter.
///
/// Presents abstract parent for 
/// all parameters (polimorphism).
struct abstract_parameter {};

/// \struct
/// \brief 
///
///
struct empty_type {};

/// \struct parameter
/// \brief Command line parameter.
///
///
template< typename Object, template Argument = empty_type >
struct parameter : private boost::noncopyable, 
                   public abstract_parameter {
public:
    typedef parameter< Object, Argument >
            own_type;

    typedef boost::signals2::signal< void () >
    		sig_type;
    typedef boost::signals2::signal< void ( const Argument& ) >
            sig_with_value_type;
    typedef std::pair< std::string, std::string >
            parameter_name;
public:
	/// \brief Overloaded ctor, for callable functions without values.
	/// \param nm Parameter's name.
	/// \param callable Pointer on function.
    explicit parameter( const parameter_name& nm, void (*callable)() ) :
            name( nm )
            , is_necessary( false )
            , def_value()
            , has_def_value( false )
            , value_t( no_type )
            , value_s( no_semantic ) {
        if ( boost::contains( name.first, " " ) 
             || 
             boost::contains( name.second, " " ) ) {
        	std::string error = "Invalid parameter's name '" 
        						+ name.first 
        						+ "', it shouldn't contains space(s)!";
        	throw std::runtime_error( error );
        } else {}
        sig.connect( callable );
    }
    
   	/// \brief Overloaded ctor, for callable functions with values.
   	/// \param nm Parameter's name.
   	/// \param callable Pointer on function.
    explicit parameter( const parameter_name& nm, 
      					void (*callable)( const Argument& ) :
            name( nm )
            , is_necessary( false )
            , def_value()
            , has_def_value( false )
            , value_t( no_type )
            , value_s( no_semantic ) {
        if ( boost::contains( name.first, " " ) 
             || 
             boost::contains( name.second, " " ) ) {
        	std::string error = "Invalid parameter's name '" 
        						+ name.first 
        						+ "', it shouldn't contains space(s)!";
        	throw std::runtime_error( error );
        } else {}
        sig_with_value.connect( callable );
    }
    
    /// \brief Overloaded ctor, for callable object's function without values.
   	/// \param nm Parameter's name.
   	/// \param obj Pointer on object.
   	/// \param callable Pointer on object's function.
    explicit parameter( const parameter_name& 	nm, 
      					Object* 				obj,
      					void (Object::*callable)() ) :
            name( nm )
            , is_necessary( false )
            , def_value()
            , has_def_value( false )
            , value_t( no_type )
            , value_s( no_semantic ) {
        if ( boost::contains( name.first, " " ) 
             || 
             boost::contains( name.second, " " ) ) {
        	std::string error = "Invalid parameter's name '" 
        						+ name.first 
        						+ "', it shouldn't contains space(s)!";
        	throw std::runtime_error( error );
        } else {}
        sig.connect( boost::bind( callable, obj ) );
    }
    
    /// \brief Overloaded ctor, for callable object's function with values.
   	/// \param nm Parameter's name.
   	/// \param obj Pointer on object.
   	/// \param callable Pointer on object's function.
    explicit parameter( const parameter_name& 	nm, 
      					Object*					obj,
      					void (Object::*callable)( const Argument& ) ) :
            name( nm )
            , is_necessary( false )
            , def_value()
            , has_def_value( false )
            , value_t( no_type )
            , value_s( no_semantic ) {
        if ( boost::contains( name.first, " " ) 
             || 
             boost::contains( name.second, " " ) ) {
        	std::string error = "Invalid parameter's name '" 
        						+ name.first 
        						+ "', it shouldn't contains space(s)!";
        	throw std::runtime_error( error );
        } else {}
        sig_with_value.connect( boost::bind( callable, obj, _1 ) );
    }
public:
	/// \brief Parameter's name.
	parameter_name  	name;
	
	/// \brief Necessity flag.
	/// If it true, this parameter _must_
	/// be in command line.
	bool 				is_necessary;
	
	/// \brief Parameter's default value.
	Argument			def_value;
	
	bool 				has_def_value;

	/// \brief Signal for callback correspond function.
	/// Must be used for parameters without value.
    sig_type          	sig;
    
    /// \brief Signal for callback correspond function.
	/// Must be used for parameters with value.
    sig_with_value_type sig_with_value;
    
    /// \brief Value's type label.
	value_type 			value_t;
	
	/// \brief Value's semantis label.
	value_semantic 		value_s;
public:
	/// \brief Define parameter with type's checked value.
	/// \param vt Value's type field.
	/// \return *this
	parameter& check_type( const value_type& vt ) {
		value_t = vt;
		return *this;
	}
	
	/// \brief Define parameter with semantic's checked value.
	/// \param vs Value's semantic field.
	/// \return *this
	own_type& check_semantic( const value_semantic& vs ) {
		value_s = vs;
		return *this;
	}
	
	/// \brief Define parameter as necessary.
	/// \return *this
	own_type& necessary() {
		if ( has_def_value ) {
			std::string error = "Option '" 
			                    + name.first 
			                    + "' already have default value, so it cannot define in necessary mode!"; 
			throw std::runtime_error( error );
		} else {}
		is_necessary = true;
		return *this;
	}
	
	/// \brief Define parameter's default value.
	/// \param value Default value.
	/// \return *this
	template< typename Some_argument >
	own_type& default_value( const Some_argument& value ) {
		if ( is_necessary ) {
			std::string error = "Option '" 
			                    + name.first 
			                    + "' already define in necessary mode, so it cannot have default value!"; 
			throw std::invalid_argument( error );
		} else {}
        if ( typeid( Some_argument ) != typeid( Argument ) ) {
        	std::string error = "Default value's type differ from value's type defined by callable function!";
        	throw std::invalid_argument( error );
        } else {}
		def_value = value;
		has_def_value = true;
		if ( typeid( def_value ) == typeid( std::string )
             && 
             boost::contains( def_value, " " ) ) {
        	std::string error = "Invalid default parameter's (string) value '" 
        						+ name.first 
        						+ "': it shouldn't contains space(s)!";
        	throw std::invalid_argument( error );
        } else {}
		return *this;
	}
};
*/
///////////////////////////////////////////////////////////////////////////////////////////////////

} // namespace detail

typedef detail::parameter
		cl_param;

// no typedef on 1.0rc

} // namespace clp_parser

#endif // DETAIL__PARAMETER_HPP
