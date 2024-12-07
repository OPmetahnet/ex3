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

//puts INIT_VALUE in every cell of the cube
void initCube(int cube[][NUM_OF_BRANDS][NUM_OF_TYPES], int days, int brands, int types) {
    for (int i = 0; i < days; i++) {
        for (int j = 0; j < brands; j++) {
            for (int k = 0; k < types; k++) {
                cube[i][j][k] = INIT_VALUE;
            }
        }
    }
}

//checks if the current day's representation in the cube has data in it
int checkIfThereIsMissingData(int cube[][NUM_OF_BRANDS][NUM_OF_TYPES],int days, int brands, int current_day) {
    //prevent program from trying to add data after the last day of the year
    if(current_day == days) return 0;

    /*
     array was initialized to -1 at the start of the program so that we can check
     whether it had data inserted into it already
    */
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

//prints all brands with no sales data for given day(gets called for current day)
void printMissingDataBrands(int cube[][NUM_OF_BRANDS][NUM_OF_TYPES], int brands, int current_day) {
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

//sets the sales data in today's cube cells
void insertBrandData(int cube[][NUM_OF_BRANDS][NUM_OF_TYPES], int types, int current_day, int brand_index, int daily_sum[]) {
    for(int j = 0; j < types; j++) {
        if(cube[current_day][brand_index][j] != INIT_VALUE) {
            printf("This brand is not valid\n");
            return;
        }
        cube[current_day][brand_index][j] = daily_sum[j];
    }
}

//calculates daily sales sum for a given day
int calculateDailySum(int cube[][NUM_OF_BRANDS][NUM_OF_TYPES], int brands, int types, int day_to_check) {
    int total_sum = 0;

    //sums each sale number into a grand total
    for(int i = 0; i < brands; i++) {
        for(int j = 0; j < types; j++) {
            total_sum += cube[day_to_check][i][j];
        }
    }

    return total_sum;
}

//prints all sales data for a given brand
void printBrandSalesData(int cube[][NUM_OF_BRANDS][NUM_OF_TYPES], int types, int brand_to_check, int current_day) {
    for(int i = 0; i < current_day; i++) {
        printf("Day %d- ", i + 1);
        for(int j = 0; j < types; j++) {
            printTypeName(j);
            printf(": %d ", cube[i][brand_to_check][j]);
        }
        printf("\n");
    }
}

//prints all the sales data in the cube for each brand
void printAllSalesData(int cube[][NUM_OF_BRANDS][NUM_OF_TYPES], int brands, int types, int current_day) {
    printf("*****************************************\n");

    //prints all data by brand
    for(int i = 0; i < brands; i++) {
        printf("Sales for ");
        printBrandName(i);
        printf(":\n");
        printBrandSalesData(cube, types, i, current_day);
    }

    printf("*****************************************\n");
}

//returns highest selling brand index for a given day range
int findHighestSellingBrandOfDayRange(int cube[][NUM_OF_BRANDS][NUM_OF_TYPES], int brands, int types, int start_day, int end_day) {
    int daily_brand_sales[brands];
    int max_brand_sales = 0, max_brand_sales_index = 0;

    //init brand sales array with zeroes
    for(int i = 0; i < brands; i++) {
        daily_brand_sales[i] = 0;
    }

    //sum sales for each brand and store them in a matching index
    for(int k = start_day; k <= end_day; k++) {
        for(int i = 0; i < brands; i++) {
            for(int j = 0; j < types; j++) {
                daily_brand_sales[i] += cube[k][i][j];
            }

            //comparison to find the max sales value of the day range per brand
            if(max_brand_sales < daily_brand_sales[i]) {
                max_brand_sales = daily_brand_sales[i];
                max_brand_sales_index = i;
            }
        }
    }

    return max_brand_sales_index;
}

//returns highest amount of sales per brand for a given day range
int findHighestBrandSalesOfDayRange(int cube[][NUM_OF_BRANDS][NUM_OF_TYPES], int brands, int types, int start_day, int end_day) {
    int daily_brand_sales[brands];
    int max_brand_sales = 0;

    //init brand sales array with zeroes
    for(int i = 0; i < brands; i++) {
        daily_brand_sales[i] = 0;
    }

    //sum sales for each brand and store them in a matching index
    for(int k = start_day; k <= end_day; k++) {
        for(int i = 0; i < brands; i++) {
            for(int j = 0; j < types; j++) {
                daily_brand_sales[i] += cube[k][i][j];
            }

            //comparison to find the max sales value of the day range per brand
            if(max_brand_sales < daily_brand_sales[i]) {
                max_brand_sales = daily_brand_sales[i];
            }
        }
    }

    return max_brand_sales;
}

//returns the highest selling type for a given day range
int findHighestSellingTypeOfDayRange(int cube[][NUM_OF_BRANDS][NUM_OF_TYPES], int brands, int types, int start_day, int end_day) {
    int daily_type_sales[types];
    int max_type_sales = 0, max_type_sales_index = 0;

    //init type sales array with zeroes
    for(int i = 0; i < types; i++) {
        daily_type_sales[i] = 0;
    }

    //sum all type sales together into the type sales array
    for(int k = start_day; k <= end_day; k++) {
        for(int i = 0; i < brands; i++) {
            for(int j = 0; j < types; j++) {
                daily_type_sales[j] += cube[k][i][j];
            }
        }
    }

    //find the max amount of sales for the day range by type
    for (int i = 0; i < types; i++) {
        if(max_type_sales < daily_type_sales[i]) {
            max_type_sales = daily_type_sales[i];
            max_type_sales_index = i;
        }
    }

    return max_type_sales_index;
}

//returns the highest amount of sales per type for a given day range
int findHighestTypeSalesOfDayRange(int cube[][NUM_OF_BRANDS][NUM_OF_TYPES], int brands, int types, int start_day, int end_day) {
    int daily_type_sales[types];
    int max_type_sales = 0;

    //init type sales array with zeroes
    for(int i = 0; i < types; i++) {
        daily_type_sales[i] = 0;
    }

    //sum all type sales together into the type sales array
    for(int k = start_day; k <= end_day; k++) {
        for(int i = 0; i < brands; i++) {
            for(int j = 0; j < types; j++) {
                daily_type_sales[j] += cube[k][i][j];
            }
        }
    }

    //find the max amount of sales for the day range by type
    for (int i = 0; i < types; i++) {
        if(max_type_sales < daily_type_sales[i]) {
            max_type_sales = daily_type_sales[i];
        }
    }

    return max_type_sales;
}

//calculates the delta metric value of a given brand
float calculateBrandDeltaValue(int cube[][NUM_OF_BRANDS][NUM_OF_TYPES], int brand_to_check, int current_day) {
    float delta_value = 0;

    //run through all days until current day and calculate the delta sum for the brand
    for(int j = 1; j < current_day; j++) {
        for(int k = 0; k < NUM_OF_TYPES; k++) {
            //take the difference between each day and the day before it and add to delta
            delta_value += (float)cube[j][brand_to_check][k] - (float)cube[j - 1][brand_to_check][k];
        }
    }
    delta_value /= (float)current_day - 1;//completing the formula calculation

    return delta_value;
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

int findMostProfitableDay(int cube[][5][4], int brands, int types, int day) {
    int most_profitable_day = 0, max_daily_revenue = 0;

    for(int i = 0; i < day; i++) {
        int today_sum = calculateDailySum(cube, brands, types, i);

        if(max_daily_revenue < today_sum) {
            most_profitable_day = i;
        }
    }

    return most_profitable_day;
}

int findHighestDailyProfit(int cube[][NUM_OF_BRANDS][NUM_OF_TYPES], int brands, int types, int day) {
    int max_daily_revenue = 0;

    for(int i = 0; i < day; i++) {
        int today_sum = calculateDailySum(cube, brands, types, i);

        if(max_daily_revenue < today_sum) {
            max_daily_revenue = today_sum;
        }
    }

    return max_daily_revenue;
}

int main() {
    int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES];
    // int days[NUM_OF_BRANDS] = {0};
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
                insertBrandData(cube, NUM_OF_TYPES ,day, brand_index, daily_sum);

                break;
            }

            /*
             insert data for all brand types
            */
            case addAll: {
                int brand_index, daily_sum[NUM_OF_TYPES];

                //if data already exists
                if(checkIfThereIsMissingData(cube,DAYS_IN_YEAR, NUM_OF_BRANDS, day) == 0)
                    break;

                //get input for current day and insert it into the cube until its complete
                while(checkIfThereIsMissingData(cube,DAYS_IN_YEAR, NUM_OF_BRANDS, day) == 1) {
                    printf(("No data for brands "));
                    printMissingDataBrands(cube, NUM_OF_BRANDS, day);
                    printf("Please complete the data\n");

                    scanf(("%d %d %d %d %d"), &brand_index, &daily_sum[0], &daily_sum[1], &daily_sum[2], &daily_sum[3]);

                    //check the brand number's validity
                    if(brand_index > NUM_OF_BRANDS - 1 || brand_index < 0) {
                        printf("This brand is not valid\n");
                        continue;
                    }

                    //insert the data into the cube
                    insertBrandData(cube, NUM_OF_TYPES, day, brand_index, daily_sum);
                }

                //if the data is complete for today - increase day counter by 1 and break
                if(day < DAYS_IN_YEAR) day++;

                break;
            }

            /*
                print daily sales statistics for a given day number
           */
            case stats: {
                int day_to_analyze = 0;

                printf("What day would you like to analyze?\n");
                scanf("%d", &day_to_analyze);

                //get input until it's a number between 1 and 365(options for a day of the year)
                while(day_to_analyze > day || day_to_analyze < 1) {
                    printf("Please enter a valid day.\n"
                           "What day would you like to analyze?\n");
                    scanf("%d", &day_to_analyze);
                }

                //calculate the daily sales sum
                int daily_sales_sum = calculateDailySum(cube, NUM_OF_BRANDS, NUM_OF_TYPES, day_to_analyze - 1);

                //find the highest selling brand of the chosen day
                int max_brand_sales_index = findHighestSellingBrandOfDayRange(cube, NUM_OF_BRANDS, NUM_OF_TYPES, day_to_analyze - 1, day_to_analyze - 1);
                int max_brand_sales = findHighestBrandSalesOfDayRange(cube, NUM_OF_BRANDS, NUM_OF_TYPES, day_to_analyze - 1, day_to_analyze - 1);

                //find the highest selling type of the chosen day
                int max_type_sales_index = findHighestSellingTypeOfDayRange(cube, NUM_OF_BRANDS, NUM_OF_TYPES, day_to_analyze - 1, day_to_analyze - 1);
                int max_type_sales = findHighestTypeSalesOfDayRange(cube, NUM_OF_BRANDS, NUM_OF_TYPES, day_to_analyze - 1, day_to_analyze - 1);

                //print the total sales number
                printf("In day number %d:\n"
                       "The sales total was %d\n"
                       ,day_to_analyze, daily_sales_sum);

                //print the highest selling brand of the day
                printf("The best sold brand with %d sales was ", max_brand_sales);
                printBrandName(max_brand_sales_index);
                printf("\n");

                //print the highest selling type of the day
                printf("The best sold type with %d sales was ", max_type_sales);
                printTypeName(max_type_sales_index);
                printf("\n");

                break;
            }

            /*
                print the data cube information day by day for every day that has sales data
            */
            case print: {
                printAllSalesData(cube, NUM_OF_BRANDS, NUM_OF_TYPES, day);

                break;
            }

            /*
             provide business insights about the sales data
            */
            case insights: {
                //find the most profitable day
                int most_profitable_day = findMostProfitableDay(cube, NUM_OF_BRANDS, NUM_OF_TYPES, day);
                int highest_daily_profit = findHighestDailyProfit(cube, NUM_OF_BRANDS, NUM_OF_TYPES, day);

                //find the highest selling brand
                int max_sales_brand_index = findHighestSellingBrandOfDayRange(cube, NUM_OF_BRANDS, NUM_OF_TYPES, 0, day - 1);
                int max_sales_brand = findHighestBrandSalesOfDayRange(cube, NUM_OF_BRANDS, NUM_OF_TYPES, 0, day - 1);

                //find the highest selling type
                int max_sales_type_index = findHighestSellingTypeOfDayRange(cube, NUM_OF_BRANDS, NUM_OF_TYPES, 0, day - 1);
                int max_sales_type = findHighestTypeSalesOfDayRange(cube, NUM_OF_BRANDS, NUM_OF_TYPES, 0, day - 1);

                //print most sold brand overall
                printf("The best-selling brand overall is ");
                printBrandName(max_sales_brand_index);
                printf(": %d$\n", max_sales_brand);

                //print most sold type overall
                printf("The best-selling type of car is ");
                printTypeName(max_sales_type_index);
                printf(": %d$\n", max_sales_type);

                //print most profitable day
                printf("The most profitable day was day number %d: %d$\n", most_profitable_day - 1, highest_daily_profit);

                break;
            }

            /*
             calculate and print the delta metric for each brand's sales independently
            */
            case deltas: {
                float delta = 0;

                //run for each brand and go through all days with data
                for(int i = 0; i < NUM_OF_BRANDS; i++) {
                    delta = calculateBrandDeltaValue(cube, i, day);

                    //print data for user before next iteration
                    printf("Brand: ");
                    printBrandName(i);
                    printf(", Average Delta: %f\n", delta);

                    //reset before next iteration
                    delta = 0;
                }

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


