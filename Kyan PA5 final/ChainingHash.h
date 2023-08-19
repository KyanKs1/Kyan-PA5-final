/*
 *  Separate chaining hashtable
 */

#ifndef __CHAINING_HASH_H
#define __CHAINING_HASH_H

 // Standard library includes
#include <iostream>
#include <vector>
#include <list>
#include <stdexcept>

// Custom project includes
#include "Hash.h"

// Namespaces to include
using std::vector;
using std::list;
using std::pair;

using std::cout;
using std::endl;

//
// Separate chaining based hash table - derived from Hash
//
template<typename K, typename V>
class ChainingHash : public Hash<K, V> {
private:

public:
    ChainingHash(int n = 11) {
        currentSize = n;
        theLists.resize(findNextPrime(n), list<pair<K, V>>());
    }

    ~ChainingHash() {
        //this->clear();
    }

    bool empty() {
        for (const auto& list : theLists) {
            if (!list.empty()) {
                return false;
            }
        }
        return true;
    }

    int size() {
        int total_size = 0;
        for (const auto& list : theLists) {
            total_size += int(list.size());
        }
        return total_size;
    }

    V& at(const K& key) {
        int hashKey = hash(key);
        list<pair<K, V>>& chainL = theLists[hashKey];
        for (pair<K, V>& p : chainL) {
            if (p.first == key) {
                return p.second;
            }
        }
        throw std::out_of_range("Key not Found");
    }

    V& operator[](const K& key) {
        return at(key);
    }

    int count(const K& key) {
        int hashKey = hash(key);
        int sum = 0;
        list<pair<K, V>>& chainL = theLists[hashKey];
        for (pair<K, V>& p : chainL) {
            if (p.first == key) {
                sum++;
            }
        }
        return sum;
    }

    void emplace(K key, V value) {
        int hashKey = hash(key);
        for (auto& p : theLists[hashKey]) {
            if (p.first == key) {
                p.second = value;  // update the existing value doing nothing would also work becuase this Pa has pairs as the same value.
                return;
            }
        }
        theLists[hashKey].emplace_front(key, value);  // insert a new pair
        if (load_factor() > CONSTLOADFACTOR) {
            rehash();
        }
    }


    void insert(const std::pair<K, V>& pair) {
        emplace(pair.first, pair.second);

    }

    void erase(const K& key) {
        int hkey = hash(key);
        list<pair<K, V>>& Chain = theLists[hkey];
        auto itr = Chain.begin();

        for (pair<K, V> p : Chain) {
            if (p.first == key) {
                Chain.erase(itr);
                return;
            }
            else {
                itr++;
            }
        }
    }


    void clear() {
        for (auto i = 0; i < theLists.size(); i++) {
            theLists[i].clear();
        }
    }

    int bucket_count() {
        return int(theLists.capacity());
    }

    int bucket_size(int n) {
        return 0;
    }

    int bucket(const K& key) {
        return 0;

    }

    float load_factor() {
        float b = size();
        float Lf = b / bucket_count();
        return Lf;
    }

    void rehash() {
        cout << "Rehashing";
        int newSize = findNextPrime(2 * bucket_count());
        vector<pair<K, V>> temptable;
        for (int i = 0; i < theLists.size(); i++) {
            for (pair<K, V>& j : theLists[i]) {
                temptable.emplace_back(std::move(j));
            }
        }
        theLists.clear();
        theLists.resize(newSize);
        currentSize = newSize;
        for (pair<K, V>& p : temptable) {
            insert(std::move(p));
        }
        cout << currentSize << endl;
    }

    void rehash(int n) {
        currentSize = findNextPrime(n);
        vector<pair<K, V>> AllVals;
        pair<K, V> tmpPair;
        for (int i = 0; i < theLists.capacity(); i++) {
            for (pair<K, V> j : theLists[i]) {
                AllVals.push_back(j);
            }
        }
        clear();
        theLists.resize(currentSize);
        for (pair<K, V> p : AllVals) {
            insert(p);
        }
        cout << "Rehashing";
    }
    int getCurrentSize() {
        return currentSize;
    }

private:
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
    vector<list<pair<K, V>>> theLists;   // The array of Lists
    int  currentSize;
    float CONSTLOADFACTOR = .75;
};

#endif //__CHAINING_HASH_H