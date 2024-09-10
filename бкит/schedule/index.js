const currentPage = window.location.pathname;

if (currentPage.includes("home.html") || currentPage === "/") {
  console.log("Loaded home.html");

  const getTodayButton = document.getElementById("getToday");
  const getTomorrowButton = document.getElementById("getTomorrow");
  const groupNameInput = document.getElementById("groupName");
  const subgroupInput = document.getElementById("subgroup");
  const getWeekScheduleButton = document.getElementById("getWeekSchedule");
  const getNextWeekScheduleButton = document.getElementById(
    "getNextWeekSchedule",
  );

  if (getWeekScheduleButton && getNextWeekScheduleButton) {
    getWeekScheduleButton.addEventListener("click", () => {
      const groupName = groupNameInput.value.trim();
      const subgroup = subgroupInput.value.trim();

      if (!groupName || !subgroup) {
        alert("Please enter both group name and subgroup");
        return;
      }

      window.location.href = `/weekSchedule.html?week=currentWeek&groupName=${groupName}&subgroup=${subgroup}`;
    });

    getNextWeekScheduleButton.addEventListener("click", () => {
      const groupName = groupNameInput.value.trim();
      const subgroup = subgroupInput.value.trim();

      if (!groupName || !subgroup) {
        alert("Please enter both group name and subgroup");
        return;
      }
      window.location.href = `/weekSchedule.html?week=nextWeek&groupName=${groupName}&subgroup=${subgroup}`;
    });
  }

  if (getTodayButton && getTomorrowButton) {
    getTodayButton.addEventListener("click", () => {
      fetchSchedule("today");
    });

    getTomorrowButton.addEventListener("click", () => {
      fetchSchedule("tomorrow");
    });
  } else {
    console.error("Buttons for today and tomorrow not found.");
  }

  const fetchSchedule = (day) => {
    const groupName = groupNameInput.value.trim();
    const subgroup = subgroupInput.value.trim();

    if (!groupName || !subgroup) {
      alert("Please enter both group name and subgroup");
      return;
    }

    const currentDay = new Date().getDay(); // Get current day number (0=Sunday, 1=Monday, ..., 6=Saturday)
    window.location.href = `/daySchedule.html?day=${day}&groupName=${groupName}&subgroup=${subgroup}&currentDay=${currentDay}`;
  };
} else if (currentPage.includes("daySchedule.html")) {
  console.log("Loaded daySchedule.html");

  const weekdayElement = document.getElementById("weekday");
  const classesContainer = document.querySelector(".classes");
  const getTomorrowButton = document.getElementById("getTomorrow");
  const getTodayButton = document.getElementById("getToday");
  const goBackButton = document.getElementById("goBack");
  const getWeekScheduleButton = document.getElementById("getWeekSchedule");
  const getNextWeekScheduleButton = document.getElementById(
    "getNextWeekSchedule",
  );

  const urlParams = new URLSearchParams(window.location.search);
  const day = urlParams.get("day") || "today";
  const groupName = urlParams.get("groupName");
  const subgroup = urlParams.get("subgroup");

  if (getWeekScheduleButton && getNextWeekScheduleButton) {
    getWeekScheduleButton.addEventListener("click", () => {
      const groupName = urlParams.get("groupName");
      const subgroup = urlParams.get("subgroup");

      if (!groupName || !subgroup) {
        alert("Please enter both group name and subgroup");
        return;
      }

      window.location.href = `/weekSchedule.html?week=currentWeek&groupName=${groupName}&subgroup=${subgroup}`;
    });

    getNextWeekScheduleButton.addEventListener("click", () => {
      const groupName = urlParams.get("groupName");
      const subgroup = urlParams.get("subgroup");

      if (!groupName || !subgroup) {
        alert("Please enter both group name and subgroup");
        return;
      }
      window.location.href = `/weekSchedule.html?week=nextWeek&groupName=${groupName}&subgroup=${subgroup}`;
    });
  }

  if (day == "today") {
    getTomorrowButton.style.display = "inline-block";
    getTodayButton.style.display = "none";
  } else {
    getTomorrowButton.style.display = "none";
    getTodayButton.style.display = "inline-block";
  }

  const fetchSchedule = (day) => {
    if (!groupName || !subgroup) {
      alert("Please enter both group name and subgroup");
      return;
    }

    window.location.href = `/daySchedule.html?day=${day}&groupName=${groupName}&subgroup=${subgroup}`;
  };

  if (getTodayButton && goBackButton && getTomorrowButton) {
    goBackButton.addEventListener("click", () => {
      window.history.back();
    });

    getTomorrowButton.addEventListener("click", () => {
      fetchSchedule("tomorrow");
    });

    getTodayButton.addEventListener("click", () => {
      fetchSchedule("today");
    });
  } else {
    console.error("Buttons for today and tomorrow not found.");
  }

  if (groupName && subgroup) {
    fetch(`/classes/${day}?groupName=${groupName}&subgroup=${subgroup}`)
      .then((response) => response.json())
      .then((data) => {
        if (data.data && data.data.length > 0) {
          populateSchedule(data);
        } else {
          if (data.weekday == 7) {
            classesContainer.innerHTML = "<p class='message'>Выходной :)</p>";
            weekdayElement.innerHTML = `${weekdays[data.weekday - 1]}`;
          } else {
            classesContainer.innerHTML =
              "<p class='message'>Что-то пошло не так :(</p>";
          }
        }
      })
      .catch((error) => {
        console.error("Error fetching schedule:", error);
        classesContainer.innerHTML = `<div class="error">Error fetching schedule: ${error.message}</div>`;
      });
  } else {
    classesContainer.innerHTML =
      "<p>Missing group name or subgroup in URL parameters.</p>";
  }

  const weekdays = [
    "понедельник",
    "вторник",
    "среда",
    "четверг",
    "пятница",
    "суббота",
    "воскресенье",
  ];
  const populateSchedule = (data) => {
    const classes = data.data;
    const weekday = data.weekday;

    weekdayElement.textContent = weekdays[weekday - 1];

    classesContainer.innerHTML = "";

    classes.forEach((classItem) => {
      const classLine = document.createElement("div");
      classLine.classList.add("classLine");

      classLine.innerHTML = `
        <div class="classNumber">${classItem.class_number}</div>
        <div class="className">${classItem.class_name}</div>
        <div class="classTime">
          <p id="classStart">${getClassTime(classItem.class_number)[0]}</p>
          <p id="classEnd">${getClassTime(classItem.class_number)[1]}</p>
        </div>
        <div class="classTeacher">${classItem.teacher || "N/A"}</div>
        <div class="classroom">${classItem.classroom || "N/A"}</div>
      `;
      classesContainer.appendChild(classLine);
    });
  };
} else if (currentPage.includes("weekSchedule.html")) {
  console.log("Loaded weekSchedule.html");

  const weekdayElement = document.getElementById("weekName");
  const classesContainer = document.querySelector(".classes");
  const getTomorrowButton = document.getElementById("getTomorrow");
  const getTodayButton = document.getElementById("getToday");
  const goBackButton = document.getElementById("goBack");
  const getWeekScheduleButton = document.getElementById("getWeekSchedule");
  const getNextWeekScheduleButton = document.getElementById(
    "getNextWeekSchedule",
  );

  const urlParams = new URLSearchParams(window.location.search);
  const week = urlParams.get("week") || "currentWeek";
  const groupName = urlParams.get("groupName");
  const subgroup = urlParams.get("subgroup");

  weekdayElement.innerHTML =
    week == "nextWeek" ? "Следующая неделя" : "Текущая неделя";

  if (week === "nextWeek") {
    getWeekScheduleButton.style.display = "inline-block";
    getNextWeekScheduleButton.style.display = "none";
  } else {
    getNextWeekScheduleButton.style.display = "inline-block";
    getWeekScheduleButton.style.display = "none";
  }

  if (getWeekScheduleButton && getNextWeekScheduleButton) {
    getWeekScheduleButton.addEventListener("click", () => {
      if (!groupName || !subgroup) {
        alert("Please enter both group name and subgroup");
        return;
      }

      window.location.href = `/weekSchedule.html?week=currentWeek&groupName=${groupName}&subgroup=${subgroup}`;
    });

    getNextWeekScheduleButton.addEventListener("click", () => {
      if (!groupName || !subgroup) {
        alert("Please enter both group name and subgroup");
        return;
      }
      window.location.href = `/weekSchedule.html?week=nextWeek&groupName=${groupName}&subgroup=${subgroup}`;
    });
  }

  const fetchSchedule = (day) => {
    if (!groupName || !subgroup) {
      alert("Please enter both group name and subgroup");
      return;
    }

    window.location.href = `/daySchedule.html?day=${day}&groupName=${groupName}&subgroup=${subgroup}`;
  };

  if (getTodayButton && goBackButton && getTomorrowButton) {
    goBackButton.addEventListener("click", () => {
      window.history.back();
    });

    getTomorrowButton.addEventListener("click", () => {
      fetchSchedule("tomorrow");
    });

    getTodayButton.addEventListener("click", () => {
      fetchSchedule("today");
    });
  } else {
    console.error("Buttons for today and tomorrow not found.");
  }

  if (groupName && subgroup) {
    fetch(`/weekSchedule/${week}?groupName=${groupName}&subgroup=${subgroup}`)
      .then((response) => response.json())
      .then((data) => {
        if (data.data && data.data.length > 0) {
          populateSchedule(data);
        } else {
          classesContainer.innerHTML =
            "<p class='message'>No schedule available</p>";
        }
      })
      .catch((error) => {
        console.error("Error fetching schedule:", error);
        classesContainer.innerHTML = `<div class="error">Error fetching schedule: ${error.message}</div>`;
      });
  } else {
    classesContainer.innerHTML =
      "<p>Missing group name or subgroup in URL parameters.</p>";
  }

  const weekdays = [
    "Понедельник",
    "Вторник",
    "Среда",
    "Четверг",
    "Пятница",
    "Суббота",
    "Воскресенье",
  ];

  const populateSchedule = (data) => {
    const weekSchedule = data.data;

    // Clear previous content
    classesContainer.innerHTML = "";

    weekSchedule.forEach((daySchedule, index) => {
      const dayContainer = document.createElement("div");
      dayContainer.classList.add("dayContainer");

      const dayName = document.createElement("div");
      dayName.classList.add("weekday");
      dayName.textContent = weekdays[index];
      dayContainer.appendChild(dayName);

      if (daySchedule.length === 0) {
        // If daySchedule is empty, display "Выходной"
        const dayMessage = document.createElement("div");
        dayMessage.classList.add("classLine");
        dayMessage.textContent = "Выходной :)";
        dayContainer.appendChild(dayMessage);
      }

      daySchedule.forEach((classItem) => {
        const classLine = document.createElement("div");
        classLine.classList.add("classLine");

        classLine.innerHTML = `
          <div class="classNumber">${classItem.class_number}</div>
          <div class="className">${classItem.class_name}</div>
          <div class="classTime">
            <p id="classStart">${getClassTime(classItem.class_number)[0]}</p>
            <p id="classEnd">${getClassTime(classItem.class_number)[1]}</p>
          </div>
          <div class="classTeacher">${classItem.teacher || "N/A"}</div>
          <div class="classroom">${classItem.classroom || "N/A"}</div>
        `;
        dayContainer.appendChild(classLine);
      });

      classesContainer.appendChild(dayContainer);
    });
  };

  if (goBackButton) {
    goBackButton.addEventListener("click", () => {
      window.history.back();
    });
  }
}

const getClassTime = (classNumber) => {
  const classTimes = {
    1: ["08:30", "10:05"],
    2: ["10:20", "11:55"],
    3: ["12:10", "13:45"],
    4: ["14:15", "15:50"],
    5: ["16:05", "17:40"],
    6: ["17:55", "19:25"],
  };
  return classTimes[classNumber] || ["00:00", "00:00"];
};
