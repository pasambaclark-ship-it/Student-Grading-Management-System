#include "raylib.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// ============================================================
// SETTINGS
// ============================================================

#define SCREEN_WIDTH 1100
#define SCREEN_HEIGHT 700

#define MAX_HISTORY 100
#define MAX_ALIAS 50

// ============================================================
// PLAYER
// ============================================================

typedef struct
{
    char alias[MAX_ALIAS];
    int reputation;
    int skillLevel;
} Player;

// ============================================================
// HISTORY
// ============================================================

typedef struct
{
    char description[200];
    int reputation;
    int skillLevel;
} HistoryEntry;

HistoryEntry history[MAX_HISTORY];
int historyCount = 0;

// ============================================================
// MISSION
// ============================================================

typedef struct
{
    char title[100];
    char description1[200];
    char description2[200];

    char choices[3][100];

    int successChance[3];
    int reputationChange[3];
    int skillChange[3];

    char successMessage[3][200];
    char failureMessage[3][200];

    char awarenessMessage[200];

} Mission;

// ============================================================
// GAME STATES
// ============================================================

typedef enum
{
    SCREEN_ALIAS,
    SCREEN_MENU,
    SCREEN_MISSIONS,
    SCREEN_MISSION,
    SCREEN_RESULT,
    SCREEN_HISTORY,
    SCREEN_GAME_COMPLETE

} GameScreen;

GameScreen currentScreen = SCREEN_ALIAS;

// ============================================================
// GLOBAL VARIABLES
// ============================================================

Player player;

Mission missions[15];

int currentMission = -1;
int selectedChoice = -1;

int missionRoll = 0;
int missionSuccess = 0;

char resultMessage[200];
char awarenessMessage[200];

int gameRunning = true;

char aliasInput[MAX_ALIAS] = "";
int aliasLength = 0;

// ============================================================
// COLORS
// ============================================================

Color BACKGROUND = {10, 10, 18, 255};
Color PANEL = {20, 22, 35, 255};
Color PANEL_LIGHT = {30, 32, 48, 255};

Color GREEN = {50, 220, 120, 255};
Color RED = {230, 70, 80, 255};
Color CYAN = {60, 200, 255, 255};
Color YELLOW = {245, 210, 70, 255};
Color WHITE = {240, 240, 240, 255};
Color GRAY = {160, 160, 175, 255};

// ============================================================
// DRAW CENTERED TEXT
// ============================================================

void DrawCenteredText(const char *text, int y, int fontSize, Color color)
{
    int width = MeasureText(text, fontSize);

    DrawText(
        text,
        SCREEN_WIDTH / 2 - width / 2,
        y,
        fontSize,
        color
    );
}

// ============================================================
// BUTTON
// ============================================================

bool DrawButton(Rectangle rect, const char *text, Color color)
{
    Vector2 mouse = GetMousePosition();

    bool hovered = CheckCollisionPointRec(mouse, rect);

    Color buttonColor = color;

    if (hovered)
    {
        buttonColor.r = (unsigned char) ((buttonColor.r + 255) / 2);
        buttonColor.g = (unsigned char) ((buttonColor.g + 255) / 2);
        buttonColor.b = (unsigned char) ((buttonColor.b + 255) / 2);
    }

    DrawRectangleRounded(rect, 0.2f, 10, buttonColor);

    int fontSize = 20;

    int textWidth = MeasureText(text, fontSize);

    DrawText(
        text,
        rect.x + rect.width / 2 - textWidth / 2,
        rect.y + rect.height / 2 - fontSize / 2,
        fontSize,
        WHITE
    );

    return hovered && IsMouseButtonPressed(MOUSE_BUTTON_LEFT);
}

// ============================================================
// INITIALIZE MISSIONS
// ============================================================

