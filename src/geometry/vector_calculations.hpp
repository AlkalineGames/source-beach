#if !defined(BEACH_GEOMETRY_VECTOR_CALCULATIONS)
#define      BEACH_GEOMETRY_VECTOR_CALCULATIONS
//----------------------------------------------------------
//  Copyright 2013-2017 (c) Alkaline Games LLC
//
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at http://mozilla.org/MPL/2.0/.
//----------------------------------------------------------
/**
 *  @file       vector_calculations.hpp
 *  @note       platform independent, Standard C++
 *  @author     Christopher Augustus
 */
//----------------------------------------------------------

#include <geometry/vector.hpp>

namespace geometry
{

//--------------------------------------

/// template for a 3-D vector, left-handed, with its derived calculations
/**
 *  @note   design patterns applied:
 *              - Lazy Evaluation [???]
 */
template <class T>
class vector_xyz_calculations
{
public:

    vector_xyz_calculations()
      : _magnitude( 0 ),
        _magnitude_squared( 0 )
    {}
    vector_xyz_calculations( const vector_xyz<T> & v )
      : _vector( v ),
        _direction( v ),
        _magnitude( 0 ),
        _magnitude_squared( 0 )
    {}
    vector_xyz_calculations & operator =( const vector_xyz<T> & v )
    {
        this->_vector = v;
        this->_direction = v;
        this->_magnitude = 0;
        this->_magnitude_squared = 0;
    }
    bool operator ==( const vector_xyz_calculations & rhs ) const
    {
        return (_vector == rhs._vector);
    }
    bool operator ==( const vector_xyz<T> & v ) const
    {
        return (_vector == v);
    }
    operator const vector_xyz<T> &() const 
    {
        return this->_vector;
    }
    const vector_xyz<T> &   get_vector() const 
    {
        return this->_vector;
    }
    const vector_xyz<T> &   acquire_direction() const
    {
        establish_calculations();
        return this->_direction;
    } 
    T                       acquire_magnitude() const
    {
        establish_calculations();
        return this->_magnitude;
    } 
    T                       acquire_magnitude_squared() const
    {
        establish_calculations();
        return this->_magnitude_squared;
    } 

private:

    void establish_calculations() const
    {
        if ( (_magnitude == 0) && (! _direction.is_zero()) )
        {
            this->_direction.normalize_get_magnitude( this->_magnitude ); // $$$ 
            this->_magnitude_squared = this->_magnitude * this->_magnitude;
        }
    } 
    vector_xyz<T>           _vector;
    mutable vector_xyz<T>   _direction;
    mutable T               _magnitude;
    mutable T               _magnitude_squared;

}; // end of template vector_xyz_calculations

//--------------------------------------

}; // end of namespace geometry

//----------------------------------------------------------
#endif // BEACH_GEOMETRY_VECTOR_CALCULATIONS
