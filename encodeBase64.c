#include <stdio.h>
#include <stdlib.h>
#include <strings.h>


char rules[64];

void rules_init(){
	int i;
	for(i=0;i<26;i++){
		rules[i] = i+65;		//A-Z
		rules[i+26] = i+97;		//a-z
		if(i<10){
			rules[i+52] = i+48;	//0-9
		}
	}
	rules[62] = '+';
	rules[63] = '/';
}

char* encode(char * msg_to_go){
	int len = strlen(msg_to_go);
	//Now converting ascii value of each character to binary value of 8-bits and storing it in to_binary array
	//to_binary stores the binary value of each 8-bit character, size of this array will be total 8*len+24-(8*len)%24
	int ascii,i=0,b=0,to_binary[8*len+24-(8*len)%24],bits,k,all_bits=0; 	
	for(i=0;i<len;i++){					
		ascii = (int)msg_to_go[i];
		for (bits = 7; bits >= 0; bits--)
		{
			k = ascii>>bits;
			if (k & 1)
				to_binary[all_bits] = 1;
			else
				to_binary[all_bits] = 0;
			all_bits++;
		}	
	}
	rules_init();
	//Padding bits in case 24 bits group can't be formed
	int flag = 0,rem_bits=0,temp_k;
	len*=8;							//updating len to be len*8(equal to total number of bits in given message: msg_to_go)
	if (len%24==8)					//if 16 more bits are needed
	{
		for(rem_bits = 0;rem_bits<16;rem_bits++)
			to_binary[all_bits+rem_bits] = 0;
		all_bits+=16;
		flag=2;
		temp_k = 12;

	}
	else if (len%24==16)				//if 8 more bits are needed
	{
		for(rem_bits = 0;rem_bits<8;rem_bits++)
			to_binary[all_bits+rem_bits] = 0;
		all_bits+=8;
		flag=1;
		temp_k = 18;
	}
	//Padding ends
	//Encoding of binary bits to text by forming group of 24 bits each and within each group, 4 groups of 6 bits
	char *base64,temp;
	base64 = (char*)malloc(sizeof(char)*(all_bits/6));
	bzero(base64,all_bits/6);
	int group24 = all_bits/24;		//number of groups
	if (flag==1||flag==2)					//If only 8 more bits were required
	{
		for (i = 0; i < group24-1; i++)
		{
			for (k = i*24; k < (i+1)*24; k+=6)
			{
				//convert each binary value to corresponding character from rules array
				temp = to_binary[k]*32 + to_binary[k+1]*16 + to_binary[k+2]*8 + to_binary[k+3]*4 + to_binary[k+4]*2 + to_binary[k+5]*1;
				base64[b] = rules[temp];
				b++;
			}
		}
		for (k = i*24; k < i*24+temp_k; k+=6)
		{
			temp = to_binary[k]*32 + to_binary[k+1]*16 + to_binary[k+2]*8 + to_binary[k+3]*4 + to_binary[k+4]*2 + to_binary[k+5]*1;
			base64[b] = rules[temp];
			b++;
		}
		base64[b] = '=';
		b++;
		if(flag==2){
			base64[b]='=';
			b++;
		}
		return (char*)base64;
	}
	else if(flag==0){						//if input text's bits are already in a multiple of 24	
		for (i = 0; i < group24; i++)
		{
			for (k = i*24; k < (i+1)*24; k+=6)
			{
				//convert each binary value to corresponding character from rules array
				temp = to_binary[k]*32 + to_binary[k+1]*16 + to_binary[k+2]*8 + to_binary[k+3]*4 + to_binary[k+4]*2 + to_binary[k+5]*1;
				base64[b] = rules[temp];
				b++;
			}
		}
		return (char*)base64;
	}
	else{
		return NULL;
	}
}

int main(){
	printf("Base64 Encoding Program:\n\n");
	int char_nums,choice;
	printf("How many maximum characters you want to allow in a single message: ");
	scanf("%d",&char_nums);
	char *msg;
	msg = (char*)malloc(sizeof(int)*char_nums);
	bzero(msg,char_nums);
	while(1){
			printf("Press 1. to continue\nOther to exit: ");
			scanf("%d",&choice);
			if(choice==1){
				printf("Enter your message: ");
				scanf("%s",msg);
				printf("Output Encode Message is: %s\n\n",encode(msg));
				bzero(msg,char_nums);	
			}
			else{
				printf("Program is exiting...");
				break;
			}
	}
	return 0;
}
