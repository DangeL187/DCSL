#include "Server/RoomManager.h"

#include "Server/Room.h"

RoomManager::RoomManager() = default;

void RoomManager::createRoom(const std::string& room_name) {
    Room room(room_name);
    rooms_list.push_back(room);
}

Room* RoomManager::getRoom(const std::string& room_name) {
    for (auto& room: rooms_list) {
        if (room.getName() == room_name) {
            return &room;
        }
    }
    return nullptr;
}

std::vector<Room> RoomManager::getRooms() {
    return rooms_list;
}

void RoomManager::removeRoom(const std::string& room_name) {
    for (int i = 0; i < rooms_list.size(); i++) {
        if (rooms_list[i].getName() == room_name) {
            rooms_list.erase(rooms_list.begin() + i);
            break;
        }
    }
}
