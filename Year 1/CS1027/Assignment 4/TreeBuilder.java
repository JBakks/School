//Josh Bakelaar (251139121)
//July 23rd, 2021
//TreeBuilder.java
//This class is used to create the binary trees for the program. 
//They must be created using a queue-based approach, very similar to the level-order traversal that uses queues, but here the tree is being built rather than traversed.

public class TreeBuilder<T> {
	
	//Variable
	LinkedBinaryTree<T> tree;
	
	//Constructor
	public TreeBuilder(T[] array) {
		LinkedQueue dataQueue = new LinkedQueue();
		
		//Initialize dataQueue with all elements (from T[ ] parameter) to be added in the nodes in order
		for(int i = 0; i<array.length; i++) {
			dataQueue.enqueue(array[i]);
		}
		
		//Initialize parentQueue as empty queue
		LinkedQueue parentQueue = new LinkedQueue();
		
		//Create the tree's root node with the first element of the data queue
		BinaryTreeNode root = new BinaryTreeNode(dataQueue.dequeue());
		
		//Enqueue the root node on parentQueue
		parentQueue.enqueue(root);
		
		//While dataQueue has elementS
		while(!dataQueue.isEmpty()) {
			BinaryTreeNode a = null;
			BinaryTreeNode b = null;
			
			//If the queue is empty it will not allow
			try {
				//a = dequeue from dataQueue
				a = new BinaryTreeNode(dataQueue.dequeue());
				
				//b = dequeue from dataQueue
				b = new BinaryTreeNode(dataQueue.dequeue());
				
			}catch(Exception EmptyCollectionException ) {
			}
			
			//parent = dequeue from parentQueue
			BinaryTreeNode parent = (BinaryTreeNode) parentQueue.dequeue();
			
			//If a is not null, add node with a as left child of parent and enqueue on parentQueue
			if(a.getData() != null) {
				parent.setLeft(a);
				parentQueue.enqueue(a);
			}
			
			//If b is not null, add node with b as right child of parent and enqueue on parentQueue
			if(b.getData() != null) {
				parent.setRight(b);
				parentQueue.enqueue(b);
			}
		}
		
		//Initialize the LinkedBinaryTree instance variable with the root node
		tree = new LinkedBinaryTree(root);
	}
	
	//Returns the tree
	public LinkedBinaryTree<T> getTree(){
		return tree;
	}
}
