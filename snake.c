#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>

#define W 50
#define H 20


static struct termios old, current;

typedef struct obj{
  int x;
  int y;
   
  int xs;
  int ys;
  
  int body[100][2];	
  int head;
  int n;
  
  
} SNAKE;


typedef struct point{
  int x;
  int y;
  
} APPLE;






void CreateTable(char***,int,int);
void fillmap(char **map,int h,int w);
void makeBox(char **t,int,int);
void Acceleration(struct obj *point);
void delay(int msec);
void keyInput(struct obj *point);
void clear_steps(struct obj *snake,char **t);
void isInEdge(struct obj *snake,char *f);
void generateApple(APPLE *ap,int h,int w);
void isEatApple(SNAKE *snake,APPLE *ap,int h,int w);
void isCollide(SNAKE *snake,char *f);
int kbhit(void);



void initTermios(int echo);
void resetTermios(void) ;

char getch_(int echo);
char getch(void);
char getche(void);

int main(){
	char **t;
	int h=H,w=W;
	char flag = 1;
	SNAKE snake;
	APPLE  apple;
	srand(time(NULL));

	
	//create snake
	  snake.y = 10;
	  snake.x = 10;
	  snake.xs = 1;
	  snake.ys = 0; 
          snake.head = 0;
          snake.n = 4; 
      
        //create apple
	  apple.x = 15;
	  apple.y = 15;   
   	 
	//create map
	  CreateTable(&t,h,w);
	  fillmap(t,h,w);
	
	
//game main loop
	
while(flag){	
		
	t[snake.y][snake.x] = '*';
	t[apple.y][apple.x] = '@';
	
    
	snake.body[snake.head][0] = snake.y;
	snake.body[snake.head][1] = snake.x;
		
	makeBox(t,h,w);
	
	
	
	Acceleration(&snake);
	clear_steps(&snake,t);

	
    
   	isInEdge(&snake,&flag);
    
        isEatApple(&snake,&apple,h,w);
    
        isCollide(&snake,&flag);

        keyInput(&snake);
        keyInput(&snake);

	delay(90000);

	system("clear");	
	
}
    system("clear");
    printf("YOU LOSE\n");
    free(t);
	
    delay(1500);
    return 0;
}




void CreateTable(char ***table,int h,int w){
	int i;
	*table = (char**)malloc(h*sizeof(char*));
	
	for(i=0;i<h;i++){
	  *(*table+i) = (char*)malloc(w*sizeof(char));
	}	
	
	
	
}


void fillmap(char **map,int h,int w){
	int i,j;
	for(i =0;i<h;i++){
	   for(j =0;j<w;j++)
	     map[i][j] = ' ';
	}
	
	
}



void makeBox(char **t,int y,int x){
	int i,j;

	
    for(i=0;i<x;i++){printf("*");}

    printf("*\n");


  for(i=0;i<y;i++){
    	printf("*");
   for(j=0;j<x;j++){
      printf("%c",t[i][j]);
      
   }
   printf("*\n");
 }



for(i=0;i<x;i++){printf("*");}

	
	
}



void Acceleration(struct obj *point){
	
	(*(point)).x+=(*(point)).xs;
	(*(point)).y+=(*(point)).ys;
	
	point->head+=1;
	
}


void keyInput(struct obj *point){


  if (kbhit()){ 
	  switch(getche()){
	        case 'w':
	  	if(point->ys == 0){
	  		point->ys = -1;
	  		point->xs = 0;
	     }
	  	break;
	  	case 's':
	  	 if(point->ys == 0){
	  		point->ys = 1;
	  		point->xs = 0;
	    	}
	  	break;
	  	case 'a':
	  	  if(point->xs == 0){
	  		point->ys = 0;
	  		point->xs = -1;
	  	  }
	  	break;
	  	case 'd':
	  		if(point->xs ==0){
			  
	  		 point->ys = 0;
	  		 point->xs = 1;
	  	}
	  	break;
	  }
	  
	  }



}






void delay(int msec) 
{ 
    
  
    clock_t stime = clock(); 
  
    while(clock() < stime + msec); 
} 



void clear_steps(struct obj *snake,char **t){
	int i,j;
	
	if(snake->head >= snake->n){
		t[snake->body[snake->head-snake->n][0]][snake->body[snake->head-snake->n][1]]	= ' ';
		
		for(i =0;i<snake->n-1;i++){
		  snake->body[i][0] = snake->body[i+1][0];
		  snake->body[i][1] = snake->body[i+1][1];
		  
		
	    }   
	    snake->body[snake->n-1][0] = snake->body[snake->n][0];
	    snake->body[snake->n-1][1] = snake->body[snake->n][1];
	
		snake->head--;
		
	
	
}
}


void isInEdge(struct obj *snake,char *f){
	
	if(snake->x == W || snake->x == -1 || snake->y == H || snake->y == -1)*f = 0;
	
}


void generateApple(APPLE *ap,int h,int w){
	
	ap->x = rand()%((w-1)-1)+1;
	ap->y = rand()%((h-1)-1)+1;
	
	
	
}

void isEatApple(SNAKE *snake,APPLE *ap,int h,int w){
	
	if(snake->x == ap->x)
	  if(snake->y == ap->y){
	       generateApple(ap,h,w);
		   snake->n++;
	   }
	
}

void isCollide(SNAKE *snake,char *f){
	int i;
	int x = snake->x;
	int y = snake->y;
	
	
	
	for(i=0;i<snake->n-1;i++){
		if(x == snake->body[i][1])
	   	  if(y == snake->body[i][0])
                 *f = 0;		   
		
		
	}
	
	
	
	
}





int kbhit(void)
{
  struct termios oldt, newt;
  int ch;
  int oldf;

  tcgetattr(STDIN_FILENO, &oldt);
  newt = oldt;
  newt.c_lflag &= ~(ICANON | ECHO);
  tcsetattr(STDIN_FILENO, TCSANOW, &newt);
  oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
  fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);

  ch = getchar();

  tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
  fcntl(STDIN_FILENO, F_SETFL, oldf);

  if(ch != EOF)
  {
    ungetc(ch, stdin);
    return 1;
  }

  return 0;
}



/* Initialize new terminal i/o settings */
void initTermios(int echo) 
{
  tcgetattr(0, &old); /* grab old terminal i/o settings */
  current = old; /* make new settings same as old settings */
  current.c_lflag &= ~ICANON; /* disable buffered i/o */
  if (echo) {
      current.c_lflag |= ECHO; /* set echo mode */
  } else {
      current.c_lflag &= ~ECHO; /* set no echo mode */
  }
  tcsetattr(0, TCSANOW, &current); /* use these new terminal i/o settings now */
}

/* Restore old terminal i/o settings */
void resetTermios(void) 
{
  tcsetattr(0, TCSANOW, &old);
}

/* Read 1 character - echo defines echo mode */
char getch_(int echo) 
{
  char ch;
  initTermios(echo);
  ch = getchar();
  resetTermios();
  return ch;
}

/* Read 1 character without echo */
char getch(void) 
{
  return getch_(0);
}

char getche(void) 
{
  return getch_(1);
}
