#include "Node.hh"

using namespace BeeCoLL;

Node::Node()
{

}

Node::~Node()
{

}

uint64_t
Node::GetUniqueAddress()
{
    uint64_t address;
    // Puts the least significant number in the least significant part of the address.
    address = m_SL;
    // Shifts by 32 bits and puts SH in address by OR operation.
    address |= static_cast<uint64_t>(m_SH) << 32;

    return address;
}

uint16_t
Node::GetNetworkAddress()
{
    return m_MY;
}

std::string
Node::GetNodeIdentifier()
{
    return m_NI;
}

uint16_t
Node::GetPANIdentifier()
{
    // Check if the ID is in auto (set to 0).
    if (m_ID == 0)
    {
        // Return the Operating PAN ID.
        return m_OP;
    }
    // Return PAN ID.
    return m_ID;
}

void
Node::SetUniqueAddress(uint64_t new_addr)
{
    m_SL = new_addr;
    m_SH = new_addr >> 32;
}

void
Node::SetNetworkAddr(uint16_t new_addr)
{
    m_MY = new_addr;
}

void
Node::SetNodeIdentifier(const std::string& new_id)
{
    m_NI = new_id;
}

void
Node::SetPANIdentifier(uint16_t new_id)
{
    m_ID = new_id;
}

uint8_t
Node::GetNodeType()
{
    return m_node_type;
}

void
Node::SetNodeType(uint8_t node_type)
{
    m_node_type = node_type;
}
