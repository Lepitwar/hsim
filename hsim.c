/* name:               Lane Scobie   Dylan Waters
 * ONE Card number:    1448158       1343144
 * Unix id:            scobie        dwaters
 *
 */
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>

#define LINE_LEN 257
int graph[26];
int distance [51];
char singleline[LINE_LEN];
int GlobalCNT= 0;
int internalCNT=0;
int size = 0;
char temp[52];
char temp2[4];
int temp3;
int dia=25;//Diameter of the graph, currently unknown

struct node {
  int pos;
  int neighbours[26];
  int distance[51];
  int via[51];
};
void LinkState(struct node * nodes,FILE* fp);
void notDistanceVector(struct node * nodes,FILE* fp);
void DistanceVector(struct node * nodes,FILE* fp);
void HotPotato(struct node * nodes,FILE* fp);
void HotPot2(struct node * nodes,FILE* fp);


int main(int argc, char* argv[]){
  int j;
  FILE * fpointer;
  struct node * nodes;
  struct node * nodes1;
  struct node * nodes2;
  struct node * nodes3;
  srand(time(NULL));
  //double randoms = ( (double)rand()/(double)RAND_MAX  );
  //~~~~~~~~~~~~~~~~~~~~~~~WRITING DATA~~~~~~~~~~~~~~~~~~~~~~~
  FILE * fp;
  fp=fopen("hsimData.txt","a+");
  //~~~~~~~~~~~~~~~~~~~~~~~WRITING DATA~~~~~~~~~~~~~~~~~~~~~~~
  fpointer = fopen(argv[1],"r");
  if (fpointer==NULL){
    fprintf(stderr, "ESIM line:0 error\n");
    return 0;
  }
  //printf("Input file: %s\n",argv[1]);
  fprintf(fp,"\n\n%s\n",argv[1]);
  //~~~~~~~~~~MALLOCING SPACE~~~~~~~~~~~~~~~~~``
  nodes=(struct node*)malloc(25* sizeof(struct node));
  nodes1=(struct node*)malloc(25* sizeof(struct node));
  nodes2=(struct node*)malloc(25* sizeof(struct node));
  nodes3=(struct node*)malloc(25* sizeof(struct node));
  for(int i=0; i<25;i++){
    memset(nodes[i].neighbours,-1,sizeof(nodes[i].neighbours ));
    memset(nodes1[i].neighbours,-1,sizeof(nodes[i].neighbours ));
    memset(nodes2[i].neighbours,-1,sizeof(nodes[i].neighbours ));
    memset(nodes3[i].neighbours,-1,sizeof(nodes[i].neighbours ));
  }
  //~~~~~~~~~~~~~~~~END-O-MALLOC~~~~~~~~~~~~
  //~~~~~~~~~~~Start of reading text file~~~
  while(fgets(singleline,LINE_LEN,fpointer)!=NULL) {
    char * pointer = singleline;
    while (isblank(*pointer)){
      pointer++;//to ignore blank areas
    }
    if (GlobalCNT==0){
      size = atoi(singleline);
      //printf("node network of %d\n",size);
      for(int i = 0;i<size;i++){
	distance[i*2]=i;
	distance[i*2+1]=99999;
      }
    }else{
      strcpy(temp,singleline);
      j = 0;
      for(int i = 0;i<strlen(temp);i++){
	internalCNT=0;
        while(!isblank(temp[i])){
	  temp2[internalCNT]=temp[i];
	  i++;
	  internalCNT++;
	}
	temp3=atoi(temp2);
	nodes[GlobalCNT-1].neighbours[j]=temp3;
	nodes1[GlobalCNT-1].neighbours[j]=temp3;
	nodes2[GlobalCNT-1].neighbours[j]=temp3;
	nodes3[GlobalCNT-1].neighbours[j]=temp3;
	temp2[1]='\0';
	j++;
      }
      nodes[GlobalCNT-1].pos=GlobalCNT-1;
      nodes1[GlobalCNT-1].pos=GlobalCNT-1;
      nodes2[GlobalCNT-1].pos=GlobalCNT-1;
      nodes3[GlobalCNT-1].pos=GlobalCNT-1;
    }
    GlobalCNT++;
  }
  //~~~~~~~~END-o-TEXT-FILE~~~~~~~~~~~~~~~~
  //Setting up distance charts
 for(int i = 0;i<size;i++){
   for(j=0;j<size;j++ ){
     //DISTANCE
     nodes[i].distance[2*j]=j;
     nodes[i].via[2*j]=j;
     //Link State
     nodes1[i].distance[2*j]=j;
     nodes1[i].via[2*j]=j;
     //Hot pot 1
     nodes2[i].distance[2*j]=j;
     nodes2[i].via[2*j]=j;
     //Hot Pot 2
     nodes3[i].distance[2*j]=j;
     nodes3[i].via[2*j]=j;

     if(i==j){
       //DISTANCE
       nodes[i].distance[2*j+1]=0;
       nodes[i].via[2*j+1]=i;
       //Link State
       nodes1[i].distance[2*j+1]=0;
       nodes1[i].via[2*j+1]=i;
       //Hot Pot 1
       nodes2[i].distance[2*j+1]=0;
       nodes2[i].via[2*j+1]=i;
       //Hot Pot 2
       nodes3[i].distance[2*j+1]=0;
       nodes3[i].via[2*j+1]=i;
     }else{
       //DISTANCE
       nodes[i].distance[2*j+1]=9999;
       nodes[i].via[2*j+1]=-1;
       //Link State
       nodes1[i].distance[2*j+1]=9999;
       nodes1[i].via[2*j+1]=-1;
       //Hot Pot 1
       nodes2[i].distance[2*j+1]=9999;
       nodes2[i].via[2*j+1]=-1;
       //Hot pot 2
       nodes3[i].distance[2*j+1]=9999;
       nodes3[i].via[2*j+1]=-1;
     }
   }
 }
 //rabble^^^^^^^^^^
 // finding neighbours
 for(int i = 0;i<size;i++){
   for(j=0;j<26;j++ ){
     //Distance
     if(nodes[i].neighbours[j]!=-1){
       nodes[i].distance[2*nodes[i].neighbours[j]+1]=1;
       nodes[i].via[2*nodes[i].neighbours[j]+1]=nodes[i].neighbours[j];
     }
     //Link State
     if(nodes1[i].neighbours[j]!=-1){
       nodes1[i].distance[2*nodes[i].neighbours[j]+1]=1;
       nodes1[i].via[2*nodes[i].neighbours[j]+1]=nodes[i].neighbours[j];
     }
     //Hot pot 1
     if(nodes2[i].neighbours[j]!=-1){
       //nodes[i]2.distance[2*nodes[i].neighbours[j]+1]=1;
       //nodes[i]2.via[2*nodes[i].neighbours[j]+1]=nodes[i].neighbours[j];
     }
     //Hot Pot 2
     if(nodes3[i].neighbours[j]!=-1){
       nodes3[i].distance[2*nodes[i].neighbours[j]+1]=1;
       nodes3[i].via[2*nodes[i].neighbours[j]+1]=nodes[i].neighbours[j];
     }
   }
 }
 int totalDegree=0;
 //Printing out distance chart
 for(int i =0;i<size;i++){   
   //printf("\nnode:%d: ",i);
   for(j=0;j<size;j++){
     if(nodes[i].neighbours[j]!=-1){
       totalDegree++;
     }
   }
 }
 //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 //OutPUT
 printf("\n%d average degree if the network\n",totalDegree/(size));
 fprintf(fp,"%d\n",totalDegree/(size));
 LinkState(nodes1,fp);
 notDistanceVector(nodes,fp);
 DistanceVector(nodes,fp);
 HotPotato(nodes2,fp);
 HotPot2(nodes3,fp);
 //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 free(nodes);
 free(nodes1);
 free(nodes2);
 free(nodes3);
 fclose(fpointer);
 fclose(fp);
} 

