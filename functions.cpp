#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <cmath>
#include <algorithm>
#include <cctype>
#include <fstream>
#include <chrono>
#include "functions.h"

using namespace std;

void sort_students(vector<Student> &stud, vector<Student> &susikaupe, vector<Student> &vargseliai) {
    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < stud.size(); i++) {
        if (stud.at(i).get_final_res_med() >= 5) {
            std::swap(stud.at(i), stud.back());
            susikaupe.push_back(std::move(stud.back()));
            stud.pop_back();
            i--;
        } else {
            std::swap(stud.at(i), stud.back());
            vargseliai.push_back(std::move(stud.back()));
            stud.pop_back();
            i--;
        }
    }
    std::chrono::duration<double> diff = std::chrono::high_resolution_clock::now() - start;
    std::cout << "Studentu rusiavimas uztruko " << diff.count() << " s" << std::endl;
}

void generate_file() {
    int student_num = 0, hw_num = 0, width = 20, width_hw = 10;
    string file_name;
    bool entered = false;
    ofstream file;
    
    while (!entered) {
        cout << "Iveskite studentu skaiciu: ";
        if (cin >> student_num) {
            entered = true;
        } else {
            cout <<  "Bloga ivestis, galima ivesti tik sveikuosius skaicius." << endl << endl;
        }
        clear_stream();
    }

    entered = false;
    while (!entered) {
        cout << "Iveskite namu darbu pazymiu skaiciu: ";
        if (cin >> hw_num) {
            entered = true;
        } else {
            cout <<  "Bloga ivestis, galima ivesti tik sveikuosius skaicius." << endl << endl;
        }
        clear_stream();
    }
    
    while(true) {
        cout << "Iveskite failo pavadinima: ";
        cin >> file_name;
        
        file = ofstream(file_name);
        if(!file) {
            cout << "Ivedete bloga failo pavadinima." << endl;   
        }else {
            break;
        }
    }

    auto start = std::chrono::high_resolution_clock::now();
    file << left << setw(width) << "Vardas";
    file << right << setw(width) << "Pavarde";
    for(int i = 0; i < hw_num; i++) {
        file << right << setw(width_hw) << "ND" + to_string(i + 1);
    }
    file << right << setw(width_hw) << "Egz.";
    for(int i = 0; i < student_num; i++) {
        file << endl << left << setw(width) << "Vardenis" + to_string(i + 1);
        file << right << setw(width) << "Pavardenis" + to_string(i + 1);
        for(int j = 0; j < hw_num; j++) {
            file << right << setw(width_hw) << generate_mark();
        }
        file << right << setw(width_hw) << generate_mark();
    }
    file.close();
    std::chrono::duration<double> diff = std::chrono::high_resolution_clock::now() - start;
    std::cout << "Failo generavimas " << diff.count() << " s" << std::endl;
}

void clear_stream() {
    cin.clear();
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void main_menu(int &menu_choice, bool &read_from_file, bool &generate_marks, bool &generate_names, bool &generate_files) {
    bool entered = false;
    while (!entered) {
        cout << "\n----- Pagrindinis meniu -----\n1 - vesti duomenis ranka;\n2 - skaityti duomenis is failo;\n3 - generuoti pazymius;\n4 - generuoti visus duomenis;\n5 - generuoti faila;\n6 - baigti darba;\n\nIvesti pasirinkima:";
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
                    entered = true;
                    generate_files = true;
                    break;
                case 6:
                    exit(0);
                default:
                    cout << "Bloga ivestis, galima ivesti tik nurodytus pasirinkimus" << endl << endl;
                    break;
            }
        }
        clear_stream();
    }
}

void output_menu(bool &output_console) {
    string output_choice;
    bool entered = false;
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

void avg_median_menu(bool &use_median) {
    bool entered = false;
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
        clear_stream();
    }
}

void sort_menu(vector <Student> &good, vector <Student> &bad) {
    int sort_choice;
    bool entered = false;
    while (!entered) {
        cout << "\nRusiuoti pagal:\n1 - varda;\n2 - pavarde;\n3 - vidurki;\n4 - mediana;\n\nIvesti pasirinkima:";
        if (!(cin >> sort_choice)) {
            cout << "Bloga ivestis, bandykite dar karta" << endl << endl;
        } else {
            auto start = std::chrono::high_resolution_clock::now(); auto st = start;
            switch(sort_choice) {
                case 1:
                    sort(good.begin(), good.end(), compare_name);
                    sort(bad.begin(), bad.end(), compare_name);
                    entered = true;
                    break;
                case 2:
                    sort(good.begin(), good.end(), compare_last_name);
                    sort(bad.begin(), bad.end(), compare_last_name);
                    entered = true;
                    break;
                case 3:
                    sort(good.begin(), good.end(), compare_avg);
                    sort(bad.begin(), bad.end(), compare_avg);
                    entered = true;
                    break;
                case 4:
                    sort(good.begin(), good.end(), compare_med);
                    sort(bad.begin(), bad.end(), compare_med);
                    entered = true;
                    break;
                default:
                    cout << "Bloga ivestis, galima ivesti tik nurodytus pasirinkimus" << endl << endl;
                    break;
            }
            std::chrono::duration<double> diff = std::chrono::high_resolution_clock::now() - start;
            cout << "Masyvo rusiavimas uztruko " << diff.count() << " s" << endl;
        }
        clear_stream();
    }
}

