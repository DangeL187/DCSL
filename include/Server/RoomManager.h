#include <memory>
#include <string>
#include <vector>

class Room;

class RoomManager {
public:
    RoomManager();

    void createRoom(const std::string& room_name);
    Room* getRoom(const std::string& room_name);
    std::vector<Room> getRooms();
    void removeRoom(const std::string& room_name);

private:
    std::vector<Room>   rooms_list;
};
