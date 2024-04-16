let updatepokedexForm = document.getElementById('updatepokedex');

updatepokedexForm.addEventListener("submit", function (e) {

    e.preventDefault();

    // Get form fields we need to get data from
    let feild_pokedexID = document.getElementById("pokedexIDInput");
    let field_pname = document.getElementById("pnameInput");
    let field_ptype = document.getElementById("ptypeInput");
    let field_regionID = document.getElementById("regionInput");


    // Get the values from the form fields
    let val_pokdexID = feild_pokedexID.value;
    let val_pname = field_pname.value;
    let val_ptype = field_ptype.value;
    let val_regionID = field_regionID.value;
    
    //no nulls for name
    if (isNaN(val_pname)) 
    {
        return;
    }
    if (isNaN(val_ptype)) 
    {
        return;
    }
    if (isNaN(val_regionID)) 
    {
        return;
    }

    // Put our data we want to send in a javascript object
    let data = {
        pokedexID:val_pokdexID,
        pname: val_pname,
        ptype: val_ptype,
        regionID: val_regionID,
    }
    
    // Setup our AJAX request
    var xhttp = new XMLHttpRequest();
    xhttp.open("PUT", "/pokedex/update", true);
    xhttp.setRequestHeader("Content-type", "application/json");

    // Tell our AJAX request how to resolve
    xhttp.onreadystatechange = () => {
        if (xhttp.readyState == 4 && xhttp.status == 200) {

            // Add the new data to the table
            updateRow(xhttp.response, fullNameValue);

        }
        else if (xhttp.readyState == 4 && xhttp.status != 200) {
            console.log("There was an error with the input.")
        }
    }

    // Send the request and wait for the response
    xhttp.send(JSON.stringify(data));

})


function updateRow(data, pokedexID){
    let parsedData = JSON.parse(data);
    
    let table = document.getElementById("pokedexTable");

    for (let i = 0, row; row = table.rows[i]; i++) {
       //iterate through rows
       //rows would be accessed using the "row" variable assigned in the for loop
       if (table.rows[i].getAttribute("data-value") == pokedexID) {

            // Get the location of the row where we found the matching pokedex ID
            let updateRowIndex = table.getElementsByTagName("tr")[i];

            // Get td of homeworld value
            let td = updateRowIndex.getElementsByTagName("td")[3];

            // Reassign homeworld to our value we updated to
            td.innerHTML = parsedData[0].name; 
       }
    }
}
