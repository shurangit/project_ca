#include <iostream> 
#include <iomanip> 
#include <string>
#include <cstdlib>  
#include <fstream> 
#include <map> 

using namespace std;
int readaddr(ifstream *); // read address line by line
void delete_least(map<int,int> *); //delete the address had the least state when map.size()>=8

int main()
{
	int curr; 
	int right = 0; // no.of right prediction
	int wrong = 0;// no. of wrong prediction
	int miss = 0; // no.of branch miss
	int hit=0; // no.of hits
	map<int , int> add_state; // map<key, value> key--address, value--state, state:00->0,01->1,10->2,11->3; 0,1->not taken, 2,3->taken
	map<int , int>::iterator tag ; 

	ifstream txtfile("d:\\vs2012\\code\\sample1\\debug\\itrace-long.txt", ios::in);
	ifstream &inputtxt = txtfile;

	int prev = -1; // start value
	while((curr=readaddr(&inputtxt))!=-1)
	{
		if(prev == -1) // first time read a file
		{
			prev = curr; // define the first address as previous address
			continue; 
		}
		tag = add_state.find(prev); 
		if( (curr-prev) != 4 ) //  branch
		{
			if(tag != add_state.end()) //address exists
			{
				if(tag->second==0||tag->second==1) //predict no branch
				{
					wrong++;

				} 
				else // predict branch
				{
					right++;
				}
				add_state[prev] ++; // branch->state+1
				if(tag->second >3 )
				{
					add_state[prev] = 3;
				}
				hit++;
			} 
			else //address doesn't exist
			{
				if(add_state.size()>=8)//8 entries
				{
					delete_least(&add_state); 
				}
				add_state.insert(make_pair(prev,1)); // initialize the value as weakly taken 01->1
				miss++;
			}
		}
		else // no branch
		{
			if(tag != add_state.end()) //exist address
			{
				if(tag->second==0||tag->second==1)//predict no branch
				{
					right++;
				} 
				else  //predict  branch
				{
					wrong++;
					}
					add_state[prev] --; // no branch->state-1
					if(tag->second < 0)
					{
						add_state.erase(prev);
					}
			}

			
		
}
prev = curr;
}
cout<<"The no.of right prediction is "<<right<<endl;
cout<<"The no.of wrong prediction is "<<wrong<<endl;
cout<<"The no of miss branch is "<<miss<<endl;
cout<<"The no.of hit is "<<hit<<endl;
cout<<"8 entries goes like the followings:"<<endl;

for (tag = add_state.begin(); tag !=add_state.end(); tag++ ) 
{
	cout << "Address: " << tag->first << " \t State: " <<tag-> second << endl;
}
return 0;
}

void delete_least(map<int,int> *add_state)
{
	map<int , int>::iterator tag ;
	for(int i=0;i<=3;i++) // find state from 0, once delete the least number, return
	{
		for (tag = add_state->begin(); tag !=add_state->end(); tag++ ) 
		{
			if(tag->second==i)
			{
				add_state->erase(tag->first);
				return;
			}
		}
	}
}

int readaddr(ifstream *inputtxtfile)
{
	int address;
	if (!(*inputtxtfile)) 
	{
		cerr << "txtfile could not find" << endl; // output error message
		exit( 1 );
}
	string Line;
	if(getline(*inputtxtfile,Line))
	{
		sscanf_s(Line.data(),"%x",&address); 
		return address;
	}
	return -1;
}