void InitializeMissions()
{
    // ========================================================
    // MISSION 1
    // ========================================================

    strcpy(missions[0].title, "MISSION 1: DATA BREACH");

    strcpy(
        missions[0].description1,
        "A company has suffered a data breach."
    );

    strcpy(
        missions[0].description2,
        "Private customer information may be exposed."
    );

    strcpy(missions[0].choices[0], "Report immediately");
    strcpy(missions[0].choices[1], "Investigate");
    strcpy(missions[0].choices[2], "Secure accounts");

    missions[0].successChance[0] = 90;
    missions[0].successChance[1] = 60;
    missions[0].successChance[2] = 75;

    missions[0].reputationChange[0] = 5;
    missions[0].reputationChange[1] = 10;
    missions[0].reputationChange[2] = 8;

    missions[0].skillChange[0] = 2;
    missions[0].skillChange[1] = 3;
    missions[0].skillChange[2] = 3;

    strcpy(
        missions[0].successMessage[0],
        "You reported the breach."
    );

    strcpy(
        missions[0].successMessage[1],
        "You found evidence."
    );

    strcpy(
        missions[0].successMessage[2],
        "You secured the accounts."
    );

    strcpy(
        missions[0].failureMessage[0],
        "The report failed."
    );

    strcpy(
        missions[0].failureMessage[1],
        "The investigation failed."
    );

    strcpy(
        missions[0].failureMessage[2],
        "You failed to secure the accounts."
    );

    strcpy(
        missions[0].awarenessMessage,
        "Reporting suspicious activity helps protect users."
    );

    // ========================================================
    // MISSION 2
    // ========================================================

    strcpy(missions[1].title, "MISSION 2: FIREWALL PUZZLE");

    strcpy(
        missions[1].description1,
        "You reached a protected system."
    );

    strcpy(
        missions[1].description2,
        "A firewall is blocking your access."
    );

    strcpy(missions[1].choices[0], "Safe method");
    strcpy(missions[1].choices[1], "Risky shortcut");
    strcpy(missions[1].choices[2], "Analyze rules");

    missions[1].successChance[0] = 80;
    missions[1].successChance[1] = 50;
    missions[1].successChance[2] = 70;

    missions[1].reputationChange[0] = 5;
    missions[1].reputationChange[1] = 15;
    missions[1].reputationChange[2] = 7;

    missions[1].skillChange[0] = 3;
    missions[1].skillChange[1] = 4;
    missions[1].skillChange[2] = 4;

    strcpy(
        missions[1].successMessage[0],
        "The safe method worked."
    );

    strcpy(
        missions[1].successMessage[1],
        "The risky shortcut worked."
    );

    strcpy(
        missions[1].successMessage[2],
        "You analyzed the rules successfully."
    );

    strcpy(
        missions[1].failureMessage[0],
        "The safe method failed."
    );

    strcpy(
        missions[1].failureMessage[1],
        "The shortcut failed."
    );

    strcpy(
        missions[1].failureMessage[2],
        "You could not analyze the rules."
    );

    strcpy(
        missions[1].awarenessMessage,
        "Use authorized methods when dealing with protected systems."
    );

    // ========================================================
    // MISSION 3
    // ========================================================

    strcpy(missions[2].title, "MISSION 3: AI BIAS");

    strcpy(
        missions[2].description1,
        "An AI system is being used to make important decisions."
    );

    strcpy(
        missions[2].description2,
        "You suspect the system may be treating users unfairly."
    );

    strcpy(missions[2].choices[0], "Report bias");
    strcpy(missions[2].choices[1], "Ignore for reward");
    strcpy(missions[2].choices[2], "Review evidence");

    missions[2].successChance[0] = 85;
    missions[2].successChance[1] = 55;
    missions[2].successChance[2] = 75;

    missions[2].reputationChange[0] = 8;
    missions[2].reputationChange[1] = 12;
    missions[2].reputationChange[2] = 10;

    missions[2].skillChange[0] = 3;
    missions[2].skillChange[1] = 2;
    missions[2].skillChange[2] = 4;

    strcpy(
        missions[2].successMessage[0],
        "The bias was reported."
    );

    strcpy(
        missions[2].successMessage[1],
        "You gained a quick reward."
    );

    strcpy(
        missions[2].successMessage[2],
        "You found evidence."
    );

    strcpy(
        missions[2].failureMessage[0],
        "The report failed."
    );

    strcpy(
        missions[2].failureMessage[1],
        "You failed to gain the reward."
    );

    strcpy(
        missions[2].failureMessage[2],
        "You found no useful evidence."
    );

    strcpy(
        missions[2].awarenessMessage,
        "AI systems should be checked for fairness and bias."
    );

    // ========================================================
    // MISSION 4
    // ========================================================

    strcpy(missions[3].title, "MISSION 4: PHISHING INVESTIGATION");

    strcpy(
        missions[3].description1,
        "An employee received a suspicious email."
    );

    strcpy(
        missions[3].description2,
        "The message requests sensitive account information."
    );

    strcpy(missions[3].choices[0], "Report email");
    strcpy(missions[3].choices[1], "Investigate");
    strcpy(missions[3].choices[2], "Verify sender");

    missions[3].successChance[0] = 90;
    missions[3].successChance[1] = 65;
    missions[3].successChance[2] = 85;

    missions[3].reputationChange[0] = 7;
    missions[3].reputationChange[1] = 12;
    missions[3].reputationChange[2] = 9;

    missions[3].skillChange[0] = 3;
    missions[3].skillChange[1] = 4;
    missions[3].skillChange[2] = 3;

    strcpy(
        missions[3].successMessage[0],
        "You reported the phishing email."
    );

    strcpy(
        missions[3].successMessage[1],
        "You investigated successfully."
    );

    strcpy(
        missions[3].successMessage[2],
        "You verified the sender."
    );

    strcpy(
        missions[3].failureMessage[0],
        "The report failed."
    );

    strcpy(
        missions[3].failureMessage[1],
        "The investigation was too slow."
    );

    strcpy(
        missions[3].failureMessage[2],
        "You could not verify the sender."
    );

    strcpy(
        missions[3].awarenessMessage,
        "Always verify suspicious messages before responding."
    );

    // ========================================================
    // MISSION 5
    // ========================================================

    strcpy(missions[4].title, "MISSION 5: RANSOMWARE CRISIS");

    strcpy(
        missions[4].description1,
        "Multiple computers are suddenly unavailable."
    );

    strcpy(
        missions[4].description2,
        "Important files appear to have been locked."
    );

    strcpy(missions[4].choices[0], "Emergency plan");
    strcpy(missions[4].choices[1], "Risky recovery");
    strcpy(missions[4].choices[2], "Isolate computers");

    missions[4].successChance[0] = 75;
    missions[4].successChance[1] = 40;
    missions[4].successChance[2] = 80;

    missions[4].reputationChange[0] = 15;
    missions[4].reputationChange[1] = 25;
    missions[4].reputationChange[2] = 12;

    missions[4].skillChange[0] = 5;
    missions[4].skillChange[1] = 6;
    missions[4].skillChange[2] = 5;

    strcpy(
        missions[4].successMessage[0],
        "The response plan worked."
    );

    strcpy(
        missions[4].successMessage[1],
        "The risky recovery worked."
    );

    strcpy(
        missions[4].successMessage[2],
        "You isolated the computers."
    );

    strcpy(
        missions[4].failureMessage[0],
        "The response plan failed."
    );

    strcpy(
        missions[4].failureMessage[1],
        "The recovery failed."
    );

    strcpy(
        missions[4].failureMessage[2],
        "You failed to isolate the computers."
    );

    strcpy(
        missions[4].awarenessMessage,
        "Isolating affected systems can limit the spread of ransomware."
    );

    // ========================================================
    // MISSION 6
    // ========================================================

    strcpy(missions[5].title, "MISSION 6: INSIDER THREAT");

    strcpy(
        missions[5].description1,
        "Security logs show unusual activity from an employee."
    );

    strcpy(
        missions[5].description2,
        "You must investigate without making a false accusation."
    );

    strcpy(missions[5].choices[0], "Report activity");
    strcpy(missions[5].choices[1], "Confront employee");
    strcpy(missions[5].choices[2], "Review logs");

    missions[5].successChance[0] = 85;
    missions[5].successChance[1] = 45;
    missions[5].successChance[2] = 80;

    missions[5].reputationChange[0] = 18;
    missions[5].reputationChange[1] = 20;
    missions[5].reputationChange[2] = 10;

    missions[5].skillChange[0] = 5;
    missions[5].skillChange[1] = 4;
    missions[5].skillChange[2] = 4;

    strcpy(
        missions[5].successMessage[0],
        "You reported the activity properly."
    );

    strcpy(
        missions[5].successMessage[1],
        "The confrontation became complicated."
    );

    strcpy(
        missions[5].successMessage[2],
        "You found evidence."
    );

    strcpy(
        missions[5].failureMessage[0],
        "The report failed."
    );

    strcpy(
        missions[5].failureMessage[1],
        "The confrontation failed."
    );

    strcpy(
        missions[5].failureMessage[2],
        "You found no evidence."
    );

    strcpy(
        missions[5].awarenessMessage,
        "Security investigations should be based on evidence."
    );

    // ========================================================
    // MISSION 7
    // ========================================================

    strcpy(missions[6].title, "MISSION 7: PASSWORD SECURITY");

    strcpy(
        missions[6].description1,
        "An employee is using a weak and predictable password."
    );

    strcpy(
        missions[6].description2,
        "The account has access to important resources."
    );

    strcpy(missions[6].choices[0], "Report weak password");
    strcpy(missions[6].choices[1], "Change password");
    strcpy(missions[6].choices[2], "Review policies");

    missions[6].successChance[0] = 85;
    missions[6].successChance[1] = 80;
    missions[6].successChance[2] = 75;

    missions[6].reputationChange[0] = 6;
    missions[6].reputationChange[1] = 8;
    missions[6].reputationChange[2] = 7;

    missions[6].skillChange[0] = 3;
    missions[6].skillChange[1] = 4;
    missions[6].skillChange[2] = 4;

    strcpy(
        missions[6].successMessage[0],
        "You reported the weak password."
    );

    strcpy(
        missions[6].successMessage[1],
        "You changed the password successfully."
    );

    strcpy(
        missions[6].successMessage[2],
        "You reviewed the password policies."
    );

    strcpy(
        missions[6].failureMessage[0],
        "The report failed."
    );

    strcpy(
        missions[6].failureMessage[1],
        "You failed to change the password."
    );

    strcpy(
        missions[6].failureMessage[2],
        "You could not review the policies."
    );

    strcpy(
        missions[6].awarenessMessage,
        "Strong and unique passwords help protect accounts."
    );

    // ========================================================
    // MISSION 8
    // ========================================================

    strcpy(missions[7].title, "MISSION 8: SOCIAL ENGINEERING");

    strcpy(
        missions[7].description1,
        "Someone calls pretending to be a senior manager."
    );

    strcpy(
        missions[7].description2,
        "They urgently request confidential information."
    );

    strcpy(missions[7].choices[0], "Provide information");
    strcpy(missions[7].choices[1], "Verify caller");
    strcpy(missions[7].choices[2], "Report request");

    missions[7].successChance[0] = 35;
    missions[7].successChance[1] = 90;
    missions[7].successChance[2] = 85;

    missions[7].reputationChange[0] = 15;
    missions[7].reputationChange[1] = 10;
    missions[7].reputationChange[2] = 9;

    missions[7].skillChange[0] = 2;
    missions[7].skillChange[1] = 4;
    missions[7].skillChange[2] = 4;

    strcpy(
        missions[7].successMessage[0],
        "The information was provided."
    );

    strcpy(
        missions[7].successMessage[1],
        "You verified the caller successfully."
    );

    strcpy(
        missions[7].successMessage[2],
        "You reported the suspicious request."
    );

    strcpy(
        missions[7].failureMessage[0],
        "The request was rejected."
    );

    strcpy(
        missions[7].failureMessage[1],
        "You could not verify the caller."
    );

    strcpy(
        missions[7].failureMessage[2],
        "The report failed."
    );

    strcpy(
        missions[7].awarenessMessage,
        "Always verify unusual requests before sharing information."
    );

    // ========================================================
    // MISSION 9
    // ========================================================

    strcpy(missions[8].title, "MISSION 9: SECURE BACKUP");

    strcpy(
        missions[8].description1,
        "Important backups have not been tested."
    );

    strcpy(
        missions[8].description2,
        "A recent system failure makes the situation urgent."
    );

    strcpy(missions[8].choices[0], "Test backup");
    strcpy(missions[8].choices[1], "Ignore issue");
    strcpy(missions[8].choices[2], "Create new backup");

    missions[8].successChance[0] = 85;
    missions[8].successChance[1] = 40;
    missions[8].successChance[2] = 80;

    missions[8].reputationChange[0] = 9;
    missions[8].reputationChange[1] = 12;
    missions[8].reputationChange[2] = 10;

    missions[8].skillChange[0] = 4;
    missions[8].skillChange[1] = 2;
    missions[8].skillChange[2] = 5;

    strcpy(
        missions[8].successMessage[0],
        "The backup test was successful."
    );

    strcpy(
        missions[8].successMessage[1],
        "You ignored the issue."
    );

    strcpy(
        missions[8].successMessage[2],
        "You created a new backup successfully."
    );

    strcpy(
        missions[8].failureMessage[0],
        "The backup test failed."
    );

    strcpy(
        missions[8].failureMessage[1],
        "Ignoring the issue caused problems."
    );

    strcpy(
        missions[8].failureMessage[2],
        "The backup could not be created."
    );

    strcpy(
        missions[8].awarenessMessage,
        "Backups should be maintained and tested regularly."
    );

    // ========================================================
    // MISSION 10
    // ========================================================

    strcpy(missions[9].title, "MISSION 10: PUBLIC WI-FI");

    strcpy(
        missions[9].description1,
        "You are working from a public location."
    );

    strcpy(
        missions[9].description2,
        "You need to access an important company account."
    );

    strcpy(missions[9].choices[0], "Use public network");
    strcpy(missions[9].choices[1], "Use secure connection");
    strcpy(missions[9].choices[2], "Wait for trusted network");

    missions[9].successChance[0] = 40;
    missions[9].successChance[1] = 90;
    missions[9].successChance[2] = 85;

    missions[9].reputationChange[0] = 14;
    missions[9].reputationChange[1] = 10;
    missions[9].reputationChange[2] = 8;

    missions[9].skillChange[0] = 2;
    missions[9].skillChange[1] = 4;
    missions[9].skillChange[2] = 3;

    strcpy(
        missions[9].successMessage[0],
        "You accessed the account."
    );

    strcpy(
        missions[9].successMessage[1],
        "You used a secure connection."
    );

    strcpy(
        missions[9].successMessage[2],
        "You waited for a trusted network."
    );

    strcpy(
        missions[9].failureMessage[0],
        "The connection caused security problems."
    );

    strcpy(
        missions[9].failureMessage[1],
        "The secure connection failed."
    );

    strcpy(
        missions[9].failureMessage[2],
        "You could not find a trusted network."
    );

    strcpy(
        missions[9].awarenessMessage,
        "Avoid sensitive activities on unsecured networks."
    );

    // ========================================================
    // MISSION 11
    // ========================================================

    strcpy(missions[10].title, "MISSION 11: SOFTWARE UPDATE");

    strcpy(
        missions[10].description1,
        "A critical security update is available."
    );

    strcpy(
        missions[10].description2,
        "Employees worry that the update may interrupt work."
    );

    strcpy(missions[10].choices[0], "Install immediately");
    strcpy(missions[10].choices[1], "Delay update");
    strcpy(missions[10].choices[2], "Test update first");

    missions[10].successChance[0] = 85;
    missions[10].successChance[1] = 45;
    missions[10].successChance[2] = 90;

    missions[10].reputationChange[0] = 9;
    missions[10].reputationChange[1] = 12;
    missions[10].reputationChange[2] = 10;

    missions[10].skillChange[0] = 4;
    missions[10].skillChange[1] = 2;
    missions[10].skillChange[2] = 5;

    strcpy(
        missions[10].successMessage[0],
        "The security update was installed successfully."
    );

    strcpy(
        missions[10].successMessage[1],
        "You delayed the update."
    );

    strcpy(
        missions[10].successMessage[2],
        "You tested the update successfully."
    );

    strcpy(
        missions[10].failureMessage[0],
        "The update installation failed."
    );

    strcpy(
        missions[10].failureMessage[1],
        "The delay caused problems."
    );

    strcpy(
        missions[10].failureMessage[2],
        "The update test failed."
    );

    strcpy(
        missions[10].awarenessMessage,
        "Keeping software updated reduces security risks."
    );

    // ========================================================
    // MISSION 12
    // ========================================================

    strcpy(missions[11].title, "MISSION 12: USB THREAT");

    strcpy(
        missions[11].description1,
        "An unknown USB device has been found in the office."
    );

    strcpy(
        missions[11].description2,
        "You do not know whether it contains malicious software."
    );

    strcpy(missions[11].choices[0], "Plug it into a computer");
    strcpy(missions[11].choices[1], "Report the device");
    strcpy(missions[11].choices[2], "Give it to security");

    missions[11].successChance[0] = 30;
    missions[11].successChance[1] = 90;
    missions[11].successChance[2] = 85;

    missions[11].reputationChange[0] = 18;
    missions[11].reputationChange[1] = 8;
    missions[11].reputationChange[2] = 9;

    missions[11].skillChange[0] = 2;
    missions[11].skillChange[1] = 3;
    missions[11].skillChange[2] = 4;

    strcpy(
        missions[11].successMessage[0],
        "The USB device appeared harmless."
    );

    strcpy(
        missions[11].successMessage[1],
        "You reported the unknown device."
    );

    strcpy(
        missions[11].successMessage[2],
        "You gave the device to security staff."
    );

    strcpy(
        missions[11].failureMessage[0],
        "The USB device caused a security incident."
    );

    strcpy(
        missions[11].failureMessage[1],
        "The report failed."
    );

    strcpy(
        missions[11].failureMessage[2],
        "Security staff could not safely process the device."
    );

    strcpy(
        missions[11].awarenessMessage,
        "Unknown devices should never be connected to company computers."
    );

    // ========================================================
    // MISSION 13
    // ========================================================

    strcpy(missions[12].title, "MISSION 13: DATA CLASSIFICATION");

    strcpy(
        missions[12].description1,
        "Several files contain sensitive company information."
    );

    strcpy(
        missions[12].description2,
        "The files have incorrect access permissions."
    );

    strcpy(missions[12].choices[0], "Restrict access");
    strcpy(missions[12].choices[1], "Ignore permissions");
    strcpy(missions[12].choices[2], "Review permissions");

    missions[12].successChance[0] = 85;
    missions[12].successChance[1] = 35;
    missions[12].successChance[2] = 80;

    missions[12].reputationChange[0] = 10;
    missions[12].reputationChange[1] = 15;
    missions[12].reputationChange[2] = 9;

    missions[12].skillChange[0] = 4;
    missions[12].skillChange[1] = 2;
    missions[12].skillChange[2] = 5;

    strcpy(
        missions[12].successMessage[0],
        "You restricted access to the sensitive files."
    );

    strcpy(
        missions[12].successMessage[1],
        "You ignored the permissions."
    );

    strcpy(
        missions[12].successMessage[2],
        "You reviewed and corrected the permissions."
    );

    strcpy(
        missions[12].failureMessage[0],
        "You failed to restrict access."
    );

    strcpy(
        missions[12].failureMessage[1],
        "Ignoring the permissions caused problems."
    );

    strcpy(
        missions[12].failureMessage[2],
        "You could not correct the permissions."
    );

    strcpy(
        missions[12].awarenessMessage,
        "Sensitive information should only be accessible to authorized users."
    );

    // ========================================================
    // MISSION 14
    // ========================================================

    strcpy(missions[13].title, "MISSION 14: SECURITY AUDIT");

    strcpy(
        missions[13].description1,
        "A routine security audit reveals unusual settings."
    );

    strcpy(
        missions[13].description2,
        "You need to determine whether they create risks."
    );

    strcpy(missions[13].choices[0], "Ignore settings");
    strcpy(missions[13].choices[1], "Review settings");
    strcpy(missions[13].choices[2], "Report findings");

    missions[13].successChance[0] = 35;
    missions[13].successChance[1] = 85;
    missions[13].successChance[2] = 90;

    missions[13].reputationChange[0] = 14;
    missions[13].reputationChange[1] = 10;
    missions[13].reputationChange[2] = 12;

    missions[13].skillChange[0] = 2;
    missions[13].skillChange[1] = 5;
    missions[13].skillChange[2] = 4;

    strcpy(
        missions[13].successMessage[0],
        "You ignored the settings."
    );

    strcpy(
        missions[13].successMessage[1],
        "You reviewed the settings successfully."
    );

    strcpy(
        missions[13].successMessage[2],
        "You reported the audit findings."
    );

    strcpy(
        missions[13].failureMessage[0],
        "Ignoring the settings caused problems."
    );

    strcpy(
        missions[13].failureMessage[1],
        "You could not review the settings."
    );

    strcpy(
        missions[13].failureMessage[2],
        "The report failed."
    );

    strcpy(
        missions[13].awarenessMessage,
        "Regular security audits help identify weaknesses."
    );

    // ========================================================
    // MISSION 15
    // ========================================================

    strcpy(missions[14].title, "MISSION 15: INCIDENT RESPONSE");

    strcpy(
        missions[14].description1,
        "Multiple security alerts appear across the network."
    );

    strcpy(
        missions[14].description2,
        "You must respond before the situation gets worse."
    );

    strcpy(missions[14].choices[0], "Investigate alerts");
    strcpy(missions[14].choices[1], "Shut down everything");
    strcpy(missions[14].choices[2], "Follow response plan");

    missions[14].successChance[0] = 80;
    missions[14].successChance[1] = 50;
    missions[14].successChance[2] = 90;

    missions[14].reputationChange[0] = 12;
    missions[14].reputationChange[1] = 15;
    missions[14].reputationChange[2] = 15;

    missions[14].skillChange[0] = 5;
    missions[14].skillChange[1] = 3;
    missions[14].skillChange[2] = 6;

    strcpy(
        missions[14].successMessage[0],
        "You investigated the alerts successfully."
    );

    strcpy(
        missions[14].successMessage[1],
        "The shutdown prevented further activity."
    );

    strcpy(
        missions[14].successMessage[2],
        "You successfully followed the response plan."
    );

    strcpy(
        missions[14].failureMessage[0],
        "The investigation failed."
    );

    strcpy(
        missions[14].failureMessage[1],
        "The shutdown caused additional problems."
    );

    strcpy(
        missions[14].failureMessage[2],
        "The response plan failed."
    );

    strcpy(
        missions[14].awarenessMessage,
        "A prepared incident response plan helps organizations handle incidents."
    );
}

