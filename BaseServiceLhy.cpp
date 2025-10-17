#include "BaseServiceLhy.h"
#include "QQServiceLhy.h"
#include "WeChatServiceLhy.h"
#include <iostream>
#include <algorithm>
#include <cctype>  // ����toupper�����Դ�Сд��


std::vector<BaseServiceLhy*> BaseServiceLhy::allServices;


// ��������������ָ�����͵ķ���
BaseServiceLhy* BaseServiceLhy::createService(std::string serviceType, BaseUserLhy* user) {
    if (user == nullptr) {
        std::cout << "[���񹤳�] ����ʧ�ܣ��û�����Ϊ��" << std::endl;
        return nullptr;
    }

    // ���Դ�Сд��֧��"qq"/"QQ"/"wx"/"WeChat"�����룩
    for (auto& c : serviceType) {
        c = toupper(c);
    }

    if (serviceType == "QQ") {
        return new QQServiceLhy(user);
    }
    else if (serviceType == "WECHAT" || serviceType == "WX") {
        return new WeChatServiceLhy(user);
    }
    else {
        std::cout << "[���񹤳�] ����ʧ�ܣ���֧�ֵķ������ͣ�" << serviceType << "����֧��QQ/WeChat��" << std::endl;
        return nullptr;
    }
}

// ���ി����������ʵ�֣��ӷ����б��Ƴ���ǰʵ����
BaseServiceLhy::~BaseServiceLhy() {
    auto it = std::find(allServices.begin(), allServices.end(), this);
    if (it != allServices.end()) {
        allServices.erase(it);
    }
}