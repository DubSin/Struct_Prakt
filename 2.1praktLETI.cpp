#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>
using namespace std;

struct Student {
    string name;
    string surname;
    string sex;
    int numberGroup;
    int id;
    int evaluations[8];
    float average;
};

vector<Student> students;
const int evaluationsCount = 8;
const string fileName = "students.txt";


vector<Student> loadStudents() {
    vector<Student> students;
    ifstream file(fileName);
    if (file.is_open()) {
        Student student;
        while (file >> student.name >> student.surname >> student.sex >> student.numberGroup >> student.id) {
            for (int i = 0; i < evaluationsCount; i++) {
                file >> student.evaluations[i];
            }
            file >> student.average;
            students.push_back(student);
        }
        file.close();
    }
    return students;
}

void saveStudents(const vector<Student>& students) {
    ofstream file(fileName);
    if (file.is_open()) {
        for (const auto& student : students) {
            file << student.name << " " << student.surname << " " << student.sex << " " << student.numberGroup << " " << student.id << " ";
            for (int i = 0; i < evaluationsCount; i++) {
                file << student.evaluations[i] << " ";
            }
            file << student.average << endl;
        }
        file.close();
    }
}


bool isUnique(const vector<Student>& students, int numberGroup, int id) {
    for (const auto& student : students) {
        if (student.numberGroup == numberGroup && student.id == id) {
            return false;
        }
    }
    return true;
}


void addStudents() {
    Student student;
    float average = 0;
    int count;
    auto existingStudents = loadStudents();

    cout << "Введите имя студента: ";
    cin.ignore();
    getline(cin, student.name);
    cout << "Введите фамилию студента: ";
    cin.ignore();
    getline(cin, student.surname);

    cout << "Введите пол студента(M/F): ";
    cin >> student.sex;
    while (student.sex != "M" && student.sex != "F") {
        cout << "Некорректный ввод. Введите только M или F: ";
        cin >> student.sex;
    }

    cout << "Введите группу студента: ";
    cin >> student.numberGroup;
    while (student.numberGroup < 1000 && student.numberGroup > 10000) {
        cout << "Введите существующую группу (от 1000 до 10000): ";
        cin >> student.numberGroup;
    }

    cout << "Введите количество студентов в группе: ";
    cin >> count;
    while (count > 50 && count < 1) {
        cout << "Некорректный ввод. Введите корректное количество студентов (от 1 до 50): ";
        cin >> count;
    }

    cout << "Введите номер в списке: ";
    cin >> student.id;
    while (student.id > count && student.id < 1) {
        cout << "Некорректный ввод. Введите корректный номер в списке (от 1 до " << count << "): ";
        cin >> student.id;
    }

    while (!isUnique(existingStudents, student.numberGroup, student.id)) {
        cout << "Студент с такой группой и номером в списке уже существует. Введите другие данные." << endl;

        cout << "Введите группу студента: ";
        cin >> student.numberGroup;
        while (student.numberGroup < 1000 && student.numberGroup > 10000) {
            cout << "Введите существующую группу (от 1000 до 10000): ";
            cin >> student.numberGroup;
        }

        cout << "Введите номер в списке: ";
        cin >> student.id;
        while (student.id > count && student.id < 1) {
            cout << "Некорректный ввод. Введите корректный номер в списке (от 1 до " << count << "): ";
            cin >> student.id;
        }
    }

    cout << "Введите оценки студента: " << endl;
    for (int i = 0; i < evaluationsCount; i++) {
        cin >> student.evaluations[i];
        if (student.evaluations[i] < 3 && student.evaluations[i] > 5) {
            cout << "Введите существующую оценку (от 3 до 5)!: ";
            i--;
        }
        else {
            average += student.evaluations[i];
        }
    }
	student.average = average / evaluationsCount;
    cout << "Средний балл: " << student.average << endl;
    existingStudents.push_back(student);
    saveStudents(existingStudents);
    cout << "Студент добавлен" << endl;
}

void makingChanges() {
    int id, group;
    cout << "Введите id студента: ";
    cin >> id;
    cout << "Введите группу студента: ";
    cin >> group;

    auto students = loadStudents();
    bool isFound = false;

    for (auto& student : students) {
        if (student.id == id && student.numberGroup == group) {
            cin.ignore();
            cout << "Введите новое имя студента: ";
            getline(cin, student.name);
            cin.ignore();
            cout << "Введите новую фамилию студента: ";
            getline(cin, student.surname);

            cout << "Введите новый пол студента (M/F): ";
            cin >> student.sex;
            while (student.sex != "M" && student.sex != "F") {
                cout << "Некорректный ввод. Введите только M или F: ";
                cin >> student.sex;
            }

            cout << "Введите новый номер группы: ";
            cin >> student.numberGroup;
            while (student.numberGroup < 1000 && student.numberGroup > 10000) {
                cout << "Введите существующую группу (от 1000 до 10000): ";
                cin >> student.numberGroup;
            }

            cout << "Введите новый номер в списке: ";
            cin >> student.id;
            while (student.id < 1) {
                cout << "Некорректный ввод. Введите корректный номер в списке: ";
                cin >> student.id;
            }
            while (!isUnique(students, student.numberGroup, student.id)) {
                cout << "Студент с такой группой и номером в списке уже существует. Введите другие данные." << endl;

                cout << "Введите группу студента: ";
                cin >> student.numberGroup;
                while (student.numberGroup < 1000 && student.numberGroup > 10000) {
                    cout << "Введите существующую группу (от 1000 до 10000): ";
                    cin >> student.numberGroup;
                }

                cout << "Введите номер в списке: ";
                cin >> student.id;
                while (student.id > 50 && student.id < 1) {
                    cout << "Некорректный ввод. Введите корректный номер в списке (от 1 до 50 ): ";
                    cin >> student.id;
                }
            }
            cout << "Введите новые оценки студента: " << endl;
            float average = 0;
            for (int i = 0; i < evaluationsCount; i++) {
                cin >> student.evaluations[i];
                if (student.evaluations[i] < 3 && student.evaluations[i] > 5) {
                    cout << "Введите существующую оценку (от 3 до 5)!: ";
                    i--;
                }
                else {
                    average += student.evaluations[i];
                }
            }
            student.average = average / evaluationsCount;

            isFound = true;
            break;
        }
    }

    if (isFound) {
        saveStudents(students);
        cout << "Данные обновлены" << endl;
    }
    else {
        cout << "Студент не найден." << endl;
    }
}


