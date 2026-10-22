#include "SocialMediaPlatform.h"

#include <algorithm>
#include <cctype>
#include <cstdlib>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <limits>

SocialMediaPlatform::SocialMediaPlatform() { loadData(); }

std::string SocialMediaPlatform::readLine(const std::string& prompt) {
    std::cout << prompt;
    std::string value;
    std::getline(std::cin, value);
    return value;
}

int SocialMediaPlatform::readInt(const std::string& prompt) {
    while (true) {
        const std::string input = readLine(prompt);
        try {
            std::size_t used = 0;
            const int value = std::stoi(input, &used);
            if (used == input.size()) return value;
        } catch (...) {
            // Re-prompt below for invalid input.
        }
        std::cout << "Please enter a valid number.\n";
    }
}

bool SocialMediaPlatform::isValidUsername(const std::string& username) {
    if (username.size() < 3 || username.size() > 20) return false;
    return std::all_of(username.begin(), username.end(), [](unsigned char ch) {
        return std::isalnum(ch) || ch == '_' || ch == '-';
    });
}

User* SocialMediaPlatform::findUser(const std::string& username) {
    for (auto& user : users_) if (user.getUsername() == username) return &user;
    return nullptr;
}

const User* SocialMediaPlatform::findUser(const std::string& username) const {
    for (const auto& user : users_) if (user.getUsername() == username) return &user;
    return nullptr;
}

Post* SocialMediaPlatform::findPost(int id) {
    for (auto& post : posts_) if (post.getId() == id) return &post;
    return nullptr;
}

void SocialMediaPlatform::loadData() {
    {
        std::ifstream in("users.txt");
        std::string username, password, displayName;
        while (in >> std::quoted(username) >> std::quoted(password) >> std::quoted(displayName))
            users_.emplace_back(username, password, displayName);
    }
    {
        std::ifstream in("posts.txt");
        while (in) {
            int id = 0;
            std::string author, content;
            std::size_t likeCount = 0, commentCount = 0;
            if (!(in >> id >> std::quoted(author) >> std::quoted(content) >> likeCount)) break;
            Post post(id, author, content);
            bool valid = true;
            for (std::size_t i = 0; i < likeCount; ++i) {
                std::string liker;
                if (!(in >> std::quoted(liker))) { valid = false; break; }
                post.likes_.push_back(liker);
            }
            if (!valid || !(in >> commentCount)) break;
            for (std::size_t i = 0; i < commentCount; ++i) {
                std::string commenter, comment;
                if (!(in >> std::quoted(commenter) >> std::quoted(comment))) { valid = false; break; }
                post.comments_.emplace_back(commenter, comment);
            }
            if (!valid) break;
            posts_.push_back(std::move(post));
            nextPostId_ = std::max(nextPostId_, id + 1);
        }
    }
}

void SocialMediaPlatform::saveUsers() const {
    std::ofstream out("users.txt", std::ios::trunc);
    if (!out) { std::cerr << "Warning: could not save users.txt\n"; return; }
    for (const auto& user : users_)
        out << std::quoted(user.getUsername()) << ' ' << std::quoted(user.getPassword())
            << ' ' << std::quoted(user.getDisplayName()) << '\n';
}

void SocialMediaPlatform::savePosts() const {
    std::ofstream out("posts.txt", std::ios::trunc);
    if (!out) { std::cerr << "Warning: could not save posts.txt\n"; return; }
    for (const auto& post : posts_) {
        out << post.id_ << ' ' << std::quoted(post.author_) << ' ' << std::quoted(post.content_)
            << ' ' << post.likes_.size();
        for (const auto& liker : post.likes_) out << ' ' << std::quoted(liker);
        out << ' ' << post.comments_.size();
        for (const auto& comment : post.comments_)
            out << ' ' << std::quoted(comment.first) << ' ' << std::quoted(comment.second);
        out << '\n';
    }
}

bool SocialMediaPlatform::registerUser() {
    std::cout << "\n--- Create an account ---\n";
    const std::string username = readLine("Username (3-20 letters, numbers, _ or -): ");
    if (!isValidUsername(username)) {
        std::cout << "Invalid username format.\n";
        return false;
    }
    if (findUser(username)) {
        std::cout << "That username is already taken.\n";
        return false;
    }
    const std::string displayName = readLine("Display name: ");
    const std::string password = readLine("Password: ");
    if (displayName.empty() || password.size() < 4) {
        std::cout << "Display name cannot be empty; password must be at least 4 characters.\n";
        return false;
    }
    users_.emplace_back(username, password, displayName);
    saveUsers();
    std::cout << "Account created. You can now log in.\n";
    return true;
}

bool SocialMediaPlatform::loginUser() {
    std::cout << "\n--- Log in ---\n";
    const std::string username = readLine("Username: ");
    const std::string password = readLine("Password: ");
    const User* user = findUser(username);
    if (!user || user->getPassword() != password) {
        std::cout << "Incorrect username or password.\n";
        return false;
    }
    currentUsername_ = username;
    std::cout << "Welcome, " << user->getDisplayName() << "!\n";
    return true;
}

