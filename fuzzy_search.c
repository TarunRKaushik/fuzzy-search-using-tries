#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX 256
#include <time.h>

typedef struct use
{
	char* st;
	int index;
	int n;		//indicates length of suffux array to which the string belongs to
	char* doc_title;
}use;

typedef struct rev
{
	int doc_no;
	int score;
}rev;

use** destroy_and_remake(use** arr_of_suffix_arrs);
int search_str(char* pattern, use* suf_arr, int n);
char* get_text_title(int i,char** heading);
char* search_lcs(char* a,use** arr_of_suf_arr, int g, int* index);
int no_of_occurances(char* pattern, use* suf_arr, int n);

use* create_suf_arr(char* t,char* title)
{
	use* suf_arr=(use*)malloc(sizeof(use)*(strlen(t)));

	int i;
	char* text=t;
	int n=strlen(t);
	for(i=0;i<strlen(t);i++){
		suf_arr[i].n=strlen(t);
		suf_arr[i].st=(char*)malloc(sizeof(char)*(n-i+1));
		strcpy(suf_arr[i].st,text);
		suf_arr[i].doc_title=(char*)malloc(sizeof(char)*(strlen(title)+1));
		strcpy(suf_arr[i].doc_title,title);
		text++;
	//	printf("%d\t%d\n",strlen(text),(n-i));
		suf_arr[i].index=i+1;
	}
	/*
	for(i=0;i<n;i++){
		printf("%d\t%s\n",suf_arr[i].index,suf_arr[i].st);
	}
	*/
	return suf_arr;
	
	//free(suf_arr);
}

int compare_string(char* a, char* b)
{
	
	int m=strlen(a);
	int n=strlen(b);
	int x;
	if(m>n){
		x=n;
	}
	else{
		x=m;
	}
	int i;
	
	for(i=0;i<x;i++){
		if(a[i]<b[i]){return -1;}
		else if(a[i]>b[i]){return 1;}
		else{}
	}
	if(m>n){
		return 1;
	}
	else if(m<n){
		return -1;
	}
	else{
		return 0;
	}
}
int compare_k_string(char* a, char* b)
{
	
	int m=strlen(a);
	int n=strlen(b);
	int x;
	if(m>n){
		x=n;
	}
	else{
		x=m;
	}
	int i;
	
	for(i=0;i<x;i++){
		if(a[i]<b[i]){return -1;}
		else if(a[i]>b[i]){return 1;}
		else{}
	}
	if(m>=n){
		return 0;
	}
	else{
		return -1;
	}
}

