# События

| Событие                  | Когда возникает                    | Кто слушает             |
| ------------------------ | ---------------------------------- | ----------------------- |
| `UserRegistered`         | Новый пользователь зарегистрирован | User, Mailing, Activity |
| `UserLoggedIn`           | Пользователь успешно вошёл         | Activity                |
| `UserLoggedOut`          | Пользователь вышел                 | Activity                |
| `PasswordChanged`        | Пользователь изменил пароль        | Mailing, Activity       |
| `PasswordResetRequested` | Запрошен сброс пароля              | Mailing                 |
| `PasswordResetCompleted` | Пароль успешно сброшен             | Activity                |

---

# User Service

| Событие              | Когда возникает             | Кто слушает    |
| -------------------- | --------------------------- | -------------- |
| `UserProfileCreated` | Создан профиль пользователя | Activity       |
| `UserProfileUpdated` | Изменён профиль             | Activity       |
| `UserDeleted`        | Пользователь удалён         | Activity, Auth |
| `UserRoleChanged`    | Изменена роль пользователя  | Activity       |
| `UserSuspended`      | User                        | Activity, Auth |

# Mailing Service

| Событие           | Когда возникает     | Кто слушает |
| ----------------- | ------------------- | ----------- |
| `EmailSent`       | Письмо отправлено   | Activity    |
| `EmailFailed`     | Ошибка при отправке | Activity    |
| `TemplateUpdated` | Обновлён шаблон     | Activity    |

# Board Management

| Категория | Событие                   | Кто слушает            |
| --------- | ------------------------- | ---------------------- |
| Board     | `BoardCreated`            | Activity               |
| Board     | `BoardUpdated`            | Activity               |
| Board     | `BoardDeleted`            | Activity               |
| Project   | `ProjectCreated`          | Activity               |
| Project   | `ProjectUpdated`          | Activity               |
| Project   | `ProjectDeleted`          | Activity               |
| Task      | `TaskCreated`             | Notification, Activity |
| Task      | `TaskUpdated`             | Notification, Activity |
| Task      | `TaskDeleted`             | Activity               |
| Task      | `TaskStatusChanged`       | Notification           |
| Task      | `TaskDeadlineApproaching` | Notification           |
| Task      | `TaskAssigned`            | Notification           |

# Notification Service

| Событие              | Когда возникает        | Кто слушает |
| -------------------- | ---------------------- | ----------- |
| `NotificationSent`   | Уведомление доставлено | Activity    |
| `NotificationFailed` | Ошибка уведомления     | Activity    |
