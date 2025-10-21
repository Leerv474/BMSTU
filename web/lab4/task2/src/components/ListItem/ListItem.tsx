import styles from "./ListItem.module.css";
import ListItemProps from "./ListItemProps";

export const ListItem: React.FC<ListItemProps> = ({ itemName }) => {
  return <li className={styles.list_item}>{itemName}</li>;
};