// ============================================================
// ADD HISTORY
// ============================================================

void AddHistory(const char *message)
{
    if (historyCount >= MAX_HISTORY)
        return;

    strcpy(history[historyCount].description, message);

    history[historyCount].reputation =
        player.reputation;

    history[historyCount].skillLevel =
        player.skillLevel;

    historyCount++;
}

// ============================================================
// START RANDOM MISSION
// ============================================================

void StartRandomMission()
{
    currentMission = rand() % 15;

    selectedChoice = -1;

    currentScreen = SCREEN_MISSION;
}

// ============================================================
// RESOLVE CHOICE
// ============================================================

void ResolveChoice(int choice)
{
    if (choice < 0 || choice > 2)
        return;

    Mission *m = &missions[currentMission];

    missionRoll = rand() % 100 + 1;

    if (missionRoll <= m->successChance[choice])
    {
        missionSuccess = true;

        player.reputation +=
            m->reputationChange[choice];

        player.skillLevel +=
            m->skillChange[choice];

        strcpy(
            resultMessage,
            m->successMessage[choice]
        );
    }
    else
    {
        missionSuccess = false;

        player.reputation -=
            m->reputationChange[choice];

        player.skillLevel -= 1;

        strcpy(
            resultMessage,
            m->failureMessage[choice]
        );
    }

    strcpy(
        awarenessMessage,
        m->awarenessMessage
    );

    AddHistory(resultMessage);

    selectedChoice = choice;

    currentScreen = SCREEN_RESULT;
}

