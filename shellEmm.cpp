//Corey Diehl



#include "shellEMM.h"
//  one
void GetInput(string& one, string& two);

//  two
void runCommand(string& WD, Directory * & currentDirr, 
		string& one, string& two, string& three);

//
//--------------------MAIN FUNCTION---------------------
//

int main()
{


  //  this code sets up the root directory	
  Directory Root("root");
  Directory * currentDirr;

  string input;
  string command;
  string commandParam = "blank";
  string thirdCm;
  string WD;
  


  currentDirr = & Root;
  currentDirr -> parent = currentDirr;


  //  main loop
  while(command != "quit")
  {
    WD = currentDirr -> WD;
    cout << endl << "User:~" << WD << "$";

    GetInput(command, commandParam);
    if(command == "chmod")
    {
      cin >> thirdCm;
    }

    runCommand(WD, currentDirr, command, commandParam, thirdCm);
    
  }

  return 0;
}

//
//-------------------END OF MAIN-----------------------
//


//  -------------------ONE----------------------
void GetInput(string& one, string& two)
{
  cin >> one;
  if(cin.peek() != '\n')
  {
    cin >> two;
  }
  return;
}

//  ------------------TWO----------------------
void runCommand(string& WD, Directory * & currentDirr, 
		string& one, string& two, string& three)
{

  // checks if first command is known
  if(one == "ls" || one == "cd" || one == "pwd"
		 || one == "mkdir" || one == "rmdir"
		 || one == "rm" || one == "chmod"
		 || one == "touch" || one == "quit")
  {

    if(one == "chmod")
    {
      currentDirr -> chmod(two, three);
    }

    //  IF TWO IS BLANK
    if(two == "blank")
    {
      if(one == "ls")
      {
	currentDirr -> ls();
      }
     
      if(one == "pwd")
      {
        cout << endl << WD;
      }

    }
    //  IF TWO HAS BEEN SET
    else
    {
      if(one == "ls")
      {
        if(two == "-l")
	{
          currentDirr -> lsLong();
	}
      }
      if(one == "rm")
      {
        currentDirr -> rm(two);
      }
      if(one == "touch")
      {
        currentDirr -> touch(two);
      }

      if(one == "mkdir")
      {
	currentDirr -> mkdir(two);
      }

      if(one == "rmdir")
      {
        currentDirr -> rmdir(two);
      }
      //  start of CD
      if(one == "cd")
      {
        if(two == "..")
	{
          currentDirr = currentDirr -> parent;
	}
	else
	{
          for(unsigned int i=0; i < currentDirr -> subDirectories.size(); i++)
	  {
            if(currentDirr -> subDirectories[i] -> name == two)
	    {
              currentDirr = currentDirr -> subDirectories[i];
	    }
	  }
        }
      }     
      //  End of CD
    }
  
  }
  //  in cae first command is unknown
  else
  {
    cout << endl << "unknown command" << endl;
  }


  //resets second imput
  two = "blank";
  

  return;
}

