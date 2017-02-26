#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>


/* SECTION I: Structures */

// Structure for (x,y)
struct XYCoordinate
{
  float x, y;
};

// Structure for (x,y,z)
struct XYZCoordinate
{
  float x, y, z;
};

// Structure for (x,y,z,w)
struct XYZWCoordinate
{
  float x, y, z, w;
};

// Structure of a single node in the the adj list
struct Node
{
  int dst;
  float weight;
  struct Node* next;
};
 
// structure of an adjacency list
struct AdjList
{
  struct Node *head;
};
 
// graph = array (size is that of number of vertices in graph) of adjacency lists
struct Graph
{
  int vertices;
  struct AdjList* array;
};

/* SECTION II: Creating new elements of structures */

struct XYCoordinate* new2dCoord(float x, float y)
{
  struct XYCoordinate* newCoord = (struct XYCoordinate*) malloc(sizeof(struct XYCoordinate));
  newCoord->x = x;
  newCoord->y = y;
  return newCoord;
}

struct XYZCoordinate* new3dCoord(float x, float y, float z)
{
  struct XYZCoordinate* newCoord = (struct XYZCoordinate*) malloc(sizeof(struct XYZCoordinate));
  newCoord->x = x;
  newCoord->y = y;
  newCoord->z = z;
  return newCoord;
}

struct XYZWCoordinate* new4dCoord(float x, float y, float z, float w)
{
  struct XYZWCoordinate* newCoord = (struct XYZWCoordinate*) malloc(sizeof(struct XYZWCoordinate));
  newCoord->x = x;
  newCoord->y = y;
  newCoord->z = z;
  newCoord->w = w;
  return newCoord;
}
 
// create an adjacency list for a node (for each vertex)
struct Node* newNodeLst(int dst, float weight)
{
  struct Node* newNode = (struct Node*) malloc(sizeof(struct Node));
  newNode->dst = dst;
  newNode->weight = weight;
  newNode->next = NULL;
  return newNode;
}
 
struct Graph* generateGraph(int vertices)
{
  struct Graph* graph = (struct Graph*) malloc(sizeof(struct Graph));
  graph->vertices = vertices;

  // array of size of vertices
  graph->array = (struct AdjList*) malloc(vertices * sizeof(struct AdjList));

   // Inisialize all elements in adj array and set them to zero
  int node;
  for (node = 0; node < vertices; node++)
    graph->array[node].head = NULL;

  return graph;
}

/* SECTION II: Calculating Distance */

// Generate Random number between [0,1]
float rnum()
{
  return (((float)rand()/(float)(RAND_MAX)) * 1.0);
}

// Global locations array pointer
struct XYCoordinate * *locations2d;
struct XYZCoordinate * *locations3d;
struct XYZWCoordinate * *locations4d;

void dim2locations(int vertices)
{
  // float locations[vertices];
  locations2d = malloc((sizeof(struct XYCoordinate)) * vertices);

  int i;
  for (i = 0; i < vertices; i++)
  {
    locations2d[i] = new2dCoord(rnum(),rnum());
  }
}

void dim3locations(int vertices)
{
  // float locations[vertices];
  locations3d = malloc((sizeof(struct XYZCoordinate)) * vertices);

  int i;
  for (i = 0; i < vertices; i++)
  {
    locations3d[i] = new3dCoord(rnum(),rnum(),rnum());
  }
}

void dim4locations(int vertices)
{
  // float locations[vertices];
  locations4d = malloc((sizeof(struct XYZWCoordinate)) * vertices);

  int i;
  for (i = 0; i < vertices; i++)
  {
    locations4d[i] = new4dCoord(rnum(),rnum(),rnum(),rnum());
  }
}

float distance2d(int src, int dst)
{
  float x1 = locations2d[src]->x;
  float y1 = locations2d[src]->y;
  float x2 = locations2d[dst]->x;
  float y2 = locations2d[dst]->y;

  return (sqrtf(pow(x1-x2, 2) + pow(y1-y2,2)));
}

