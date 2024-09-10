const express = require("express");
const sqlite3 = require("sqlite3").verbose();
const cors = require("cors");
const moment = require("moment");
const path = require("path");

const app = express();
const port = 3000;

app.use(express.json());
app.use(cors());

app.use(express.static(path.join(__dirname), { index: "home.html" }));

app.get("/", (req, res) => {
  res.sendFile(path.join(__dirname, "home.html"));
});

const db = new sqlite3.Database("./schedule.db", (err) => {
  if (err) {
    console.error("Error connecting to the SQLite database:", err);
  } else {
    console.log("Connected to the SQLite database.");
  }
});

const getCurrentWeekday = () => moment().isoWeekday();

const getCurrentWeekNumber = () => {
  const firstWeekOfSeptember = moment().month(8).startOf("month").isoWeekday(1);
  const weekDiff = moment().diff(firstWeekOfSeptember, "weeks");
  return weekDiff % 2 === 0 ? 2 : 1;
};

app.post("/getSchedule", (req, res) => {
  const { day, groupName, subgroup } = req.body;

  if (!day || !groupName || isNaN(parseInt(subgroup))) {
    return res.status(400).json({ error: "Invalid input." });
  }

  res.json({ success: true });
});

app.get("/classes/today", (req, res) => {
  const today = getCurrentWeekday();
  const currentWeekNumber = getCurrentWeekNumber();
  const groupName = req.query.groupName;
  const subgroup = parseInt(req.query.subgroup, 10);

  if (isNaN(subgroup)) {
    return res.status(400).json({ error: "Invalid subgroup value." });
  }

  db.all(
    `SELECT * FROM classes 
     WHERE weekday = ? 
     AND (week_number = 0 OR week_number = ?) 
     AND group_name = ? 
     AND (subgroup = ? OR subgroup = 0)`,
    [today, currentWeekNumber, groupName, subgroup],
    (err, rows) => {
      if (err) {
        return res.status(500).json({ error: err.message });
      }
      res.json({ weekday: today, data: rows });
    },
  );
});

app.get("/classes/tomorrow", (req, res) => {
  const tomorrow = getCurrentWeekday() + 1;
  if (tomorrow > 7) {
    tomorrow = 1;
  }
  const currentWeekNumber = getCurrentWeekNumber();
  const groupName = req.query.groupName;
  const subgroup = parseInt(req.query.subgroup, 10);

  if (isNaN(subgroup)) {
    return res.status(400).json({ error: "Invalid subgroup value." });
  }

  db.all(
    `SELECT * FROM classes 
     WHERE weekday = ? 
     AND (week_number = 0 OR week_number = ?) 
     AND group_name = ? 
     AND (subgroup = ? OR subgroup = 0)`,
    [tomorrow, currentWeekNumber, groupName, subgroup],
    (err, rows) => {
      if (err) {
        return res.status(500).json({ error: err.message });
      }
      res.json({ weekday: tomorrow, data: rows });
    },
  );
});

// Helper function to calculate the full week's schedule
function getWeekSchedule(weekNumber, groupName, subgroup, res) {
  const query = `
    SELECT * FROM classes 
    WHERE (week_number = 0 OR week_number = ?) 
    AND group_name = ? 
    AND (subgroup = ? OR subgroup = 0)`;

  db.all(query, [weekNumber, groupName, subgroup], (err, rows) => {
    if (err) {
      return res.status(500).json({ error: err.message });
    }

    const weekSchedule = [[], [], [], [], [], [], []]; // One array for each weekday (Mon-Sun)

    // Distribute the rows into respective weekdays (1=Monday, 7=Sunday)
    rows.forEach((row) => {
      weekSchedule[row.weekday - 1].push(row);
    });
    // Sort each day's classes by class_number
    weekSchedule.forEach((daySchedule) => {
      daySchedule.sort((a, b) => a.class_number - b.class_number);
    });

    res.json({ weekNumber, data: weekSchedule });
  });
}

// Route for current week's schedule
app.get("/weekSchedule/currentWeek", (req, res) => {
  const currentWeekNumber = getCurrentWeekNumber();
  const groupName = req.query.groupName;
  const subgroup = parseInt(req.query.subgroup, 10);

  if (isNaN(subgroup)) {
    return res.status(400).json({ error: "Invalid subgroup value." });
  }

  getWeekSchedule(currentWeekNumber, groupName, subgroup, res);
});

// Route for next week's schedule
app.get("/weekSchedule/nextWeek", (req, res) => {
  const nextWeekNumber = getCurrentWeekNumber() + 1;
  const groupName = req.query.groupName;
  const subgroup = parseInt(req.query.subgroup, 10);

  if (isNaN(subgroup)) {
    return res.status(400).json({ error: "Invalid subgroup value." });
  }

  getWeekSchedule(nextWeekNumber, groupName, subgroup, res);
});

app.listen(port, () => {
  console.log(`Server is running on http://localhost:${port}`);
});