// ============================================================
// DRAW PLAYER STATS
// ============================================================

void DrawStats()
{
    DrawRectangle(
        780,
        20,
        290,
        110,
        PANEL
    );

    DrawText(
        "PLAYER STATUS",
        800,
        35,
        20,
        CYAN
    );

    DrawText(
        TextFormat("Alias: %s", player.alias),
        800,
        65,
        18,
        WHITE
    );

    DrawText(
        TextFormat("Reputation: %d", player.reputation),
        800,
        90,
        18,
        YELLOW
    );

    DrawText(
        TextFormat("Skill Level: %d", player.skillLevel),
        800,
        115,
        18,
        GREEN
    );
}

// ============================================================
// ALIAS SCREEN
// ============================================================

void DrawAliasScreen()
{
    ClearBackground(BACKGROUND);

    DrawCenteredText(
        "CYBERPUNK CODEBREAKER",
        100,
        48,
        CYAN
    );

    DrawCenteredText(
        "DIGITAL REBEL",
        160,
        25,
        GREEN
    );

    DrawCenteredText(
        "Enter your player alias",
        240,
        25,
        WHITE
    );

    Rectangle inputBox =
    {
        300,
        300,
        500,
        60
    };

    DrawRectangleRounded(
        inputBox,
        0.15f,
        10,
        PANEL
    );

    DrawText(
        aliasInput,
        320,
        318,
        25,
        WHITE
    );

    DrawText(
        TextFormat("%d/%d", aliasLength, MAX_ALIAS - 1),
        750,
        320,
        18,
        GRAY
    );

    Rectangle startButton =
    {
        400,
        400,
        300,
        60
    };

    if (DrawButton(startButton, "START GAME", GREEN))
    {
        if (aliasLength == 0)
        {
            strcpy(aliasInput, "Digital Rebel");
        }

        strcpy(player.alias, aliasInput);

        player.reputation = 0;
        player.skillLevel = 1;

        currentScreen = SCREEN_MENU;
    }

    DrawCenteredText(
        "Type your alias using the keyboard",
        500,
        18,
        GRAY
    );
}

