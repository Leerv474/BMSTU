import { ChangeEvent, useState } from "react";
import styles from "./AddForm.module.css";
import AddFormProps from "./AddFormProps";

export const AddForm: React.FC<AddFormProps> = ({
  // studentName,
  setValue,
}) => {
  const [inputValue, setInputValue] = useState<string>("");
  const handleChange = (e: ChangeEvent<HTMLInputElement>) => {
    setInputValue(e.target.value);
  };

  const onClick = () => {
    if (inputValue.trim() !== "") {
      setValue((prev) => [...prev, inputValue]);
      setInputValue("");
    }
  };

  const handleSpacebarPress = (
    event: React.KeyboardEvent<HTMLInputElement>,
  ) => {
    if (event.key === " ") {
      onClick();
      event.preventDefault();
    }
  };
  return (
    <>
      <input
        className={styles.input}
        type="text"
        name="student"
        value={inputValue}
        onChange={handleChange}
        onKeyDown={handleSpacebarPress}
      />
      <button onClick={onClick} className={styles.add_button}>
        Add student
      </button>
    </>
  );
};
