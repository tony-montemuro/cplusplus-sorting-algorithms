#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <queue>
#include <chrono>
#include <string>
#include <fstream>
#include <assert.h>
#include "sorting.hpp"

#define logLine(x) std::cout << x << std::endl
#define log(x) std::cout << x << " "
#define nl() std::cout << std::endl;
#define logLineF(out, x) out << x << std::endl
#define logF(out, x) out << x << " "
#define nlF(out) out << std::endl
#define SIZE 5
#define NUM_SORTS 7
#define NUM_RUNS 100

enum sortEnum {
    bubble,
    shortbubble,
    selection,
    insertion,
    merge,
    quick,
    radix
};

sortEnum hash(const std::string& s) {
    if (s == "Bubble Sort") return bubble;
    if (s == "Short Bubble Sort") return shortbubble;
    if (s == "Selection Sort") return selection;
    if (s == "Insertion Sort") return insertion;
    if (s == "Merge Sort") return merge;
    if (s == "Quick Sort") return quick;
    if (s == "Radix Sort") return radix;
}

template<class item_t>
int printVect(const std::vector<item_t>& v)
{
    for (int i = 0; i < v.size(); i++) {
        log(v.at(i));
        if ((i+1) % 40 == 0) {
            std::cout << std::endl;
        }
    }
}

template<class item_t>
float timeOfSort(std::vector<item_t> v, const std::string& s)
{
    std::chrono::time_point<std::chrono::system_clock> start = std::chrono::system_clock::now();
    switch (hash(s)) {
        case bubble:
            mysorts::bubbleSort(v);
            break;
        case shortbubble:
            mysorts::shortBubbleSort(v);
            break;
        case selection:
            mysorts::selectionSort(v);
            break;
        case insertion:
            mysorts::insertionSort(v);
            break;
        case merge:
            mysorts::mergeSort(v, 0, v.size()-1);
            break;
        case quick:
            mysorts::quickSort(v, 0, v.size()-1);
            break;
        case radix:
            mysorts::radixSort(v, 5, 10);
            break;
    }
    std::chrono::time_point<std::chrono::system_clock> end = std::chrono::system_clock::now();
    std::chrono::duration<float> elapsed = end-start;
    return elapsed.count();
}

int main()
{
    //Randomize seed
    srand(time(0));
    // Initialize 5 (SIZE) unsorted vectors of unsigned ints, each of which containing 10^n unsigned ints (n >= 1 && n <= 5)
    std::vector<std::vector<unsigned int>> v;
    v.reserve(SIZE);
    for (int n = 10; n <= 100000; n*=10) {
        std::vector<unsigned int> vect;
        vect.reserve(n);
        for (int i = 0; i < n; i++) {
            vect.push_back(rand());
        }
        v.push_back(vect);
    }
    //Open file for output
    std::ofstream out;
    out.open("output.txt");
    assert(out);
    //Now, calculate and log the amount of time it takes to perform each sort on each of the 6 generated vectors.
    std::string sortName[] {"Bubble Sort", "Short Bubble Sort", "Selection Sort", "Insertion Sort", "Merge Sort", "Quick Sort", "Radix Sort"};
    //For each run
    for (int i = 0; i < NUM_RUNS; i++) {
        logLineF(out, "Test " << i+1 << ":");
        //For each sort
        for (int j = 0; j < NUM_SORTS; j++) {
            std::string sort = sortName[j];
            int n = 10;
            //For each vector
            for (int k = 0; k < SIZE; k++) {
                logF(out, sort << " on vector with " << n << " unsorted elements takes");
                logF(out, timeOfSort(v.at(k), sort) << " seconds.");
                nlF(out);
                n*=10;
            }
        }
        nlF(out);
    }
    //End of program
    logLine("Tests complete! File created!");
    out.close();
    return 0;
}