void displayAllStudents() {
    auto students = loadStudents();
    for (const auto& student : students) {
        cout << "Имя: " << student.name << ", Фамилия: " << student.surname << ", Пол: " << student.sex
            << ", Группа: " << student.numberGroup << ", Номер в списке: " << student.id
            << ", Средний балл: " << student.average << endl;
    }
}

void displayAllStudentsInGroup() {
    int group;
    cout << "Введите номер группы: ";
    cin >> group;

    auto students = loadStudents();
    for (const auto& student : students) {
        if (student.numberGroup == group) {
            cout << "Номер в списке: " << student.id << ", Имя: " << student.name << ", Фамилия: " << student.surname
                << ", Пол: " << student.sex << ", Средний балл: " << student.average << endl;
        }
    }
}

void displayTopStudents() {
    auto students = loadStudents();
    sort(students.begin(), students.end(), [](const Student& a, const Student& b) {
        return a.average > b.average;
        });

    cout << "Топ студентов:" << endl;
    for (const auto& student : students) {
        cout << "Номер в списке: " << student.id << ", Имя: " << student.name << ", Фамилия: " << student.surname
            << ", Средний балл: " << student.average << endl;
    }
}

void countSex() {
    auto students = loadStudents();
    int countMale = 0, countFemale = 0;

    for (const auto& student : students) {
        if (student.sex == "M") countMale++;
        else if (student.sex == "F") countFemale++;
    }

    cout << "Мужчины: " << countMale << ", Женщины: " << countFemale << endl;
}

void scholarship() {
    auto students = loadStudents();

    cout << "Студенты, не получающие стипендию: " << endl;
    for (const auto& student : students) {
        bool hasLowGrades = false;
        for (int i = 0; i < evaluationsCount; i++) {
            if (student.evaluations[i] == 3) {
                hasLowGrades = true;
                break;
            }
        }
        if (hasLowGrades) {
            cout << "Имя: " << student.name << ", Фамилия: " << student.surname << ", Пол: " << student.sex
                << ", Группа: " << student.numberGroup << ", Номер в списке: " << student.id
                << ", Средний балл: " << student.average << endl;
        }
    }

    cout << "Студенты, учащиеся только на «отлично»: " << endl;
    for (const auto& student : students) {
        bool allExcellent = true;
        for (int i = 0; i < evaluationsCount; i++) {
            if (student.evaluations[i] != 5) {
                allExcellent = false;
                break;
            }
        }
        if (allExcellent) {
            cout << "Имя: " << student.name << ", Фамилия: " << student.surname << ", Пол: " << student.sex
                << ", Группа: " << student.numberGroup << ", Номер в списке: " << student.id
                << ", Средний балл: " << student.average << endl;
        }
    }

    cout << "Студенты, учащиеся только на «хорошо» и «отлично»: " << endl;
    for (const auto& student : students) {
        bool goodAndExcellent = true;
        for (int i = 0; i < evaluationsCount; i++) {
            if (student.evaluations[i] != 4 && student.evaluations[i] != 5) {
                goodAndExcellent = false;
                break;
            }
        }
        if (goodAndExcellent) {
            cout << "Имя: " << student.name << ", Фамилия: " << student.surname << ", Пол: " << student.sex
                << ", Группа: " << student.numberGroup << ", Номер в списке: " << student.id
                << ", Средний балл: " << student.average << endl;
        }
    }
}

void numberGroup() {
    int id;
    cout << "Введите id студента: ";
    cin >> id;

    auto students = loadStudents();
    for (const auto& student : students) {
        if (student.id == id) {
            cout << "Имя: " << student.name << ", Фамилия: " << student.surname << ", Пол: " << student.sex
                << ", Группа: " << student.numberGroup
                << ", Средний балл: " << student.average << endl;
            return;
        }
    }
    cout << "Студент с таким номером не найден." << endl;
}

int main() {
    setlocale(LC_ALL, "RU");
    int choice;
    do {
        cout << "1. Добавить студента\n2. Изменить студента\n3. Вывести всех студентов\n"
            << "4. Вывести студентов группы\n5. Топ студентов\n6. Количество студентов по полу\n"
            << "7. Информация о стипендиях\n8. Найти студента по номеру в списке\n9. Удалить файл\n0. Выход\n";
        cin >> choice;
        switch (choice) {
        case 1: addStudents(); break;
        case 2: makingChanges(); break;
        case 3: displayAllStudents(); break;
        case 4: displayAllStudentsInGroup(); break;
        case 5: displayTopStudents(); break;
        case 6: countSex(); break;
        case 7: scholarship(); break;
        case 8: numberGroup(); break;
        case 9:
            if (remove(fileName.c_str())) {
                cout << "Ошибка: не удалось удалить файл " << fileName << endl;
            }
            else {
                cout << "Файл успешно удален" << endl;
            };
            break;
        case 0: break;
        default: cout << "Неверный выбор." << endl;
        }
    } while (choice != 0);

    return 0;
}
