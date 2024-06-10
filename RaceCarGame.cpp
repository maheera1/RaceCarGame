//Maheera Ashfaq (21i-1158)  Hamna Amjad(21i-1158)
#include <iostream>
#include <queue>
#include <limits>  //for max min
#include <cstdlib> //for rand no generation
#include <ctime>   //to get time 
#include <fstream>
#include <string>
#include <sstream>
#include <chrono>  //used for time calculation delays

using namespace std;

const int nodes_max = 100;
const int heapsize_max = 100;
const int infini = numeric_limits<int>::max();  //infinity val

//MinHeap Class
class MinHeap {
private:
    pair<int, int> heap[heapsize_max]; // An array of pairs representing the heap. Each pair contains a distance and a node identifier.
    int size; // Current number of elements in the heap.

    // get indices in the heap array.
    int parent(int ind)
    {
        return(ind - 1) / 2;
    }
    int left(int ind)
    {
        return(2 * ind + 1);
    }
    int right(int ind)
    {
        return(2 * ind + 2);
    }

    // Reorganizes the heap downwards from the specified index to maintain heap property.
    void heapifyDown(int i) {
        int l = left(i);
        int r = right(i);
        int smallest = i;

        // Find the smallest among the node, left child, and right child
        if (l < size && heap[l].first < heap[i].first)
            smallest = l;
        if (r < size && heap[r].first < heap[smallest].first)
            smallest = r;

        // Swap and continue heapifying if needed
        if (smallest != i) {
            swap(heap[i], heap[smallest]);
            heapifyDown(smallest);
        }
    }

    // Reorganizes the heap upwards from the specified index to maintain heap property.
    void heapifyUp(int i) {
        // Swap with parent until heap property is restored
        while (i != 0 && heap[parent(i)].first > heap[i].first) {
            swap(heap[i], heap[parent(i)]);
            i = parent(i);
        }
    }

public:
    MinHeap() : size(0) {} // Constructor 

    // Inserts a new element (distance, node) into the heap and reorganizes to maintain heap property.
    void push(pair<int, int> element) {
        heap[size] = element; // Place element at the end of the heap
        int index = size;
        size++; // Increase heap size
        heapifyUp(index); // Restore heap property
    }

    // Removes and returns the root/smallest element from the heap.
    pair<int, int> pop() {
        if (size == 0) return make_pair(-1, -1); //invalid if empty

        pair<int, int> root = heap[0]; // Store root element to return
        heap[0] = heap[size - 1]; // Move last element to root
        size--; // Reduce heap size
        heapifyDown(0); // Restore heap property
        return root; // Return original root
    }

    // Checks if the heap is empty.
    bool isEmpty() const {
        return size == 0;
    }
};

class Graph {
    int adj[nodes_max][nodes_max]; // 2D array representing an adjacency matrix of the graph.
    int node_Count; // Number of nodes currently in the graph.

public:
    // Optimized Constructor initializes the adjacency matrix.
    Graph() : node_Count(0)
    {
        for (int i = 0; i < nodes_max; i++)
        {
            for (int j = 0; j < nodes_max; j++)
            {
                // Set the distance to itself as zero and to others as infinity
                adj[i][j] = (i == j) ? 0 : infini;
            }
        }
    }

    // Adds a directed edge from src to dest with given weight
    void add_Edge(int src, int dest, int weight)
    {
        if (src >= 0 && src < node_Count && dest >= 0 && dest < node_Count)
        {
            adj[src][dest] = weight; // Set the weight for the edge
        }
        else
        {
            cout << "Invalid node index for edge between " << src << " and " << dest << endl;
        }
    }

    // Returns the weight of an edge between src and dest
    int getWeight(int src, int dest)
    {
        return adj[src][dest];
    }

    // Returns the current node count in the graph
    int getNodeCount() const
    {
        return node_Count;
    }

    // Sets the number of nodes in the graph
    void setNodeCount(int count)
    {
        node_Count = count;
    }

