#if !defined(BEACH_LIFECYCLE_LABELS)
#define      BEACH_LIFECYCLE_LABELS
//----------------------------------------------------------
//  Copyright 2011-2017 (c) by Alkaline Games LLC
//
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at http://mozilla.org/MPL/2.0/.
//----------------------------------------------------------
/**
 *  @file       logger_labels.hpp
 *  @note       platform independent, Standard C++
 *  @author     Christopher Augustus
 */
//----------------------------------------------------------

namespace lifecycle
{

//--------------------------------------

/// logger labels for all tracepoints in beach

class logger_labels
{
public:

    static void install();
};

//--------------------------------------

}; // end of namespace lifecycle

//----------------------------------------------------------
#endif // BEACH_LIFECYCLE_LABELS
