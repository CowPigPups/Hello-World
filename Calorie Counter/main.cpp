#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <limits>

using namespace std;

// ��������� ��� �������� ���������� � ������������
struct User {
    string username; // ��� ������������
    string password; // ������
    double height;   // ����
    double weight;   // ���
};

// ��������� ��� �������� ���������� � ���������
struct Food {
    string name;     // �������� ��������
    double calories; // ���������� �������
};

// ����� ��� ������ � ����� ������
class Database {
public:
    // ���������� ������������ � ���� ������
    void addUser(const User& user) {
        users[user.username] = user;
    }

    // ���������� ���������� � ��������� ��� ������������
    void addFood(const string& username, const Food& food) {
        foodIntake[username].push_back(food);
    }

    // ��������� ������ ���������� �������, ������������ �������������
    double getTotalCalories(const string& username) {
        double total = 0.0;
        for (const auto& food : foodIntake[username]) {
            total += food.calories;
        }
        return total;
    }

private:
    unordered_map<string, User> users;               // ���� ������ �������������
    unordered_map<string, vector<Food>> foodIntake;  // ���� ������ ���������, ������������ ��������������
};

// ������� ��� ������� ����� � ������ ������
void clearInput() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

// ������� ����������� ������������
void registerUser(Database& db) {
    User user;
    cout << "������� ��� ������������: ";
    cin >> user.username;
    clearInput();
    cout << "������� ������: ";
    cin >> user.password;
    clearInput();
    cout << "������� ���� (� ��): ";
    while (!(cin >> user.height)) {
        cout << "������������ ����. ������� ���� (� ��): ";
        clearInput();
    }
    clearInput();
    cout << "������� ��� (� ��): ";
    while (!(cin >> user.weight)) {
        cout << "������������ ����. ������� ��� (� ��): ";
        clearInput();
    }
    clearInput();

    db.addUser(user);
}

// ������� ��� ���������� ���������� � ������������ ���������
void addFoodIntake(Database& db, const string& username) {
    Food food;
    cout << "������� �������� ��������: ";
    cin >> food.name;
    clearInput();
    cout << "������� ���������� �������: ";
    while (!(cin >> food.calories)) {
        cout << "������������ ����. ������� ���������� �������: ";
        clearInput();
    }
    clearInput();

    db.addFood(username, food);
}

// ������� ��� ��������� ������ ���������� ������������ �������
void viewTotalCalories(Database& db, const string& username) {
    double totalCalories = db.getTotalCalories(username);
    cout << "����� ���������� ������������ ������� ��� " << username << ": " << totalCalories << " ����" << endl;
}

// ������� ��� ����������� ����
void displayMenu() {
    cout << "1. �����������" << endl;
    cout << "2. �������� ���������� � ���������" << endl;
    cout << "3. ���������� ����� ���������� �������" << endl;
    cout << "4. �����" << endl;
}

// ������� �������
int main() {
    Database db;
    int choice;
    string username;

    while (true) {
        displayMenu();
        cin >> choice;
        clearInput(); // ������� ����� ����� ������

        switch (choice) {
        case 1:
            registerUser(db);
            break;
        case 2:
            cout << "������� ��� ������������: ";
            cin >> username;
            clearInput();
            addFoodIntake(db, username);
            break;
        case 3:
            cout << "������� ��� ������������: ";
            cin >> username;
            clearInput();
            viewTotalCalories(db, username);
            break;
        case 4:
            return 0;
        default:
            cout << "������������ �����. ����������, ���������� �����." << endl;
        }
    }

    return 0;
}
