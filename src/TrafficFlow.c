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
      TODO:  - Need to find out how to put in seperation distance. Set up change in initial velocity of initial vehicle.
             - CHECK EQUATION FOR ACCURACY l46
             - NEED THE MATHEMATICAL SOLUTION FOR THE 1st CAR l82
*/

// Amount of vehicles on road. Change to malloc for dynamic array
#define N 10
#define dt 1.0
#define tEnd 10
// Architecture. No matrix to store the time steps of each car so that memory issues wont be a problem. Instead stored to a file.

struct Vehicle{
    float v;
    float y;
};

float f(float v1,float y1,  float v0){
    return y1*(v0-v1);
}
float v0( float v0, short flag );

int main()
{
    struct Vehicle road[N];
    FILE *fvel = fopen("TrafficFlow.csv","w");
    short i=0, j=0; // loop counters
    float lambda = .9; // default all set to this lambda (>1 means everyone overeacts, <1 everyone underreacts, 1 everyone reacts perfectly?)

    //omp_set_num_threads(4); // Only got 4 CPUs on my laptop

    /// Block asks for user input. (How many cars, trucks?, position of trucks, speed change)
        // Setting up the initial velocity of the lead vehicle.
    //printf(" %d\n ", road[0].v);
        // Setting up lambda for each vehicle. Defaults to 1
    //#pragma omp parallel for private(lambda)
    for( i=0; i<N; i++ ){
        road[i].y = lambda;
        road[i].v = 30 ;

    }
    road[0].v = 30;


    /// Block of code calculates the change in velocity of each vehicle per timestep
        // dv/dj is 0 for this sections (STEADY STATE). NOTE Unable to parallelize
    float sizeT = (float)tEnd/dt;
//    for( i=0; i<sizeT; i++ ){
//        printf("t(%f):  ",i*dt); fprintf(f, "%f,",i*dt);
//        for( j=1; j<N; j++ ){
//            road[j].v = road[j-1].v;
//            fprintf(f, "%f,",road[j].v); printf("%f  ",road[j].v);
//        }
//        fprintf(f, "\n"); printf("\n");
//    }
        // For non steady state need the first vehicle to change according to conditions. ALl others Runge-Kutta

    float vNew, vStar, vStar2, vStar3; //Temporary vars
    float t;
    for( t=0; t<tEnd+dt; t+=dt ){
        // Setting the initial (first car to an initial acceleration)
        road[0].v = v0( road[0].v, 0);
        printf("(Time: %2.2f) (%d) %f   ", t,0, road[0].v );
        // Setting the rest of the cars
        for( i=1; i<N; i++ ){
            vStar = road[i].v + dt/2*f(road[i].v,road[i].y, road[i-1].v);
            vStar2 = road[i].v + dt/2*f(vStar,road[i].y, road[i-1].v);
            vStar3 = road[i].v + dt*f(vStar2,road[i].y, road[i-1].v);
            vNew = road[i].v+dt/6*( f(road[i].v,road[i].y, road[i-1].v) + 2*f(vStar,road[i].y, road[i-1].v) +
                                     2*f(vStar2,road[i].y, road[i-1].v) +   f(vStar3,road[i].y, road[i-1].v) );

            // Check max acceleration


            road[i].v = vNew;
            printf("(%d) %f   ", i,vNew );
        }
        printf("\n\n\n");
    }


    /// Block of code tests and evaluates a crash?


    fclose(fvel);

    return 0;
}


float v0( float v0, short flag ){
    /// Steady State, Acceleration = 0
    if( flag == 0 ){
        return v0;
    }
}
