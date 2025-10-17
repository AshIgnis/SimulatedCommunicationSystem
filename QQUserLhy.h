#ifndef QQ_USER_LHY_H
#define QQ_USER_LHY_H

#include "BaseUserLhy.h"

// QQ�û����֧ࣨ����΢�Ű󶨣�
class QQUserLhy : public BaseUserLhy {
private:
    std::string bindWeChatId;  // �󶨵�΢��ID������Ϊ�գ�

public:
    // ���캯��
    QQUserLhy(std::string id, std::string nickname, std::string birthDate,
        int tAge, std::string location, std::string bindWeChatId = "")
        : BaseUserLhy(id, nickname, birthDate, tAge, location), bindWeChatId(bindWeChatId) {
    }

    ~QQUserLhy() override = default;

    // ��΢�Žӿ�
    void setBindWeChatId(std::string weChatId) { bindWeChatId = weChatId; }
    std::string getBindWeChatId() const { return bindWeChatId; }

    // ʵ�ֺ��ѹ���ӿ�
    bool addFriend(std::string friendId) override {
        if (isFriend(friendId)) return false;  // ��Ϊ����
        friendIds.push_back(friendId);
        return true;
    }

    bool deleteFriend(std::string friendId) override {
        for (auto it = friendIds.begin(); it != friendIds.end(); ++it) {
            if (*it == friendId) {
                friendIds.erase(it);
                return true;
            }
        }
        return false;  // ���Ǻ���
    }

    bool isFriend(std::string friendId) const override {
        for (const auto& id : friendIds) {
            if (id == friendId) return true;
        }
        return false;
    }
};

#endif // QQ_USER_LHY_H