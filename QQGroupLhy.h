#ifndef QQ_GROUP_LHY_H
#define QQ_GROUP_LHY_H

#include "BaseGroupLhy.h"
#include <vector>
#include <string>
#include <algorithm>
#include <iostream>

// QQȺ���֧ࣨ����ʱ�����顢������Ⱥ������Ա�ƶȣ�
class QQGroupLhy : public BaseGroupLhy {
private:
    std::vector<QQGroupLhy*> tempSubGroups;  // ��ʱ�������б���Ⱥ��
    std::vector<std::string> adminIds;       // ����ԱID�б���Ⱥ���⣩

public:
    // ���캯��
    QQGroupLhy(std::string id, std::string name, BaseUserLhy* owner)
        : BaseGroupLhy(id, name, owner) {
    }

    ~QQGroupLhy() override {
        // ����ʱ�ͷ���ʱ�������ڴ�
        for (auto subGroup : tempSubGroups) {
            delete subGroup;
        }
    }

    // ʵ��Ⱥ����ӿڣ�QQȺ֧��������Ⱥ���򻯣�������ˣ�
    bool addMember(BaseUserLhy* user) override {
        if (user == nullptr) return false;
        std::string userId = user->getId();

        if (isMember(userId)) {
            std::cout << "[QQȺ] " << user->getNickname() << "��" << userId << "������Ⱥ��" << std::endl;
            return false;
        }

        members[userId] = user;
        user->addGroupId(id);
        std::cout << "[QQȺ] " << user->getNickname() << "��" << userId << "��������Ⱥ�ɹ�����ǰȺ��Ա����" << getMemberCount() << std::endl;
        return true;
    }

    // ʵ��Ⱥ����ӿڣ��Ƴ�Ⱥ��Ա��Ⱥ��/����Ա�ɲ�����
    bool deleteMember(std::string userId) override {
        if (!isMember(userId)) {
            std::cout << "[QQȺ] �û�" << userId << "����Ⱥ��" << std::endl;
            return false;
        }

        // ������Ȩ�ޣ�Ⱥ�������Ա��
        std::string operatorId = owner->getId();
        bool isAdmin = (std::find(adminIds.begin(), adminIds.end(), operatorId) != adminIds.end());
        if (operatorId != userId && !isAdmin) {
            std::cout << "[QQȺ] ��Ⱥ��/����Ա���Ƴ���Ա" << std::endl;
            return false;
        }

        // �Ƴ���Ա
        BaseUserLhy* user = members[userId];
        members.erase(userId);
        user->removeGroupId(id);
        std::cout << "[QQȺ] " << user->getNickname() << "��" << userId << "���ѱ��Ƴ�����ǰȺ��Ա����" << getMemberCount() << std::endl;
        return true;
    }

    // ʵ��Ⱥ����ӿڣ����ҳ�Ա���޸��ṹ���󶨣�����C++14��
    std::vector<BaseUserLhy*> searchMember(std::string keyword) override {
        std::vector<BaseUserLhy*> result;
        // �õ���������map������ṹ���󶨣�����E0020����
        for (auto it = members.begin(); it != members.end(); ++it) {
            std::string userId = it->first;    // ��ȡ�����û�ID��
            BaseUserLhy* user = it->second;    // ��ȡֵ���û�ָ�룩
            // ģ��ƥ��ID���ǳ�
            if (userId.find(keyword) != std::string::npos || user->getNickname().find(keyword) != std::string::npos) {
                result.push_back(user);
            }
        }

        if (result.empty()) {
            std::cout << "[QQȺ] δ�ҵ������ؼ���\"" << keyword << "\"�ĳ�Ա" << std::endl;
        }
        else {
            std::cout << "[QQȺ] �ҵ�" << result.size() << "�������ؼ���\"" << keyword << "\"�ĳ�Ա��" << std::endl;
            for (auto user : result) {
                std::cout << "  - " << user->getNickname() << "��" << user->getId() << "��" << std::endl;
            }
        }
        return result;
    }

    // ʵ�ֲ��컯�ӿڣ�QQȺ������ʱ������
    bool isTempGroupAllowed() const override {
        return true;
    }

    // QQȺ���У�������ʱ�����飨���Ĺ��ܣ�����Ⱥ��ְ��
    QQGroupLhy* createTempSubGroup(std::string subGroupName, BaseUserLhy* subOwner) {
        std::string subGroupId = id + "_temp_" + std::to_string(tempSubGroups.size() + 1);
        QQGroupLhy* subGroup = new QQGroupLhy(subGroupId, subGroupName, subOwner);
        tempSubGroups.push_back(subGroup);
        std::cout << "[QQȺ] ��ʱ������\"" << subGroupName << "\"��ID��" << subGroupId << "�������ɹ�" << std::endl;
        return subGroup;
    }

    // QQȺ���У���ɢ��ʱ������
    bool dissolveTempSubGroup(std::string subGroupId) {
        for (auto it = tempSubGroups.begin(); it != tempSubGroups.end(); ++it) {
            if ((*it)->getGroupId() == subGroupId) {
                delete* it;
                tempSubGroups.erase(it);
                std::cout << "[QQȺ] ��ʱ�����飨ID��" << subGroupId << "����ɢ�ɹ�" << std::endl;
                return true;
            }
        }
        std::cout << "[QQȺ] δ�ҵ���ʱ�����飨ID��" << subGroupId << "��" << std::endl;
        return false;
    }

    // QQȺ���У�����Ա����
    bool addAdmin(std::string userId) {
        if (!isMember(userId) || userId == owner->getId()) {
            std::cout << "[QQȺ] ��ӹ���Աʧ�ܣ��û�����Ⱥ�л�ΪȺ��" << std::endl;
            return false;
        }
        if (std::find(adminIds.begin(), adminIds.end(), userId) != adminIds.end()) {
            std::cout << "[QQȺ] �û�" << userId << "���ǹ���Ա" << std::endl;
            return false;
        }
        adminIds.push_back(userId);
        std::cout << "[QQȺ] �û�" << userId << "�����Ϊ����Ա" << std::endl;
        return true;
    }

    bool removeAdmin(std::string userId) {
        auto it = std::find(adminIds.begin(), adminIds.end(), userId);
        if (it == adminIds.end()) {
            std::cout << "[QQȺ] �û�" << userId << "���ǹ���Ա" << std::endl;
            return false;
        }
        adminIds.erase(it);
        std::cout << "[QQȺ] �û�" << userId << "���Ƴ�����Ա���" << std::endl;
        return true;
    }
};

#endif // QQ_GROUP_LHY_H