void merge(use* suf_arr,int k, int n)
{	
	use* temp_arr=(use*)malloc(sizeof(use)*n);
	int i=0,j=k,l=0,p=0;
	//char* te;
	while(i<k && j<n){

		if(compare_string(suf_arr[i].st,suf_arr[j].st)==-1){
			
			temp_arr[l].index=suf_arr[i].index;
			temp_arr[l].n=suf_arr[i].n;
			temp_arr[l].st=(char*)malloc(sizeof(char)*(strlen(suf_arr[i].st)+1));
			strcpy(temp_arr[l].st,suf_arr[i].st);
			temp_arr[l].doc_title=(char*)malloc(sizeof(char)*(strlen(suf_arr[i].doc_title)+1));
			strcpy(temp_arr[l].doc_title,suf_arr[i].doc_title);
			i++;
		}
		else{
			temp_arr[l].index=suf_arr[j].index;
			temp_arr[l].n=suf_arr[j].n;
			temp_arr[l].st=(char*)malloc(sizeof(char)*(strlen(suf_arr[j].st)+1));
			strcpy(temp_arr[l].st,suf_arr[j].st);
			temp_arr[l].doc_title=(char*)malloc(sizeof(char)*(strlen(suf_arr[j].doc_title)+1));
			strcpy(temp_arr[l].doc_title,suf_arr[j].doc_title);
			j++;
		}
		l++;
	}
	
	if(i==k){
		while(j<n){
			temp_arr[l].index=suf_arr[j].index;
			temp_arr[l].n=suf_arr[j].n;
			temp_arr[l].st=(char*)malloc(sizeof(char)*(strlen(suf_arr[j].st)+1));
			strcpy(temp_arr[l].st,suf_arr[j].st);
			temp_arr[l].doc_title=(char*)malloc(sizeof(char)*(strlen(suf_arr[j].doc_title)+1));
			strcpy(temp_arr[l].doc_title,suf_arr[j].doc_title);
			j++;l++;
		}
	}
	else{
		while(i<k){
			temp_arr[l].index=suf_arr[i].index;
			temp_arr[l].n=suf_arr[i].n;
			temp_arr[l].st=(char*)malloc(sizeof(char)*(strlen(suf_arr[i].st)+1));
			strcpy(temp_arr[l].st,suf_arr[i].st);
			temp_arr[l].doc_title=(char*)malloc(sizeof(char)*(strlen(suf_arr[i].doc_title)+1));
			strcpy(temp_arr[l].doc_title,suf_arr[i].doc_title);
			i++;l++;
		}
	}
	//printf("%d\t%d\t%d\n",l,n,k);
	for(p=0;p<n;p++){
		suf_arr[p].index=temp_arr[p].index;
		suf_arr[p].n=temp_arr[p].n;
		suf_arr[p].st=(char*)realloc(suf_arr[p].st,sizeof(char)*(strlen(temp_arr[p].st)+1));
		strcpy(suf_arr[p].st,temp_arr[p].st);
		suf_arr[p].doc_title=(char*)realloc(suf_arr[p].doc_title,sizeof(char)*(strlen(temp_arr[p].doc_title)+1));
		strcpy(suf_arr[p].doc_title,temp_arr[p].doc_title);
		free(temp_arr[p].st);
		free(temp_arr[p].doc_title);
	}
	
	free(temp_arr);
}

void sort_arr(use* suf_arr,int a)
{
	//printf("%d\n",a);
	fflush(stdout);
	int l=0;
	
	//int h=sizeof(suf_arr)/sizeof(use);
	//int in_temp;	
	//char* temp;
	//int t;
	if(a<=1){
		//return 
	}
	else{
		int k=a/2;
		sort_arr(suf_arr,k);
		
		sort_arr(suf_arr+k,a-k);
		merge(suf_arr,k,a);
	}
}