bool compare_name(Student first, Student second) {
    return first.get_name() > second.get_name();
}

bool compare_last_name(Student first, Student second) {
    return first.get_last_name() > second.get_last_name();
}

bool compare_avg(Student first, Student second) {
    return first.get_final_res_avg() > second.get_final_res_avg();
}

bool compare_med(Student first, Student second) {
    return first.get_final_res_med() > second.get_final_res_med();
}

string generate_surname() {
    return SURNAMES.at(rand() % (NAME_COUNT - 1));
}

string generate_name() {
    return NAMES.at(rand() % (NAME_COUNT - 1));
}

int generate_mark() {
    return rand() % 9 + 2;
}

bool valid_mark(int input) {
    if (input < MIN_MARK || input > MAX_MARK) {
        return false;
    }else {
        return true;
    }
}

bool valid_alphabet(string input) {
    try {
        if(input.length() > NAME_MAX_SYMBOLS || input.length() < NAME_MIN_SYMBOLS) {
            throw(0);
        }
        for (int i = 0; i < input.length(); i++) {
            if (!isalpha(input[i])) {
                throw(1);
            }
        }
        return true;
    }catch(int err_num) {
        if (err_num == 0) {
            cout << "Bloga ivestis, min. " << NAME_MIN_SYMBOLS << ", maks. " << NAME_MAX_SYMBOLS << " simboliu." << endl;
        } else if (err_num == 1) {
            cout << "Bloga ivestis, galima ivesti tik raides." << endl << endl;
        }
        return false;
    }
}

void read_data_from_file(const string& file_name, vector <Student> &stud) {
    stringstream buffer;
    int mark;
    bool first_line = true;
    // Read file
    auto start = std::chrono::high_resolution_clock::now(); auto st = start;
    try {
        ifstream file(file_name);
        if (!file) {
            throw(0);
        }
        while (!file.eof()) {
            if (first_line) {
                string line;
                getline(file, line);
                first_line = false;
            } else {
                Student student;
                string name, last_name;
                vector<int> hw_res;
                file >> name >> last_name;
                student.set_full_name(name, last_name);
                while (file.peek() == 32) {
                    file >> mark;
                    hw_res.push_back(mark);
                };

                student.enter_exam(hw_res.back());
                hw_res.pop_back();
                student.set_hw(hw_res);
                student.calc_final_average_hw();
                student.calc_final_median_hw();
                student.calc_final_avg();
                student.calc_final_med();
                stud.push_back(student);
            }
        }
        file.close();

        std::chrono::duration<double> diff = std::chrono::high_resolution_clock::now() - start;
        cout << "Failo nuskaitymas uztruko " << diff.count() << "s" << endl;
    }
    catch (int err_num) {
        if (err_num == 0) {
            cout << "Failo negalima atidaryti..." << endl;
            exit(1);
        }
    }
}

