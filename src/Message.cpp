#include "Message.h"

bool Message::operator==(const Message& other) const {
    return (this->command == other.command && this->msg == other.msg && this->sender == other.sender);
}