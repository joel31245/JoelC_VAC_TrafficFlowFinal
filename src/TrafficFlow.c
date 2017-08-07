#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/* Program Creates a single lane of traffic and evaluates
    what happens when their is an acceleration difference
    in the initial car and how that translates back to each
    driver. Each driver is assumed to react the exact same
    way.
    Applications: Automated Traffic on a single lane highway.

    Goals:
     - BASE GET base code in. Make everything variable.
        - Steady State Conditions ---> 30% increase in velocity
        - Steady State Conditions ---> 30% increase in velocity
        - From Standing (Rest)    ---> Initial Velocity
     - BASE GET acceleration based on distance between vehicles.
     - Be able to add in vehicles with different reaction parameters (like trucks and motorcycles)
     - Full Stop (A simulated light or reacting to a crash up ahead )
     - Minimum Separation Distance without crashing.
     - Write to a file
     - Display using Matlab or Paraview
     - Display using Animations on a PowerPoint

     Equations:
      - dv(j)/dt = y[v(j-1)(t) - v(j)(t)]   where y = lambda, a reaction time coefficient. In this application reaction time will be some constant
      - dv(j)/dt = v(j-1)(t') - v(j)(t')    where t' = y*t

      NOTE: MAX Decel is 23.87 ft/s2
      TODO:  - Need to find out how to put in seperation distance.

*/

// Amount of vehicles on road. Change to malloc for dynamic array
#define N 10
#define dt 1.0
#define tEnd 10
#define maxAccel 23.87
// Architecture. No matrix to store the time steps of each car so that memory issues wont be a problem. Instead stored to a file.

struct Vehicle{
    float x;      //( Position of the front bumper. )
    float length; //( Used for crashes. )
    float v;
    float y;
};

float f(float v1,float y1,  float v0){ return y1*(v0-v1); }
float v(float v1) { return v1; }

float v0( float v0, short flag );

int main()
{
    struct Vehicle road[N];
    FILE *fvel = fopen("TrafficFlow.csv","w");
    short i=0, j=0; // loop counters
    short crash = 0; // Crash flag. Lets the output know that there was a crash.
    float lambda = .9; // default all set to this lambda (>1 means everyone overreacts, <1 everyone under reacts, 1 everyone reacts perfectly to speed changes?)

    //omp_set_num_threads(4); // Only got 4 CPUs on my laptop

    /// Block asks for user input. (How many cars, trucks?, position of trucks, speed change)
    //#pragma omp parallel for private(lambda)
    for( i=0; i<N; i++ ){
        road[i].y = lambda;
        road[i].v = 30 ;
        road[i].x = -i*200.0;
        road[i].length = 4.80;
        printf(" %f\n", road[i].x);
    }
    road[0].v = 30;


    /// Block of code calculates the change in velocity of each vehicle per timestep
        // dv/dj is 0 for this sections (STEADY STATE). NOTE Unable to parallelize
    float vNew, vStar, vStar2, vStar3; //Temporary vars for velocity
    float xNew, xStar, xStar2, xStar3;
    float t;
    for( t=dt; t<tEnd+dt; t+=dt ){
        // Setting the initial (first car to an initial acceleration)
        road[0].v = v0( road[0].v, 0);
        road[0].x = road[0].v*dt + road[0].x;
        printf("(Time: %2.2f) (%d) %f (XXX) %f", t,0, road[0].v, road[0].x );
        // Setting the rest of the cars
        for( i=1; i<N; i++ ){
            vStar = road[i].v + dt/2*f(road[i].v,road[i].y, road[i-1].v);
            xStar = road[i].x + dt/2*v(road[i].v);

            vStar2 = road[i].v + dt/2*f(vStar,road[i].y, road[i-1].v);
            xStar2 = road[i].x + dt/2*v(vStar);

            vStar3 = road[i].v + dt*f(vStar2,road[i].y, road[i-1].v);
            xStar3 = road[i].x + dt/2*v(vStar2);

            vNew = road[i].v+dt/6*( f(road[i].v,road[i].y, road[i-1].v) + 2*f(vStar,road[i].y, road[i-1].v) +
                                    2*f(vStar2,road[i].y, road[i-1].v) +   f(vStar3,road[i].y, road[i-1].v) );
            xNew = road[i].x+dt/6*( v(road[i].v) + 2*v(vStar) + 2*v(vStar2) + v(vStar3) );

            // Check max acceleration
            if( fabs(vNew-road[i].v)/dt > maxAccel ){
                if( (vNew-road[i].v)/dt > 0 ){
                    vNew = maxAccel*dt + road[i].v;
                }
                else {
                    vNew = -maxAccel*dt + road[i].v;
                }
            }
            // Check for crash
            if( fabs(road[i-1].x - road[i].x < road[i-1].length ){
                crash = 1;
            }


            road[i].v = vNew; road[i].x = xNew;
            printf("(%d) %f (XXXX) %f   ", i,vNew,xNew );
        }
        printf("\n\n\n");
    }


    fclose(fvel);

    return 0;
}


float v0( float v0, short flag ){
    /// Steady State, Acceleration = 0
    if( flag == 0 ){
        return v0;
    }
}
