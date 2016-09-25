/*! \file bbst.h
\brief It implements balanced binary search tree and provides various methods to integrate range query with BBST.
*/

/*! \fn void insert(float data)
\brief Calls  BBSTNode *insert(float v, BBSTNode *t) to insert an entry in BBST.
\param data Value to insert.
*/

/*! \fn BBSTNode *insert(float v, BBSTNode *t)
\brief Returns the pointer to the node inserted in BBST.
\param v Value to insert.
\param t Pointer to the tree root.
*/

/*! \fn int height(BBSTNode *t)
\brief Returns the height of the node in BBST.
\param t Pointer to a node of tree.
*/

/*! \fn int max(int lhs, int rhs)
\brief Returns maximum of the two heights.
\param lhs Height of left child.
\param rhs Height of right child.
*/

/*! \fn BBSTNode *rotateWithLeftChild(BBSTNode* k)
\brief Returns the pointer to the node inserted in BBST after rotating the given node with its left child node.
\param k Pointer to a node in tree.
*/

/*! \fn BBSTNode *rotateWithRightChild(BBSTNode* k)
\brief Returns the pointer to the node inserted in BBST after rotating the given node with its right child node.
\param k Pointer to a node in tree.
*/

/*! \fn BBSTNode* findSplitNode(float v1, float v2)
\brief Calls BBSTNode *findSplitNode(BBSTNode* k, float v1, float v2)
\param v1 Lower range value.
\param v2 Upper range value.
*/

/*! \fn BBSTNode *findSplitNode(BBSTNode* k, float v1, float v2)
\brief Returns the splitting node for v1 and v2 ie. the least common ancestor of v1 and v2.
\param v1 Lower range value.
\param v2 Upper range value.
*/

/*! \fnBBSTNode *doubleRotateWithLeftChild(BBSTNode *k) 
\brief Returns the pointer to the node inserted in BBST after rotating the left child with its right child then node k with new left child.
\param k Pointer to a tree node.
*/

/*! \fn BBSTNode *doubleRotateWithRightChild(BBSTNode *k)
\brief Returns the pointer to the node inserted in BBST after rotating the right child with its left child then node k with new right child.
\param k Pointer to a tree node.
*/

/*! \fn bool search(float v)
\brief Calls bool search(BBSTNode *k, float val).
\param v Value to be searched in tree.
*/

/*! \fn bool search(BBSTNode *k, float v)
\brief Returns true if a noe with value v is found, else returns false.
\param k Pointer to the tree root.
\param v Value to be searched in tree.
*/

/*! \fn void addValue( BBSTNode *k, vector< float >& v)
\brief Adds all the nodes in the pointer defined by k to the vector v. 
\param k Pointer to a tree node.
\param v Vector containing the nodes in the range.
*/

/*! \fn void preorder()
\brief Calls void preorder(BBSTNode *k)
*/

/*! \fn  void preorder(BBSTNode *k)
\brief Prints the preorder traversal of the tree starting from the root.
\param k Pointer to the tree root.
*/

/*! \fn void followLower( float v1, BBSTNode* k, vector< float >& v)
\brief Follows the lower range value until a tree leaf is encountered and report the subtrees encountered.
\param v1 Lower range value.
\param k Pointer to the split node in the tree.
\param v Vector containing the nodes in the range.
*/

/*! \fn void followUpper( float v2, BBSTNode* k, vector< float >& v)
\brief Follows the upper range value until a tree leaf is encountered and report the subtrees encountered.
\param v2 Upper range value.
\param k Pointer to the split node in the tree.
\param v Vector containing the nodes in the range.
*/

/*! \fn void reportSubTree( BBSTNode* k, vector< float>& v)
\brief Reports all the nodes under k node by calling addValue function,
\param k Pointer to a node in the tree.
\param v Vector containing the nodes in the range.
*/


#ifndef bbst_h
#define bbst_h
#include <iostream>
#include <math.h>
#include <string>
#include <set>
#include <cstring>
#include <vector>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <algorithm>
#include <locale> 
#include "bbst.h"

using namespace std;

/*! A class for defining node in a balanced Binary Search Tree */
class BBSTNode
{
	public:
		int height; /*!< Value of the height of a node */
		float data; /*!< Value of the node */
		BBSTNode *left; /*!< Pointer to the left child of the node */
		BBSTNode *right; /*!< Pointer to the right child of the node */

		//! Constructor
    		/*!
    		  To initialize an empty root node.
    		*/
        BBSTNode()
		{
			left = NULL;
			right = NULL;
			data = 0.0;
			height = 0;
		}
		
		//! Constructor
    		/*!
    		  To initialize any node in the BBST.
    		*/
	    BBSTNode(float n)
        {
			left = NULL;
			right = NULL;
			data = n;
			height = 0;
		}
};

/*! A class for defining all the functions of the balanced Binary Search Tree */
class BBST
{
	 private:
		BBSTNode *root; /*!< Pointer to the root node */

