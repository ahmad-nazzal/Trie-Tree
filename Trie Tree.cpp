#include <iostream>
#include <vector>
#include <algorithm>
#include <stack>
using namespace std;

struct TrieNode
{
    vector <TrieNode*> children;
    char val;
};
TrieNode* createNode(char ch)
{
    TrieNode* trieNode = new TrieNode();
    trieNode->val = ch;
    return trieNode;

}
void insert(TrieNode* root, string strr)
{
    TrieNode* tempRoot = root;
    for (int j = 0; j < strr.size(); j++)
    {
        bool existchild = false;
        for (int i = 0; i < tempRoot->children.size(); i++)
        {
            if (tempRoot->children[i]->val == strr[j])
            {
                existchild = true;
                tempRoot = tempRoot->children[i];
                break;
            }
        }
        if (!existchild)
        {
            tempRoot->children.push_back(createNode(strr[j]));
            tempRoot = tempRoot->children[tempRoot->children.size() - 1];

        }

    }
    tempRoot->children.push_back(createNode('$'));

}

void search(TrieNode* root, string strr)
{
    TrieNode* tempRoot = root;
    for (int j = 0; j < strr.size(); j++)
    {
        bool existchild = false;
        for (int i = 0; i < tempRoot->children.size(); i++)
        {
            if (tempRoot->children[i]->val == strr[j])
            {
                existchild = true;
                tempRoot = tempRoot->children[i];

            }
        }
        if (!existchild)
        {

            cout << "NO\n";
            return;
        }

    }
    for (int i = 0; i < tempRoot->children.size(); i++)
    {
        if (tempRoot->children[i]->val == '$')
        {
            cout << "YES\n";
            return;

        }
    }
    //to solve the problem that if the word was add and exist adding
    cout << "NO\n";
    return;
}

void deleteString(TrieNode* root, string strr)
{
    stack <TrieNode*>stk;
    TrieNode* tempRoot = root;
    for (int j = 0; j < strr.size(); j++)
    {
        bool existchild = false;
        for (int i = 0; i < tempRoot->children.size(); i++)
        {
            if (tempRoot->children[i]->val == strr[j])
            {
                existchild = true;
                stk.push(tempRoot->children[i]);
                tempRoot = tempRoot->children[i];
            }
        }
        if (!existchild)
        {
            cout << strr + " not exist in the tree to delete\n";
            return;
        }

    }
    bool existStr = false;
    for (int i = 0; i < tempRoot->children.size(); i++)
    {
        if (tempRoot->children[i]->val == '$')
        {
            tempRoot->children.erase(tempRoot->children.begin() + i);
            existStr = true;
            break;
        }
    }
    //to solve the problem that if the word was add and exist adding
    if (!existStr)
    {
        cout << strr + " not exist in the tree to delete\n";
        return;
    }
    ////to delete each node that dont have children
    //TrieNode* trieNode;
    //while (!stk.empty())
    //{
    //    trieNode = stk.top();
    //    if (trieNode->children.size() == 0)
    //    {
    //        delete trieNode;
    //        trieNode = NULL;
    //    }
    //    else {
    //        break;
    //    }
    //    stk.pop();
    //}

}

void startWithAllPaths(TrieNode* root, vector <string>& strs, string strr)
{
    if (root->val == '$')
    {
        strs.push_back(strr);
    }
    for (int i = 0; i < root->children.size(); i++)
    {
        if (root->children[i]->val != '$')
            startWithAllPaths(root->children[i], strs, strr + root->children[i]->val);
        else
            startWithAllPaths(root->children[i], strs, strr);

    }
}

void startWith(TrieNode* root, string strr)
{
    TrieNode* tempRoot = root;
    for (int j = 0; j < strr.size(); j++)
    {
        bool existchild = false;
        for (int i = 0; i < tempRoot->children.size(); i++)
        {
            if (tempRoot->children[i]->val == strr[j])
            {
                existchild = true;
                tempRoot = tempRoot->children[i];

            }
        }
        if (!existchild)
        {

            cout << "NO string\n";
            return;
        }

    }
    vector <string>strs;
    startWithAllPaths(tempRoot, strs, strr);
    sort(strs.begin(), strs.end());
    for (int i = 0; i < strs.size(); i++)
    {
        cout << strs[i] << endl;
    }

}
void longest(TrieNode* root, string str, string& longestStr)
{
    if (root->val == '$')
    {
        if (str.size() > longestStr.size())
        {
            longestStr = str;
        }
    }
    for (int i = 0; i < root->children.size(); i++)
    {
        if (root->children[i]->val != '$')
            longest(root->children[i], str + root->children[i]->val, longestStr);
        else
            longest(root->children[i], str, longestStr);
    }

}


int main()
{
    int test;
    cin >> test;
    string opInput, strInputt;
    TrieNode* root = new TrieNode();
    for (int i = 0; i < test; i++)
    {
        cin >> opInput;
        if (opInput == "longest")
        {
            string longestStr = "";
            longest(root, "", longestStr);
            cout << longestStr << endl;
        }
        else
        {
            cin >> strInputt;
            if (opInput == "insert")
            {
                insert(root, strInputt);
            }
            else if (opInput == "search")
            {
                search(root, strInputt);
            }
            else if (opInput == "startwith")
            {
                startWith(root, strInputt);

            }
            else if (opInput == "delete")
            {
                deleteString(root, strInputt);
            }
            else
            {
                cout << "enter valid input" << endl;
            }

        }

    }





}

