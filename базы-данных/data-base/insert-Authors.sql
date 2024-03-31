INSERT INTO authors (nickname) VALUES
('The Beatles'),
('Queen'),
('Nirvana'),
('Coldplay'),
('BTS');

-- Insert artists into the table
INSERT INTO artists (full_name) VALUES
('John Lennon'),
('Paul McCartney'),
('George Harrison'),
('Ringo Starr'),
('Freddie Mercury'),
('Brian May'),
('Roger Taylor'),
('John Deacon'),
('Kurt Cobain'),
('Krist Novoselic'),
('Dave Grohl'),
('Chris Martin'),
('Jonny Buckland'),
('Guy Berryman'),
('Will Champion'),
('RM'),
('Jin'),
('Suga'),
('J-Hope'),
('Jimin'),
('V'),
('Jungkook');

INSERT INTO authors_artists (author_id, artist_id) VALUES
(1, 1),  -- The Beatles: John Lennon
(1, 2),  -- The Beatles: Paul McCartney
(1, 3),  -- The Beatles: George Harrison
(1, 4),  -- The Beatles: Ringo Starr
(2, 5),  -- Queen: Freddie Mercury
(2, 6),  -- Queen: Brian May
(2, 7),  -- Queen: Roger Taylor
(2, 8),  -- Queen: John Deacon
(3, 9),  -- Nirvana: Kurt Cobain
(3, 10),-- Nirvana: Krist Novoselic
(3, 11),-- Nirvana: Dave Grohl
(4, 12),-- Coldplay: Chris Martin
(4, 13),-- Coldplay: Jonny Buckland
(4, 14),-- Coldplay: Guy Berryman
(4, 15),-- Coldplay: Will Champion
(5, 16),-- BTS: RM
(5, 17),-- BTS: Jin
(5, 18),-- BTS: Suga
(5, 19),-- BTS: J-Hope
(5, 20),-- BTS: Jimin
(5, 21),-- BTS: V
(5, 22);-- BTS: Jungkook


