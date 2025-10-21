import React, { useState } from "react";
import styles from "./Room.module.css";

export const Room: React.FC = () => {
  const [isLightOn, setIsLightOn] = useState<boolean>(true);

  const toggleLight = () => {
    setIsLightOn((prev) => !prev);
  };

  return (
    <div
      className={`${styles.container} ${isLightOn ? styles.lightOn : styles.lightOff}`}
    >
      <h2>Комната</h2>
      <p>{isLightOn ? "В комнате светло" : "В комнате темно"}</p>
      <button
        onClick={toggleLight}
        className={`${styles.button} ${isLightOn ? styles.lightOn : styles.lightOff}`}
      >
        Выключатель света
      </button>
    </div>
  );
};
