#include "AVL.h"
#include <cassert>
#include <iostream>
#include <string>
#include<algorithm>
#include<stdio.h>

#include <queue>

#include "json.hpp"


AVLNode::AVLNode(int key) :   // first insertion since it is the 
	key_(key),
	parent_(std::weak_ptr<AVLNode>()), 
	left_(nullptr),
	right_(nullptr) {}

AVLNode::AVLNode(int key, std::weak_ptr<AVLNode> parent) :
	key_(key),
	parent_(parent),
	left_(nullptr),
	right_(nullptr) {}



AVL::AVL() : 
    root_(nullptr),
    size_(0) {}



int AVL::height(std::shared_ptr<AVLNode> keyNode)
{
    if (!keyNode)
    {
        return -1;
    }
    return (std::max(height(keyNode->left_), height(keyNode->right_)) + 1);
}



std::shared_ptr<AVLNode> AVL::leftRotate(std::shared_ptr<AVLNode> keyNode)
{
    std::shared_ptr<AVLNode> temp = keyNode->right_;     // making temp pointer
    keyNode->right_ = temp->left_;       // readjustment of pointers
    temp->left_ = keyNode;

    if (keyNode->right_ != nullptr)                 // if there is a child make the child's parent the rotated note
    {
        keyNode->right_->parent_ = keyNode;
    }
    temp->parent_ = keyNode->parent_;
    if (keyNode->parent_.lock())
    {
        if (keyNode == keyNode->parent_.lock()->left_)
        {
            keyNode->parent_.lock()->left_ = temp;
        }
        else if (keyNode == keyNode->parent_.lock()->right_)
        {
            keyNode->parent_.lock()->right_ = temp;
        }
    }
    keyNode->parent_ = temp;                    // making the temp pointer the new root
    return temp;
}



std::shared_ptr<AVLNode> AVL::rightRotate(std::shared_ptr<AVLNode> keyNode){
    std::shared_ptr<AVLNode> temp = keyNode->left_;

    keyNode->left_ = temp->right_;
    temp->right_ = keyNode;                     // readjustment of pointers
    
    if (keyNode->left_)
    {
        keyNode->left_->parent_ = keyNode;
    }
    temp->parent_ = keyNode->parent_;
    
    if (keyNode->parent_.lock())                // if there is a child make the child's parent the rotated note
    {
        if (keyNode == keyNode->parent_.lock()->left_)
        {
            keyNode->parent_.lock()->left_ = temp;
        }
        else if (keyNode == keyNode->parent_.lock()->right_)
        {
            keyNode->parent_.lock()->right_ = temp;
        }
    }
    keyNode->parent_ = temp;                     // making the temp pointer the new root
    return temp;
}


std::shared_ptr<AVLNode> AVL::LRrotate(std::shared_ptr<AVLNode> keyNode)
{
    keyNode->left_ = leftRotate(keyNode->left_);            // rotating the left child node
    return rightRotate(keyNode);                            // then rotate the left node after
}
std::shared_ptr<AVLNode> AVL::RLrotate(std::shared_ptr<AVLNode> keyNode)
{
    keyNode->right_ = rightRotate(keyNode->right_);         // rotating the right child note
    return leftRotate(keyNode);                             // then rotate the left node after
}




void AVL::rebalance(std::shared_ptr<AVLNode> keyNode){
    if (abs(height(keyNode->right_) - height(keyNode->left_)) > 1)
    {

            if(getBalance(keyNode) < -1 && getBalance(keyNode->left_) <= -1){       // if left heavy
                    keyNode = rightRotate(keyNode);
            }
            if(getBalance(keyNode)  < -1 && getBalance(keyNode->left_) >= 1){       // if right-left heavy
                    keyNode = LRrotate(keyNode);
            }
            if(getBalance(keyNode)  > 1 &&  getBalance(keyNode->right_) >= 1){      // if right heavy
                    keyNode = leftRotate(keyNode);
                }
            if(getBalance(keyNode)  > 1 &&  getBalance(keyNode->right_) <= -1){     // if left-right heacy 
                    keyNode = RLrotate(keyNode);
            }
            if (keyNode->parent_.lock() == nullptr){    // if the parent of the rotated node is null change the root   
                root_ = keyNode;
            }

    }   
    if (!keyNode->parent_.lock())               // if parent is null then all parents are balanced
    {
        return;
    }
    else{
        rebalance(keyNode->parent_.lock());  // rebalance if not null parent
    }      
    
}


int AVL::getBalance(std::shared_ptr<AVLNode> keyNode){
    return (height(keyNode->right_) - height(keyNode->left_));
}




void AVL::Insert(int key) {   // inserting a key
	if (root_ == nullptr) {
		root_ = std::make_shared<AVLNode>(key);    // make a smart pointer to a new AVLNode and make it the root if no nodes are present
		size_++;  // increase size
		return;
	}
    
    std::shared_ptr<AVLNode> keyNode = std::make_shared<AVLNode>(key);  // make a keynode and insert it from the root
    Insert(root_, keyNode);
    return;
}



void AVL::Insert(std::shared_ptr<AVLNode> parent, std::shared_ptr<AVLNode> keyNode){
    if (keyNode->key_ < parent->key_){
            if (!parent->left_)
            {
                parent->left_ = keyNode;
                keyNode->parent_ = parent;
                size_++;
            }
            else
            {
                Insert(parent->left_, keyNode);
            }
    }
    else if (keyNode->key_ > parent->key_){
            if (!parent->right_)
            {
                parent->right_ = keyNode;
                keyNode->parent_ = parent;
                size_++;
            }
            else
            {
                Insert(parent->right_, keyNode);
            }
        }
    else{
        return;
    }
    rebalance(keyNode);
    return;
}






std::string AVL::JSON()  {
	nlohmann::json result;
	std::queue< std::shared_ptr<AVLNode> > nodes;
	if (root_ != nullptr) {
		result["root"] = root_->key_;
		nodes.push(root_);
		while (!nodes.empty()) {
			auto v = nodes.front();
			nodes.pop();
			std::string key = std::to_string(v->key_);
            result[key]["height"] = height(v);
            result[key]["balance factor"] = getBalance(v);
			if (v->left_ != nullptr) {
				result[key]["left"] = v->left_->key_;
				nodes.push(v->left_);
			}

			if (v->right_ != nullptr) {
				result[key]["right"] = v->right_->key_;
				nodes.push(v->right_);
			}

			if (v->parent_.lock() != nullptr) {
				result[key]["parent"] = v->parent_.lock()->key_;
			} else {
				result[key]["root"] = true;
			}
		}
	}
	result["size"] = size_;
    result["height"] = height(root_);
	return result.dump(2) + "\n";
}