void LinkState(struct node * nodes,FILE* fp){
  //Flood
  printf("Link State: ");
 int tx= 0;
  int AdjNodes=0; 
  int currentnode;
  
  //int x;
  //int y;
  for(int x=0; x<size;x++)
    nodes[x].neighbours[size-1]=-1;

  for(int i=0; i<size; i++)
    {	  
      currentnode=i;      
      //Counting Adj Nodes
      AdjNodes=0;
      for(int scan =0;scan<size;scan++)
	{
	  if(nodes[currentnode].neighbours[scan]!=-1)
	    {
	      AdjNodes+=1;
	      //printf("%d ", nodes[currentnode].neighbours[scan]);
	    }
	}
      //printf("\n");
      tx+= AdjNodes;
      //printf("SRC: %d Nodes: %d\n", i,AdjNodes);

      for(int j = 0; j<size;j++)
	{
	  if(i!=j)
	    {
	      currentnode=j;      
	 
	      //Counting Adj Nodes
	      AdjNodes=0;
	      for(int scan =0;scan<size;scan++)
		{
		  if(nodes[currentnode].neighbours[scan]!=-1)
		    AdjNodes+=1;
		}
	      tx+= AdjNodes-1;
	      //printf("tx: %d\n", tx);

	    }
	}
    }
  int totalPL=0;
  int pairs=0;
  for(int i =0;i<size;i++){   
    for(int j=0;j<size;j++){
      totalPL+=nodes[i].distance[2*j+1];
      pairs++;
    }
    pairs--;
  }  
  printf("%d, ",tx/size);
  fprintf(fp,"linkstate\n");
  fprintf(fp,"%d\n",tx/size);
}
void notDistanceVector(struct node * nodes,FILE* fp){
 int nextnode;
  int changes=0;
  int tx=0;

  int biggest=0;
  //Periodically Sharing
  //printf("\nDistance Vector\n");
  for(int k=0;k<26;k++){
    changes=0;
    tx=0;
    //printf("Looped %d times\n",k);
    for(int i = 0; i<size; i++){
      //printf("\n\nWE ARE CURRENTLY ON NODE %d",i);
      for(int j = 0; j<size;j++){
	if(nodes[i].neighbours[j]!=-1){//checking the next node
	  nextnode=nodes[i].neighbours[j];
	  //printf("\nCurrent Neighbour:%d Distance Vectors\n",nextnode);
	  tx++;
	  //giving nextnode all the other neighbours
	  for(int q = 0; q<size;q++){
	    /*
	    printf("\n");
	    printf("%d=",nodes[nextnode].distance[2*q]);
	    printf("%d ",nodes[nextnode].distance[2*q+1]);
	    printf("Parent Node->");
	    printf("%d=",nodes[i].distance[2*q]);
	    printf("%d ",nodes[i].distance[2*q+1]);
	    */
	    if(nodes[i].distance[2*q+1]<nodes[nextnode].distance[2*q+1]-1){
	      // printf("Update Will occur");
	      changes=1;
	      nodes[nextnode].distance[2*q+1]=nodes[i].distance[2*q+1]+1;
	      //printf("%d=",nodes[nextnode].distance[2*q]);
	      //printf("%d ",nodes[nextnode].distance[2*q+1]);
	    }
	  }
	}
      }
    }
    if(!changes){
      for(int i =0;i<size;i++){   
	for(int j=0;j<size;j++){
	  if(biggest<nodes[i].distance[2*j+1]){
	    biggest=nodes[i].distance[2*j+1];
	    dia=nodes[i].distance[2*j+1];
	  }
	}
      }
      tx--;
      k=26;
    }
  }
  int totalPL=0;
  int pairs=0;
  for(int i =0;i<size;i++){   
    for(int j=0;j<size;j++){
      totalPL+=nodes[i].distance[2*j+1];
      pairs++;
    }
    pairs--;
  }  
  /*
  fprintf(fp,"Distance\n");
  //printf("A total of %d tx occurs\n",tx*dia);
  printf("Avg tx: %d\n",tx*dia/size);
  fprintf(fp,"%d\n",tx*dia/size);
  //printf("Diameter is %d\n",dia);
  //printf("Total hops %d\n",totalPL);
  */
  printf("%d\n",totalPL/pairs);
  fprintf(fp,"%d\n",totalPL/pairs);
  // printf("End of distance \n\n");
}



