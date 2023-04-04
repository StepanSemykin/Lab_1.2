#include<iostream>

using namespace std;

struct TreeNode
{
	double data;
	TreeNode* right, * left;
};

class MySet
{
	private:
		TreeNode* root;

		void _clear(TreeNode* root)
		{
			if (root)
			{
				_clear(root->left);
				_clear(root->right);
				delete root;
			}
			root = nullptr;
		}

		TreeNode* _copy(TreeNode* other)
		{
			if (!other) return nullptr;
			TreeNode* tmp = new TreeNode;
			tmp->data = other->data;
			tmp->left = _copy(other->left);
			tmp->right = _copy(other->right);
			return tmp;
		}

	public:
		MySet()
		{
			root = nullptr;
		}

		MySet(const MySet& m)
		{
			root = _copy(m.root);
		}

		~MySet()
		{
			_clear(root);
		}

		void clear()
		{
			_clear(root);
		}

		MySet& operator = (const MySet& m)
		{
			if (!root) root = _copy(m.root);
			else 
			{
				_clear(root);
				root = _copy(m.root);
			}
			return *this;
		}


};