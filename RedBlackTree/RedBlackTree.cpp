// RedBlackTree.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <vector>
#include <iostream>

using namespace std;

struct RedBlackTreeNode
{
    enum Color
    {
        Red,
        Black,
    };

    RedBlackTreeNode(int v, Color c = Red)
    {
        mValue = v;
        mColor = c;
        mLeft = NULL;
        mRight = NULL;
    }

    bool IsRed()
    {
        return mColor == Red;
    }

    bool IsBlack()
    {
        return mColor == Black;
    }

    Color mColor;
    int mValue;
    RedBlackTreeNode* mLeft;
    RedBlackTreeNode* mRight;
};


struct RedBlackTree
{
    enum ErrorCode
    {
        Success,
        AlreadeExist,
        StructureError,

    };
    RedBlackTree() 
    {
        mRoot = NULL;
    }

    RedBlackTreeNode* ParentRed(RedBlackTreeNode* parent, RedBlackTreeNode* node, RedBlackTreeNode* child)
    {
        if (parent->mLeft == node)
        {
            if (node->mLeft == child)
            {
                parent->mLeft = node->mRight;
                node->mRight = parent;
                return node;
            }
            else if(node->mRight== child)
            {
                node->mRight = child->mLeft;
                parent->mLeft = child->mRight;

                child->mLeft = node;
                child->mRight = parent;

                return child;
            }
            else
            {
                throw StructureError;
            }
        }
        else if (parent->mRight == node)
        {
            if (node->mLeft == child)
            {
                parent->mRight = child->mLeft;
                node->mLeft = child->mRight;

                child->mLeft = parent;
                child->mRight = node;

                return child;
            }
            else if (node->mRight == child)
            {
                parent->mRight = node->mLeft;
                node->mLeft = parent;
                return node;

            }
            else
            {
                throw StructureError;
            }
        }
        else
        {
            throw StructureError;
        }
    }

    void Adjust(vector<RedBlackTreeNode*>& stack)
    {
        while (stack.size())
        {
            RedBlackTreeNode* child = stack.back();
            stack.pop_back();
            if (stack.empty())
            {
                child->mColor = RedBlackTreeNode::Black;
                break;
            }

            if (child->IsBlack())
            {
                break;
            }

            RedBlackTreeNode* node = stack.back();
            if (node->mLeft == child)
            {
                if (node->mRight && node->mRight->IsRed())
                {
                    node->mLeft->mColor = RedBlackTreeNode::Black;
                    node->mRight->mColor = RedBlackTreeNode::Black;
                    node->mColor = RedBlackTreeNode::Red;
                    continue;
                }
            }
            else if (node->mRight == child)
            {
                if (node->mLeft && node->mLeft->IsRed())
                {
                    node->mLeft->mColor = RedBlackTreeNode::Black;
                    node->mRight->mColor = RedBlackTreeNode::Black;
                    node->mColor = RedBlackTreeNode::Red;
                    continue;
                }

            }
            else
            {
                throw StructureError;
            }

            if (node->IsBlack())
            {
                break;
            }

            stack.pop_back();
            if (stack.empty())
            {
                throw StructureError;
            }
            
            RedBlackTreeNode* parent = stack.back();
            if (parent->IsRed())
            {
                stack.pop_back();
                parent = ParentRed(parent, node, child);
                parent->mColor = RedBlackTreeNode::Red;
                stack.push_back(parent);
            }
            else
            {
                stack.push_back(node);
            }
        }


    }

    void _Insert(RedBlackTreeNode* node, int v, vector<RedBlackTreeNode*>& stack)
    {
        stack.push_back(node);
        if (node->mValue > v)
        {
            if (node->mLeft)
            {
                _Insert(node->mLeft, v, stack);
            }
            else
            {
                node->mLeft = new RedBlackTreeNode(v);
                stack.push_back(node->mLeft);
                Adjust(stack);
            }

        }
        else if (node->mValue < v)
        {
            if (node->mRight)
            {
                _Insert(node->mRight, v, stack);
            }
            else
            {
                node->mRight = new RedBlackTreeNode(v);
                stack.push_back(node->mRight);
                Adjust(stack);

            }

        }
        else
        {
            throw AlreadeExist;
        }
    }

    ErrorCode Insert(int v)
    {
        if (mRoot)
        {
            try
            {
                vector<RedBlackTreeNode*> stack;
                _Insert(mRoot, v, stack);

            }
            catch (ErrorCode error)
            {
                return error;
            }
        }
        else
        {
            mRoot = new RedBlackTreeNode(v, RedBlackTreeNode::Black);
        }

        return Success;

    }

    void Remove(int node)
    {

    }

    void Travers(RedBlackTreeNode* node, int currentDepth, int& maxDepth)
    {
        if (node->IsBlack())
        {
        ++maxDepth;
        ++currentDepth;
        }

        if (node->mLeft)
        {
            Travers(node->mLeft, currentDepth, maxDepth);
        }

        if (node->mRight)
        {
            Travers(node->mRight, currentDepth , maxDepth);

        }

            if ((node->mLeft==NULL )&& (node->mRight == NULL))
            {
                if (currentDepth == maxDepth)
                {

                }
                else
                {
                    throw StructureError;
                }
            }
    }

    bool Check()
    {
        try
        {
            int maxDepth = 0;
            Travers(mRoot, 0, maxDepth);
        }
        catch (ErrorCode )
        {
            return false;
        }

        return true;
    }
private:
    RedBlackTreeNode* mRoot;
};


int main()
{
    RedBlackTree tree;
    tree.Insert(13);
    tree.Insert(8);
    tree.Insert(17);
    tree.Insert(1);
    tree.Insert(6);
    tree.Insert(11);
    tree.Insert(15);
    tree.Insert(25);
    tree.Insert(22);
    tree.Insert(27);
    cout << tree.Check() << '\n';
    return 0;
}

