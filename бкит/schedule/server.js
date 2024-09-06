const express = require('express');
const sqlite3 = require('sqlite3').verbose();
const cors = require('cors');
const moment = require('moment');
const path = require('path'); // Include path module for serving static files

const app = express();
const port = 3000;

// Middleware to parse incoming JSON requests and handle CORS
app.use(express.json());
app.use(cors());

// Serve static files (including index.html)
app.use(express.static(path.join(__dirname)));

// Connect to SQLite database
const db = new sqlite3.Database('./schedule.db', (err) => {
    if (err) {
        console.error('Error connecting to the SQLite database:', err);
    } else {
        console.log('Connected to the SQLite database.');
    }
});

// Get current day of the week
const getCurrentWeekday = () => {
    return moment().isoWeekday();
};

const getFirstWeekOfSeptember = () => {
    const firstSeptember = moment().month(8).startOf('month'); // 8 = September (0-indexed)
    const firstMonday = firstSeptember.isoWeekday(1); // 1 = Monday
    if (firstMonday.month() !== 8) {
        // If the first Monday is not in September, move to the next week
        return firstMonday.add(1, 'week');
    }
    return firstMonday;
};

const getCurrentWeekNumber = () => {
    const firstWeekOfSeptember = getFirstWeekOfSeptember();
    const currentWeek = moment();
    
    // Calculate the difference in weeks between now and the first week of September
    const weekDiff = currentWeek.diff(firstWeekOfSeptember, 'weeks');
    
    // Determine if it's an odd or even week
    const isEvenWeek = (weekDiff % 2) === 0;
    
    return isEvenWeek ? 0 : 1; // 0 for even weeks, 1 for odd weeks
};
// API to get classes for the current day
app.get('/classes/today', (req, res) => {
    const today = getCurrentWeekday(); // Get today's weekday number
    const currentWeekNumber = getCurrentWeekNumber();
    db.all('SELECT * FROM classes WHERE weekday = ? and (week_number = 0 or week_number = ?)', [today, currentWeekNumber], (err, rows) => {
        if (err) {
            return res.status(500).json({ error: err.message });
        }
        res.json({ data: rows });
    });
});

// Start the server
app.listen(port, () => {
    console.log(`Server is running on http://localhost:${port}`);
});

