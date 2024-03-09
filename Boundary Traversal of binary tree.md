# Boundary Traversal of binary tree

#### Solved at : [GFG](https://www.geeksforgeeks.org/problems/boundary-traversal-of-binary-tree/1) 
![image](https://github.com/yashasviyadav1/dsa-questions/assets/124666305/c6d3e964-dd8a-45f9-8150-d209b4671a98)
![image](https://github.com/yashasviyadav1/dsa-questions/assets/124666305/314973cb-697b-48f8-a9f3-f60ea2dbbbcd)

## ✔️Approach - 1 (Recursive)
```java
class Solution
{
    private void leftBoundary(Node root, ArrayList<Integer> bound){
        if(root == null) return;
        if(root.left == null && root.right == null) return; // do not include leafs
        
        bound.add(root.data);
        if(root.left != null) leftBoundary(root.left, bound);
        else leftBoundary(root.right, bound);
    }
    
    private void inorder(Node root, ArrayList<Integer> bound){
        if(root == null) return;
        // LNR
        inorder(root.left, bound);
        if(root.left == null && root.right == null){ // leaf node 
            bound.add(root.data);
            return;
        }
        inorder(root.right, bound);
    }
    
    private void rightBoundary(Node root, ArrayList<Integer> bound){
        if(root == null) return;
        if(root.left == null && root.right == null) return;
        
        if(root.right != null) rightBoundary(root.right, bound);
        else rightBoundary(root.left, bound);
        bound.add(root.data);
    } 
    
	ArrayList <Integer> boundary(Node root)
	{
	    ArrayList<Integer> bound = new ArrayList<>();
	    bound.add(root.data); // including root initially, to avoid confusions
	    
	    // from root to bottom (find left boundary (except for leafs))
	    // add curr node to bound, go to left is there exists, else go to right (if left doesn't exists)
	    leftBoundary(root.left, bound);
	    
	    // add all leaf nodes (from left to right) so LNR
	    inorder(root.left, bound);
	    inorder(root.right, bound);
	    
	    // from bottom to up (find right boundary() except for leafs) 
	    // go to right node if exists, else go to left node, while comming back (add node to bound)
	    rightBoundary(root.right, bound);
	    
	    return bound;
	}
}
```