void DistanceVector(struct node * nodes,FILE* fp){
  int nextnode;
  int changes=0;
  int tx=0;

  int biggest=0;
  //Periodically Sharing
  printf("Distance Vector: ");
  for(int k=0;k<26;k++){
    changes=0;
    tx=0;
    //printf("Looped %d times\n",k);
    for(int i = 0; i<size; i++){
      //printf("\n\nWE ARE CURRENTLY ON NODE %d",i);
      for(int j = 0; j<size;j++){
	if(nodes[i].neighbours[j]!=-1){//checking the next node
	  nextnode=nodes[i].neighbours[j];
	  //printf("\nCurrent Neighbour:%d Distance Vectors\n",nextnode);
	  tx++;
	  //giving nextnode all the other neighbours
	  for(int q = 0; q<size;q++){
	    /*
	    printf("\n");
	    printf("%d=",nodes[nextnode].distance[2*q]);
	    printf("%d ",nodes[nextnode].distance[2*q+1]);
	    printf("Parent Node->");
	    printf("%d=",nodes[i].distance[2*q]);
	    printf("%d ",nodes[i].distance[2*q+1]);
	    */
	    if(nodes[i].distance[2*q+1]<nodes[nextnode].distance[2*q+1]-1){
	      // printf("Update Will occur");
	      changes=1;
	      nodes[nextnode].distance[2*q+1]=nodes[i].distance[2*q+1]+1;
	      //printf("%d=",nodes[nextnode].distance[2*q]);
	      //printf("%d ",nodes[nextnode].distance[2*q+1]);
	    }
	  }
	}
      }
    }
    if(!changes){
      for(int i =0;i<size;i++){   
	for(int j=0;j<size;j++){
	  if(biggest<nodes[i].distance[2*j+1]){
	    biggest=nodes[i].distance[2*j+1];
	    dia=nodes[i].distance[2*j+1];
	  }
	}
      }
      tx--;
      k=26;
    }
  }
  int totalPL=0;
  int pairs=0;
  for(int i =0;i<size;i++){   
    for(int j=0;j<size;j++){
      totalPL+=nodes[i].distance[2*j+1];
      pairs++;
    }
    pairs--;
  }  
  fprintf(fp,"Distance\n");
  //printf("A total of %d tx occurs\n",tx*dia);
  printf("%d,",tx*dia/size);
  fprintf(fp,"%d\n",tx*dia/size);
  //printf("Diameter is %d\n",dia);
  //printf("Total hops %d\n",totalPL);
  printf(" %d\n",totalPL/pairs);
  fprintf(fp,"%d\n",totalPL/pairs);
  // printf("End of distance \n\n");
}


