#include <stdlib.h>
#include <stdio.h>

#define PRENUM 2013000000
#define OFFSET 48577
int main(int argc,char* argv[])
{
	int i;
	int countNo;
	int digitSize;
	int bucketSize;
	int value;
	FILE* fp;
	if(argc!=4)
	{
		printf("Usage: <func><digitSize><countNo><bucketSize>\n");
		return 0;
	}

	fp=fopen("random.txt","wb+");

	digitSize=atoi(argv[1]);
	countNo=atoi(argv[2]);
	bucketSize=atoi(argv[3]);
	srandom(time(NULL));
	
	fprintf(fp,"DIGITSIZE=%d\n",digitSize);
	fprintf(fp,"COUNTNO=%d\n",countNo);
	fprintf(fp,"BUCKETSIZE=%d\n",bucketSize);
	fprintf(fp,"\n");


	for(i=0;i<countNo;i++)
	{
		value=random();
		value=value>>11;
		value-=OFFSET;
		if(value<0)
			value=-value;
		value+=PRENUM;
		fprintf(fp,"%d\n",value);
	}
	
	fclose(fp);
	return 1;
}
