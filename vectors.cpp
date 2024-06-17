#include <iostream>
#include <vector>
#include <chrono>
#include "functions.cpp"

using namespace std;

int main() {
    while(true) {
        vector<Student> students, susikaupe, vargseliai;
        bool output_console = false;
        bool generate_marks = false;
        bool generate_names = false;
        bool read_from_file = false;
        bool generate_file_var = false;
        bool use_median = false;
        int menu_choice = 5;

        main_menu(menu_choice, read_from_file, generate_marks, generate_names, generate_file_var);
        srand(time(nullptr));
        if (generate_file_var) {
            generate_file();
        } else {
            if (read_from_file) {
                read_data_from_file("studentai1000.txt", students);
            } else {
                read_data_from_console(students, use_median, generate_marks, generate_names);
            }
            output_menu(output_console);
            clear_stream();
            sort_students(students, susikaupe, vargseliai);
            sort_menu(susikaupe, vargseliai);
            if (output_console) {
                avg_median_menu(use_median);
                cout << "Vargseliai (galutinis balas < 5)" << endl;
                print_data_choice(vargseliai, vargseliai.size(), use_median);
                cout << "Susikaupe (galutinis balas >= 5)" << endl;
                print_data_choice(susikaupe, susikaupe.size(), use_median);
            } else {
                print_data_file(vargseliai, vargseliai.size(), use_median, "vargseliai.txt");
                print_data_file(susikaupe, susikaupe.size(), use_median, "susikaupe.txt");
            }
        }
    }
}

