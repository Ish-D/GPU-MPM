// Copyright (C) 2018-2024, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#ifndef __TELLUSIM_CORE_SOCKET_H__
#define __TELLUSIM_CORE_SOCKET_H__

#include <core/TellusimStream.h>

/*
 */
namespace Tellusim {
	
	/**
	 * Socket class
	 */
	class TS_API Socket : public Stream {
			
			TS_DECLARE_PTR(Socket, 2)
			
		public:
			
			/// Socket type
			enum Type {
				TypeStream = 0,
				TypeDatagram,
				NumTypes,
			};
			
			explicit Socket(Type type = TypeStream);
			virtual ~Socket();
			
			/// open/close socket
			bool open(uint16_t port, uint16_t num = 32);
			bool open(const char *name, uint16_t port);
			bool open(const String &name, uint16_t port);
			void close();
			
			/// stream socket
			bool connect(uint32_t sec, uint32_t usec = 0);
			virtual bool accept(Socket &socket);
			
			/// socket operations
			bool select(uint32_t sec, uint32_t usec = 0);
			
			/// socket timeout
			bool setTimeout(uint32_t sec);
			uint32_t getTimeout() const;
			
			/// socket blocking
			bool setBlock(bool block);
			bool getBlock() const;
			
			/// sockey delay
			bool setDelay(bool delay);
			bool getDelay() const;
			
			/// socket parameters
			void setName(const char *name);
			void setName(const String &name);
			uint16_t getPort() const;
			int32_t getFD() const;
			Type getType() const;
			
			/// socket utils
			static String getAddress(const char *delimiter = nullptr);
	};
	
	/**
	 * SocketSSL class
	 */
	class TS_API SocketSSL : public Socket {
			
			TS_DECLARE_PTR_1(SocketSSL, Socket, 0)
			
		public:
			
			SocketSSL();
			virtual ~SocketSSL();
			
			/// stream socket
			bool handshake(const char *name = nullptr);
			virtual bool accept(SocketSSL &socket);
			virtual bool accept(Socket &socket);
			
			/// socket certificate
			bool load(Stream &stream);
			bool load(const char *name);
			bool load(const String &name);
			
			/// socket status
			bool isConnected() const;
	};
}

#endif /* __TELLUSIM_CORE_SOCKET_H__ */
