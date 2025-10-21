import React, { useState } from "react";
import "./App.css";
import { Button } from "./components/Button/Button";
import { Circle } from "./components/Circle/Circle";

function App() {
  let [blackout, setBlackout] = useState(false);
  return (
    <div className="root">
      <Circle blackout={blackout} />
      <Button
        onClick={() => {
          setBlackout(!blackout);
        }}
      />
    </div>
  );
}

export default App;
