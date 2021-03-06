#if !defined(BEACH_LIFECYCLE_COUNTED_PTR_CONST)
#define      BEACH_LIFECYCLE_COUNTED_PTR_CONST
//----------------------------------------------------------
//  Copyright 1996-2017 (c) Alkaline Games LLC
//
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at http://mozilla.org/MPL/2.0/.
//----------------------------------------------------------
/**
 *  @file       counted_ptr_const.hpp
 *  @note       platform independent, Standard C++
 *  @author     Christopher Augustus
 */
//----------------------------------------------------------

namespace lifecycle
{
        
//--------------------------------------

/// pointer-like "handle" template to a constant reference counted object
/**
 *  A template for the "handle" participant of a
 *  a mechanism that implements the Counted Pointer
 *  design pattern idiom for C++.
 *
 *  !!! Since this class has the semantics of a pointer,
 *  !!! clients must take care to check for null before
 *  !!! deferencing (operators -> or *).
 *
 *  The syntax and semantics of this class matches the
 *  Ref<T> template defined by ODMG 2.0.
 *
 *  Actual code is based on Scott Meyers book:
 *  More Effective C++, Item 29: Reference Counting.
 *
 *  @note   design patterns applied:
 *              - Counted Pointer [POSA1]
 */
template <class T>      ///< T must be a subclass of counted_object
class counted_ptr_const
{
public:

    typedef T object;

    counted_ptr_const()
      :
        _object( 0 )
    {}
    counted_ptr_const( const object * obj )
      :
        _object( obj )
    {
        add_reference_count();
    }
    counted_ptr_const( const counted_ptr_const & rhs )
      :
        _object( rhs._object )
    {
        add_reference_count();
    }
    ~counted_ptr_const()
    {
        remove_reference_count();
    }
    bool operator ==( const counted_ptr_const & rhs ) const
    {
        return _object == rhs._object;
    }
    bool operator !=( const counted_ptr_const & rhs ) const
    {
        return _object != rhs._object;
    }
    counted_ptr_const & operator =(
        const counted_ptr_const & rhs )
    {
        if ( &rhs != this )
        {
            if ( _object != rhs._object )
            {
                remove_reference_count();
                _object = rhs._object;
                add_reference_count();
            }                    
        }                
        return *this;
    }
    counted_ptr_const & operator =(
        const object * in_object )
    {
        if ( _object != in_object )
        {
            remove_reference_count();
            _object = in_object;
            add_reference_count();
        }          
        return *this;      
    }
    void assign_without_deref(  ///< !!! only to be used in special cases
        const object * in_object )
    {
        if ( _object != in_object )
        {
            // remove_reference_count(); !!! no dereference
            _object = in_object;
            add_reference_count();
        }                
    }
    void assign_without_ref(  ///< !!! only to be used in special cases
        const object * in_object )
    {
        if ( _object != in_object )
        {
            // remove_reference_count(); !!! no dereference
            _object = in_object;
            // add_reference_count(); !!! no reference
        }                
    }
    void clear()
    {
        remove_reference_count();
        _object = 0;
    }
    const object *  ptr()           const { return _object; }
    bool            is_null()       const { return _object == 0; }
    bool            operator !()    const { return _object == 0; }    

    /// @name dereferencing operators
    /**
     *  !!! clients must not call these
     *  !!! if the pointer value is null
     */
    //@{
    const object *  operator ->()   const { return  _object; }
    const object &  operator  *()   const { return *_object; }
    const object &  ref()           const { return *_object; }
    //@}
    
private:

    void add_reference_count()
    {
        if ( _object != 0 )
        {
            _object->add_reference();
        }
    }
    void remove_reference_count()
    {
        if ( _object != 0 )
        {
            object::remove_reference_to_object(
            //  static_cast<counted_object&>(*_object) );
                *_object );
        }
    }

    const object * _object;

}; // end of template class counted_ptr_const

//--------------------------------------

}; // end of namespace lifecycle

//----------------------------------------------------------
#endif // BEACH_LIFECYCLE_COUNTED_PTR_CONST
