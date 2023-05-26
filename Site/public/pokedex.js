const pokedexTable = document.getElementById("pokedexTable");

function displaypokedex() {
    pokedexTable.innerHTML = ""; 
    fetch(":9351/api/accounts/get")
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



displaypokedex();