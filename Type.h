#ifndef _____TYPE_____
#define _____TYPE_____

#include <stdint.h>
#include <string>
#include <memory>
#include <memory.h>
const int NETWORK_BUF_SIZE = 1024 * 16;

using ui8 = uint8_t;
using i16 = int16_t;
using ui16 = uint16_t;
using i32 = int32_t;
using ui32 = uint32_t;
using i64 = int64_t;
using ui64 = uint64_t;

const ui16 SYSPING_REQ = 0xFFFA;// 65530
const ui16 SYSPING_ACK = 0xFFFB;// 65531
const ui16 PROTOCOL_VERSION_NTF = 0xFFFC;// 65532
const ui16 PROTOCOL_VERSION_AVAILABLE_NTF = 0xFFFD;// 65533
const ui16 KCP_READY_NTF = 0xFFF0;// 65529
const ui16 KCP_CLOSE = 0xFFEF;// 65528

namespace nicehero 
{
	struct Binary
	{
		Binary() {}
		Binary(ui32 s, const void* data) 
			:m_Size(s)
		{
			if (s > 0)
			{
				m_Data = std::unique_ptr<char[]>(new char[m_Size]);
				memcpy(m_Data.get(), data, m_Size);
			}
		}
		ui32 m_Size = 0;
		std::unique_ptr<char[]> m_Data;
	};

}


#endif

