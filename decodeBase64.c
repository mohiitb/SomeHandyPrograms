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

int rules_index(char c){
	int i=0;
	for (i = 0; i < 64; i++){
		if (rules[i]==c)
			break;
	}
		return i;
}

char * decode(char *msg_in){
	int len = strlen(msg_in);
	int ascii,i=0,b,to_binary[2040],bits,k,all_bits=0,temp;
	rules_init();
	if (len>0){
  		int bits_to_take = 0,all_bits=0;
  		if (msg_in[len-1]=='='){
  			if (msg_in[len-2]=='='){
  				bits_to_take = 6*(len)-16;
        		len = len-2;
  			}
  			else{
  				bits_to_take = 6*(len)-8;
        		len = len-1;
  			}
  		}
  		else
  			bits_to_take = 6*(len);

    	//converting character to 6 bit binary values
		for(i=0;i<len;i++){
			ascii = rules_index(msg_in[i]);
			for (bits = 5; bits >= 0; bits--){
				k = ascii>>bits;
    			if (k & 1)
    				to_binary[all_bits] = 1;
    			else
    				to_binary[all_bits] = 0;
    			all_bits++;
			}
		}

  		//Converting back to Characters from binary values of 8 bit
	    int group8 = bits_to_take/8;
	    char * output_msg;
	    output_msg = (char *)malloc(255*sizeof(char));
	    for (i = 0; i < group8; i++){
	    	temp = to_binary[i*8]*128 +to_binary[i*8+1]*64 +to_binary[i*8+2]*32 + to_binary[i*8+3]*16 + to_binary[i*8+4]*8 + to_binary[i*8+5]*4 + to_binary[i*8+6]*2 + to_binary[i*8+7]*1;
      		output_msg[b] = temp;
      		b++;   
	    }
	    return (char*)output_msg;
  	}
  	else{
  		return NULL;
  	}
}

int main(){
	printf("Base64 Decoding Program:\n\n");
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
				printf("Output Decoded Message is: %s\n\n",decode(msg));
				bzero(msg,char_nums);	
			}
			else{
				printf("Program is exiting...");
				break;
			}
	}
	return 0;
}
