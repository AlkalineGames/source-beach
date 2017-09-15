//----------------------------------------------------------
//  Copyright 2001-2017 (c) Alkaline Games LLC
//
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at http://mozilla.org/MPL/2.0/.
//----------------------------------------------------------
/**
 *  @file       extension_typed.tpp
 *  @note       platform independent, Standard C++
 *  @author     Christopher Augustus
 */
//----------------------------------------------------------

#include <chain/extension_typed.hpp>

namespace chain
{

//--------------------------------------
//  protected methods
//--------------------------------------

template <class T>
extension_typed<T>::extension_typed(
    class_identity  in_class_id,
    T &             in_owner )
  : 
    extension(      in_class_id,
                   &in_owner )
{}

//--------------------------------------

}; // end of namespace chain

//----------------------------------------------------------
// (end of file)