    // Implementation of Dijkstra's algorithm for shortest path finding
    void dijkstra(int src, int dist[], int prev[])
    {
        MinHeap minHeap;
        for (int i = 0; i < node_Count; ++i)
        {
            dist[i] = infini; // Initialize distances as infinity
            prev[i] = -1; // Initialize previous nodes as -1 (undefined)
        }

        dist[src] = 0; // Distance to the source is zero
        minHeap.push(make_pair(0, src)); // Push source node to MinHeap

        while (!minHeap.isEmpty())
        {
            int u = minHeap.pop().second; // Extract node with the smallest dist

            for (int v = 0; v < node_Count; ++v)
            {
                if (adj[u][v] != infini) { // If there's an edge between u and v.
                    int alt = dist[u] + adj[u][v]; // Calculate alternate path distance.
                    if (alt < dist[v]) { // If alternate path is shorter.
                        dist[v] = alt; // Update shortest distance to v.
                        prev[v] = u; // Update previous node for v.
                        minHeap.push(make_pair(dist[v], v)); // Push updated distance to MinHeap.
                    }
                }
            }
        }
    }

};

// Queue for Obstacles
class Obstacle_Queue
{
    int obstacles[nodes_max]; // Array to store obstacles, acting as a queue.
    int front, rear; // Pointers to the front and rear of the queue.

public:
    // Constructor 
    Obstacle_Queue() : front(0), rear(0)
    {
        for (int i = 0; i < nodes_max; ++i)
        {
            obstacles[i] = 0;  // Initialize all slots to 0 (or any other default value indicating empty).
        }
    }

    // Adds an obstacle to the queue.
    void enqueue_Obstacle(int obstacle)
    {
        obstacles[rear] = obstacle; // Place the obstacle at the current rear position.
        rear = (rear + 1) % nodes_max; // Increment rear and wrap around if necessary.
    }

    // Removes and returns an obstacle from the front of the queue.
    int dequeue_Obstacle()
    {
        if (front != rear) { // Check if the queue is not empty.
            int obstacle = obstacles[front]; // Store the obstacle at front.
            front = (front + 1) % nodes_max; // Increment front 
            return obstacle; // Return the dequeued obstacle.
        }
        return -1; // Return -1 if the queue is empty.
    }
    void updateTrack_WithObstacles(char track[][40], int trackCols, char obstacleChar)
    {
        for (int i = front; i != rear; i = (i + 1) % nodes_max)
        {
            if (obstacles[i] != 0) {  // Assuming 0 indicates no obstacle
                int row = obstacles[i] / trackCols;
                int col = obstacles[i] % trackCols;
                track[row][col] = obstacleChar; // Place obstacle on the track
            }
        }
    }

    void remove_Obstacle(int position)
    {
        // Search for the obstacle and remove it
        for (int i = front; i != rear; i = (i + 1) % nodes_max)
        {
            if (obstacles[i] == position)
            {
                obstacles[i] = 0; // Assuming 0 means no obstacle
                break;
            }
        }
    }

};

// Node class for the linked list
class Node
{
public:
    int data;
    Node* next; // Pointer to the next node 

    // Constructor 
    Node(int data) : data(data), next(nullptr) {}
};

// Linked list class for managing a collection of power ups and coins
class LinkedList
{
    Node* head; // Pointer to the first node in the linked list.

public:
    // Constructor initializes the linked list with an empty head (nullptr).
    LinkedList()
    {
        head = nullptr;
    }

    // Adds a new node with the provided data at the beginning of the linked list.
    void add_Node(int data)
    {
        Node* newNode = new Node(data); // Create a new Node.
        newNode->next = head; // Link the new node to the current head.
        head = newNode; // Update head to the new node.
    }
    void updateTrack_WithItems(char track[][40], int trackCols, char itemChar)
    {
        Node* current = head;
        while (current != nullptr)
        {
            int row = current->data / trackCols;
            int col = current->data % trackCols;
            track[row][col] = itemChar; // Place item (power-up or coin)
            current = current->next;
        }
    }

