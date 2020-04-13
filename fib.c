#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

int n;
int *fibseq;
int i;
int j;
pthread_mutex_t lock;

void *calc(void *arg);

int main(int argc, char *argv[])
{
	if (argc != 2)
	{
		printf("Argument format is incorrect\n");
		return -1;
	}

	if (atoi(argv[1]) < 1)
	{
		printf("input (%d) must be > 0\n", atoi(argv[1]));
		return -1;
	}

	n = atoi(argv[1]);

	fibseq = (int *)malloc(n * sizeof(int));

	pthread_t *threads = (pthread_t *)malloc(n * sizeof(pthread_t));

	for(i = 0; i < n; i++)
	{
		pthread_create(&threads[i], NULL, calc, NULL);
		pthread_join(threads[i], NULL);
	}

	for(j = 0; j < n; j++)
	{
		printf("%d ", fibseq[j]);
	}
	printf("\n");
	return 0;
}

void *calc(void *arg)
{
	pthread_mutex_lock(&lock);
	if(i == 0)
	{
		fibseq[i] = 0;
		pthread_mutex_unlock(&lock);
		pthread_exit(0);
	}
	if(i == 1)
	{
		fibseq[i] = 1;
		pthread_mutex_unlock(&lock);
		pthread_exit(0);
	}
	else
	{
		fibseq[i] = fibseq[i-1] + fibseq[i-2];
		pthread_mutex_unlock(&lock);
		pthread_exit(0);
	}
}
