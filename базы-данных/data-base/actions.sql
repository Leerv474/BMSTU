-- look up collection
SELECT at.id, at.name AS track_name, at.duration, at.release_date, g.name AS genre, at.type_id
FROM collections_tracks ct
JOIN audio_tracks at ON ct.track_id = at.id
JOIN albums alb ON at.album_id = alb.id
JOIN genres g ON at.genre_id = g.id
JOIN collections c ON ct.collection_id = c.id
WHERE c.name = 'Romans Collection';

-- look up tracks by The Beatles
SELECT at.id, at.name AS track_name, at.duration, at.release_date, g.name AS genre, at.type_id
FROM audio_tracks at
JOIN albums alb ON at.album_id = alb.id
JOIN authors_artists aa ON aa.artist_id = alb.author_id
JOIN authors a ON aa.author_id = a.id
JOIN genres g ON at.genre_id = g.id
WHERE a.nickname = 'The Beatles';

