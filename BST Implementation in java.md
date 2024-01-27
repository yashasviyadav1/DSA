# Binary Search Tree Implementation in java

```java
import java.util.*;

// Binary Search Tree Implementation - JAVA

class TreeNode{
    int val;
    TreeNode left;
    TreeNode right;
    TreeNode(){
        this.left = null;
        this.right = null;
    }
    TreeNode(int val){
        this.val = val;
    }
}

class BinaryTreeImplement{


    private static TreeNode buildBST(int arr[], int low, int high){
        if(low > high) return null;// base 

        int mid = low + (high-low)/2;
        TreeNode root = new TreeNode(arr[mid]); // create root

        root.left = buildBST(arr, low, mid - 1); // build its subtrees
        root.right = buildBST(arr, mid + 1, high);
        return root; // binary tree is ready
    }

    public static void levelOrderTraversal(TreeNode root){

        ArrayList<ArrayList<Integer>> levelOrderArr = new ArrayList<>();

        Queue<TreeNode> q = new LinkedList<>();
        q.add(root);
        while(q.size() != 0){

            int size = q.size();
            ArrayList<Integer> currLevel = new ArrayList<>();
            for(int i=0; i < size; i++){
                TreeNode front = q.remove();
                if(front.left != null) q.add(front.left);
                if(front.right != null) q.add(front.right);
                currLevel.add(front.val);
            }

            levelOrderArr.add(currLevel);
        }
        // System.out.print(levelOrderArr);
        for(int i=0; i < levelOrderArr.size(); i++){
            for(int j=0; j < levelOrderArr.get(i).size(); j++){
                System.out.print(levelOrderArr.get(i).get(j) + " ");
            }
            System.out.println();
        }
    }

    public static void main(String[] args) {
        
        // build binary search tree from array
        int arr[] = {5,7,8,9,1,2,3};

        int low = 0;
        int high = arr.length-1;
        Arrays.sort(arr); // for bst we need sorted array
        TreeNode root = buildBST(arr, low, high);

        // print this binary tree level wise
        levelOrderTraversal(root);

      /* Output :   5 
                   2 8 
                 1 3 7 9
      */
    }
}
```
