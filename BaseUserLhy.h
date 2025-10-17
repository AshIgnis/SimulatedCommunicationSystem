#ifndef BASE_USER_LHY_H
#define BASE_USER_LHY_H

#include <string>
#include <vector>

// ������ࣺ�����û��Ĺ�������
class BaseUserLhy {

protected:
    std::string id;
    std::string nickname;
    std::string password; // �洢����
    std::string birthDate;
    int tAge;
    std::string location;
    std::vector<std::string> friendIds;
    std::vector<std::string> groupIds;   // ȺID�б�


public:
    // ���캯��
    BaseUserLhy(const std::string& id, const std::string& nickname,
        const std::string& birthDate, int tAge, const std::string& location,
        const std::string& password = "123"); // Ĭ������

    // ��������������ȷ�����������������ã�
    virtual ~BaseUserLhy() = 0;

    // ͨ��Get�ӿ�
    std::string getId() const { return id; }
    std::string getNickname() const { return nickname; }
    std::string getBirthDate() const { return birthDate; }
    int getTAge() const { return tAge; }
    std::string getLocation() const { return location; }
    std::vector<std::string> getFriendIds() const { return friendIds; }
    std::vector<std::string> getGroupIds() const { return groupIds; }
    std::string getPassword() const { return password; }

    // ͨ��Set�ӿ�
    void setNickname(std::string newNickname) { nickname = newNickname; }
    void setLocation(std::string newLocation) { location = newLocation; }

    // ���ѹ�����ӿڣ�����ͳһʵ�֣�
    virtual bool addFriend(std::string friendId) = 0;
    virtual bool deleteFriend(std::string friendId) = 0;
    virtual bool isFriend(std::string friendId) const = 0;

    // Ⱥ����ͨ�ýӿ�
    void addGroupId(std::string groupId) { groupIds.push_back(groupId); }
    bool removeGroupId(std::string groupId) {
        for (auto it = groupIds.begin(); it != groupIds.end(); ++it) {
            if (*it == groupId) {
                groupIds.erase(it);
                return true;
            }
        }
        return false;
    }


    // ��������֤���뷽��
    bool verifyPassword(const std::string& inputPassword) const;

    // �������޸���Ϣ����
    bool changePassword(const std::string& oldPassword, const std::string& newPassword);
    void changeNickname(const std::string& newNickname);
    void changeLocation(const std::string& newLocation);
    void changeBirthDate(const std::string& newBirthDate);

};

// ������������������ʵ��
inline BaseUserLhy::~BaseUserLhy() = default;

#endif // BASE_USER_LHY_H