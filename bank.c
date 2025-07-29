#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <conio.h>
#include <ctype.h>

#define MAX_NAME_LEN 50
#define MAX_USERNAME_LEN 20
#define MAX_PASSWORD_LEN 20
#define MAX_ACCOUNTS 1000
#define MIN_BALANCE 500
#define MAX_TRANSACTIONS 100

// Enhanced structures
typedef struct {
    char date[20];
    char type[20];          // DEPOSIT, WITHDRAW, TRANSFER_IN, TRANSFER_OUT
    double amount;
    double balance_after;
    char description[100];
    char reference_account[15];
} Transaction;

typedef struct {
    char account_number[15];
    char name[MAX_NAME_LEN];
    char username[MAX_USERNAME_LEN];
    char password_hash[50];
    char dob[12];
    char mobile[15];
    char email[50];
    double balance;
    char account_type[20];  // SAVINGS, CURRENT, PREMIUM
    int is_active;
    int failed_attempts;
    char created_date[20];
    Transaction transactions[MAX_TRANSACTIONS];
    int transaction_count;
} BankAccount;

typedef struct {
    char admin_username[20];
    char admin_password[50];
} AdminCredentials;

// Function prototypes
void main_menu();
void admin_panel();
void user_login();
void create_account();
void deposit_money();
void withdraw_money();
void transfer_money();
void view_account_details();
void view_transaction_history();
void change_password();
void admin_view_all_accounts();
void admin_block_account();
void admin_unblock_account();

// Utility functions
char* hash_password(const char* password);
int validate_account_number(const char* account_number);
int validate_email(const char* email);
int validate_mobile(const char* mobile);
int validate_amount(double amount);
void generate_account_number(char* account_number);
void get_current_date(char* date);
void clear_screen();
void pause_system();
BankAccount* find_account_by_username(const char* username);
BankAccount* find_account_by_number(const char* account_number);
int load_accounts();
int save_accounts();
void add_transaction(BankAccount* account, const char* type, double amount, const char* description, const char* ref_account);

// Global variables
BankAccount accounts[MAX_ACCOUNTS];
int total_accounts = 0;
BankAccount* current_user = NULL;
AdminCredentials admin = {"admin", "admin"};

// Simple hash function (MD5-like but simpler for demo)
char* hash_password(const char* password) {
    static char hash[50];
    unsigned long hash_value = 5381;
    int c;
    
    while ((c = *password++)) {
        hash_value = ((hash_value << 5) + hash_value) + c;
    }
    
    sprintf(hash, "%lx", hash_value);
    return hash;
}

void get_current_date(char* date) {
    time_t now = time(NULL);
    struct tm* t = localtime(&now);
    sprintf(date, "%02d/%02d/%04d %02d:%02d", 
            t->tm_mday, t->tm_mon + 1, t->tm_year + 1900,
            t->tm_hour, t->tm_min);
}

void generate_account_number(char* account_number) {
    srand(time(NULL));
    sprintf(account_number, "SAR%010d", rand() % 1000000000);
}

void clear_screen() {
    system("cls");
}

void pause_system() {
    printf("\nPress any key to continue...");
    getch();
}

int validate_email(const char* email) {
    int at_count = 0, dot_after_at = 0;
    int len = strlen(email);
    
    if (len < 5) return 0;
    
    for (int i = 0; i < len; i++) {
        if (email[i] == '@') {
            at_count++;
            if (at_count > 1) return 0;
        } else if (email[i] == '.' && at_count == 1) {
            dot_after_at = 1;
        }
    }
    
    return (at_count == 1 && dot_after_at);
}

int validate_mobile(const char* mobile) {
    if (strlen(mobile) != 10) return 0;
    
    for (int i = 0; i < 10; i++) {
        if (!isdigit(mobile[i])) return 0;
    }
    
    return 1;
}

int validate_amount(double amount) {
    return (amount > 0 && amount <= 1000000);
}

BankAccount* find_account_by_username(const char* username) {
    for (int i = 0; i < total_accounts; i++) {
        if (strcmp(accounts[i].username, username) == 0) {
            return &accounts[i];
        }
    }
    return NULL;
}

