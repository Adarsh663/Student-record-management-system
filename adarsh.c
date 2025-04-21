#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Student {
    int roll;
    char name[50];
    float marks;
};

void addStudent() {
    FILE *fp = fopen("students.dat", "ab");
    struct Student s;
    printf("Enter Roll Number: ");
    scanf("%d", &s.roll);
    printf("Enter Name: ");
    scanf(" %[^\n]", s.name);
    printf("Enter Marks: ");
    scanf("%f", &s.marks);

    fwrite(&s, sizeof(s), 1, fp);
    fclose(fp);
    printf("Student record added successfully.\n");
}

void viewStudents() {
    FILE *fp = fopen("students.dat", "rb");
    struct Student s;
    printf("\nAll Student Records:\n");
    printf("Roll\tName\tMarks\n");
    while (fread(&s, sizeof(s), 1, fp)) {
        printf("%d\t%s\t%.2f\n", s.roll, s.name, s.marks);
    }
    fclose(fp);
}

void searchStudent() {
    FILE *fp = fopen("students.dat", "rb");
    int roll, found = 0;
    struct Student s;
    printf("Enter Roll Number to Search: ");
    scanf("%d", &roll);
    while (fread(&s, sizeof(s), 1, fp)) {
        if (s.roll == roll) {
            printf("Record Found:\nRoll: %d\nName: %s\nMarks: %.2f\n", s.roll, s.name, s.marks);
            found = 1;
            break;
        }
    }
    if (!found) {
        printf("No record found with Roll Number %d.\n", roll);
    }
    fclose(fp);
}

void updateStudent() {
    FILE *fp = fopen("students.dat", "rb+");
    int roll, found = 0;
    struct Student s;
    printf("Enter Roll Number to Update: ");
    scanf("%d", &roll);

    while (fread(&s, sizeof(s), 1, fp)) {
        if (s.roll == roll) {
            found = 1;
            fseek(fp, -sizeof(s), SEEK_CUR);
            printf("Enter New Name: ");
            scanf(" %[^\n]", s.name);
            printf("Enter New Marks: ");
            scanf("%f", &s.marks);
            fwrite(&s, sizeof(s), 1, fp);
            printf("Record updated successfully.\n");
            break;
        }
    }
    if (!found) {
        printf("Record not found.\n");
    }
    fclose(fp);
}

void deleteStudent() {
    FILE *fp = fopen("students.dat", "rb");
    FILE *temp = fopen("temp.dat", "wb");
    int roll, found = 0;
    struct Student s;

    printf("Enter Roll Number to Delete: ");
    scanf("%d", &roll);

    while (fread(&s, sizeof(s), 1, fp)) {
        if (s.roll != roll) {
            fwrite(&s, sizeof(s), 1, temp);
        } else {
            found = 1;
        }
    }

    fclose(fp);
    fclose(temp);
    remove("students.dat");
    rename("temp.dat", "students.dat");

    if (found) {
        printf("Record deleted successfully.\n");
    } else {
        printf("Record not found.\n");
    }
}

int main() {
    int choice;
    while (1) {
        printf("\n--- Student Record System ---\n");
        printf("1. Add Student\n");
        printf("2. View Students\n");
        printf("3. Search Student\n");
        printf("4. Update Student\n");
        printf("5. Delete Student\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: addStudent(); break;
            case 2: viewStudents(); break;
            case 3: searchStudent(); break;
            case 4: updateStudent(); break;
            case 5: deleteStudent(); break;
            case 6: exit(0);
            default: printf("Invalid choice. Try again.\n");
        }
    }

    return 0;
}