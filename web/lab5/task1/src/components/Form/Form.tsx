import React, { Component, ChangeEvent, FormEvent } from "react";
import styles from "./Form.module.css";

interface FormState {
  firstName: string;
  lastName: string;
  email: string;
  phone: string;
  gender: string;
  errors: {
    firstName?: string;
    lastName?: string;
    email?: string;
    phone?: string;
    gender?: string;
  };
}

class FormComponent extends Component<{}, FormState> {
  constructor(props: {}) {
    super(props);
    this.state = {
      firstName: "",
      lastName: "",
      email: "",
      phone: "",
      gender: "",
      errors: {},
    };
  }

  validate = (): boolean => {
    const errors: FormState["errors"] = {};
    const { firstName, lastName, email, phone, gender } = this.state;

    if (!firstName.trim()) errors.firstName = "Введите имя";
    if (!lastName.trim()) errors.lastName = "Введите фамилию";
    if (!email.trim()) errors.email = "Введите email";
    else if (!/^[^\s@]+@[^\s@]+\.[^\s@]+$/.test(email))
      errors.email = "Неверный формат email";

    if (!phone.trim()) errors.phone = "Введите номер телефона";
    else if (!/^\+?\d{7,15}$/.test(phone))
      errors.phone = "Неверный формат номера";

    if (!gender) errors.gender = "Выберите пол";

    this.setState({ errors });
    return Object.keys(errors).length === 0;
  };

  handleChange = (e: ChangeEvent<HTMLInputElement | HTMLSelectElement>) => {
    const { name, value } = e.target;
    this.setState({ [name]: value } as unknown as Pick<FormState, keyof FormState>);
  };

  handleSubmit = (e: FormEvent<HTMLFormElement>) => {
    e.preventDefault();
    if (this.validate()) {
      const { firstName, lastName, email, phone, gender } = this.state;
      const formData = { firstName, lastName, email, phone, gender };

      console.log("Данные формы:", formData);
      alert(`Отправлено:\n${JSON.stringify(formData, null, 2)}`);

      this.setState({
        firstName: "",
        lastName: "",
        email: "",
        phone: "",
        gender: "",
        errors: {},
      });
    }
  };

  render() {
    const { firstName, lastName, email, phone, gender, errors } = this.state;

    return (
      <div className={styles.container}>
        <h2 className={styles.title}>Форма регистрации</h2>
        <form onSubmit={this.handleSubmit} noValidate>
          <div className={styles.formGroup}>
            <label className={styles.label}>Имя:</label>
            <input
              className={styles.input}
              type="text"
              name="firstName"
              value={firstName}
              onChange={this.handleChange}
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
              value={lastName}
              onChange={this.handleChange}
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
              value={email}
              onChange={this.handleChange}
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
              value={phone}
              onChange={this.handleChange}
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
              value={gender}
              onChange={this.handleChange}
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
  }
}

export default FormComponent;

