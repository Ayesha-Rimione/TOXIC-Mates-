#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <queue>
#include <string>
#include <algorithm>
#include <chrono>

using namespace std;

// User Management
class User {
public:
    string username;
    string details;

    User(string uname, string det) : username(uname), details(det) {}
};

class UserManager {
private:
    unordered_map<string, User*> users;

public:
    ~UserManager() {
        for (auto& pair : users) {
            delete pair.second;
        }
    }

    void addUser(const string& username, const string& details) {
        users[username] = new User(username, details);
    }

    void removeUser(const string& username) {
        auto it = users.find(username);
        if (it != users.end()) {
            delete it->second;
            users.erase(it);
        }
    }

    void updateUser(const string& username, const string& newDetails) {
        if (users.find(username) != users.end()) {
            users[username]->details = newDetails;
        }
    }

    void displayUsers() const {
        for (const auto& user : users) {
            cout << "Username: " << user.second->username << "\tDetails: " << user.second->details << endl;
        }
    }
};

// Interest Management
class InterestRecommendation;  // Forward declaration

class InterestManager {
private:
    unordered_map<string, unordered_set<string>> userInterests;
    InterestRecommendation* interestRecommendation;

public:
    InterestManager(InterestRecommendation* ir) : interestRecommendation(ir) {}

    void addInterest(const string& username, const string& interest);
    void removeInterest(const string& username, const string& interest);
    void listInterests(const string& username) const;
};

// Connections (Friends) Management
class ConnectionsManager {
private:
    unordered_map<string, unordered_set<string>> adjacencyList;

public:
    void addConnection(const string& user1, const string& user2) {
        adjacencyList[user1].insert(user2);
        adjacencyList[user2].insert(user1);
    }

    void removeConnection(const string& user1, const string& user2) {
        adjacencyList[user1].erase(user2);
        adjacencyList[user2].erase(user1);
    }

    void listConnections(const string& username) const {
        if (adjacencyList.find(username) != adjacencyList.end()) {
            for (const auto& friendName : adjacencyList.at(username)) {
                cout << friendName << "\t";
            }
            cout << endl;
        }
    }
};

// Activity Feed
class Activity {
public:
    string user;
    string activity;

    Activity(const string& u, const string& a) : user(u), activity(a) {}
};

class ActivityFeed {
private:
    queue<Activity> feed;
    static const int MAX_FEED_SIZE = 1000; // Prevent unbounded growth

public:
    void postActivity(const string& user, const string& activity) {
        if (feed.size() >= MAX_FEED_SIZE) {
            feed.pop();
        }
        feed.push(Activity(user, activity));
    }

    void retrieveActivities() {
        queue<Activity> tempFeed = feed;
        while (!tempFeed.empty()) {
            Activity activity = tempFeed.front();
            tempFeed.pop();
            cout << activity.user << ": " << activity.activity << endl;
        }
    }
};

// Interest-based Recommendations
class InterestRecommendation {
private:
    unordered_map<string, unordered_set<string>> userInterests;

public:
    void addInterest(const string& username, const string& interest) {
        userInterests[username].insert(interest);
    }

    vector<string> findUsersWithSimilarInterests(const string& username) const {
        vector<string> similarUsers;
        if (userInterests.find(username) == userInterests.end()) {
            return similarUsers;
        }
        const auto& interests = userInterests.at(username);

        for (const auto& user : userInterests) {
            if (user.first != username) {
                for (const auto& interest : user.second) {
                    if (interests.find(interest) != interests.end()) {
                        similarUsers.push_back(user.first);
                        break;
                    }
                }
            }
        }
        return similarUsers;
    }
};

void InterestManager::addInterest(const string& username, const string& interest) {
    userInterests[username].insert(interest);
    interestRecommendation->addInterest(username, interest);
}

void InterestManager::removeInterest(const string& username, const string& interest) {
    userInterests[username].erase(interest);
}

void InterestManager::listInterests(const string& username) const {
    if (userInterests.find(username) != userInterests.end()) {
        for (const auto& interest : userInterests.at(username)) {
            cout << interest << ", ";
        }
        cout << endl;
    }
}

// Messaging System
class Message {
public:
    string sender;
    string receiver;
    string content;

    Message(const string& s, const string& r, const string& c) : sender(s), receiver(r), content(c) {}
};

class MessagingSystem {
private:
    unordered_map<string, queue<Message>> messages;

public:
    void sendMessage(const string& sender, const string& receiver, const string& content) {
        messages[receiver].push(Message(sender, receiver, content));
    }

    void receiveMessage(const string& username) {
        while (!messages[username].empty()) {
            Message message = messages[username].front();
            messages[username].pop();
            cout << message.sender << " to " << message.receiver << ": " << message.content << endl;
        }
    }
};

// Performance Analysis
void benchmarkUserManagement(UserManager& userManager) {
    auto start = chrono::high_resolution_clock::now();
    for (int i = 0; i < 1000; ++i) {
        userManager.addUser("user" + to_string(i), "details" + to_string(i));
    }
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> diff = end - start;
    cout << "Time to add 1000 users: " << diff.count() << " s\n";

    start = chrono::high_resolution_clock::now();
    userManager.updateUser("user500", "new details");
    end = chrono::high_resolution_clock::now();
    diff = end - start;
    cout << "Time to update a user: " << diff.count() << " s\n";

    start = chrono::high_resolution_clock::now();
    userManager.removeUser("user500");
    end = chrono::high_resolution_clock::now();
    diff = end - start;
    cout << "Time to remove a user: " << diff.count() << " s\n";
}