BankAccount* find_account_by_number(const char* account_number) {
    for (int i = 0; i < total_accounts; i++) {
        if (strcmp(accounts[i].account_number, account_number) == 0) {
            return &accounts[i];
        }
    }
    return NULL;
}

void add_transaction(BankAccount* account, const char* type, double amount, const char* description, const char* ref_account) {
    if (account->transaction_count < MAX_TRANSACTIONS) {
        Transaction* trans = &account->transactions[account->transaction_count];
        get_current_date(trans->date);
        strcpy(trans->type, type);
        trans->amount = amount;
        trans->balance_after = account->balance;
        strcpy(trans->description, description);
        if (ref_account) {
            strcpy(trans->reference_account, ref_account);
        } else {
            strcpy(trans->reference_account, "N/A");
        }
        account->transaction_count++;
    }
}

int load_accounts() {
    FILE* fp = fopen("accounts.dat", "rb");
    if (fp == NULL) {
        return 0; // File doesn't exist yet
    }
    
    fread(&total_accounts, sizeof(int), 1, fp);
    fread(accounts, sizeof(BankAccount), total_accounts, fp);
    fclose(fp);
    return 1;
}

int save_accounts() {
    FILE* fp = fopen("accounts.dat", "wb");
    if (fp == NULL) {
        printf("Error: Unable to save data!\n");
        return 0;
    }
    
    fwrite(&total_accounts, sizeof(int), 1, fp);
    fwrite(accounts, sizeof(BankAccount), total_accounts, fp);
    fclose(fp);
    return 1;
}

void main_menu() {
    int choice;
    
    load_accounts();
    
    while (1) {
        clear_screen();
        printf("===============================================================\n");
        printf("=                    SARNATH ADVANCED BANK                    =\n");
        printf("=                   Professional Banking System               =\n");
        printf("===============================================================\n");
        printf("=  [1] Admin Login                                            =\n");
        printf("=  [2] User Login                                             =\n");
        printf("=  [3] Create New Account                                     =\n");
        printf("=  [4] Exit                                                   =\n");
        printf("===============================================================\n");
        printf("\nEnter your choice: ");
        
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                admin_panel();
                break;
            case 2:
                user_login();
                break;
            case 3:
                create_account();
                break;
            case 4:
                printf("\nThank you for using Sarnath Bank!\n");
                save_accounts();
                exit(0);
            default:
                printf("Invalid choice! Please try again.\n");
                pause_system();
        }
    }
}

void admin_panel() {
    char username[20], password[20];
    
    clear_screen();
    printf("===============================================================\n");
    printf("=                        ADMIN LOGIN                          =\n");
    printf("===============================================================\n");
    
    printf("\nEnter Admin Username: ");
    scanf("%s", username);
    
    printf("Enter Admin Password: ");
    // Hide password input
    int i = 0;
    char ch;
    while ((ch = getch()) != '\r' && i < 19) {
        if (ch == '\b' && i > 0) {
            printf("\b \b");
            i--;
        } else if (ch != '\b') {
            password[i++] = ch;
            printf("*");
        }
    }
    password[i] = '\0';
    
    if (strcmp(username, admin.admin_username) == 0 && 
        strcmp(password, admin.admin_password) == 0) {
        
        int choice;
        while (1) {
            clear_screen();
            printf("===============================================================\n");
            printf("=                      ADMIN DASHBOARD                        =\n");
            printf("===============================================================\n");
            printf("\n[1] View All Accounts\n");
            printf("[2] Block Account\n");
            printf("[3] Unblock Account\n");
            printf("[4] View System Statistics\n");
            printf("[5] Back to Main Menu\n");
            printf("\nEnter choice: ");
            
            scanf("%d", &choice);
            
            switch (choice) {
                case 1:
                    admin_view_all_accounts();
                    break;
                case 2:
                    admin_block_account();
                    break;
                case 3:
                    admin_unblock_account();
                    break;
                case 4:
                    printf("\nTotal Accounts: %d\n", total_accounts);
                    double total_balance = 0;
                    for (int i = 0; i < total_accounts; i++) {
                        total_balance += accounts[i].balance;
                    }
                    printf("Total Bank Balance: %.2f\n", total_balance);
                    pause_system();
                    break;
                case 5:
                    return;
                default:
                    printf("Invalid choice!\n");
                    pause_system();
            }
        }
    } else {
        printf("\n\nInvalid admin credentials!\n");
        pause_system();
    }
}

