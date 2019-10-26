#include <iostream>
#include <vector>
#include <queue>

typedef unsigned short int usi;

class HashTable{
private:
    static const int p = 257;
    static const int SIZE_OF_TABLE = 1e5;
    std::vector < std::pair < std::string, int >> table[SIZE_OF_TABLE];

    int get_hash(std::string key) {
        long long result = 0, pow = 1;

        for (int i = 0; i < key.size(); i++) {
            result += (int)key[i] * pow;
            pow *= p, pow %= SIZE_OF_TABLE;
            result %= SIZE_OF_TABLE;
        }

        return result;
    }
public:
    HashTable() = default;

    int find_in_talbe(int index, const std::string &key) {
        int res = -1;
        for (int i = 0; i < table[index].size(); i++) {
            if (table[index][i].first == key) {
                res = i;
            }
        }
        return res;
    }

    void put(const std::string &key, int value) {
        int hash = get_hash(key);
        int index = find_in_talbe(hash, key);
        if (index == -1) {
            table[hash].push_back(std::make_pair(key, value));
        } else {
            table[hash][index].second = value;
        }
    }

    void erase(const std::string &key) {
        int hash = get_hash(key);
        int index = find_in_talbe(hash, key);
        if (index != -1) {
            std::swap(table[hash].back(), table[hash][index]);
            table[hash].pop_back();
        }
    }

    int get(const std::string &key) {
        int hash = get_hash(key);
        int index = find_in_talbe(hash, key);
        return table[hash][index].second;
    }
};

class Quack{
private:
    int pointer;
    usi reg[26];
    HashTable hashTable;
    std::queue < usi > q;
    std::vector<std::string> code;
public:

    Quack() {
        for (int i = 0; i < 26; i++) {
            reg[i] = 0;
        }
        pointer = 0;
    }

    void input() {
        std::string command;
        while (std::cin >> command) {
            code.push_back(command);
        }
    }

    void build() {
        while (pointer < code.size()) {
            add_label(code[pointer]);
            pointer++;
        }
    }

    void add_label(const std::string &command) {
        if (command[0] == ':') { // init label
            hashTable.put(command.substr(1, command.size() - 1), pointer);
            return;
        }
    }

    void run() {
        pointer = 0;
        while (pointer < code.size()) {
            do_command(code[pointer]);
            pointer++;
        }
    }

    void do_command(const std::string &command) {
        if (command[0] == '+') { // +
            put(get() + get());
            return;
        }

        if (command[0] == '-') { // -
            put(get() - get());
            return;
        }

        if (command[0] == '*') { // *
            put(get() * get());
            return;
        }

        if (command[0] == '/') { // div
            usi a = get(), b = get();
            put(b ? a / b : 0);
            return;
        }

        if (command[0] == '%') { // mod
            usi a = get(), b = get();
            put(b ? a % b : 0);
            return;
        }

        if (command[0] == '>') { // put in register
            int id_register = command[1] - 'a';
            reg[id_register] = get();
            return;
        }

        if (command[0] == '<') { // put register in a queue
            int id_register = command[1] - 'a';
            put(reg[id_register]);
            return;
        }

        if (command[0] == 'P' && command.size() == 1) { // print get()
            std::cout << get() << std::endl;
            return;
        }

        if (command[0] == 'P' && command.size() == 2) { // print register
            int id_register = command[1] - 'a';
            std::cout << reg[id_register] << std::endl;
            return;
        }

        if (command[0] == 'C' && command.size() == 1) { // print (char)get()
            std::cout << (char)get();
            return;
        }

        if (command[0] == 'C' && command.size() == 2) { // print (char)register
            int id_register = command[1] - 'a';
            std::cout << (char)reg[id_register];
            return;
        }

        if (command[0] == ':') { // init label
            return; // because we add label on the step build
        }

        if (command[0] == 'J') { // go to label
            pointer = hashTable.get(command.substr(1, command.size() - 1)) - 1; // -1 because pointer++ in function "run"
            return;
        }

        if (command[0] == 'Z') { // if (register == 0) go to label
            int id_register = command[1] - 'a';

            if (reg[id_register] == 0) {
                pointer = hashTable.get(command.substr(2, command.size() - 2)) - 1; // -1 because pointer++ in function "run"
            }
            return;
        }

        if (command[0] == 'E') { // if (register1 == register2) go to label
            int id_register1 = command[1] - 'a';
            int id_register2 = command[2] - 'a';

            if (reg[id_register1] == reg[id_register2]) {
                pointer = hashTable.get(command.substr(3, command.size() - 3)) - 1; // -1 because pointer++ in function "run"
            }
            return;
        }

        if (command[0] == 'G') { // if (register1 > register2) go to label
            int id_register1 = command[1] - 'a';
            int id_register2 = command[2] - 'a';

            if (reg[id_register1] > reg[id_register2]) {
                pointer = hashTable.get(command.substr(3, command.size() - 3)) - 1; // -1 because pointer++ in function "run"
            }
            return;
        }

        if (command[0] == 'Q') { // end of program
            exit(0);
        }

        // simple number
        put(atoi(command.c_str()));
    }

    usi get() {
        usi result = q.front();
        q.pop();
        return result;
    }

    void put(usi x) {
        q.push(x);
    }
};

int main() {
    std::ios_base::sync_with_stdio(false);
    Quack quack;
    quack.input();
    quack.build();
    quack.run();
    return 0;
}