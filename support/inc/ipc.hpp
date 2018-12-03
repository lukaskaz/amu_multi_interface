#ifndef __IPC_H__
#define __IPC_H__

#include <cstring>
#include <queue>
#include <mutex>
#include <condition_variable>

typedef enum {
    IPC_DATA_NONE = 0,
    IPC_DATA_WEB,
    IPC_DATA_SPEED,
    IPC_DATA_LIGHT,
    IPC_DATA_SNDSIGNAL
} IpcData_t;

struct ipcData {
    IpcData_t type;

    struct {
        IpcData_t type;
        int32_t request_nb;
        std::string nick;
        std::string name;
    } web;

    struct {
        IpcData_t type;
        uint8_t value;
    } speed;

    struct {
        IpcData_t type;
        uint8_t value;
    } light;

    struct {
        IpcData_t type;
        bool state;
    } sndsignal;
};

struct completeData
{
    completeData() { web.request_nb = 0, speed.value = 0, light.value = 0; sndsignal.state = false; }

    struct {
        int32_t request_nb;
        std::string nick;
        std::string name;
    } web;

    struct {
        uint8_t value;
    } speed;

    struct {
        uint8_t value;
    } light;

    struct {
        bool state;
    } sndsignal;
};

template <typename T>
class ipcDataStream
{
public:
    void get(T& item) {
        std::unique_lock<std::mutex> lock(mutex);
        while (isEmpty() == true) {
            cond_var.wait(lock);
        }

        item = data.front();
        data.pop();
    }

    void put(T& item) {
        std::unique_lock<std::mutex> lock(mutex);
        data.push(item);

        lock.unlock();
        cond_var.notify_one();
    }

    bool isEmpty(void) const { return data.empty(); }

private:
    std::queue<T> data;
    std::mutex mutex;
    std::condition_variable cond_var;
};

class ipcCommunication
{
public:
    ipcCommunication(const ipcCommunication &obj) = delete;
    ipcCommunication& operator=(ipcCommunication const&) = delete;

    static ipcCommunication &get_instance(void) {
        static ipcCommunication instance;
        return instance;
    }
    const completeData &getData(void) {
        if(isIpcPending() == true) {
            processIpc();
        }
        return complete_data;
    }

    bool isIpcPending(void) const { return (ipc.isEmpty() == false) ? true : false; }

    ipcDataStream<ipcData> &get_ipc(void) { return ipc; }
private:
    ipcDataStream<ipcData> ipc;
    ipcData tmp_data;
    completeData complete_data;

    ipcCommunication() {}
    ~ipcCommunication() {}

    void processIpc(void) {
        while(isIpcPending() == true) {
            ipc.get(tmp_data);
            switch(tmp_data.type) {
                case IPC_DATA_WEB:
                    get_web_data();
                    break;
                case IPC_DATA_SPEED:
                    get_speed_data();
                    break;
                case IPC_DATA_LIGHT:
                    get_light_data();
                    break;
                case IPC_DATA_SNDSIGNAL:
                    get_sndsignal_data();
                    break;
                default:
                    break;
            }
        }
    }

    void get_web_data(void) {
        complete_data.web.name = tmp_data.web.name;
        complete_data.web.nick = tmp_data.web.nick;
        complete_data.web.request_nb = tmp_data.web.request_nb;
    }

    void get_speed_data(void) {
        complete_data.speed.value = tmp_data.speed.value;
    }

    void get_light_data(void) {
        complete_data.light.value = tmp_data.light.value;
    }

    void get_sndsignal_data(void) {
        complete_data.sndsignal.state = tmp_data.sndsignal.state;
    }
};

#endif
