#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <iostream>
#include "../include/maxHeap.h"

using namespace std;

TEST(MaxHeap, test_hasKey) {
    cout << "\tTesting MaxHeap - hasKey\n" << endl;

    MaxHeap<int, int> maxHeap(8, -1);
    maxHeap.insert(8, 1);
    maxHeap.insert(7, 2);
    maxHeap.insert(6, 3);
    maxHeap.insert(5, 4);

    ASSERT_EQ(false, maxHeap.hasKey(1));
    ASSERT_EQ(true, maxHeap.hasKey(8));
    ASSERT_EQ(true, maxHeap.hasKey(7));
    ASSERT_EQ(false, maxHeap.hasKey(9));
    ASSERT_EQ(true, maxHeap.hasKey(6));
    ASSERT_EQ(true, maxHeap.hasKey(5));
    ASSERT_EQ(true, maxHeap.hasKey(5)); //just to check again
}


TEST(MaxHeap, test_removeMax) {
    cout << "\tTesting MaxHeap - insert & removeMax\n" << endl;

    MaxHeap<int, int> maxHeap(8, -1);
    maxHeap.insert(8, 1);
    maxHeap.insert(7, 2);
    maxHeap.insert(6, 3);
    maxHeap.insert(5, 4);
    maxHeap.insert(1, 10);
    maxHeap.insert(2, 20);
    maxHeap.insert(3, 15);
    maxHeap.insert(4, 100);

    ASSERT_EQ(4, maxHeap.removeMax());
    ASSERT_EQ(2, maxHeap.removeMax());
    ASSERT_EQ(3, maxHeap.removeMax());
    ASSERT_EQ(1, maxHeap.removeMax());
    ASSERT_EQ(5, maxHeap.removeMax());
    ASSERT_EQ(6, maxHeap.removeMax());
    ASSERT_EQ(7, maxHeap.removeMax());
    ASSERT_EQ(8, maxHeap.removeMax());
}

TEST(MaxHeap, test_increaseKey) {
    cout << "\tTesting MaxHeap - increaseKey\n" << endl;

    MaxHeap<int, int> maxHeap(8, -1);
    maxHeap.insert(8, 1);
    maxHeap.insert(7, 2);
    maxHeap.insert(6, 3);
    maxHeap.insert(5, 4);
    maxHeap.insert(1, 10);
    maxHeap.insert(2, 20);
    maxHeap.insert(3, 15);
    maxHeap.insert(4, 100);

    maxHeap.increaseKey(8, 200);
    maxHeap.increaseKey(6, 70);
    maxHeap.increaseKey(5, 150);
    maxHeap.increaseKey(3, 1000);
    maxHeap.increaseKey(3, 1);

    ASSERT_EQ(3, maxHeap.removeMax());
    ASSERT_EQ(8, maxHeap.removeMax());
    ASSERT_EQ(5, maxHeap.removeMax());
    ASSERT_EQ(4, maxHeap.removeMax());
    ASSERT_EQ(6, maxHeap.removeMax());
    ASSERT_EQ(2, maxHeap.removeMax());
    ASSERT_EQ(1, maxHeap.removeMax());
    ASSERT_EQ(7, maxHeap.removeMax());

}





