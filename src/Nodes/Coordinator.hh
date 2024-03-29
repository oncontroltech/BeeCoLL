#ifndef BEECOLL_NODE_COORDINATOR_HH
#define BEECOLL_NODE_COORDINATOR_HH

#ifdef _WIN32
    #ifdef BEECOLL_BUILD
        #define BEECOLL_API __declspec(dllexport)
    #else
        #define BEECOLL_API __declspec(dllimport)
    #endif
#elif __unix__
    #ifndef BEECOLL_API
        #define BEECOLL_API
    #endif
#endif

// BeeCoLL headers
#include "../Frames/Frame.hh"
#include "Node.hh"
#include "Serial.hh"
#include "NetworkNode.hh"
#include "../ATCommands/ND.hh"

// STD headers
#include <string>
#include <bitset>
#include <vector>
#include <thread>
#include <functional>
#include <memory>

namespace BeeCoLL
{
    constexpr const std::size_t N_SUPPORTED_CHANNELS = 16;

    constexpr const uint8_t COORDINATOR_NODE_TYPE_CODE = 0;

    enum XBEE_SPECIAL_MAC_ADDR : uint64_t
    {
        XBEE_SH_ID = 0x0013A20000000000,
        BROADCAST = 0x000000000000FFFF
    };

    enum XBEE_SPECIAL_MY_ADDR : uint16_t
    {
        COORDINATOR = 0x0000,
        NOT_CONNECTED = 0xFFFE
    };

    struct CallbackRegister
    {
        uint8_t frame_id;
        uint8_t frame_response_type;
        std::function<void(const Frame&)> callback_function;
    };

    //! @brief zigbee network cordinator.
    //! 
    //! Contain function which can onlu 
    //!
    class BEECOLL_API Coordinator : public Node, public Serial
    {
    public:

        explicit Coordinator(const std::string& serial_device_path);

        Coordinator(const Coordinator& other);

        ~Coordinator();

        void SendAPICommand(const Frame& frame,
                            const std::function<void(const Frame&)>& callback_function);

        std::vector<std::shared_ptr<class NetworkNode>> GetNetworkNodes();

        void StartDiscover(bool async = false);

        void SendMessageToNode(uint64_t dest_uniq_addr,
                               const std::vector<uint8_t>& msg);
    
    private:
        int m_fd_write;

        int m_fd_write_wait;

        int m_fd_terminus;

        std::vector<uint8_t> m_ipc_msg;

        std::vector<CallbackRegister> m_callbacks;

        std::vector<std::shared_ptr<class NetworkNode>> m_network_nodes;

        std::thread m_serial_thread;

        bool m_run_serial_handler;

        void RegisterCallback(uint8_t frame_id,
                              uint8_t frame_response_type,
                              std::function<void(const Frame&)> callback_function);
        
        void RemoveCallback(uint8_t frame_id,
                            uint8_t frame_response_type);

        void InterfaceHandler();

        void Parser(const Frame& frame);

        void ATResponseHandler(const Frame& frame);

        void SetSLSH(const Frame& frame);

        void AddNode(ATCommands::ND& node_info);
        
    };
};
#endif // BEECOLL_NODE_COORDINATOR_HH