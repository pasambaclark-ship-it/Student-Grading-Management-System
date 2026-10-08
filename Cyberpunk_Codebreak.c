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
    const char *resultMessage;

    delayPrint("Processing your decision...", 1000);
    printf("Success Chance: %d%%\n", successChance);
    printf("Random Roll: %d\n", roll);

    if (roll <= successChance) {
        delayPrint("MISSION SUCCESS!", 1000);
        delayPrint(successMessage, 1000);
        p->reputation += reputationChange;
        p->skillLevel += skillChange;

        resultMessage = successMessage;
    } else {
        delayPrint("MISSION FAILED!", 1000);
        delayPrint(failureMessage, 1000);
        p->reputation -= reputationChange;
        p->skillLevel -= 1;

        resultMessage = failureMessage;
    }

    sprintf(history[historyCount].description, "%s", resultMessage);
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
    delayPrint("=== Player Log History ===", 1000);
    seperator(100);

    if(historyCount == 0) {
        printf("No missions taken yet.\n");
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
    int mission = rand() % 15 + 1;
    int choice;

    printf("\n====================================\n");
    printf("          NEW MISSION\n");
    printf("====================================\n");

    if (mission == 1) {
        printf("\n--- MISSION 1: DATA BREACH ---\n");
        delayPrint("A company has suffered a data breach.", 1000);
        delayPrint("Private customer information may be exposed.", 1000);
        printf("1. Report immediately\n2. Investigate\n3. Secure accounts\n4. Abort\n");
        printf("What is your choice, comrade? Be wise!: ");
        scanf("%d", &choice);

        if (choice == 1)
            resolveChoice(p, choice, 90, 5, 2, "You reported the breach.", "The report failed.", "Reporting suspicious activity helps.");
        else if (choice == 2)
            resolveChoice(p, choice, 60, 10, 3, "You found evidence.", "The investigation failed.", "Investigating requires careful handling.");
        else if (choice == 3)
            resolveChoice(p, choice, 75, 8, 3, "You secured the accounts.", "You failed to secure the accounts.", "Securing accounts prevents further access.");
        else if (choice == 4)
            resolveChoice(p, 4, 0, 0, 0, "", "", "");
        else
            printf("Invalid choice. Please choose an option from 1 to 4.\n");
    }

    else if (mission == 2) {
        printf("\n--- MISSION 2: FIREWALL PUZZLE ---\n");
        delayPrint("You reached a protected system.", 1000);
        delayPrint("A firewall is blocking your access.", 1000);
        printf("1. Safe method\n2. Risky shortcut\n3. Analyze rules\n4. Abort\n");
        printf("What is your choice, comrade? Be wise!: ");
        scanf("%d", &choice);

        if (choice == 1)
            resolveChoice(p, choice, 80, 5, 3, "The safe method worked.", "The safe method failed.", "Use authorized methods.");
        else if (choice == 2)
            resolveChoice(p, choice, 50, 15, 4, "The risky shortcut worked.", "The shortcut failed.", "Risks can have consequences.");
        else if (choice == 3)
            resolveChoice(p, choice, 70, 7, 4, "You analyzed the rules successfully.", "You could not analyze the rules.", "Understanding rules reduces mistakes.");
        else if (choice == 4)
            resolveChoice(p, 4, 0, 0, 0, "", "", "");
        else
            printf("Invalid choice. Please choose an option from 1 to 4.\n");
    }

    else if (mission == 3) {
        printf("\n--- MISSION 3: AI BIAS ---\n");
        delayPrint("An AI system is being used to make important decisions.", 1000);
        delayPrint("You suspect that the system may be treating some users unfairly.", 1000);
        printf("1. Report bias\n2. Ignore for reward\n3. Review evidence\n4. Abort\n");
        printf("What is your choice, comrade? Be wise!: ");
        scanf("%d", &choice);

        if (choice == 1)
            resolveChoice(p, choice, 85, 8, 3, "The bias was reported.", "The report failed.", "AI systems must be checked.");
        else if (choice == 2)
            resolveChoice(p, choice, 55, 12, 2, "You gained a quick reward.", "You failed to gain the reward.", "Ethics matter in technology.");
        else if (choice == 3)
            resolveChoice(p, choice, 75, 10, 4, "You found evidence.", "You found no evidence.", "Reviewing evidence helps ensure fairness.");
        else if (choice == 4)
            resolveChoice(p, 4, 0, 0, 0, "", "", "");
        else
            printf("Invalid choice. Please choose an option from 1 to 4.\n");
    }

    else if (mission == 4) {
        printf("\n--- MISSION 4: PHISHING INVESTIGATION ---\n");
        delayPrint("An employee received a suspicious email.", 1000);
        delayPrint("The message appears to request sensitive account information.", 1000);
        printf("1. Report email\n2. Investigate\n3. Verify sender\n4. Abort\n");
        printf("What is your choice, comrade? Be wise!: ");
        scanf("%d", &choice);

        if (choice == 1)
            resolveChoice(p, choice, 90, 7, 3, "You reported the phishing email.", "The report failed.", "Verify suspicious messages.");
        else if (choice == 2)
            resolveChoice(p, choice, 65, 12, 4, "You investigated successfully.", "The investigation was too slow.", "Careful observation is key.");
        else if (choice == 3)
            resolveChoice(p, choice, 85, 9, 3, "You verified the sender.", "You could not verify the sender.", "Trusted channels are safer.");
        else if (choice == 4)
            resolveChoice(p, 4, 0, 0, 0, "", "", "");
        else
            printf("Invalid choice. Please choose an option from 1 to 4.\n");
    }

    else if (mission == 5) {
        printf("\n--- MISSION 5: RANSOMWARE CRISIS ---\n");
        delayPrint("WARNING: Multiple computers in the company are suddenly unavailable.", 1000);
        delayPrint("Important files appear to have been locked by malicious software.", 1000);
        delayPrint("The company is under pressure to restore its operations.", 1000);
        printf("1. Emergency plan\n2. Risky recovery\n3. Isolate computers\n4. Abort\n");
        printf("What is your choice, comrade? Be wise!: ");
        scanf("%d", &choice);

        if (choice == 1)
            resolveChoice(p, choice, 75, 15, 5, "The response plan worked.", "The response plan failed.", "Incident response reduces damage.");
        else if (choice == 2)
            resolveChoice(p, choice, 40, 25, 6, "The risky recovery worked.", "The recovery failed.", "Unauthorized actions can increase damage.");
        else if (choice == 3)
            resolveChoice(p, choice, 80, 12, 5, "You isolated the computers.", "You failed to isolate the computers.", "Isolation limits the spread.");
        else if (choice == 4)
            resolveChoice(p, 4, 0, 0, 0, "", "", "");
        else
            printf("Invalid choice. Please choose an option from 1 to 4.\n");
    }

    else if (mission == 6) {
        printf("\n--- MISSION 6: INSIDER THREAT ---\n");
        delayPrint("Security logs show unusual activity from an employee account.", 1000);
        delayPrint("The account appears to be accessing information outside its normal role.", 1000);
        delayPrint("You must decide what to do without making a false accusation.", 1000);
        printf("1. Report activity\n2. Confront employee\n3. Review logs\n4. Abort\n");
        printf("What is your choice, comrade? Be wise!: ");
        scanf("%d", &choice);

        if (choice == 1)
            resolveChoice(p, choice, 85, 18, 5, "You reported the activity properly.", "The report failed.", "Investigations need evidence.");
        else if (choice == 2)
            resolveChoice(p, choice, 45, 20, 4, "The confrontation became complicated.", "The confrontation failed.", "Accusations require caution.");
        else if (choice == 3)
            resolveChoice(p, choice, 80, 10, 4, "You found evidence.", "You found no evidence.", "Logs help with investigations.");
        else if (choice == 4)
            resolveChoice(p, 4, 0, 0, 0, "", "", "");
        else
            printf("Invalid choice. Please choose an option from 1 to 4.\n");
    }

    else if (mission == 7) {
        printf("\n--- MISSION 7: PASSWORD SECURITY ---\n");
        delayPrint("An employee is using a weak and predictable password.", 1000);
        delayPrint("The account contains access to important company resources.", 1000);
        printf("1. Report weak password\n2. Change password\n3. Review password policies\n4. Abort\n");
        printf("What is your choice, comrade? Be wise!: ");
        scanf("%d", &choice);

        if (choice == 1)
            resolveChoice(p, choice, 85, 6, 3, "You reported the weak password.", "The report failed.", "Strong passwords help protect accounts.");
        else if (choice == 2)
            resolveChoice(p, choice, 80, 8, 4, "You changed the password successfully.", "You failed to change the password.", "Use strong and unique passwords.");
        else if (choice == 3)
            resolveChoice(p, choice, 75, 7, 4, "You reviewed the password policies.", "You could not review the policies.", "Password policies improve account security.");
        else if (choice == 4)
            resolveChoice(p, 4, 0, 0, 0, "", "", "");
        else
            printf("Invalid choice. Please choose an option from 1 to 4.\n");
    }

    else if (mission == 8) {
        printf("\n--- MISSION 8: SOCIAL ENGINEERING ---\n");
        delayPrint("Someone calls the company pretending to be a senior manager.", 1000);
        delayPrint("They urgently request confidential information.", 1000);
        printf("1. Provide the information\n2. Verify the caller\n3. Report the request\n4. Abort\n");
        printf("What is your choice, comrade? Be wise!: ");
        scanf("%d", &choice);

        if (choice == 1)
            resolveChoice(p, choice, 35, 15, 2, "The information was provided.", "The request was rejected.", "Never share sensitive information without verification.");
        else if (choice == 2)
            resolveChoice(p, choice, 90, 10, 4, "You verified the caller successfully.", "You could not verify the caller.", "Always verify unusual requests.");
        else if (choice == 3)
            resolveChoice(p, choice, 85, 9, 4, "You reported the suspicious request.", "The report failed.", "Reporting suspicious behavior helps prevent social engineering.");
        else if (choice == 4)
            resolveChoice(p, 4, 0, 0, 0, "", "", "");
        else
            printf("Invalid choice. Please choose an option from 1 to 4.\n");
    }

    else if (mission == 9) {
        printf("\n--- MISSION 9: SECURE BACKUP ---\n");
        delayPrint("A company discovers that its important backups have not been tested.", 1000);
        delayPrint("A recent system failure makes the situation urgent.", 1000);
        printf("1. Test the backup\n2. Ignore the issue\n3. Create a new backup\n4. Abort\n");
        printf("What is your choice, comrade? Be wise!: ");
        scanf("%d", &choice);

        if (choice == 1)
            resolveChoice(p, choice, 85, 9, 4, "The backup test was successful.", "The backup test failed.", "Regular backup testing helps ensure recovery.");
        else if (choice == 2)
            resolveChoice(p, choice, 40, 12, 2, "You ignored the issue.", "Ignoring the issue caused problems.", "Backups should be maintained and tested regularly.");
        else if (choice == 3)
            resolveChoice(p, choice, 80, 10, 5, "You created a new backup successfully.", "The backup could not be created.", "Reliable backups help protect important data.");
        else if (choice == 4)
            resolveChoice(p, 4, 0, 0, 0, "", "", "");
        else
            printf("Invalid choice. Please choose an option from 1 to 4.\n");
    }

    else if (mission == 10) {
        printf("\n--- MISSION 10: PUBLIC WI-FI ---\n");
        delayPrint("You are working from a public location using an unsecured Wi-Fi network.", 1000);
        delayPrint("You need to access an important company account.", 1000);
        printf("1. Use public network\n2. Use secure connection\n3. Wait for trusted network\n4. Abort\n");
        printf("What is your choice, comrade? Be wise!: ");
        scanf("%d", &choice);

        if (choice == 1)
            resolveChoice(p, choice, 40, 14, 2, "You accessed the account.", "The connection caused security problems.", "Avoid sensitive activities on unsecured networks.");
        else if (choice == 2)
            resolveChoice(p, choice, 90, 10, 4, "You used a secure connection.", "The secure connection failed.", "Secure connections protect sensitive information.");
        else if (choice == 3)
            resolveChoice(p, choice, 85, 8, 3, "You waited for a trusted network.", "You could not find a trusted network.", "Patience can prevent security risks.");
        else if (choice == 4)
            resolveChoice(p, 4, 0, 0, 0, "", "", "");
        else
            printf("Invalid choice. Please choose an option from 1 to 4.\n");
    }

    else if (mission == 11) {
        printf("\n--- MISSION 11: SOFTWARE UPDATE ---\n");
        delayPrint("A critical security update is available for company computers.", 1000);
        delayPrint("Some employees are worried that the update may interrupt their work.", 1000);
        printf("1. Install immediately\n2. Delay the update\n3. Test the update first\n4. Abort\n");
        printf("What is your choice, comrade? Be wise!: ");
        scanf("%d", &choice);

        if (choice == 1)
            resolveChoice(p, choice, 85, 9, 4, "The security update was installed successfully.", "The update installation failed.", "Keeping software updated reduces security risks.");
        else if (choice == 2)
            resolveChoice(p, choice, 45, 12, 2, "You delayed the update.", "The delay caused problems.", "Important security updates should not be ignored.");
        else if (choice == 3)
            resolveChoice(p, choice, 90, 10, 5, "You tested the update successfully.", "The update test failed.", "Testing helps identify problems before deployment.");
        else if (choice == 4)
            resolveChoice(p, 4, 0, 0, 0, "", "", "");
        else
            printf("Invalid choice. Please choose an option from 1 to 4.\n");
    }

    else if (mission == 12) {
        printf("\n--- MISSION 12: USB THREAT ---\n");
        delayPrint("An unknown USB device has been found in the office.", 1000);
        delayPrint("You do not know whether it contains malicious software.", 1000);
        printf("1. Plug it into a computer\n2. Report the device\n3. Give it to security staff\n4. Abort\n");
        printf("What is your choice, comrade? Be wise!: ");
        scanf("%d", &choice);

        if (choice == 1)
            resolveChoice(p, choice, 30, 18, 2, "The USB device appeared harmless.", "The USB device caused a security incident.", "Unknown devices should not be connected to company computers.");
        else if (choice == 2)
            resolveChoice(p, choice, 90, 8, 3, "You reported the unknown device.", "The report failed.", "Report unknown devices to security personnel.");
        else if (choice == 3)
            resolveChoice(p, choice, 85, 9, 4, "You gave the device to security staff.", "Security staff could not safely process the device.", "Security teams can safely investigate unknown devices.");
        else if (choice == 4)
            resolveChoice(p, 4, 0, 0, 0, "", "", "");
        else
            printf("Invalid choice. Please choose an option from 1 to 4.\n");
    }

    else if (mission == 13) {
        printf("\n--- MISSION 13: DATA CLASSIFICATION ---\n");
        delayPrint("You discover several files containing sensitive company information.", 1000);
        delayPrint("The files are stored in a folder with incorrect access permissions.", 1000);
        printf("1. Restrict access\n2. Ignore permissions\n3. Review files and permissions\n4. Abort\n");
        printf("What is your choice, comrade? Be wise!: ");
        scanf("%d", &choice);

        if (choice == 1)
            resolveChoice(p, choice, 85, 10, 4, "You restricted access to the sensitive files.", "You failed to restrict access.", "Sensitive information should only be accessible to authorized users.");
        else if (choice == 2)
            resolveChoice(p, choice, 35, 15, 2, "You ignored the permissions.", "Ignoring the permissions caused problems.", "Incorrect permissions can expose sensitive information.");
        else if (choice == 3)
            resolveChoice(p, choice, 80, 9, 5, "You reviewed the files and corrected the permissions.", "You could not correct the permissions.", "Proper data classification helps protect sensitive information.");
        else if (choice == 4)
            resolveChoice(p, 4, 0, 0, 0, "", "", "");
        else
            printf("Invalid choice. Please choose an option from 1 to 4.\n");
    }

    else if (mission == 14) {
        printf("\n--- MISSION 14: SECURITY AUDIT ---\n");
        delayPrint("A routine security audit has revealed several unusual system settings.", 1000);
        delayPrint("You need to determine whether the settings create security risks.", 1000);
        printf("1. Ignore settings\n2. Review settings\n3. Report findings\n4. Abort\n");
        printf("What is your choice, comrade? Be wise!: ");
        scanf("%d", &choice);

        if (choice == 1)
            resolveChoice(p, choice, 35, 14, 2, "You ignored the settings.", "Ignoring the settings caused problems.", "Security issues should be investigated instead of ignored.");
        else if (choice == 2)
            resolveChoice(p, choice, 85, 10, 5, "You reviewed the settings successfully.", "You could not review the settings.", "Regular audits help identify security weaknesses.");
        else if (choice == 3)
            resolveChoice(p, choice, 90, 12, 4, "You reported the audit findings.", "The report failed.", "Reporting security findings helps organizations respond to risks.");
        else if (choice == 4)
            resolveChoice(p, 4, 0, 0, 0, "", "", "");
        else
            printf("Invalid choice. Please choose an option from 1 to 4.\n");
    }

    else if (mission == 15) {
        printf("\n--- MISSION 15: INCIDENT RESPONSE ---\n");
        delayPrint("Multiple security alerts have appeared across the company's network.", 1000);
        delayPrint("You must determine how to respond before the situation gets worse.", 1000);
        printf("1. Investigate the alerts\n2. Shut down everything\n3. Follow the incident response plan\n4. Abort\n");
        printf("What is your choice, comrade? Be wise!: ");
        scanf("%d", &choice);

        if (choice == 1)
            resolveChoice(p, choice, 80, 12, 5, "You investigated the alerts successfully.", "The investigation failed.", "Careful investigation helps identify the source of incidents.");
        else if (choice == 2)
            resolveChoice(p, choice, 50, 15, 3, "The shutdown prevented further activity.", "The shutdown caused additional problems.", "Emergency actions should be carefully considered.");
        else if (choice == 3)
            resolveChoice(p, choice, 90, 15, 6, "You successfully followed the incident response plan.", "The response plan failed.", "A prepared response plan helps organizations handle incidents.");
        else if (choice == 4)
            resolveChoice(p, 4, 0, 0, 0, "", "", "");
        else
            printf("Invalid choice. Please choose an option from 1 to 4.\n");
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
        printf("What is your choice, comrade? ");
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
                printf("7. Password Security\n");
                printf("8. Social Engineering\n");
                printf("9. Secure Backup\n");
                printf("10. Public Wi-Fi\n");
                printf("11. Software Update\n");
                printf("12. USB Threat\n");
                printf("13. Data Classification\n");
                printf("14. Security Audit\n");
                printf("15. Incident Response\n");
                break;

            case 2:
                randomMission(&player);
                seperator(100);
                printf("\nDo you want to take another mission?\n1. Yes\n2. No\n");
                printf("What is your choice, comrade? ");
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