    // Method to remove an item from the list
    void remove_Item(int position)
    {
        Node* temp = head, * prev = nullptr;
        if (temp != nullptr && temp->data == position)
        {
            head = temp->next;
            delete temp;
            return;
        }
        while (temp != nullptr && temp->data != position)
        {
            prev = temp;
            temp = temp->next;
        }
        if (temp == nullptr) return;
        prev->next = temp->next;
        delete temp;
    }
    // Destructor to free memory of all nodes in the linked list.
    ~LinkedList()
    {
        Node* current = head;
        while (current != nullptr)
        {
            Node* next = current->next; // Store next node.
            delete current; // Free current node.
            current = next; // Move to next node.
        }
        head = nullptr; //head is set to nullptr.
    }
};

// Creates the game track with obstacles, power-ups, and coins
void generate_Square_Track(char track[][40], int& playerRow, int& playerCol, int trackHeight, int trackWidth, int difficultyLevel, Obstacle_Queue& obstacles, LinkedList& powerUps, LinkedList& coins, bool isAutomated) {
    srand(static_cast<unsigned int> (time(nullptr))); // Start the randomizer.

    for (int i = 0; i < trackHeight; i++)
    {
        for (int j = 0; j < trackWidth; j++)
        {
            if (i == 0 && j == 0) track[i][j] = 'S'; // Starting point
            else if (i == trackHeight - 1 && j == trackWidth - 1) track[i][j] = 'E'; // End point
            else if (i % 4 == 0 && j % 4 == 0) track[i][j] = '+'; // Places a turn
            else track[i][j] = '-'; // Regular path

            // Modify this part to conditionally place obstacles
            if (!isAutomated) {  // Skip placing obstacles if in automated mode
                int randNum = rand() % 10;
                if (randNum == 3) powerUps.add_Node(i * trackWidth + j);
                else if (randNum == 1) coins.add_Node(i * trackWidth + j);
                else if (randNum == 2) obstacles.enqueue_Obstacle(i * trackWidth + j);
            }
            else
            {

                int randNum = rand() % 10;
                if (randNum == 3) powerUps.add_Node(i * trackWidth + j);
                else if (randNum == 1) coins.add_Node(i * trackWidth + j);
            }
        }
    }

    playerRow = 0; // Set player's starting row
    playerCol = 0; // Set player's starting column
}

// Shows the game track in the console
void display_Square_Track(const char track[][40], int trackRows, int trackCols, int playerRow, int playerCol)
{
    system("cls");

    for (int i = 0; i < trackRows; i++)
    {
        for (int j = 0; j < trackCols; j++)
        {
            if (i == playerRow && j == playerCol)
            {
                cout << "\033[34mP\033[0m"; // Player's current position
            }
            else
            {
                switch (track[i][j])
                {
                case '+': cout << "\033[32m+\033[0m"; break; // Turns
                case '*': cout << "\033[35m*\033[0m"; break; // Power-ups
                case '$': cout << "\033[33m$\033[0m"; break; // Coins
                case '#': cout << "\033[31m#\033[0m"; break; // Obstacles
                default:  cout << track[i][j]; // Regular path
                }
            }
        }
        cout << endl;
    }
}

// Handles player input for moving and controlling the game
void handle_Input(char track[][40], int trackRows, int trackCols, int& playerRow, int& playerCol, bool& isRunning, bool& isPaused)
{
    char command;
    cin >> command; // Read the player's command

    switch (command)
    {
    case 'w': // Move up
    case 'W':
        if (playerRow > 0) playerRow--; // Decrease row, making sure it's within bounds
        break;
    case 'a': // Move left
    case 'A':
        if (playerCol > 0) playerCol--; // Decrease column, within bounds
        break;
    case 's': // Move down
    case 'S':
        if (playerRow < trackRows - 1) playerRow++; // Increase row, within bounds
        break;
    case 'd': // Move right
    case 'D':
        if (playerCol < trackCols - 1) playerCol++; // Increase column, within bounds
        break;
    case 'p': // Pause or unpause the game
    case 'P':
        isPaused = !isPaused; // Toggle pause state
        break;
    case 'q': // Quit the game
    case 'Q':
        isRunning = false; // Set running flag to false
        break;
    }
}

