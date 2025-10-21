import React from "react"
import ButtonProps from "./ButtonProps"
import styles from "./Button.module.css"

export const Button: React.FC<ButtonProps> = ({onClick}) => {
  return <button className={styles.circle} onClick={onClick}>
    Change color
  </button>
}
