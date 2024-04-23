CREATE TABLE genres (
    id SERIAL PRIMARY KEY,
    name VARCHAR NOT NULL
);

CREATE TABLE audio_types (
    id SERIAL PRIMARY KEY,
    name VARCHAR NOT NULL
);


CREATE TABLE authors (
    id SERIAL PRIMARY KEY,
    nickname VARCHAR(80) NOT NULL
);

CREATE TABLE artists (
    id SERIAL PRIMARY KEY,
    full_name VARCHAR(80) NOT NULL
);

CREATE TABLE authors_artists (
    artist_id INT,
    author_id INT,
    PRIMARY KEY (artist_id, author_id),
    FOREIGN KEY (artist_id) REFERENCES artists(id),
    FOREIGN KEY (author_id) REFERENCES authors(id)
);

CREATE TABLE albums (
    id SERIAL PRIMARY KEY,
    name VARCHAR(80) NOT NULL,
    release_date DATE NOT NULL,
    number_of_tracks INT NOT NULL,
    genre_id INT NOT NULL,
    author_id INT NOT NULL,
    FOREIGN KEY (genre_id) REFERENCES genres(id),
    FOREIGN KEY (author_id) REFERENCES authors(id)
);

CREATE TABLE audio_tracks (
    id SERIAL PRIMARY KEY,
    name VARCHAR(80) NOT NULL,
    duration INT NOT NULL,
    release_date DATE NOT NULL,
    genre_id INT NOT NULL,
    type_id INT NOT NULL,
    album_id INT NOT NULL,
    FOREIGN KEY (album_id) REFERENCES albums(id),
    FOREIGN KEY (genre_id) REFERENCES genres(id),
    FOREIGN KEY (type_id) REFERENCES audio_types(id)
);

CREATE TABLE tracks_authors (
    track_id INT,
    author_id INT,
    PRIMARY KEY (track_id, author_id),
    FOREIGN KEY (track_id) REFERENCES audio_tracks(id),
    FOREIGN KEY (author_id) REFERENCES authors(id)
);

CREATE TABLE users (
    id SERIAL PRIMARY KEY,
    login VARCHAR(80) NOT NULL,
    password VARCHAR(80) NOT NULL
);

CREATE TABLE collections (
    id SERIAL PRIMARY KEY,
    name VARCHAR(80) DEFAULT 'unnamed',
    number_of_tracks INT NOT NULL,
    total_duration INT NOT NULL,
    owner_id INT NOT NULL,
    FOREIGN KEY (owner_id) REFERENCES users(id)
);

CREATE TABLE collections_tracks (
    collection_id INT,
    track_id INT,
    PRIMARY KEY (collection_id, track_id),
    FOREIGN KEY (collection_id) REFERENCES collections(id),
    FOREIGN KEY (track_id) REFERENCES audio_tracks(id)
);
