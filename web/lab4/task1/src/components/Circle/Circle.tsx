import React from "react";
import { CircleProps }from "./CircleProps"
import styles from "./Circle.module.css"

export const Circle: React.FC<CircleProps> = ({
  blackout = false,
}) => {
  return <div className={`${styles.circle} ${blackout ? styles.black : styles.white}`}></div>;
}
