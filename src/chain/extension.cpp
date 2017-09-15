//----------------------------------------------------------
//  Copyright 2001-2017 (c) Alkaline Games LLC
//
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at http://mozilla.org/MPL/2.0/.
//----------------------------------------------------------
/**
 *  @file       extension.cpp
 *  @note       platform independent, Standard C++
 *  @author     Christopher Augustus
 */
//----------------------------------------------------------

#include <chain/extension.hpp> // this header

namespace chain
{

//--------------------------------------
//  protected methods
//--------------------------------------

extension::extension(
    class_identity  in_class_id,
    void *          in_owner )
  :
    linked(         in_class_id ),
    _owner(         in_owner )
{}

//--------------------------------------

// virtual
extension::~extension()
{}

//--------------------------------------

}; // end of namespace chain

//----------------------------------------------------------
// (end of file)