//game result class
class Game_Result
{
public:
    string name;
    int score;
    int distance;  // Number of moves made
    double timeTaken;  // Time taken in seconds
    int powerUpsCollected;  // Number of power-ups collected
    int coinsCollected;  // Number of coins collected
    string difficulty;  // Difficulty level

    //constructor
    Game_Result()
        : score(0), distance(0), timeTaken(0.0), powerUpsCollected(0), coinsCollected(0), difficulty("Unknown") {}

    Game_Result(string dataLine)
    {
        stringstream ss(dataLine);
        string temp;

        // Extract name
        getline(ss, temp, ':'); // Skip "Player"
        getline(ss, name, ',');

        // Extract score
        getline(ss, temp, ':'); // Skip "Score"
        ss >> score;
        getline(ss, temp, ','); // Skip until next field

        // Extract distance
        getline(ss, temp, ':'); // Skip "Distance"
        ss >> distance;
        getline(ss, temp, ','); // Skip until next field

        // Extract time taken
        getline(ss, temp, ':'); // Skip "Time Taken"
        ss >> timeTaken;
        getline(ss, temp, 's'); // Skip until 's'
        getline(ss, temp, ','); // Skip until next field

        // Extract power-ups collected
        getline(ss, temp, ':'); // Skip "Power-ups"
        ss >> powerUpsCollected;
        getline(ss, temp, ','); // Skip until next field

        // Extract coins collected
        getline(ss, temp, ':'); // Skip "Coins"
        ss >> coinsCollected;
        getline(ss, temp, ','); // Skip until next field

        // Extract difficulty
        getline(ss, temp, ':'); // Skip "Difficulty"
        getline(ss, difficulty);
    }
};

class Score_Node
{
public:
    Game_Result data;
    Score_Node* left;
    Score_Node* right;

    Score_Node(Game_Result data) : data(data), left(nullptr), right(nullptr) {}

};

class Score_BST
{
private:
    Score_Node* root;

    Score_Node* insert(Score_Node* node, Game_Result data)
    {
        if (node == nullptr)
        {
            return new Score_Node(data);
        }
        if (data.score < node->data.score)
        {
            node->left = insert(node->left, data);
        }
        else
        {
            node->right = insert(node->right, data);
        }
        return node;
    }

public:
    Score_BST() : root(nullptr) {}

    void insert(Game_Result data)
    {
        root = insert(root, data);
    }

    void inOrder_Traversal(Score_Node* node)
    {
        if (node != nullptr)
        {
            inOrder_Traversal(node->left);
            cout << "\033[0m" << "Name :" << node->data.name << " - Score : " << node->data.score << "-Distance : " << node->data.distance << " - Time Taken : " << node->data.timeTaken << "-Difficulty Level : " << node->data.difficulty << "\033[0m" << endl;
            inOrder_Traversal(node->right);
        }
    }

    void displayScores()
    {
        inOrder_Traversal(root);
    }

};

//function to check collisions on track
bool checkCollision_And_UpdateScore(char track[][40], int trackCols, int& playerRow, int& playerCol, int& score, Game_Result& result, LinkedList& powerUpsList, LinkedList& coinsList, Obstacle_Queue& obstaclesQueue) {
    int position = playerRow * trackCols + playerCol; // Use trackCols for position calculation
    char cell = track[playerRow][playerCol];

    switch (cell)
    {
    case '*': // Power-up
        score *= 2; // Double score for power-up
        powerUpsList.remove_Item(position); // Remove from power-ups list
        track[playerRow][playerCol] = '-'; // Clear the cell
        break;
    case '$': // Coin
        score += 3; // Increase score for coin
        coinsList.remove_Item(position); // Remove from coins list
        track[playerRow][playerCol] = '-'; // Clear the cell
        break;
    case '#': // Obstacle
        score -= 5; // Decrease score for hitting an obstacle
        obstaclesQueue.remove_Obstacle(position); // Remove from obstacles queue
        track[playerRow][playerCol] = '-'; // Clear the cell
        break;
    case '+': // Turning point
        // Do not clear the cell
        break;
    case 'E': // End point
        return true; // Signal that end point is reached
    default:
        break;
    }

    return false; // Continue game (end point not reached)
}