// ============================================================
// HANDLE ALIAS INPUT
// ============================================================

void HandleAliasInput()
{
    int key = GetCharPressed();

    while (key > 0)
    {
        if (key >= 32 &&
            key <= 125 &&
            aliasLength < MAX_ALIAS - 1)
        {
            aliasInput[aliasLength] =
                (char) key;

            aliasLength++;

            aliasInput[aliasLength] =
                '\0';
        }

        key = GetCharPressed();
    }

    if (IsKeyPressed(KEY_BACKSPACE) &&
        aliasLength > 0)
    {
        aliasLength--;

        aliasInput[aliasLength] =
            '\0';
    }

    if (IsKeyPressed(KEY_ENTER))
    {
        if (aliasLength == 0)
        {
            strcpy(aliasInput, "Digital Rebel");
        }

        strcpy(player.alias, aliasInput);

        currentScreen = SCREEN_MENU;
    }
}

// ============================================================
// MAIN MENU
// ============================================================

void DrawMenu()
{
    ClearBackground(BACKGROUND);

    DrawCenteredText(
        "CYBERPUNK CODEBREAKER",
        70,
        45,
        CYAN
    );

    DrawCenteredText(
        "MISSION CONTROL",
        125,
        22,
        GREEN
    );

    DrawStats();

    Rectangle previewButton =
    {
        350,
        210,
        400,
        60
    };

    Rectangle missionButton =
    {
        350,
        290,
        400,
        60
    };

    Rectangle historyButton =
    {
        350,
        370,
        400,
        60
    };

    Rectangle exitButton =
    {
        350,
        450,
        400,
        60
    };

    if (DrawButton(
            previewButton,
            "PREVIEW MISSIONS",
            CYAN))
    {
        currentScreen =
            SCREEN_MISSIONS;
    }

    if (DrawButton(
            missionButton,
            "PLAY RANDOM MISSION",
            GREEN))
    {
        StartRandomMission();
    }

    if (DrawButton(
            historyButton,
            "MISSION HISTORY",
            YELLOW))
    {
        currentScreen =
            SCREEN_HISTORY;
    }

    if (DrawButton(
            exitButton,
            "EXIT GAME",
            RED))
    {
        currentScreen =
            SCREEN_GAME_COMPLETE;
    }
}

