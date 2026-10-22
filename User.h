#ifndef USER_H
#define USER_H

#include <string>

class User {
public:
    User() = default;
    User(std::string username, std::string password, std::string displayName);

    const std::string& getUsername() const;
    const std::string& getPassword() const;
    const std::string& getDisplayName() const;

private:
    std::string username_;
    std::string password_;
    std::string displayName_;
};

#endif
