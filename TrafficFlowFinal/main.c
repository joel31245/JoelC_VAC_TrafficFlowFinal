#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "structVehicle.c"
//#include "omp.h"

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
      TODO: Need to find out how to put in seperation distance. Set up change in initial velocity of initial vehicle.

*/

// Amount of vehicles on road. Change to malloc for dynamic array
#define N 10
#define dt .01
#define tEnd 10
// Architecture. No matrix to store the time steps of each car so that memory issues wont be a problem. Instead stored to a file.



int main()
{
    struct Vehicle road[N];
    FILE *f = fopen("TrafficFlow.csv","w");
    short i=0, j=0; // loop counters
    float lambda = 1;

    //omp_set_num_threads(4); // Only got 4 CPUs on my laptop

    /// Block asks for user input. (How many cars, trucks?, position of trucks, speed change)
        // Setting up the initial velocity of the lead vehicle.
    road[0].v = 30;

        // Setting up lambda for each vehicle. Defaults to 1
    //#pragma omp parallel for private(lambda)
    for( i=0; i<N; i++ ){
        road[i].y = lambda;
    }


    /// Block of code calculates the change in velocity of each vehicle per timestep
        // dv/dj is 0 for this sections. NOTE Unable to parallelize
    float sizeT = (float)tEnd/dt;
    for( i=0; i<sizeT; i++ ){
        printf("t(%f):  ",i*dt); fprintf(f, "%f,",i*dt);
        for( j=1; j<N; j++ ){
            road[j].v = road[j-1].v;
            fprintf(f, "%f,",road[j].v); printf("%f  ",road[j].v);
        }
        fprintf(f, "\n"); printf("\n");
    }

    /// Block of code evaluates a crash?

    fclose(f);

    return 0;
}
