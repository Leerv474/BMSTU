INSERT INTO users (login, password) VALUES ('roman', '123');

INSERT INTO collections (name, number_of_tracks, total_duration) VALUES ('Romans Collection', 0, 0);

SELECT id FROM collections WHERE name = 'Romans Collection';

INSERT INTO collections_tracks (collection_id, track_id) VALUES
(1, 1),
(1, 2),
(1, 3),
(1, 4),
(1, 5),
(1 ,6),
(1, 7);

