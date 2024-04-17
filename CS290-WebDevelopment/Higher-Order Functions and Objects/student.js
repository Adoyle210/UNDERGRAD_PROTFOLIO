// You are not permitted to change this in any way
function Student(name, major, yearInSchool, club) {
    this.name = name; // string, (e.g. "Jim", "Pam", "Michael")
    this.major = major; // string, (e.g. "Computer Science", "Art", "Business")
    this.yearInSchool = yearInSchool; // int, (e.g. 1, 2, 3, 4)
    this.club = club; // string, (e.g. "Improv", "Art")
  }
  
  var students = [
    new Student("Pam", "Art", 2, "Art"),
    new Student("Michael", "Business", 4, "Improv"),
    new Student("Dwight", "Horticulture", 1, "Karate"),
    new Student("Jim", "Sports Science", 2, "Guitar"),
    new Student("Angela", "Accounting", 4, "Cat"),
    new Student("Toby", "Human Resources", 3, "Photography")
  ];
  
  /* This function sorts arrays using an arbitrary comparator. You pass it a comparator 
  and an array of objects appropriate for that comparator and it will return a new array 
  which is sorted with the largest object in index 0 and the smallest in the last index*/
  function sortArr(comparator, array) {
    // your code here
    var sortedArr = array.slice(0);   //making a copy of the old array
      var tempArr;  													
      for(var i = 0; i < sortedArr.length - 1; i++)  //goes through whole array
      {
          for(var j = i + 1; j < sortedArr.length; j++) //nest loop to compare array
          {
              if(comparator(sortedArr[j], sortedArr[i]))    //switching arr after its compared
              {
                  tempArr = sortedArr[i];
                  sortedArr[i] = sortedArr[j];
                  sortedArr[j] = tempArr;
              }
          }
      }
      return sortedArr;
  }
  
  /* A comparator takes two arguments and uses some algorithm to compare them. If the first 
  argument is larger or greater than the 2nd it returns true, otherwise it returns false.
  Here is an example that works on integers*/
  function exComparator( int1, int2){
    if (int1 > int2){
        return true;
    } 
    else {
        return false;
    }
  }
  
  /* For all comparators if students are 'tied' according to the comparison rules then the order of 
  those 'tied' students is not specified and either can come first*/
  
  /* This compares two students based on their year in school. Sort in descending order.*/
  function yearComparator(student1, student2) {
   //your code here
   if(student1.yearInSchool > student2.yearInSchool){		//compares year 
        return true;
    }
    else{
        return false;
    }
  }
  
  /* This compares two students based on their major. It should be case insensitive and 
  makes which are alphabetically earlier in the alphabet are "greater" than ones that 
  come later (from A-Z).*/
  function majorComparator(student1, student2) {
  //your code here
    if(student1.major.charCodeAt(0) < student2.major.charCodeAt(0)){ //looks at ascii value to compare
        return true;
    }
    else{
        return false;
    }
  }
  
  /* This compares two students based on the club they're in. The ordering from "greatest" 
  to "least" is as follows: improv, cat, art, guitar, (types not otherwise listed). 
  It should be case insensitive. If two clubs are of equal type then the student who
  has the higher year in school should be "greater."*/
  function clubComparator(student1, student2) {
  //your code here
    var order = function(student) // replacing with numbers using a switch case to give them an order
      {
          switch(student.club)
          {
              case "Improv":
              return 1;
              break;
              
              case "Cat":
              return 2;
              break;
              
              case "Art":
              return 3;
              break;
              
              case "Guitar":
              return 4;
              break;
              
              default:		// this is for clubs not listed 
              return 5;
          }
      }
      
      if(order(student1) < order(student2))  //looks at assigned order number to see which is greater
      {
          return true;
      }
      
      else if(order(student1) == order(student2)) //compares the students year if both are in the same club to determine the order 
      {
          return yearComparator(student1, student2);
      }
      else
      {
          return false;
      }
  }
  
  // Log me function 
  Student.prototype.logMe = function(bool)
  {
      if(bool == true)
      {
          console.log(this.name + " " + this.major + " " + this.yearInSchool + " " + this.club); //when club is needed
      }
      else
      {
          console.log(this.name + " " + this.major + " " + this.yearInSchool + " ");//for when club is not required 
      }
  }
  
  //printing array function
  function printArray(studentArr, bool)
  {
      studentArr.forEach(function(x)
      {
          x.logMe(bool);
      })
  }
  
  
  
  /* Your program should output the following to the console.log, including each of the opening and closing 
  stars. All values in parenthesis should be replaced with appropriate values. To accomplish this, you will 
  have to sort the array of students using each comparator and then loop through the array and and call logMe
  on each student of the now-sorted array. If the argument is 'true' then it prints the student's name, major, 
  year in school, and club affiliation. If the argument is 'false' then the club affiliation is ommited and 
  just the student's name, major and year in school is logged. Please carefully note which sorted results require
  the club to be displayed and which do not.
  
  **********
  The students sorted by year in school are:
  (Name - Major - Year) // of the "greatest" student
  ...
  (Name - Major - Year) // of the "least" student
  
  **********
  The students sorted by major are:
  (Name - Major - Year) // of the "greatest" student
  ...
  (Name - Major - Year) // of the "least" student
  
  **********
  The students sorted by club affiliation are:
  (Name - Major - Year - Club) // of the "greatest" student
  ...
  (Name - Major - Year - Club) // of the "least" student
  
  **********
  
  As an example of what is expected to be printed to the console with logMe being sent True for a single student:
  Jim - Sports Science - 2 - Guitar
  
  */
  
  var studentYear = sortArr(yearComparator, students);  //Sorts the years the students are in school
  var studentMajor = sortArr(majorComparator, students);  //Sorts the majors of the students 
  var studentClub = sortArr(clubComparator, students);   //Sorts the clubs of the students 
  
  console.log("*****");
  console.log("The students sorted by year in school are:");
  printArray(studentYear, false);
  
  console.log("*****");
  console.log("The students sorted by major are:");
  printArray(studentMajor, false);
  
  console.log("*****");
  console.log("The students sorted by club affiliation are:");
  printArray(studentClub, true);
  console.log("*****");
  