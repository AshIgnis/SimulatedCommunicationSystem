#ifndef WECHAT_USER_LHY_H
#define WECHAT_USER_LHY_H

#include "BaseUserLhy.h"

// ΢���û����֧ࣨ����QQ�󶨣�
class WeChatUserLhy : public BaseUserLhy {
private:
    std::string bindQQId;  // �󶨵�QQID������Ϊ�գ�

public:
    // ���캯��
    WeChatUserLhy(std::string id, std::string nickname, std::string birthDate,
        int tAge, std::string location, std::string bindQQId = "")
        : BaseUserLhy(id, nickname, birthDate, tAge, location), bindQQId(bindQQId) {
    }

    ~WeChatUserLhy() override = default;

    // ��QQ�ӿ�
    void setBindQQId(std::string qqId) { bindQQId = qqId; }
    std::string getBindQQId() const { return bindQQId; }

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

#endif // WECHAT_USER_LHY_H