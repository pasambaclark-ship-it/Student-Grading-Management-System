#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

// =========================
// PLAYER STRUCTURE
// =========================
typedef struct {
    char alias[50];
    int reputation;
    int skillLevel;
} Player;

typedef struct {
    char description[200];
    int reputation;
    int skillevel;
}HistoryEntry;
HistoryEntry history[100];
int historyCount= 0;


// seperator
void seperator(int length) {
    for (int i = 0; i < length; i++) {
        putchar('=');
    }
    putchar('\n');
}

// =========================
// DELAY PRINT FUNCTION
// =========================
void delayPrint(const char *text, int ms) {
    printf("%s\n", text);
#ifdef _WIN32
    Sleep(ms);
#else
    usleep(ms * 1000);
#endif
}

// =========================
// RESOLVE PLAYER CHOICE
// =========================
void resolveChoice(
    Player *p,
    int choice,
    int successChance,
    int reputationChange,
    int skillChange,
    const char *successMessage,
    const char *failureMessage,
    const char *awarenessMessage
) {
    if (choice == 4) {
        delayPrint("Mission aborted.", 1000);
        return;
    }

    int roll = rand() % 100 + 1;
    delayPrint("Processing your decision...", 1000);
    printf("Success Chance: %d%%\n", successChance);
    printf("Random Roll: %d\n", roll);

    if (roll <= successChance) {
        delayPrint("MISSION SUCCESS!", 1000);
        delayPrint(successMessage, 1000);
        p->reputation += reputationChange;
        p->skillLevel += skillChange;
    } else {
        delayPrint("MISSION FAILED!", 1000);
        delayPrint(failureMessage, 1000);
        p->reputation -= reputationChange;
        p->skillLevel -= 1;
    }

    sprintf(history[historyCount].description, "%s", failureMessage);
    history[historyCount].reputation = p->reputation;
    history[historyCount].skillevel = p->skillLevel;
    historyCount++;

    delayPrint("Cybersecurity Awareness:", 1000);
    delayPrint(awarenessMessage, 1000);

    printf("\n--- UPDATED PLAYER STATS ---\n");
    printf("Alias: %s\n", p->alias);
    printf("Reputation: %d\n", p->reputation);
    printf("Skill Level: %d\n", p->skillLevel);
}

//History Part :))
void showHistory() {
    seperator(100);
    delayPrint("===Player LOG History=== \n", 1000);
    seperator(100);

    if(historyCount == 0) {
        printf("No Missions take yet. \n");
        return;
    } else {
        for(int i=0; i < historyCount; i++) {
            printf("%d. %s | Reputation: %d | Skill Level: %d\n",
            i+1,
            history[i].description,
            history[i].reputation,
            history[i].skillevel
            );
        }
    }
}

