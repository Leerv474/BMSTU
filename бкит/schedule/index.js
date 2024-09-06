window.onload = function() {
  fetch('http://localhost:3000/classes/today')
    .then(response => response.json())
    .then(data => {
      console.log('Fetched data:', data);  // Log the fetched data for debugging

      const classes = data.data;
      if (!classes || classes.length === 0) {
        console.error('No classes found for today.');
        return;
      }

      const classNumbers = document.getElementsByClassName("classNumber");
      const classTimes = document.getElementsByClassName("classTime");
      const classSubjects = document.getElementsByClassName("className");
      const classTeachers = document.getElementsByClassName("classTeacher");
      const classrooms = document.getElementsByClassName("classroom");

      // Populate the HTML elements with class data
      classes.forEach((classItem, index) => {
        if (classNumbers[index]) {
          classNumbers[index].textContent = classItem.class_number;
          classSubjects[index].textContent = classItem.class_name;
          const [startTime, endTime] = getClassTime(classItem.class_number);
          classTimes[index].querySelector("#classStart").textContent = startTime;
          classTimes[index].querySelector("#classEnd").textContent = endTime;
          classTeachers[index].textContent = classItem.teacher;
          classrooms[index].textContent = classItem.classroom || "N/A";
        }
      });
    })
    .catch(error => console.error('Error fetching classes:', error));
};

const getClassTime = (classNumber) => {
  const classTimes = {
    1: ['08:30', '10:05'],
    2: ['10:20', '11:55'],
    3: ['12:10', '13:45'],
    4: ['14:15', '15:50'],
    5: ['16:05', '17:40'],
    6: ['17:55', '19:25']
  };
  return classTimes[classNumber] || ['00:00', '00:00'];
};

