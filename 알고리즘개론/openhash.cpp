#include <iostream>
#include <vector>
#include <ctime>
#include <algorithm>

using namespace std;

class OpenHashTable {
private:
    static const int m = 43;
    vector<int> table;
    int c1 = 1, c2 = 3;
    int totalProbes = 0;
    int Insertions = 0;

public:
    OpenHashTable() : table(m, -1) {}

    void linear_probing(int k) {
        int h;
        for(int i = 0; i < m; i++) {
            h = ((k % m) + i) % m;
            if (table[h] == -1) {
                table[h] = k;
                totalProbes += (i + 1);
                Insertions++;
                break;
            }
        }
    }

    void quadratic_probing(int k) {
        int h;
        for(int i = 0; i < m; i++) {
            h = ((k % m) + c1 * i + c2 * i * i) % m;
            if (table[h] == -1) {
                table[h] = k;
                totalProbes += (i + 1);
                Insertions++;
                break;
            }
        }
    }

    void double_hashing(int k) {
        int h;
        for(int i = 0; i < m; i++) {
            h = ((k % m) + i * (1 + (k % (m - 1)))) % m;
            if (table[h] == -1) {
                table[h] = k;
                totalProbes += (i + 1);
                Insertions++;
                break;
            }
        }
    }

    void print() const {
        int largestCluster = 0;
        int currentCluster = 0;

        for (int i = 0; i < m; i++) {
            if (table[i] != -1) {
                cout << i << " : " << "[" << table[i] << "]"<< endl;
                currentCluster++;
                largestCluster = max(largestCluster, currentCluster);
            } else {
                currentCluster = 0;
            }
        }

        double avgProbes = (Insertions == 0) ? 0 : static_cast<double>(totalProbes) / Insertions;
        cout << "\nLargest Cluster Size: " << largestCluster << endl;
        cout << "Average Probes per Insertion: " << avgProbes << endl;
    }
};

int main() {
    srand(time(NULL));
    vector<int> values;
    while (values.size() < 30) {
        int randomNum = rand() % 500;
        if (std::find(values.begin(), values.end(), randomNum) == values.end()) {
            values.push_back(randomNum);
        }
    }

    OpenHashTable linearTable;
    OpenHashTable quadraticTable;
    OpenHashTable doubleTable;

    for (int key : values) {
        linearTable.linear_probing(key);
        quadraticTable.quadratic_probing(key);
        doubleTable.double_hashing(key);
    }

    cout << "Linear Hashing Table:" << endl;
    linearTable.print();
    cout << endl;

    cout << "Quadratic Hashing Table:" << endl;
    quadraticTable.print();
    cout << endl;

    cout << "Double Hashing Table:" << endl;
    doubleTable.print();
    cout << endl;

    return 0;
}
