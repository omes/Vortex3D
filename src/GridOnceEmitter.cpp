#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include "Main.h"
#include "Emitter.h"
#include "Emitter.cpp"
#include "Particle.cpp"
#include <blitz/array.h>

using namespace std;
using namespace blitz;

class GridOnceEmitter : public Emitter {
protected:
    vector3d getStartPos(const int &p) {
        // What variables are used in this function?

        /* 
        * This function directly calculates the starting position from the
        * particle number; this comes in handy when resetting particles, if
        * they leave the cube, to the position they started;
        */
        int i = p/((p_grid(1))*(p_grid(2)));
        int j = ( p % ((p_grid(1))*(p_grid(2))) ) / (p_grid(2)+1);
        int k = p % (p_grid(2));

        return vector3d(delimiter(0,0)+i*dx,delimiter(1,0)+j*dy,delimiter(2,0)+k*dz);
    }

    vector3d getStartVel(const int &p) {
        return vector3d(0,0,p_velocity);
    }
public:
    GridOnceEmitter(const double &p_density, const double &p_diameter, const double &p_velocity, const string &dimensions, const double &radius, const double &p_rate, const int &reset_particles) : Emitter(p_density, p_diameter, p_velocity, dimensions, radius, p_rate, reset_particles) {    // "[double:int:double,double:int:double,double:int:double] <-- relative to R_v
    }

    virtual void init(ParticleArray *particles) {
        for (int p = 0; p < p_N; p++) {
            particles->add( getStartPos(p), getStartVel(p), 0 );
        }
    }

    virtual void update(const double &relative_time, ParticleArray *particles) {
    }

};