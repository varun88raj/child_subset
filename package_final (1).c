#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <string.h>
#include <fcntl.h>
#include <stdbool.h>

char *ip_f_name="input.dat";
char *op_f_name="output.dat";

bool is_subset(int set[],int n,int sum)
{
	if(sum==0)
	{
		return true;
	}
	if(n==0&&sum!=0)
	{
		return false;
	}
	if(set[n-1]>sum)
	{
		return is_subset(set,n-1,sum);
	}
	return is_subset(set,n-1,sum)||is_subset(set,n-1,sum-set[n-1]);
}

void store(int A[],int size,int pid)
{
	char temp[5];
	char msg[50];
	sprintf(msg,"%d",pid);
	strcat(msg," : ");
	for(int i=0;i<size;i++)
	{
		sprintf(temp,"%d",A[i]);
		strcat(msg,temp);
		if(i!=size-1)
		{
			strcat(msg," + ");
		}
	}
	strcat(msg,"\n");
	int fd;
	fd=open(op_f_name,O_WRONLY|O_APPEND|O_CREAT,0644);
	write(fd,msg,strlen(msg));
	close(fd);
}

void subset_sum(int s[],int t[],int s_size,int t_size,int sum,int ite,int const target_sum,int const pid)
{
	if(target_sum==sum)
	{
		store(t,t_size,pid);
		return;
	}
	else
	{
		for(int i=ite;i<s_size;i++)
		{
			t[t_size]=s[i];
			subset_sum(s,t,s_size,t_size+1,sum+s[i],i+1,target_sum,pid);
		}
	}
}

void generate_subset(int s[],int size,int target_sum,int pid)
{
	int *tuplet_vector=(int *)malloc(size*sizeof(int));
	subset_sum(s,tuplet_vector,size,0,0,0,target_sum,pid);
	free(tuplet_vector);
}

void options()
{
	printf("\nUSAGE:logparse -h -i <input_file_name> -o <output_file_name> -t <time_in_seconds>\nARGUMENTS FOR OPTIONS ARE OPTIONAL\n\n");
}

int main(int argc,char *argv[])
{
	int option;
	int time=10;
	while((option=getopt(argc,argv,"hi:o:t:"))!=-1)   //getting arguments if there are any
	{
		switch(option)
		{
			case 'h':
				options();
				break;
			case 'i':
				ip_f_name=optarg;
				break;
			case 'o':
                                op_f_name=optarg;
                                break;
			case 't':
				time=atoi(optarg);
				break;
		}
	}
	int fd,sz,count,offset=1,fd1;
	pid_t pid;
	char *c=(char *) calloc(1, sizeof(char));
	fd=open(ip_f_name, O_RDONLY | O_CREAT);
	sz=read(fd,c,1);				//reading the number of child process to be created
	count=atoi(c);
	close(fd);
	FILE *stream;
	stream=fopen(ip_f_name,"r");
	char *s=NULL;
	size_t length=0;
	ssize_t nread;
	int *sub_arr;
	int len=0;
	alarm(time);
	for(int i=0;i<count+1;i++)
	{
		pid=fork();
		len=0;
		sub_arr=calloc(15,sizeof(int));
		if(pid==0)
		{
			alarm(1);
			int i=0;
			char temp[]="";
			nread=getline(&s,&length,stream);	//reading a line from in each child process
			for(int j=0;j<strlen(s)+1;j++)
			{
				if(s[j]!=' '&&s[j]!='\0')
				{
					strncat(temp,&s[j],1);
				}
				else
				{
					sub_arr[len]=atoi(temp);
					len++;
					strcpy(temp,"");
				}
			}
			if(len!=1)
			{
				int sum=sub_arr[0];
				for(int k=0;k<len-1;k++)
                       		{
                       			sub_arr[k]=sub_arr[k+1];
                       		}
                       		len--;
				if(is_subset(sub_arr,len,sum))			//checking if there is a subset
				{
					generate_subset(sub_arr,len,sum,getpid());	//writing the subset to the output file
				}
				else
				{
					int temp;
					char msg[50];
					temp=getpid();					//writing the error message if there no subset
					sprintf(msg,"%d",temp);
					strcat(msg,":No subset of numbers summed to ");
					temp=sum;
					char *t=calloc(10,sizeof(char));
					sprintf(t,"%d",temp);
					strcat(msg,t);
					strcat(msg,"\n");
					free(t);
					fd1=open(op_f_name,O_WRONLY|O_APPEND|O_CREAT,0644);
					temp=write(fd1,msg,strlen(msg));
					close(fd1);
				}
			}
			free(sub_arr);
			exit(0);
		}
		else if(pid>0)
		{
			wait(NULL);
		}
	}
}
