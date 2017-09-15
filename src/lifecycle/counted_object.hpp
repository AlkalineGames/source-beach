#if !defined(BEACH_LIFECYCLE_COUNTED_OBJECT)
#define      BEACH_LIFECYCLE_COUNTED_OBJECT

//----------------------------------------------------------
//	Copyright 1996-2017 (c) by Alkaline Games LLC
//
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at http://mozilla.org/MPL/2.0/.
//----------------------------------------------------------
/**
 *  @file       counted_object.hpp
 *  @note       platform independent, Standard C++
 *  @author     Christopher Augustus
 */
//----------------------------------------------------------

#include <atoms/primitives.hpp>

namespace lifecycle
{
	class counted_object;
	using atoms::boolean;
	using atoms::whole;

//--------------------------------------

/// required interface for managers of reference counted objects

class counted_object_manager
{
friend class counted_object;
protected:

	virtual void release_object( counted_object & ) = 0;
};

//--------------------------------------

/// superclass an object that is reference counted
/**
 *  A common superclass for the "body" participant of a
 *  a mechanism that implements the Counted Body or
 *  Counted Pointer design pattern idioms for C++.
 *
 *  Actual code is based on Scott Meyers book:
 *  More Effective C++, Item 29: Reference Counting.
 *
 *  @note	design patterns applied:
 *				- Counted Body    [PLOP4]
 *              - Counted Pointer [POSA1]
 *              - Template Method [GoF]
 */
class counted_object
{
public:

	static void remove_reference_to_object( ///< $$$ SHOULD NOT BE PUBLIC
		const counted_object &  in_object,
		whole		            in_priority = 0 );

	virtual counted_object_manager * get_manager() const;
		///< intended for override, this level returns 0
	
	whole get_reference_count() const
    {
        return _reference_count;
    }
    void add_reference( whole in_priority = 0 ) const
    {
        ++_reference_count;
        augment_add_reference( in_priority );
    }
    boolean is_shared()    const { return (_reference_count > 1); }
    boolean is_shareable() const { return _is_shareable; }
    void    mark_unshareable()   { _is_shareable = false; }

protected:

    counted_object();
    counted_object(              const counted_object & rhs );
    counted_object & operator =( const counted_object & rhs )
    {} ///< counted state not copied; nor on copy constructor

    virtual ~counted_object();

    // @name template methods; these do nothing
	//@{
    virtual void augment_add_reference(    whole in_priority ) const;
    virtual void augment_remove_reference( whole in_priority ) const;
	//@}

private:

    void remove_reference( whole in_priority = 0 ) const
    {
        --_reference_count;
        augment_remove_reference( in_priority );
    }

    mutable whole _reference_count;
    boolean       _is_shareable;

}; // end of class counted_object

//--------------------------------------

}; // end of namespace lifecycle

//----------------------------------------------------------
#endif // BEACH_LIFECYCLE_COUNTED_OBJECT
