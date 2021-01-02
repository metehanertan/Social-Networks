#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<locale.h>
#define INFINITY 9999

//Metehan ERTAN 150117051

typedef struct node
{
    char name[50];
    struct node* next;
    int weight;
    int vertex;
}node;

typedef struct Graph
{
    int numVertices;
    struct node** adjLists;
    int* visited;
}Graph;

node* createNode(char name[50],int vertex);

void printGraph(Graph* graph);
void printMatrix(Graph* graph);
int search(node* pCrawl,node* head);
Graph* createGraph(int vertices);
void addEdge(Graph* graph, char src[50], char dest[50],int i,int k);
void printGraph(Graph* graph);
int bfs(struct Graph* graph, char *src,char dest[50]);
void Centrality(Graph *graph);
int dijkstra( Graph* graph,int startnode,int betweeness);


node *source,*temp;
int betweenNode[10] = {0};

int main(void)
{
    int V = 10;
     Graph* graph = createGraph(V);
    
	addEdge(graph,"Cem","Ayse",0,1);
	addEdge(graph,"Cem","Ferit",0,6);
	addEdge(graph,"Cem","Dundar",0,4);
	addEdge(graph,"Ayse","Cem",1,0);
	addEdge(graph,"Ayse","Ferit",1,6);
	addEdge(graph,"Ayse","Dundar",1,4);
	addEdge(graph,"Ayse","Belma",1,2);
	addEdge(graph,"Belma","Ayse",2,1);
	addEdge(graph,"Belma","Dundar",2,4);
	addEdge(graph,"Belma","Edip",2,3);
	addEdge(graph,"Edip","Belma",3,2);
	addEdge(graph,"Edip","Dundar",3,4);
	addEdge(graph,"Edip","Gamze",3,5);
	addEdge(graph,"Dundar","Ayse",4,1);
	addEdge(graph,"Dundar","Belma",4,2);
	addEdge(graph,"Dundar","Cem",4,0);
	addEdge(graph,"Dundar","Ferit",4,6);
	addEdge(graph,"Dundar","Gamze",4,5);
	addEdge(graph,"Dundar","Edip",4,3);
	addEdge(graph,"Gamze","Dundar",5,4);
	addEdge(graph,"Gamze","Edip",5,3);
	addEdge(graph,"Gamze","Ferit",5,6);
	addEdge(graph,"Gamze","Halit",5,7);
	addEdge(graph,"Ferit","Ayse",6,1);
	addEdge(graph,"Ferit","Cem",6,0);
	addEdge(graph,"Ferit","Dundar",6,4);
	addEdge(graph,"Ferit","Gamze",6,5);
	addEdge(graph,"Ferit","Halit",6,7);
	addEdge(graph,"Halit","Gamze",7,5);
	addEdge(graph,"Halit","Ferit",7,6);
	addEdge(graph,"Halit","Ilke",7,8);
	addEdge(graph,"Ilke","Halit",8,7);
	addEdge(graph,"Ilke","Jale",8,9);
	addEdge(graph,"Jale","Ilke",9,8);
	
	
	printf("Adjacency matrix:\n\n");
     printMatrix(graph);
     printf("\n\n");
     Centrality(graph);
     printf("\n");
  
   int v = 0;
   printf("Source | Target\t |Intermediate Nodes|\tPath");
   printf("\n---------------------------------------------------\n");
   while(v < graph->numVertices){
   
   	dijkstra(graph,v,1);
   	v++;
   }
   
   
 
    return 0;
}

node* createNode(char name[50],int vertex)
{
    
    node* newNode = (node*) malloc(sizeof(node));
    memcpy(newNode->name, name, sizeof newNode->name);
    newNode->weight = 1;
	newNode->next = NULL;
	newNode->vertex = vertex;
	 return newNode;
}
 

Graph* createGraph(int vertices)
{
    Graph* graph = malloc(sizeof(struct Graph));
    graph->numVertices = vertices;
 
    graph->adjLists = malloc(vertices * sizeof(struct node*));
    graph->visited = malloc(vertices * sizeof(int));
    
 
    int i;
    for (i = 0; i < vertices; i++) {
        graph->adjLists[i] = NULL;
        graph->visited[i] = 0;
    }
 
    return graph;
}
 
void addEdge(Graph* graph,char src[50],char dest[50],int vertex1,int vertex2)
{
	node *desti =createNode(dest,vertex2);

if(graph->adjLists[vertex1] == NULL){
	
	source = createNode(src,vertex1);
    graph->adjLists[vertex1]=source;
    temp = graph->adjLists[vertex1];
    graph->adjLists[vertex1]->next = desti;
    temp = desti;
    
}
	else{	
		temp->next = desti;
		temp = temp->next;
	
}
	
   
}


int search(node* temp,node* head){
	while(temp != NULL){
		
	if(strcmp(temp->name,head->name) == 0){
	
		return 1;
	}

	temp = temp->next;
}
	
}

