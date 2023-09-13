class RoomManager {
private:
    std::vector<Room> rooms_list;
    Room room_empty;
public:
    RoomManager() = default;

    void createRoom(std::string room_name) {
        Room room(room_name);
        rooms_list.push_back(room);
    }
    void removeRoom(std::string room_name) {
        for (int i = 0; i < rooms_list.size(); i++) {
            if (rooms_list[i].getName() == room_name) {
                rooms_list.erase(rooms_list.begin() + i);
                break;
            }
        }
    }
    Room& getRoom(std::string room_name) {
        for (auto& room: rooms_list) {
            if (room.getName() == room_name) {
                return room;
            }
        }
        return room_empty;
    }
    std::vector<Room> getRooms() {
        return rooms_list;
    }
};
