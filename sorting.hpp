//Programmer: Tony Montemuro
//Date: 12/30/2020
//This is a sorting algorithm library.

#ifndef MY_SORTS
#define MY_SORTS

namespace mysorts 
{
    //Swap
    template <class item_t>
    inline void swap(item_t& a, item_t& b) {
        item_t temp = a;
        a = b;
        b = temp;
    }

    //Bubble Sort
    template <class item_t>
    void bubbleUp (std::vector<item_t>& values, int start)
    {
        /*
            Precond: values is a reference to a vector of "item_t". start is of type int. start refers to the index of the first unsorted position of the vector.
            Postcond: Starting at the last element of the vector, if the current element at index i is less than the previous element, swap these two elements. Otherwise, do
            nothing. Do this while i is greater than start.
        */
        int end = values.size()-1;
        for (int i = end; i > start; i--) {
            if (values.at(i) < values.at(i-1)) swap(values.at(i), values.at(i-1));
        }
    }

    template<class item_t>
    void bubbleSort(std::vector<item_t>& values)
    {
        /*
            Precond: values is a reference to a vector of "item_t". item_t is a type that can be compared using logical operators.
            Postcond: values is sorted using the Bubble Sort algorithm.
        */
        int n = values.size();
        for (int current = 0; current < n-1; current++) {
            bubbleUp(values, current);
        }
    }

    //Short Bubble Sort
    template <class item_t>
    void bubbleUpShort(std::vector<item_t>& values, int start, bool& isSorted) 
    {
        /*
            Precond: values is a reference to a vector of values. start is of type int. isSorted is a reference to a boolean
            flag, which determines whether or not values is sorted or not.
            Postcond: Starting at the last element of the vector, if the current element at index i is less than the previous element, swap these two elements. Otherwise, do
            nothing. Do this while i is greater than start. If no swaps occur throughout the bubbleUp process, isSorted will be true, since this indicates
            that the list is sorted. Otherwise, reset isSorted back to false.
        */
        isSorted = true;
        int end = values.size()-1;
        for (int i = end; i > start; i--) {
            if (values.at(i) < values.at(i-1)) {
                swap(values.at(i), values.at(i-1));
                isSorted = false;
            }
        }
    }

    template <class item_t>
    void shortBubbleSort(std::vector<item_t>& values)
    {
        /*
            Precond: values is a reference to a vector of "item_t". item_t is a type that can be compared using logical operators.
            Postcond: values is sorted using the Short Bubble Sort algorithm.
        */
        bool isSorted = false;
        int n = values.size(), current = 0;
        while (current < n-1 && !isSorted) {
            bubbleUpShort(values, current, isSorted);
            current++;
        }
    }

    //Selection Sort
    template <class item_t>
    int indexOfMin(const std::vector<item_t>& values, int start)
    {
        /*
            Precond: values is a const reference to a vector of "item_t". start is of type int. start refers to the index of the first
            unsorted element in the vector.
            Postcond: The minimum element of the unsorted section of the vector is found, and returned.
        */
        int minIndex = start;
        for (int i = start+1; i < values.size(); i++) {
            if (values.at(i) < values.at(minIndex)) minIndex = i;
        }
        return minIndex;
    }

    template<class item_t>
    void selectionSort(std::vector<item_t>& values)
    {
        /*
            Precond: values is a reference to a vector of "item_t". item_t is a type that can be compared using logical operators.
            Postcond: values is sorted using the Selection Sort algorithm.
        */
        int lastIndex = values.size()-1;
        for (int current = 0; current < lastIndex; current++) {
            swap(values.at(current), values.at(indexOfMin(values, current)));
        }
    }

