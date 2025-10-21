# User

- register
- log in
- log out
- reset password
- change email/username

# User interactions

- create board
- get list of boards
- view board
- rename board
- change board statuses
- create task
- get list of tasks
- view task
- update task
- change task status
- convert task into a project
- create project
- view project
- update project

# Board interactions

Create a board

1. API Gateway receives request `POST /boards`
2. Gateway validates JWT → extracts userId and role
3. Forward request (with X-User-Id header) to Board Service
4. Board Service:
   - Creates board entity (name, creatorId = userId)
   - Creates default statuses
   - Adds any provided custom statuses
   - Sets order and relationships
   - Emits BoardCreated event to Activity service
5. Return 201 Created with board details

Get board list

1. API Gateway receives request `GET /boards`
2. Gateway validates JWT → extracts userId and role
3. Forward request (with X-User-Id header) to Board Service
4. Board Service:
   - Fetches board data related to the current user
   - Returns board details
5. Return 200 Success with board details

View a board

1. API Gateway receives request `GET /boards/{id}`
2. Gateway validates JWT → extracts userId and role
3. Forward request (with X-User-Id header) to Board Service
4. Board Service:
   - Fetches board data
   - Checks if user is allowed to access the data
   - Fetches task and project data related to the current board
   - Returns board details
   - Emits BoardViewed event to Activity service
5. Return 200 Success with board details

Rename board

1. API Gateway receives request `PATCH /boards/{id}`
2. Gateway validates JWT → extracts userId and role
3. Forward request (with X-User-Id header) to Board Service
4. Board Service:
   - Fetches board data
   - Checks if user is allowed to access the data
   - Sets new board name
   - Emits BoardUpdated event to Activity service
5. Return 204 Success No content

Change board statuses

1. API Gateway receives request `POST /boards/{id}/statuses`
2. Gateway validates JWT → extracts userId and role
3. Forward request (with X-User-Id header) to Board Service
4. Board Service:
   - Fetches statuses data from specified board
   - Checks if user is allowed to access the data
   - Applies changes to status data (name, order)
   - Emits BoardUpdated event to Activity service
5. Return 204 Success No content

Delete board

1. API Gateway receives request `DELETE /boards/{id}`
2. Gateway validates JWT → extracts userId and role
3. Forward request (with X-User-Id header) to Board Service
4. Board Service:
   - Fetches statuses data from specified board
   - Checks if user is allowed to access the data
   - Soft deletes the board data
   - Emits BoardDeleted event to Activity service
5. Return 204 Success No content

Create task

1. API Gateway receives request `POST /boards/{id}/tasks`
2. Gateway validates JWT → extracts userId and role
3. Forward request (with X-User-Id header) to Board Service
4. Board Service:
   - Creates task entity
   - Sets default status
   - Emits TaskCreated event to Activity service
5. Return 201 Created and task details

View Task

1. API Gateway receives request `GET /tasks/{id}/`
2. Gateway validates JWT → extracts userId and role
3. Forward request (with X-User-Id header) to Board Service
4. Board Service:
   - Fetches task data
   - Checks if user is allowed to access the task
   - Emits TaskViewed event to Activity service
5. Return 200 Success and task details

Update task

1. API Gateway receives request `PATCH /tasks/{id}/`
2. Gateway validates JWT → extracts userId and role
3. Forward request (with X-User-Id header) to Board Service
4. Board Service:
   - Fetches task data
   - Checks if user is allowed to access the task
   - Applies changes to the task
   - Emits TaskViewed event to Activity service
5. Return 204 Success No content

Delete task

1. API Gateway receives request `DELETE /tasks/{id}/`
2. Gateway validates JWT → extracts userId and role
3. Forward request (with X-User-Id header) to Board Service
4. Board Service:
   - Fetches task data
   - Checks if user is allowed to access the task
   - Applies changes to the task
   - Emits TaskViewed event to Activity service
5. Return 204 Success No content

