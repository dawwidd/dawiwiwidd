CREATE TABLE gracze (
    id_gracza INTEGER NOT NULL,
    login     VARCHAR(64) NOT NULL
);

ALTER TABLE gracze ADD CONSTRAINT gracze_pk PRIMARY KEY ( id_gracza );

CREATE TABLE gry_multiplayer (
    id                INTEGER NOT NULL,
    wynik_gracza_1    INTEGER NOT NULL,
    wynik_gracza_2    INTEGER NOT NULL,
    gracze_id_gracza  INTEGER NOT NULL,
    gracze_id_gracza2 INTEGER NOT NULL
);

ALTER TABLE gry_multiplayer ADD CONSTRAINT gry_multiplayer_pk PRIMARY KEY ( id );

CREATE TABLE gry_singleplayer (
    id               INTEGER NOT NULL,
    wynik            INTEGER NOT NULL,
    gracze_id_gracza INTEGER NOT NULL
);

ALTER TABLE gry_singleplayer ADD CONSTRAINT gry_singleplayer_pk PRIMARY KEY ( id );

ALTER TABLE gry_multiplayer
    ADD CONSTRAINT gry_multiplayer_gracze_fk FOREIGN KEY ( gracze_id_gracza )
        REFERENCES gracze ( id_gracza );

ALTER TABLE gry_multiplayer
    ADD CONSTRAINT gry_multiplayer_gracze_fkv2 FOREIGN KEY ( gracze_id_gracza2 )
        REFERENCES gracze ( id_gracza );

ALTER TABLE gry_singleplayer
    ADD CONSTRAINT gry_singleplayer_gracze_fk FOREIGN KEY ( gracze_id_gracza )
        REFERENCES gracze ( id_gracza ); 
