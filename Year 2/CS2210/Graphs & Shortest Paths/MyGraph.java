/*  @author Ariel Johannes, Josh Bakelaar
*   Group Members :  Ariel Johannes, Josh Bakelaar  
*   Western ID: AJOHANNE, JBAKELA
*   Student Number: 251174570, 251139121
*/

import java.util.*;

/**
 * A representation of a graph. Assumes that we do not have negative cost edges
 * in the graph.
 */
public class MyGraph implements Graph {
	// you will need some private fields to represent the graph
	// you are also likely to want some private helper methods

	// YOUR CODE HERE
	private Set<Vertex> myVertexs;
	private Set<Edge> myEdges;
	private Map<Vertex, Set<Edge>> myGraph;

	/**
	 * Creates a MyGraph object with the given collection of vertices and the
	 * given collection of edges.
	 * 
	 * @param v
	 *            a collection of the vertices in this graph
	 * @param e
	 *            a collection of the edges in this graph
	 */
	public MyGraph(Collection<Vertex> v, Collection<Edge> e) {
		// YOUR CODE HERE
		if(v == null || e == null){
			throw new IllegalArgumentException();
		}

		myVertexs = new HashSet<Vertex>();
		myEdges = new HashSet<Edge>();
		myGraph = new HashMap<Vertex, Set<Edge>>();

		for(Vertex vertex: v){
			myVertexs.add(vertex);
		}
		for(Vertex vertex: v){
			myGraph.put(vertex, new HashSet<Edge>());
		}

		checkEdges(e);
	}

	/**
	 * Return the collection of vertices of this graph
	 * 
	 * @return the vertices as a collection (which is anything iterable)
	 */
	@Override
	public Collection<Vertex> vertices() {

		// YOUR CODE HERE
		return myVertexs;

	}

	/**
	 * Return the collection of edges of this graph
	 * 
	 * @return the edges as a collection (which is anything iterable)
	 */
	@Override
	public Collection<Edge> edges() {

		// YOUR CODE HERE
		return myEdges;
	}

	/**
	 * Return a collection of vertices adjacent to a given vertex v. i.e., the
	 * set of all vertices w where edges v -> w exist in the graph. Return an
	 * empty collection if there are no adjacent vertices.
	 * 
	 * @param v
	 *            one of the vertices in the graph
	 * @return an iterable collection of vertices adjacent to v in the graph
	 * @throws IllegalArgumentException
	 *             if v does not exist.
	 */
	@Override
	public Collection<Vertex> adjacentVertices(Vertex v) {

		// YOUR CODE HERE
		if(!myGraph.containsKey(v)){
			throw new IllegalArgumentException();
		}

		Set<Vertex> adjacent = new HashSet<Vertex>();

		for(Edge edge : myGraph.get(v)){
			adjacent.add(edge.getDestination());
		}

		return adjacent;
	}

	/**
	 * Test whether vertex b is adjacent to vertex a (i.e. a -> b) in a directed
	 * graph. Assumes that we do not have negative cost edges in the graph.
	 * 
	 * @param a
	 *            one vertex
	 * @param b
	 *            another vertex
	 * @return cost of edge if there is a directed edge from a to b in the
	 *         graph, return -1 otherwise.
	 * @throws IllegalArgumentException
	 *             if a or b do not exist.
	 */
	@Override
	public int edgeCost(Vertex a, Vertex b) {

		// YOUR CODE HERE
		if (!myGraph.containsKey(a) || !myGraph.containsKey(b)){
			throw new IllegalArgumentException();
		}
		int weight = -1;
		
		for(Edge edge : myGraph.get(a)){
			if(edge.getDestination().equals(b)){
				weight = edge.getWeight();
			}
		}
		return weight;
	}

	/**
	 * Returns the shortest path from a to b in the graph, or null if there is
	 * no such path. Assumes all edge weights are nonnegative. Uses Dijkstra's
	 * algorithm.
	 * 
	 * @param a
	 *            the starting vertex
	 * @param b
	 *            the destination vertex
	 * @return a Path where the vertices indicate the path from a to b in order
	 *         and contains a (first) and b (last) and the cost is the cost of
	 *         the path. Returns null if b is not reachable from a.
	 * @throws IllegalArgumentException
	 *             if a or b does not exist.
	 */
	public Path shortestPath(Vertex a, Vertex b) {

		// YOUR CODE HERE (you might comment this out this method while doing
		// Part 1)

		//make sure a and b exist, if not throw error
		if (!myGraph.containsKey(a) || !myGraph.containsKey(b)) {
			throw new IllegalArgumentException("Vertex Does Not Exist");
		}
		
		List<Vertex> vertices = new ArrayList<Vertex>();
		
		//if self edge cost = 0
		if(a.equals(b)){
			vertices.add(a);
			return new Path(vertices,0);
		}
		
		//For each node: x.myCost=infinity, x.known=false;
		for(Vertex vertex: vertices()){
			vertex.changeCost(Integer.MAX_VALUE);
			vertex.changeStatus(false);
		}

		
		PriorityQueue<Vertex> queue =new PriorityQueue<Vertex>();
		// Set the cost of start vertex to 0;
		a.changeCost(0);
		queue.add(a);

		//make queue with all vertexs
		while(!queue.isEmpty()){
			Vertex target = queue.poll();
			target.changeStatus(true);
			
			for(Vertex adjacentVertex : this.adjacentVertices(target)){
				for(Vertex vertex : vertices()){
					if(vertex.equals(adjacentVertex)){
						adjacentVertex = vertex;
						break;
					}
				}

				if(!adjacentVertex.getStatus()){
					int newCost = target.getCost()+edgeCost(target, adjacentVertex);
					int oldCost = adjacentVertex.getCost();

					if(newCost<oldCost){
						queue.remove(adjacentVertex);
						adjacentVertex.changeCost(newCost);
						adjacentVertex.changePath(target);
						queue.add(adjacentVertex);

						if(adjacentVertex.equals(b)){
							b.changeCost(adjacentVertex.getCost());
							b.changePath(adjacentVertex.getPath());
						}
					}
				}
			}
		}

		List<Vertex> result = new ArrayList<Vertex>();
		result.add(b);
		Vertex node = b;
		while(node.getPath()!=null){
			result.add(node.getPath());
			node = node.getPath();
		}

		Collections.reverse(result);
		return new Path(result, b.getCost());

	}

	private void checkEdges(Collection<Edge> edge){
		for(Edge thisEdge : edge){
			//checks for the condition of the graph
			if(!myGraph.containsKey(thisEdge.getSource()) || !myGraph.containsKey(thisEdge.getDestination())){
				throw new IllegalArgumentException("edge " + thisEdge.getSource() + " is not in the graph");
			}

			if(thisEdge.getWeight() < 0){
				throw new IllegalArgumentException("edge " + thisEdge.getSource() + "s weight is not valid");
			}

			//check thisEdge with tempEdge. if its the same with a different weight error, else store it in map
			for(Edge tempEdge : edge){
				if(thisEdge.getSource().equals(tempEdge.getSource()) && thisEdge.getDestination().equals(tempEdge.getDestination()) && thisEdge.getWeight() != tempEdge.getWeight()){
					throw new IllegalArgumentException();
				}else{
					myEdges.add(thisEdge);
					myGraph.get(thisEdge.getSource()).add(thisEdge);
				}
			}
		}
	}

}

