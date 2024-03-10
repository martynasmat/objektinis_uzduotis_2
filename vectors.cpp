#include <iostream>
#include <vector>
#include <chrono>
#include "functions.cpp"

using namespace std;

void sort_students(vector<Student> &stud, vector<Student> &rimciausi, vector<Student> &sukriteliai) {
    for(int i = 0; i < stud.size(); i++) {
        if(stud.at(i).final_hw_med >= 5) {
            rimciausi.push_back(stud.at(i));
            stud.erase(stud.begin() + i);
        }else {
            sukriteliai.push_back(stud.at(i));
            stud.erase(stud.begin() + i);
        }
    }
}

int main() {
    while(true) {
        vector<Student> students, rimciausi, sukriteliai;
        bool output_console = false;
        bool generate_marks = false;
        bool generate_names = false;
        bool read_from_file = false;
        bool generate_file_var = false;
        bool use_median = false;
        int menu_choice = 5;

        main_menu(menu_choice, read_from_file, generate_marks, generate_names, generate_file_var);
        output_menu(output_console);
        clear_stream();
        srand(time(nullptr));
        if (generate_file_var) {
            generate_file();
        } else {
            if (read_from_file) {
                string file_name;
                while(true) {
                    cout << "Iveskite failo pavadinima: ";
                    cin >> file_name;

                    ofstream file(file_name);
                    if(!file) {
                        cout << "Ivedete bloga failo pavadinima." << endl;
                    }else {
                        file.close();
                        break;
                    }
                }
                read_data_from_file("studentai100000.txt", students);
            } else {
                read_data_from_console(students, use_median, generate_marks, generate_names);
            }
            sort_students(students, rimciausi, sukriteliai);
            sort_menu(students);
            if (output_console) {
                avg_median_menu(use_median);
                print_data_choice(students, students.size(), use_median);
            } else {
                print_data_file(students, students.size(), use_median);
            }
        }
    }
}