    //Insertion Sort
    template<class item_t>
    void insertItem(std::vector<item_t>& values, int current)
    {
        /*
            Precond: values is a reference to a vector of "item_t". current is of type int. current refers to the index of the first item
            of the non-sorted section of the vector.
            Postcond: The value at index is inserted into the sorted section of values in it's proper location.
        */
        bool isFinished = false;
        //Loop runs until either current has reached the first index of vector values or until item has been placed correctly in vector
        while (current != 0 && !isFinished) {
            if (values.at(current) < values.at(current-1)) {
                swap(values.at(current), values.at(current-1));
                current--;
            } else {
                isFinished = true;
            }
        }
    }

    template <class item_t>
    void insertionSort(std::vector<item_t>& values)
    {
        /*
            Precond: values is a reference to a vector of "item_t". item_t is a type that can be compared using logical operators.
            Postcond: values is sorted using the Insertion Sort algorithm.
        */
        for (int current = 0; current < values.size(); current++) {
            insertItem(values, current);
        }
    }

    //Merge Sort
    template <class item_t>
    void merge(std::vector<item_t>& values, int left, int middle, int right) 
    {
        /*
            Precond: values is a reference to a vector of "item_t". left, middle, and right are all of type int. left refers to the
            left most index of the vector that we plan to merge, middle refers to the middle index of the vector that we plan to merge,
            while right refers to the right index of the vector that we plan to merge.
            Postcond: The two subvectors formed by the split at middle are merged back together into values.
        */
        //Create two subvectors, which represent the two halfs of a particular section in values.
        int leftSize = middle-left+1, rightSize = right-middle;
        std::vector<item_t> leftSub, rightSub;
        leftSub.reserve(leftSize);
        rightSub.reserve(rightSize);
        for (int i = 0; i < leftSize; i++) {
            leftSub.push_back(values.at(i+left));
        }
        for (int i = 0; i < rightSize; i++) {
            rightSub.push_back(values.at(i+middle+1));
        }
        //Merge Process:
        int totalItr = left, leftItr = 0, rightItr = 0;
        while (leftItr < leftSize && rightItr < rightSize) {
            if (leftSub.at(leftItr) <= rightSub.at(rightItr)) {
                values.at(totalItr) = leftSub.at(leftItr); 
                leftItr++;
            } else {
                values.at(totalItr) = rightSub.at(rightItr);
                rightItr++; 
            }
            totalItr++;
        }
        //Merge remaining elements back into values
        while (leftItr < leftSize) {
            values.at(totalItr) = leftSub.at(leftItr);
            leftItr++;
            totalItr++;
        }
        while (rightItr < rightSize) {
            values.at(totalItr) = rightSub.at(rightItr);
            rightItr++;
            totalItr++;
        }
    }

    template <class item_t>
    void mergeSort(std::vector<item_t>& values, int left, int right)
    {
        /*
            Precond: values is a reference to a vector of "item_t". left and right are both of type int. left reperesents the leftmost
            index of the array to be sorted, while right represents the rightmost index of the array to be sorted.
            Postcond: This method recursively breaks down the values vector, and then merges these divided parts into one sorted vector.
        */
        //Base Case: values has been broken down to a size of 1 or less elements at a particular point in the vector.
        if (left >= right) return;
        //Recursive Case: Break down the vector into halves: left and right half, and merge together each half in a sorted manner.
        int middle = (left+right)/2;
        mergeSort(values, left, middle);
        mergeSort(values, middle+1, right);
        merge(values, left, middle, right);
    }

    //Quick Sort
    template <class item_t>
    void split(std::vector<item_t>& values, int left, int right, int& splitPoint1, int& splitPoint2)
    {
        /*
            Precond: values is a reference to a vector of "item_t". left and right are both of type int, while splitPoint1 & 
            splitPoint2 are references to ints. left represents the leftmost index of the particular section of the vector to
            be split, while right represents the rightmost index of the particular section of the vector to be split. Both
            split points will be determined once the splitting process has completed.
            Postcond: All elements greater than the value of the index of the average of left and right are shifted to the
            right of splitPoint1, while all elements less or equal to the value of the index of the average of the left and
            right are shifted to the left of splitPoint2.
        */
        item_t splitValue = values.at((left+right)/2);
        bool notFound;
        do {
            notFound = true;
            while (notFound) {
                if (values.at(left) >= splitValue) {
                    notFound = false;
                } else {
                    left++;
                }
            }
            notFound = true;
            while (notFound) {
                if (values.at(right) <= splitValue) {
                    notFound = false;
                } else {
                    right--;
                }
            }
            if (left <= right) {
                swap(values.at(left), values.at(right));
                left++;
                right--;
            }
        } while (left <= right);
        splitPoint1 = left;
        splitPoint2 = right;
    }

