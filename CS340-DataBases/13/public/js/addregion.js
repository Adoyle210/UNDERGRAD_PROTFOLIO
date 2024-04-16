let addregionform = document.getElementById('addregion');

addregionform.addEventListener("submit", function (e) {
    //this prevents the form from submmiting
    e.preventDefault(); 

    // this is to get the fields from the form
    let field_region1 = document.getElementById("region1Input");
    let field_region2 = document.getElementById("region2Input");
    
    //this is to get the valies from the form fields 
    let val_region1 = field_region1.value;
    let val_region2 = field_region2.value;

    //this is to send the data as a javascript object
    let data = {
        region1: val_region1,
        region2: val_region2,
    }

    //setup our AJAX request
    var xhttp = new XMLHttpRequest();
    xhttp.open("POST", "/region/add", true);
    xhttp.setRequestHeader("Content-type", "application/json");

    //this tells out AJAX request how to resolve
    xhttp.onreadystatechange = () => {
        if(xhttp.readyState == 4 && xhttp.status == 200){
            //add new data
            addRowToTable(xhttp.response);

            //clear the input fields 
            field_region1.value = '';
            field_region2.value = '';
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
    let currentTable = document.getElementById("regionTable");

    // Get the location where we should insert the new row (end of table)
    let newRowIndex = currentTable.rows.length;

    // Get a reference to the new row from the database query (last object)
    let parsedData = JSON.parse(data);
    let newRow = parsedData[parsedData.length - 1]

    // Create a row and 4 cells
    let row = document.createElement("TR");
    let idCell = document.createElement("TD");
    let region1Cell = document.createElement("TD");
    let region2Cell = document.createElement("TD");
    

    // Fill the cells with correct data
    idCell.innerText = newRow.regionID;
    region1Cell.innerText = newRow.tname;
    region2Cell.innerText = newRow.wins;


    // Add the cells to the row 
    row.appendChild(idCell);
    row.appendChild(region1Cell);
    row.appendChild(region2Cell);


    currentTable.appendChild(row);

}