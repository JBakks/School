//Josh Bakelaar (251139121)
//July 23rd, 2021
//Playoffs.java
//This class represents the NHL Playoffs and contains several methods for updating the playoff tree and the standings table.

import java.util.Iterator;

public class Playoffs {
	
	//Variables
	private LinkedBinaryTree<String> tree;
	private HockeySeries[] standings;
	
	//Constructor
	public Playoffs() {
		
		//Create a string array with 31 slots
		String[] array = new String[31];
		
		//Since the top several layers of the tree are unknown, were going to use "TBD #" for the first 15
		for(int i = 0; i<15; i++) {
			array[i] = "TBD " + i;
		}
		
		//Create a FileReader for the teams.txt file
		MyFileReader teams = new MyFileReader("teams.txt");
		
		//Go through the lines and add each team to the rest of the array
		for(int i = 15; i<31; i++) {
			array[i] = teams.readString();
		}
		
		//Reset the FileReader
		teams = new MyFileReader("teams.txt");
		
		//Initialize the standings table with 15 slots (8 round 1, 4 round 2, 2 round 3, 1 round 4)
		standings = new HockeySeries[15];
		
		//Put each team in the correct series
		for(int i = 0; i<=8; i++) {		
			standings[i] = new HockeySeries(teams.readString(), teams.readString(), 0, 0);
		}
		
		//Build a new tree for the playoffs
		TreeBuilder playoffs = new TreeBuilder(array);
		
		//Tree = playoffs tree
		tree = playoffs.getTree();
	}
	
	//Return the tree
	public LinkedBinaryTree<String> getTree(){
		return tree;
	}
	
	//Return the standings
	public HockeySeries[] getStandings() {
		return standings;
	}
	
	//Take in 2 strings representing team names and 2 ints representing the number of wins to update the standings for these teams
	public String updateStandings(String teamOne, String teamTwo, int teamOneWins, int teamTwoWins) {
		//Look through each standing slot
		for(int i = 0; i<standings.length; i++) {
			//If it = null, skip
			if(standings[i] == null) {
				continue;
			}
			
			//If it = null, skip
			if(standings[i] == null || standings[i].getTeamA() == null || standings[i].getTeamB() == null) {
				continue;
			}
			
			String teamA = standings[i].getTeamA();
			String teamB = standings[i].getTeamB();
			
			int teamAWins = 0;
			int teamBWins = 0;
			
			//Find the correct series
			if(teamA.equals(teamOne)) {
				if(teamB.equals(teamTwo)) {
					
					//Find out which team won and add a point towards them
					if(teamOneWins>teamTwoWins) {
						teamAWins++;
					}else if(teamTwoWins>teamOneWins) {
						teamBWins++;
					}
					
					//Increment wins of the teams
					standings[i].incrementWins(teamAWins, teamBWins);
					
					//If either team hits 4 wins in the series, they have won it
					if(standings[i].getTeamAWins() == 4) {
						return teamOne;
					}
					if(standings[i].getTeamBWins() == 4) {
						return teamTwo;
					}
				}
			}
		}
		//If no winner, return null
		return null;
	}
	
	//Load in the scores text file that corresponds to the current round
	public void updateRound(int roundNum) {
		MyFileReader round = null;
		//See which file corresponds to the roundNum
		if(roundNum == 1) {
			round = new MyFileReader("scores1.txt");
		}else if(roundNum == 2) {
			round = new MyFileReader("scores2.txt");
		}else if(roundNum == 3) {
			round = new MyFileReader("scores3.txt");
		}else if(roundNum == 4) {
			round = new MyFileReader("scores4.txt");
		}
		
		//Split up the line into an array
		String[] line = round.readString().split(",");
		String winner = updateStandings(line[0],line[1],Integer.valueOf(line[2]),Integer.valueOf(line[3]));
		
		//Keep going until end of the file
		while(!round.endOfFile()) {
			line = round.readString().split(",");
			winner = updateStandings(line[0],line[1],Integer.valueOf(line[2]),Integer.valueOf(line[3]));
			
			//If there is a winner then find the parent node
			if(winner != null) {
				if(winner == line[0] || winner == line[1]) {
					BinaryTreeNode parent = findParent(line[0],line[1]);
					parent.setData(winner);
				}
			}
		}
	}
	
	//Take in two strings representing names, and this method will find the parent node of the given strings
	public BinaryTreeNode<String> findParent(String teamOne, String teamTwo) {
		//If the root is null, return null
		if(tree.getRoot() == null) return null;
		
		//Make a queue for the queue-based traversal
		LinkedQueue<BinaryTreeNode> Q = new LinkedQueue<BinaryTreeNode>();
		//enqueue the root
		Q.enqueue(tree.getRoot());
		
		//Queue-based level-order traversal
		while(!Q.isEmpty()) {
			BinaryTreeNode v = Q.dequeue();
			
			if(v.getLeft() != null) Q.enqueue(v.getLeft());
			if(v.getRight() != null) Q.enqueue(v.getRight());
			
			if(v.getLeft() == null || v.getRight() == null) {
				continue;
			}
			
			String left = (String) v.getLeft().getData();
			String right = (String) v.getRight().getData();
			
			//If its the parent of both teams return that node
			if(left.contains(teamOne) || left.contains(teamTwo)) {
				if(right.contains(teamOne) || right.contains(teamTwo)) {
					return v;
				}
			}
		}
		
		//If no parent found return null
		return null;
	}
	/**
	 * This method adds the new series to the standings array before a new round begins. It does this using an iterator
	 * from the tree and skipping over the nodes that are still unknown until it gets to the nodes from the new round.
	 * It then takes two teams at a time from the iterator and creates a new series in the standings array for those
	 * two teams. The series standings (number of wins for each team) are set to 0 by default. 
	 */
	public void addNewStandings (int numSkips, int sIndex, int eIndex) {
		Iterator<String> iter = tree.iteratorLevelOrder();
		int i;
		String team1, team2;
		for (i = 0; i < numSkips; i++) {
			iter.next();
		}
		for (i = sIndex; i <= eIndex; i++) {
			team1 = iter.next();
			team2 = iter.next();
			standings[i] = new HockeySeries(team1, team2, 0, 0);
		}
	}
	
	/**
	 * This method simply prints out the standings table in a cleanly formatted table structure.
	 */
	public void printStandings () {
		String str;
		for (int k = 0; k < standings.length; k++) {
			if (standings[k] != null) {
				str = String.format("%-15s\t%-15s\t%3d-%d", standings[k].getTeamA(), standings[k].getTeamB(), standings[k].getTeamAWins(), standings[k].getTeamBWins());
				System.out.println(str);
			}
		}
	}
	
	
	public static void main(String[] args) {
		Playoffs pl = new Playoffs();
		pl.updateRound(1);

		// Uncomment each pair of lines when you are ready to run the subsequent rounds. 
		
		//pl.addNewStandings(7, 8, 11); // Ensure you execute this line before calling updateRound(2).
		//pl.updateRound(2);

		
		//pl.addNewStandings(3, 12, 13); // Ensure you execute this line before calling updateRound(3).
		//pl.updateRound(3);

		
		//pl.addNewStandings(1, 14, 14); // Ensure you execute this line before calling updateRound(4).
		//pl.updateRound(4);
	}

}
