CREATE TABLE genres (
    genre_id            integer         PRIMARY KEY,
    genre_name          varchar(80)     NOT NULL,
);
CREATE TABLE types (
    type_id             integer         PRIMARY KEY,
    type_name           varchar(80)     NOT NULL,
);
CREATE TABLE audio_tracks (
    audio_id            integer         PRIMARY KEY,
    audio_name          varchar(80)     NOT NULL, 
    audio_genre         integer         FOREIGN KEY REFERENCES genres (genre_id),    
    audio_type          integer         FOREIGN KEY REFERENCES types(type_id),
    audio_duration      integer         NOT NULL,
    audio_release_date  date            NOT NULL,
);



