#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <cmath>
#include <algorithm>
#include <cctype>
#include <fstream>
#include <chrono>

using namespace std;

const int NAME_MAX_SYMBOLS = 20;
const int NAME_MIN_SYMBOLS = 2;
const int MIN_MARK = 2;
const int MAX_MARK = 10;
const int NAME_COUNT = 10;
const vector <string> NAMES = {"Dominykas", "Lukas", "Matas", "Benas", "Augustas", "Martynas", "Jonas", "Ignas", "Emilis", "Adomas"};
const vector <string> SURNAMES = {"Kazlauskas", "Petrauskas", "Jankauskas", "Butkus", "Paulauskas", "Vasiliauskas", "Baranauskas", "Urbonas", "Navickas", "Ramanauskas"};

struct Vector {
    string name, last_name;
    vector <int> hw_res;
    int exam_res = 0;
    float final_res_avg = 0, final_res_med = 0, final_hw_avg = 0, final_hw_med = 0;
};

class Student {
    private:
        string name;
        string last_name;
        vector <int> hw_res;
        int exam_res = 0;
        float final_res_avg = 0;
        float final_res_med = 0;
        float final_hw_avg = 0;
        float final_hw_med = 0;
    public:
        Student() = default;
        Student(string name, string last_name, vector<int> hw_results, int exam_result) {
            this->name = name;
            this->last_name = last_name;
            this->hw_res = hw_results;
            this->exam_res = exam_result;
        };

        void set_full_name(string name, string last_name) {
            this->name = name;
            this->last_name = last_name;
        };

        void set_hw(vector<int> hw) {
            this->hw_res = std::move(hw);
        };

        void enter_hw(int mark) {
            this->hw_res.push_back(mark);
        };

        void enter_exam(int mark) {
            this->exam_res = mark;
        };

        void calc_final_avg() {
            this->final_res_avg = 0.4 * this->final_hw_avg + 0.6 * (float)this->exam_res;
        };
        void calc_final_med() {
            this->final_res_med = 0.4 * this->final_hw_med + 0.6 * (float)this->exam_res;
        };
        void calc_final_average_hw() {
            int vec_size = this->hw_res.size();
            int sum = 0;
            for(int i = 0; i < vec_size; i++) {
                sum += this->hw_res.at(i);
            }

            if(vec_size > 0) {
                this->final_hw_avg = (float)sum / (float)vec_size;
            }else {
                this->final_hw_avg = 0.0;
            }
        };
        void calc_final_median_hw() {
            sort(this->hw_res.begin(), this->hw_res.end());
            int vec_size = this->hw_res.size();
            int size_divided = ceil(vec_size / 2.0);

            // If there are no entries, median = 0.0
            if(vec_size > 0) {
                if (vec_size % 2 == 0) {
                    // If number of entries is even, median is calculated by taking the average of the 2 middle numbers.
                    this->final_hw_med = (float)(this->hw_res.at(size_divided - 1) + this->hw_res.at(size_divided)) / 2.0;
                } else {
                    // If number of entries is odd, median is the middle entry.
                    this->final_hw_avg = (float)this->hw_res.at(size_divided - 1);
                }
            }else {
                this->final_hw_avg = 0.0;
            }
        };
        string get_name() {
            return this->name;
        };
        string get_last_name() {
            return this->last_name;
        };
        float get_final_res_med() {
            return this->final_res_med;
        };
        float get_final_res_avg() {
            return this->final_res_avg;
        };
};

void sort_students(vector<Student> &stud, vector<Student> &susikaupe, vector<Student> &vargseliai);
void generate_file();
void clear_stream();
void main_menu(int &menu_choice, bool &read_from_file, bool &generate_marks, bool &generate_names);
void output_menu(bool &output_console);
void avg_median_menu(bool &use_median);
void sort_menu(vector <Student> &students);
bool compare_name(Student first, Student second);
bool compare_last_name(Student first, Student second);
bool compare_avg(Student first, Student second);
bool compare_med(Student first, Student second);
string generate_surname();
string generate_name();
int generate_mark();
bool valid_mark(int input);
bool valid_alphabet(string input);
void read_data_from_file(const string& file_name, vector <Student> &stud);
void read_data_from_console(vector <Student> &stud, bool use_median, bool gen_marks, bool gen_names);
float average(vector <int> &res);
float median(vector <int> &res);
float final(float hw, int exam);
void print_data_choice(vector <Student> &stud, int num, bool use_median);
void print_data_file(vector <Student> &stud, int num, bool use_median);