void printMatrix(Graph* graph){
	
	 int a,b,c;
    for(a = 0; a < graph->numVertices; a++){
    	if(a == 0){
    		printf("\t   %s  ",graph->adjLists[a]);
		}
		else if(a == 3){
			printf("   %s ",graph->adjLists[a]);
		}
		else{
		printf("  %s ",graph->adjLists[a]);	
		}
    	
	}
	printf("\n-----------------------------------------------------------------------------------------");
	printf("\n");
	for(b = 0; b < graph->numVertices; b++){
		node* temp = graph->adjLists[b];
	
		
		printf("%s\t|",graph->adjLists[b]);
		for(c = 0; c < graph->numVertices; c++){
		
		if(search(temp->next,graph->adjLists[c]) == 1){
			
			printf("   %d\t|",1);
		}
		else{
			
			printf("   %d\t|",0);
		}
	}
printf("\n-----------------------------------------------------------------------------------------");
printf("\n");
}
		
}



int dijkstra( Graph* graph,int startnode,int betweeness)
{
	
	int interNode[50] = {11};
	int Path[50] = {11};
	int PathPrev[50] = {0};
	int distanceT = 0;
	int distance[10],pred[10];
	int visited[10],count,distanceM,next;
	
	node *p;
	int i;
	for(i=0;i<graph->numVertices;i++)
	   {
		distance[i]=INFINITY;
		pred[i]=startnode;visited[i]=0;
	   }
	distance[startnode]=0;
	count=0;
	while(count<graph->numVertices-1)
	   {
		distanceM=INFINITY ;
// nextnode is the node at minimum distance
		for(i=0;i<graph->numVertices;i++){
		if(distance[i] < distanceM && !visited[i])
			    {
				distanceM=distance[i];
				next=i;
			    }
		}	
//check if a better path exist through nextnode
		visited[next]=1;
		for(p=graph->adjLists[next];p!=NULL;p=p->next){
		if(!visited[p->vertex])
				if(distanceM+p->weight<distance[p->vertex])
				    {
					distance[p->vertex]=distanceM+p->weight;
					pred[p->vertex]=next;
				    }
				}    
		count++;
	   }

 //print the path and distance of each node

 int a = 0;
 int b = 0;
 int j;
	for(i=0;i<graph->numVertices;i++)
		if(i!=startnode)
		   {
		   	distanceT += distance[i];
		   
			   Path[a] = i+1;
			    //printf("\n Distance of %d = %d ",i,distance[i]);
			//printf("       Path = %d ",Path[a]);
			   j=i;
			
			do{
			
			     a++;
			   	j=pred[j];
			
			   		Path[a] = j + 1;
				
			   	
			   		//printf("<- %d ",Path[a]);
			   	if(j != startnode && j != i){
					interNode[b] = j+1;
					if(i  > startnode){
						betweenNode[j]++;
					}
					
					b++;
				}
				else{
					interNode[b] = 11;
				}
			
		}while(j!=startnode);
		
	if(betweeness == 1){
		
	if(Path[0] > startnode+1){
		
		printf("%-7s| %-8s|",graph->adjLists[startnode],graph->adjLists[Path[0]-1]);
		
		int s = 0;
	if(interNode[s] == 11 ){
			printf("%c",'-');
	}
	int lent = 0;
	
	while(s < b){
	
		if(s == b-1){
			
			printf("%s",graph->adjLists[interNode[s-1]]->name);
			lent += strlen(graph->adjLists[interNode[s-1]]->name);
			
		}
		else{
			printf("%s,",graph->adjLists[interNode[s-1]]->name);
			lent += strlen(graph->adjLists[interNode[s-1]]->name);			
		}
		
		s++;
	}

	int m;
	for(m = 0; m < lent; m++){
		printf(" ");
	}
	if(s==0){
		printf("\t\t\t");
		
	}else if(s==1){
		printf("\t\t");
		
	}else if(s==2){
		printf("\t");

	}

	else {
		printf(" ");
		
	}
	
	int l = a;
	while(l >= 0){
	if(l == 0){
		printf("%s",graph->adjLists[Path[l]-1]);
	}
	else{
			printf("%s%s",graph->adjLists[Path[l]-1],"->");
	}

	
		l--;
	
	}
	   
	
	printf("\n------------------------------------------------------------\n");
	}
		   
	b = 0;
	a = 0;	
		   }
	
}
return distanceT;
	
}

void Centrality(Graph *graph){
	int score = 0;
	int b,c;
	int interPath[10] = {11};
	int k;
	int score2 = 0;
	int score3 = 0;
	printf("Node\t|Degree Centrality\t|Closeness Centrality\t|Betweeness Centrality\n");
	printf("------------------------------------------------------------------------------\n");
	for(b = 0; b < graph->numVertices; b++){
		node* temp = graph->adjLists[b];
		while(temp != NULL){
			score++;
				temp = temp->next;
				
			}
			printf("%s\t|\t%d/%d\t",graph->adjLists[b],score-1,(graph->numVertices)-1);
			score2 = dijkstra(graph,b,0);
		    printf("\t|\t%d/%d\t\t|\t",graph->numVertices-1,score2);
		    
		    score3 = betweenNode[b];
		if(score3 == 0){
			printf("%d\n",0);
			printf("------------------------------------------------------------------------------\n");
		}
		else{
			printf("%d/%d\n",score3,((graph->numVertices-1)*(graph->numVertices-2)/2)*((graph->numVertices-1)*(graph->numVertices-2)/2));
			printf("------------------------------------------------------------------------------\n");
		}
			score = 0;
		
	}
}





