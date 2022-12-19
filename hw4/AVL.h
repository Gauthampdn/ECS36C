#include <memory>
#include <string>

class AVL;

class AVLNode {
 public:


 	AVLNode(int key);  // constructor when no nodes
 	AVLNode(int key, std::weak_ptr<AVLNode> parent); // constructor with node

 private:
  int key_;

  std::weak_ptr<AVLNode> parent_;
  std::shared_ptr<AVLNode> left_;
  std::shared_ptr<AVLNode> right_;

  friend AVL;
}; // class AVLNode

class AVL {
 public:
 	AVL();

 	void Insert(int key);
   void Insert(std::shared_ptr<AVLNode> parent, std::shared_ptr<AVLNode> keyNode);
 	std::string JSON() ;

    int height(std::shared_ptr<AVLNode> keyNode);
    int getBalance(std::shared_ptr<AVLNode> keyNode);
    void rebalance(std::shared_ptr<AVLNode> keyNode);

    std::shared_ptr<AVLNode> leftRotate(std::shared_ptr<AVLNode> keyNode);
    std::shared_ptr<AVLNode> rightRotate(std::shared_ptr<AVLNode> keyNode);
    std::shared_ptr<AVLNode> LRrotate(std::shared_ptr<AVLNode> keyNode);
    std::shared_ptr<AVLNode> RLrotate(std::shared_ptr<AVLNode> keyNode);

 private:
 	std::shared_ptr<AVLNode> root_;
 	size_t size_;
}; // class AVL