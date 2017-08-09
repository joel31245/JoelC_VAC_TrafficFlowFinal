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
    float length; //( Used for crashes. )
    float y;
    // COULD HAVE SPEED, AND ACCELERATION CAPS IN HERE
};

/// CALCULATION SPECIFIC FUNCTIONS
    float f(float v1,float y1,  float v0){ return y1*(v0-v1); }
    float v(float v1) { return v1; }
    // Method for different runtime conditions
    float v0( float start0Vel, float v0, float dt, short flag );


int main()
{
    struct Vehicle *road, sizeOfVeh;
    FILE *inpt = fopen("VehicleInfo.txt", "r");
    FILE *fvel = fopen("TrafficFlowVel.csv", "w");
    FILE *fpos = fopen("TrafficFlowPos.csv", "w");
    FILE *ferror = fopen("ProgramError.txt","w");
    FILE *fcrash = fopen("CrashReport.txt", "w");
    short i=0, j=0;         // loop counters
    /// CONSTANTS
    float maxAccel = 7.276;     // NOTE: Instead of constant across all cars change to make it car specific
    float maxSpeed = 49.174;
    /// INPUT VARS
    short vehAmt = 10;
    // Initial Vehicle Conditions (For now all the same, later on will change to have individual tendencies.
        float start0Vel;
        float initVel = 30;     // NOTE: All units in meters, meters/second, or meters per second squared
        float initSepDist = 200;// NOTE: Instead of constant across all cars, User will be able to change it.
        float eachVehLength = 4.80;
        float lambda = .9;      // default all set to this lambda (>1 means everyone overreacts, <1 everyone under reacts, 1 everyone reacts perfectly to speed changes?)
        float **velsP;
        float **posP;
    // Runtime Protocol
        short accelFlag = 1;    // Sets the first vehicle's runtime conditions. ( 0 - steady state, 1 - 30% increase in speed, 2 - 30% decrease in speed )
        short crash = 0;        // Crash flag. Lets the output know that there was a crash.
    // Time
        short tEnd = 10;        // End of time sample. Should not be too long as we are only doing specific cases.
        float dt = 1;

    /// READING IN INPUT (How many cars, trucks?, position of trucks, speed change)
    if( inpt == NULL ){ printf("Error Reading File. Possibly empty File."); fprintf(ferror, "Error Reading File. Possibly empty File."); return 1; }
    else{
        // Time
            fscanf(inpt, "%d,", &tEnd);
                if(tEnd <= 0 || tEnd > 1000000){
                                        printf("Invalid End Time Entry. Using a default value (10).\n");
                                        fprintf(ferror, "Error Reading File. Invalid End Time Entry. Using a default value (10).\n");
                                        tEnd = 10;
                                      }
            fscanf(inpt, "%f,", &dt);
                if(dt <= 0 || dt > tEnd/10){
                                        printf("Invalid Time Step Entry. Using a default value (0.01).\n");
                                        fprintf(ferror, "Error Reading File. Invalid Time Step Entry. Using a default value (0.01).\n");
                                        dt = 0.01;
                                      }
        // Runtime Protocol
            fscanf(inpt, "%d,", &accelFlag);
                if(accelFlag < 0 || accelFlag > 2){
                                        printf("Invalid RunTime Flag Entry. Using a default value (0 - Steady State).\n");
                                        fprintf(ferror, "Error Reading File. Invalid RunTime Flag Entry. Using a default value (0 - Steady State).\n");
                                        accelFlag = 0;
                                      }
                printf("Accel Flag: %d\n", accelFlag);
        // Vehicle Information
        float prevSepDist = 4.80;
        fscanf(inpt, "%d,", &vehAmt);
            if( vehAmt<0 ){
                    printf("Invalid Vehicle Amount Entered. Process Terminated.\n");
                    fprintf(ferror, "Error Reading File. Invalid Vehicle Amount Entered.");
                    return 2;
            }
            if( vehAmt==1){
                    printf("Entry making Program Run 1 Vehicle. NOTE: This is not a traffic flow problem.\n");
                    fprintf(ferror, "Error Reading File. Entry making Program Run 1 Vehicle. NOTE: This is not a traffic flow problem..\n");
            }


    /// OUTPUT VARS
        road = malloc( sizeof(sizeOfVeh)*vehAmt );
        velsP = malloc( sizeof(float)*(ceil(tEnd/dt)) );
        for( j=0; j<ceil(tEnd/dt); j++ ){
            velsP[j] = malloc( sizeof(float)*vehAmt );
        }
        posP = malloc( sizeof(float)*(ceil(tEnd/dt)) );
        for( j=0; j<ceil(tEnd/dt); j++ ){
            posP[j] = malloc( sizeof(float)*vehAmt );
        }


    /// READING IN EACH VEHICLE PARAMETERS
        for( i=0; i<vehAmt; i++ ){
            fscanf(inpt, "%f,", &lambda);
                if(lambda <= 0       ){ printf("Invalid Lambda Entry. Using a default value (4.80 m).\n");
                                        fprintf(ferror, "Error Reading File. Invalid Lambda Entry. Using a default value (0.90 m).\n");
                                        lambda = 0.9;
                                      }
                road[i].y = lambda;
            fscanf(inpt, "%f,", &eachVehLength);
                if(eachVehLength <= 0){ printf("Invalid Vehicle Length Entry. Using a default value (4.80 m).\n");
                                        fprintf(ferror, "Error Reading File. Invalid Vehicle Length Entry. Using a default value (4.80 m).\n");
                                        eachVehLength = 4.80;
                                      }
                road[i].length = eachVehLength;
            fscanf(inpt, "%f,", &initSepDist);
                if(i!=0 && initSepDist <= road[i-1].length){
                                        printf("Invalid Initial Seperation Distance Entry. Using a default value (200 m).\n");
                                        fprintf(ferror, "Error Reading File. Invalid Initial Seperation Distance Entry. Using a default value (200 m).\n");
                                        initSepDist = 200;
                                      }
                if(i==0) posP[0][0] = 0;
                else     posP[0][i] = posP[0][i-1] - initSepDist;
            fscanf(inpt, "%f,", &initVel);
                if(initVel >= maxSpeed || initVel <= -maxSpeed ){
                                        printf("Invalid Initial Speed Entry. Using a default value (30 m/s).\n");
                                        fprintf(ferror, "Error Reading File. Invalid Initial Speed Entry. Using a default value (30 m/s).\n");
                                        initVel = 30;
                                      }
                velsP[0][i] = initVel;
        }
    }


    //omp_set_num_threads(4); // Only got 4 CPUs on my laptop


    /// Block of code calculates the change in velocity of each vehicle per timestep
        // dv/dj is 0 for this sections (STEADY STATE). NOTE Unable to parallelize
    float vNew, vStar, vStar2, vStar3; //Temporary vars for velocity
    float xNew, xStar, xStar2, xStar3;
    float t;
    start0Vel = velsP[0][0];
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

            // Check for crash
            if(   (posP[j][i-1] - xNew) < road[i-1].length   ){
                crash = 1;
                break;
            }
            // Check max acceleration
            if( fabs(vNew-velsP[j-1][i])/dt > maxAccel ){
                if( (vNew-velsP[j-1][i])/dt > 0 ){
                    vNew = maxAccel*dt + velsP[j-1][i];
                }
                else {
                    vNew = -maxAccel*dt + velsP[j-1][i];
                }
            }
            // Check max Velocity
            if( velsP[j][i] > maxSpeed)       velsP[j][i] = maxSpeed;
            else if( velsP[j][i] < -maxSpeed) velsP[j][i] = -maxSpeedl


            velsP[j][i] = vNew; posP[j][i] = xNew;
        }
        if( crash != 0 ){ break;  }
        j++;
    }


    if( crash == 0 ){
        fprintf(fcrash, "CLEAR - No incidents to report.");
    }
    else{
        fprintf(fcrash, "ACCIDENT - Time(%2.2f)\nVehicles: %d and %d\nCollision Speed: %f", t,  i,i-1,  fabs(vNew-velsP[j][i-1]) );
    }

    /// Printing to a file and print sequence.
    t = 0.00;
    for( j=0; j<(ceil(tEnd/dt)); j++ ){
        printf("(Time: %2.2f)  ", t );
        for( i=0; i<vehAmt; i++ ){
            fprintf(fvel, "%f,",velsP[j][i] );
            fprintf(fpos, "%f,",posP[j][i] );
            printf("(%d) %2.2f (XXXX) %2.2f   ", i,velsP[j][i],posP[j][i] );
        }
        printf("\n\n\n");
        fprintf(fvel, "\n");
        fprintf(fpos,"\n");
        t+=dt;
    }


    fclose(fvel);
    fclose(fpos);
    fclose(fcrash);
    fclose(ferror);
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

    /// UNSTEADY, Acceleration Speed Up 30% over .5 a second
        if ( accelFlag == 1) return v0+vDiff;
    /// UNSTEADY, Acceleration Slow Down 30%
        else if ( accelFlag == 2) return v0-vDiff;
    }

}
