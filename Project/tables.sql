-- this file is to set up all the tables in the database 

DROP TABLE IF EXISTS type;
 
CREATE TABLE type (            
    id int NOT NULL AUTO_INCREMENT,    
    fire varchar(25) DEFAULT 'false',
    Water varchar(25) DEFAULT 'false',
    grass varchar(25) DEFAULT 'false',
    normal varchar(25) DEFAULT 'false',
    bug varchar(25) DEFAULT 'false',
    poison varchar(25) DEFAULT 'false',
    flying varchar(25) DEFAULT 'false',
    PRIMARY KEY (id)
);

DROP TABLE IF EXISTS region;

CREATE TABLE region (
    id int NOT NULL AUTO_INCREMENT,     
    kanto varchar(25) DEFAULT 'false',
    johto varchar(25) DEFAULT 'false',
    PRIMARY KEY (id)
);

DROP TABLE IF EXISTS pokemon;

CREATE TABLE pokemon (
    pname varchar(25) NOT NULL,
    ptype int NOT NULL,     
    pokedexID int NOT NULL,
    regionID int NOT NULL  
);

DROP TABLE IF EXISTS trainer;

CREATE TABLE trainer (
    trainerID int(11) NOT NULL AUTO_INCREMENT,   
    tname varchar(25) NOT NULL,
    wins int NOT NULL,
    losses int NOT NULL
);

DROP TABLE IF EXISTS trainerHas;

CREATE TABLE trainerHas (
    trainerID int NOT NULL,
    pokedexID int NOT NULL,
    pokemonID int NOT NULL AUTO_INCREMENT,
    FOREIGN KEY (trainerID) REFERENCES trainer(trainerID),
    FOREIGN KEY (pokedexID) REFERENCES pokemon(pokedexID)
)
