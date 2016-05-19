//
//  main.cpp
//  Maintenace
//
//  Created by Christopher Edler on 11/26/14.
//  Copyright (c) 2014 ChristopherEdler. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <string>       
#include <map>
#include <vector>
#include <utility>
#include <cstdlib>
#include <stdio.h>
using namespace std;


void explode(map<char, vector<char>>& map1, char transaction_to_explode,  int depth, int& max, vector<char>& vec2, vector<char>& vec3);         //Explodes selected transaction and all modules attached

void retrieveDefects(map<char, vector<char>>& map1, char transaction_to_explode,  int depth, int& max, vector<char>& vec, char defect);      //Retrieves the paths of the defective

void bubblesort(string& list_module);       //Sorts list alphabetically

void modifyTransactions(string& transaction, string module);        //Deletes any modules in transactions

void modifyModules(string module);          //Deletes any duplicate modules

void displayTransactions_and_Count(string transaction);     //Displays the transactions and the number of transactions

void displayModules_and_Count(string module);               //Displays the modules and the number of modules

void retrieveDepth(map<char, vector<char>>& map1, char transaction_to_explode,  int depth, int& max);


int main()
{
    ifstream file1("/Users/Christopher/Desktop/Maintenace/input.txt");     //Location of file (SUBJECT TO CHANGE)
    
/*----------------------------------------------------------------------------------------------*/
    if(!file1.is_open())
    {
        exit(EXIT_FAILURE);     //Exit program if file does not open
    }
    
    
    string line, modules, transactions;
    
    char explosion;
    
    
    int count = 1, max = 0;
    
    vector<char> vec, vec2, vec3;
   
    file1 >> line;            //Gets first module in the file
    
    map<char,vector<char>>place;
    
    
    
/*---------------------------------------------------------------------------------------------*/
    
    while(file1.good())         //While not at the end of the file
    {
        while(line[2] == ';')                           //Checks that module is being read in
        {
            place[line[0]].push_back(line[1]);
            
            modules.push_back(line[1]);                 //Populates array of modules
            transactions.push_back(line[0]);            //Populates array of transactions
            
            file1 >> line;
            
            count++;
        }
        
        bubblesort(modules);            //Puts the modules into alphabetical order
        bubblesort(transactions);       //Puts the transactions into alphabetical order
        
        modifyTransactions(transactions, modules);          //Rids transaction list of any modules
        modifyModules(modules);                             //Rids modules of any duplicates
        
        
        cout << "-----------------------------------------------"<<endl<<endl;
        cout << "MAINTENANCE PROJECT"<<endl<<endl;;
        cout << "-----------------------------------------------"<<endl<<endl;
        
       
        displayModules_and_Count(modules);
        displayTransactions_and_Count(transactions);

       
/*----------------------------EXPLOSION---------------------------------------------------------*/
        
       
        cout<< "Explode: " << line[0] << endl ;
        
        
        explosion = line[0];            //Creates character of transaction that is being exploded
        
        
        retrieveDepth(place, explosion,  0, max);
        
        
        explode(place, explosion,  0, max, vec2, vec3);
        
        cout <<endl<<"(These modules should be starred. They have been called previously: ";
        for(int i= 0; i<vec3.size();i++)
        {
            cout<<vec3[i]<< ",";
        }
        cout<<")"<<endl;
        
    
        cout<<endl<<"-----------------------------------------------"<<endl;
        
 /*---------------------------------------------------------------------------------------------*/
        
        
        file1 >> line;      //Now at defective module line
        
        cout << "Defective module: "<< line[0] <<endl;
        
        char defect = line[0];
        
    
        retrieveDefects(place, explosion,  0,  max, vec, defect);
        
        cout<<endl<<"-----------------------------------------------"<<endl;
    

        file1 >> line;      //Done reading file
        
    }

/*-----------------------------------------------------------------------------------------------*/

  
    return 0;
}

