#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <set>
#include <algorithm>

#define FILENAME "amazon-meta.txt"

using namespace std;

string findCustomer(string line);
string formatSubjects(set<string> new_purchases);
string incrementSubjects(string new_purchases, string cur_purchase_string);

int main()
{
	int line_count = 0;
	int id = -1;
	int iterator = 1;
	int review_count = 0;
	int j;
	int book_count = 0;
	int music_count = 0;
	int dvd_count = 0;
	int video_count = 0;
	int discontinued_count;
	ifstream input;
	string line, customer, customer_purchases, review_count_str, counts, it2_up, it2_reg;
	bool discontinued = 0;
	
	set<string> customers;
	set<string> AUC;
	vector<string> cur_pro_subject_counts;

	//AUCP String Format: A5213442 |Books[283155][2]|Nonfiction[53][4] |Music..
	//Has person Id with a space, then followed by everything they've bought with a space between each purchase type.
	//All possible purchase types (just so I don't forget): Book, Music, Video, DVD


	input.open(FILENAME);

	//count the lines
	cout << "Counting lines..." << endl;
	while(getline(input, line))
	{
		line_count++;
	}
	cout << "There are " << line_count << " lines." << endl;

	//restart at beginning of input file
	input.clear();
	input.seekg(0);

	cout << "Beginning training..." << endl;

	//train dataset
	for(int i = 1; i <  line_count + 1; i++)
	{
		getline(input, line);

		if(i > ((line_count / 10) * iterator))
		{
			if(iterator > 1)
			{
				cout << "\r";
			}
			cout << "Approximate Progress: " << iterator * 10 << "%" << endl;
			iterator++;
		}
		if(line.length() > 9)
		{
			
			if(line.compare(2,7,"group: ") == 0)
			{
				if(line[9] == 'B') book_count++;
				if(line[9] == 'M') music_count++;
				if(line[9] == 'D') dvd_count++;
				if(line[9] == 'V') video_count++;
			}
		}


		//increment id value
		if(line.compare(0,3, "Id:") == 0)
		{
			//store the previously acquired customers, only while they're unique
			
			string subjects = formatSubjects(customers);
			for(set<string>::iterator it = customers.begin(); it != customers.end(); ++it)
			{	
				set<string>::iterator it2;
				auto pair = AUC.insert(*it);
				it2 = pair.first;
				it2_up = *pair.first;
				it2_reg = *pair.first;
				
				it2++;
				if(it2 != AUC.end())
				{
					it2_up = *it2;
					//cout << "it2_up: " << it2_up << endl;
				}
				it2--;
				if(it2_up.compare(0, it2_reg.length(), it2_reg) == 0)
				{
					//cout << it2_reg << " was found equal to " << it2_up << endl;
					customer_purchases = incrementSubjects(subjects, it2_up);
					AUC.erase(it2_up);
					AUC.erase(it2_reg);
					AUC.insert(customer_purchases);
				}
				else
				{
					//cout << it2_reg << " was found to have no equal partners." << endl;
					customer_purchases = incrementSubjects(subjects, it2_reg);
					AUC.erase(it2_reg);
					AUC.insert(customer_purchases);
				}					
			}
			id++;
			discontinued = false;
			review_count = 0;
			customers.clear();
			cur_pro_subject_counts.clear();
		}

		//find if product is discontinued
		if(line.length() >= 22)
		{
			if(line.compare(2,20,"discontinued product") == 0)
			{
				discontinued = true;
			}
		}
	
		if(!discontinued)
		{
			//avoiding seg faults
			if(line.length() > 4)
			{
				if(line.compare(0, 4, "   |") == 0)
				{
					cur_pro_subject_counts.push_back(line);
				}
			}

			//avoiding seg faults
			if(line.length() > 18)
			{
				//if at line where review count is shown
				if(line.compare(2, 16, "reviews: total: ") == 0)
				{
					//find how many reviews there are
					for(j = 18; line[j] != ' '; j++)
					{
					}
					review_count_str.resize(j - 18);
					for(int k = 0; k < (j - 18); k++)
					{
						review_count_str[k] = line[k + 18];
					}
					review_count = atoi(review_count_str.c_str());
				}
			}

			if(review_count != 0)
			{
				customer = findCustomer(line);
				if(!customer.empty())
				{
					customers.insert(customer);
				}
			}
		}
	}
	cout << endl;
	cout << "Training Complete on " << id << " products, and " << AUC.size() << " unique customers." << endl;
	cout << "Of all the products, there are " << book_count << " books, ";
	cout << music_count << " CD's, " << video_count << " videos, and "<< endl;
	cout << dvd_count << " DVD's." << endl;
	/*for(set<string>::iterator it = AUC.begin(); it != AUC.end(); it++)
	{
		cout << *it << endl;
	}*/
	return 0;
}

string findCustomer(string line)
{
	int last_space = 0;
	string customer;
	unsigned int i;

	for(i = 0; line[i] != 'c' && i < line.length(); i++)
	{
	}
	if(i != line.length())
	{
		if(line.compare(i, 7, "cutomer") == 0)
		{
			while(line[i] != 'A')
			{
				i++;
			}
			last_space = i;
			while(line[i] != ' ')
			{
				i++;
			}
			customer.resize(i - last_space);
			for(unsigned int j = 0; j < (i - last_space); j++)
			{
				customer[j] = line[j + last_space];
			}
		}
	}
	return customer;
}

string formatSubjects(set<string> new_purchases)
{
	string subjects;
	for(int 
	set<string>::iterator it = new_purchases.begin();
	subjects = *it;
	cout << subjects << endl;
	return "fart";
}

string incrementSubjects(string new_purchases, string cur_purchase_string)
{
	return cur_purchase_string+" "+new_purchases;
}
