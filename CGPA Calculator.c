#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SUBJECTS 10
#define FILENAME "students.dat"


typedef struct {
    char name[50];
    int id;
    int numSubjects;
    float grades[MAX_SUBJECTS];
    int credits[MAX_SUBJECTS];
    float cgpa;
} Student;


float calculateCGPA(Student *s) {
    float totalGradePoints = 0;
    int totalCredits = 0;
    for (int i = 0; i < s->numSubjects; i++) {
        totalGradePoints += s->grades[i] * s->credits[i];
        totalCredits += s->credits[i];
    }
    return (totalCredits == 0) ? 0 : (totalGradePoints / totalCredits);
}


void addStudent() {
    Student s;
    printf("Enter Student Name: ");
    getchar();
    fgets(s.name, sizeof(s.name), stdin);
    s.name[strcspn(s.name, "\n")] = 0; 
    
    printf("Enter Student ID: ");
    scanf("%d", &s.id);
    printf("Enter Number of Subjects: ");
    scanf("%d", &s.numSubjects);
    
    for (int i = 0; i < s.numSubjects; i++) {
        printf("Enter Grade (0-10) and Credit Hours for Subject %d: ", i + 1);
        scanf("%f %d", &s.grades[i], &s.credits[i]);
    }
    
    s.cgpa = calculateCGPA(&s);
    
    FILE *file = fopen(FILENAME, "ab");
    if (!file) {
        printf("Error saving student data!\n");
        return;
    }
    fwrite(&s, sizeof(Student), 1, file);
    fclose(file);
    printf("Student data saved successfully!\n");
}


void displayStudents() {
    FILE *file = fopen(FILENAME, "rb");
    if (!file) {
        printf("No student data found!\n");
        return;
    }
    Student s;
    printf("\nStudent Records:\n");
    while (fread(&s, sizeof(Student), 1, file)) {
        printf("-------------------------\n");
        printf("Name: %s\nID: %d\nCGPA: %.2f\n", s.name, s.id, s.cgpa);
    }
    fclose(file);
}


void searchStudent() {
    int id;
    printf("Enter Student ID to search: ");
    scanf("%d", &id);
    
    FILE *file = fopen(FILENAME, "rb");
    if (!file) {
        printf("No student data found!\n");
        return;
    }
    Student s;
    int found = 0;
    while (fread(&s, sizeof(Student), 1, file)) {
        if (s.id == id) {
            printf("\nName: %s\nID: %d\nCGPA: %.2f\n", s.name, s.id, s.cgpa);
            found = 1;
            break;
        }
    }
    fclose(file);
    if (!found) {
        printf("Student ID not found!\n");
    }
}

int main() {
    int choice;
    do {
        printf("\n==== CGPA Calculator ====\n");
        printf("1. Add Student\n2. Display Students\n3. Search Student\n4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                addStudent();
                break;
            case 2:
                displayStudents();
                break;
            case 3:
                searchStudent();
                break;
            case 4:
                printf("Exiting program...\n");
                break;
            default:
                printf("Invalid choice! Try again.\n");
        }
    } while (choice != 4);
    
    return 0;
}
