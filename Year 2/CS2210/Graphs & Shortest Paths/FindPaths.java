/*  @author Ariel Johannes, Josh Bakelaar
*   Group Members :  Ariel Johannes, Josh Bakelaar  
*   Western ID: AJOHANNE, JBAKELA
*   Student Number: 251174570, 251139121
*/

import java.util.*;
import java.io.*;

/**
 * Driver program that reads in a graph and prompts user for shortests paths in the graph.
 * (Intentionally without comments.  Read through the code to understand what it does.)
 */

public class FindPaths {
	public static void main(String[] args) {
		if(args.length != 2) {
			System.err.println("USAGE: java FindPaths <vertex_file> <edge_file>");
			System.exit(1);
		}
		MyGraph g = readGraph(args[0],args[1]);

		@SuppressWarnings("resource")
		Scanner console = new Scanner(System.in);
		Collection<Vertex> v = g.vertices();
                Collection<Edge> e = g.edges();
		System.out.println("Vertices are "+v);
		System.out.println("Edges are "+e);
		while(true) {
			System.out.print("Start vertex? ");
			Vertex a = new Vertex(console.nextLine());
			if(!v.contains(a)) {
				System.out.println("no such vertex");
				System.exit(0);
			}
			
			System.out.print("Destination vertex? ");
			Vertex b = new Vertex(console.nextLine());
			if(!v.contains(b)) {
				System.out.println("no such vertex");
				System.exit(1);
			}
			
			// YOUR CODE HERE: call shortestPath and print
			// out the result

			System.out.println("Shortest path from " + a + " to " + b);
			Path path = g.shortestPath(a, b);

			//if the path doesnt exist
			if(path == null){
				System.out.println("No such path.");
			} else{
				List<Vertex> vList = path.vertices;
				
				StringBuilder string = new StringBuilder();
				string.append(vList.get(0).getLabel());
				for(int i = 1; i < vList.size(); i++){
					string.append(" > " + vList.get(i).getLabel());
				}
				System.out.println(string.toString());
				System.out.println("cost of the path is: " + path.cost + "\n");
			}
		}
	}

    public static MyGraph readGraph(String f1, String f2) {
        Scanner s = null;
        try {
            s = new Scanner(new File(f1));
        } catch(FileNotFoundException e1) {
            System.err.println("file "+f1+" does not exist ");
            System.exit(1);
        }

        Collection<Vertex> v = new ArrayList<Vertex>();
        while(s.hasNext()) v.add(new Vertex(s.next()));

        try {
            s = new Scanner(new File(f2));
        } catch(FileNotFoundException e1) {
            System.err.println("file "+f2+" does not exist ");
            System.exit(1);
        }

        Collection<Edge> e = new ArrayList<Edge>();
        while(s.hasNext()) {
            try {
                Vertex a = new Vertex(s.next());
                Vertex b = new Vertex(s.next());
                int w = s.nextInt();
                e.add(new Edge(a,b,w));
            } catch (NoSuchElementException e2) {
                System.err.println("incorrect edge");
                System.exit(2);
            }
        }

        return new MyGraph(v,e);
    }
}

