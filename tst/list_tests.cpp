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
    EXPECT_FALSE(tree.remove(1));

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

TEST(BST, const_indexation_operator) {
    BST<int, int> tree;
    EXPECT_EQ(tree.get_size(), 0);
    EXPECT_TRUE(tree.insert(1, 1));
    EXPECT_EQ(tree.get_size(), 1);
    EXPECT_TRUE(tree.insert(2, 2));
    EXPECT_EQ(tree.get_size(), 2);
    EXPECT_TRUE(tree.insert(3, 3));
    EXPECT_EQ(tree.get_size(), 3);

    const BST<int, int>& ctree = tree;
    EXPECT_EQ(tree.get_size(), 3);
    EXPECT_EQ(ctree[1], 1);
    EXPECT_EQ(ctree[2], 2);
    EXPECT_EQ(ctree[3], 3);
    EXPECT_EQ(tree.get_size(), 3);
    EXPECT_THROW(ctree[4], Array_exception);
    EXPECT_THROW(ctree[-100], Array_exception);
    EXPECT_THROW(ctree[0], Array_exception);
}

TEST(BST, printing_test) {
    BST<int, int> tree;
    tree.insert(5, 5);
    tree.insert(8, 8);
    tree.insert(3, 3);
    tree.insert(6, 6);
    tree.insert(7, 7);
    tree.insert(9, 9);
    tree.insert(4, 4);
    tree.insert(2, 2);
    tree.insert(1, 1);
    tree.print_tree();
}

TEST (BST, at_test) {
    BST<int, int> tree;
    tree.insert(5, 5);
    tree.insert(8, 8);
    tree.insert(3, 3);
    tree.insert(6, 6);
    tree.insert(7, 7);
    tree.insert(9, 9);
    tree.insert(4, 4);
    tree.insert(2, 2);
    tree.insert(1, 1);
    EXPECT_EQ(tree.at(1), 1);
    EXPECT_EQ(tree.at(2), 2);
    EXPECT_EQ(tree.at(3), 3);
    EXPECT_EQ(tree.at(4), 4);
    EXPECT_EQ(tree.at(5), 5);
    EXPECT_EQ(tree.at(6), 6);
    EXPECT_EQ(tree.at(7), 7);
    EXPECT_EQ(tree.at(8), 8);
    EXPECT_EQ(tree.at(9), 9);
    EXPECT_THROW(tree.at(10), Array_exception);
    EXPECT_THROW(tree.at(-100), Array_exception);
    EXPECT_THROW(tree.at(0), Array_exception);
}

TEST (BST, const_at_test) {
    BST<int, int> tree;
    tree.insert(5, 5);
    tree.insert(8, 8);
    tree.insert(3, 3);
    tree.insert(6, 6);
    tree.insert(7, 7);
    tree.insert(9, 9);
    tree.insert(4, 4);
    tree.insert(2, 2);
    tree.insert(1, 1);

    const BST<int, int>& ctree = tree;
    EXPECT_EQ(ctree.at(1), 1);
    EXPECT_EQ(ctree.at(2), 2);
    EXPECT_EQ(ctree.at(3), 3);
    EXPECT_EQ(ctree.at(4), 4);
    EXPECT_EQ(ctree.at(5), 5);
    EXPECT_EQ(ctree.at(6), 6);
    EXPECT_EQ(ctree.at(7), 7);
    EXPECT_EQ(ctree.at(8), 8);
    EXPECT_EQ(ctree.at(9), 9);
    EXPECT_THROW(ctree.at(10), Array_exception);
    EXPECT_THROW(ctree.at(-100), Array_exception);
    EXPECT_THROW(ctree.at(0), Array_exception);
}

TEST(BST, get_keys_test) {
    BST<int, int> tree;
    tree.insert(5, 5);
    tree.insert(8, 8);
    tree.insert(3, 3);
    tree.insert(6, 6);
    tree.insert(7, 7);
    tree.insert(9, 9);
    tree.insert(4, 4);
    tree.insert(2, 2);
    tree.insert(1, 1);

    std::vector<int> keys = tree.get_keys();
    EXPECT_EQ(keys.size(), 9);

    EXPECT_EQ(keys[0], 1);
    EXPECT_EQ(keys[1], 2);
    EXPECT_EQ(keys[2], 3);
    EXPECT_EQ(keys[3], 4);
    EXPECT_EQ(keys[4], 5);
    EXPECT_EQ(keys[5], 6);
    EXPECT_EQ(keys[6], 7);
    EXPECT_EQ(keys[7], 8);
    EXPECT_EQ(keys[8], 9);
}

TEST (BST, get_keys_test2) {
    BST<int, int> tree;
    tree.insert(5, 5);
    tree.insert(4, 4);
    tree.insert(3, 3);
    tree.insert(2, 2);
    tree.insert(1, 1);

    std::vector<int> keys = tree.get_keys();
    EXPECT_EQ(keys.size(), 5);

    EXPECT_EQ(keys[0], 1);
    EXPECT_EQ(keys[1], 2);
    EXPECT_EQ(keys[2], 3);
    EXPECT_EQ(keys[3], 4);
    EXPECT_EQ(keys[4], 5);
}

TEST(BST, get_external_path_length_test) {
    BST<int, int> tree;
    tree.insert(5, 5);
    tree.insert(8, 8);
    tree.insert(3, 3);
    tree.insert(6, 6);
    tree.insert(7, 7);
    tree.insert(9, 9);
    tree.insert(4, 4);
    tree.insert(2, 2);
    tree.insert(1, 1);

    EXPECT_EQ(tree.get_external_path_length(), 10);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}