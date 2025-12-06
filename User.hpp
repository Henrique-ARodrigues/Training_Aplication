#ifndef USER_HPP
#define USER_HPP


#include <iostream>
#include <string>


class User {
    private:
        int id;
        std::string name;
        std::string email;

    public:
        User(int userId, const std::string& userName, const std::string& userEmail)
            : id(userId), name(userName), email(userEmail) {}

        // Getters
        
        int getId() const{
            return id;
        }
        std::string getName() const{
            return name;
        }
        std::string getEmail() const{
            return email;
        }

        // Setters

        void setName(std::string newName) {
            name = newName;
        }
        void setEmail(std::string newEmail) {
            email = newEmail;
        }

};

#endif