void user_login() {
    char username[20], password[20];
    
    clear_screen();
    printf("===============================================================\n");
    printf("=                        USER LOGIN                           =\n");
    printf("===============================================================\n");
    
    printf("\nEnter Username: ");
    scanf("%s", username);
    
    printf("Enter Password: ");
    // Hide password input
    int i = 0;
    char ch;
    while ((ch = getch()) != '\r' && i < 19) {
        if (ch == '\b' && i > 0) {
            printf("\b \b");
            i--;
        } else if (ch != '\b') {
            password[i++] = ch;
            printf("*");
        }
    }
    password[i] = '\0';
    
    BankAccount* account = find_account_by_username(username);
    
    if (account == NULL) {
        printf("\n\nAccount not found!\n");
        pause_system();
        return;
    }
    
    if (!account->is_active) {
        printf("\n\nAccount is blocked! Contact administrator.\n");
        pause_system();
        return;
    }
    
    if (strcmp(account->password_hash, hash_password(password)) != 0) {
        account->failed_attempts++;
        if (account->failed_attempts >= 3) {
            account->is_active = 0;
            printf("\n\nAccount blocked due to multiple failed attempts!\n");
        } else {
            printf("\n\nInvalid password! Attempts remaining: %d\n", 3 - account->failed_attempts);
        }
        save_accounts();
        pause_system();
        return;
    }
    
    account->failed_attempts = 0;
    current_user = account;
    
    int choice;
    while (1) {
        clear_screen();
        printf("===============================================================\n");
        printf("=                    WELCOME %s%-20s                          =\n", "", current_user->name);
        printf("=                      USER DASHBOARD                         =\n");
        printf("===============================================================\n");
        printf("\n[1] View Account Details\n");
        printf("[2] Deposit Money\n");
        printf("[3] Withdraw Money\n");
        printf("[4] Transfer Money\n");
        printf("[5] Transaction History\n");
        printf("[6] Change Password\n");
        printf("[7] Logout\n");
        printf("\nCurrent Balance: %.2f\n", current_user->balance);
        printf("\nEnter choice: ");
        
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                view_account_details();
                break;
            case 2:
                deposit_money();
                break;
            case 3:
                withdraw_money();
                break;
            case 4:
                transfer_money();
                break;
            case 5:
                view_transaction_history();
                break;
            case 6:
                change_password();
                break;
            case 7:
                current_user = NULL;
                return;
            default:
                printf("Invalid choice!\n");
                pause_system();
        }
    }
}

