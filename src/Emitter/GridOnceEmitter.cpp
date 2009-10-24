// Copyright (c) 2009, Pietje Bell <pietjebell@ana-chan.com>
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//     * Redistributions of source code must retain the above copyright
//       notice, this list of conditions and the following disclaimer.
//     * Redistributions in binary form must reproduce the above copyright
//       notice, this list of conditions and the following disclaimer in the
//       documentation and/or other materials provided with the distribution.
//     * Neither the name of the Pietje Bell Group nor the
//       names of its contributors may be used to endorse or promote products
//       derived from this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
// ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
// LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
// CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
// SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
// INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
// CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
// POSSIBILITY OF SUCH DAMAGE.


///////////
// Headers
#include "GridOnceEmitter.h"

#include "..\ParticleArray.h"
#include "..\Particle.h"


////////////////////////////////////////
// Constructor
GridOnceEmitter::GridOnceEmitter( double p_density, double p_diameter, 
                                  double p_velocity, const string &dimensions, 
                                  double radius, double p_rate, int reset_particles ) :
    Emitter( p_density, p_diameter, p_velocity, dimensions, radius, p_rate, reset_particles )
{}


//////////////
// Destructor
GridOnceEmitter::~GridOnceEmitter() {}


////////////////////////////////////////
// Particle Property Generators (private)
Vector3d GridOnceEmitter::startPos( int p )
{
    // What variables are used in this function?

    /*
     * This function directly calculates the starting position from the
     * particle number; this comes in handy when resetting particles, if
     * they leave the cube, to the position they started;
     */
    int i = p / (( p_grid(1) ) * ( p_grid(2) ));
    int j = (p % (( p_grid(1) ) * ( p_grid(2) ))) / ( p_grid(2) + 1 );
    int k = p % ( p_grid(2) );

    return Vector3d( delimiter(0, 0) + i * dx,
                     delimiter(1, 0) + j * dy,
                     delimiter(2, 0) + k * dz );
}

Vector3d GridOnceEmitter::startVel( int p )
{
    return Vector3d( 0, 0, p_velocity );
}


////////////////////////////////////////
// Init, Update (public), Reset is default
void GridOnceEmitter::init( ParticleArray *particles )
{
    for ( int p = 0; p < p_N; p++ )
        particles->add( startPos( p ), startVel( p ), 0 );
}

void GridOnceEmitter::update( double relative_time, ParticleArray *particles )
{}