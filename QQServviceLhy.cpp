#include "QQServiceLhy.h"
#include <iostream>

// �������з������ֲ���...

// ����������QQȺʵ��
QQGroupLhy* QQServiceLhy::createGroup(const std::string& groupId, const std::string& groupName) {
    // ���ȺID�Ƿ��Ѵ���
    for (const auto& group : joinedGroups) {
        if (group->getGroupId() == groupId) {
            std::cout << "����ʧ�ܣ�ȺID�Ѵ��ڣ�" << std::endl;
            return nullptr;
        }
    }

    // ������Ⱥ����ǰ�û�ΪȺ��
    QQGroupLhy* newGroup = new QQGroupLhy(groupId, groupName, user);

    // �������߼���Ⱥ��
    newGroup->addMember(user);
    joinedGroups.push_back(newGroup);

    std::cout << "QQȺ�����ɹ���ȺID��" << groupId << "��Ⱥ���ƣ�" << groupName << std::endl;
    return newGroup;
}
