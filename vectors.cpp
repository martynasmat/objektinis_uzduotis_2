#include <iostream>
#include <vector>
#include <chrono>
#include "functions.cpp"

using namespace std;

void sort_students(vector<Student> &stud, vector<Student> &susikaupe, vector<Student> &vargseliai) {
    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < stud.size(); ++i) {
        if (stud.at(i).final_res_med >= 5) {
            std::swap(stud[i], stud.back());
            susikaupe.push_back(std::move(stud.at(i)));
            stud.pop_back();
            --i;
        } else {
            std::swap(stud[i], stud.back());
            vargseliai.push_back(std::move(stud.back()));
            stud.pop_back();
            --i;
        }
    }
    std::chrono::duration<double> diff = std::chrono::high_resolution_clock::now() - start;
    std::cout << "Studentu rusiavimas uztruko " << diff.count() << " s" << std::endl;
}

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
            sort_students(students, susikaupe, vargseliai);
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

