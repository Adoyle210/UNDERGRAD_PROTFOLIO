-- this file is for all the data we insert into the tables

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

INSERT INTO pokemon (pname, ptype, pokedexID, regionID) 
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
    VALUES ((SELECT trainerID FROM trainer WHERE tname = 'Ash'), (SELECT pokedexID FROM pokemon WHERE pname = 'bulbasaur')),
    ((SELECT trainerID FROM trainer WHERE tname = 'Misty'), (SELECT pokedexID FROM pokemon WHERE pname = 'squirtle')),
    ((SELECT trainerID FROM trainer WHERE tname = 'Broc'), (SELECT pokedexID FROM pokemon WHERE pname = 'beedrill'));