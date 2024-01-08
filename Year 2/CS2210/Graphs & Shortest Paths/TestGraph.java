/*  @author Ariel Johannes, Josh Bakelaar
*   Group Members :  Ariel Johannes, Josh Bakelaar  
*   Western ID: AJOHANNE, JBAKELA
*   Student Number: 251174570, 251139121
*/
import java.io.File;
import java.io.FileNotFoundException;
import java.util.ArrayList;
import java.util.Collection;
import java.util.NoSuchElementException;
import java.util.Scanner;



/*
*  Test cases:
*  Test one: checks the path from the starting vertex to itself
*       Pass = (Cost == 0)      Fail = (Cost != 0)
*  Test two: check for the path from the starting vertex to an unreachable location
*       Pass = (Cost == 0)      Fail = (Cost != 0)
*  Test three: check for the correct path from the start vertex to end vertex that is a reachable location
*       Pass = (Path != null)   Fail = (Path == null)
*  Test four: check if the end vertex will be chosen if it isn't the lowest weight but is the adjacent to initial location
*       Pass = (Path != null)   Fail = (Path == null)
*  Test five : checking if vertex doesn't exist, and how the program handles the error
*       Pass = (ExceptionCathced)   Fail = (Exception not Catched)
* */

public class TestGraph {
    public static void main(String[] args) {
        String [] files = {"vertex.txt","edge.txt"};

        MyGraph testGraph = readGraph(files[0],files[1]);

        System.out.println("\nTest 1: for the path from the starting vertex to an unreachable location");
        Vertex ATL = new Vertex("ATL");
        Vertex SEA = new Vertex("SEA");
        Path path = testGraph.shortestPath(ATL,SEA);
        if (path != null) {
            System.out.println("the shortest path includes the vertices : " + path.vertices +
            "\nThe length of this path is : "+path.cost);
        }
        if (path == null) {
            System.out.println("Test Passed");
        } else{
            System.out.println("Test Failed");
        }

        System.out.println("\nTest 2 : Checks for the path from the starting vertex to itself");
        path = testGraph.shortestPath(SEA,SEA);
        if (path != null) {
            System.out.println("the shortest path includes the vertices : " + path.vertices +
            "\nThe length of this path is : "+path.cost);
        }
        if (path.cost == 0) {
            System.out.println("Test Passed");
        } else{
            System.out.println("Test Failed");
        }

        //test three: check for the correct path from the start vertex to end vertex that is a reachable location
        System.out.println("\nTest case 3 : Checking for the correct path from the start vertex to end vertex that is a reachable location ");
        Vertex IND = new Vertex("IND");
        path = testGraph.shortestPath(IND,SEA);
        if (path != null) {
            System.out.println("the shortest path includes the vertices : " + path.vertices
            +"\nThe length of this path is : " + path.cost);

            System.out.println("Test Passed");
        } else {
            System.out.println("Test Failed");
        }
        //test case four: check if the end vertex will be chosen if it isn't the lowest weight but is the adjacent to initial location
        System.out.println("\nTest case 4 : Checking for shortest path when the end location isn't the lowest weight in adjacency ");
        Vertex IAH = new Vertex("IAH");
        path = testGraph.shortestPath(ATL,IAH);
        if (path != null) {
            System.out.println("the shortest path includes the vertices : " + path.vertices);
            System.out.println("The length of this path is : " + path.cost);
            System.out.println("Test Passed");
        } else {
            System.out.println("Test Failed");
        }

        // test Case five : checking if vertex doesn't exist, and how the program handles the error

        System.out.println("\nTest case 5 : checking if vertex doesn't exist ");
        Vertex ABC = new Vertex("ABC");
        boolean catched = false;
        try {
            path = testGraph.shortestPath(ATL,ABC); 
        } catch (IllegalArgumentException e) {
            System.out.println("Test Passed");
            catched = true;
        }
        if(!catched) {
            System.out.println("the shortest path includes the vertices : " + path.vertices);
            System.out.println("The length of this path is : " + path.cost);
            System.out.println("Test Failed");
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
