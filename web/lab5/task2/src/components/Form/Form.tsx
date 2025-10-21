import React, { useState, ChangeEvent, FormEvent } from "react";
import styles from "./Form.module.css";

interface FormData {
  firstName: string;
  lastName: string;
  email: string;
  phone: string;
  gender: string;
}

interface FormErrors {
  firstName?: string;
  lastName?: string;
  email?: string;
  phone?: string;
  gender?: string;
}

const FormComponent: React.FC = () => {
  const [formData, setFormData] = useState<FormData>({
    firstName: "",
    lastName: "",
    email: "",
    phone: "",
    gender: "",
  });

  const [errors, setErrors] = useState<FormErrors>({});

  const validate = (): boolean => {
    const newErrors: FormErrors = {};
    const { firstName, lastName, email, phone, gender } = formData;

    if (!firstName.trim()) newErrors.firstName = "Введите имя";
    if (!lastName.trim()) newErrors.lastName = "Введите фамилию";
    if (!email.trim()) newErrors.email = "Введите email";
    else if (!/^[^\s@]+@[^\s@]+\.[^\s@]+$/.test(email))
      newErrors.email = "Неверный формат email";

    if (!phone.trim()) newErrors.phone = "Введите номер телефона";
    else if (!/^\+?\d{7,15}$/.test(phone))
      newErrors.phone = "Неверный формат номера";

    if (!gender) newErrors.gender = "Выберите пол";

    setErrors(newErrors);
    return Object.keys(newErrors).length === 0;
  };

  const handleChange = (
    e: ChangeEvent<HTMLInputElement | HTMLSelectElement>
  ) => {
    const { name, value } = e.target;
    setFormData((prev) => ({
      ...prev,
      [name]: value,
    }));
  };

  const handleSubmit = (e: FormEvent<HTMLFormElement>) => {
    e.preventDefault();
    if (validate()) {
      console.log("Данные формы:", formData);
      alert(`Отправлено:\n${JSON.stringify(formData, null, 2)}`);

      // Очистка формы
      setFormData({
        firstName: "",
        lastName: "",
        email: "",
        phone: "",
        gender: "",
      });
      setErrors({});
    }
  };

  return (
    <div className={styles.container}>
      <h2 className={styles.title}>Форма регистрации</h2>
      <form onSubmit={handleSubmit} noValidate>
        <div className={styles.formGroup}>
          <label className={styles.label}>Имя:</label>
          <input
            className={styles.input}
            type="text"
            name="firstName"
            value={formData.firstName}
            onChange={handleChange}
          />
          {errors.firstName && (
            <div className={styles.error}>{errors.firstName}</div>
          )}
        </div>

        <div className={styles.formGroup}>
          <label className={styles.label}>Фамилия:</label>
          <input
            className={styles.input}
            type="text"
            name="lastName"
            value={formData.lastName}
            onChange={handleChange}
          />
          {errors.lastName && (
            <div className={styles.error}>{errors.lastName}</div>
          )}
        </div>

        <div className={styles.formGroup}>
          <label className={styles.label}>Email:</label>
          <input
            className={styles.input}
            type="email"
            name="email"
            value={formData.email}
            onChange={handleChange}
          />
          {errors.email && (
            <div className={styles.error}>{errors.email}</div>
          )}
        </div>

        <div className={styles.formGroup}>
          <label className={styles.label}>Телефон:</label>
          <input
            className={styles.input}
            type="tel"
            name="phone"
            value={formData.phone}
            onChange={handleChange}
          />
          {errors.phone && (
            <div className={styles.error}>{errors.phone}</div>
          )}
        </div>

        <div className={styles.formGroup}>
          <label className={styles.label}>Пол:</label>
          <select
            className={styles.select}
            name="gender"
            value={formData.gender}
            onChange={handleChange}
          >
            <option value="">-- Выберите --</option>
            <option value="male">Мужской</option>
            <option value="female">Женский</option>
          </select>
          {errors.gender && (
            <div className={styles.error}>{errors.gender}</div>
          )}
        </div>

        <button type="submit" className={styles.button}>
          Отправить
        </button>
      </form>
    </div>
  );
};

export default FormComponent;

