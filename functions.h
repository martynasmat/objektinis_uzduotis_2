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

struct Student {
    string name, last_name;
    vector <int> hw_res;
    int exam_res = 0;
    float final_res_avg = 0, final_res_med = 0, final_hw_avg = 0, final_hw_med = 0;
};

void clear_stream();
void main_menu(int &menu_choice, bool &read_from_file, bool &generate_marks, bool &generate_names);
void output_menu(bool &output_console);
void avg_median_menu(bool &use_median);
void sort_menu(vector <Student> &students);
bool compare_name(const Student& first, const Student& second);
bool compare_last_name(const Student& first, const Student& second);
bool compare_avg(const Student& first, const Student& second);
bool compare_med(const Student& first, const Student& second);
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

