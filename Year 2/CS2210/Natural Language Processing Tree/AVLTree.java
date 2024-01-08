//Josh Bakelaar
//251139121
//3/31/2022
//AVLTree.java

 class AVLTree{

	private AVLNode root; public AVLTree Right; public AVLTree Left;
	
     //constructor AVLTree

    public AVLTree() {
            root = null;
    }
     
    AVLTree(int i) {
        root = null;
    }

    /* Function to check if tree is empty */
	public boolean isEmpty() {
        return root == null;
    }

     /* Make the tree logically empty */
    public void makeEmpty() {
        root = null;
    }

    /* Function to insert data */
     public void Insert(int data) {
        root = insert(data, root);
    }

     /* Function to get height of node */
    private int getheight(AVLNode t ) {
        return t == null ? -1 : t.height;
    }

     /* Function to max of left/right node */
    private int max(int lhs, int rhs) {
        return lhs > rhs ? lhs : rhs;
    }

     /* Function to insert data recursively */
    private AVLNode insert(int x, AVLNode t){

        if (t == null)

            t = new AVLNode(x);

        else if (x < t.data)

        {

            t.left = insert( x, t.left );

            if( getheight( t.left ) - getheight( t.right ) == 2 )

                if( x < t.left.data )

                    t = rotateWithLeftChild( t );

                else

                    t = doubleWithLeftChild( t );

        }

        else if( x > t.data )

        {

            t.right = insert( x, t.right );

            if( getheight( t.right ) - getheight( t.left ) == 2 )

                if( x > t.right.data)

                    t = rotateWithRightChild( t );

                else

                    t = doubleWithRightChild( t );

        }

        else

           ;  // Duplicate; do nothing

        t.height = max( getheight( t.left ), getheight( t.right ) ) + 1;

        return t;


     }

     /* Rotate binary tree node with left child */   
    private AVLNode rotateWithLeftChild(AVLNode k2)

    {

        AVLNode k1 = k2.left;

        k2.left = k1.right;

        k1.right = k2;

        k2.height = max( getheight( k2.left ), getheight( k2.right ) ) + 1;

        k1.height = max( getheight( k1.left ), k2.height ) + 1;

        return k1;

     }

 

     /* Rotate binary tree node with right child */
     private AVLNode rotateWithRightChild(AVLNode k1)

     {

         AVLNode k2 = k1.right;

         k1.right = k2.left;

         k2.left = k1;

         k1.height = max( getheight( k1.left ), getheight( k1.right ) ) + 1;

         k2.height = max( getheight( k2.right ), k1.height ) + 1;

         return k2;

     }

     /**
      * 
      * Double rotate binary tree node: first left child

      * with its right child; then node k3 with new left child */
    private AVLNode doubleWithLeftChild(AVLNode k3)

    {

        k3.left = rotateWithRightChild( k3.left );

        return rotateWithLeftChild( k3 );

    }

     /**

      * Double rotate binary tree node: first right child

      * with its left child; then node k1 with new right child */      
    private AVLNode doubleWithRightChild(AVLNode k1)

    {

        k1.right = rotateWithLeftChild( k1.right );

        return rotateWithRightChild( k1 );

    }    

     /* Functions to count number of nodes */
    public int CountNumberNodes()
    {return countNodes(root);
    }
     
     //private
     private int countNodes(AVLNode r)

     {

         if (r == null)

             return 0;

         else

         {

             int l = 1;

             l += countNodes(r.left);

             l += countNodes(r.right);

             return l;

         }

     }

     /* Functions to search for an element */
     public boolean Search(int val) {
        return search(root, val);
    }
     
     private boolean search(AVLNode r, int val)

     {

         boolean found = false;

         while ((r != null) && !found)

         {

             int rval = r.data;

             if (val < rval)

                 r = r.left;

             else if (val > rval)

                 r = r.right;

             else

             {

                 found = true;

                 break;

             }

             found = search(r, val);

         }

         return found;

     }

     /* Function for inorder traversal */
     
     public void inorderTrav() {
        inorder(root);
    }
     
     private void inorder(AVLNode r)

     {

         if (r != null)

         {

             inorder(r.left);
             
             System.out.print(r.data +" ");
            
             inorder(r.right);
       
         }

     }

     /* Function for preorder traversal */
    
    public void preorderTrav() {
        preorder(root);
    }
    
    private void preorder(AVLNode r)

    {

        if (r != null)

        {

            System.out.print(r.data +" ");

            preorder(r.left);      

            preorder(r.right);

         }

     }

     /* Function for postorder traversal */
    public void postorderTrav(){
        postorder(root);
    }
     
  	 
    private void postorder(AVLNode r)

    {

        if (r != null)

        {

            postorder(r.left);             

            postorder(r.right);

            System.out.print(r.data +" ");

        }

     }

    /* extra methods and functions */
     
    //gets the balance of the tree
    private int returnbalance(AVLNode node) {
        if (node != null)
            return getheight(node.left) - getheight(node.right);
        else {
        return 0;
        }
    }

    //balances the AVL tree
    private AVLNode balance_it(AVLNode node) {

        //variable to hold number oh node
        int val;
        val = returnbalance(node);

        if (val >= 2 && node.left.data > root.data) {
            return rotateWithRightChild(node);
        }
        
        if (val >= 2 && node.left.data < root.data) {
                node.left = rotateWithLeftChild(node.left);
                return rotateWithRightChild(node);
        }
        if (val <= -2 && node.right.data > root.data) {
            node.right = rotateWithRightChild(node.right);
            return rotateWithLeftChild(node);
        }
        if (val <= -2 && node.right.data < root.data) {
            return rotateWithLeftChild(node);
        }

        return node;
    }

    //printing the external node
    public void external() {

        AVLNode node;
        node = root;
            
        if(node == null) 
            return; 

        if(node.right == null && node.left == null) {System.out.print(node.data + " ");}
    }

    //checks if tree is balanced, balance it if its not
    public boolean is_Balanced(AVLTree tree) {

        if(tree != null) {
            balance_it(tree.root);
            return true;
        }else {  
            return false;
        }

    }

    //changes the value to new value
    public void newvalue() {

        if (root == null) {
            System.out.println("tree is null");
            return;
        }else {
            
            AVLTree tree;
            tree = new AVLTree();

            while (tree.isEmpty() == false) {
                    
                //stores # of nodes at the level
                int length;
                length = tree.CountNumberNodes();

                //while length > 0, do
                while (length >= 1) { 
                    //front node = i
                    AVLNode i;
                    i = root;
                    //output node we are  at
                    System.out.print(
                        i.data + " ");
                    //while node left is not null
                    if (i.right != null)
                        tree.insert(i.data, i.right);
                    if (i.left != null)
                        //insert node
                        tree.insert(i.data, i.left);
                    //Decrement length
                    length--;
                }

                System.out.println();
            }
        }

    }
        
    public boolean BST(AVLTree avl) {
        if (avl.root == null) {
            return true;
        } 
        // false if: left is > than node or right is < than node
        if ((root.left.data > avl.root.data && avl.root.left != null) || (root.right.data < avl.root.data && avl.root.right != null)) {
            return false;
        }
        
        return true;
    }

}


