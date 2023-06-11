let addpokemonform = document.getElementById('addpokedex');

addpokemonform.addEventListener("submit", function (e) {
    //this prevents the form from submmiting
    e.preventDefault(); 

    // this is to get the fields from the form
    let field_pname = document.getElementById("pnameInput");
    let field_ptype = document.getElementById("ptypeInput");
    let field_regionID = document.getElementById("regionInput");

    //this is to get the valies from the form fields 
    let val_pname = field_pname.value;
    let val_ptype = field_ptype.value;
    let val_regionID = field_regionID.value;

    //this is to send the data as a javascript object
    let data = {
        pname: val_pname,
        ptype: val_ptype,
        regionID: val_regionID,
    }

    //setup our AJAX request
    var xhttp = new XMLHttpRequest();
    xhttp.open("POST", "/pokedex/add", true);
    xhttp.setRequestHeader("Content-type", "application/json");

    //this tells out AJAC request how to resolve
    xhttp.onreadystatechange = () => {
        if(xhttp.readyState == 4 && xhttp.status == 200){
            //add new data
            addRowToTable(xhttp.response);

            //clear the input fields 
            field_pname.value = '';
            field_ptype.value = '';
            field_regionID.value = '';
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
    let currentTable = document.getElementById("");

    // Get the location where we should insert the new row (end of table)
    let newRowIndex = currentTable.rows.length;

    // Get a reference to the new row from the database query (last object)
    let parsedData = JSON.parse(data);
    let newRow = parsedData[parsedData.length - 1]

    // Create a row and 4 cells
    let row = document.createElement("TR");
    let idCell = document.createElement("TD");
    let firstNameCell = document.createElement("TD");
    let lastNameCell = document.createElement("TD");
    let homeworldCell = document.createElement("TD");
    let ageCell = document.createElement("TD");

    // Fill the cells with correct data
    idCell.innerText = newRow.id;
    firstNameCell.innerText = newRow.fname;
    lastNameCell.innerText = newRow.lname;
    homeworldCell.innerText = newRow.homeworld;
    ageCell.innerText = newRow.age;

    // Add the cells to the row 
    row.appendChild(idCell);
    row.appendChild(firstNameCell);
    row.appendChild(lastNameCell);
    row.appendChild(homeworldCell);
    row.appendChild(ageCell);

    currentTable.appendChild(row);

}