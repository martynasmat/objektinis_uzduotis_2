#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <cmath>
#include <algorithm>
#include <cctype>

using namespace std;

struct Studentas {
    string name, last_name;
    vector <int> hw_res;
    int exam_res;
    float final_res = 0, final_hw = 0;
};

const int NAME_MAX_SYMBOLS = 20;
const int NAME_MIN_SYMBOLS = 2;
const int MIN_MARK = 2;
const int MAX_MARK = 10;

void readData(vector <Studentas> &stud, bool use_median);
float average(vector <int> &res);
float median(vector <int> &res);
float final(float hw, int exam);
void printData(vector <Studentas> &stud, int num, bool use_median);
bool valid_mark(int input);
bool valid_alphabet(string input);

int main() {
    while(true) {
        vector<Studentas> students;
        bool ivesta = false;
        bool use_median;
        int menu_choice;

        while (!ivesta) {
            cout
                    << "\n----- Pagrindinis meniu -----\n1 - vesti duomenis ranka;\n2 - generuoti pazymius;\n3 - generuoti visus duomenis;\n4 - baigti darba;\n\nIvesti pasirinkima:";
            if (!(cin >> menu_choice)) {
                cout << "Bloga ivestis, bandykite dar karta" << endl << endl;
            } else {
                if (menu_choice < 1 or menu_choice > 4) {
                    cout << "Bloga ivestis, galima ivesti tik nurodytus pasirinkimus" << endl << endl;
                } else if (menu_choice == 1){
                    ivesta = true;
                } else if (menu_choice == 2) {
                    ivesta = true;
                } else if (menu_choice == 3) {
                    ivesta = true;
                } else if (menu_choice == 4) {
                    return 0;
                    ivesta = true;
                };
            };
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        };

        ivesta = false;
        while (!ivesta) {
            cout << "Naudoti vidurki ar mediana? (0 - vidurkis, 1 - mediana):";
            if (cin >> use_median) {
                if (use_median != 0 && use_median != 1) {
                    cout << "Bloga ivestis, galima ivesti tik 0 arba 1." << endl << endl;
                } else {
                    ivesta = true;
                }
            } else {
                cout << "Bloga ivestis, bandykite dar karta" << endl << endl;
            };
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        };
        readData(students, use_median);
        printData(students, students.size(), use_median);
    };
};

bool valid_mark(int input) {
    if (input < MIN_MARK) {
        cout << "Bloga ivestis, pazymys turi buti lygus arba didesnis nei 2." << endl << endl;
        return false;
    }else if (input > MAX_MARK) {
        cout << "Bloga ivestis, pazymys turi buti lygus arba mazenis nei 10." << endl << endl;
        return false;
    };
    return true;
};

bool valid_alphabet(string input) {
    if (input.length() <= NAME_MAX_SYMBOLS && input.length() >= NAME_MIN_SYMBOLS) {
        for (int i = 0; i < input.length(); i++) {
            if (!isalpha(input[i])) {
                cout << "Bloga ivestis, galima ivesti tik raides." << endl << endl;
                return false;
            };
        };
        return true;
    }else {
        cout << "Bloga ivestis, min. " << NAME_MIN_SYMBOLS << ", maks. " << NAME_MAX_SYMBOLS << " simboliu." << endl << endl;
        return false;
    };
};

