#include <stdio.h>
#include <string.h>

void alterParam(char fileName[100], short program, char param[100], float minbnd, float stpsz, float maxbnd );

int main(){

    char fileName[100];
    printf("Please Give a file name for this set of input data: ");
    scanf(" %s", &fileName);
    strcat(fileName, ".txt");


    printf("Which parameter to alter? (Meant to alter only 1)\n");
    printf("(tEnd, dt, runtimeProtocolFlag, amount of Vehicles, lambda, vehicleLength, initialSeperationDistance, initiialVelocity\n");
    char param[100];
    scanf(" %s", &param);
    float minbnd, stpsz, maxbnd; invalidBounds = 1;
    while(invalidBounds == 1 ){
        printf("Please Specify range you want the parameter to go between. (min bound, step size, max bound)");
        scanf(" %f, %f, %f", minbnd,maxbnd, stpsz);
            // error message
        if( minbnd+stpsz < maxbnd ) invalidBounds = 0;
    }
    printf("Which Program? (0 - Steady State, 1 - Accelerate 30\%, 2 - Decelerate 30\%)\n");
    short program;
    scanf("%d", &program);
    strcat(fileName, "_"); strcat(fileName, "Program%d", program);
    strcat(fileName, "_"); strcat(fileName, param);
    strcat(fileName, "_"); strcat(fileName, "%2.2f", minbnd);
    strcat(fileName, "_"); strcat(fileName, "%2.2f", stpsz);
    strcat(fileName, "_"); strcat(fileName, "%2.2f", maxbnd);

    alterParam(fileName, program, param, minbnd, stpsz, maxbnd);


    return 0;
}

void alterParam(char fileName[100], short program, char param[100], float minbnd, float stpsz, float maxbnd ){
    float i, j; /* loop counters */
    FILE *f = fopen(fileName, "w");
    short amtVeh = 10;

    /// tEnd Range.
    if( strcmp(param, "tEnd") == 0 ){
        for( i=minbnd; i<=maxbnd; i+=stpsz ){
            fprintf(f, "%f, .01, %d, %d,\n", i,program, amtVeh);
            for( j=0; j<amtVeh; j+=1 ){
                if( j != amtVeh-1 )     fprintf(f, "0.9, 4.80, 200, 30,\n");
                else                    fprintf(f, "0.9, 4.80, 200, 30");

            }
        }
    }
}