float distance3d(int src, int dst)
{
  float x1 = locations3d[src]->x;
  float y1 = locations3d[src]->y;
  float z1 = locations3d[src]->z;
  float x2 = locations3d[dst]->x;
  float y2 = locations3d[dst]->y;
  float z2 = locations3d[dst]->z;

  return (sqrtf(pow(x1-x2, 2) + pow(y1-y2,2) + pow(z1-z2, 2)));
}

float distance4d(int src, int dst)
{
  float x1 = locations4d[src]->x;
  float y1 = locations4d[src]->y;
  float z1 = locations4d[src]->z;
  float w1 = locations4d[src]->w;
  float x2 = locations4d[dst]->x;
  float y2 = locations4d[dst]->y;
  float z2 = locations4d[dst]->z;
  float w2 = locations4d[dst]->w;

  return (sqrtf(pow(x1-x2, 2) + pow(y1-y2,2) + pow(z1-z2, 2) + + pow(w1-w2, 2)));
}

/* SECTION IIII: Usefull function*/
 
// Add edge to graph from A->B and B->A as it's an undirected graph
void addEdge(struct Graph* graph, int src, int dst, float weight)
{
  // A->B
  struct Node* newNode = newNodeLst(dst, weight);
  newNode->next = graph->array[src].head;
  graph->array[src].head = newNode;

  // B->A
  newNode = newNodeLst(src, weight);
  newNode->next = graph->array[dst].head;
  graph->array[dst].head = newNode;
}

float findWeight(int vertices, int src, int dst, int dimension)
{
  float weight;

  if (dimension == 0)
  {
    weight = rnum();
  } else if (dimension == 2)
  {
    // create locations array (first iteration = build locations array)
    if (src == 0 && dst == 1)
    {
      dim2locations(vertices);
    }
    weight = distance2d(src, dst);

  }else if (dimension == 3)
  {
    // create locations array (first iteration = build locations array)
    if (src == 0 && dst == 1)
    {
      dim3locations(vertices);
    }
    weight = distance3d(src, dst);
  }else if (dimension == 4)
  {
    // create locations array (first iteration = build locations array)
    if (src == 0 && dst == 1)
    {
      dim4locations(vertices);
    }
    weight = distance4d(src, dst);
  }else
  {
    //exit because user entered inavailable dimention.. with error message
    printf("Sorry, we don't support this dimension \n");
    exit(0);
  }
  return weight;
}

/* SECTION 5: Testing*/

// Print graph representation for TESTING ONLY (COMMENT OUT BEFORE SUBMISSION)
void showGraph(struct Graph* graph)
{
  int v;
  for (v = 0; v < graph->vertices; ++v)
  {
    struct Node* Crawl = graph->array[v].head;
    printf("\n vertex %d \n head: ", v);
    while (Crawl)
    {
        printf("-> V = %d , W = %f", Crawl->dst, Crawl->weight);
        Crawl = Crawl->next;
    }
    printf("\n");
  }
}

/* SECTION 6: Main Function*/
 int main(int argc, char *argv[])
{

  /* Intializes random number generator */
  srand((unsigned int)time(NULL));

  // Values entered by user
  int flexible = atoi(argv[1]);
  int vertices = atoi(argv[2]);
  int numtrials = atoi(argv[3]);
  int dimension = atoi(argv[4]);

  // Generate graph space
  struct Graph* graph = generateGraph(vertices);

  // Initialize values for creating edges
  int vertexCounter;
  int dst; // Destination of edge

  // Add all edges for complete undirected graph (UNWIEGHTED FOR NOW, NEED TO ADD WIEGHTS LATER)
  if (vertices > 1){
    for( vertexCounter = 0; vertexCounter <= vertices; vertexCounter++ ){
      for( dst = (vertexCounter + 1); dst < vertices; dst++ ){
        addEdge(graph, vertexCounter, dst, findWeight(vertices, vertexCounter, dst, dimension));
      }
    }
  }

  // prints generated graph for testing...
  showGraph(graph);

  return 0;
}



