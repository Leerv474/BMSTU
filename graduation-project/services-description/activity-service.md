# **Activity Service**

#### **Get All Activities**

**Request:** `GET /admin/activities`

**Flow:**

1. API Gateway validates JWT → extracts `userId` and `role`
2. Gateway verifies that the user has `ADMIN` role
3. Forwards request to Activity Service
4. Activity Service:

   * Retrieves a paginated list of activity logs
   * Supports filters: `?from=`, `?to=`, `?action=`, `?userId=`, `?service=`
   * Returns the activity list

**Response:** `200 OK`

Response body:

```json
[
  {
    "id": "a001",
    "timestamp": "2025-10-16T12:00:00Z",
    "userId": "u001",
    "service": "BoardService",
    "action": "BoardCreated",
    "details": {
      "boardId": "b123",
      "boardName": "Development Roadmap"
    }
  },
  {
    "id": "a002",
    "timestamp": "2025-10-16T12:05:00Z",
    "userId": "u002",
    "service": "AuthService",
    "action": "Login",
    "details": {}
  }
]
```
$2^2$

---

#### **Get Activity by ID**

**Request:** `GET /admin/activities/{id}`

**Flow:**

1. API Gateway validates JWT → extracts `userId` and `role`
2. Gateway verifies that the user has `ADMIN` role
3. Forwards request to Activity Service
4. Activity Service:

   * Retrieves specific log entry by ID
   * Returns detailed activity data

**Response:** `200 OK`

Response body:

```json
{
  "id": "a001",
  "timestamp": "2025-10-16T12:00:00Z",
  "userId": "u001",
  "service": "BoardService",
  "action": "BoardCreated",
  "details": {
    "boardId": "b123",
    "boardName": "Development Roadmap"
  }
}
```

---

#### **Get User Activities**

**Request:** `GET /admin/activities/user/{userId}`

**Flow:**

1. API Gateway validates JWT → extracts `userId` and `role`
2. Gateway verifies that the requester has `ADMIN` role
3. Forwards request to Activity Service
4. Activity Service:

   * Queries all logs for given `userId`
   * Returns chronological list of actions

**Response:** `200 OK`

Response body:

```json
[
  {
    "id": "a005",
    "timestamp": "2025-10-15T14:20:00Z",
    "userId": "u003",
    "service": "BoardService",
    "action": "TaskUpdated",
    "details": { "taskId": "t123", "status": "In Progress" }
  }
]
```

---

#### **Get Service Activities**

**Request:** `GET /admin/activities/service/{serviceName}`

**Flow:**

1. API Gateway validates JWT → extracts `userId` and `role`
2. Gateway verifies that the requester has `ADMIN` role
3. Forwards request to Activity Service
4. Activity Service:

   * Fetches all logs produced by a given microservice (e.g., `"AuthService"`, `"BoardService"`)
   * Returns log entries grouped or sorted by timestamp

**Response:** `200 OK`

Response body:

```json
[
  {
    "id": "a010",
    "timestamp": "2025-10-16T10:00:00Z",
    "service": "AuthService",
    "action": "UserRegistered",
    "details": { "userId": "u007", "email": "test@mail.com" }
  }
]
```

---

#### **Record New Activity (Internal)**

**Request:** `POST /internal/activities`

Request body:

```json
{
  "timestamp": "2025-10-16T12:00:00Z",
  "userId": "u001",
  "service": "BoardService",
  "action": "TaskCreated",
  "details": {
    "taskId": "t789",
    "boardId": "b321"
  }
}
```

**Flow:**

1. Called internally by other microservices (no JWT; secured via service token)
2. Authenticated via `X-Service-Token` header
3. Activity Service:

   * Validates payload
   * Writes new log entry to database
   * Returns confirmation

**Response:** `201 Created`

Response body:

```json
{
  "id": "a012",
  "status": "logged"
}
```