// ============================================================
// MISSION LIST
// ============================================================

void DrawMissionList()
{
    ClearBackground(BACKGROUND);

    DrawCenteredText(
        "MISSION DATABASE",
        40,
        38,
        CYAN
    );

    for (int i = 0; i < 15; i++)
    {
        int column = i / 8;
        int row = i % 8;

        int x = 80 + column * 480;
        int y = 110 + row * 60;

        DrawRectangleRounded(
            (Rectangle)
            {
                x,
                y,
                430,
                45
            },
            0.1f,
            8,
            PANEL
        );

        DrawText(
            TextFormat(
                "%02d. %s",
                i + 1,
                missions[i].title + 10
            ),
            x + 15,
            y + 12,
            17,
            WHITE
        );
    }

    Rectangle backButton =
    {
        400,
        625,
        300,
        50
    };

    if (DrawButton(
            backButton,
            "BACK TO MENU",
            CYAN))
    {
        currentScreen =
            SCREEN_MENU;
    }
}

// ============================================================
// MISSION SCREEN
// ============================================================

void DrawMission()
{
    ClearBackground(BACKGROUND);

    Mission *m =
        &missions[currentMission];

    DrawStats();

    DrawText(
        m->title,
        50,
        50,
        32,
        CYAN
    );

    DrawText(
        m->description1,
        50,
        120,
        21,
        WHITE
    );

    DrawText(
        m->description2,
        50,
        155,
        21,
        WHITE
    );

    DrawText(
        "Choose your action:",
        50,
        215,
        23,
        YELLOW
    );

    for (int i = 0; i < 3; i++)
    {
        Rectangle button =
        {
            80,
            270 + i * 75,
            700,
            55
        };

        if (DrawButton(
                button,
                TextFormat(
                    "%d. %s",
                    i + 1,
                    m->choices[i]
                ),
                PANEL_LIGHT))
        {
            ResolveChoice(i);
        }

        DrawText(
            TextFormat(
                "Success Chance: %d%%",
                m->successChance[i]
            ),
            805,
            285 + i * 75,
            17,
            GRAY
        );
    }

    Rectangle abortButton =
    {
        80,
        510,
        300,
        50
    };

    if (DrawButton(
            abortButton,
            "ABORT MISSION",
            RED))
    {
        currentScreen =
            SCREEN_MENU;
    }

    DrawText(
        "Choose carefully. Your reputation and skill depend on your decisions.",
        80,
        590,
        17,
        GRAY
    );
}

