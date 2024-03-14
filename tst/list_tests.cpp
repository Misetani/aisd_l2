#include <gtest/gtest.h>

#include "../tree.h"
#include "../array_exception.h"

TEST(BST, DefaultConstructor) {
    BST<int, int> tree;
    EXPECT_EQ(tree.get_size(), 0);
}

TEST(BST, Insert) {
    BST<int, int> tree;
    EXPECT_EQ(tree.get_size(), 0);
    EXPECT_TRUE(tree.insert(1, 1));
    EXPECT_EQ(tree.get_size(), 1);
    EXPECT_TRUE(tree.insert(2, 2));
    EXPECT_EQ(tree.get_size(), 2);
    EXPECT_TRUE(tree.insert(3, 3));
    EXPECT_EQ(tree.get_size(), 3);
    EXPECT_TRUE(tree.insert(4, 4));
    EXPECT_EQ(tree.get_size(), 4);
    EXPECT_TRUE(tree.insert(5, 5));
    EXPECT_EQ(tree.get_size(), 5);
    EXPECT_TRUE(tree.insert(6, 6));
    EXPECT_EQ(tree.get_size(), 6);
    EXPECT_TRUE(tree.insert(7, 7));
    EXPECT_EQ(tree.get_size(), 7);
    EXPECT_TRUE(tree.insert(8, 8));
    EXPECT_EQ(tree.get_size(), 8);
    EXPECT_TRUE(tree.insert(9, 9));
    EXPECT_EQ(tree.get_size(), 9);
    EXPECT_FALSE(tree.insert(9, 9));
    EXPECT_EQ(tree.get_size(), 9);
    EXPECT_FALSE(tree.insert(1, 1));
}

TEST(BST, Remove) {
    BST<int, int> tree;
    EXPECT_EQ(tree.get_size(), 0);
    EXPECT_FALSE(tree.remove(1));
    EXPECT_EQ(tree.get_size(), 0);

    EXPECT_EQ(tree.get_size(), 0);
    EXPECT_TRUE(tree.insert(1, 1));
    EXPECT_TRUE(tree.insert(2, 2));
    EXPECT_TRUE(tree.insert(3, 3));

    EXPECT_EQ(tree.get_size(), 3);
    EXPECT_TRUE(tree.remove(2));
    EXPECT_EQ(tree.get_size(), 2);
    EXPECT_TRUE(tree.remove(3));
    EXPECT_EQ(tree.get_size(), 1);
    EXPECT_TRUE(tree.remove(1));
    EXPECT_EQ(tree.get_size(), 0);

    EXPECT_FALSE(tree.remove(1));
    EXPECT_FALSE(tree.remove(2));
    EXPECT_FALSE(tree.remove(3));

    EXPECT_EQ(tree.get_size(), 0);

    EXPECT_TRUE(tree.insert(1, 1));
    EXPECT_EQ(tree.get_size(), 1);
}

TEST(BST, clear) {
    BST<int, int> tree;
    EXPECT_EQ(tree.get_size(), 0);
    EXPECT_TRUE(tree.insert(1, 1));
    EXPECT_EQ(tree.get_size(), 1);
    EXPECT_TRUE(tree.insert(2, 2));
    EXPECT_EQ(tree.get_size(), 2);
    EXPECT_TRUE(tree.insert(3, 3));
    EXPECT_EQ(tree.get_size(), 3);

    tree.clear();

    EXPECT_EQ(tree.get_size(), 0);

    EXPECT_TRUE(tree.insert(1, 1));
    EXPECT_EQ(tree.get_size(), 1);
}

TEST(BST, indexation_operator) {
    BST<int, int> tree;
    EXPECT_EQ(tree.get_size(), 0);
    EXPECT_TRUE(tree.insert(1, 1));
    EXPECT_EQ(tree.get_size(), 1);
    EXPECT_TRUE(tree.insert(2, 2));
    EXPECT_EQ(tree.get_size(), 2);
    EXPECT_TRUE(tree.insert(3, 3));
    EXPECT_EQ(tree.get_size(), 3);

    EXPECT_EQ(tree[1], 1);
    EXPECT_EQ(tree[2], 2);
    EXPECT_EQ(tree[3], 3);

    EXPECT_THROW(tree[4], Array_exception);
    EXPECT_THROW(tree[-100], Array_exception);
    EXPECT_THROW(tree[0], Array_exception);

    tree[1] = 10;
    EXPECT_EQ(tree[1], 10);
    EXPECT_EQ(tree.get_size(), 3);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}