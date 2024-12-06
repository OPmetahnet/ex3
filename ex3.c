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
#define INIT_VALUE -1

char brands[NUM_OF_BRANDS][BRANDS_NAMES] = {"Toyoga", "HyunNight", "Mazduh", "FolksVegan", "Key-Yuh"};
char types[NUM_OF_TYPES][TYPES_NAMES] = {"SUV", "Sedan", "Coupe", "GT"};

void initCube(int cube[][NUM_OF_BRANDS][NUM_OF_TYPES], int days, int brands, int types) {
    for (int i = 0; i < days; i++) {
        for (int j = 0; j < brands; j++) {
            for (int k = 0; k < types; k++) {
                cube[i][j][k] = INIT_VALUE;
            }
        }
    }
}

void insertBrandData(int cube[][NUM_OF_BRANDS][NUM_OF_TYPES], int days, int brands, int types, int current_day, int brand_index, int daily_sum[]) {
    for(int j = 0; j < types; j++) {
        if(cube[current_day][brand_index][j] != INIT_VALUE) {
            printf("This brand is not valid\n");
            return;
        }
        cube[current_day][brand_index][j] = daily_sum[j];
    }
}

int checkIfThereIsMissingData(int cube[][NUM_OF_BRANDS][NUM_OF_TYPES], int days, int brands, int types, int current_day) {
    for(int i = 0; i < brands; i++) {
        if(cube[current_day][i][0] == INIT_VALUE) return 1;
    }
    return 0;
}

void printBrandName(int index) {
    printf("%s", brands[index]);
}

void printTypeName(int index) {
    printf("%s", types[index]);
}

void printMissingDataBrands(int cube[][NUM_OF_BRANDS][NUM_OF_TYPES], int days, int brands, int types, int current_day) {
    /*
     go over second dimension and see if any value has been set.
     Then, map it to the indicator array.
    */
    for(int i = 0; i < brands; i++) {
        if(cube[current_day][i][0] == INIT_VALUE) {
            printBrandName(i);
            printf(" ");
        }
        if(i == brands - 1) printf("\n");
    }
}

int calculateDailySum(int cube[][NUM_OF_BRANDS][NUM_OF_TYPES], int days, int brands, int types, int day_to_check) {
    int total_sum = 0;

    //sums each sale number into a grand total
    for(int i = 0; i < brands; i++) {
        for(int j = 0; j < types; j++) {
            total_sum += cube[day_to_check][i][j];
        }
    }

    return total_sum;
}

void printMaxDailyBrandSales(int cube[][NUM_OF_BRANDS][NUM_OF_TYPES], int days, int brands, int types, int day_to_check) {
    int daily_brand_sales[brands];
    int max_daily_brand_sales = 0, max_daily_brand_sales_index = 0;

    //init brand sales array with zeroes
    for(int i = 0; i < brands; i++) {
        daily_brand_sales[i] = 0;
    }

    //sum sales for each brand and store them in a matching index
    for(int i = 0; i < brands; i++) {
        for(int j = 0; j < types; j++) {
            daily_brand_sales[i] += cube[day_to_check][i][j];
        }

        //comparison to find the max sales value of the day per brand
        if(max_daily_brand_sales < daily_brand_sales[i]) {
            max_daily_brand_sales = daily_brand_sales[i];
            max_daily_brand_sales_index = i;
        }
    }

    //prints the data results
    printf("The best sold brand with %d sales was ", max_daily_brand_sales);
    printBrandName(max_daily_brand_sales_index);
    printf("\n");
}

void printMaxDailyTypeSales(int cube[][NUM_OF_BRANDS][NUM_OF_TYPES], int days, int brands, int types, int day_to_check) {
    int daily_type_sales[types];
    int max_daily_type_sales = 0, max_daily_type_sales_index = 0;

    //init type sales array with zeroes
    for(int i = 0; i < types; i++) {
        daily_type_sales[i] = 0;
    }

    //sum all type sales together into the daily type sales array
    for(int i = 0; i < brands; i++) {
        for(int j = 0; j < types; j++) {
            daily_type_sales[j] += cube[day_to_check][i][j];
        }
    }

    //find the max amount of daily sales by type
    for (int i = 0; i < types; i++) {
        if(max_daily_type_sales < daily_type_sales[i]) {
            max_daily_type_sales = daily_type_sales[i];
            max_daily_type_sales_index = i;
        }
    }

    //prints the data results
    printf("The best sold type with %d sales was ", max_daily_type_sales);
    printTypeName(max_daily_type_sales_index);
    printf("\n");
}