void create_account() {
    if (total_accounts >= MAX_ACCOUNTS) {
        printf("Sorry, maximum account limit reached!\n");
        pause_system();
        return;
    }
    
    BankAccount new_account = {0};
    char confirm_password[20];
    
    clear_screen();
    printf("===============================================================\n");
    printf("=                    CREATE NEW ACCOUNT                       =\n");
    printf("===============================================================\n");
    
    // Generate account number
    generate_account_number(new_account.account_number);
    
    printf("\nEnter Full Name: ");
    scanf(" %[^\n]", new_account.name);
    
    // Validate name
    for (int i = 0; new_account.name[i]; i++) {
        if (!isalpha(new_account.name[i]) && new_account.name[i] != ' ') {
            printf("Invalid name! Only letters and spaces allowed.\n");
            pause_system();
            return;
        }
    }
    
    printf("Enter Username (8-15 characters): ");
    scanf("%s", new_account.username);
    
    if (strlen(new_account.username) < 8 || strlen(new_account.username) > 15) {
        printf("Username must be 8-15 characters!\n");
        pause_system();
        return;
    }
    
    if (find_account_by_username(new_account.username) != NULL) {
        printf("Username already exists!\n");
        pause_system();
        return;
    }
    
    printf("Enter Email: ");
    scanf("%s", new_account.email);
    
    if (!validate_email(new_account.email)) {
        printf("Invalid email format!\n");
        pause_system();
        return;
    }
    
    printf("Enter Mobile Number (10 digits): ");
    scanf("%s", new_account.mobile);
    
    if (!validate_mobile(new_account.mobile)) {
        printf("Invalid mobile number!\n");
        pause_system();
        return;
    }
    
    printf("Enter Date of Birth (DD/MM/YYYY): ");
    scanf("%s", new_account.dob);
    
    printf("Enter Password: ");
    char password[20];
    int i = 0;
    char ch;
    while ((ch = getch()) != '\r' && i < 19) {
        if (ch == '\b' && i > 0) {
            printf("\b \b");
            i--;
        } else if (ch != '\b') {
            password[i++] = ch;
            printf("*");
        }
    }
    password[i] = '\0';
    
    printf("\nConfirm Password: ");
    i = 0;
    while ((ch = getch()) != '\r' && i < 19) {
        if (ch == '\b' && i > 0) {
            printf("\b \b");
            i--;
        } else if (ch != '\b') {
            confirm_password[i++] = ch;
            printf("*");
        }
    }
    confirm_password[i] = '\0';
    
    if (strcmp(password, confirm_password) != 0) {
        printf("\n\nPasswords don't match!\n");
        pause_system();
        return;
    }
    
    printf("\n\nSelect Account Type:\n");
    printf("[1] Savings (Min Balance: 500)\n");
    printf("[2] Current (Min Balance: 1000)\n");
    printf("[3] Premium (Min Balance: 5000)\n");
    printf("Choice: ");
    
    int acc_type;
    scanf("%d", &acc_type);
    
    double min_deposit;
    switch (acc_type) {
        case 1:
            strcpy(new_account.account_type, "SAVINGS");
            min_deposit = 500;
            break;
        case 2:
            strcpy(new_account.account_type, "CURRENT");
            min_deposit = 1000;
            break;
        case 3:
            strcpy(new_account.account_type, "PREMIUM");
            min_deposit = 5000;
            break;
        default:
            printf("Invalid choice!\n");
            pause_system();
            return;
    }
    
    printf("\nEnter initial deposit (Min: %.0f): ", min_deposit);
    scanf("%lf", &new_account.balance);
    
    if (new_account.balance < min_deposit) {
        printf("Insufficient initial deposit!\n");
        pause_system();
        return;
    }
    
    // Set account details
    strcpy(new_account.password_hash, hash_password(password));
    new_account.is_active = 1;
    new_account.failed_attempts = 0;
    new_account.transaction_count = 0;
    get_current_date(new_account.created_date);
    
    // Add initial deposit transaction
    add_transaction(&new_account, "DEPOSIT", new_account.balance, "Initial Deposit", NULL);
    
    // Save account
    accounts[total_accounts] = new_account;
    total_accounts++;
    
    save_accounts();
    
    printf("\n===============================================================\n");
    printf("=                  ACCOUNT CREATED SUCCESSFULLY!              =\n");
    printf("===============================================================\n");
    printf("\nAccount Number: %s\n", new_account.account_number);
    printf("Account Type: %s\n", new_account.account_type);
    printf("Initial Balance: %.2f\n", new_account.balance);
    printf("\nPlease save your account number and login credentials securely!\n");
    
    pause_system();
}

void deposit_money() {
    double amount;
    
    clear_screen();
    printf("===============================================================\n");
    printf("=                        DEPOSIT MONEY                        =\n");
    printf("===============================================================\n");
    
    printf("\nCurrent Balance: %.2f\n", current_user->balance);
    printf("Enter amount to deposit: ");
    scanf("%lf", &amount);
    
    if (!validate_amount(amount)) {
        printf("Invalid amount!\n");
        pause_system();
        return;
    }
    
    current_user->balance += amount;
    add_transaction(current_user, "DEPOSIT", amount, "Cash Deposit", NULL);
    save_accounts();
    
    printf("\n✓ Deposit successful!\n");
    printf("Amount Deposited: %.2f\n", amount);
    printf("New Balance: %.2f\n", current_user->balance);
    
    pause_system();
}

