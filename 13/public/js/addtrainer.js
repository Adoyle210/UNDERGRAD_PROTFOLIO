let addtrainerform = document.getElementById('addtrainer');

addtrainerform.addEventListener("submit", function (e) {
    //this prevents the form from submmiting
    e.preventDefault(); 

    // this is to get the fields from the form
    let field_tname = document.getElementById("tnameInput");
    let field_wins = document.getElementById("winsInput");
    let field_losses = document.getElementById("lossesInput");

    //this is to get the valies from the form fields 
    let val_tname = field_tname.value;
    let val_wins = field_wins.value;
    let val_losses = field_losses.value;

    //this is to send the data as a javascript object
    let data = {
        tname: val_tname,
        wins: val_wins,
        losses: val_losses,
    }

    //setup our AJAX request
    var xhttp = new XMLHttpRequest();
    xhttp.open("POST", "/trainer/add", true);
    xhttp.setRequestHeader("Content-type", "application/json");

    //this tells out AJAX request how to resolve
    xhttp.onreadystatechange = () => {
        if(xhttp.readyState == 4 && xhttp.status == 200){
            //add new data
            addRowToTable(xhttp.response);

            //clear the input fields 
            field_tname.value = '';
            field_wins.value = '';
            field_losses.value = '';
        }
        else if (xhttp.readyState == 4 && xhttp.status != 200) {
            console.log("rip amiga there is an error")
        }
    }
    //send request and wait for response
    xhttp.send(JSON.stringify(data));
})

addRowToTable = (data) => {

    // Get a reference to the current table on the page and clear it out.
    let currentTable = document.getElementById("trainerTable");

    // Get the location where we should insert the new row (end of table)
    let newRowIndex = currentTable.rows.length;

    // Get a reference to the new row from the database query (last object)
    let parsedData = JSON.parse(data);
    let newRow = parsedData[parsedData.length - 1]

    // Create a row and 4 cells
    let row = document.createElement("TR");
    let idCell = document.createElement("TD");
    let tnameCell = document.createElement("TD");
    let winsCell = document.createElement("TD");
    let lossesCell = document.createElement("TD");
    

    // Fill the cells with correct data
    idCell.innerText = newRow.trainerID;
    tnameCell.innerText = newRow.tname;
    winsCell.innerText = newRow.wins;
    lossesCell.innerText = newRow.losses;


    // Add the cells to the row 
    row.appendChild(idCell);
    row.appendChild(tnameCell);
    row.appendChild(winsCell);
    row.appendChild(lossesCell);


    currentTable.appendChild(row);

}