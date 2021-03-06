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
#include "ByteOutput.h"

#include "../Main.h" 
#include "../ParticleArray.h" 
#include "../Particle.h" 
#include "../Vortex/Vortex.h" 


///////////////
// Constructor
ByteOutput::ByteOutput( const Vortex3dParam &param, Vortex *the_vortex ) : 
                          Output( param, the_vortex ) 
{
    f = fopen( param.datafile.c_str(), "wb" );
}

//////////////
// Destructor
ByteOutput::~ByteOutput() 
{
    fclose( f );
}


void ByteOutput::printFileHeader() { 
}

void ByteOutput::printFileFooter() { 
}


// Trajectories
inline void ByteOutput::writeTrajectories( bool first_call, double time, const ParticleArray &particles )
{
    if ( first_call )
    {
        // Write the and delimiter values to file.
        // i.e. buf[] = { xmin, xmax, ymin, ymax, zmin, zmax }
        double buf[] = { delimiter(0, 0), delimiter(0, 1),
                         delimiter(1, 0), delimiter(1, 1),
                         delimiter(2, 0), delimiter(2, 1) };
        fwrite( buf, 8, 6, f );
    }

    // Write data
    for ( int i = 0; i < particles.getLength(); i++ )
        {
        // Readability
        const int & num = particles.getParticle( i ).getNum();
        const Vector3d & pos = particles.getParticle( i ).getPos();
        const double & speed = particles.getParticle( i ).speed();
        
        double buf[] = {time, (double)num, pos(0), pos(1), pos(2), speed };
        fwrite( buf, 8, 6, f );
    }
}

// Concentration
inline void ByteOutput::writeConcentration( bool first_call, double time, const ParticleArray &particles )
{
    if ( first_call )
    {
        // Write the time, and delimiter/grid values to file.
        // i.e. buf[] = { xmin, xstep, xmax, ymin, ystep, ymax, zmin, zstep, zmax, time }
        double buf[] = { delimiter(0, 0), grid(0), delimiter(0, 1), 
                         delimiter(1, 0), grid(1), delimiter(1, 1), 
                         delimiter(2, 0), grid(2), delimiter(2, 1), 
                         timestep };
        fwrite( buf, 8, 10, f );
    }

    ScalarField concentration( grid(0), grid(1), grid(2) );
    getConcentration( particles, &concentration );

    for ( int i = 0; i < grid(0); i++ )
    {
        for ( int j = 0; j < grid(1); j++ )
        {
            for ( int k = 0; k < grid(2); k++ )
            {
                double buf[] = { concentration(i,j,k) };
                fwrite( buf, 8, 1, f);
            }
        }
    }

}

// Velocity Field
inline void ByteOutput::writeVelocityField( bool first_call, double time )
{
    const VectorField &v = the_vortex->getVectorField();

    // Write the time, and delimiter/grid values to file.
    // i.e. buf[] = { time, xmin, xstep, xmax, ymin, ystep, ymax, zmin, zstep, zmax }
    double buf[] = { time, delimiter(0, 0), grid(0), delimiter(0, 1), 
                           delimiter(1, 0), grid(1), delimiter(1, 1), 
                           delimiter(2, 0), grid(2), delimiter(2, 1) };
    fwrite( buf, 8, 10, f );

    // Write the velocity values to file.
    for ( int i = 0; i < grid(0); i++ )
    {
        for ( int j = 0; j < grid(1); j++ )
        {
            for ( int k = 0; k < grid(2); k++ )
            {
                const Vector3d &vel = v(i, j, k);
                double buf[] = { vel(0), vel(1), vel(2) };
                fwrite( buf, 8, 3, f ); 
            }
        }
    }
}



