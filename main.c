#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <windows.h>

#define RED "\033[1;31m"
#define GREEN "\033[1;32m"
#define YELLOW "\033[1;33m"
#define BLUE "\033[1;34m"
#define RESET "\033[0m"

const char *breached[] = {"123456", "password", "qwerty", "letmein", "admin", "welcome"};
const int breached_count = 6;

int has_upper(const char *p) {
    while (*p) if (isupper(*p++)) return 1;
    return 0;
}

int has_lower(const char *p) {
    while (*p) if (islower(*p++)) return 1;
    return 0;
}

int has_digit(const char *p) {
    while (*p) if (isdigit(*p++)) return 1;
    return 0;
}

int has_special(const char *p) {
    while (*p) if (ispunct(*p++)) return 1;
    return 0;
}

int is_breached(const char *p) {
    for (int i = 0; i < breached_count; i++) {
        if (strcmp(p, breached[i]) == 0) return 1;
    }
    return 0;
}

int get_strength_score(const char *p) {
    int score = 0;
    if (strlen(p) >= 8) score++;
    if (has_upper(p)) score++;
    if (has_lower(p)) score++;
    if (has_digit(p)) score++;
    if (has_special(p)) score++;
    return score;
}

const char* get_strength_level(int score) {
    switch (score) {
        case 0: case 1: return "Very Weak";
        case 2: return "Weak";
        case 3: return "Moderate";
        case 4: return "Strong";
        case 5: return "Very Strong";
        default: return "Unknown";
    }
}

void give_suggestions(const char *p) {
    if (strlen(p) < 8) printf(RED "- Use at least 8 characters\n" RESET);
    if (!has_upper(p)) printf(RED "- Add uppercase letters\n" RESET);
    if (!has_lower(p)) printf(RED "- Add lowercase letters\n" RESET);
    if (!has_digit(p)) printf(RED "- Include numbers\n" RESET);
    if (!has_special(p)) printf(RED "- Add special characters\n" RESET);
    if (is_breached(p)) printf(RED "- Avoid common/breached passwords\n" RESET);
}

int username_exists(const char *account) {
    FILE *f = fopen("passwords.txt", "r");
    char line[256];
    if (f) {
        while (fgets(line, sizeof(line), f)) {
            if (strstr(line, account)) {
                fclose(f);
                return 1;
            }
        }
        fclose(f);
    }
    return 0;
}

void save_password(const char *account, const char *password) {
    FILE *f = fopen("passwords.txt", "a");
    if (f) {
        fprintf(f, "%s: %s\n", account, password);
        fclose(f);
    }
}

void search_password() {
    char query[100], line[256];
    int found = 0;
    printf(YELLOW "Enter account name to search: " RESET);
    scanf("%s", query);
    FILE *f = fopen("passwords.txt", "r");
    if (f) {
        while (fgets(line, sizeof(line), f)) {
            if (strstr(line, query)) {
                printf(GREEN "Found: %s" RESET, line);
                Beep(800, 200);
                found = 1;
                break;
            }
        }
        fclose(f);
    }
    if (!found) {
        printf(RED "No entry found for %s\n" RESET, query);
        Beep(300, 300);
    }
}

int get_valid_choice() {
    int ch;
    while (1) {
        Beep(700, 100);
        printf(BLUE "\nPassword Manager Menu:\n" RESET);
        printf("1. Add New Password\n");
        printf("2. Search by Account Name\n");
        printf("3. Exit\n");
        printf("4. Get Suggestions for a Password\n");
        printf("Enter your choice: ");
        if (scanf("%d", &ch) != 1) {
            while (getchar() != '\n');
            ch = -1;
        }
        if (ch >= 1 && ch <= 4) return ch;
        else {
            printf(RED "Invalid choice! Try again.\n" RESET);
            Beep(200, 400);
        }
    }
}

int main() {
    int ch;
    char acc[100], pass[100];

    while (1) {
        ch = get_valid_choice();
        switch (ch) {
            case 1:
                Beep(500, 150);
                printf(YELLOW "Enter account name: " RESET);
                scanf("%s", acc);
                if (username_exists(acc)) {
                    printf(RED "\u26A0\ufe0f Username already exists!\n" RESET);
                    Beep(300, 300);
                    break;
                }
                while (1) {
                    Beep(500, 150);
                    printf(YELLOW "Enter password: " RESET);
                    scanf("%s", pass);

                    int score = get_strength_score(pass);
                    const char *strength = get_strength_level(score);

                    printf(BLUE "Password Strength: %s\n" RESET, strength);

                    if (score >= 4 && !is_breached(pass)) {
                        printf(GREEN " Password saved successfully.\n" RESET);
                        Beep(1000, 200);
                        save_password(acc, pass);
                        break;
                    } else {
                        if (is_breached(pass)) {
                            printf(RED "This password is too common!\n" RESET);
                        }
                        printf(RED "Weak password! Please improve it:\n" RESET);
                        give_suggestions(pass);
                        Beep(400, 300);
                    }
                }
                break;

            case 2:
                search_password();
                break;

            case 3:
                Beep(600, 150);
                Beep(400, 150);
                Beep(300, 300);
                printf(GREEN "Exiting program...\n" RESET);
                return 0;

            case 4:
                Beep(500, 150);
                printf(YELLOW "Enter a password to check and get suggestions: " RESET);
                scanf("%s", pass);
                int score = get_strength_score(pass);
                const char *strength = get_strength_level(score);
                printf(BLUE "Password Strength: %s\n" RESET, strength);
                if (score >= 4 && !is_breached(pass)) {
                    printf(GREEN "This is a strong password!\n" RESET);
                } else {
                    if (is_breached(pass)) {
                        printf(RED "This password is too common!\n" RESET);
                    }
                    printf(RED "Suggestions to improve your password:\n" RESET);
                    give_suggestions(pass);
                    Beep(400, 300);
                }
                break;
        }
    }
}