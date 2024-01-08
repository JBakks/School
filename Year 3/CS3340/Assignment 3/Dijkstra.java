//Josh Bakelaar
//251139121
import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collections;
import java.util.Comparator;
import java.util.LinkedList;
import java.util.List;
import java.util.PriorityQueue;

public class Dijkstra {

    // Edge class
    static class Edge {
        // Source vertex of edge
        int src;
        // Destination vertex of edge
        int destination;
        // Weight of edge
        int weight;

        // Constructor
        public Edge(int src, int destination, int weight) {
            this.src = src;
            this.destination = destination;
            this.weight = weight;
        }
        
        // Method for printing the edge
        public void PrintEdge() {
            System.out.print(src + "->");
            System.out.print("destination is: " + destination);
            System.out.print(" with a weight: " + weight);
        }
    }

    // Class called graph
    static class Graph {
        // COnstant for infinity
        int INF = Integer.MAX_VALUE;
        // Number of vertices in a graph
        int numVertices;
        // Adjacency list for the graph
        LinkedList<Edge>[] adjacencyList;
        // Array which stores parents of vertexs
        int[] parent;
        // Array to store distances from the source vertex
        int[] distances;

        // Constructor
        public Graph(int numVertices) {
            this.numVertices = numVertices;
	    this.adjacencyList = new LinkedList[numVertices];
            parent = new int[numVertices];
            distances = new int[numVertices];
            // Initially set the parent of each vertex to -1
            Arrays.fill(parent, -1);
            // Initially set the distance of each vertex to infinity
            Arrays.fill(distances, INF);
            for (int i = 0; i < numVertices; i++) {
                // Create linked list for each vertex
                adjacencyList[i] = new LinkedList<>();
            }
        }

        // Method to add an edge
        public void addEdge(int src, int destination, int weight) {
            if (adjacencyList[src] == null) {
                // If there is no linked list create one
                adjacencyList[src] = new LinkedList<>();
            }
            Edge edge = new Edge(src, destination, weight);
            // Add the edge to the linked list of the source vertex
            adjacencyList[src].addFirst(edge);
        }

        // Method for printing the graph
        public void printGraph() {
            for (int i = 0; i < numVertices; i++) {
                System.out.println("\nVertex " + i + ":");
                System.out.println("edges: " + adjacencyList[i].size());
                for (int j = 0; j < adjacencyList[i].size(); j++) {
                    adjacencyList[i].get(j).PrintEdge();
                    System.out.println();
                }
                System.out.println();
            }
        }

        // Method to perform Dijkstra's algorithm
        public void dijkstra(int source) {
            // Queue to store the vertices with minimum distance
            PriorityQueue<Edge> pq = new PriorityQueue<>(Comparator.comparingInt(e -> e.weight));
            // add the source vertex with distance 0 to the queue
            pq.add(new Edge(source, source, 0));
            // Set distance to 0
            distances[source] = 0;
            
            while (!pq.isEmpty()) {
                // Remove the vertex with minimum distance
                Edge edge = pq.poll();
                // Get destination vertex
                int u = edge.destination;
                // Continuously add vertices with the smallest distance to the priority queue
                if (edge.weight > distances[u]) {
                    continue;
                }
                // For each vertex u, update distances to its neighbors v with an edge weight w
                for (Edge neighbor : adjacencyList[u]) {
                    int v = neighbor.destination;
                    int alt = distances[u] + neighbor.weight;
                    // If the new distance to v is smaller than its current distance, update distance and add v to the priority queue
                    if (alt < distances[v]) {
                        distances[v] = alt;
                        parent[v] = u;
                        pq.add(new Edge(u, v, alt));
                    }
                }
            }

            // Once all vertices have been processed, print the shortest paths to all reachable vertices from the source vertex        
            for (int v = 0; v < numVertices; v++) {
                if (v != source && parent[v] != -1) {
                    System.out.println("(" + parent[v] + ", " + v + ") : " + distances[v]);
                }
            }
        }
    }
    public static void main(String[] args) throws IOException {
        BufferedReader reader;
        //reads the file
        reader = new BufferedReader(new FileReader("sssp_graph_medium.txt"));
        //spilt line
        String line = reader.readLine();
        //get the total vertex
        int numV = Integer.parseInt(line);
        //create the graph
        Graph graph = new Graph(numV+1);
        String[] numbers;
        while((line=reader.readLine())!=null) {
            //this line ignores all the heading or ending whitespaces and spilt whitespaces with single or multiple occurrences
            numbers = line.replaceAll("(^\\s+|\\s+$)", "").split(" +");
            //add edges into the graph
            graph.addEdge(Integer.parseInt(numbers[0]), Integer.parseInt(numbers[1]), Integer.parseInt(numbers[2]));
        }
        //driver code
        graph.printGraph();
        graph.dijkstra(1);
    }
}
    
