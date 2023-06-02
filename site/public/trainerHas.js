const trainerHasTable = document.getElementById("trainerHas");

function displaytrainerHas() {
    trainerHasTable.innerHTML = ""; 
    fetch("http://flip1.engr.oregonstate.edu:65532/api/trainerHas/get")
        .then(response => response.json())
        .then(trainerHas => {
            trainerHas.forEach(trainerHas => {
                const row = document.createElement("tr");
                const trainerIDCell = document.createElement("td");
                trainerIDCell.textContent = trainer.trainerID;
                trainerIDCell.setAttribute('id', 'data-trainer-id');
                row.appendChild(trainerIDCell);

                const pokedexIDCell = document.createElement("td");
                pokedexIDCell.textContent = pokedex.pokedexID;
                row.appendChild(pokedexIDCell);

                const pokemonIDCell = document.createElement("td");
                pokemonIDCell.textContent = pokemon.pokemonID;
                row.appendChild(pokemonIDCell);

//                 const actionsCell = document.createElement("td");
//                 const deleteButton = document.createElement("button");
//                 deleteButton.textContent = "Delete";
//                 deleteButton.addEventListener("click", () => {
//                     deletepokedex(pokedex.pokedexID);
//                 });
//                 actionsCell.appendChild(deleteButton);

//                 const updateButton = document.createElement("button");
//                 updateButton.textContent = "Update";
//                 updateButton.addEventListener("click", () => {
//                     updatepokedex(pokedex);
//                 });
//                 actionsCell.appendChild(updateButton);

//                 row.appendChild(actionsCell);

                trainerHasTable.appendChild(row);
            });
        })
        .catch(error => {
            console.error("Error fetching trainerHas:", error);
        });
}



displaytrainerHas();
