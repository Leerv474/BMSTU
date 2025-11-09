# **Mailing Service**

#### **Send Mail**

**Request:** `POST /internal/mail/send`

Request body:

```json
{
  "to": "user@example.com",
  "subject": "Welcome to TaskFlow!",
  "templateId": "welcome-user",
  "variables": {
    "username": "John",
    "link": "https://app.example.com/welcome"
  }
}
```

**Flow:**

1. API Gateway forwards request (can be called publicly or internally, depending on use case)
2. Mailing Service:

   * Validates recipient address and template data
   * Loads email template (if `templateId` provided)
   * Merges dynamic variables into template
   * Sends message via SMTP or external provider (e.g., SendGrid)
   * Logs activity (via **Activity Service** → `/internal/activities`)
   * Returns delivery status

**Response:** `202 Accepted`

Response body:

```json
{
  "id": "m001",
  "status": "queued"
}
```

---

#### **Get Mail Status**

**Request:** `GET /admin/mail/status/{id}`

**Flow:**

1. API Gateway validates JWT → extracts `userId` and `role`
2. Gateway ensures the user has `ADMIN` role
3. Forwards request to Mailing Service
4. Mailing Service:

   * Looks up message by internal mail ID
   * Returns delivery status and metadata

**Response:** `200 OK`

Response body:

```json
{
  "id": "m001",
  "status": "delivered",
  "sentAt": "2025-10-16T12:00:00Z",
  "to": "user@example.com",
  "subject": "Welcome to TaskFlow",
  "providerMessageId": "sg-9f234...",
  "error": null
}
```

---

#### **Get Mail Templates**

**Request:** `GET /admin/mail/templates`

**Flow:**

1. API Gateway validates JWT → extracts `userId` and `role`
2. Ensures `ADMIN` privileges
3. Forwards request to Mailing Service
4. Mailing Service:

   * Retrieves list of email templates (paginated)
   * Returns summary info for each

**Response:** `200 OK`

Response body:

```json
[
  {
    "id": "welcome-user",
    "name": "Welcome Email",
    "subject": "Welcome to TaskFlow!",
    "createdAt": "2025-05-01T10:00:00Z"
  },
  {
    "id": "password-reset",
    "name": "Password Reset",
    "subject": "Reset your password",
    "createdAt": "2025-06-10T08:00:00Z"
  }
]
```

---

#### **Add Mail Template**

**Request:** `POST /admin/mail/templates`

Request body:

```json
{
  "id": "new-feature",
  "name": "New Feature Announcement",
  "subject": "Check out our latest update!",
  "body": "<p>Hello {{username}}, check out our new features <a href='{{link}}'>here</a>.</p>"
}
```

**Flow:**

1. API Gateway validates JWT → extracts `userId` and verifies `ADMIN` role
2. Forwards request to Mailing Service
3. Mailing Service:

   * Validates template ID and structure
   * Saves template to database/storage
   * Returns confirmation

**Response:** `201 Created`

Response body:

```json
{
  "id": "new-feature",
  "status": "created"
}
```

---

#### **Update Mail Template**

**Request:** `PUT /admin/mail/templates/{id}`

Request body:

```json
{
  "name": "Updated Welcome Email",
  "subject": "Welcome to TaskFlow (Updated)",
  "body": "<p>Hi {{username}}, welcome back to TaskFlow!</p>"
}
```

**Flow:**

1. API Gateway validates JWT → extracts `userId` and verifies `ADMIN` role
2. Forwards request to Mailing Service
3. Mailing Service:

   * Finds existing template
   * Updates fields
   * Returns updated template info

**Response:** `200 OK`

Response body:

```json
{
  "id": "welcome-user",
  "status": "updated"
}
```

---

#### **Delete Mail Template**

**Request:** `DELETE /admin/mail/templates/{id}`

**Flow:**

1. API Gateway validates JWT → verifies `ADMIN` role
2. Forwards request to Mailing Service
3. Mailing Service:

   * Removes template from database/storage
   * Logs action in Activity Service
   * Returns confirmation

**Response:** `204 No Content`


