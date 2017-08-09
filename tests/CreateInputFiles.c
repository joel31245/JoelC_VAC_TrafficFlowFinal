#include <stdio.h>
#include <string.h>

int alterParam(char fileName[100], short program, char param[100], float minbnd, float stpsz, float maxbnd );

int main(){

    char fileName[100];
    char param[100];
    float minbnd, stpsz, maxbnd; short invalidBounds = 1;
    short program;
    char strnum[100];
    char continu = 'y';
    short checkParam = 0;

    while( continu == 'y' ){
        printf("Please Give a file name for this set of input data: ");
        scanf(" %s", &fileName);

        printf("Which parameter to alter? (Meant to alter only 1)\n");
        printf("(tEnd, dt, runtimeProtocolFlag, amountOfVehicles, lambda, vehicleLength, initSepDist, initialVelocity\n");

        scanf(" %s", &param);

        while(invalidBounds == 1 ){
            printf("Please Specify range you want the parameter to go between. (min bound, step size, max bound)");
            scanf(" %f, %f, %f", &minbnd, &stpsz, &maxbnd);
                // error message
            if( minbnd+stpsz < maxbnd ) invalidBounds = 0;
        }
        printf("Which Program? \n(0 - Steady State\n 1 - Accelerate 30\%\n 2 - Decelerate 30\%\n 3 - Accelerate From Rest \n 4 - Decelerate To Rest)\n");
        scanf("%d", &program);
        strcat(fileName, "_"); sprintf(strnum, "%d", program); strcat(strnum,"Program"); strcat(fileName, strnum);
        strcat(fileName, "_"); strcat(fileName, param);
        strcat(fileName, "_"); sprintf(strnum, "%2.2f", minbnd); strcat(fileName, strnum);
        strcat(fileName, "_"); sprintf(strnum, "%2.2f", stpsz); strcat(fileName, strnum);
        strcat(fileName, "_"); sprintf(strnum, "%2.2f", maxbnd); strcat(fileName, strnum);
        strcat(fileName, ".txt");

        checkParam = alterParam(fileName, program, param, minbnd, stpsz, maxbnd);

        if( checkParam == 1 ){
            printf("The Parameter you inputed is not correct. Would you like the application to restart and try again? (y/n) ");
            scanf(" %c", &continu);
        }
        else if( checkParam == 0 ){
            printf("The files have been made! Would you like to do this again? (y/n) ");
            scanf(" %c", &continu);
        }
        else { continu == 'n'; } // Safety to prevent infinite loops if the function fails to send a 0 or 1

    }

    printf("Have a nice day! Program terminating... \n\n");

    return 0;
}

