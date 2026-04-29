#include <gtest/gtest.h>
#include "../lib/include/array.h"

// ============================================================================
// Pruebas de Constructor
// ============================================================================

TEST(ArrayTest, DefaultConstructor) {
    Array<int> arr({});
    EXPECT_EQ(arr.size(), 0);
}

TEST(ArrayTest, ConstructorWithInitializerList) {
    Array<int> arr({1, 2, 3, 4, 5});
    EXPECT_EQ(arr.size(), 5);
}

TEST(ArrayTest, ConstructorWithSingleElement) {
    Array<int> arr({42});
    EXPECT_EQ(arr.size(), 1);
    EXPECT_EQ(arr[0], 42);
}

// ============================================================================
// Pruebas de Size
// ============================================================================

TEST(ArrayTest, SizeAfterCreation) {
    Array<int> arr({10, 20, 30});
    EXPECT_EQ(arr.size(), 3);
}

TEST(ArrayTest, SizeOfEmptyArray) {
    Array<int> arr({});
    EXPECT_EQ(arr.size(), 0);
}

// ============================================================================
// Pruebas de Acceso con Operador []
// ============================================================================

TEST(ArrayTest, IndexAccessRead) {
    Array<int> arr({10, 20, 30, 40});
    EXPECT_EQ(arr[0], 10);
    EXPECT_EQ(arr[1], 20);
    EXPECT_EQ(arr[2], 30);
    EXPECT_EQ(arr[3], 40);
}

TEST(ArrayTest, IndexAccessWrite) {
    Array<int> arr({1, 2, 3});
    arr[0] = 100;
    arr[1] = 200;
    arr[2] = 300;
    EXPECT_EQ(arr[0], 100);
    EXPECT_EQ(arr[1], 200);
    EXPECT_EQ(arr[2], 300);
}

TEST(ArrayTest, IndexAccessModify) {
    Array<int> arr({5, 10, 15});
    arr[1] += 5;
    EXPECT_EQ(arr[1], 15);
}

// ============================================================================
// Pruebas con Diferentes Tipos de Datos
// ============================================================================

TEST(ArrayTest, ArrayOfDoubles) {
    Array<double> arr({1.5, 2.5, 3.5});
    EXPECT_DOUBLE_EQ(arr[0], 1.5);
    EXPECT_DOUBLE_EQ(arr[1], 2.5);
    EXPECT_DOUBLE_EQ(arr[2], 3.5);
}

TEST(ArrayTest, ArrayOfStrings) {
    Array<std::string> arr({"hello", "world", "test"});
    EXPECT_EQ(arr[0], "hello");
    EXPECT_EQ(arr[1], "world");
    EXPECT_EQ(arr[2], "test");
}

TEST(ArrayTest, ArrayOfChars) {
    Array<char> arr({'a', 'b', 'c'});
    EXPECT_EQ(arr[0], 'a');
    EXPECT_EQ(arr[1], 'b');
    EXPECT_EQ(arr[2], 'c');
}

// ============================================================================
// Pruebas de Operador const
// ============================================================================

TEST(ArrayTest, ConstAccessOperator) {
    const Array<int> arr({10, 20, 30});
    EXPECT_EQ(arr[0], 10);
    EXPECT_EQ(arr[1], 20);
    EXPECT_EQ(arr[2], 30);
}

TEST(ArrayTest, ConstArraySizeCheck) {
    const Array<int> arr({1, 2, 3, 4, 5});
    EXPECT_EQ(arr.size(), 5);
}

// ============================================================================
// Pruebas de Acceso Secuencial
// ============================================================================

TEST(ArrayTest, IterateThroughArray) {
    Array<int> arr({1, 2, 3, 4, 5});
    int sum = 0;
    for (size_t i = 0; i < arr.size(); ++i) {
        sum += arr[i];
    }
    EXPECT_EQ(sum, 15);
}

TEST(ArrayTest, ModifyAllElements) {
    Array<int> arr({1, 2, 3, 4});
    for (size_t i = 0; i < arr.size(); ++i) {
        arr[i] *= 2;
    }
    EXPECT_EQ(arr[0], 2);
    EXPECT_EQ(arr[1], 4);
    EXPECT_EQ(arr[2], 6);
    EXPECT_EQ(arr[3], 8);
}

// ============================================================================
// Pruebas de Casos Especiales
// ============================================================================

TEST(ArrayTest, LargeArray) {
    Array<int> arr({0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 
                    20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39,
                    40, 41, 42, 43, 44, 45, 46, 47, 48, 49});
    EXPECT_EQ(arr.size(), 50);
    EXPECT_EQ(arr[0], 0);
    EXPECT_EQ(arr[49], 49);
}

TEST(ArrayTest, ArrayOfZeros) {
    Array<int> arr({0, 0, 0, 0});
    for (size_t i = 0; i < arr.size(); ++i) {
        EXPECT_EQ(arr[i], 0);
    }
}

TEST(ArrayTest, ArrayWithNegativeNumbers) {
    Array<int> arr({-1, -2, -3, -4});
    EXPECT_EQ(arr[0], -1);
    EXPECT_EQ(arr[1], -2);
    EXPECT_EQ(arr[2], -3);
    EXPECT_EQ(arr[3], -4);
}

// ============================================================================
// Pruebas de Propiedades
// ============================================================================

TEST(ArrayTest, SizeImmutableAfterCreation) {
    Array<int> arr({1, 2, 3});
    size_t size1 = arr.size();
    arr[0] = 100;
    size_t size2 = arr.size();
    EXPECT_EQ(size1, size2);
}

TEST(ArrayTest, ArrayIndexStartsAtZero) {
    Array<int> arr({10});
    EXPECT_EQ(arr[0], 10);
}
