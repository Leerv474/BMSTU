-- Insert albums for The Beatles
INSERT INTO albums (name, release_date, number_of_tracks, genre_id, author_id) VALUES
('Abbey Road', '1969-09-26', 17, 1, 1),  -- The Beatles
('A Night at the Opera', '1975-11-21', 12, 1, 2),  -- Queen
('Nevermind', '1991-09-24', 12, 1, 3),  -- Nirvana
('Parachutes', '2000-07-10', 10, 1, 4),  -- Coldplay
('Map of the Soul: 7', '2020-02-21', 20, 1, 5);  -- BTS

-- Insert audio tracks for The Beatles
INSERT INTO audio_tracks (name, duration, release_date, genre_id, type_id, album_id) VALUES
('Come Together', 259, '1969-09-26', 1, 1, 1),
('Bohemian Rhapsody', 354, '1975-11-21', 1, 1, 2),
('Smells Like Teen Spirit', 302, '1991-09-24', 1, 1, 3),
('Yellow', 266, '2000-07-10', 1, 1, 4),
('ON', 228, '2020-02-21', 1, 1, 5);

-- Insert tracks_authors for The Beatles
INSERT INTO tracks_authors (track_id, author_id) VALUES
(1, 1),  -- Come Together: The Beatles
(2, 2),  -- Bohemian Rhapsody: Queen
(3, 3),  -- Smells Like Teen Spirit: Nirvana
(4, 4),  -- Yellow: Coldplay
(5, 5);  -- ON: BTS
-- Insert additional tracks for The Beatles' album
INSERT INTO audio_tracks (name, duration, release_date, genre_id, type_id, album_id) VALUES
('Here Comes the Sun', 185, '1969-09-26', 1, 1, 1), -- The Beatles
('Let It Be', 243, '1969-09-26', 1, 1, 1);        -- The Beatles

-- Insert additional tracks for Queen's album
INSERT INTO audio_tracks (name, duration, release_date, genre_id, type_id, album_id) VALUES
('We Will Rock You', 122, '1975-11-21', 1, 1, 2), -- Queen
('We Are the Champions', 189, '1975-11-21', 1, 1, 2); -- Queen

-- Insert additional tracks for Nirvana's album
INSERT INTO audio_tracks (name, duration, release_date, genre_id, type_id, album_id) VALUES
('Lithium', 257, '1991-09-24', 1, 1, 3),        -- Nirvana
('In Bloom', 254, '1991-09-24', 1, 1, 3);       -- Nirvana

-- Insert additional tracks for Coldplay's album
INSERT INTO audio_tracks (name, duration, release_date, genre_id, type_id, album_id) VALUES
('Clocks', 307, '2000-07-10', 1, 1, 4),         -- Coldplay
('Fix You', 296, '2000-07-10', 1, 1, 4);        -- Coldplay

-- Insert additional tracks for BTS's album
INSERT INTO audio_tracks (name, duration, release_date, genre_id, type_id, album_id) VALUES
('Dynamite', 199, '2020-02-21', 1, 1, 5),      -- BTS
('Boy with Luv', 229, '2020-02-21', 1, 1, 5);  -- BTS

-- Link authors with the new tracks

-- The Beatles' tracks
INSERT INTO tracks_authors (track_id, author_id) VALUES
(6, 1), -- Here Comes the Sun: The Beatles
(7, 1); -- Let It Be: The Beatles

-- Queen's tracks
INSERT INTO tracks_authors (track_id, author_id) VALUES
(8, 2), -- We Will Rock You: Queen
(9, 2); -- We Are the Champions: Queen

-- Nirvana's tracks
INSERT INTO tracks_authors (track_id, author_id) VALUES
(10, 3), -- Lithium: Nirvana
(11, 3); -- In Bloom: Nirvana

-- Coldplay's tracks
INSERT INTO tracks_authors (track_id, author_id) VALUES
(12, 4), -- Clocks: Coldplay
(13, 4); -- Fix You: Coldplay

-- BTS's tracks
INSERT INTO tracks_authors (track_id, author_id) VALUES
(14, 5), -- Dynamite: BTS
(15, 5); -- Boy with Luv: BTS

