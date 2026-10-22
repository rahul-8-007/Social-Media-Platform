#include "Post.h"
#include <algorithm>
#include <utility>

Post::Post(int id, std::string author, std::string content)
    : id_(id), author_(std::move(author)), content_(std::move(content)) {}

int Post::getId() const { return id_; }
const std::string& Post::getAuthor() const { return author_; }
const std::string& Post::getContent() const { return content_; }
const std::vector<std::string>& Post::getLikes() const { return likes_; }
const std::vector<std::pair<std::string, std::string>>& Post::getComments() const { return comments_; }

bool Post::toggleLike(const std::string& username) {
    const auto it = std::find(likes_.begin(), likes_.end(), username);
    if (it != likes_.end()) {
        likes_.erase(it);
        return false;
    }
    likes_.push_back(username);
    return true;
}

void Post::addComment(const std::string& username, const std::string& comment) {
    comments_.emplace_back(username, comment);
}