// =========================
// RANDOM MISSION FUNCTION
// =========================
void randomMission(Player *p) {
    int mission = rand() % 6 + 1;
    int choice;

    printf("\n====================================\n");
    printf("          NEW MISSION\n");
    printf("====================================\n");

    if (mission == 1) {
        printf("\n--- MISSION 1: DATA BREACH ---\n");
        delayPrint("A company has suffered a data breach.", 1000);
        delayPrint("Private customer information may be exposed.", 1000);
        printf("1. Report immediately\n2. Investigate\n3. Secure accounts\n4. Abort\n");
        printf("What is you choice comrad, be wise!: ");
        scanf("%d", &choice);
        if (choice == 1)
            resolveChoice(p, choice, 90, 5, 2, "You reported the breach.", "Report failed.", "Reporting suspicious activity helps.");
        else if (choice == 2)
            resolveChoice(p, choice, 60, 10, 3, "You found evidence.", "Investigation failed.", "Investigating requires careful handling.");
        else if (choice == 3)
            resolveChoice(p, choice, 75, 8, 3, "You secured accounts.", "Failed to secure.", "Securing accounts prevents further access.");
        else resolveChoice(p, 4, 0, 0, 0, "", "", "");
    }
    else if (mission == 2) {
        printf("\n--- MISSION 2: FIREWALL PUZZLE ---\n");
        delayPrint("You reached a protected system.", 1000);
        delayPrint("A firewall is blocking your access.", 1000);
        printf("1. Safe method\n2. Risky shortcut\n3. Analyze rules\n4. Abort\n");
        printf("What is you choice comrad, be wise!: ");
        scanf("%d", &choice);
        if (choice == 1)
            resolveChoice(p, choice, 80, 5, 3, "Safe method worked.", "Failed firewall.", "Use authorized methods.");
        else if (choice == 2)
            resolveChoice(p, choice, 50, 15, 4, "Risky shortcut worked.", "Shortcut failed.", "Risks can have consequences.");
        else if (choice == 3)
            resolveChoice(p, choice, 70, 7, 4, "Analyzed rules successfully.", "Could not analyze.", "Understanding rules reduces mistakes.");
        else resolveChoice(p, 4, 0, 0, 0, "", "", "");
    }
    else if (mission == 3) {
        printf("\n--- MISSION 3: AI BIAS ---\n");
        delayPrint("An AI system is being used to make important decisions.", 1000);
        delayPrint("You suspect that the system may be treating some users unfairly.", 1000);
        printf("1. Report bias\n2. Ignore for reward\n3. Review evidence\n4. Abort\n");
        printf("What is you choice comrad, be wise!: ");
        scanf("%d", &choice);
        if (choice == 1)
            resolveChoice(p, choice, 85, 8, 3, "Bias reported.", "Report failed.", "AI systems must be checked.");
        else if (choice == 2)
            resolveChoice(p, choice, 55, 12, 2, "Quick reward gained.", "Failed reward.", "Ethics matter in tech.");
        else if (choice == 3)
            resolveChoice(p, choice, 75, 10, 4, "Evidence found.", "No evidence.", "Reviewing evidence helps fairness.");
        else resolveChoice(p, 4, 0, 0, 0, "", "", "");
    }
    else if (mission == 4) {
        printf("\n--- MISSION 4: PHISHING INVESTIGATION ---\n");
        delayPrint("An employee received a suspicious email.", 1000);
        delayPrint("The message appears to request sensitive account information.", 1000);
        printf("1. Report email\n2. Investigate\n3. Verify sender\n4. Abort\n");
        printf("What is you choice comrad, be wise!: ");
        scanf("%d", &choice);
        if (choice == 1)
            resolveChoice(p, choice, 90, 7, 3, "Reported phishing.", "Failed report.", "Verify suspicious messages.");
        else if (choice == 2)
            resolveChoice(p, choice, 65, 12, 4, "Investigated successfully.", "Too slow.", "Careful observation is key.");
        else if (choice == 3)
            resolveChoice(p, choice, 85, 9, 3, "Verified sender.", "Could not verify.", "Trusted channels are safer.");
        else resolveChoice(p, 4, 0, 0, 0, "", "", "");
    }
    else if (mission == 5) {
        printf("\n--- MISSION 5: RANSOMWARE CRISIS ---\n");
        delayPrint("WARNING: Multiple computers in the company are suddenly unavailable.", 1000);
        delayPrint("Important files appear to have been locked by malicious software.", 1000);
        delayPrint("The company is under pressure to restore its operations.", 1000);
        printf("1. Emergency plan\n2. Risky recovery\n3. Isolate computers\n4. Abort\n");
        printf("What is you choice comrad, be wise!: ");
        scanf("%d", &choice);
        if (choice == 1)
            resolveChoice(p, choice, 75, 15, 5, "Response plan worked.", "Plan failed.", "Incident response reduces damage.");
        else if (choice == 2)
            resolveChoice(p, choice, 40, 25, 6, "Risky recovery worked.", "Recovery failed.", "Unauthorized actions increase damage.");
        else if (choice == 3)
            resolveChoice(p, choice, 80, 12, 5, "Isolated computers.", "Failed isolation.", "Isolation limits spread.");
        else resolveChoice(p, 4, 0, 0, 0, "", "", "");
    }
    else if (mission == 6) {
        printf("\n--- MISSION 6: INSIDER THREAT ---\n");
        delayPrint("Security logs show unusual activity from an employee account.", 1000);
        delayPrint("The account appears to be accessing information outside its normal role.", 1000);
        delayPrint("You must decide what to do without making a false accusation.", 1000);
        printf("1. Report activity\n2. Confront employee\n3. Review logs\n4. Abort\n");
        printf("What is you choice comrad, be wise!: ");
        scanf("%d", &choice);
        if (choice == 1)
            resolveChoice(p, choice, 85, 18, 5, "Reported properly.", "Report failed.", "Investigations need evidence.");
        else if (choice == 2)
            resolveChoice(p, choice, 45, 20, 4, "Confrontation complicated.", "Failed confrontation.", "Accusations need caution.");
        else if (choice == 3)
            resolveChoice(p, choice, 80, 10, 4, "Found evidence.", "No evidence.", "Logs help investigations.");
        else resolveChoice(p, 4, 0, 0, 0, "", "", "");
    }
}

