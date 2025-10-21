# User Service

`user_service_db`

Сущности:

- users (id, email, username, is_enabled, created_at, updated_at)
- roles (id, name, description)

Связи:

- пользователь имеет множество ролей

# Auth Service

`auth_service_db`

Сущности:

- credentials (id, user_id, email, password_hash, is_locked, created_at, updated_at)
- refresh_tokens (id, user_id, token, expires_at, revoked)
- password_reset_tokens (id, user_id, token, expires_at, used)

# Activity Service

`activity_service_db`

Сущности:

- activity (id, user_id, entity_type, entity_id, event_type, description, metadata, created_at)

# Board Service

`board_service_db`

Сущности:

- boards (id, name, created_at, updated_at, is_deleted, deleted_at)
- statuses (id, name, completion_order, created_at, updated_at, is_deleted, deleted_at)
- projects (id, title, description, deadline, created_at, updated_at, is_deleted, deleted_at)
- tasks (id, title, description, deadline, completed_at, created_at, updated_at, is_deleted, deleted_at)

Связи:

- доски содержат множество статусов
- доски содержат множество проектов
- статусы содержат множество задач
- проекты содержат множество задач

# Email and Notification Service

`messaging_services_db`

Сущности:

- email_messages (id, user_id, status, subject, body, template_id, metadata, created_at, sent_at)
- email_templates (id, name, subject, body, language, created_at, updated_at)
- notification_messages (id, user_id, status, body, template_id, metadata, created_at, read_at)
