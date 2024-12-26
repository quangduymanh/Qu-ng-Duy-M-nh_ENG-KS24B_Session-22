#include <stdio.h>
#include <string.h>

struct SinhVien {
    char id[50];
    char name[50];
    int age;
};

struct SinhVien sv[100]; // Danh sach sinh vien (global)
int numberStudent = 0;   // So luong sinh vien

// Cac ham xu ly
void getStudentByFile(); // Lay danh sach sinh vien tu file
void printStudent();     // In danh sach sinh vien
void addStudent();       // Them sinh vien moi
void saveStudent();      // Luu danh sach sinh vien vao file

int main() {
    getStudentByFile(); // Goi ham lay danh sach sinh vien tu file
    int choose;
    do {
        printf("1. In danh sach sinh vien\n");
        printf("2. Them sinh vien\n");
        printf("3. Sua thong tin sinh vien\n");
        printf("4. Xoa sinh vien\n");
        printf("5. Tim thong tin sinh vien\n");
        printf("6. Sap xep sinh vien\n");
        printf("7. Thoat\n");
        printf("Moi ban nhap lua chon: ");
        scanf("%d", &choose);
        getchar();

        switch (choose) {
        case 1:
            printStudent(); 
            break;
        case 2:
            addStudent(); 
            break;
        case 3:
            break;
        case 4:
            break;
        case 5:
            break;
        case 6:
            break;
        case 7:
            printf("Thoat chuong trinh.\n");
            break;
        default:
            printf("Lua chon khong hop le!\n");
            break;
        }
    } while (choose != 7);

    return 0;
}
// Ham lay danh sach sinh vien tu file
void getStudentByFile() {
    FILE *file = fopen("sinhvien.bin", "rb"); // Mo file nhi phan de doc
    if (file == NULL) {
        printf("Khong the mo file hoac file chua ton tai.\n");
        return;
    }
    numberStudent = fread(sv, sizeof(struct SinhVien), 100, file); // Doc danh sach sinh vien
    fclose(file); // Dong file
}
// Ham in danh sach sinh vien
void printStudent() {
    if (numberStudent == 0) {
        printf("Khong co sinh vien nao trong danh sach.\n");
        return;
    }
    for (int i = 0; i < numberStudent; i++) {
        printf("Thong tin sinh vien thu %d:\n", i + 1);
        printf("Ma SV: %s\n", sv[i].id);
        printf("Ten SV: %s\n", sv[i].name);
        printf("Tuoi SV: %d\n", sv[i].age);
    }
}
// Ham them sinh vien moi
void addStudent() {
    if (numberStudent >= 100) {
        printf("Danh sach sinh vien da day.\n");
        return;
    }
    struct SinhVien sv1;
    printf("Nhap ma SV: ");
    fgets(sv1.id, sizeof(sv1.id), stdin); // Nhap ma sinh vien
    sv1.id[strcspn(sv1.id, "\n")] = '\0'; // Xoa ky tu xuong dong
    printf("Nhap ten SV: ");
    fgets(sv1.name, sizeof(sv1.name), stdin); // Nhap ten sinh vien
    sv1.name[strcspn(sv1.name, "\n")] = '\0'; // Xoa ky tu xuong dong
    printf("Nhap tuoi SV: ");
    scanf("%d", &sv1.age); // Nhap tuoi sinh vien
    getchar(); // Xoa ky tu xuong dong
    sv[numberStudent] = sv1; // Them sinh vien vao danh sach
    numberStudent++;         // Tang so luong sinh vien
    saveStudent();           // Luu danh sach vao file
}
// Ham luu danh sach sinh vien vao file
void saveStudent() {
    FILE *file = fopen("sinhvien.bin", "wb"); // Mo file nhi phan de ghi
    if (file == NULL) {
        printf("Khong the mo file de ghi.\n");
        return;
    }
    fwrite(sv, sizeof(struct SinhVien), numberStudent, file); // Ghi danh sach sinh vien
    fclose(file); // Dong file
}
