#include <stdio.h>
#include <string.h>


//Macros
#define MAXMUM_SIZE  100

//prototypes;
char search(char search_id);
void ReArrange(char index);
void Add_Book ();		//private
void Print_Library();	
void Borrow_Book();
void Delete_Book();		//private
void Buy_BookCopies();

//Global
typedef struct 
{
	char 	ID;
	char 	BookTitle[100];
	char 	AutherName[100];
	int 	PublicationYear;
	float 	Price;
} Book_Info;

typedef struct 
{
	Book_Info 	Book;
	int 		NumberOfCopies;
	char 		Status[50];    //provided or needed
}Library;

Library BookArray[MAXMUM_SIZE];
Library NullStruct = {};
int BookCounter = 0;




//start
void main()
{
	char Choise;
	char password[4];
	char mode,exit='\0';
	printf("Hello, Welcome to BookArray Management System\n");

	Add_Book();
	Add_Book();
	Add_Book();
	Print_Library();
	Borrow_Book();
	Print_Library();	
	Delete_Book();
	Print_Library();
	
	
/*
	while(exit != 'e')
	{
		printf("Press 1 for administor mode, or 0 for user mode: ");
		scanf("%d",&mode);
		if (mode)
		{
			printf("Enter password: ");
			scanf("%s",password);
			if (!strcmp(password,"0000"))
			{
				printf("Press 1 to add a book\n");
				printf("Press 2 to print library content\n");
				printf("Press 3 to delete a book\n");
				printf("Press 4 to buy a copies of books");
				scanf("%d",&Choise);
				switch (Choise)
				{
					case 1:	Add_Book();			break;
					case 2: Print_Library();	break;
					case 3: Delete_Book();		break;
					case 4: Buy_BookCopies();	break;
					default: break;
				}
			}
			else
			{
				printf("Wrong Password\n");
			}

		}
		else
		{
			printf("Press 1 to print library content\n");
			printf("Press 2 to borrow a book\n");
			scanf("%d",&Choise);
			switch (Choise)
			{
				case 1:	Print_Library();	break;
				case 2: Borrow_Book();		break;
				default: break;
			}	
		}
	
		
		printf("\nEnter e to exit , otherwise to continue ..");
		gets(&exit);
	}
*/
}


//Function1: Add Book

void Add_Book()
{
	char NewBookID,index;
	if (BookCounter == MAXMUM_SIZE)
	{
		printf("Sorry the linrary is Completed now \n");
	}
	else
	{	
		printf("Please Enter the Book ID: ");
		scanf("%d",&NewBookID);
		index = search(NewBookID);
		if(index == -1)  //new book
		{
			BookArray[BookCounter].Book.ID = NewBookID;
			
			printf("Please Enter the BookTitle: ");
			scanf("%s",&BookArray[BookCounter].Book.BookTitle);
			
			printf("Please Enter the AutherName: ");
			scanf("%s",&BookArray[BookCounter].Book.AutherName);
			
			printf("Please Enter the PublicationYear: ");
			scanf("%d",&BookArray[BookCounter].Book.PublicationYear);
			
			printf("Please Enter the Price: ");
			scanf("%f",&BookArray[BookCounter].Book.Price);

			BookArray[BookCounter].NumberOfCopies = 1;
			strcpy(BookArray[BookCounter].Status,"Available");
			
			BookCounter++;
		}
		else  //new book
		{
			BookArray[index].NumberOfCopies ++;
			printf("the book already exists, a new copy has been added\n");
			strcpy(BookArray[index].Status,"Available");
		}
	}
}


char search(char search_id)
{
	for (int i =0; i<=BookCounter; i++)
	{
		if  (BookArray[i].Book.ID==search_id)
			return i;
	}
	return -1;
}


void Print_Library()
{
	for (int i =0; i<BookCounter; i++)
	{
		if(!strcmp(BookArray[i].Status,"Deleted"))
			continue;
		else
		{
			printf("Book %d Info:\n",i);
			printf("ID: %s\n",BookArray[i].Book.ID);
			printf("BookTitle: %s\n",BookArray[i].Book.BookTitle);
			printf("AutherName: %s\n",BookArray[i].Book.AutherName);
			printf("PublicationYear: %d\n",BookArray[i].Book.PublicationYear);
			printf("NumberOfCopies: %d\n",BookArray[i].NumberOfCopies);
			printf("Price: %f\n",BookArray[i].Book.Price);
			printf("Status: %s\n",BookArray[i].Status);
			printf("\n------------------------\n\n");
		}
	}
}

void Borrow_Book()
{	
	char NewBookID,index;
	printf("Enter the book ID: ");	
	scanf("%d",&NewBookID);
	index = search(NewBookID);
	if(index == -1)  //new book
	{
		printf("Sorry we don't have this book\n");
	}
	else 
	{
		BookArray[index].NumberOfCopies --;
		if(BookArray[index].NumberOfCopies)
			strcpy(BookArray[index].Status,"Available");
		else 
			strcpy(BookArray[index].Status,"Borrowed");
	}	
}


void ReArrange(char index)
{
	for (int i =index; i<=BookCounter; i++)
	{
		BookArray[i]=BookArray[i+1];
	}
	BookArray[BookCounter] = NullStruct;	
}


void Delete_Book()
{
	char NewBookID,index;
	printf("Enter the book ID: ");	
	scanf("%d",&NewBookID);
	index = search(NewBookID);
	if(index == -1)  //new book
	{
		printf("Sorry this book does not exist\n");
	}
	else 
	{
		BookCounter--;
		ReArrange(index);
	}	
}


void Buy_BookCopies()
{
	int copies,NewBookID,index;
	printf("Please Enter the Book ID: ");
	scanf("%d",&NewBookID);
	index = search(NewBookID);
	printf("How many copies do you want to buy? : ");
	scanf("%d",&copies);
	BookArray[index].NumberOfCopies +=copies;
	strcpy(BookArray[index].Status,"Available");
}