void printBrandSalesData(int cube[][NUM_OF_BRANDS][NUM_OF_TYPES], int days, int brands, int types, int brand_to_check, int current_day) {
    for(int i = 0; i < current_day; i++) {
        printf("Day %d- ", i + 1);
        for(int j = 0; j < types; j++) {
            printTypeName(j);
            printf(": %d ", cube[i][brand_to_check][j]);
        }
        printf("\n");
    }
}

void printAllSalesData(int cube[][NUM_OF_BRANDS][NUM_OF_TYPES], int days, int brands, int types, int current_day) {
    printf("*****************************************\n\n");

    //prints all data by brand
    for(int i = 0; i < brands; i++) {
        printf("Sales for ");
        printBrandName(i);
        printf(":\n");
        printBrandSalesData(cube, days, brands, types, i, current_day);
    }

    printf("*****************************************\n");
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

    //init cube to minus 1 (INIT_VALUE)
    initCube(cube, DAYS_IN_YEAR, NUM_OF_BRANDS, NUM_OF_TYPES);

    printMenu();

    scanf("%d", &choice);

    while(choice != done){
        switch(choice){

            /*
             insert daily sales data for each car type
            */
            case addOne: {
                int brand_index, daily_sum[NUM_OF_TYPES];

                //get input for data insertion
                printf("Enter brand index, 4 sales values: \n");
                scanf(("%d %d %d %d %d"), &brand_index, &daily_sum[0], &daily_sum[1], &daily_sum[2], &daily_sum[3]);

                //check the brand number's validity
                if(brand_index > NUM_OF_BRANDS - 1 || brand_index < 0) {
                    printf("This brand is not valid\n");
                    break;
                }

                //insert the data into the cube
                insertBrandData(cube, DAYS_IN_YEAR, NUM_OF_BRANDS, NUM_OF_TYPES ,day, brand_index, daily_sum);

                break;
            }

            /*
             inserts data for all brand types
            */
            case addAll: {
                int brand_index, daily_sum[NUM_OF_TYPES];

                //if data already exists
                if(checkIfThereIsMissingData(cube, DAYS_IN_YEAR, NUM_OF_BRANDS, NUM_OF_TYPES, day) == 0)
                    break;

                //get input for current day and insert it into the cube until its complete
                while(checkIfThereIsMissingData(cube, DAYS_IN_YEAR, NUM_OF_BRANDS, NUM_OF_TYPES, day) == 1) {
                    printf(("No data for brands "));
                    printMissingDataBrands(cube, DAYS_IN_YEAR, NUM_OF_BRANDS, NUM_OF_TYPES, day);
                    printf("Please complete the data\n");

                    scanf(("%d %d %d %d %d"), &brand_index, &daily_sum[0], &daily_sum[1], &daily_sum[2], &daily_sum[3]);

                    //check the brand number's validity
                    if(brand_index > NUM_OF_BRANDS - 1 || brand_index < 0) {
                        printf("This brand is not valid\n");
                        continue;
                    }

                    //insert the data into the cube
                    insertBrandData(cube, DAYS_IN_YEAR, NUM_OF_BRANDS, NUM_OF_TYPES, day, brand_index, daily_sum);
                }

                //if the data is complete for today - increase day counter by 1 and break
                day++;

                break;
            }

            /*
                prints daily sales statistics for a given day number
           */
            case stats: {
                int day_to_analyze = 0, daily_sales_sum;

                printf("What day would you like to analyze?\n");
                scanf("%d", &day_to_analyze);

                //get input until it's a number between 1 and 365(options for a day of the year)
                while(day_to_analyze > day || day_to_analyze < 1) {
                    printf("Please enter a valid day.\n"
                           "What day would you like to analyze?\n");
                    scanf("%d", &day_to_analyze);
                }

                daily_sales_sum = calculateDailySum(cube, DAYS_IN_YEAR, NUM_OF_BRANDS, NUM_OF_TYPES, day_to_analyze - 1);

                //print the results
                printf("In day number %d:\n"
                       "The sales total was %d\n"
                       ,day_to_analyze, daily_sales_sum);
                printMaxDailyBrandSales(cube, DAYS_IN_YEAR, NUM_OF_BRANDS, NUM_OF_TYPES, day_to_analyze - 1);
                printMaxDailyTypeSales(cube, DAYS_IN_YEAR, NUM_OF_BRANDS, NUM_OF_TYPES, day_to_analyze - 1);

                break;
            }

            /*
                print the data cube information day by day for every day that has sales data
            */
            case print: {
                printAllSalesData(cube, DAYS_IN_YEAR, NUM_OF_BRANDS, NUM_OF_TYPES, day);

                break;
            }

            default: {
                printf("Invalid input\n");

                break;
            }
        }
        printMenu();
        scanf("%d", &choice);
    }
    printf("Goodbye!\n");
    return 0;
}


