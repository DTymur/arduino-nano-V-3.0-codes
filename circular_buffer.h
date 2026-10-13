#ifndef CIRCULAR_BUFFER_H
#define CIRCULAR_BUFFER_H

#include <stdio.h>
#include <stdlib.h> 

struct buffer{
	int tail, head, size, count;
	float *arr;
	};

struct buffer init (int size){
	struct buffer buf;
	buf.tail = 0;
	buf.head = 0;
	buf.count = 0;
	buf.size = size;
	float *temp = (float*)malloc(size*sizeof(float));
	if(temp != NULL){
		buf.arr = temp;
		return buf;
		}
	else{printf("Not enough memory\n");	
	return buf;}
	};
	
int isfull (struct buffer *buf){
	if (buf->count == buf->size - 1){
		return 1;
		}
	return 0;
	};
	
int isempty (struct buffer *buf){
	if (buf->count == 0){
		return 1;
	}
	return 0;
};
	
void push (struct buffer *buf, float data){
	
	if(buf->count == buf->size){
		buf->tail++;
		};
	
	buf->arr[buf->head] = data;
	
	buf->head++;
	
	if (buf->head > buf->size - 1){
		buf->head = 0;
		}
	
	if(buf->count < buf->size){
		buf->count++;
		}
		
	if (buf->tail > buf->size - 1){
		buf->tail = 0;
		}	
	};
	
float pop (struct buffer *buf){
	
	float value = buf->arr[buf->tail];
	
	buf->count--;
	buf->tail++ ;
	
	if (buf->count < 0){
		buf->count = 0;
		return 0;
		}	
	
	if (buf->tail > buf->size - 1){
		buf->tail = 0;
		}
			
	if(buf->count == 0){
		buf->tail = 0;
		buf->head = 0;
		}
	return value;
	};
#endif
