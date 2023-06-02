-- set up all the tables in the database 
DROP TABLE IF EXISTS type;
 
CREATE TABLE type (            
    id int NOT NULL AUTO_INCREMENT,    
    type1 varchar(25) NOT NULL,
    type2 varchar(25),
    PRIMARY KEY (id)
);

DROP TABLE IF EXISTS region;

CREATE TABLE region (
    id int NOT NULL AUTO_INCREMENT,     
    region1 varchar(25) NOT NULL,
    region2 varchar(25),
    PRIMARY KEY (id)
);

DROP TABLE IF EXISTS pokedex;

CREATE TABLE pokedex (
    pname varchar(25) NOT NULL,
    ptype int NOT NULL,     
    pokedexID int NOT NULL AUTO_INCREMENT,
    regionID int NOT NULL,
    PRIMARY KEY (pokedexID)
);

DROP TABLE IF EXISTS trainer;

CREATE TABLE trainer (
    trainerID int(11) NOT NULL AUTO_INCREMENT,   
    tname varchar(25) NOT NULL,
    wins int NOT NULL,
    losses int NOT NULL,
    PRIMARY KEY (trainerID)
);

DROP TABLE IF EXISTS trainerHas;

CREATE TABLE trainerHas (
    trainerID int NOT NULL,
    pokedexID int NOT NULL,
    pokemonID int NOT NULL AUTO_INCREMENT,
    PRIMARY Key (pokemonID),
    FOREIGN KEY (trainerID) REFERENCES trainer(trainerID),
    FOREIGN KEY (pokedexID) REFERENCES pokedex(pokedexID)
);

-- all the data we insert into the tables
INSERT INTO type (type1, type2)
    VALUES ('grass', 'poison'),
    ('fire', NULL),
    ('fire', 'flying'),
    ('water', NULL),
    ('bug', NULL),
    ('bug', 'poison'),
    ('normal', 'flying'),
    ('normal', NULL);

/*INSERT INTO type (grass, poison) VALUES ('true', 'true');
INSERT INTO type (fire) VALUES ('true');
INSERT INTO type (fire, flying) VALUES ('true', 'true');
INSERT INTO type (water) VALUES ('true');
INSERT INTO type (bug) VALUES ('true');
INSERT INTO type (bug, poison) VALUES ('true', 'true');
INSERT INTO type (normal, flying) VALUES ('true', 'true');
INSERT INTO type (normal) VALUES ('true');*/

INSERT INTO region (region1, region2) 
    VALUES ('johto', NULL),
    ('kanto', NULL),
    ('johnto', 'kanto');

INSERT INTO pokedex (pname, ptype, regionID) 
    VALUES ('bulbasaur', 1, 1),
        ('ivysaur', 1, 1),
        ('venusaur', 1, 1), 
        ('charmander', 2, 1), 
        ('charmeleon', 2, 1),
        ('charizard', 3, 1),
        ('squirtle', 4, 1),
        ('wartortle', 4, 1),
        ('blastoise', 4, 1),
        ('caterpir', 5, 1), 
        ('metapod',  5, 1),
        ('butterfree', 6, 1), 
        ('weedle', 7, 1),
        ('kakuna', 7, 1),
        ('beedrill', 7, 1),
        ('pidgey', 8, 1), 
        ('pidgeotto', 8, 1),
        ('pidgeot', 8, 1),
        ('rattata', 9, 1),
        ('raticate', 9, 1); 



INSERT INTO trainer (tname, wins, losses) 
    VALUES ('Ash', 5, 2),
    ('Misty', 3, 1),
    ('Broc', 4, 2);

INSERT INTO trainerHas (trainerID, pokedexID)
    VALUES ((SELECT trainerID FROM trainer WHERE tname = 'Ash'), (SELECT pokedexID FROM pokedex WHERE pname = 'bulbasaur')),
    ((SELECT trainerID FROM trainer WHERE tname = 'Misty'), (SELECT pokedexID FROM pokedex WHERE pname = 'squirtle')),
    ((SELECT trainerID FROM trainer WHERE tname = 'Broc'), (SELECT pokedexID FROM pokedex WHERE pname = 'beedrill'));