void readData(vector <Studentas> &stud, bool use_median) {
    bool do_continue = false;
    bool do_continue_inner = false;
    bool ivesta, ivesta_inner;
    string response;
    Studentas stud_var;
    int hw;
    do{
        ivesta = false;
        while(!ivesta) {
            cout << "Vardas (maks. 20 simboliu):";
            getline(cin, stud_var.name);
            if(valid_alphabet(stud_var.name)) {
                ivesta = true;
            };
        };

        ivesta = false;
        while (!ivesta) {
            cout << "Pavarde (maks. 20 simboliu):";
            getline(cin, stud_var.last_name);
            if(valid_alphabet(stud_var.last_name)) {
                ivesta = true;
            };
        };

        do {
            ivesta = false;
            cout << "Ivesti namu darbu rezultata? (y - taip, n - ne):";
            cin >> response;
            while (!ivesta) {
                if (response == "n") {
                    do_continue_inner = false;
                    ivesta = true;
                } else if (response == "y") {
                    ivesta = true;
                    do_continue_inner = true;
                    ivesta_inner = false;
                    while(!ivesta_inner) {
                        cout << "Namu darbo nr. " << stud_var.hw_res.size() + 1 << " rezultatas:";
                        if(cin >> hw) {
                            if (valid_mark(hw)) {
                                stud_var.hw_res.push_back(hw);
                                ivesta_inner = true;
                            };
                        }else {
                            cout << "Bloga ivestis, galima ivesti tik sveikuosius skaicius." << endl << endl;
                        };
                        cin.clear();
                        cin.ignore (std::numeric_limits<std::streamsize>::max(), '\n');
                    };
                } else {
                    cout << "Bloga ivestis, bandykite dar karta." << endl << endl;
                    ivesta = true;
                    do_continue_inner = true;
                };
            };
        }while(do_continue_inner);

        ivesta = false;
        while(!ivesta) {
            cout << "Egzamino rezultatas:";
            if(cin >> stud_var.exam_res) {
                if(valid_mark(stud_var.exam_res)) {
                    ivesta = true;
                };
            }else {
                cout << "Bloga ivestis, galima ivesti tik sveikuosius skaicius." << endl << endl;
            };
            cin.clear();
            cin.ignore (std::numeric_limits<std::streamsize>::max(), '\n');
        };

        if(use_median) {
            stud_var.final_hw = median(stud_var.hw_res);
        }else {
            stud_var.final_hw = average(stud_var.hw_res);
        };

        stud_var.final_res = final(stud_var.final_hw, stud_var.exam_res);
        stud.push_back(stud_var);
        cout << endl;

        ivesta = false;
        cout << endl;
        while(!ivesta) {
            cout << "Ivesti dar vieno studento duomenis? (y - taip, n - ne):";
            cin >> response;
            if (response == "n") {
                do_continue = false;
                ivesta = true;
            }else if (response == "y") {
                do_continue = true;
                ivesta = true;
            }else {
                cout << "Bloga ivestis, bandykite dar karta." << endl << endl;
                ivesta = false;
            };
        };
        cin.ignore (std::numeric_limits<std::streamsize>::max(), '\n');
    }while(do_continue);
};

float average(vector <int> &res) {
    int vec_size = res.size();
    int sum = 0;
    for(int i = 0; i < vec_size; i++) {
        sum += res[i];
    };

    if(vec_size > 0) {
        return (float)sum / (float)vec_size;
    }else {
        return 0.0;
    };
};

float median(vector <int> &res) {
    sort(res.begin(), res.end());
    int vec_size = res.size();
    int size_divided = ceil(vec_size / 2.0);
    if(vec_size > 0) {
        if (vec_size % 2 == 0) {
            cout << (float)(res[size_divided - 1] + res[size_divided]) / 2.0 << endl;
            return (float)(res[size_divided - 1] + res[size_divided]) / 2.0;
        } else {

            return (float)res[size_divided - 1];
        };
    }else {
        return 0.0;
    };
};

float final(float hw, int exam) {
    return 0.4 * hw + 0.6 * exam;
};

void printData(vector <Studentas> &stud, int num, bool use_median) {
    string galutinis = use_median ? "Galutinis (med.)" : "Galutinis (vid.)";
    int width = 20;
    cout << left << setw(width) << "Pavarde";
    cout << left << setw(width) << "Vardas";

    cout << left << setw(width) << galutinis << endl;
    cout << "------------------------------------------------------------" << endl;
    for(int i = 0; i < num; i++) {
        cout << left << setw(width) << stud[i].last_name;
        cout << left << setw(width) << stud[i].name;
        cout << left << setw(width) << fixed << setprecision(2) << stud[i].final_res << endl;
    };
};