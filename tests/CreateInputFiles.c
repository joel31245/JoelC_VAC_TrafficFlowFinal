#include <stdio.h>
#include <string.h>

int alterParam(char fileName[100], short program, char param[100], float minbnd, float stpsz, float maxbnd );

int main(){

    char fileName[100];
    printf("Please Give a file name for this set of input data: ");
    scanf(" %s", &fileName);
    strcat(fileName, ".txt");


    printf("Which parameter to alter? (Meant to alter only 1)\n");
    printf("(tEnd, dt, runtimeProtocolFlag, amountOfVehicles, lambda, vehicleLength, initialSeperationDistance, initialVelocity\n");
    char param[100];
    scanf(" %s", &param);
    float minbnd, stpsz, maxbnd; short invalidBounds = 1;
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

int alterParam(char fileName[100], short program, char param[100], float minbnd, float stpsz, float maxbnd ){
    float i, j; /* loop counters */
    FILE *f = fopen(fileName, "w");
    short amtVeh = 10;

    /// tEnd Range.
    if( strcmp(param, "tEnd") == 0 ){
        // Check if bounds make sense
        if( (short) stpsz < 0 ) stpsz = -stpsz;
        else if( (short) stpsz == 0 ) stpsz = 1;
        if( (short) minbnd <= 0) minbnd = sptsz;

        for( i=(short)minbnd; i<=(short)maxbnd; i+=(short)stpsz ){
            fprintf(f, "%d, .01, %d, %d,\n", i,program, amtVeh);
            for( j=0; j<amtVeh; j+=1 ){
                if( j != amtVeh-1 )     fprintf(f, "0.9, 4.80, 200, 30,\n");
                else                    fprintf(f, "0.9, 4.80, 200, 30");
            }
        }
        return 0;
    }/// END OF tEnd
    /// dt
    if( strcmp(param, "dt") == 0 ){
        // Check if bounds make sense
        if(  stpsz < 0 ) stpsz = -stpsz;
        else if(  stpsz == 0 ) stpsz = .1;
        if(  minbnd <= 0) minbnd = sptsz;

        for( i=minbnd; i<=maxbnd; i+=stpsz ){
            fprintf(f, "10, %f, %d, %d,\n", i,program, amtVeh);
            for( j=0; j<amtVeh; j+=1 ){
                if( j != amtVeh-1 )     fprintf(f, "0.9, 4.80, 200, 30,\n");
                else                    fprintf(f, "0.9, 4.80, 200, 30");
            }
        }
        return 0;
    }/// END OF dt
    /// amtVeh
    if( strcmp(param, "amountOfVehicles") == 0 ){
            // Check if bounds make sense
        if( (short) stpsz < 0 ) stpsz = -stpsz;
        else if( (short) stpsz == 0 ) stpsz = 1;
        if( (short) minbnd <= 0) minbnd = sptsz;

        for( i=(short)minbnd; i<=(short)maxbnd; i+=(short)stpsz ){
            fprintf(f, "10, .01, %d, %d,\n", program, i);
            for( j=0; j<i; j+=1 ){
                if( j != amtVeh-1 )     fprintf(f, "0.9, 4.80, 200, 30,\n");
                else                    fprintf(f, "0.9, 4.80, 200, 30");
            }
        }
        return 0;
    }/// END OF amtVeh

    /// Lambda
    if( strcmp(param, "lambda") == 0 ){
        if(  stpsz < 0 ) stpsz = -stpsz;
        else if(  stpsz == 0 ) stpsz = .1;
        if(  minbnd <= 0) minbnd = sptsz;

        for( i=minbnd; i<=maxbnd; i+=stpsz ){
            fprintf(f, "10, .01, %d, %d,\n", program, amtVeh);
            for( j=0; j<amtVeh; j+=1 ){
                if( j != amtVeh-1 )     fprintf(f, "%f, 4.80, 200.0, 30.0,\n", i);
                else                    fprintf(f, "%f, 4.80, 200.0, 30.0", i);
            }
        }
        return 0;
    }/// END OF Lambda
    /// vehLength
    if( strcmp(param, "vehicleLength") == 0 ){
        if(  stpsz < 0 ) stpsz = -stpsz;
        else if(  stpsz == 0 ) stpsz = .1;
        if(  minbnd <= 0) minbnd = sptsz;

        for( i=minbnd; i<=maxbnd; i+=stpsz ){
            fprintf(f, "10, .01, %d, %d,\n", program, amtVeh);
            for( j=0; j<amtVeh; j+=1 ){
                if( j != amtVeh-1 )     fprintf(f, "0.9, %f, 200.0, 30.0,\n", i);
                else                    fprintf(f, "0.9, %f, 200.0, 30.0", i);
            }
        }
        return 0;
    }/// END OF vehLength
    /// Seperation Distance
    if( strcmp(param, "initialSeperationDistance") == 0 ){
        if(  stpsz < 0 ) stpsz = -stpsz;
        else if(  stpsz == 0 ) stpsz = 9.60;
        if(  minbnd <= 0) minbnd = sptsz;

        for( i=minbnd; i<=maxbnd; i+=stpsz ){
            fprintf(f, "10, .01, %d, %d,\n", program, amtVeh);
            for( j=0; j<amtVeh; j+=1 ){
                if( j != amtVeh-1 )     fprintf(f, "0.9, 4.80, %f, 30.0,\n", i);
                else                    fprintf(f, "0.9, 4.80, %f, 30.0", i);
            }
        }
        return 0;
    }/// END OF Seperation Distance
    /// Initial Velocity
    if( strcmp(param, "initialVelocity") == 0 ){
        if(  stpsz < 0 ) stpsz = -stpsz;
        else if(  stpsz == 0 ) stpsz = .1;
        if(  minbnd < 0) minbnd = sptsz;
        if(  minbnd > 45.0) minbnd = sptsz; if(maxbnd > 45) maxbnd = 45.0;

        for( i=minbnd; i<=maxbnd; i+=stpsz ){
            fprintf(f, "10, .01, %d, %d,\n", program, amtVeh);
            for( j=0; j<amtVeh; j+=1 ){
                if( j != amtVeh-1 )     fprintf(f, "0.9, 4.80, 200.0, %f,\n", i);
                else                    fprintf(f, "0.9, 4.80, 200.0, %f", i);
            }
        }
        return 0;
    }/// END OF Initial Velocity
    else return 1;
}
