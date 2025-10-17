#ifndef WECHAT_SERVICE_LHY_H
#define WECHAT_SERVICE_LHY_H

#include "BaseServiceLhy.h"
#include "WeChatGroupLhy.h"
#include "WeChatUserLhy.h"
#include "QQUserLhy.h"
#include <vector>
#include <algorithm>
#include <iostream>

// ΢�ŷ������֧ࣨ��QQ�󶨡�΢��Ⱥ����
class WeChatServiceLhy : public BaseServiceLhy {
private:
    std::vector<WeChatGroupLhy*> joinedGroups;  // �û������΢��Ⱥ�б�
    std::string bindQQId;                       // �󶨵�QQID
    bool isBoundWithQQ;                         // �Ƿ��QQ

public:
    // ���캯�������û������ȡ��ʼ��״̬
    WeChatServiceLhy(BaseUserLhy* user) : BaseServiceLhy(user), isBoundWithQQ(false) {
        WeChatUserLhy* wxUser = dynamic_cast<WeChatUserLhy*>(user);
        if (wxUser != nullptr) {
            bindQQId = wxUser->getBindQQId();
            isBoundWithQQ = !bindQQId.empty();
            if (isBoundWithQQ) {
                std::cout << "[΢�ŷ���] �Ѱ�QQ��" << bindQQId << std::endl;
            }
        }
    }

    ~WeChatServiceLhy() override {
        // �ͷ�΢��Ⱥ�б�
        for (auto group : joinedGroups) {
            delete group;
        }
    }

    // ʵ�ַ������ͽӿ�
    std::string getServiceType() const override {
        return "΢�ŷ���";
    }

    // ʵ�ֵ�¼�ӿڣ�΢�ŵ�¼����֤��̶�Ϊ"6666"��
    bool login(std::string verifyInfo) override {
        if (getIsLoggedIn()) {
            std::cout << "[΢�ŷ���] " << user->getNickname() << "�ѵ�¼" << std::endl;
            return true;
        }
        if (verifyInfo != "6666") {
            std::cout << "[΢�ŷ���] ��¼ʧ�ܣ���֤�������ȷ��֤�룺6666��" << std::endl;
            return false;
        }
        setIsLoggedIn(true);
        std::cout << "[΢�ŷ���] " << user->getNickname() << "��" << user->getId() << "����¼�ɹ�" << std::endl;
        return true;
    }

    // ΢�ŷ������У�QQ�󶨹���
    bool bindWithQQ(std::string qqId) {
        if (isBoundWithQQ) {
            std::cout << "[΢�ŷ���] �Ѱ�QQ��" << bindQQId << "�������ظ���" << std::endl;
            return false;
        }
        bindQQId = qqId;
        isBoundWithQQ = true;
        // �����û�����İ���Ϣ
        WeChatUserLhy* wxUser = dynamic_cast<WeChatUserLhy*>(user);
        if (wxUser != nullptr) {
            wxUser->setBindQQId(qqId);
        }
        std::cout << "[΢�ŷ���] �ɹ���QQ��" << qqId << std::endl;
        return true;
    }

    bool unbindQQ() {
        if (!isBoundWithQQ) {
            std::cout << "[΢�ŷ���] δ��QQ��������" << std::endl;
            return false;
        }
        bindQQId.clear();
        isBoundWithQQ = false;
        WeChatUserLhy* wxUser = dynamic_cast<WeChatUserLhy*>(user);
        if (wxUser != nullptr) {
            wxUser->setBindQQId("");
        }
        std::cout << "[΢�ŷ���] �ɹ����QQ" << std::endl;
        return true;
    }

    // ΢�ŷ������У�����΢��Ⱥ����Ⱥ���Ƽ���
    bool joinGroup(WeChatGroupLhy* group) {
        if (!getIsLoggedIn()) {
            std::cout << "[΢�ŷ���] ���ȵ�¼�ټ���Ⱥ" << std::endl;
            return false;
        }
        // ΢��Ⱥ��Ⱥ��������ӣ��˴�����Ⱥ��ָ��
        if (group->addMember(group->getGroupOwner())) {
            joinedGroups.push_back(group);
            return true;
        }
        return false;
    }

    // ΢�ŷ������У��˳�΢��Ⱥ
    bool quitGroup(std::string groupId) {
        for (auto it = joinedGroups.begin(); it != joinedGroups.end(); ++it) {
            if ((*it)->getGroupId() == groupId) {
                (*it)->deleteMember(user->getId());
                joinedGroups.erase(it);
                return true;
            }
        }
        std::cout << "[΢�ŷ���] δ����Ⱥ��ID��" << groupId << "��" << std::endl;
        return false;
    }

    // ΢�ŷ������У��Ӱ�QQ��ȡ�Ƽ�����
    std::vector<std::string> getQQRecommendedFriends(std::vector<BaseUserLhy*> allUsers) {
        if (!isBoundWithQQ) {
            std::cout << "[΢�ŷ���] δ��QQ���޷���ȡ�Ƽ�����" << std::endl;
            return {};
        }
        // ���Ұ󶨵�QQ�û�����ȡ������б�
        std::vector<std::string> recommendedFriends;
        for (auto u : allUsers) {
            QQUserLhy* qqUser = dynamic_cast<QQUserLhy*>(u);
            if (qqUser != nullptr && qqUser->getId() == bindQQId) {
                recommendedFriends = qqUser->getFriendIds();
                break;
            }
        }
        // ����Ƽ����
        if (recommendedFriends.empty()) {
            std::cout << "[΢�ŷ���] �󶨵�QQ��" << bindQQId << "���޺��ѣ����Ƽ�" << std::endl;
        }
        else {
            std::cout << "[΢�ŷ���] �Ӱ�QQ��" << bindQQId << "����ȡ�Ƽ����ѣ�" << std::endl;
            for (const auto& friendId : recommendedFriends) {
                std::cout << "  - " << friendId << std::endl;
            }
        }
        return recommendedFriends;
    }

    // Get�ӿ�
    std::vector<WeChatGroupLhy*> getJoinedGroups() const { return joinedGroups; }
    bool getIsBoundWithQQ() const { return isBoundWithQQ; }
    std::string getBindQQId() const { return bindQQId; }


    WeChatGroupLhy* createGroup(const std::string& groupId, const std::string& groupName);

};

#endif // WECHAT_SERVICE_LHY_H