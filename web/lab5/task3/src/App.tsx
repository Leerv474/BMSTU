import React, { useState } from "react";
import logo from "./logo.svg";
import "./App.css";
import { AddForm } from "./components/AddForm/AddForm";
import { ListItem } from "./components/ListItem/ListItem";

function App() {
  let [studentList, setStudentList] = useState<string[]>([]);

  return (
    <>
      <div className="App">
        <h1>Students</h1>
        <AddForm
          setValue={setStudentList}
        />
        {studentList.map((student, _) => {
          return <ListItem listItemValue={student} />;
        })}
      </div>
    </>
  );
}

export default App;
