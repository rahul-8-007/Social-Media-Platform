#ifndef POST_H
#define POST_H

#include <string>
#include <utility>
#include <vector>

class Post {
public:
    Post() = default;
    Post(int id, std::string author, std::string content);

    int getId() const;
    const std::string& getAuthor() const;
    const std::string& getContent() const;
    const std::vector<std::string>& getLikes() const;
    const std::vector<std::pair<std::string, std::string>>& getComments() const;

    bool toggleLike(const std::string& username);
    void addComment(const std::string& username, const std::string& comment);

private:
    int id_ = 0;
    std::string author_;
    std::string content_;
    std::vector<std::string> likes_;
    std::vector<std::pair<std::string, std::string>> comments_;

    friend class SocialMediaPlatform;
};

#endif
