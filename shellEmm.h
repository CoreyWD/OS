#ifndef SHELLEMM_H
#define SHELLEMM_H

#include <string>
#include <cstdlib>
#include <iostream>
#include <vector>
#include <time.h>
#include <fstream>
#include <ctime>


using namespace std;


//stores object of type file
class file
{
  public:
    string name;
    bool permission[10] = {0, 1, 1, 0, 1, 0, 0, 1, 0, 0};
  
    //  constructor
    file(string x)
    {
      name = x;
    }

    string now()
    {
      time_t tt = time(NULL);
      string s = ctime(&tt);
      return s.substr(0, s.size()-1);
    }

    string timeStamp = now();
    
};

class Directory
{
  public:
    string name;
    string WD;
    bool permission[10] = {1, 1, 1, 0, 1, 0, 0, 1, 0, 0};

    Directory* parent = NULL;

    vector<file> files;
    vector<Directory*> subDirectories;    
    
    //  constructor
    Directory(string x)
    {
      name = x;
      permission[0] = 1;
      WD = x + "/";
    }

    string now()
    {
      time_t tt = time(NULL);
      string s = ctime(&tt);
      return s.substr(0, s.size()-1);
    }

    string timeStamp = now();

    //  helper function for the cleanUp function in main
    void eraseHelp()
    {
      delete subDirectories[0];
      subDirectories.erase(subDirectories.begin());
      return;
    }

    //  updates timestamp on directories and files
    //  makes files if they don't exist yet
    void touch(string x)
    { 
      if(subDirectories.size() > 0)
      {
        for(unsigned int i = 0; i < subDirectories.size(); i++)
        {
          if(subDirectories[i] -> name == x)
	  {
            subDirectories[i] -> timeStamp = now();
	    return;
	  }
        }
      }
      if(files.size() > 0) 
      {
	for(unsigned int j = 0; j < files.size(); j++)
	{
	  if(files[j].name == x)
	  {
            files[j].timeStamp = now();
            return;
	  }
        }
      }
            
      file fi(x);
      files.push_back(fi);
      
      return;
    
      
    }

    //  removes file if it exists
    void rm(string x)
    {
      for(unsigned int i = 0; i < files.size(); i++)
      {
        if(files[i].name == x)
	{
          files.erase(files.begin() + i);
	  return;
	}
      }
      cout << endl << "File not found";
      return;
    }


    //  makes new subdirectory
    void mkdir(string x)
    {
      for(unsigned int i = 0; i < subDirectories.size(); i++)
      {
        if(subDirectories[i] -> name == x)
	{
          cout << endl << "Directory of that name already exists";
	  return;
	}

      }
      Directory * dir = new Directory(x);
      dir -> parent = this;
      dir -> WD = this -> WD + x + "/";
      subDirectories.push_back(dir);
      
      return;
    }

    //  removes subdirectory
    void rmdir(string x)
    {
      for(unsigned int i = 0; i < subDirectories.size(); i++)
      {
	if(subDirectories[i] -> name == x)
	{
	  if(subDirectories[i] -> files.size() == 0 
	      && subDirectories[i] -> subDirectories.size() == 0)
	  {
	    delete subDirectories[i];

            subDirectories.erase(subDirectories.begin() + i);
	    return;
	  }
	  else
	  {
            cout << endl << "Directory not empty, cannot delete";
	    return;

	  }
	}
      }
      
      cout << endl << "Directory not found";
      return;
    }



    //  prints directory
    void ls()
    {
      for(unsigned int i = 0; i < subDirectories.size(); i++)
      {
        cout << endl << subDirectories[i] -> name;
      }

      for(unsigned int j = 0; j < files.size(); j++)
      {
        cout << endl << files[j].name;
      }
    
      return;
    }

    //  changes file or directory privelages
    void chmod(string name, string x)
    {
      char temp;
      int count = 1;
      
      bool tempArr[10];
      
      bool arr0[3] = {0, 0, 0};
      bool arr1[3] = {0, 0, 1};
      bool arr2[3] = {0, 1, 0};
      bool arr3[3] = {0, 1, 1};
      bool arr4[3] = {1, 0, 0};
      bool arr5[3] = {1, 0, 1};
      bool arr6[3] = {1, 1, 0};
      bool arr7[3] = {1, 1, 1};


      for(int i = 0; i < 3; i++)
      {
        temp = x[i];
        if(temp < '0' || temp > '7')
	{
          cout << endl << "invalid input";
	  return;
	}
        for(int j = 0; j < 3; j++)
	{
          if(temp == '0')
	  {
            tempArr[count] = arr0[j];
	    count++;
	  }
	  else if(temp == '1')
	  {
            tempArr[count] = arr1[j];
	    count++;
	  }
	  else if(temp == '2')
	  {
            tempArr[count] = arr2[j];
	    count++;
	  }
	  else if(temp == '3')
	  {
            tempArr[count] = arr3[j];
            count++;
	  }
	  else if(temp == '4')
	  {
            tempArr[count] = arr4[j];
            count++;
	  }
	  else if(temp == '5')
	  {
            tempArr[count] = arr5[j];
            count++;
	  }
	  else if(temp == '6')
	  {
            tempArr[count] = arr6[j];
            count++;
	  }
	  else if(temp == '7')
	  {
            tempArr[count] = arr7[j];
            count++;
	  }
	}
      }
      
      for(unsigned int k = 0; k < subDirectories.size(); k++)
      {
        if(subDirectories[k] -> name == name)
	{
	  for(int y = 1; y < 10; y++)
	  {
            subDirectories[k] -> permission[y] = tempArr[y];
	  }
	}
      }
  
      for(unsigned int l = 0; l < files.size(); l++)
      {
        if(files[l].name == name)
	{
	  for(int z = 1; z < 10; z++)
	  {
            files[l].permission[z] = tempArr[z];
	  }
	}
      }

    }
 
    //  print to screen a more detailed list of directory contents
    void lsLong()
    {
      char permissions[10] = {'d','r','w','x','r','w','x','r','w','x'};
      for(unsigned int i = 0; i < subDirectories.size(); i++)
      {
	cout << endl;

        for(int j = 0; j < 10; j++)
	{
          if(subDirectories[i] -> permission[j] == 1)
	  {
	    cout <<  permissions[j];
	  }
          else
	  {
            cout << "-";
	  }
	}
        cout << " USER " << "GROUP " << "FILESIZE "
	     << subDirectories[i] -> timeStamp 
	     << " " << subDirectories[i] -> name;
      }

      for(unsigned int k = 0; k < files.size(); k++)
      {
	cout << endl;
        for(int l = 0; l < 10; l++)
	{
          if(files[k].permission[l] == 1)
	  {
            cout << permissions[l];
	  }
	  else
	  {
            cout << "-";
	  }
	}
        cout << " USER " << "GROUP " << "FILESIZE "
             << files[k].timeStamp << " " << files[k].name;

      }

    }

};





#endif
