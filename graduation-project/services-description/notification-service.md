# **Notification Service**

#### **Get Notifications**

**Request:** `GET /notifications`

**Flow:**

1. API Gateway validates JWT → extracts `userId`  
2. Forwards request to Notification Service  
3. Notification Service:
   - Retrieves all notifications for the current user (paginated)
   - Returns list sorted by creation date (newest first)

**Response:** `200 OK`

Response body:
```json
[
  {
    "id": "n001",
    "type": "BOARD_INVITE",
    "title": "You were added to a board",
    "message": "Alice added you to 'Marketing Roadmap'",
    "createdAt": "2025-10-16T12:00:00Z",
    "read": false
  },
  {
    "id": "n002",
    "type": "TASK_UPDATE",
    "title": "Task updated",
    "message": "Task 'Design login page' was moved to 'In Progress'",
    "createdAt": "2025-10-15T09:30:00Z",
    "read": true
  }
]
```

---

#### **Get Notification by ID**

**Request:** `GET /notifications/{id}`

**Flow:**

1. API Gateway validates JWT → extracts `userId`
2. Forwards request to Notification Service  
3. Notification Service:
   - Validates ownership of the notification  
   - Retrieves full details (with metadata if needed)
   - Returns notification info

**Response:** `200 OK`

Response body:
```json
{
  "id": "n001",
  "type": "BOARD_INVITE",
  "title": "You were added to a board",
  "message": "Alice added you to 'Marketing Roadmap'",
  "createdAt": "2025-10-16T12:00:00Z",
  "read": false,
  "data": {
    "boardId": "b123",
    "inviter": "Alice"
  }
}
```

---

#### **Mark Notifications as Read**

**Request:** `POST /notifications/read`

Request body:
```json
{
  "ids": ["n001", "n002", "n003"]
}
```

**Flow:**

1. API Gateway validates JWT → extracts `userId`
2. Forwards request to Notification Service  
3. Notification Service:
   - Validates ownership of notifications  
   - Updates `read` status to `true` for given IDs  
   - Returns confirmation  

**Response:** `204 No Content`

---

#### **Delete Notification**

**Request:** `DELETE /notifications/{id}`

**Flow:**

1. API Gateway validates JWT → extracts `userId`
2. Forwards request to Notification Service  
3. Notification Service:
   - Validates ownership  
   - Deletes notification record  
   - Returns confirmation  

**Response:** `204 No Content`

---

#### **Send Test Notification (Admin)**

**Request:** `POST /admin/notifications/test`

Request body:
```json
{
  "userId": "u001",
  "title": "Test Notification",
  "message": "This is a test notification from admin panel."
}
```

**Flow:**

1. API Gateway validates JWT → verifies `ADMIN` role  
2. Forwards request to Notification Service  
3. Notification Service:
   - Creates a test notification for the given user  
   - Optionally pushes it via WebSocket or queue to the user in real time  
   - Logs the action via **Activity Service**  

**Response:** `201 Created`

Response body:
```json
{
  "id": "n999",
  "status": "sent"
}
```

