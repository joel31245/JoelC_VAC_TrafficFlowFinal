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
      - dv(j)/dt = y[v(j-1)(t) - v(j)(t)]   where y = lambda, a reaction time coefficient. In this application reaction time will be constant and not based on roadway conditions.
      - dv(j)/dt = v(j-1)(t') - v(j)(t')    where t' = y*t

      NOTE: MAX Decel is 23.87 ft/s^2 or 7.276 m/s^2
      TODO:  - Need to find out how to put in seperation distance. DEPENDS ON SPEED. FOR 30 m/s^s at 0.9 lambda its calculatable. Use computer to display min Sep Distance.
             - Put cap on speed
             - Build Test Cases and File Formatting

*/

// Architecture. No matrix to store the time steps of each car so that memory issues wont be a problem. Instead stored to a file.

struct Vehicle{
    float x;      //( Position of the front bumper. )
    float length; //( Used for crashes. )
    float v;
    float y;
};

float f(float v1,float y1,  float v0){ return y1*(v0-v1); }
float v(float v1) { return v1; }

float v0( float start0Vel, float v0, float dt, short flag );

int main()
{
    struct Vehicle *road, sizeOfVeh;
    FILE *inF = fopen("VehicleInfo.txt", "r");
    FILE *fvel = fopen("TrafficFlowVel.csv", "w");
    FILE *fpos = fopen("TrafficFlowPos.csv", "w");
    FILE *fcrash = fopen("CrashReport.txt", "w");
    short i=0, j=0;         // loop counters
    /// CONSTANTS
    float maxAccel = 7.276;
    /// INPUT VARS
    short vehAmt = 10;
    // Initial Vehicle Conditions (For now all the same, later on will change to have individual tendencies.
        float start0Vel;
        float initVel = 30;     // NOTE: All units in meters, meters/second, or meters per second squared
        float initSepDist = 200;
        float eachVehLength = 4.80;
        float lambda = .9;      // default all set to this lambda (>1 means everyone overreacts, <1 everyone under reacts, 1 everyone reacts perfectly to speed changes?)
    // Runtime Protocol
        short accelFlag = 1;    // Sets the first vehicle's runtime conditions. ( 0 - steady state, 1 - 30% increase in speed, 2 - 30% decrease in speed )
    // Time
        short tEnd = 10;        // End of time sample. Should not be too long as we are only doing specific cases.
        float dt = 1;
    /// OUTPUT VARS
    short crash = 0;        // Crash flag. Lets the output know that there was a crash.
    road = malloc( sizeof(sizeOfVeh)*vehAmt );
    float **velsP = malloc( sizeof(float)*(ceil(tEnd/dt)+1) );
    for( j=0; j<ceil(tEnd/dt)+1; j++ ){
        velsP[j] = malloc( sizeof(float)*vehAmt );
    }
    float **posP = malloc( sizeof(float)*(ceil(tEnd/dt)+1) );
    for( j=0; j<ceil(tEnd/dt)+1; j++ ){
        posP[j] = malloc( sizeof(float)*vehAmt );
    }



    //omp_set_num_threads(4); // Only got 4 CPUs on my laptop

    /// Block asks for user input. (How many cars, trucks?, position of trucks, speed change)
    //#pragma omp parallel for private(lambda)
    for( i=0; i<vehAmt; i++ ){
        road[i].y = lambda;
        road[i].v = initVel;                velsP[0][i] = initVel;
        road[i].x = -i*initSepDist;         posP[0][i] = -i*initSepDist;
        road[i].length = eachVehLength;
    }
    start0Vel = road[0].v;


    /// Block of code calculates the change in velocity of each vehicle per timestep
        // dv/dj is 0 for this sections (STEADY STATE). NOTE Unable to parallelize
    float vNew, vStar, vStar2, vStar3; //Temporary vars for velocity
    float xNew, xStar, xStar2, xStar3;
    float t;
    j=1;
    for( t=dt; t<tEnd+dt; t+=dt ){
        // Setting the initial (first car to an initial acceleration)

        velsP[j][0] = v0( start0Vel, velsP[j-1][0], dt, accelFlag);
        vNew = ( velsP[j][0]-velsP[j-1][0] )/2;
        // WORKS FOR CONSTANT ACCELERATION. IS THE ANALYTICAL SOLUTION.
        if( velsP[j][0]-velsP[j-1][0] > 0 ) posP[j][0] = ( velsP[j-1][0]+vNew )*dt + posP[j-1][0];
        else if( velsP[j][0]-velsP[j-1][0] < 0 ) posP[j][0] = ( velsP[j-1][0]-vNew )*dt + posP[j-1][0];
        else posP[j][0] = ( velsP[j][0] )*dt + posP[j-1][0];

        // Setting the rest of the cars
        for( i=1; i<vehAmt; i++ ){
            vStar = velsP[j-1][i] + dt/2*f(velsP[j-1][i],road[i].y, velsP[j][i-1]);
            xStar = posP[j-1][i] + dt/2*v(velsP[j-1][i]);

            vStar2 = velsP[j-1][i] + dt/2*f(vStar,road[i].y, velsP[j][i-1]);
            xStar2 = posP[j-1][i] + dt/2*v(vStar);

            vStar3 = velsP[j-1][i] + dt*f(vStar2,road[i].y, velsP[j][i-1]);
            xStar3 = posP[j-1][i] + dt/2*v(vStar2);

            vNew = velsP[j-1][i]+dt/6*( f(velsP[j-1][i],road[i].y, velsP[j][i-1]) + 2*f(vStar,road[i].y, velsP[j][i-1]) +
                                    2*f(vStar2,road[i].y, velsP[j][i-1]) +   f(vStar3,road[i].y, velsP[j][i-1]) );
            xNew = posP[j-1][i]+dt/6*( v(velsP[j-1][i]) + 2*v(vStar) + 2*v(vStar2) + v(vStar3) );

            // Check max acceleration
            if( fabs(vNew-velsP[j-1][i])/dt > maxAccel ){
                if( (vNew-velsP[j-1][i])/dt > 0 ){
                    vNew = maxAccel*dt + velsP[j-1][i];
                }
                else {
                    vNew = -maxAccel*dt + velsP[j-1][i];
                }
            }
            // Check for crash
            if(   (posP[j][i-1] - xNew) < road[i-1].length   ){
                crash = 1;
                break;
            }

            velsP[j][i] = vNew; posP[j][i] = xNew;
            road[i].v = vNew; road[i].x = xNew;
        }
        if( crash != 0 ){ break;  }
        j++;
    }
    printf("\n\n\n\n\n");


    if( crash == 0 ){
        fprintf(fcrash, "CLEAR - No incidents to report.");
    }
    else{
        fprintf(fcrash, "ACCIDENT - Time(%2.2f)\nVehicles: %d and %d\nCollision Speed: %f", t,  i,i-1,  fabs(vNew-velsP[j][i-1]) );
    }

    /// Printing to a file and print sequence.
    t = 0.00;
    for( j=0; j<(ceil(tEnd/dt)+1); j++ ){
        printf("(BLOCKTime: %2.2f)  ", t );
        for( i=0; i<vehAmt; i++ ){
            fprintf(fvel, "%f,",velsP[j][i] );
            fprintf(fpos, "%f,",posP[j][i] );
            printf("(%d) %2.2f (XXXX) %2.2f   ", i,velsP[j][i],posP[j][i] );
        }
        printf("\n\n\n"); fprintf(fvel, "\n"); fprintf(fpos,"\n");
        t+=dt;
    }


    fclose(fvel);
    fclose(fpos);
    fclose(fcrash);
    free(road);
    free(velsP);
    free(posP);

    return 0;
}


float v0( float start0Vel, float v0, float dt, short accelFlag ){
    /// Steady State, Acceleration = 0
    if( accelFlag == 0 ){
        return v0;
    }

        // Optional HOWEVER, ENCROACHING ON NICO'S PROJECT. Suggested by Dr Prosperreti, use a function (specifically tanh) to model this acceleration
    else if( accelFlag != 0 ){
        float vDiff = start0Vel*1.3 - start0Vel;
        if( fabs(v0-start0Vel) < fabs(start0Vel*1.3-start0Vel) ){
            vDiff = vDiff/.5*dt; // Acceleration.
        }
        else vDiff = 0;
//        printf("Accel: %f\n", vDiff);

    /// UNSTEADY, Acceleration Speed Up 30% over .5 a second
        if ( accelFlag == 1) return v0+vDiff;
    /// UNSTEADY, Acceleration Slow Down 30%
        else if ( accelFlag == 2) return v0-vDiff;
    }

}
