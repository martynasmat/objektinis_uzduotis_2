#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct Studentas {
    string vardas, pavarde;
    vector <int> nd_rez;
    int egz_rez, n;
    float gal_rez, avg_nd;
};

void readData(vector <Studentas> &stud);
float average(vector <int> &rez);

int main() {
    vector <Studentas> studentai;
    readData(studentai);
    return 0;
}

void readData(vector <Studentas> &stud) {
    Studentas stud_var;
    int nd;
    cout << "Vardas: ";
    cin >> stud_var.vardas;
    cout << "Pavarde: ";
    cin >> stud_var.pavarde;
    cout << "n: ";
    cin >> stud_var.n;
    for(int i = 0; i < stud_var.n; i++) {
        cout << "Namu darbo nr. " << i + 1 << " rezultatas: ";
        cin >> nd;
        stud_var.nd_rez.push_back(nd);
    };
    cout << "Egzamino rezultatas: ";
    cin >> stud_var.gal_rez;
    stud_var.avg_nd = average(stud_var.nd_rez);
    cout << stud_var.avg_nd << endl;
    stud.push_back(stud_var);
    return;
};

float average(vector <int> &rez) {
    int vec_size = rez.size();
    int sum = 0;
    for(int i = 0; i < vec_size; i++) {
        sum += rez[i];
    };

    if(vec_size > 0) {
        return (float) sum / vec_size;
    }else {
        return 0.0;
    };
};