let addtrainerform = document.getElementById('addtrainerHas');

addtrainerform.addEventListener("submit", function (e) {
    //this prevents the form from submmiting
    e.preventDefault(); 

    // this is to get the fields from the form
    let field_trainerID = document.getElementById("trainerIDInput");
    let field_pokedexID = document.getElementById("pokedexIDInput");

    //this is to get the valies from the form fields 
    let val_trainerID = field_trainerID.value;
    let val_pokedexID = field_pokedexID.value;

    //this is to send the data as a javascript object
    let data = {
        trainerID: val_trainerID,
        pokedexID: val_pokedexID,
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
            field_trainerID.value = '';
            field_pokedexID.value = '';
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
    let currentTable = document.getElementById("trainerHasTable");

    // Get the location where we should insert the new row (end of table)
    let newRowIndex = currentTable.rows.length;

    // Get a reference to the new row from the database query (last object)
    let parsedData = JSON.parse(data);
    let newRow = parsedData[parsedData.length - 1]

    // Create a row and 4 cells
    let row = document.createElement("TR");
    let idCell = document.createElement("TD");
    let trainerIDCell = document.createElement("TD");
    let pokedexIDCell = document.createElement("TD");
    

    // Fill the cells with correct data
    idCell.innerText = newRow.pokemonID;
    trainerIDCell.innerText = newRow.trainerID;
    pokedexIDCell.innerText = newRow.pokedexID;


    // Add the cells to the row 
    row.appendChild(idCell);
    row.appendChild(trainerIDCell);
    row.appendChild(pokedexIDCell);


    currentTable.appendChild(row);

}