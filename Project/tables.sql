-- this file is to set up all the tables in the database 

DROP TABLE IF EXISTS type;

-- 1) having these all as varchars doesnt make sense to me 
-- should they not be like bools or something 
-- 2) i added id as a PK bc i think it make more sense 
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

-- 1) i added id bc i think it make more sense 
CREATE TABLE region (
    id int NOT NULL AUTO_INCREMENT,     
    kanto varchar(25) DEFAULT 'false',
    johto varchar(25) DEFAULT 'false',
    PRIMARY KEY (id)
);

-- 1) this table still needs to be connected to the other tables
-- 2) ptype was og a varchar that connected to type but that didnt make sense to my pea brain
-- i think ptype sould be the id number instead 
-- 3) same point as abouve but for region 
-- FOREIGN KEY (regionID) REFERENCES region(id)
-- 4) i think added a constraint of a unique name is a good idea
-- so we dont have duplicates of pokemon in the pokedex

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