//write in file
void write_Score_ToFile(const Game_Result& gameResult)
{
    ofstream scoreFile("final_score.txt", ios::app); // Open in append mode
    if (scoreFile.is_open())
    {
        scoreFile << "Player: " << gameResult.name
            << ", Score: " << gameResult.score
            << ", Distance: " << gameResult.distance
            << ", Time Taken: " << gameResult.timeTaken << "s"
            << ", Power-ups: " << gameResult.powerUpsCollected
            << ", Coins: " << gameResult.coinsCollected
            << ", Difficulty: " << gameResult.difficulty
            << endl;
        scoreFile.close();
        cout << "Player score saved " << endl;
    }
    else
    {
        cout << "Unable to open file to save score." << endl;
    }
}

// Function to create a delay for a specified number of milliseconds
void delay(int milliseconds)
{
    auto start = chrono::high_resolution_clock::now(); // Get the current time as the start point
    auto end = start + chrono::milliseconds(milliseconds); // Calculate the end time based on the delay

    // Loop until the current time reaches the end time
    while (chrono::high_resolution_clock::now() < end)
    {
        // Empty loop to just pass time
    }
}


Game_Result runGame(int difficultyLevel, bool automated)
{
    // Initialize variables
    const int maxRows = 20, maxCols = 40;
    char track[maxRows][maxCols];
    int playerRow, playerCol, score = 0;
    bool isRunning = true, isPaused = false;
    int distance = 0;  // Distance covered counter
    int trackRows, trackCols;
    Obstacle_Queue obstacles;
    Game_Result result;

    LinkedList powerUps;
    LinkedList coins;



    // Set the track size based on the difficulty level
    if (difficultyLevel == 1) { // Easy (5x10)
        trackRows = 5;
        trackCols = 10;
        result.difficulty = "Easy";
    }
    else if (difficultyLevel == 2) { // Medium (10x20) - Current Track
        trackRows = 10;
        trackCols = 20;
        result.difficulty = "Medium";
    }
    else { // Hard (20x40)
        trackRows = 20;
        trackCols = 40;
        result.difficulty = "Hard";
    }

    // Generate the track based on the selected difficulty
    generate_Square_Track(track, playerRow, playerCol, trackRows, trackCols, difficultyLevel, obstacles, powerUps, coins, true); // true for automated mode

    auto startTime = chrono::steady_clock::now(); // Start timer

    // Automated mode
    if (automated)
    {
        int startX, startY, endX, endY;
        display_Square_Track(track, trackRows, trackCols, playerRow, playerCol);

        // Prompt for start and end points
        cout << "Enter start coordinates:\n (row)\n";
        cin >> startX;
        cout << " (column)\n";
        cin >> startY;
        cout << "Enter end coordinates: \n (row)\n";
        cin >> endX;
        cout << " (column)\n";
        cin >> endY;

        // Convert coordinates to node indices
        int startNode = startX * trackCols + startY;
        int endNode = endX * trackCols + endY;


        // Prepare for Dijkstra's algorithm
        int* dist = new int[nodes_max];
        int* prev = new int[nodes_max];
        Graph graph;
        // Initialize the graph with the given track
        graph.setNodeCount(trackRows * trackCols);

        for (int row = 0; row < trackRows; row++)
        {
            for (int col = 0; col < trackCols; col++)
            {
                int node = row * trackCols + col;

                // Only consider non-obstacle cells for graph edges
                if (track[row][col] != '#' && track[row][col] != '+') { // Assuming '#' and '+' are obstacles or turnings

                    // Check and add connections in all four directions (up, down, left, right)
                    if (row > 0 && track[row - 1][col] != '#' && track[row - 1][col] != '+') // Up
                        graph.add_Edge(node, (row - 1) * trackCols + col, 1);
                    if (row < trackRows - 1 && track[row + 1][col] != '#' && track[row + 1][col] != '+') // Down
                        graph.add_Edge(node, (row + 1) * trackCols + col, 1);
                    if (col > 0 && track[row][col - 1] != '#' && track[row][col - 1] != '+') // Left
                        graph.add_Edge(node, row * trackCols + (col - 1), 1);
                    if (col < trackCols - 1 && track[row][col + 1] != '#' && track[row][col + 1] != '+') // Right
                        graph.add_Edge(node, row * trackCols + (col + 1), 1);
                }
            }
        }


        // Run Dijkstra's algorithm
        graph.dijkstra(startNode, dist, prev);

        // Reconstruct the path from endNode to startNode
        int path[nodes_max];
        int pathLength = 0;
        for (int at = endNode; at != -1 && at >= 0 && at < nodes_max && pathLength < nodes_max; at = prev[at])

        {
            path[pathLength++] = at;
        }


        // Reverse the path array
        for (int i = 0; i < pathLength / 2; i++)
        {
            int temp = path[i];
            path[i] = path[pathLength - 1 - i];
            path[pathLength - 1 - i] = temp;
        }

        // Check if a path exists
        if (pathLength < 2 || path[0] != startNode)
        {
            cout << "No path exists between the given points!" << endl;
            return result;
        }

        // Move the player along the path
        for (int i = 0; i < pathLength; i++)
        {
            int node = path[i];
            int row = node / trackCols;
            int col = node % trackCols;

            // Highlight the path (you can use a different character or color to show the path)
            track[row][col] = '@'; // Example: using '@' to highlight the path

            // Update player position
            playerRow = row;
            playerCol = col;

            // Display the track with player's new position
            display_Square_Track(track, trackRows, trackCols, playerRow, playerCol);
            // Simulate a delay to create the illusion of movement
            delay(500);

            // Update game state (score, collision, etc.)
            bool gameEnded = checkCollision_And_UpdateScore(track, trackCols, playerRow, playerCol, score, result, powerUps, coins, obstacles);
            if (gameEnded || score < 0)
            {
                isRunning = false;
                break;
            }

        }
        // Record end time and calculate game duration
        auto endTime = chrono::steady_clock::now();
        chrono::duration<double> elapsedTime = endTime - startTime;
        result.timeTaken = elapsedTime.count();

        delete[] dist;
        delete[] prev;
    }

    else
    {
        // Manual mode
        int updateCounter = 0;
        const int updateInterval = 5;
        int obstacleAddCounter = 0;
        const int obstacleAddInterval = 10; // Frequency of adding new obstacles
        while (isRunning)
        {
            display_Square_Track(track, trackRows, trackCols, playerRow, playerCol);// Update to show different track sizes
            cout << "\033[36mScore: " << score << "\033[0m" << endl;
            cout << "Use WASD to move, P to pause, Q to quit: ";

            if (!isPaused)
            {
                int prevRow = playerRow, prevCol = playerCol;
                handle_Input(track, trackRows, trackCols, playerRow, playerCol, isRunning, isPaused);

                if (playerRow != prevRow || playerCol != prevCol)
                {
                    distance++;  // Increment distance for each valid move
                }

                bool reachedEnd = checkCollision_And_UpdateScore(track, trackCols, playerRow, playerCol, score, result, powerUps, coins, obstacles);
                if (reachedEnd || score < 0)
                {
                    isRunning = false;  // End the game
                }


                // Periodic update of obstacles and items
                if (updateCounter % updateInterval == 0 && !isPaused)
                {
                    // Add new obstacles
                    if (obstacleAddCounter++ % obstacleAddInterval == 0)
                    {
                        int newObstaclePosition = -1;  // Initialize to an invalid position
                        bool validPositionFound = false;

                        while (!validPositionFound)
                        {
                            int randRow = rand() % trackRows;  // Random row
                            int randCol = rand() % trackCols;  // Random column

                            // Calculate position index
                            int positionIndex = randRow * trackCols + randCol;

                            // Check if the position is valid and not occupied
                            if (track[randRow][randCol] == '-' && positionIndex != (playerRow * trackCols + playerCol))
                            {
                                newObstaclePosition = positionIndex;
                                validPositionFound = true;
                            }
                        }

                        // Enqueue the new obstacle position
                        obstacles.enqueue_Obstacle(newObstaclePosition);
                    }

                    // Update the track with new obstacles and items
                    obstacles.updateTrack_WithObstacles(track, trackCols, '#');
                    powerUps.updateTrack_WithItems(track, trackCols, '*');
                    coins.updateTrack_WithItems(track, trackCols, '$');
                }

                // Update distance and counter
                distance++;
                updateCounter++;

            }

            else
            {
                cout << "Game Paused ! Press P to resume!\n" << endl;
            }
        }
        auto endTime = chrono::steady_clock::now();
        chrono::duration<double> elapsedTime = endTime - startTime;
        result.timeTaken = elapsedTime.count();  // Set time taken in result

    }


    cout << "Game Ended! Score : " << score << endl;

    cout << "Enter your name : ";
    cin.ignore();  // To clear the newline character from the buffer
    getline(cin, result.name);  // Using getline to allow spaces in names
    result.score = score;
    result.distance = distance;  // Set distance in result

    // Scoring formula
    int baseScore = 10;
    int timePenalty = static_cast<int>(result.timeTaken);  // Simple time penalty
    result.score = baseScore + (result.distance * 3) - timePenalty + score; //score formula

    cout << "\033[35mThe final score is: " << result.score << "\033[0m" << endl;
    cout << "\033[35mPower-ups Collected: " << result.powerUpsCollected << "\033[0m" << endl;
    cout << "\033[35mCoins Collected: " << result.coinsCollected << "\033[0m" << endl;
    cout << "\033[35mThe distance covered is: " << result.distance << "\033[0m" << endl;
    cout << "\033[35mThe time taken is: " << result.timeTaken << "\033[0m" << endl;

    return result;
}

