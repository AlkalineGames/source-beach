//----------------------------------------------------------
//  Copyright 2003-2017 (c) Alkaline Games LLC
//
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at http://mozilla.org/MPL/2.0/.
//----------------------------------------------------------
/**
 *  @file       expression_templates.cpp
 *  @note       platform independent, Standard C++
 *  @author     Christopher Augustus
 */
//----------------------------------------------------------

#include <expression/splash.h>
#include <expression/range.h>

namespace expression
{

//--------------------------------------

template class SPList<int>;
template class SPList<SPString>;
template class SPList<range>;
template class SPListBase<int>;
template class SPListBase<SPString>;
template class SPListBase<range>;
template class SubList<int>;
template class SubList<SPString>;
template class SubList<range>;

template ostream& operator<<(ostream &, SPList<int> const &);
template ostream& operator<<(ostream &, SPList<SPString> const &);

//--------------------------------------

}; // end of namespace expression

//----------------------------------------------------------
// (end of file)