// =========================
// INTRO FUNCTION
// =========================
void intro(Player *p) {
    seperator(100);
    printf("Enter your player alias: ");
    fgets(p->alias, sizeof(p->alias), stdin);
    p->alias[strcspn(p->alias, "\n")] = '\0';

    delayPrint("Welcome, Digital Rebel...", 1000);
    delayPrint("Your decisions will shape your reputation, skills, and story.", 1500);
    delayPrint("You will begin... in", 1000);

    printf("3\n"); delayPrint("", 1000);
    printf("2\n"); delayPrint("", 1000);
    printf("1\n"); delayPrint("", 1000);

    printf("\nAlias: %s\n", p->alias);
    printf("Reputation: %d\n", p->reputation);
    printf("Skill Level: %d\n", p->skillLevel);
}

// =========================
// MAIN FUNCTION
// =========================
int main() {
    Player player;
    player.reputation = 0;
    player.skillLevel = 1;

    srand(time(NULL));

    intro(&player);

    int menu, playAgain = 1;

    while (playAgain == 1) {
        seperator(100);
        printf("\n--- Mission Menu ---\n");
        printf("1. Preview all missions\n");
        printf("2. Play a random mission\n");
        printf("3. View History\n");
        printf("4. Exit game\n");
        printf("What is you choice comrad: ");
        scanf("%d", &menu);
        seperator(100);

        switch (menu) {
            case 1:
                printf("\nMission List:\n");
                printf("1. Data Breach\n");
                printf("2. Firewall Puzzle\n");
                printf("3. AI Bias\n");
                printf("4. Phishing Investigation\n");
                printf("5. Ransomware Crisis\n");
                printf("6. Insider Threat\n");
                break;
            case 2:
                randomMission(&player);
                seperator(100);
                printf("\nDo you want to take another mission?\n1. Yes\n2. No\n");
                printf("What is you choice comrad: ");
                scanf("%d", &playAgain);
                break;
            case 3:
                showHistory();
                break;
            case 4:
                playAgain = 0;
                break;
            default:
                printf("Invalid choice.\n");
        }
    }

    printf("\n====================================\n");
    printf("          GAME COMPLETE\n");
    printf("====================================\n");
    printf("Final Alias: %s\n", player.alias);
    delayPrint("", 1000); 
    printf("Final Reputation: %d\n", player.reputation);
    delayPrint("", 1000); 
    printf("Final Skill Level: %d\n", player.skillLevel);
    delayPrint("", 1000); 
    delayPrint("Thank you for playing Cyberpunk Codebreaker.", 1000);
    seperator(100);

    return 0;
}