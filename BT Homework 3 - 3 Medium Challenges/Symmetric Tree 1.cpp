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

class Solution {
public:

    bool sysmtric(TreeNode *first , TreeNode *second) {

        if (!first&&!second)
            return true;

        if ((first&&!second)||(!first&&second)||(first->val!= second->val))
            return false;


        return sysmtric(first->left,second->right)&& sysmtric(first->right,second->left);




    }

    bool isSymmetric(TreeNode* root) {

        if (root)
            return true;
        return sysmtric(root->left,root->right);
    }



};