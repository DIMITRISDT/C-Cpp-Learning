#include <stdio.h>
#include <stdbool.h>
#include <string.h>


//Average grade calculation
float Average_Grade (int i, int n, float grades[n][3]) { //4
    float sum_for_AG = 0.0; //sum for the grades of one student. 
    for (int j = 0; j<3; j++) {
        sum_for_AG += grades[i][j];
    }
    return sum_for_AG /3;
}
//Category letter grade calculation
char Category_For_Average_Grade(int i, float AG[i]) {
    if (AG[i] >= 9.0) {
        return 'A';
    }
    else if (AG[i] >= 8.0) {
        return 'B';
    }
    else if (AG[i] >= 7.0) {
        return 'C';
    }
    else if (AG[i] >= 5.0) {
        return 'D';
    }
    else {
        return 'F';
    }
} 
// Display students
void Display_Students(int n, char name[n][50], int age[n], float grades[n][3], float AG[n], char letter_Grade[n]) {
    printf("_-_-_-{STUDENTS INFORMATION}-_-_-_\n");
    for (int i=0; i<n; ++i) {
        //name
        printf("[Name : %s", *(name+i));
        //age
        printf(" - Age : %d", *(age+i));
        //grades
        for (int j = 0; j<3; ++j) {
            printf(" - Grade %d : %.1f / ", j+1, grades[i][j]);
        }
        //average grade
        printf(" - Average Grade : %.1f", *(AG+i));
        //letter grade;
        printf(" - Letter Grade : %c]\n", *(letter_Grade+i));
    }
    printf("\n"); //space
}

int main() {
    int i, j ,n; //riser for loops, n = number of students

    printf("Type the number of the students: ");                //1
    scanf("%d", &n);
    
    int age[n]; // age of the students,
    char name[n][50], Letter_Grade[n]; // the name of a single student if the students are n.
    float grades[n][3], AG[n]; // each student has 3 grades,  AG = average grade

    i = 0;                                                      //2
    while (i < n) {
        printf("Type your name: ");
        getchar();
        fgets(name[i], 50, stdin);
        printf("Type your age: ");
        scanf("%d", &age[i]);
        for(j = 0; j<3; j++) {
            do { //input check
                printf("Type your Grade %d: ", j+1);
                scanf("%f", &grades[i][j]);
            }while(grades[i][j] <0.0 || grades[i][j] >10.0);
        }
        //Average grade calculation
        AG[i] = Average_Grade(i, n, grades);
        //Category letter grade calculation
        Letter_Grade[i] = Category_For_Average_Grade(i, AG);
        
        i++;
    }
    printf("\n");

    //menu
    int choose;
    do {
        printf("1. Display all the student's infos\n");
        printf("2. Display the students who passed with AverageGrade >= 5\n");
        printf("3. Search for a student with its name\n");
        printf("4. Calculation of the all students average grade\n");
        printf("5. Exit\n");

        printf("Type your answer: ");
        scanf("%d", &choose);
    
        switch(choose){
        case 1:
            //display students call
            Display_Students(n, name, age, grades, AG, Letter_Grade);
            break;
        case 2:
            printf("_-_-_-{Students with greater than 5 average grade}-_-_-_\n");
            for (int k = 0; k<n; k++) {
                if (AG[k] >= 5) {
                    printf("%s, ", name[k]);    
                }
            }
            printf("\n"); //space
            break;
        case 3:
            printf("_-_-_-{Search for a student}-_-_-_\n");
            char students_name[50];
            //search
            printf("Type the name of the student : ");
            getchar();
            fgets(students_name ,50, stdin);
            //comparison
            bool found = false;
            for (int h =0; h<n; h++) {
                if (strcmp(students_name, name[h]) == 0) {
                    found = true;
                    //name
                    printf("[Name : %s", *(name+h));
                    //age
                    printf(" - Age : %d", *(age+h));
                    //grades
                    for (int j = 0; j<3; ++j) {
                        printf(" - Grade %d : %.1f / ", j+1, grades[h][j]);
                    }
                    //average grade
                    printf(" - Average Grade : %.1f", *(AG+h));
                    //letter grade;
                    printf(" - Letter Grade : %c]\n", *(Letter_Grade+h));
                }
            }
            if(found == false) {
                printf("The student has not been found.");
            }
            printf("\n"); //space
            break;
        case 4:
            printf("_-_-_-{Calculation of all students average grade}-_-_-_\n");
            float sum_overall = 0.0;
            for(int i = 0; i < n; i++) {
                sum_overall += AG[i]; 
            }

            float OAG = sum_overall/n; // overall average grade
            
            printf("\n%.1f\n\n", OAG);
            break;
        case 5:
            printf("Exiting...");
            break;
        }
    }while (choose > 0 && choose < 5);

    return 0;
}