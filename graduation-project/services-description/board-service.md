# **Boards**

#### **Create Board**

**Request:** `POST /boards`
Request Body:

```json
{
  "name": "...",
  "customStatuses": ["...", "...", "..."]
}
```

**Flow:**

1. Gateway validates JWT → extracts `userId` and `role`
2. Forwards request to Board Service (adds `X-User-Id`)
3. Board Service:

   - Creates board (sets `creatorId = userId`)
   - Adds default and any provided custom statuses
   - Sets order and relationships
   - Emits `BoardCreated` event to Activity Service
     **Response:** `201 Created` → returns board details

Response Body:

```json
{
  "id": "...",
  "name": "...",
  "statuses": [
    { "id": "s001", "name": "to do", "order": 1 },
    { "id": "s002", "name": "in progress", "order": 2 },
    { "id": "s003", "name": "done", "order": 3 }
  ]
}
```

#### **Get Boards**

**Request:** `GET /boards`

**Flow:**

1. Gateway validates JWT → extracts `userId`
2. Forwards request to Board Service
3. Board Service:

   - Retrieves all boards accessible by `userId`
     **Response:** `200 OK` → returns list of boards

Response Body:

```json
{
  "boardList": [
    {
      "id": "...",
      "name": "..."
    },
    {
      "id": "...",
      "name": "..."
    }
  ]
}
```

#### **Get Board**

**Request:** `GET /boards/{boardId}`
**Flow:**

1. Gateway validates JWT → extracts `userId`
2. Forwards request to Board Service
3. Board Service:

   - Fetches board
   - Verifies access permissions
   - Fetches related tasks and projects
   - Emits `BoardViewed` event
     **Response:** `200 OK` → returns board details

Response Body:

```json
{
  "id": "...",
  "name": "...",
  "statuses": [
    { "id": "s001", "name": "to do", "order": 1 },
    { "id": "s002", "name": "in progress", "order": 2 },
    { "id": "s003", "name": "done", "order": 3 }
  ]
}
```

#### **Update Board (Rename / Edit Metadata)**

**Request:** `PATCH /boards/{boardId}`
Request Body:

```json
{
  "name": "?"
}
```

**Flow:**

1. Gateway validates JWT
2. Board Service:

   - Fetches board and validates access
   - Updates board fields (e.g. name, description)
   - Emits `BoardUpdated` event
     **Response:** `204 No Content`

#### **Update Board Statuses** (cancelled)

**Request:** `PATCH /boards/{boardId}/statuses`

**Flow:**

1. Gateway validates JWT
2. Board Service:

   - Validates user access
   - Updates or reorders statuses
   - Emits `BoardUpdated` event
     **Response:** `204 No Content`

#### **Reorder Board Statuses**

**Request:** `PATCH /boards/{boardId}/statuses/reorder`
Request body:

```json
{
  "order": [
    { "id": "...", "position": "..." },
    { "id": "...", "position": "..." },
    { "id": "...", "position": "..." }
  ]
}
```

**Flow:**

1. Gateway validates JWT
2. Board Service:

   - Validates user access
   - Reorders statuses
   - Emits `BoardUpdated` event
     **Response:** `204 No Content`

#### **Delete Board**

**Request:** `DELETE /boards/{boardId}`
**Flow:**

1. Gateway validates JWT
2. Board Service:

   - Validates access
   - Soft-deletes board
   - Emits `BoardDeleted` event
     **Response:** `204 No Content`

---

### **Tasks**

#### **Create Task**

**Request:** `POST /boards/{boardId}/tasks`
Request body:

```json
{
  "title": "...",
  "description": "...",
  "deadline": "..."
}
```

**Flow:**

1. Gateway validates JWT
2. Board Service:

   - Validates board access
   - Creates new task (sets default status)
   - Emits `TaskCreated` event
     **Response:** `201 Created` → returns task details

Response body:

```json
{
  "id": "...",
  "title": "...",
  "description": "...",
  "deadline": "..."
}
```

#### **Get Task**

**Request:** `GET /tasks/{taskId}`
**Flow:**

1. Gateway validates JWT
2. Board Service:

   - Fetches task
   - Validates access
   - Emits `TaskViewed` event
     **Response:** `200 OK` → returns task details

Response Body:

```json
{
  "id": "...",
  "title": "...",
  "description": "...",
  "deadline": "..."
}
```

#### **Update Task**

**Request:** `PATCH /tasks/{taskId}`
Request body:

```json
{
  "name": "?",
  "description": "?",
  "deadline": "?"
}
```

**Flow:**

1. Gateway validates JWT
2. Board Service:

   - Fetches task and validates access
   - Applies partial updates
   - Emits `TaskUpdated` event
     **Response:** `204 No Content`

#### **Delete Task**

