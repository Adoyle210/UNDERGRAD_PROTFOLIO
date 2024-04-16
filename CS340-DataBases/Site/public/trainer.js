const trainerTable = document.getElementById("trainerTable");

function displaytrainer() {
    trainerTable.innerHTML = ""; 
    fetch("http://flip1.engr.oregonstate.edu:65532/api/trainer/get")
        .then(response => response.json())
        .then(trainer => {
            trainer.forEach(trainer => {
                const row = document.createElement("tr");
                const trainerIDCell = document.createElement("td");
                trainerIDCell.textContent = trainer.trainerID;
                trainerIDCell.setAttribute('id', 'data-trainer-id');
                row.appendChild(trainerIDCell);

                const tnameCell = document.createElement("td");
                tnameCell.textContent = trainer.tname;
                row.appendChild(tnameCell);

                const winsCell = document.createElement("td");
                winsCell.textContent = trainer.wins;
                row.appendChild(winsCell);

                const lossesCell = document.createElement("td");
                lossesCell.textContent = trainer.losses;
                row.appendChild(lossesCell);

                const actionsCell = document.createElement("td");
                const deleteButton = document.createElement("button");
                deleteButton.textContent = "Delete";
                deleteButton.addEventListener("click", () => {
                    deletetrainer(trainer.trainerID);
                });
                actionsCell.appendChild(deleteButton);

                const updateButton = document.createElement("button");
                updateButton.textContent = "Update";
                updateButton.addEventListener("click", () => {
                    updatetrainer(trainer);
                });
                actionsCell.appendChild(updateButton);

                row.appendChild(actionsCell);

                trainerTable.appendChild(row);
            });
        })
        .catch(error => {
            console.error("Error fetching trainer:", error);
        });
}

//MUTATE DATA
// ADD trainer
function addtrainer(tname, wins, losses) {
    fetch("http://flip1.engr.oregonstate.edu:65532/api/trainer/add", {
        method: "POST",
        headers: {
            "Content-Type": "application/json"
        },
        body: JSON.stringify({ tname, wins, losses})
    })
    .then(() => {
        displaytrainer();
        document.getElementById("tnameInput").value = "";
        document.getElementById("winsInput").value = "";
        document.getElementById("lossesInput").value = "";
    })
    .catch(error => {
        console.error("Error adding trainer:", error);
    });
}

//ADD listener
const addtrainerForm = document.getElementById("addtrainer");
addtrainerForm.addEventListener("submit", event => {
    event.preventDefault();

    const tname = document.getElementById("tnameInput").value;
    const wins = document.getElementById("winsInput").value;
    const losses = document.getElementById("lossesInput").value;

    addtrainer(tname, wins, losses);
});

//DELETE trainer
function deletetrainer(trainerId) {
    fetch(`http://flip1.engr.oregonstate.edu:65532/api/trainer/delete/${trainerId}`, {
        method: "DELETE"
    })
    .then(() => {
        displaytrainer(); //refresh table
    })
    .catch(error => {
        console.error("Error deleting trainer:", error);
    });
}

// // Function to update 
function updatetrainer(trainer) {
    const updateForm = document.getElementById("updatetrainerForm");
    updateForm.style.display = 'block';

    updateForm.addEventListener("submit", event => {
        event.preventDefault();

        var tname = document.getElementById("tnameInput");
        var wins = document.getElementById("winsInput");
        var losses = document.getElementById("lossesInput");
        

        // Get the input values
        const updatedtrainer = {
            // shallow copy of trainer
            ...trainer,
            tname: tname.value,
            wins: wins.value,
            losses: losses.value,
        };

        fetch(`http://flip1.engr.oregonstate.edu:65532/api/trainer/update/${trainer.trainerID}`, {
        method: "PUT",
        headers: {
            "Content-Type": "application/json"
        },
        body: JSON.stringify(updatedtrainer)
        })
        .then(() => {
            tname.value = '';
            wins.value = '';
            losses.value = '';
            updateForm.style.display = 'none';
            displaytrainer();
        })
        .catch(error => {
            console.error("Error updating trainer:", error);
        });
    });
}


displaytrainer();