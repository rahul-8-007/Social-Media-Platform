#ifndef SOCIAL_MEDIA_PLATFORM_H
#define SOCIAL_MEDIA_PLATFORM_H

#include "Post.h"
#include "User.h"
#include <string>
#include <vector>

class SocialMediaPlatform {
public:
    SocialMediaPlatform();
    void run();

private:
    std::vector<User> users_;
    std::vector<Post> posts_;
    int nextPostId_ = 1;
    std::string currentUsername_;

    void loadData();
    void saveUsers() const;
    void savePosts() const;
    bool registerUser();
    bool loginUser();
    void logoutUser();
    void showMainMenu();
    void createPost();
    void viewFeed() const;
    void likePost();
    void commentOnPost();
    void viewMyPosts() const;
    User* findUser(const std::string& username);
    const User* findUser(const std::string& username) const;
    Post* findPost(int id);
    static std::string readLine(const std::string& prompt);
    static int readInt(const std::string& prompt);
    static bool isValidUsername(const std::string& username);
};

#endif
