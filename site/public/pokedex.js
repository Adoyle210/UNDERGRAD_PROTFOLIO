const pokedexTable = document.getElementById("pokedexTable");

function displaypokedex() {
    pokedexTable.innerHTML = ""; 
    fetch("http://flip1.engr.oregonstate.edu:65532/api/pokedex/get")
        .then(response => response.json())
        .then(pokedex => {
            pokedex.forEach(pokedex => {
                const row = document.createElement("tr");
                const pokedexIDCell = document.createElement("td");
                pokedexIDCell.textContent = pokedex.pokedexID;
                pokedexIDCell.setAttribute('id', 'data-pokedex-id');
                row.appendChild(pokedexIDCell);

                const pnameCell = document.createElement("td");
                pnameCell.textContent = pokedex.pname;
                row.appendChild(pnameCell);

                const ptypeCell = document.createElement("td");
                ptypeCell.textContent = pokedex.ptype;
                row.appendChild(ptypeCell);

                const regionIDCell = document.createElement("td");
                regionIDCell.textContent = pokedex.regionID;
                row.appendChild(regionIDCell);

                const actionsCell = document.createElement("td");
                const deleteButton = document.createElement("button");
                deleteButton.textContent = "Delete";
                deleteButton.addEventListener("click", () => {
                    deletepokedex(pokedex.pokedexID);
                });
                actionsCell.appendChild(deleteButton);

                const updateButton = document.createElement("button");
                updateButton.textContent = "Update";
                updateButton.addEventListener("click", () => {
                    updatepokedex(pokedex);
                });
                actionsCell.appendChild(updateButton);

                row.appendChild(actionsCell);

                pokedexTable.appendChild(row);
            });
        })
        .catch(error => {
            console.error("Error fetching pokedex:", error);
        });
}

//MUTATE DATA
// ADD Pokedex
function addpokedex(pname, ptype, regionID) {
    fetch("http://flip1.engr.oregonstate.edu:65532/api/pokedex/add", {
        method: "POST",
        headers: {
            "Content-Type": "application/json"
        },
        body: JSON.stringify({ pname, ptype, regionID})
    })
    .then(() => {
        displaypokedex();
        document.getElementById("pnameInput").value = "";
        document.getElementById("ptypeInput").value = "";
        document.getElementById("regionInput").value = "";
    })
    .catch(error => {
        console.error("Error adding pokedex:", error);
    });
}

//ADD listener
const addpokedexForm = document.getElementById("addpokedex");
addpokedexForm.addEventListener("submit", event => {
    event.preventDefault();

    const pname = document.getElementById("pnameInput").value;
    const ptype = document.getElementById("ptypeInput").value;
    const regionID = document.getElementById("regionInput").value;

    addpokedex(pname, ptype, regionID);
});

//DELETE pokedex
function deletepokedex(pokedexId) {
    fetch(`http://flip1.engr.oregonstate.edu:65532/api/pokedex/delete/${pokedexId}`, {
        method: "DELETE"
    })
    .then(() => {
        displaypokedex(); //refresh table
    })
    .catch(error => {
        console.error("Error deleting pokedex:", error);
    });
}

// // Function to update 
function updatepokedex(pokedex) {
    const updateForm = document.getElementById("updatepokedexForm");
    updateForm.style.display = 'block';

    updateForm.addEventListener("submit", event => {
        event.preventDefault();

        var pname = document.getElementById("pnameInput");
        var ptype = document.getElementById("ptypeInput");
        var regionID = document.getElementById("regionInput");
        

        // Get the input values
        const updatedpokedex = {
            // shallow copy of pokedex
            ...pokedex,
            pname: pname.value,
            ptype: ptype.value,
            regionID: regionID.value,
        };

        fetch(`http://flip1.engr.oregonstate.edu:65532/api/pokedex/update/${pokedex.pokedexID}`, {
        method: "PUT",
        headers: {
            "Content-Type": "application/json"
        },
        body: JSON.stringify(updatedpokedex)
        })
        .then(() => {
            pname.value = '';
            ptype.value = '';
            regionID.value = '';
            updateForm.style.display = 'none';
            displaypokedex();
        })
        .catch(error => {
            console.error("Error updating pokedex:", error);
        });
    });
}



displaypokedex();