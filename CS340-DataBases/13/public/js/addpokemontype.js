let addtypeform = document.getElementById('addtype');

addtypeform.addEventListener("submit", function (e) {
    //this prevents the form from submmiting
    e.preventDefault();

    let field_type1 = document.getElementById("type1Input");
    let field_type2 = document.getElementById("type2Input");

    let val_type1 = field_type1.value;
    let val_type2 = field_type2.value;

    let data = {
        type1: val_type1,
        type2: val_type2,
    }

    var xhttp = new XMLHttpRequest();
    xhttp.open("POST", "/type/add", true);
    xhttp.setRequestHeader("Content-type", "application/json");

    xhttp.onreadystatechange = () => {
        if (xhttp.readyState == 4 && xhttp.status == 200) {
            addRowToTable(xhttp.response);

            if (field_type1 !== null) {
                field_type1.value = '';
            }

            if (field_type2 !== null) {
                field_type2.value = '';
            }
        } else if (xhttp.readyState == 4 && xhttp.status != 200) {
            console.log("rip amiga there is an error");
        }
    }

    xhttp.send(JSON.stringify(data));
})

addRowToTable = (data) => {
    let currentTable = document.getElementById("typesTable");
    let newRowIndex = currentTable.rows.length;
    let parsedData = JSON.parse(data);
    let newRow = parsedData[parsedData.length - 1]

    let row = document.createElement("TR");
    let idCell = document.createElement("TD");
    let type1Cell = document.createElement("TD");
    let type2Cell = document.createElement("TD");

    idCell.innerText = newRow.id;
    type1Cell.innerText = newRow.type1;
    type2Cell.innerText = newRow.type2;

    row.appendChild(idCell);
    row.appendChild(type1Cell);
    row.appendChild(type2Cell);

    currentTable.appendChild(row);
}
