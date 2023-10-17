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
	char 		NumberOfCopies;
	char 		Status[50];    //provided or needed
}Library;

Library BookArray[MAXMUM_SIZE];
Library NullStruct = {};
char BookCounter = 0;
char TotalBookCounter = 0;

char exit_flag = 0;
char Choise;
char mode;
char password[4];


//start
void main()
{

	
	printf("Hello, Welcome to BookArray Management System\n");
 
	while(1)
	{
		printf("Press 1 for admin mode, or 0 for user mode: ");
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
				printf("Press 4 to buy a copies of books\n");
				printf("Press 5 to exit the system\n");
				scanf("%d",&Choise);
				switch (Choise)
				{
					case 1:	Add_Book();			break;
					case 2: Print_Library();	break;
					case 3: Delete_Book();		break;
					case 4: Buy_BookCopies();	break;
					case 5: exit_flag = 1;		break;
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
			printf("Press 3 to exit the system\n");
			scanf("%d",&Choise);
			switch (Choise)
			{
				case 1:	Print_Library();	break;
				case 2: Borrow_Book();		break;
				case 3: exit_flag =1;		break;
				default: break;
			}	
		}
	
		if (exit_flag)
			break;
		
	}
	
	
}


/*Function1: Add Book
 *check if the number of books in library exceeds the maxmum sizeof
 *if there is empty place we can add new books
 *the book ID should be unique 
 *we use the new coming ID to check if this book already exists or not
 *if the book exists the system only increases the number of copies
 */
void Add_Book()
{
	char NewBookID,index;
	if (TotalBookCounter == MAXMUM_SIZE)
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
			scanf(" %[^\n]%*c",&BookArray[BookCounter].Book.BookTitle);
			
			printf("Please Enter the AutherName: ");
			scanf(" %[^\n]%*c",&BookArray[BookCounter].Book.AutherName);
			
			printf("Please Enter the PublicationYear: ");
			scanf("%d",&BookArray[BookCounter].Book.PublicationYear);
			
			printf("Please Enter the Price: ");
			scanf("%f",&BookArray[BookCounter].Book.Price);

			BookArray[BookCounter].NumberOfCopies = 1;
			
			strcpy(BookArray[BookCounter].Status,"Available");
			
			BookCounter++;
			TotalBookCounter++;
			printf("\nthe book has been added succesfully\n\n");

		}
		else 
		{
			BookArray[index].NumberOfCopies ++;
			TotalBookCounter++;
			printf("\nthe book already exists, a new copy has been added\n\n");
			strcpy(BookArray[index].Status,"Available");
		}
	}
}


char search(char search_id)
{
	for (int i =0; i<BookCounter; i++)
	{
		if  (BookArray[i].Book.ID==search_id)
			return i;
	}
	return -1;
}


void Print_Library()
{
	printf("\nThe library contains the following books:\n\n");
	for (int i =0; i<BookCounter; i++)
	{
		printf("Book %d Info:\n",i+1);
		printf("ID: %d\n",BookArray[i].Book.ID);
		printf("BookTitle: %s\n",BookArray[i].Book.BookTitle);
		printf("AutherName: %s\n",BookArray[i].Book.AutherName);
		printf("PublicationYear: %d\n",BookArray[i].Book.PublicationYear);
		printf("NumberOfCopies: %d\n",BookArray[i].NumberOfCopies);
		printf("Price: %f\n",BookArray[i].Book.Price);
		printf("Status: %s\n",BookArray[i].Status);
		printf("\n------------------------\n");
	}
}

void Borrow_Book()
{	
	char NewBookID,index,flag;
	printf("\nEnter the ID of the book you want to borrow: \n");	
	printf("You can print the library content if you don't know the ID of the book\n");
	printf("do you want to print library content ? \n press 1 if yes, 0 if No \n");
	scanf("%d",&flag);
	if (flag)
		Print_Library();
	printf("Now enter the Book ID:");
	scanf("%d",&NewBookID);
	index = search(NewBookID);
	if(index == -1)  //new book
	{
		printf("Sorry this book doesn't exist\n\n");
	}
	else 
	{
		BookArray[index].NumberOfCopies --;
		if(BookArray[index].NumberOfCopies)
			strcpy(BookArray[index].Status,"Available");
		else 
			strcpy(BookArray[index].Status,"Borrowed");
		printf ("Please return the book before 2 weeks from now\n");
		printf ("We wish you enjoy reading the book\n\n");
	}	


}


// to shift the array elements after deleting a book
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
	printf("Enter the book ID you want to delete: ");	
	scanf("%d",&NewBookID);
	index = search(NewBookID);
	if(index == -1)  //new book
	{
		printf("Sorry this book does not exist\n\n");
	}
	else 
	{
		BookCounter--;
		TotalBookCounter--;
		ReArrange(index);
		printf("deleted syccessfully \n\n");
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
	printf("A %d copies of this book has been added successfully\n\n",copies);
}




