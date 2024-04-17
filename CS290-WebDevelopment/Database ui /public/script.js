/*******************************************************************
* description: adding functionality to addExerciseButton	
* this function is sets up the user input and adds a delete and update button 
* it also displays the table that has been saved with user data 
********************************************************************/
document.getElementById('addExerciseButton').addEventListener('click',function(event){     	
	
	var addExercise = document.getElementById("addExercise");               //gets form id so we can edit it

	
	var req = new XMLHttpRequest();

	
	var param =         "exercise="+addExercise.elements.exercise.value+    //setting the parameters so we can send it in the get request
						"&reps="+addExercise.elements.reps.value+
						"&weight="+addExercise.elements.weight.value+
						"&date="+addExercise.elements.date.value;
	
	if(addExercise.elements.unitCheck.checked){
		param += "&unitCheck=1";                                     //if they checked lbs then set unitCheck to 1 (for boolean value)
	}
	else{
		param += "&unitCheck=0";									//else value is 0 and it is kgs
	}

	
	req.open("GET", "/insert?" + param, true);                 //opening the get request and set the last value to true for asynchronous request
	req.setRequestHeader('Content-Type','application/x-www-form-urlencoded');

	
	req.addEventListener('load', function(){                        //adding to the table once it loads properly
		if(req.status >= 200 && req.status < 400){

			
			var response = JSON.parse(req.responseText);            //the response is now saved
			var id = response.inserted;

			
			var table = document.getElementById("exerciseTable");   //save the table to add more to it

			
			var row = table.insertRow(-1);                          //this variable is so we can add to the table each time
			
			var exerciseName = document.createElement('td');                //the following creates table data by grabbing the values
			exerciseName.textContent = addExercise.elements.exercise.value; //the values are supplied by the user and then appendes them to the table
			row.appendChild(exerciseName);

			
			var repsCounted = document.createElement('td');
			repsCounted.textContent = addExercise.elements.reps.value;		//adding reps 
			row.appendChild(repsCounted);

			
			var weightLifted = document.createElement('td');
			weightLifted.textContent = addExercise.elements.weight.value;	//adding weight
			row.appendChild(weightLifted);


            var dateDone = document.createElement('td');
			dateDone.textContent = addExercise.elements.date.value;			//adding date
			row.appendChild(dateDone);
            
			var unitChecker = document.createElement('td');
			if(addExercise.elements.unitCheck.checked){                 //if they checked pounds then add lbs
				unitChecker.textContent = "lbs";
			}
			else{
				unitChecker.textContent = "kg";                         //otherwise it is kg if not checked
			}
			row.appendChild(unitChecker);
            
            	

			var updateData = document.createElement('td');              //this will add an update button to the table to redirect to a different page and update the exercise
			var updateDataLink = document.createElement('a');
			updateDataLink.setAttribute('href','/updateTable?id=' + id);      //this is placed in the views folder so we redirect here so we set it's href value to the handlebars file
			var updateButton = document.createElement('input');         	  //create the button
			updateButton.setAttribute('value','Update Exercise');       	 //setting the attributes for the button ^
            updateButton.setAttribute('type','button');         
			updateDataLink.appendChild(updateButton);
			updateData.appendChild(updateDataLink);
			row.appendChild(updateData);                            		//here the button is added to the table           
            
   
			var deleteCell = document.createElement('td');                  //this will add a delete button to remove exercises
			var deleteButton = document.createElement('input');             //here we are createing a  button
			deleteButton.setAttribute('type','button');
			deleteButton.setAttribute('name','delete');                     //once again we are setting the attributes for the button^
			deleteButton.setAttribute('value','Delete');
			deleteButton.setAttribute('onClick', 'deleteData("dataTable",' + id +')');
			var deleteHidden = document.createElement('input');             //this is the hidden input to remove elements from database as sugested
			deleteHidden.setAttribute('type','hidden');
			deleteHidden.setAttribute('id', 'delete' + id);
			deleteCell.appendChild(deleteButton);                           //add both buttons to the cell
			deleteCell.appendChild(deleteHidden);
			row.appendChild(deleteCell);                                    //now adding to the table itself

		}
		else {
	    	console.log("error");
		}
	});
	
	
	req.send("/insert?" + param);                               //this send the request to the server
	event.preventDefault();                                     //always included
});


/*******************************************************************
* description: this function is used to delete data 
* this function searches for the item that is to be deleted 
*  once found a request is sent so it can be deleted 
********************************************************************/
function deleteData(tableId, id){                                
    var deleteItem = "delete" + id;                             //creating a variable to use to search for in the loop (allows us to find the hidden id)	
	var table = document.getElementById("exerciseTable");       //saving the table and the number of rows to use for a loop
	var numRows = table.rows.length;

	
	for(var i = 1; i < numRows; i++){                           //loops through the table for number of existing rows
		var row = table.rows[i];
		var findData = row.getElementsByTagName("td");		    //this finds each table data and save it
		var erase = findData[findData.length -1];		        
		if(erase.children[1].id === deleteItem){                //removes data from the table when it is found
			table.deleteRow(i);
		}

	}

	var req = new XMLHttpRequest();
	

	req.open("GET", "/delete?id=" + id, true);              //opens the request to delete data

	req.addEventListener("load",function(){
		if(req.status >= 200 && req.status < 400){          //this checks if the request has occured properly
	    	console.log('success');
		} else {
		    console.log('error');
		}
	});

	req.send("/delete?id=" + id);                           //this sends the request

}