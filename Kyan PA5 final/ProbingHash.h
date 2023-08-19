#ifndef __PROBING_HASH_H
#define __PROBING_HASH_H

#include <vector>
#include <stdexcept>

#include "Hash.h"

using std::vector;
using std::pair;

// Can be used for tracking lazy deletion for each element in your table
enum EntryState {
    EMPTY = 0,
    VALID = 1,
    DELETED = 2
};

template<typename K, typename V>
class ProbingHash : public Hash<K, V> { // derived from Hash
private:
    // Needs a table and a size.
    // Table should be a vector of std::pairs for lazy deletion

public:
    ProbingHash(int n = 11) {
        currentSize = n;
        Table.resize(findNextPrime(n), pair<EntryState, pair<K, V>>());
    }

    ~ProbingHash() {
        // Needs to actually free all table contents
    }

    bool empty() {
        for (int i = 0; i < Table.capacity(); i++) {
            if (Table[i].first != EMPTY)
                return false;
        }
        return true;
    }

    int size() {
        int sum = 0;
        for (int i = 0; i < Table.size(); i++) {
            if (Table[i].first == VALID) {
                sum++;
            }
        }
        return sum;
    }

    V& at(const K& key) {
        int hashKey = hash(key);
        K p = key;
        while (Table[hashKey].first != EMPTY) {
            if (Table[hashKey].first == VALID && Table[hashKey].second.first == key) {
                return Table[hashKey].second.second;
            }
            p++;
            hashKey = hash(p);
        }
        throw std::out_of_range("Key not in hash");
    }

    V& operator[](const K& key) {
        return at(key);
    }

    int count(const K& key) {
        int Hashkey = hash(key);
        int sum = 0;
        int i = 0;
        while (Table[Hashkey].first != EMPTY) {
            if (Table[Hashkey].second.first == key && Table[Hashkey].first != DELETED) {
                sum++;
            }
            i++;
            Hashkey = hash(key + i);
        }
        return sum;
    }

    void emplace(K key, V value) {
        int Hashkey = hash(key);
        K tmpkey = key;
        while (Table[Hashkey].first != EMPTY) {
            if (Table[Hashkey].second.first == key && Table[Hashkey].first != DELETED) {
                // Key already exists, update value and return
                Table[Hashkey].second.second = value;
                return;
            }
            tmpkey++;
            Hashkey = hash(tmpkey);
        }
        // Key not found, insert new key-value pair
        Table[Hashkey].first = VALID;
        Table[Hashkey].second.first = key;
        Table[Hashkey].second.second = value;

        // Rehash if load factor exceeds threshold
        if (load_factor() > .75) {
            rehash();
        }
    }

    void insert(const std::pair<K, V>& pair) {
        emplace(pair.first, pair.second);
    }

    void erase(const K& key) {
        int Hashkey = hash(key);
        K Temp = key;
        while (Table[Hashkey].first != EMPTY) {
            if (Table[Hashkey].second.first == key && Table[Hashkey].first != DELETED) {
                Table[Hashkey].first = DELETED;
                return;
            }
            Temp++;
            Hashkey = hash(Temp);
        }
    }

    void clear() {
        for (int i = 0; i < bucket_count(); i++) {
            Table[i].first = EMPTY;
        }
        Table.clear();
    }

    int bucket_count() {
        return Table.capacity();
    }

    int bucket_size(int n) {
        return 0;
    }

    int bucket(const K& key) {
        return 0;
    }

    float load_factor() {
        float p = size();
        return p / bucket_count();  

    }

    void rehash() {
        cout << "Rehashing" << endl;
        currentSize = findNextPrime(2 * bucket_count());
        vector<pair<K, V>> old;
        for (int i = 0; i < bucket_count(); i++) {
            if (Table[i].first != EMPTY) {
                old.push_back(move(Table[i].second));
            }
        }
        clear();
        Table.resize(currentSize);

        for (pair<K, V> p : old) {
            insert(move(p));
        }
        cout << currentSize << endl;

    }
    int getcurrentSize() {
        return currentSize;
    }

    void rehash(int n) {
    }

private:
    vector<pair<EntryState, pair<K, V>>> Table;
    int currentSize;
    int findNextPrime(int n)
    {
        while (!isPrime(n))
        {
            n++;
        }
        return n;
    }

    int isPrime(int n)
    {
        for (int i = 2; i <= sqrt(n); i++)
        {
            if (n % i == 0)
            {
                return false;
            }
        }

        return true;
    }

    int hash(const K& key) {
        return key % currentSize;
    }

};

#endif //__PROBING_HASH_H