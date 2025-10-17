#ifndef USERDATAIOLHY_H
#define USERDATAIOLHY_H

#include <vector>
#include <string>
#include "BaseUserLhy.h"
#include "BaseGroupLhy.h"
#include "QQUserLhy.h"
#include "WeChatUserLhy.h"
#include "QQGroupLhy.h"
#include "WeChatGroupLhy.h"

class UserDataIOLhy {
public:
    // ���ļ������û�����
    static std::vector<BaseUserLhy*> loadUsers(const std::string& filename);

    // �����û����ݵ��ļ�
    static void saveUsers(const std::string& filename, const std::vector<BaseUserLhy*>& users);

    // ���ļ�����Ⱥ����
    static std::vector<BaseGroupLhy*> loadGroups(const std::string& filename,
        const std::vector<BaseUserLhy*>& allUsers);

    // ����Ⱥ���ݵ��ļ�
    static void saveGroups(const std::string& filename, const std::vector<BaseGroupLhy*>& groups);
};

#endif // USERDATAIOLHY_H