void buildAndDisplay_Leaderboard()
{
    ifstream scoreFile("final_score.txt");
    string line;
    Score_BST leaderboard;

    if (scoreFile.is_open())
    {
        while (getline(scoreFile, line))
        {
            Game_Result result(line);
            leaderboard.insert(result);
        }
        scoreFile.close();
    }
    else
    {
        cout << "Unable to open file or no scores saved yet !" << endl;
        return;
    }

    // Display the leaderboard
    leaderboard.displayScores();
}

void displayMenu()
{
    cout << "\033[36m"; // Set color to Cyan for the title
    cout << " ********************** RACE CAR GAME *********************** ";
    cout << R"(
 *                                                          *
 *                                  ..-------++.            *
 *                  .-'/ |      _||  \"--.                  *
 *            .--'`./\j_/_||___\    `----.                  *
 *       .--'____    |          \     _____    /            *
 *     j    /,---.\   |        =o |   /,---.\   |           *
 *    [__]==// .-. \\==`===========/==// .-. \\=[__]        *
 *     `-._|\ `-' /|___\_________/___|\ `-' /|_.'           *
 *            `---'                     `---'               *
 ************************************************************
    )" << "\033[0m"; // Reset color after title
    cout << "\033[36m" << "By: Maheera (21i-1158) & Hamna (21i-1189)" << "\033[0m" << endl << endl;

    cout << "\033[35m"; // Set color to Magenta for the menu
    cout << "Menu:\n";
    cout << "-----------------\n";
    cout << "1 - Play Manual game" << endl;
    cout << "2 - Play Automated game" << endl;
    cout << "3 - View Scores" << endl;
    cout << "4 - Game Instructions" << endl;
    cout << "5 - Quit" << endl;
    cout << "Enter your choice: ";
    cout << "\033[0m";
}


