# Left View of Binary Tree

### Solved at : [GFG](https://www.geeksforgeeks.org/problems/left-view-of-binary-tree/1)

## ✔️Approach - 2 (recrusive)
```java
class Tree
{
    // recursive approach 
    // maintain horiLevel, go to left first, then go to right
    void solve(Node root, Map<Integer,Integer> map, int horiLevel){
        if(root == null) return;
        if(map.containsKey(horiLevel) == false) // first occ
            map.put(horiLevel, root.data);
        
        solve(root.left, map, horiLevel + 1);
        solve(root.right, map, horiLevel + 1);
    }
    ArrayList<Integer> leftView(Node root)
    {
       ArrayList<Integer> leftViewArr = new ArrayList<>();
       // mapping the horizontal level to the 1st occ that we encounter
       Map<Integer,Integer> map = new TreeMap<>();
       solve(root, map, 0); 
       
       // fetch each ele hori level wise in inc order
       map.forEach((horiLevel, nodeData) -> leftViewArr.add(nodeData));
       return leftViewArr;
    }
}
```

## ✔️Approach - 1 (level order, iterative)
```java
// iterative method using level order 
class Tree
{
    //Function to return list containing elements of left view of binary tree.
    ArrayList<Integer> leftView(Node root)
    {
        if(root == null) return new ArrayList<>(); // exception case

        List<List<Integer>> levelOrder = new ArrayList<>();
        Queue<Node> q = new LinkedList<>();
        q.add(root);
        
        while(q.size() != 0){
            int size = q.size();
            List<Integer> currLevel = new ArrayList<>();
            for(int i=0; i < size; i++){
                Node front = q.remove();
                if(front.left != null) q.add(front.left);
                if(front.right != null) q.add(front.right);
                currLevel.add(front.data);
            }
            levelOrder.add(currLevel);
        }

        // fetch the first/leftMost element of each level
        ArrayList<Integer> leftViewArr = new ArrayList<>();
        for(List<Integer> currLevel:levelOrder){
            int firstEle = currLevel.get(0);
            leftViewArr.add(firstEle);
        } 
        
        return leftViewArr;
    }
}
```