int alterParam(char fileName[100], short program, char param[100], float minbnd, float stpsz, float maxbnd ){
    float i, j; /* loop counters */
    FILE *f = fopen(fileName, "w");

    short tEnd = 50;
    float dt = .1;
    short amtVeh = 10;
    float y = 0.9;
    float vLen = 4.80;
    float sepD = 200.0;
    float iniV = 30.0;

    /// tEnd Range.
    if( strcmp(param, "tEnd") == 0 ){
        // Check if bounds make sense
        if( (short) stpsz < 0 ) stpsz = -stpsz;
        else if( (short) stpsz == 0 ) stpsz = 1;
        if( (short) minbnd <= 0) minbnd = stpsz;

        for( i=(short)minbnd; i<=(short)maxbnd; i+=(short)stpsz ){
            fprintf(f, "%d, %f, %d, %d,\n", i,dt, program, amtVeh);
            for( j=0; j<amtVeh; j+=1 ){
                if( j != amtVeh-1 )     fprintf(f, "%f, 4.80, 200, 30,\n",y, vLen, sepD, iniV);
                else                    fprintf(f, "%f, 4.80, 200, 30",y, vLen, sepD, iniV);
            }
        }
        fclose(f);
        return 0;
    }/// END OF tEnd
    /// dt
    if( strcmp(param, "dt") == 0 ){
        // Check if bounds make sense
        if(  stpsz < 0 ) stpsz = -stpsz;
        else if(  stpsz == 0 ) stpsz = .1;
        if(  minbnd <= 0) minbnd = stpsz;

        for( i=minbnd; i<=maxbnd; i+=stpsz ){
            fprintf(f, "%d, %f, %d, %d,\n", tEnd, i,program, amtVeh);
            for( j=0; j<amtVeh; j+=1 ){
                if( j != amtVeh-1 )     fprintf(f, "%f, 4.80, 200, 30,\n",y, vLen, sepD, iniV);
                else                    fprintf(f, "%f, 4.80, 200, 30",y, vLen, sepD, iniV);
            }
        }
        fclose(f);
        return 0;
    }/// END OF dt
    /// amtVeh
    if( strcmp(param, "amountOfVehicles") == 0 ){
            // Check if bounds make sense
        if( (short) stpsz < 0 ) stpsz = -stpsz;
        else if( (short) stpsz == 0 ) stpsz = 1;
        if( (short) minbnd <= 0) minbnd = stpsz;

        for( i=(short)minbnd; i<=(short)maxbnd; i+=(short)stpsz ){
            fprintf(f, "%d, %f, %d, %d,\n", tEnd, dt, program, i);
            for( j=0; j<i; j+=1 ){
                if( j != amtVeh-1 )     fprintf(f, "%f, 4.80, 200, 30,\n",y, vLen, sepD, iniV);
                else                    fprintf(f, "%f, 4.80, 200, 30",y, vLen, sepD, iniV);
            }
        }
        fclose(f);
        return 0;
    }/// END OF amtVeh

    /// Lambda
    if( strcmp(param, "lambda") == 0 ){
        if(  stpsz < 0 ) stpsz = -stpsz;
        else if(  stpsz == 0 ) stpsz = .1;
        if(  minbnd <= 0) minbnd = stpsz;

        for( i=minbnd; i<=maxbnd; i+=stpsz ){
            fprintf(f, "%d, %f, %d, %d,\n", tEnd, dt, program, amtVeh);
            for( j=0; j<amtVeh; j+=1 ){
                if( j != amtVeh-1 )     fprintf(f, "%f, 4.80, 200.0, 30.0,\n", i, vLen, sepD, iniV);
                else                    fprintf(f, "%f, 4.80, 200.0, 30.0", i, vLen, sepD, iniV);
            }
        }
        fclose(f);
        return 0;
    }/// END OF Lambda
    /// vehLength
    if( strcmp(param, "vehicleLength") == 0 ){
        if(  stpsz < 0 ) stpsz = -stpsz;
        else if(  stpsz == 0 ) stpsz = .1;
        if(  minbnd <= 0) minbnd = stpsz;

        for( i=minbnd; i<=maxbnd; i+=stpsz ){
            fprintf(f, "%d, %f, %d, %d,\n", tEnd, dt, program, amtVeh);
            for( j=0; j<amtVeh; j+=1 ){
                if( j != amtVeh-1 )     fprintf(f, "%f, %f, 200.0, 30.0,\n", y, i, sepD, iniV);
                else                    fprintf(f, "%f, %f, 200.0, 30.0", y, i, sepD, iniV);
            }
        }
        fclose(f);
        return 0;
    }/// END OF vehLength
    /// Seperation Distance
    if( strcmp(param, "initSepDist") == 0 ){
        if(  stpsz < 0 ) stpsz = -stpsz;
        else if(  stpsz == 0 ) stpsz = 9.60;
        if(  minbnd <= 0) minbnd = stpsz;

        for( i=minbnd; i<=maxbnd; i+=stpsz ){
            fprintf(f, "%d, %f, %d, %d,\n", tEnd, dt, program, amtVeh);
            for( j=0; j<amtVeh; j+=1 ){
                if( j != amtVeh-1 )     fprintf(f, "%f, 4.80, %f, 30.0,\n", y, vLen, i, iniV);
                else                    fprintf(f, "%f, 4.80, %f, 30.0", y, vLen, i, iniV);
            }
        }
        fclose(f);
        return 0;
    }/// END OF Seperation Distance
    /// Initial Velocity
    if( strcmp(param, "initialVelocity") == 0 ){
        if(  stpsz < 0 ) stpsz = -stpsz;
        else if(  stpsz == 0 ) stpsz = .1;
        if(  minbnd < 0) minbnd = stpsz;
        if(  minbnd > 45.0) minbnd = stpsz; if(maxbnd > 45) maxbnd = 45.0;

        for( i=minbnd; i<=maxbnd; i+=stpsz ){
            fprintf(f, "%d, %f, %d, %d,\n", tEnd, dt, program, amtVeh);
            for( j=0; j<amtVeh; j+=1 ){
                if( j != amtVeh-1 )     fprintf(f, "%f, 4.80, 200.0, %f,\n", y, vLen, sepD, i);
                else                    fprintf(f, "%f, 4.80, 200.0, %f", y, vLen, sepD, i);
            }
        }
        fclose(f);
        return 0;
    }/// END OF Initial Velocity

    fclose(f);
    return 1;
}