    template <class item_t>
    void quickSort(std::vector<item_t>& values, int left, int right)
    {
        /*
            Precond: values is a reference to a vector of "item_t". left and right are both of type int. left represents the leftmost
            index of the array to be sorted, while right represents the rightmost index of the array to be sorted.
            Postcond: This method recursively breaks down the values vector by using a splitting point. Once values has been fully broken
            down, it will be sorted.
        */
        //Base Case: values has been broken down to a size of 1 or less elements at a particular point in the vector.
        if (left >= right) return;
        //Recursive Case: The section of the vector is broken down on a split value.
        int splitPoint1, splitPoint2;
        split(values, left, right, splitPoint1, splitPoint2);
        if (splitPoint1 < right) quickSort(values, splitPoint1, right);
        if (splitPoint2 > left) quickSort(values, left, splitPoint2);
    }

    //Radix Sort
    template<class item_t>
    void collectQueues(std::vector<item_t>& values, std::queue<item_t> queues[], int radix)
    {
        /*
            Precond: values is a reference to a vector of "item_t". queues is a vector of queues of size radix. radix is of type int,
            and is the radix of the data.
            Postcond: The queues are emptied, and determine the new order of values, which is based on the ordering of one of the poisitions
            of the data.
        */
        int i = 0;
        for (int j = 0; j < radix; j++) {
            while (!queues[j].empty()) {
                item_t val = queues[j].front();
                queues[j].pop();
                values.at(i) = val;
                i++;
            }
        } 
    }

    template <class item_t>
    void radixSort(std::vector<item_t>& values, int numPositions, int radix)
    {
        /*
            Precond: values is a reference to a vector of "item_t". numPositions is of type int, and refers to the max length of the elements
            in values. radix is of type int, and refers to the number of unique digits that can represent a number. NOTE: THIS IMPLEMENTATION
            ONLY WORKS FOR INTEGER TYPES!!!
            Postcond: values is sorted using the radix sort algorithm.
        */
        for (int i = 1; i <= numPositions; i++) {
            std::queue<item_t> queues[radix];
            for (int j = 0; j < values.size(); j++) {
                item_t val = (int)(values.at(j)/pow(10, i-1))%10;
                queues[val].push(values.at(j));
            }
            collectQueues(values, queues, radix);
        }
    }

    //Bogo Sort
    template <class item_t>
    bool isSorted(const std::vector<item_t>& values)
    {
        /*
            Precond: values is a const reference to a vector of "item_t".
            Postcond: If this vector is sorted, return true. Otherwise, return false.
        */
        for (int i = 1; i < values.size(); i++) {
            if (values.at(i) < values.at(i-1)) return false;
        }
        return true;
    }

    template <class item_t>
    void shuffle(std::vector<item_t>& values)
    {
        /*
            Precond: values is a reference to a vector of "item_t".
            Postcond: Shuffles all the elements in values into a random order.
        */
        int n = values.size();
        for (int i = 0; i < n; i++) {
            swap(values.at(i), values.at(rand()%n));
        }
    }

    template <class item_t>
    void bogoSort(std::vector<item_t>& values)
    {
        /*
            Precond: values is a reference to a vector of "item_t". 
            Postcond: values is sorted using the Bogo Sort algorithm. NOTE: This algorithm has an average runtime of O((n+1)!), meaning it
            should NEVER BE USED!
        */
        while (!isSorted(values)) {
            shuffle(values);
        }
    }
}

#endif