void SocialMediaPlatform::logoutUser() {
    currentUsername_.clear();
    std::cout << "You have been logged out.\n";
}

void SocialMediaPlatform::createPost() {
    std::cout << "\n--- Create a post ---\n";
    const std::string content = readLine("What's on your mind? ");
    if (content.empty()) { std::cout << "Post cannot be empty.\n"; return; }
    if (content.size() > 1000) { std::cout << "Posts must be 1000 characters or fewer.\n"; return; }
    posts_.emplace_back(nextPostId_++, currentUsername_, content);
    savePosts();
    std::cout << "Post published.\n";
}

void SocialMediaPlatform::viewFeed() const {
    std::cout << "\n========== COMMUNITY FEED ==========\n";
    if (posts_.empty()) { std::cout << "No posts yet. Be the first to post!\n"; return; }
    for (auto it = posts_.rbegin(); it != posts_.rend(); ++it) {
        const User* author = findUser(it->getAuthor());
        std::cout << "\nPost #" << it->getId() << " | @" << it->getAuthor();
        if (author) std::cout << " (" << author->getDisplayName() << ")";
        std::cout << "\n" << it->getContent() << "\nLikes: " << it->getLikes().size();
        if (std::find(it->getLikes().begin(), it->getLikes().end(), currentUsername_) != it->getLikes().end())
            std::cout << " | You liked this";
        std::cout << "\nComments (" << it->getComments().size() << "):\n";
        if (it->getComments().empty()) std::cout << "  No comments yet.\n";
        for (const auto& comment : it->getComments())
            std::cout << "  @" << comment.first << ": " << comment.second << '\n';
        std::cout << "------------------------------------\n";
    }
}

void SocialMediaPlatform::likePost() {
    viewFeed();
    if (posts_.empty()) return;
    const int id = readInt("Enter post ID to like/unlike (0 to cancel): ");
    if (id == 0) return;
    Post* post = findPost(id);
    if (!post) { std::cout << "Post not found.\n"; return; }
    const bool liked = post->toggleLike(currentUsername_);
    savePosts();
    std::cout << (liked ? "You liked this post.\n" : "You removed your like.\n");
}

void SocialMediaPlatform::commentOnPost() {
    viewFeed();
    if (posts_.empty()) return;
    const int id = readInt("Enter post ID to comment on (0 to cancel): ");
    if (id == 0) return;
    Post* post = findPost(id);
    if (!post) { std::cout << "Post not found.\n"; return; }
    const std::string comment = readLine("Your comment: ");
    if (comment.empty()) { std::cout << "Comment cannot be empty.\n"; return; }
    if (comment.size() > 500) { std::cout << "Comments must be 500 characters or fewer.\n"; return; }
    post->addComment(currentUsername_, comment);
    savePosts();
    std::cout << "Comment added.\n";
}

void SocialMediaPlatform::viewMyPosts() const {
    std::cout << "\n--- Your posts ---\n";
    bool found = false;
    for (auto it = posts_.rbegin(); it != posts_.rend(); ++it) {
        if (it->getAuthor() != currentUsername_) continue;
        found = true;
        std::cout << "Post #" << it->getId() << ": " << it->getContent()
                  << "\nLikes: " << it->getLikes().size()
                  << " | Comments: " << it->getComments().size() << "\n\n";
    }
    if (!found) std::cout << "You haven't posted anything yet.\n";
}

void SocialMediaPlatform::showMainMenu() {
    while (!currentUsername_.empty()) {
        std::cout << "\n========== SOCIAL MEDIA PLATFORM ==========\n"
                  << "Logged in as @" << currentUsername_ << "\n"
                  << "1. Create a post\n2. View community feed\n3. Like / unlike a post\n"
                  << "4. Comment on a post\n5. View my posts\n6. Log out\n0. Exit\n";
        const int choice = readInt("Choose an option: ");
        switch (choice) {
            case 1: createPost(); break;
            case 2: viewFeed(); break;
            case 3: likePost(); break;
            case 4: commentOnPost(); break;
            case 5: viewMyPosts(); break;
            case 6: logoutUser(); break;
            case 0: saveUsers(); savePosts(); std::cout << "Goodbye!\n"; std::exit(0);
            default: std::cout << "Choose an option from the menu.\n";
        }
    }
}

void SocialMediaPlatform::run() {
    std::cout << "==========================================\n"
              << "       SOCIAL MEDIA PLATFORM (C++)        \n"
              << "==========================================\n";
    while (true) {
        std::cout << "\n1. Register\n2. Log in\n0. Exit\n";
        const int choice = readInt("Choose an option: ");
        switch (choice) {
            case 1: registerUser(); break;
            case 2: if (loginUser()) showMainMenu(); break;
            case 0: saveUsers(); savePosts(); std::cout << "Goodbye!\n"; return;
            default: std::cout << "Choose an option from the menu.\n";
        }
    }
}
