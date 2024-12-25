#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
    int studentId;
    char studentName[50];
    int studentAge;
} Student;

Student students[100];
int studentCount = 0;
int maxStudents = 100;
char fileName[] = "students.dat";

void loadStudentsFromFile() {
    FILE *file = fopen(fileName, "rb");
    if (file) {
        fread(&studentCount, sizeof(int), 1, file);
        fread(students, sizeof(Student), studentCount, file);
        fclose(file);
    } else {
        studentCount = 0;
    }
}

void saveStudentsToFile() {
    FILE *file = fopen(fileName, "wb");
    if (file) {
        fwrite(&studentCount, sizeof(int), 1, file);
        fwrite(students, sizeof(Student), studentCount, file);
        fclose(file);
    }
}

void printStudents() {
    for (int i = 0; i < studentCount; i++) {
        printf("ID: %d, Ten: %s, Tuoi: %d\n", students[i].studentId, students[i].studentName, students[i].studentAge);
    }
}

void addStudent() {
    if (studentCount >= maxStudents) {
        printf("Danh sach day.\n");
        return;
    }

    Student newStudent;
    printf("Nhap ID: ");
    scanf("%d", &newStudent.studentId);
    printf("Nhap Ten: ");
    scanf("%s", newStudent.studentName);
    printf("Nhap Tuoi: ");
    scanf("%d", &newStudent.studentAge);

    students[studentCount++] = newStudent;
    saveStudentsToFile();
}

void updateStudent() {
    int id;
    printf("Nhap ID sinh vien can sua: ");
    scanf("%d", &id);

    for (int i = 0; i < studentCount; i++) {
        if (students[i].studentId == id) {
            printf("Nhap Ten moi: ");
            scanf("%s", students[i].studentName);
            printf("Nhap Tuoi moi: ");
            scanf("%d", &students[i].studentAge);
            saveStudentsToFile();
            return;
        }
    }

    printf("Khong tim thay sinh vien.\n");
}

void deleteStudent() {
    int id;
    printf("Nhap ID sinh vien can xoa: ");
    scanf("%d", &id);

    for (int i = 0; i < studentCount; i++) {
        if (students[i].studentId == id) {
            for (int j = i; j < studentCount - 1; j++) {
                students[j] = students[j + 1];
            }
            studentCount--;
            saveStudentsToFile();
            return;
        }
    }

    printf("Khong tim thay sinh vien.\n");
}

void searchStudent() {
    int id;
    printf("Nhap ID sinh vien can tim: ");
    scanf("%d", &id);

    for (int i = 0; i < studentCount; i++) {
        if (students[i].studentId == id) {
            printf("ID: %d, Ten: %s, Tuoi: %d\n", students[i].studentId, students[i].studentName, students[i].studentAge);
            return;
        }
    }

    printf("Khong tim thay sinh vien.\n");
}

void sortStudents() {
    for (int i = 0; i < studentCount - 1; i++) {
        for (int j = i + 1; j < studentCount; j++) {
            if (students[i].studentId > students[j].studentId) {
                Student temp = students[i];
                students[i] = students[j];
                students[j] = temp;
            }
        }
    }

    saveStudentsToFile();
    printf("Danh sach da sap xep theo ID.\n");
}

void menu() {
    int choice;
    do {
        printf("\nMENU\n");
        printf("1. In danh sach sinh vien\n");
        printf("2. Them sinh vien\n");
        printf("3. Sua thong tin sinh vien\n");
        printf("4. Xoa sinh vien\n");
        printf("5. Tim kiem sinh vien\n");
        printf("6. Sap xep danh sach sinh vien\n");
        printf("7. Thoat\n");
        printf("Lua chon cua ban: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printStudents();
                break;
            case 2:
                addStudent();
                break;
            case 3:
                updateStudent();
                break;
            case 4:
                deleteStudent();
                break;
            case 5:
                searchStudent();
                break;
            case 6:
                sortStudents();
                break;
            case 7:
                printf("Thoat chuong trinh.\n");
                break;
            default:
                printf("Lua chon khong hop le. Thu lai.\n");
        }
    } while (choice != 7);
}

int main() {
    loadStudentsFromFile();
    menu();
    return 0;
}

