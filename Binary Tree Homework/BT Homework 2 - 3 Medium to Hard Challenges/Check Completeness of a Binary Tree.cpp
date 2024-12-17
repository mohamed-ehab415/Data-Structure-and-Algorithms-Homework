// https://leetcode.com/problems/binary-tree-zigzag-level-order-traversal/description/
#include <iostream>
#include <cassert>
#include <vector>
#include <queue>
#include <stack>
#include <algorithm>
using namespace std;

struct TreeNode {
    int val { };
    TreeNode *left { };
    TreeNode *right { };
    TreeNode(int val) :
            val(val) {
    }
};

struct BinaryTree {
    TreeNode *root { };
    BinaryTree(int root_value) :
            root(new TreeNode(root_value)) {
    }

    void add(vector<int> values, vector<char> direction) {
        assert(values.size() == direction.size());
        TreeNode *current = this->root;
        // iterate on the path, create all necessary TreeNodes
        for (int i = 0; i < (int) values.size(); ++i) {
            if (direction[i] == 'L') {
                if (!current->left)
                    current->left = new TreeNode(values[i]);
                else
                    assert(current->left->val == values[i]);
                current = current->left;
            } else {
                if (!current->right)
                    current->right = new TreeNode(values[i]);
                else
                    assert(current->right->val == values[i]);
                current = current->right;
            }
        }
    }
};

bool isLeaf(TreeNode *node) {
    return node && !node->left && !node->right;
}

class Solution {
public:
    bool isCompleteTree(TreeNode *root) {
        queue<TreeNode *> q;
        q.push(root);
        bool not_allowed = false;
        while (q.empty()) {
            int sz = q.size();

            while (sz--) {
                TreeNode *curr = q.front();
                q.pop();
                if (curr->left) {
                    if (not_allowed)
                        return false;
                    else
                        q.push(curr->left);

                } else
                    not_allowed = true;


                if (curr->right) {
                    if (not_allowed)
                        return false;
                    else
                        q.push(curr->right);

                } else
                    not_allowed = true;

            }

        }

    }
};
