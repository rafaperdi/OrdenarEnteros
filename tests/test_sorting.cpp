#include <gtest/gtest.h>

#include "sorting.h"

TEST(SortingTest, SelectionSortHandlesEmptyArray) {
    Array<int> values({});
    ordenar(values);
    EXPECT_EQ(values.size(), 0U);
}

TEST(SortingTest, SelectionSortOrdersValues) {
    Array<int> values({4, -1, 4, 2, 0});
    ordenar(values);

    EXPECT_EQ(values[0], -1);
    EXPECT_EQ(values[1], 0);
    EXPECT_EQ(values[2], 2);
    EXPECT_EQ(values[3], 4);
    EXPECT_EQ(values[4], 4);
}

TEST(SortingTest, QuickSortHandlesEmptyArray) {
    Array<int> values({});
    quickSort(values);
    EXPECT_EQ(values.size(), 0U);
}

TEST(SortingTest, QuickSortHandlesSingleValue) {
    Array<int> values({42});
    quickSort(values);
    EXPECT_EQ(values[0], 42);
}

TEST(SortingTest, QuickSortOrdersValues) {
    Array<int> values({8, 3, 5, 1, 9, 2, 7, 4});
    quickSort(values);

    for (std::size_t i = 1; i < values.size(); ++i) {
        EXPECT_LE(values[i - 1], values[i]);
    }
}