int main()
{
	struct timespec start;
	struct timespec end;
	FILE *fp;
	fp=fopen("AesopTales.txt","r");
	char ch;
	char* buf=(char*)malloc(sizeof(char)*100000000);
	int flag=0;
	int i=0;
	float tb=0;
	char* title;
	int fhead=0;
	//clock_gettime(CLOCK_REALTIME,&start);
	while(!feof(fp)){
		ch=fgetc(fp);
		if(ch==13 || ch==10){

			if(fhead>5 && fhead<1000){
				fhead=1000;
				//buf[i]='\0';
				title=(char*)malloc(sizeof(char)*(strlen(buf)+1));
				strcpy(title,buf);
			}
			flag++;
			//printf("%d\n",ch);
			//printf("%c\t newline\t%d",ch,flag);
			if(flag==6 || i>=1000){
				break;
			}
			buf[i]=ch;
			i++;
		}	
		else{
			fhead++;
			buf[i]=ch;
			i++;
			flag=0;
		}			
		
	}
	buf[i]='\0';
	int n=strlen(buf);
	char* t=(char*)malloc(sizeof(char)*(n+1));
	strcpy(t,buf);
	free(buf);
	
	
	use** arr_of_suffix_arrs=(use**)malloc(sizeof(use*)*10);	//creating array of suffix trees for the first 10 documents in the file
	arr_of_suffix_arrs[0]=create_suf_arr(t,title);
	sort_arr(arr_of_suffix_arrs[0],strlen(t));
	
	
	char* text;
	char* heading;	
	for(i=2;i<=10;i++){
		
		text=get_text_title(i,&heading);

		//printf("%shello\n%s",text,heading);
		//fflush(stdout);
		arr_of_suffix_arrs[i-1]=create_suf_arr(text,heading);

		sort_arr(arr_of_suffix_arrs[i-1],strlen(text));

		free(text);
		free(heading);
	}

	
	//The query string has not been scanned from user input. If needed, the query string can be changed in the following lines as required.
	
	for(i=1;i<=10;i++){
		int answer=search_str("meeting",arr_of_suffix_arrs[i-1],arr_of_suffix_arrs[i-1][0].n);		//searching for the 1st occurances of the query string in the first 10 documents
		if(answer!=-1){
			
			printf("%d\n",answer);	
			
		}
		else{
			char* lcs=search_lcs("meeting",arr_of_suffix_arrs,i-1,&answer);			//searching for the longest substring of the query string in the first 10 documents
			printf("%d\t%s\n",answer,lcs);
		}
	}
	printf("\n\n\n");
	//free(arr_of_suffix_arrs);
	arr_of_suffix_arrs=destroy_and_remake(arr_of_suffix_arrs);
	free(t);
	free(title);
	//printf("%d\n",arr_of_suffix_arrs[1][0].n);
	fflush(stdout);

	

	rev* relevance=(rev*)malloc(sizeof(rev)*10);		//creating a relevance array for the 10 documents to quantify and store the relevance of the documents to the query string
	for(i=1;i<=10;i++){relevance[i-1].doc_no=i-1;
			   relevance[i-1].score=0;}
	

	for(i=1;i<=10;i++){

		int answer=search_str("meeting",arr_of_suffix_arrs[i-1],arr_of_suffix_arrs[i-1][0].n);
	
		int count;
		char* lcs;
		if(answer!=-1){

			if(answer<=strlen(arr_of_suffix_arrs[i-1][0].doc_title)){		//if the query strng is present in the title, it its more relevant and receives a higher score
				relevance[i-1].score+=10000;
			}
		

			count=no_of_occurances("meeting",arr_of_suffix_arrs[i-1],arr_of_suffix_arrs[i-1][0].n);		//Higher the number of occurances of the query string, higher the score

			relevance[i-1].score+=count*1000;
		}

		else{

			lcs=search_lcs("meeting",arr_of_suffix_arrs,i-1,&answer);		//Longer the substring of the query string matched, higher the score
			arr_of_suffix_arrs=destroy_and_remake(arr_of_suffix_arrs);
			relevance[i-1].score+=100*strlen(lcs);
			count=no_of_occurances(lcs,arr_of_suffix_arrs[i-1],arr_of_suffix_arrs[i-1][1].n);		//Higher the number of occurances of the substring of query string, higher the score

			relevance[i-1].score+=10*count;
		}

	}
	int j;
	rev temp;
		//for(i=0;i<10;i++){printf("%d\t",relevance[i].score);}printf("\n");
	for(i=0;i<10;i++){
		for(j=0;j<9-i;j++){
			if(relevance[j].score<relevance[j+1].score){
				temp=relevance[j];
				relevance[j]=relevance[j+1];
				relevance[j+1]=temp;
			}
		}	
	}
		//for(i=0;i<10;i++){printf("%d\t",relevance[i].score);}
	for(i=0;i<10;i++){
		printf("%s\n",arr_of_suffix_arrs[relevance[i].doc_no][0].doc_title);
	}
	printf("\nThe relevance is determined as follows:\nif the query string is present in the title of the document, then it is more relevant.\nif the query string is present more number of times in the document, it is more relevant\nif the query string is partially present, then the document with the longer substring of the query string is more relevant.\nFinally, the more number of times the substring occurs in the document, the more relevant it is.\n");
}

use** destroy_and_remake(use** arr_of_suffix_arrs)
{
	
	free(arr_of_suffix_arrs);
	arr_of_suffix_arrs=(use**)malloc(sizeof(use*)*10);
	char* text;
	char* heading;	
	int i;
	for(i=1;i<=10;i++){
		
		text=get_text_title(i,&heading);

		//printf("%shello\n%s",text,heading);
		//fflush(stdout);
		arr_of_suffix_arrs[i-1]=create_suf_arr(text,heading);

		sort_arr(arr_of_suffix_arrs[i-1],strlen(text));

		free(text);
		free(heading);
	}
	return arr_of_suffix_arrs;
}

