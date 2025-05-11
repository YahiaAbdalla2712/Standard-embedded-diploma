#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//student structure
struct student{
	int id;         //student ID
	char name[50];  //student name
	int age;        //student age
	float gpa;      //student gpa
};

//structure to represent node in the linked list
struct node{
	struct student data;
	struct node *next;
};

struct node *head = NULL; //intialize the head pointer as a null pointer

void addstudent(const struct student *const ptr);

void displayStudents(void);

void searchStudentByID(int id);

void updateStudent(int id);

float calculateAverageGPA(void);

void searchHighestGPA(void);

void deleteStudent(int id);


int main(void){
	setvbuf(stdout, NULL, _IONBF, 0);
	setvbuf(stderr, NULL, _IONBF, 0);

	char input;
	int id,age;
	float gpa;
	char name[50];
	int search_id,update_id,delete_id;
	struct student s ;
	float avg_gpa;


while(1){
	printf("1. Add student\n"
		   "2. Display students\n"
		   "3. Search students by ID\n"
		   "4. Update student by ID\n"
		   "5. Delete student\n"
		   "6. Calculate Average GPA\n"
		   "7. Search for student with highest GPA\n"
		   "8. Exit\n"
		   "Enter your choice:");


	scanf(" %c",&input);
	if((input>'8')||(input<'1')){
		printf("invalid input\n");
	}
	else{
		if(input == '8'){
			printf("Thank you");
			break;
		}
		else{
			switch(input){
			case'1':
					printf("Enter student id:");
					scanf("%d",&id);
					printf("Enter student name:");
					scanf(" %49[^\n]", name);
					printf("Enter student age:");
					scanf("%d",&age);
					printf("Enter student gpa:");
					scanf("%f",&gpa);
					s.age = age;
					s.gpa = gpa;
					strcpy(s.name,name);
					s.id = id;
					addstudent(&s);
					break;

			case'2':displayStudents();
					break;

			case'3':printf("Enter an id to search:");
					scanf("%d",&search_id);
					searchStudentByID(search_id);
					break;

			case'4':printf("Enter an id to update:");
			        scanf("%d",&update_id);
			        updateStudent(update_id);
			        break;

			case'5':printf("Enter an id to delete its data:");
					scanf("%d",&delete_id);
					deleteStudent(delete_id);
					break;

			case'6':avg_gpa=calculateAverageGPA();
					printf("%f",avg_gpa);
					break;

			case'7':searchHighestGPA();
					break;


			}
		}
	}
}
	return 0;
}
void addstudent(const struct student *const ptr){
	struct node *current = head;
	while(current != NULL){
		if(current ->data.id == ptr -> id){
			printf("Student ID already exists\n");
			return;
		}
		current = current -> next;
	}
	struct node *newstudent = (struct node*)malloc(sizeof(struct node));
	if(newstudent == NULL){
		printf("can't allocate memory\n");
		return;
	}
	newstudent -> data.id = ptr ->id;
	strcpy(newstudent->data.name ,ptr->name);
	newstudent ->data.age = ptr->age;
	newstudent ->data.gpa = ptr->gpa;
	newstudent ->next = NULL;

	if(head == NULL){
		head = newstudent;
	}
	else{
		current = head;
		while(current ->next != NULL){
			current = current -> next;
		}
		current -> next = newstudent;
	}
	printf("student is successfuly registered\n");
}


void displayStudents(void){
	if(head != NULL){
		struct node *current = head;
		while(current != NULL){
			printf("ID: %d,",current->data.id);
			printf("Name: %s,",current -> data.name);
			printf("Age: %d,",current -> data.age);
			printf("GPA: %f\n",current ->data.gpa);
			current = current->next;
		}
	}
	else{
		printf("No students' data to print");
		return;
	}
}


void searchStudentByID(int id)
{
	int flag = 0;
	if(head != NULL){
	struct node *current = head;

	while(current != NULL){
		if(current->data.id == id){
			printf("ID: %d,",current->data.id);
			printf("Name: %s,",current -> data.name);
			printf("Age: %d,",current -> data.age);
			printf("GPA: %f\n",current ->data.gpa);
			flag = 1;
			break;
		}
		current = current -> next;
	  }
	}

	if(flag==0){
		printf("No student with this id is found\n");
	}
}

void updateStudent(int id){
	struct node *current = head;
	int flag = 0;
	char name[50];
	int age;
	float gpa;
	struct node*temp = head;
	while(current != NULL){
		if(current->data.id == id){
			flag = 1;
			head = current;
			break;
		}
		current = current -> next;
	}
	if(flag==1){
			printf("Enter name:");
			scanf(" %49[^\n]", name);
			strcpy(head->data.name,name);
			printf("Enter age:");
			scanf("%d",&age);
			head->data.age = age;
			printf("Enter gpa:");
			scanf("%f",&gpa);
			head->data.gpa = gpa;
			head = temp;
			printf("the updated data is: \n");
			printf("ID: %d,",current->data.id);
			printf("Name: %s,",current -> data.name);
			printf("Age: %d,",current -> data.age);
			printf("GPA: %f\n",current ->data.gpa);
		}
	else{
		printf("No student id is found\n");
	}
}

float calculateAverageGPA(void){
	float avg = 0;
	int count=0;
	float sum=0;
	struct node*current = head;
	if(head == NULL){
		return 0;
	}
	while(current != NULL){
		sum += (current->data.gpa);
		count++;
		current = current ->next;
	}
	avg = sum/count;
	return avg;
}

void searchHighestGPA(void){
	struct node *current = head;
	float max=current->data.gpa;
	while(current != NULL){
		if((current->data.gpa)>max){
			max = current->data.gpa;
		}
		current = current->next;
	}
	current = head;
	while(current != NULL){
		if((current->data.gpa)==max){
			printf("this the data of the highest gpa student:\n");
			printf("ID: %d,",current->data.id);
			printf("Name: %s,",current -> data.name);
			printf("Age: %d,",current -> data.age);
			printf("GPA: %f\n",current ->data.gpa);
		}
		current = current->next;
	}
}

void deleteStudent(int id){
	 struct node*current = head;
	 struct node *previous = NULL;
	 int flag = 0;
	 while(current != NULL){
		 if((current->data.id)==id){
			 if (previous == NULL) {
				 head = current->next;
			 }
			 else{
				 previous->next = current->next;
			 }
			 free(current);
			 printf("Student data is successfuly deleted.\n");
			 flag=1;
			 break;
		 }
		 previous = current;
		 current = current->next;
	 }
	 if(flag == 0){
		 printf("No student with this id is found\n");
	 }
}
