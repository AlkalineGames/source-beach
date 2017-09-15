//----------------------------------------------------------
//  Copyright 1996-2017 (c) Alkaline Games LLC
//
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at http://mozilla.org/MPL/2.0/.
//----------------------------------------------------------
/**
 *  @file       cuboid_aligned.tpp
 *  @note       platform independent, Standard C++
 *  @author     Christopher Augustus
 */
//----------------------------------------------------------

#include <geometry/cuboid_aligned.hpp> // this header

#include <cmath>

namespace geometry
{
    using namespace atoms;

//--------------------------------------
//  public methods
//--------------------------------------

template <class T>
boolean
cuboid_aligned<T>::intersects_ray(
    const position &    in_origin,
    const vector &      in_direction,
    units               in_length,      ///< if 0, ray is infinite
    units *             out_intersection_length,
    position *          out_intersection_point ) const
{
    // (Gems comment:)
    // Fast Ray-Box Intersection
    // by Andrew Woo
    // from "Graphics Gems", Academic Press, 1990

    enum Constants
    {
        RIGHT,
        LEFT,
        MIDDLE
    };

    // $$$ make vectors indexable
    units origin[3] =
    {
        in_origin.x(), in_origin.y(), in_origin.z()
    };
    units dir[3] =
    {
        in_direction.x(), in_direction.y(), in_direction.z()
    };
    units minB[3] =
    {
        _minimum.x(), _minimum.y(), _minimum.z()
    };
    units maxB[3] =
    {
        _maximum.x(), _maximum.y(), _maximum.z()
    };

    // (Gems comment:)
    // Find candidate planes; this loop can be avoided if
    // rays cast all from the eye(assume perpsective view)
    boolean inside = true;
    whole   quadrant[3];
    units   candidatePlane[3];
    for ( integer i = 0; i < 3; i++ )
    {
        if ( origin[i] < minB[i] )
        {
            quadrant[i] = LEFT;
            candidatePlane[i] = minB[i];
            inside = false;
        }
        else if ( origin[i] > maxB[i] )
        {
            quadrant[i] = RIGHT;
            candidatePlane[i] = maxB[i];
            inside = false;
        }
        else    
        {
            quadrant[i] = MIDDLE;

            // this code was added to the original Gem by C.Augustus
            // we still have to test against candidate planes in the middle
            // unless we never intersect either the min or max
            if ( dir[i] < 0 )
            {
                candidatePlane[i] = minB[i];
            }
            else if ( dir[i] > 0 )
            {
                candidatePlane[i] = maxB[i];
            }
        }
    }
    if ( inside ) // code added by World Fusion [cat]
    {
        if ( out_intersection_length != 0 )
        {
            *out_intersection_length = 0.0;
        }
        if ( out_intersection_point != 0 )
        {
            *out_intersection_point = in_origin;
        }
        return true;
    }
    // (Gems comment:)
    // Calculate T distances to candidate planes
    units distance[3];
    integer i;
    for ( i = 0; i < 3; i++ )
    {
        if ( dir[i] != 0.0 ) // modified from original gem: include MIDDLE calcs
        {
            distance[i] = (candidatePlane[i]-origin[i]) / dir[i];
        }
        else
        {
            distance[i] = -1.0;
        }
    }
    // (Gems comment:)
    // Get largest of the distance's for final choice of intersection
    boolean doroundcomparison = false;
    integer whichPlane = -1; // modified from original gem: don't assume X is largest
    for ( i = 0; i < 3; i++ )
    {
        if ( quadrant[i] != MIDDLE ) // added to original gem: MIDDLE cannot be closest
        {
            // modified from original gem 
            if (   (whichPlane == -1)
                || (distance[whichPlane] < distance[i]) )
            {
                whichPlane = i;
            }
            else if ( distance[whichPlane] == distance[i] )
            {
                doroundcomparison = true;
            }
        }
    }
    // (Gems comment:)
    // Check final candidate actually inside cuboid
    if (   (distance[whichPlane] < 0             )
        || (   (in_length > 0) 
            && (distance[whichPlane] > in_length)) )
    {
        return false;
    }
    units coord[3]; // point of intersection
    for ( i = 0; i < 3; i++ )
    {
        if ( whichPlane == i )
        {
            coord[i] = candidatePlane[i];
        }
        else
        {
            coord[i] = origin[i] + (distance[whichPlane] * dir[i]);
        }
        units lhs    = coord[i];
        units rhsmin = minB[i];            
        units rhsmax = maxB[i];            
        if ( doroundcomparison )
        {
            // !!! round to nearest mm
            units lhsint;
            lhs = std::modf( lhs * 1000.0, &lhsint );
            lhs = lhsint * 0.001;
            units rhsminint;
            rhsmin = std::modf( rhsmin * 1000.0, &rhsminint );
            rhsmin = rhsminint * 0.001;
            units rhsmaxint;
            rhsmax = std::modf( rhsmax * 1000.0, &rhsmaxint );
            rhsmax = rhsmaxint * 0.001;
        }            
        // !!! point of intersection must be inside cuboid, so the
        // !!! quadrant should be superfluous for this comparison
        //if (   ((quadrant[i] == LEFT ) && (lhs < rhsmin))
        //    || ((quadrant[i] == RIGHT) && (lhs > rhsmax)) )
        if (   (lhs < rhsmin)
            || (lhs > rhsmax) )
        {
            return false;
        }
    }
    if ( out_intersection_length != 0 )
    {
        *out_intersection_length = distance[whichPlane];
    }
    if ( out_intersection_point != 0 )
    {
        out_intersection_point->set(
            coord[0], coord[1], coord[2] );
    }
    return true;
}

//--------------------------------------

template <class T>
integer 
cuboid_aligned<T>::side_of_plane(
    const position &    in_displacement,
    const vector &      in_normal_plane ) const
{
    // $$$ OPTIMIZE ALL OF THIS
    // $$$ WE SHOULDN'T HAVE TO CHECK ALL 8 CORNERS
    // cost == 24 multiplies, 40 adds, 16 compares

    const T corner[][3] =
    {
        { _minimum.x() - in_displacement.x(),
          _minimum.y() - in_displacement.y(),
          _minimum.z() - in_displacement.z() },
        { _maximum.x() - in_displacement.x(),
          _minimum.y() - in_displacement.y(),
          _minimum.z() - in_displacement.z() },
        { _minimum.x() - in_displacement.x(),
          _maximum.y() - in_displacement.y(),
          _minimum.z() - in_displacement.z() },
        { _maximum.x() - in_displacement.x(),
          _maximum.y() - in_displacement.y(),
          _minimum.z() - in_displacement.z() },
        { _minimum.x() - in_displacement.x(),
          _minimum.y() - in_displacement.y(),
          _maximum.z() - in_displacement.z() },
        { _maximum.x() - in_displacement.x(),
          _minimum.y() - in_displacement.y(),
          _maximum.z() - in_displacement.z() },
        { _minimum.x() - in_displacement.x(),
          _maximum.y() - in_displacement.y(),
          _maximum.z() - in_displacement.z() },
        { _maximum.x() - in_displacement.x(),
          _maximum.y() - in_displacement.y(),
          _maximum.z() - in_displacement.z() }
    };
    boolean negative = false;
    boolean positive = false;
    for ( integer i = 0; i < 8; i++ )
    {
        T side = (in_normal_plane.x() * corner[i][0])
               + (in_normal_plane.y() * corner[i][1])
               + (in_normal_plane.z() * corner[i][2]);
        if ( side < 0 )
        {
            negative = true;
            if ( positive )
            {
                return 0; // short-circuit
            }
        }
        else if ( side > 0 )
        {
            positive = true;
            if ( negative )
            {
                return 0; // short-circuit
            }
        }
    }
    if ( negative )
    {
        return -1;
    }
    else if ( positive )
    {
        return 1;
    }
    return 0;
}       

//--------------------------------------

}; // end of namespace geometry

//----------------------------------------------------------
// (end of file)