int search_prefix(char* a, char* b)
{
	int n=strlen(a);
	int m=strlen(b);
	int x;
	if(n<m){x=n;}
	else{x=m;}
	int i;
	int k=0;
	for(i=0;i<x;i++){
		if(a[i]==b[i]){
			k++;
		}
		else{
			break;
		}
	}
	return k;
}
char* search_lcs(char* a,use** arr_of_suf_arr,int g,int* ans)
{
	
	char* b=a;
	int i;
	int lcs=0;
	int fi=-1;
	int ii=-1;
	use* suf_arr=arr_of_suf_arr[g];
	suf_arr=(use*)realloc(suf_arr,sizeof(use)*(suf_arr[0].n+strlen(a)));

	for(i=0;i<strlen(a);i++){
		suf_arr[i+suf_arr[0].n].st=(char*)malloc(sizeof(char)*(strlen(a)-i));
		strcpy(suf_arr[i+suf_arr[0].n].st,b);
		suf_arr[i+suf_arr[0].n].doc_title=(char*)malloc(sizeof(char)*10);
		strcpy(suf_arr[i+suf_arr[0].n].doc_title,"noheading\0");
		b++;
		suf_arr[i+suf_arr[0].n].index=-1;
		
	}

	sort_arr(suf_arr,suf_arr[0].n+strlen(a));

	int k;
	for(i=0;i<strlen(a)+suf_arr[0].n-1;i++){
		k=search_prefix(suf_arr[i].st,suf_arr[i+1].st);
		
		if(k>lcs && ((suf_arr[i].index==-1 && suf_arr[i+1].index!=-1)  || (suf_arr[i+1].index==-1 && suf_arr[i].index!=-1))){
			lcs=k;
			if(suf_arr[i+1].index==-1){fi=suf_arr[i].index;ii=i;}
			else{fi=suf_arr[i+1].index;ii=i;}
		}
	}

	//printf("%dhello",fi);
	char* common_substr;
	if(fi!=-1){
		common_substr=(char*)malloc(sizeof(char)*lcs);
		for(i=0;i<lcs;i++){
			common_substr[i]=suf_arr[ii].st[i];
			//printf("%c\n",suf_arr[ii].st[i]);
		}
		common_substr[i]='\0';
	}
	int nempty=1;
	//printf("testing");
	//int d=0;
	for(i=0;i<suf_arr[0].n+strlen(a);i++){
		if(suf_arr[i].index==-1){//d++;
			suf_arr[i].st=(char*)realloc(suf_arr[i].st,sizeof(char)*strlen(suf_arr[suf_arr[0].n+strlen(a)-nempty].st)+1);
			strcpy(suf_arr[i].st,suf_arr[suf_arr[0].n+strlen(a)-nempty].st);
			suf_arr[i].doc_title=(char*)realloc(suf_arr[i].st,sizeof(char)*strlen(suf_arr[suf_arr[0].n+strlen(a)-nempty].doc_title)+1);
			strcpy(suf_arr[i].doc_title,suf_arr[suf_arr[0].n+strlen(a)-nempty].doc_title);
			
			suf_arr[i].n=suf_arr[suf_arr[0].n+strlen(a)-nempty].n;
			free(suf_arr[suf_arr[0].n+strlen(a)-nempty].st);
			free(suf_arr[suf_arr[0].n+strlen(a)-nempty].doc_title);
			nempty++;
		}
	}
fflush(stdout);
	//printf("%d\n",d);
	suf_arr=(use*)realloc(suf_arr,sizeof(use)*(suf_arr[0].n));
	//printf("testing");
	//sort_arr(suf_arr,suf_arr[0].n);

	*ans=fi;
	return common_substr;
}
int search_str(char* pattern, use* suf_arr, int n)
{
	//printf("\n\n\n");
	int l=0;
	int h=n;
	int m,k;

	int i;
	int ans_index=1000000;

	while(l<=h){
		
		m=(l+h)/2;

		//printf("Searching\t%d\t%d\t%d\t%s\n",l,h,m,suf_arr[m].st);
		k=compare_k_string(suf_arr[m].st,pattern);

		if(k==0){

			int z=m;
			
			//printf("%d hello",suf_arr[m].index);
			while(compare_k_string(suf_arr[m].st,pattern)==0 && (m>0 && m<n)){
				if(suf_arr[m].index<ans_index){ans_index=suf_arr[m].index;}
				m++;
			}
			m=z;
			while(compare_k_string(suf_arr[m].st,pattern)==0 && (m>0 && m<n)){
				if(suf_arr[m].index<ans_index){ans_index=suf_arr[m].index;}
				m--;
			}
			
			return ans_index;
			
		}	
		else if(k>0){
			h=m-1;
		}
		else{
			l=m+1;
		}
	}
	return -1;
}

