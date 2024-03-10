# Top View of Binary Tree

#### Solved at : [GFG](https://www.geeksforgeeks.org/problems/top-view-of-binary-tree/1)

#### Concept : Why we use LevelOrder but Recursion fails here ??
![Flow - Frame 7](https://github.com/yashasviyadav1/dsa-questions/assets/124666305/e9a21879-3e23-4f0b-a402-d0f124d05d5f)

## ✔️Approach - 1 (levelOrderTraversal + verticalLevel logic)
```java

// Approach-1  (levelOrderTraversal + verticalLevel logic)
// T:O(n) S:O(n) 
// using verticalLevels we store the 1st element that we encounter at that level only 
// at the end we print the 1st elements of those levels in sorted order of vertical level
class Pair{
    Node node;
    int verticalLevel;
    Pair(Node node, int verticalLevel){
        this.node = node;
        this.verticalLevel = verticalLevel;
    }
    Node getKey(){
        return node;
    }
    int getValue(){
        return verticalLevel;
    }
}
class Solution
{
    
    static ArrayList<Integer> topView(Node root)
    {
        // map (verticallevel, 1st element that we encounter at that level)
        Map<Integer,Integer> hm = new TreeMap<>(); 
        
        // level order traversal
        // q(pair(node,itsVerticalLevel))
        Queue<Pair> q = new LinkedList<>();
        q.add(new Pair(root, 0));
        
        while(q.size() != 0){
            
            int size = q.size();
            
            for(int i=0; i < size; i++){
                
                Pair pair = q.remove();
                Node front = pair.getKey();
                int verticalLevel = pair.getValue();
                
                if(front.left != null) q.add(new Pair(front.left, verticalLevel - 1));
                if(front.right != null) q.add(new Pair(front.right, verticalLevel + 1));
                
                if(hm.containsKey(verticalLevel) == false) // this vertical levels first node has not yet found so store it
                    hm.put(verticalLevel, front.data);
            }
        }
        
        ArrayList<Integer> ans = new ArrayList<>();
        hm.forEach((vertLevel, firstElement) -> ans.add(firstElement));
        
        return ans;
    }
}
```
