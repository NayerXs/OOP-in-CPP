#include <iostream>
#include <string>
using namespace std;

// Tema Utama: RPG Game
// ---------------------------------------------------------
string congratulationTxt = "Congratulations, Adventurer! You have reached level: ";
string announch = "You have unlocked a new skill!\nCheck your skill in status info!";

// ---------------------------------------------------------
// Abstract Class (Abstraction)
class CharacterBase {
public:
    virtual void showStatus() = 0;
    virtual void decisionUser() = 0;
};

// ---------------------------------------------------------
class MenuOption {
protected:
    string userPick;
public:
    void showMenu() {
        cout << "\n===== GAME MENU =====\n";
        cout << "1. Open Status\n";
        cout << "2. Save Game\n";
        cout << "3. Load Game\n";
        cout << "4. Back to Main Menu\n";
        cout << "Choose: ";
        cin >> userPick;
    }
    string getUserPick() const { 
        return userPick; }
};

// ---------------------------------------------------------
// Class SkillManager: CRUD sederhana untuk skill karakter
class SkillManager {
private:
    string skills[10];
    int skillCount = 0;

public:
    void addSkill(string skill) { // Create
        if (skillCount < 10) {
            skills[skillCount++] = skill;
            cout << "Skill '" << skill << "' added!\n";
        } else {
            cout << "Skill list full!\n";
        }
    }

    void showSkills() { // Read
        cout << "\n=== Skill List ===\n";
        if (skillCount == 0) cout << "No skills learned yet.\n";
        else {
            for (int i = 0; i < skillCount; i++)
                cout << i + 1 << ". " << skills[i] << endl;
        }
    }

    void updateSkill(int index, string newSkill) { // Update
        if (index >= 0 && index < skillCount) {
            cout << "Skill '" << skills[index] << "' updated to '" << newSkill << "'.\n";
            skills[index] = newSkill;
        } else {
            cout << "Invalid index!\n";
        }
    }

    void deleteSkill(int index) { // Delete
        if (index >= 0 && index < skillCount) {
            cout << "Skill '" << skills[index] << "' removed.\n";
            for (int i = index; i < skillCount - 1; i++)
                skills[i] = skills[i + 1];
            skillCount--;
        } else {
            cout << "Invalid index!\n";
        }
    }
};

// ---------------------------------------------------------
class mainCharStatus : public CharacterBase {
protected:
    string username;
    int charlevel;
    float XP;
    string levelUpSkill;

public:
    mainCharStatus(string name = "MC", int level = 1, float exp = 0.0) {
        username = name;
        charlevel = level;
        XP = exp;
        levelUpSkill = "Locked";
    }

    void showStatus() override {
        cout << "Name: " << username << "\nLevel: " << charlevel << "\nXP: " << XP << "\n";
    }

    int getLevel() const { 
        return charlevel; 
    }
    string getName() const { return 
        username; 
    }
    string getSkillStatus() const { return 
        levelUpSkill; 
    }

    void setLevel(int newLevel) { 
        charlevel = newLevel; 
    }
    void setSkillStatus(string newSkill) { 
        levelUpSkill = newSkill; 
    }

    virtual void decisionUser() override {
        cout << "Base character has no specific decision logic yet.\n";
    }
};

// ---------------------------------------------------------
class adventureRoute {
protected:
    string userPick;
public:
    void showRouteMenu() {
        cout << "\n===== ADVENTURE MENU =====\n";
        cout << "1. Continue\n";
        cout << "2. Rest\n";
        cout << "3. Train\n";
        cout << "4. Option\n";
        cout << "Choose: ";
        cin >> userPick;
    }
    string getUserPick() const { return userPick; }
};

// ---------------------------------------------------------
class charRole : public mainCharStatus {
protected:
    string decision;
    string newSkill;
    int upgradedLevelSkill;
    MenuOption menu;
    SkillManager skillManager; // Komposisi CRUD

public:
    charRole(string name = "MC", int level = 1, float exp = 0.0)
        : mainCharStatus(name, level, exp) {}

    void decisionUser() override {
        cout << congratulationTxt << (1 + charlevel) << "!\n" << announch << "\n\n";
        cout << "Choose your next action (Train / Rest / Skill): ";
        cin >> decision;

        cout << "\n=== RESULT ===\n";
        if (decision == "Train" || decision == "train") {
            newSkill = "Fireball";
            upgradedLevelSkill = charlevel + 1;
            setLevel(upgradedLevelSkill);
            setSkillStatus(newSkill);
            skillManager.addSkill(newSkill);
        } 
        else if (decision == "Rest" || decision == "rest") {
            cout << "You decided to rest and recover your stamina.\n";
        } 
        else if (decision == "Skill" || decision == "skill") {
            int choice;
            cout << "\n1. Show Skills\n2. Update Skill\n3. Delete Skill\nChoose: ";
            cin >> choice;

            if (choice == 1) skillManager.showSkills();
            else if (choice == 2) {
                int idx; string newSkill;
                skillManager.showSkills();
                cout << "Enter index to update: "; cin >> idx;
                cout << "Enter new skill name: "; cin >> newSkill;
                skillManager.updateSkill(idx - 1, newSkill);
            }
            else if (choice == 3) {
                int idx;
                skillManager.showSkills();
                cout << "Enter index to delete: "; cin >> idx;
                skillManager.deleteSkill(idx - 1);
            }
        } 
        else {
            cout << "Invalid choice. Nothing happens.\n";
        }
    }

    void showStatus() override {
        cout << "\n===== Character Status =====\n";
        cout << "Role: Wizard\n";
        mainCharStatus::showStatus();
        cout << "Unlocked Skill: " << getSkillStatus() << "\n";
    }
};

// ---------------------------------------------------------
int main() {
    CharacterBase* player = new charRole("Anza", 1, 0.0);

    player->decisionUser();
    player->showStatus();

    delete player;
    return 0;
}
