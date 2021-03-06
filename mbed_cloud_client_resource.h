#ifndef MBED_CLOUD_CLIENT_RESOURCE_H
#define MBED_CLOUD_CLIENT_RESOURCE_H

#include "mbed.h"
#include "simple-mbed-cloud-client.h"
#include "mbed-client/m2mstring.h"

namespace M2MMethod {

enum M2MMethod {
    GET    = 0x01,
    PUT    = 0x02,
    POST   = 0x04,
    DELETE = 0x08
};

};

struct mcc_resource_def {
    unsigned int object_id;
    unsigned int instance_id;
    unsigned int resource_id;
    String name;
    unsigned int method_mask;
    String value;
    bool observable;
    Callback<void(const char*)> *put_callback;
    Callback<void(void*)> *post_callback;
    Callback<void(const M2MBase&, const NoticationDeliveryStatus)> *notification_callback;
};

class SimpleMbedCloudClient;

class MbedCloudClientResource {
    public:
        MbedCloudClientResource(SimpleMbedCloudClient *client, const char *path, const char *name);

        void observable(bool observable);
        void methods(unsigned int methodMask);
        void attach_put_callback(Callback<void(const char*)> callback);
        void attach_post_callback(Callback<void(void*)> callback);
        void attach_notification_callback(Callback<void(const M2MBase&, const NoticationDeliveryStatus)> callback);
        void detach_put_callback();
        void detach_post_callback();
        void detach_notification_callback();
        void set_value(int value);
        void set_value(char *value);
        String get_value();

        void get_data(mcc_resource_def *resourceDef);
        void set_resource(M2MResource *res);

    private:
        SimpleMbedCloudClient *client;
        M2MResource *resource;
        String path;
        String name;
        String value;
        bool isObservable;
        unsigned int methodMask;

        Callback<void(const char*)> putCallback;
        Callback<void(void*)> postCallback;
        Callback<void(const M2MBase&, const NoticationDeliveryStatus)> notificationCallback;
};

#endif // MBED_CLOUD_CLIENT_RESOURCE_H
