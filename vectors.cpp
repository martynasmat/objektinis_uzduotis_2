#include <iostream>
#include <vector>
#include <chrono>
#include "functions.cpp"

using namespace std;

void sort_students(vector<Student> &stud, vector<Student> &rimciausi, vector<Student> &sukriteliai) {
    for(int i = 0; i < stud.size(); i++) {
        if(stud.at(i).final_res_med >= 5) {
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
                read_data_from_file("testinis.txt", students);
            } else {
                read_data_from_console(students, use_median, generate_marks, generate_names);
            }
            sort_menu(students);
            sort_students(students, rimciausi, sukriteliai);
            if (output_console) {
                avg_median_menu(use_median);
                cout << "Sukriteliai (galutinis balas < 5)" << endl;
                print_data_choice(sukriteliai, sukriteliai.size(), use_median);
                cout << "Rimciausi (galutinis balas >= 5)" << endl;
                print_data_choice(rimciausi, rimciausi.size(), use_median);
            } else {
                print_data_file(sukriteliai, sukriteliai.size(), use_median, "sukriteliai.txt");
                print_data_file(rimciausi, rimciausi.size(), use_median, "rimciausi.txt");
            }
        }
    }
}

