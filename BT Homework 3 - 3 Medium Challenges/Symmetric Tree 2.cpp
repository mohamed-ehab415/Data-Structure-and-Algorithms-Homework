#include <iostream>
#include <cassert>
#include <vector>
using namespace std;

struct TreeNode {		// don't copy for leetcode
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

class Solution{

public:
    string parenthesize(TreeNode *root, bool left_first = true) {
        if (!root)
            return "()";

        string repr="(" + to_string(root->val);
        if (left_first){
            if (left)
                repr+= parenthesize(root->left);
            else
                repr+="()";
            if (right)
                repr+= parenthesize(root->right);
            else
                repr+="()";

        }
        else{
            if (right)
                repr+= parenthesize(root->right);
            else
                repr+="()";

            if (left)
                repr+= parenthesize(root->left);
            else
                repr+="()";

        }

        repr+=')';

        return repr;


    }

    bool isSymmetric(TreeNode *root) {
        if (!root)
            return false;

        if (!root->left && !root->right)
            return true;

        if (!root->left && root->right || root->left && !root->right)
            return false;

        return parenthesize(root->left, true) == parenthesize(root->right, false);
    }
};