   	 public:
   	 	
   	 	//! Constructor
    		/*!
    		  To initialize the root node of BBST as NULL.
    		*/
         	BBST()
         	{
         		root = NULL;
         	}

         void insert(float data)
         {
		root = insert(data, root);
         }

         int height(BBSTNode *t)
         {
                return t == NULL ? -1 : t->height;
         }

         int max(int lhs, int rhs)
         {
             	return lhs > rhs ? lhs : rhs;
         }

         BBSTNode *insert(float v, BBSTNode *t)
         {
                if (t == NULL)
                 	t = new BBSTNode(v);
		else if (v < t->data)
		{
			t->left = insert(v, t->left);
			if (height(t->left) - height(t->right) == 2)
				if (v < t->left->data)
					t = rotateWithLeftChild(t);
				else
					t = doubleRotateWithLeftChild(t);
		}
		else if (v > t->data)
		{
			t->right = insert(v, t->right);
			if (height(t->right) - height(t->left) == 2)
				if (v > t->right->data)
					t = rotateWithRightChild(t);
				else
					t = doubleRotateWithRightChild(t);
		}
		t->height = max(height(t->left), height(t->right)) + 1;
             	return t;
	 }
	 
         BBSTNode *rotateWithLeftChild(BBSTNode* k)
	 {
		BBSTNode *k1 = k->left;
		k->left = k1->right;
		k1->right = k;
		k->height = max(height(k->left), height(k->right)) + 1;
		k1->height = max(height(k1->left), k->height) + 1;
		return k1;
         }

	 BBSTNode *rotateWithRightChild(BBSTNode* k)
	 {
		BBSTNode *k1 = k->right;
		k->right = k1->left;
		k1->left = k;
		k->height = max(height(k->left), height(k->right)) + 1;
		k1->height = max(height(k1->right), k->height) + 1;
		return k1;
         }
       
         BBSTNode* findSplitNode(float v1, float v2)
         {
         	 //cout << root->data;
		 return findSplitNode(root, v1, v2);
         }
        
	 BBSTNode *findSplitNode(BBSTNode* k, float v1, float v2)
	 {
	 	//cout << " " << k->data << " ";
	 	while(( k!= NULL )&&((v2 <= k->data)||(v1 > k->data)))
	 	{
	 		if(v2 <= k->data)
	 		{
	 			if((k->left == NULL)&&(k->right ==NULL))
	 				return k;
	 			k = k->left;
	 		}
	 		else
	 		{
	 			if((k->left == NULL)&&(k->right ==NULL))
	 				return k;
	 			k = k->right;
	 		}
	 	}
	 	return k;
	 }
 
	 BBSTNode *doubleRotateWithLeftChild(BBSTNode *k)
	 {	
	 	k->left = rotateWithRightChild(k->left);
		return rotateWithLeftChild(k);
         }

	 BBSTNode *doubleRotateWithRightChild(BBSTNode *k)
	 {	
	 	k->right = rotateWithLeftChild(k->right);
		return rotateWithRightChild(k);
         }

         bool search(float v)
         {
		return search(root, v);
         }

         bool search(BBSTNode *k, float v)
         {
		bool found = false;
		while ((k != NULL) && !found)
		{
			int rvalue = k->data;
			if (v < rvalue)
				k = k->left;
			else if (v > rvalue)
				k = k->right;
			else
			{
				found = true;
				break;
			}
			found = search(k, v);
		}
		return found;
         }
         
	 void addValue( BBSTNode *k, vector< float >& v)
	 {
	 	if (k != NULL)
		{
			addValue( k->left, v);
			v.push_back( k->data);
			addValue( k->right, v);
		}
	 }
	 
	 void preorder()
	 {
	 	preorder(root);
	 }
	 
	 void preorder(BBSTNode *k)
         {
		if (k != NULL)
		{
			cout<< k->data << "  ";
			preorder( k->left);
			preorder( k->right );
		}
	 }
	 
	 void followLower( float v1, BBSTNode* k, vector< float >& v)
	 {
	 	k = k->left;
	 	if( k->data >= v1)
	 		v.push_back(k->data);
	 	while(k!=NULL)
	 	{
			if(v1 <= k->data)
			{
			        v.push_back(k->data);
				reportSubTree(k->right, v);
				k = k->left;
			}
			else
				k = k->right;
		}
	 }

	 void followUpper( float v2, BBSTNode* k, vector< float >& v)
	 {
	 	k = k->right;
	 	if( k->data <= v2)
	 		v.push_back(k->data);
	 	while(k!=NULL)
		{
			if(v2 >=  k->data)
			{
				v.push_back(k->data);
				reportSubTree(k->left, v);
				k = k->right;
			}
			else
				k = k->left;
		}
	 }

	 void reportSubTree( BBSTNode* k, vector< float>& v)
	 {
		addValue(k,v );
	 }
};

#endif