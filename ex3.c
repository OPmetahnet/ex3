/******************
Name: Oz Pinto
ID: 212320733
Assignment: ex3
*******************/

#include <stdio.h>

#define NUM_OF_BRANDS 5
#define BRANDS_NAMES 15
#define NUM_OF_TYPES 4
#define TYPES_NAMES 10
#define DAYS_IN_YEAR 365
#define addOne  1
#define addAll  2  
#define stats  3
#define print  4
#define insights  5
#define deltas  6
#define done  7

char brands[NUM_OF_BRANDS][BRANDS_NAMES] = {"Toyoga", "HyunNight", "Mazduh", "FolksVegan", "Key-Yuh"};
char types[NUM_OF_TYPES][TYPES_NAMES] = {"SUV", "Sedan", "Coupe", "GT"};

void initCube(int arr[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES]) {
    for (int i = 0; i < DAYS_IN_YEAR; i++) {
        for (int j = 0; j < NUM_OF_BRANDS; j++) {
            for (int k = 0; k < NUM_OF_TYPES; k++) {
                arr[i][j][k] = -1;
            }
        }
    }
}

void insertBrandData(int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES], int current_day, int brand_index, int daily_sum[]) {
    for(int j = 0; j < NUM_OF_TYPES; j++) {
        cube[current_day][brand_index][j] = daily_sum[j];
    }
}

int checkIfThereIsMissingData(int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES], int current_day) {
    for(int i = 0; i < NUM_OF_BRANDS; i++) {
        if(cube[current_day][i][0] == INIT_VALUE) return 1;
    }
    return 0;
}

void printMissingDataBrands(int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES], int current_day) {
    /*
     go over second dimension and see if any value has been set.
     Then, map it to the indicator array.
    */
    for(int i = 0; i < NUM_OF_BRANDS; i++) {
        if(cube[current_day][i][0] == INIT_VALUE) {
            printf("%s ", brands[i]);
        }
        if(i == NUM_OF_BRANDS - 1) printf("\n");
    }
}

void printMenu(){
    printf("Welcome to the Cars Data Cube! What would you like to do?\n"
           "1.Enter Daily Data For A Brand\n"
           "2.Populate A Day Of Sales For All Brands\n"
           "3.Provide Daily Stats\n"
           "4.Print All Data\n"
           "5.Provide Overall (simple) Insights\n"
           "6.Provide Average Delta Metrics\n"
           "7.exit\n");
}

int main() {
    int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES];
    int days[NUM_OF_BRANDS] = {0};
    int choice, day = 0;

    //init cube to minus 1
    initCube(cube);

    printMenu();
    scanf("%d", &choice);
    while(choice != done){
        switch(choice){

            //insert daily sales data for each car type
            case addOne: {
                int brand_index, daily_sum[NUM_OF_TYPES];

                //gets input accordingly
                printf("Enter brand index, 4 sales values: \n");
                scanf(("%d %d %d %d %d"), &brand_index, &daily_sum[0], &daily_sum[1], &daily_sum[2], &daily_sum[3]);

                //checks the brand number's validity
                if(brand_index > NUM_OF_BRANDS - 1 || brand_index < 0) {
                    printf("This brand is not valid\n");
                    break;
                }

                //insert the data into the cube
                insertBrandData(cube, day, brand_index, daily_sum);

                break;
            }

            //inserts data for all brand types
            case addAll:


                break;
            /*
             ......
             */
            default:
                printf("Invalid input\n");
        }
        printMenu();
        scanf("%d", &choice);
    }
    printf("Goodbye!\n");
    return 0;
}


