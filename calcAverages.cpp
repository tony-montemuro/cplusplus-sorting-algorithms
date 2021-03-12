#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <assert.h>

#define logLine(x) std::cout << x << std::endl
#define logF(out, x) out << x << " "
#define nlF(out) out << std::endl
#define NUM_TESTS 100
#define NUM_SORTS 7
#define DATA_PER_SORT 5

enum sortEnum {
    bubble,
    shortbubble,
    selection,
    insertion,
    merge,
    quick,
    radix
};

sortEnum hash(std::string s) {
    if (s == "Bubble Sort") return bubble;
    if (s == "Short Bubble Sort") return shortbubble;
    if (s == "Selection Sort") return selection;
    if (s == "Insertion Sort") return insertion;
    if (s == "Merge Sort") return merge;
    if (s == "Quick Sort") return quick;
    if (s == "Radix Sort") return radix;
}

struct time {
    float ten;
    float hundred;
    float thousand;
    float tenThousand;
    float hundredThousand;
};

struct sortsData {
    std::vector<time> bubble;
    std::vector<time> shortBubble;
    std::vector<time> selection;
    std::vector<time> insertion;
    std::vector<time> merge;
    std::vector<time> quick;
    std::vector<time> radix;
};

void addToData(sortsData& d, time& table, const std::string& curSort)
{
    //Add a new table to the data
    switch (hash(curSort)) {
        case bubble:
            d.bubble.push_back(table);
            break;
        case shortbubble:
            d.shortBubble.push_back(table);
            break;
        case selection:
            d.selection.push_back(table);
            break;
        case insertion:
            d.insertion.push_back(table);
            break;
        case merge:
            d.merge.push_back(table);
            break;
        case quick:
            d.quick.push_back(table);
            break;
        case radix:
            d.radix.push_back(table);
            break;
    }
}

void addToTable(time& table, std::string& val_s, int dataNum) {
    //Add a new value to a table
    float val = std::stof(val_s);
    switch (dataNum) {
        case 0:
            table.ten = val;
            break;
        case 1:
            table.hundred = val;
            break;
        case 2:
            table.thousand = val;
            break;
        case 3:
            table.tenThousand = val;
            break;
        case 4:
            table.hundredThousand = val;
            break;
    }
}

std::vector<time>& getList(sortsData& d, const std::string& curSort)
{
    //Returns the correct list based off the curSort parameter
    switch (hash(curSort)) {
        case bubble:
            return d.bubble;
        case shortbubble:
            return d.shortBubble;
        case selection:
            return d.selection;
        case insertion:
            return d.insertion;
        case merge:
            return d.merge;
        case quick:
            return d.quick;
        case radix:
            return d.radix;
    }
}

float getVal(time& table, int dataNum) {
    float val;
    switch (dataNum) {
        case 0:
            val = table.ten;
            break;
        case 1:
            val = table.hundred;
            break;
        case 2:
            val = table.thousand;
            break;
        case 3:
            val = table.tenThousand;
            break;
        case 4:
            val = table.hundredThousand;
            break;
    }
    return val;
}

int main() 
{
    //Open file to read and write
    std::ifstream in;
    std::ofstream out;
    in.open("output.txt");
    out.open("averageTable.txt");
    assert(in && out);
    //Collect all data from file
    std::string s;
    getline(in, s, '\n');
    std::string sortName[] {"Bubble Sort", "Short Bubble Sort", "Selection Sort", "Insertion Sort", "Merge Sort", "Quick Sort", "Radix Sort"};
    sortsData d;
    //For each test
    for (int testNum = 0; testNum < NUM_TESTS; testNum++) {
        //For each sort
        for (int sortIndex = 0; sortIndex < NUM_SORTS; sortIndex++) {
            std::string curSort = sortName[sortIndex];
            time table;
            //For each data point per sort
            for (int dataNum = 0; dataNum < DATA_PER_SORT; dataNum++) {
                getline(in, s, '\n');
                int begin = s.find("takes");
                begin+=6;
                int end = s.find("seconds");
                end--;
                std::string val = s.substr(begin, end-begin);
                addToTable(table, val, dataNum);
            }
            addToData(d, table, curSort);
        }
        getline(in, s, '\n');
        getline(in, s, '\n');
    }
    //Calculate averages, and print them to an output file
    out << std::fixed;
    //For each data point per sort
    for (int dataNum = 0; dataNum < DATA_PER_SORT; dataNum++) {
        //For each sort
        for (int sortIndex = 0; sortIndex < NUM_SORTS; sortIndex++) {
            std::string curSort = sortName[sortIndex];
            float average, total = 0;
            std::vector<time> curList = getList(d, curSort);
            //For each test
            for (int testNum = 0; testNum < NUM_TESTS; testNum++) {
                time table = curList.at(testNum);
                total += getVal(table, dataNum);
            }
            average = total / NUM_TESTS;
            logF(out, average);
        }
        nlF(out);
    }
    //End of program
    logLine("Average table created!");
    in.close();
    out.close();
    return 0;
}