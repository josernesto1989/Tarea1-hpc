// g++ -pthread program_name.cpp

// CPP Program to multiply two matrix using pthreads 

// #include <bits/stdc++.h> 
#if defined(__APPLE__) && defined(__arm64__)
	#include <iostream>
	#include <vector>
	#include <chrono>   // Useful if you are timing matrix multiplication
#else
	#include <bits/stdc++.h>
#endif

#include <cstdlib>
#include <time.h>
using namespace std; 
  
// maximum size of matrix 
#define MAX 1000

// maximum number of threads 
//#define MAX_THREAD 1
int MAX_THREAD;
int matA[MAX][MAX]; 
int matB[MAX][MAX]; 
int matC[MAX][MAX]; 
//int step_i = 0;
double total_time;
int total_time2;
clock_t start, end1, start2, end2;

//const double CLK_TCK = 1000.0;
using namespace std;
void* multi(void *arg) 
{ 	
	int *core = (int *) arg;
	//cout<<endl<<"core= "<<*core<<endl;
	// Each thread computes 1/MAX_THREAD of matrix multiplication 
	for (int i = *core * MAX / MAX_THREAD; i < (*core+1) * MAX / MAX_THREAD; i++){
	for (int j = 0; j < MAX; j++)  
        	for (int k = 0; k < MAX; k++){  
        		matC[i][j] += matA[i][k] * matB[k][j];
		}
	}
	//cout<<endl;
	pthread_exit(NULL);
} 
  
// Driver Code      
int main(int argc, char *argv[]){
	
	if(argc != 2)
		cout<< "Indique el número de hilos a ejecutar"<<endl;
	else
		MAX_THREAD=atoi(argv[1]);
	
	int id[MAX_THREAD];

	// Generating random values in matA and matB
	for (int i = 0; i < MAX; i++) { 
			for (int j = 0; j < MAX; j++) { 
				matA[i][j] = rand() % 10; 
				matB[i][j] = rand() % 10; 
			} 
	} 
  
	// Displaying matA 
	/*cout << endl << "Matrix A" << endl; 
	for (int i = 0; i < MAX; i++){ 
		for (int j = 0; j < MAX; j++)  
			cout << matA[i][j] << " "; 
		cout << endl; 
	}*/
  
	// Displaying matB 
	/*cout << endl << "Matrix B" << endl; 
	for (int i = 0; i < MAX; i++) { 
		for (int j = 0; j < MAX; j++)  
			cout << matB[i][j] << " ";         
		cout << endl; 
	}*/
  
	// declaring four threads 
	pthread_t threads[MAX_THREAD];
	pthread_attr_t atr;
	int r;

	start = clock();   
	start2 = time(NULL); 
	pthread_attr_init(&atr);
	pthread_attr_setdetachstate(&atr, PTHREAD_CREATE_JOINABLE);
	// Creating four threads, each evaluating its own part 
	for (int i = 0; i < MAX_THREAD; i++) { 
		//int *p;
		id[i]=i;
		r=pthread_create(&threads[i], &atr, multi, (void*)(id+i));
		if (r){
          		printf("Error en la creación del hilo %d, código: %d\n",i,r);
          		exit(-1);
       		}
	}
	
	/*Se libera atr*/
	pthread_attr_destroy(&atr);
	// joining and waiting for all threads to complete 
	for (int i = 0; i < MAX_THREAD; i++){  
		r=pthread_join(threads[i], NULL);
		if (r){
			printf("Error en pthread_join() del hilo %d, codígo: %d\n", i,r);
			exit(-1);
		}
	}
	end2 = time(NULL);
        end1= clock();

	// Displaying the result matrix 
	/*cout << endl << "Multiplication of A and B" << endl; 
	for (int i = 0; i < MAX; i++) { 
		for (int j = 0; j < MAX; j++)  
			cout << matC[i][j] << " ";         
		cout << endl; 
	}*/

        total_time = ((double) (end1 - start))/CLOCKS_PER_SEC;
	total_time2 = (int) (end2-start2);
	
	//Comentar para utilizar ini.sh
	/*cout <<"No. de hilos: "<<MAX_THREAD<<", "<< "Total time clock(): "<< total_time <<"segundos"<< endl;
	cout <<"Total time time(): " << total_time2 << "segundos" << endl;*/

	//Descomentar para utilizar ini.sh
	printf("%.2lf %d\n",total_time,total_time2);

	pthread_exit(NULL);

	//return 0;
}

