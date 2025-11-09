# **Users Service**

#### Get Public User

**Request:** `GET /users/{id}`

**Flow:**

1. Gateway validates JWT -> extracts `userId` and `role`
2. Forwards request to User Service
3. User Service

   - Validates access
   - Retrieves user data
     **Response:** `200 OK` -> returns user data

Response body:

```json
{
  "id": "...",
  "username": "..."
}
```

#### Get Curret User

**Request:** `GET /users/me`

**Flow:**

1. Gateway validates JWT -> extracts `userId` and `role`
2. Forwards request to User Service
3. User Service

   - Validates access
   - Retrieves user data
     **Response:** `200 OK` -> returns user data

Response body:

```json
{
  "id": "...",
  "username": "..."
  "email": "..."
}
```

#### Update Current User

**Request:** `PATCH /users/me`
Request body:

```json
{
  "username": "?",
  "email": "?"
}
```

**Flow:**

1. Gateway validates JWT -> extracts `userId` and `role`
2. Forwards request to User Service
3. User Service

   - Validates access
   - Retrieves user data
   - Updates user fields
   - Emits `UserUpdated` event
     **Response:** `204 No Content`

#### Delete Current User

**Request:** `DELETE /users/me`

**Flow:**

1. Gateway validates JWT -> extracts `userId` and `role`
2. Forwards request to User Service
3. User service
   - Validates access
   - Soft-deletes user
   - Emits `UserDeleted` event
     **Response:** `204 No Content`

#### Create User

**Request:** `POST /internal/users`
Request body:

```json
{
  "username": "...",
  "email": "...",
  "created_by": "...",
  "role": "..."
}
```

**Flow:**

1. Verifies service token
2. Creates new user entity
3. Emits `UserCreated` event
   **Response:** `201 Created`

Response body:

```json
{
  "id": "...",
  "username": "...",
  "email": "...",
  "created_by": "...",
  "role": "..."
}
```

#### Disable User

**Request:** `PATCH /internal/users/{id}/disable`

**Flow:**

1. Verifies service token
2. Disables user
3. Emits `UserDisabled` event
   **Response:** `204 No Content`

#### Enable User

**Request:** `PATCH /internal/users/{id}/enable`

**Flow:**

1. Verifies service token
2. Enables user
3. Emits `UserEnabled` event
   **Response:** `204 No Content`

#### Update User

**Request:** `PATCH /admin/users/{id}`

```json
{
  "username": "...",
  "email": "..."
}
```

**Flow:**

1. Gateway validates JWT -> extracts `userId` and `role`
2. Forwards request to User Service
3. User service
   - Validates admin access
   - Applies changes
   - Emits `UserUpdated` event
     **Response:** `204 No Content`

#### Delete User

**Request:** `DELETE /admin/users/{id}`

**Flow:**

1. Gateway validates JWT -> extracts `userId` and `role`
2. Forwards request to User Service
3. User Service
   - Validates admin access
   - Soft-deletes data
   - Emits `UserUpdated` event
     **Response:** `204 No Content`

#### Get User List

**Request:** `GET /admin/users`

**Flow:**

1. Gateway validates JWT -> extracts `userId` and `role`
2. Forwards request to User Service
3. User Service
   - Validates admin access
   - Fetches data
     **Response:** `200 OK` with user list

Response body:

```json
{
  "userList": [
    {
      "id": "...",
      "username": "...",
      "email": "...",
      "is_enabled": "...",
      "created_at": "...",
      "updated_at": "...",
      "created_by": "..."
    }
  ]
}
```

#### Get User By ID

**Request:** `GET /admin/users/{id}`

**Flow:**

1. Gateway validates JWT -> extracts `userId` and `role`
2. Forwards request to User Service
3. User Service
   - Validates admin access
   - Fetches data
     **Response:** `200 OK` with user details

Response body:

```json
{
  "id": "...",
  "username": "...",
  "email": "...",
  "is_enabled": "...",
  "created_at": "...",
  "updated_at": "...",
  "created_by": "...",
  "roles": []
}
```

#### Get Roles

**Request:** `GET /admin/roles`

**Flow:**

1. Gateway validates JWT -> extracts `userId` and `role`
2. Forwards request to User Service
3. User Service
   - Validates admin access
   - Fetches data
     **Response:** `200 OK` with roles list

Response body:

```json
{
  "roleList": [
    { "id": "...", "name": "...", "description": "..." },
    { "id": "...", "name": "...", "description": "..." }
  ]
}
```

#### Get Roles of User

**Request:** `GET /admin/users/{id}/roles`

**Flow:**

1. Gateway validates JWT -> extracts `userId` and `role`
2. Forwards request to User Service
3. User Service
   - Validates admin access
   - Fetches data
     **Response:** `200 OK` with role details

Response body:

```json
{
  "userRoles": [
    { "id": "...", "name": "...", "description": "..." },
    { "id": "...", "name": "...", "description": "..." }
  ]
}
```

#### Update Roles of User

**Request:** `PUT /admin/users/{id}/roles`
Request body:

```json
{
  "userRoles": [
    { "id": "...", "name": "...", "description": "..." },
    { "id": "...", "name": "...", "description": "..." }
  ]
}
```

**Flow:**

1. Gateway validates JWT -> extracts `userId` and `role`
2. Forwards request to User Service
3. User Service
   - Validates admin access
   - Fetches data
   - Applies changes
   - Emits `UserRolesUpdated` event
     **Response:** `200 OK` with role details

Response body:

```json
{
  "userRoles": [
    { "id": "...", "username": "...", "description": "..." },
    { "id": "...", "username": "...", "description": "..." }
  ]
}
```
