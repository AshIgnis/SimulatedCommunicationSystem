#ifndef WECHAT_GROUP_LHY_H
#define WECHAT_GROUP_LHY_H

#include "BaseGroupLhy.h"
#include <vector>
#include <string>

// ΢��Ⱥ���ࣨ��ֹ��ʱ�����顢��Ⱥ���Ƽ���Ⱥ���޹���Ա��
class WeChatGroupLhy : public BaseGroupLhy {
private:
    std::string announcement;  // ΢��Ⱥ���棨���й��ܣ�
    const int maxMemberCount = 500;  // ΢��Ⱥ��Ա���ޣ�Ĭ��500�ˣ�

public:
    // ���캯��
    WeChatGroupLhy(std::string id, std::string name, BaseUserLhy* owner)
        : BaseGroupLhy(id, name, owner), announcement("���޹���") {
    }

    ~WeChatGroupLhy() override = default;

    // ʵ��Ⱥ����ӿڣ�΢��Ⱥ��Ⱥ�����Ƽ���Ⱥ
    bool addMember(BaseUserLhy* user) override {
        if (user == nullptr) return false;
        std::string userId = user->getId();

        // ����Ա����
        if (getMemberCount() >= maxMemberCount) {
            std::cout << "[΢��Ⱥ] ��Ա����������" << maxMemberCount << "�ˣ����޷�����³�Ա" << std::endl;
            return false;
        }

        if (isMember(userId)) {
            std::cout << "[΢��Ⱥ] " << user->getNickname() << "��" << userId << "������Ⱥ��" << std::endl;
            return false;
        }

        // ��Ⱥ������ӳ�Ա���Ƽ���Ⱥ��
        if (userId != owner->getId()) {
            std::cout << "[΢��Ⱥ] ��Ⱥ�����Ƽ���Ա��Ⱥ��" << user->getNickname() << "��Ⱥʧ��" << std::endl;
            return false;
        }

        members[userId] = user;
        user->addGroupId(id);
        std::cout << "[΢��Ⱥ] Ⱥ���Ƽ�" << user->getNickname() << "��" << userId << "����Ⱥ�ɹ�����ǰȺ��Ա����" << getMemberCount() << std::endl;
        return true;
    }

    // ʵ��Ⱥ����ӿڣ��Ƴ�Ⱥ��Ա����Ⱥ���ɲ�����
    bool deleteMember(std::string userId) override {
        if (!isMember(userId)) {
            std::cout << "[΢��Ⱥ] �û�" << userId << "����Ⱥ��" << std::endl;
            return false;
        }

        // ��Ⱥ�����Ƴ���Ա
        if (owner->getId() != userId) {
            std::cout << "[΢��Ⱥ] ��Ⱥ�����Ƴ���Ա" << std::endl;
            return false;
        }

        // �Ƴ���Ա
        BaseUserLhy* user = members[userId];
        members.erase(userId);
        user->removeGroupId(id);
        std::cout << "[΢��Ⱥ] " << user->getNickname() << "��" << userId << "���ѱ��Ƴ�����ǰȺ��Ա����" << getMemberCount() << std::endl;
        return true;
    }

    // ʵ��Ⱥ����ӿڣ����ҳ�Ա������C++14���õ�����������
    std::vector<BaseUserLhy*> searchMember(std::string keyword) override {
        std::vector<BaseUserLhy*> result;
        for (auto it = members.begin(); it != members.end(); ++it) {
            std::string userId = it->first;
            BaseUserLhy* user = it->second;
            if (userId.find(keyword) != std::string::npos || user->getNickname().find(keyword) != std::string::npos) {
                result.push_back(user);
            }
        }

        if (result.empty()) {
            std::cout << "[΢��Ⱥ] δ�ҵ������ؼ���\"" << keyword << "\"�ĳ�Ա" << std::endl;
        }
        else {
            std::cout << "[΢��Ⱥ] �ҵ�" << result.size() << "�������ؼ���\"" << keyword << "\"�ĳ�Ա��" << std::endl;
            for (auto user : result) {
                std::cout << "  - " << user->getNickname() << "��" << user->getId() << "��" << std::endl;
            }
        }
        return result;
    }

    // ʵ�ֲ��컯�ӿڣ�΢��Ⱥ��ֹ��ʱ������
    bool isTempGroupAllowed() const override {
        return false;
    }

    // ΢��Ⱥ���У��������
    void setAnnouncement(std::string content) {
        announcement = content;
        std::cout << "[΢��Ⱥ] Ⱥ�����Ѹ���Ϊ��" << content << std::endl;
    }

    std::string getAnnouncement() const {
        return announcement;
    }

    // ΢��Ⱥ���У���ȡ��Ա����
    int getMaxMemberCount() const {
        return maxMemberCount;
    }
};

#endif // WECHAT_GROUP_LHY_H