#include <iostream>
#include<string>
#include "json.hpp"
#include "priorityqueue.h"

PriorityQueue::PriorityQueue(std::size_t max_size) :
	nodes_(1, KeyValuePair()),  // changed from maxsize + 1 to 1 since it would be easy to pushback nodes than to modify existing nodes 
	max_size_(max_size),
	size_(0) {
}

void PriorityQueue::insert(Key k) {
	insert(std::make_pair(k, std::make_pair(0, 0)));  
}

void PriorityQueue::insert(KeyValuePair kv) {
	unsigned int i = size();   // storing size
    if( i < max_size_){   // if the size is not greater than the max push back the key value pair
        nodes_.push_back(kv); 
        size_++;  // increment size
        heapifyUp(size_); // hepify up since it is the last node
    }    
    return;

}

KeyValuePair PriorityQueue::min() {
	return nodes_[ROOT];
}

KeyValuePair PriorityQueue::removeMin() {
	KeyValuePair Min = min(); 
    removeNode(ROOT);  // remove the first node after retrieving its value
    return Min;
}

bool PriorityQueue::isEmpty() const {
	if(size_ == 0){return true;}
    return false;
}

size_t PriorityQueue::size() const {
	return size_;
}

nlohmann::json PriorityQueue::JSON() const {
	nlohmann::json result;
  for (size_t i = 1; i <= size_; i++) {
      nlohmann::json node;
      KeyValuePair kv = nodes_[i];
      node["key"] = kv.first;
      node["value"] = kv.second;
      if (i != ROOT) {
          node["parent"] = std::to_string(i / 2);
      }
      if (2 * i <= size_) {
          node["leftChild"] = std::to_string(2 * i);
      }
      if (2 * i + 1 <= size_) {
          node["rightChild"] = std::to_string(2 * i + 1);
      }
      result[std::to_string(i)] = node;
  }
  result["metadata"]["max_size"] = max_size_;
  result["metadata"]["size"] = size_;
	return result;
}

void PriorityQueue::heapifyUp(size_t i) {  
	if(nodes_[i].first < nodes_[i/2].first){    // if the node is less than its parent swap them
        swap(nodes_[i],nodes_[i/2]);  
        heapifyUp(i/2);
    }
    
}

void PriorityQueue::heapifyDown(size_t i) {

    if(2*i > size_){
        return;
    }

    else if(2*i == size_){
        if(nodes_[i].first > nodes_[2*i].first){
            swap(nodes_[i],nodes_[2*i]);
        }
        else{ return; }
    }
    else {

    size_t parent = i;
    size_t leftNode = 2*i;
    size_t rightNode = 2*i+1;
    size_t smallest = parent;
    
    if(nodes_[leftNode] < nodes_[smallest]){
        smallest = leftNode;    
    }
    if(nodes_[rightNode] < nodes_[smallest]){
        smallest = rightNode;
    } 
    if(smallest != parent){
        swap(nodes_[smallest],nodes_[parent]);
        heapifyDown(smallest);
    }
    return;
}
}



void PriorityQueue::removeNode(size_t i) {
	nodes_[i] = nodes_[size_];      // copy in the last value
    nodes_.pop_back();              //  pop the last value
    if(i == 1){             // decide to heapify up or down the node
        heapifyDown(i);
    }
    else if(nodes_[i].first < nodes_[i/2].first){
        heapifyUp(i);
    }
    else{
        heapifyDown(i);
    }
    size_--;
}

Key PriorityQueue::getKey(size_t i) {
	Key Keyreturn = nodes_[i].first;   // get the first value in the key value pair
    return Keyreturn;
}
