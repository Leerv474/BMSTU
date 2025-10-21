import React, { useEffect, useState } from "react";
import "./App.css";
import { ListItem } from "./components/ListItem/ListItem";

function App() {
  let [items, setItems] = useState<string[]>([]);

  useEffect(() => {
    setItems(["eggs", "apples", "banana", "potato", "oil", "rice"]);
  }, []);

  return (
    <div className="App">
      <h3>Shopping list</h3>
      <>
        {items.map((value, _) => (
          <ListItem itemName={value} />
        ))}
      </>
    </div>
  );
}

export default App;