int selectDifficulty()
{
    int difficulty;
    cout << "Select Difficulty:\n";
    cout << "\033[32m1 - Easy\033[0m\n"; // Green for Easy
    cout << "\033[33m2 - Medium\033[0m\n"; // Yellow for Medium
    cout << "\033[31m3 - Hard\033[0m\n"; // Red for Hard
    cout << "Enter choice: ";
    cin >> difficulty;
    return difficulty;
}

void displayInstructions()
{
    cout << "\033[36m"; // Set color to Cyan for the title
    cout << "*********************** GAME INSTRUCTIONS **********************" << "\033[0m" << endl << endl;

    // ASCII art for visual appeal
    cout << R"(
  
   (       ) (          (                     (       )     ) (     
   )\ ) ( /( )\ )  *   ))\ )        (    *   ))\ ) ( /(  ( /( )\ )  
  (()/( )\()|()/(` )  /(()/(   (    )\ ` )  /(()/( )\()) )\()|()/(  
   /(_)|(_)\ /(_))( )(_))(_))  )\ (((_) ( )(_))(_)|(_)\ ((_)\ /(_)) 
  (_))  _((_|_)) (_(_()|_)) _ ((_))\___(_(_()|_))   ((_) _((_|_))   
  |_ _|| \| / __||_   _| _ \ | | ((/ __|_   _|_ _| / _ \| \| / __|  
   | | | .` \__ \  | | |   / |_| || (__  | |  | | | (_) | .` \__ \  
  |___||_|\_|___/  |_| |_|_\\___/  \___| |_| |___| \___/|_|\_|___/  
                                                                    
    )";
    cout << endl;

    // Manual Mode Instructions
    cout << "\033[33m" << "Manual Mode:" << "\033[0m" << endl; // Yellow color
    cout << "\033[32m"; // Green color for instructions
    cout << "- Use WASD keys to move the car (W = up, A = left, S = down, D = right)." << endl;
    cout << "- Collect coins ($) and power-ups (*) to increase your score." << endl;
    cout << "- Avoid obstacles (#) as they decrease your score." << endl;
    cout << "- Reach the end point (E) to finish the game." << endl;
    cout << "- Press P to pause/unpause the game and Q to quit." << endl;
    cout << "\033[0m" << endl; // Reset color

    // Automated Mode Instructions
    cout << "\033[34m" << "Automated Mode:" << "\033[0m" << endl; // Blue color
    cout << "\033[36m"; // Cyan color for instructions
    cout << "- Enter start and end coordinates when prompted." << endl;
    cout << "- The game will automatically find the shortest path from start to end." << endl;
    cout << "- Watch as the car moves along the path." << endl;
    cout << "- The game ends when the car reaches the end point." << endl;
    cout << "\033[0m" << endl; // Reset color

    cout << "Press Enter to return to the main menu!";
    cin.ignore(); // Wait for Enter key
}

// Main Function for Testing
int main() {
    int choice;
    do {
        displayMenu();
        cin >> choice;

        switch (choice)
        {
        case 1:
        { // Manual Play
            int difficulty = selectDifficulty();
            Game_Result gameResult = runGame(difficulty, false); // false for manual mode
            write_Score_ToFile(gameResult);
            break;
        }

        case 2:
        { // Automated Play
            int difficulty = 1;

            Game_Result gameResult = runGame(difficulty, true); // true for automated mode
            write_Score_ToFile(gameResult);
            break;
        }
        case 3:
            cout << "\033[31m\n\n** Player Scores **\033[0m\n\n";
            buildAndDisplay_Leaderboard();
            break;
        case 4: // Game Instructions
            displayInstructions();
            break;
        case 5:
            cout << "Exiting the game Goodbye!" << endl;
            break;


        default:
            cout << "Incorrect option! Please choose again!" << endl;
            break;
        }

        // Clear the input buffer to handle invalid input
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (choice != 5)
        {
            cout << "\nPress Enter to continue...";
            cin.ignore(); // Wait for Enter key
        }

    } while (choice != 5);

    return 0;
}