// ============================================================
// RESULT SCREEN
// ============================================================

void DrawResult()
{
    ClearBackground(BACKGROUND);

    if (missionSuccess)
    {
        DrawCenteredText(
            "MISSION SUCCESS!",
            70,
            45,
            GREEN
        );
    }
    else
    {
        DrawCenteredText(
            "MISSION FAILED!",
            70,
            45,
            RED
        );
    }

    DrawCenteredText(
        TextFormat(
            "Random Roll: %d",
            missionRoll
        ),
        140,
        23,
        WHITE
    );

    DrawRectangleRounded(
        (Rectangle)
        {
            150,
            200,
            800,
            120
        },
        0.1f,
        10,
        PANEL
    );

    DrawText(
        resultMessage,
        180,
        235,
        23,
        WHITE
    );

    DrawText(
        "CYBERSECURITY AWARENESS",
        150,
        370,
        24,
        CYAN
    );

    DrawText(
        awarenessMessage,
        150,
        410,
        20,
        WHITE
    );

    DrawStats();

    Rectangle continueButton =
    {
        350,
        540,
        400,
        60
    };

    if (DrawButton(
            continueButton,
            "RETURN TO MENU",
            GREEN))
    {
        currentScreen =
            SCREEN_MENU;
    }
}

// ============================================================
// HISTORY SCREEN
// ============================================================

