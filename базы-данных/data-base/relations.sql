SELECT 
    audio_tracks.id AS track_id,
    audio_tracks.name AS track_name,
    audio_tracks.duration AS track_duration,
    audio_tracks.release_date AS track_release_date,
    audio_types.name AS audio_type,
    genres.name AS genre,
    albums.name AS album_name,
    albums.release_date AS album_release_date,
    artists.full_name AS artist_name,
    authors.nickname AS author_nickname
FROM 
    audio_tracks
JOIN 
    audio_types ON audio_tracks.type_id = audio_types.id
JOIN 
    genres ON audio_tracks.genre_id = genres.id
JOIN 
    albums ON audio_tracks.album_id = albums.id
JOIN 
    authors_artists ON albums.author_id = authors_artists.author_id
JOIN 
    artists ON authors_artists.artist_id = artists.id
JOIN 
    tracks_authors ON audio_tracks.id = tracks_authors.track_id
JOIN 
    authors ON tracks_authors.author_id = authors.id;

