#include <stdio.h>
#include <string.h>

struct Account {
    char username[50];
    char password[50];
};

struct Account accounts[100];
int accountCount = 0;

void loadAccounts();
void saveAccounts();
void registerAccount();
void loginAccount();
int isUsernameExist(const char *username);

int main() {
    loadAccounts();
    int choice;

    do {
        printf("\nMENU\n");
        printf("1. Dang nhap\n");
        printf("2. Dang ky\n");
        printf("3. Thoat\n");
        printf("Lua chon cua ban: ");
        scanf("%d", &choice);
        getchar();

        switch (choice) {
        case 1:
            loginAccount();
            break;
        case 2:
            registerAccount();
            break;
        case 3:
            printf("Thoat chuong trinh.\n");
            break;
        default:
            printf("Lua chon khong hop le. Vui long chon lai.\n");
            break;
        }
    } while (choice != 3);

    return 0;
}

void loadAccounts() {
    FILE *file = fopen("accounts.bin", "rb");
    if (file == NULL) {
        return;
    }
    accountCount = fread(accounts, sizeof(struct Account), 100, file);
    fclose(file);
}

void saveAccounts() {
    FILE *file = fopen("accounts.bin", "wb");
    if (file == NULL) {
        return;
    }
    fwrite(accounts, sizeof(struct Account), accountCount, file);
    fclose(file);
}

int isUsernameExist(const char *username) {
    for (int i = 0; i < accountCount; i++) {
        if (strcmp(accounts[i].username, username) == 0) {
            return 1;
        }
    }
    return 0;
}

void registerAccount() {
    if (accountCount >= 100) {
        printf("Danh sach tai khoan da day.\n");
        return;
    }

    struct Account newAccount;
    char confirmPassword[50];

    do {
        printf("Nhap tai khoan: ");
        fgets(newAccount.username, sizeof(newAccount.username), stdin);
        newAccount.username[strcspn(newAccount.username, "\n")] = '\0';
        if (isUsernameExist(newAccount.username)) {
            printf("Tai khoan da ton tai. Vui long nhap tai khoan khac.\n");
        }
    } while (isUsernameExist(newAccount.username));

    printf("Nhap mat khau: ");
    fgets(newAccount.password, sizeof(newAccount.password), stdin);
    newAccount.password[strcspn(newAccount.password, "\n")] = '\0';

    printf("Xac nhan mat khau: ");
    fgets(confirmPassword, sizeof(confirmPassword), stdin);
    confirmPassword[strcspn(confirmPassword, "\n")] = '\0';

    if (strcmp(newAccount.password, confirmPassword) != 0) {
        printf("Mat khau xac nhan khong trung khop. Dang ky that bai.\n");
        return;
    }

    accounts[accountCount] = newAccount;
    accountCount++;
    saveAccounts();
    printf("Dang ky tai khoan thanh cong.\n");
}

void loginAccount() {
    char username[50];
    char password[50];

    printf("Nhap tai khoan: ");
    fgets(username, sizeof(username), stdin);
    username[strcspn(username, "\n")] = '\0';

    printf("Nhap mat khau: ");
    fgets(password, sizeof(password), stdin);
    password[strcspn(password, "\n")] = '\0';

    for (int i = 0; i < accountCount; i++) {
        if (strcmp(accounts[i].username, username) == 0 &&
            strcmp(accounts[i].password, password) == 0) {
            printf("Dang nhap thanh cong.\n");
            return;
        }
    }
    printf("Dang nhap that bai. Tai khoan hoac mat khau khong dung.\n");
}
