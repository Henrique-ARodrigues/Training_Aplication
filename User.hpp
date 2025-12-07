#ifndef USER_HPP
#define USER_HPP


#include <iostream>
#include <string>


class User {
    private:
        int id;
        int age;
        int weight;
        int height;
        std::string name;
        std::string email;
        
    public:
        User(int userId, int userAge, int userWeight, int userHeight, const std::string& userName, const std::string& userEmail)
            : id(userId), age(userAge), weight(userWeight), height(userHeight), name(userName), email(userEmail) {}

        // Getters
        
        int getId() const{
            return id;
        }
        int getAge() const{
            return age;
        }
        int getWeight() const{
            return weight;
        }
        int getHeight() const{
            return height;
        }
        std::string getName() const{
            return name;
        }
        std::string getEmail() const{
            return email;
        }

        // Setters
        
        void setWeight(int newWeight) {
            weight = newWeight;
        }
        void setHeight(int newHeight) {
            height = newHeight;
        }
        void setName(std::string newName) {
            name = newName;
        }
        void setEmail(std::string newEmail) {
            email = newEmail;
        }

};

#endif
