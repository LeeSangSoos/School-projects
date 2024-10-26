#include <iostream>
#include <vector>
#include <ctime>
#include <set>

using namespace std;

class ChainHashTable{
    private:
        int table_size;
        vector<vector<int>> table;
    
    public:
        ChainHashTable(int size) : table_size(size), table(size) {}
        
        void insert(int k){
            int index = k%table_size;
            table[index].push_back(k);
        }

        void print() const {
            int longestchain=0;
            float totalchain=0;
            for(int i = 0;i<table_size;i++){
                if(longestchain < table[i].size()){
                    longestchain = table[i].size();
                }
                totalchain += table[i].size();
            }
            std::cout << "Longest Chain: " << longestchain << std::endl;
            std::cout << "Average Chain Length: " << totalchain / table_size << std::endl;
            std::cout << std::endl;
            for (int i = 0; i < table_size; i++) {
                std::cout << i;
                for (int x : table[i]) {
                    std::cout << " -> " << x;
                }
                std::cout << std::endl;
            }
    }
};

int main(){
    ChainHashTable h7(7);
    ChainHashTable h11(11);
    ChainHashTable h17(17);

    std::set<int> keys;
    srand(time(NULL));
    while (keys.size() < 50) {
        keys.insert(rand() % 500);
    }

    for (int key : keys) {
        h7.insert(key);
        h11.insert(key);
        h17.insert(key);
    }

    h7.print();
    h11.print();
    h17.print();

    return 0;
}