void explode(map<char, vector<char>>& map1, char transaction_to_explode,  int depth, int& max, vector<char>& vec2, vector<char>& vec3)
{
    
    depth = depth + 1;
    
    
    for(int bar = 0; bar < (depth-1); bar++)
    {
        cout << "  | ";
    }
    
    
    cout << transaction_to_explode;
    
    for(int i = 0; i<vec2.size();i++)
    {
        if(transaction_to_explode==vec2[i])
        {
            vec3.push_back(transaction_to_explode);
        }
    }
    
    for(int bar_after = 0; bar_after < (max-depth); bar_after++)
    {
        cout<< " |  ";
    }
    
    
    
    vec2.push_back(transaction_to_explode);             //Storing already exploded modules.  For use of asterisks
    

    cout << endl;
    
    if(map1[transaction_to_explode].empty())            //If there is no characters in the vector
    {
        if(depth > max)
        {
            max = depth;
        }
        else
        {
            
        }
    }
    else
    {
        for(int count = 0; count < map1[transaction_to_explode].size(); count++)
        {
            explode(map1, map1[transaction_to_explode][count], depth, max, vec2, vec3);
        }
    }
    
    depth = depth - 1;
        
     
}

void bubblesort(string& list_module)
{
    for(int x=0; x<list_module.size(); x++)
        
    {
        
        for(int y=0; y<list_module.size()-1; y++)
            
        {
            
            if(list_module[y]>list_module[y+1])
                
            {
                
                int temp = list_module[y+1];
                
                list_module[y+1] = list_module[y];
                
                list_module[y] = temp;
                
            }
            
        }
        
    }
}

void modifyTransactions(string& transaction, string module)
{
    for(int current=0; current< transaction.size(); current++)
    {
        for(int current2 = 0; current2 < transaction.size(); current2++)
        {
            while(transaction[current] == module[current2] && current != current2)
            {
                transaction.erase(current,1);
            }
            
            if(transaction[current]  == transaction[current+1])
            {
                transaction.erase(current,1);
            }
        }
    }
}


void modifyModules(string module)
{
    for(int current=0; current< module.size(); current++)
    {
        for(int current2 = 0; current2 < module.size(); current2++)
        {
            while(module[current] == module[current2] && current != current2)
            {
                module.erase(current2,1);
            }
        }
    }
}


void displayModules_and_Count(string module)
{
    cout<< "Modules: "<<endl<<endl;
    
    for(int i = 0; i < module.size(); i++)
    {
        cout<< " [" <<module[i] << "] " <<endl;
    }

    cout<<endl << "Module count: " << module.size() <<endl;
    cout << "-----------------------------------------------"<<endl;
}

void displayTransactions_and_Count(string transaction)
{
    cout<< "Transactions: " << transaction <<endl<<endl;
    for(int i = 0; i < transaction.size(); i++)
    {
        cout<< " [" <<transaction[i] << "] " <<endl;
    }

    cout<<endl << "Transaction count: " << transaction.size() <<endl;
    cout<< "-----------------------------------------------"<<endl;
}

void retrieveDepth(map<char, vector<char>>& map1, char transaction_to_explode,  int depth, int& max)
{
    depth = depth + 1;
    
    if(map1[transaction_to_explode].empty())
    {
        if(depth > max)
        {
            max = depth;
        }
    }
    else
    {
        for(int count = 0; count < map1[transaction_to_explode].size(); count++)
        {
            retrieveDepth(map1, map1[transaction_to_explode][count], depth, max);
        }
    }
    
    depth = depth - 1;
    
}

void retrieveDefects(map<char, vector<char>>& map1, char transaction_to_explode,  int depth, int& max, vector<char>& vec, char defect)
{
    depth = depth + 1;
    
    vec.push_back(transaction_to_explode);
    
        if(vec[vec.size()-1] == defect)
        {
            for(int i = 0; i< vec.size(); i++)
            {
                cout << vec[i];
            }
            cout<<endl;
        }
        
        else{
            
        }
    
    
    
 
    
    if(map1[transaction_to_explode].empty())            //If there is no characters in the vector
    {
        if(depth > max)
        {
            max = depth;
        }
        else
        {
            
        }
    }
    else
    {
        for(int count = 0; count < map1[transaction_to_explode].size(); count++)
        {
            retrieveDefects(map1, map1[transaction_to_explode][count], depth, max, vec, defect);
        }
    }
    
    vec.pop_back();
    
    depth = depth - 1;
    
    
}