void read_data_from_console(vector <Student> &stud, bool use_median, bool gen_marks, bool gen_names) {
    bool do_continue, do_continue_inner;
    bool entered, entered_inner;
    string response;
    Student stud_var;
    int hw, mark;
    do{
        entered = false;
        if (gen_names) {
            string name = generate_name();
            string surname = generate_surname();
            cout << "Sugeneruotas vardas: " << name << endl;
            cout << "Sugeneruota pavarde: " << surname << endl;
            stud_var.set_full_name(name, surname);
        }else {
            string name;
            string last_name;
            while (!entered) {
                cout << "Vardas (maks. 20 simboliu):";
                getline(cin, name);
                if (valid_alphabet(name)) {
                    entered = true;
                }
            }

            entered = false;
            while (!entered) {
                cout << "Pavarde (maks. 20 simboliu):";
                getline(cin, last_name);
                if (valid_alphabet(last_name)) {
                    entered = true;
                }
            }

            stud_var.set_full_name(name, last_name);
        }

        do {
            entered = false;
            cout << "Ivesti namu darbu rezultata? (y - taip, n - ne):";
            cin >> response;
            while (!entered) {
                if (response == "n") {
                    do_continue_inner = false;
                    entered = true;
                } else if (response == "y") {
                    if (gen_marks) {
                        mark = generate_mark();
                        stud_var.enter_hw(mark);
                        cout << "Sugeneruotas pazymys: " << mark << endl;
                        entered = true;
                        do_continue_inner = true;
                    } else {
                        entered = true;
                        do_continue_inner = true;
                        entered_inner = false;
                        while (!entered_inner) {
                            cout << "Namu darbo rezultatas:";
                            if (cin >> hw) {
                                if (valid_mark(hw)) {
                                    stud_var.enter_hw(hw);
                                    entered_inner = true;
                                }
                            } else {
                                cout <<  "Bloga ivestis, galima ivesti tik sveikuosius skaicius." << endl << endl;
                            }
                            clear_stream();
                        }
                    }
                } else {
                    cout << "Bloga ivestis, bandykite dar karta." << endl << endl;
                    entered = true;
                    do_continue_inner = true;
                }
            }
        }while(do_continue_inner);

        entered = false;
        if (gen_marks) {
            mark = generate_mark();
            stud_var.enter_exam(mark);
            cout << "Sugeneruotas egzamino rezultatas: " << mark << endl << endl;
        } else {
            while (!entered) {
                cout << "Egzamino rezultatas:";
                int exam_res;
                if (cin >> exam_res) {
                    if (valid_mark(exam_res)) {
                        stud_var.enter_exam(mark);
                        entered = true;
                    }
                } else {
                    cout << "Bloga ivestis, galima ivesti tik sveikuosius skaicius." << endl << endl;
                }
                clear_stream();
            }
        }

        stud_var.calc_final_median_hw();
        stud_var.calc_final_average_hw();

        stud_var.calc_final_avg();
        stud_var.calc_final_med();
        stud.push_back(stud_var);
        cout << endl;

        entered = false;
        cout << endl;
        while(!entered) {
            cout << "Ivesti dar vieno studento duomenis? (y - taip, n - ne):";
            cin >> response;
            if (response == "n") {
                do_continue = false;
                entered = true;
            }else if (response == "y") {
                do_continue = true;
                entered = true;
            }else {
                cout << "Bloga ivestis, bandykite dar karta." << endl << endl;
                entered = false;
            }
        }
        cin.ignore (std::numeric_limits<std::streamsize>::max(), '\n');
    }while(do_continue);
}

void print_data_choice(vector <Student> &stud, int num, bool use_median) {
    // Different output for average and median
    string galutinis = use_median ? "Galutinis (med.)" : "Galutinis (vid.)";
    int width = 20;
    cout << left << setw(width) << "Pavarde";
    cout << left << setw(width) << "Vardas";

    cout << left << setw(width) << galutinis << endl;
    cout << "------------------------------------------------------------" << endl;
    for(int i = 0; i < num; i++) {
        cout << left << setw(width) << stud.at(i).get_last_name();
        cout << left << setw(width) << stud.at(i).get_name();
        if(use_median) {
            cout << left << setw(width) << fixed << setprecision(2) << stud.at(i).get_final_res_med() << endl;
        }else {
            cout << left << setw(width) << fixed << setprecision(2) << stud.at(i).get_final_res_avg() << endl;
        }
    }
}

void print_data_file(vector <Student> &stud, int num, bool use_median, string filename) {
    // Different output for average and median
    auto start = std::chrono::high_resolution_clock::now(); auto st = start;
    ofstream file(filename);
    string galutinis = use_median ? "Galutinis (med.)" : "Galutinis (vid.)";
    int width = 20;
    file << left << setw(width) << "Pavarde";
    file << left << setw(width) << "Vardas";
    file << left << setw(width) << "Galutinis (med.)";
    file << left << setw(width) << "Galutinis (vid.)" << endl;
    file << "----------------------------------------------------------------------------------" << endl;
    for(int i = 0; i < num; i++) {
        file << left << setw(width) << stud.at(i).get_last_name();
        file << left << setw(width) << stud.at(i).get_name();
        file << left << setw(width) << fixed << setprecision(2) << stud.at(i).get_final_res_med();
        file << left << setw(width) << fixed << setprecision(2) << stud.at(i).get_final_res_avg() << endl;
    }
    file.close();
    std::chrono::duration<double> diff = std::chrono::high_resolution_clock::now() - start;
    cout << "Rasymas i faila " << filename << " uztruko " << diff.count() << " s" << endl;
}