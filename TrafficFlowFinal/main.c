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

*/

// Amount of vehicles on road. Change to malloc for dynamic array
#define N 10
#define dt .01
// Architecture. No matrix to store the time steps of each car so that memory issues wont be a problem. Instead stored to a file.

int main()
{
    double vehTrack[N];

    // Block asks for user input. (How many cars, trucks?, position of trucks, speed changes

    // Block of code calculates the change in velocity of each vehicle per timestep

    // Block of code evaluates a crash?
}
