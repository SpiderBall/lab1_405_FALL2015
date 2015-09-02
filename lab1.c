#include <stdio.h>
#include <stdlib.h>

struct node{
    int data;//data stored in the node
    struct node* prev;//a node previous to the current node
    struct node* next;//and a node after the current node
};

void add_node(struct node **list, int new_value){
	//passes in a pointer to a pointer to the list and the value to be inserted

	struct node * current = *list;//current node in this context (starts at the head of the list)
	struct node * trail = malloc(sizeof(struct node*));//node previous to the current node in this context (starts as NULL)
	struct node* new_node = malloc(sizeof(struct node*));//pointer to a new node

	if(new_node != NULL){//if malloc was successful
		new_node->data = new_value;	//set new_node's data to the new value
	}

	//1) If Linked list is empty then make the node as head and return
	if((*list)==NULL){
		*list = new_node;//sets the head of the list to the new node
		return;
	}

	//2) If value of the node to be inserted is smaller than value of head node
		//then insert the node at start and make it head.
	if(new_node->data < current->data){
		*list = new_node; //sets the head of the list to the new node
		new_node->next = current;//connects the next pointer for the new node to what used to be the head
		current->prev = new_node;//connects new node to current
		return;
	}else{
		/*
		3) In a loop, find the appropriate node after which the input node is
			to be inserted. To find the appropriate node start from head, keep moving 
			until you reach a node GN who's value is greater than the input node. 
			The node just before GN is the appropriate node.
		4) Insert the node after the appropriate node found in step 3.
		*/
		while(current->next!=NULL){
			if(new_node->data < current->data){//if new_node is less than the current node
				trail->next = new_node;//connects trail to new_node	
				new_node->prev = trail;

				new_node->next = current;//connects new_node to current 
				current->prev = new_node;

				return;
			}else{//if new_node is greater than the current node
				trail = current;
				current = current->next;//increments the placement of current when new_node is not in the appropriate place
			}
		}
			if(current->next==NULL){//we've incremented until the end of the list since the number is greater than everything before it
				//when we reach the end of the list, add the new node to the end of the list
				trail = current;//sets previous to the end

				new_node->prev = trail;//connects the new node to the end of the trail
				trail->next = new_node;

				new_node->next = NULL;//sets new_node at the end of the list (where next points to null)
				current = new_node;//sets current node to the newly added node
				return;
			}	
	}
}


void remove_node(struct node ** list, int old_value){
	struct node * current = *list;//current node in this context (starts at the head of the list)
	struct node * trail = malloc(sizeof(struct node*));//node previous to the current node in this context (starts as NULL)
	struct node* old_node = malloc(sizeof(struct node*));//pointer to the old node
	struct node* temp = malloc(sizeof(struct node*));//pointer to the old node


	if(current->data == old_value){//if the head of the list has the old value
		//delete the head
		temp = current;//set node to be removed
		current = current->next;//move current to the next space
		*list = current;//set the head of the list to the now current node
		free(temp);//delete what used to be the head
		return;

	}

	while(current->next!=NULL){//traverses the list
		if(current->data == old_value){//if the value matches the current value
			temp = current;//set the node to be removed
			current = current->next;//increment current
			trail->next= current;//connect trail to current
			current->prev = trail;//connect current to trail
			free(temp);//remove the node
			return;
		}else{
			trail = current;//set trail to the appropriate value
			current = current->next;//increment current
		}
	}
	if(current->next == NULL){ //if we've reached the end of the list
		if(current->data == old_value){//if the value to be deleted is at the end of the list
			//remove from the end
			temp = current;//set node to be removed
			current = current->prev;//set current back one
			trail = current->prev;//set trail to be before current
			current->next = NULL;
			free(temp);
			return;
		}
	}
}

//print the list
void print_list(struct node *list){//passes in a pointer to the list
    struct node * current;
    current = list;//set current to the head of the list
    int num_nodes=0;//counter for the number of nodes in the list
    while((current) != NULL){//if head is not null
        fprintf(stderr, "[%d] the value of the current node is %d \n",num_nodes, (current)->data);
        (current) = (current)->next;//increments current
        num_nodes+=1;//increments numnodes
    }
	fprintf(stderr, "========================================= \n");//separates each print out of the list from other print statements
}

int main(int argc, const char * argv[]) {

    struct node* test= 0;
    add_node(&test, 10);
    add_node(&test, 8);
    add_node(&test, 4);
    add_node(&test, 11);
    add_node(&test, 9);
    print_list(test);
    remove_node(&test, 4);
    print_list(test);
    remove_node(&test, 9);
    print_list(test);
    remove_node(&test, 11);
    print_list(test);
    return 0;
}

