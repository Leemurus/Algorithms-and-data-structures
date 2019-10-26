#include <iostream>
#include <vector>

class HashTable{
private:
    int count;
    static const int p = 521;
    static const int mod = 1e9 + 7;
    static const int SIZE_TABLE = 100;

    std::vector<std::string> table[SIZE_TABLE];

    int get_hash(const std::string &key) {
        long long result = 0, pow = 1;

        for (int i = 0; i < key.size(); i++) {
            result += (int) key[i] * pow;
            pow *= p, pow %= mod;
            result %= mod;
        }
        return (int)(result % SIZE_TABLE);
    }

public:
    HashTable():count(0) {}

    int find_in_table(int hash_value, const std::string &value) {
        int index = -1;
        for (int i = 0; i < table[hash_value].size(); i++) {
            if (table[hash_value][i] == value) {
                index = i;
            }
        }

        return index;
    }

    void put(const std::string &value) {
        int hash_value = get_hash(value);
        int index = find_in_table(hash_value, value);

        if (index == -1) {
            table[hash_value].push_back(value);
            count++;
        }
    }

    void erase(const std::string &value) {
        int hash_value = get_hash(value);
        int index = find_in_table(hash_value, value);

        if (index != -1) {
            std::swap(table[hash_value][index], table[hash_value].back());
            table[hash_value].pop_back();
            count--;
        }
    }

    void print_all() {
        std::cout << count << std::endl;
        for (int i = 0; i < SIZE_TABLE; i++) {
            for (int j = 0; j < table[i].size(); j++) {
                std::cout << table[i][j] << " ";
            }
        }
        std::cout << std::endl;
    }
};

class MultiMap {
private:
    static const int p = 257;
    static const int mod = 1e9 + 7;
    static const int SIZE_TABLE = 10000;
    std::vector < std::pair < std::string, HashTable >> table[SIZE_TABLE];

    int get_hash(const std::string &key) {
        long long result = 0, pow = 1;

        for (int i = 0; i < (int)key.size(); i++) {
            result += (int) key[i] * pow;
            pow *= p, pow %= mod;
            result %= mod;
        }
        return (int) (result % SIZE_TABLE);
    }

public:
    MultiMap() {}

    int find_in_table(int hash_key, const std::string &key) {
        int index = -1;
        for (int i = 0; i < table[hash_key].size(); i++) {
            if (table[hash_key][i].first == key) {
                index = i;
            }
        }

        return index;
    }

    void put(const std::string &key, const std::string &value) {
        int hash_key = get_hash(key);
        int index = find_in_table(hash_key, key);

        if (index == -1) {
            table[hash_key].push_back(std::make_pair(key, HashTable()));
            index = (int)table[hash_key].size() - 1;
        }
        table[hash_key][index].second.put(value);
    }

    void erase(const std::string &key, const std::string &value) {
        int hash_key = get_hash(key);
        int index = find_in_table(hash_key, key);

        if (index != -1) {
            table[hash_key][index].second.erase(value);
        }
    }

    void erase_key(const std::string &key) {
        int hash_key = get_hash(key);
        int index = find_in_table(hash_key, key);

        if (index != -1) {
            std::swap(table[hash_key][index], table[hash_key].back());
            table[hash_key].pop_back();
        }
    }

    void print_all_value(const std::string &key) {
        int hash_key = get_hash(key);
        int index = find_in_table(hash_key, key);

        if (index != -1) {
            table[hash_key][index].second.print_all();
        } else {
            std::cout << "0" << std::endl << std::endl;
        }
    }
};

MultiMap m;
std::string request;

int main() {
    std::ios_base::sync_with_stdio(false);

    while (std::cin >> request) {
        std::string key, value;
        std::cin >> key;

        if (request == "put") {
            std::cin >> value;
            m.put(key, value);
        }

        if (request == "get") {
            m.print_all_value(key);
        }

        if (request == "delete") {
            std::cin >> value;
            m.erase(key, value);
        }

        if (request == "deleteall") {
            m.erase_key(key);
        }
    }

    return 0;
}