int no_of_occurances(char* pattern, use* suf_arr, int n)
{
	
	int l=0;
	int h=n;
	int m,k;
	int count=0;
	int i;
	int ans_index=1000000;
	while(l<=h){
		
		m=(l+h)/2;

		//printf("Searching\t%d\t%d\t%d\t%s\n",l,h,m,suf_arr[m].st);
		k=compare_k_string(suf_arr[m].st,pattern);

		if(k==0){
			int z=m;
			
			//printf("%d hello",suf_arr[m].index);
			while(compare_k_string(suf_arr[m].st,pattern)==0 && (m>0 && m<n)){
				if(suf_arr[m].index<ans_index){ans_index=suf_arr[m].index;}
				m++;
				count++;
			}
			m=z;
			while(compare_k_string(suf_arr[m].st,pattern)==0 && (m>0 && m<n)){
				if(suf_arr[m].index<ans_index){ans_index=suf_arr[m].index;}
				m--;
				count++;
			}
			count--;
			return count;
			
		}	
		else if(k>0){
			h=m-1;
		}
		else{
			l=m+1;
		}
	}
	return 0;
}

char* get_text_title(int doc_id,char** heading)
{
	
	FILE *fp;
	fp=fopen("AesopTales.txt","r");
	char* buf=(char*)malloc(sizeof(char)*100000000);
	char ch;
	int flag=0,f2=0;
	int i=0;
	int count=1;
	int fhead=0;
	char* text;
	while(!feof(fp)){
		if(count==doc_id){
			//printf("%c\t%d\t%d\t%d\n",ch,ch,f2,count);
			ch=fgetc(fp);
			//printf("%c\t%d\n",ch,ch);
			if(ch==13 || ch==10  || (ch==32 && f2>0)){
				if(fhead>5 && fhead<1000){
					fhead=1000;
					buf[i]='\0';
					
					*heading=(char*)malloc(sizeof(char)*(strlen(buf)+1));
					strcpy(*heading,buf);
					//printf("%s",*heading);
					fflush(stdout);
				}
				f2++;
				//printf("%d\n",ch);
				//printf("%c\t newline\t%d",ch,flag);
				if(f2>=6){
					break;
				}
				buf[i]=ch;
				i++;
			}	
			else{
				fhead++;
				buf[i]=ch;
				i++;
				f2=0;
			}			
		}

		else{
			ch=fgetc(fp);
			//printf("%c\t%d\t%d\t%d\n",ch,ch,flag,count);
			
			if(ch==13 || ch==10  || (ch==32 && flag>0)){
				flag++;
				//printf("%d\n",ch);
				//printf("%c\t newline\t%d",ch,flag);
				if(flag>=6){
					count++;
					flag=0;
				}
			}
			else{
				flag=0;
			}
		}	
	}
	buf[i]='\0';
	int n=strlen(buf);
	//printf("%s",n);
	text=(char*)malloc(sizeof(char)*(n+1));
	strcpy(text,buf);
	//printf("%s",*text);
	free(buf);
	return (text);
}

		

	
	
