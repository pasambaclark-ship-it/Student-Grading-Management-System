#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

typedef struct {
    char alias[50];
    int reputation;
    int skillLevel;
} Player;

void seperator(int length) {
    for (int i = 0; i < length; i++) {
        putchar('=');
    }
    putchar('\n');
}

// Utility: print with delay
void delayPrint(const char *text, int seconds) {
    printf("%s\n", text);
    fflush(stdout);
    #ifdef _WIN32
        Sleep(seconds * 1000); // Windows uses milliseconds
    #else
        sleep(seconds);        // Linux/macOS uses seconds
    #endif
}

void intro(Player *p);
void missionMenu(Player *p);
void randomMission(Player *p);
void resolveChoice(Player *p, int choice, int winChance,
                   const char *successMsg, const char *failMsg, const char *awareness);

int main() {
    Player player = {"", 0, 1};
    srand(time(NULL));

    intro(&player);
    missionMenu(&player);

    return 0;
}

void intro(Player *p) {
    delayPrint("=====================================", 1);
    delayPrint("   NEON SHADOWS: CODEBREAKERS", 1);
    delayPrint("=====================================", 1);
    printf("Enter your hacker alias: ");
    scanf("%49s", p->alias);
    delayPrint("\nBooting sequence...", 1);
    delayPrint("Welcome to the neon city...", 1);
    printf("Alias confirmed: %s\n", p->alias);
    delayPrint("Corporations tighten their grip, but shadows resist.\n", 2);
}

void missionMenu(Player *p) {
    int choice;
    while (1) {
        delayPrint("\n--- Mission Console ---", 1);
        printf("1. Random Mission\n");
        printf("2. Exit\n");
        printf("Choose your mission: ");
        scanf("%d", &choice);

        if (choice == 1) {
            randomMission(p);
        } else if (choice == 2) {
            delayPrint("\nExiting game...", 1);
            printf("Goodbye, %s. The neon shadows await your return.\n", p->alias);
            break;
        } else {
            delayPrint("Invalid choice. Try again.", 1);
        }
    }
}

void randomMission(Player *p) {
    int missionType = rand() % 3;
    int choice;

    switch (missionType) {
        case 0:
            delayPrint("\n>>> Mission: Corporate Data Breach", 1);
            delayPrint("You slip into a neon-lit server room. Files flicker across your console.", 2);
            printf("Options:\n1. Scan for corrupted packets\n2. Attempt brute-force decryption\n3. Plant a backdoor\n4. Abort mission\n");
            printf("Choose your path: ");
            scanf("%d", &choice);
            resolveChoice(p, choice, 70,
                "You extracted hidden records successfully!",
                "Your intrusion triggered alarms!",
                "Awareness: Reckless hacking can expose you to risks.");
            break;

        case 1:
            delayPrint("\n>>> Mission: Firewall Intrusion", 1);
            delayPrint("A corporate AI firewall challenges you with a puzzle.", 2);
            printf("Options:\n1. Route Alpha (fast but noisy)\n2. Route Beta (slow but stealthy)\n3. Route Gamma (unknown risk)\n4. Abort mission\n");
            printf("Choose your path: ");
            scanf("%d", &choice);
            resolveChoice(p, choice, 60,
                "You bypassed the firewall undetected!",
                "Alarm triggered! Security traced your signal.",
                "Awareness: Stealth and patience improve digital safety.");
            break;

        case 2:
            delayPrint("\n>>> Mission: AI Bias Discovery", 1);
            delayPrint("You uncover hidden files: 'Project Neon — AI trained on biased data.'", 2);
            printf("Options:\n1. Publish findings publicly\n2. Report anonymously to watchdogs\n3. Exploit bias for gain\n4. Delete files to protect innocents\n");
            printf("Choose your path: ");
            scanf("%d", &choice);
            resolveChoice(p, choice, 80,
                "You exposed biased AI training data!",
                "You failed to uncover the hidden bias.",
                "Awareness: AI bias can harm marginalized groups.");
            break;
    }
}

void resolveChoice(Player *p, int choice, int winChance,
                   const char *successMsg, const char *failMsg, const char *awareness) {
    if (choice == 4) {
        delayPrint("You aborted the mission. Sometimes caution is the safest path.", 2);
        return;
    }

    int roll = rand() % 100 + 1;
    delayPrint("Rolling chance of success...", 1);
    char buffer[100];
    sprintf(buffer, "Random roll: %d (Threshold: %d%%)", roll, winChance);
    delayPrint(buffer, 1);

    if (roll <= winChance) {
        delayPrint("Result: SUCCESS!", 1);
        delayPrint(successMsg, 2);
        p->reputation += 15;
        p->skillLevel += 1;
    } else {
        delayPrint("Result: FAILURE!", 1);
        delayPrint(failMsg, 2);
        p->reputation -= 5;
    }
    delayPrint(awareness, 2);

    char stats[100];
    sprintf(stats, "Reputation: %d | Skill Level: %d", p->reputation, p->skillLevel);
    delayPrint(stats, 2);
}
