#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct Studentas {
    string name, last_name;
    vector <int> hw_res;
    int exam_res, n;
    float final_res, avg_hw;
};

void readData(vector <Studentas> &stud, int stud_num);
float average(vector <int> &res);
float final(float hw, int exam);
void printData(vector <Studentas> &stud, int num);

int main() {
    vector <Studentas> students;
    int stud_num;
    cout << "Studentu skaicius:";
    cin >> stud_num;
    readData(students, stud_num);
    printData(students, stud_num);
    return 0;
}

void readData(vector <Studentas> &stud, int stud_num) {
    for(int i = 0; i < stud_num; i++) {
        Studentas stud_var;
        int hw;
        cout << "Vardas:";
        cin >> stud_var.name;
        cout << "Pavarde:";
        cin >> stud_var.last_name;
        cout << "n: ";
        cin >> stud_var.n;
        for (int j = 0; j < stud_var.n; j++) {
            cout << "Namu darbo nr. " << j + 1 << " rezultatas:";
            cin >> hw;
            stud_var.hw_res.push_back(hw);
        };
        cout << "Egzamino rezultatas:";
        cin >> stud_var.exam_res;

        stud_var.avg_hw = average(stud_var.hw_res);

        stud_var.final_res = final(stud_var.avg_hw, stud_var.exam_res);
        stud.push_back(stud_var);
        cout << endl;
    }
    return;
};

float average(vector <int> &res) {
    int vec_size = res.size();
    int sum = 0;
    for(int i = 0; i < vec_size; i++) {
        sum += res[i];
    };

    if(vec_size > 0) {
        return (float) sum / vec_size;
    }else {
        return 0.0;
    };
};

float final(float hw, int exam) {
    return (float) 0.4 * hw + 0.6 * exam;
};

void printData(vector <Studentas> &stud, int num) {
    for(int i = 0; i < num; i++) {
        cout << stud[i].name << " " << stud[i].last_name << " " << stud[i].final_res << endl;
    };
};