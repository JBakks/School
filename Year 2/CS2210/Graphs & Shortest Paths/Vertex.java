/**
 * Representation of a graph vertex
 */
public class Vertex implements Comparable<Vertex> {
	// label attached to this vertex
	private String label;
	private int cost;
	private boolean status;
	private Vertex path;

	/**
	 * Construct a new vertex
	 * 
	 * @param label
	 *            the label attached to this vertex
	 */
	public Vertex(String label) {
		if (label == null)
			throw new IllegalArgumentException("null");
		this.label = label;
	}

	/**
	 * Get a vertex label
	 * 
	 * @return the label attached to this vertex
	 */
	public String getLabel() {
		return label;
	}

	/**
	 * A string representation of this object
	 * 
	 * @return the label attached to this vertex
	 */
	public String toString() {
		return label;
	}

	// auto-generated: hashes on label
	public int hashCode() {
		final int prime = 31;
		int result = 1;
		result = prime * result + ((label == null) ? 0 : label.hashCode());
		return result;
	}

	// auto-generated: compares labels
	public boolean equals(Object obj) {
		if (this == obj)
			return true;
		if (obj == null)
			return false;
		if (getClass() != obj.getClass())
			return false;
		final Vertex other = (Vertex) obj;
		if (label == null) {
			return other.label == null;
		} else {
			return label.equals(other.label);
		}
	}

	//getter method to return cost
	public int getCost(){
		return cost;
	}

	//change cost of vertex
	public void changeCost(int newCost){
		cost = newCost;
	}

	//getter method to return status
	public boolean getStatus(){
		return status;
	}

	//change status of vertex
	public void changeStatus(boolean newStatus){
		status = newStatus;
	}

	//getter method for path
	public Vertex getPath(){
		return path;
	}

	//change path
	public void changePath(Vertex newPath){
		path = newPath;
	}

	//compare vertex costs, if equal return 0, if this is higher then return 1, if this is lower return -1
	public int compareTo(Vertex newVertex){
		return (int) Math.signum(this.cost - newVertex.cost);
	}

}

