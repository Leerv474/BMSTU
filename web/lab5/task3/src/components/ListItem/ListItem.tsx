import React from "react";
import styles from "./ListItem.module.css"
import ListItemProps from "./ListItemProps";

export const ListItem: React.FC<ListItemProps> = ({
  listItemValue
}) => {
  return <>
    <div className={styles.list_item}>
      {listItemValue}
    </div>
  </>;
};