void DrawHistory()
{
    ClearBackground(BACKGROUND);

    DrawCenteredText(
        "PLAYER LOG HISTORY",
        40,
        38,
        CYAN
    );

    if (historyCount == 0)
    {
        DrawCenteredText(
            "No missions taken yet.",
            250,
            25,
            GRAY
        );
    }
    else
    {
        int visibleEntries = historyCount;

        if (visibleEntries > 8)
            visibleEntries = 8;

        for (int i = 0;
             i < visibleEntries;
             i++)
        {
            int y = 110 + i * 55;

            DrawRectangle(
                70,
                y,
                960,
                45,
                PANEL
            );

            DrawText(
                TextFormat(
                    "%d.",
                    i + 1
                ),
                85,
                y + 12,
                17,
                CYAN
            );

            DrawText(
                history[i].description,
                120,
                y + 12,
                17,
                WHITE
            );

            DrawText(
                TextFormat(
                    "REP: %d",
                    history[i].reputation
                ),
                720,
                y + 12,
                16,
                YELLOW
            );

            DrawText(
                TextFormat(
                    "SKILL: %d",
                    history[i].skillLevel
                ),
                850,
                y + 12,
                16,
                GREEN
            );
        }
    }

    Rectangle backButton =
    {
        400,
        625,
        300,
        50
    };

    if (DrawButton(
            backButton,
            "BACK TO MENU",
            CYAN))
    {
        currentScreen =
            SCREEN_MENU;
    }
}

// ============================================================
// GAME COMPLETE
// ============================================================

void DrawGameComplete()
{
    ClearBackground(BACKGROUND);

    DrawCenteredText(
        "GAME COMPLETE",
        100,
        48,
        CYAN
    );

    DrawCenteredText(
        TextFormat(
            "Final Alias: %s",
            player.alias
        ),
        210,
        25,
        WHITE
    );

    DrawCenteredText(
        TextFormat(
            "Final Reputation: %d",
            player.reputation
        ),
        270,
        25,
        YELLOW
    );

    DrawCenteredText(
        TextFormat(
            "Final Skill Level: %d",
            player.skillLevel
        ),
        330,
        25,
        GREEN
    );

    DrawCenteredText(
        "Thank you for playing",
        430,
        22,
        GRAY
    );

    DrawCenteredText(
        "CYBERPUNK CODEBREAKER",
        470,
        30,
        CYAN
    );

    Rectangle exitButton =
    {
        400,
        550,
        300,
        60
    };

    if (DrawButton(
            exitButton,
            "CLOSE GAME",
            RED))
    {
        gameRunning = false;
    }
}

// ============================================================
// MAIN
// ============================================================

int main()
{
    srand((unsigned int)time(NULL));

    InitializeMissions();

    InitWindow(
        SCREEN_WIDTH,
        SCREEN_HEIGHT,
        "Cyberpunk Codebreaker"
    );

    SetTargetFPS(60);

    while (!WindowShouldClose() && gameRunning)
    {
        // ====================================================
        // UPDATE
        // ====================================================

        if (currentScreen == SCREEN_ALIAS)
        {
            HandleAliasInput();
        }

        // ====================================================
        // DRAW
        // ====================================================

        BeginDrawing();

        switch (currentScreen)
        {
            case SCREEN_ALIAS:
                DrawAliasScreen();
                break;

            case SCREEN_MENU:
                DrawMenu();
                break;

            case SCREEN_MISSIONS:
                DrawMissionList();
                break;

            case SCREEN_MISSION:
                DrawMission();
                break;

            case SCREEN_RESULT:
                DrawResult();
                break;

            case SCREEN_HISTORY:
                DrawHistory();
                break;

            case SCREEN_GAME_COMPLETE:
                DrawGameComplete();
                break;
        }

        EndDrawing();
    }

    CloseWindow();

    return 0;
}