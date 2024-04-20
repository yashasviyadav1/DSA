
## creating AdjList of undirected Graph and printing it

```java
import java.util.*;
class Main{

    // creating a undirected graph from scratch
    // AdjList : T:O(e*v) S:O(2v)

    public static void main(String[] args){

        int n = 6; 
        int[][] edges = {{5,1},{1,4},{3,1},{2,1},{2,6}};

        // considering 1 based indexing
        ArrayList<ArrayList<Integer>> AdjList = new ArrayList<>();
        
        for(int i=0; i <= n; i++){// creating n+1 spaces
            AdjList.add(new ArrayList<>());
        }

        // inserting edges in nodes
        for(int i=0; i < edges.length; i++){
            int node1 = edges[i][0];
            int node2 = edges[i][1];
            AdjList.get(node1).add(node2);
            AdjList.get(node2).add(node1);
        }

        // printing the Adjacency List
        for(int i=1; i < AdjList.size(); i++){
            System.out.print(i + " -> ");
            for(int j=0; j < AdjList.get(i).size(); j++){
                System.out.print(AdjList.get(i).get(j) + " ");
            }
            System.out.println();
        }   

        
    }
}
```
