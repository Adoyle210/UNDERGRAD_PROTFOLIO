-- set up all the tables in the database 

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

DROP TABLE IF EXISTS pokedex;

CREATE TABLE pokedex (
    pname varchar(25) NOT NULL,
    ptype int NOT NULL,     
    pokedexID int NOT NULL,
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
    FOREIGN KEY (trainerID) REFERENCES trainer(trainerID),
    FOREIGN KEY (pokedexID) REFERENCES pokemon(pokedexID)
);

-- all the data we insert into the tables

INSERT INTO type (grass, poison) VALUES ('true', 'true');
INSERT INTO type (fire) VALUES ('true');
INSERT INTO type (fire, flying) VALUES ('true', 'true');
INSERT INTO type (water) VALUES ('true');
INSERT INTO type (bug) VALUES ('true');
INSERT INTO type (bug, poison) VALUES ('true', 'true');
INSERT INTO type (normal, flying) VALUES ('true', 'true');
INSERT INTO type (normal) VALUES ('true');

INSERT INTO region (kanto) VALUES ('true');
INSERT INTO region (johto) VALUES ('true');

INSERT INTO pokedex (pname, ptype, pokedexID, regionID) 
    VALUES ('bulbasaur', (SELECT id FROM type WHERE grass = 'true' AND poison = 'true'), 1, (SELECT id FROM region WHERE kanto = 'true')),
        ('ivysaur', (SELECT id FROM type WHERE grass = 'true' AND poison = 'true'), 2, (SELECT id FROM region WHERE kanto = 'true')),
        ('venusaur', (SELECT id FROM type WHERE grass = 'true' AND poison = 'true'), 3, (SELECT id FROM region WHERE kanto = 'true')), 
        ('charmander', (SELECT id FROM type WHERE fire = 'true'), 4, (SELECT id FROM region WHERE kanto = 'true')), 
        ('charmeleon', (SELECT id FROM type WHERE fire = 'true') ,5, (SELECT id FROM region WHERE kanto = 'true')),
        ('charizard', (SELECT id FROM type WHERE fire = 'true' AND flying = 'true') ,6, (SELECT id FROM region WHERE kanto = 'true')),
        ('squirtle', (SELECT id FROM type WHERE water = 'true') ,7, (SELECT id FROM region WHERE kanto = 'true')),
        ('wartortle', (SELECT id FROM type WHERE water = 'true') ,8,(SELECT id FROM region WHERE kanto = 'true')),
        ('blastoise', (SELECT id FROM type WHERE water = 'true'), 9,(SELECT id FROM region WHERE kanto = 'true')),
        ('caterpir', (SELECT id FROM type WHERE bug = 'true'), 10, (SELECT id FROM region WHERE kanto = 'true')), 
        ('metapod',  (SELECT id FROM type WHERE bug = 'true'), 11, (SELECT id FROM region WHERE kanto = 'true')),
        ('butterfree', (SELECT id FROM type WHERE bug = 'true' AND flying = 'true'), 12, (SELECT id FROM region WHERE kanto = 'true')), 
        ('weedle', (SELECT id FROM type WHERE bug = 'true' AND poison = 'true'), 13, (SELECT id FROM region WHERE kanto = 'true')),
        ('kakuna', (SELECT id FROM type WHERE bug = 'true' AND poison = 'true'), 14, (SELECT id FROM region WHERE kanto = 'true')),
        ('beedrill', (SELECT id FROM type WHERE bug = 'true' AND poison = 'true'), 15, (SELECT id FROM region WHERE kanto = 'true')),
        ('pidgey', (SELECT id FROM type WHERE normal = 'true' AND flying = 'true'), 16, (SELECT id FROM region WHERE kanto = 'true')), 
        ('pidgeotto', (SELECT id FROM type WHERE normal = 'true' AND flying = 'true'), 17, (SELECT id FROM region WHERE kanto = 'true')),
        ('pidgeot', (SELECT id FROM type WHERE normal = 'true' AND flying = 'true'), 18, (SELECT id FROM region WHERE kanto = 'true')),
        ('rattata', (SELECT id FROM type WHERE normal = 'true'), 19, (SELECT id FROM region WHERE kanto = 'true')),
        ('raticate', (SELECT id FROM type WHERE normal = 'true'), 20,(SELECT id FROM region WHERE kanto = 'true')); 

INSERT INTO trainer (tname, wins, losses) 
    VALUES ('Ash', 5, 2),
    ('Misty', 3, 1),
    ('Broc', 4, 2);

INSERT INTO trainerHas (trainerID, pokedexID)
    VALUES ((SELECT trainerID FROM trainer WHERE tname = 'Ash'), (SELECT pokedexID FROM pokedex WHERE pname = 'bulbasaur')),
    ((SELECT trainerID FROM trainer WHERE tname = 'Misty'), (SELECT pokedexID FROM pokedex WHERE pname = 'squirtle')),
    ((SELECT trainerID FROM trainer WHERE tname = 'Broc'), (SELECT pokedexID FROM pokedex WHERE pname = 'beedrill'));

