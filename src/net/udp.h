#ifndef __UDP_H__
#define __UDP_H__

#include "utils/types.h"
#include "utils/io.h"
#include "utils/bits.h"
#include "memory/memory.h"
#include "net/ipv4.h"

#define MAX_NUM_SOCKETS 65536


struct UDP_frame {
	uint16_t src_port;
	uint16_t dst_port;
	uint16_t length;
	uint16_t crc;
} __attribute__((packed));


class UDP_socket;
class User_datagram_protocol_handler {
friend class UDP_socket;
private:
	UDP_socket* socket;

public:
	User_datagram_protocol_handler();
	~User_datagram_protocol_handler();

	virtual void on_receive(uint8_t* payload, uint32_t size);
	void send(uint8_t* data, uint32_t size);
};


class User_datagram_protocol_provider;
class UDP_socket {
friend class User_datagram_protocol_provider;
private:
	uint16_t remote_port;
	uint32_t remote_ip;
	uint16_t local_port;
	uint32_t local_ip;
	bool listening;
	User_datagram_protocol_provider* backend;
	User_datagram_protocol_handler* handler;

public:
	UDP_socket(User_datagram_protocol_provider* backend);
	~UDP_socket();

	bool is_listening();

	void on_receive(uint8_t* payload, uint32_t size);
	void send(uint8_t* data, uint32_t size);
	void bind(User_datagram_protocol_handler* handler);
	void unbind(User_datagram_protocol_handler* handler);
	void disconnect();
};


class User_datagram_protocol_provider: public Internet_protocol_handler {
private:
	UDP_socket* sockets[MAX_NUM_SOCKETS];
	uint32_t num_sockets;
	uint16_t free_port;

public:
	User_datagram_protocol_provider(Internet_protocol_provider* backend);
	~User_datagram_protocol_provider();

	virtual bool on_receive(uint32_t src_ip, uint32_t dst_ip, uint8_t* buffer, uint32_t size) override;
	void send(UDP_socket* socket, uint8_t* buffer, uint32_t size);

	UDP_socket* connect(uint32_t ip, uint16_t port);
	UDP_socket* listen(uint16_t port);
	void disconnect(UDP_socket* socket);
};


#endif
