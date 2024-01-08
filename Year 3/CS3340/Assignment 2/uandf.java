// Josh Bakelaar
// 251139121
// A Disjoint-Set data struture, which uses union by rnak and path compression

import java.util.Set;

public class uandf{
    int[] rank;
    int[] parent;
    int n;

    // Constructor
    public uandf(int n){
        rank = new int[n + 1];
        parent = new int[n + 1];
        this.n = n;

        // Initialize the parent and rank arrays with values 1 - n, set rank of each element to 0
        for (int i = 1; i < n; i++){
            parent[i] = i;
            rank[i] = 0;
        }
    }

    // Creates a new set with element i
    void make_set(int i){
        // Set parent to i
        parent[i] = i;
        // Set rank to 0
        rank[i] = 0;
    }

    // Find the root of a set that contains i
    int find_set(int i){
        // if parent of i is not equal to i, recursively call find_set
        if (parent[i] != i){
            parent[i] = find_set(parent[i]);
        }
        // return root
        return parent[i];
    }

    // Combine sets which contain i and j
    void union_sets(int i, int j){
        int iRoot = find_set(i);
        int jRoot = find_set(j);

        // If i and j are the same nothing to do
        if(iRoot == jRoot){
            return;
        }
        // move i under j so that depth remains less
        if(rank[iRoot] < rank[jRoot]){
            parent[iRoot] = parent[jRoot];
        // move j under i so that depth remains less
        } else if(rank[iRoot] > rank[jRoot]){
            parent[jRoot] = parent[iRoot];
        // then they are the same, move j under i
        } else{
            parent[jRoot] = iRoot;
            //increment rank by 1
            rank[iRoot]++;
        }
    }

    // Returns an array of n+1 that contains the representatives of the final sets
    int[] final_sets(){
        int[] sets = new int[n];
        int nextSet = 1;

        // Iterate through parent array to find the representatives
        for (int i = 1; i < parent.length ; i++){
            // If parent of i is i, then i is a representative
            if(parent[i] == i){
                sets[nextSet] = i;
                nextSet++;
            }
        }
        // Iterate through the sets array and update the parent of each element
        for(int i = 1; i < n; i++){
            int oldRoot = sets[i];
            int newRoot = i;

            //  Update parent of each element
            while (oldRoot != newRoot){
                int temp = parent[oldRoot];
                parent[oldRoot] = newRoot;
                oldRoot = temp;
            }
        }
        // Return
        return sets;
    }
}