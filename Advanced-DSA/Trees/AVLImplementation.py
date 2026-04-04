from collections import deque

### Implementing AVL Tree in python

### how to identify weather LL LR RR RL case in rotation ? Explained:  https://i.ibb.co/jk11Fb4G/image.png

class Node:
    def __init__(self, data):
        self.data = data
        self.left = None
        self.right = None
        self.height = 0

class AVLTree:
    def __init__(self):
        self.root = None

    def height(self, node):
        if node == None:
            return -1 # given leaf node has height 0, so None has height -1
        return node.height

    def balanceFactor(self, node):
        if node == None: return 0
        return self.height(node.left) - self.height(node.right)
    

    """ left rotation
        node
           \
            x
           / \
        t1    t2    
    
        to 

             x
           /  \
        node   t2
           \       
            t1
    """
    def leftRotate(self, node):
        x = node.right
        t1 = x.left
        # assign
        x.left = node
        node.right = t1
        # update new heights - note: only changed hight nodes are node : node, x  (Update bottom up, first node then x otherwise incorrect output will be there because upper node depend on. lower nodes height)
        node.height = max(self.height(node.left), self.height(node.right)) + 1
        x.height = max(self.height(x.left), self.height(x.right)) + 1
        # now x is the new root
        return x

    
    """ right rotation
              node
             /
            x
           / \
        t1    t2    
    
        to 

             x
            /  \
         t1     node
                /
               t2 
    """
    
    def rightRotate(self, node):
        x = node.left
        t2 = x.right
        # assign
        x.right = node
        node.left = t2
        # update new heights - note: only changed hight nodes are node : node, x  (Update bottom up, first node then x otherwise incorrect output will be there because upper node depend on. lower nodes height)
        node.height = max(self.height(node.left), self.height(node.right)) + 1
        x.height = max(self.height(x.left), self.height(x.right)) + 1
        # now x is the new root
        return x

    def insertionHelper(self, root, data):
        if root is None:
            return Node(data)
        if root.data == data: # already present a node with this data
            return root
        if root.data < data: # go right
            root.right = self.insertionHelper(root.right, data)
        else: # go left
            root.left = self.insertionHelper(root.left, data)
        
        # after insertion, update the height of the node, and balance if necessary
        root.height = 1 + max(self.height(root.left), self.height(root.right));
        # check if after insertion node has been unbalanced
        rootBalanceFactor = self.balanceFactor(root)
        # unbalanced
        if rootBalanceFactor < -1 or rootBalanceFactor > 1:
            # left heavy 
            if rootBalanceFactor > 1:
                # LL -> right rotate root
                if self.balanceFactor(root.left) >= 0: # covers case: when left subtree bf is 0, 1
                    root = self.rightRotate(root)
                # LR -> left rotate leftsubtree, right rotate root
                else:
                    root.left = self.leftRotate(root.left)
                    root = self.rightRotate(root)
            # right heavy 
            else:
                # RR -> left rotate root
                if self.balanceFactor(root.right) <= 0:  # covers case: when left subtree bf is 0, -1,
                    root = self.leftRotate(root)
                # RL -> right rotate rigth subtree, left rotate root
                else:
                    root.right = self.rightRotate(root.right)
                    root = self.leftRotate(root)

        # reached here means 'Root' is/has been balanced now
        return root

    def inorderSuccessor(self, node):
        temp = node.right
        while (temp is not None) and (temp.left is not None):
            temp = temp.left
        return temp


    def insert(self, data):
        # insertion is same like BST plus some rotational checks every after every insertion
        self.root = self.insertionHelper(self.root, data)
        return True

    def deletionHelper(self, root, targetData):
        if root is None:
            print(f"Node to be deleted {targetData}, Not found")
            return None
        
        if root.data < targetData: # go right
            root.right = self.deletionHelper(root.right, targetData)
        elif root.data > targetData: # go left
            root.left = self.deletionHelper(root.left, targetData)
        else: # reached target node
            # case 1: 
            if root.left is None: # to delete curr node, its right part is transfered above
                root = root.right
            elif root.right is None:
                root = root.left
            else: # its a middle node
                inorderSuccessorNode = self.inorderSuccessor(root)
                root.data = inorderSuccessorNode.data
                # delete the original entry of inorder successor
                root.right = self.deletionHelper(root.right, inorderSuccessorNode.data)

        # reached here means teh target node is deleted, so check if curr node is unbalanced due to the deletion
        # edcase: if is the one deleted
        if root is None:
            return None
        # after deletion, update the height of the node, and balance if necessary
        root.height = 1 + max(self.height(root.left), self.height(root.right));

        rootBalanceFactor = self.balanceFactor(root)
        # unbalanced
        if rootBalanceFactor < -1 or rootBalanceFactor > 1:
            # left heavy 
            if rootBalanceFactor > 1: # means bf is 2
                # LL -> right rotate root 
                if self.balanceFactor(root.left) >= 0:  # covers case: when left subtree bf is 0, 1
                    root = self.rightRotate(root)
                # LR -> left rotate leftsubtree, right rotate root
                else:
                    root.left = self.leftRotate(root.left)
                    root = self.rightRotate(root)
            # right heavy 
            else:
                # RR -> left rotate root
                if self.balanceFactor(root.right) <= 0: # covers case: when left subtree bf is 0, -1
                    root = self.leftRotate(root)
                # RL -> right rotate rigth subtree, left rotate root
                else:
                    root.right = self.rightRotate(root.right)
                    root = self.leftRotate(root)

        # reached here means 'Root' is/has been balanced now
        return root


    def delete(self, data):
        self.root = self.deletionHelper(self.root, data)

    def display(self):
        if self.root is None:
            print("Can't display empty AVL tree")
            return
        q = deque()
        q.append(self.root)
        while len(q):
            size = len(q)
            for i in range(size):
                front = q.popleft()
                print(front.data, end=" ")
                if front.left is not None:
                    q.append(front.left)
                if front.right is not None:
                    q.append(front.right)
            print()




avl = AVLTree()
li = [30, 20, 10, 25, 28]
for ele in li:
    avl.insert(ele)

print("Original Tree:")
avl.display()

print("Deleted Node 20")
avl.delete(20)

print("Now Tree:")
avl.display()




""" OUTPUT:- 

Original Tree:
        20
    10      28
        25      30
Deleted Node 20
Now Tree:
        25
    10      28
        30



"""