**Request:** `DELETE /tasks/{taskId}`
**Flow:**

1. Gateway validates JWT
2. Board Service:

   - Validates access
   - Soft-deletes task
   - Emits `TaskDeleted` event
     **Response:** `204 No Content`

---

### **Projects**

#### **Create Project**

**Request:** `POST /boards/{boardId}/projects`
Request body:

```json
{
  "title": "...",
  "description": "...",
  "deadline": "..."
}
```

**Flow:**

1. Gateway validates JWT
2. Board Service:

   - Validates board access
   - Creates project
   - Emits `ProjectCreated` event
     **Response:** `201 Created` → returns project details

Request body:

```json
{
  "id": "...",
  "title": "...",
  "description": "...",
  "deadline": "..."
}
```

---

#### **Convert Task to Project**

**Request:** `POST /tasks/{taskId}/convert`
**Flow:**

1. Gateway validates JWT
2. Board Service:

   - Validates task access
   - Creates project (copies shared fields)
   - Soft-deletes old task
   - Emits `TaskConverted` event
     **Response:** `201 Created` → returns project details

Response body:

```json
{
  "id": "...",
  "title": "...",
  "description": "...",
  "deadline": "..."
}
```

#### **Get Project**

**Request:** `GET /projects/{projectId}`
**Flow:**

1. Gateway validates JWT
2. Board Service:

   - Fetches project
   - Validates access
   - Emits `ProjectViewed` event
     **Response:** `200 OK` → returns project details

Response body:

```json
{
  "id": "...",
  "title": "...",
  "description": "...",
  "deadline": "..."
}
```

#### **Update Project**

**Request:** `PATCH /projects/{projectId}`
Request body:

```json
{
  "title": "?"
  "description": "?",
  "deadline": "?"
}
```

**Flow:**

1. Gateway validates JWT
2. Board Service:

   - Validates access
   - Applies updates
   - Emits `ProjectUpdated` event
     **Response:** `204 No Content`

#### **Delete Project**

**Request:** `DELETE /projects/{projectId}`
**Flow:**

1. Gateway validates JWT
2. Board Service:

   - Validates access
   - Soft-deletes project
   - Emits `ProjectDeleted` event
     **Response:** `204 No Content`

#### **List Project Tasks**

**Request:** `GET /projects/{projectId}/tasks`
**Flow:**

1. Gateway validates JWT
2. Board Service:

   - Validates access
   - Fetches related tasks
     **Response:** `200 OK` → returns task list

Response body:

```json
{
  "taskList": [
    {
      "id": "...",
      "title": "..."
    },
    {
      "id": "...",
      "title": "..."
    },
    {
      "id": "...",
      "title": "..."
    }
  ]
}
```

---

### **Statuses**

#### **Create Status**

**Request:** `POST /boards/{boardId}/statuses`
Request body:

```json
{
  "name": "...",
  "order": "..."
}
```

**Flow:**

1. Gateway validates JWT
2. Board Service:

   - Validates board access
   - Creates new status
   - Emits `StatusCreated` event
     **Response:** `201 Created` → returns status details

Response body:

```json
{
  "id": "...",
  "name": "...",
  "order": "..."
}
```

#### **Get Status**

**Request:** `GET /statuses/{statusId}`
**Flow:**

1. Gateway validates JWT
2. Board Service:

   - Fetches status
   - Validates access
   - Emits `StatusViewed` event
     **Response:** `200 OK` → returns status details

Response body:

```json
{
  "id": "...",
  "name": "...",
  "order": "..."
}
```

#### **Update Status**

**Request:** `PATCH /statuses/{statusId}`
Request body:

```json
{
  "name": "?",
  "order": "?"
}
```

**Flow:**

1. Gateway validates JWT
2. Board Service:

   - Validates access
   - Updates status
   - Emits `StatusUpdated` event
     **Response:** `204 No Content`

#### **Delete Status**

**Request:** `DELETE /statuses/{statusId}`
**Flow:**

1. Gateway validates JWT
2. Board Service:

   - Validates access
   - Soft-deletes status
   - Emits `StatusDeleted` event
     **Response:** `204 No Content`

#### **Get Tasks by Status**

**Request:** `GET /statuses/{statusId}/tasks`
**Flow:**

1. Gateway validates JWT
2. Board Service:

   - Validates access
   - Retrieves all tasks under the status
     **Response:** `200 OK` → returns task list

Response body:

```json
{
  "taskList": [
    { "id": "...", "title": "..." },
    { "id": "...", "title": "..." },
    { "id": "...", "title": "..." }
  ]
}
```

---


| `POST`    | `/board/{boardId}/lock`              | Заблокировать доску                      |
| `POST`    | `/board/{boardId}/unlock`            | Разблокировать доску                     |
