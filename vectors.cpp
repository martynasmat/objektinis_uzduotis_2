#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <chrono>
#include "functions.cpp"

using namespace std;

void main_menu(bool &entered, int &menu_choice, bool &read_from_file, bool &generate_marks, bool &generate_names) {
    while (!entered) {
        cout << "\n----- Pagrindinis meniu -----\n1 - vesti duomenis ranka;\n2 - skaityti duomenis is failo;\n3 - generuoti pazymius;\n4 - generuoti visus duomenis;\n5 - baigti darba;\n\nIvesti pasirinkima:";
        if (!(cin >> menu_choice)) {
            cout << "Bloga ivestis, bandykite dar karta" << endl << endl;
        } else {
            switch(menu_choice) {
                case 1:
                    entered = true;
                    break;
                case 2:
                    entered = true;
                    read_from_file = true;
                    break;
                case 3:
                    entered = true;
                    generate_marks = true;
                    break;
                case 4:
                    entered = true;
                    generate_marks = true;
                    generate_names = true;
                    break;
                case 5:
                    exit(0);
                default:
                    cout << "Bloga ivestis, galima ivesti tik nurodytus pasirinkimus" << endl << endl;
                    break;
            }
        }
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}

void output_menu(bool &entered, bool &output_console) {
    string output_choice;
    entered = false;
    while(!entered) {
        cout << "Isvesti ekrane ar faile? (e - ekrane, f - faile):";
        cin >> output_choice;
        try {
            if (output_choice == "e") {
                output_console = true;
                entered = true;
            } else if (output_choice == "f") {
                output_console = false;
                entered = true;
            } else {
                throw(0);
            }
        }
        catch (...){
            cout << "Bloga ivestis, bandykite dar karta." << endl << endl;
        }
    }
}

int main() {
    while(true) {
        vector<Student> students;
        bool entered = false;
        bool output_console = false;
        bool generate_marks = false;
        bool generate_names = false;
        bool read_from_file = false;
        bool use_median = false;
        int menu_choice = 5;

        main_menu(entered, menu_choice, read_from_file, generate_marks, generate_names);
        output_menu(entered, output_console);
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        if (read_from_file) {
            read_data_from_file("studentai100000.txt", students);
        }else {
            read_data_from_console(students, use_median, generate_marks, generate_names);
        }

        entered = false;
        int sort_choice;
        while (!entered) {
            cout << "\nRusiuoti pagal:\n1 - varda;\n2 - pavarde;\n3 - vidurki;\n4 - mediana;\n\nIvesti pasirinkima:";
            if (!(cin >> sort_choice)) {
                cout << "Bloga ivestis, bandykite dar karta" << endl << endl;
            } else {
                auto start = std::chrono::high_resolution_clock::now(); auto st = start;
                switch(sort_choice) {
                    case 1:
                        sort(students.begin(), students.end(), compare_name);
                        entered = true;
                        break;
                    case 2:
                        sort(students.begin(), students.end(), compare_last_name);
                        entered = true;
                        break;
                    case 3:
                        sort(students.begin(), students.end(), compare_avg);
                        entered = true;
                        break;
                    case 4:
                        sort(students.begin(), students.end(), compare_med);
                        entered = true;
                        break;
                    default:
                        cout << "Bloga ivestis, galima ivesti tik nurodytus pasirinkimus" << endl << endl;
                        break;
                }
                std::chrono::duration<double> diff = std::chrono::high_resolution_clock::now() - start;
                cout << "Masyvo rusiavimas uztruko " << diff.count() << " s" << endl;
            }
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }

        if (output_console) {
            entered = false;
            while (!entered) {
                cout << "Naudoti vidurki ar mediana? (0 - vidurkis, 1 - mediana):";
                if (cin >> use_median) {
                    if (use_median != 0 && use_median != 1) {
                        cout << "Bloga ivestis, galima ivesti tik 0 arba 1." << endl << endl;
                    } else {
                        entered = true;
                    }
                } else {
                    cout << "Bloga ivestis, bandykite dar karta" << endl << endl;
                }
                cin.clear();
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }

            print_data_choice(students, students.size(), use_median);
        }else {
            print_data_file(students, students.size(), use_median);
        }
    }
}

