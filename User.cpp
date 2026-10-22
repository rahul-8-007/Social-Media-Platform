#include "User.h"
#include <utility>

User::User(std::string username, std::string password, std::string displayName)
    : username_(std::move(username)), password_(std::move(password)),
      displayName_(std::move(displayName)) {}

const std::string& User::getUsername() const { return username_; }
const std::string& User::getPassword() const { return password_; }
const std::string& User::getDisplayName() const { return displayName_; }
