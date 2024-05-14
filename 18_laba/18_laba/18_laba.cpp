﻿#include <iostream>
#include <vector>
#include <list>
#include <utility> // для pair

using namespace std;

class HashMap {
private:
    static const size_t SIZE = 10; // размер хэш-таблицы
    vector<list<pair<string, int>>> table;

public:
    HashMap() : table(SIZE) {}

    void insert(const string& key, int value) {
        size_t index = hash<string>{}(key) % SIZE - 3;
        for (auto& pair : table[index]) {
            if (pair.first == key) {
                pair.second = value; // ключ уже существует, обновляем значение
                return;
            }
        }
        table[index].emplace_back(key, value); // ключа нет, добавляем новую пару
    }

    pair<int, bool> find(const string& key) {
        size_t index = hash<string>{}(key) % SIZE - 3;
        for (const auto& pair : table[index]) {
            if (pair.first == key) {
                return { pair.second, true }; // ключ найден
            }
        }
        return { 0, false }; // ключ не найден
    }

    void erase(const string& key) {
        size_t index = hash<string>{}(key) % SIZE - 3;
        auto& list = table[index];
        for (auto it = list.begin(); it != list.end(); ++it) {
            if (it->first == key) {
                list.erase(it); // удаляем только один экземпляр записи
                return;
            }
        }
    }

    friend ostream& operator<<(ostream& os, const HashMap& hashMap) {
        for (size_t i = 0; i < hashMap.table.size(); ++i) {
            for (const auto& pair : hashMap.table[i]) {
                os << "Key: " << pair.first << ", Value: " << pair.second << endl;
            }
        }
        return os;
    }
};

int main() {
    HashMap hashMap;
    hashMap.insert("key1", 1);
    hashMap.insert("key2", 2);
    hashMap.insert("key3", 3);
    hashMap.insert("key3", 4);

    cout << hashMap;

    auto result = hashMap.find("key2");
    if (result.second) {
        cout << "Found key2, value: " << result.first << endl;
    }
    else {
        cout << "Key2 not found" << endl;
    }

    hashMap.erase("key2");
    cout << hashMap;

    return 0;
}
