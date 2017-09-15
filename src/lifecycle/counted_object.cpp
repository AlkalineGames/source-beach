//----------------------------------------------------------
//	Copyright 1996-2017 (c) by Alkaline Games LLC
//
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at http://mozilla.org/MPL/2.0/.
//----------------------------------------------------------
/**
 *  @file       counted_object.cpp
 *  @note       platform independent, Standard C++
 *  @author     Christopher Augustus
 */
//----------------------------------------------------------

#include <lifecycle/counted_object.hpp> // this header

namespace lifecycle
{

//--------------------------------------
//	public methods
//--------------------------------------

//static
void
counted_object::remove_reference_to_object(
	const counted_object &  in_object,
	whole		            in_priority )
{
	in_object.remove_reference( in_priority );
	if ( in_object._reference_count == 0 )
	{
		counted_object_manager * manager
			= in_object.get_manager();
		if ( manager != 0 )
		{
			manager->release_object( // !!! const cast
                const_cast<counted_object&>(in_object) );
		}
	}
}

//--------------------------------------

// virtual
counted_object_manager *
counted_object::get_manager() const
{
	return 0; // intended for optional override
}
	
//--------------------------------------
//	protected methods
//--------------------------------------

counted_object::counted_object()
  :          
    _reference_count( 0 ),
    _is_shareable( true )
{}

//--------------------------------------

counted_object::counted_object(
    const counted_object & rhs )
  :
    _reference_count( 0 ),
    _is_shareable( true )
{}

//--------------------------------------

// virtual 
void
counted_object::augment_add_reference(
    whole in_priority ) const
{
    // do nothing; intended for override
}

//--------------------------------------

// virtual
void
counted_object::augment_remove_reference(
    whole in_priority ) const
{
    // do nothing; intended for override
}

//--------------------------------------

// virtual
counted_object::~counted_object()
{}

//--------------------------------------

}; // end of namespace lifecycle

//----------------------------------------------------------
// (end of file)
