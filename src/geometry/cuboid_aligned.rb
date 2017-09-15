#  Copyright 1996-2012 (c) C.A.Thames

# Write code that represents 3D objects in space
# - to keep it real simple, only "rectangular cuboids."
# That way you could represent one by having an origin
# (z,y,x) and length, width, height. Of course,
# you should be able to create (initialize) an object
# at a certain origin, with a certain length/width/height.
# You should also be able to move your object to a different
# origin. Additionally, you should be able to get a list of
# the vertices that represent the cuboid (a total of 8 vertices). 

# Now here's the important part - write a method that tests
# whether or not 2 cuboids are overlapping. Bonus points:
# Allow your objects to rotate (to keep it simple, only at 90
# degree angles). The "tricky" part about the rotation is that
# - imagine the origin is walled - a rotation of an object that
# is up against a corner would also require the object to shift
# if you are rotating the object around its origin.
# This restriction exists because the objects are actually part
# of a bin packing algorithm - meaning the objects are inside a
# box and can only exist within the walls of the outer box. 

require 'matrix.rb'

class CuboidAligned

  attr_reader :minimum, :maximum

  X = 0
  Y = 1
  Z = 2

  def initialize( origin = [0.0,0.0,0.0], size = [1.0,1.0,1.0] )
    sizehalf = Vector.elements( size ) * 0.5
    @minimum = Vector.elements( origin ) - sizehalf
    @maximum = Vector.elements( origin ) + sizehalf
  end

  def size
    maximum - minimum
  end

  def size_half
    size * 0.5
  end

  def origin
    maximum - size_half
  end

  def vertices
    [[minimum[X],minimum[Y],minimum[Z]],
     [minimum[X],minimum[Y],maximum[Z]],
     [minimum[X],maximum[Y],minimum[Z]],
     [minimum[X],maximum[Y],maximum[Z]],
     [maximum[X],minimum[Y],minimum[Z]],
     [maximum[X],minimum[Y],maximum[Z]],
     [maximum[X],maximum[Y],minimum[Z]],
     [maximum[X],maximum[Y],maximum[Z]]]
  end

  def includes_point?( point )
    minimum[X] <= point[X] &&
    minimum[Y] <= point[Y] &&
    minimum[Z] <= point[Z] &&
    maximum[X] >= point[X] &&
    maximum[Y] >= point[Y] &&
    maximum[Z] >= point[Z] 
  end

  def overlaps_other?( other )
    minimum[X] < other.maximum[X] &&
    minimum[Y] < other.maximum[Y] &&
    minimum[Z] < other.maximum[Z] &&
    maximum[X] > other.minimum[X] &&
    maximum[Y] > other.minimum[Y] &&
    maximum[Z] > other.minimum[Z]
  end

  def envelope_point( point )
    if point[X] < minimum[X] then minimum[X] = point[X] end
    if point[Y] < minimum[Y] then minimum[Y] = point[Y] end
    if point[Z] < minimum[Z] then minimum[Z] = point[Z] end
    if point[X] > maximum[X] then maximum[X] = point[X] end
    if point[Y] > maximum[Y] then maximum[Y] = point[Y] end
    if point[Z] > maximum[Z] then maximum[Z] = point[Z] end
  end

  def translate( displacement )
    @maximum += displacement
    @minimum += displacement
  end

end

cuboids = [
  { origin: [ 1.0, 2.0, 3.0], size: [ 4.0, 5.0, 6.0]},
  { origin: [-3.0,-2.0,-1.0], size: [ 6.0, 5.0, 4.0]}
].map do |args|
  CuboidAligned.new( args[:origin], args[:size] )
end

sprintf_digits = "%6.1f"

cuboids.each_with_index do |c,i|
  puts "cuboid ##{i}:"
  puts "  origin: [#{sprintf_digits % c.origin[0]},#{sprintf_digits % c.origin[1]},#{sprintf_digits % c.origin[2]} ]"
  puts "  size:   [#{sprintf_digits % c.size[0]},#{sprintf_digits % c.size[1]},#{sprintf_digits % c.size[2]} ]"
  c.vertices.each_with_index do |v,iv|
    puts "  vert #{iv}: [#{sprintf_digits % v[0]},#{sprintf_digits % v[1]},#{sprintf_digits % v[2]} ]"
  end
  cuboids.each_with_index do |cc,ii|
    unless c.equal? cc
      if c.overlaps_other? cc
        puts "    OVERLAPS with other cuboid ##{ii}"
      end
    end
  end
end

# (eof)
