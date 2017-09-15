//----------------------------------------------------------
//  Copyright 2012-2017 (c) Alkaline Games LLC
//
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at http://mozilla.org/MPL/2.0/.
//----------------------------------------------------------
/**
 *  @file       test_cuboid_aligned.cpp
 *  @note       platform independent, Standard C++
 *  @author     Christopher Augustus
 */
//----------------------------------------------------------

#include "test_cuboid_aligned.hpp"

#include <atoms/primitives.hpp>
#include <geometry/coordinates.hpp>
#include <geometry/cuboid_aligned.hpp>
#include <geometry/vector.hpp>

namespace geometry
{

//--------------------------------------
//  public methods
//--------------------------------------

test_cuboid_aligned::test_cuboid_aligned()
  :
    CppUnit::TestCase( "test_cuboid_aligned" )
{}

//--------------------------------------

void
test_cuboid_aligned::register_tests(
    CppUnit::TestSuite * suite )
{
    suite->addTest( new CppUnit::TestCaller<test_cuboid_aligned>(
        "test_side_of_plane", &test_cuboid_aligned::test_side_of_plane, *this ) );
}

//--------------------------------------

void
test_cuboid_aligned::test_side_of_plane()
{
    // test against a pyramid on its side (e.g. viewing frustum)

    coordinates_xyz<real> pospyramidapex(  0,  0, -5 );
    coordinates_xyz<real> pospyramidbase(  0,  0,  5 );

    vector_xyz<real> normalplaneback(    0,  0,  1 );
    vector_xyz<real> normalplanebottom(  0,  1,  0 );
    vector_xyz<real> normalplaneright(  -1,  0,  0 );
    vector_xyz<real> normalplaneleft(    1,  0,  0 );
    vector_xyz<real> normalplanetop(     0, -1,  0 );
    vector_xyz<real> normalplanefront(   0,  0, -1 );

    real radianspyramidside( constants<real>::get_pi_quartered() );

    normalplanebottom.rotate_x( - radianspyramidside );
    normalplaneright .rotate_y( - radianspyramidside );
    normalplaneleft  .rotate_y(   radianspyramidside );
    normalplanetop   .rotate_x(   radianspyramidside );

    cuboid_aligned<real> cubalignedback(    -2,  -2, -10,   2,   2,  -6 );
    cuboid_aligned<real> cubalignedbottom(  -2, -12,  -2,   2,  -8,   2 );
    cuboid_aligned<real> cubalignedright(    8,  -2,  -2,  12,   2,   2 );
    cuboid_aligned<real> cubalignedleft(   -12,  -2,  -2,  -8,   2,   2 );
    cuboid_aligned<real> cubalignedtop(     -2,   8,  -2,   2,  12,   2 );
    cuboid_aligned<real> cubalignedfront(   -2,  -2,   6,   2,   2,  10 );

    CPPUNIT_ASSERT( cubalignedback  .side_of_plane( pospyramidapex, normalplaneback    ) <  0 );
    CPPUNIT_ASSERT( cubalignedback  .side_of_plane( pospyramidapex, normalplanebottom  ) == 0 );
    CPPUNIT_ASSERT( cubalignedback  .side_of_plane( pospyramidapex, normalplaneright   ) == 0 );
    CPPUNIT_ASSERT( cubalignedback  .side_of_plane( pospyramidapex, normalplaneleft    ) == 0 );
    CPPUNIT_ASSERT( cubalignedback  .side_of_plane( pospyramidapex, normalplanetop     ) == 0 );
    CPPUNIT_ASSERT( cubalignedback  .side_of_plane( pospyramidbase, normalplanefront   ) >  0 );
    CPPUNIT_ASSERT( cubalignedback  .side_of_plane( pospyramidbase, normalplaneback    ) <  0 );

    CPPUNIT_ASSERT( cubalignedbottom.side_of_plane( pospyramidapex, normalplaneback    ) >  0 );
    CPPUNIT_ASSERT( cubalignedbottom.side_of_plane( pospyramidapex, normalplanebottom  ) <  0 );
    CPPUNIT_ASSERT( cubalignedbottom.side_of_plane( pospyramidapex, normalplaneright   ) >  0 );
    CPPUNIT_ASSERT( cubalignedbottom.side_of_plane( pospyramidapex, normalplaneleft    ) >  0 );
    CPPUNIT_ASSERT( cubalignedbottom.side_of_plane( pospyramidapex, normalplanetop     ) >  0 );
    CPPUNIT_ASSERT( cubalignedbottom.side_of_plane( pospyramidbase, normalplanefront   ) >  0 );
    CPPUNIT_ASSERT( cubalignedbottom.side_of_plane( pospyramidbase, normalplaneback    ) <  0 );

    CPPUNIT_ASSERT( cubalignedright .side_of_plane( pospyramidapex, normalplaneback    ) >  0 );
    CPPUNIT_ASSERT( cubalignedright .side_of_plane( pospyramidapex, normalplanebottom  ) >  0 );
    CPPUNIT_ASSERT( cubalignedright .side_of_plane( pospyramidapex, normalplaneright   ) <  0 );
    CPPUNIT_ASSERT( cubalignedright .side_of_plane( pospyramidapex, normalplaneleft    ) >  0 );
    CPPUNIT_ASSERT( cubalignedright .side_of_plane( pospyramidapex, normalplanetop     ) >  0 );
    CPPUNIT_ASSERT( cubalignedright .side_of_plane( pospyramidbase, normalplanefront   ) >  0 );
    CPPUNIT_ASSERT( cubalignedright .side_of_plane( pospyramidbase, normalplaneback    ) <  0 );

    CPPUNIT_ASSERT( cubalignedleft  .side_of_plane( pospyramidapex, normalplaneback    ) >  0 );
    CPPUNIT_ASSERT( cubalignedleft  .side_of_plane( pospyramidapex, normalplanebottom  ) >  0 );
    CPPUNIT_ASSERT( cubalignedleft  .side_of_plane( pospyramidapex, normalplaneright   ) >  0 );
    CPPUNIT_ASSERT( cubalignedleft  .side_of_plane( pospyramidapex, normalplaneleft    ) <  0 );
    CPPUNIT_ASSERT( cubalignedleft  .side_of_plane( pospyramidapex, normalplanetop     ) >  0 );
    CPPUNIT_ASSERT( cubalignedleft  .side_of_plane( pospyramidbase, normalplanefront   ) >  0 );
    CPPUNIT_ASSERT( cubalignedleft  .side_of_plane( pospyramidbase, normalplaneback    ) <  0 );

    CPPUNIT_ASSERT( cubalignedtop   .side_of_plane( pospyramidapex, normalplaneback    ) >  0 );
    CPPUNIT_ASSERT( cubalignedtop   .side_of_plane( pospyramidapex, normalplanebottom  ) >  0 );
    CPPUNIT_ASSERT( cubalignedtop   .side_of_plane( pospyramidapex, normalplaneright   ) >  0 );
    CPPUNIT_ASSERT( cubalignedtop   .side_of_plane( pospyramidapex, normalplaneleft    ) >  0 );
    CPPUNIT_ASSERT( cubalignedtop   .side_of_plane( pospyramidapex, normalplanetop     ) <  0 );
    CPPUNIT_ASSERT( cubalignedtop   .side_of_plane( pospyramidbase, normalplanefront   ) >  0 );
    CPPUNIT_ASSERT( cubalignedtop   .side_of_plane( pospyramidbase, normalplaneback    ) <  0 );

    CPPUNIT_ASSERT( cubalignedfront .side_of_plane( pospyramidapex, normalplaneback    ) >  0 );
    CPPUNIT_ASSERT( cubalignedfront .side_of_plane( pospyramidapex, normalplanebottom  ) >  0 );
    CPPUNIT_ASSERT( cubalignedfront .side_of_plane( pospyramidapex, normalplaneright   ) >  0 );
    CPPUNIT_ASSERT( cubalignedfront .side_of_plane( pospyramidapex, normalplaneleft    ) >  0 );
    CPPUNIT_ASSERT( cubalignedfront .side_of_plane( pospyramidapex, normalplanetop     ) >  0 );
    CPPUNIT_ASSERT( cubalignedfront .side_of_plane( pospyramidbase, normalplanefront   ) <  0 );
    CPPUNIT_ASSERT( cubalignedfront .side_of_plane( pospyramidbase, normalplaneback    ) >  0 );
}

//--------------------------------------

// virtual
int
test_cuboid_aligned::countTestCases() const
{
    return 1;
}

//--------------------------------------

// virtual
void
test_cuboid_aligned::setUp()
{
//    _cuboid_aligned = new cuboid_aligned;
}

//--------------------------------------

// virtual
void
test_cuboid_aligned::tearDown()
{
//    delete _cuboid_aligned;
}

//--------------------------------------

}; // end of namespace geometry

//--------------------------------------
//  template instantiations
//--------------------------------------

template class CppUnit::TestCaller<geometry::test_cuboid_aligned>;

//----------------------------------------------------------
// (end of file)
