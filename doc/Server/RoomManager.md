# [RoomManager](https://github.com/DangeL187/DCSL/blob/main/include/Server/RoomManager.h)
## Manages Room objects and stores them in a rooms list

### Public Member Functions
| Return type | Function name | Description |
| ----------- | ------------- | ----------- |
| | `RoomManager()` | Default constructor. |
| void | `createRoom(std::string room_name)` | Create a new room with specified name. |
| void | `removeRoom(std::string room_name)` | Remove a room by name. |
| Room& | `getRoom(std::string room_name)` | Get a reference to the Room object by name. |
| std::vector<Room> | `getRooms()` | Get the vector of Room objects. |