void withdraw_money() {
    double amount;
    
    clear_screen();
    printf("===============================================================\n");
    printf("=                       WITHDRAW MONEY                        =\n");
    printf("===============================================================\n");
    
    printf("\nCurrent Balance: %.2f\n", current_user->balance);
    printf("Enter amount to withdraw: ");
    scanf("%lf", &amount);
    
    if (!validate_amount(amount)) {
        printf("Invalid amount!\n");
        pause_system();
        return;
    }
    
    double min_balance = 500;
    if (strcmp(current_user->account_type, "CURRENT") == 0) min_balance = 1000;
    if (strcmp(current_user->account_type, "PREMIUM") == 0) min_balance = 5000;
    
    if (current_user->balance - amount < min_balance) {
        printf("Insufficient balance! Minimum balance required: %.0f\n", min_balance);
        pause_system();
        return;
    }
    
    current_user->balance -= amount;
    add_transaction(current_user, "WITHDRAW", amount, "Cash Withdrawal", NULL);
    save_accounts();
    
    printf("\n✓ Withdrawal successful!\n");
    printf("Amount Withdrawn: %.2f\n", amount);
    printf("New Balance: %.2f\n", current_user->balance);
    
    pause_system();
}

void transfer_money() {
    char target_account[15];
    double amount;
    
    clear_screen();
    printf("===============================================================\n");
    printf("=                       TRANSFER MONEY                        =\n");
    printf("===============================================================\n");
    
    printf("\nCurrent Balance: %.2f\n", current_user->balance);
    printf("Enter target account number: ");
    scanf("%s", target_account);
    
    BankAccount* target = find_account_by_number(target_account);
    if (target == NULL) {
        printf("Target account not found!\n");
        pause_system();
        return;
    }
    
    if (!target->is_active) {
        printf("Target account is blocked!\n");
        pause_system();
        return;
    }
    
    if (strcmp(target->account_number, current_user->account_number) == 0) {
        printf("Cannot transfer to same account!\n");
        pause_system();
        return;
    }
    
    printf("Target Account Holder: %s\n", target->name);
    printf("Enter amount to transfer: ");
    scanf("%lf", &amount);
    
    if (!validate_amount(amount)) {
        printf("Invalid amount!\n");
        pause_system();
        return;
    }
    
    double min_balance = 500;
    if (strcmp(current_user->account_type, "CURRENT") == 0) min_balance = 1000;
    if (strcmp(current_user->account_type, "PREMIUM") == 0) min_balance = 5000;
    
    if (current_user->balance - amount < min_balance) {
        printf("Insufficient balance! Minimum balance required: %.0f\n", min_balance);
        pause_system();
        return;
    }
    
    // Process transfer
    current_user->balance -= amount;
    target->balance += amount;
    
    char desc[100];
    sprintf(desc, "Transfer to %s", target->name);
    add_transaction(current_user, "TRANSFER_OUT", amount, desc, target->account_number);
    
    sprintf(desc, "Transfer from %s", current_user->name);
    add_transaction(target, "TRANSFER_IN", amount, desc, current_user->account_number);
    
    save_accounts();
    
    printf("\n✓ Transfer successful!\n");
    printf("Amount Transferred: %.2f\n", amount);
    printf("To: %s (%s)\n", target->name, target->account_number);
    printf("Your New Balance: %.2f\n", current_user->balance);
    
    pause_system();
}

void view_account_details() {
    clear_screen();
    printf("===============================================================\n");
    printf("=                     ACCOUNT DETAILS                         =\n");
    printf("===============================================================\n");
    
    printf("\nAccount Number    : %s\n", current_user->account_number);
    printf("Account Holder    : %s\n", current_user->name);
    printf("Account Type      : %s\n", current_user->account_type);
    printf("Username          : %s\n", current_user->username);
    printf("Email             : %s\n", current_user->email);
    printf("Mobile            : %s\n", current_user->mobile);
    printf("Date of Birth     : %s\n", current_user->dob);
    printf("Account Created   : %s\n", current_user->created_date);
    printf("Current Balance   : %.2f\n", current_user->balance);
    printf("Account Status    : %s\n", current_user->is_active ? "ACTIVE" : "BLOCKED");
    printf("Total Transactions: %d\n", current_user->transaction_count);
    
    pause_system();
}

