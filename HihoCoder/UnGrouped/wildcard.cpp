#include <string.h>
#include <stdlib.h>
bool match(char *src,char *cmp){//used to match no '*' str
	int len_src = strlen(src);
	int len_cmp = strlen(cmp);
	if(len_src!=len_cmp)
		return false;
	for(int i=0;i<len_cmp;i++){
		if(src[i]!=cmp[i]&&'?'!=cmp[i])
			return false;
	}
	return true;
}
char* _free_match(char *src,char *cmp){
	if(strlen(src)<strlen(cmp))
		return NULL;
	bool judge;
	char *src_head = src;
	while(1){
		char *tail = src_head+strlen(cmp);
		if(tail-src>strlen(src))
			return NULL;//match end
		char temp = *tail;
		*tail = '\0';
		judge = match(src_head,cmp);
		*tail = temp;
		if(judge)
			return src_head+strlen(cmp);
		src_head++;
	}
}
bool freematch(char *src,char *cmp){// used to match [*A*]
	char *record_src = src;
	int len_src = strlen(src);
	int len_cmp = strlen(cmp);
	char *cmp_head = cmp;
	for(int i=0;i<len_cmp+1;i++){
		if(cmp[i]=='*'||cmp[i]=='\0'){
			cmp[i]='\0';
			if(src-record_src>strlen(record_src)&&strlen(cmp_head)!=0)
				return false;//no more src, but still match.false
			src = _free_match(src,cmp_head);
			cmp_head = cmp+i+1;//
			if(src==NULL)
				return false;
		}
	}
	return true;
}
bool isMatch(char *src, char *cmp) {
	int len_src = strlen(src);
	int len_cmp = strlen(cmp);
	char *star_head = strstr(cmp,"*");
	if(star_head==NULL)
		return match(src,cmp);
	/*match head*/
	*star_head = '\0';
	char temp = *(src+strlen(cmp));
	*(src+strlen(cmp))='\0';
	bool judge = match(src,cmp);
	if(judge==false)
		return false;
	*(src+strlen(cmp))=temp;
	src = src + strlen(cmp);//move src
	/*match tail*/
	char *star_tail = cmp+len_cmp;//point to last char
	bool found = false;
	for(int i=0;i<len_cmp;i++){
		star_tail--;
		if('*'==*star_tail){
			found = true;
			break;
		}
	}
	if(found==false){//no second star,just A*B style.
		if(strlen(src)<strlen(star_head+1))//not enough to match
			return false;
		return match(src+strlen(src)-strlen(star_head+1),star_head+1);
	}
	char *tail_match_ptr = src+strlen(src)-strlen(star_tail+1);
	judge = match(tail_match_ptr,star_tail+1);
	if(judge == false)
		return false;
	*star_tail='\0';
	*tail_match_ptr='\0';
	/*match middle*/
	return freematch(src,star_head+1);
}

int main()
{
	int ret = 0;
	char src[]="ab";
	char cmp[]= "*?*?*";
	ret = isMatch(src,cmp);
	//ret = isMatch("aa", "a*");
	//ret = isMatch("ab", "?*");
	//ret = isMatch("aab", "c*a*b");
}