void HotPotato(struct node * nodes,FILE* fp ){
  //random
  int currentnode;
  int notfound=1;
  int parentnode;
  int nextnode;
  int targetnode;
  int PathLen=0;
  int path[1000];
  int Speedcount;
  int AdjNodes=0;
  int totaltx=0;
  int OverAlltx=0;
  int OverAllpl=0;
  int listTX[10];
  double listPL[10];
  srand(time(NULL));
  int random = rand()%size;
  printf("Hot Potato I: ");
  for(int k=0;k<10;k++){
    totaltx=0;
    for(int i =0; i<size;i++){
      //printf("\nWE ARE CURRENTLY ON NODE %d\n",i);
      AdjNodes=0;
      for(int j = 0; j<size;j++){
	currentnode=i;
	targetnode=j;
	parentnode=-1;
	//printf("\n\nTarget~%d: ",targetnode);
	notfound=1;
	PathLen=0;
	path[0]=currentnode;
	while(notfound){
	  //Counting Adj Nodes
	  AdjNodes=0;
	  for(int scan =0;scan<size;scan++){
	    if(nodes[currentnode].neighbours[scan]!=-1){
	      AdjNodes+=1;
	    }
	  }
	  //printf("we are on Node %d and have %d adj nodes \n",currentnode,AdjNodes);
	  if(currentnode==targetnode){
	    //printf("\nNode Found!  in %d hops!\n",PathLen);
	    Speedcount=-1;
	    for(int scan =0;scan<=PathLen;scan++){
	      //printf("%d ",path[scan]);
	      Speedcount++;
	      for(int q =scan+1;q<=PathLen;q++){
		if(path[q]==path[scan]){
		  scan=q;
		}
	      }
	      //printf("Short hop is %d",Speedcount);
	    }

	    //printf("\nShort hop from %d to %d is %d",i,targetnode,Speedcount);
	    nodes[i].distance[2*targetnode+1]=Speedcount;
	    //printf(" with a total tx of %d",PathLen+Speedcount);
	    totaltx+=PathLen+Speedcount;
	    notfound=0;
	  }else{
	    //AdjNodes=2;
	    random = rand()%AdjNodes;
	    nextnode=nodes[currentnode].neighbours[random];
	    if(nextnode!=parentnode){
	      //printf(" %d",nextnode);
	      parentnode= currentnode;
	      currentnode=nextnode;
	      PathLen++;
	      path[PathLen]=currentnode;
	    }else if(AdjNodes==1){
	      //printf(" ~%d",nextnode);
	      parentnode= currentnode;
	      currentnode=nextnode;
	      PathLen++;
	      path[PathLen]=currentnode;
	    }
	    if(currentnode>=size){
	      currentnode=0;
	    }
	  }
	}
      }
    } 
    int totalPL=0;
    int pairs=0;
    for(int i =0;i<size;i++){   
      for(int j=0;j<size;j++){
	totalPL+=nodes[i].distance[2*j+1];
	pairs++;
      }
      pairs--;
    } 
    //printf("Total hops %d\n",totalPL);
    //printf("Average path length %d\n",totalPL/pairs);
    //printf("Total tx sent: %d\n",totaltx); 
    listTX[k]=totaltx;
    listPL[k]=totalPL/pairs;
    //printf("paris: %d ",pairs);
    //printf("%lf\n", listPL[k]);
    OverAlltx+=totaltx;
    OverAllpl+=totalPL/pairs;
  }
  double STDev;
  double STDev2;
  double tempV;
  double tempV2;
  double C1;
  double C2;
  double C22;
  double C12;
  for(int k=0; k<10;k++){
    tempV=listTX[k]/size- (OverAlltx/(size*10));
    tempV2=listPL[k]- (OverAllpl/10);
    STDev+= pow( tempV, 2) ;
    STDev2+= pow( tempV2, 2) ;
    //printf("loop %lf \n",tempV2);

  }
  STDev=STDev/10;
  STDev2=STDev2/10;
  STDev=pow(STDev,0.5 );
  STDev2=pow(STDev2,0.5 );

  C2 = (OverAlltx/(size*10) )-(2.262*STDev/pow(10,0.5));
  C1 = ( OverAlltx/(size*10))+(2.262*STDev/pow(10,0.5));
  C22 = (OverAllpl/10 )-(2.262*STDev2/pow(10,0.5));
  C12 = (OverAllpl/10)+(2.262*STDev2/pow(10,0.5));


  //printf("%lf \n",STDev2);
  //printf("%lf \n",pow(STDev2,0.5 ));
  //printf("%lf \n", (2.262*STDev2/pow(10,0.5)));

  fprintf(fp,"Hot Potato\n");
  fprintf(fp,"%d %lf %lf\n",OverAlltx/(size*10),C2,C1);
  fprintf(fp,"%d %lf %lf\n",OverAllpl/10,C22,C12);

  printf("%d {%lf, %lf}",OverAlltx/(size*10),C2,C1);
  printf(",%d {%lf, %lf}\n",OverAllpl/10,C22,C12);
}