void view_transaction_history() {
    clear_screen();
    printf("===============================================================\n");
    printf("=                   TRANSACTION HISTORY                       =\n");
    printf("===============================================================\n");
    
    if (current_user->transaction_count == 0) {
        printf("\nNo transactions found!\n");
        pause_system();
        return;
    }
    
    printf("\n%-20s %-15s %-12s %-12s %-20s\n", "Date", "Type", "Amount", "Balance", "Description");
    printf("================================================================================\n");
    
    for (int i = current_user->transaction_count - 1; i >= 0; i--) {
        Transaction* trans = &current_user->transactions[i];
        printf("%-20s %-15s %-10.2f %-10.2f %-20s\n",
               trans->date, trans->type, trans->amount, 
               trans->balance_after, trans->description);
    }
    
    pause_system();
}

void change_password() {
    char old_password[20], new_password[20], confirm_password[20];
    
    clear_screen();
    printf("===============================================================\n");
    printf("=                      CHANGE PASSWORD                        =\n");
    printf("===============================================================\n");
    
    printf("\nEnter current password: ");
    int i = 0;
    char ch;
    while ((ch = getch()) != '\r' && i < 19) {
        if (ch == '\b' && i > 0) {
            printf("\b \b");
            i--;
        } else if (ch != '\b') {
            old_password[i++] = ch;
            printf("*");
        }
    }
    old_password[i] = '\0';
    
    if (strcmp(current_user->password_hash, hash_password(old_password)) != 0) {
        printf("\n\nIncorrect current password!\n");
        pause_system();
        return;
    }
    
    printf("\nEnter new password: ");
    i = 0;
    while ((ch = getch()) != '\r' && i < 19) {
        if (ch == '\b' && i > 0) {
            printf("\b \b");
            i--;
        } else if (ch != '\b') {
            new_password[i++] = ch;
            printf("*");
        }
    }
    new_password[i] = '\0';
    
    printf("\nConfirm new password: ");
    i = 0;
    while ((ch = getch()) != '\r' && i < 19) {
        if (ch == '\b' && i > 0) {
            printf("\b \b");
            i--;
        } else if (ch != '\b') {
            confirm_password[i++] = ch;
            printf("*");
        }
    }
    confirm_password[i] = '\0';
    
    if (strcmp(new_password, confirm_password) != 0) {
        printf("\n\nNew passwords don't match!\n");
        pause_system();
        return;
    }
    
    strcpy(current_user->password_hash, hash_password(new_password));
    save_accounts();
    
    printf("\n\n✓ Password changed successfully!\n");
    pause_system();
}

void admin_view_all_accounts() {
    clear_screen();
    printf("===============================================================\n");
    printf("=                       ALL ACCOUNTS                          =\n");
    printf("===============================================================\n");
    
    if (total_accounts == 0) {
        printf("\nNo accounts found!\n");
        pause_system();
        return;
    }
    
    printf("\n%-15s %-20s %-15s %-12s %-8s\n", "Account No", "Name", "Type", "Balance", "Status");
    printf("========================================================================\n");
    
    for (int i = 0; i < total_accounts; i++) {
        printf("%-15s %-20s %-15s %-10.2f %-8s\n",
               accounts[i].account_number, accounts[i].name, 
               accounts[i].account_type, accounts[i].balance,
               accounts[i].is_active ? "ACTIVE" : "BLOCKED");
    }
    
    pause_system();
}

void admin_block_account() {
    char account_number[15];
    
    printf("\nEnter account number to block: ");
    scanf("%s", account_number);
    
    BankAccount* account = find_account_by_number(account_number);
    if (account == NULL) {
        printf("Account not found!\n");
        pause_system();
        return;
    }
    
    account->is_active = 0;
    save_accounts();
    
    printf("Account %s has been blocked!\n", account_number);
    pause_system();
}

void admin_unblock_account() {
    char account_number[15];
    
    printf("\nEnter account number to unblock: ");
    scanf("%s", account_number);
    
    BankAccount* account = find_account_by_number(account_number);
    if (account == NULL) {
        printf("Account not found!\n");
        pause_system();
        return;
    }
    
    account->is_active = 1;
    account->failed_attempts = 0;
    save_accounts();
    
    printf("Account %s has been unblocked!\n", account_number);
    pause_system();
}

int main() {
    main_menu();
    return 0;
}