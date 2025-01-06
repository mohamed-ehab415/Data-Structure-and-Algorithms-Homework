#include <iostream>
#include <cassert>
#include <vector>
#include <algorithm>
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


class Solution {
public:

    string partenzie(TreeNode * root){
        vector<string>s;
        string  repr='('+ to_string(root->val);
        if (!root)
            return "()";

        if (root->left)
            s.push_back(partenzie(root->left));
        else
            s.push_back("()");

        if (root->right)
            s.push_back(partenzie(root->right));
        else
            s.push_back("()");
        s.push_back(")");


        sort(s.begin(),s.end());
        for (int i = 0; i <s.size(); ++i) {
            repr+=s[i];

        }

        return repr;
    }

    bool flipEquiv(TreeNode* root1, TreeNode* root2) {
        if (!root1 ||!root2)
            return false;
        if (!root1&&!root2)
            return true;
        return partenzie(root1)== partenzie(root2);


    }
};