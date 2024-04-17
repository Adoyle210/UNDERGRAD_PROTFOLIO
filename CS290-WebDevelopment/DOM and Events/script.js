/* Function name: makeTable
    parameters: None
    desctption: makes a 4X4 table (including the header row) 
 */
function makeTable(){
    var body = document.getElementsByTagName("body")[0]; //creates a reference to add the table to the body at the end 
    var createTable = document.createElement("table");  //making the table 
    var createTableBody = document.createElement("tbody"); //making the body for the table
    for(var i = 0; i < 4; i++){
        var createRow = document.createElement("tr"); //creating four table rows 
        for(var j = 0; j < 4; j ++){
            if(i == 0){ //checks if i == 0 to make the header area of the table 
               var tableHeader = document.createElement("th");
               var tableHeaderText = document.createTextNode("Header " + (j +1)); //the header text will be header 1, header 2 ... etc.
               tableHeader.appendChild(tableHeaderText); //adding the tables text to the tableHeader(element) 
               createRow.appendChild(tableHeader); // adding the pervious lines to the rows 
            }
            else{   //the other cells of the table that are not the header 
                var cell = document.createElement("td");
                var cellText =document.createTextNode((i) + ',' + (j+1));   //adds the cells data as its place on the table 
                cell.appendChild(cellText); //adding cell's text  to the cell
                createRow.appendChild(cell); //adding  the cell to the rows
            }
        }
        createTableBody.appendChild(createRow); //adding the rows to the table 
    }
    createTable.appendChild(createTableBody);
    body.appendChild(createTable);  //puts table in 
    createTable.setAttribute("border", "2px"); //seting a boarder so the table is thicker 
}

/* Function name: makeButton
    parameters: None
    desctption: set up for all the buttons (there are five)
 */
function makeButton(){
    //#1 Up button:
    var upButton = document.createElement("button");
    upButton.id = "up";
    var upButtonText = document.createTextNode("Up");
    upButton.appendChild(upButtonText);
    document.body.appendChild(upButton);

    //#2 down button:
    var downButton = document.createElement("button");
    downButton.id = "down";
    var downButtonText = document.createTextNode("Down");
    downButton.appendChild(downButtonText);
    document.body.appendChild(downButton);

    //#3 left button:
    var leftButton = document.createElement("button");
    leftButton.id = "left";
    var leftButtonText = document.createTextNode("Left");
    leftButton.appendChild(leftButtonText);
    document.body.appendChild(leftButton);

    //#4 right button:
    var rightButton = document.createElement("button");
    rightButton.id = "right";
    var rightButtonText = document.createTextNode("Right");
    rightButton.appendChild(rightButtonText);
    document.body.appendChild(rightButton);

    //#5 Mark button:
    var markButton = document.createElement("button");
    markButton.id = "mark";
    var markButtonText = document.createTextNode("Mark Cell");
    markButton.appendChild(markButtonText);
    document.body.appendChild(markButton);
}

/* Function name: moveUp
    parameters: None
    desctption: a directional button to move up 
 */
function moveUp(){
    current = document.getElementById("curr");
    if(current.parentNode.rowIndex <= 1){return; } // wont do anything at the top
    var tempIndex = current.cellIndex; //holds the index column for the loop 
    current.style.borderWidth = "2px"; //setting style 
    current.removeAttribute("id"); //clears id 
    current = current.parentNode;
    current = current.previousElementSibling;
    current = current.firstElementChild; //sets current cell to the first element
    for(var i = 0; i < tempIndex; i ++){
        current = current.nextElementSibling;
    }
    current.style.borderWidth = "4px"; //setting thick boarder style to see the selected cell 
    current.id = "curr"; // reassigns id
}

/* Function name: moveDown
    parameters: None
    desctption: a directional button to move Down 
 */
function moveDown(){
    current = document.getElementById("curr");
    if(current.parentNode.rowIndex >= 3){return; } // wont do anything at at the bottom
    var tempIndex = current.cellIndex; //holds the index of the column for the loop 
    current.style.borderWidth = "2px";
    current.removeAttribute("id");
    current = current.parentNode;
    current = current.nextElementSibling;
    current =  current.firstElementChild; //sets current cell to first element 
    for(var i = 0; i < tempIndex; i ++){
        current = current.nextElementSibling;
    }
    current.style.borderWidth = "4px";
    current.id = "curr";
}

/* Function name: moveLeft
    parameters: None
    desctption: a directional button to move Left
 */
function moveLeft(){
    current = document.getElementById("curr");
    if(current.cellIndex == 0){return;} // wont do anything if all the way to the left
    current.style.borderWidth = "2px";
    current.removeAttribute("id");
    current = current.previousElementSibling;
    current.style.borderWidth = "4px";
    current.id = "curr";
}

/* Function name: moveRight
    parameters: None
    desctption: a directional button to move Right
 */
function moveRight(){
    current = document.getElementById("curr");
    if(current.cellIndex == 3){return;} //wont do anything if all the way to the right 
    current.style.borderWidth = "2px";
    current.removeAttribute("id");
    current = current.nextElementSibling;
    current.style.borderWidth = "4px";
    current.id = "curr"
}

/* Function name: markCell
    parameters: None
    desctption: makes a button labeled mark cell that marks the cell 
 */
function markCell(){
    current = document.getElementById("curr");
    current.style.backgroundColor = "#F6E481";      // changes current to yellow
}

/* Function name: main
    parameters: None
    desctption: does all the set up by making the table and buttons, as well as setting buttons to work with clicks 
 */
function main(){
    //set up of table and buttons:
    makeTable();
    makeButton();

    //setting up current for the buttons:
    var current = document.getElementsByTagName("td")[0];   //setting the first selected cell to the top left nonheader cell
    current.id = "curr"; 
    current.style.borderWidth = "4px"; 

    //setting up the five button's functions 
    document.getElementById("up").addEventListener("click", moveUp);
    document.getElementById("down").addEventListener("click", moveDown);
    document.getElementById("left").addEventListener("click", moveLeft);
    document.getElementById("right").addEventListener("click", moveRight);
    document.getElementById("mark").addEventListener("click",markCell);
}

main(); //runs everything 