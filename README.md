# Social Media Platform (C++)

A menu-driven mini social media application built in C++ to demonstrate object-oriented programming, modular design, STL containers, and file-based persistence.

## Features

- Register an account and log in
- Validate unique usernames
- Create and view posts in a community feed
- Like and unlike posts
- Comment on posts
- View posts created by the logged-in user
- Save users, posts, likes, and comments to local text files so data remains after restarting
- Input validation for menu choices, usernames, post length, and comment length

## Tech stack

- C++17
- Object-oriented programming (classes, encapsulation, separation of concerns)
- Standard Template Library (`vector`, `string`, algorithms)
- File handling (`ifstream`, `ofstream`)

## Project structure

```text
Social-Media-Platform/
├── main.cpp
├── User.h
├── User.cpp
├── Post.h
├── Post.cpp
├── SocialMediaPlatform.h
├── SocialMediaPlatform.cpp
├── README.md
├── .gitignore
├── users.txt       # created automatically when accounts are saved
└── posts.txt       # created automatically when posts are saved
```

## Requirements

Install a C++ compiler with C++17 support, such as GCC/G++ (MinGW on Windows) or Clang.

## Compile and run

### Linux / macOS / WSL

From the project directory:

```bash
g++ -std=c++17 -Wall -Wextra -pedantic main.cpp User.cpp Post.cpp SocialMediaPlatform.cpp -o social_media
./social_media
```

### Windows (MinGW-w64)

From Command Prompt or PowerShell in the project directory:

```powershell
g++ -std=c++17 -Wall -Wextra -pedantic main.cpp User.cpp Post.cpp SocialMediaPlatform.cpp -o social_media.exe
.\social_media.exe
```

The program reads and writes `users.txt` and `posts.txt` in its current working directory. Keep these files beside the executable when you want to reuse your saved data.

## How to use

1. Choose **Register** and create a username, display name, and password.
2. Log in using the account you created.
3. Create posts, view the community feed, like/unlike posts, or add comments.
4. Choose **View my posts** to see your own posts.
5. Log out or exit. Data is saved to local text files.

## Concepts demonstrated

- **Encapsulation:** user and post data are managed through classes.
- **Modularity:** user, post, and application logic are split across separate files.
- **STL:** vectors and algorithms manage users, posts, likes, and comments.
- **Persistence:** streams serialize application data to local files.
- **Input validation:** menu choices and text input are checked before use.

## Limitations and security note

This is an educational console project, not a production authentication system. Passwords are stored as plain text in `users.txt`; do not use real or reused passwords. A production version should hash passwords with a suitable password-hashing algorithm, validate and protect stored data, and use a database with access controls.

## Possible future improvements

- Password hashing and account recovery
- Delete or edit posts and comments
- User profiles and following/follower relationships
- Search and pagination for posts
- SQLite database support
- Automated unit tests and a graphical/web interface

## License

You may use and modify this project for learning and portfolio purposes. Add a license file if you intend to distribute it under specific terms.
