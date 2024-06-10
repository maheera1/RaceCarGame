# RaceCarGame
The code represents a console-based game that integrates various data structures and algorithms to offer an interactive and engaging experience. The game features a track with obstacles, power-ups, and coins, and supports both manual and automated gameplay modes. A leaderboard system is also implemented to track player scores.

Classes and Structures
1.	MinHeap Class:
•	Purpose: Implements a min-heap data structure, primarily used in Dijkstra's algorithm for finding the shortest path in the game's automated mode.

•	Efficiency: The use of a min-heap allows efficient retrieval and updating of the smallest element, crucial for the priority queue in Dijkstra's algorithm.

2.	Graph Class:
•	Purpose: Represents the game track as a graph, useful in pathfinding and game logic.

•	Efficiency: The adjacency matrix representation offers constant-time access to check for an edge's presence or weight, beneficial for the dense graph in the game.

3.	ObstacleQueue Class:
•	Purpose: Manages obstacles on the game track using a queue structure.

•	Efficiency: The queue provides an orderly way to add and remove obstacles, ensuring a fair and predictable game environment.

4.	LinkedList Class:
•	Purpose: Handles collections of power-ups and coins on the game track.

•	Efficiency: The linked list allows dynamic and efficient insertion and deletion of items, which is vital as the game progresses.

5.	Node Class:
•	Purpose: A utility class used by LinkedList to store individual elements.

•	Efficiency: Facilitates easy and efficient management of list elements.

6.	GameResult Class:
•	Purpose: Stores and manages game results.

•	Efficiency: Encapsulating game results in a class simplifies data management and enhances readability.

7.	ScoreNode and ScoreBST Class:
•	Purpose: Implements a binary search tree to maintain a leaderboard.

•	Efficiency: The BST structure allows efficient insertion and in-order traversal, ideal for maintaining a sorted leaderboard.

Main Functions and Their Workings

1.	generateSquareTrack:
•	Generates the game track with obstacles, power-ups, and coins.
•	Method Efficiency: Random placement of items and obstacles ensures variability and unpredictability in gameplay.

2.	displaySquareTrack:
•	Displays the current state of the game track.
•	Method Efficiency: Systematic iteration over the game grid allows for a clear and concise display of the game state.

3.	handleInput:
•	Processes player input for movement and game control.
•	Method Efficiency: Direct mapping of key inputs to game actions provides a responsive and intuitive user experience.

4.	runGame:
•	Manages the main game loop, including game initialization, user interaction, and game termination.
•	Method Efficiency: The separation of manual and automated gameplay logic within the same function enhances code reuse and maintainability.

5.	writeScoreToFile:
•	Writes the game result to a file.
•	Method Efficiency: File I/O operations are encapsulated in a single function, centralizing and simplifying data persistence.

6.	checkCollisionAndUpdateScore:
•	Checks for collisions on the track and updates the score accordingly.
•	Method Efficiency: Efficient checking of the player's position against track elements minimizes computational overhead.

7.	buildAndDisplayLeaderboard:
•	Reads game results from a file and displays a leaderboard.
•	Method Efficiency: In-order traversal of a BST provides a sorted view of scores, optimizing for leaderboard presentation.


Data Structure Usage
•	Graphs: The use of graphs for the game track enables efficient implementation of pathfinding algorithms like Dijkstra's, enhancing the automated mode's performance.

•	Linked Lists: The use of linked lists for managing dynamic collections of game items (power-ups, coins) allows for flexible and efficient insertion and removal, which is ideal for the constantly changing game environment.

•	Queues: The obstacle management using a queue ensures a systematic and predictable gameplay experience, as obstacles are handled in a FIFO manner.


Conclusion
The game's implementation effectively utilizes various data structures, each chosen for its specific advantages in the game context. This strategic use of graphs, linked lists, and queues not only enhances the game's performance but also contributes to a more structured and maintainable codebase. The distinction between manual and automated gameplay modes, along with a robust scoring and leaderboard system, adds depth and replayability to the game.