// Main Function
int main() {
    InterestRecommendation interestRecommendation;
    UserManager userManager;
    InterestManager interestManager(&interestRecommendation);
    ConnectionsManager connectionsManager;
    ActivityFeed activityFeed;
    MessagingSystem messagingSystem;
    cout<<"Welcokme to TOXIC UNO Mates";

    int choice;
    string username, details, interest, user1, user2, activity, content;
    cout << "\t\tTOXIC UNO Mates\n\t_______________________________\n\t_______________________________\n\n"
         << "1. Add User         \t"
         << "2. Remove User      \n"
         << "3. Update User      \t"
         << "4. Display Users    \n"
         << "5. Add Interest     \t"
         << "6. Remove Interest  \n"
         << "7. List Interests   \t"
         << "8. Add Connection   \n"
         << "9. Remove Connection\t"
         << "10. List Connections\n"
         << "11. Post Activity   \t"
         << "12. Retrieve Activities\n"
         << "13. Send Message    \t"
         << "14. Receive Messages\n"
         << "15. Find Users with Similar Interests\n"
         << "16. Benchmark User Management\t    "
         << "17. Exit\n\n";

    while (true) {
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "Enter username to sign up in Toxic Mates: ";
            cin >> username;
            cout << "Enter Bio: ";
            cin.ignore();
            getline(cin, details);
            userManager.addUser(username, details);
            cout << "Congratulations! " << username << " is a member of TOXIC Mates.\n\n";
            break;
        case 2:
            cout << "Enter username to remove: ";
            cin >> username;
            userManager.removeUser(username);
            cout << username << " is no longer a member of TOXIC Mates.\n\n";
            break;
        case 3:
            cout << "Enter username to update: ";
            cin >> username;
            cout << "Enter new details: ";
            cin.ignore();
            getline(cin, details);
            userManager.updateUser(username, details);
            cout << "Congratulations! User info is updated!\n\n";
            break;
        case 4:
            cout << "Here's the list of the members of TOXIC Mates:\n";
            userManager.displayUsers();
            cout << "\n\n";
            break;
        case 5:
            cout << "Enter username who wants to add interests: ";
            cin >> username;
            cout << "Enter interest: ";
            cin >> interest;
            interestManager.addInterest(username, interest);
            cout << username << " has successfully added his/her interests.\n\n";
            break;
        case 6:
            cout << "Enter username who wants to remove interests: ";
            cin >> username;
            cout << "Enter interest to remove: ";
            cin >> interest;
            interestManager.removeInterest(username, interest);
            cout << username << " has successfully removed his/her interest.\n\n";
            break;
        case 7:
            cout << "Enter username: ";
            cin >> username;
            cout << username << " has interest in these fields below:\n";
            interestManager.listInterests(username);
            cout << endl << endl;
            break;
        case 8:
            cout << "Enter username of who wants to add: ";
            cin >> user1;
            cout << "Enter username of whom " << user1 << " wants to add: ";
            cin >> user2;
            connectionsManager.addConnection(user1, user2);
            cout << user1 << " and " << user2 << " are friends now! :)\n";
            break;
        case 9:
            cout << "Enter username of who wants to remove: ";
            cin >> user1;
            cout << "Enter username of whom " << user1 << " wants to remove: ";
            cin >> user2;
            connectionsManager.removeConnection(user1, user2);
            cout << user1 << " and " << user2 << " are no longer friends now! :(\n";
            break;
        case 10:
            cout << "Enter username to see his/her friend list: ";
            cin >> username;
            cout << username << " has ";
            connectionsManager.listConnections(username);
            cout << " as friends.\n";
            break;
        case 11:
            cout << "Enter username who wants to post: ";
            cin >> username;
            cout << "Enter content to post: ";
            cin.ignore();
            getline(cin, activity);
            activityFeed.postActivity(username, activity);
            cout << username << " has successfully posted in a while.\n";
            break;
        case 12:
            activityFeed.retrieveActivities();
            break;
        case 13:
            cout << "Enter sender: ";
            cin >> user1;
            cout << "Enter receiver: ";
            cin >> user2;
            cout << "Enter message: ";
            cin.ignore();
            getline(cin, content);
            messagingSystem.sendMessage(user1, user2, content);
            cout << "Message Sent Successfully!\n";
            break;
        case 14:
            cout << "Enter username to receive messages: ";
            cin >> username;
            messagingSystem.receiveMessage(username);
            break;
        case 15:
            cout << "Enter username to find similar interests: ";
            cin >> username;
            {
                auto similarUsers = interestRecommendation.findUsersWithSimilarInterests(username);
                if (similarUsers.empty()) {
                    cout << "No similarities found.\n\n";
                } else {
                    for (const auto& user : similarUsers) {
                        cout << user << endl;
                    }
                    cout << "\n\n";
                }
            }
            break;
        case 16:
            benchmarkUserManagement(userManager);
            break;
        case 17:
            cout << "Thank you for browsing and spending your time in TOXIC Mates! See you!\n";
            return 0;
        default:
            cout << "Invalid choice. Please try again.\n";
        }
    }

    return 0;
}
