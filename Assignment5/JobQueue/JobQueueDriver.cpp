/****************************************************************/
/*                Job Queue Driver File                 */
/****************************************************************/
/* TODO: Implement menu options as described in the writeup     */
/****************************************************************/

#include "JobQueue.hpp"
#include <iostream>
// you may include more libraries as needed

using namespace std;

/*
 * Purpose: displays a menu with options
 * @param none
 * @return none
 */
void menu()
{
	cout << "*----------------------------------------*" << endl;
	cout << "Choose an option:" << endl;
    cout << "1. Add jobs into the queue" << endl;
	cout << "2. Dispatch jobs from the queue" << endl;
	cout << "3. Return the queue size and exit" << endl;
	cout << "*----------------------------------------*" << endl;
}
// Use getline for reading
int main(int argc, char const *argv[])
{
	/* TODO */
	JobQueue queue;
	int choice;
	while (1) {
		menu();
		cin >> choice;
		string input;
		int numJobs;
		switch (choice) 
		{
			case 1:
				cout << "Enter the number of jobs to be created:" << endl;
				cin >> numJobs;
				for(int i = 1; i <= numJobs; i++) {
					cout << "job" << i << ":" << endl;
					cin >> input;
					queue.enqueue(input);
				}
				break;
			case 2:
				cout << "Enter the number of jobs to be dispatched:" << endl;
				cin >> numJobs;
				for (int i = 1; i <= numJobs; i++) {
					if (queue.queueSize() <= 0) {
						cout << "No more jobs to be dispatched from queue" << endl;
						break;
					}
					cout << "Dispatched: " << queue.peek() << endl;
					queue.dequeue();
				}
				break;
			case 3:
				cout << "Number of jobs in the queue:" << queue.queueSize() << endl;
				return 0;
			default:
				cout << "------- Oops! Wrong choice ------ " << endl;
				return 0;
		}
	}
	return 0;
}
