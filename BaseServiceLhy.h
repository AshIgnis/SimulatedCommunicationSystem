#ifndef BASE_SERVICE_LHY_H
#define BASE_SERVICE_LHY_H

#include "BaseUserLhy.h"
#include <vector>
#include <string>
#include <iostream>


class BaseServiceLhy {
private:
    bool isLoggedIn;                      // �����¼״̬����Ϊ˽�У�

protected:
    BaseUserLhy* user;                    // �������û�����
    // ��������̬��Ա��������
    static std::vector<BaseServiceLhy*> allServices;  // ����
    //virtual std::string getServiceType() const = 0;

public:
    BaseServiceLhy(BaseUserLhy* user) : user(user), isLoggedIn(false) {
        allServices.push_back(this);
    }

    virtual ~BaseServiceLhy() = 0;

    // ���Ľӿڣ���¼��ͬ��

    virtual std::string getServiceType() const = 0;   // �������ͽӿ�

    static std::vector<BaseServiceLhy*>& getAllServices() {
        return allServices;
    }

    virtual bool login(std::string verifyInfo) = 0;
    virtual void logout() {
        isLoggedIn = false;
        // �޸�������ɷ��� user���˴����������� user->getNickname()
        std::cout << "[" << getServiceType() << "] " << user->getNickname() << "���˳���¼" << std::endl;
    }

    void syncLogin() {
        if (!isLoggedIn) return;
        std::cout << "\n[��¼ͬ��] " << user->getNickname() << "����������ʼ�Զ���¼..." << std::endl;

        // ʹ�ù��нӿڷ��ʣ����ֱ�ӷ��� allServices
        for (auto service : getAllServices()) {
            if (service != this && !service->isLoggedIn) {
                service->isLoggedIn = true;
                std::cout << "[��¼ͬ��] " << service->getServiceType() << "���Զ���¼" << std::endl;
            }
        }
        std::cout << "[��¼ͬ��] ���з����¼���\n" << std::endl;
    }

    // ������������������ʵ��
    static BaseServiceLhy* createService(std::string serviceType, BaseUserLhy* user);

    // ���з��ʽӿڣ��ⲿ������� user��ͨ���ýӿڣ���ѡ��������ӣ�
    BaseUserLhy* getUser() const {
        return user;
    }

    // Get/Set �ӿ�
    bool getIsLoggedIn() const { return isLoggedIn; }
    void setIsLoggedIn(bool status) { isLoggedIn = status; }
};

// ��̬��Ա��ʼ��
//std::vector<BaseServiceLhy*> BaseServiceLhy::allServices;

#endif // BASE_SERVICE_LHY_H