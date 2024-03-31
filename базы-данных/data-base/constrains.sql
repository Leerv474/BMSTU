ALTER TABLE audio_tracks
ADD CONSTRAINT positive_duration_check
CHECK (duration >= 0);

ALTER TABLE albums
ADD CONSTRAINT positive_number_of_tracks_check
CHECK (number_of_tracks >= 0);

ALTER TABLE audio_tracks
ADD CONSTRAINT positive_duration_check
CHECK (duration >= 0);

ALTER TABLE collections
ADD CONSTRAINT positive_number_of_tracks_check
CHECK (number_of_tracks >= 0),
ADD CONSTRAINT positive_total_duration_check
CHECK (total_duration >= 0);

ALTER TABLE authors
ADD CONSTRAINT longer_than_0_characters_nickname_check
CHECK (LENGTH(nickname) > 0);

ALTER TABLE artists
ADD CONSTRAINT longer_than_0_characters_full_name_check
CHECK (LENGTH(full_name) > 0);


ALTER TABLE collections
ADD CONSTRAINT longer_than_0_characters_name_check
CHECK (LENGTH(name) > 0);

ALTER TABLE users
ADD CONSTRAINT longer_than_0_characters_login_check
CHECK (LENGTH(login) > 0);

ALTER TABLE genres
ADD CONSTRAINT longer_than_0_characters_name_check
CHECK (LENGTH(name) > 0);

ALTER TABLE audio_types
ADD CONSTRAINT longer_than_0_characters_name_check
CHECK (LENGTH(name) > 0);

