SELECT * FROM audio_tracks;
-- look up collection
SELECT at.id, at.name AS track_name, at.duration, at.release_date, g.name AS genre, at.type_id
FROM collections_tracks ct
INNER JOIN audio_tracks at ON ct.track_id = at.id
INNER JOIN albums alb ON at.album_id = alb.id
INNER JOIN genres g ON at.genre_id = g.id
INNER JOIN collections c ON ct.collection_id = c.id
WHERE c.name = 'Romans Collection';

-- look up tracks by The Beatles
SELECT at.id, at.name AS track_name, at.duration, at.release_date, g.name AS genre, at.type_id
FROM audio_tracks at
INNER JOIN albums alb ON at.album_id = alb.id
INNER JOIN authors_artists aa ON aa.artist_id = alb.author_id
INNER JOIN authors a ON aa.author_id = a.id
INNER JOIN genres g ON at.genre_id = g.id
WHERE a.nickname = 'The Beatles';


SELECT name FROM audio_tracks ORDER BY name DESC;

SELECT audio_tracks.name FROM audio_tracks
RIGHT OUTER JOIN genres
ON audio_tracks.genre_id = genres.id;

SELECT audio_tracks.name FROM audio_tracks
LEFT OUTER JOIN genres
ON audio_tracks.genre_id = genres.id;

DELETE FROM collections_tracks
    WHERE track_id IN (
        SELECT id FROM audio_tracks WHERE audio_tracks.album_id = 1
    );

UPDATE audio_tracks SET genre_id = 2 WHERE album_id = 2;

SELECT login FROM users
WHERE EXISTS ( SELECT id FROM collections WHERE collections.owner_id = users.id);

SELECT * FROM albums WHERE number_of_tracks BETWEEN 10 AND 15;

SELECT * FROM audio_tracks WHERE name LIKE 'W%';
