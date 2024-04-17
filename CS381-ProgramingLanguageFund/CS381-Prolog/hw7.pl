/******************************************************************
* CS 381: Homework 7
* By Alexis Doyle
******************************************************************/

/* course(course_number, course_name, credits) */

course(cs101,python, 2).
course(mth210, calculusI, 5).
course(cs120, web_design, 3).
course(cs200, data_structures, 4).
course(cs210, algorithms, 4).
course(wrt101, basic_writing, 3).

/* section(CRN, course_number) */

section(1522,cs101).
section(1122,cs101).
section(2322,mth210).
section(2421,cs120).
section(8522,mth210).
section(1621,cs200).
section(7822,mth210).
section(2822,cs210).
section(3522,wrt101).

/* place( CRN, building, time) */

place(1522,owen102,10).
place(1122,dear118,11).
place(2322,with210,11).
place(2421,cov216,15).
place(8522,kec1001,13).
place(1621,cov216,14).
place(7822,kec1001,14).
place(2822,owen102,13).
place(3522,with210,15).

/* enroll(sid, CRN) */

enroll(122,1522).
enroll(122,8522).
enroll(150,1522).
enroll(150,2421).
enroll(212,7822).
enroll(300,2822).
enroll(300,8522).
enroll(310,3522).
enroll(310,8522).
enroll(310,1621).
enroll(175,2822).
enroll(175,7822).
enroll(175,3522).
enroll(410,1621).
enroll(410,7822).
enroll(113,3522).

/* student(sid, student_name, major) */

student(122, mary, cs).
student(150, john, math).
student(212, jim, ece).
student(300, lee, cs).
student(310, pat, cs).
student(175, amy, math).
student(410, john, cs).
student(113, zoe, ece).

/*START OF CODE PROBLEM 1*/
/******************************************************************
*   PART A:
*   Define a predicate schedule/4 that gives for a student (by sid) 
*   the course name, building and time of the classes the student 
*   is taking
*   x  = SID    c = course name     b = building    t = time
*   y = CRN     z = course number  
******************************************************************/
schedule(X,C,B,T) :- enroll(X,Y), place(Y,B,T), section(Y,Z), course(Z,C,_).

/******************************************************************
*   PART B:
*   Define a predicate schedule/3 that gives for a student (by sid), 
*   he students name and the names of the courses the student
*   is taking.
******************************************************************/
schedule(X,N,C) :- student(X,N,_), enroll(X,Y), section(Y,Z), course(Z,C,_).

/******************************************************************
*   PART C:
*   Define a predicate offer/4 that gives, the course number,
*   course name, CRNs for sections and times the sections of 
*   of the course are offered. 
******************************************************************/
offer(X,N,C,T) :- section(C,X), place(C,_,T), course(X,N,_).

/******************************************************************
*   PART D:
*   Define a predicate conflict/3 that can compute conflicts in a 
*   student’s schedule. A conflict exists if a student is enrolled
*   in two classes that are scheduled to meet at the same time. 
*   The arguments of conflict are a student’s sid and two CRNs for 
*   sections of classes. If the students is not enrolled in the 
*   section then a false is returned.
******************************************************************/
conflict(Z,X,Y) :- enroll(Z,X), place(X, _, XT), enroll(Z,Y), place(Y, _, XT), X \= Y.

/******************************************************************
*   PART E:
*   Define a predicate meet/2 that can determine pairs of students 
*   that can meet in a classroom by either attending the same class 
*   or by having classes that are back to back in the same classroom.
*   Meet will take a two student sids as arguments.
*   meet(X,Y) :- enroll(X, XC), enroll(Y,XC), X \= Y. (/wout time)
******************************************************************/
meet(X,Y) :- enroll(X, XC), place(XC, XB, XT), enroll(Y,YC), place(YC,XB, XT), X \= Y.
meet(X,Y) :- enroll(X, XC), place(XC, XB, XT), enroll(Y,YC), XT1 is XT+1, place(YC,XB, XT1).
meet(X,Y) :- enroll(X, XC), place(XC, XB, XT), enroll(Y,YC), XT2 is XT-1, place(YC,XB, XT2).

/******************************************************************
*   PART F:
*   Define a predicate roster/3 that produces a list of all students 
*   talking a section of a course. The arguments to roster are 
*   roster(CRN, Student_name).
******************************************************************/
roster(X,Sname) :- enroll(Y,X), student(Y, Sname, _).

/******************************************************************
*   PART G:
*   Define a predicate highCredits/1 that produces a list of courses 
*   that are 4 or more credits. The argument to highCredits is a 
*   course_name.
******************************************************************/
highCredits(Cname) :- course(_,Cname, X), X >= 4.


/*START OF CODE PROBLEM 2*/
/******************************************************************
*   PART A:
*   Define a Prolog predicate rdup(L,M) to remove duplicates from an 
*   ordered list L. The resulting list should be bound to M. Note 
*   that M must contain each element of L exactly once and in the 
*   same order as in L. You can assume that L is an ordered list.
******************************************************************/
rdup(L,M) :- rdup3(L,M,[]).
rdup3([],[],_).
rdup3([X|L],[X|M],T) :- not(member(X,T)),rdup3(L,M,[X|T]).
rdup3([X|L],[Y|M],T) :- (member(X,T)),rdup3(L,[Y|M],T).
rdup3([X|L],[],T) :- (member(X,T)),rdup3(L,[],T).

/******************************************************************
*   PART B:
*   Define a Prolog predicate flat(L,F) that binds to F the flat 
*   list of all elemets in L ( where L can be a possibly nexted list).
*   For example flat( [a,b, [c,d],[],[[e]],f], L) yields L = [a,b,c,d,e,f].
******************************************************************/
flat(L,F) :- flat3(L,[],F).
flat3([],F,F).
flat3([X|L],T,F) :- flat3(X,Y,F),flat3(L,T,Y).
flat3(X,F,[X|F]) :- not(is_list(X)).

/******************************************************************
*   PART C:
*   Define a Prolog predicate project/3 that selects elements from 
*   a list by their position and collects them in a result list. 
*   For example, the goal of project( [2,4],[a,b,c,d],L) should 
*   produce the answer L=[b,d]. You can assume that the numbers 
*   in the first list are strictly increasing, that is, your 
*   implementation does not have to care about situations like 
*   project([1,1,2],..) or project([2,5,3],..).
******************************************************************/
/*project(X,Y,Z) :- project4(X,Y,Z,W).
project4(Y,[W|X],Y,W) :- !.
project4(T,[_|X],Y,W) :- T1 is T+1, project4(X,T1,Y,W). */