void HotPot2(struct node * nodes,FILE* fp ){
  //random but with knowledge of neighbours
  //printf("Hot Potato 2: electric boogaloo\n");//random
  printf("Hot Potato II: ");//random

  int currentnode;
  int notfound=1;
  int parentnode;
  int nextnode;
  int targetnode;
  int PathLen=0;
  int path[1000];
  int Speedcount;
  int AdjNodes=0;
  int totaltx=0;
  int OverAlltx=0;
  int OverAllpl=0;
  int listTX[10];
  double listPL[10];
  srand(time(NULL));
  int random = rand()%size;
  for(int k=0;k<10;k++){
    totaltx=0;
    for(int i =0; i<size;i++){
      //printf("\nWE ARE CURRENTLY ON NODE %d\n",i);
      AdjNodes=0;
      for(int j = 0; j<size;j++){
	currentnode=i;
	targetnode=j;
	parentnode=-1;
	//printf("\n\nTarget~%d: ",targetnode);
	notfound=1;
	PathLen=0;
	path[0]=currentnode;
	while(notfound){
	  //Counting Adj Nodes
	  AdjNodes=0;
	  for(int scan =0;scan<size;scan++){
	    if(nodes[currentnode].neighbours[scan]!=-1){
	      AdjNodes+=1;
	      if(nodes[currentnode].neighbours[scan]==targetnode){
		PathLen++;
		currentnode=targetnode;
		path[PathLen]=currentnode;
	      }
	    }
	  }
	  if(currentnode==targetnode){
	    Speedcount=-1;
	    for(int scan =0;scan<=PathLen;scan++){
	      Speedcount++;
	      for(int q =scan+1;q<=PathLen;q++){
		if(path[q]==path[scan]){
		  scan=q;
		}
	      }
	    }
	    nodes[i].distance[2*targetnode+1]=Speedcount;;
	    totaltx+=PathLen+Speedcount;
	    notfound=0;
	  }else{
	    //AdjNodes=2;
	    random = rand()%AdjNodes;
	    nextnode=nodes[currentnode].neighbours[random];
	    if(nextnode!=parentnode){
	      //printf(" %d",nextnode);
	      parentnode= currentnode;
	      currentnode=nextnode;
	      PathLen++;
	      path[PathLen]=currentnode;
	    }else if(AdjNodes==1){
	      //printf(" ~%d",nextnode);
	      parentnode= currentnode;
	      currentnode=nextnode;
	      PathLen++;
	      path[PathLen]=currentnode;
	    }
	    if(currentnode>=size){
	      currentnode=0;
	    }
	  }
	}
      }
    } 
    int totalPL=0;
    int pairs=0;
    for(int i =0;i<size;i++){   
      for(int j=0;j<size;j++){
	totalPL+=nodes[i].distance[2*j+1];
	pairs++;
      }
      pairs--;
    } 
    //printf("Total hops %d\n",totalPL);
    //printf("Average path length %d\n",totalPL/pairs);
    //printf("Total tx sent: %d\n",totaltx); 
    listTX[k]=totaltx;
    listPL[k]=totalPL/pairs;
    OverAlltx+=totaltx;
    OverAllpl+=totalPL/pairs;
  }
  double STDev;
  double STDev2;
  double tempV;
  double tempV2;
  double C1;
  double C2;
  double C22;
  double C12;
  for(int k=0; k<10;k++){
    tempV=listTX[k]/size- (OverAlltx/(size*10));
    tempV2=listPL[k]- (OverAllpl/10);
    STDev+= pow( tempV, 2) ;
    STDev2+= pow( tempV2, 2) ;
  }
  STDev=STDev/10;
  STDev2=STDev2/10;
  STDev=pow(STDev,0.5 );
  STDev2=pow(STDev2,0.5 );

  C2 = (OverAlltx/(size*10) )-(2.262*STDev/pow(10,0.5));
  C1 = ( OverAlltx/(size*10))+(2.262*STDev/pow(10,0.5));
  C22 = (OverAllpl/10 )-(2.262*STDev2/pow(10,0.5));
  C12 = (OverAllpl/10)+(2.262*STDev2/pow(10,0.5));


  fprintf(fp,"Hot Potato2\n");
  fprintf(fp,"%d %lf %lf\n",OverAlltx/(size*10),C2,C1);
  fprintf(fp,"%d %lf %lf\n",OverAllpl/10,C22,C12);

  printf("%d {%lf, %lf}",OverAlltx/(size*10),C2,C1);
  printf(", %d {%lf, %lf}\n \n",OverAllpl/10,C22,C12);
  //printf("END OF the eletric boogaloo\n");
}
