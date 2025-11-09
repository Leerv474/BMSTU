# **Auth Service**

#### **Register New User**

**Request:** `POST /auth/register`

**Flow:**

1. API Gateway forwards request (no JWT validation, public endpoint)
2. Auth Service:

   - Validates input (email, username, password)
   - Creates authentication record (hashed password, userId)
   - Calls **User Service (internal)** → `POST /internal/users` to create user profile
   - Returns tokens (access + refresh) to the client

**Response:** `201 Created` with Cookies and Auth Header

Response body:

```json
{
  "id": "...",
  "username": "...",
  "email": "..."
}
```

**Emits** UserRegistered
Payload:

```json
{
  "event": "...",
  "source": "...",
  "timestamp": "...",
  "data": {}
}
```

---

#### **Login**

**Request:** `POST /auth/login`

**Flow:**

1. Gateway forwards request to Auth Service
2. Auth Service:

   - Validates credentials
   - Generates access and refresh tokens
   - Stores refresh token in database/Redis
   - Returns tokens and basic user info

**Response:** `200 OK` with Cookies and Auth Header

Response body:

```json
{
  "id": "...",
  "username": "...",
  "role": "..."
}
```

---

#### **Refresh Token**

**Request:** `POST /auth/refresh`

**Flow:**

1. Gateway forwards request (no JWT required)
2. Auth Service:

   - Validates refresh token
   - Issues new access and refresh tokens
   - Invalidates old refresh token (if rotation enabled)
   - Returns new tokens

**Response:** `200 OK` with Cookies and Auth Header

---

#### **Logout**

**Request:** `POST /auth/logout`

**Flow:**

1. Gateway validates JWT → extracts `userId`
2. Forwards request to Auth Service
3. Auth Service:

   - Revokes refresh token(s) for this user/session
   - Optionally blacklists access token
   - Returns confirmation

**Response:** `204 No Content`

---

#### **Request Password Reset**

**Request:** `POST /auth/password/reset-request`

**Flow:**

1. Gateway forwards request (public endpoint)
2. Auth Service:

   - Validates email
   - Generates reset token
   - Sends reset link via **Notification Service**
   - Returns success

**Response:** `200 OK`

Response body:

```json
{
  "message": "Password reset link sent to your email"
}
```

---

#### **Reset Password**

**Request:** `POST /auth/password/reset`

**Flow:**

1. Gateway forwards request (public endpoint)
2. Auth Service:

   - Validates reset token
   - Updates user’s password (hashed)
   - Invalidates all existing tokens
   - Returns confirmation

**Response:** `204 No Content`

---

#### **Get Current User**

**Request:** `GET /auth/me`

**Flow:**

1. Gateway validates JWT → extracts `userId`
2. Forwards request to Auth Service
3. Auth Service:

   - Retrieves user authentication data (from DB or User Service cache)
   - Returns it to the client

**Response:** `200 OK`

Response body:

```json
{
  "id": "...",
  "username": "...",
  "email": "..."
}
```

---

#### **Validate JWT (Internal)**

**Request:** `GET /internal/auth/validate`

**Flow:**

1. Gateway sends token in Authorization header
2. Auth Service:

   - Validates token signature and expiry
   - Returns `userId`, `role`, and token status

**Response:** `200 OK` with Cookies and Auth Header

Response body:

```json
{
  "userId": "...",
  "role": "USER"
}
```

---

#### **Validate Service Token (Internal)**

**Request:** `GET /internal/auth/service-token/validate`

**Flow:**

1. Internal service (e.g. Gateway, Notification) sends `X-Service-Token`
2. Auth Service:

   - Checks token against internal registry
   - Returns validity and service name

**Response:** `200 OK`

Response body:

```json
{
  "valid": true,
  "service": "gateway"
}
```

---

#### **Issue Service Token (Internal)**

**Request:** `GET /internal/auth/service-token/{tokenId}/issue`

**Flow:**

1. Called manually or by admin service to generate token for another service
2. Auth Service:

   - Creates token with predefined permissions and expiration
   - Returns token

**Response:** `201 Created`

Response body:

```json
{
  "service": "notification-service",
  "token": "..."
}
```

---

#### **Revoke Service Token (Internal)**

**Request:** `DELETE /internal/auth/service-token/{tokenId}/revoke`

**Flow:**

1. Called by admin or automation when service credentials need rotation
2. Auth Service:

   - Marks token as revoked
   - Returns confirmation

**Response:** `204 No Content`

---

#### **Sync User Data (Internal)**

**Request:** `GET /internal/auth/users/{id}/sync`

**Flow:**

1. User Service sends request after user data change (e.g., email updated)
2. Auth Service:

   - Updates auth record (e.g., email or username)
   - Returns confirmation

**Response:** `204 No Content`
